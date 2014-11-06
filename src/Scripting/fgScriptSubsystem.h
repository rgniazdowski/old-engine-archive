/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_SCRIPT_SUBSYSTEM_H_
    #define _FG_SCRIPT_SUBSYSTEM_H_
    #define _FG_SCRIPT_SUBSYSTEM_H_BLOCK_

    #if defined(_FG_GUI_WIDGET_H_BLOCK_)
        #error "FG_GUI_WIDGET_H_BLOCK is defined: Do not include ScriptSubsystem header inside of Widget header"
    #endif

    #if defined(_FG_GUI_MAIN_H_BLOCK_)
        #error "FG_GUI_MAIN_H_BLOCK is defined: Do not include ScriptSubsystem header inside of GuiMain header"
    #endif

    #include "fgBuildConfig.h"
    #include "fgManagerBase.h"

    #include "Util/fgMemory.h"

    #define FG_MANAGER_SCRIPT       0x00004000
    #define FG_SUBSYSTEM_SCRIPT     0x00004000

    #if defined(FG_USING_LUA_PLUS)
        #include "LuaPlus/LuaPlus.h"
    #endif

    #include "fgScriptMetatables.h"
    #include "fgLog.h"

    #if !defined(FG_USING_LUA) && !defined(FG_USING_LUA_PLUS)
        #define FG_LUA_STATE_TYPEDEF_HAX

struct lua_State {
    void *_ptr;
};
    #endif

    #include <map>
    
    // #FIXME
    #include "fgScriptCD.h"

/**
 * 
 */
class fgScriptSubsystem : public fgManagerBase {
public:
    typedef fgManagerBase base_type;
private:
    #if defined(FG_USING_LUA_PLUS)
    ///
    typedef std::map<uintptr_t, LuaPlus::LuaObject> userDataObjectMap;
    #else
    ///
    typedef std::map<uintptr_t, void *> userDataObjectMap;
    #endif
    ///
    typedef userDataObjectMap::iterator userDataObjectMapItor;

    #if defined(FG_USING_LUA_PLUS)
    /// Main global state for LUA
    static LuaPlus::LuaState *m_luaState;
    /// Globals table
    static LuaPlus::LuaObject m_globals;

    /// Lua metatable for the external event manager
    LuaPlus::LuaObject m_metatableEventMgr;
    /// Lua metatable for the external resource manager
    LuaPlus::LuaObject m_metatableResourceMgr;
    /// Lua metatable for the external shader manager
    LuaPlus::LuaObject m_metatableShaderMgr;
    /// Lua metatable for the external 2D Scene manager
    LuaPlus::LuaObject m_metatable2DSceneMgr;
    /// Lua metatable for the external 3D Scene manager
    LuaPlus::LuaObject m_metatable3DSceneMgr;
    /// Lua metatable for the external particle manager
    LuaPlus::LuaObject m_metatableParticleMgr;
    /// Lua metatable for the external widget manager
    LuaPlus::LuaObject m_metatableWidgetMgr;
    /// Lua metatable for the external style manager
    LuaPlus::LuaObject m_metatableStyleMgr;
    /// Lua metatable for the external sound manager
    LuaPlus::LuaObject m_metatableSoundMgr;
    #endif

    /// Pointer to the external event manager
    static fgManagerBase *m_pEventMgr;
    /// Pointer to the external resource manager
    static fgManagerBase *m_pResourceMgr;
    /// Pointer to the external shader manager
    static fgManagerBase *m_pShaderMgr;
    /// Pointer to the external 2D Scene manager
    static fgManagerBase *m_p2DSceneMgr;
    /// Pointer to the external 3D Scene manager
    static fgManagerBase *m_p3DSceneMgr;
    /// Pointer to the external particle manager
    static fgManagerBase *m_pParticleMgr;
    /// Pointer to the external widget manager
    static fgManagerBase *m_pWidgetMgr;
    /// Pointer to the external style manager
    static fgManagerBase *m_pStyleMgr;
    /// Pointer to the external sound manager
    static fgManagerBase *m_pSoundMgr;

