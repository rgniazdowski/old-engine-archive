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
 * File:   fgGfxTraits.h
 * Author: vigilant
 *
 * Created on September 18, 2015, 11:07 PM
 */

#ifndef FG_INC_GFX_SCENE_TRAITS
    #define FG_INC_GFX_SCENE_TRAITS
    #define FG_INC_GFX_SCENE_TRAITS_BLOCK

    #include "fgEnumFlags.h"

namespace fg {
    namespace gfx {
        namespace traits {

            enum SceneNode {
                NONE,
                ANIMATED,
                COLLIDABLE,
                DRAWABLE,
                LOGICAL,
                PHYSICAL,
                SPATIAL,
                TRIGGERABLE,
            };

        } // namespace traits
    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_SCENE_TRAITS_BLOCK
#endif	/* FG_INC_GFX_SCENE_TRAITS */
