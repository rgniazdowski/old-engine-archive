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
 * File:   fgGfxAnimationType.h
 * Author: vigilant
 *
 * Created on January 4, 2016, 10:37 PM
 */

#ifndef FG_INC_GFX_ANIMATION_TYPE
    #define FG_INC_GFX_ANIMATION_TYPE
    #define FG_INC_GFX_ANIMATION_TYPE_BLOCK
    
namespace fg {
    namespace gfx {
        namespace anim {

            enum class Type {
                INVALID = 0,
                NODE = 1,
                OBJECT = Type::NODE,
                BONE = 2,
                BONE_RAGDOLL = 3,
                CAMERA = 4,
                COUNT = 5
            };

        } // namespace anim
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_ANIMATION_TYPE_BLOCK
#endif /* FG_INC_GFX_ANIMATION_TYPE */
