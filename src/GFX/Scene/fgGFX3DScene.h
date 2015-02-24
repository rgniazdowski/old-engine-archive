/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_3D_SCENE
    #define FG_INC_GFX_3D_SCENE
    #define FG_INC_GFX_3D_SCENE_BLOCK

    #include "fgGFXSceneManager.h"
    #include "fgGFXOctree.h"

    #include <stack>

namespace fg {

    namespace physics {
        class CWorld;
    };

    namespace gfx {

        /**
         *
         */
        class CScene3D : public CSceneManager {
        public:
            ///
            typedef fg::gfx::CSceneManager base_type;

        private:

        public:
            /**
             * 
             */
            CScene3D();
            /**
             * 
             */
            virtual ~CScene3D();

        public:

            /**
             * 
             */
            virtual void sortCalls(void);

            /**
             * 
             */
            virtual void render(void);

            /**
             * 
             * @param pModelRes
             * @param nameTag
             * @return 
             */
            CSceneNode *addFromModel(CModelResource *pModelRes, const std::string& nameTag);
            /**
             * 
             * @param modelNameTag
             * @param nameTag
             * @return 
             */
            CSceneNode *addFromModel(const std::string& modelNameTag, const std::string& nameTag);
            /**
             * 
             * @param modelNameTag
             * @param nameTag
             * @return 
             */
            CSceneNode *addFromModel(const char *modelNameTag, const char *nameTag);

        public:
            /**
             * 
             * @return 
             */
            COctree* getOctree(void) const {
                return m_octree;
            }
            /**
             * 
             * @return 
             */
            inline physics::CWorld *getPhysicsWorld(void) const {
                return m_physicsWorld;
            }
            /**
             * 
             * @return 
             */
            inline fgBool hasPhysicsWorld(void) const {
                return (fgBool)(m_physicsWorld != NULL);
            }


        protected:
            /**
             * 
             * @param pNode
             */
            void checkCollisions(const CSceneNode* sceneNode);

        private:
            ///
            physics::CWorld *m_physicsWorld;
            ///
            COctree *m_octree;
            ///
            std::stack<SOctreeNode *> m_octNodes;
        };
    };
};

    #undef FG_INC_GFX_3D_SCENE_BLOCK
#endif /* FG_INC_GFX_3D_SCENE */
