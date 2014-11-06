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
        VECTOR2I_METATABLE_ID = 1, // #used
        VECTOR2F_METATABLE_ID = 2, // #used
        VECTOR3I_METATABLE_ID = 3, // #used
        VECTOR3F_METATABLE_ID = 4, // #used
        VECTOR4I_METATABLE_ID = 5, // #used
        VECTOR4F_METATABLE_ID = 6, // #used
        ERROR_METATABLE_ID = 7,
        EVENT_MANAGER_METATABLE_ID = 8,
        RESOURCE_MANAGER_METATABLE_ID = 9, // #used
        SHADER_MANAGER_METATABLE_ID = 10,
        SCENE2D_MANAGER_METATABLE_ID = 11,
        SCENE3D_MANAGER_METATABLE_ID = 12,
        PARTICLE_SYSTEM_METATABLE_ID = 13,
        WIDGET_MANAGER_METATABLE_ID = 14, // #used
        STYLE_MANAGER_METATABLE_ID = 15,
        SOUND_MANAGER_METATABLE_ID = 16,
        RESOURCE_METATABLE_ID = 17, // #used
        TEXTURE_RESOURCE_METATABLE_ID = 18, // #used
        FONT_RESOURCE_METATABLE_ID = 19, // #used
        GFX_MODEL_RESOURCE_METATABLE_ID = 20, // #used
        PARTICLE_EFFECT_RESOURCE_METATABLE_ID = 21, // #used
        SOUND_RESOURCE_METATABLE_ID = 22,
        MUSIC_RESOURCE_METATABLE_ID = 23,
        PLUGIN_RESOURCE_METATABLE_ID = 24,
        SAVE_FILE_RESOURCE_METATABLE_ID = 25,
        CONFIG_METATABLE_ID = 26,
        SETTINGS_METATABLE_ID = 27,
        GUI_WIDGET_METATABLE_ID = 28, // #used
        GUI_BUTTON_METATABLE_ID = 29, // #used
        GUI_CONSOLE_METATABLE_ID = 30, // #used
        GUI_CONTAINER_METATABLE_ID = 31, // #used
        GUI_FRAME_METATABLE_ID = 32, // #used
        GUI_LABEL_METATABLE_ID = 33, // #used
        GUI_LOADER_METATABLE_ID = 34, // #used
        GUI_MENU_METATABLE_ID = 35, // #used
        GUI_MESSAGE_BOX_METATABLE_ID = 36, // #used
        GUI_POPUP_METATABLE_ID = 37, // #used
        GUI_PROGRESS_BAR_METATABLE_ID = 38, // #used
        GUI_SCROLL_AREA_METATABLE_ID = 39, // #used
        GUI_STYLE_METATABLE_ID = 40, // base style meta
        GUI_STYLE_CONTENT_METATABLE_ID = 41,
        GUI_STYLE_SIZE_METATABLE_ID = 42,
        GUI_STYLE_BACKGROUND_METATABLE_ID = 43,
        GUI_STYLE_FOREGROUND_METATABLE_ID = 44,
        GUI_STYLE_MARGIN_METATABLE_ID = 45,
        //GUI_STYLE_PADDING_METATABLE_ID = 45, // this is the same as margin
        GUI_STYLE_BORDER_INFO_METATABLE_ID = 46,
        GUI_STYLE_BORDER_METATABLE_ID = 46,
        GUI_STYLE_POSITION_METATABLE_ID = 47,
        //GUI_STYLE_ALIGN_METATABLE_ID = XX, // this is enum ...
        GUI_TABLE_METATABLE_ID = 48, // #used
        GUI_TEXT_AREA_METATABLE_ID = 49, // #used
        GUI_TOGGLE_BUTTON_METATABLE_ID = 50, // #used
        GUI_WINDOW_METATABLE_ID = 51, // #used

        METATABLE_SIZE
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
        unsigned short int id;
        ///
        char name[NAME_MAX_LENGTH];
        /**
         * 
         */
        metatableInfo() : id(0) {
            randomizeName();
            //FG_LOG_DEBUG("Script: metatableInfo: name: '%s'", name);
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
         * @param _name
         */
        metatableInfo(const char *_name) : id(0) {
            if(_name)
                strncpy(name, _name, (int)NAME_MAX_LENGTH);
            else
                memset(name, 0, (int)NAME_MAX_LENGTH);
        }
        /**
         * 
         * @param prefix
         * @param suffix
         */
        metatableInfo(const char *prefix, const char *suffix) : id(0) {
            randomizeName(prefix, suffix);
            //FG_LOG_DEBUG("Script: metatableInfo: name: '%s'", name);

        }
        /**
         * 
         * @param _id
         * @param prefix
         * @param suffix
         */
        metatableInfo(const unsigned short int _id, const char *prefix, const char *suffix) : id(_id) {
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
    typedef fgVector<metatableInfo> scriptMetatableInfoVec;
    ///
    typedef scriptMetatableInfoVec::iterator scriptMetatableInfoVecItor;

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
    static scriptMetatableInfoVec m_scriptMetatableInfoVec;

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
    static inline const char *getMetatableName(const unsigned short int metatableID) {
        const char *failedName = "__NO_B33F_";
        if(m_scriptMetatableInfoVec.empty())
            return failedName; // #FIXME
        if(metatableID >= m_scriptMetatableInfoVec.size())
            return failedName;
        return m_scriptMetatableInfoVec[metatableID].name;
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
    FG_LOG_DEBUG("Script: Simple Typed New: ptr[%p], [offset=%lu]", ptr, offset);
    if(it == m_userDataObjectMap.end() && offset) {
        m_userDataObjectMap[offset] = newObj;
    }
    const char *metatableName = getMetatableName(METATABLE_ID);
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
    FG_LOG_DEBUG("Script: Simple Typed Malloc: ptr[%p], offset[%lu]", ptr, offset);
    if(it == m_userDataObjectMap.end() && offset) {
        m_userDataObjectMap[offset] = newObj;
    }
    const char *metatableName = getMetatableName(METATABLE_ID);
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
    FG_LOG_DEBUG("Script: Simple In Place Typed New: ptr[%p], offset[%lu]", ptr, offset);
    if(it == m_userDataObjectMap.end() && offset) {
        m_userDataObjectMap[offset] = newObj;
    }
    const char *metatableName = getMetatableName(METATABLE_ID);
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

    #if defined(FG_USING_LUA_PLUS)

namespace LPCD {

    /***************************************************************************
     * FG VECTOR 2I
     **************************************************************************/

    template<> struct Type<fgVector2i> {
        static inline void Push(lua_State* L, const fgVector2i& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgVector2i]", ptr, (uintptr_t)ptr);
        #endif
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
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgVector2f]", ptr, (uintptr_t)ptr);
        #endif
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
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgVector3i]", ptr, (uintptr_t)ptr);
        #endif
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
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgVector3f]", ptr, (uintptr_t)ptr);
        #endif
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
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgVector4i]", ptr, (uintptr_t)ptr);
        #endif
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
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgVector4f]", ptr, (uintptr_t)ptr);
        #endif
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

    /***************************************************************************
     * fgGuiWidget pointer parameter *
     **************************************************************************/

    template<> struct Type<fgGuiWidget *> {
        static inline void Push(lua_State* L, const fgGuiWidget * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
            // Can check the pointer (offset) and instead of creating new object
            // (BoxPointer) simply push already existing pointer
            // Maybe create something like universal Push?
            fgScriptSubsystem::METAID metaID = fgScriptSubsystem::getMetatableIDFromWidgetType(value);
            const char *metatableName = fgScriptSubsystem::getMetatableName(metaID);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], name[%s], type_name[%s]", value, (uintptr_t)value, value->getNameStr(), value->getTypeNameStr());
        #endif
            // This wont work - this simply packs widget that will have
            // unregistered pointer / need to add some wrapper over this
            // lua side object __GC callback will exit without doing anything
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            bool result = (obj.GetMetatable() == state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::GUI_WIDGET_METATABLE_ID)]);
            // This is fubar
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

    ////////////////////////////////////////////////////////////////////////////
    // FG GUI STYLE STRUCTURES
    ////////////////////////////////////////////////////////////////////////////

    /***************************************************************************
     * fgGuiStyleContent pointer parameter *
     **************************************************************************/

    template<> struct Type<fgGuiStyleContent *> {
        static inline void Push(lua_State* L, const fgGuiStyleContent * value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->BoxPointer((void*)value);
            // Can check the pointer (offset) and instead of creating new object
            // (BoxPointer) simply push already existing pointer
            // Maybe create something like universal Push?
            fgScriptSubsystem::METAID metaID = fgScriptSubsystem::GUI_STYLE_CONTENT_METATABLE_ID;
            const char *metatableName = fgScriptSubsystem::getMetatableName(metaID);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgGuiStyleContent]", value, (uintptr_t)value);
        #endif
            // This wont work - this simply packs widget that will have
            // unregistered pointer / need to add some wrapper over this
            // lua side object __GC callback will exit without doing anything
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            bool result = (obj.GetMetatable() == state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::GUI_STYLE_CONTENT_METATABLE_ID)]);
            // This is fubar
            //result = (bool) obj.IsUserdata();
            return result;
        }
        static inline fgGuiStyleContent * Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            fgGuiStyleContent *pStyleContent = (fgGuiStyleContent *)state->UnBoxPointer(idx);
            return pStyleContent;
        }
    };

    template<> struct Type<fgGuiStyleContent *&> : public Type<fgGuiStyleContent *> {
    };

    template<> struct Type<const fgGuiStyleContent *&> : public Type<fgGuiStyleContent *> {
    };
    
    /***************************************************************************
     * FG GUI SIZE STRUCTURE
     **************************************************************************/

    template<> struct Type<fgGuiSize> {
        static inline void Push(lua_State* L, const fgGuiSize& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgGuiSize]", ptr, (uintptr_t)ptr);
        #endif
            const char *metatableName = fgScriptSubsystem::getMetatableName(fgScriptSubsystem::GUI_STYLE_SIZE_METATABLE_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::GUI_STYLE_SIZE_METATABLE_ID)];
        }
        static inline fgGuiSize Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgGuiSize*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgGuiSize&> : public Type<fgGuiSize> {
    };

    template<> struct Type<const fgGuiSize&> : public Type<fgGuiSize> {
    };

    /***************************************************************************
     * FG GUI BACKGROUND STRUCTURE
     **************************************************************************/

    template<> struct Type<fgGuiBackground> {
        static inline void Push(lua_State* L, const fgGuiBackground& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgGuiBackground]", ptr, (uintptr_t)ptr);
            //FG_LOG_DEBUG("Script: LPCD Push: type_name[fgGuiBackground], color[%.2f %.2f %.2f %.2f]", value.color.r, value.color.g, value.color.b, value.color.a);
        #endif
            const char *metatableName = fgScriptSubsystem::getMetatableName(fgScriptSubsystem::GUI_STYLE_BACKGROUND_METATABLE_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::GUI_STYLE_BACKGROUND_METATABLE_ID)];
        }
        static inline fgGuiBackground Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgGuiBackground*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgGuiBackground&> : public Type<fgGuiBackground> {
    };

    template<> struct Type<const fgGuiBackground&> : public Type<fgGuiBackground> {
    };

    /***************************************************************************
     * FG GUI FOREGROUND STRUCTURE
     **************************************************************************/

    template<> struct Type<fgGuiForeground> {
        static inline void Push(lua_State* L, const fgGuiForeground& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgGuiForeground]", ptr, (uintptr_t)ptr);
        #endif
            const char *metatableName = fgScriptSubsystem::getMetatableName(fgScriptSubsystem::GUI_STYLE_FOREGROUND_METATABLE_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::GUI_STYLE_FOREGROUND_METATABLE_ID)];
        }
        static inline fgGuiForeground Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgGuiForeground*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgGuiForeground&> : public Type<fgGuiForeground> {
    };

    template<> struct Type<const fgGuiForeground&> : public Type<fgGuiForeground> {
    };

    /***************************************************************************
     * FG GUI MARGIN/PADDING STRUCTURE
     **************************************************************************/

    template<> struct Type<fgGuiMargin> {
        static inline void Push(lua_State* L, const fgGuiMargin& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgGuiMargin]", ptr, (uintptr_t)ptr);
        #endif
            const char *metatableName = fgScriptSubsystem::getMetatableName(fgScriptSubsystem::GUI_STYLE_MARGIN_METATABLE_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::GUI_STYLE_MARGIN_METATABLE_ID)];
        }
        static inline fgGuiMargin Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgGuiMargin*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgGuiMargin&> : public Type<fgGuiMargin> {
    };

    template<> struct Type<const fgGuiMargin&> : public Type<fgGuiMargin> {
    };

    /***************************************************************************
     * FG GUI BORDER INFO STRUCTURE
     **************************************************************************/

    template<> struct Type<fgGuiBorderInfo> {
        static inline void Push(lua_State* L, const fgGuiBorderInfo& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgGuiBorderInfo]", ptr, (uintptr_t)ptr);
        #endif
            const char *metatableName = fgScriptSubsystem::getMetatableName(fgScriptSubsystem::GUI_STYLE_BORDER_INFO_METATABLE_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::GUI_STYLE_BORDER_INFO_METATABLE_ID)];
        }
        static inline fgGuiBorderInfo Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgGuiBorderInfo*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgGuiBorderInfo&> : public Type<fgGuiBorderInfo> {
    };

    template<> struct Type<const fgGuiBorderInfo&> : public Type<fgGuiBorderInfo> {
    };

    /***************************************************************************
     * FG GUI BORDER STRUCTURE
     **************************************************************************/

    template<> struct Type<fgGuiBorder> {
        static inline void Push(lua_State* L, const fgGuiBorder& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgGuiBorder]", ptr, (uintptr_t)ptr);
        #endif
            const char *metatableName = fgScriptSubsystem::getMetatableName(fgScriptSubsystem::GUI_STYLE_BORDER_METATABLE_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::GUI_STYLE_BORDER_METATABLE_ID)];
        }
        static inline fgGuiBorder Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgGuiBorder*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgGuiBorder&> : public Type<fgGuiBorder> {
    };

    template<> struct Type<const fgGuiBorder&> : public Type<fgGuiBorder> {
    };

    /***************************************************************************
     * FG GUI POSITION STRUCTURE
     **************************************************************************/

    template<> struct Type<fgGuiPosition> {
        static inline void Push(lua_State* L, const fgGuiPosition& value) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            void *ptr = (void*)&value;
            LuaPlus::LuaObject obj = state->BoxPointer(ptr);
        #if defined(FG_DEBUG)
            FG_LOG_DEBUG("Script: LPCD Push: ptr[%p], offset[%lu], type_name[fgGuiPosition]", ptr, (uintptr_t)ptr);
        #endif
            const char *metatableName = fgScriptSubsystem::getMetatableName(fgScriptSubsystem::GUI_STYLE_POSITION_METATABLE_ID);
            obj.SetMetatable(state->GetRegistry()[metatableName]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            LuaPlus::LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()[fgScriptSubsystem::getMetatableName(fgScriptSubsystem::GUI_STYLE_POSITION_METATABLE_ID)];
        }
        static inline fgGuiPosition Get(lua_State* L, int idx) {
            LuaPlus::LuaState* state = lua_State_to_LuaState(L);
            return *(fgGuiPosition*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgGuiPosition&> : public Type<fgGuiPosition> {
    };

    template<> struct Type<const fgGuiPosition&> : public Type<fgGuiPosition> {
    };

    /***************************************************************************
     * FG GUI ENUMERATION TYPES -> INT
     **************************************************************************/

    template<> struct Type<fgGuiUnitType> : public Type<int> {
        static inline fgGuiUnitType Get(lua_State* L, int idx) {
            return (fgGuiUnitType)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgGuiUnitType&> : public Type<fgGuiUnitType> {
    };

    template<> struct Type<const fgGuiUnitType&> : public Type<fgGuiUnitType> {
    };

    ////////////////////////////////////////////////////////////////////////////
    
    template<> struct Type<fgGuiBorderStyle> : public Type<int> {
        static inline fgGuiBorderStyle Get(lua_State* L, int idx) {
            return (fgGuiBorderStyle)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgGuiBorderStyle&> : public Type<fgGuiBorderStyle> {
    };

    template<> struct Type<const fgGuiBorderStyle&> : public Type<fgGuiBorderStyle> {
    };
    
    ////////////////////////////////////////////////////////////////////////////
    
    template<> struct Type<fgGuiBorderWhich> : public Type<int> {
        static inline fgGuiBorderWhich Get(lua_State* L, int idx) {
            return (fgGuiBorderWhich)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgGuiBorderWhich&> : public Type<fgGuiBorderWhich> {
    };

    template<> struct Type<const fgGuiBorderWhich&> : public Type<fgGuiBorderWhich> {
    };

    ////////////////////////////////////////////////////////////////////////////
    
    template<> struct Type<fgGuiBackgroundStyle> : public Type<int> {
        static inline fgGuiBackgroundStyle Get(lua_State* L, int idx) {
            return (fgGuiBackgroundStyle)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgGuiBackgroundStyle&> : public Type<fgGuiBackgroundStyle> {
    };

    template<> struct Type<const fgGuiBackgroundStyle&> : public Type<fgGuiBackgroundStyle> {
    };

    ////////////////////////////////////////////////////////////////////////////
    
    template<> struct Type<fgGuiMarginWhich> : public Type<int> {
        static inline fgGuiMarginWhich Get(lua_State* L, int idx) {
            return (fgGuiMarginWhich)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgGuiMarginWhich&> : public Type<fgGuiMarginWhich> {
    };

    template<> struct Type<const fgGuiMarginWhich&> : public Type<fgGuiMarginWhich> {
    };

    ////////////////////////////////////////////////////////////////////////////
    
    template<> struct Type<fgGuiPaddingWhich> : public Type<int> {
        static inline fgGuiPaddingWhich Get(lua_State* L, int idx) {
            return (fgGuiPaddingWhich)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgGuiPaddingWhich&> : public Type<fgGuiPaddingWhich> {
    };

    template<> struct Type<const fgGuiPaddingWhich&> : public Type<fgGuiPaddingWhich> {
    };

    ////////////////////////////////////////////////////////////////////////////
    
    template<> struct Type<fgGuiAlign> : public Type<int> {
        static inline fgGuiAlign Get(lua_State* L, int idx) {
            return (fgGuiAlign)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgGuiAlign&> : public Type<fgGuiAlign> {
    };

    template<> struct Type<const fgGuiAlign&> : public Type<fgGuiAlign> {
    };

    ////////////////////////////////////////////////////////////////////////////

    template<> struct Type<fgGuiPositionStyle> : public Type<int> {
        static inline fgGuiPositionStyle Get(lua_State* L, int idx) {
            return (fgGuiPositionStyle)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgGuiPositionStyle&> : public Type<fgGuiPositionStyle> {
    };

    template<> struct Type<const fgGuiPositionStyle&> : public Type<fgGuiPositionStyle> {
    };
    
    ////////////////////////////////////////////////////////////////////////////

    template<> struct Type<fgGuiSizeStyle> : public Type<int> {
        static inline fgGuiSizeStyle Get(lua_State* L, int idx) {
            return (fgGuiSizeStyle)Type<int>::Get(L, idx);
        }
    };

    template<> struct Type<fgGuiSizeStyle&> : public Type<fgGuiSizeStyle> {
    };

    template<> struct Type<const fgGuiSizeStyle&> : public Type<fgGuiSizeStyle> {
    };

    ////////////////////////////////////////////////////////////////////////////
}

    #endif /* FG_USING_LUA_PLUS */

////////////////////////////////////////////////////////////////////////////////

#endif /* _FG_SCRIPT_SUBSYSTEM_H_ */
