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

const long fg::editor::CPreviewBspBuilder::idMenuFreeLook = ::wxNewId();
const long fg::editor::CPreviewBspBuilder::idMenuLeft = ::wxNewId();
const long fg::editor::CPreviewBspBuilder::idMenuRight = ::wxNewId();
const long fg::editor::CPreviewBspBuilder::idMenuTop = ::wxNewId();
const long fg::editor::CPreviewBspBuilder::idMenuBottom = ::wxNewId();
const long fg::editor::CPreviewBspBuilder::idMenuFront = ::wxNewId();
const long fg::editor::CPreviewBspBuilder::idMenuBack = ::wxNewId();
const long fg::editor::CPreviewBspBuilder::idMenuGridProperties = ::wxNewId();
const long fg::editor::CPreviewBspBuilder::idMenuMaterials = ::wxNewId();
const long fg::editor::CPreviewBspBuilder::idMenuCheckSnapToGrid = ::wxNewId();
const long fg::editor::CPreviewBspBuilder::idMenuCheckSnapToPolygon = ::wxNewId();

const long fg::editor::CPreviewBspBuilder::idMenuFirst = fg::editor::CPreviewBspBuilder::idMenuFreeLook;
const long fg::editor::CPreviewBspBuilder::idMenuLast = fg::editor::CPreviewBspBuilder::idMenuCheckSnapToPolygon;

using namespace fg;

//------------------------------------------------------------------------------

editor::CPreviewBspBuilder::SPolygonHolder::SPolygonHolder() :
polygon(),
drawCall(NULL),
isSelected(FG_FALSE) { }
//------------------------------------------------------------------------------

editor::CPreviewBspBuilder::SPolygonHolder::~SPolygonHolder() {
    if(drawCall)
        delete drawCall;
    drawCall = NULL;
    polygon.clear();
    isSelected = FG_FALSE;
}
//------------------------------------------------------------------------------

void editor::CPreviewBspBuilder::SPolygonHolder::render(const fgBool drawBox) {
    if(drawCall) drawCall->draw();
    if(drawBox) {
        if(drawCall)
            if(drawCall->getShaderProgram())
                drawCall->getShaderProgram()->setUniform(gfx::FG_GFX_USE_TEXTURE, 0.0f);
        gfx::primitives::drawAABBLines(polygon.bbox, colors::getColor("red"));
    }
}
//------------------------------------------------------------------------------

fgBool editor::CPreviewBspBuilder::SPolygonHolder::rayIntersect(const Vec3f& rayEye,
                                                                const Vec3f& rayDir,
                                                                Vec3f& intersectionPoint,
                                                                const fgBool bothSides) {
    return polygon.rayIntersect(rayEye, rayDir, intersectionPoint, bothSides);
}
//------------------------------------------------------------------------------

void editor::CPreviewBspBuilder::SPolygonHolder::refreshDrawCall(void) {
    if(!drawCall) {
        drawCall = new gfx::CDrawCall(FG_GFX_DRAW_CALL_EXTERNAL_ARRAY,
                                      polygon.getVertexData()->attribMask());
    }
    drawCall->setupFromVertexData(polygon.getVertexData());
    drawCall->setPrimitiveMode(gfx::PrimitiveMode::TRIANGLE_FAN);
}
//------------------------------------------------------------------------------

void editor::CPreviewBspBuilder::SPolygonHolder::setMaterial(const gfx::SMaterial* pMaterial) {
    if(!pMaterial || !drawCall)
        return;
    drawCall->setupMaterial(pMaterial);
}
//------------------------------------------------------------------------------

