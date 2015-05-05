/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/*
 * Interface file for core components and functions.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under license. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software license.
 */

/**
 * @mainpage Cyclone Reference
 *
 * Cyclone is a general purpose and robust system for real-time
 * simulation of rigid bodies. The library was designed to be used in
 * computer games, but may be applicable to other areas of simulation
 * or research.
 *
 * @section docs About This Document
 *
 * This documentation contains detailed reference to every aspect of
 * the Cyclone library.
 *
 * @subsection contents Contents
 *
 * Use the navigation system on the left side of the page to view the
 * documentation. The navigation tool uses JavaScript, and requires a
 * version 4 browser or above.
 *
 * All the publically accessible functions and classes of Cyclone
 * are provided in a set of header files. These, and their contents,
 * can be browsed from the File List section.
 *
 * Cyclone is contained in a single namespace, cyclone. Its
 * contents can be viewed in the Compound List section. The Class
 * Hierarchy section provides an alternative way to navigate these
 * classes. The Graphical Class Hierarchy provides an overview of
 * class inheritance.
 *
 * The Compound List section gives an alphabetic list of all symbols
 * in the library, including method names and functions.
 *
 * @subsection graphs Graphs
 *
 * Most of the documentation contains detailed graphical
 * representations of the file and class dependencies. These diagrams
 * are clickable, and provide the fastest mechanism for browsing the
 * documentation. Each diagram is followed by a link to a help file
 * giving a legend.
 *
 * @section use Using Cyclone
 *
 * To set up:
 *
 * @li Create a set of instances of RigidBody.
 *
 * @li Set their mass, inertia tensor, and damping.
 *
 * @li Set their initial location, orientation, velocity and rotation.
 *
 * @li Apply any permanent forces (such as gravity).
 *
 * Then each frame:
 *
 * @li Apply any transient forces (such as springs or thrusts).
 *
 * @li Call eulerIntegrate on each body in turn.
 *
 * @li Fill an array of Contact instances with all contacts on all
 * bodies.
 *
 * @li Call ContactResolver::resolveContacts to resolve the
 * contacts.
 *
 * @li Call calculateInternals to update the bodies' internal
 * properties (such as the transform matrix).
 *
 * @li Render the bodies.
 *
 * @section legal Legal
 *
 * This documentation is distributed under license. Use of this
 * documentation implies agreement with all terms and conditions of
 * the accompanying software and documentation license.
 */

/**
 * @file
 *
 * The core contains utility functions, helpers and a basic set of
 * mathematical types.
 */
#ifndef FG_INC_CYCLONE_CORE_MATH
    #define FG_INC_CYCLONE_CORE_MATH
    #define FG_INC_CYCLONE_CORE_MATH_BLOCK

    #include "fgBuildConfig.h"

    #if defined(FG_DEBUG)
        #include "fgDebugConfig.h"
    #endif
    #include "Math/fgMathLib.h"
    #include "fgPrecision.h"

    #define PHYS_USE_2D_MAPPING_ENABLED 0 // 0 ?

namespace fg {
    namespace physics {

        template <typename T, math::precision P>
        GLM_FUNC_DECL math::detail::tmat4x4<T, P> transform(math::detail::tmat4x4<T, P> const & m1,
                                                            math::detail::tmat4x4<T, P> const & m2);

        template <typename T, math::precision P>
        GLM_FUNC_DECL math::detail::tvec3<T, P> transform(math::detail::tmat4x4<T, P> const & m,
                                                          math::detail::tvec3<T, P> const & v);

        template <typename T, math::precision P>
        GLM_FUNC_DECL math::detail::tvec3<T, P> transformInverse(math::detail::tmat4x4<T, P> const & m,
                                                                 math::detail::tvec3<T, P> const & v);

        template <typename T, math::precision P>
        GLM_FUNC_DECL math::detail::tvec3<T, P> transformDirection(math::detail::tmat4x4<T, P> const & m,
                                                                   math::detail::tvec3<T, P> const & v);

