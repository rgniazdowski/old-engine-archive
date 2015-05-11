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
 * File:   fgGfxPolygon.cpp
 * Author: vigilant
 * 
 * Created on May 9, 2015, 10:35 AM
 */

#include "fgGfxPolygon.h"

using namespace fg;

//------------------------------------------------------------------------------

gfx::SPolygon::SPolygon(unsigned int reserve) :
base_type(),
planeIdx(-1),
materialIdx(-1),
bbox(),
flags(0),
vertexData(NULL) {
    if(reserve < 3)
        reserve = 4;
    vertexData = new CVertexData4v();
    vertexData->reserve(reserve);
}
//------------------------------------------------------------------------------

gfx::SPolygon::~SPolygon() {
    if(vertexData) {
        vertexData->clear(); // vertexes array
        delete vertexData;
        vertexData = NULL;
    }
}
//------------------------------------------------------------------------------

void gfx::SPolygon::calcNormal(void) {
    if(!vertexData)
        return;
    CVertexData4v *data4v = (CVertexData4v *)vertexData;
    fg::Vector3f &a = data4v->at(0).position;
    fg::Vector3f &b = data4v->at(1).position;
    fg::Vector3f &c = data4v->at(2).position;
    this->set(c, b, a);
}
//------------------------------------------------------------------------------

