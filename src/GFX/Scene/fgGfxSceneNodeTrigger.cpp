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
 * File:   fgGFXSceneNodeTrigger.cpp
 * Author: vigilant
 * 
 * Created on February 18, 2015, 10:34 PM
 */

#include "fgGfxSceneNodeTrigger.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::CSceneNodeTrigger::CSceneNodeTrigger() :
base_type(SCENE_NODE_TRIGGER),
triggerable_type() {
    this->setNodeTrait(triggerable_type::SELF_TRAIT);
    this->setNodeTypeMask(SCENE_NODE_TRIGGER);
}
//------------------------------------------------------------------------------

gfx::CSceneNodeTrigger::CSceneNodeTrigger(const CSceneNodeTrigger& orig) :
base_type(orig),
triggerable_type(orig) {
    this->setNodeTrait(triggerable_type::SELF_TRAIT);
    this->setNodeTypeMask(SCENE_NODE_TRIGGER);
}
//------------------------------------------------------------------------------

gfx::CSceneNodeTrigger::~CSceneNodeTrigger() { }
//------------------------------------------------------------------------------

fgBool gfx::CSceneNodeTrigger::queryTrait(const fg::traits::SceneNode trait, void **pObj) {
    fgBool status = hasTraits(trait);
    status = (fgBool)(status && (pObj != NULL));
    if(status) {
        if(trait & fg::traits::TRIGGERABLE) {
            *pObj = static_cast<traits::CTriggerable*>(this);
        } else {
            status = FG_FALSE;
        }
    }
    if(!status) {
        status = base_type::queryTrait(trait, pObj);
    }
    return status;
}
//------------------------------------------------------------------------------