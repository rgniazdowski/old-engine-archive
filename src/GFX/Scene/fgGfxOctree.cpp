/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxOctree.h"

using namespace fg;

//------------------------------------------------------------------------------

gfx::COctree::COctree() :
m_root(NULL) { }
//------------------------------------------------------------------------------

gfx::COctree::COctree(const COctree& orig) { }
//------------------------------------------------------------------------------

gfx::COctree::~COctree() {
    if(m_root) {
        delete m_root;
        m_root = NULL;
    }
}
//------------------------------------------------------------------------------

void gfx::COctree::deleteRoot(void) {
    if(m_root) {
        delete m_root;
        m_root = NULL;
    }
    m_traverse.rewind();
}
//------------------------------------------------------------------------------

int gfx::COctree::insert(traits::CSpatialObject* pObject, STreeNode* pTreeNode) {
    return -1;
}
//------------------------------------------------------------------------------

gfx::SOctreeNode* gfx::COctree::STraverse::next(SOctreeNode *pRoot) {
    if(!current) {
        if(!pRoot)
            return 0;
        rewind();
        current = pRoot;
        count++;
        return current;
    }

    for(int i = idx; i < 8; i++) {
        uintptr_t offset = (uintptr_t)(&current->child[0][0][0]);
        offset += sizeof (SOctreeNode*)*(i);
        SOctreeNode *node = *((SOctreeNode**)offset);
        if(node) {
            idx = i + 1;
            nodeStack.push(current);
            idStack.push(idx);
            idx = 0;
            current = node;
            count++;
            return node;
        }
    }

    if(idStack.empty()) {
        current = NULL;
        return current;
    }

    idx = idStack.top();
    idStack.pop();
    current = nodeStack.top();
    nodeStack.pop();

    if(!current) {
        return current;
    }
    return next(pRoot);
}
//------------------------------------------------------------------------------

gfx::STreeNode* gfx::COctree::next(void) {
    return m_traverse.next(m_root);
}
//------------------------------------------------------------------------------

void gfx::COctree::rewind(void) {
    m_traverse.rewind();
}
//------------------------------------------------------------------------------

void gfx::COctree::skip(void) {
    m_traverse.skip(m_root);
}
//------------------------------------------------------------------------------
