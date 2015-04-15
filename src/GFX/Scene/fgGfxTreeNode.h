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
 * File:   fgGFXTreeNode.h
 * Author: vigilant
 *
 * Created on January 16, 2015, 9:40 PM
 */

#ifndef FG_INC_GFX_TREE_NODE
    #define FG_INC_GFX_TREE_NODE
    #define FG_INC_GFX_TREE_NODE_BLOCK

    #include "fgBool.h"
    #include "fgVector.h"
    #include "Math/fgMathLib.h"
    #include "fgGfxTreeNodeObject.h"

namespace fg {
    namespace gfx {

        ///
        typedef unsigned char TreeNodeType;

        const TreeNodeType TREE_NODE_INVALID = 0;
        const TreeNodeType TREE_NODE_QUADTREE = 1;
        const TreeNodeType TREE_NODE_OCTREE = 2;
        const TreeNodeType TREE_NODE_BSP = 3;
        const TreeNodeType TREE_NODE_ABT = 4;
        const TreeNodeType TREE_NODE_DYNAMIC_AABB = 5;
        //const TreeNodeType TREE_NODE_BVH = 6;

        struct STreeNodeBase {
        public:
            ///
            typedef STreeNodeBase type;
            ///
            typedef STreeNodeBase self_type;
            ///
            typedef CVector<CTreeNodeObject *> ObjectsVec;
            ///
            typedef ObjectsVec::iterator ObjectsVecItor;

        protected:
            ///
            TreeNodeType nodeType;
        public:
            ///
            ObjectsVec objects;
            /**
             *
             */
            STreeNodeBase(TreeNodeType _nodeType = TREE_NODE_INVALID) : nodeType(_nodeType), objects() { }
            /**
             *
             */
            virtual ~STreeNodeBase() {
                objects.clear_optimised();
                objects.resize(0);
            }

            /**
             *
             * @param pNode
             * @return
             */
            virtual fgBool removeObject(CTreeNodeObject *pObject);
            /**
             * 
             * @return
             */
            inline TreeNodeType getType(void) const {
                return nodeType;
            }

        protected:
            /**
             *
             * @param _nodeType
             */
            inline void setType(TreeNodeType _nodeType) {
                nodeType = _nodeType;
            }
        };

        /**
         * Standard Node for any kind of 3D/2D spatial tree - GFX subsystem
         * This will be usable for octree/quadtree/bvh
         * For BSP it's more likely not usable
         */
        struct STreeNode : public STreeNodeBase {
            ///
            typedef STreeNode type;
            ///
            typedef STreeNode self_type;
            ///
            typedef STreeNodeBase base_type;

            ///
            Vector3f center;
            ///
            int depth;
            /**
             * 
             */
            STreeNode() : base_type(), center(), depth(0) { }
            /**
             * 
             * @param _parent
             * @param _center
             * @param _depth
             */
            STreeNode(Vector3f _center, int _depth = 0) :
            base_type(), center(_center), depth(_depth) { }
            /**
             * 
             * @param _parent
             * @param _center
             * @param _depth
             */
            STreeNode(Vector2f _center, int _depth = 0) :
            base_type(), center(), depth(_depth) {
                center.x = _center.x;
                center.y = _center.y;
                center.z = 0.0f;
            }
            /**
             * 
             */
            virtual ~STreeNode() { }
        };
    };
};

    #undef FG_INC_GFX_TREE_NODE_BLOCK
#endif	/* FG_INC_GFX_TREE_NODE */
