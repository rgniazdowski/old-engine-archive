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
 * Game Programming Gems: Vol 6, General Programming
 * Gem:    BSP Techniques
 * Author: Octavian Marius Chincisan
 */
#include "fgGfxBspTypes.h"
#include "fgGfxBspGeometry.h"
#include "GFX/fgGfxAABoundingBox.h"
#include "GFX/fgGfxVertexData.h"
#include <set>

using namespace fg;

gfx::CPolygon::CPolygon(unsigned int reserve) {
    if(reserve < 3)
        reserve = 4;
    m_vertexData = new CVertexData4v();
    m_vertexData->reserve(reserve);
    m_planeIdx = -1;
    m_flags = 0;
}

gfx::CPolygon::~CPolygon() {
    if(m_vertexData) {
        m_vertexData->clear(); // vertexex array
        delete m_vertexData;
    }
}

void gfx::CPolygon::calcNormal(void) {
    if(!m_vertexData)
        return;
    CVertexData4v *data4v = (CVertexData4v *)m_vertexData;
    fg::Vector3f &a = data4v->at(0).position;
    fg::Vector3f &b = data4v->at(1).position;
    fg::Vector3f &c = data4v->at(2).position;
    this->set(c, b, a);
}

fgBool gfx::CPolygon::operator ==(const CPolygon& p) {
    if(this->n == p.n &&
       this->d == p.d &&
       m_vertexData->size() == p.m_vertexData->size()) {
        return !memcmp(m_vertexData->front(), p.m_vertexData->front(), sizeof (Vertex4v) * m_vertexData->size());
    }
    return FG_FALSE;
}

void gfx::CPolygon::create(int points, Vertex4v* pPoints) {
    m_vertexData->clear();
    if(points < 3)
        return;
    m_bbox.invalidate();
    for(int i = 0; i < points; i++) {
        m_vertexData->append(pPoints[i].position,
                             pPoints[i].normal,
                             pPoints[i].uv,
                             pPoints[i].color);
        m_bbox.merge(pPoints[i].position);
    }
    calcNormal();
    sortVertexes();
}

void gfx::CPolygon::create(int points, Vector3f* pPoints) {
    m_vertexData->clear();
    Vector3f* pWalk = pPoints;
    if(points < 3)
        return;
    m_bbox.invalidate();
    for(int i = 0; i < points; i++) {
        Vector3f &point = *(pWalk++);
        m_vertexData->append(point);
        m_bbox.merge(point);
    }
    calcNormal();
    sortVertexes();
}

void gfx::CPolygon::sortVertexes(void) {
    return;
}

fgBool gfx::CPolygon::doesContainPoint(Vector3f& pi) {
    Vector3f v1;
    Vector3f v2;
    float sum = DOIPI;
    Vertex4v *pData = (Vertex4v *)m_vertexData->front();
    unsigned int n = m_vertexData->size();
    if(!n)
        return FG_FALSE;
    Vertex4v& lastVx = pData[n - 1];
    v1 = lastVx.position;
    v1 -= pi;
    v1 = math::normalize(v1);


    for(unsigned int i = 0; i < n; i++) {
        Vertex4v &wv = (*(pData + i));
        v2 = wv.position;
        if(math::distance(v1, v2) < 1.f)
            return FG_FALSE;
        v2 -= pi;
        v2 = math::normalize(v2);
        sum -= (float)math::acos(math::dot(v1, v2));
        v1 = v2;
    }
    return math::isZero(sum);
}

gfx::CPolygon::CPolygon(const CPolygon& p) {
    this->operator =(p);
}

gfx::CPolygon& gfx::CPolygon::operator =(const CPolygon& p) {
    if(this != &p) {
        m_vertexData->clear();
        copyProperties((CPolygon&)p);
        Vertex4v *pData = (Vertex4v *)p.m_vertexData->front();
        unsigned int n = p.m_vertexData->size();
        for(unsigned int i = 0; i < n; i++) {
            Vertex4v &vtx = (*(pData + i));
            m_vertexData->append(vtx.position, vtx.normal, vtx.uv, vtx.color); // #FIXME
        }
    }
    return *this;
}

void gfx::CPolygon::copyProperties(CPolygon& p) {
    this->n = p.n;
    this->axis = p.axis;
    this->d = p.d;
    m_bbox = p.m_bbox;
    m_flags = p.m_flags;
    m_planeIdx = p.m_planeIdx;
}

void gfx::CPolygon::recalculate(void) {
    m_bbox.invalidate();
    Vertex4v *pData = (Vertex4v *)m_vertexData->front();
    unsigned int n = m_vertexData->size();
    for(unsigned int i = 0; i < n; i++) {
        Vertex4v &vtx = (*(pData + i));
        m_bbox.merge(vtx.position);
    }
    calcNormal();
}

void gfx::CPolygon::clear(void) {
    m_bbox.invalidate();
    m_vertexData->clear();
    this->n = Vector3f(0.0f, 0.0f, 0.0f); // invalid normal
    this->d = 0.0f;
    this->axis = Axis::ANY;
}

