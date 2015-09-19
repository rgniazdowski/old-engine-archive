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
 * File:   fgGFXBasetree.cpp
 * Author: vigilant
 *
 * Created on January 16, 2015, 11:07 PM
 */

#include "fgGfxBasetree.h"
#include "fgGfxSceneNode.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::CBasetree::CBasetree() :
m_worldSize((float)2000.0f, (float)2000.0f, (float)2000.0f),
m_maxDepth(DEFAULT_DEPTH) { }
//------------------------------------------------------------------------------

gfx::CBasetree::~CBasetree() { }
//------------------------------------------------------------------------------

fgBool gfx::CBasetree::fitsInBox(const traits::CSpatialObject* pObject,
                                 STreeNode* pTreeNode,
                                 const float halfExtent) {
    if(!pObject || !pTreeNode)
        return FG_FALSE;

    // nope, it needs to check if the bounding volume of scene node can fit inside
    // the Quad-tree Node (center+halfExtents)
    //sceneNode->getRefBoundingVolume().test(treeNode->center, halfExtent);
    return fitsInBox(pObject, pTreeNode->center, halfExtent);
}
//------------------------------------------------------------------------------

fgBool gfx::CBasetree::fitsInBox(const traits::CSpatialObject* pObject,
                                 const Vector3f& center,
                                 const float halfExtent) {
    if(!pObject)
        return FG_FALSE;

    const Vector3f& objpos = pObject->getBoundingVolume().center;
    const Vector3f& objext = pObject->getBoundingVolume().extent;
    //float r = pObject->getRefBoundingVolume().radius;

    if(objpos.x - objext.x < center.x - halfExtent ||
       objpos.x + objext.x > center.x + halfExtent ||
       objpos.y - objext.y < center.y - halfExtent ||
       objpos.y + objext.y > center.y + halfExtent ||
       objpos.z - objext.z < center.z - halfExtent ||
       objpos.z + objext.z > center.z + halfExtent) {
        return FG_FALSE;
    } else {
        return FG_TRUE;
    }
}
//------------------------------------------------------------------------------

fgBool gfx::CBasetree::fitsInBox(const traits::CSpatialObject* pObject,
                                 const Vector2f& center,
                                 const float halfExtent) {
    if(!pObject)
        return FG_FALSE;

    const Vector3f& objpos = pObject->getBoundingVolume().center;
    const Vector3f& objext = pObject->getBoundingVolume().extent;
    //float r = pObject->getRefBoundingVolume().radius;

    if(objpos.x - objext.x < center.x - halfExtent ||
       objpos.x + objext.x > center.x + halfExtent ||
       objpos.y - objext.y < center.y - halfExtent ||
       objpos.y + objext.y > center.y + halfExtent) {
        return FG_FALSE;
    } else {
        return FG_TRUE;
    }
}
//------------------------------------------------------------------------------
