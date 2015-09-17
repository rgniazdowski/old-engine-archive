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
 * File:   fgGfxSkinningInfo.cpp
 * Author: vigilant
 * 
 * Created on September 16, 2015, 6:05 PM
 */

#include "fgGfxSkinningInfo.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::anim::SSkinningInfo::SSkinningInfo() :
blendingInfo(),
armatureInfo(),
boneTypesMap(),
actionsMap() { }
//------------------------------------------------------------------------------

gfx::anim::SSkinningInfo::SSkinningInfo(const SSkinningInfo& orig) {
    blendingInfo.append(orig.blendingInfo);
    armatureInfo.append(orig.armatureInfo);
    boneTypesMap.insert(orig.boneTypesMap.begin(),
                        orig.boneTypesMap.end());

    actionsMap.insert(orig.actionsMap.begin(),
                      orig.actionsMap.end());
}
//------------------------------------------------------------------------------

gfx::anim::SSkinningInfo::~SSkinningInfo() {
    boneTypesMap.clear();
    actionsMap.clear();
}
//------------------------------------------------------------------------------

gfx::anim::StandardActionType gfx::anim::SSkinningInfo::getActionType(const std::string& animationName) {
    if(animationName.empty())
        return ACTION_NONE;
    return getActionType(animationName.c_str());
}
//------------------------------------------------------------------------------

gfx::anim::StandardActionType gfx::anim::SSkinningInfo::getActionType(const char* animationName) {
    if(!animationName)
        return ACTION_NONE;
    ActionsMapConstItor itor = actionsMap.begin();
    ActionsMapConstItor end = actionsMap.end();
    for(; itor != end; itor++) {
        if(itor->second.compare(animationName) == 0) {
            return itor->first;
        }
    }
    return ACTION_NONE;
}
//------------------------------------------------------------------------------
