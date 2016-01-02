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
 * File:   fgGFXFrustum.cpp
 * Author: vigilant
 * 
 * Created on November 13, 2014, 7:23 AM
 */

#include "fgGfxFrustum.h"
#include "Math/fgMathLib.h"
#include "fgGfxGL.h"
#include "fgGfxBoundingVolume.h"

using namespace fg;

//------------------------------------------------------------------------------

gfx::CFrustum::CFrustum() { }
//------------------------------------------------------------------------------

gfx::CFrustum::CFrustum(const CFrustum& orig) { }
//------------------------------------------------------------------------------

gfx::CFrustum::~CFrustum() { }
//------------------------------------------------------------------------------

void gfx::CFrustum::setCamera(const float angle,
                              const float ratio,
                              const float zNear,
                              const float zFar) {
    this->m_aspect = ratio;
    this->m_angle = angle;
    this->m_zNear = zNear;
    this->m_zFar = zFar;

    this->m_tang = (float)tan(angle * FG_DEG2RAD * 0.5);
    this->m_nh = zNear * this->m_tang;
    this->m_nw = m_nh * ratio;
    this->m_fh = zFar * this->m_tang;
    this->m_fw = this->m_fh * ratio;
}
//------------------------------------------------------------------------------

void gfx::CFrustum::set(const Vector3f &eye,
                        const Vector3f &center,
                        const Vector3f &up) {
    Vector3f dir, nc, fc, X, Y, Z;

    Z = eye - center;
    Z = math::normalize(Z);

    X = math::cross(up, Z);
    X = math::normalize(X);

    Y = math::cross(Z, X);

    nc = eye - Z * m_zNear;
    fc = eye - Z * m_zFar;

    m_point.ntl = nc + Y * m_nh - X * m_nw;
    m_point.ntr = nc + Y * m_nh + X * m_nw;
    m_point.nbl = nc - Y * m_nh - X * m_nw;
    m_point.nbr = nc - Y * m_nh + X * m_nw;

    m_point.ftl = fc + Y * m_fh - X * m_fw;
    m_point.ftr = fc + Y * m_fh + X * m_fw;
    m_point.fbl = fc - Y * m_fh - X * m_fw;
    m_point.fbr = fc - Y * m_fh + X * m_fw;

    m_planes[NEARP].set(-Z, nc);
    m_planes[FARP].set(Z, fc);

    Vec3f aux, normal;
    aux = (nc + Y * m_nh) - eye;
    aux = math::normalize(aux);
    normal = math::cross(aux, X);
    m_planes[TOP].set(normal, nc + Y * m_nh);

    aux = (nc - Y * m_nh) - eye;
    aux = math::normalize(aux);
    normal = math::cross(X, aux);
    m_planes[BOTTOM].set(normal, nc - Y * m_nh);

    aux = (nc - X * m_nw) - eye;
    aux = math::normalize(aux);
    normal = math::cross(aux, Y);
    m_planes[LEFT].set(normal, nc - X * m_nw);

    aux = (nc + X * m_nw) - eye;
    aux = math::normalize(aux);
    normal = math::cross(Y, aux); //normal = Y * aux;
    m_planes[RIGHT].set(normal, nc + X * m_nw);

#if defined(FG_DEBUG) && 0 // #FIXME
    dumpPlane(m_planes[LEFT], "LEFT");
    dumpPlane(m_planes[RIGHT], "RIGHT");
    dumpPlane(m_planes[TOP], "TOP");
    dumpPlane(m_planes[BOTTOM], "BOTTOM");
    dumpPlane(m_planes[NEARP], "NEARP");
    dumpPlane(m_planes[FARP], "FARP");
#endif
}
//------------------------------------------------------------------------------

