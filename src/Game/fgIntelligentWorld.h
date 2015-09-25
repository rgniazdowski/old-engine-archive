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
 * File:   fgIntelligentWorld.h
 * Author: vigilant
 *
 * Created on September 23, 2015, 9:46 PM
 */

#ifndef FG_INC_GAME_INTELLIGENT_WORLD
    #define FG_INC_GAME_INTELLIGENT_WORLD
    #define FG_INC_GAME_INTELLIGENT_WORLD_BLOCK

    #include "fgBool.h"

namespace fg {
    namespace game {

        /**
         *
         */
        class CIntelligentWorld {
        public:
            typedef CIntelligentWorld self_type;
            typedef CIntelligentWorld type;

        public:
            CIntelligentWorld();
            CIntelligentWorld(const CIntelligentWorld& orig);
            virtual ~CIntelligentWorld();

        public:
            virtual fgBool initialize(void);
            virtual fgBool destroy(void);

            virtual void update(float delta = 0.0f);

        private:

        }; // class CIntelligentWorld

    } // namespace game
} // namespace fg

    #undef FG_INC_GAME_INTELLIGENT_WORLD_BLOCK
#endif	/* FG_INC_GAME_INTELLIGENT_WORLD */
