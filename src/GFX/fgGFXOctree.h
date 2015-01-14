/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_OCTREE
    #define FG_INC_GFX_OCTREE
    #define FG_INC_GFX_OCTREE_BLOCK

    #include "fgGFXStdInc.h"
    #include "fgGFXSceneNode.h"
    #include "fgVector.h"
    #include "fgBool.h"

namespace fg {
    namespace gfx {

        /**
         *
         */
        struct SOctreeNode {
            ///
            typedef SOctreeNode type;
            ///
            typedef SOctreeNode self_type;
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
            self_type *child[2][2][2];
            /**
             * 
             * @param _parent
             * @param _center
             * @param _depth
             */
            SOctreeNode(self_type *_parent, Vector3f _center, int _depth = 0) :
            center(_center), parent(_parent), depth(_depth) {
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
            parent(_parent), depth(_depth) {
                center.x = _center.x;
                center.y = _center.y;
                center.z = 0.0f;

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
                objects.clear_optimised();
                depth = 0;
                parent = NULL;
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
        class COctree {
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
            
        private:

        };
        
    };
};

    #undef FG_INC_GFX_OCTREE_BLOCK
#endif /* FG_INC_GFX_OCTREE */