void gfx::CFrustum::set(const Matrix4f &matrix) {
    float a = 0.0f, b = 0.0f, c = 0.0f, d = 0.0f;
    // The elements of the 4x4 matrix are stored in
    // column-major order (see "OpenGL Programming Guide",
    // 3rd edition, pp 106, glLoadMatrix).
#if defined(FG_DEBUG) // #FIXME
    //dumpMatrix(math::value_ptr(matrix), NULL); // #FIXME
#endif
    Matrix4f m = math::transpose(matrix);
    /***************************************************************************
     * Supporting Non-Identity World and View Matrices
     ***************************************************************************
     * 
     * Until now we have assumed  that both, the  world and the  view matrix are 
     * identity matrices. However,  the goal  obviously is to make the algorithm 
     * work for  an arbitrary view.  This is, in fact,  so easy that it’s almost 
     * unbelievable.  If you think about it for a moment then you’ll immediately 
     * understand it,  and that’s  why we  are not  going to explain this in any 
     * great detail. All we are giving to you is this:
     * 
     * * 1. If the matrix M is equal to the projection  matrix P (i.e., M = P ), 
     *      then the algorithm gives the clipping planes in view space 
     *      (i.e., camera space).
     * 
     * * 2. If the matrix M is equal to the combined view and projection matrix,
     *      then the algorithm gives the  clipping planes  in world space (i.e., 
     *      M = VP, where V is the view matrix, and P is the projection matrix).
     * 
     * * 3. If the matrix M is equal to the combined world, view, and projection
     *      matrices,  then the  algorithm  gives  the clipping planes in object 
     *      space (i.e., M = W * V * P , where W  is  the world matrix, V is the 
     *      view matrix, and P is the projection matrix).
     * 
     * * 4. and so on...
     ***************************************************************************/
#if defined(FG_USING_OPENGL) || defined(FG_USING_OPENGL_ES)
    // Left clipping plane 
    a = m[3][0] + m[0][0];
    b = m[3][1] + m[0][1];
    c = m[3][2] + m[0][2];
    d = m[3][3] + m[0][3];
    m_planes[LEFT].set(a, b, c, d);
    // Right clipping plane
    a = m[3][0] - m[0][0];
    b = m[3][1] - m[0][1];
    c = m[3][2] - m[0][2];
    d = m[3][3] - m[0][3];
    m_planes[RIGHT].set(a, b, c, d);
    // Top clipping plane
    a = m[3][0] - m[1][0];
    b = m[3][1] - m[1][1];
    c = m[3][2] - m[1][2];
    d = m[3][3] - m[1][3];
    m_planes[TOP].set(a, b, c, d);
    // Bottom clipping plane
    a = m[3][0] + m[1][0];
    b = m[3][1] + m[1][1];
    c = m[3][2] + m[1][2];
    d = m[3][3] + m[1][3];
    m_planes[BOTTOM].set(a, b, c, d);
    // Near clipping plane
    a = m[3][0] + m[2][0];
    b = m[3][1] + m[2][1];
    c = m[3][2] + m[2][2];
    d = m[3][3] + m[2][3];
    m_planes[NEARP].set(a, b, c, d);
    // Far clipping plane
    a = m[3][0] - m[2][0];
    b = m[3][1] - m[2][1];
    c = m[3][2] - m[2][2];
    d = m[3][3] - m[2][3];
    m_planes[FARP].set(a, b, c, d);
#elif defined(FG_USING_DIRECTX) 
    // The elements of the 4x4 matrix are stored in
    // row-major order.
    // Left clipping plane 
    a = m[0][3] + m[0][0];
    b = m[1][3] + m[1][0];
    c = m[2][3] + m[2][0];
    d = m[3][3] + m[3][0];
    m_planes[LEFT].set(a, b, c, d);
    // Right clipping plane
    a = m[0][3] - m[0][0];
    b = m[1][3] - m[1][0];
    c = m[2][3] - m[2][0];
    d = m[3][3] - m[3][0];
    m_planes[RIGHT].set(a, b, c, d);
    // Top clipping plane
    a = m[0][3] - m[0][1];
    b = m[1][3] - m[1][1];
    c = m[2][3] - m[2][1];
    d = m[3][3] - m[3][1];
    m_planes[TOP].set(a, b, c, d);
    // Bottom clipping plane
    a = m[0][3] + m[0][1];
    b = m[1][3] + m[1][1];
    c = m[2][3] + m[2][1];
    d = m[3][3] + m[3][1];
    m_planes[BOTTOM].set(a, b, c, d);
    // Near clipping plane
    a = m[0][2]; // + m[0][3];
    b = m[1][2]; // + m[1][3];
    c = m[2][2]; // + m[2][3];
    d = m[3][2]; // + m[3][3];
    m_planes[NEARP].set(a, b, c, d);
    // Far clipping plane
    a = m[0][3] - m[0][2];
    b = m[1][3] - m[1][2];
    c = m[2][3] - m[2][2];
    d = m[3][3] - m[3][2];
    m_planes[FARP].set(a, b, c, d);
#endif
#if defined(FG_DEBUG) && 0 // #FIXME
    dumpPlane(m_planes[LEFT], "LEFT");
    dumpPlane(m_planes[RIGHT], "RIGHT");
    dumpPlane(m_planes[TOP], "TOP");
    dumpPlane(m_planes[BOTTOM], "BOTTOM");
    dumpPlane(m_planes[NEARP], "NEARP");
    dumpPlane(m_planes[FARP], "FARP");
#endif
}
//------------------------------------------------------------------------------

