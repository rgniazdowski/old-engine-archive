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
 * File:   fgGFXLooseQuadtree.cpp
 * Author: vigilant
 * 
 * Created on January 14, 2015, 9:58 PM
 */

#include "fgGfxLooseQuadtree.h"

using namespace fg;

//------------------------------------------------------------------------------

const float gfx::CLooseQuadtree::DEFAULT_LOOSE_K = 2.0f;

gfx::CLooseQuadtree::CLooseQuadtree() :
CQuadtree(),
m_looseK(DEFAULT_LOOSE_K) { }
//------------------------------------------------------------------------------

gfx::CLooseQuadtree::CLooseQuadtree(const CLooseQuadtree& orig) { }
//------------------------------------------------------------------------------

gfx::CLooseQuadtree::~CLooseQuadtree() { }
//------------------------------------------------------------------------------

int gfx::CLooseQuadtree::insert(traits::CSpatialObject* pObject, STreeNode* pTreeNode) {
    if(!pObject) {
        return -1;
    }
    // Insert the given object (sceneNode - logical) into the tree given by treeNode.
    // Returns the depth of the node the object was placed in.
    if(!pTreeNode) {
        if(!m_root) {
            m_root = new SQuadtreeNode(NULL, Vector3f(0.0f, 0.0f, 0.0f), 0);
        }
        pTreeNode = m_root;
    } else if(pTreeNode->getType() != TREE_NODE_QUADTREE) {
        return -1;
    }
    Vector2f c;    
    // Check child nodes to see if object fits in one of them.
    //	if (o->radius < WORLD_SIZE / (4 << q->depth)) {
    if(pTreeNode->depth + 1 < (int)getMaxDepth()) {
        float halfSize = m_looseK * getWorldSize().x / (2 << pTreeNode->depth);
        float quarterSize = halfSize / 2;
        float offset = (getWorldSize().x / (2 << pTreeNode->depth)) / 2;
        const Vector3f& objpos = pObject->getBoundingVolume().center;

        // Pick child based on classification of object's center point.
        int i = (objpos.x <= pTreeNode->center.x) ? 0 : 1;
        int j = (objpos.y <= pTreeNode->center.y) ? 0 : 1;

        c.x = pTreeNode->center.x + ((i == 0) ? -offset : offset);
        c.y = pTreeNode->center.y + ((j == 0) ? -offset : offset);

        SQuadtreeNode *quadNode = static_cast<SQuadtreeNode *>(pTreeNode);

        if(fitsInBox(pObject, c, quarterSize)) {
            // Recurse into this node.
            if(quadNode->child[j][i] == 0) {
                quadNode->child[j][i] = new SQuadtreeNode(quadNode, c, pTreeNode->depth + 1);
            }
            return insert(pObject, quadNode->child[j][i]);
        }
    }

    // Keep object in this node.
    if(!pTreeNode->objects.contains(pObject)) {
        pObject->setTreeNode(pTreeNode);
        pTreeNode->objects.push_back(pObject);
    }
    return pTreeNode->depth;
}
//------------------------------------------------------------------------------