    ///
    static fgBool m_isBindingComplete;
    ///
    static userDataObjectMap m_userDataObjectMap;

public:
    /**
     * 
     */
    fgScriptSubsystem();
    /**
     * 
     */
    virtual ~fgScriptSubsystem();

public:
    /**
     * 
     * @param pEventManager
     */
    inline void setEventManager(fgManagerBase *pEventManager) {
        m_pEventMgr = pEventManager;
    }
    /**
     * 
     * @param pResourceManager
     */
    inline void setResourceManager(fgManagerBase *pResourceManager) {
        m_pResourceMgr = pResourceManager;
    }
    /**
     * 
     * @param pShaderManager
     */
    inline void setShaderManager(fgManagerBase *pShaderManager) {
        m_pShaderMgr = pShaderManager;
    }
    /**
     * 
     * @param p2DSceneManager
     */
    inline void set2DSceneManager(fgManagerBase *p2DSceneManager) {
        m_p2DSceneMgr = p2DSceneManager;
    }
    /**
     * 
     * @param p3DSceneManager
     */
    inline void set3DSceneManager(fgManagerBase *p3DSceneManager) {
        m_p3DSceneMgr = p3DSceneManager;
    }
    /**
     * 
     * @param pParticleSystem
     */
    inline void setParticleSystem(fgManagerBase *pParticleSystem) {
        m_pParticleMgr = pParticleSystem;
    }
    /**
     * 
     * @param pWidgetManager
     */
    inline void setWidgetManager(fgManagerBase *pWidgetManager) {
        m_pWidgetMgr = pWidgetManager;
    }
    /**
     * 
     * @param pStyleManager
     */
    inline void setStyleManager(fgManagerBase *pStyleManager) {
        m_pStyleMgr = pStyleManager;
    }
    /**
     * 
     * @param pSoundManager
     */
    inline void setSoundManager(fgManagerBase *pSoundManager) {
        m_pSoundMgr = pSoundManager;
    }

protected:
    /**
     * 
     */
    virtual void clear(void);

public:
    /**
     * 
     * @return 
     */
    virtual fgBool destroy(void);
    /**
     * 
     * @return 
     */
    virtual fgBool initialize(void);

public:
    #if defined(FG_USING_LUA_PLUS)
    /**
     * 
     * @return 
     */
    static LuaPlus::LuaState *getLuaState(void) {
        return m_luaState;
    }
    #endif
    /**
     * 
     * @return 
     */
    static lua_State *getCLuaState(void) {
        if(!m_luaState)
            return (lua_State *)NULL;
        return m_luaState->GetCState();
    }
    #if defined(FG_USING_LUA_PLUS)
    /**
     * 
     * @return 
     */
    static LuaPlus::LuaObject& getGlobals(void) {
        return m_globals;
    }
    #endif

protected:
    /**
     * 
     * @param state
     * @return 
     */
    template<class Type, fgScriptMetatables::METAID METATABLE_ID>
    static int simpleTypedMallocEvent(lua_State* L);

    /**
     * 
     * @param L
     * @return 
     */
    template<class Type>
    static int simpleTypedFreeGCEvent(lua_State* L);

    /**
     * 
     * @param state
     * @return 
     */
    template<class Type, fgScriptMetatables::METAID METATABLE_ID>
    static int simpleInPlaceTypedNewEvent(lua_State* L);

    /**
     * 
     * @param L
     * @return 
     */
    template<class Type>
    static int simpleInPlaceTypedGCEvent(lua_State* L);

    /**
     * 
     * @param L
     * @return 
     */
    static int simpleFreeGCEvent(lua_State* L);

    /**
     * 
     * @param L
     * @return 
     */
    template<class Type, fgScriptMetatables::METAID METATABLE_ID>
    static int managedObjectTypedNewEvent(lua_State *L);

    /**
     * 
     * @param L
     * @return 
     */
    template<class HandleType>
    static int managedObjectTypedGCEvent(lua_State* L);
    /**
     * 
     * @param L
     * @return 
     */
    static int managedResourceGCEvent(lua_State* L);
    /**
     * 
     * @param state
     * @return 
     */
    static int newResourceWrapper(lua_State *L);
    
    /**
     * 
     * @param L
     * @return 
     */
    static int addEventCallbackWrapper(lua_State *L);

