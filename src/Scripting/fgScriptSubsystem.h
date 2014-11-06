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

    #include "fgBuildConfig.h"
    #include "fgScriptResource.h" // #FIXME

    #include "fgManagerBase.h"

    #include "GFX/fgGFXTypes.h"
    #include "GFX/Textures/fgTextureResource.h"

    #include "GUI/fgGuiWidget.h"
    #include "Util/fgMemory.h"

    #define FG_MANAGER_SCRIPT       0x00004000
    #define FG_SUBSYSTEM_SCRIPT     0x00004000

    #if defined(FG_USING_LUA_PLUS)
        #include "LuaPlus/LuaPlus.h"
    #endif

    #if !defined(FG_USING_LUA) && !defined(FG_USING_LUA_PLUS)

struct lua_State {
    void *_ptr;
};
    #endif

    #include <map>


    #if defined(FG_USING_LUA_PLUS)
/*
namespace LPCD {

    template<> struct Type<fgTextureResource *> {
        static inline void Push(lua_State* L, const fgTextureResource *& value) {
            LuaState* state = lua_State_to_LuaState(L);
            LuaObject obj = state->BoxPointer((void*)&value);
            obj.SetMetatable(state->GetRegistry()["fgTextureResourceMETATABLE"]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaState* state = lua_State_to_LuaState(L);
            LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()["fgTextureResourceMETATABLE"];
        }
        static inline fgTextureResource *Get(lua_State* L, int idx) {
            LuaState* state = lua_State_to_LuaState(L);
            return (fgTextureResource *)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgVector3f&> : public Type<fgVector3f> {
    };

    template<> struct Type<const fgVector3f&> : public Type<fgVector3f> {
    };
}
 */
    #endif /* FG_USING_LUA_PLUS */

/**
 * 
 */
class fgScriptSubsystem : public fgManagerBase {
public:

    enum METAID {
        EMPTY_METATABLE_ID = 0,
        VECTOR2I_METATABLE_ID = 1,
        VECTOR2F_METATABLE_ID = 2,
        VECTOR3I_METATABLE_ID = 3,
        VECTOR3F_METATABLE_ID = 4,
        VECTOR4I_METATABLE_ID = 5,
        VECTOR4F_METATABLE_ID = 6,
        ERROR_METATABLE_ID = 7,
        EVENT_MANAGER_METATABLE_ID = 8,
        RESOURCE_MANAGER_METATABLE_ID = 9,
        SHADER_MANAGER_METATABLE_ID = 10,
        SCENE2D_MANAGER_METATABLE_ID = 11,
        SCENE3D_MANAGER_METATABLE_ID = 12,
        PARTICLE_SYSTEM_METATABLE_ID = 13,
        WIDGET_MANAGER_METATABLE_ID = 14,
        STYLE_MANAGER_METATABLE_ID = 15,
        SOUND_MANAGER_METATABLE_ID = 16,
        RESOURCE_METATABLE_ID = 17,
        TEXTURE_RESOURCE_METATABLE_ID = 18,
        FONT_RESOURCE_METATABLE_ID = 19,
        GFX_MODEL_RESOURCE_METATABLE_ID = 20,
        PARTICLE_EFFECT_RESOURCE_METATABLE_ID = 21,
        SOUND_RESOURCE_METATABLE_ID = 22,
        MUSIC_RESOURCE_METATABLE_ID = 23,
        PLUGIN_RESOURCE_METATABLE_ID = 24,
        SAVE_FILE_RESOURCE_METATABLE_ID = 25,
        CONFIG_METATABLE_ID = 26,
        SETTINGS_METATABLE_ID = 27,
        GUI_WIDGET_METATABLE_ID = 28,
        GUI_BUTTON_METATABLE_ID = 29,
        GUI_CONSOLE_METATABLE_ID = 30,
        GUI_CONTAINER_METATABLE_ID = 31,
        GUI_FRAME_METATABLE_ID = 32,
        GUI_LABEL_METATABLE_ID = 33,
        GUI_LOADER_METATABLE_ID = 34,
        GUI_MENU_METATABLE_ID = 35,
        GUI_MESSAGE_BOX_METATABLE_ID = 36,
        GUI_POPUP_METATABLE_ID = 37,
        GUI_PROGRESS_BAR_METATABLE_ID = 38,
        GUI_SCROLL_AREA_METATABLE_ID = 39,
        GUI_STYLE_METATABLE_ID = 40,
        GUI_STYLE_CONTENT_METATABLE_ID = 41,
        GUI_TABLE_METATABLE_ID = 42,
        GUI_TEXT_AREA_METATABLE_ID = 43,
        GUI_TOGGLE_BUTTON_METATABLE_ID = 44,
        GUI_WINDOW_METATABLE_ID = 45
    };
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

