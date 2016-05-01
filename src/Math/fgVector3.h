/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_MATH_VECTOR_3
    #define FG_INC_MATH_VECTOR_3
    #define FG_INC_MATH_VECTOR_3_BLOCK

    #include "fgMathBase.h"

    #if defined(FG_USING_GLM)

        #include "glm/vec3.hpp"

namespace fg {

        #if !defined(FG_MATH_GLM_VECTOR_3_MASK)
            #define FG_MATH_GLM_VECTOR_3_MASK

            #if !defined(FG_MATH_GLM_VECTOR_3_TEMPLATE_MASK)
                #define FG_MATH_GLM_VECTOR_3_TEMPLATE_MASK

                #if 0 // #FIXME - This requires c++11

    template<typename T>
    struct Vector3T {
        typedef glm::detail::tvec3<T, glm::defaultp> type;
    };

    template<typename T>
    struct Vec3T {
        typedef glm::detail::tvec3<T, glm::defaultp> type;
    };

                #else

    template<typename T>
    using Vector3T = glm::detail::tvec3<T, glm::defaultp>;

    template<typename T>
    using Vec3T = glm::detail::tvec3<T, glm::defaultp>;

                #endif /* */
            #endif /* !defined(FG_MATH_GLM_VECTOR_3_TEMPLATE_MASK) */

    typedef glm::bvec3 Vector3b;
    typedef glm::bvec3 Vec3b;

    typedef glm::uvec3 Vector3u;
    typedef glm::uvec3 Vec3u;

    typedef glm::ivec3 Vector3i;
    typedef glm::ivec3 Vec3i;

    typedef glm::vec3 Vector3f;
    typedef glm::vec3 Vec3f;
    typedef glm::dvec3 Vector3d;
    typedef glm::dvec3 Vec3d;
        #endif /* !defined(FG_MATH_GLM_VECTOR_3_MASK) */

    namespace math {
        #ifndef FG_MATH_USING_NAMESPACE_GLM
            #define FG_MATH_USING_NAMESPACE_GLM
        using namespace ::glm;
        #endif /* FG_MATH_USING_NAMESPACE_GLM */
        namespace detail {
        #ifndef FG_MATH_USING_NAMESPACE_GLM_DETAIL
            #define FG_MATH_USING_NAMESPACE_GLM_DETAIL
            using namespace ::glm::detail;
        #endif /* FG_MATH_USING_NAMESPACE_GLM_DETAIL */
        } /* namespace detail */

        //----------------------------------------------------------------------
        template <typename T, precision P>
        inline fgBool isZero(detail::tvec3<T, P> const & v, T b = (T)0.00001) {
            return (fgBool)(isZero(v.x, b) && isZero(v.y, b) && isZero(v.z, b));
        }
        //----------------------------------------------------------------------
        template <typename T, precision P>
        GLM_FUNC_QUALIFIER T squareLength(detail::tvec3<T, P> const & v) {
            GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'squareLength' only accept floating-point inputs");
            return (v.x * v.x + v.y * v.y + v.z * v.z);
        }
        //----------------------------------------------------------------------
        template <typename T, precision P>
        GLM_FUNC_QUALIFIER detail::tvec3<T, P> componentProduct(detail::tvec3<T, P> const & v1, detail::tvec3<T, P> const & v2) {
            return detail::tvec3<T, P>(v1.x * v2.x,
                    v1.y * v2.y,
                    v1.z * v2.z);
        }

    } /* namespace math */
} /* namespace fg */

    #endif /* defined(FG_USING_GLM) */

// Structure definitions when not using GLM (OpenGL Mathematics)
// They're going to match functions and structures from glm namespace.
// Possible use-case? Level of abstraction over DX-* functions.
    #if !defined(FG_USING_GLM)
    #endif /* !defined(FG_USING_GLM) */

    #undef FG_INC_MATH_VECTOR_3_BLOCK
#endif /* FG_INC_MATH_VECTOR_3 */