    /**
     * 
     * @param systemData
     * @param userData
     * @return 
     */
    static fgBool managedObjectDestructorCallback(void *systemData, void *userData);

private:
    /**
     * 
     * @return 
     */
    fgBool registerConstants(void);
    /**
     * 
     * @return 
     */
    fgBool registerAdditionalTypes(void);
    /**
     * 
     * @return 
     */
    fgBool registerEventManager(void);
    /**
     * 
     * @return 
     */
    fgBool registerResourceManager(void);
    /**
     * 
     * @return
     */
    fgBool registerShaderManager(void);
    /**
     * 
     * @return
     */
    fgBool register2DSceneManager(void);
    /**
     * 
     * @return
     */
    fgBool register3DSceneManager(void);
    /**
     * 
     * @return
     */
    fgBool registerParticleSystem(void);
    /**
     * 
     * @return
     */
    fgBool registerWidgetManager(void);
    /**
     * 
     * @return
     */
    fgBool registerStyleManager(void);
    /**
     * 
     * @return
     */
    fgBool registerSoundManager(void);
};
/**
 * 
 * @param L
 * @return 
 */
template<class Type, fgScriptMetatables::METAID METATABLE_ID>
int fgScriptSubsystem::managedObjectTypedNewEvent(lua_State* L) {
    if(!L)
        return 1;
    #if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    LuaPlus::LuaStack args(state);
    if(!m_isBindingComplete) {
        LuaPlus::LuaObject nilObj = state->BoxPointer(0);
        nilObj.SetMetatable(LuaPlus::LuaObject());
        nilObj.AssignNil();
        return 1;
    }
    // Using new operator to create data
    Type *ptr = new Type();
    if(!ptr) {
        LuaPlus::LuaObject nilObj = state->BoxPointer(0);
        nilObj.SetMetatable(LuaPlus::LuaObject());
        nilObj.AssignNil();
        return 1;
    }
    LuaPlus::LuaObject newObj = state->BoxPointer(ptr);
    uintptr_t offset = (uintptr_t)ptr;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    FG_LOG_DEBUG("Script: Simple Typed New: ptr[%p], [offset=%lu]", ptr, offset);
    if(it == m_userDataObjectMap.end() && offset) {
        m_userDataObjectMap[offset] = newObj;
    }
    const char *metatableName = fgScriptMetatables::getMetatableName(METATABLE_ID);
    if(!metatableName) {
        newObj.SetMetatable(LuaPlus::LuaObject());
        FG_LOG_DEBUG("Script: Simple Typed New: metatable will be empty");
    } else {
        newObj.SetMetatable(state->GetRegistry()[metatableName]);
        FG_LOG_DEBUG("Script: Simple Typed New: metatable: id[%d], name[%s]", METATABLE_ID, metatableName);
        ptr->registerOnDestruct(&fgScriptSubsystem::managedObjectDestructorCallback, NULL);

    }
    #endif /* FG_USING_LUA_PLUS */
    return 1;
}
/**
 * 
 * @param L
 * @return 
 */
template<class HandleType>
int fgScriptSubsystem::managedObjectTypedGCEvent(lua_State* L) {
    if(!L)
        return 0;
    #if defined(FG_USING_LUA_PLUS)
    // Mainly for resources ?
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    //get the pointer lua is trying to delete.
    if(!state->IsUserdata(1)) {
        int isTable = (int)state->IsTable(1);
        int isNoneOrNil = (int)state->IsNoneOrNil(1);
        int isLightuserdata = (int)state->IsLightUserdata(1);
        int isUserdata = 0;
        FG_LOG_DEBUG("Script: Managed Object Typed GC: not compatible: lightuserdata[%d], userdata[%d], table[%d], none/nil[%d],  HandleType[%s]",
                     isLightuserdata,
                     isUserdata,
                     isTable,
                     isNoneOrNil,
                     HandleType::getTagName());

        return 0;
    }
    void *unboxed = state->UnBoxPointer(1);
    if(!unboxed) {
        FG_LOG_DEBUG("Script: Managed Object Typed GC: unboxed.ptr[%p]", unboxed);
        return 0;
    }
    typedef fgManagedObjectBase<HandleType> object_type;
    object_type *pManagedObject = (object_type *)unboxed;
    uintptr_t offset = (uintptr_t)pManagedObject;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it == m_userDataObjectMap.end()) {
        // The pointer is not registered
        FG_LOG_DEBUG("Script: Managed Object Typed GC: pointer is not registered: ptr[%p], [offset: %lu], HandleType[%s]", unboxed, offset, HandleType::getTagName());
        return 0;
    } else {
        m_userDataObjectMap.erase(it);
    }
    FG_LOG_DEBUG("Script: GC event for Managed Object: name[%s], HandleType[%s]", pManagedObject->getNameStr(), HandleType::getTagName());
    if(pManagedObject->isManaged() == FG_FALSE) {
        // Object is not managed in some manager
        // Can call destructors
        FG_LOG_DEBUG("Script: Managed Object Typed GC: Object is not managed, will be deleted name[%s], ptr[%p], offset[%lu]", pManagedObject->getNameStr(), pManagedObject, offset);
        delete pManagedObject;
    }
    #endif /* FG_USING_LUA_PLUS */
    return 0;
}
/**
 * 
 * @param L
 * @return 
 */
