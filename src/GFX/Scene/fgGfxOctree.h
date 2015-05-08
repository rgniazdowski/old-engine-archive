/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_OCTREE
    #define FG_INC_GFX_OCTREE
    #define FG_INC_GFX_OCTREE_BLOCK

    #include "GFX/fgGfxStdInc.h"
    #include "fgGfxBasetree.h"
    #include "fgGfxTreeNode.h"

    #include "fgBool.h"
    #include "fgVector.h"

    #include <stack>

namespace fg {
    namespace gfx {

        /**
         * Those quadtree/octree structures need to be made linear #FIXME
         */
        struct SOctreeNode : public STreeNode {
            ///
            typedef SOctreeNode type;
            ///
            typedef SOctreeNode self_type;
            ///
            typedef STreeNode base_type;

            ///
            self_type *parent;
            ///
            self_type *child[2][2][2];
            /**
             * 
             * @param _parent
             * @param _center
             * @param _depth
             */
            SOctreeNode(self_type *_parent, Vector3f _center, int _depth = 0) :
            base_type(_center, _depth), parent(_parent) {
                nodeType = TREE_NODE_OCTREE;
                for(int i = 0; i < 2; i++) {
                    for(int j = 0; j < 2; j++) {
                        for(int k = 0; k < 2; k++) {
                            child[i][j][k] = NULL;
                        } // for(k)
                    } // for(j)
                } // for(i)
            }
            /**
             * 
             * @param _parent
             * @param _center
             * @param _depth
             */
            SOctreeNode(self_type *_parent, Vector2f _center, int _depth = 0) :
            base_type(_center, _depth), parent(_parent) {
                nodeType = TREE_NODE_OCTREE;
                for(int i = 0; i < 2; i++) {
                    for(int j = 0; j < 2; j++) {
                        for(int k = 0; k < 2; k++) {
                            child[i][j][k] = NULL;
                        } // for(k)
                    } // for(j)
                } // for(i)
            }
            /**
             * 
             */
            virtual ~SOctreeNode() {
                depth = 0;
                parent = NULL;
                nodeType = 0;
                for(int i = 0; i < 2; i++) {
                    for(int j = 0; j < 2; j++) {
                        for(int k = 0; k < 2; k++) {
                            if(child[i][j][k]) {
                                delete child[i][j][k];
                                child[i][j][k] = NULL;
                            }
                        } // for(k)
                    } // for(j)
                } // for(i)
            }

        };

        /**
         *
         */
        class COctree : public CBasetree {
        public:
            ///
            static const unsigned int DEFAULT_WORLD_SIZE = 2048;

        protected:

            /**
             *
             */
            struct STraverse : public STraverseBase<SOctreeNode> {
                ///
                typedef STraverseBase<SOctreeNode> base_type;
                ///
                typedef STraverse type;
                ///
                typedef SOctreeNode node_type;
                /**
                 * 
                 */
                STraverse() : base_type() { }
                /**
                 * 
                 */
                virtual ~STraverse() { }
                /**
                 * 
                 * @return 
                 */
                SOctreeNode *next(SOctreeNode *pRoot);
            };

        public:
            /**
             * 
             */
            COctree();
            /**
             * 
             * @param orig
             */
            COctree(const COctree& orig);
            /**
             * 
             */
            virtual ~COctree();

        public:
            /**
             * 
             * @return 
             */
            SOctreeNode *getRoot(void) const {
                return m_root;
            }
            
            /**
             * 
             */
            void deleteRoot(void);

        public:
            /**
             * 
             * @param sceneNode
             * @param treeNode
             * @return 
             */
            virtual int insert(CTreeNodeObject* pObject, STreeNode* pTreeNode = NULL);

        public:
            /**
             *
             */
            STreeNode* next(void);
            /**
             * 
             * @return 
             */
            STreeNode* current(void) const {
                return m_traverse.current;
            }
            /**
             * 
             */
            void rewind(void);
            
            /**
             * 
             */
            void skip(void);

        protected:
            ///
            SOctreeNode *m_root;
            ///
            STraverse m_traverse;

        };

    };
};

    #undef FG_INC_GFX_OCTREE_BLOCK
#endif /* FG_INC_GFX_OCTREE */
