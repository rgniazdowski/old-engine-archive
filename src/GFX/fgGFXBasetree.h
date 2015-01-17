/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXBaseTree.h
 * Author: vigilant
 *
 * Created on January 16, 2015, 10:58 PM
 */

#ifndef FG_INC_GFX_BASE_TREE
    #define FG_INC_GFX_BASE_TREE
    #define FG_INC_GFX_BASE_TREE_BLOCK

    #include "fgGFXSceneNode.h"
    #include "fgGFXTreeNode.h"

    #include <stack>

namespace fg {
    namespace gfx {

        /**
         *
         */
        class CBasetree {
        public:
            ///
            const unsigned int DEFAULT_DEPTH = 5;

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

                /// Stack containing child ids
                std::stack<int> id_stack;
                /// Stack for containing nodes
                std::stack<TNodeType*> node_stack;
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
                    while(id_stack.size()) {
                        id_stack.pop();
                    }
                    while(node_stack.size()) {
                        node_stack.pop();
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
                    while(id_stack.size()) {
                        id_stack.pop();
                    }
                    while(node_stack.size()) {
                        node_stack.pop();
                    }
                    count = 0;
                }
                /**
                 * 
                 */
                void skip(TNodeType *root) {
                    if(root && !id_stack.empty()) {
                        idx = id_stack.top();
                        id_stack.pop();
                        current = node_stack.top();
                        node_stack.pop();
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
            virtual int insert(CSceneNode* sceneNode, STreeNode* treeNode = NULL) = 0;

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

