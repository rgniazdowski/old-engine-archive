/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgScriptSubsystem.h"

#include "Event/fgEventManager.h"
#include "Resource/fgResourceManager.h"
#include "Resource/fgResourceFactory.h"
#include "GFX/fgGFXSceneManager.h"
#include "GFX/Shaders/fgGFXShaderManager.h"
#include "GFX/Particles/fgParticleSystem.h"
#include "GUI/fgGuiWidgetManager.h"
#include "GUI/fgGuiStyleManager.h"

#if defined(FG_USING_LUA_PLUS)
///
LuaPlus::LuaState *fgScriptSubsystem::m_luaState = NULL;
///
LuaPlus::LuaObject fgScriptSubsystem::m_globals;
#endif /* FG_USING_LUA_PLUS */

///
fgBool fgScriptSubsystem::m_isBindingComplete = FG_FALSE;
///
fgScriptSubsystem::userDataObjectMap fgScriptSubsystem::m_userDataObjectMap;

/// Pointer to the external event manager
fgManagerBase *fgScriptSubsystem::m_pEventMgr = NULL;
/// Pointer to the external resource manager
fgManagerBase *fgScriptSubsystem::m_pResourceMgr = NULL;
/// Pointer to the external shader manager
fgManagerBase *fgScriptSubsystem::m_pShaderMgr = NULL;
/// Pointer to the external 2D Scene manager
fgManagerBase *fgScriptSubsystem::m_p2DSceneMgr = NULL;
/// Pointer to the external 3D Scene manager
fgManagerBase *fgScriptSubsystem::m_p3DSceneMgr = NULL;
/// Pointer to the external particle manager
fgManagerBase *fgScriptSubsystem::m_pParticleMgr = NULL;
/// Pointer to the external widget manager
fgManagerBase *fgScriptSubsystem::m_pWidgetMgr = NULL;
/// Pointer to the external style manager
fgManagerBase *fgScriptSubsystem::m_pStyleMgr = NULL;
/// Pointer to the external sound manager
fgManagerBase *fgScriptSubsystem::m_pSoundMgr = NULL;

/**
 * 
 */
fgScriptSubsystem::fgScriptSubsystem() :
#if defined(FG_USING_LUA_PLUS)
m_metatableEventMgr(),
m_metatableResourceMgr(),
m_metatableShaderMgr(),
m_metatable2DSceneMgr(),
m_metatable3DSceneMgr(),
m_metatableParticleMgr(),
m_metatableWidgetMgr(),
m_metatableStyleMgr(),
m_metatableSoundMgr()
#endif /* FG_USING_LUA_PLUS */
{
    m_managerType = FG_MANAGER_SCRIPT;
}

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
    m_managerType = FG_MANAGER_SCRIPT;
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
    m_metatableEventMgr.Reset();
    m_metatableResourceMgr.Reset();
    m_metatableShaderMgr.Reset();
    m_metatable2DSceneMgr.Reset();
    m_metatable3DSceneMgr.Reset();
    m_metatableParticleMgr.Reset();
    m_metatableWidgetMgr.Reset();
    m_metatableStyleMgr.Reset();
    m_metatableSoundMgr.Reset();
    userDataObjectMapItor it = m_userDataObjectMap.begin(), end = m_userDataObjectMap.end();
    for(; it != end; it++) {
        userDataObjectMap::value_type &pair = *it;
        pair.second.Reset();
    }
    if(m_luaState)
        LuaPlus::LuaState::Destroy(m_luaState);
    m_luaState = NULL;
#endif /* FG_USING_LUA_PLUS */

    m_isBindingComplete = FG_FALSE;
    m_init = FG_FALSE;

    m_userDataObjectMap.clear();
    userDataObjectMap map;
    m_userDataObjectMap.swap(map);
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
    float t1 = fgTime::ms();
#if defined(FG_USING_LUA_PLUS)
    if(!m_luaState)
        m_luaState = LuaPlus::LuaState::Create(true);
    if(!m_luaState) {
        FG_LOG::PrintError("Script: Failed to initialize main state");
        return FG_FALSE;
    }
    m_globals = m_luaState->GetGlobals();
