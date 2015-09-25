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
 * File:   fgGfxSceneNodeType.h
 * Author: vigilant
 *
 * Created on September 23, 2015, 9:02 PM
 */

#ifndef FG_INC_GFX_SCENE_NODE_TYPE
    #define FG_INC_GFX_SCENE_NODE_TYPE
    #define FG_INC_GFX_SCENE_NODE_TYPE_BLOCK

namespace fg {
    namespace gfx {

        ///
        typedef unsigned int SceneNodeType;

        /// Invalid scene node - initial value
        const SceneNodeType SCENE_NODE_INVALID = 0;
        /// This is a special SceneNode type - it's for specifying root nodes
        const SceneNodeType SCENE_NODE_ROOT = (1 << 0);
        /// Node mesh is based on GfxMesh/Shape - Model is made of Shapes
        /// Every shape is made of one mesh. This will be mostly child node.
        const SceneNodeType SCENE_NODE_MESH = (1 << 1);
        /// This is special type of mesh node - based on GfxModel
        /// this will contain multiple children (mesh/shapes) with
        /// configured draw calls and updated bounding boxes
        const SceneNodeType SCENE_NODE_OBJECT = (1 << 2);
        /// Trigger is a special node type - when collision occurs with it
        /// the special event is thrown - registered callbacks will be called
        const SceneNodeType SCENE_NODE_TRIGGER = (1 << 3);
        ///
        const SceneNodeType SCENE_NODE_INTERIOR = (1 << 4);
        ///
        const SceneNodeType SCENE_NODE_LANDSCAPE = (1 << 5);
        ///
        //const SceneNodeType SCENE_NODE_ROOT = (1 << 6);
        /// Particle emitter special node
        const SceneNodeType SCENE_NODE_PARTICLE_EMITTER = (1 << 6);

        const unsigned int LAST_VALUE_SHIFT_GFX_SCENE_NODE = 6;

    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_SCENE_NODE_TYPE_BLOCK
#endif	/* FG_INC_GFX_SCENE_NODE_TYPE */
