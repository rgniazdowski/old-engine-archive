/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgScriptCallback.cpp
 * Author: vigilant
 *
 * Created on November 6, 2014, 6:12 PM
 */

#include "fgScriptCallback.h"
#include "fgScriptCD.h"

#include "GUI/fgGuiWidget.h"
#include "GUI/fgGuiButton.h"
#include "Event/fgEventDefinitions.h"

using namespace fg;

/**
 * 
 * @param L
 * @param info
 * @param _type
 */
script::CScriptCallback::CScriptCallback(lua_State *L,
                                         const char *info,
                                         unsigned short int _argc,
                                         ScriptCallbackType _type) :
m_luaState(L),
m_script(),
m_function(NULL),
m_type(_type),
m_argc(_argc) {
    if(!info || !L) {
        m_type = INVALID;
        return;
    }
    if(_type == INVALID)
        return;
    if(_type == EVENT_CALLBACK || _type == GUI_CALLBACK) {
#if defined(FG_USING_LUA_PLUS)
        LuaPlus::LuaState *state = lua_State_to_LuaState(m_luaState);
        if(!state)
            return;
        m_function = fgMalloc<function_type>();
        // info is function name
        *m_function = function_type(state, info);
        FG_LOG_DEBUG("ScriptCallback: Initializing with Lua Function: '%s'", info);
#endif /* FG_USING_LUA_PLUS */
    } else if(_type == SCRIPT) {
        m_function = NULL;
        // Initialize buffer of script to execute
        m_script = info;
        FG_LOG_DEBUG("ScriptCallback: Initializing with script: '%s'", info);
    }
}

/**
 * 
 * @return 
 */
