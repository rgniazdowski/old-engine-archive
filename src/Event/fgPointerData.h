/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_POINTER_DATA
    #define FG_INC_POINTER_DATA
    #define FG_INC_POINTER_DATA_BLOCK

    #ifndef FG_INC_BUILD_CONFIG
        #include "fgBuildConfig.h"
    #endif

    #ifndef FG_INC_BOOL
        #include "fgBool.h"
    #endif

    #if defined(FG_USING_MARMALADE)

        #include "s3ePointer.h"
        #define FG_POINTER_BUTTON_SELECT		((unsigned int)S3E_POINTER_BUTTON_SELECT)
        #define FG_POINTER_BUTTON_LEFT             ((unsigned int)S3E_POINTER_BUTTON_LEFTMOUSE)
        #define FG_POINTER_BUTTON_RIGHT		((unsigned int)S3E_POINTER_BUTTON_RIGHTMOUSE)
        #define FG_POINTER_BUTTON_MIDDLE		((unsigned int)S3E_POINTER_BUTTON_MIDDLEMOUSE)
        #define FG_POINTER_BUTTON_WHEELUP		((unsigned int)S3E_POINTER_BUTTON_MOUSEWHEELUP)
        #define FG_POINTER_BUTTON_WHEELDOWN	((unsigned int)S3E_POINTER_BUTTON_MOUSEWHEELDOWN)

        #define FG_POINTER_STATE_UP			((unsigned int)S3E_POINTER_STATE_UP)
        #define FG_POINTER_STATE_DOWN			((unsigned int)S3E_POINTER_STATE_DOWN)
        #define FG_POINTER_STATE_PRESSED		((unsigned int)S3E_POINTER_STATE_PRESSED)
        #define FG_POINTER_STATE_RELEASED		((unsigned int)S3E_POINTER_STATE_RELEASED)
        #define FG_POINTER_STATE_UNKNOWN		((unsigned int)S3E_POINTER_STATE_UNKNOWN)

    #elif defined(FG_USING_SDL2)
        #include "SDL2/SDL_mouse.h"
        #include "SDL2/SDL_events.h"
        #define FG_POINTER_BUTTON_SELECT            SDL_BUTTON_LEFT
        #define FG_POINTER_BUTTON_LEFT              SDL_BUTTON_LEFT
        #define FG_POINTER_BUTTON_RIGHT             SDL_BUTTON_RIGHT
        #define FG_POINTER_BUTTON_MIDDLE            SDL_BUTTON_MIDDLE
        #define FG_POINTER_BUTTON_WHEELUP           10	
        #define FG_POINTER_BUTTON_WHEELDOWN         11

        #define FG_POINTER_STATE_UP                 0x4
        #define FG_POINTER_STATE_DOWN               0x2
        #define FG_POINTER_STATE_PRESSED            SDL_PRESSED     // 1 0x1
        #define FG_POINTER_STATE_RELEASED           SDL_RELEASED    // 0 0x0
        #define FG_POINTER_STATE_UNKNOWN            0x7

    #else

        #define FG_POINTER_BUTTON_SELECT            0
        #define FG_POINTER_BUTTON_LEFTMOUSE         0
        #define FG_POINTER_BUTTON_RIGHTMOUSE        1
        #define FG_POINTER_BUTTON_MIDDLEMOUSE       2
        #define FG_POINTER_BUTTON_MOUSEWHEELUP      3
        #define FG_POINTER_BUTTON_MOUSEWHEELDOWN    4

        #define FG_POINTER_STATE_UP                 0
        #define FG_POINTER_STATE_DOWN               1
        #define FG_POINTER_STATE_PRESSED            2
        #define FG_POINTER_STATE_RELEASED           4
        #define FG_POINTER_STATE_UNKNOWN            5

    #endif

typedef unsigned int fgTouchID;
typedef unsigned int fgPointerID;
typedef unsigned int fgButtonID;

typedef unsigned int fgPointerState;

/**
 *
 */
struct fgPointerData {

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
    fgPointerData() :
    m_touchID(0),
    m_state(FG_POINTER_STATE_UP),
    m_x(0), m_y(0),
    m_active(FG_FALSE),
    m_pointerTap(FG_FALSE) { }
};

    #undef FG_INC_POINTER_DATA_BLOCK
#endif /* FG_INC_POINTER_DATA */
