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
 * File:   fgGameEntityType.h
 * Author: vigilant
 *
 * Created on September 23, 2015, 9:00 PM
 */

#ifndef FG_INC_GAME_ENTITY_TYPE
    #define FG_INC_GAME_ENTITY_TYPE
    #define FG_INC_GAME_ENTITY_TYPE_BLOCK

    #include "GFX/Scene/fgGfxSceneNodeType.h"

namespace fg {
    namespace game {

        typedef gfx::SceneNodeType GameEntityType;

        const GameEntityType GAME_ENTITY_INVALID = gfx::SCENE_NODE_INVALID;

        const GameEntityType GAME_ENTITY = (1 << (gfx::LAST_VALUE_SHIFT_GFX_SCENE_NODE + 1));
        const GameEntityType GAME_ENTITY_MESH = (1 << (gfx::LAST_VALUE_SHIFT_GFX_SCENE_NODE + 2));


        const unsigned int LAST_VALUE_SHIFT_GAME_ENTITY = gfx::LAST_VALUE_SHIFT_GFX_SCENE_NODE + 2;

    } // namespace game
} // namespace fg

    #undef FG_INC_GAME_ENTITY_TYPE_BLOCK
#endif	/* FG_INC_GAME_ENTITY_TYPE */
