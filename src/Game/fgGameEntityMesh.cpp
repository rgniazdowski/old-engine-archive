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
 * File:   fgGameEntityMesh.cpp
 * Author: vigilant
 * 
 * Created on September 23, 2015, 8:04 PM
 */

#include "fgGameEntityMesh.h"

using namespace fg;
//------------------------------------------------------------------------------

game::CEntityMesh::CEntityMesh(gfx::SMeshBase* pMesh, gfx::CSceneNode* pParent) :
base_type(pMesh, pParent),
physical_type() {
    setNodeType(SELF_NODE_TYPE);
    setNodeTypeMask(SELF_NODE_TYPE);
    setNodeTrait(physical_type::SELF_TRAIT);

    // automatically update collision body
    physical_type::setupCollisionBody(physics::CCollisionBody::BOX);
    //physical_type::getCollisionBody()->setHalfSize()
}
//------------------------------------------------------------------------------

game::CEntityMesh::CEntityMesh(const CEntityMesh& orig) :
base_type(orig),
physical_type(orig) { }
//------------------------------------------------------------------------------

game::CEntityMesh::~CEntityMesh() { }
//------------------------------------------------------------------------------

fgBool game::CEntityMesh::queryTrait(const fg::traits::SceneNode trait, void **pObj) {
    fgBool status = hasTraits(trait);
    status = (fgBool)(status && (pObj != NULL));
    if(status) {
        if(trait & physical_type::SELF_TRAIT) {
            *pObj = static_cast<physical_type*>(this);
        }
    } else {
        status = base_type::queryTrait(trait, pObj);
    }
    return status;
}
//------------------------------------------------------------------------------

void game::CEntityMesh::updateAABB(void) {
    base_type::updateAABB();
    physics::CCollisionBody* pBody = physical_type::getCollisionBody();
    if(pBody && getMesh()) {
        physical_type::getCollisionBody()->setHalfSize(getMesh()->aabb.getExtent());
    }
    if(pBody) {
        // copy to the body current model matrix - two way management
        // matrix from physical body will be copied after Physical world update
        pBody->setWorldTransform(getFinalModelMatrix());
    }
}
//------------------------------------------------------------------------------