template<class Type, fgScriptMetatables::METAID METATABLE_ID>
int fgScriptSubsystem::simpleTypedMallocEvent(lua_State* L) {
    if(!L)
        return 1;
    #if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    LuaPlus::LuaStack args(state);
    if(!m_isBindingComplete) {
        LuaPlus::LuaObject nilObj = state->BoxPointer(0);
        nilObj.SetMetatable(LuaPlus::LuaObject());
        nilObj.AssignNil();
        return 1;
    }
    // This will not check for any arguments...
    // Simple allocation via fgMalloc
    Type *ptr = fgMalloc<Type>();
    if(!ptr) {
        LuaPlus::LuaObject nilObj = state->BoxPointer(0);
        nilObj.SetMetatable(LuaPlus::LuaObject());
        nilObj.AssignNil();
        return 1;
    }
    new (ptr)Type();
    LuaPlus::LuaObject newObj = state->BoxPointer(ptr);
    uintptr_t offset = (uintptr_t)ptr;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    FG_LOG_DEBUG("Script: Simple Typed Malloc: ptr[%p], offset[%lu]", ptr, offset);
    if(it == m_userDataObjectMap.end() && offset) {
        m_userDataObjectMap[offset] = newObj;
    }
    const char *metatableName = fgScriptMetatables::getMetatableName(METATABLE_ID);
    if(!metatableName) {
        newObj.SetMetatable(LuaPlus::LuaObject());
        FG_LOG_DEBUG("Script: Simple Typed Malloc: metatable will be empty");
    } else {
        newObj.SetMetatable(state->GetRegistry()[metatableName]);
        FG_LOG_DEBUG("Script: Simple Typed Malloc: metatable: id[%d], name[%s]", METATABLE_ID, metatableName);
    }
    #endif /* FG_USING_LUA_PLUS */
    return 1;
}
/**
 * 
 * @param L
 * @return 
 */
template<class Type>
int fgScriptSubsystem::simpleTypedFreeGCEvent(lua_State* L) {
    if(!L)
        return 0;
    #if defined(FG_USING_LUA_PLUS)
    // Mainly for resources ?
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    //get the pointer lua is trying to delete.
    if(!state->IsUserdata(1)) {
        int isTable = (int)state->IsTable(1);
        int isNoneOrNil = (int)state->IsNoneOrNil(1);
        int isLightuserdata = (int)state->IsLightUserdata(1);
        int isUserdata = 0;
        FG_LOG_DEBUG("Script: Simple Typed GC: not compatible: lightuserdata[%d], userdata[%d], table[%d], none/nil[%d]",
                     isLightuserdata,
                     isUserdata,
                     isTable,
                     isNoneOrNil);
        return 0;
    }
    void *unboxed = state->UnBoxPointer(1);
    if(!unboxed) {
        FG_LOG_DEBUG("Script: Simple Typed GC: unboxed.ptr[%p]", unboxed);
        return 0;
    }
    uintptr_t offset = (uintptr_t)unboxed;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it == m_userDataObjectMap.end()) {
        // The pointer is not registered
        FG_LOG_DEBUG("Script: Simple Typed GC: pointer is not registered: ptr[%p], offset[%lu]", unboxed, offset);
        return 0;
    } else {
        m_userDataObjectMap.erase(it);
    }
    FG_LOG_DEBUG("Script: Simple Typed GC: calling destructor, freeing memory: ptr[%p], offset[%lu]", unboxed, offset);
    Type *ptrObj = (Type *)unboxed;
    ptrObj->~Type();
    fgFree<Type>(ptrObj, FG_TRUE);
    #endif /* FG_USING_LUA_PLUS */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