        template <typename T, math::precision P>
        GLM_FUNC_DECL math::detail::tvec3<T, P> transformInverseDirection(math::detail::tmat4x4<T, P> const & m,
                                                                          math::detail::tvec3<T, P> const & v);
        /**
         * 
         * @param m1
         * @param m2
         * @return 
         */
        template <typename T, math::precision P>
        GLM_FUNC_QUALIFIER math::detail::tmat4x4<T, P> transform(math::detail::tmat4x4<T, P> const & m1,
                                                                 math::detail::tmat4x4<T, P> const & m2) {
            math::detail::tmat4x4<T, P> result;
            const float *data = math::value_ptr(m1);
            const float *o_data = math::value_ptr(m1);
            float *result_data = math::value_ptr(result);

            result_data[0] = (o_data[0] * data[0]) + (o_data[4] * data[1]) + (o_data[8] * data[2]);
            result_data[4] = (o_data[0] * data[4]) + (o_data[4] * data[5]) + (o_data[8] * data[6]);
            result_data[8] = (o_data[0] * data[8]) + (o_data[4] * data[9]) + (o_data[8] * data[10]);

            result_data[1] = (o_data[1] * data[0]) + (o_data[5] * data[1]) + (o_data[9] * data[2]);
            result_data[5] = (o_data[1] * data[4]) + (o_data[5] * data[5]) + (o_data[9] * data[6]);
            result_data[9] = (o_data[1] * data[8]) + (o_data[5] * data[9]) + (o_data[9] * data[10]);

            result_data[2] = (o_data[2] * data[0]) + (o_data[6] * data[1]) + (o_data[10] * data[2]);
            result_data[6] = (o_data[2] * data[4]) + (o_data[6] * data[5]) + (o_data[10] * data[6]);
            result_data[10] = (o_data[2] * data[8]) + (o_data[6] * data[9]) + (o_data[10] * data[10]);

            result_data[3] = (o_data[3] * data[0]) + (o_data[7] * data[1]) + (o_data[11] * data[2]) + data[3];
            result_data[7] = (o_data[3] * data[4]) + (o_data[7] * data[5]) + (o_data[11] * data[6]) + data[7];
            result_data[11] = (o_data[3] * data[8]) + (o_data[7] * data[9]) + (o_data[11] * data[10]) + data[11];
            result_data[15] = 1.0f;
            return result;
        }
        /**
         * 
         * @param m
         * @param v
         * @return 
         */
        template <typename T, math::precision P>
        GLM_FUNC_QUALIFIER math::detail::tvec3<T, P> transform(math::detail::tmat3x3<T, P> const & m,
                                                               math::detail::tvec3<T, P> const & v) {

            const float *data = math::value_ptr(m);
            return math::detail::tvec3<T, P>(
                    v.x * data[0] + v.y * data[1] + v.z * data[2],
                    v.x * data[3] + v.y * data[4] + v.z * data[5],
                    v.x * data[6] + v.y * data[7] + v.z * data[8]
                    );
        }
        /**
         * Transform the given vector by this matrix.
         * @param m     Matrix 4x4 to use with transformation
         * @param v     Vector to transform
         * @return      Transformed vector
         */
        template <typename T, math::precision P>
        GLM_FUNC_QUALIFIER math::detail::tvec3<T, P> transform(math::detail::tmat4x4<T, P> const & m,
                                                               math::detail::tvec3<T, P> const & v) {
    #if PHYS_USE_2D_MAPPING_ENABLED
            return math::detail::tvec3<T, P>(
                    v.x * m[0][0] +
                    v.y * m[0][1] +
                    v.z * m[0][2] + m[0][3],

                    v.x * m[1][0] +
                    v.y * m[1][1] +
                    v.z * m[1][2] + m[1][3],

                    v.x * m[2][0] +
                    v.y * m[2][1] +
                    v.z * m[2][2] + m[2][3]
                    );
    #else
            const float *data = math::value_ptr(m);
            return math::detail::tvec3<T, P>(
                    v.x * data[0] +
                    v.y * data[1] +
                    v.z * data[2] + data[3],

                    v.x * data[4] +
                    v.y * data[5] +
                    v.z * data[6] + data[7],

                    v.x * data[8] +
                    v.y * data[9] +
                    v.z * data[10] + data[11]
                    );
    #endif
        }
        template <typename T, math::precision P>
        GLM_FUNC_QUALIFIER math::detail::tvec3<T, P> transformInverse(math::detail::tmat4x4<T, P> const & m,
                                                                      math::detail::tvec3<T, P> const & v) {
    #if PHYS_USE_2D_MAPPING_ENABLED
            math::detail::tvec3<T, P> tmp = v;
            tmp.x -= m[0][3];
            tmp.y -= m[1][3];
            tmp.z -= m[2][3];

            return math::detail::tvec3<T, P>(
                    tmp.x * m[0][0] +
                    tmp.y * m[1][0] +
                    tmp.z * m[2][0],

                    tmp.x * m[0][1] +
                    tmp.y * m[1][1] +
                    tmp.z * m[2][1],

                    tmp.x * m[0][2] +
                    tmp.y * m[1][2] +
                    tmp.z * m[2][2]
                    );
    #else
            const float *data = math::value_ptr(m);
            math::detail::tvec3<T, P> tmp = v;
            tmp.x -= data[3];
            tmp.y -= data[7];
            tmp.z -= data[11];
            return math::detail::tvec3<T, P>(
                    tmp.x * data[0] +
                    tmp.y * data[4] +
                    tmp.z * data[8],

                    tmp.x * data[1] +
                    tmp.y * data[5] +
                    tmp.z * data[9],

                    tmp.x * data[2] +
                    tmp.y * data[6] +
                    tmp.z * data[10]
                    );
    #endif
        }
        template <typename T, math::precision P>
        GLM_FUNC_QUALIFIER math::detail::tvec3<T, P> transformDirection(math::detail::tmat4x4<T, P> const & m,
                                                                        math::detail::tvec3<T, P> const & v) {
    #if PHYS_USE_2D_MAPPING_ENABLED
            return math::detail::tvec3<T, P>(
                    v.x * m[0][0] +
                    v.y * m[0][1] +
                    v.z * m[0][2],

                    v.x * m[1][0] +
                    v.y * m[1][1] +
                    v.z * m[1][2],

                    v.x * m[2][0] +
                    v.y * m[2][1] +
                    v.z * m[2][2]
                    );
    #else
            const float *data = math::value_ptr(m);
            return math::detail::tvec3<T, P>(
                    v.x * data[0] +
                    v.y * data[1] +
                    v.z * data[2],

                    v.x * data[4] +
                    v.y * data[5] +
                    v.z * data[6],

                    v.x * data[8] +
                    v.y * data[9] +
                    v.z * data[10]
                    );
    #endif
        }
        template <typename T, math::precision P>
        GLM_FUNC_QUALIFIER math::detail::tvec3<T, P> transformInverseDirection(math::detail::tmat4x4<T, P> const & m,
                                                                               math::detail::tvec3<T, P> const & v) {
    #if PHYS_USE_2D_MAPPING_ENABLED
            return math::detail::tvec3<T, P>(
                    v.x * m[0][0] +
                    v.y * m[1][0] +
                    v.z * m[2][0],

                    v.x * m[0][1] +
                    v.y * m[1][1] +
                    v.z * m[2][1],

                    v.x * m[0][2] +
                    v.y * m[1][2] +
                    v.z * m[2][2]
                    );
    #else
            const float *data = math::value_ptr(m);
            return math::detail::tvec3<T, P>(
                    v.x * data[0] +
                    v.y * data[4] +
                    v.z * data[8],

                    v.x * data[1] +
                    v.y * data[5] +
                    v.z * data[9],

                    v.x * data[2] +
                    v.y * data[6] +
                    v.z * data[10]
                    );
    #endif
        }
        template <typename T, math::precision P>
        GLM_FUNC_QUALIFIER math::detail::tvec3<T, P> transformTranspose(math::detail::tmat3x3<T, P> const & m,
                                                                        math::detail::tvec3<T, P> const & v) {
    #if PHYS_USE_2D_MAPPING_ENABLED
            return math::detail::tvec3<T, P>(
                    v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0],
                    v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1],
                    v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2]
                    );
    #else
            //return transform(m, v); // ?
            const float *data = math::value_ptr(m);
            return math::detail::tvec3<T, P>(
                    v.x * data[0] + v.y * data[3] + v.z * data[6],
                    v.x * data[1] + v.y * data[4] + v.z * data[7],
                    v.x * data[2] + v.y * data[5] + v.z * data[8]
                    );
    #endif
        }
        template <typename T, math::precision P>
        GLM_FUNC_QUALIFIER math::detail::tmat3x3<T, P> skewSymmetric(math::detail::tvec3<T, P> const & v) {
            math::detail::tmat3x3<T, P> m;
    #if PHYS_USE_2D_MAPPING_ENABLED
            m[0][0] = 0.0f; // 0
            m[0][1] = -v.z; // 1
            m[0][2] = v.y; // 2
            m[1][0] = v.z; // 3
            m[1][1] = 0.0f; // 4            
            m[1][2] = -v.x; // 5
            m[2][0] = -v.y; // 6
            m[2][1] = v.x; // 7            
            m[2][2] = 0.0f; // 8
    #else
            float *data = math::value_ptr(m);
            data[0] = data[4] = data[8] = 0;
            data[1] = -v.z;
            data[2] = v.y;
            data[3] = v.z;
            data[5] = -v.x;
            data[6] = -v.y;
            data[7] = v.x;
    #endif

            return m;
        }
        template <typename T, math::precision P>
        GLM_FUNC_QUALIFIER math::detail::tmat3x3<T, P> linearInterpolate(math::detail::tmat3x3<T, P> const & a,
                                                                         math::detail::tmat3x3<T, P> const & b,
                                                                         T prop) {
            math::detail::tmat3x3<T, P> result;
            for(unsigned int i = 0; i < 3; i++) {
                for(unsigned int j = 0; j < 3; j++) {
                    result[i][j] = a[i][j] * (1.0f - prop) + b[i][j] * prop;
                }
            }
            return result;
        }
