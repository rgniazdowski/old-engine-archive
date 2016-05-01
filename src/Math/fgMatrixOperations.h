/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_MATH_MATRIX_OPERATIONS
    #define FG_INC_MATH_MATRIX_OPERATIONS
    #define FG_INC_MATH_MATRIX_OPERATIONS_BLOCK

    #include "fgMathBase.h"    

    #if defined(FG_USING_GLM)
        #include "glm/common.hpp"
        #include "glm/gtc/matrix_transform.hpp"
        #include "glm/gtc/matrix_inverse.hpp"

        #include "glm/gtx/projection.hpp"
        #include "glm/gtx/intersect.hpp"
        #include "glm/gtx/transform.hpp"

namespace fg {
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

        template <typename T, typename U, precision P>
        GLM_FUNC_QUALIFIER detail::tvec3<T, P> project(detail::tvec3<T, P> const & obj,
                                                       detail::tmat4x4<T, P> const & mvp,
                                                       detail::tvec4<U, P> const & viewport) {
            detail::tvec4<T, P> tmp = detail::tvec4<T, P>(obj, T(1));
            tmp = mvp * tmp;

            tmp /= tmp.w;
            tmp = tmp * T(0.5) + T(0.5);
            tmp[0] = tmp[0] * T(viewport[2]) + T(viewport[0]);
            tmp[1] = tmp[1] * T(viewport[3]) + T(viewport[1]);

            return detail::tvec3<T, P>(tmp);
        }

    } /* namespace math */
} /* namespace fg */

    #endif /* defined(FG_USING_GLM) */


    #undef FG_INC_MATH_MATRIX_OPERATIONS_BLOCK
#endif /* FG_INC_MATH_MATRIX_OPERATIONS */
