/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgBuildConfig.h"
#include "fgDebugConfig.h"
#include "fgLog.h"
#include "fgEngineMain.h"
#include "fgPluginResource.h"
#include "ChainReaction.h"
#include "Event/fgCallback.h"
#include "Event/fgEventManager.h"
#include "GameLogic/fgGrid.h"

extern "C" {
    fgBool fgInitPluginFunction_CHAINREACTION(fg::CPluginResource::SInternalInfo* info);
    fgBool fgExitPluginFunction_CHAINREACTION(fg::CPluginResource::SInternalInfo* info);
}
//------------------------------------------------------------------------------

fgBool fgInitPluginFunction_CHAINREACTION(fg::CPluginResource::SInternalInfo* info) {
    if(!info) {
        return FG_FALSE;
    }
    if(!info->pEngineMain) {
        return FG_FALSE;
    }
   
    fg::CChainReaction* pChainReactionMgr = new fg::CChainReaction(info->pEngineMain, info);
    if(!pChainReactionMgr) {
        return FG_FALSE;
    }

    info->pPluginData = (void *)pChainReactionMgr;

    if(!pChainReactionMgr->initialize()) {
        info->pPluginData = NULL;
        delete pChainReactionMgr;
        pChainReactionMgr = NULL;
        return FG_FALSE;
    }

    FG_LOG_DEBUG("ChainReaction: Initialized successfully!");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool fgExitPluginFunction_CHAINREACTION(fg::CPluginResource::SInternalInfo* info) {
    if(!info) {
        return FG_FALSE;
    }
    if(!info->pEngineMain) {
        return FG_FALSE;
    }

    if(!info->pPluginData) {
        return FG_FALSE;
    }

    fg::CChainReaction* pChainReactionMgr = (fg::CChainReaction*) info->pPluginData;
    delete pChainReactionMgr;
    pChainReactionMgr = NULL;
    info->pPluginData = NULL;

    FG_LOG_DEBUG("ChainReaction: Plugin closed successfully!");
    return FG_TRUE;
}
//------------------------------------------------------------------------------

using namespace fg;

//------------------------------------------------------------------------------

CChainReaction::CChainReaction(CEngineMain* pEngineMain,
                               CPluginResource::SInternalInfo* pPluginInfo) :
m_pEngineMain(pEngineMain),
m_pPluginInfo(pPluginInfo),
m_grid(NULL),
m_updateCallback(NULL),
m_preRenderCallback(NULL),
m_renderCallback(NULL) {

    m_managerType = FG_MANAGER_CHAIN_REACTION;
}
//------------------------------------------------------------------------------

CChainReaction::~CChainReaction() { 
    destroy();    
}
//------------------------------------------------------------------------------

void CChainReaction::clear(void) {
    m_managerType = FG_MANAGER_CHAIN_REACTION;
    m_init = FG_FALSE;
    m_grid = NULL;
}
//------------------------------------------------------------------------------

fgBool CChainReaction::destroy(void) {
    m_init = FG_FALSE;
    unregisterCallbacks();
    if(m_grid) {
        delete m_grid;
        m_grid = NULL;
    }
    if(m_updateCallback) {
        delete m_updateCallback;
        m_updateCallback = NULL;
    }
    if(m_preRenderCallback) {
        delete m_preRenderCallback;
        m_preRenderCallback = NULL;
    }
    if(m_renderCallback) {
        delete m_renderCallback;
        m_renderCallback = NULL;
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CChainReaction::initialize(void) {
    if(!m_pEngineMain || !m_pPluginInfo) {
        return FG_FALSE;
    }
    if(!m_init) {
        registerCallbacks();
    }
    if(m_grid)
        delete m_grid;
    m_grid = new game::CGrid(game::CGrid::TWO_DIMENSIONAL);
    m_grid->setMaxSize(48, 48);
    m_grid->reserve(48, 48);
    m_init = FG_TRUE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void CChainReaction::registerCallbacks(void) {
    if(!m_pEngineMain || !m_pPluginInfo) {
        return;
    }

    if(!m_updateCallback)
        m_updateCallback = new event::CPlainFunctionCallback(&self_type::updateHandler,
                                                             (void*)m_pPluginInfo);

    if(!m_preRenderCallback)
        m_preRenderCallback = new event::CPlainFunctionCallback(&self_type::preRenderHandler,
                                                                (void*)m_pPluginInfo);

    if(!m_renderCallback)
        m_renderCallback = new event::CPlainFunctionCallback(&self_type::renderHandler,
                                                             (void*)m_pPluginInfo);

    m_pEngineMain->addCallback(event::UPDATE_SHOT, m_updateCallback);
    m_pEngineMain->addCallback(event::PRERENDER_SHOT, m_preRenderCallback);
    m_pEngineMain->addCallback(event::RENDER_SHOT, m_renderCallback);
}
//------------------------------------------------------------------------------

void CChainReaction::unregisterCallbacks(void) {
    if(!m_pEngineMain || !m_pPluginInfo) {
        return;
    }

    m_pEngineMain->removeCallback(event::UPDATE_SHOT, m_updateCallback);
    m_pEngineMain->removeCallback(event::PRERENDER_SHOT, m_preRenderCallback);
    m_pEngineMain->removeCallback(event::RENDER_SHOT, m_renderCallback);
}
//------------------------------------------------------------------------------

fgBool CChainReaction::updateHandler(void* system, void* user) {
    if(!system || !user) {
        return FG_FALSE;
    }
    fg::CPluginResource::SInternalInfo* info = (fg::CPluginResource::SInternalInfo*) user;

    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CChainReaction::preRenderHandler(void* system, void* user) {
    if(!system || !user) {
        return FG_FALSE;
    }
    fg::CPluginResource::SInternalInfo* info = (fg::CPluginResource::SInternalInfo*) user;

    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CChainReaction::renderHandler(void* system, void* user) {
    if(!system || !user) {
        return FG_FALSE;
    }
    fg::CPluginResource::SInternalInfo* info = (fg::CPluginResource::SInternalInfo*) user;

    return FG_TRUE;
}
//------------------------------------------------------------------------------
