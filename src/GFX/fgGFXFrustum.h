/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
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

#ifndef FG_INC_GFX_FRUSTUM
    #define FG_INC_GFX_FRUSTUM
    #define FG_INC_GFX_FRUSTUM_BLOCK

    #include "fgGFXPlane.h"

    #ifndef FG_INC_GFX_BOUNDING_VOLUME
        #include "fgGFXBoundingVolume.h"
    #endif

namespace fg {

    namespace gfx {

        /**
         * 
         */
        class CFrustum {
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
            CFrustum();
            /**
             * 
             * @param orig
             */
            CFrustum(const CFrustum& orig);
            /**
             * 
             */
            virtual ~CFrustum();

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
            void set(const Vector3f &eye,
                     const Vector3f &center,
                     const Vector3f &up);

            /**
             * 
             * @param m
             */
            void set(const Matrix4f &m);

            /**
             * 
             * @param point
             * @return 
             */
            int testPoint(const Vector3f &point);
            /**
             * 
             * @param point
             * @param radius
             * @return 
             */
            int testSphere(const Vector3f &point, const float radius);
            /**
             * 
             * @param box
             * @return 
             */
            int testSphere(const BoundingVolume3Df& box);
            /**
             * 
             * @param box
             * @return 
             */
            int testVolume(const AABoundingBox3Df& box);
            /**
             * 
             * @param box
             * @return 
             */
            int testVolume(const BoundingVolume3Df& box);
            /**
             * 
             * @param center
             * @param extent
             * @return 
             */
            int testVolume(const Vector3f& center, const float extent);
            /**
             * 
             * @param center
             * @param extent
             * @return 
             */
            int testVolume(const Vector3f& center, const Vector3f& extent);

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

            struct {
                /// Near Top Left
                Vector3f ntl;
                /// Near Top Right
                Vector3f ntr;
                /// Near Bottom Left
                Vector3f nbl;
                /// Near Bottom Right
                Vector3f nbr;
                /// Far Top Left
                Vector3f ftl;
                /// Far Top Right
                Vector3f ftr;
                /// Far Bottom Left
                Vector3f fbl;
                /// Far Bottom Right
                Vector3f fbr;
            } m_point;
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
    };
};

    #undef FG_INC_GFX_FRUSTUM_BLOCK
#endif	/* FG_INC_GFX_FRUSTUM */