    /**
     * 
     */
    struct metatableInfo {
        ///
        static const unsigned char NAME_MAX_LENGTH = 24;
        ///
        int id;
        ///
        char name[NAME_MAX_LENGTH];
        /**
         * 
         */
        metatableInfo() : id(0) {
            randomizeName();
        }
        /**
         * 
         * @param _id
         * @param _name
         */
        metatableInfo(const int _id, const char *_name) : id(_id) {
            if(_name)
                strncpy(name, _name, (int)NAME_MAX_LENGTH);
            else
                memset(name, 0, (int)NAME_MAX_LENGTH);
        }
        /**
         * 
         * @param _id
         * @param prefix
         * @param suffix
         */
        metatableInfo(const int _id, const char *prefix, const char *suffix) : id(_id) {
            randomizeName(prefix, suffix);
        }
        /**
         * 
         * @param prefix
         * @param suffix
         */
        char* randomizeName(const char *prefix = NULL, const char *suffix = NULL) {
            if(!name)
                return name;
            memset(name, 0, (int)NAME_MAX_LENGTH);
            int i = 0, j = 0, suflen = 0, limit = NAME_MAX_LENGTH - 1;
            // Numbers 0 - 9 ASCII 48 to 57
            // Uppercase letters A - Z ASCII 65 - 90
            // Lowercase letters a - z ASCII 97 to 122
            int _n[2] = {48, 57};
            int _u[2] = {65, 90};
            int _l[2] = {97, 122};
            int *_c[3] = {_n, _u, _l};
            if(prefix) {
                sprintf(name, "%s", prefix);
                i = strlen(name);
            } else {
                // without prefix need to ensure that beginning is alpha
                for(; i < 3; i++) {
                    j = 1;
                    name[i] = (char)FG_RAND(_c[j][0], _c[j][1]);
                }
            }
            name[i] = '_', i++;
            if(suffix) {
                suflen = (int)strlen(suffix);
                limit -= suflen;
            } else {
                limit++;
            }
            for(; i < limit - 1; i++) {
                j = FG_RAND(0, 2);
                name[i] = (char)FG_RAND(_c[j][0], _c[j][1]);
            }
            if(suffix) {
                name[i] = '_', i++;
                for(j = 0; i < NAME_MAX_LENGTH - 1 && j < suflen; i++, j++) {
                    name[i] = suffix[j];
                }
            }
            return name;
        }
    };

    ///
    typedef std::map<unsigned short, metatableInfo> scriptMetatableInfoMap;
    ///
    typedef scriptMetatableInfoMap::iterator scriptMetatableInfoMapItor;

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
    ///
    static scriptMetatableInfoMap m_scriptMetatableInfoMap;

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
     * @param metatableID
     * @return 
     */
    static const char *getMetatableName(const unsigned short metatableID) {
        const char *failedName = "__NO_B33F_";
        if(m_scriptMetatableInfoMap.empty())
            return failedName; // #FIXME

        scriptMetatableInfoMapItor it = m_scriptMetatableInfoMap.find(metatableID);
        if(it == m_scriptMetatableInfoMap.end())
            return failedName;
        return (*it).second.name;
    }
    
