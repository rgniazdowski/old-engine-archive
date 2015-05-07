/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_QUADTREE
    #define FG_INC_GFX_QUADTREE
    #define FG_INC_GFX_QUADTREE_BLOCK

    #include "GFX/fgGfxStdInc.h"
    #include "fgGfxSceneNode.h"
    #include "fgGfxTreeNode.h"
    #include "fgGfxBasetree.h"

    #include "fgVector.h"

namespace fg {
    namespace gfx {

        /**
         *
         */
        struct SQuadtreeNode : public STreeNode {
            ///
            typedef SQuadtreeNode type;
            ///
            typedef SQuadtreeNode self_type;
            ///
            typedef STreeNode base_type;

            ///
            self_type *parent;
            ///
            self_type *child[2][2];
            /**
             * 
             * @param _parent
             * @param _center
             * @param _depth
             */
            SQuadtreeNode(self_type *_parent, Vector3f _center, int _depth = 0) :
            base_type(_center, _depth), parent(_parent) {
                nodeType = TREE_NODE_QUADTREE;
                for(int i = 0; i < 2; i++) {
                    for(int j = 0; j < 2; j++) {
                        child[i][j] = NULL;
                    } // for(j)
                } // for(i)
            }
            /**
             * 
             * @param _parent
             * @param _center
             * @param _depth
             */
            SQuadtreeNode(self_type *_parent, Vector2f _center, int _depth = 0) :
            base_type(_center, _depth), parent(_parent) {
                nodeType = TREE_NODE_QUADTREE;
                for(int i = 0; i < 2; i++) {
                    for(int j = 0; j < 2; j++) {
                        child[i][j] = NULL;
                    } // for(j)
                } // for(i)
            }
            /**
             * 
             */
            virtual ~SQuadtreeNode() {
                objects.clear_optimised();
                depth = 0;
                parent = NULL;
                nodeType = 0;
                for(int i = 0; i < 2; i++) {
                    for(int j = 0; j < 2; j++) {
                        if(child[i][j]) {
                            delete child[i][j];
                            child[i][j] = NULL;
                        }
                    } // for(j)
                } // for(i)
            }
        };

        /**
         * 
         */
        class CQuadtree : public CBasetree {
        public:
            ///
            static const unsigned int DEFAULT_WORLD_SIZE = 1000;

        protected:

            /**
             *
             */
            struct STraverse : public STraverseBase<SQuadtreeNode> {
                ///
                typedef STraverseBase<SQuadtreeNode> base_type;
                ///
                typedef STraverse type;
                ///
                typedef SQuadtreeNode node_type;
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
                SQuadtreeNode *next(SQuadtreeNode *root) {
                    if(!current) {
                        if(!root)
                            return 0;
                        rewind();
                        current = root;
                        count++;
                        return current;
                    }

                    for(int i = idx; i < 4; i++) {
                        uintptr_t offset = (uintptr_t)(&current->child[0][0]);
                        offset += sizeof (SQuadtreeNode*)*(i);
                        SQuadtreeNode *node = *((SQuadtreeNode**)offset);
                        if(node) {
                            idx = i + 1;
                            nodeStack.push(current);
                            idStack.push(idx);
                            idx = 0;
                            current = node;
                            count++;
                            return node;
                        }
                    }

                    if(idStack.empty()) {
                        current = NULL;
                        return current;
                    }

                    idx = idStack.top();
                    idStack.pop();
                    current = nodeStack.top();
                    nodeStack.pop();

                    if(!current) {
                        return current;
                    }
                    return next(root);
                }
            };

        public:
            /**
             * 
             */
            CQuadtree();
            /**
             * 
             */
            CQuadtree(const CQuadtree& orig);
            /**
             * 
             */
            virtual ~CQuadtree();

        public:
            /**
             * 
             * @return 
             */
            SQuadtreeNode *getRoot(void) const {
                return m_root;
            }

            /**
             * 
             */
            void deleteRoot(void) = 0;

        public:
            /**
             * Insert the given object (sceneNode - logical) into the tree given by treeNode
             * Returns the depth of the node the object was placed in.
             * @param pObject
             * @param pTreeNode
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
            SQuadtreeNode *m_root;
            ///
            STraverse m_traverse;
        };
    };
};

    #undef FG_INC_GFX_QUADTREE_BLOCK
#endif /* FG_INC_GFX_QUADTREE */
