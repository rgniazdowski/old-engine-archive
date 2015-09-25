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
 * File:   fgIntelligent.h
 * Author: vigilant
 *
 * Created on September 23, 2015, 8:39 PM
 */

#ifndef FG_INC_GAME_INTELLIGENT
    #define FG_INC_GAME_INTELLIGENT
    #define FG_INC_GAME_INTELLIGENT_BLOCK

    #include "fgTraits.h"

namespace fg {
    namespace game {
        namespace traits {

            /**
             *
             */
            class CIntelligent {
            public:
                typedef CIntelligent self_type;
                typedef CIntelligent type;

            public:
                static const fg::traits::SceneNode SELF_TRAIT = fg::traits::INTELLIGENT;

            public:
                CIntelligent();
                CIntelligent(const CIntelligent& orig);
                virtual ~CIntelligent();
                
            private:

            }; // class CIntelligent

        } // namespace traits
    } // namespace game
} // namespace fg
    #undef FG_INC_GAME_INTELLIGENT_BLOCK
#endif	/* FG_INC_GAME_INTELLIGENT */