int gfx::CFrustum::testPoint(const Vector3f &point) const {
    // #FIXME - OPTIMIZE!
    int result = INSIDE;
    for(int i = 0; i < 6; i++) {
        float d = this->m_planes[i].distance(point);
        if(d < 0)
            return OUTSIDE;
    }
    return result;
}
//------------------------------------------------------------------------------

int gfx::CFrustum::testSphere(const Vector3f &point, const float radius) const {
    // #FIXME - OPTIMIZE!
    // #FIXME - remember that for now this all works with world-space (MVP transform)
    int result = INSIDE;
    float distance;

    for(int i = 0; i < NUM_PLANES; i++) {
        distance = m_planes[i].distance(point);
        if(distance < -radius)
            return OUTSIDE;
        else if(distance < radius)
            result = INTERSECT;
    }
    return result;
}
//------------------------------------------------------------------------------

int gfx::CFrustum::testSphere(const BoundingVolume3Df& box) const {
    // #FIXME - remember that for now this all works with world-space (MVP transform)
    int result = INSIDE;
    float distance = 0.0f;

    for(int i = 0; i < NUM_PLANES; i++) {
        distance = m_planes[i].distance(box.center);
        if(distance < -box.radius)
            return OUTSIDE;
        else if(distance < box.radius)
            result = INTERSECT;
    }
    return result;
}
//------------------------------------------------------------------------------

int gfx::CFrustum::testVolume(const AABoundingBox3Df& box) const {
    if(!box.isValid())
        return OUTSIDE;
    // #FIXME - OPTIMIZE!
    int result = INSIDE;
    Vec3f center = box.getCenter();
    Vec3f extent = box.getExtent();

    for(int i = 0; i < NUM_PLANES; i++) {
        //and since plane is(expected to be) constant for some number of boxes, 
        //we can compute the abs once(it’s just an and with a constant anyway) 
        //and keep the results in a register – it boils down to having a 
        //second vector, absPlane, that’s just the componentwise abs of plane

        //Using this notation, we get :
        Vec3f absPlane = math::abs(m_planes[i].n);
        float d = math::dot(center, m_planes[i].n);
        float r = math::dot(extent, absPlane);

        if(d + r < -m_planes[i].d) {
            return OUTSIDE;
        }

        // P/N vertex method is FUBAR, something is not working here
        // It yields wrong results
        // P max
        //if(m_planes[i].distance(b.getVertexP(m_planes[i].n)) < 0)
        //    return OUTSIDE;
        // N min
        //else if(m_planes[i].distance(b.getVertexN(m_planes[i].n)) < 0)
        //    result = INTERSECT;
    }
    return result;
}
//------------------------------------------------------------------------------

int gfx::CFrustum::testVolume(const BoundingVolume3Df& box) const {
    if(!box.isValid())
        return OUTSIDE;
    int result = INSIDE;
    for(int i = 0; i < NUM_PLANES; i++) {
        Vec3f absPlane = math::abs(m_planes[i].n);
        float d = math::dot(box.center, m_planes[i].n);
        float r = math::dot(box.extent, absPlane);
        if(d + r < -m_planes[i].d) {
            return OUTSIDE;
        }
    }
    return result;
}
//------------------------------------------------------------------------------

int gfx::CFrustum::testVolume(const Vector3f& center, const float extent) const {
    int result = INSIDE;
    for(int i = 0; i < NUM_PLANES; i++) {
        Vec3f absPlane = math::abs(m_planes[i].n);
        float d = math::dot(center, m_planes[i].n);
        float r = math::dot(Vector3f(extent, extent, extent), absPlane);
        if(d + r < -m_planes[i].d) {
            return OUTSIDE;
        }
    }
    return result;
}
//------------------------------------------------------------------------------

int gfx::CFrustum::testVolume(const Vector3f& center, const Vector3f& extent) const {
    int result = INSIDE;
    for(int i = 0; i < NUM_PLANES; i++) {
        Vec3f absPlane = math::abs(m_planes[i].n);
        float d = math::dot(center, m_planes[i].n);
        float r = math::dot(extent, absPlane);
        if(d + r < -m_planes[i].d) {
            return OUTSIDE;
        }
    }
    return result;
}
//------------------------------------------------------------------------------
