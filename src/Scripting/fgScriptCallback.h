/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgScriptCallback.h
 * Author: vigilant
 *
 * Created on November 6, 2014, 5:41 PM
 */

#ifndef _FG_SCRIPT_CALLBACK_H_
    #define	_FG_SCRIPT_CALLBACK_H_

    #if defined(_FG_SCRIPT_METATABLES_H_BLOCK_)
        #error "FG_SCRIPT_METATABLES_H_BLOCK is defined: Do not include ScriptCallback header inside of ScriptMetatables header"
    #endif

    #include "fgBuildConfig.h"
    #include "Event/fgCallback.h"

    #if defined(FG_USING_LUA_PLUS)
        #include "LuaPlus/LuaPlus.h"
    #endif

    #include "Util/fgMemory.h"

/**
 * 
 * @return 
 */
class fgScriptCallback : public fgFunctionCallback {
public:

    enum ScriptCallbackType {
        SCRIPT,
        EVENT_CALLBACK,
        GUI_CALLBACK,
        INVALID
    };
    typedef fgFunctionCallback base_type;
    #if defined(FG_USING_LUA_PLUS)
    typedef LuaPlus::LuaFunctionVoid function_type;
    #else
    typedef void function_type; // #ERROR
    #endif /* FG_USING_LUA_PLUS */
    /**
     * 
     */
    fgScriptCallback() :
    m_luaState(NULL),
    m_script(),
    m_function(NULL),
    m_type(INVALID),
    m_argc(0) { }
    /**
     * 
     * @param function
     */
    #if defined(FG_USING_LUA_PLUS)
    fgScriptCallback(lua_State *L,
                     const LuaPlus::LuaObject& function,
                     unsigned short int _argc = 1,
                     const ScriptCallbackType _type = EVENT_CALLBACK) :
    m_luaState(L),
    m_script(),
    m_function(NULL),
    m_type(_type),
    m_argc(_argc) {
        // Will use simple malloc because there's no need to call destructor
        // on this type
        m_function = fgMalloc<function_type>();
        *m_function = function_type(function);
    }
    #endif /* FG_USING_LUA_PLUS */
    /**
     * 
     * @param L
     * @param info
     * @param _type
     */
    fgScriptCallback(lua_State *L,
                     const char *info,
                     const unsigned short int _argc = 1,
                     ScriptCallbackType _type = EVENT_CALLBACK);
    /**
     * 
     */
    virtual ~fgScriptCallback() {
        m_luaState = NULL;
        if(m_function) {
            fgFree(m_function);
        }
        m_function = NULL;
        m_script.clear();
    }
    /**
     * 
     * @param L
     */
    void setState(lua_State *L) {
        m_luaState = L;
    }
    /**
     * 
     * @param function
     */
    #if defined(FG_USING_LUA_PLUS)
    void setFunction(const LuaPlus::LuaObject& function) {
        if(!m_function) {
            m_function = fgMalloc<function_type>();
        }
        if(!function.GetCState())
            return;
        if(!m_luaState)
            m_luaState = function.GetCState();
        *m_function = function_type(function);
        if(m_type == INVALID)
            m_type = EVENT_CALLBACK;
    }
    #endif /* FG_USING_LUA_PLUS */
    /**
     * 
     * @param script
     */
    void setScript(const char *script) {
        if(!script)
            return;
        if(strlen(script) < 1)
            return;
        m_script = script;
        m_type = SCRIPT;
    }
    /**
     * 
     * @return 
     */
    ScriptCallbackType getType(void) const {
        return m_type;
    }
    /**
     * 
     * @param argc
     */
    void setArgC(const unsigned short int argc) {
        m_argc = argc;
    }
    /**
     * 
     * @return 
     */
    unsigned short int getArgC(void) const {
        return m_argc;
    }
    /**
     * 
     * @return 
     */
    virtual fgBool Call(void);
    /**
     * 
     * @param argv
     * @return 
     */
    virtual fgBool Call(fgArgumentList *argv);
private:
    ///
    lua_State *m_luaState;
    ///
    std::string m_script;
    ///
    function_type *m_function;
    ///
    ScriptCallbackType m_type;
    ///
    unsigned short int m_argc;
};

#endif	/* _FG_SCRIPT_CALLBACK_H_ */