    // #FIXME - FOOBBAR!@
    static METAID getMetatableIDFromWidgetType(const fgGuiWidget *pWidget);

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
    template<class Type, METAID METATABLE_ID>
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
    template<class Type, METAID METATABLE_ID>
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
    template<class Type, METAID METATABLE_ID>
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
template<class Type, fgScriptSubsystem::METAID METATABLE_ID>
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
    FG_LOG::PrintDebug("Script: Simple Typed New, pointer: %p [offset=%lu]", ptr, offset);
    if(it == m_userDataObjectMap.end() && offset) {
        m_userDataObjectMap[offset] = newObj;
    }
    const char *metatableName = getMetatableName(METATABLE_ID);
    if(!metatableName) {
        newObj.SetMetatable(LuaPlus::LuaObject());
    } else {
        newObj.SetMetatable(state->GetRegistry()[metatableName]);
        FG_LOG::PrintDebug("Script: Setting metatable.%d=[%s]", METATABLE_ID, metatableName);
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
    if(!state->IsUserdata(1))
        return 0;
    void *unboxed = state->UnBoxPointer(1);
    if(!unboxed)
        return 0;
    typedef fgManagedObjectBase<HandleType> object_type;
    object_type *pManagedObject = (object_type *)unboxed;
    uintptr_t offset = (uintptr_t)pManagedObject;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it == m_userDataObjectMap.end()) {
        // The pointer is not registered
        FG_LOG::PrintDebug("Managed Object Typed GC: pointer is not registered %p [offset: %lu]", unboxed, offset);
        return 0;
    } else {
        m_userDataObjectMap.erase(it);
    }
    FG_LOG::PrintDebug("Script: GC event for Managed Object: '%s'", pManagedObject->getNameStr());
    if(pManagedObject->isManaged() == FG_FALSE) {
        // Object is not managed in some manager
        // Can call destructors
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
template<class Type, fgScriptSubsystem::METAID METATABLE_ID>
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
    FG_LOG::PrintDebug("Script: Simple Typed malloc, pointer: %p [offset=%lu]", ptr, offset);
    if(it == m_userDataObjectMap.end() && offset) {
        m_userDataObjectMap[offset] = newObj;
    }
    const char *metatableName = getMetatableName(METATABLE_ID);
    if(!metatableName) {
        newObj.SetMetatable(LuaPlus::LuaObject());
    } else {
        newObj.SetMetatable(state->GetRegistry()[metatableName]);
        FG_LOG::PrintDebug("Script: Setting metatable.%d=[%s]", METATABLE_ID, metatableName);
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
    if(!state->IsUserdata(1))
        return 0;
    void *unboxed = state->UnBoxPointer(1);
    if(!unboxed)
        return 0;
    uintptr_t offset = (uintptr_t)unboxed;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it == m_userDataObjectMap.end()) {
        // The pointer is not registered
        FG_LOG::PrintDebug("Simple Typed GC: pointer is not registered %p [offset: %lu]", unboxed, offset);
        return 0;
    } else {
        m_userDataObjectMap.erase(it);
    }
    FG_LOG::PrintDebug("Simple Typed GC: called destructor, freeing memory %p [offset: %lu]", unboxed, offset);
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
template<class Type, fgScriptSubsystem::METAID METATABLE_ID>
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
    FG_LOG::PrintDebug("Script: Simple typed in place  allocation, pointer: %p [offset=%lu]", ptr, offset);
    if(it == m_userDataObjectMap.end() && offset) {
        m_userDataObjectMap[offset] = newObj;
    }
    const char *metatableName = getMetatableName(METATABLE_ID);
    if(!metatableName) {
        newObj.SetMetatable(LuaPlus::LuaObject());
    } else {
        newObj.SetMetatable(state->GetRegistry()[metatableName]);
        FG_LOG::PrintDebug("Script: Setting metatable.%d=[%s]", METATABLE_ID, metatableName);
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
    if(!state->IsUserdata(1))
        return 0;
    void *unboxed = state->UnBoxPointer(1);
    if(!unboxed) {
        FG_LOG::PrintDebug("Simple typed in place GC: unboxed pointer is [%p]", unboxed);
        return 0;
    }
    uintptr_t offset = (uintptr_t)unboxed;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it == m_userDataObjectMap.end()) {
        // The pointer is not registered
        FG_LOG::PrintDebug("Simple typed in place GC: pointer is not registered %p [offset: %lu]", unboxed, offset);
        return 0;
    } else {
        m_userDataObjectMap.erase(it);
    }
    FG_LOG::PrintDebug("Simple typed in place GC: called destructor on memory %p [offset: %lu]", unboxed, offset);
    Type *ptrObj = (Type *)unboxed;
    ptrObj->~Type();
    #endif /* FG_USING_LUA_PLUS */
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

    #if defined(FG_USING_LUA_PLUS)

namespace LPCD {

    /***************************************************************************
     * FG VECTOR 2I
     **************************************************************************/

    template<> struct Type<fgVector2i> {
        static inline void Push(lua_State* L, const fgVector2i& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)&value);
            obj.SetMetatable(state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::VECTOR2I_METATABLE_ID)]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::VECTOR2I_METATABLE_ID)];
        }
        static inline fgVector2i Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgVector2i*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgVector2i&> : public Type<fgVector2i> {
    };

    template<> struct Type<const fgVector2i&> : public Type<fgVector2i> {
    };

    /***************************************************************************
     * FG VECTOR 2F
     **************************************************************************/

    template<> struct Type<fgVector2f> {
        static inline void Push(lua_State* L, const fgVector2f& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)&value);
            obj.SetMetatable(state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::VECTOR2F_METATABLE_ID)]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::VECTOR2F_METATABLE_ID)];
        }
        static inline fgVector2f Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            fgVector2f* ptr = (fgVector2f *)state->UnBoxPointer(idx);
            return *ptr;
        }
    };

    template<> struct Type<fgVector2f&> : public Type<fgVector2f> {
    };

    template<> struct Type<const fgVector2f&> : public Type<fgVector2f> {
    };

    /***************************************************************************
     * FG VECTOR 3I
     **************************************************************************/

    template<> struct Type<fgVector3i> {
        static inline void Push(lua_State* L, const fgVector3i& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)&value);
            obj.SetMetatable(state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::VECTOR3I_METATABLE_ID)]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::VECTOR3I_METATABLE_ID)];
        }
        static inline fgVector3i Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgVector3i*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgVector3i&> : public Type<fgVector3i> {
    };

    template<> struct Type<const fgVector3i&> : public Type<fgVector3i> {
    };

    /***************************************************************************
     * FG VECTOR 3F
     **************************************************************************/

    template<> struct Type<fgVector3f> {
        static inline void Push(lua_State* L, const fgVector3f& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)&value);
            obj.SetMetatable(state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::VECTOR3F_METATABLE_ID)]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::VECTOR3F_METATABLE_ID)];
        }
        static inline fgVector3f Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgVector3f*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgVector3f&> : public Type<fgVector3f> {
    };

    template<> struct Type<const fgVector3f&> : public Type<fgVector3f> {
    };

    /***************************************************************************
     * FG VECTOR 4I
     **************************************************************************/

    template<> struct Type<fgVector4i> {
        static inline void Push(lua_State* L, const fgVector4i& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)&value);
            obj.SetMetatable(state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::VECTOR4I_METATABLE_ID)]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::VECTOR4I_METATABLE_ID)];
        }
        static inline fgVector4i Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgVector4i*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgVector4i&> : public Type<fgVector4i> {
    };

    template<> struct Type<const fgVector4i&> : public Type<fgVector4i> {
    };

    /***************************************************************************
     * FG VECTOR 4F
     **************************************************************************/

    template<> struct Type<fgVector4f> {
        static inline void Push(lua_State* L, const fgVector4f& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)&value);
            obj.SetMetatable(state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::VECTOR4F_METATABLE_ID)]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::VECTOR4F_METATABLE_ID)];
        }
        static inline fgVector4f Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgVector4f*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgVector4f&> : public Type<fgVector4f> {
    };

    template<> struct Type<const fgVector4f&> : public Type<fgVector4f> {
    };
}

