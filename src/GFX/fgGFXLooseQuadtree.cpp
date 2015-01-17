/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXLooseQuadtree.cpp
 * Author: vigilant
 * 
 * Created on January 14, 2015, 9:58 PM
 */

#include "fgGFXLooseQuadtree.h"

using namespace fg;

/**
 * 
 */
gfx::CLooseQuadtree::CLooseQuadtree() :
CQuadtree(),
m_looseK(DEFAULT_LOOSE_K) { }

/**
 * 
 * @param orig
 */
gfx::CLooseQuadtree::CLooseQuadtree(const CLooseQuadtree& orig) { }

/**
 * 
 */
gfx::CLooseQuadtree::~CLooseQuadtree() { }

/**
 * 
 * @param sceneNode
 * @param treeNode
 * @return 
 */
int gfx::CLooseQuadtree::insert(CSceneNode* sceneNode, SQuadtreeNode* treeNode) {
    if(!sceneNode) {
        return -1;
    }
    // Insert the given object (sceneNode - logical) into the tree given by treeNode.
    // Returns the depth of the node the object was placed in.
    if(!treeNode) {
        if(!m_root) {
            m_root = new SQuadtreeNode(NULL, Vector3f(0.0f, 0.0f, 0.0f), 0);
        }
        treeNode = m_root;
    }

    // Check child nodes to see if object fits in one of them.
    //	if (o->radius < WORLD_SIZE / (4 << q->depth)) {
    if(treeNode->depth + 1 < (int)getMaxDepth()) {
        float halfSize = m_looseK * getWorldSize().x / (2 << treeNode->depth);
        float quarterSize = halfSize / 2;
        float offset = (getWorldSize().x / (2 << treeNode->depth)) / 2;
        const Vector3f& objpos = sceneNode->getRefBoundingVolume().center;

        // Pick child based on classification of object's center point.
        int i = (objpos.x <= treeNode->center.x) ? 0 : 1;
        int j = (objpos.y <= treeNode->center.y) ? 0 : 1;

        float cx = treeNode->center.x + ((i == 0) ? -offset : offset);
        float cy = treeNode->center.y + ((j == 0) ? -offset : offset);

        if(fitsInBox(sceneNode, Vector2f(cx, cy), quarterSize)) {
            // Recurse into this node.
            if(treeNode->child[j][i] == 0) {
                treeNode->child[j][i] = new SQuadtreeNode(treeNode, Vector2f(cx, cy), treeNode->depth + 1);
            }
            return insert(sceneNode, treeNode->child[j][i]);
        }
    }

    // Keep object in this node.
    if(!treeNode->objects.contains(sceneNode)) {
        sceneNode->setTreeNode(treeNode);
        treeNode->objects.push_back(sceneNode);
    }
    return treeNode->depth;
}
