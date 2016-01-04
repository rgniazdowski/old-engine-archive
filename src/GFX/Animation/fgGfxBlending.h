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
 * File:   fgGfxBlending.h
 * Author: vigilant
 *
 * Created on September 16, 2015, 6:02 PM
 */

#ifndef FG_INC_GFX_ANIM_BLENDING
    #define FG_INC_GFX_ANIM_BLENDING
    #define FG_INC_GFX_ANIM_BLENDING_BLOCK

    #include "fgGfxAnimation.h"
    #include "fgGfxAnimationInfo.h"    

namespace fg {
    namespace gfx {
        namespace anim {

            struct SBlendingInfo;

            /**
             * 
             * @param anims
             * @param animType
             * @param blendInfo
             * @param pResult
             * @return
             */
            int blendAnimations(const CVector<anim::SAnimationInfo>& anims, 
                                Type animType,
                                const SBlendingInfo& blendInfo,
                                SAnimationFrameInfo* pResult);

        } // namespace anim
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_ANIM_BLENDING_BLOCK
#endif	/* FG_INC_GFX_ANIM_BLENDING */