////////////////////////////////////////////////////////////////////////////////

namespace LPCD {

    template<> struct Type<std::string> {
        static inline void Push(lua_State* L, const std::string& value) {
            lua_pushstring(L, value.c_str());
        }
        static inline bool Match(lua_State* L, int idx) {
            return lua_type(L, idx) == LUA_TSTRING;
        }
        static inline std::string Get(lua_State* L, int idx) {
            return lua_tostring(L, idx);
        }
    };

    template<> struct Type<std::string&> : public Type<std::string> {
    };

    template<> struct Type<const std::string&> : public Type<std::string> {
    };

    //
    // fgGuiWidget pointer parameter *
    //

    template<> struct Type<fgGuiWidget *> {
        static inline void Push(lua_State* L, const fgGuiWidget * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);            
            fgScriptSubsystem::METAID metaID = fgScriptSubsystem::getMetatableIDFromWidgetType(value);
            const char *metatableName = fgScriptSubsystem::getMetatableName(metaID);
            FG_LOG::PrintDebug("Script: LPCD Push: pointer: %p [offset=%lu] [widget: %s][%s]", value, (uintptr_t)value, value->getNameStr(), value->getTypeNameStr());
            // This wont work - this simply packs widget that will have
            // unregistered pointer / need to add some wrapper over this
            // lua side object __GC callback will exit without doing anything
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            bool result = (obj.GetMetatable() == state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::GUI_WIDGET_METATABLE_ID)]);
            // This is foobar
            result = (bool) obj.IsUserdata();
            return result;
        }
        static inline fgGuiWidget * Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            fgGuiWidget *pWidget = (fgGuiWidget *)state->UnBoxPointer(idx);
            return pWidget;
        }
    };

    template<> struct Type<fgGuiWidget *&> : public Type<fgGuiWidget *> {
    };

    template<> struct Type<const fgGuiWidget *&> : public Type<fgGuiWidget *> {
    };
}

    #endif /* FG_USING_LUA_PLUS */

////////////////////////////////////////////////////////////////////////////////

#endif /* _FG_SCRIPT_SUBSYSTEM_H_ */
