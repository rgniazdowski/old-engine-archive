/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_VECTOR_OPERATIONS
    #define FG_INC_VECTOR_OPERATIONS
    #define FG_INC_VECTOR_OPERATIONS_BLOCK

    #include "fgMathBase.h"

    #if defined(FG_USING_GLM)
        #include "glm/common.hpp"
        #include "glm/geometric.hpp"
        #include "glm/gtx/intersect.hpp"
        #include "glm/gtx/component_wise.hpp"
        #include "glm/gtx/quaternion.hpp"
        #include "glm/gtx/norm.hpp"    

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

    } /* namespace math */
} /* namespace fg */

    #endif /* defined(FG_USING_GLM) */


    #undef FG_INC_VECTOR_OPERATIONS_BLOCK
#endif /* FG_INC_VECTOR_OPERATIONS */
