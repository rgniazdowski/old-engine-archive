/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
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

#ifndef FG_INC_SCRIPT_CALLBACK
    #define FG_INC_SCRIPT_CALLBACK
    #define FG_INC_SCRIPT_CALLBACK_BLOCK

    #if defined(FG_INC_SCRIPT_MT_BLOCK)
        #error "FG_SCRIPT_MTBLOCK is defined: Do not include ScriptCallback header inside of ScriptMetatables header"
    #endif

    #include "fgBuildConfig.h"
    #include "Event/fgCallback.h"

    #if defined(FG_USING_LUA_PLUS)
        #include "LuaPlus/LuaPlus.h"
    #endif

    #if !defined(FG_USING_LUA) && !defined(FG_USING_LUA_PLUS) && !defined(FG_LUA_STATE_TYPEDEF_HAX)
        #define FG_LUA_STATE_TYPEDEF_HAX

    struct lua_State {
	    void *_ptr;
    };
    #endif

    #include "Util/fgMemory.h"

/**
 * 
 * @return 
 */
class fgScriptCallback : public virtual fgFunctionCallback {
public:

    typedef fgFunctionCallback base_type;
    #if defined(FG_USING_LUA_PLUS)
    typedef LuaPlus::LuaFunctionVoid function_type;
    #else
    typedef void function_type; // #ERROR
    #endif /* FG_USING_LUA_PLUS */

    enum ScriptCallbackType {
        SCRIPT,
        EVENT_CALLBACK,
        GUI_CALLBACK,
        INVALID
    };
public:
    /**
     * 
     */
    fgScriptCallback() :
    m_luaState(NULL),
    m_script(),
    m_function(NULL),
    m_type(INVALID),
    m_argc(0) {
        fgFunctionCallback::setFunction((fgFunctionCallback::fgFunction)NULL);
    }
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
     * @param type
     */
    void setType(const ScriptCallbackType type) {
        if(type != INVALID)
            m_type = type;
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
    /**
     * 
     * @param pSystemData
     * @return 
     */
    virtual fgBool Call(void *pSystemData);

private:
    #if defined(FG_USING_LUA_PLUS) || defined(FG_USING_LUA)
    ///
    lua_State *m_luaState;
    #else
    void *m_luaState;
    #endif /* LUA_PLUS / LUA */
    ///
    std::string m_script;
    ///
    function_type *m_function;
    ///
    ScriptCallbackType m_type;
    ///
    unsigned short int m_argc;
};

    #include "GUI/fgGuiCallback.h"

/**
 *
 */
class fgScriptGuiCallback : public fgScriptCallback, public fgGuiCallback {
public:
    /**
     * 
     */
    fgScriptGuiCallback(fgGuiMain *pGuiMain = NULL) :
    fgScriptCallback(),
    fgGuiCallback(pGuiMain) {
        fgFunctionCallback::setFunction((fgFunctionCallback::fgFunction)NULL);
    }
    /**
     * 
     * @param function
     */
    #if defined(FG_USING_LUA_PLUS)
    fgScriptGuiCallback(fgGuiMain *pGuiMain, lua_State *L,
                        const LuaPlus::LuaObject& function,
                        unsigned short int _argc = 1) :
    fgScriptCallback(L, function, _argc, GUI_CALLBACK),
    fgGuiCallback(pGuiMain) {
        // Just to be sure - no harm done
        fgFunctionCallback::setFunction((fgFunctionCallback::fgFunction)NULL);
    }
    #endif /* FG_USING_LUA_PLUS */
    /**
     * 
     * @param L
     * @param info
     * @param _type
     */
    fgScriptGuiCallback(fgGuiMain *pGuiMain, lua_State *L,
                        const char *info,
                        const unsigned short int _argc = 1);
    
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
    
    /**
     * 
     * @param pSystemData
     * @return 
     */
    virtual fgBool Call(void *pSystemData);
    
    /**
     * 
     * @param pWidget
     * @return 
     */
    virtual fgBool Call(fgGuiWidget *pWidget);

    /**
     * 
     * @param pGuiMain
     * @param pWidget
     * @return 
     */
    virtual fgBool Call(fgGuiMain *pGuiMain, fgGuiWidget *pWidget);
};

    #undef FG_INC_SCRIPT_CALLBACK_BLOCK
#endif	/* FG_INC_SCRIPT_CALLBACK */
