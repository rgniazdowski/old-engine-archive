/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GFX_3D_SCENE
    #define FG_INC_GFX_3D_SCENE
    #define FG_INC_GFX_3D_SCENE_BLOCK

    #include "fgGfxSceneManager.h"
    #include "fgGfxOctree.h"

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
            typedef CScene3D self_type;
            ///
            typedef CScene3D type;
            ///
            typedef fg::gfx::CSceneManager base_type;

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
            CVector<SOctreeNode *> m_octNodes;
        }; // class CScene3D

    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_3D_SCENE_BLOCK
#endif /* FG_INC_GFX_3D_SCENE */
