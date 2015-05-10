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

    #include "fgBool.h"
    #ifndef FG_INC_MATHLIB
        #include "Math/fgMathLib.h"
    #endif 

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
                NEUTRAL = 0,
                POSITIVE = 1
            };

            enum Axis {
                X,
                Y,
                Z,
                ANY_X,
                ANY_Y,
                ANY_Z,
                ANY
            };

            /// Normal vector
            vector_type n;
            /// 
            value_type d;
            ///
            Axis axis;
            /**
             * 
             */
            SPlaneT() : n(0, 0, 0), d(0), axis(Axis::ANY) { }
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
             * @param normal
             * @param point
             */
            SPlaneT(const vector_type &normal, const vector_type &point) {
                set(normal, point);
            }
            /**
             * 
             * @param normal
             * @param _d
             */
            SPlaneT(const vector_type &normal, value_type _d) {
                set(normal, _d);
            }
            /**
             * 
             * @param _a
             * @param _b
             * @param _c
             * @param _d
             */
            SPlaneT(value_type _a, value_type _b, value_type _c, value_type _d) {
                set(_a, _b, _c, _d);
            }
            /**
             * 
             * @param _axis
             * @param _d
             */
            SPlaneT(Axis _axis, value_type _d) {
                set(_axis, _d);
            }
            /**
             * 
             * @param other
             */
            SPlaneT(const self_type& other) {
                this->n = other.n;
                this->d = other.d;
                this->axis = other.axis;
            }
            /**
             * 
             */
            virtual ~SPlaneT() { }

        public:
            /**
             * 
             * @param _axis
             * @param _d
             */
            void set(Axis _axis, value_type _d) {
                this->d = d;
                switch(_axis) {
                    case Axis::X:
                        this->n = vector_type((value_type)1, 0, 0);
                        break;
                    case Axis::Y:
                        this->n = vector_type(0, (value_type)1, 0);
                        break;
                    case Axis::Z:
                        this->n = vector_type(0, 0, (value_type)1);
                        break;
                    default:
                        this->n = vector_type(0, (value_type)1, 0);
                        break;
                }
                this->axis = _axis;
            }
            /**
             * 
             * @param v1
             * @param v2
             * @param v3
             */
            void set(const vector_type &v1,
                     const vector_type &v2,
                     const vector_type &v3) {
                vector_type aux1 = v1 - v2;
                vector_type aux2 = v3 - v2;

                //this->n = aux2 * aux1;
                this->n = math::cross(aux2, aux1);
                this->n = math::normalize(this->n);
                this->d = /*-*/math::dot(this->n, v2);
                determineAxis();
            }
            /**
             * 
             * @param normal
             * @param point
             */
            void set(const vector_type &normal, const vector_type &point) {
                this->n = math::normalize(normal);
                this->d = /*-*/math::dot(this->n, point);
                determineAxis();
            }
            /**
             * 
             * @param normal
             * @param _d
             */
            void set(const vector_type &normal, value_type _d) {
                this->n = math::normalize(normal);
                this->d = _d;
                determineAxis();
            }
            /**
             * 
             * @param _a
             * @param _b
             * @param _c
             * @param _d
             */
            void set(value_type _a, value_type _b, value_type _c, value_type _d) {
                // set the normal vector
                this->n = vector_type(_a, _b, _c);
                this->d = _d;
                normalize();
            }
            /**
             * 
             */
            void normalize(void) {
                value_type l = math::length(this->n);
                this->n.x = this->n.x / l;
                this->n.y = this->n.y / l;
                this->n.z = this->n.z / l;
                this->d = this->d / l;
                determineAxis();
            }
            /**
             * 
             * @param point
             * @return 
             */
            value_type distance(const vector_type& point) {
                return (value_type)(this->d + math::dot(this->n, point));
                //return (value_type)(math::dot(point, this->n) - this->d);
                //return (d + normal.innerProduct(p));
            }
            /**
             * 
             * @param a
             * @param b
             * @param c
             * @return
             */
            value_type distance(value_type a, value_type b, value_type c) {
                return (value_type)(this->d + math::dot(this->n, vector_type(a, b, c)));
                //return (value_type)(math::dot(vector_type(a, b, c), this->n) - this->d);

                //return (d + normal.innerProduct(p));
            }
            /**
             * 
             * @param point
             * @return 
             */
            Halfspace classify(const vector_type& point) {
                value_type _d = distance(point);
                if(_d < (value_type)0) return NEGATIVE;
                if(_d > (value_type)0) return POSITIVE;
                return NEUTRAL;
            }
            /**
             *
             * @return
             */
            Axis determineAxis(void) {
                axis = Axis::ANY;
                if(math::isZero(math::abs(n.x) - (value_type)1.0)) {
                    axis = Axis::X;
                } else if(math::isZero(math::abs(n.y) - (value_type)1.0)) {
                    axis = Axis::Y;
                } else if(math::isZero(math::abs(n.z) - (value_type)1.0)) {
                    axis = Axis::Z;
                }
                return axis;
            }
            /**
             * 
             * @return
             */
            inline char getApproxAlignment(void) {
                if(math::abs(n.x) > math::abs(n.y) && math::abs(n.x) > math::abs(n.z)) {
                    return 'x';
                } else if(math::abs(n.y) > math::abs(n.x) && math::abs(n.y) > math::abs(n.z)) {
                    return 'y';
                }
                return 'z';
            }
            /**
             *
             * @param point
             * @return
             */
            inline value_type fastDistance(const vector_type& point) {
                switch(this->axis) {
                    case Axis::X:
                        if(n.x < 0) {
                            return -(point.x - (-this->d));
                        }
                        return (point.x - this->d);
                        break;
                    case Axis::Y:
                        if(n.y < 0) {
                            return -(point.y - (-this->d));
                        }
                        return (point.y - this->d);
                        break;
                    case Axis::Z:
                        if(n.z < 0) {
                            return -(point.z - (-this->d));
                        }
                        return (point.z - this->d);
                        break;
                    default:
                        break;
                }
                return (value_type)(math::dot(point, this->n) - this->d);
            }
            /**
             *
             */
            inline void reverse(void) {
                this->n *= -1.0f;
                this->d = -this->d;
            }
            /**
             * 
             * @param vpos
             * @param vdir
             * @param ip
             * @return 
             */
            fgBool rayIntersect(const vector_type& rayOrigin,
                                const vector_type& rayDir,
                                vector_type& intersectionPoint,
                                const fgBool bothSides = FG_FALSE) {
                float distance = 0.0f;
                fgBool status = rayIntersect(rayOrigin, rayDir, distance, bothSides);
                if(status) {
                    intersectionPoint = rayOrigin + rayDir * distance;
                }
                return (fgBool)status;
            }
            /**
             *
             * @param rayOrigin
             * @param rayDir
             * @param distance
             * @return
             */
            fgBool rayIntersect(const vector_type& rayOrigin,
                                const vector_type& rayDir,
                                value_type& distance,
                                const fgBool bothSides = FG_FALSE) {
                bool status = math::intersectRayPlane(rayOrigin,
                                                      rayDir,
                                                      n * d,
                                                      n,
                                                      distance);
                if(!status && bothSides) {
                    reverse();
                    status = math::intersectRayPlane(rayOrigin,
                                                     rayDir,
                                                     n * d,
                                                     n,
                                                     distance);
                    reverse();
                }
                return (fgBool)status;
            }
            /**
             *
             * @param a
             * @param b
             * @param v
             * @return
             */
            fgBool getIP(const self_type &a,
                         const self_type &b,
                         vector_type &v) {
                vector_type cp = math::cross(a.n, b.n);
                value_type denom = math::dot(this->n, cp);

                if(math::abs(denom) < (value_type)1e-5) {
                    return FG_FALSE;
                }
                vector_type va = math::cross(a.n, b.n) * - this->d;
                vector_type vb = math::cross(b.n, this->n) * a.d;
                vector_type vc = math::cross(this->n, a.n) * b.d;
                v = (va - vb - vc) / denom;
                return FG_TRUE;
            }
            /**
             * 
             * @param p
             * @return
             */
            fgBool operator ==(const self_type& p) const {
                if(math::isZero(p.d - this->d)) {
                    return math::isZero(math::dot(this->n, p.n) - (value_type)1.0);
                }
                return FG_FALSE;
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

    #undef FG_INC_GFX_PLANE_BLOCK
#endif	/* FG_INC_GFX_PLANE */
