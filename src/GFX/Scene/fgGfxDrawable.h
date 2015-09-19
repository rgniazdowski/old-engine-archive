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
 * File:   fgGFXDrawable.h
 * Author: vigilant
 *
 * Created on November 14, 2014, 11:01 AM
 */

#ifndef FG_INC_GFX_DRAWABLE
    #define FG_INC_GFX_DRAWABLE
    #define FG_INC_GFX_DRAWABLE_BLOCK

    #ifndef FG_INC_MATHLIB
        #include "Math/fgMathLib.h"
    #endif

namespace fg {
    namespace gfx {
        namespace traits {

            /**
             *
             */
            class CDrawable {
            public:
                /**
                 *
                 */
                CDrawable() { }
                /**
                 *
                 */
                virtual ~CDrawable() { }

            public:
                /**
                 *
                 */
                void draw(void) {
                    this->draw(Matrix4f());
                }

                /**
                 * Draw with given model matrix
                 * @param modelMat
                 */
                virtual void draw(const Matrix4f& modelMat) = 0;

            }; // class CDrawable

        } // namespace traits
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_DRAWABLE_BLOCK
#endif	/* FG_INC_GFX_DRAWABLE */
