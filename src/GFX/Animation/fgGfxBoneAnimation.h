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
 * File:   fgGfxBoneAnimation.h
 * Author: vigilant
 *
 * Created on September 2, 2015, 5:40 PM
 */

#ifndef FG_INC_GFX_BONE_ANIMATION
    #define FG_INC_GFX_BONE_ANIMATION
    #define FG_INC_GFX_BONE_ANIMATION_BLOCK

    #include "fgGfxAnimation.h"

namespace fg {
    namespace gfx {
        namespace anim {

            class CArmature;

            /**
             * 
             */
            class CBoneAnimation : public CAnimation {
            public:
                typedef CBoneAnimation self_type;
                typedef CBoneAnimation type;
                typedef CAnimation base_type;

            public:
                /**
                 *
                 */
                CBoneAnimation(CArmature* pArmature = NULL);
                /**
                 *
                 * @param orig
                 */
                CBoneAnimation(const CBoneAnimation& orig);
                /**
                 *
                 */
                virtual ~CBoneAnimation();

                /**
                 * 
                 * @param frameInfo
                 * @param elapsed
                 */
                virtual void calculate(SAnimationFrameInfo& frameInfo,
                                       float elapsed = 0.0f);

            public:
                /**
                 *
                 * @param pArmature
                 */
                void setArmature(CArmature* pArmature) {
                    m_pArmature = pArmature;
                }
                /**
                 *
                 * @return
                 */
                CArmature* getArmature(void) {
                    return m_pArmature;
                }
                /**
                 * 
                 * @return
                 */
                CArmature const* getArmature(void) const {
                    return m_pArmature;
                }

            private:
                CArmature* m_pArmature;
                MatricesVec m_intermediate;
            }; // class CBoneAnimation

        } // namespace anim
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_BONE_ANIMATION_BLOCK
#endif	/* FG_INC_GFX_BONE_ANIMATION */