#if defined(FG_USING_MARMALADE)
		template <typename T, math::precision P>
#else
        template <typename T, math::precision P = math::precision::defaultp>
#endif
        GLM_FUNC_QUALIFIER math::detail::tmat3x3<T, P> setInertiaTensorCoeffs(T ix, T iy, T iz,
                                                                              T ixy = (T)0.0,
                                                                              T ixz = (T)0.0,
                                                                              T iyz = (T)0.0) {
#if defined(FG_USING_MARMALADE)
			glm::detail::tmat3x3<T, math::precision::defaultp> result;
#else
            glm::detail::tmat3x3<T, P> result;
#endif
    #if PHYS_USE_2D_MAPPING_ENABLED
            result[0][0] = ix; // 0
            result[0][1] = result[1][0] = -ixy; // 1 3
            result[0][2] = result[2][0] = -ixz; // 2 6

            result[1][1] = iy; // 4
            result[1][2] = result[2][1] = -iyz; // 5 7
            result[2][2] = iz; // 8
    #else 



            float *data = math::value_ptr(result);
            data[0] = ix;
            data[1] = data[3] = -ixy;
            data[2] = data[6] = -ixz;
            data[4] = iy;
            data[5] = data[7] = -iyz;
            data[8] = iz;

    #endif

            return result;
        }
        template <typename T, math::precision P>
        GLM_FUNC_QUALIFIER math::detail::tmat3x3<T, P> setBlockInertiaTensor(math::detail::tvec3<T, P> const & halfSizes, T mass) {
            math::detail::tvec3<T, P> squares = math::componentProduct(halfSizes, halfSizes);

            return setInertiaTensorCoeffs<T, P>(0.3f * mass * (squares.y + squares.z),
                    0.3f * mass * (squares.x + squares.z),
                    0.3f * mass * (squares.x + squares.y));
        }
#if defined(FG_USING_MARMALADE)
		template <typename T, math::precision P>
#else
        template <typename T, math::precision P = math::precision::defaultp>
#endif
        GLM_FUNC_QUALIFIER math::detail::tmat3x3<T, P> setDiagonal(T a,
                                                                   T b,
                                                                   T c) {
            
#if defined(FG_USING_MARMALADE)
			return setInertiaTensorCoeffs<T, math::precision::defaultp>(a, b, c);
#else
			return setInertiaTensorCoeffs<T, P>(a, b, c);
#endif
        }
        template <typename T, math::precision P>
        GLM_FUNC_QUALIFIER math::detail::tmat3x3<T, P> setInverse(math::detail::tmat3x3<T, P> const & m) {

            const float *m_data = math::value_ptr(m);
            math::detail::tmat3x3<T, P> result;
            float *result_data = math::value_ptr(result);

            real t4 = m_data[0] * m_data[4];
            real t6 = m_data[0] * m_data[5];
            real t8 = m_data[1] * m_data[3];
            real t10 = m_data[2] * m_data[3];
            real t12 = m_data[1] * m_data[6];
            real t14 = m_data[2] * m_data[6];

            // Calculate the determinant
            real t16 = (t4 * m_data[8] - t6 * m_data[7] - t8 * m_data[8] +
                    t10 * m_data[7] + t12 * m_data[5] - t14 * m_data[4]);

            // Make sure the determinant is non-zero.
            if(t16 == (real)0.0f) return result;
            real t17 = 1 / t16;

            result_data[0] = (m_data[4] * m_data[8] - m_data[5] * m_data[7]) * t17;
            result_data[1] = -(m_data[1] * m_data[8] - m_data[2] * m_data[7]) * t17;
            result_data[2] = (m_data[1] * m_data[5] - m_data[2] * m_data[4]) * t17;
            result_data[3] = -(m_data[3] * m_data[8] - m_data[5] * m_data[6]) * t17;
            result_data[4] = (m_data[0] * m_data[8] - t14) * t17;
            result_data[5] = -(t6 - t10) * t17;
            result_data[6] = (m_data[3] * m_data[7] - m_data[4] * m_data[6]) * t17;
            result_data[7] = -(m_data[0] * m_data[7] - t12) * t17;
            result_data[8] = (t4 - t8) * t17;

            return result;
        }
        template <typename T, math::precision P>
        GLM_FUNC_QUALIFIER math::detail::tmat3x3<T, P> setTranspose(math::detail::tmat3x3<T, P> const & m) {
            const float *m_data = math::value_ptr(m);
            math::detail::tmat3x3<T, P> result;
            float *result_data = math::value_ptr(result);
            result_data[0] = m_data[0];
            result_data[1] = m_data[3];
            result_data[2] = m_data[6];
            result_data[3] = m_data[1];
            result_data[4] = m_data[4];
            result_data[5] = m_data[7];
            result_data[6] = m_data[2];
            result_data[7] = m_data[5];
            result_data[8] = m_data[8];
            return result;
        }
        template <typename T, math::precision P>
        GLM_FUNC_QUALIFIER math::detail::tmat3x3<T, P> setComponents(math::detail::tvec3<T, P> const & v1,
                                                                     math::detail::tvec3<T, P> const & v2,
                                                                     math::detail::tvec3<T, P> const & v3) {
            math::detail::tmat3x3<T, P> result;
            float *result_data = math::value_ptr(result);
            /* result_data[0] = m_data[0];
            result_data[1] = m_data[3];
            result_data[2] = m_data[6];
            result_data[3] = m_data[1];
            result_data[4] = m_data[4];
            result_data[5] = m_data[7];
            result_data[6] = m_data[2];
            result_data[7] = m_data[5];
            result_data[8] = m_data[8]; */

            result_data[0] = v1.x;
            result_data[1] = v2.x;
            result_data[2] = v3.x;
            result_data[3] = v1.y;
            result_data[4] = v2.y;
            result_data[5] = v3.y;
            result_data[6] = v1.z;
            result_data[7] = v2.z;
            result_data[8] = v3.z;

            return result;
        }
        template <typename T, math::precision P>
        GLM_FUNC_QUALIFIER math::detail::tmat3x3<T, P> multiply(math::detail::tmat3x3<T, P> const & m1,
                                                                math::detail::tmat3x3<T, P> const & m2) {
            math::detail::tmat3x3<T, P> result;
            const float *m1_data = math::value_ptr(m1);
            const float *m2_data = math::value_ptr(m2);
            float *result_data = math::value_ptr(result);
            real t1;
            real t2;
            real t3;

            t1 = m1_data[0] * m2_data[0] + m1_data[1] * m2_data[3] + m1_data[2] * m2_data[6];
            t2 = m1_data[0] * m2_data[1] + m1_data[1] * m2_data[4] + m1_data[2] * m2_data[7];
            t3 = m1_data[0] * m2_data[2] + m1_data[1] * m2_data[5] + m1_data[2] * m2_data[8];
            result_data[0] = t1;
            result_data[1] = t2;
            result_data[2] = t3;

            t1 = m1_data[3] * m2_data[0] + m1_data[4] * m2_data[3] + m1_data[5] * m2_data[6];
            t2 = m1_data[3] * m2_data[1] + m1_data[4] * m2_data[4] + m1_data[5] * m2_data[7];
            t3 = m1_data[3] * m2_data[2] + m1_data[4] * m2_data[5] + m1_data[5] * m2_data[8];
            result_data[3] = t1;
            result_data[4] = t2;
            result_data[5] = t3;

            t1 = m1_data[6] * m2_data[0] + m1_data[7] * m2_data[3] + m1_data[8] * m2_data[6];
            t2 = m1_data[6] * m2_data[1] + m1_data[7] * m2_data[4] + m1_data[8] * m2_data[7];
            t3 = m1_data[6] * m2_data[2] + m1_data[7] * m2_data[5] + m1_data[8] * m2_data[8];
            result_data[6] = t1;
            result_data[7] = t2;
            result_data[8] = t3;

            return result;
        }
        template <typename T, math::precision P>
        GLM_FUNC_QUALIFIER math::detail::tquat<T, P> addScaledVector(math::detail::tquat<T, P> & original, math::detail::tvec3<T, P> const& v, T scale) {
            math::detail::tquat<T, P> q((T)0.0,
                                        v.x * scale,
                                        v.y * scale,
                                        v.z * scale);
            q *= original;
            original.w += q.w * ((T)0.5);
            original.x += q.x * ((T)0.5);
            original.y += q.y * ((T)0.5);
            original.z += q.z * ((T)0.5);
            return original;
        }
    }
}

