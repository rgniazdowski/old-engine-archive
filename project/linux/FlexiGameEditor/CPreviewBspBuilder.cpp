/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/* 
 * File:   CPreviewBspBuilder.cpp
 * Author: vigilant
 * 
 * Created on May 14, 2015, 2:17 AM
 */

#include "fgEngineMain.h"
#include "fgDebugConfig.h"
// Scene includes
#include "GFX/Scene/fgGfx3DScene.h"
#include "GFX/Scene/fgGfxBspCompiler.h"
#include "GFX/Scene/fgGfxBspTree.h"
#include "GFX/Scene/fgGfxBspNode.h"
#include "GFX/Scene/fgGfxBspFile.h"
// The rest of GFX
#include "GFX/fgGfxCameraAnimation.h"
#include "GFX/fgGfxDrawingBatch.h"
#include "GFX/fgGfxPrimitives.h"
#include "GFX/fgGfxPlane.h"
#include "GFX/fgGfxPolygon.h"
// GUI
#include "GUI/fgGuiDrawer.h"
// Color data
#include "fgColors.h"
// Internal
#include "CPreviewBspBuilder.h"
#include "CEngineGfxCanvas.h"

const long fg::editor::CPreviewBspBuilder::idBspPreviewFreeLook = ::wxNewId();
const long fg::editor::CPreviewBspBuilder::idBspPreviewLeft = ::wxNewId();
const long fg::editor::CPreviewBspBuilder::idBspPreviewRight = ::wxNewId();
const long fg::editor::CPreviewBspBuilder::idBspPreviewTop = ::wxNewId();
const long fg::editor::CPreviewBspBuilder::idBspPreviewBottom = ::wxNewId();
const long fg::editor::CPreviewBspBuilder::idBspPreviewFront = ::wxNewId();
const long fg::editor::CPreviewBspBuilder::idBspPreviewBack = ::wxNewId();

using namespace fg;

//------------------------------------------------------------------------------