#endif /* FG_USING_LUA_PLUS */

    if(!registerConstants()) {
        FG_LOG::PrintError("Script: Failed to register global constants");
    }

    if(!registerEventManager()) {
        FG_LOG::PrintError("Script: Failed to register EventManager object");
    }

    if(!registerResourceManager()) {
        FG_LOG::PrintError("Script: Failed to register ResourceManager object");
    }

    if(!registerShaderManager()) {
        FG_LOG::PrintError("Script: Failed to register ShaderManager object");
    }

    if(!register2DSceneManager()) {
        FG_LOG::PrintError("Script: Failed to register 2DSceneManager object");
    }

    if(!register3DSceneManager()) {
        FG_LOG::PrintError("Script: Failed to register 3DSceneManager object");
    }

    if(!registerParticleSystem()) {
        FG_LOG::PrintError("Script: Failed to register ParticleSystem object");
    }

    if(!registerWidgetManager()) {
        FG_LOG::PrintError("Script: Failed to register WidgetManager object");

    }

    if(!registerStyleManager()) {
        FG_LOG::PrintError("Script: Failed to register StyleManager object");

    }

    if(!registerSoundManager()) {
        FG_LOG::PrintError("Script: Failed to register SoundManager object");
    }
    float t2 = fgTime::ms();
    FG_LOG::PrintDebug("Script: ScriptSubsystem initialized in %.2f seconds", (t2 - t1) / 1000.0f);
    m_init = FG_TRUE;
    m_isBindingComplete = FG_TRUE;
    m_managerType = FG_MANAGER_SCRIPT;
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
int fgScriptSubsystem::managedResourceGCEvent(lua_State* L) {
    if(!L)
        return 0;
    // Mainly for resources ?
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    //get the pointer lua is trying to delete.
    void *unboxed = state->UnBoxPointer(1);
    if(!unboxed)
        return 0;
    fgResource *pResource = (fgResource *)unboxed;
    uintptr_t offset = (uintptr_t)pResource;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it == m_userDataObjectMap.end()) {
        // The pointer is not registered
        FG_LOG::PrintDebug("Managed Resource GC: pointer is not registered %p [offset: %lu]", unboxed, offset);
        return 0;
    }
    pResource->dispose();
    FG_LOG::PrintDebug("Called gc_event from lua for some Resource '%s'", pResource->getNameStr());
    return 0;
}

fgBool fgScriptSubsystem::managedObjectDestructorCallback(void *systemData, void *userData) {
    if(!systemData)
        return FG_FALSE;

    uintptr_t offset = (uintptr_t)systemData;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        // This pointer was stored - erase it
        FG_LOG::PrintDebug("Managed Resource Destructor Callback: pointer is registered - will be deleted [offset: %lu]", offset);
        m_userDataObjectMap.erase(it);
    }

    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool fgScriptSubsystem::registerConstants(void) {
    if(!m_luaState)
        return FG_FALSE;

    if(m_isBindingComplete)
        return FG_TRUE;

#if defined(FG_USING_LUA_PLUS)
    if(m_globals.GetRef() < 0)
        return FG_FALSE;

    m_globals.SetInteger("FG_BUILD_VERSION", (int)FG_BUILD_VERSION);

#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool fgScriptSubsystem::registerEventManager(void) {
    if(!m_luaState)
        return FG_FALSE;
    if(m_isBindingComplete)
        return FG_TRUE;
    if(!m_pEventMgr)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    if(m_metatableEventMgr.GetRef() >= 0)
        return FG_TRUE;
    if(m_globals.GetRef() < 0)
        return FG_FALSE;

    m_metatableEventMgr = m_globals.CreateTable("fgEventManagerMETATABLE");
    m_metatableEventMgr.SetObject("__index", m_metatableEventMgr);
    //m_metatableEventMgr.RegisterObjectDirect("");

    uintptr_t offset = (uintptr_t)m_pEventMgr;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        // This pointer is already registered ?
        return FG_FALSE;
    }
    LuaPlus::LuaObject eventMgrObj = m_luaState->BoxPointer((void *)m_pEventMgr);
    eventMgrObj.SetMetatable(m_metatableEventMgr);
    m_globals.SetObject("EventManager", eventMgrObj);
    m_userDataObjectMap[offset] = eventMgrObj;