namespace fg {
    
    namespace physics {

        const Vector3f GRAVITY = Vector3f(0, -9.81f, 0);
        const Vector3f HIGH_GRAVITY = Vector3f(0, -19.62f, 0);
        const Vector3f UP = Vector3f(0, 1, 0);
        const Vector3f RIGHT = Vector3f(1, 0, 0);
        const Vector3f OUT_OF_SCREEN = Vector3f(0, 0, 1);
        const Vector3f X = Vector3f(0, 1, 0);
        const Vector3f Y = Vector3f(1, 0, 0);
        const Vector3f Z = Vector3f(0, 0, 1);

        /*const Vector3f GRAVITY;
        const Vector3f HIGH_GRAVITY;
        const Vector3f UP;
        const Vector3f RIGHT;
        const Vector3f OUT_OF_SCREEN;
        const Vector3f X;
        const Vector3f Y;
        const Vector3f Z; */

        /**
         * Holds the value for energy under which a body will be put to
         * sleep. This is a global value for the whole solution.  By
         * default it is 0.1, which is fine for simulation when gravity is
         * about 20 units per second squared, masses are about one, and
         * other forces are around that of gravity. It may need tweaking
         * if your simulation is drastically different to this.
         */
        extern real sleepEpsilon;

        /**
         * Sets the current sleep epsilon value: the kinetic energy under
         * which a body may be put to sleep. Bodies are put to sleep if
         * they appear to have a stable kinetic energy less than this
         * value. For simulations that often have low values (such as slow
         * moving, or light objects), this may need reducing.
         *
         * The value is global; all bodies will use it.
         *
         * @see sleepEpsilon
         *
         * @see getSleepEpsilon
         *
         * @param value The sleep epsilon value to use from this point
         * on.
         */
        void setSleepEpsilon(real value);

        /**
         * Gets the current value of the sleep epsilon parameter.
         *
         * @see sleepEpsilon
         *
         * @see setSleepEpsilon
         *
         * @return The current value of the parameter.
         */
        real getSleepEpsilon(void);

        /**
         * Holds a vector in 3 dimensions. Four data members are allocated
         * to ensure alignment in an array.
         *
         * @note This class contains a lot of inline methods for basic
         * mathematics. The implementations are included in the header
         * file.
         */
    #if 0
        #if !defined(FG_USING_GLM)

        class Vector3 {
        public:
            /** Holds the value along the x axis. */
            real x;

            /** Holds the value along the y axis. */
            real y;

            /** Holds the value along the z axis. */
            real z;

        private:
            /** Padding to ensure 4 word alignment. */
            real pad;

        public:
            /** The default constructor creates a zero vector. */
            Vector3() : x(0), y(0), z(0) { }
            /**
             * The explicit constructor creates a vector with the given
             * components.
             */
            Vector3(const real x, const real y, const real z)
            : x(x), y(y), z(z) { }

            const static Vector3 GRAVITY;
            const static Vector3 HIGH_GRAVITY;
            const static Vector3 UP;
            const static Vector3 RIGHT;
            const static Vector3 OUT_OF_SCREEN;
            const static Vector3 X;
            const static Vector3 Y;
            const static Vector3 Z;