/**
 * 
 * @param L
 * @return 
 */
template<class Type, fgScriptMetatables::METAID METATABLE_ID>
int fgScriptSubsystem::simpleInPlaceTypedNewEvent(lua_State* L) {
    if(!L)
        return 1;
    #if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    LuaPlus::LuaStack args(state);
    if(!m_isBindingComplete) {
        LuaPlus::LuaObject nilObj = state->BoxPointer(0);
        nilObj.SetMetatable(LuaPlus::LuaObject());
        nilObj.AssignNil();
        return 1;
    }
    // This will not check for any arguments...
    // Simple allocation via fgMalloc
    //    new (ptr)Type();
    LuaPlus::LuaObject newObj = state->NewUserdata(sizeof (Type));
    void *ptr = newObj.GetUserdata();
    if(!ptr) {
        newObj.SetMetatable(LuaPlus::LuaObject());
        newObj.AssignNil();
        return 1;
    }
    // Create constructor - creates object in specified memory holder (Lua side)
    new (ptr)Type();
    uintptr_t offset = (uintptr_t)ptr;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    FG_LOG_DEBUG("Script: Simple In Place Typed New: ptr[%p], offset[%lu]", ptr, offset);
    if(it == m_userDataObjectMap.end() && offset) {
        m_userDataObjectMap[offset] = newObj;
    }
    const char *metatableName = fgScriptMetatables::getMetatableName(METATABLE_ID);
    if(!metatableName) {
        newObj.SetMetatable(LuaPlus::LuaObject());
    } else {
        newObj.SetMetatable(state->GetRegistry()[metatableName]);
        FG_LOG_DEBUG("Script: Simple In Place Typed New: metatable: id[%d], name[%s]", METATABLE_ID, metatableName);
    }
    #endif /* FG_USING_LUA_PLUS */
    return 1;
}
/**
 * 
 * @param L
 * @return 
 */
template<class Type>
int fgScriptSubsystem::simpleInPlaceTypedGCEvent(lua_State* L) {
    if(!L)
        return 0;
    #if defined(FG_USING_LUA_PLUS)

    // Mainly for resources ?
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    //get the pointer lua is trying to delete.
    if(!state->IsUserdata(1)) {
        int isTable = (int)state->IsTable(1);
        int isNoneOrNil = (int)state->IsNoneOrNil(1);
        int isLightuserdata = (int)state->IsLightUserdata(1);
        int isUserdata = 0;
        FG_LOG_DEBUG("Script: Simple Typed GC: not compatible: lightuserdata[%d], userdata[%d], table[%d], none/nil[%d]",
                     isLightuserdata,
                     isUserdata,
                     isTable,
                     isNoneOrNil);
        return 0;
    }
    void *unboxed = state->UnBoxPointer(1);
    if(!unboxed) {
        FG_LOG_DEBUG("Script: Simple In Place Typed GC: unboxed.ptr[%p]", unboxed);
        return 0;
    }
    uintptr_t offset = (uintptr_t)unboxed;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it == m_userDataObjectMap.end()) {
        // The pointer is not registered
        FG_LOG_DEBUG("Script: Simple In Place Typed GC: pointer is not registered: ptr[%p], offset[%lu]", unboxed, offset);
        return 0;
    } else {
        m_userDataObjectMap.erase(it);
    }
    FG_LOG_DEBUG("Script: Simple In Place Typed GC: calling destructor: ptr[%p], offset[%lu]", unboxed, offset);
    Type *ptrObj = (Type *)unboxed;
    ptrObj->~Type();
    #endif /* FG_USING_LUA_PLUS */
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

    #undef _FG_SCRIPT_SUBSYSTEM_H_BLOCK_

#endif /* _FG_SCRIPT_SUBSYSTEM_H_ */
