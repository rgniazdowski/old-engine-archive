/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_POINTER_DATA
    #define FG_INC_POINTER_DATA
    #define FG_INC_POINTER_DATA_BLOCK

    #include "fgBuildConfig.h"
    #include "fgBool.h"

    #if defined(FG_USING_SDL2)
        #include "SDL2/SDL_mouse.h"
        #include "SDL2/SDL_events.h"
        #define FG_POINTER_BUTTON_SELECT            SDL_BUTTON_LEFT
        #define FG_POINTER_BUTTON_LEFT              SDL_BUTTON_LEFT
        #define FG_POINTER_BUTTON_MIDDLE            SDL_BUTTON_MIDDLE
        #define FG_POINTER_BUTTON_RIGHT             SDL_BUTTON_RIGHT
        #define FG_POINTER_BUTTON_AUX1              SDL_BUTTON_X1
        #define FG_POINTER_BUTTON_AUX2              SDL_BUTTON_X2
        #define FG_POINTER_BUTTON_WHEELUP           10
        #define FG_POINTER_BUTTON_WHEELDOWN         11

        #define FG_POINTER_STATE_PRESSED            SDL_PRESSED     // 1 0x1
        #define FG_POINTER_STATE_RELEASED           SDL_RELEASED    // 0 0x0
        #define FG_POINTER_STATE_UP                 0x4
        #define FG_POINTER_STATE_DOWN               0x2        
        #define FG_POINTER_STATE_UNKNOWN            0x7

    #else

        #define FG_POINTER_BUTTON_SELECT            1
        #define FG_POINTER_BUTTON_LEFT              1
        #define FG_POINTER_BUTTON_MIDDLE            2
        #define FG_POINTER_BUTTON_RIGHT             3
        #define FG_POINTER_BUTTON_AUX1              4
        #define FG_POINTER_BUTTON_AUX2              5
        #define FG_POINTER_BUTTON_WHEELUP           10
        #define FG_POINTER_BUTTON_WHEELDOWN         11


        #define FG_POINTER_STATE_PRESSED            1
        #define FG_POINTER_STATE_RELEASED           0
        #define FG_POINTER_STATE_UP                 4
        #define FG_POINTER_STATE_DOWN               2
        #define FG_POINTER_STATE_UNKNOWN            5

    #endif

typedef unsigned int fgTouchID;
typedef unsigned int fgPointerID;
typedef unsigned int fgButtonID;

typedef unsigned int fgPointerState;

namespace fg {
    namespace event {

        /**
         *
         */
        struct SPointerData {

            /**
             */
            union {
                ///
                fgTouchID m_touchID;
                ///
                fgButtonID m_buttonID;
                ///
                fgPointerID m_pointerID;
            };
            ///
            fgPointerState m_state;

            /**
             */
            union {
                ///
                int m_moveX;
                ///
                int m_x;
            };

            /**
             */
            union {
                ///
                int m_moveY;
                ///
                int m_y;
            };

            int m_relX;
            int m_relY;

            /**
             */
            union {
                fgBool m_pressed;
                fgBool m_active;
            };
            ///
            fgBool m_pointerTap;
            /**
             * 
             */
            SPointerData() :
            m_touchID(0),
            m_state(FG_POINTER_STATE_UP),
            m_x(0), m_y(0),
            m_relX(0), m_relY(0),
            m_active(FG_FALSE),
            m_pointerTap(FG_FALSE) { }
        }; // struct SPointerData
        
    } // namespace event
} // namespace fg

    #undef FG_INC_POINTER_DATA_BLOCK
#endif /* FG_INC_POINTER_DATA */
