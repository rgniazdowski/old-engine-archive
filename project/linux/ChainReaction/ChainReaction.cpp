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
#include "fgGameMain.h"
#include "fgPluginResource.h"
#include "ChainReaction.h"
#include "Event/fgCallback.h"

fg::event::CFunctionCallback* dispCallbackPtr = NULL;

extern "C" {
    fgBool fgInitPluginFunction_CHAINREACTION(fg::CPluginResource::SInternalInfo* info);
    fgBool fgExitPluginFunction_CHAINREACTION(fg::CPluginResource::SInternalInfo* info);
}

fgBool displayCallback(void* system, void* user) {
    if(!user) {
        return FG_FALSE;
    }
    fg::CPluginResource::SInternalInfo* info = (fg::CPluginResource::SInternalInfo*) user;
    return FG_TRUE;
}

fgBool fgInitPluginFunction_CHAINREACTION(fg::CPluginResource::SInternalInfo* info) {
    if(!info) {
        return FG_FALSE;
    }
    if(!info->pGameMain) {
        return FG_FALSE;
    }
    dispCallbackPtr = new fg::event::CPlainFunctionCallback(&displayCallback, (void*)info);
    info->pGameMain->addCallback(fg::event::DISPLAY_SHOT, dispCallbackPtr);
    if(!dispCallbackPtr) {
    }
    return FG_TRUE;
}

fgBool fgExitPluginFunction_CHAINREACTION(fg::CPluginResource::SInternalInfo* info) {    
    if(!info) {
        return FG_FALSE;
    }
    if(!info->pGameMain) {
        return FG_FALSE;
    }
    if(dispCallbackPtr) {
        info->pGameMain->removeCallback(fg::event::DISPLAY_SHOT, dispCallbackPtr);
        delete dispCallbackPtr;
        dispCallbackPtr = NULL;
    }
    return FG_TRUE;
}
