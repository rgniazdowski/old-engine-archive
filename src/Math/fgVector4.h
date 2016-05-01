/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_MATH_VECTOR_4
    #define FG_INC_MATH_VECTOR_4
    #define FG_INC_MATH_VECTOR_4_BLOCK

    #include "fgMathBase.h"

    #if defined(FG_USING_GLM)

        #include "glm/vec4.hpp"

namespace fg {

        #if !defined(FG_MATH_GLM_VECTOR_4_MASK)
            #define FG_MATH_GLM_VECTOR_4_MASK

            #if !defined(FG_MATH_GLM_VECTOR_4_TEMPLATE_MASK)
                #define FG_MATH_GLM_VECTOR_4_TEMPLATE_MASK

                #if 0 // #FIXME - This requires c++11

    template<typename T>
    struct Vector4T {
        typedef glm::detail::tvec4<T, glm::defaultp> type;
    };

    template<typename T>
    struct Vec4T {
        typedef glm::detail::tvec4<T, glm::defaultp> type;
    };

                #else

    template<typename T>
    using Vector4T = glm::detail::tvec4<T, glm::defaultp>;

    template<typename T>
    using Vec4T = glm::detail::tvec4<T, glm::defaultp>;

                #endif /* */
            #endif /* !defined(FG_MATH_GLM_VECTOR_4_TEMPLATE_MASK) */

    typedef glm::bvec4 Vector4b;
    typedef glm::bvec4 Vec4b;

    typedef glm::uvec4 Vector4u;
    typedef glm::uvec4 Vec4u;

    typedef glm::ivec4 Vector4i;
    typedef glm::ivec4 Vec4i;

    typedef glm::vec4 Vector4f;
    typedef glm::vec4 Vec4f;
    typedef glm::dvec4 Vector4d;
    typedef glm::dvec4 Vec4d;
        #endif /* !defined(FG_MATH_GLM_VECTOR_4_MASK) */

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
        inline fgBool isZero(detail::tvec4<T, P> const & v, T b = (T)0.00001) {
            return (fgBool)(isZero(v.x, b) && isZero(v.y, b) && isZero(v.z, b) && isZero(v.w, b));
        }
        //----------------------------------------------------------------------
        template <typename T, precision P>
        GLM_FUNC_QUALIFIER T squareLength(detail::tvec4<T, P> const & v) {
            GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'squareLength' only accept floating-point inputs");
            return (v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
        }
        //----------------------------------------------------------------------
        template <typename T, precision P>
        GLM_FUNC_QUALIFIER detail::tvec4<T, P> componentProduct(detail::tvec4<T, P> const & v1, detail::tvec4<T, P> const & v2) {
            return detail::tvec4<T, P>(v1.x * v2.x,
                    v1.y * v2.y,
                    v1.z * v2.z,
                    v1.w * v2.w);
        }

    } /* namespace math */
} /* namespace fg */

    #endif /* defined(FG_USING_GLM) */

// Structure definitions when not using GLM (OpenGL Mathematics)
// They're going to match functions and structures from glm namespace.
// Possible use-case? Level of abstraction over DX-* functions.
    #if !defined(FG_USING_GLM)
    #endif /* !defined(FG_USING_GLM) */

    #undef FG_INC_MATH_VECTOR_4_BLOCK
#endif /* FG_INC_MATH_VECTOR_4 */
