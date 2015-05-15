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

#include "GFX/Scene/fgGfx3DScene.h"
#include "GFX/Scene/fgGfxBspCompiler.h"
#include "GFX/Scene/fgGfxBspTree.h"
#include "GFX/Scene/fgGfxBspNode.h"
#include "GFX/Scene/fgGfxBspFile.h"

#include "GFX/fgGfxCameraAnimation.h"
#include "GFX/fgGfxDrawingBatch.h"
#include "GFX/fgGfxPrimitives.h"
#include "GFX/fgGfxPlane.h"
#include "GFX/fgGfxPolygon.h"

#include "GUI/fgGuiDrawer.h"

#include "CPreviewBspBuilder.h"
#include "CEngineGfxCanvas.h"

using namespace fg;

//------------------------------------------------------------------------------

editor::CPreviewBspBuilder::CPreviewBspBuilder(fg::CEngineMain** pEngineMainOrig) :
base_type(pEngineMainOrig),
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
}
//------------------------------------------------------------------------------

editor::CPreviewBspBuilder::~CPreviewBspBuilder() {
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
    if(!getEngineMain() || !m_p3DScene)
        return;
    gfx::Planef plane;
    switch(previewSide) {
        case PreviewSide::FREE_LOOK:
            m_p3DScene->setGroundPlane(gfx::Planef::Y, m_p3DScene->getGroundLevel());
            m_pCamera->setType(gfx::CCameraAnimation::FREE);
            // camera on the side, looks at the center
            break;
        case PreviewSide::LEFT:            
            plane.n = Vec3f(-1.0f, 0.0f, 0.0f);
            plane.d = m_p3DScene->getGroundLevel();
            m_p3DScene->setGroundPlane(plane);
            m_pCamera->setType(gfx::CCameraAnimation::FREE);
            // camera on the left side, looks to the right
            break;
        case PreviewSide::RIGHT:
            plane.n = Vec3f(1.0f, 0.0f, 0.0f);
            plane.d = m_p3DScene->getGroundLevel();
            m_p3DScene->setGroundPlane(plane);
            m_pCamera->setType(gfx::CCameraAnimation::FREE);
            // camera on the right side, looks to the left
            break;
        case PreviewSide::TOP:
            plane.n = Vec3f(0.0f, 1.0f, 0.0f);
            plane.d = m_p3DScene->getGroundLevel();
            m_p3DScene->setGroundPlane(plane);
            m_pCamera->setType(gfx::CCameraAnimation::FREE);
            // camera over, points down
            break;
        case PreviewSide::BOTTOM:
            plane.n = Vec3f(0.0f, -1.0f, 0.0f);
            plane.d = m_p3DScene->getGroundLevel();
            m_p3DScene->setGroundPlane(plane);
            m_pCamera->setType(gfx::CCameraAnimation::FREE);
            // camera below, points up
            break;
        case PreviewSide::FRONT:
            plane.n = Vec3f(0.0f, 0.0f, 1.0f);
            plane.d = m_p3DScene->getGroundLevel();
            m_p3DScene->setGroundPlane(plane);
            m_pCamera->setType(gfx::CCameraAnimation::FREE);
            // camera at +Z looks at -Z
            break;
        case PreviewSide::BACK:
            plane.n = Vec3f(0.0f, 0.0f, -1.0f);
            plane.d = m_p3DScene->getGroundLevel();
            m_p3DScene->setGroundPlane(plane);
            m_pCamera->setType(gfx::CCameraAnimation::FREE);
            // camera at -Z looks at +Z
            break;
    }
    m_previewSide = previewSide;
}
//------------------------------------------------------------------------------

fgBool editor::CPreviewBspBuilder::registerCallbacks(void) {
    if(!getEngineMain())
        return FG_FALSE;
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
    pSelf->registerCallbacks();
    pSelf->refreshInternals();
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
    pSelf->unregisterCallbacks();
    pSelf->refreshInternals();
    return FG_TRUE;
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

    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool editor::CPreviewBspBuilder::mouseHandler(fg::event::CArgumentList* argv) {
    if(!argv || !m_isActive)
        return FG_FALSE;
    fg::event::SEvent *pEvent = (fg::event::SEvent *)argv->getValueByID(0);
    if(!pEvent)
        return FG_FALSE;
    const fg::event::EventType type = pEvent->code;
    if(type != fg::event::MOUSE_MOTION &&
       type != fg::event::MOUSE_PRESSED &&
       type != fg::event::MOUSE_RELEASED) {
        return FG_FALSE;
    }
    fg::event::SMouse* pMouse = reinterpret_cast<fg::event::SMouse*>(pEvent);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool editor::CPreviewBspBuilder::keyboardHandler(fg::event::CArgumentList* argv) {
    if(!argv || !m_isActive)
        return FG_FALSE;
    fg::event::SEvent* pEvent = (fg::event::SEvent *)argv->getValueByID(0);
    if(!pEvent)
        return FG_FALSE;
    const fg::event::EventType type = pEvent->code;
    if(type != fg::event::KEY_DOWN && type != fg::event::KEY_UP) {
        return FG_FALSE;
    }
    fg::event::SKey* pKey = reinterpret_cast<fg::event::SKey*>(pEvent);
    return FG_TRUE;
}
//------------------------------------------------------------------------------
