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
 * File:   fgGfxBspNode.cpp
 * Author: vigilant
 * 
 * Created on May 10, 2015, 11:56 AM
 */

#include "fgGfxBspNode.h"
#include "fgGfxBspTree.h"
#include "GFX/fgGfxPolygon.h"

using namespace fg;

//------------------------------------------------------------------------------

gfx::CBspNode::CBspNode(CBspTree* pBsp, unsigned long int _nflags) {
    m_idxNodeThis = -1;
    m_nodeIdx[N_BACK] = -1;
    m_nodeIdx[N_FRONT] = -1;
    m_planeIdx = -1;
    m_nPolys = 0;
    m_polyIdx = -1;
    m_flags = _nflags;
    m_pBsp = pBsp;
    m_leafIdx = -1;
    m_idxParent = -1;
}
//------------------------------------------------------------------------------

gfx::CBspNode::~CBspNode() { }
//------------------------------------------------------------------------------

gfx::CBspNode* gfx::CBspNode::getBack(void) {
    if(m_nodeIdx[N_BACK] >= 0)
        return m_pBsp->m_nodes[m_nodeIdx[N_BACK]];
    return 0;
}
//------------------------------------------------------------------------------

gfx::CBspNode* gfx::CBspNode::getFront(void) {
    if(m_nodeIdx[N_FRONT] >= 0)
        return m_pBsp->m_nodes[m_nodeIdx[N_FRONT]];
    return 0;
}
//------------------------------------------------------------------------------

gfx::CBspNode* gfx::CBspNode::getParent(void) {
    if(m_idxParent >= 0)
        return m_pBsp->m_nodes[m_idxParent];
    return 0;
}
//------------------------------------------------------------------------------

gfx::Planef& gfx::CBspNode::getPlane(void) const {
    if(m_planeIdx >= 0 && m_planeIdx < (int)m_pBsp->m_planes.size())
        return m_pBsp->m_planes[m_planeIdx];
    return m_pBsp->m_planes[0];
}
//------------------------------------------------------------------------------

gfx::SPolygon* gfx::CBspNode::getPolygons(int& count) {
    count = m_nPolys;
    return &(m_pBsp->getPolygons()[m_polyIdx]);
}
//------------------------------------------------------------------------------

gfx::CBspLeaf::CBspLeaf(CBspTree* pBsp, unsigned long int _nflags) :
base_type(pBsp, _nflags),
m_pvsIdx(-1),
m_flags(0),
m_portalIdxes() {
    m_portalIdxes.reserve(4);
}
//------------------------------------------------------------------------------

gfx::CBspLeaf::~CBspLeaf() {
    m_portalIdxes.clear();
}
//------------------------------------------------------------------------------
