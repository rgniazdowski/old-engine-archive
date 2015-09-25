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
}
//------------------------------------------------------------------------------

game::CEntityMesh::CEntityMesh(const CEntityMesh& orig) :
base_type(orig),
physical_type(orig) {
 }
//------------------------------------------------------------------------------

game::CEntityMesh::~CEntityMesh() { }
//------------------------------------------------------------------------------