fgBool gfx::SPolygon::operator ==(const SPolygon& p) {
    if(this->n == p.n &&
       this->d == p.d &&
       vertexData->size() == p.vertexData->size()) {
        return !memcmp(vertexData->front(), p.vertexData->front(), sizeof (Vertex4v) * vertexData->size());
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

void gfx::SPolygon::create(int points, Vertex4v* pPoints) {
    vertexData->clear();
    if(points < 3)
        return;
    bbox.invalidate();
    for(int i = 0; i < points; i++) {
        vertexData->append(pPoints[i].position,
                             pPoints[i].normal,
                             pPoints[i].uv,
                             pPoints[i].color);
        bbox.merge(pPoints[i].position);
    }
    calcNormal();
    sortVertexes();
}
//------------------------------------------------------------------------------

void gfx::SPolygon::create(int points, Vector3f* pPoints) {
    vertexData->clear();
    Vector3f* pWalk = pPoints;
    if(points < 3)
        return;
    bbox.invalidate();
    for(int i = 0; i < points; i++) {
        Vector3f &point = *(pWalk++);
        vertexData->append(point);
        bbox.merge(point);
    }
    calcNormal();
    sortVertexes();
}
//------------------------------------------------------------------------------

void gfx::SPolygon::sortVertexes(void) {
    return;
}
//------------------------------------------------------------------------------

fgBool gfx::SPolygon::doesContainPoint(Vector3f& pi) {
    Vector3f v1;
    Vector3f v2;
    float sum = M_PIF * 2.0f;
    Vertex4v *pData = (Vertex4v *)vertexData->front();
    unsigned int n = vertexData->size();
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
//------------------------------------------------------------------------------

gfx::SPolygon::SPolygon(const SPolygon& p) {
    planeIdx = 0;
    flags = 0;
    vertexData = NULL;
    this->operator =(p);
}
//------------------------------------------------------------------------------

gfx::SPolygon& gfx::SPolygon::operator =(const SPolygon& p) {
    if(this != &p) {
        if(vertexData) {
            vertexData->clear();
        } else {
            vertexData = new CVertexData4v();
            if(p.vertexData) {
                if(p.vertexData->size()) {
                    vertexData->reserve(p.vertexData->size());
                }
            }
        }
        copyProperties((SPolygon&)p);
        Vertex4v *pData = (Vertex4v *)p.vertexData->front();
        unsigned int n = p.vertexData->size();
        for(unsigned int i = 0; i < n; i++) {
            Vertex4v &vtx = (*(pData + i));
            vertexData->append(vtx.position, vtx.normal, vtx.uv, vtx.color); // #FIXME
        }
    }
    return *this;
}
//------------------------------------------------------------------------------

void gfx::SPolygon::copyProperties(SPolygon& p) {
    this->n = p.n;
    this->axis = p.axis;
    this->d = p.d;
    bbox = p.bbox;
    flags = p.flags;
    planeIdx = p.planeIdx;
}
//------------------------------------------------------------------------------

void gfx::SPolygon::recalculate(void) {
    bbox.invalidate();
    Vertex4v *pData = (Vertex4v *)vertexData->front();
    unsigned int n = vertexData->size();
    for(unsigned int i = 0; i < n; i++) {
        Vertex4v &vtx = (*(pData + i));
        bbox.merge(vtx.position);
    }
    calcNormal();
}
//------------------------------------------------------------------------------

void gfx::SPolygon::clear(void) {
    bbox.invalidate();
    vertexData->clear();
    this->n = Vector3f(0.0f, 0.0f, 0.0f); // invalid normal
    this->d = 0.0f;
    this->axis = Axis::ANY;
}
//------------------------------------------------------------------------------

void gfx::SPolygon::split(base_type& plane,
                          SPolygon& a,
                          SPolygon& b,
                          fgBool bAnyway) {
    a.copyProperties(*this);
    b.copyProperties(*this);
    Vertex4v iv;
    //Vtx itxB = *vertexData.begin();
    //Vtx itxA = vertexData.back();
    Vertex4v itxA = *((Vertex4v*)vertexData->back());
    float fB = 0.0f;
    float fA = plane.distance(itxA.position);

    Vertex4v *pData = (Vertex4v *)vertexData->front();
    unsigned int n = vertexData->size();
    for(unsigned int i = 0; i < n; i++) {
        Vertex4v &itxB = (*(pData + i));
        //FOREACH(CVector<Vtx>, vertexData, vxI) {
        //itxB = *vxI;
        fB = plane.distance(itxB.position);
        if(fB > .2f) {
            if(fA < -.2f) {
                float t = -fA / (fB - fA);
                iv = Vertex4v::interpolate(itxA, itxB, t);
                //a << iv;
                a.vertexData->append(iv.position, iv.normal, iv.uv, iv.color);
                //b << iv;
                b.vertexData->append(iv.position, iv.normal, iv.uv, iv.color);
            }
            //a << itxB;
            a.vertexData->append(itxB.position, itxB.normal, itxB.uv, itxB.color);
        } else if(fB < -.2f) {
            if(fA > .2f) {
                float t = -fA / (fB - fA); // t of segment
                iv = Vertex4v::interpolate(itxA, itxB, t);
                //a << iv;
                a.vertexData->append(iv.position, iv.normal, iv.uv, iv.color);
                //b << iv;
                b.vertexData->append(iv.position, iv.normal, iv.uv, iv.color);
            }
            //b << itxB;
            b.vertexData->append(itxB.position, itxB.normal, itxB.uv, itxB.color);
        } else {
            //a << itxB;
            a.vertexData->append(itxB.position, itxB.normal, itxB.uv, itxB.color);
            //b << itxB;
            b.vertexData->append(itxB.position, itxB.normal, itxB.uv, itxB.color);
        }
        itxA = itxB;
        fA = fB;
    }

    if(!bAnyway) {
        if(b.vertexData->size() == vertexData->size() && a.vertexData->size() < 3)
            a.clear();
        if(a.vertexData->size() == vertexData->size() && b.vertexData->size() < 3)
            b.clear();
        if(a.vertexData->size() < 3)
            a.clear();
        if(b.vertexData->size() < 3)
            b.clear();
    }

    if(a.vertexData->size() >= 3)
        a.recalculate();
    if(b.vertexData->size() >= 3)
        b.recalculate();
}
//------------------------------------------------------------------------------

void gfx::SPolygon::clip(SPolygon& plane, SPolygon& pout) {
    pout.vertexData->clear();
    pout.bbox.invalidate();
    pout.copyProperties(*this);
    Vertex4v iv;
    //Vertex4v& itxB = *((Vertex4v*)vertexData->front());
    Vertex4v& itxA = *((Vertex4v*)vertexData->back());
    float fB;
    int sB;
    float fA = plane.distance(itxA.position);
    int sA = plane.classify(itxA.position);

    Vertex4v *pData = (Vertex4v *)vertexData->front();
    unsigned int n = vertexData->size();
    for(unsigned int i = 0; i < n; i++) {
        Vertex4v &itxB = (*(pData + i));
        //itxB = *vxI;
        fB = plane.distance(itxB.position);
        sB = plane.classify(itxB.position);
        if(sB > 0) {
            if(sA < 0) {
                float t = -fA / (fB - fA);
                iv = Vertex4v::interpolate(itxA, itxB, t);
                pout.vertexData->append(iv.position, iv.normal, iv.uv, iv.color);
            }
            //pout << itxB;
            pout.vertexData->append(itxB.position, itxB.normal, itxB.uv, itxB.color);
        } else if(sB < 0) {
            if(sA > 0) {
                float t = -fA / (fB - fA); // t of segment
                iv = Vertex4v::interpolate(itxA, itxB, t);
                pout.vertexData->append(iv.position, iv.normal, iv.uv, iv.color);
            }
        } else {
            pout.vertexData->append(itxB.position, itxB.normal, itxB.uv, itxB.color);
        }
        itxA = itxB;
        fA = fB;
    }
    pout.recalculate();
    //ASSERT(pout.vertexData.size() >= 3);
}
//------------------------------------------------------------------------------

int gfx::SPolygon::classify(Vector3f& point) {
    Vector3f vdir = point - ((Vertex4v*)vertexData->front())->position;
    float d = math::dot(vdir, this->n);

    if(d < -.2f)
        return -1;
    else
        if(d > .2f)
        return 1;
    return 0;
}
//------------------------------------------------------------------------------

gfx::SPolygon::RelPos gfx::SPolygon::classify(base_type& plane) {
    unsigned int fronts = 0, backs = 0, coinciss = 0;
    unsigned int vxes = vertexData->size();
    float rdp = 0.0f;

    Vertex4v *pData = (Vertex4v *)vertexData->front();
    unsigned int n = vertexData->size();
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
//------------------------------------------------------------------------------

Vector3f gfx::SPolygon::getCenter(void) const {
    Vector3f ret;
    if(!vertexData)
        return ret;
    CVertexData4v *data4v = (CVertexData4v *)vertexData;
    for(unsigned int i = 0; i < data4v->size(); ++i) {
        ret += data4v->at(i).position;
    }
    ret /= (float)data4v->size();
    return ret;
}
//------------------------------------------------------------------------------
