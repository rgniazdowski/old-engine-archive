/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
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

typedef unsigned int fgGfxDrawableType;

    #define FG_GFX_DRAWABLE_INVALID     0

namespace fg {

    namespace gfx {

        /**
         * 
         */
        class CDrawable {
        public:
            /**
             * 
             */
            CDrawable(const fgGfxDrawableType drawableType = FG_GFX_DRAWABLE_INVALID) :
            m_drawableType(drawableType) { }
            /**
             * 
             */
            virtual ~CDrawable() { }

        public:
            /**
             * 
             */
            virtual void draw(void) = 0;
            /**
             * Draw with relative 2D position
             * @param relPos
             */
            virtual void draw(const Vec2f& relPos) = 0;
            /**
             * Draw with relative 3D position
             * @param relPos
             */
            virtual void draw(const Vec3f& relPos) = 0;
            /**
             * Draw with given model matrix
             * @param modelMat
             */
            virtual void draw(const Matrix4f& modelMat) = 0;

        public:
            /**
             * 
             * @return 
             */
            fgGfxDrawableType getDrawableType(void) const {
                return m_drawableType;
            }

        protected:
            /**
             * 
             * @param drawableType
             */
            void setDrawableType(const fgGfxDrawableType drawableType) {
                m_drawableType = drawableType;
            }

        private:
            ///
            fgGfxDrawableType m_drawableType;
        };
    };
};

    #undef FG_INC_GFX_DRAWABLE_BLOCK
#endif	/* FG_INC_GFX_DRAWABLE */

