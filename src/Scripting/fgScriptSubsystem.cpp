/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgScriptSubsystem.h"

#if defined(FG_USING_LUA_PLUS)
///
LuaPlus::LuaState *fgScriptSubsystem::m_luaState = NULL;
///
LuaPlus::LuaObject fgScriptSubsystem::m_globals;
#endif

///
fgBool fgScriptSubsystem::m_isBindingComplete = FG_FALSE;
///
fgScriptSubsystem::userDataObjectMap fgScriptSubsystem::m_userDataObjectMap;

/**
 * 
 */
fgScriptSubsystem::fgScriptSubsystem() :
m_pEventMgr(NULL),
m_pResourceMgr(NULL),
m_pShaderMgr(NULL),
m_p2DSceneMgr(NULL),
m_p3DSceneMgr(NULL),
m_pParticleMgr(NULL),
m_pWidgetMgr(NULL),
m_pStyleMgr(NULL),
m_pSoundMgr(NULL) { }

/**
 * 
 */
fgScriptSubsystem::~fgScriptSubsystem() {
    fgScriptSubsystem::destroy();
}

/**
 * 
 */
void fgScriptSubsystem::clear(void) {
    memset(this, 0, sizeof (fgScriptSubsystem));
}

/**
 * 
 * @return 
 */
fgBool fgScriptSubsystem::destroy(void) {
    if(!m_init)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    m_globals.Reset();
    if(m_luaState)
        LuaPlus::LuaState::Destroy(m_luaState);
    m_luaState = NULL;
#endif

    m_isBindingComplete = FG_FALSE;
    m_init = FG_FALSE;
    m_userDataObjectMap.clear();
    fgScriptSubsystem::clear();
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool fgScriptSubsystem::initialize(void) {
    if(m_init)
        return m_init;
    if(m_isBindingComplete) {
        m_init = FG_TRUE;
        return m_init;
    }

    if(!m_pEventMgr || !m_pResourceMgr) {
        return FG_FALSE;
    }
    
    return FG_TRUE;
}

/**
 * 
 * @param L
 * @return 
 */
int fgScriptSubsystem::simpleGCEvent(lua_State* L) {
    if(!L)
        return 0;
    return 0;
}

/**
 * 
 * @param L
 * @return 
 */
int fgScriptSubsystem::simpleInPlaceGCEvent(lua_State* L) {
    if(!L)
        return 0;
    return 0;
}

/**
 * 
 * @param L
 * @return 
 */
int fgScriptSubsystem::managedGCEvent(lua_State* L) {
    if(!L)
        return 0;
    return 0;
}

/**
 * 
 * @return 
 */
fgBool fgScriptSubsystem::registerConstants(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool fgScriptSubsystem::registerEventManager(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool fgScriptSubsystem::registerResourceManager(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    return FG_TRUE;
}

/**
 * 
 * @return
 */
fgBool fgScriptSubsystem::registerShaderManager(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    return FG_TRUE;
}

/**
 * 
 * @return
 */
fgBool fgScriptSubsystem::register2DSceneManager(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    return FG_TRUE;
}

/**
 * 
 * @return
 */
fgBool fgScriptSubsystem::register3DSceneManager(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    return FG_TRUE;
}

/**
 * 
 * @return
 */
fgBool fgScriptSubsystem::registerParticleSystem(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    return FG_TRUE;
}

/**
 * 
 * @return
 */
fgBool fgScriptSubsystem::registerWidgetManager(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    return FG_TRUE;
}

/**
 * 
 * @return
 */
fgBool fgScriptSubsystem::registerStyleManager(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    return FG_TRUE;
}

/**
 * 
 * @return
 */
fgBool fgScriptSubsystem::registerSoundManager(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    return FG_TRUE;
}
