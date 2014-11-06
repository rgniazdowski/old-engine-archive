/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
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

/**
 * 
 * @param L
 * @param info
 * @param _type
 */
fgScriptCallback::fgScriptCallback(lua_State *L,
                                   const char *info,
                                   unsigned short int _argc,
                                   ScriptCallbackType _type) :
m_luaState(L),
m_script(),
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
        // info is function name
        m_function = new function_type(state, info);
        FG_LOG_DEBUG("ScriptCallback: Initializing with Lua Function: '%s'", info);
#endif /* FG_USING_LUA_PLUS */
    } else if(_type == SCRIPT) {
        // Initialize buffer of script to execute
        m_script = info;
        FG_LOG_DEBUG("ScriptCallback: Initializing with script: '%s'", info);
    }
}

/**
 * 
 * @return 
 */
fgBool fgScriptCallback::Call(void) {
    if(m_type == INVALID || !m_luaState)
        return FG_FALSE;
    if(m_argc > 0 && m_type != SCRIPT) {
        // This callback requires at least one argument
        // The call will fail
        return FG_FALSE;
    }
#if defined(FG_USING_LUA_PLUS)
    if(m_type == GUI_CALLBACK) {
        // Standard mode is that Lua/Script callback get only one parameter
        // In case of Event this will be proper event structure
        // With GUI this will be proper pointer to Widget
        // This call is without parameters so, need to pass empty Widget
        fgGuiButton button;
        (*m_function)((fgGuiWidget *) & button); // No return value expected
    } else if(m_type == EVENT_CALLBACK) {
        fgEvent event;
        memset(&event, 0, sizeof (fgEvent));
        (*m_function)((fgEvent *) & event);
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
fgBool fgScriptCallback::Call(fgArgumentList *argv) {
    if(m_type == INVALID || !m_luaState)
        return FG_FALSE;
    if(!argv) {
        return Call();
    }
    if(!argv->getArgumentCount()) {
        // This is hacky, what if script callback is to function that takes
        // some number of arguments?
        return Call();
    }
#if defined(FG_USING_LUA_PLUS)
    fgArgumentType argType = FG_ARGUMENT_NONE;
    void *pArg = argv->getArgumentValueByID(0, &argType);
    if(!pArg)
        return FG_FALSE;
    if(m_type == GUI_CALLBACK) {
        // This is all kinda hacky, what if callback does not take any arguments
        // argv contains arguments - there is a special arg type - pointer struct
        // Will need to hack it!

        fgGuiWidget *pWidget = (fgGuiWidget *)pArg;
        if(!pWidget)
            return FG_FALSE;
        if(pWidget->getTypeTraits() & FG_GUI_WIDGET) {
            (*m_function)(pWidget); // No return value expected
        }
        return FG_TRUE;
    } else if(m_type == EVENT_CALLBACK) {
        fgEventBase *pEvent = (fgEventBase *)pArg;
        //
        // #FIXME -- need to automate this somehow ... cant quite see if it's possible
        //
        fgEventType eType = pEvent->eventType;
        switch(eType) {
            case FG_EVENT_TOUCH_PRESSED:
            case FG_EVENT_TOUCH_RELEASED:
            case FG_EVENT_TOUCH_MOTION:
            case FG_EVENT_TOUCH_TAP_FINISHED:
                //fgTouchEvent
                //FG_EVENT_TOUCH = 5,
                break;

            case FG_EVENT_MOUSE_PRESSED:
            case FG_EVENT_MOUSE_RELEASED:
            case FG_EVENT_MOUSE_MOTION:
                //fgMouseEvent
                //FG_EVENT_MOUSE = 9,
                break;

            case FG_EVENT_SWIPE_X:
            case FG_EVENT_SWIPE_Y:
            case FG_EVENT_SWIPE_XY:
            //case FG_EVENT_SWIPE_ANGLE:
                //fgSwipeEvent
                break;

            case FG_EVENT_SWIPE_PINCH:
                //fgSwipePinchEvent
                break;

            case FG_EVENT_MULTI_SWIPE_ROTATE:
                //fgSwipeRotateEvent
                break;

            case FG_EVENT_KEY_DOWN:
            case FG_EVENT_KEY_UP:
                //fgKeyEvent
                break;

            case FG_EVENT_RESOURCE_CREATED:
            case FG_EVENT_RESOURCE_REMOVED:
            case FG_EVENT_RESOURCE_DISPOSED:
            case FG_EVENT_RESOURCE_DESTROYED:
            case FG_EVENT_RESOURCE_REQUESTED:
                //fgResourceEvent
                break;
                
            case FG_EVENT_PROGRAM_INIT:
                // ??
                break;

            case FG_EVENT_VERTEX_STREAM_READY:
                // fgVertexStreamEvent ??
                break;
            case FG_EVENT_CAMERA_CHANGED:
                // ???
                // fgCameraEvent
                break;
                
            case FG_EVENT_SOUND_PLAYED:
                // fgSoundEvent ??
                break;

            case FG_EVENT_MENU_CHANGED:
                // fgMenuChangedEvent ??
                break;
            case FG_EVENT_WIDGET_STATE_CHANGED: 
                // fgWidgetEvent
                break;

            case FG_EVENT_SENSORS_CHANGED:
                // fgSensorsEvent
                break;

            case FG_EVENT_GAME_CONTROLLER_ADDED:
            case FG_EVENT_GAME_CONTROLLER_REMOVED:
                //fgControllerDeviceEvent
                break;
            case FG_EVENT_GAME_CONTROLLER_BUTTON:
                //fgControllerButtonEvent
                break;
            case FG_EVENT_GAME_CONTROLLER_AXIS:
                //fgControllerAxisEvent
                break;
            default:
                return FG_FALSE;
                break;
        };
        // Need to cast to proper pointer already
        // Some helper ?
        //m_function((fgMouseEvent *));
        // fgEvent is just one big union, first bytes point
        // to the same thing in every event structure - eventType + timeStamp
        (*m_function)((fgEvent *)pEvent); 
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