editor::CPreviewBspBuilder::CPreviewBspBuilder(fg::CEngineMain** pEngineMainOrig) :
base_type(pEngineMainOrig),
m_polygons(),
m_currentPolygon(NULL),
m_currentMaterial(NULL),
m_internalMaterial(NULL),
m_previewSide(FREE_LOOK),
m_bspCompiler(NULL),
m_bspFile(NULL),
m_p3DScene(NULL),
m_pCamera(NULL),
m_pResourceMgr(NULL),
m_pGuiMain(NULL),
m_pGuiDrawer(NULL),
m_stateFlags(NONE),
m_minCamDistance(200.0f),
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

    m_internalMaterial = new gfx::SMaterial();
    m_internalMaterial->name.clear();
    m_internalMaterial->name.append("InternalMaterial");
    m_internalMaterial->shaderName = "sPlainEasy";
    m_internalMaterial->ambientTexName = "brick_13.jpg";
    m_internalMaterial->setTextureRepeat(FG_TRUE);

    m_previewSide = FREE_LOOK;
    m_bspCompiler = new gfx::CBspCompiler();
    m_bspFile = new gfx::CBspFile();
    refreshInternals();

    wxMenu *previewsSubMenu = new wxMenu();
    previewsSubMenu->Append(idMenuFreeLook,
                            _("Free look"),
                            _("Switch camera to free look"),
                            wxITEM_NORMAL);
    previewsSubMenu->Append(idMenuLeft,
                            _("Left"),
                            _("Switch camera to look at left side"),
                            wxITEM_NORMAL);
    previewsSubMenu->Append(idMenuRight,
                            _("Right"),
                            _("Switch camera to look at right side"),
                            wxITEM_NORMAL);
    previewsSubMenu->Append(idMenuTop,
                            _("Top"),
                            _("Switch camera to look at top"),
                            wxITEM_NORMAL);
    previewsSubMenu->Append(idMenuBottom,
                            _("Bottom"),
                            _("Switch camera to look from bottom"),
                            wxITEM_NORMAL);
    previewsSubMenu->Append(idMenuFront,
                            _("Front"),
                            _("Switch camera to look at front"),
                            wxITEM_NORMAL);
    previewsSubMenu->Append(idMenuBack,
                            _("Back"),
                            _("Switch camera to look from back"),
                            wxITEM_NORMAL);
    m_contextMenu.AppendSubMenu(previewsSubMenu,
                                _("Change camera"),
                                wxEmptyString);

    m_contextMenu.Append(idMenuGridProperties,
                         _("Grid properties"),
                         wxEmptyString,
                         wxITEM_NORMAL);

    m_contextMenu.Append(idMenuMaterials,
                         _("Materials"),
                         wxEmptyString,
                         wxITEM_NORMAL);

    m_contextMenu.Append(idMenuCheckSnapToGrid,
                         _("Snap to grid"),
                         _("Snap click and motion events to ground grid"),
                         wxITEM_CHECK);

    m_contextMenu.Append(idMenuCheckSnapToPolygon,
                         _("Snap to polygon"),
                         _("Snap click and motion events to the closest polygon edge"),
                         wxITEM_CHECK);

    m_contextMenu.Check(idMenuCheckSnapToGrid, true);
    m_contextMenu.Check(idMenuCheckSnapToPolygon, false);
    setSnapToGrid(FG_TRUE);
    setSnapToPolygon(FG_FALSE);

    /*m_contextMenu.Connect(idMenuFreeLook, wxEVT_COMMAND_MENU_SELECTED,
                          (wxObjectEventFunction) & self_type::OnContextItemSelected);
    m_contextMenu.Connect(idMenuLeft, wxEVT_COMMAND_MENU_SELECTED,
                          (wxObjectEventFunction) & self_type::OnContextItemSelected);
    m_contextMenu.Connect(idMenuRight, wxEVT_COMMAND_MENU_SELECTED,
                          (wxObjectEventFunction) & self_type::OnContextItemSelected);
    m_contextMenu.Connect(idMenuTop, wxEVT_COMMAND_MENU_SELECTED,
                          (wxObjectEventFunction) & self_type::OnContextItemSelected);
    m_contextMenu.Connect(idMenuBottom, wxEVT_COMMAND_MENU_SELECTED,
                          (wxObjectEventFunction) & self_type::OnContextItemSelected);
    m_contextMenu.Connect(idMenuFront, wxEVT_COMMAND_MENU_SELECTED,
                          (wxObjectEventFunction) & self_type::OnContextItemSelected);
    m_contextMenu.Connect(idMenuBack, wxEVT_COMMAND_MENU_SELECTED,
                          (wxObjectEventFunction) & self_type::OnContextItemSelected);*/
    m_contextMenu.Bind(wxEVT_COMMAND_MENU_SELECTED, &self_type::OnContextItemSelected, this,
                       idMenuFirst, idMenuLast);
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
    m_currentPolygon = NULL;
    m_currentMaterial = NULL;
    if(m_internalMaterial) {
        delete m_internalMaterial;
        m_internalMaterial = NULL;
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
        //m_p3DScene->setHideAll(FG_TRUE);
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
        m_pResourceMgr = getEngineMain()->getResourceManager();
        m_pGuiMain = getEngineMain()->getGuiMain();
        m_pGuiDrawer = getEngineMain()->getGuiMain()->getDrawer();

        refreshMaterial(m_internalMaterial);
    } else {
        m_p3DScene = NULL;
        m_pCamera = NULL;
        m_pResourceMgr = NULL;
        m_pGuiMain = NULL;
        m_pGuiDrawer = NULL;
    }
}
//------------------------------------------------------------------------------

