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
 * File:   fgGFXBaseTree.h
 * Author: vigilant
 *
 * Created on January 16, 2015, 10:58 PM
 */

#ifndef FG_INC_GFX_BASE_TREE
    #define FG_INC_GFX_BASE_TREE
    #define FG_INC_GFX_BASE_TREE_BLOCK

    #include "fgGfxTreeNode.h"
    #include "fgBool.h"

    #include <stack>

namespace fg {
    namespace gfx {

        class CSceneNode;

        ///
        typedef unsigned int SpatialTreeType;

        ///
        const SpatialTreeType TREE_INVALID = 0;
        ///
        const SpatialTreeType TREE_QUADTREE = 1;
        ///
        const SpatialTreeType TREE_OCTREE = 2;
        ///
        const SpatialTreeType TREE_LOOSE_QUADTREE = 3;
        ///
        const SpatialTreeType TREE_LOOSE_OCTREE = 4;
        ///
        const SpatialTreeType TREE_BSP = 5;
        ///
        const SpatialTreeType TREE_ABT = 6;
        ///
        const SpatialTreeType TREE_DYNAMIC_AABB = 7;
        //const SpatialTreeType TREE_BVH = 8;

        /**
         * Base class implementation for holding tree structure
         * Used mainly in spatial partitioning (object based)
         * meaning structures like quad/octree, loose variants, BVH trees
         * and other. It is not suitable for BSP tree structures that are
         * used mainly for convex space partitioning (vertices, planes) #FIXME
         */
        class CBasetree {
        public:
            ///
            static const unsigned int DEFAULT_DEPTH = 5;

        protected:

            /**
             *
             */
            template<class TNodeType>
            struct STraverseBase {
                ///
                typedef TNodeType node_type;
                ///
                typedef STraverseBase<TNodeType> base_type;
                ///
                typedef std::stack<int> IdStack;
                ///
                typedef std::stack<TNodeType*> NodeStack;

                /// Stack containing child ids
                IdStack idStack;
                /// Stack for containing nodes
                NodeStack nodeStack;
                /// Current node pointer
                TNodeType *current;
                /// Index of the child to read (0-7)
                int idx;
                /// Number of objects traversed
                int count;
                /**
                 * 
                 */
                STraverseBase() :
                current(NULL),
                idx(0),
                count(0) { }
                /**
                 * 
                 */
                virtual ~STraverseBase() {
                    while(idStack.size()) {
                        idStack.pop();
                    }
                    while(nodeStack.size()) {
                        nodeStack.pop();
                    }
                    current = NULL;
                    idx = 0;
                    count = 0;
                }
                /**
                 * 
                 */
                void rewind(void) {
                    current = NULL;
                    idx = 0;
                    while(idStack.size()) {
                        idStack.pop();
                    }
                    while(nodeStack.size()) {
                        nodeStack.pop();
                    }
                    count = 0;
                }
                /**
                 * 
                 */
                void skip(TNodeType *root) {
                    if(root && !idStack.empty()) {
                        idx = idStack.top();
                        idStack.pop();
                        current = nodeStack.top();
                        nodeStack.pop();
                    }
                }

                /**
                 * 
                 * @return 
                 */
                virtual TNodeType *next(TNodeType *root) = 0;
            };

        public:
            /**
             * 
             */
            CBasetree();
            /**
             * 
             */
            virtual ~CBasetree();

        public:
            /**
             * 
             * @return 
             */
            virtual STreeNode *getRoot(void) const = 0;

            /**
             * 
             */
            virtual void deleteRoot(void) = 0;

            ////////////////////////////////////////////////////////////////////
            /**
             * 
             * @param worldSize
             */
            void setWorldSize(const Vector3f& worldSize) {
                m_worldSize = worldSize;
            }
            /**
             * 
             * @param x
             * @param y
             * @param z
             */
            void setWorldSize(const float x, const float y, const float z) {
                m_worldSize.x = x;
                m_worldSize.y = y;
                m_worldSize.z = z;
            }
            /**
             * 
             * @return 
             */
            Vector3f& getWorldSize(void) {
                return m_worldSize;
            }
            /**
             * 
             * @return 
             */
            Vector3f const& getWorldSize(void) const {
                return m_worldSize;
            }
            /**
             * 
             * @param maxDepth
             */
            void setMaxDepth(const unsigned int maxDepth) {
                m_maxDepth = maxDepth;
            }
            /**
             * 
             * @return 
             */
            unsigned int getMaxDepth(void) const {
                return m_maxDepth;
            }

        public:
            /**
             * 
             * @param sceneNode
             * @param treeNode
             * @param halfExtent
             * @return 
             */
            static fgBool fitsInBox(const CSceneNode* sceneNode,
                                    STreeNode* treeNode,
                                    const float halfExtent);
            /**
             * 
             * @param sceneNode
             * @param center
             * @param halfExtent
             * @return 
             */
            static fgBool fitsInBox(const CSceneNode* sceneNode,
                                    const Vector3f& center,
                                    const float halfExtent);
            /**
             * 
             * @param sceneNode
             * @param center
             * @param halfExtent
             * @return 
             */
            static fgBool fitsInBox(const CSceneNode* sceneNode,
                                    const Vector2f& center,
                                    const float halfExtent);


        public:
            /**
             * 
             * @param sceneNode
             * @param treeNode
             * @return 
             */
            virtual int insert(CTreeNodeObject* pObject, STreeNode* pTreeNode = NULL) = 0;

        public:
            /**
             *
             */
            virtual STreeNode* next(void) = 0;
            /**
             * 
             * @return 
             */
            virtual STreeNode* current(void) const = 0;
            /**
             * 
             */
            virtual void rewind(void) = 0;
            /**
             * 
             */
            virtual void skip(void) = 0;

        private:
            ///
            Vector3f m_worldSize;
            ///
            unsigned int m_maxDepth;
        };

    };
};

    #undef FG_INC_GFX_BASE_TREE_BLOCK
#endif	/* FG_INC_GFX_BASE_TREE */

