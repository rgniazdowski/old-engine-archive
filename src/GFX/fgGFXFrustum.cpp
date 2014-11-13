/* 
 * File:   fgGFXFrustum.cpp
 * Author: vigilant
 * 
 * Created on November 13, 2014, 7:23 AM
 */

#include "fgGFXFrustum.h"
#include "Math/fgMathLib.h"

/**
 * 
 */
fgGfxFrustum::fgGfxFrustum() { }

/**
 * 
 * @param orig
 */
fgGfxFrustum::fgGfxFrustum(const fgGfxFrustum& orig) { }

/**
 * 
 */
fgGfxFrustum::~fgGfxFrustum() { }

/**
 * 
 * @param angle
 * @param ratio
 * @param nearD
 * @param farD
 */
void fgGfxFrustum::setCameraInternals(const float angle,
                                      const float ratio,
                                      const float nearD,
                                      const float farD) {
    this->m_aspect = ratio;
    this->m_angle = angle;
    this->m_nearD = nearD;
    this->m_farD = farD;

    this->m_tang = (float)tan(angle * FG_DEG2RAD * 0.5);
    this->m_nh = nearD * this->m_tang;
    this->m_nw = m_nh * ratio;
    this->m_fh = farD * this->m_tang;
    this->m_fw = this->m_fh * ratio;
}
#include <cstdio>

/**
 * 
 * @param p
 * @param l
 * @param u
 */
void fgGfxFrustum::setCamera(const fgVector3f &p, const fgVector3f &l, const fgVector3f &u) {
    fgVector3f dir, nc, fc, X, Y, Z;

    Z = p - l;
    Z = fgMath::normalize(Z);
    //Z.normalize();

    X = fgMath::cross(u, Z);
    X = fgMath::normalize(X);
    //X.normalize();

    Y = fgMath::cross(Z, X);

    nc = p - Z * m_nearD;
    fc = p - Z * m_farD;

    m_point.ntl = nc + Y * m_nh - X * m_nw;
    m_point.ntr = nc + Y * m_nh + X * m_nw;
    m_point.nbl = nc - Y * m_nh - X * m_nw;
    m_point.nbr = nc - Y * m_nh + X * m_nw;

    m_point.ftl = fc + Y * m_fh - X * m_fw;
    m_point.ftr = fc + Y * m_fh + X * m_fw;
    m_point.fbl = fc - Y * m_fh - X * m_fw;
    m_point.fbr = fc - Y * m_fh + X * m_fw;

    const char *info = "TOP";
    //    m_planes[TOP].set(m_point.ntr, m_point.ntl, m_point.ftl);
    fgVec3f VV = m_planes[TOP].n;
    /*
    printf("Vec3[%s](%.2f, %.2f, %.2f)\n", info, VV.x, VV.y, VV.z);
    printf("D: %.2f\n", m_planes[TOP].d);

    info = "BOTTOM";
    m_planes[BOTTOM].set(m_point.nbl, m_point.nbr, m_point.fbr);
    VV = m_planes[BOTTOM].n;
    printf("Vec3[%s](%.2f, %.2f, %.2f)\n", info, VV.x, VV.y, VV.z);
    printf("D: %.2f\n", m_planes[BOTTOM].d);

    info = "LEFT";
    m_planes[LEFT].set(m_point.ntl, m_point.nbl, m_point.fbl);
    VV = m_planes[LEFT].n;
    printf("Vec3[%s](%.2f, %.2f, %.2f)\n", info, VV.x, VV.y, VV.z);
    printf("D: %.2f\n", m_planes[LEFT].d);

    info = "RIGHT";
    m_planes[RIGHT].set(m_point.nbr, m_point.ntr, m_point.fbr);
    VV = m_planes[RIGHT].n;
    printf("Vec3[%s](%.2f, %.2f, %.2f)\n", info, VV.x, VV.y, VV.z);
    printf("D: %.2f\n", m_planes[RIGHT].d);

    info = "NEARP";
    m_planes[NEARP].set(m_point.ntl, m_point.ntr, m_point.nbr);
    VV = m_planes[NEARP].n;
    printf("Vec3[%s](%.2f, %.2f, %.2f)\n", info, VV.x, VV.y, VV.z);
    printf("D: %.2f\n", m_planes[NEARP].d);

    info = "FARP";
    m_planes[FARP].set(m_point.ftr, m_point.ftl, m_point.fbl);
    VV = m_planes[FARP].n;    
    printf("Vec3[%s](%.2f, %.2f, %.2f)\n", info, VV.x, VV.y, VV.z);
    printf("D: %.2f\n", m_planes[FARP].d);
     */


    ///////////////////////////////////////////////////////////
    //printf("\n");
    info = "NEARP";
    m_planes[NEARP].set(-Z, nc);
    //printf("Vec3[%s](%.2f, %.2f, %.2f)\n", info, VV.x, VV.y, VV.z);
    //printf("D: %.2f\n", m_planes[NEARP].d);

    info = "FARP";
    m_planes[FARP].set(Z, fc);
    VV = m_planes[FARP].n;
    //printf("Vec3[%s](%.2f, %.2f, %.2f)\n", info, VV.x, VV.y, VV.z);
    //printf("D: %.2f\n", m_planes[FARP].d);

    fgVec3f aux, normal;

    info = "TOP";
    aux = (nc + Y * m_nh) - p;
    aux = fgMath::normalize(aux);
    normal = fgMath::cross(aux, X);
    m_planes[TOP].set(normal, nc + Y * m_nh);
    VV = m_planes[TOP].n;
    //printf("Vec3[%s](%.2f, %.2f, %.2f)\n", info, VV.x, VV.y, VV.z);
    //printf("D: %.2f\n", m_planes[TOP].d);

    info = "BOTTOM";
    aux = (nc - Y * m_nh) - p;
    aux = fgMath::normalize(aux);
    normal = fgMath::cross(X, aux);
    m_planes[BOTTOM].set(normal, nc - Y * m_nh);
    VV = m_planes[BOTTOM].n;
    //printf("Vec3[%s](%.2f, %.2f, %.2f)\n", info, VV.x, VV.y, VV.z);
    //printf("D: %.2f\n", m_planes[BOTTOM].d);

    info = "LEFT";
    aux = (nc - X * m_nw) - p;
    aux = fgMath::normalize(aux);
    normal = fgMath::cross(aux, Y);
    m_planes[LEFT].set(normal, nc - X * m_nw);
    VV = m_planes[LEFT].n;
    //printf("Vec3[%s](%.2f, %.2f, %.2f)\n", info, VV.x, VV.y, VV.z);
    //printf("D: %.2f\n", m_planes[LEFT].d);


    info = "RIGHT";
    aux = (nc + X * m_nw) - p;
    aux = fgMath::normalize(aux);
    //normal = Y * aux;
    normal = fgMath::cross(Y, aux);
    m_planes[RIGHT].set(normal, nc + X * m_nw);
    VV = m_planes[RIGHT].n;
    //printf("Vec3[%s](%.2f, %.2f, %.2f)\n", info, VV.x, VV.y, VV.z);
    //printf("D: %.2f\n", m_planes[RIGHT].d);
}

