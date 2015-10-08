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
    setNodeType(self_type::SELF_ENTITY_TYPE);
    setNodeTypeMask(self_type::SELF_ENTITY_TYPE);
    setNodeTrait(physical_type::SELF_TRAIT);

    // automatically update collision body
    physical_type::setupCollisionBody(physics::CCollisionBody::BOX);
    if(pMesh)
        physical_type::getCollisionBody()->setHalfSize(pMesh->aabb.getExtent());
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

void game::CEntityMesh::setScale(const Vector3f& scale) {
    base_type::setScale(scale);
    physics::CCollisionBody* pBody = physical_type::getCollisionBody();
    if(pBody) {
        pBody->setLocalScaling(this->getScale());
    }
}
//------------------------------------------------------------------------------

void game::CEntityMesh::setMesh(gfx::SMeshBase* pMesh) {
    base_type::setMesh(pMesh);
    physics::CCollisionBody* pBody = physical_type::getCollisionBody();
    if(pMesh && pBody) {
        physical_type::getCollisionBody()->setHalfSize(getMesh()->aabb.getExtent());
    }
}
//------------------------------------------------------------------------------

void game::CEntityMesh::updateAABB(void) {
    base_type::updateAABB();
    physics::CCollisionBody* pBody = physical_type::getCollisionBody();
    if(pBody) {
        //pBody->setLocalScaling(this->getScale());
        // copy to the body current model matrix - two way management
        // matrix from physical body will be copied after Physical world update
        // the matrix should be without scaling...
        pBody->setWorldTransform(getFinalModelMatrix());
    }
}
//------------------------------------------------------------------------------