fgBool script::CScriptCallback::Call(void) {
    if(m_type == INVALID || !m_luaState || !m_function)
        return FG_FALSE;
    if(m_argc > 0 && m_type != SCRIPT) {
        // This callback requires at least one argument
        // The call will fail
        return FG_FALSE;
    }
        
#if defined(FG_USING_LUA_PLUS)
    if(!m_argc) {
        (*m_function)(); // No return value expected
    } else if(m_type == GUI_CALLBACK) {
        // Standard mode is that Lua/Script callback get only one parameter
        // In case of Event this will be proper event structure
        // With GUI this will be proper pointer to Widget
        // This call is without parameters so, need to pass empty Widget
        gui::CButton button;
        (*m_function)((gui::CWidget *) & button); // No return value expected
    } else if(m_type == EVENT_CALLBACK) {
        event::SEvent event;
        memset(&event, 0, sizeof (event::SEvent));
        (*m_function)((event::SEvent *) & event);
    } else if(m_type == SCRIPT) {
        if(m_script.empty())
            return FG_FALSE;
        LuaPlus::LuaState *state = lua_State_to_LuaState(m_luaState);
        state->DoString(m_script.c_str());
    }
#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}

/**
 * 
 * @param argv
 * @return 
 */
fgBool script::CScriptCallback::Call(event::CArgumentList *argv) {
    if(m_type == INVALID || !m_luaState)
        return FG_FALSE;
    if(!argv) {
        return Call();
    }
    if(!argv->getCount()) {
        // This is hacky, what if script callback is to function that takes
        // some number of arguments?
        return Call();
    }
    if(!m_argc) {
        return Call();
    }
#if defined(FG_USING_LUA_PLUS)
    event::SArgument::Type argType = event::SArgument::Type::ARG_NONE;
    void *pArg = argv->getValueByID(0, &argType);
    if(!pArg)
        return FG_FALSE;
    if(m_type == GUI_CALLBACK) {
        // This is all kinda hacky, what if callback does not take any arguments
        // argv contains arguments - there is a special arg type - pointer struct
        // Will need to hack it!
        // This probably wont be used often or event removed as there will
        // be separate class for this fgScriptGuiCallback
        gui::CWidget *pWidget = (gui::CWidget *)pArg;
        if(!pWidget)
            return FG_FALSE;
        if(pWidget->getTypeTraits() & gui::WIDGET) {
            (*m_function)(pWidget); // No return value expected
        }
        return FG_TRUE;
    } else if(m_type == EVENT_CALLBACK) {
        event::SEvent *pEvent = (event::SEvent *)pArg;
        //
        // #FIXME -- need to automate this somehow ... cant quite see if it's possible
        //
#if 0
        event::EventType eType = pEvent->eventType;
        switch(eType) {
            case event::TOUCH_PRESSED:
            case event::TOUCH_RELEASED:
            case event::TOUCH_MOTION:
            case event::TOUCH_TAP_FINISHED:
                //fgTouchEvent
                //event::TOUCH = 5,
                break;

            case event::MOUSE_PRESSED:
            case event::MOUSE_RELEASED:
            case event::MOUSE_MOTION:
                //fgMouseEvent
                //event::MOUSE = 9,
                break;

            case event::SWIPE_X:
            case event::SWIPE_Y:
            case event::SWIPE_XY:
                //case event::SWIPE_ANGLE:
                //fgSwipeEvent
                break;

            case event::SWIPE_PINCH:
                //fgSwipePinchEvent
                break;

            case event::MULTI_SWIPE_ROTATE:
                //fgSwipeRotateEvent
                break;

            case event::KEY_DOWN:
            case event::KEY_UP:
                //fgKeyEvent
                break;

            case event::RESOURCE_CREATED:
            case event::RESOURCE_REMOVED:
            case event::RESOURCE_DISPOSED:
            case event::RESOURCE_DESTROYED:
            case event::RESOURCE_REQUESTED:
                //fgResourceEvent
                break;

            case event::PROGRAM_INIT:
                // ??
                break;

            case event::VERTEX_STREAM_READY:
                // fgVertexStreamEvent ??
                break;
            case event::CAMERA_CHANGED:
                // ???
                // fgCameraEvent
                break;

            case event::SOUND_PLAYED:
                // fgSoundEvent ??
                break;

            case event::MENU_CHANGED:
                // fgMenuChangedEvent ??
                break;
            case event::WIDGET_STATE_CHANGED:
                // fgWidgetEvent
                break;

            case event::SENSORS_CHANGED:
                // fgSensorsEvent
                break;

            case event::GAME_CONTROLLER_ADDED:
            case event::GAME_CONTROLLER_REMOVED:
                //fgControllerDeviceEvent
                break;
            case event::GAME_CONTROLLER_BUTTON:
                //fgControllerButtonEvent
                break;
            case event::GAME_CONTROLLER_AXIS:
                //fgControllerAxisEvent
                break;
            default:
                return FG_FALSE;
                break;
        };
#endif
        // Need to cast to proper pointer already
        // Some helper ?
        //m_function((fgMouseEvent *));
        // fgEvent is just one big union, first bytes point
        // to the same thing in every event structure - eventType + timeStamp
        (*m_function)((event::SEvent *)pEvent);
        return FG_TRUE;
    } else if(m_type == SCRIPT) {
        if(m_script.empty())
            return FG_FALSE;
        LuaPlus::LuaState *state = lua_State_to_LuaState(m_luaState);
        state->DoString(m_script.c_str());
    }
#endif /* FG_USING_LUA_PLUS */
    return FG_FALSE;
}

/**
 * 
 * @return 
 */
fgBool script::CScriptCallback::Call(void *pSystemData) {
    if(m_type == INVALID || !m_luaState)
        return FG_FALSE;
    if(!pSystemData) {
        return Call();
    }
    if(!m_argc) {
        return Call();
    }
#if defined(FG_USING_LUA_PLUS)
    if(m_type == GUI_CALLBACK) {
        // This is all kinda hacky, what if callback does not take any arguments
        // argv contains arguments - there is a special arg type - pointer struct
        // Will need to hack it!
        // This probably wont be used often or event removed as there will
        // be separate class for this fgScriptGuiCallback
        gui::CWidget *pWidget = (gui::CWidget *)pSystemData;
        if(!pWidget)
            return FG_FALSE;
        if(!pWidget->isManaged())
            return FG_FALSE;
        if(pWidget->getTypeTraits() & gui::WIDGET) {
            (*m_function)(pWidget); // No return value expected
        }
        return FG_TRUE;
    } else if(m_type == EVENT_CALLBACK) {
        event::SEvent *pEvent = (event::SEvent *)pSystemData;
        // Need to cast to proper pointer already
        // Some helper ?
        //m_function((fgMouseEvent *));
        // fgEvent is just one big union, first bytes point
        // to the same thing in every event structure - eventType + timeStamp
        (*m_function)((event::SEvent *)pEvent);
        return FG_TRUE;
    } else if(m_type == SCRIPT) {
        if(m_script.empty())
            return FG_FALSE;
        LuaPlus::LuaState *state = lua_State_to_LuaState(m_luaState);
        state->DoString(m_script.c_str());
    }
#endif /* FG_USING_LUA_PLUS */
    return FG_FALSE;
}

/*******************************************************************************
 * SCRIPT GUI CALLBACK - SPECIAL CALLBACK TO BE USED IN GUI 
 */

/**
 * 
 * @param L
 * @param info
 * @param _type
 */
script::CScriptGuiCallback::CScriptGuiCallback(gui::CGuiMain *pGuiMain, lua_State *L,
                                               const char *info,
                                               const unsigned short int _argc) :
CScriptCallback(L, info, _argc, SCRIPT),
gui::CGuiCallback(pGuiMain) {
    event::CFunctionCallback::setFunction((event::CFunctionCallback::fgFunction)NULL);
}

/**
 * 
 * @return 
 */
fgBool script::CScriptGuiCallback::Call(void) {
    if(getType() == INVALID) {
        return FG_FALSE;
    } else if(getType() == GUI_CALLBACK || getType() == SCRIPT) {
        return script::CScriptCallback::Call();
    }
    return FG_FALSE;
}

/**
 * 
 * @param argv
 * @return 
 */
fgBool script::CScriptGuiCallback::Call(event::CArgumentList *argv) {
    if(!argv)
        return FG_FALSE;
    return script::CScriptCallback::Call(argv);
}

/**
 * 
 * @param pSystemData
 * @return 
 */
fgBool script::CScriptGuiCallback::Call(void *pSystemData) {
    if(!pSystemData)
        return FG_FALSE;
    return script::CScriptCallback::Call(pSystemData);
}

/**
 * 
 * @param pWidget
 * @return 
 */
fgBool script::CScriptGuiCallback::Call(gui::CWidget *pWidget) {
    if(!pWidget)
        return FG_FALSE;
    return script::CScriptCallback::Call((void *)pWidget);
}

/**
 * 
 * @param pGuiMain
 * @param pWidget
 * @return 
 */
fgBool script::CScriptGuiCallback::Call(gui::CGuiMain *pGuiMain, gui::CWidget *pWidget) {
    if(!pWidget)
        return FG_FALSE;
    return script::CScriptCallback::Call((void *)pWidget);
}