/**
 * 
 * @param p
 * @return 
 */
int fgGfxFrustum::testPoint(const fgVector3f &p) {
    // #FIXME - OPTIMIZE!
    int result = INSIDE;
    for(int i = 0; i < 6; i++) {
        float d = this->m_planes[i].distance(p);
        if(d < 0)
            return OUTSIDE;
    }
    return result;
}

/**
 * 
 * @param p
 * @param raio
 * @return 
 */
int fgGfxFrustum::testSphere(const fgVector3f &p, const float radius) {
    // #FIXME - OPTIMIZE!
    // #FIXME - remember that for now this all works with worldspace (MVP transform)
    int result = INSIDE;
    float distance;

    for(int i = 0; i < NUM_PLANES; i++) {
        distance = m_planes[i].distance(p);
        if(distance < -radius)
            return OUTSIDE;
        else if(distance < radius)
            result = INTERSECT;
    }
    return result;
}

/**
 * 
 * @param b
 * @return 
 */
int fgGfxFrustum::testAABB(const fgAABoundingBox3Df &b) {
    // #FIXME - OPTIMIZE!
    int result = INSIDE;
    fgVec3f center = b.getCenter();
    fgVec3f extent = b.getExtent();

    for(int i = 0; i < NUM_PLANES; i++) {
        //and since plane is(expected to be) constant for some number of boxes, 
        //we can compute the abs once(it’s just an and with a constant anyway) 
        //and keep the results in a register – it boils down to having a 
        //second vector, absPlane, that’s just the componentwise abs of plane

        //Using this notation, we get :
        fgVec3f absPlane = fgMath::abs(m_planes[i].n);
        float d = fgMath::dot(center, m_planes[i].n);
        float r = fgMath::dot(extent, absPlane);

        if(d + r < -m_planes[i].d)
            return OUTSIDE;
        
//        if(d - r >= -m_planes[i].d) {
//            // fully inside
//        } if(d + r > -m_planes[i].d) {
//            // partially inside
//        } else {
//        }

        // P max
        //if(m_planes[i].distance(b.getVertexP(m_planes[i].n)) < 0)
        //    return OUTSIDE;
        // M min
        //else if(m_planes[i].distance(b.getVertexN(m_planes[i].n)) < 0)
        //    result = INTERSECT;
    }
    return result;
}
