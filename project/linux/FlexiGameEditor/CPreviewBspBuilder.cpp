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
#include "CPreviewBspBuilder.h"
#include "CEngineGfxCanvas.h"

//------------------------------------------------------------------------------

CPreviewBspBuilder::CPreviewBspBuilder(fg::CEngineMain** pEngineMainOrig) :
base_type(pEngineMainOrig),
m_displayShotCB(NULL),
m_updateShotCB(NULL),
m_renderShotCB(NULL),
m_mouseHandlerCB(NULL),
m_keyboardHandlerCB(NULL) {
    m_displayShotCB = new fg::event::CPlainFunctionCallback(&CPreviewBspBuilder::displayHandler,
                                                            this);

    m_updateShotCB = new fg::event::CPlainFunctionCallback(&CPreviewBspBuilder::updateHandler,
                                                           this);

    m_renderShotCB = new fg::event::CPlainFunctionCallback(&CPreviewBspBuilder::renderHandler,
                                                           this);

    m_mouseHandlerCB = new fg::event::CMethodCallback<self_type>(this,
                                                                 &CPreviewBspBuilder::mouseHandler);

    m_keyboardHandlerCB = new fg::event::CMethodCallback<self_type>(this,
                                                                    &CPreviewBspBuilder::keyboardHandler);

    refreshInternals();
}
//------------------------------------------------------------------------------

CPreviewBspBuilder::~CPreviewBspBuilder() {
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
}
//------------------------------------------------------------------------------

fgBool CPreviewBspBuilder::activate(fgBool toggle) {
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
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void CPreviewBspBuilder::refreshInternals(void) {
    
}
//------------------------------------------------------------------------------

fgBool CPreviewBspBuilder::registerCallbacks(void) {
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
    if(!pEngineMain->isRegistered(fg::event::KEY_DOWN, m_keyboardHandlerCB)) {
        pEngineMain->addCallback(fg::event::KEY_DOWN, m_keyboardHandlerCB);
    }
    m_callbacksRegistered = FG_TRUE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CPreviewBspBuilder::unregisterCallbacks(void) {
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
    m_callbacksRegistered = FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CPreviewBspBuilder::engineInit(void* systemData, void* userData) {
    if(!systemData || !userData)
        return FG_FALSE;
    // user data is the pointer to the CPreviewBspBuilder object
    // system data is the pointer to the gfx engine canvas holder object
    // it's from where the programInit/Quit events are thrown (internal cb)
    CPreviewBspBuilder *pSelf = static_cast<CPreviewBspBuilder*>(userData);
    CEngineGfxCanvas* pGfxCanvas = static_cast<CEngineGfxCanvas*>(systemData);
    fg::CEngineMain* pEngineMain = pGfxCanvas->getEngineMain();
    pSelf->registerCallbacks();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CPreviewBspBuilder::engineDestroy(void* systemData, void* userData) {
    if(!systemData || !userData)
        return FG_FALSE;
    // user data is the pointer to the CPreviewBspBuilder object
    // system data is the pointer to the gfx engine canvas holder object
    // it's from where the programInit/Quit events are thrown (internal cb)
    CPreviewBspBuilder *pSelf = static_cast<CPreviewBspBuilder*>(userData);
    CEngineGfxCanvas* pGfxCanvas = static_cast<CEngineGfxCanvas*>(systemData);
    fg::CEngineMain* pEngineMain = pGfxCanvas->getEngineMain();
    pSelf->unregisterCallbacks();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CPreviewBspBuilder::displayHandler(void* systemData, void* userData) {
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

fgBool CPreviewBspBuilder::updateHandler(void* systemData, void* userData) {
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

fgBool CPreviewBspBuilder::renderHandler(void* systemData, void* userData) {
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

fgBool CPreviewBspBuilder::mouseHandler(fg::event::CArgumentList* argv) {
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

fgBool CPreviewBspBuilder::keyboardHandler(fg::event::CArgumentList* argv) {
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
