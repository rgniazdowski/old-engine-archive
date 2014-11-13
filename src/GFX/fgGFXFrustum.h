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
    #include "fgGFXAABoundingBox.h"

/**
 * 
 */
class fgGfxFrustum {
public:

    enum {
        TOP = 0,
        BOTTOM = 1,
        LEFT = 2,
        RIGHT = 3,
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
    void setCameraInternals(const float angle,
                            const float ratio,
                            const float nearD,
                            const float farD);
    /**
     * 
     * @param p
     * @param l
     * @param u
     */
    void setCamera(const fgVector3f &p,
                   const fgVector3f &l,
                   const fgVector3f &u);

    /**
     * 
     * @param p
     * @return 
     */
    int testPoint(const fgVector3f &p);
    /**
     * 
     * @param p
     * @param raio
     * @return 
     */
    int testSphere(const fgVector3f &p, const float radius);
    /**
     * 
     * @param b
     * @return 
     */
    int testAABB(const fgAABoundingBox3Df &b);

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
    
    float getNearD(void) const {
        return m_nearD;
    }
    
    float getFarD(void) const {
        return m_farD;
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
    float m_nearD;
    ///
    float m_farD;

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

