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

int gfx::COctree::insert(CTreeNodeObject* pObject, STreeNode* pTreeNode) {
    return -1;
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
