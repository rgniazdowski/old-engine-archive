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
 * File:   fgGFXPlane.h
 * Author: vigilant
 *
 * Created on November 13, 2014, 6:55 AM
 */

#ifndef FG_INC_GFX_PLANE
    #define FG_INC_GFX_PLANE
    #define FG_INC_GFX_PLANE_BLOCK

    #include "fgGFXVertex.h"
    #include "Math/fgMathLib.h"

namespace fg {
    namespace gfx {

        /**
         *
         */
        template<class TValueType>
        struct SPlaneT {
            ///
            typedef SPlaneT<TValueType> self_type;
            ///
            typedef SPlaneT<TValueType> type;
            ///
            typedef typename fg::Vector3T<TValueType>::type vector_type;
            ///
            typedef TValueType value_type;

            enum Halfspace {
                NEGATIVE = -1,
                ON_PLANE = 0,
                POSITIVE = 1
            };

            /// Normal vector
            vector_type n;
            /// 
            value_type d;
            /**
             * 
             * @param v1
             * @param v2
             * @param v3
             */
            SPlaneT(const vector_type &v1, const vector_type &v2, const vector_type &v3) {
                set(v1, v2, v3);
            }
            /**
             * 
             * @param other
             */
            SPlaneT(const self_type& other) {
                this->n = other.n;
                this->d = other.d;
            }
            /**
             * 
             */
            SPlaneT() : n(0), d(0) { }
            /**
             * 
             */
            ~SPlaneT() { }

        public:
            /**
             * 
             * @param v1
             * @param v2
             * @param v3
             */
            void set(const vector_type &v1, const vector_type &v2, const vector_type &v3) {
                vector_type aux1, aux2;

                aux1 = v1 - v2;
                aux2 = v3 - v2;

                this->n = aux2 * aux1;
                this->n = fg::math::normalize(this->n);
                this->d = -fg::math::dot(this->n, v2);
            }
            /**
             * 
             * @param normal
             * @param point
             */
            void set(const vector_type &normal, const vector_type &point) {
                this->n = fg::math::normalize(normal);
                this->d = -fg::math::dot(this->n, point);
            }
            /**
             * 
             * @param _a
             * @param _b
             * @param _c
             * @param _d
             */
            void set(const float _a, const float _b, const float _c, const float _d) {
                // set the normal vector
                this->n = vector_type(_a, _b, _c);
                this->d = _d;
                this->normalize();
            }
            /**
             * 
             */
            void normalize(void) {
                float l = fg::math::length(this->n);
                this->n.x = this->n.x / l;
                this->n.y = this->n.y / l;
                this->n.z = this->n.z / l;
                this->d = this->d / l;
            }
            /**
             * 
             * @param _p
             * @return 
             */
            float distance(const vector_type &point) {
                return (d + fg::math::dot(n, point));
                //return (d + normal.innerProduct(p));
            }
            /**
             * 
             * @param _p
             * @return 
             */
            Halfspace classify(const vector_type &point) {
                float _d = distance(point);
                if(_d < 0) return NEGATIVE;
                if(_d > 0) return POSITIVE;
                return ON_PLANE;
            }

        };

        ///
        typedef SPlaneT<int> Planei;
        ///
        typedef SPlaneT<float> Planef;
        ///
        typedef SPlaneT<unsigned int> Planeu;
        ///
        typedef SPlaneT<double> Planed;

    }
}

    #include <cstdio>
inline void dumpPlane(const fg::gfx::Planef & plane, const char *title) {
    printf("%s = { %.2f %.2f %.2f d=%.2f}\n", (title ? title : "X"), plane.n.x, plane.n.y, plane.n.z, plane.d);
}

    #undef FG_INC_GFX_PLANE_BLOCK
#endif	/* FG_INC_GFX_PLANE */