void editor::CPreviewBspBuilder::refreshMaterial(gfx::SMaterial* pMaterial) {
    if(!pMaterial || !m_pResourceMgr || !getEngineMain())
        return;

    if(!pMaterial->shaderProgram && pMaterial->shaderName.length()) {
        pMaterial->shaderProgram =
                getEngineMain()->getGfxMain()->getShaderManager()->get(pMaterial->shaderName);
    }

    resource::CResource* pResource = NULL;
    // Ambient texture handle lookup
    pResource = m_pResourceMgr->request(pMaterial->ambientTexName);
    if(pResource) {
        if(pResource->getResourceType() == resource::TEXTURE) {
            pMaterial->ambientTex = static_cast<gfx::CTextureResource *>(pResource);
        }
    }
    // Diffuse texture handle lookup
    pResource = m_pResourceMgr->request(pMaterial->diffuseTexName);
    if(pResource) {
        if(pResource->getResourceType() == resource::TEXTURE) {
            pMaterial->diffuseTex = static_cast<gfx::CTextureResource *>(pResource);
        }
    }
    // Specular texture handle lookup
    pResource = m_pResourceMgr->request(pMaterial->specularTexName);
    if(pResource) {
        if(pResource->getResourceType() == resource::TEXTURE) {
            pMaterial->specularTex = static_cast<gfx::CTextureResource *>(pResource);
        }
    }
    // Normal texture handle lookup
    pResource = m_pResourceMgr->request(pMaterial->normalTexName);
    if(pResource) {
        if(pResource->getResourceType() == resource::TEXTURE) {
            pMaterial->normalTex = static_cast<gfx::CTextureResource *>(pResource);
        }
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

void editor::CPreviewBspBuilder::createPolygonQuad(const Vec3f& begin,
                                                   const Vec3f& end,
                                                   gfx::SPolygon & polygon,
                                                   const fgBool uvTiled) {
    if(!m_p3DScene)
        return;
    // Quad top is the same direction as the current grid normal
    Vec2f uv1(0, 0); // lower left corner
    Vec2f uv2(1, 0); // lower right corner
    Vec2f uv3(1, 1); // upper right corner
    Vec2f uv4(0, 1); // upper left corner
    Vector3f pos, normal;
    Vec2f ratio(1.0f, 1.0f);
    float height = m_p3DScene->getGroundGridCellSize();
    float length = math::abs(math::length(end - begin));
    const float uvStep = m_p3DScene->getGroundGridCellSize();
    const Vec3f& gridNormal = m_p3DScene->getGroundGrid().n;
    Color4f color(1.0f, 1.0f, 1.0f, 1.0f);
    polygon.clear();
    gfx::CVertexData* pVertexData = polygon.getVertexData();
    //
    // 4--3     (0,1)--(1,1)
    // |  |       |      |
    // 1--2     (0,0)--(1,0)
    //

    // 1
    pos = begin;
    if(uvTiled) {
        ratio.x = length / uvStep;
        ratio.y = height / uvStep;
    }
    pVertexData->append(pos, normal, uv1, color);

    // 2
    pos = end;
    if(uvTiled) {
        uv2.x = ratio.x;
    }
    pVertexData->append(pos, normal, uv2, color);

    // 3
    pos = end + gridNormal*height;
    if(uvTiled) {
        uv3.x = ratio.x;
        uv3.y = ratio.y;
    }
    pVertexData->append(pos, normal, uv3, color);

    // 4
    pos = begin + gridNormal*height;
    if(uvTiled) {
        uv4.y = ratio.y;
    }
    pVertexData->append(pos, normal, uv4, color);

    polygon.recalculate();
}
//------------------------------------------------------------------------------

void editor::CPreviewBspBuilder::updatePolygonQuad(const Vec3f& begin,
                                                   const Vec3f& end,
                                                   gfx::SPolygon & polygon,
                                                   const fgBool uvTiled) {
    if(!m_p3DScene)
        return;
    //if(polygon.getVertexData()->empty())
    //    return;
    if(polygon.getVertexData()->size() != 4)
        return;
    Vec2f ratio(1.0f, 1.0f);
    const float uvStep = m_p3DScene->getGroundGridCellSize();
    Vector3f pos;
    float height = 0.0f;
    float length = 0.0f;
    const Vec3f& gridNormal = m_p3DScene->getGroundGrid().n;
    const Vec3f gridPoint = m_p3DScene->getGroundGrid().d * gridNormal;
    gfx::CVertexData4v* pVertexData = (gfx::CVertexData4v*)polygon.getVertexData();
    //
    // 4--3     (0,1)--(1,1)
    // |  |       |      |
    // 1--2     (0,0)--(1,0)
    //
    if(isActionPolygonResize()) {
        Vec3f newEnd = end;
        // need to calculate current height
        height = m_p3DScene->getGroundGrid().fastDistance(end);
        const Vec3f lenVecDiff = pVertexData->at(2).position - pVertexData->at(3).position;
        length = math::length(lenVecDiff);
        if(isResizeProportional()) {
            const Vec3f lengthDir = math::normalize(lenVecDiff);
            const float diff = math::abs(length - height);
            if(length > height) {
                newEnd = newEnd + gridNormal*diff;
                height += diff;
            } else {
                // length <= height
                height -= diff;
                newEnd = newEnd - gridNormal*diff;
            }
        }
        // now this is resize so the 1 point is determined by begin
        // 1
        pos = begin;
        pVertexData->at(0).position = pos;
        // 2
        pos = newEnd - gridNormal*height;
        pVertexData->at(1).position = pos;
        // 3 - this is intersection point
        pos = newEnd;
        pVertexData->at(2).position = pos;
        // 4
        pos = begin + gridNormal*height;
        pVertexData->at(3).position = pos;

        gfx::Planef tmp;
        tmp.n = polygon.n;
        tmp.axis = polygon.axis;
        tmp.d = polygon.d;
        // update normal and BBOX
        polygon.recalculate();
        polygon.n = tmp.n;
        polygon.axis = tmp.axis;
        polygon.d = tmp.d;
    } else {
        height = m_p3DScene->getGroundGridCellSize();
        if(uvTiled) {
            length = math::abs(math::length(end - begin));
        }
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
    if(uvTiled) {
        ratio.x = length / uvStep;
        ratio.y = height / uvStep;
        // 2
        pVertexData->at(1).uv.x = ratio.x;
        // 3
        pVertexData->at(2).uv.x = ratio.x;
        pVertexData->at(2).uv.y = ratio.y;
        // 4
        pVertexData->at(3).uv.y = ratio.y;
    }
}
//------------------------------------------------------------------------------

fgBool editor::CPreviewBspBuilder::displayHandler(void* systemData, void* userData) {
    if(!userData)
        return FG_FALSE;
    // user data is the pointer to the CPreviewBspBuilder object
    // system data should be the pointer to the CEngineMain object
    CPreviewBspBuilder *pSelf = static_cast<CPreviewBspBuilder*>(userData);
    fg::CEngineMain* pEngineMain = static_cast<fg::CEngineMain*>(systemData);
    fgBool uvTiled = FG_TRUE;
    if(!pSelf->isActive())
        return FG_FALSE;
    if(!pSelf->m_p3DScene)
        return FG_FALSE;

    //--------------------------------------------------------------------------
    if(pSelf->isMousePressed()) {
        pSelf->setMousePressed(FG_FALSE);
        if(pSelf->isActionPolygonDraw()) {
            pSelf->m_polygons.push_back(new SPolygonHolder());
            unsigned int n = pSelf->m_polygons.size();
            SPolygonHolder& polygonHolder = *(pSelf->m_polygons[n - 1]);
            polygonHolder.refreshDrawCall();
            polygonHolder.drawCall->setMVP(pSelf->m_p3DScene->getMVP());
            polygonHolder.setMaterial(pSelf->m_internalMaterial);
            pSelf->m_currentPolygon = &polygonHolder.polygon;
            gfx::SPolygon& polygon = *(pSelf->m_currentPolygon);
            Vec3f begin, end;
            begin = pSelf->m_p3DScene->getGroundIntersectionPoint(0);
            end = pSelf->m_p3DScene->getGroundIntersectionPoint(1);
            pSelf->createPolygonQuad(begin, end, polygon, uvTiled);

            polygonHolder.drawCall->refreshDrawingInfo(polygonHolder.getVertexData());
        }
    }
    //--------------------------------------------------------------------------
    if(pSelf->isMouseMotion()) {
        pSelf->setMouseMotion(FG_FALSE);
        if(pSelf->m_currentPolygon && pSelf->isActionPolygonDraw()) {
            const Vec3f& gridNormal = pSelf->m_p3DScene->getGroundGrid().n;
            const float gridHeight = pSelf->m_p3DScene->getGroundGrid().d;
            const gfx::SPlaneGridf::Axis axis = pSelf->m_p3DScene->getGroundGrid().axis;
            Vec3f begin = pSelf->m_p3DScene->getGroundIntersectionPoint(0),
                    end = pSelf->m_p3DScene->getGroundIntersectionPoint(1);
            if(pSelf->isSnapToGrid()) {
                pSelf->m_p3DScene->getGroundGrid().snapTo(begin,
                                                          begin,
                                                          0.2f,
                                                          FG_TRUE, FG_FALSE);
                pSelf->m_p3DScene->getGroundGrid().snapTo(end,
                                                          end,
                                                          0.2f,
                                                          FG_TRUE, FG_FALSE);
            }
            gfx::SPolygon& polygon = *(pSelf->m_currentPolygon);
            if(!pSelf->isActionPolygonResize()) {
                pSelf->updatePolygonQuad(begin, end, polygon, uvTiled);
            } else {
                // Polygon needs to be resized - need to get intersection point
                // for the current ray and current polygon plane
                Vec3f rayDir, rayEye, intersectionPoint;
                pSelf->m_p3DScene->getPickSelectionRayInfo(rayEye, rayDir);
                fgBool intersectionStatus = polygon.rayIntersect(rayEye,
                                                                 rayDir,
                                                                 intersectionPoint,
                                                                 FG_TRUE);
                if(intersectionStatus) {
                    Vec3f diff = intersectionPoint - gridNormal*gridHeight;
                    float distance = pSelf->m_p3DScene->getGroundGrid().fastDistance(intersectionPoint);
                    if(distance < 0.0f)
                        intersectionPoint -= gridNormal * distance;

                    // ray intersects, now have a point -> need to resize
                    // meaning that lower two points stay on the same line
                    // in other words - the polygons plane does not change
                    if(pSelf->isSnapToGrid()) {
                        pSelf->m_p3DScene->getGroundGrid().snapTo(intersectionPoint,
                                                                  intersectionPoint,
                                                                  0.2f,
                                                                  FG_TRUE, FG_FALSE);
                    }
                    // This will work - > the polygon resize flag is active
                    pSelf->updatePolygonQuad(begin, intersectionPoint, polygon, uvTiled);
                }
            }
        }
    }
    //--------------------------------------------------------------------------
    if(pSelf->isMouseReleased()) {
        pSelf->setMouseReleased(FG_FALSE);
        if(pSelf->isActionPolygonDraw()) {
            pSelf->setActionPolygonDraw(FG_FALSE);
            pSelf->setActionPolygonResize(FG_FALSE);
            pSelf->setResizeProportional(FG_FALSE);
        }
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
        SPolygonHolder& polygonHolder = *polygons[i];
        if(polygonHolder.drawCall) {
            if(polygonHolder.drawCall->getShaderProgram() == NULL)
                polygonHolder.drawCall->setShaderProgram(pProgram);
            polygonHolder.render(FG_TRUE);
        }
    }

    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool editor::CPreviewBspBuilder::mouseHandler(event::CArgumentList * argv) {
    if(!argv || !m_isActive || getEngineMain() == NULL)
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
    static int xLast = 128000;
    static int yLast = 128000;
    int xRel = 0, yRel = 0;
    if(xLast > 100000 && yLast > 100000) {
        xLast = pMouse->x;
        yLast = pMouse->y;
    }
    xRel = -(xLast - pMouse->x);
    yRel = -(yLast - pMouse->y);
    xLast = pMouse->x;
    yLast = pMouse->y;

    if(type == event::MOUSE_PRESSED) {
        // mouse clicked - begin new polygon
        // set as current
        // this will be executed in the UPDATE
        // set special toggle
        // Update polygons etc... in DISPLAY - after 3dScene sort calls
        if(pMouse->buttonID == FG_POINTER_BUTTON_LEFT)
            setMousePressed(FG_TRUE);
    }
    event::CInputHandler* pInputHandler = getEngineMain()->getInputHandler();
    // is control button down? only control (not alt nor shift)
    const fgBool isOnlyCtrlDown = pInputHandler->isControlDown(FG_TRUE);
    const fgBool isCtrlDown = pInputHandler->isControlDown(FG_FALSE);
    const fgBool isShiftDown = pInputHandler->isShiftDown(FG_FALSE);
    const fgBool isAltDown = pInputHandler->isAltDown(FG_FALSE);
    const fgBool isGuiDown = pInputHandler->isGuiDown(FG_FALSE);
    const fgBool isModDown = (fgBool)!!(isCtrlDown || isShiftDown || isAltDown || isGuiDown);

    if((type == event::MOUSE_PRESSED ||
        type == event::MOUSE_MOTION) &&
       pMouse->buttonID == FG_POINTER_BUTTON_LEFT) {
        if(isOnlyCtrlDown && type == event::MOUSE_PRESSED) {
            // activate drawing polygon action only on mouse press event
            // and ctrl button down - then the CTRL button can be released
            // as long the mouse button is being held down
            setActionPolygonDraw(FG_TRUE);
        } else if(!isGuiDown && type == event::MOUSE_MOTION && isActionPolygonDraw()) {
            setActionPolygonResize(FG_FALSE);
            setResizeProportional(FG_FALSE);
            if(!isAltDown && isShiftDown) {
                // shift is down - mouse motion
                setActionPolygonResize(FG_TRUE);
            } else if(isAltDown && isShiftDown) {
                // shift + alt - mouse motion
                setActionPolygonResize(FG_TRUE);
                setResizeProportional(FG_TRUE);
            }
        }
    }

    if(type == event::MOUSE_MOTION) {
        // mouse moved - update current polygon
        setMouseMotion(FG_TRUE);
        if(!isActionPolygonDraw() && m_pCamera &&
           pMouse->buttonID == FG_POINTER_BUTTON_MIDDLE &&
           pMouse->pressed) {

            if(!isModDown) {
                // pan move
                if(xRel < 0) {
                    for(unsigned int i = 0; i < math::abs(xRel); i++) {
                        m_pCamera->moveRight();
                    }
                } else {
                    for(unsigned int i = 0; i < math::abs(xRel); i++) {
                        m_pCamera->moveLeft();
                    }
                }
                if(yRel < 0) {
                    for(unsigned int i = 0; i < math::abs(yRel); i++) {
                        m_pCamera->moveBackward();
                    }
                } else {
                    for(unsigned int i = 0; i < math::abs(yRel); i++) {
                        m_pCamera->moveForward();
                    }
                }
            } else if(isOnlyCtrlDown && yRel != 0) {
                // only control pressed, middle button and motion
                // change grid offset proportionally
                m_p3DScene->getGroundGrid().d += (float)yRel * 2.0f;
                float gLevel = m_p3DScene->getGroundGrid().d;
                const float cell = m_p3DScene->getGroundGrid().cellSize / 2.0f;
                const int steps = (int)gLevel / cell;
                const float stepsMin = (float)steps * cell;
                const float threshold = 0.2f;
                float diffRatio = (gLevel - stepsMin) / cell;
                float sign = 1.0f;
                if(diffRatio < 0.0f) {
                    diffRatio *= -1.0f;
                    sign = -1.0f;
                }
                if(diffRatio < threshold)
                    gLevel = stepsMin;
                if(diffRatio > 1.0f - threshold)
                    gLevel = stepsMin + cell * sign;
                m_p3DScene->getGroundGrid().d = gLevel;
            }

        }
    } // if event mouse motion

    if(type == event::MOUSE_RELEASED) {
        setMouseReleased(FG_TRUE);
        xLast = 128000;
        yLast = 128000;
        //setActionPolygonDraw(FG_FALSE);
        //setActionPolygonResize(FG_FALSE);
        //setResizeProportional(FG_FALSE);
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool editor::CPreviewBspBuilder::keyboardHandler(event::CArgumentList * argv) {
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

    if(pKey->isMod()) {
        const fgBool isShiftDown = pKey->isShiftDown();
        const fgBool isAltDown = pKey->isAltDown();
        const fgBool isGuiDown = pKey->isGuiDown();

        if(!isGuiDown && isActionPolygonDraw()) {
            setActionPolygonResize(FG_FALSE);
            setResizeProportional(FG_FALSE);
            if(!isAltDown && isShiftDown) {
                // shift is down
                setActionPolygonResize(FG_TRUE);
            } else if(isAltDown && isShiftDown) {
                // shift + alt
                setActionPolygonResize(FG_TRUE);
                setResizeProportional(FG_TRUE);
            }
            // when the state of the mod key changes
            // force motion flag for true so the drawing will be updated
            setMouseMotion(FG_TRUE);
        }
    }

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

void editor::CPreviewBspBuilder::OnContextItemSelected(wxCommandEvent & event) {
    const long id = (long)event.GetId();

    if(id == idMenuFreeLook) {
        this->activatePreviewSide(FREE_LOOK);
    } else if(id == idMenuLeft) {
        this->activatePreviewSide(LEFT);
    } else if(id == idMenuRight) {
        this->activatePreviewSide(RIGHT);
    } else if(id == idMenuTop) {
        this->activatePreviewSide(TOP);
    } else if(id == idMenuBottom) {
        this->activatePreviewSide(BOTTOM);
    } else if(id == idMenuFront) {
        this->activatePreviewSide(FRONT);
    } else if(id == idMenuBack) {
        this->activatePreviewSide(BACK);
    } else if(id == idMenuGridProperties) {
    } else if(id == idMenuMaterials) {
    } else if(id == idMenuCheckSnapToGrid) {
        this->setSnapToGrid((fgBool)this->m_contextMenu.IsChecked(id));
    } else if(id == idMenuCheckSnapToPolygon) {
        this->setSnapToPolygon((fgBool)this->m_contextMenu.IsChecked(id));
    }
}
//------------------------------------------------------------------------------
