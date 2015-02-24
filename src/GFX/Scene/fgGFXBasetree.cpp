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

#include "fgGFXBasetree.h"
#include "fgGFXSceneNode.h"

using namespace fg;

/**
 * 
 */
gfx::CBasetree::CBasetree() :
m_worldSize((float)2000.0f, (float)2000.0f, (float)2000.0f),
m_maxDepth(DEFAULT_DEPTH) { }

/**
 * 
 */
gfx::CBasetree::~CBasetree() { }

/**
 * 
 * @param sceneNode
 * @param treeNode
 * @param halfExtent
 * @return 
 */
fgBool gfx::CBasetree::fitsInBox(const CSceneNode* sceneNode,
                                 STreeNode* treeNode,
                                 const float halfExtent) {
    if(!sceneNode || !treeNode)
        return FG_FALSE;

    // nope, it needs to check if the bounding volume of scene node can fit inside
    // the Quad-tree Node (center+halfExtents)
    //sceneNode->getRefBoundingVolume().test(treeNode->center, halfExtent);
    return fitsInBox(sceneNode, treeNode->center, halfExtent);
}

/**
 * 
 * @param sceneNode
 * @param center
 * @param halfExtent
 * @return 
 */
fgBool gfx::CBasetree::fitsInBox(const CSceneNode* sceneNode,
                                 const Vector3f& center,
                                 const float halfExtent) {
    if(!sceneNode)
        return FG_FALSE;

    const Vector3f& objpos = sceneNode->getRefBoundingVolume().center;
    const Vector3f& objext = sceneNode->getRefBoundingVolume().extent;
    float r = sceneNode->getRefBoundingVolume().radius;

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

/**
 * 
 * @param sceneNode
 * @param center
 * @param halfExtent
 * @return 
 */
fgBool gfx::CBasetree::fitsInBox(const CSceneNode* sceneNode,
                                 const Vector2f& center,
                                 const float halfExtent) {
    if(!sceneNode)
        return FG_FALSE;

    const Vector3f& objpos = sceneNode->getRefBoundingVolume().center;
    const Vector3f& objext = sceneNode->getRefBoundingVolume().extent;
    float r = sceneNode->getRefBoundingVolume().radius;

    if(objpos.x - objext.x < center.x - halfExtent ||
       objpos.x + objext.x > center.x + halfExtent ||
       objpos.y - objext.y < center.y - halfExtent ||
       objpos.y + objext.y > center.y + halfExtent) {
        return FG_FALSE;
    } else {
        return FG_TRUE;
    }
}