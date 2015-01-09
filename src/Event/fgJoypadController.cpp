/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgJoypadController.h"
#include "Util/fgMemory.h"
#include "fgLog.h"

///
fg::event::CJoypadController *fg::event::CJoypadController::m_controllers = NULL;
///
fgBool fg::event::CJoypadController::m_init = FG_FALSE;

/**
 * 
 * @param eventMgr
 */
fg::event::CJoypadController::CJoypadController(CEventManager *eventMgr) :
m_gamepad(NULL),
m_haptic(NULL),
m_instanceID(-1),
m_pEventMgr(eventMgr),
m_isConnected(FG_FALSE) {
 }

/**
 * 
 */
fg::event::CJoypadController::~CJoypadController() { }

/**
 * Opens the joystick controller
 * @param device
 */
void fg::event::CJoypadController::open(const int device) {
#if defined(FG_USING_SDL2)
    fgBool isGameController = FG_FALSE;
    if(SDL_IsGameController(device)) {
        FG_LOG_DEBUG("SDL: Device(%d) is a game controller.", device);
        isGameController = FG_TRUE;
    } else {
        FG_LOG_DEBUG("SDL: Device(%d) is not a game controller.", device);
    }
    if(SDL_JoystickNameForIndex(device)) {
        FG_LOG_DEBUG("SDL: Device(%d) name: '%s'", device, SDL_JoystickNameForIndex(device));
    }
    SDL_Joystick *j = NULL;
    if(isGameController) {
        m_gamepad = SDL_GameControllerOpen(device);
        if(!m_gamepad) {
            FG_LOG::PrintError("SDL: Error occurred for game controller: '%s'", SDL_GetError());
            SDL_ClearError();
        }
        j = SDL_GameControllerGetJoystick(m_gamepad);
    } else {
        j = SDL_JoystickOpen(device);
        if(j) {
            FG_LOG_DEBUG("SDL: Successfully opened joystick [%d] '%s'", device, SDL_JoystickNameForIndex(device));
        }
    }
    if(!j) {
        FG_LOG::PrintError("SDL: Error occured for game controller: '%s'", SDL_GetError());
        SDL_ClearError();
    }
    m_instanceID = SDL_JoystickInstanceID(j);
    m_isConnected = FG_TRUE;
    if(SDL_JoystickIsHaptic(j)) {
        m_haptic = SDL_HapticOpenFromJoystick(j);
        FG_LOG_DEBUG("SDL: Haptic Effects: %d", SDL_HapticNumEffects(m_haptic));
        FG_LOG_DEBUG("SDL: Haptic Query: %x", SDL_HapticQuery(m_haptic));
        if(SDL_HapticRumbleSupported(m_haptic)) {
            if(SDL_HapticRumbleInit(m_haptic) != 0) {
                FG_LOG_DEBUG("SDL: Haptic Rumble Init: %s", SDL_GetError());
                SDL_HapticClose(m_haptic);
                m_haptic = 0;
            }
        } else {
            SDL_HapticClose(m_haptic);
            m_haptic = 0;
        }
    }
#endif
}

/**
 *
 */
void fg::event::CJoypadController::close(void) {
#if defined(FG_USING_SDL2)
    if(m_isConnected) {
        m_isConnected = FG_FALSE;
        if(m_haptic) {
            SDL_HapticClose(m_haptic);
            m_haptic = 0;
        }
        if(m_gamepad)
            SDL_GameControllerClose(m_gamepad);
        m_gamepad = 0;
    }
#endif
}

/**
 *
 */
void fg::event::CJoypadController::quit(void) {
    if(m_controllers) {
        for(int i = 0; i < FG_MAX_GAME_CONTROLLERS; i++)
            m_controllers[i].close();
        fgFree(m_controllers, sizeof (CJoypadController) * FG_MAX_GAME_CONTROLLERS);
    }
    m_controllers = NULL;
#if defined(FG_USING_SDL2)
    if(m_init || SDL_WasInit(SDL_INIT_GAMECONTROLLER) != 0) {
        m_init = FG_FALSE;
        SDL_JoystickEventState(SDL_IGNORE);
        SDL_GameControllerEventState(SDL_IGNORE);
        SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC);
        FG_LOG_DEBUG("SDL: Closing GameController.");

    }
#endif
}

/**
 *
 * @return
 */
fgBool fg::event::CJoypadController::initialize(void) {
    if(!m_controllers) {
        m_controllers = fgMalloc<CJoypadController>(FG_MAX_GAME_CONTROLLERS);
    }
#if defined(FG_USING_SDL2)
    if(SDL_WasInit(SDL_INIT_GAMECONTROLLER) == 0) {
        if(SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC) != 0) {
            FG_LOG::PrintError("SDL: Couldn't initialize GameController subsystem: '%s'", SDL_GetError());
            m_init = FG_FALSE;
            return FG_FALSE;
        }
        int joys = SDL_NumJoysticks();
        FG_LOG_DEBUG("SDL: GameController initialized successfully. Number of joysticks: %d", joys);
        m_init = FG_TRUE;
        SDL_GameControllerEventState(SDL_ENABLE);
        SDL_JoystickEventState(SDL_ENABLE);

        for(int i = 0; i < joys; i++) {
            CJoypadController& jc = m_controllers[i];
            jc.open(i);
            if(m_pEventMgr) {
                fgControllerDeviceEvent *fgevent = fgMalloc<fgControllerDeviceEvent>();
                fgArgumentList *list = new fgArgumentList(1);
                fgevent->which = i;
                fgevent->timeStamp = 0; // #FIXME
                fgevent->eventType = FG_EVENT_GAME_CONTROLLER_ADDED;
                list->pushArgument(FG_ARGUMENT_TEMP_POINTER, (void*)fgevent);
                m_pEventMgr->throwEvent(fgevent->eventType, list);
            }
        }


    } else {
        FG_LOG_DEBUG("SDL: GameController already initialized.");
    }
