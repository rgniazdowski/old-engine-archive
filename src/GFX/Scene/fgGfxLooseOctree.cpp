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
 * File:   fgGFXLooseOctree.cpp
 * Author: vigilant
 * 
 * Created on January 14, 2015, 9:58 PM
 */

#include "fgGfxLooseOctree.h"
#include "fgGfxSceneNode.h"

using namespace fg;
//------------------------------------------------------------------------------

const float gfx::CLooseOctree::DEFAULT_LOOSE_K = 2.0f;

gfx::CLooseOctree::CLooseOctree() :
COctree(),
m_looseK(DEFAULT_LOOSE_K) { }
//------------------------------------------------------------------------------

gfx::CLooseOctree::CLooseOctree(const CLooseOctree& orig) { }
//------------------------------------------------------------------------------

gfx::CLooseOctree::~CLooseOctree() { }
//------------------------------------------------------------------------------

int gfx::CLooseOctree::insert(traits::CSpatialObject* pObject, STreeNode* pTreeNode) {
    if(!pObject) {
        return -1;
    }
    // Insert the given object (pObject - logical) into the tree given by treeNode.
    // Returns the depth of the node the object was placed in.
    if(!pTreeNode) {
        if(!m_root) {
            m_root = new SOctreeNode(NULL, Vector3f(0.0f, 0.0f, 0.0f), 0);
        }
        pTreeNode = m_root;
    } else if(pTreeNode->getType() != TREE_NODE_OCTREE) {
        return -1;
    }
    // #FIXME - not type safe
    CSceneNode *sceneNode = static_cast<CSceneNode *>(pObject);
    // Check child nodes to see if object fits in one of them.
    //	if (o->radius < WORLD_SIZE / (4 << q->depth)) {
    if(pTreeNode->depth + 1 < (int)getMaxDepth()) {
        float halfSize = m_looseK * getWorldSize().x / (2 << pTreeNode->depth);
        float quarterSize = halfSize / 2.0f;
        float offset = (getWorldSize().x / (2 << pTreeNode->depth)) / 2.0f;
        const Vector3f& objpos = sceneNode->getBoundingVolume().center;

        // Pick child based on classification of object's center point.
        int xi = (objpos.x <= pTreeNode->center.x) ? 0 : 1;
        int yi = (objpos.y <= pTreeNode->center.y) ? 0 : 1;
        int zi = (objpos.z <= pTreeNode->center.z) ? 0 : 1;

        Vector3f c;
        c.x = pTreeNode->center.x + ((xi == 0) ? -offset : offset);
        c.y = pTreeNode->center.y + ((yi == 0) ? -offset : offset);
        c.z = pTreeNode->center.z + ((zi == 0) ? -offset : offset);

        SOctreeNode *octNode = static_cast<SOctreeNode *>(pTreeNode);
        if(fitsInBox(sceneNode, c, quarterSize)) {
            // Recurse into this node.
            if(octNode->child[zi][yi][xi] == 0) {
                octNode->child[zi][yi][xi] = new SOctreeNode(octNode, c, pTreeNode->depth + 1);
            }
            return insert(sceneNode, octNode->child[zi][yi][xi]);
        }
    }

    // Keep object in this node.
    if(!pTreeNode->objects.contains(sceneNode)) {
        pObject->setTreeNode(pTreeNode);
        pTreeNode->objects.push_back(sceneNode);
    }
    return pTreeNode->depth;
}
//------------------------------------------------------------------------------
