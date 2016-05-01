/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_MATH_MATRIX_4
    #define FG_INC_MATH_MATRIX_4
    #define FG_INC_MATH_MATRIX_4_BLOCK

    #include "fgMathBase.h"

    #if defined(FG_USING_GLM)

        #include "glm/mat4x4.hpp"

namespace fg {

        #if !defined(FG_MATH_GLM_MATRIX_4_MASK)
            #define FG_MATH_GLM_MATRIX_4_MASK

            #if !defined(FG_MATH_GLM_MATRIX_4_TEMPLATE_MASK)
                #define FG_MATH_GLM_MATRIX_4_TEMPLATE_MASK

                #if 0 // #FIXME - This requires c++11 - alias template/typedef cap

    template<typename T>
    struct Matrix4T {
        typedef glm::detail::tmat4x4<T, glm::defaultp> type;
    };

    template<typename T>
    struct Mat4T {
        typedef glm::detail::tmat4x4<T, glm::defaultp> type;
    };

                #else

    template<typename T>
    using Matrix4T = glm::detail::tmat4x4<T, glm::defaultp>;

    template<typename T>
    using Mat4T = glm::detail::tmat4x4<T, glm::defaultp>;

                #endif /* */
            #endif /* !defined(FG_MATH_MATRIX_4_TEMPLATE_MASK) */

    typedef glm::mat4 Matrix4f;
    typedef glm::dmat4 Matrix4d;

    typedef Matrix4f Mat4f;
    typedef Matrix4d Mat4d;

        #endif /* !defined(FG_MATH_GLM_MATRIX_4_MASK) */

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

    } /* namespace math */
} /* namespace fg */

    #endif /* defined(FG_USING_GLM) */

// Structure definitions when not using GLM (OpenGL Mathematics)
// They're going to match functions and structures from glm namespace.
// Possible use-case? Level of abstraction over DX-* functions.
    #if !defined(FG_USING_GLM)
    #endif /* !defined(FG_USING_GLM) */

    #undef FG_INC_MATH_MATRIX_4_BLOCK
#endif /* FG_INC_MATH_MATRIX_4 */