            // ... Other Vector3 code as before ...
            real operator [](unsigned i)const {
                if(i == 0) return x;
                if(i == 1) return y;
                return z;
            }
            real& operator [](unsigned i) {
                if(i == 0) return x;
                if(i == 1) return y;
                return z;
            }
            /** Adds the given vector to this. */
            void operator +=(const Vector3& v) {
                x += v.x;
                y += v.y;
                z += v.z;
            }
            /**
             * Returns the value of the given vector added to this.
             */
            Vector3 operator +(const Vector3& v) const {
                return Vector3(x + v.x, y + v.y, z + v.z);
            }
            /** Subtracts the given vector from this. */
            void operator -=(const Vector3& v) {
                x -= v.x;
                y -= v.y;
                z -= v.z;
            }
            /**
             * Returns the value of the given vector subtracted from this.
             */
            Vector3 operator -(const Vector3& v) const {
                return Vector3(x - v.x, y - v.y, z - v.z);
            }
            /** Multiplies this vector by the given scalar. */
            void operator *=(const real value) {
                x *= value;
                y *= value;
                z *= value;
            }
            /** Returns a copy of this vector scaled the given value. */
            Vector3 operator *(const real value)const {
                return Vector3(x*value, y*value, z * value);
            }
            /**
             * Calculates and returns a component-wise product of this
             * vector with the given vector.
             */
            Vector3 componentProduct(const Vector3 &vector) const {
                return Vector3(x * vector.x, y * vector.y, z * vector.z);
            }
            /**
             * Performs a component-wise product with the given vector and
             * sets this vector to its result.
             */
            void componentProductUpdate(const Vector3 &vector) {
                x *= vector.x;
                y *= vector.y;
                z *= vector.z;
            }
            /**
             * Calculates and returns the vector product of this vector
             * with the given vector.
             */
            Vector3 vectorProduct(const Vector3 &vector) const {
                return Vector3(y * vector.z - z * vector.y,
                               z * vector.x - x * vector.z,
                               x * vector.y - y * vector.x);
            }
            /**
             * Updates this vector to be the vector product of its current
             * value and the given vector.
             */
            void operator %=(const Vector3 &vector) {
                *this = vectorProduct(vector);
            }
            /**
             * Calculates and returns the vector product of this vector
             * with the given vector.
             */
            Vector3 operator %(const Vector3 &vector) const {
                return Vector3(y * vector.z - z * vector.y,
                               z * vector.x - x * vector.z,
                               x * vector.y - y * vector.x);
            }
        }
        /**
         * Calculates and returns the scalar product of this vector
         * with the given vector.
         */
        real scalarProduct(const Vector3 &vector) const {
            return x * vector.x + y * vector.y + z * vector.z;
        }
        /**
         * Calculates and returns the scalar product of this vector
         * with the given vector.
         */
        real operator *(const Vector3 &vector) const {
            return x * vector.x + y * vector.y + z * vector.z;
        }
        /**
         * Adds the given vector to this, scaled by the given amount.
         */
        void addScaledVector(const Vector3& vector, real scale) {
            x += vector.x * scale;
            y += vector.y * scale;
            z += vector.z * scale;
        }
        /** Gets the magnitude of this vector. */
        real magnitude() const {
            return real_sqrt(x * x + y * y + z * z);
        }
        /** Gets the squared magnitude of this vector. */
        real squareMagnitude() const {
            return x * x + y * y + z*z;
        }
        /** Limits the size of the vector to the given maximum. */
        void trim(real size) {
            if(squareMagnitude() > size * size) {
                normalise();
                x *= size;
                y *= size;
                z *= size;
            }
        }
        /** Turns a non-zero vector into a vector of unit length. */
        void normalise() {
            real l = magnitude();
            if(l > 0) {
                (*this) *= ((real)1) / l;
            }
        }
        /** Returns the normalised version of a vector. */
        Vector3 unit() const {
            Vector3 result = *this;
            result.normalise();
            return result;
        }
        /** Checks if the two vectors have identical components. */
        bool operator ==(const Vector3& other) const {
            return x == other.x &&
                    y == other.y &&
                    z == other.z;
        }
        /** Checks if the two vectors have non-identical components. */
        bool operator !=(const Vector3& other) const {
            return !(*this == other);
        }
        /**
         * Checks if this vector is component-by-component less than
         * the other.
         *
         * @note This does not behave like a single-value comparison:
         * !(a < b) does not imply (b >= a).
         */
        bool operator <(const Vector3& other) const {
            return x < other.x && y < other.y && z < other.z;
        }
        /**
         * Checks if this vector is component-by-component less than
         * the other.
         *
         * @note This does not behave like a single-value comparison:
         * !(a < b) does not imply (b >= a).
         */
        bool operator >(const Vector3& other) const {
            return x > other.x && y > other.y && z > other.z;
        }
        /**
         * Checks if this vector is component-by-component less than
         * the other.
         *
         * @note This does not behave like a single-value comparison:
         * !(a <= b) does not imply (b > a).
         */
        bool operator <=(const Vector3& other) const {
            return x <= other.x && y <= other.y && z <= other.z;
        }
        /**
         * Checks if this vector is component-by-component less than
         * the other.
         *
         * @note This does not behave like a single-value comparison:
         * !(a <= b) does not imply (b > a).
         */
        bool operator >=(const Vector3& other) const {
            return x >= other.x && y >= other.y && z >= other.z;
        }
        /** Zero all the components of the vector. */
        void clear() {
            x = y = z = 0;
        }
        /** Flips all the components of the vector. */
        void invert() {
            x = -x;
            y = -y;
            z = -z;
        }

    };
        #endif
    #endif
    /**
     * Holds a three degree of freedom orientation.
     *
     * Quaternions have
     * several mathematical properties that make them useful for
     * representing orientations, but require four items of data to
     * hold the three degrees of freedom. These four items of data can
     * be viewed as the coefficients of a complex number with three
     * imaginary parts. The mathematics of the quaternion is then
     * defined and is roughly correspondent to the math of 3D
     * rotations. A quaternion is only a valid rotation if it is
     * normalised: i.e. it has a length of 1.
     *
     * @note Angular velocity and acceleration can be correctly
     * represented as vectors. Quaternions are only needed for
     * orientation.
     */
    #if 0
        #if !defined(FG_USING_GLM)

    class Quaternion {
    public:

        union {

            struct {
                /**
                 * Holds the real component of the quaternion.
                 */
                real r;

                /**
                 * Holds the first complex component of the
                 * quaternion.
                 */
                real i;

                /**
                 * Holds the second complex component of the
                 * quaternion.
                 */
                real j;

                /**
                 * Holds the third complex component of the
                 * quaternion.
                 */
                real k;
            };

            /**
             * Holds the quaternion data in array form.
             */
            real data[4];
        };

        // ... other Quaternion code as before ...
        /**
         * The default constructor creates a quaternion representing
         * a zero rotation.
         */
        Quaternion() : r(1), i(0), j(0), k(0) { }
        /**
         * The explicit constructor creates a quaternion with the given
         * components.
         *
         * @param r The real component of the rigid body's orientation
         * quaternion.
         *
         * @param i The first complex component of the rigid body's
         * orientation quaternion.
         *
         * @param j The second complex component of the rigid body's
         * orientation quaternion.
         *
         * @param k The third complex component of the rigid body's
         * orientation quaternion.
         *
         * @note The given orientation does not need to be normalised,
         * and can be zero. This function will not alter the given
         * values, or normalise the quaternion. To normalise the
         * quaternion (and make a zero quaternion a legal rotation),
         * use the normalise function.
         *
         * @see normalise
         */
        Quaternion(const real r, const real i, const real j, const real k)
        : r(r), i(i), j(j), k(k) { }
        /**
         * Normalises the quaternion to unit length, making it a valid
         * orientation quaternion.
         */
        void normalise() {
            real d = r * r + i * i + j * j + k*k;

            // Check for zero length quaternion, and use the no-rotation
            // quaternion in that case.
            if(d < real_epsilon) {
                r = 1;
                return;
            }

            d = ((real)1.0) / real_sqrt(d);
            r *= d;
            i *= d;
            j *= d;
            k *= d;
        }
        /**
         * Multiplies the quaternion by the given quaternion.
         *
         * @param multiplier The quaternion by which to multiply.
         */
        void operator *=(const Quaternion &multiplier) {
            Quaternion q = *this;
            r = q.r * multiplier.r - q.i * multiplier.i -
                    q.j * multiplier.j - q.k * multiplier.k;
            i = q.r * multiplier.i + q.i * multiplier.r +
                    q.j * multiplier.k - q.k * multiplier.j;
            j = q.r * multiplier.j + q.j * multiplier.r +
                    q.k * multiplier.i - q.i * multiplier.k;
            k = q.r * multiplier.k + q.k * multiplier.r +
                    q.i * multiplier.j - q.j * multiplier.i;
        }
        /**
         * Adds the given vector to this, scaled by the given amount.
         * This is used to update the orientation quaternion by a rotation
         * and time.
         *
         * @param vector The vector to add.
         *
         * @param scale The amount of the vector to add.
         */
        void addScaledVector(const Vector3& vector, real scale) {
            Quaternion q(0,
                         vector.x * scale,
                         vector.y * scale,
                         vector.z * scale);
            q *= *this;
            r += q.r * ((real)0.5);
            i += q.i * ((real)0.5);
            j += q.j * ((real)0.5);
            k += q.k * ((real)0.5);
        }
        void rotateByVector(const Vector3& vector) {
            Quaternion q(0, vector.x, vector.y, vector.z);
            (*this) *= q;
        }
    };
        #endif
    #endif
    /**
     * Holds a transform matrix, consisting of a rotation matrix and
     * a position. The matrix has 12 elements, it is assumed that the
     * remaining four are (0,0,0,1); producing a homogenous matrix.
     */
    #if 0
        #if !defined(FG_USING_GLM)