editor::CPreviewBspBuilder::CPreviewBspBuilder(fg::CEngineMain** pEngineMainOrig) :
base_type(pEngineMainOrig),
m_polygons(),
m_currentPolygon(NULL),
m_previewSide(FREE_LOOK),
m_bspCompiler(NULL),
m_bspFile(NULL),
m_p3DScene(NULL),
m_pCamera(NULL),
m_pGuiDrawer(NULL),
m_minCamDistance(200.0f),
m_mousePressed(FG_FALSE),
m_mouseMotion(FG_FALSE),
m_mouseReleased(FG_FALSE),
m_displayShotCB(NULL),
m_updateShotCB(NULL),
m_renderShotCB(NULL),
m_mouseHandlerCB(NULL),
m_keyboardHandlerCB(NULL) {
    {
        using namespace fg::event;
        m_displayShotCB = new CPlainFunctionCallback(&CPreviewBspBuilder::displayHandler,
                                                     this);

        m_updateShotCB = new CPlainFunctionCallback(&CPreviewBspBuilder::updateHandler,
                                                    this);

        m_renderShotCB = new CPlainFunctionCallback(&CPreviewBspBuilder::renderHandler,
                                                    this);

        m_mouseHandlerCB = new CMethodCallback<self_type>(this,
                                                          &CPreviewBspBuilder::mouseHandler);

        m_keyboardHandlerCB = new CMethodCallback<self_type>(this,
                                                             &CPreviewBspBuilder::keyboardHandler);
    }
    m_previewSide = FREE_LOOK;
    m_bspCompiler = new gfx::CBspCompiler();
    m_bspFile = new gfx::CBspFile();
    refreshInternals();

    wxMenu *previewsSubMenu = new wxMenu();
    previewsSubMenu->Append(idBspPreviewFreeLook,
                            _("Free look"),
                            _("Switch camera to free look"),
                            wxITEM_NORMAL);
    previewsSubMenu->Append(idBspPreviewLeft,
                            _("Left"),
                            _("Switch camera to look at left side"),
                            wxITEM_NORMAL);
    previewsSubMenu->Append(idBspPreviewRight,
                            _("Right"),
                            _("Switch camera to look at right side"),
                            wxITEM_NORMAL);
    previewsSubMenu->Append(idBspPreviewTop,
                            _("Top"),
                            _("Switch camera to look at top"),
                            wxITEM_NORMAL);
    previewsSubMenu->Append(idBspPreviewBottom,
                            _("Bottom"),
                            _("Switch camera to look from bottom"),
                            wxITEM_NORMAL);
    previewsSubMenu->Append(idBspPreviewFront,
                            _("Front"),
                            _("Switch camera to look at front"),
                            wxITEM_NORMAL);
    previewsSubMenu->Append(idBspPreviewBack,
                            _("Back"),
                            _("Switch camera to look from back"),
                            wxITEM_NORMAL);
    m_contextMenu.AppendSubMenu(previewsSubMenu,
                                _("Change camera"),
                                wxEmptyString);

    /*m_contextMenu.Connect(idBspPreviewFreeLook, wxEVT_COMMAND_MENU_SELECTED,
                          (wxObjectEventFunction) & self_type::OnContextItemSelected);
    m_contextMenu.Connect(idBspPreviewLeft, wxEVT_COMMAND_MENU_SELECTED,
                          (wxObjectEventFunction) & self_type::OnContextItemSelected);
    m_contextMenu.Connect(idBspPreviewRight, wxEVT_COMMAND_MENU_SELECTED,
                          (wxObjectEventFunction) & self_type::OnContextItemSelected);
    m_contextMenu.Connect(idBspPreviewTop, wxEVT_COMMAND_MENU_SELECTED,
                          (wxObjectEventFunction) & self_type::OnContextItemSelected);
    m_contextMenu.Connect(idBspPreviewBottom, wxEVT_COMMAND_MENU_SELECTED,
                          (wxObjectEventFunction) & self_type::OnContextItemSelected);
    m_contextMenu.Connect(idBspPreviewFront, wxEVT_COMMAND_MENU_SELECTED,
                          (wxObjectEventFunction) & self_type::OnContextItemSelected);
    m_contextMenu.Connect(idBspPreviewBack, wxEVT_COMMAND_MENU_SELECTED,
                          (wxObjectEventFunction) & self_type::OnContextItemSelected);*/
    m_contextMenu.Bind(wxEVT_COMMAND_MENU_SELECTED, &self_type::OnContextItemSelected, this,
                       idBspPreviewFreeLook, idBspPreviewBack);
}
//------------------------------------------------------------------------------

editor::CPreviewBspBuilder::~CPreviewBspBuilder() {
    FG_LOG_DEBUG("WX: BSP Editor Preview mode: Destroying internal data...");
    refreshInternals();
    unregisterCallbacks();
    if(m_displayShotCB) {
        delete m_displayShotCB;
        m_displayShotCB = NULL;
    }
    if(m_updateShotCB) {
        delete m_updateShotCB;
        m_updateShotCB = NULL;
    }
    if(m_renderShotCB) {
        delete m_renderShotCB;
        m_renderShotCB = NULL;
    }
    if(m_mouseHandlerCB) {
        delete m_mouseHandlerCB;
        m_mouseHandlerCB = NULL;
    }
    if(m_keyboardHandlerCB) {
        delete m_keyboardHandlerCB;
        m_keyboardHandlerCB = NULL;
    }
    m_isActive = FG_FALSE;
    m_previewID = 0;
    m_name.clear();
    if(m_bspFile) {
        delete m_bspFile;
        m_bspFile = NULL;
    }
    if(m_bspCompiler) {
        delete m_bspCompiler;
        m_bspCompiler = NULL;
    }
}
//------------------------------------------------------------------------------

