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
namespace LPCD {

    template<> struct Type<fgVector3f> {
        static inline void Push(lua_State* L, const fgVector3f& value) {
            LuaState* state = lua_State_to_LuaState(L);
            LuaObject obj = state->BoxPointer((void*)&value);
            obj.SetMetatable(state->GetRegistry()["fgVector3fMETATABLE"]);
        }
        static inline bool Match(lua_State* L, int idx) {
            LuaState* state = lua_State_to_LuaState(L);
            LuaObject obj = state->Stack(idx);
            return obj.GetMetatable() == state->GetRegistry()["fgVector3fMETATABLE"];
        }
        static inline fgVector3f Get(lua_State* L, int idx) {
            LuaState* state = lua_State_to_LuaState(L);
            return *(fgVector3f*)state->UnBoxPointer(idx);
        }
    };

    template<> struct Type<fgVector3f&> : public Type<fgVector3f> {
    };

    template<> struct Type<const fgVector3f&> : public Type<fgVector3f> {
    };
}

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
private:
    #if defined(FG_USING_LUA_PLUS)
    typedef std::map<uintptr_t, LuaPlus::LuaObject> userDataObjectMap;
    #else
    typedef std::map<uintptr_t, void *> userDataObjectMap;
    #endif
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
     * @param L
     * @return 
     */
    static int simpleGCEvent(lua_State* L);
    /**
     * 
     * @param L
     * @return 
     */
    static int simpleInPlaceGCEvent(lua_State* L);
    /**
     * 
     * @param L
     * @return 
     */
    static int managedResourceGCEvent(lua_State* L);
    #if defined(FG_USING_LUA_PLUS)
    /**
     * 
     * @param state
     * @return 
     */
    static int newResourceWrapper(LuaPlus::LuaState* state);
    
    #endif /* FG_USING_LUA_PLUS */
    
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

#endif /* _FG_SCRIPT_SUBSYSTEM_H_ */
