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
 * File:   fg3DGameWorld.h
 * Author: vigilant
 *
 * Created on September 23, 2015, 8:00 PM
 */

#ifndef FG_INC_GAME_3D_GAMEWORLD
    #define FG_INC_GAME_3D_GAMEWORLD
    #define FG_INC_GAME_3D_GAMEWORLD_BLOCK

    #include "GFX/Scene/fgGfx3DScene.h"
    #include "fgGameWorld.h"

namespace fg {
    namespace game {

        /**
         *
         */
        class CGameWorld3D :
        public CGameWorld,
        public gfx::CScene3D {
        public:
            typedef CGameWorld3D self_type;
            typedef CGameWorld3D type;
            typedef CGameWorld base_type;
            typedef gfx::CScene3D scene_type;

        public:
            /**
             *
             */
            CGameWorld3D();
            /**
             *
             * @param orig
             */
            CGameWorld3D(const CGameWorld3D& orig);
            /**
             * 
             */
            virtual ~CGameWorld3D();

        public:

            virtual fgBool initialize(void);
            virtual fgBool destroy(void);

            virtual void update(float delta = 0.0f);

        private:

        }; // class CGameWorld3D

    } // namespace game
} // namespace fg

    #undef FG_INC_GAME_3D_GAMEWORLD_BLOCK
#endif	/* FG_INC_GAME_3D_GAMEWORLD */
