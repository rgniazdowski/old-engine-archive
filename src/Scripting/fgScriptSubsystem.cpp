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
#include "GUI/Font/fgFontResource.h"
#include "GUI/fgGuiWidget.h"
#include "GUI/fgGuiButton.h"
#include "GUI/fgGuiConsole.h"
#include "GUI/fgGuiContainer.h"
#include "GUI/fgGuiEditableText.h"
#include "GUI/fgGuiFrame.h"
#include "GUI/fgGuiLabel.h"
#include "GUI/fgGuiLoader.h"
#include "GUI/fgGuiMenu.h"
#include "GUI/fgGuiMessageBox.h"
#include "GUI/fgGuiPopup.h"
#include "GUI/fgGuiProgressBar.h"
#include "GUI/fgGuiScrollArea.h"
#include "GUI/fgGuiStyle.h"
#include "GUI/fgGuiTable.h"
#include "GUI/fgGuiTextArea.h"
#include "GUI/fgGuiToggleButton.h"
#include "GUI/fgGuiWindow.h"

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
///
fgScriptSubsystem::scriptMetatableInfoMap fgScriptSubsystem::m_scriptMetatableInfoMap;

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
    userDataObjectMap dmmap;
    m_userDataObjectMap.swap(dmmap);
    m_scriptMetatableInfoMap.clear();
    scriptMetatableInfoMap smmap;
    m_scriptMetatableInfoMap.swap(smmap);
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

    {
        // Initializing metatable map
        m_scriptMetatableInfoMap.clear();

        // can generate random IDS? YEP :D
        // Numbers 0 - 9 ASCII 48 to 57
        // Lowercase letters a - z ASCII 97 to 122
        // Uppercase letters A - Z ASCII 65 - 90

        m_scriptMetatableInfoMap[EMPTY_METATABLE_ID] = metatableInfo(EMPTY_METATABLE_ID, "FG_L_EMPTY_META_TAB");
        m_scriptMetatableInfoMap[VECTOR2I_METATABLE_ID] = metatableInfo(VECTOR2I_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[VECTOR2F_METATABLE_ID] = metatableInfo(VECTOR2F_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[VECTOR3I_METATABLE_ID] = metatableInfo(VECTOR3I_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[VECTOR3F_METATABLE_ID] = metatableInfo(VECTOR3F_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[VECTOR4I_METATABLE_ID] = metatableInfo(VECTOR4I_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[VECTOR4F_METATABLE_ID] = metatableInfo(VECTOR4F_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[ERROR_METATABLE_ID] = metatableInfo(ERROR_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[EVENT_MANAGER_METATABLE_ID] = metatableInfo(EVENT_MANAGER_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[RESOURCE_MANAGER_METATABLE_ID] = metatableInfo(RESOURCE_MANAGER_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[SHADER_MANAGER_METATABLE_ID] = metatableInfo(SHADER_MANAGER_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[SCENE2D_MANAGER_METATABLE_ID] = metatableInfo(SCENE2D_MANAGER_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[SCENE3D_MANAGER_METATABLE_ID] = metatableInfo(SCENE3D_MANAGER_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[PARTICLE_SYSTEM_METATABLE_ID] = metatableInfo(PARTICLE_SYSTEM_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[WIDGET_MANAGER_METATABLE_ID] = metatableInfo(WIDGET_MANAGER_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[STYLE_MANAGER_METATABLE_ID] = metatableInfo(STYLE_MANAGER_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[SOUND_MANAGER_METATABLE_ID] = metatableInfo(SOUND_MANAGER_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[RESOURCE_METATABLE_ID] = metatableInfo(RESOURCE_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[TEXTURE_RESOURCE_METATABLE_ID] = metatableInfo(TEXTURE_RESOURCE_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[FONT_RESOURCE_METATABLE_ID] = metatableInfo(FONT_RESOURCE_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[GFX_MODEL_RESOURCE_METATABLE_ID] = metatableInfo(GFX_MODEL_RESOURCE_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[PARTICLE_EFFECT_RESOURCE_METATABLE_ID] = metatableInfo(PARTICLE_EFFECT_RESOURCE_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[SOUND_RESOURCE_METATABLE_ID] = metatableInfo(SOUND_RESOURCE_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[MUSIC_RESOURCE_METATABLE_ID] = metatableInfo(MUSIC_RESOURCE_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[PLUGIN_RESOURCE_METATABLE_ID] = metatableInfo(PLUGIN_RESOURCE_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[SAVE_FILE_RESOURCE_METATABLE_ID] = metatableInfo(SAVE_FILE_RESOURCE_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[CONFIG_METATABLE_ID] = metatableInfo(CONFIG_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[SETTINGS_METATABLE_ID] = metatableInfo(SETTINGS_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[GUI_WIDGET_METATABLE_ID] = metatableInfo(GUI_WIDGET_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[GUI_BUTTON_METATABLE_ID] = metatableInfo(GUI_BUTTON_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[GUI_CONSOLE_METATABLE_ID] = metatableInfo(GUI_CONSOLE_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[GUI_CONTAINER_METATABLE_ID] = metatableInfo(GUI_CONTAINER_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[GUI_FRAME_METATABLE_ID] = metatableInfo(GUI_FRAME_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[GUI_LABEL_METATABLE_ID] = metatableInfo(GUI_LABEL_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[GUI_LOADER_METATABLE_ID] = metatableInfo(GUI_LOADER_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[GUI_MENU_METATABLE_ID] = metatableInfo(GUI_MENU_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[GUI_MESSAGE_BOX_METATABLE_ID] = metatableInfo(GUI_MESSAGE_BOX_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[GUI_POPUP_METATABLE_ID] = metatableInfo(GUI_POPUP_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[GUI_PROGRESS_BAR_METATABLE_ID] = metatableInfo(GUI_PROGRESS_BAR_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[GUI_SCROLL_AREA_METATABLE_ID] = metatableInfo(GUI_SCROLL_AREA_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[GUI_STYLE_METATABLE_ID] = metatableInfo(GUI_STYLE_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[GUI_STYLE_CONTENT_METATABLE_ID] = metatableInfo(GUI_STYLE_CONTENT_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[GUI_TABLE_METATABLE_ID] = metatableInfo(GUI_TABLE_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[GUI_TEXT_AREA_METATABLE_ID] = metatableInfo(GUI_TEXT_AREA_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[GUI_TOGGLE_BUTTON_METATABLE_ID] = metatableInfo(GUI_TOGGLE_BUTTON_METATABLE_ID, "FG_L_", "_TAB");
        m_scriptMetatableInfoMap[GUI_WINDOW_METATABLE_ID] = metatableInfo(GUI_WINDOW_METATABLE_ID, "FG_L_", "_TAB");
    }

    if(!registerConstants()) {
        FG_LOG::PrintError("Script: Failed to register global constants");
    }

    if(!registerAdditionalTypes()) {
        FG_LOG::PrintError("Script: Failed to register additional types");
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
int fgScriptSubsystem::simpleFreeGCEvent(lua_State* L) {
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
        FG_LOG::PrintDebug("Simple GC: pointer is not registered %p [offset: %lu]", unboxed, offset);
        return 0;
    } else {
        m_userDataObjectMap.erase(it);
    }
    FG_LOG::PrintDebug("Simple GC: freeing memory %p [offset: %lu]", unboxed, offset);
    fgFree(unboxed);

#endif /* FG_USING_LUA_PLUS */
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
#if defined(FG_USING_LUA_PLUS)
    // Mainly for resources ?
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    //get the pointer lua is trying to delete.
    if(!state->IsUserdata(1))
        return 0;
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
#endif /* FG_USING_LUA_PLUS */
    return 0;
}

/**
 * 
 * @param systemData
 * @param userData
 * @return 
 */
fgBool fgScriptSubsystem::managedObjectDestructorCallback(void *systemData, void *userData) {
    if(!systemData)
        return FG_FALSE;

    uintptr_t offset = (uintptr_t)systemData;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        // This pointer was stored - erase it
#if defined(FG_USING_LUA_PLUS)
        if((*it).second.GetRef() > 0) {
            (*it).second.SetMetatable(LuaPlus::LuaObject());
            (*it).second.AssignNil();
        }
        (*it).second.Reset();
#endif /* FG_USING_LUA_PLUS */
        FG_LOG::PrintDebug("Managed Object Destructor Callback: pointer is registered - will be deleted [offset: %lu]", offset);
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
fgBool fgScriptSubsystem::registerAdditionalTypes(void) {
    if(!m_luaState)
        return FG_FALSE;

    if(m_isBindingComplete)
        return FG_TRUE;

#if defined(FG_USING_LUA_PLUS)
    if(m_globals.GetRef() < 0)
        return FG_FALSE;

    // fgVector2i | FG VECTOR 2I    
    LPCD::Class(m_luaState->GetCState(), getMetatableName(VECTOR2I_METATABLE_ID))
            .Property("x", &fgVector2i::x)
            .Property("y", &fgVector2i::y)
            .Property("s", &fgVector2i::s)
            .Property("t", &fgVector2i::t)
            .MetatableFunction("__gc", &fgScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<fgVector2i>
    m_globals.Register("Vector2i", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector2i, VECTOR2I_METATABLE_ID>);
    FG_LOG::PrintDebug("Script: Register metatable '%s' for Vector2i", getMetatableName(VECTOR2I_METATABLE_ID));

    // fgVector2f | FG VECTOR 2F
    LPCD::Class(m_luaState->GetCState(), getMetatableName(VECTOR2F_METATABLE_ID))
            .Property("x", &fgVector2f::x)
            .Property("y", &fgVector2f::y)
            .Property("s", &fgVector2f::s)
            .Property("t", &fgVector2f::t)
            .MetatableFunction("__gc", &fgScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<fgVector2f>
    m_globals.Register("Vector2f", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector2f, VECTOR2F_METATABLE_ID>);
    FG_LOG::PrintDebug("Script: Register metatable '%s' for Vector2f", getMetatableName(VECTOR2F_METATABLE_ID));

    // fgVector3i | FG VECTOR 3I    
    LPCD::Class(m_luaState->GetCState(), getMetatableName(VECTOR3I_METATABLE_ID))
            .Property("x", &fgVector3i::x)
            .Property("y", &fgVector3i::y)
            .Property("z", &fgVector3i::z)
            .Property("r", &fgVector3i::r)
            .Property("g", &fgVector3i::g)
            .Property("b", &fgVector3i::b)
            .Property("s", &fgVector3i::s)
            .Property("t", &fgVector3i::t)
            .MetatableFunction("__gc", &fgScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<fgVector3i>
    m_globals.Register("Vector3i", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector3i, VECTOR3I_METATABLE_ID>);
    FG_LOG::PrintDebug("Script: Register metatable '%s' for Vector3i", getMetatableName(VECTOR3I_METATABLE_ID));

    // fgVector3f | FG VECTOR 3F    
    LPCD::Class(m_luaState->GetCState(), getMetatableName(VECTOR3F_METATABLE_ID))
            .Property("x", &fgVector3f::x)
            .Property("y", &fgVector3f::y)
            .Property("z", &fgVector3f::z)
            .Property("r", &fgVector3f::r)
            .Property("g", &fgVector3f::g)
            .Property("b", &fgVector3f::b)
            .Property("s", &fgVector3f::s)
            .Property("t", &fgVector3f::t)
            .MetatableFunction("__gc", &fgScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<fgVector3f>
    m_globals.Register("Vector3f", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector3f, VECTOR3F_METATABLE_ID>);
    FG_LOG::PrintDebug("Script: Register metatable '%s' for Vector3f", getMetatableName(VECTOR3F_METATABLE_ID));

    // fgVector4i | FG VECTOR 4I 
    LPCD::Class(m_luaState->GetCState(), getMetatableName(VECTOR4I_METATABLE_ID))
            .Property("x", &fgVector4i::x)
            .Property("y", &fgVector4i::y)
            .Property("z", &fgVector4i::z)
            .Property("w", &fgVector4i::w)
            .Property("r", &fgVector4i::r)
            .Property("g", &fgVector4i::g)
            .Property("b", &fgVector4i::b)
            .Property("a", &fgVector4i::a)
            .Property("s", &fgVector4i::s)
            .Property("t", &fgVector4i::t)
            .MetatableFunction("__gc", &fgScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<fgVector4i>
    m_globals.Register("Vector4i", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector4i, VECTOR4I_METATABLE_ID>);
    FG_LOG::PrintDebug("Script: Register metatable '%s' for Vector4i", getMetatableName(VECTOR4I_METATABLE_ID));

    // fgVector4f | FG VECTOR 4F    
    LPCD::Class(m_luaState->GetCState(), getMetatableName(VECTOR4F_METATABLE_ID))
            .Property("x", &fgVector4f::x)
            .Property("y", &fgVector4f::y)
            .Property("z", &fgVector4f::z)
            .Property("w", &fgVector4f::w)
            .Property("r", &fgVector4f::r)
            .Property("g", &fgVector4f::g)
            .Property("b", &fgVector4f::b)
            .Property("a", &fgVector4f::a)
            .Property("s", &fgVector4f::s)
            .Property("t", &fgVector4f::t)
            .MetatableFunction("__gc", &fgScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<fgVector4f>
    m_globals.Register("Vector4f", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector4f, VECTOR4F_METATABLE_ID>);
    FG_LOG::PrintDebug("Script: Register metatable '%s' for Vector4f", getMetatableName(VECTOR4F_METATABLE_ID));
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

    m_metatableEventMgr = m_globals.CreateTable(getMetatableName(EVENT_MANAGER_METATABLE_ID));
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
int fgScriptSubsystem::newResourceWrapper(lua_State* L) {
    if(!L)
        return 0;
#if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
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
    FG_LOG::PrintDebug("Script: New resource, pointer: %p [offset=%lu]", pResource, offset);
    fgResourceType resType = pResource->getResourceType();
    METAID metaID = EMPTY_METATABLE_ID;
    const char *metatableName = NULL;
    if(resType == FG_RESOURCE_TEXTURE) {
        metaID = TEXTURE_RESOURCE_METATABLE_ID;
        metatableName = getMetatableName(metaID);
    } else if(resType == FG_RESOURCE_FONT) {
        metaID = FONT_RESOURCE_METATABLE_ID;
        metatableName = getMetatableName(metaID);
    } else if(resType == FG_RESOURCE_3D_MODEL) {
        metaID = GFX_MODEL_RESOURCE_METATABLE_ID;
        metatableName = getMetatableName(metaID);
    } else if(resType == FG_RESOURCE_PARTICLE_EFFECT) {
        metaID = PARTICLE_EFFECT_RESOURCE_METATABLE_ID;
        metatableName = getMetatableName(metaID);
    } else {
        resourceObj.SetMetatable(LuaPlus::LuaObject());
        resourceObj.AssignNil();
        status = FG_FALSE;
        FG_LOG::PrintDebug("Script: Unknown resource type requested / not supported [resType=%d]", resType);
    }
    if(status) {
        resourceObj.SetMetatable(state->GetRegistry()[metatableName]);
        FG_LOG::PrintDebug("Script: Setting special metatable.%d=[%s]", metaID, metatableName);
    }
    if(it == m_userDataObjectMap.end() && offset) {
        m_userDataObjectMap[offset] = resourceObj;
    }
    if(status) {
        pResource->registerOnDestruct(&fgScriptSubsystem::managedObjectDestructorCallback, NULL);
    }
#endif /* FG_USING_LUA_PLUS */
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

    // Resource manager metatable
    m_metatableResourceMgr = m_globals.CreateTable(getMetatableName(RESOURCE_MANAGER_METATABLE_ID));
    m_metatableResourceMgr.SetObject("__index", m_metatableResourceMgr);
    m_metatableResourceMgr.Register("request", &fgScriptSubsystem::newResourceWrapper);

    uintptr_t offset = (uintptr_t)m_pResourceMgr;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        return FG_FALSE;
    }
    // Create lua object for resource manager global
    LuaPlus::LuaObject resourceMgrObj = m_luaState->BoxPointer((void *)m_pResourceMgr);
    resourceMgrObj.SetMetatable(m_metatableResourceMgr);
    m_globals.SetObject("ResourceManager", resourceMgrObj);
    m_userDataObjectMap[offset] = resourceMgrObj;

    //
    // Registering now metatables for various resource types
    //

    typedef const char*(fgResource::base_type::*getFilePathStrType)(void)const;
    // Register Base Resource metatable
    LPCD::Class(m_luaState->GetCState(), getMetatableName(RESOURCE_METATABLE_ID))
            .ObjectDirect("getName", (fgResource::base_type::base_type *)0, &fgResource::base_type::base_type::getNameStr)
            .ObjectDirect("isManaged", (fgResource::base_type::base_type *)0, &fgResource::base_type::base_type::isManaged)
            .ObjectDirect("getFilePath",
                          (fgResource::base_type *)0,
                          static_cast<getFilePathStrType>(&fgResource::base_type::getFilePathStr))
            .ObjectDirect("getSize", (fgResource *)0, &fgResource::getSize)
            .ObjectDirect("getLastAccess", (fgResource *)0, &fgResource::getLastAccess)
            .ObjectDirect("isDisposed", (fgResource *)0, &fgResource::isDisposed)
            .ObjectDirect("isLocked", (fgResource *)0, &fgResource::isLocked)
            .ObjectDirect("dispose", (fgResource *)0, &fgResource::dispose);
    //.MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent);

    // Register Texture Resource metatable
    LPCD::Class(m_luaState->GetCState(), getMetatableName(TEXTURE_RESOURCE_METATABLE_ID), getMetatableName(RESOURCE_METATABLE_ID))
            .ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
            .ObjectDirect("getHeight", (fgTextureResource *)0, &fgTextureResource::getHeight)
            .ObjectDirect("getComponents", (fgTextureResource *)0, &fgTextureResource::getComponents)
            .MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent);

    // Register Font Resource metatable
    LPCD::Class(m_luaState->GetCState(), getMetatableName(FONT_RESOURCE_METATABLE_ID), getMetatableName(TEXTURE_RESOURCE_METATABLE_ID))
            .ObjectDirect("getFontType", (fgFontResource *)0, &fgFontResource::getFontType)
            .ObjectDirect("getStep", (fgFontResource *)0, &fgFontResource::getStep)
            .MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent);

    // Register Gfx Model Resource metatable
    LPCD::Class(m_luaState->GetCState(), getMetatableName(GFX_MODEL_RESOURCE_METATABLE_ID), getMetatableName(RESOURCE_METATABLE_ID))
            .ObjectDirect("getModelType", (fgGfxModelResource *)0, &fgGfxModelResource::getModelType)
            .ObjectDirect("getNumIndices", (fgGfxModelResource *)0, &fgGfxModelResource::getNumIndices)
            .ObjectDirect("getNumMaterials", (fgGfxModelResource *)0, &fgGfxModelResource::getNumMaterials)
            .ObjectDirect("getNumNormals", (fgGfxModelResource *)0, &fgGfxModelResource::getNumNormals)
            .ObjectDirect("getNumPolygons", (fgGfxModelResource *)0, &fgGfxModelResource::getNumPolygons)
            .ObjectDirect("getNumShapes", (fgGfxModelResource *)0, &fgGfxModelResource::getNumShapes)
            .ObjectDirect("getNumTriangles", (fgGfxModelResource *)0, &fgGfxModelResource::getNumTriangles)
            .ObjectDirect("getNumUVs", (fgGfxModelResource *)0, &fgGfxModelResource::getNumUVs)
            .ObjectDirect("getNumVertices", (fgGfxModelResource *)0, &fgGfxModelResource::getNumVertices)
            .ObjectDirect("isInterleaved", (fgGfxModelResource *)0, &fgGfxModelResource::isInterleaved)
            .ObjectDirect("isTextured", (fgGfxModelResource *)0, &fgGfxModelResource::isTextured)
            .ObjectDirect("isMultitextured", (fgGfxModelResource *)0, &fgGfxModelResource::isMultitextured)
            .ObjectDirect("hasMaterial", (fgGfxModelResource *)0, &fgGfxModelResource::hasMaterial)
            .MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent);

    typedef void (fgParticleEffect::*PE_void_4X_INT_IN)(const int, const int, const int, const int);
    typedef void (fgParticleEffect::*PE_void_2X_FLOAT_IN)(const float, const float);
    typedef void (fgParticleEffect::*PE_void_Vec4f_IN)(const fgVector4f&);
    typedef void (fgParticleEffect::*PE_void_Vec3f_IN)(const fgVector3f&);
    typedef void (fgParticleEffect::*PE_void_Vec2f_IN)(const fgVector2f&);
    typedef void (fgParticleEffect::*PE_void_Vec2i_IN)(const fgVector2i&);
    typedef void (fgParticleEffect::*PE_void_C_STR_IN)(const char *);

    // Register Particle Effect Resource metatable

    LPCD::Class(m_luaState->GetCState(), getMetatableName(PARTICLE_EFFECT_RESOURCE_METATABLE_ID), getMetatableName(RESOURCE_METATABLE_ID))
            .ObjectDirect("setMaxCount", (fgParticleEffect *)0, &fgParticleEffect::setMaxCount)
            .ObjectDirect("getMaxCount", (fgParticleEffect *)0, &fgParticleEffect::getMaxCount)
            .ObjectDirect("isAreaCheck", (fgParticleEffect *)0, &fgParticleEffect::isAreaCheck)
            .ObjectDirect("isAreaSet", (fgParticleEffect *)0, &fgParticleEffect::isAreaSet)
            .ObjectDirect("unsetParticleArea", (fgParticleEffect *)0, &fgParticleEffect::unsetParticleArea)
            //.ObjectDirect("setParticleArea", (fgParticleEffect *)0, &fgParticleEffect::setParticleArea)
            .ObjectDirect("setAreaCheck", (fgParticleEffect *)0, &fgParticleEffect::setAreaCheck)
            .ObjectDirect("setTextureXSize", (fgParticleEffect *)0, &fgParticleEffect::setTextureXSize)
            .ObjectDirect("setTextureYSize", (fgParticleEffect *)0, &fgParticleEffect::setTextureYSize)
            //.ObjectDirect("setTextureIDRange", (fgParticleEffect *)0, &fgParticleEffect::setTextureIDRange)
            .ObjectDirect("setParamsActive", (fgParticleEffect *)0, &fgParticleEffect::setParamsActive)
            .ObjectDirect("setRandomVelocity", (fgParticleEffect *)0, &fgParticleEffect::setRandomVelocity)
            .ObjectDirect("setLifeAsSize", (fgParticleEffect *)0, &fgParticleEffect::setLifeAsSize)
            .ObjectDirect("setFacingVelocity", (fgParticleEffect *)0, &fgParticleEffect::setFacingVelocity)
            .ObjectDirect("setRandomAngle", (fgParticleEffect *)0, &fgParticleEffect::setRandomAngle)
            .ObjectDirect("setSpreadSpeed", (fgParticleEffect *)0, &fgParticleEffect::setSpreadSpeed)
            .ObjectDirect("setStartSize",
                          (fgParticleEffect *)0,
                          static_cast<PE_void_Vec3f_IN>(&fgParticleEffect::setStartSize))

            .ObjectDirect("setEndSize",
                          (fgParticleEffect *)0,
                          static_cast<PE_void_Vec3f_IN>(&fgParticleEffect::setEndSize))

            .ObjectDirect("setLowLife", (fgParticleEffect *)0, &fgParticleEffect::setLowLife)
            .ObjectDirect("setHighLife", (fgParticleEffect *)0, &fgParticleEffect::setHighLife)

            .ObjectDirect("setLifeRange",
                          (fgParticleEffect *)0,
                          static_cast<PE_void_Vec2f_IN>(&fgParticleEffect::setLifeRange))

            .ObjectDirect("setLifeRange2f",
                          (fgParticleEffect *)0,
                          static_cast<PE_void_2X_FLOAT_IN>(&fgParticleEffect::setLifeRange))

            .ObjectDirect("setTTLRange",
                          (fgParticleEffect *)0,
                          static_cast<PE_void_Vec2i_IN>(&fgParticleEffect::setTTLRange))

            .ObjectDirect("setStartColor",
                          (fgParticleEffect *)0,
                          static_cast<PE_void_Vec4f_IN>(&fgParticleEffect::setStartColor))

            .ObjectDirect("setStartColor4i",
                          (fgParticleEffect *)0,
                          static_cast<PE_void_4X_INT_IN>(&fgParticleEffect::setStartColor))

            .ObjectDirect("setEndColor",
                          (fgParticleEffect *)0,
                          static_cast<PE_void_Vec4f_IN>(&fgParticleEffect::setEndColor))

            .ObjectDirect("setEndColor4i",
                          (fgParticleEffect *)0,
                          static_cast<PE_void_4X_INT_IN>(&fgParticleEffect::setEndColor))

            .ObjectDirect("setFadeSpeedRange",
                          (fgParticleEffect *)0,
                          static_cast<PE_void_Vec2f_IN>(&fgParticleEffect::setFadeSpeedRange))

            .ObjectDirect("setFadeSpeedRange2f",
                          (fgParticleEffect *)0,
                          static_cast<PE_void_2X_FLOAT_IN>(&fgParticleEffect::setFadeSpeedRange))

            .ObjectDirect("setTextureName",
                          (fgParticleEffect *)0,
                          static_cast<PE_void_C_STR_IN>(&fgParticleEffect::setTextureName))

            //.ObjectDirect("getFlags", (fgParticleEffect *)0, &fgParticleEffect::getFlags)
            //.ObjectDirect("getParticleArea", (fgParticleEffect *)0, &fgParticleEffect::getParticleArea)
            .ObjectDirect("getTextureName", (fgParticleEffect *)0, &fgParticleEffect::getTextureNameStr)
            .ObjectDirect("getTextureSheetSize", (fgParticleEffect *)0, &fgParticleEffect::getTextureSheetSize)
            .ObjectDirect("getTextureIDRange", (fgParticleEffect *)0, &fgParticleEffect::getTextureIDRange)
            .ObjectDirect("getStartSize", (fgParticleEffect *)0, &fgParticleEffect::getStartSize)
            .ObjectDirect("getEndSize", (fgParticleEffect *)0, &fgParticleEffect::getEndSize)
            .ObjectDirect("getSpreadSpeed", (fgParticleEffect *)0, &fgParticleEffect::getSpreadSpeed)
            .ObjectDirect("getLifeRange", (fgParticleEffect *)0, &fgParticleEffect::getLifeRange)
            .ObjectDirect("getTTLRange", (fgParticleEffect *)0, &fgParticleEffect::getTTLRange)
            .ObjectDirect("getFadeSpeedRange", (fgParticleEffect *)0, &fgParticleEffect::getFadeSpeedRange)
            .ObjectDirect("getStartColor", (fgParticleEffect *)0, &fgParticleEffect::getStartColor)
            .ObjectDirect("getEndColor", (fgParticleEffect *)0, &fgParticleEffect::getEndColor)
            .ObjectDirect("isParamsActive", (fgParticleEffect *)0, &fgParticleEffect::isParamsActive)
            .ObjectDirect("isRandomVelocity", (fgParticleEffect *)0, &fgParticleEffect::isRandomVelocity)
            .ObjectDirect("isLifeAsSize", (fgParticleEffect *)0, &fgParticleEffect::isLifeAsSize)
            .ObjectDirect("isFacingVelocity", (fgParticleEffect *)0, &fgParticleEffect::isFacingVelocity)
            .ObjectDirect("isRandomAngle", (fgParticleEffect *)0, &fgParticleEffect::isRandomAngle)
            .MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent);

    //m_globals.Register("Texture", &fgScriptSubsystem::newResourceWrapper);
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
    if(!m_pShaderMgr)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    if(m_metatableShaderMgr.GetRef() >= 0)
        return FG_TRUE;
    if(m_globals.GetRef() < 0)
        return FG_FALSE;

#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}

/**
 * 
 * @return
 */
fgBool fgScriptSubsystem::register2DSceneManager(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    if(!m_p2DSceneMgr)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    if(m_metatable2DSceneMgr.GetRef() >= 0)
        return FG_TRUE;
    if(m_globals.GetRef() < 0)
        return FG_FALSE;

#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}

/**
 * 
 * @return
 */
fgBool fgScriptSubsystem::register3DSceneManager(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    if(!m_p3DSceneMgr)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    if(m_metatable3DSceneMgr.GetRef() >= 0)
        return FG_TRUE;
    if(m_globals.GetRef() < 0)
        return FG_FALSE;

#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}

/**
 * 
 * @return
 */
fgBool fgScriptSubsystem::registerParticleSystem(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    if(!m_pParticleMgr)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    if(m_metatableParticleMgr.GetRef() >= 0)
        return FG_TRUE;
    if(m_globals.GetRef() < 0)
        return FG_FALSE;

    // Particle sysyem/manager metatable
    m_metatableParticleMgr = m_globals.CreateTable(getMetatableName(PARTICLE_SYSTEM_METATABLE_ID));
    m_metatableParticleMgr.SetObject("__index", m_metatableParticleMgr);
    //m_metatableParticleMgr.Register("request", &fgScriptSubsystem::newResourceWrapper);

    uintptr_t offset = (uintptr_t)m_pParticleMgr;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        return FG_FALSE;
    }
    // Create lua object for particle system/manager global
    LuaPlus::LuaObject particleMgrObj = m_luaState->BoxPointer((void *)m_pParticleMgr);
    particleMgrObj.SetMetatable(m_metatableParticleMgr);
    m_globals.SetObject("ParticleSystem", particleMgrObj);
    m_userDataObjectMap[offset] = particleMgrObj;

#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}

/**
 * 
 * @return
 */
fgBool fgScriptSubsystem::registerWidgetManager(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    if(!m_pWidgetMgr)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    if(m_metatableWidgetMgr.GetRef() >= 0)
        return FG_TRUE;
    if(m_globals.GetRef() < 0)
        return FG_FALSE;

    // Widget manager metatable
    m_metatableWidgetMgr = m_globals.CreateTable(getMetatableName(WIDGET_MANAGER_METATABLE_ID));
    m_metatableWidgetMgr.SetObject("__index", m_metatableWidgetMgr);
    //m_metatableWidgetMgr.Register("request", &fgScriptSubsystem::newResourceWrapper);

    uintptr_t offset = (uintptr_t)m_pWidgetMgr;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        return FG_FALSE;
    }
    // Create lua object for particle system/manager global
    LuaPlus::LuaObject widgetMgrObj = m_luaState->BoxPointer((void *)m_pWidgetMgr);
    widgetMgrObj.SetMetatable(m_metatableWidgetMgr);
    m_globals.SetObject("WidgetManager", widgetMgrObj);
    m_userDataObjectMap[offset] = widgetMgrObj;

    typedef void (fgGuiWidget::*GW_void_C_STR_IN)(const char *);

    const char *metatableNameWidget = getMetatableName(GUI_WIDGET_METATABLE_ID);
    const char *metatableName = NULL;
    // Register Base Widget metatable
    LPCD::Class(m_luaState->GetCState(), metatableNameWidget)
            .ObjectDirect("getName", (fgGuiWidget::base_type *)0, &fgGuiWidget::base_type::getNameStr)
            .ObjectDirect("isManaged", (fgGuiWidget::base_type *)0, &fgGuiWidget::base_type::isManaged)
            .ObjectDirect("setFlags", (fgGuiWidget *)0, static_cast<GW_void_C_STR_IN>(&fgGuiWidget::setFlags))
            .ObjectDirect("refresh", (fgGuiWidget *)0, &fgGuiWidget::refresh)
            //.ObjectDirect("updateState", (fgGuiWidget *)0, &fgGuiWidget::updateState)
            //.ObjectDirect("getFather", (fgGuiWidget *)0, &fgGuiWidget::refresh)
            .ObjectDirect("getType", (fgGuiWidget *)0, &fgGuiWidget::getType)
            .ObjectDirect("getTypeTraits", (fgGuiWidget *)0, &fgGuiWidget::getTypeTraits)
            .ObjectDirect("getTypeName", (fgGuiWidget *)0, &fgGuiWidget::getTypeNameStr)
            .ObjectDirect("setVisible", (fgGuiWidget *)0, &fgGuiWidget::setVisible)
            .ObjectDirect("isVisible", (fgGuiWidget *)0, &fgGuiWidget::isVisible)
            .ObjectDirect("setActive", (fgGuiWidget *)0, &fgGuiWidget::setActive)
            .ObjectDirect("isActive", (fgGuiWidget *)0, &fgGuiWidget::isActive)
            .ObjectDirect("setIgnoreState", (fgGuiWidget *)0, &fgGuiWidget::setIgnoreState)
            .ObjectDirect("isIgnoreState", (fgGuiWidget *)0, &fgGuiWidget::isIgnoreState)
            //.ObjectDirect("refresh", (fgGuiWidget *)0, &fgGuiWidget::doesIgnoreState)
            .ObjectDirect("getState", (fgGuiWidget *)0, &fgGuiWidget::getState)
            .ObjectDirect("setPosition", (fgGuiWidget *)0, &fgGuiWidget::setPosition)
            .ObjectDirect("getPosition", (fgGuiWidget *)0, &fgGuiWidget::getPosition)
            .ObjectDirect("getRelativePos", (fgGuiWidget *)0, &fgGuiWidget::getRelativePos)
            .ObjectDirect("setRelativePos", (fgGuiWidget *)0, &fgGuiWidget::setRelativePos)
            .ObjectDirect("setSize", (fgGuiWidget *)0, &fgGuiWidget::setSize)
            .ObjectDirect("getSize", (fgGuiWidget *)0, &fgGuiWidget::getSize)
            .ObjectDirect("getLink", (fgGuiWidget *)0, &fgGuiWidget::getLinkStr)
            .ObjectDirect("getScript", (fgGuiWidget *)0, &fgGuiWidget::getScriptStr)
            .ObjectDirect("getAction", (fgGuiWidget *)0, &fgGuiWidget::getActionStr)
            .ObjectDirect("getConfig", (fgGuiWidget *)0, &fgGuiWidget::getConfigStr)
            .ObjectDirect("getText", (fgGuiWidget *)0, &fgGuiWidget::getTextStr)
            .ObjectDirect("setLink", (fgGuiWidget *)0, static_cast<GW_void_C_STR_IN>(&fgGuiWidget::setLink))
            .ObjectDirect("setScript", (fgGuiWidget *)0, static_cast<GW_void_C_STR_IN>(&fgGuiWidget::setScript))
            .ObjectDirect("setAction", (fgGuiWidget *)0, static_cast<GW_void_C_STR_IN>(&fgGuiWidget::setAction))
            .ObjectDirect("setConfig", (fgGuiWidget *)0, static_cast<GW_void_C_STR_IN>(&fgGuiWidget::setConfig))
            .ObjectDirect("setText", (fgGuiWidget *)0, static_cast<GW_void_C_STR_IN>(&fgGuiWidget::setText))
            .ObjectDirect("getStyleName", (fgGuiWidget *)0, &fgGuiWidget::getStyleNameStr)
            .ObjectDirect("setStyleName", (fgGuiWidget *)0, static_cast<GW_void_C_STR_IN>(&fgGuiWidget::setStyleName))
            //.ObjectDirect("getStyleContents", (fgGuiWidget *)0, &fgGuiWidget::getStyleContents)
            //.ObjectDirect("getStyleContent", (fgGuiWidget *)0, &fgGuiWidget::getStyleContent)
            //.ObjectDirect("refresh", (fgGuiWidget *)0, &fgGuiWidget::setOnFocusCallback)
            ;
    //.MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent);

    // Register Gui Button metatable
    metatableName = getMetatableName(GUI_BUTTON_METATABLE_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Button", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiButton, GUI_BUTTON_METATABLE_ID>);

    // Register Gui Console metatable
    metatableName = getMetatableName(GUI_CONSOLE_METATABLE_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Console", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiButton, GUI_CONSOLE_METATABLE_ID>);

    // Register Gui Container metatable
    metatableName = getMetatableName(GUI_CONTAINER_METATABLE_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Container", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiContainer, GUI_CONTAINER_METATABLE_ID>);
    
    // Register Gui Editable Text metatable
    //metatableName = getMetatableName(E);
    //LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
    //        //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
    //        .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    //m_globals.Register("EditableText", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiButton, GUI_CONSOLE_METATABLE_ID>);

    // Register Gui Frame metatable
    metatableName = getMetatableName(GUI_FRAME_METATABLE_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Frame", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiFrame, GUI_FRAME_METATABLE_ID>);

    // Register Gui Label metatable
    metatableName = getMetatableName(GUI_LABEL_METATABLE_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Label", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiLabel, GUI_LABEL_METATABLE_ID>);

    // Register Gui Loader metatable
    metatableName = getMetatableName(GUI_CONSOLE_METATABLE_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Loader", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiLoader, GUI_CONSOLE_METATABLE_ID>);

    // Register Gui Menu metatable
    metatableName = getMetatableName(GUI_MENU_METATABLE_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Menu", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiMenu, GUI_MENU_METATABLE_ID>);

    // Register Gui MessageBox metatable
    metatableName = getMetatableName(GUI_MESSAGE_BOX_METATABLE_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("MessageBox", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiMessageBox, GUI_MESSAGE_BOX_METATABLE_ID>);

    // Register Gui Popup metatable
    metatableName = getMetatableName(GUI_POPUP_METATABLE_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Popup", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiPopup, GUI_POPUP_METATABLE_ID>);

    // Register Gui Progress Bar metatable
    metatableName = getMetatableName(GUI_PROGRESS_BAR_METATABLE_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("ProgressBar", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiProgressBar, GUI_PROGRESS_BAR_METATABLE_ID>);

    // Register Gui Scroll Area metatable
    metatableName = getMetatableName(GUI_SCROLL_AREA_METATABLE_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("ScrollArea", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiScrollArea, GUI_SCROLL_AREA_METATABLE_ID>);

    // Register Gui Table metatable
    metatableName = getMetatableName(GUI_TABLE_METATABLE_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Table", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiTable, GUI_TABLE_METATABLE_ID>);

    // Register Gui TextArea metatable
    metatableName = getMetatableName(GUI_TEXT_AREA_METATABLE_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("TextArea", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiTextArea, GUI_TEXT_AREA_METATABLE_ID>);

    // Register Gui Toggle Button metatable
    metatableName = getMetatableName(GUI_TOGGLE_BUTTON_METATABLE_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("ToggleButton", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiToggleButton, GUI_TOGGLE_BUTTON_METATABLE_ID>);

    // Register Gui Window metatable
    metatableName = getMetatableName(GUI_WINDOW_METATABLE_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Window", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiWindow, GUI_WINDOW_METATABLE_ID>);


#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}

/**
 * 
 * @return
 */
fgBool fgScriptSubsystem::registerStyleManager(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    if(!m_pStyleMgr)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    if(m_metatableStyleMgr.GetRef() >= 0)
        return FG_TRUE;
    if(m_globals.GetRef() < 0)
        return FG_FALSE;

#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}

/**
 * 
 * @return
 */
fgBool fgScriptSubsystem::registerSoundManager(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    if(!m_pSoundMgr)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    if(m_metatableSoundMgr.GetRef() >= 0)
        return FG_TRUE;
    if(m_globals.GetRef() < 0)
        return FG_FALSE;

#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}
