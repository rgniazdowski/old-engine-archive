/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written permission from the author.
 *******************************************************/
/* 
 * File:   fgGfxObjectAnimation.h
 * Author: vigilant
 *
 * Created on September 2, 2015, 5:41 PM
 */

#ifndef FG_INC_GFX_OBJECT_ANIMATION
    #define FG_INC_GFX_OBJECT_ANIMATION
    #define FG_INC_GFX_OBJECT_ANIMATION_BLOCK

    #include "fgGfxAnimation.h"
    
namespace fg {
    namespace gfx {
        namespace anim {

            /**
             *
             */
            class CObjectAnimation : public CAnimation {
            public:
                typedef CObjectAnimation self_type;
                typedef CObjectAnimation type;
                typedef CAnimation base_type;

            public:
                /**
                 *
                 */
                CObjectAnimation();
                /**
                 *
                 * @param orig
                 */
                CObjectAnimation(const CObjectAnimation& orig);
                /**
                 *
                 */
                virtual ~CObjectAnimation();

                /**
                 *
                 * @param frameInfo
                 * @param elapsed
                 */
                virtual void calculate(SAnimationFrameInfo& frameInfo,
                                       float elapsed = 0.0f);

            private:

            }; // class CObjectAnimation

        } // namespace anim
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_OBJECT_ANIMATION_BLOCK
#endif	/* FG_INC_GFX_OBJECT_ANIMATION */
