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

namespace fg {

    namespace gfx {
        ///
        typedef unsigned int DrawableType;

        /// Invalid drawable
        const DrawableType DRAWABLE_INVALID = 0x000;
        /// Drawable draw call       
        const DrawableType DRAWABLE_DRAWCALL = 0x0A0;
        /// Drawable scene node
        const DrawableType DRAWABLE_SCENENODE = 0x0A1;
        /// Drawable scene box
        const DrawableType DRAWABLE_SKYBOX = 0x0A2;

        /**
         * 
         */
        class CDrawable {
        public:
            /**
             * 
             */
            CDrawable(const DrawableType drawableType = DRAWABLE_INVALID) :
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
            DrawableType getDrawableType(void) const {
                return m_drawableType;
            }

        protected:
            /**
             * 
             * @param drawableType
             */
            void setDrawableType(const DrawableType drawableType) {
                m_drawableType = drawableType;
            }

        private:
            ///
            DrawableType m_drawableType;
        };
    };
};

    #undef FG_INC_GFX_DRAWABLE_BLOCK
#endif	/* FG_INC_GFX_DRAWABLE */

