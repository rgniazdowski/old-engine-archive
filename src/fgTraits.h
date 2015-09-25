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

    namespace traits {

        /**
         * Contains traits flags for scene node various types.
         * Most likely the final GameObject will contain all of those
         * traits.
         */
        enum SceneNode {
            /// Currently no flags are lit
            NO_NODE_TRAITS = 0,
            /// Node is animated, can have node animations or bone animations
            ANIMATED = (1 << 0),
            /// Node is drawable, it contains draw call data that needs to be
            /// updated
            DRAWABLE = (1 << 1),
            /// Node is intelligent - this refers to artificial intelligence
            /// meaning that this node is controlled automatically and
            /// contains special kind of data.
            INTELLIGENT = (1 << 2),
            /// Node contains special physical properties that update
            /// the model matrix in non trivial way. Also contains special
            /// collision body (more sophisticated than regular AABB or sphere)
            PHYSICAL = (1 << 3),
            /// Node has spatial properties, meaning that it has volume, AABB
            /// and can be put inside of hierarchical spatial tree (BVH,
            /// octree, quadtree, etc.)
            SPATIAL = (1 << 4),
            /// Node can be triggered - it contains callbacks
            TRIGGERABLE = (1 << 5)
        }; // enum SceneNode

        FG_ENUM_FLAGS(SceneNode);

    } // namespace traits
} // namespace fg

    #undef FG_INC_GFX_SCENE_TRAITS_BLOCK
#endif	/* FG_INC_GFX_SCENE_TRAITS */
