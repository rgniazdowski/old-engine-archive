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
armatureInfo(),
boneTypesMap(),
actionsMap(),
rootMotionsMap() { }
//------------------------------------------------------------------------------

gfx::anim::SSkinningInfo::SSkinningInfo(const SSkinningInfo& orig) {
    armatureInfo.append(orig.armatureInfo);
    boneTypesMap.insert(orig.boneTypesMap.begin(),
                        orig.boneTypesMap.end());

    actionsMap.insert(orig.actionsMap.begin(),
                      orig.actionsMap.end());

    rootMotionsMap.insert(orig.rootMotionsMap.begin(),
                          orig.rootMotionsMap.end());
}
//------------------------------------------------------------------------------

gfx::anim::SSkinningInfo::~SSkinningInfo() {
    armatureInfo.clear();
    boneTypesMap.clear();
    actionsMap.clear();
    rootMotionsMap.clear();
}
//------------------------------------------------------------------------------

gfx::anim::StandardActionType gfx::anim::SSkinningInfo::getActionType(const std::string& animationName) {
    if(animationName.empty())
        return ACTION_NONE;
    return getActionType(animationName.c_str());
}
//------------------------------------------------------------------------------

gfx::anim::StandardActionType
gfx::anim::SSkinningInfo::getActionType(const char* animationName) {
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

fgBool gfx::anim::SSkinningInfo::hasAction(StandardActionType actionType) const {
    return (fgBool)(this->actionsMap.find(actionType) != actionsMap.end());
}
//------------------------------------------------------------------------------

fgBool gfx::anim::SSkinningInfo::hasRootMotion(StandardActionType actionType) const {
    return (fgBool)(this->rootMotionsMap.find(actionType) != rootMotionsMap.end());
}
//------------------------------------------------------------------------------

fgBool gfx::anim::SSkinningInfo::hasBone(BoneType boneType) const {
    return (fgBool)(this->boneTypesMap.find(boneType) != boneTypesMap.end());
}
//------------------------------------------------------------------------------

gfx::anim::SBone* gfx::anim::SSkinningInfo::getBone(BoneType boneType, unsigned int index) {
    if(!hasBone(boneType))
        return NULL;
    const unsigned int nBones = this->boneTypesMap[boneType].size();
    if(index >= nBones)
        return NULL;
    return this->boneTypesMap[boneType][index];
}
//------------------------------------------------------------------------------

const gfx::anim::SBone* gfx::anim::SSkinningInfo::getBone(BoneType boneType,
                                                          unsigned int index) const {
    BoneTypesMapConstItor itor = this->boneTypesMap.find(boneType);
    if(itor == this->boneTypesMap.end())
        return NULL;
    const unsigned int nBones = itor->second.size();
    if(index >= nBones)
        return NULL;
    return itor->second.at(index);
}
//------------------------------------------------------------------------------
