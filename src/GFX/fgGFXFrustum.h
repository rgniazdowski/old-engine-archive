/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXFrustum.h
 * Author: vigilant
 *
 * Created on November 13, 2014, 7:23 AM
 */

#ifndef _FG_GFX_FRUSTUM_H_
    #define _FG_GFX_FRUSTUM_H_
    #define _FG_GFX_FRUSTUM_H_BLOCK_

    #include "fgGFXPlane.h"
    #ifndef _FG_GFX_AA_BOUNDING_BOX_H_
        #include "fgGFXAABoundingBox.h"
    #endif

/**
 * 
 */
class fgGfxFrustum {
public:

    enum {
        LEFT = 0,
        RIGHT = 1,
        TOP = 2,
        BOTTOM = 3,
        NEARP = 4,
        FARP = 5,
        NUM_PLANES = 6
    };

    enum {
        OUTSIDE,
        INTERSECT,
        INSIDE
    };

    enum {
        NEAR_TOP_LEFT = 0,
        NEAR_TOP_RIGHT = 1,
        NEAR_BOTTOM_LEFT = 2,
        NEAR_BOTTOM_RIGHT = 3,

        FAR_TOP_LEFT = 4,
        FAR_TOP_RIGHT = 5,
        FAR_BOTTOM_LEFT = 6,
        FAR_BOTTOM_RIGHT = 7,

        NUM_FRUSTUM_POINTS = 8
    };

public:
    /**
     * 
     */
    fgGfxFrustum();
    /**
     * 
     * @param orig
     */
    fgGfxFrustum(const fgGfxFrustum& orig);
    /**
     * 
     */
    virtual ~fgGfxFrustum();

public:
    /**
     * 
     * @param angle
     * @param ratio
     * @param nearD
     * @param farD
     */
    void setCamera(const float angle,
                   const float ratio,
                   const float zNear,
                   const float zFar);
    /**
     * 
     * @param eye
     * @param center
     * @param up
     */
    void set(const fgVector3f &eye,
             const fgVector3f &center,
             const fgVector3f &up);

    /**
     * 
     * @param m
     */
    void set(const fgMatrix4f &m);

    /**
     * 
     * @param point
     * @return 
     */
    int testPoint(const fgVector3f &point);
    /**
     * 
     * @param point
     * @param radius
     * @return 
     */
    int testSphere(const fgVector3f &point, const float radius);
    /**
     * 
     * @param box
     * @return 
     */
    int testAABB(const fgAABoundingBox3Df &box);

public:
    /**
     * 
     * @return 
     */
    fgPlanef *getPlanes(void) {
        return m_planes;
    }
    /**
     * 
     * @return 
     */
    fgVector3f *getFrustumPoints(void) {
        return m_points;
    }
    /**
     * 
     * @return 
     */
    float getZNear(void) const {
        return m_zNear;
    }
    /**
     * 
     * @return 
     */
    float getZFar(void) const {
        return m_zFar;
    }

private:
    ///
    fgPlanef m_planes[NUM_PLANES];

    union {

        struct {
            /// Near Top Left
            fgVector3f ntl;
            /// Near Top Right
            fgVector3f ntr;
            /// Near Bottom Left
            fgVector3f nbl;
            /// Near Bottom Right
            fgVector3f nbr;
            /// Far Top Left
            fgVector3f ftl;
            /// Far Top Right
            fgVector3f ftr;
            /// Far Bottom Left
            fgVector3f fbl;
            /// Far Bottom Right
            fgVector3f fbr;
        } m_point;
        ///
        fgVector3f m_points[NUM_FRUSTUM_POINTS];
    };

    ///
    float m_zNear;
    ///
    float m_zFar;

    union {
        ///
        float m_ratio;
        ///
        float m_aspect;
    };
    ///
    float m_angle;
    ///
    float m_tang;

    ///
    float m_nw;
    ///
    float m_nh;
    ///
    float m_fw;
    ///
    float m_fh;
};

    #undef _FG_GFX_FRUSTUM_H_BLOCK_
#endif	/* _FG_GFX_FRUSTUM_H_ */