#endif
    return m_init;
}

/**
 * 
 * @param instance
 * @return 
 */
#if defined(FG_USING_SDL2)
int fg::event::CJoypadController::getControllerIdx(const SDL_JoystickID instance) {
#else
int fg::event::CJoypadController::getControllerIdx(const int instance) {
#endif

    for(int i = 0; i < FG_MAX_GAME_CONTROLLERS; ++i) {
        if(m_controllers[i].m_instanceID && m_controllers[i].m_instanceID == instance) {
            return i;
        }
    }
    return -1;
}

/**
 * 
 * @param event
 * @return 
 */
#if defined(FG_USING_SDL2)
int fg::event::CJoypadController::processEvent(const SDL_Event& event) {
    //if(!m_eventMgr)
    //return;
    switch(event.type) {

        case SDL_CONTROLLERAXISMOTION:
        {
            const SDL_ControllerAxisEvent &caxis = event.caxis;
            // handle axis motion
            int cIndex = getControllerIdx(event.cdevice.which);
            if(cIndex < 0) return 0; // unknown controller?
            //fgJoypadController& jc = m_controllers[cIndex];
            // Throw proper fgEventManager event + info
            if(m_pEventMgr) {
                fgControllerAxisEvent *fgevent = fgMalloc<fgControllerAxisEvent>();
                fgArgumentList *list = new fgArgumentList(1);
                fgevent->axis = caxis.axis;
                fgevent->value = caxis.value;
                fgevent->which = caxis.which;
                fgevent->timeStamp = caxis.timestamp;
                fgevent->eventType = FG_EVENT_GAME_CONTROLLER_AXIS;
                list->pushArgument(FG_ARGUMENT_TEMP_POINTER, (void*)fgevent);
                m_pEventMgr->throwEvent(fgevent->eventType, list);
            }
            break;
        }

        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP:
        {
            const SDL_ControllerButtonEvent &cbutton = event.cbutton;
            // handle button up/down
            int cIndex = getControllerIdx(event.cdevice.which);
            if(cIndex < 0) return 0; // unknown controller?
            //fgJoypadController& jc = m_controllers[cIndex];
            // Throw proper fgEventManager event + info
            if(m_pEventMgr) {
                fgControllerButtonEvent *fgevent = fgMalloc<fgControllerButtonEvent>();
                fgArgumentList *list = new fgArgumentList(1);
                fgevent->state = cbutton.state;
                fgevent->button = cbutton.button;
                fgevent->which = cbutton.which;
                fgevent->timeStamp = cbutton.timestamp;
                fgevent->eventType = FG_EVENT_GAME_CONTROLLER_BUTTON;
                list->pushArgument(FG_ARGUMENT_TEMP_POINTER, (void*)fgevent);
                m_pEventMgr->throwEvent(fgevent->eventType, list);
            }
            break;
        }

        case SDL_CONTROLLERDEVICEADDED:
        {
            if(event.cdevice.which < FG_MAX_GAME_CONTROLLERS) {
                CJoypadController& jc = m_controllers[event.cdevice.which];
                jc.open(event.cdevice.which);
                if(m_pEventMgr) {
                    fgControllerDeviceEvent *fgevent = fgMalloc<fgControllerDeviceEvent>();
                    fgArgumentList *list = new fgArgumentList(1);
                    fgevent->which = event.cdevice.which;
                    fgevent->timeStamp = event.cdevice.timestamp;
                    fgevent->eventType = FG_EVENT_GAME_CONTROLLER_ADDED;
                    list->pushArgument(FG_ARGUMENT_TEMP_POINTER, (void*)fgevent);
                    m_pEventMgr->throwEvent(fgevent->eventType, list);
                }
            }
            break;
        }

        case SDL_CONTROLLERDEVICEREMOVED:
        {
            int cIndex = getControllerIdx(event.cdevice.which);
            if(cIndex < 0) return 0; // unknown controller?
            CJoypadController& jc = m_controllers[cIndex];
            jc.close();
            if(m_pEventMgr) {
                fgControllerDeviceEvent *fgevent = fgMalloc<fgControllerDeviceEvent>();
                fgArgumentList *list = new fgArgumentList(1);
                fgevent->which = event.cdevice.which;
                fgevent->timeStamp = event.cdevice.timestamp;
                fgevent->eventType = FG_EVENT_GAME_CONTROLLER_REMOVED;
                list->pushArgument(FG_ARGUMENT_TEMP_POINTER, (void*)fgevent);
                m_pEventMgr->throwEvent(fgevent->eventType, list);
            }
            break;
        }
    }
    return 0;
}
#else
/*
 *
 */
int fg::event::CJoypadController::processEvent(void) {
    return 0;
}
#endif /* defined(FG_USING_SDL2) */
