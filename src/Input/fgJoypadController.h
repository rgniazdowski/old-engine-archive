/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_JOYPAD_CONTROLLER
    #define FG_INC_JOYPAD_CONTROLLER

    #define FG_MAX_GAME_CONTROLLERS 5

    #include "fgBuildConfig.h"
    #include "fgBool.h"

    #if defined(FG_USING_SDL2)
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_gamecontroller.h>
        #include <SDL2/SDL_joystick.h>
        #include <SDL2/SDL_haptic.h>
        #include <SDL2/SDL_events.h>
    #endif

    #include "Event/fgEventManager.h"

/*
 *
 */
class fgJoypadController {
public:

    //
    fgJoypadController(fgEventManager *eventMgr = NULL);

    //
    virtual ~fgJoypadController();

    //

    fgBool initialize(void);

    //

    void quit(void);

    //
    fgEventManager *getEventManager(void) const {
        return m_eventMgr;
    }

    //
    void setEventManager(fgEventManager *eventMgr) {
        m_eventMgr = eventMgr;
    }

    #if defined(FG_USING_SDL2)
    int processEvent(const SDL_Event& event);
    #else
    int processEvent(void);
    #endif

    //static fgBool isConnected(void);

private:
    #if defined(FG_USING_SDL2)
    ///
    SDL_GameController *m_gamepad;
    ///
    SDL_Haptic *m_haptic;
    ///
    SDL_JoystickID m_instanceID;
    #else
    void *m_gamepad;
    void *m_haptic;
    int m_instanceID;
    #endif
    ///
    fgEventManager *m_eventMgr;
    ///
    fgBool m_isConnected;
    ///
    static fgBool m_init;
    //
    static fgJoypadController* m_controllers;
    //
    #if defined(FG_USING_SDL2)
    static int getControllerIdx(const SDL_JoystickID instance);
    #else
    static int getControllerIdx(const int instance);
    #endif

    //
    void open(const int device);
    //
    void close(void);

};

#endif /* FG_INC_JOYPAD_CONTROLLER */ 
