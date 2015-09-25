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
    #include "fgBool.h"
    #include "fgTraits.h"

namespace fg {
    namespace gfx {
        class CDrawCall;
        class CDrawingBatch;

        namespace traits {

            /**
             *
             */
            class CDrawable {
            public:
                typedef CDrawable self_type;
                typedef CDrawable type;
            public:
                static const fg::traits::SceneNode SELF_TRAIT = fg::traits::DRAWABLE;
                
            public:
                /**
                 *
                 */
                CDrawable();
                /**
                 *
                 */
                virtual ~CDrawable();

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
                /**
                 *
                 * @return
                 */
                fgBool hasDrawCall(void) const {
                    return (fgBool)(m_drawCall != NULL);
                }
                /**
                 * 
                 * @return
                 */
                CDrawCall* getDrawCall(void) const {
                    return m_drawCall;
                }

            public:
                /**
                 * 
                 * @param a
                 * @return 
                 */
                bool operator ==(const self_type& a) const;
                /**
                 *
                 * @param a
                 * @return
                 */
                bool operator !=(const self_type& a) const;
                /**
                 *
                 * @param a
                 * @return
                 */
                bool operator <(const self_type& a) const;
                /**
                 *
                 * @param a
                 * @return
                 */
                bool operator >(const self_type& a) const;
                /**
                 *
                 * @param a
                 * @return
                 */
                bool operator <=(const self_type& a) const;
                /**
                 *
                 * @param a
                 * @return
                 */
                bool operator >=(const self_type& a) const;

            protected:
                CDrawCall* m_drawCall;

            }; // class CDrawable

        } // namespace traits
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_DRAWABLE_BLOCK
#endif	/* FG_INC_GFX_DRAWABLE */
