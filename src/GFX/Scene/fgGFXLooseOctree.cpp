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

#include "fgGFXLooseOctree.h"

using namespace fg;

/**
 * 
 */
gfx::CLooseOctree::CLooseOctree() :
COctree(),
m_looseK(DEFAULT_LOOSE_K) { }

/**
 * 
 * @param orig
 */
gfx::CLooseOctree::CLooseOctree(const CLooseOctree& orig) { }

/**
 * 
 */
gfx::CLooseOctree::~CLooseOctree() { }

/**
 * 
 * @param sceneNode
 * @param treeNode
 * @return 
 */
int gfx::CLooseOctree::insert(CSceneNode* sceneNode, STreeNode* treeNode) {
    if(!sceneNode) {
        return -1;
    }
    // Insert the given object (sceneNode - logical) into the tree given by treeNode.
    // Returns the depth of the node the object was placed in.
    if(!treeNode) {
        if(!m_root) {
            m_root = new SOctreeNode(NULL, Vector3f(0.0f, 0.0f, 0.0f), 0);
        }
        treeNode = m_root;
    }

    // Check child nodes to see if object fits in one of them.
    //	if (o->radius < WORLD_SIZE / (4 << q->depth)) {
    if(treeNode->depth + 1 < (int)getMaxDepth()) {
        float halfSize = m_looseK * getWorldSize().x / (2 << treeNode->depth);
        float quarterSize = halfSize / 2.0f;
        float offset = (getWorldSize().x / (2 << treeNode->depth)) / 2.0f;
        const Vector3f& objpos = sceneNode->getRefBoundingVolume().center;

        // Pick child based on classification of object's center point.
        int xi = (objpos.x <= treeNode->center.x) ? 0 : 1;
        int yi = (objpos.y <= treeNode->center.y) ? 0 : 1;
        int zi = (objpos.z <= treeNode->center.z) ? 0 : 1;

        Vector3f c;
        c.x = treeNode->center.x + ((xi == 0) ? -offset : offset);
        c.y = treeNode->center.y + ((yi == 0) ? -offset : offset);
        c.z = treeNode->center.z + ((zi == 0) ? -offset : offset);

        SOctreeNode *oNode = static_cast<SOctreeNode *>(treeNode);
        
        if(fitsInBox(sceneNode, c, quarterSize)) {
            // Recurse into this node.
            if(oNode->child[zi][yi][xi] == 0) {
                oNode->child[zi][yi][xi] = new SOctreeNode(oNode, c, treeNode->depth + 1);
            }
            return insert(sceneNode, oNode->child[zi][yi][xi]);
        }
    }

    // Keep object in this node.
    if(!treeNode->objects.contains(sceneNode)) {
        sceneNode->setTreeNode(treeNode);
        treeNode->objects.push_back(sceneNode);
    }
    return treeNode->depth;
}