/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_MATH_BASE
    #define FG_INC_MATH_BASE
    #define FG_INC_MATH_BASE_BLOCK

    #include "fgBuildConfig.h"
    #include "fgBool.h"
    #include <cmath>

    #if !defined(FG_RAND)
        #define FG_RAND(_A, _B) (_A + (int)(((float)(_B - _A + 1)) * rand() / (((float)RAND_MAX) + 1.0f)))
    #endif

    #ifndef FG_EPSILON
        #define FG_EPSILON 1e-6f
    #endif

    #ifndef M_PI
        #define M_PI        3.14159265358979323846 /* PI (double) */
    #endif

    #ifndef M_PIF
        #define M_PIF       3.14159265358979323846f /* PI (float) */
    #endif

    #ifndef M_SQRT3F
        #define M_SQRT3F    1.73205080756887729352f /* sqrt(3)(float) */
    #endif

    #ifndef M_SQRT3
        #define M_SQRT3    1.73205080756887729352 /* sqrt(3)(double) */
    #endif

    #ifndef FG_DEG2RAD
        #define FG_DEG2RAD (M_PIF / 180.0f)
    #endif

    #ifndef FG_RAD2DEG
        #define FG_RAD2DEG (180.0f / M_PIF)
    #endif

    #if defined(FG_USING_GLM)
        #include "glm/gtc/epsilon.hpp"
    #endif /* defined(FG_USING_GLM) */

    #if defined(FG_USING_GLM) && 0

namespace fg {
    namespace math {
        using namespace glm;
    } // namespace math
} // namespace fg

    #endif /* defined(FG_USING_GLM) */

namespace fg {

    namespace math {

        //----------------------------------------------------------------------
        inline fgBool isPowOf2(int value) {
            return (fgBool)((value & (value - 1)) == 0);
        }
        //----------------------------------------------------------------------
        inline int toPow2(int value, int sv = 0x1) {
            while(value >>= 1) {
                sv <<= 1;
            }
            return sv;
        }
        //----------------------------------------------------------------------
        template <typename T>
        inline fgBool isZero(T a, T b = (T)0.00001) {
            if(a == (T)0.0) return FG_TRUE;
            return ( a > -b && a < b);
        }

    } /* namespace math */

} /* namespace fg */

    #undef FG_INC_MATH_BASE_BLOCK
#endif /* FG_INC_MATH_BASE */