    class Matrix4 {
    public:
        /**
         * Holds the transform matrix data in array form.
         */
        real data[12];

        // ... Other Matrix4 code as before ...
        /**
         * Creates an identity matrix.
         */
        Matrix4() {
            data[1] = data[2] = data[3] = data[4] = data[6] =
                    data[7] = data[8] = data[9] = data[11] = 0;
            data[0] = data[5] = data[10] = 1;
        }
        /**
         * Sets the matrix to be a diagonal matrix with the given coefficients.
         */
        void setDiagonal(real a, real b, real c) {
            data[0] = a;
            data[5] = b;
            data[10] = c;
        }
        /**
         * Returns a matrix which is this matrix multiplied by the given
         * other matrix.
         */
        Matrix4 operator *(const Matrix4 &o) const {
            Matrix4 result;
            result.data[0] = (o.data[0] * data[0]) + (o.data[4] * data[1]) + (o.data[8] * data[2]);
            result.data[4] = (o.data[0] * data[4]) + (o.data[4] * data[5]) + (o.data[8] * data[6]);
            result.data[8] = (o.data[0] * data[8]) + (o.data[4] * data[9]) + (o.data[8] * data[10]);

            result.data[1] = (o.data[1] * data[0]) + (o.data[5] * data[1]) + (o.data[9] * data[2]);
            result.data[5] = (o.data[1] * data[4]) + (o.data[5] * data[5]) + (o.data[9] * data[6]);
            result.data[9] = (o.data[1] * data[8]) + (o.data[5] * data[9]) + (o.data[9] * data[10]);

            result.data[2] = (o.data[2] * data[0]) + (o.data[6] * data[1]) + (o.data[10] * data[2]);
            result.data[6] = (o.data[2] * data[4]) + (o.data[6] * data[5]) + (o.data[10] * data[6]);
            result.data[10] = (o.data[2] * data[8]) + (o.data[6] * data[9]) + (o.data[10] * data[10]);

            result.data[3] = (o.data[3] * data[0]) + (o.data[7] * data[1]) + (o.data[11] * data[2]) + data[3];
            result.data[7] = (o.data[3] * data[4]) + (o.data[7] * data[5]) + (o.data[11] * data[6]) + data[7];
            result.data[11] = (o.data[3] * data[8]) + (o.data[7] * data[9]) + (o.data[11] * data[10]) + data[11];

            return result;
        }
        /**
         * Transform the given vector by this matrix.
         *
         * @param vector The vector to transform.
         */
        Vector3 operator *(const Vector3 &vector) const {
            return Vector3(
                           vector.x * data[0] +
                           vector.y * data[1] +
                           vector.z * data[2] + data[3],

                           vector.x * data[4] +
                           vector.y * data[5] +
                           vector.z * data[6] + data[7],

                           vector.x * data[8] +
                           vector.y * data[9] +
                           vector.z * data[10] + data[11]
                           );
        }
        /**
         * Transform the given vector by this matrix.
         *
         * @param vector The vector to transform.
         */
        Vector3 transform(const Vector3 &vector) const {
            return (*this) * vector;
        }

        /**
         * Returns the determinant of the matrix.
         */
        real getDeterminant() const;

        /**
         * Sets the matrix to be the inverse of the given matrix.
         *
         * @param m The matrix to invert and use to set this.
         */
        void setInverse(const Matrix4 &m);
        /** Returns a new matrix containing the inverse of this matrix. */
        Matrix4 inverse() const {
            Matrix4 result;
            result.setInverse(*this);
            return result;
        }
        /**
         * Inverts the matrix.
         */
        void invert() {
            setInverse(*this);
        }
        /**
         * Transform the given direction vector by this matrix.
         *
         * @note When a direction is converted between frames of
         * reference, there is no translation required.
         *
         * @param vector The vector to transform.
         */
        Vector3 transformDirection(const Vector3 &vector) const {
            return Vector3(
                           vector.x * data[0] +
                           vector.y * data[1] +
                           vector.z * data[2],

                           vector.x * data[4] +
                           vector.y * data[5] +
                           vector.z * data[6],

                           vector.x * data[8] +
                           vector.y * data[9] +
                           vector.z * data[10]
                           );
        }
        /**
         * Transform the given direction vector by the
         * transformational inverse of this matrix.
         *
         * @note This function relies on the fact that the inverse of
         * a pure rotation matrix is its transpose. It separates the
         * translational and rotation components, transposes the
         * rotation, and multiplies out. If the matrix is not a
         * scale and shear free transform matrix, then this function
         * will not give correct results.
         *
         * @note When a direction is converted between frames of
         * reference, there is no translation required.
         *
         * @param vector The vector to transform.
         */
        Vector3 transformInverseDirection(const Vector3 &vector) const {
            return Vector3(
                           vector.x * data[0] +
                           vector.y * data[4] +
                           vector.z * data[8],

                           vector.x * data[1] +
                           vector.y * data[5] +
                           vector.z * data[9],

                           vector.x * data[2] +
                           vector.y * data[6] +
                           vector.z * data[10]
                           );
        }
        /**
         * Transform the given vector by the transformational inverse
         * of this matrix.
         *
         * @note This function relies on the fact that the inverse of
         * a pure rotation matrix is its transpose. It separates the
         * translational and rotation components, transposes the
         * rotation, and multiplies out. If the matrix is not a
         * scale and shear free transform matrix, then this function
         * will not give correct results.
         *
         * @param vector The vector to transform.
         */
        Vector3 transformInverse(const Vector3 &vector) const {
            Vector3 tmp = vector;
            tmp.x -= data[3];
            tmp.y -= data[7];
            tmp.z -= data[11];
            return Vector3(
                           tmp.x * data[0] +
                           tmp.y * data[4] +
                           tmp.z * data[8],

                           tmp.x * data[1] +
                           tmp.y * data[5] +
                           tmp.z * data[9],

                           tmp.x * data[2] +
                           tmp.y * data[6] +
                           tmp.z * data[10]
                           );
        }
        /**
         * Gets a vector representing one axis (i.e. one column) in the matrix.
         *
         * @param i The row to return. Row 3 corresponds to the position
         * of the transform matrix.
         *
         * @return The vector.
         */
        Vector3 getAxisVector(int i) const {
            return Vector3(data[i], data[i + 4], data[i + 8]);
        }
        /**
         * Sets this matrix to be the rotation matrix corresponding to
         * the given quaternion.
         */
        void setOrientationAndPos(const Quaternion &q, const Vector3 &pos) {
            data[0] = 1 - (2 * q.j * q.j + 2 * q.k * q.k);
            data[1] = 2 * q.i * q.j + 2 * q.k * q.r;
            data[2] = 2 * q.i * q.k - 2 * q.j * q.r;
            data[3] = pos.x;

            data[4] = 2 * q.i * q.j - 2 * q.k * q.r;
            data[5] = 1 - (2 * q.i * q.i + 2 * q.k * q.k);
            data[6] = 2 * q.j * q.k + 2 * q.i * q.r;
            data[7] = pos.y;

            data[8] = 2 * q.i * q.k + 2 * q.j * q.r;
            data[9] = 2 * q.j * q.k - 2 * q.i * q.r;
            data[10] = 1 - (2 * q.i * q.i + 2 * q.j * q.j);
            data[11] = pos.z;
        }
        /**
         * Fills the given array with this transform matrix, so it is
         * usable as an open-gl transform matrix. OpenGL uses a column
         * major format, so that the values are transposed as they are
         * written.
         */
        void fillGLArray(float array[16]) const {
            array[0] = (float)data[0];
            array[1] = (float)data[4];
            array[2] = (float)data[8];
            array[3] = (float)0;

            array[4] = (float)data[1];
            array[5] = (float)data[5];
            array[6] = (float)data[9];
            array[7] = (float)0;

            array[8] = (float)data[2];
            array[9] = (float)data[6];
            array[10] = (float)data[10];
            array[11] = (float)0;

            array[12] = (float)data[3];
            array[13] = (float)data[7];
            array[14] = (float)data[11];
            array[15] = (float)1;
        }
    };
        #endif
    #endif
    /**
     * Holds an inertia tensor, consisting of a 3x3 row-major matrix.
     * This matrix is not padding to produce an aligned structure, since
     * it is most commonly used with a mass (single real) and two
     * damping coefficients to make the 12-element characteristics array
     * of a rigid body.
     */
    #if 0
        #if !defined(FG_USING_GLM)