void gfx::CPolygon::split(base_type& plane,
                          CPolygon& a,
                          CPolygon& b,
                          fgBool bAnyway) {
    a.copyProperties(*this);
    b.copyProperties(*this);
    Vertex4v iv;
    //Vtx itxB = *m_vertexData.begin();
    //Vtx itxA = m_vertexData.back();
    Vertex4v& itxA = *((Vertex4v*)m_vertexData->back());
    float fB = 0.0f;
    float fA = plane.distance(itxA.position);

    Vertex4v *pData = (Vertex4v *)m_vertexData->front();
    unsigned int n = m_vertexData->size();
    for(unsigned int i = 0; i < n; i++) {
        Vertex4v &itxB = (*(pData + i));
        //FOREACH(CVector<Vtx>, m_vertexData, vxI) {
        //itxB = *vxI;
        fB = plane.distance(itxB.position);
        if(fB > .2f) {
            if(fA < -.2f) {
                float t = -fA / (fB - fA);
                iv = Vertex4v::interpolate(itxA, itxB, t);
                //a << iv;
                a.m_vertexData->append(iv.position, iv.normal, iv.uv, iv.color);
                //b << iv;
                b.m_vertexData->append(iv.position, iv.normal, iv.uv, iv.color);
            }
            //a << itxB;
            a.m_vertexData->append(itxB.position, itxB.normal, itxB.uv, itxB.color);
        } else if(fB < -.2f) {
            if(fA > .2f) {
                float t = -fA / (fB - fA); // t of segment
                iv = Vertex4v::interpolate(itxA, itxB, t);
                //a << iv;
                a.m_vertexData->append(iv.position, iv.normal, iv.uv, iv.color);
                //b << iv;
                b.m_vertexData->append(iv.position, iv.normal, iv.uv, iv.color);
            }
            //b << itxB;
            b.m_vertexData->append(itxB.position, itxB.normal, itxB.uv, itxB.color);
        } else {
            //a << itxB;
            a.m_vertexData->append(itxB.position, itxB.normal, itxB.uv, itxB.color);
            //b << itxB;
            b.m_vertexData->append(itxB.position, itxB.normal, itxB.uv, itxB.color);
        }
        itxA = itxB;
        fA = fB;
    }

    if(!bAnyway) {
        if(b.m_vertexData->size() == m_vertexData->size() && a.m_vertexData->size() < 3)
            a.clear();
        if(a.m_vertexData->size() == m_vertexData->size() && b.m_vertexData->size() < 3)
            b.clear();
        if(a.m_vertexData->size() < 3)
            a.clear();
        if(b.m_vertexData->size() < 3)
            b.clear();
    }

    if(a.m_vertexData->size() >= 3)
        a.recalculate();
    if(b.m_vertexData->size() >= 3)
        b.recalculate();
}

void gfx::CPolygon::clip(CPolygon& plane, CPolygon& pout) {
    pout.m_vertexData->clear();
    pout.m_bbox.invalidate();
    pout.copyProperties(*this);
    Vertex4v iv;
    //Vertex4v& itxB = *((Vertex4v*)m_vertexData->front());
    Vertex4v& itxA = *((Vertex4v*)m_vertexData->back());
    float fB;
    int sB;
    float fA = plane.distance(itxA.position);
    int sA = plane.classify(itxA.position);

    Vertex4v *pData = (Vertex4v *)m_vertexData->front();
    unsigned int n = m_vertexData->size();
    for(unsigned int i = 0; i < n; i++) {
        Vertex4v &itxB = (*(pData + i));
        //itxB = *vxI;
        fB = plane.distance(itxB.position);
        sB = plane.classify(itxB.position);
        if(sB > 0) {
            if(sA < 0) {
                float t = -fA / (fB - fA);
                iv = Vertex4v::interpolate(itxA, itxB, t);
                pout.m_vertexData->append(iv.position, iv.normal, iv.uv, iv.color);
            }
            //pout << itxB;
            pout.m_vertexData->append(itxB.position, itxB.normal, itxB.uv, itxB.color);
        } else if(sB < 0) {
            if(sA > 0) {
                float t = -fA / (fB - fA); // t of segment
                iv = Vertex4v::interpolate(itxA, itxB, t);
                pout.m_vertexData->append(iv.position, iv.normal, iv.uv, iv.color);
            }
        } else {
            pout.m_vertexData->append(itxB.position, itxB.normal, itxB.uv, itxB.color);
        }
        itxA = itxB;
        fA = fB;
    }
    pout.recalculate();
    //ASSERT(pout.m_vertexData.size() >= 3);
}

int gfx::CPolygon::classify(Vector3f& point) {
    Vector3f vdir = point - ((Vertex4v*)m_vertexData->front())->position;
    float d = math::dot(vdir, this->n);

    if(d < -.2f)
        return -1;
    else
        if(d > .2f)
        return 1;
    return 0;
}

gfx::CPolygon::RelPos gfx::CPolygon::classify(base_type& plane) {
    unsigned int fronts = 0, backs = 0, coinciss = 0;
    unsigned int vxes = m_vertexData->size();
    float rdp = 0.0f;

    Vertex4v *pData = (Vertex4v *)m_vertexData->front();
    unsigned int n = m_vertexData->size();
    for(unsigned int i = 0; i < n; i++) {
        Vertex4v &vertex = (*(pData + i));
        rdp = plane.distance(vertex.position);
        if(rdp > .2f) {
            fronts++;
        } else if(rdp < -.2f) {
            backs++;
        } else {
            coinciss++;
            backs++;
            fronts++;
        }
    }

    if(coinciss == vxes) {
        return RelPos::ON_PLANE;
    }
    if(fronts == vxes) {
        return RelPos::ON_FRONT;
    }
    if(backs == vxes) {
        return RelPos::ON_BACK;
    }
    return RelPos::ON_SPLIT;
}

Vector3f gfx::CPolygon::getCenter(void) const {
    Vector3f ret;
    if(!m_vertexData)
        return ret;
    CVertexData4v *data4v = (CVertexData4v *)m_vertexData;
    for(unsigned int i = 0; i < data4v->size(); ++i) {
        ret += data4v->at(i).position;
    }
    ret /= (float)data4v->size();
    return ret;
}
