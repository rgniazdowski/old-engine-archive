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
 * File:   fgGfxPortal.cpp
 * Author: vigilant
 * 
 * Created on May 10, 2015, 12:07 PM
 */

#include "fgGfxPortal.h"
#include "fgGfxPortalProcessor.h"
#include "fgGfxBspNode.h"

using namespace fg;

//------------------------------------------------------------------------------
static float GEpsilon = 1.0f / 8.0f;
//------------------------------------------------------------------------------

gfx::CPortal::CPortal() : base_type() { };
//------------------------------------------------------------------------------

gfx::CPortal::~CPortal() {
    m_vertexes.clear();
    m_sideLIdx.clear();
    m_sideLIdxFinal.clear();
}
//------------------------------------------------------------------------------

gfx::CPortal::CPortal(CPortalProcessor* pPortProc) :
base_type(),
m_planeIdx(-1),
m_flags(NONE),
m_pPortProc(pPortProc) { }
//------------------------------------------------------------------------------

gfx::CPortal::CPortal(const CPortal& r) {
    m_planeIdx = r.m_planeIdx;
    m_flags = r.m_flags;
    m_vertexes = r.m_vertexes;
    m_sideLIdx = r.m_sideLIdx;
    this->n = r.n;
    this->d = r.d;
    m_pPortProc = r.m_pPortProc;
    m_idxThis = r.m_idxThis;
}
//------------------------------------------------------------------------------

void gfx::CPortal::reverse(void) {
    setFlag(REVERSED, FG_TRUE);
    this->n *= -1.0f;
    this->d = -d;
    m_vertexes.reverse();

}
//------------------------------------------------------------------------------

gfx::CPortal& gfx::CPortal::operator =(const CPortal& other) {
    if(this != &other) {
        m_planeIdx = other.m_planeIdx;
        m_flags = other.m_flags;
        m_vertexes = other.m_vertexes;
        m_sideLIdx = other.m_sideLIdx;
        this->n = other.n;
        this->d = other.d;
        m_pPortProc = other.m_pPortProc;
        m_idxThis = other.m_idxThis;
    }
    return *this;
}
//------------------------------------------------------------------------------

Vector3f gfx::CPortal::getCenter(void) const {
    Vector3f ret;
    for(unsigned int i = 0; i < m_vertexes.size(); ++i) {
        ret += m_vertexes[i];
    }
    ret /= (float)m_vertexes.size();
    return ret;
}
//------------------------------------------------------------------------------

void gfx::CPortal::calcNormal(void) {
    base_type::set(m_vertexes[0], m_vertexes[1], m_vertexes[2]);
}
//------------------------------------------------------------------------------

void gfx::CPortal::split(Planef& plane, gfx::CPortal& a, gfx::CPortal& b) {
    a.m_vertexes.clear();
    b.m_vertexes.clear();
    a.copyProperties(*this);
    b.copyProperties(*this);

    if(math::isZero(plane.d - d)) {
        if(math::isZero(math::dot(this->n, plane.n) - 1)) {
            a.m_vertexes = m_vertexes;
            return;
        }
    }
    Vector3f iv;
    Vector3f itxA = m_vertexes.back();
    float fB;
    float fA = plane.distance(itxA);

    CVector<Vector3f>::iterator end = m_vertexes.end();
    for(CVector<Vector3f>::iterator it = m_vertexes.begin(); it != end; it++) {
        Vector3f &itxB = *it;
        fB = plane.distance(itxB);
        if(fA < GEpsilon && fA > -GEpsilon)fA = 0;
        if(fB < GEpsilon && fB > -GEpsilon)fB = 0;
        if(fB > GEpsilon) {
            if(fA < -GEpsilon) {
                float t = -fA / (fB - fA);                
                iv = math::mix(itxA, itxB, t);
                a.m_vertexes.push_back(iv);
                b.m_vertexes.push_back(iv);
            }
            a.m_vertexes.push_back(itxB);
        } else if(fB < -GEpsilon) {
            if(fA > GEpsilon) {
                float t = -fA / (fB - fA); // t of segment
                iv = math::mix(itxA, itxB, t);
                a.m_vertexes.push_back(iv);
                b.m_vertexes.push_back(iv);
            }
            b.m_vertexes.push_back(itxB);
        } else {
            a.m_vertexes.push_back(itxB);
            b.m_vertexes.push_back(itxB);
        }

        itxA = itxB;
        fA = fB;
    }

    if(a.m_vertexes.size() <= 3) {
        if(b.m_vertexes.size())
            b.m_vertexes = m_vertexes;
    } else if(b.m_vertexes.size() <= 3) {

        if(a.m_vertexes.size())
            a.m_vertexes = m_vertexes;
    }
}
//------------------------------------------------------------------------------

gfx::CPortal::RelPos gfx::CPortal::classify(Planef& plane) {
    int fronts = 0, backs = 0, coinciss = 0;
    int vxes = m_vertexes.size();
    float rdp;
    CVector<Vector3f>::iterator end = m_vertexes.end();
    for(CVector<Vector3f>::iterator vx = m_vertexes.begin(); vx != end; vx++) {
        rdp = plane.distance(*vx);
        if(rdp > .5f)
            fronts++;
        else if(rdp < -.5f)
            backs++;
        else {
            coinciss++;
            backs++;
            fronts++;
        }
    }
    if(coinciss == vxes)
        return RelPos::ON_PLANE;
    if(fronts == vxes)
        return RelPos::ON_FRONT;
    if(backs == vxes)
        return RelPos::ON_BACK;
    return RelPos::ON_SPLIT;
}
//------------------------------------------------------------------------------

void gfx::CPortal::copyProperties(CPortal& other) {
    m_planeIdx = other.m_planeIdx;
    m_flags = other.m_flags;
    m_sideLIdx = other.m_sideLIdx;
    this->n = other.n;
    this->d = other.d;
    m_idxThis = other.m_idxThis;
}
//------------------------------------------------------------------------------

gfx::CBspLeaf* gfx::CPortal::getBackLeaf(void) {
    //ASSERT(m_sideLIdx.size() == 2);
    return m_pPortProc->getLeaf(m_sideLIdx[0]);
}
//------------------------------------------------------------------------------

gfx::CBspLeaf* gfx::CPortal::getFrontLeaf(void) {
    //ASSERT(m_sideLIdx.size() == 2);
    return m_pPortProc->getLeaf(m_sideLIdx[1]);
}
//------------------------------------------------------------------------------

gfx::Planef& gfx::CPortal::getPlane(void) {
    return m_pPortProc->getPlane(m_planeIdx);
}
//------------------------------------------------------------------------------

gfx::Planef const& gfx::CPortal::getPlane(void) const {
    return m_pPortProc->getPlane(m_planeIdx);
}
//------------------------------------------------------------------------------
