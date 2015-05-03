/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGfxQuadtree.h"

using namespace fg;

//------------------------------------------------------------------------------

gfx::CQuadtree::CQuadtree() :
m_root(NULL) { }
//------------------------------------------------------------------------------

gfx::CQuadtree::CQuadtree(const CQuadtree& orig) { }
//------------------------------------------------------------------------------

gfx::CQuadtree::~CQuadtree() {
    if(m_root) {
        delete m_root;
        m_root = NULL;
    }
}
//------------------------------------------------------------------------------

void gfx::CQuadtree::deleteRoot(void) {
    if(m_root) {
        delete m_root;
        m_root = NULL;
    }
    m_traverse.rewind();
}
//------------------------------------------------------------------------------

int gfx::CQuadtree::insert(CTreeNodeObject* pObject, STreeNode* pTreeNode) {
    if(!pObject) {
        return -1;
    }
    if(!pTreeNode) {
        if(!m_root) {
            m_root = new SQuadtreeNode(NULL, Vector3f(0.0f, 0.0f, 0.0f), 0);
        }
        pTreeNode = m_root;
    } else if(pTreeNode->getType() != TREE_NODE_QUADTREE) {
        return -1;
    }

    int i = 0, j = 0;
    Vector2f c;
    // Check child nodes to see if object fits in one of them.
    if(pTreeNode->depth + 1 < (int)getMaxDepth()) {
        float halfSize = getWorldSize().x / (float)(2 << pTreeNode->depth);
        float quarterSize = halfSize / 2.0f;
        float offset = quarterSize;

        for(j = 0; j < 2; j++) {
            for(i = 0; i < 2; i++) {
                c.x = pTreeNode->center.x + ((i == 0) ? -offset : offset);
                c.y = pTreeNode->center.y + ((j == 0) ? -offset : offset);

                SQuadtreeNode *quadNode = static_cast<SQuadtreeNode *>(pTreeNode);

                if(fitsInBox((CSceneNode *)pObject, c, quarterSize)) {
                    // Recurse into this node.
                    if(quadNode->child[j][i] == NULL) {
                        quadNode->child[j][i] = new SQuadtreeNode(quadNode, c, pTreeNode->depth + 1);
                    }
                    return insert(pObject, quadNode->child[j][i]);
                }
            }
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

gfx::STreeNode* gfx::CQuadtree::next(void) {
    return m_traverse.next(m_root);
}
//------------------------------------------------------------------------------

void gfx::CQuadtree::rewind(void) {
    m_traverse.rewind();
}
//------------------------------------------------------------------------------

void gfx::CQuadtree::skip(void) {
    m_traverse.skip(m_root);
}
//------------------------------------------------------------------------------
