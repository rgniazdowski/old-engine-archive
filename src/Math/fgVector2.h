/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_MATH_VECTOR_2
    #define FG_INC_MATH_VECTOR_2
    #define FG_INC_MATH_VECTOR_2_BLOCK

    #include "fgMathBase.h"

    #if defined(FG_USING_GLM)

        #include "glm/vec2.hpp"

namespace fg {

        #if !defined(FG_MATH_GLM_VECTOR_2_MASK)
            #define FG_MATH_GLM_VECTOR_2_MASK

            #if !defined(FG_MATH_GLM_VECTOR_2_TEMPLATE_MASK)
                #define FG_MATH_GLM_VECTOR_2_TEMPLATE_MASK

                #if 0 // #FIXME - This requires c++11

    template<typename T>
    struct Vector2T {
        typedef glm::detail::tvec2<T, glm::defaultp> type;
    };

    template<typename T>
    struct Vec2T {
        typedef glm::detail::tvec2<T, glm::defaultp> type;
    };

                #else

    template<typename T>
    using Vector2T = glm::detail::tvec2<T, glm::defaultp>;

    template<typename T>
    using Vec2T = glm::detail::tvec2<T, glm::defaultp>;

                #endif /* */
            #endif /* !defined(FG_MATH_GLM_VECTOR_2_TEMPLATE_MASK) */

    typedef glm::bvec2 Vector2b;
    typedef glm::bvec2 Vec2b;

    typedef glm::uvec2 Vector2u;
    typedef glm::uvec2 Vec2u;

    typedef glm::ivec2 Vector2i;
    typedef glm::ivec2 Vec2i;

    typedef glm::vec2 Vector2f;
    typedef glm::vec2 Vec2f;
    typedef glm::dvec2 Vector2d;
    typedef glm::dvec2 Vec2d;
    
        #endif /* !defined(FG_MATH_GLM_VECTOR_2_MASK) */

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
        inline fgBool isZero(detail::tvec2<T, P> const & v, T b = (T)0.00001) {
            return (fgBool)(isZero(v.x, b) && isZero(v.y, b));
        }
        //----------------------------------------------------------------------
        template <typename T, precision P>
        GLM_FUNC_QUALIFIER T squareLength(detail::tvec2<T, P> const & v) {
            GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'squareLength' only accept floating-point inputs");
            return (v.x * v.x + v.y * v.y);
        }
        //----------------------------------------------------------------------
        template <typename T, precision P>
        GLM_FUNC_QUALIFIER detail::tvec2<T, P> componentProduct(detail::tvec2<T, P> const & v1, detail::tvec2<T, P> const & v2) {
            return detail::tvec2<T, P>(v1.x * v2.x,
                    v1.y * v2.y);
        }

    } /* namespace math */
} /* namespace fg */

    #endif /* defined(FG_USING_GLM) */

// Structure definitions when not using GLM (OpenGL Mathematics)
// They're going to match functions and structures from glm namespace.
// Possible use-case? Level of abstraction over DX-* functions.
    #if !defined(FG_USING_GLM)
    #endif /* !defined(FG_USING_GLM) */

    #undef FG_INC_MATH_VECTOR_2_BLOCK
#endif /* FG_INC_MATH_VECTOR_2 */
