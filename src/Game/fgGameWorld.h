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
 * File:   fgGameWorld.h
 * Author: vigilant
 *
 * Created on September 24, 2015, 4:59 PM
 */

#ifndef FG_INC_GAME_GAME_WORLD
    #define FG_INC_GAME_GAME_WORLD
    #define FG_INC_GAME_GAME_WORLD_BLOCK

    #include "fgIntelligentWorld.h"
    #include "Physics/fgPhysicalWorld.h"
    
namespace fg {
    namespace event {
        class CArgumentList;
        class CFunctionCallback;
    }
    namespace gfx {
        class CSceneManager;
        class CSceneNode;
        class CSceneNodeObject;
        class CSceneNodeMesh;
    }
    namespace game {

        /**
         *
         */
        class CGameWorld :
        public CIntelligentWorld,
        public physics::CPhysicalWorld {
        public:
            typedef CGameWorld self_type;
            typedef CGameWorld type;
            typedef CIntelligentWorld base_type;
            typedef physics::CPhysicalWorld physical_world;
            typedef CIntelligentWorld intelligent_world;

        public:
            /**
             *
             */
            CGameWorld(gfx::CSceneManager* pSceneMgr);
            /**
             *
             * @param orig
             */
            CGameWorld(const CGameWorld& orig);
            /**
             * 
             */
            virtual ~CGameWorld();

        public:

            virtual fgBool initialize(void);
            virtual fgBool destroy(void);
            virtual void update(float delta = 0.0f);

        protected:            
            gfx::CSceneManager* getSceneManager(void) const;


        private:
            ///
            gfx::CSceneManager* m_pSceneMgr;
            ///
            fg::event::CFunctionCallback* m_sceneNodeInsertedCallback;
        }; // class CGameWorld

    } // namespace game
} // namespace fg

    #undef FG_INC_GAME_GAME_WORLD_BLOCK
#endif	/* FG_INC_GAME_GAME_WORLD */
