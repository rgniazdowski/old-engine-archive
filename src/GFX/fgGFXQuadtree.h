/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_QUADTREE
    #define FG_INC_GFX_QUADTREE
    #define FG_INC_GFX_QUADTREE_BLOCK

    #include "fgGFXStdInc.h"
    #include "fgGFXSceneNode.h"
    #include "fgVector.h"

namespace fg {
    namespace gfx {

        /**
         *
         */
        struct SQuadTNode {
            ///
            typedef SQuadTNode type;
            ///
            typedef SQuadTNode self_type;
            ///
            typedef CVector<CSceneNode *> ObjectsVec;
            ///
            typedef ObjectsVec::iterator ObjectsVecItor;

            ///
            ObjectsVec objects;
            ///
            Vector3f center;
            ///
            self_type *parent;
            ///
            int depth;
            ///
            self_type *child[2][2];
            /**
             * 
             * @param _parent
             * @param _center
             * @param _depth
             */
            SQuadTNode(self_type *_parent, Vector3f _center, int _depth = 0) :
            center(_center), parent(_parent), depth(_depth) {
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
            SQuadTNode(self_type *_parent, Vector2f _center, int _depth = 0) :
            parent(_parent), depth(_depth) {
                center.x = _center.x;
                center.y = _center.y;
                center.z = 0.0f;

                for(int i = 0; i < 2; i++) {
                    for(int j = 0; j < 2; j++) {
                        child[i][j] = NULL;
                    } // for(j)
                } // for(i)
            }
            /**
             * 
             */
            virtual ~SQuadTNode() {
                objects.clear_optimised();
                depth = 0;
                parent = NULL;
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
        class CQuadtree {
        public:
            ///
            const unsigned int DEFAULT_WORLD_SIZE = 1000;
            
        public:
            /**
             * 
             */
            CQuadtree();
            /**
             * 
             */
            virtual ~CQuadtree();

        public:
            /**
             * 
             * @return 
             */
            SQuadTNode *getRoot(void) const {
                return m_root;
            }
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

        public:
            /**
             * 
             * @param sceneNode
             * @param treeNode
             * @param halfExtent
             * @return 
             */
            static fgBool fitsInBox(const CSceneNode* sceneNode,
                                    SQuadTNode* treeNode,
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
            virtual int insert(CSceneNode* sceneNode, SQuadTNode* treeNode = NULL);
            
        protected:
            ///
            SQuadTNode *m_root;
            ///
            Vector3f m_worldSize;
            ///
            unsigned int m_maxDepth;

        private:

        };
    };
};

    #undef FG_INC_GFX_QUADTREE_BLOCK
#endif /* FG_INC_GFX_QUADTREE */
