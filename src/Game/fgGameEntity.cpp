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
 * File:   fgGameEntity.cpp
 * Author: vigilant
 *
 * Created on September 23, 2015, 8:04 PM
 */

#include "fgGameEntity.h"
#include "fgIntelligent.h"

using namespace fg;
//------------------------------------------------------------------------------

game::CEntity::CEntity(gfx::CModelResource* pModel, CSceneNode* pParent) :
base_type(pModel, pParent),
intelligent_type() {
    setNodeType(SELF_NODE_TYPE);
    setNodeTypeMask(SELF_NODE_TYPE);
    setNodeTrait(intelligent_type::SELF_TRAIT);
}
//------------------------------------------------------------------------------

game::CEntity::CEntity(const CEntity& orig) { }
//------------------------------------------------------------------------------

game::CEntity::~CEntity() { }
//------------------------------------------------------------------------------

fgBool game::CEntity::queryTrait(const fg::traits::SceneNode trait, void **pObj) {
    fgBool status = hasTraits(trait);
    status = (fgBool)(status && (pObj != NULL));
    if(status) {
        if(trait & intelligent_type::SELF_TRAIT) {
            *pObj = static_cast<intelligent_type*>(this);
        }
    } else {
        status = base_type::queryTrait(trait, pObj);
    }
    return status;
}
//------------------------------------------------------------------------------