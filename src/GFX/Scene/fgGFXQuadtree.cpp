/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXQuadtree.h"

using namespace fg;

/**
 * 
 */
gfx::CQuadtree::CQuadtree() :
m_root(NULL) { }

/**
 * 
 * @param orig
 */
gfx::CQuadtree::CQuadtree(const CQuadtree& orig) { }

/**
 * 
 */
gfx::CQuadtree::~CQuadtree() {
    if(m_root) {
        delete m_root;
        m_root = NULL;
    }
}

void gfx::CQuadtree::deleteRoot(void) {
    if(m_root) {
        delete m_root;
        m_root = NULL;
    }
    m_traverse.rewind();
}

/**
 * Insert the given object (sceneNode - logical) into the tree given by treeNode
 * Returns the depth of the node the object was placed in.
 * @param sceneNode
 * @param treeNode
 * @return 
 */
int gfx::CQuadtree::insert(CSceneNode* sceneNode, STreeNode* treeNode) {
    if(!sceneNode)
        return -1;

    if(!treeNode) {
        if(!m_root) {
            m_root = new SQuadtreeNode(NULL, Vector3f(0.0f, 0.0f, 0.0f), 0);
        }
        treeNode = m_root;
    }

    int i, j;

    // Check child nodes to see if object fits in one of them.
    if(treeNode->depth + 1 < (int)getMaxDepth()) {
        float halfSize = getWorldSize().x / (float)(2 << treeNode->depth);
        float quarterSize = halfSize / 2.0f;
        float offset = quarterSize;

        for(j = 0; j < 2; j++) {
            for(i = 0; i < 2; i++) {
                float cx = treeNode->center.x + ((i == 0) ? -offset : offset);
                float cy = treeNode->center.y + ((j == 0) ? -offset : offset);

                SQuadtreeNode *qNode = static_cast<SQuadtreeNode *>(treeNode);

                if(fitsInBox(sceneNode, Vector2f(cx, cy), quarterSize)) {
                    // Recurse into this node.
                    if(qNode->child[j][i] == NULL) {
                        qNode->child[j][i] = new SQuadtreeNode(qNode, Vector2f(cx, cy), treeNode->depth + 1);
                    }
                    return insert(sceneNode, qNode->child[j][i]);
                }
            }
        }
    }
    // Keep object in this node.
    if(!treeNode->objects.contains(sceneNode)) {
        sceneNode->setTreeNode(treeNode);
        treeNode->objects.push_back(sceneNode);
    }
    return treeNode->depth;
}

/**
 *
 */
gfx::STreeNode* gfx::CQuadtree::next(void) {
    return m_traverse.next(m_root);
}

/**
 * 
 */
void gfx::CQuadtree::rewind(void) {
    m_traverse.rewind();
}

/**
 * 
 */
void gfx::CQuadtree::skip(void) {
    m_traverse.skip(m_root);
}