#endif /* FG_USING_LUA_PLUS */    
    return FG_TRUE;
}

/**
 * 
 * @param state
 * @return 
 */
int fgScriptSubsystem::newResourceWrapper(LuaPlus::LuaState* state) {
    if(!state)
        return 0;

    LuaPlus::LuaStack args(state);

    const char *info = NULL;
    if(args.Count()) {
        if(args[1].IsString()) {
            info = args[1].GetString();
        }
    }
    fgBool status = FG_TRUE;
    if(!m_pResourceMgr)
        return 0;
    if(m_pResourceMgr->getManagerType() != FG_MANAGER_RESOURCE)
        return 0;
    fgResource *pResource = static_cast<fgResourceManager *>(m_pResourceMgr)->request(info);
    LuaPlus::LuaObject resourceObj = state->BoxPointer(pResource);
    if(!pResource) {
        resourceObj.SetMetatable(LuaPlus::LuaObject());
        return 1;
    }
    uintptr_t offset = (uintptr_t)pResource;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    printf("LUA: New resource, pointer: %p [offset=%lu]\n", pResource, offset);
    if(pResource->getResourceType() == FG_RESOURCE_TEXTURE) {
        resourceObj.SetMetatable(state->GetRegistry()["fgTextureResourceMETATABLE"]);
        printf("LUA: Setting special metatable for textureResource\n");
    } else {
        resourceObj.SetMetatable(LuaPlus::LuaObject());
        status = FG_FALSE;
    }
    if(it == m_userDataObjectMap.end() && offset) {
        m_userDataObjectMap[offset] = resourceObj;
    }
    if(status) {
        pResource->registerOnDestruct(&fgScriptSubsystem::managedObjectDestructorCallback, NULL);
    }
    return 1;
}

/**
 * 
 * @return 
 */
fgBool fgScriptSubsystem::registerResourceManager(void) {
    if(!m_luaState)
        return FG_FALSE;
    if(m_isBindingComplete)
        return FG_TRUE;
    if(!m_pResourceMgr)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    if(m_metatableResourceMgr.GetRef() >= 0)
        return FG_TRUE;
    if(m_globals.GetRef() < 0)
        return FG_FALSE;

    m_metatableResourceMgr = m_globals.CreateTable("fgResourceManagerMETATABLE");
    m_metatableResourceMgr.SetObject("__index", m_metatableResourceMgr);
    m_metatableResourceMgr.Register("request", &fgScriptSubsystem::newResourceWrapper);

    uintptr_t offset = (uintptr_t)m_pResourceMgr;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        return FG_FALSE;
    }
    typedef const char*(fgResource::base_type::*getFilePathStrType)(void)const;

    LuaPlus::LuaObject resourceMgrObj = m_luaState->BoxPointer((void *)m_pResourceMgr);
    resourceMgrObj.SetMetatable(m_metatableResourceMgr);
    m_globals.SetObject("ResourceManager", resourceMgrObj);
    m_userDataObjectMap[offset] = resourceMgrObj;

    LPCD::Class(m_luaState->GetCState(), "fgResourceMETATABLE")
            .ObjectDirect("getName", (fgResource::base_type::base_type *)0, &fgResource::base_type::base_type::getNameStr)
            .ObjectDirect("getFilePath",
                          (fgResource::base_type *)0,
                          static_cast<getFilePathStrType>(&fgResource::base_type::getFilePathStr));
    //.MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent);

    // Register Texture Resource metatable / object
    LPCD::Class(m_luaState->GetCState(), "fgTextureResourceMETATABLE", "fgResourceMETATABLE")
            .ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
            .ObjectDirect("getHeight", (fgTextureResource *)0, &fgTextureResource::getHeight)
            .MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent);

    m_globals.Register("Texture", &fgScriptSubsystem::newResourceWrapper);
#endif /* FG_USING_LUA_PLUS */    
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
