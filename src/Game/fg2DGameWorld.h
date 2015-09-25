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
 * File:   fg2DGameWorld.h
 * Author: vigilant
 *
 * Created on September 23, 2015, 8:00 PM
 */

#ifndef FG_INC_GAME_2D_GAMEWORLD
    #define FG_INC_GAME_2D_GAMEWORLD
    #define FG_INC_GAME_2D_GAMEWORLD_BLOCK

    #include "GFX/Scene/fgGfx2DScene.h"
    #include "fgGameWorld.h"

namespace fg {
    namespace game {

        /**
         *
         */
        class CGameWorld2D :
        public CGameWorld,
        public gfx::CScene2D {
        public:
            typedef CGameWorld2D self_type;
            typedef CGameWorld2D type;
            typedef CGameWorld base_type;
            typedef gfx::CScene2D scene_type;

        public:
            /**
             *
             */
            CGameWorld2D();
            /**
             *
             * @param orig
             */
            CGameWorld2D(const CGameWorld2D& orig);
            /**
             *
             */
            virtual ~CGameWorld2D();

        public:
            virtual fgBool initialize(void);
            virtual fgBool destroy(void);

        private:

        }; // class CGameWorld2D

    } // namespace game
} // namespace fg

    #undef FG_INC_GAME_2D_GAMEWORLD_BLOCK
#endif	/* FG_INC_GAME_2D_GAMEWORLD */
