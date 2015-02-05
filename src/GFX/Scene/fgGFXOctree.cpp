/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXOctree.h"
#include "fgGameMain.h"

using namespace fg;

/**
 * 
 */
gfx::COctree::COctree() :
m_root(NULL) { }

/**
 * 
 * @param orig
 */
gfx::COctree::COctree(const COctree& orig) { }

/**
 * 
 */
gfx::COctree::~COctree() {
    if(m_root) {
        delete m_root;
        m_root = NULL;
    }
}

/**
 * 
 * @param sceneNode
 * @param treeNode
 * @return 
 */
int gfx::COctree::insert(CSceneNode* sceneNode, STreeNode* treeNode) {
    return -1;
}

/**
 *
 */
gfx::STreeNode* gfx::COctree::next(void) {
    return m_traverse.next(m_root);
}

/**
 * 
 */
void gfx::COctree::rewind(void) {
    m_traverse.rewind();
}

/**
 * 
 */
void gfx::COctree::skip(void) {
    m_traverse.skip(m_root);
}