    class Matrix3 {
    public:
        /**
         * Holds the tensor matrix data in array form.
         */
        real data[9];

        // ... Other Matrix3 code as before ...
        /**
         * Creates a new matrix.
         */
        Matrix3() {
            data[0] = data[1] = data[2] = data[3] = data[4] = data[5] =
                    data[6] = data[7] = data[8] = 0;
        }
        /**
         * Creates a new matrix with the given three vectors making
         * up its columns.
         */
        Matrix3(const Vector3 &compOne, const Vector3 &compTwo,
                const Vector3 &compThree) {
            setComponents(compOne, compTwo, compThree);
        }
        /**
         * Creates a new matrix with explicit coefficients.
         */
        Matrix3(real c0, real c1, real c2, real c3, real c4, real c5,
                real c6, real c7, real c8) {
            data[0] = c0;
            data[1] = c1;
            data[2] = c2;
            data[3] = c3;
            data[4] = c4;
            data[5] = c5;
            data[6] = c6;
            data[7] = c7;
            data[8] = c8;
        }
        /**
         * Sets the matrix to be a diagonal matrix with the given
         * values along the leading diagonal.
         */
        void setDiagonal(real a, real b, real c) {
            setInertiaTensorCoeffs(a, b, c);
        }
        /**
         * Sets the value of the matrix from inertia tensor values.
         */
        void setInertiaTensorCoeffs(real ix, real iy, real iz,
                                    real ixy = 0, real ixz = 0, real iyz = 0) {
            data[0] = ix;
            data[1] = data[3] = -ixy;
            data[2] = data[6] = -ixz;
            data[4] = iy;
            data[5] = data[7] = -iyz;
            data[8] = iz;
        }
        /**
         * Sets the value of the matrix as an inertia tensor of
         * a rectangular block aligned with the body's coordinate
         * system with the given axis half-sizes and mass.
         */
        void setBlockInertiaTensor(const Vector3 &halfSizes, real mass) {
            Vector3 squares = halfSizes.componentProduct(halfSizes);
            setInertiaTensorCoeffs(0.3f * mass * (squares.y + squares.z),
                                   0.3f * mass * (squares.x + squares.z),
                                   0.3f * mass * (squares.x + squares.y));
        }
        /**
         * Sets the matrix to be a skew symmetric matrix based on
         * the given vector. The skew symmetric matrix is the equivalent
         * of the vector product. So if a,b are vectors. a x b = A_s b
         * where A_s is the skew symmetric form of a.
         */
        void setSkewSymmetric(const Vector3 vector) {
            data[0] = data[4] = data[8] = 0;
            data[1] = -vector.z;
            data[2] = vector.y;
            data[3] = vector.z;
            data[5] = -vector.x;
            data[6] = -vector.y;
            data[7] = vector.x;
        }
        /**
         * Sets the matrix values from the given three vector components.
         * These are arranged as the three columns of the vector.
         */
        void setComponents(const Vector3 &compOne, const Vector3 &compTwo,
                           const Vector3 &compThree) {
            data[0] = compOne.x;
            data[1] = compTwo.x;
            data[2] = compThree.x;
            data[3] = compOne.y;
            data[4] = compTwo.y;
            data[5] = compThree.y;
            data[6] = compOne.z;
            data[7] = compTwo.z;
            data[8] = compThree.z;

        }
        /**
         * Transform the given vector by this matrix.
         *
         * @param vector The vector to transform.
         */
        Vector3 operator *(const Vector3 &vector) const {
            return Vector3(
                           vector.x * data[0] + vector.y * data[1] + vector.z * data[2],
                           vector.x * data[3] + vector.y * data[4] + vector.z * data[5],
                           vector.x * data[6] + vector.y * data[7] + vector.z * data[8]
                           );
        }
        /**
         * Transform the given vector by this matrix.
         *
         * @param vector The vector to transform.
         */
        Vector3 transform(const Vector3 &vector) const {
            return (*this) * vector;
        }
        /**
         * Transform the given vector by the transpose of this matrix.
         *
         * @param vector The vector to transform.
         */
        Vector3 transformTranspose(const Vector3 &vector) const {
            return Vector3(
                           vector.x * data[0] + vector.y * data[3] + vector.z * data[6],
                           vector.x * data[1] + vector.y * data[4] + vector.z * data[7],
                           vector.x * data[2] + vector.y * data[5] + vector.z * data[8]
                           );
        }
        /**
         * Gets a vector representing one row in the matrix.
         *
         * @param i The row to return.
         */
        Vector3 getRowVector(int i) const {
            return Vector3(data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
        }
        /**
         * Gets a vector representing one axis (i.e. one column) in the matrix.
         *
         * @param i The row to return.
         *
         * @return The vector.
         */
        Vector3 getAxisVector(int i) const {
            return Vector3(data[i], data[i + 3], data[i + 6]);
        }
        /**
         * Sets the matrix to be the inverse of the given matrix.
         *
         * @param m The matrix to invert and use to set this.
         */
        void setInverse(const Matrix3 &m) {
            real t4 = m.data[0] * m.data[4];
            real t6 = m.data[0] * m.data[5];
            real t8 = m.data[1] * m.data[3];
            real t10 = m.data[2] * m.data[3];
            real t12 = m.data[1] * m.data[6];
            real t14 = m.data[2] * m.data[6];

            // Calculate the determinant
            real t16 = (t4 * m.data[8] - t6 * m.data[7] - t8 * m.data[8] +
                    t10 * m.data[7] + t12 * m.data[5] - t14 * m.data[4]);

            // Make sure the determinant is non-zero.
            if(t16 == (real)0.0f) return;
            real t17 = 1 / t16;

            data[0] = (m.data[4] * m.data[8] - m.data[5] * m.data[7]) * t17;
            data[1] = -(m.data[1] * m.data[8] - m.data[2] * m.data[7]) * t17;
            data[2] = (m.data[1] * m.data[5] - m.data[2] * m.data[4]) * t17;
            data[3] = -(m.data[3] * m.data[8] - m.data[5] * m.data[6]) * t17;
            data[4] = (m.data[0] * m.data[8] - t14) * t17;
            data[5] = -(t6 - t10) * t17;
            data[6] = (m.data[3] * m.data[7] - m.data[4] * m.data[6]) * t17;
            data[7] = -(m.data[0] * m.data[7] - t12) * t17;
            data[8] = (t4 - t8) * t17;
        }
        /** Returns a new matrix containing the inverse of this matrix. */
        Matrix3 inverse() const {
            Matrix3 result;
            result.setInverse(*this);
            return result;
        }
        /**
         * Inverts the matrix.
         */
        void invert() {
            setInverse(*this);
        }
        /**
         * Sets the matrix to be the transpose of the given matrix.
         *
         * @param m The matrix to transpose and use to set this.
         */
        void setTranspose(const Matrix3 &m) {
            data[0] = m.data[0];
            data[1] = m.data[3];
            data[2] = m.data[6];
            data[3] = m.data[1];
            data[4] = m.data[4];
            data[5] = m.data[7];
            data[6] = m.data[2];
            data[7] = m.data[5];
            data[8] = m.data[8];
        }
        /** Returns a new matrix containing the transpose of this matrix. */
        Matrix3 transpose() const {
            Matrix3 result;
            result.setTranspose(*this);
            return result;
        }
        /**
         * Returns a matrix which is this matrix multiplied by the given
         * other matrix.
         */
        Matrix3 operator *(const Matrix3 &o) const {
            return Matrix3(
                           data[0] * o.data[0] + data[1] * o.data[3] + data[2] * o.data[6],
                           data[0] * o.data[1] + data[1] * o.data[4] + data[2] * o.data[7],
                           data[0] * o.data[2] + data[1] * o.data[5] + data[2] * o.data[8],

                           data[3] * o.data[0] + data[4] * o.data[3] + data[5] * o.data[6],
                           data[3] * o.data[1] + data[4] * o.data[4] + data[5] * o.data[7],
                           data[3] * o.data[2] + data[4] * o.data[5] + data[5] * o.data[8],

                           data[6] * o.data[0] + data[7] * o.data[3] + data[8] * o.data[6],
                           data[6] * o.data[1] + data[7] * o.data[4] + data[8] * o.data[7],
                           data[6] * o.data[2] + data[7] * o.data[5] + data[8] * o.data[8]
                           );
        }
        /**
         * Multiplies this matrix in place by the given other matrix.
         */
        void operator *=(const Matrix3 &o) {
            real t1;
            real t2;
            real t3;

            t1 = data[0] * o.data[0] + data[1] * o.data[3] + data[2] * o.data[6];
            t2 = data[0] * o.data[1] + data[1] * o.data[4] + data[2] * o.data[7];
            t3 = data[0] * o.data[2] + data[1] * o.data[5] + data[2] * o.data[8];
            data[0] = t1;
            data[1] = t2;
            data[2] = t3;

            t1 = data[3] * o.data[0] + data[4] * o.data[3] + data[5] * o.data[6];
            t2 = data[3] * o.data[1] + data[4] * o.data[4] + data[5] * o.data[7];
            t3 = data[3] * o.data[2] + data[4] * o.data[5] + data[5] * o.data[8];
            data[3] = t1;
            data[4] = t2;
            data[5] = t3;

            t1 = data[6] * o.data[0] + data[7] * o.data[3] + data[8] * o.data[6];
            t2 = data[6] * o.data[1] + data[7] * o.data[4] + data[8] * o.data[7];
            t3 = data[6] * o.data[2] + data[7] * o.data[5] + data[8] * o.data[8];
            data[6] = t1;
            data[7] = t2;
            data[8] = t3;
        }
        /**
         * Multiplies this matrix in place by the given scalar.
         */
        void operator *=(const real scalar) {
            data[0] *= scalar;
            data[1] *= scalar;
            data[2] *= scalar;
            data[3] *= scalar;
            data[4] *= scalar;
            data[5] *= scalar;
            data[6] *= scalar;
            data[7] *= scalar;
            data[8] *= scalar;
        }
        /**
         * Does a component-wise addition of this matrix and the given
         * matrix.
         */
        void operator +=(const Matrix3 &o) {
            data[0] += o.data[0];
            data[1] += o.data[1];
            data[2] += o.data[2];
            data[3] += o.data[3];
            data[4] += o.data[4];
            data[5] += o.data[5];
            data[6] += o.data[6];
            data[7] += o.data[7];
            data[8] += o.data[8];
        }
        /**
         * Sets this matrix to be the rotation matrix corresponding to
         * the given quaternion.
         */
        void setOrientation(const Quaternion &q) {
            data[0] = 1 - (2 * q.j * q.j + 2 * q.k * q.k);
            data[1] = 2 * q.i * q.j + 2 * q.k * q.r;
            data[2] = 2 * q.i * q.k - 2 * q.j * q.r;
            data[3] = 2 * q.i * q.j - 2 * q.k * q.r;
            data[4] = 1 - (2 * q.i * q.i + 2 * q.k * q.k);
            data[5] = 2 * q.j * q.k + 2 * q.i * q.r;
            data[6] = 2 * q.i * q.k + 2 * q.j * q.r;
            data[7] = 2 * q.j * q.k - 2 * q.i * q.r;
            data[8] = 1 - (2 * q.i * q.i + 2 * q.j * q.j);
        }

        /**
         * Interpolates a couple of matrices.
         */
        static Matrix3 linearInterpolate(const Matrix3& a, const Matrix3& b, real prop);
    };
        #endif
    #endif
} // namespace physics
} // namespace fg

    #undef FG_INC_CYCLONE_CORE_MATH_BLOCK
#endif /* FG_INC_CYCLONE_CORE_MATH */
