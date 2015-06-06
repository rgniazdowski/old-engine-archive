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
const long fg::editor::CPreviewBspBuilder::idMenuCheckModePolySelection = ::wxNewId();
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

editor::CPreviewBspBuilder::CPreviewBspBuilder(wxWindow* pParent,
                                               fg::CEngineMain** pEngineMainOrig) :
base_type(pEngineMainOrig),
m_polygons(),
m_currentPolygon(NULL),
m_currentMaterial(NULL),
m_internalMaterial(NULL),
m_selectionMaterial(NULL),
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
m_preRenderShotCB(NULL),
m_updateShotCB(NULL),
m_renderShotCB(NULL),
m_mouseHandlerCB(NULL),
m_keyboardHandlerCB(NULL),
m_pMainFrame(pParent),
m_materialsEditDialog(NULL) {
    {
        using namespace fg::event;
        m_preRenderShotCB = new CPlainFunctionCallback(&CPreviewBspBuilder::preRenderHandler,
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
    m_internalMaterial->ambientTexName = "brick_14.jpg";
    m_internalMaterial->setCullFace(FG_TRUE);
    m_internalMaterial->setTextureRepeat(FG_TRUE);

    m_selectionMaterial = new gfx::SMaterial();
    m_selectionMaterial->name.clear();
    m_selectionMaterial->name.append("SelectionMaterial");
    m_selectionMaterial->shaderName = "sOrthoEasy";
    m_selectionMaterial->setCullFace(FG_FALSE);
    m_selectionMaterial->blendMode = gfx::BlendMode::BLEND_ADDITIVE;

    m_previewSide = FREE_LOOK;
    m_bspCompiler = new gfx::CBspCompiler();
    m_bspFile = new gfx::CBspFile();
    // #FIXME
    m_bspCompiler->getBspTreePtr()->getMaterials().push_back(*m_internalMaterial);

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

    m_contextMenu.AppendSeparator();

    m_contextMenu.Append(idMenuCheckModePolySelection,
                         _("Polygon selection mode"),
                         _("Activate polygon selection mode"),
                         wxITEM_CHECK);

    m_contextMenu.Append(idMenuCheckSnapToGrid,
                         _("Snap to grid"),
                         _("Snap click and motion events to ground grid"),
                         wxITEM_CHECK);

    m_contextMenu.Append(idMenuCheckSnapToPolygon,
                         _("Snap to polygon"),
                         _("Snap click and motion events to the closest polygon edge"),
                         wxITEM_CHECK);

    m_contextMenu.Check(idMenuCheckModePolySelection, false);
    m_contextMenu.Check(idMenuCheckSnapToGrid, true);
    m_contextMenu.Check(idMenuCheckSnapToPolygon, false);
    setSnapToGrid(FG_TRUE);
    setSnapToPolygon(FG_FALSE);

    m_contextMenu.Bind(wxEVT_COMMAND_MENU_SELECTED, &self_type::OnContextItemSelected, this,
                       idMenuFirst, idMenuLast);

    m_materialsEditDialog = new CBspMaterialsEditDialog(m_pMainFrame);

    refreshInternals();
}
//------------------------------------------------------------------------------

editor::CPreviewBspBuilder::~CPreviewBspBuilder() {
    FG_LOG_DEBUG("WX: BSP Editor Preview mode: Destroying internal data...");
    refreshInternals();
    unregisterCallbacks();
    if(m_preRenderShotCB) {
        delete m_preRenderShotCB;
        m_preRenderShotCB = NULL;
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
    if(m_selectionMaterial) {
        delete m_selectionMaterial;
        m_selectionMaterial = NULL;
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

        setModePolygonAdd(FG_TRUE);
        setModePolygonSelect(FG_FALSE);

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
        m_polygonSelection.pMVP = getEngineMain()->getGfxMain()->get3DScene()->getMVP();
        refreshMaterial(m_internalMaterial);
        refreshMaterial(m_selectionMaterial);

        m_materialsEditDialog->setResourceManager(m_pResourceMgr);
        m_materialsEditDialog->setShaderManager(getEngineMain()->getGfxMain()->getShaderManager());
        m_materialsEditDialog->setMaterialsVector(&(m_bspCompiler->getBspTreePtr()->getMaterials()));
        m_materialsEditDialog->refreshInternals();
    } else {
        m_p3DScene = NULL;
        m_pCamera = NULL;
        m_pResourceMgr = NULL;
        m_pGuiMain = NULL;
        m_pGuiDrawer = NULL;
        m_polygonSelection.pMVP = NULL;
        m_materialsEditDialog->setResourceManager(NULL);
        m_materialsEditDialog->setShaderManager(NULL);
        //m_materialsEditDialog->setMaterialsVector(NULL);
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
    if(!pEngineMain->isRegistered(fg::event::PRERENDER_SHOT, m_preRenderShotCB)) {
        pEngineMain->addCallback(fg::event::PRERENDER_SHOT, m_preRenderShotCB);
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
    pEngineMain->removeCallback(fg::event::PRERENDER_SHOT, m_preRenderShotCB);
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

fgBool editor::CPreviewBspBuilder::preRenderHandler(void* systemData, void* userData) {
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

    //--------------------------------------------------------------------------

    if(pSelf->isModePolygonSelect() && pSelf->isPickSelectionBox() && pSelf->isMouseDown()) {
        Vec2f pos;
        Vec2f size;
        gfx::AABB2Df pickBox = pSelf->m_polygonSelection.pickBox;
        gui::CStyleContent style;
        style.setBackground(NULL).setBackground(gui::SBackground::NONE).setBackground(Color4f(1.0f, 1.0f, 1.0f, 0.5f));
        style.setBorder(gui::SBorder::Which::ALL, 2.0f).setBorder(gui::SBorder::Which::ALL, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
        style.setBorder(gui::SBorder::Which::ALL, gui::SBorder::Style::SOLID);
        pSelf->m_pGuiDrawer->appendBackground2D(pickBox, style);
        pSelf->m_pGuiDrawer->appendBorder2D(pickBox, style);
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

    if(pSelf->isModePolygonSelect()) {
        // Select polygons - check which polygon is selected
        pSelf->m_polygonSelection.init(*(pSelf->m_pCamera), pSelf->m_stateFlags);

        PolygonsVec& polygons = pSelf->m_polygons;
        PolygonsVecItor end = polygons.end();
        PolygonsVecItor it = polygons.begin();
        unsigned int polygonIndex = 0;
        for(; it != end; it++) {
            SPolygonHolder& polygon = *(*it);
            if(!pSelf->m_polygonSelection.shouldCheck)
                break;

            fgBool pickResult = pSelf->m_polygonSelection.fullCheck(pSelf,
                                                                    &polygon,
                                                                    polygonIndex);

            polygonIndex++;
        }

        pSelf->m_polygonSelection.end(pSelf->m_stateFlags);
    }

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
            if(polygonHolder.isSelected) {
                gfx::SMaterial* pTmpMaterial = polygonHolder.drawCall->getMaterial();
                //polygonHolder.drawCall->setTexture(0);
                polygonHolder.drawCall->getTexture().reset();
                polygonHolder.setMaterial(pSelf->m_selectionMaterial);
                // half transparent red color
                polygonHolder.drawCall->getShaderProgram()->use(); // force use so can update uniforms
                polygonHolder.drawCall->getShaderProgram()->setUniform(gfx::FG_GFX_CUSTOM_COLOR,
                                                                       1.0f,
                                                                       0.0f,
                                                                       0.0f,
                                                                       0.5f);
                polygonHolder.render(FG_FALSE);

                polygonHolder.drawCall->getShaderProgram()->setUniform(gfx::FG_GFX_CUSTOM_COLOR,
                                                                       1.0f,
                                                                       1.0f,
                                                                       1.0f,
                                                                       1.0f);
                polygonHolder.drawCall->getShaderProgram()->setUniform(gfx::FG_GFX_USE_TEXTURE, 1.0f);
                polygonHolder.setMaterial(pTmpMaterial);
            }
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
    const int xRel = pMouse->relX;
    const int yRel = pMouse->relY;

    if(type == event::MOUSE_PRESSED) {
        // mouse clicked - begin new polygon
        // set as current
        // this will be executed in the UPDATE
        // set special toggle
        // Update polygons etc... in DISPLAY - after 3dScene sort calls
        if(pMouse->buttonID == FG_POINTER_BUTTON_LEFT) {
            setMousePressed(FG_TRUE);
            setMouseDown(FG_TRUE);
            m_polygonSelection.init(*(m_pCamera), m_stateFlags);
            m_polygonSelection.pickPos.x = pMouse->x;
            m_polygonSelection.pickPos.y = pMouse->y;
            m_polygonSelection.pickPosBegin = m_polygonSelection.pickPos;
            m_polygonSelection.pickBegin = timesys::exact();
        }
    }
    event::CInputHandler* pInputHandler = getEngineMain()->getInputHandler();
    // is control button down? only control (not alt nor shift)
    const fgBool isOnlyCtrlDown = pInputHandler->isControlDown(FG_TRUE);
    const fgBool isCtrlDown = pInputHandler->isControlDown(FG_FALSE);
    const fgBool isShiftDown = pInputHandler->isShiftDown(FG_FALSE);
    const fgBool isAltDown = pInputHandler->isAltDown(FG_FALSE);
    const fgBool isGuiDown = pInputHandler->isGuiDown(FG_FALSE);
    const fgBool isModDown = (fgBool)!!(isCtrlDown || isShiftDown || isAltDown || isGuiDown);

    if(!isModePolygonSelect()) {
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
    }

    if(type == event::MOUSE_MOTION) {
        // mouse moved - update current polygon
        setMouseMotion(FG_TRUE);
        m_polygonSelection.pickPos.x = pMouse->x;
        m_polygonSelection.pickPos.y = pMouse->y;
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
        setMouseDown(FG_FALSE);
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

    if(pKey->isMod() && !isModePolygonSelect()) {
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
        m_materialsEditDialog->Show(true);
    } else if(id == idMenuCheckModePolySelection) {
        if(this->m_contextMenu.IsChecked(id)) {
            setPickSelectionBox(FG_TRUE);
            setPickSelectionGroup(FG_TRUE);
            setPickSelectionToggle(FG_TRUE);
            setModePolygonSelect(FG_TRUE);
            setModePolygonAdd(FG_FALSE);
        } else {
            setPickSelectionBox(FG_FALSE);
            setPickSelectionGroup(FG_FALSE);
            setPickSelectionToggle(FG_FALSE);
            setModePolygonSelect(FG_FALSE);
            setModePolygonAdd(FG_TRUE); // FIXME
        }
    } else if(id == idMenuCheckSnapToGrid) {
        this->setSnapToGrid((fgBool)this->m_contextMenu.IsChecked(id));
    } else if(id == idMenuCheckSnapToPolygon) {
        this->setSnapToPolygon((fgBool)this->m_contextMenu.IsChecked(id));
    }
}
//------------------------------------------------------------------------------

editor::CPreviewBspBuilder::SPolygonSelection::SPolygonSelection() :
pickPos(0, 0),
pickPosBegin(0, 0),
pickBox(),
rayEye(),
rayDir(),
pickBegin(-1.0f),
shouldUnselect(FG_FALSE),
shouldCheck(FG_FALSE),
isToggle(FG_FALSE),
isGroup(FG_FALSE),
checkBox(FG_FALSE),
lastSelectedPolygon(NULL),
selectedPolygons(),
projectedPoints(),
pickedPolygonsInfo(),
pMVP(NULL) {
    selectedPolygons.reserve(32);
    projectedPoints.reserve(16);
    for(unsigned int i = 0; i < 32; i++) {
        selectedPolygons[i] = NULL;
    }
    pickBegin = timesys::exact();

}
//------------------------------------------------------------------------------

editor::CPreviewBspBuilder::SPolygonSelection::~SPolygonSelection() {
    const unsigned int n = selectedPolygons.capacity();
    for(unsigned int i = 0; i < n; i++) {
        selectedPolygons[i] = NULL;
    }
    selectedPolygons.clear();
    projectedPoints.clear();
    pickedPolygonsInfo.clear();
    lastSelectedPolygon = NULL;
    shouldUnselect = FG_FALSE;
    shouldCheck = FG_FALSE;
    isToggle = FG_FALSE;
    isGroup = FG_FALSE;
    checkBox = FG_FALSE;
    pMVP = NULL;

    pickBegin = 0.0f;
    memset(&groundIntersectionPoint[0], 0, sizeof (Vector3f));
    memset(&groundIntersectionPoint[1], 0, sizeof (Vector3f));
    memset(&rayDir, 0, sizeof (Vector3f));
    memset(&rayEye, 0, sizeof (Vector3f));
    memset(&pickBox, 0, sizeof (gfx::AABB2Di));
    memset(&pickPosBegin, 0, sizeof (Vector2i));
    memset(&pickPos, 0, sizeof (Vector2i));
}
//------------------------------------------------------------------------------

void editor::CPreviewBspBuilder::SPolygonSelection::init(const gfx::CCamera& camera,
                                                         StateFlags stateFlags) {
    //
    // Polygon pick selection init
    //
    shouldCheck = FG_FALSE;
    shouldUnselect = FG_FALSE;
    isToggle = FG_FALSE;
    isGroup = FG_FALSE;

    Vector2i size;
    Vector2i pos = pickPosBegin;
    size.x = pickPos.x - pickPosBegin.x;
    size.y = pickPos.y - pickPosBegin.y;

    if(size.x < 0) {
        pos.x = pos.x + size.x;
        size.x = -1 * size.x;
    }
    if(size.y < 0) {
        pos.y = pos.y + size.y;
        size.y = -1 * size.y;
    }
    pickBox.min = pos;
    pickBox.setWidth(size.x);
    pickBox.setHeight(size.y);
    if((fgBool)!!(stateFlags & MODE_POLYGON_SELECT)) {
        shouldCheck = (fgBool)!!(stateFlags & MOUSE_DOWN) || lastSelectedPolygon;
        isToggle = (fgBool)!!(stateFlags & PICK_SELECTION_TOGGLE) && shouldCheck;
        isGroup = (fgBool)!!(stateFlags & PICK_SELECTION_GROUP);
        checkBox = (fgBool)!!(stateFlags & PICK_SELECTION_BOX);
    }
    if(shouldCheck) {
        updateRay(camera);
    }
}
//------------------------------------------------------------------------------

void editor::CPreviewBspBuilder::SPolygonSelection::end(StateFlags stateFlags) {
    if((fgBool)!!(stateFlags & MOUSE_DOWN) == 0) {
        lastSelectedPolygon = NULL;
        pickBegin = -1.0f;
        pickBox.invalidate();
        //printf("%.3f: Removing last selected node\n", timesys::exact());
    }

}
//------------------------------------------------------------------------------

void editor::CPreviewBspBuilder::SPolygonSelection::updateRay(const gfx::CCamera& camera) {
    if(!pMVP)
        return;
    const Vector2i& screenSize = gfx::context::getScreenSize();
    //if(screenCoord.x >= 0 && screenCoord.y >= 0) {
    //    pickPosition = screenCoord;
    //}
    // Step1: 3d normalised device coords
    float x = (2.0f * pickPos.x) / (float)screenSize.x - 1.0f;
    float y = 1.0f - (2.0f * pickPos.y) / (float)screenSize.y;
    //float z = -1.0f; // -1.0f?

    rayEye = camera.getEye();
    // Step 2: 4d Homogeneous Clip Coordinates
    Vector4f rayClip = Vector4f(x, y, -1.0f, 1.0f);
    // Step 3: 4d Eye (Camera) Coordinates
    Vector4f ray4dEye = math::inverse(pMVP->getRefProjMatrix()) * rayClip;
    ray4dEye.z = -1.0f;
    ray4dEye.w = 0.0f;
    // Step 4: 4d World Coordinates
    Vector4f ray4d = (math::inverse(pMVP->getViewMatrix()) * ray4dEye);
    // don't forget to normalize the vector at some point
    rayDir = math::normalize(Vector3f(ray4d.x, ray4d.y, ray4d.z));
}
//------------------------------------------------------------------------------

fgBool editor::CPreviewBspBuilder::SPolygonSelection::isPicked(SPolygonHolder* pPolygon,
                                                               SPickedPolygonInfo& pickInfo) {
    if(!pPolygon)
        return FG_FALSE;

    pickInfo.result = pPolygon->polygon.rayIntersect(rayEye, rayDir,
                                                     pickInfo.intersectionPosition,
                                                     FG_TRUE);
    if(!pickInfo.result)
        return FG_FALSE;

    pickInfo.result = pPolygon->polygon.rayIntersectTriangles(rayEye, rayDir,
                                                              pickInfo.baryPosition,
                                                              FG_TRUE);
    const Vector4i& viewport = gfx::context::getViewport();
    const Vector2i& screensize = gfx::context::getScreenSize();

    if(checkBox) {
        gfx::AABB3Df aabb;
        aabb.invalidate();
        // need to check box - that means that polygon points need to be projected
        // onto the screen and check all of them
        unsigned int n = pPolygon->size();
        projectedPoints.resize(n);
        gfx::CVertexData4v* pVertexData = (gfx::CVertexData4v*)pPolygon->getVertexData();
        if(!pVertexData || !pMVP)
            return pickInfo.result;
        for(unsigned int i = 0; i < n; i++) {

            projectedPoints[i] = math::project(pVertexData->at(i).position,
                                               pMVP->getRefViewProjMatrix(),
                                               viewport);
            aabb.merge(projectedPoints[i]);
            fgBool pointStatus = pickBox.test(projectedPoints[i].x, screensize.y - projectedPoints[i].y);
            if(pointStatus)
                pickInfo.result = FG_TRUE;
        }

        Vector2i pos, size;
        pos.x = aabb.min.x;
        pos.y = screensize.y - aabb.max.y;
        size.x = aabb.max.x - aabb.min.x;
        size.y = aabb.max.y - aabb.min.y;
        if(size.x < 0) {
            pos.x = pos.x + size.x;
            size.x = -1 * size.x;
        }
        if(size.y < 0) {
            pos.y = pos.y + size.y;
            size.y = -1 * size.y;
        }
        pickInfo.onScreen.box.min = pos;
        pickInfo.onScreen.box.setWidth(size.x);
        pickInfo.onScreen.box.setHeight(size.y);
    }

    return pickInfo.result;
}
//------------------------------------------------------------------------------

fgBool editor::CPreviewBspBuilder::SPolygonSelection::fullCheck(CPreviewBspBuilder* pBspPreview,
                                                                SPolygonHolder* pPolygon,
                                                                unsigned int polygonIndex) {
    if(!pBspPreview || !pPolygon)
        return FG_FALSE;

    pickedPolygonsInfo[polygonIndex].pPolygon = pPolygon;
    fgBool pickResult = isPicked(pPolygon, pickedPolygonsInfo[polygonIndex]);
    fgBool shouldRemove = FG_FALSE;
    const float exact = timesys::exact();
    int idx = -1;

    if(pickResult) {
        idx = selectedPolygons.find(pPolygon);
        const float ts = pickedPolygonsInfo[polygonIndex].timeStamp;
        if(isToggle && ts < pickBegin) {
            pPolygon->isSelected = !pPolygon->isSelected;
            if(!pPolygon->isSelected) {
                shouldRemove = FG_TRUE; // remove from the list
            }
        } else if(pPolygon->isSelected) {
            // no toggle mode - already selected, no event?

        } else if(!isToggle) {
            pPolygon->isSelected = FG_TRUE;
        }
        if(lastSelectedPolygon && lastSelectedPolygon != pPolygon && !isGroup) {
            // if the last node is not as the current one
            // group selection is off so...
            lastSelectedPolygon->isSelected = FG_FALSE;
            // no need to check for more // unless multi select?
            shouldCheck = FG_FALSE;
        }
        if(!isGroup && !shouldRemove) {
            selectedPolygons.clear_optimised();
            selectedPolygons.resize(1);
            selectedPolygons[0] = pPolygon;
        }
        if(isGroup && !shouldRemove && pPolygon->isSelected) {
            if(-1 == selectedPolygons.find(pPolygon)) {
                selectedPolygons.push_back(pPolygon);
                pickedPolygonsInfo[polygonIndex].timeStamp = exact;
            }
        }
        if(shouldRemove && selectedPolygons.size()) {
            unsigned int size = selectedPolygons.size();
            selectedPolygons[idx] = selectedPolygons[size - 1];
            selectedPolygons[size - 1] = NULL;
            selectedPolygons.resize(size - 1);
            pickedPolygonsInfo[polygonIndex].timeStamp = exact;
        }
        if(pPolygon->isSelected)
            lastSelectedPolygon = pPolygon;
    }

    if(!pickResult) {
        if(shouldUnselect) {
            unsigned int size = selectedPolygons.size();
            selectedPolygons[idx] = selectedPolygons[size - 1];
            selectedPolygons[size - 1] = NULL;
            selectedPolygons.resize(size - 1);
            pickedPolygonsInfo[polygonIndex].timeStamp = exact;
        }
    }
    return pickResult;
}
//------------------------------------------------------------------------------