fgBool editor::CPreviewBspBuilder::activate(fgBool toggle) {
    refreshInternals();
    // Engine main instance is not initialized - cannot do anything
    if(!getEngineMain())
        return FG_FALSE;
    if(toggle) {
        fgBool status = registerCallbacks();
        if(!status)
            return FG_FALSE;
        m_isActive = FG_TRUE;
    } else {
        fgBool status = unregisterCallbacks();
        m_isActive = FG_FALSE;
    }

    if(m_isActive) {
        fg::g_DebugConfig.gameFreeLook = false;
        m_p3DScene->setHideAll(FG_TRUE);
        m_p3DScene->setPickSelectionOnClick(FG_TRUE);
        m_p3DScene->setPickSelectionBox(FG_FALSE);
        m_p3DScene->setPickSelectionGroup(FG_FALSE);
        m_p3DScene->setShowGroundGrid(FG_TRUE);
        activatePreviewSide(m_previewSide);
    } else {
        m_p3DScene->setHideAll(FG_FALSE);
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void editor::CPreviewBspBuilder::refreshInternals(void) {
    if(getEngineMain()) {
        m_p3DScene = getEngineMain()->getGfxMain()->get3DScene();
        m_pCamera = getEngineMain()->getGfxMain()->get3DSceneCamera();
        m_pGuiDrawer = getEngineMain()->getGuiMain()->getDrawer();
    } else {
        m_p3DScene = NULL;
        m_pCamera = NULL;
        m_pGuiDrawer = NULL;
    }
}
//------------------------------------------------------------------------------

void editor::CPreviewBspBuilder::activatePreviewSide(PreviewSide previewSide) {
    if(!getEngineMain() || !m_p3DScene || !isActive())
        return;
    gfx::Planef plane;
    switch(previewSide) {
        case PreviewSide::FREE_LOOK:
            m_p3DScene->setGroundPlane(gfx::Planef::Y, m_p3DScene->getGroundLevel());
            m_pCamera->setType(gfx::CCameraAnimation::FREE);
            // camera on the side, looks at the center
            m_pCamera->setAngleV(0.0f); // Y pos
            m_pCamera->setAngleH(0.0f); // X pos
            m_pCamera->setEye(Vec3f(0.0f, 50.0f, m_minCamDistance));
            m_pCamera->update();
            break;
        case PreviewSide::LEFT:
            plane.n = Vec3f(-1.0f, 0.0f, 0.0f);
            plane.d = m_p3DScene->getGroundLevel();
            m_p3DScene->setGroundPlane(plane);
            m_pCamera->setType(gfx::CCameraAnimation::FREE);
            // camera on the left side, looks to the right
            // X -> -150.0f
            m_pCamera->setAngleV(FG_EPSILON); // Y pos
            m_pCamera->setAngleH(M_PIF / 2.0f); // X pos
            m_pCamera->setEye(Vec3f(-m_minCamDistance, 50.0f, 0.0f));
            m_pCamera->update();
            break;
        case PreviewSide::RIGHT:
            plane.n = Vec3f(1.0f, 0.0f, 0.0f);
            plane.d = m_p3DScene->getGroundLevel();
            m_p3DScene->setGroundPlane(plane);
            m_pCamera->setType(gfx::CCameraAnimation::FREE);
            // camera on the right side, looks to the left
            m_pCamera->setAngleV(FG_EPSILON);
            m_pCamera->setAngleH(-M_PIF / 2.0f);
            m_pCamera->setEye(Vec3f(m_minCamDistance, 50.0f, 0.0f));
            m_pCamera->update();
            break;
        case PreviewSide::TOP:
            plane.n = Vec3f(0.0f, 1.0f, 0.0f);
            plane.d = m_p3DScene->getGroundLevel();
            m_p3DScene->setGroundPlane(plane);
            m_pCamera->setType(gfx::CCameraAnimation::FREE);
            // camera over, points down
            m_pCamera->setAngleV(-M_PIF / 2.0f);
            m_pCamera->setAngleH(FG_EPSILON);
            m_pCamera->setEye(Vec3f(0.0f, m_minCamDistance, 0.0f));
            m_pCamera->update();
            break;
        case PreviewSide::BOTTOM:
            plane.n = Vec3f(0.0f, -1.0f, 0.0f);
            plane.d = m_p3DScene->getGroundLevel();
            m_p3DScene->setGroundPlane(plane);
            m_pCamera->setType(gfx::CCameraAnimation::FREE);
            // camera below, points up
            m_pCamera->setAngleV(M_PIF / 2.0f);
            m_pCamera->setAngleH(FG_EPSILON);
            m_pCamera->setEye(Vec3f(0.0f, -m_minCamDistance, 0.0f));
            m_pCamera->update();
            break;
        case PreviewSide::FRONT:
            plane.n = Vec3f(0.0f, 0.0f, 1.0f);
            plane.d = m_p3DScene->getGroundLevel();
            m_p3DScene->setGroundPlane(plane);
            m_pCamera->setType(gfx::CCameraAnimation::FREE);
            // camera at +Z looks at -Z
            m_pCamera->setAngleV(FG_EPSILON);
            m_pCamera->setAngleH(M_PIF);
            m_pCamera->setEye(Vec3f(0.0f, 0.0f, m_minCamDistance));
            m_pCamera->update();
            break;
        case PreviewSide::BACK:
            plane.n = Vec3f(0.0f, 0.0f, -1.0f);
            plane.d = m_p3DScene->getGroundLevel();
            m_p3DScene->setGroundPlane(plane);
            m_pCamera->setType(gfx::CCameraAnimation::FREE);
            // camera at -Z looks at +Z
            m_pCamera->setAngleV(FG_EPSILON);
            m_pCamera->setAngleH(0.0f);
            m_pCamera->setEye(Vec3f(0.0f, 0.0f, -m_minCamDistance));
            m_pCamera->update();
            break;
    }
    m_previewSide = previewSide;
}
//------------------------------------------------------------------------------

fgBool editor::CPreviewBspBuilder::registerCallbacks(void) {
    if(!getEngineMain())
        return FG_FALSE;
    FG_LOG_DEBUG("WX: BSP Editor: registering callbacks...");
    fg::CEngineMain* pEngineMain = getEngineMain();
    if(!pEngineMain->isRegistered(fg::event::DISPLAY_SHOT, m_displayShotCB)) {
        pEngineMain->addCallback(fg::event::DISPLAY_SHOT, m_displayShotCB);
    }
    if(!pEngineMain->isRegistered(fg::event::UPDATE_SHOT, m_updateShotCB)) {
        pEngineMain->addCallback(fg::event::UPDATE_SHOT, m_updateShotCB);
    }
    if(!pEngineMain->isRegistered(fg::event::RENDER_SHOT, m_renderShotCB)) {
        pEngineMain->addCallback(fg::event::RENDER_SHOT, m_renderShotCB);
    }

    if(!pEngineMain->isRegistered(fg::event::MOUSE_MOTION, m_mouseHandlerCB)) {
        pEngineMain->addCallback(fg::event::MOUSE_MOTION, m_mouseHandlerCB);
    }
    if(!pEngineMain->isRegistered(fg::event::MOUSE_PRESSED, m_mouseHandlerCB)) {
        pEngineMain->addCallback(fg::event::MOUSE_PRESSED, m_mouseHandlerCB);
    }
    if(!pEngineMain->isRegistered(fg::event::MOUSE_RELEASED, m_mouseHandlerCB)) {
        pEngineMain->addCallback(fg::event::MOUSE_RELEASED, m_mouseHandlerCB);
    }

    if(!pEngineMain->isRegistered(fg::event::KEY_UP, m_keyboardHandlerCB)) {
        pEngineMain->addCallback(fg::event::KEY_UP, m_keyboardHandlerCB);
    }
    // Remember that Key down is called continuously
    if(!pEngineMain->isRegistered(fg::event::KEY_DOWN, m_keyboardHandlerCB)) {
        pEngineMain->addCallback(fg::event::KEY_DOWN, m_keyboardHandlerCB);
    }
    // Key pressed is called once (for the first press the down/pressed is thrown together)
    if(!pEngineMain->isRegistered(fg::event::KEY_PRESSED, m_keyboardHandlerCB)) {
        pEngineMain->addCallback(fg::event::KEY_PRESSED, m_keyboardHandlerCB);
    }
    m_callbacksRegistered = FG_TRUE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool editor::CPreviewBspBuilder::unregisterCallbacks(void) {
    if(!getEngineMain())
        return FG_FALSE;
    FG_LOG_DEBUG("WX: BSP Editor: removing callbacks...");
    fg::CEngineMain* pEngineMain = getEngineMain();
    pEngineMain->removeCallback(fg::event::DISPLAY_SHOT, m_displayShotCB);
    pEngineMain->removeCallback(fg::event::UPDATE_SHOT, m_updateShotCB);
    pEngineMain->removeCallback(fg::event::RENDER_SHOT, m_renderShotCB);

    pEngineMain->removeCallback(fg::event::MOUSE_MOTION, m_mouseHandlerCB);
    pEngineMain->removeCallback(fg::event::MOUSE_PRESSED, m_mouseHandlerCB);
    pEngineMain->removeCallback(fg::event::MOUSE_RELEASED, m_mouseHandlerCB);

    pEngineMain->removeCallback(fg::event::KEY_UP, m_keyboardHandlerCB);
    pEngineMain->removeCallback(fg::event::KEY_DOWN, m_keyboardHandlerCB);
    pEngineMain->removeCallback(fg::event::KEY_PRESSED, m_keyboardHandlerCB);
    m_callbacksRegistered = FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool editor::CPreviewBspBuilder::engineInit(void* systemData, void* userData) {
    if(!systemData || !userData)
        return FG_FALSE;
    // user data is the pointer to the CPreviewBspBuilder object
    // system data is the pointer to the gfx engine canvas holder object
    // it's from where the programInit/Quit events are thrown (internal cb)
    CPreviewBspBuilder *pSelf = static_cast<CPreviewBspBuilder*>(userData);
    CEngineGfxCanvas* pGfxCanvas = static_cast<CEngineGfxCanvas*>(systemData);
    fg::CEngineMain* pEngineMain = pGfxCanvas->getEngineMain();
    pSelf->refreshInternals();
    pSelf->registerCallbacks();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool editor::CPreviewBspBuilder::engineDestroy(void* systemData, void* userData) {
    if(!systemData || !userData)
        return FG_FALSE;
    // user data is the pointer to the CPreviewBspBuilder object
    // system data is the pointer to the gfx engine canvas holder object
    // it's from where the programInit/Quit events are thrown (internal cb)
    CPreviewBspBuilder *pSelf = static_cast<CPreviewBspBuilder*>(userData);
    CEngineGfxCanvas* pGfxCanvas = static_cast<CEngineGfxCanvas*>(systemData);
    fg::CEngineMain* pEngineMain = pGfxCanvas->getEngineMain();
    pSelf->refreshInternals();
    pSelf->unregisterCallbacks();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void editor::CPreviewBspBuilder::createPolygonQuad(gfx::SPolygon& polygon) { }
//------------------------------------------------------------------------------

void editor::CPreviewBspBuilder::createPolygonQuad(const Vec3f& begin,
                                                   const Vec3f& end,
                                                   gfx::SPolygon& polygon) {
    if(!m_p3DScene)
        return;
    // Quad top is the same direction as the current grid normal
    const Vec2f uv1(0, 0); // lower left corner
    const Vec2f uv2(1, 0); // lower right corner
    const Vec2f uv3(1, 1); // upper right corner
    const Vec2f uv4(0, 1); // upper left corner
    Vector3f pos, normal;
    float height = m_p3DScene->getGroundGridCellSize() / 2.0f;
    const Vec3f& gridNormal = m_p3DScene->getGroundGrid().n;
    Color4f color(1.0f, 1.0f, 1.0f, 1.0f);
    polygon.clear();
    gfx::CVertexData* pVertexData = polygon.getVertexData();
    //
    // 4--3
    // |  |
    // 1--2
    //

    // 1
    pos = begin;
    pVertexData->append(pos, normal, uv1, color);

    // 2
    pos = end;
    pVertexData->append(pos, normal, uv2, color);

    // 3
    pos = end + gridNormal*height;
    pVertexData->append(pos, normal, uv3, color);

    // 4
    pos = begin + gridNormal*height;
    pVertexData->append(pos, normal, uv4, color);

    polygon.recalculate();
}
//------------------------------------------------------------------------------

void editor::CPreviewBspBuilder::updatePolygonQuad(const Vec3f& begin,
                                                   const Vec3f& end,
                                                   gfx::SPolygon& polygon) {
    if(!m_p3DScene)
        return;
    //if(polygon.getVertexData()->empty())
    //    return;
    if(polygon.getVertexData()->size() != 4)
        return;
    Vector3f pos;
    float height = m_p3DScene->getGroundGridCellSize() / 2.0f;
    const Vec3f& gridNormal = m_p3DScene->getGroundGrid().n;
    gfx::CVertexData4v* pVertexData = (gfx::CVertexData4v*)polygon.getVertexData();
    //
    // 4--3
    // |  |
    // 1--2
    //

    // 1
    pos = begin;
    pVertexData->at(0).position = pos;

    // 2
    pos = end;
    pVertexData->at(1).position = pos;

    // 3
    pos = end + gridNormal*height;
    pVertexData->at(2).position = pos;

    // 4
    pos = begin + gridNormal*height;
    pVertexData->at(3).position = pos;

    // update normal and BBOX
    polygon.recalculate();
}
//------------------------------------------------------------------------------

fgBool editor::CPreviewBspBuilder::displayHandler(void* systemData, void* userData) {
    if(!userData)
        return FG_FALSE;
    // user data is the pointer to the CPreviewBspBuilder object
    // system data should be the pointer to the CEngineMain object
    CPreviewBspBuilder *pSelf = static_cast<CPreviewBspBuilder*>(userData);
    fg::CEngineMain* pEngineMain = static_cast<fg::CEngineMain*>(systemData);
    if(!pSelf->isActive())
        return FG_FALSE;
    if(!pSelf->m_p3DScene)
        return FG_FALSE;

    if(pSelf->m_mousePressed) {
        pSelf->m_mousePressed = FG_FALSE;
        gfx::SPolygon polygon;
        Vec3f begin, end;
        begin = pSelf->m_p3DScene->getGroundIntersectionPoint(0);
        end = pSelf->m_p3DScene->getGroundIntersectionPoint(1);
        pSelf->createPolygonQuad(begin, end, polygon);
        pSelf->m_polygons.push_back(polygon);
        unsigned int n = pSelf->m_polygons.size();
        pSelf->m_currentPolygon = &(pSelf->m_polygons[n - 1]);
    }
    if(pSelf->m_mouseMotion) {
        pSelf->m_mouseMotion = FG_FALSE;
        if(pSelf->m_currentPolygon) {
            Vec3f begin, end;
            pSelf->m_p3DScene->getGroundGrid().snapTo(pSelf->m_p3DScene->getGroundIntersectionPoint(0),
                                                      begin,
                                                      0.2f, 
                                                      FG_TRUE, FG_FALSE);
            pSelf->m_p3DScene->getGroundGrid().snapTo(pSelf->m_p3DScene->getGroundIntersectionPoint(1),
                                                      end,
                                                      0.2f,
                                                      FG_TRUE, FG_FALSE);

            gfx::SPolygon& polygon = *pSelf->m_currentPolygon;
            pSelf->updatePolygonQuad(begin, end, polygon);
        }
    }
    if(pSelf->m_mouseReleased) {
        pSelf->m_mouseReleased = FG_FALSE;
        if(pSelf->m_currentPolygon) {
            pSelf->m_currentPolygon = NULL;
        }
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool editor::CPreviewBspBuilder::updateHandler(void* systemData, void* userData) {
    if(!userData)
        return FG_FALSE;
    // user data is the pointer to the CPreviewBspBuilder object
    // system data should be the pointer to the CEngineMain object
    CPreviewBspBuilder *pSelf = static_cast<CPreviewBspBuilder *>(userData);
    fg::CEngineMain* pEngineMain = static_cast<fg::CEngineMain*>(systemData);
    if(!pSelf->isActive())
        return FG_FALSE;

    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool editor::CPreviewBspBuilder::renderHandler(void* systemData, void* userData) {
    if(!userData)
        return FG_FALSE;
    // user data is the pointer to the CPreviewBspBuilder object
    // system data should be the pointer to the CEngineMain object
    CPreviewBspBuilder *pSelf = static_cast<CPreviewBspBuilder *>(userData);
    fg::CEngineMain* pEngineMain = static_cast<fg::CEngineMain*>(systemData);
    if(!pSelf->isActive())
        return FG_FALSE;
    if(!pSelf->m_p3DScene || !pSelf->m_pCamera)
        return FG_FALSE;

    fg::base::CManager* pShaderMgrBase = pSelf->m_p3DScene->getShaderManager();
    fg::gfx::CShaderManager* pShaderMgr = static_cast<fg::gfx::CShaderManager*>(pShaderMgrBase);
    fg::gfx::CShaderProgram* pProgram = pShaderMgr->getCurrentProgram();
    if(pProgram) {
        pSelf->m_p3DScene->getCamera()->update();
        pSelf->m_p3DScene->getMVP()->setCamera(pSelf->m_p3DScene->getCamera());
        pSelf->m_p3DScene->getMVP()->setPerspective(45.0f, pEngineMain->getGfxMain()->getMainWindow()->getAspect());
        pSelf->m_p3DScene->getMVP()->calculate(Matrix4f());
        pProgram->setUniform(pSelf->m_p3DScene->getMVP());
    }
    PolygonsVec& polygons = pSelf->m_polygons;
    const unsigned int n = polygons.size();
    for(unsigned int i = 0; i < n; i++) {
        gfx::SPolygon& polygon = polygons[i];
        gfx::primitives::drawVertexData(polygon.getVertexData(),
                                        FG_GFX_POSITION_BIT | FG_GFX_COLOR_BIT,
                                        gfx::PrimitiveMode::TRIANGLE_FAN);
        gfx::primitives::drawAABBLines(polygon.bbox, fg::colors::getColor("red"));
    }

    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool editor::CPreviewBspBuilder::mouseHandler(event::CArgumentList* argv) {
    if(!argv || !m_isActive)
        return FG_FALSE;
    event::SEvent *pEvent = (event::SEvent *)argv->getValueByID(0);
    if(!pEvent)
        return FG_FALSE;
    const event::EventType type = pEvent->code;
    if(type != event::MOUSE_MOTION &&
       type != event::MOUSE_PRESSED &&
       type != event::MOUSE_RELEASED) {
        return FG_FALSE;
    }
    event::SMouse* pMouse = reinterpret_cast<event::SMouse*>(pEvent);

    if(type == event::MOUSE_PRESSED) {
        // mouse clicked - begin new polygon
        // set as current
        // this will be executed in the UPDATE
        // set special toggle
        // Update polygons etc... in DISPLAY - after 3dScene sort calls
        m_mousePressed = FG_TRUE;
    }

    if(type == event::MOUSE_MOTION) {
        // mouse moved - update current polygon
        m_mouseMotion = FG_TRUE;
    }

    if(type == event::MOUSE_RELEASED) {
        m_mouseReleased = FG_TRUE;
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool editor::CPreviewBspBuilder::keyboardHandler(event::CArgumentList* argv) {
    if(!argv || !m_isActive || !m_pCamera)
        return FG_FALSE;
    event::SEvent* pEvent = (event::SEvent *)argv->getValueByID(0);
    if(!pEvent)
        return FG_FALSE;
    const event::EventType type = pEvent->code;
    if(type != event::KEY_DOWN && type != event::KEY_UP) {
        return FG_FALSE;
    }
    event::SKey* pKey = reinterpret_cast<event::SKey*>(pEvent);
    event::KeyVirtualCode keyCode = pKey->keyCode;

    if(!pKey->pressed) {
        return FG_FALSE;
    }
        
    if(keyCode == event::FG_KEY_W) {
        m_pCamera->moveForward();
    }
    if(keyCode == event::FG_KEY_S) {
        m_pCamera->moveBackward();       
    }
    if(keyCode == event::FG_KEY_A) {
        m_pCamera->moveLeft();
    }
    if(keyCode == event::FG_KEY_D) {
        m_pCamera->moveRight();
    }
    if(keyCode == event::FG_KEY_SPACE) {
        m_pCamera->moveUp();
    }
    if(keyCode == event::FG_KEY_X) {
        m_pCamera->moveDown();
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void editor::CPreviewBspBuilder::OnContextItemSelected(wxCommandEvent& event) {
    const long id = (long)event.GetId();

    if(id == idBspPreviewFreeLook)
        this->activatePreviewSide(FREE_LOOK);
    else if(id == idBspPreviewLeft)
        this->activatePreviewSide(LEFT);
    else if(id == idBspPreviewRight)
        this->activatePreviewSide(RIGHT);
    else if(id == idBspPreviewTop)
        this->activatePreviewSide(TOP);
    else if(id == idBspPreviewBottom)
        this->activatePreviewSide(BOTTOM);
    else if(id == idBspPreviewFront)
        this->activatePreviewSide(FRONT);
    else if(id == idBspPreviewBack)
        this->activatePreviewSide(BACK);
}
//------------------------------------------------------------------------------
