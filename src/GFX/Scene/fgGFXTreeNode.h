/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXTreeNode.h
 * Author: vigilant
 *
 * Created on January 16, 2015, 9:40 PM
 */

#ifndef FG_INC_GFX_TREE_NODE
    #define FG_INC_GFX_TREE_NODE
    #define FG_INC_GFX_TREE_NODE_BLOCK

    #include "fgVector.h"
    #include "Math/fgMathLib.h"

namespace fg {
    namespace gfx {

        class CSceneNode;

        /**
         * Standard Node for any kind of 3D/2D spatial tree - GFX subsystem
         * This will be usable for octree/quadtree/bvh
         * For BSP it's more likely not usable
         */
        struct STreeNode {
            //
            typedef CVector<CSceneNode *> ObjectsVec;
            ///
            typedef ObjectsVec::iterator ObjectsVecItor;

            ///
            ObjectsVec objects;
            ///
            Vector3f center;
            ///
            int depth;
            /**
             * 
             */
            STreeNode() : objects(), center(), depth(0) { }
            /**
             * 
             * @param _parent
             * @param _center
             * @param _depth
             */
            STreeNode(Vector3f _center, int _depth = 0) :
            objects(), center(_center), depth(_depth) { }
            /**
             * 
             * @param _parent
             * @param _center
             * @param _depth
             */
            STreeNode(Vector2f _center, int _depth = 0) :
            objects(), center(), depth(_depth) { 
                center.x = _center.x;
                center.y = _center.y;
                center.z = 0.0f;
            }
            /**
             * 
             */
            virtual ~STreeNode() {
                objects.clear_optimised();
                objects.resize(0);
            }
        };
    };
};

    #undef FG_INC_GFX_TREE_NODE_BLOCK
#endif	/* FG_INC_GFX_TREE_NODE */
