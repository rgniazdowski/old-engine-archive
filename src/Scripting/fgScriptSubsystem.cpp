/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgScriptSubsystem.h"

/*******************************************************************************
 * The  fact that  Script Subsystem  needs  some  access to  almost every  class
 * in the FG  universe is  OK - this  is the  whole idea. This  is  kind  of one
 * directional  relation.  Script  Subsystem  utilizes  some  tools to  bind  to
 * existing objects inside of the  engine, takes care of following  the pointers
 * checking if the objects are managed or not (if the obj is managed the manager
 * will release it) - the deletion/GC of  Lua side object doesn't  mean that any
 * kind destruction of C++ FG object will take place.
 * 
 * Also other parts of the engine do not care about the Script Subsystem - 
 * Some things need to happen behind the scenes ;p
 * 
 * However there is a downside to everything:  If  something  big changes in the 
 * system (some refactoring, new classes, different mechanism, addition of smart
 * pointer, custom new/delete, different memory management, etc) - those changes
 * will need  to be  reflected in here also.  It could be  different name of the 
 * some property, different function name, whatever.
 * 
 * This binding is not automated,  there is no generator to create some classes.
 * Good. Some mechanisms in here are  not universal for  every object. Not every
 * property needs to be accessible from scratch  and not every method() needs to
 * available. 
 ******************************************************************************/

// All metatables info - just names / ids generation
#include "fgScriptMT.h"
// Event manager
#include "Event/fgEventManager.h"
// Resource management
#include "Resource/fgResourceManager.h"
#include "Resource/fgResourceFactory.h"
// GFX / Scene management
#include "GFX/fgGFXSceneManager.h"
#include "GFX/Shaders/fgGFXShaderManager.h"
#include "GFX/Particles/fgParticleSystem.h"
// GUI - Widget/Style management
#include "GUI/fgGuiWidgetManager.h"
#include "GUI/fgGuiStyleManager.h"
// GUI - Font resource (?)
#include "GUI/Font/fgFontResource.h"
// GUI - Widget definitions
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
// Special Script Callback
#include "fgScriptCallback.h"

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
    userDataObjectMapItor it = m_userDataObjectMap.begin(),
            end = m_userDataObjectMap.end();
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

    fgScriptMT::clearMetatableNames();

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

    fgScriptMT::generateMetatableNames();

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
    FG_LOG_DEBUG("Script: ScriptSubsystem initialized in %.2f seconds", (t2 - t1) / 1000.0f);
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
    if(!state->IsUserdata(1)) {
        int isTable = (int)state->IsTable(1);
        int isNoneOrNil = (int)state->IsNoneOrNil(1);
        int isLightuserdata = (int)state->IsLightUserdata(1);
        int isUserdata = 0;
        FG_LOG_DEBUG("Script: Simple Free GC: not compatible: lightuserdata[%d], userdata[%d], table[%d], none/nil[%d]",
                     isLightuserdata,
                     isUserdata,
                     isTable,
                     isNoneOrNil);
        return 0;
    }
    void *unboxed = state->UnBoxPointer(1);
    if(!unboxed) {
        FG_LOG_DEBUG("Script: Simple Free GC: unboxed.ptr[nil]");
        return 0;
    }
    uintptr_t offset = (uintptr_t)unboxed;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it == m_userDataObjectMap.end()) {
        // The pointer is not registered
        FG_LOG_DEBUG("Script: Simple Free GC: pointer is not registered: ptr[%p], offset[%lu]", unboxed, offset);
        return 0;
    } else {
        m_userDataObjectMap.erase(it);
    }
    FG_LOG_DEBUG("Script: Simple Free GC: freeing memory: ptr[%p], offset[%lu]", unboxed, offset);
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
    if(!state->IsUserdata(1)) {
        int isTable = (int)state->IsTable(1);
        int isNoneOrNil = (int)state->IsNoneOrNil(1);
        int isLightuserdata = (int)state->IsLightUserdata(1);
        int isUserdata = 0;
        FG_LOG_DEBUG("Script: Managed Resource GC: not compatible: lightuserdata[%d], userdata[%d], table[%d], none/nil[%d]",
                     isLightuserdata,
                     isUserdata,
                     isTable,
                     isNoneOrNil);
        return 0;
    }
    void *unboxed = state->UnBoxPointer(1);
    if(!unboxed) {
        return 0;
    }
    fgResource *pResource = (fgResource *)unboxed;
    uintptr_t offset = (uintptr_t)pResource;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it == m_userDataObjectMap.end()) {
        // The pointer is not registered
        FG_LOG_DEBUG("Script: Managed Resource GC: pointer is not registered: ptr[%p], offset[%lu]", unboxed, offset);
        return 0;
    }
    pResource->dispose();
    FG_LOG_DEBUG("Script: Managed Resource GC: called dispose: name[%s], ptr[%p], offset[%lu]", pResource->getNameStr(), pResource, offset);
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
        FG_LOG_DEBUG("GC: Managed Object Destructor Callback: pointer is registered - will be deleted: ptr[%p], offset[%lu]", systemData, offset);
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

    //
    // #STRINGS #OBFUSCATION #FIXME #TODO
    //

    m_globals.SetInteger("FG_BUILD_VERSION", (int)FG_BUILD_VERSION);

    //
    // GUI STYLE CONSTANTS
    //
    m_globals.SetInteger("FG_GUI_FLOAT_UNIT_INVALID", (float)FG_GUI_FLOAT_UNIT_INVALID);

    // fgGuiUnitType
    m_globals.SetInteger("FG_GUI_PIXELS", (int)FG_GUI_PIXELS);
    m_globals.SetInteger("FG_GUI_INCHES", (int)FG_GUI_INCHES);
    m_globals.SetInteger("FG_GUI_BLOCKS", (int)FG_GUI_BLOCKS);
    m_globals.SetInteger("FG_GUI_PERCENTS", (int)FG_GUI_PERCENTS);
    // fgGuiBorderStyle
    m_globals.SetInteger("FG_GUI_BORDER_NONE", (int)FG_GUI_BORDER_NONE);
    m_globals.SetInteger("FG_GUI_BORDER_DOTTED", (int)FG_GUI_BORDER_DOTTED);
    m_globals.SetInteger("FG_GUI_BORDER_DASHED", (int)FG_GUI_BORDER_DASHED);
    m_globals.SetInteger("FG_GUI_BORDER_SOLID", (int)FG_GUI_BORDER_SOLID);

    // fgGuiBorderWhich
    m_globals.SetInteger("FG_GUI_BORDER_LEFT", (int)FG_GUI_BORDER_LEFT);
    m_globals.SetInteger("FG_GUI_BORDER_RIGHT", (int)FG_GUI_BORDER_RIGHT);
    m_globals.SetInteger("FG_GUI_BORDER_TOP", (int)FG_GUI_BORDER_TOP);
    m_globals.SetInteger("FG_GUI_BORDER_BOTTOM", (int)FG_GUI_BORDER_BOTTOM);
    m_globals.SetInteger("FG_GUI_BORDER_ALL", (int)FG_GUI_BORDER_ALL);

    // fgGuiBackgroundStyle
    m_globals.SetInteger("FG_GUI_BACKGROUND_NONE", (int)FG_GUI_BACKGROUND_NONE);
    m_globals.SetInteger("FG_GUI_BACKGROUND_NORMAL", (int)FG_GUI_BACKGROUND_NORMAL);
    m_globals.SetInteger("FG_GUI_BACKGROUND_MAX", (int)FG_GUI_BACKGROUND_MAX);
    m_globals.SetInteger("FG_GUI_BACKGROUND_TILED", (int)FG_GUI_BACKGROUND_TILED);

    // fgGuiMarginWhich
    m_globals.SetInteger("FG_GUI_MARGIN_LEFT", (int)FG_GUI_MARGIN_LEFT);
    m_globals.SetInteger("FG_GUI_MARGIN_RIGHT", (int)FG_GUI_MARGIN_RIGHT);
    m_globals.SetInteger("FG_GUI_MARGIN_TOP", (int)FG_GUI_MARGIN_TOP);
    m_globals.SetInteger("FG_GUI_MARGIN_BOTTOM", (int)FG_GUI_MARGIN_BOTTOM);
    m_globals.SetInteger("FG_GUI_MARGIN_ALL", (int)FG_GUI_MARGIN_ALL);

    // fgGuiPaddingWhich
    m_globals.SetInteger("FG_GUI_PADDING_LEFT", (int)FG_GUI_PADDING_LEFT);
    m_globals.SetInteger("FG_GUI_PADDING_RIGHT", (int)FG_GUI_PADDING_RIGHT);
    m_globals.SetInteger("FG_GUI_PADDING_TOP", (int)FG_GUI_PADDING_TOP);
    m_globals.SetInteger("FG_GUI_PADDING_BOTTOM", (int)FG_GUI_PADDING_BOTTOM);
    m_globals.SetInteger("FG_GUI_PADDING_ALL", (int)FG_GUI_PADDING_ALL);

    // fgGuiAlign
    m_globals.SetInteger("FG_GUI_ALIGN_NONE", (int)FG_GUI_ALIGN_NONE);
    m_globals.SetInteger("FG_GUI_ALIGN_LEFT", (int)FG_GUI_ALIGN_LEFT);
    m_globals.SetInteger("FG_GUI_ALIGN_RIGHT", (int)FG_GUI_ALIGN_RIGHT);
    m_globals.SetInteger("FG_GUI_ALIGN_CENTER", (int)FG_GUI_ALIGN_CENTER);
    m_globals.SetInteger("FG_GUI_ALIGN_MIDDLE", (int)FG_GUI_ALIGN_MIDDLE);
    m_globals.SetInteger("FG_GUI_ALIGN_TOP", (int)FG_GUI_ALIGN_TOP);
    m_globals.SetInteger("FG_GUI_ALIGN_BOTTOM", (int)FG_GUI_ALIGN_BOTTOM);

    // fgGuiPositionStyle
    m_globals.SetInteger("FG_GUI_POS_STATIC", (int)FG_GUI_POS_STATIC);
    m_globals.SetInteger("FG_GUI_POS_FIXED", (int)FG_GUI_POS_FIXED);
    m_globals.SetInteger("FG_GUI_POS_RELATIVE", (int)FG_GUI_POS_RELATIVE);
    m_globals.SetInteger("FG_GUI_POS_ABSOLUTE", (int)FG_GUI_POS_ABSOLUTE);

    // fgGuiSizeStyle
    m_globals.SetInteger("FG_GUI_SIZE_PIXELS", (int)FG_GUI_SIZE_PIXELS);
    m_globals.SetInteger("FG_GUI_SIZE_INCHES", (int)FG_GUI_SIZE_INCHES);
    m_globals.SetInteger("FG_GUI_SIZE_BLOCKS", (int)FG_GUI_SIZE_BLOCKS);
    m_globals.SetInteger("FG_GUI_SIZE_PERCENTS", (int)FG_GUI_SIZE_PERCENTS);
    m_globals.SetInteger("FG_GUI_SIZE_MAX", (int)FG_GUI_SIZE_MAX);
    m_globals.SetInteger("FG_GUI_SIZE_MIN", (int)FG_GUI_SIZE_MIN);

    //
    // GUI WIDGET CONSTANTS
    //
    m_globals.SetInteger("FG_GUI_WIDGET_STATE_NONE", (int)FG_GUI_WIDGET_STATE_NONE);
    m_globals.SetInteger("FG_GUI_WIDGET_STATE_FOCUS", (int)FG_GUI_WIDGET_STATE_FOCUS);
    m_globals.SetInteger("FG_GUI_WIDGET_STATE_PRESSED", (int)FG_GUI_WIDGET_STATE_PRESSED);
    m_globals.SetInteger("FG_GUI_WIDGET_STATE_ACTIVATED", (int)FG_GUI_WIDGET_STATE_ACTIVATED);
    m_globals.SetInteger("FG_GUI_WIDGET_STATE_DEACTIVATED", (int)FG_GUI_WIDGET_STATE_DEACTIVATED);
    m_globals.SetInteger("FG_GUI_WIDGET_STATE_COUNT", (int)FG_GUI_WIDGET_STATE_COUNT);


    //
    // EVENT TYPE CONSTANTS #FIXME #STRING #OBFUSCATION
    //

    m_globals.SetInteger("FG_EVENT_INVALID", (int)FG_EVENT_INVALID);

    m_globals.SetInteger("FG_EVENT_TOUCH_PRESSED", (int)FG_EVENT_TOUCH_PRESSED);
    m_globals.SetInteger("FG_EVENT_TOUCH_RELEASED", (int)FG_EVENT_TOUCH_RELEASED);
    m_globals.SetInteger("FG_EVENT_TOUCH_MOTION", (int)FG_EVENT_TOUCH_MOTION);
    m_globals.SetInteger("FG_EVENT_TOUCH_TAP_FINISHED", (int)FG_EVENT_TOUCH_TAP_FINISHED);
    m_globals.SetInteger("FG_EVENT_MOUSE_PRESSED", (int)FG_EVENT_MOUSE_PRESSED);
    m_globals.SetInteger("FG_EVENT_MOUSE_RELEASED", (int)FG_EVENT_MOUSE_RELEASED);
    m_globals.SetInteger("FG_EVENT_MOUSE_MOTION", (int)FG_EVENT_MOUSE_MOTION);
    m_globals.SetInteger("FG_EVENT_SWIPE_X", (int)FG_EVENT_SWIPE_X);
    m_globals.SetInteger("FG_EVENT_SWIPE_Y", (int)FG_EVENT_SWIPE_Y);
    m_globals.SetInteger("FG_EVENT_SWIPE_XY", (int)FG_EVENT_SWIPE_XY);
    m_globals.SetInteger("FG_EVENT_SWIPE_ANGLE", (int)FG_EVENT_SWIPE_ANGLE);
    m_globals.SetInteger("FG_EVENT_SWIPE_PINCH", (int)FG_EVENT_SWIPE_PINCH);
    m_globals.SetInteger("FG_EVENT_MULTI_SWIPE_ROTATE", (int)FG_EVENT_MULTI_SWIPE_ROTATE);
    m_globals.SetInteger("FG_EVENT_KEY_DOWN", (int)FG_EVENT_KEY_DOWN);
    m_globals.SetInteger("FG_EVENT_KEY_UP", (int)FG_EVENT_KEY_UP);

    m_globals.SetInteger("FG_EVENT_RESOURCE_CREATED", (int)FG_EVENT_RESOURCE_CREATED);
    m_globals.SetInteger("FG_EVENT_RESOURCE_REMOVED", (int)FG_EVENT_RESOURCE_REMOVED);
    m_globals.SetInteger("FG_EVENT_RESOURCE_DISPOSED", (int)FG_EVENT_RESOURCE_DISPOSED);
    m_globals.SetInteger("FG_EVENT_RESOURCE_DESTROYED", (int)FG_EVENT_RESOURCE_DESTROYED);
    m_globals.SetInteger("FG_EVENT_RESOURCE_REQUESTED", (int)FG_EVENT_RESOURCE_REQUESTED);

    m_globals.SetInteger("FG_EVENT_PROGRAM_INIT", (int)FG_EVENT_PROGRAM_INIT);
    m_globals.SetInteger("FG_EVENT_VERTEX_STREAM_READY", (int)FG_EVENT_VERTEX_STREAM_READY);
    m_globals.SetInteger("FG_EVENT_CAMERA_CHANGED", (int)FG_EVENT_CAMERA_CHANGED);
    m_globals.SetInteger("FG_EVENT_SOUND_PLAYED", (int)FG_EVENT_SOUND_PLAYED);
    m_globals.SetInteger("FG_EVENT_MENU_CHANGED", (int)FG_EVENT_MENU_CHANGED);
    m_globals.SetInteger("FG_EVENT_WIDGET_STATE_CHANGED", (int)FG_EVENT_WIDGET_STATE_CHANGED);
    m_globals.SetInteger("FG_EVENT_SENSORS_CHANGED", (int)FG_EVENT_SENSORS_CHANGED);

    m_globals.SetInteger("FG_EVENT_GAME_CONTROLLER_ADDED", (int)FG_EVENT_GAME_CONTROLLER_ADDED);
    m_globals.SetInteger("FG_EVENT_GAME_CONTROLLER_REMOVED", (int)FG_EVENT_GAME_CONTROLLER_REMOVED);
    m_globals.SetInteger("FG_EVENT_GAME_CONTROLLER_BUTTON", (int)FG_EVENT_GAME_CONTROLLER_BUTTON);
    m_globals.SetInteger("FG_EVENT_GAME_CONTROLLER_AXIS", (int)FG_EVENT_GAME_CONTROLLER_AXIS);

    //
    // SWIPE DIRECTION
    //
    m_globals.SetInteger("FG_SWIPE_INVALID", (int)FG_SWIPE_INVALID);
    m_globals.SetInteger("FG_SWIPE_LEFT", (int)FG_SWIPE_LEFT);
    m_globals.SetInteger("FG_SWIPE_RIGHT", (int)FG_SWIPE_RIGHT);
    m_globals.SetInteger("FG_SWIPE_UP", (int)FG_SWIPE_UP);
    m_globals.SetInteger("FG_SWIPE_DOWN", (int)FG_SWIPE_DOWN);
    m_globals.SetInteger("FG_SWIPE_ANGLE", (int)FG_SWIPE_ANGLE);

    //
    // PINCH DIRECTION
    //
    m_globals.SetInteger("FG_PINCH_INVALID", (int)FG_PINCH_INVALID);
    m_globals.SetInteger("FG_PINCH_IN", (int)FG_PINCH_IN);
    m_globals.SetInteger("FG_PINCH_OUT", (int)FG_PINCH_OUT);

    //
    // RESOURCE STATUS
    //
    m_globals.SetInteger("FG_RESOURCE_CREATED", (int)FG_RESOURCE_CREATED);
    m_globals.SetInteger("FG_RESOURCE_REMOVED", (int)FG_RESOURCE_REMOVED);
    m_globals.SetInteger("FG_RESOURCE_DISPOSED", (int)FG_RESOURCE_DISPOSED);
    m_globals.SetInteger("FG_RESOURCE_DESTROYED", (int)FG_RESOURCE_DESTROYED);
    m_globals.SetInteger("FG_RESOURCE_REQUESTED", (int)FG_RESOURCE_REQUESTED);

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
    LPCD::Class(m_luaState->GetCState(), fgScriptMT::getMetatableName(fgScriptMT::VECTOR2I_MT_ID))
            .Property("x", &fgVector2i::x)
            .Property("y", &fgVector2i::y)
            .Property("s", &fgVector2i::s)
            .Property("t", &fgVector2i::t)
            .MetatableFunction("__gc", &fgScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<fgVector2i>
    m_globals.Register("Vector2i", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector2i, fgScriptMT::VECTOR2I_MT_ID>);
    FG_LOG_DEBUG("Script: Register metatable '%s' for Vector2i", fgScriptMT::getMetatableName(fgScriptMT::VECTOR2I_MT_ID));

    // fgVector2f | FG VECTOR 2F
    LPCD::Class(m_luaState->GetCState(), fgScriptMT::getMetatableName(fgScriptMT::VECTOR2F_MT_ID))
            .Property("x", &fgVector2f::x)
            .Property("y", &fgVector2f::y)
            .Property("s", &fgVector2f::s)
            .Property("t", &fgVector2f::t)
            .MetatableFunction("__gc", &fgScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<fgVector2f>
    m_globals.Register("Vector2f", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector2f, fgScriptMT::VECTOR2F_MT_ID>);
    FG_LOG_DEBUG("Script: Register metatable '%s' for Vector2f", fgScriptMT::getMetatableName(fgScriptMT::VECTOR2F_MT_ID));

    // fgVector3i | FG VECTOR 3I    
    LPCD::Class(m_luaState->GetCState(), fgScriptMT::getMetatableName(fgScriptMT::VECTOR3I_MT_ID))
            .Property("x", &fgVector3i::x)
            .Property("y", &fgVector3i::y)
            .Property("z", &fgVector3i::z)
            .Property("r", &fgVector3i::r)
            .Property("g", &fgVector3i::g)
            .Property("b", &fgVector3i::b)
            .Property("s", &fgVector3i::s)
            .Property("t", &fgVector3i::t)
            .MetatableFunction("__gc", &fgScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<fgVector3i>
    m_globals.Register("Vector3i", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector3i, fgScriptMT::VECTOR3I_MT_ID>);
    FG_LOG_DEBUG("Script: Register metatable '%s' for Vector3i", fgScriptMT::getMetatableName(fgScriptMT::VECTOR3I_MT_ID));

    // fgVector3f | FG VECTOR 3F    
    LPCD::Class(m_luaState->GetCState(), fgScriptMT::getMetatableName(fgScriptMT::VECTOR3F_MT_ID))
            .Property("x", &fgVector3f::x)
            .Property("y", &fgVector3f::y)
            .Property("z", &fgVector3f::z)
            .Property("r", &fgVector3f::r)
            .Property("g", &fgVector3f::g)
            .Property("b", &fgVector3f::b)
            .Property("s", &fgVector3f::s)
            .Property("t", &fgVector3f::t)
            .MetatableFunction("__gc", &fgScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<fgVector3f>
    m_globals.Register("Vector3f", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector3f, fgScriptMT::VECTOR3F_MT_ID>);
    m_globals.Register("Color3f", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector3f, fgScriptMT::VECTOR3F_MT_ID>);
    FG_LOG_DEBUG("Script: Register metatable '%s' for Vector3f", fgScriptMT::getMetatableName(fgScriptMT::VECTOR3F_MT_ID));

    // fgVector4i | FG VECTOR 4I 
    LPCD::Class(m_luaState->GetCState(), fgScriptMT::getMetatableName(fgScriptMT::VECTOR4I_MT_ID))
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
    m_globals.Register("Vector4i", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector4i, fgScriptMT::VECTOR4I_MT_ID>);
    //m_globals.Register("Color4i", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector4i, fgScriptMetatables::VECTOR4I_MT_ID>);
    FG_LOG_DEBUG("Script: Register metatable '%s' for Vector4i", fgScriptMT::getMetatableName(fgScriptMT::VECTOR4I_MT_ID));

    // fgVector4f | FG VECTOR 4F    
    LPCD::Class(m_luaState->GetCState(), fgScriptMT::getMetatableName(fgScriptMT::VECTOR4F_MT_ID))
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
    m_globals.Register("Vector4f", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector4f, fgScriptMT::VECTOR4F_MT_ID>);
    m_globals.Register("Color4f", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector4f, fgScriptMT::VECTOR4F_MT_ID>);
    FG_LOG_DEBUG("Script: Register metatable '%s' for Vector4f", fgScriptMT::getMetatableName(fgScriptMT::VECTOR4F_MT_ID));
#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}

/**
 * 
 * @param L
 * @return 
 */
int fgScriptSubsystem::addEventCallbackWrapper(lua_State *L) {
#if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    LuaPlus::LuaStack args(state);
    const char *script = NULL;
    fgEventType eventType = FG_EVENT_INVALID;
    LuaPlus::LuaObject objFunction;
    fgBool hasFunction = FG_FALSE;
    int argc = 1;
    if(args.Count() == 0) {
        FG_LOG_DEBUG("Script: EventWrapper: empty argument list");
        return 0;
    }

    //
    // Need some automation for checking the list of arguments
    //
    //LUA_TNONE         (-1)
    //LUA_TNIL           0
    //LUA_TBOOLEAN       1
    //LUA_TLIGHTUSERDATA 2
    //LUA_TNUMBER        3
    //LUA_TSTRING        4
    //LUA_TTABLE         5
    //LUA_TFUNCTION      6
    //LUA_TUSERDATA      7
    //LUA_TTHREAD        8

    FG_LOG_DEBUG("Script: addEventCallbackWrapper: argc[%d]", args.Count());
    if(args.Count() >= 2) {
        int id = 1;
        if(args[id].IsInteger()) {
            int iVal = args[id].GetInteger();
            if(iVal < (int)FG_NUM_EVENT_TYPES)
                eventType = (fgEventType)iVal;
            FG_LOG_DEBUG("Script: EventWrapper: eventType[%d]", iVal);
        }
        id++;
        if(args[id].IsFunction()) {
            objFunction = args[id];
            hasFunction = FG_TRUE;
        } else if(args[id].IsString()) {
            script = args[id].GetString();
            FG_LOG_DEBUG("Script: EventWrapper: 2nd argument is a string[%s]", script);
        }
        id++;
        if(args.Count() >= 3) {
            if(args[id].IsInteger()) {
                argc = abs(args[id].GetInteger());
                FG_LOG_DEBUG("Script: EventWrapper: 3rd argument: argc[%d]", argc);
            }
        }
    }
    if(eventType == FG_EVENT_INVALID) {
        FG_LOG_DEBUG("Script: EventWrapper: event type is invalid");
        return 0;
    }
    if(!script && !hasFunction) {
        FG_LOG_DEBUG("Script: EventWrapper: No script nor function specified");
        return 0;
    }
    if(!m_pEventMgr)
        return 0;
    //if(m_pEventMgr->isInit()) {}
    if(m_pEventMgr->getManagerType() != FG_MANAGER_EVENT)
        return 0;

    fgFunctionCallback *callback = NULL;
    if(script) {
        callback = new fgScriptCallback(L, script, 0, fgScriptCallback::SCRIPT);
    } else if(hasFunction) {
        callback = new fgScriptCallback(L, objFunction, argc, fgScriptCallback::EVENT_CALLBACK);
    }
    if(static_cast<fgEventManager *>(m_pEventMgr)->addEventCallback(eventType, callback)) {
        FG_LOG_DEBUG("Script: Successfully added callback for event[%d]", eventType);
    } else {
        FG_LOG_DEBUG("Script: Failed to add callback for event[%d]", eventType);
    }
    // Can also return this pointer for future reference - so it is possible to remove
    // callback for given event type
#endif
    return 0;
}

/**
 * 
 * @param L
 * @return 
 */
int fgScriptSubsystem::addTimeoutCallbackWrapper(lua_State *L) {
#if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    LuaPlus::LuaStack args(state);
    const char *script = NULL;
    int timeout = -1;
    LuaPlus::LuaObject objFunction;
    fgBool hasFunction = FG_FALSE;
    int argc = 0;
    if(args.Count() == 0) {
        FG_LOG_DEBUG("Script: TimeoutWrapper: empty argument list");
        return 0;
    }
    FG_LOG_DEBUG("Script: addTimeoutCallbackWrapper: argc[%d]", args.Count());
    if(args.Count() >= 1) {
        int id = 1;

        if(args[id].IsFunction()) {
            objFunction = args[id];
            hasFunction = FG_TRUE;
        } else if(args[id].IsString()) {
            script = args[id].GetString();
            FG_LOG_DEBUG("Script: TimeoutWrapper: 1st argument is a string[%s]", script);
        }
        id++;
        if(args.Count() >= 2) {
            if(args[id].IsInteger()) {
                timeout = abs(args[id].GetInteger());
                FG_LOG_DEBUG("Script: TimeoutWrapper: 2nd argument: timeout[%d]", timeout);
            }
        }
    }
    if(!script && !hasFunction) {
        FG_LOG_DEBUG("Script: EventWrapper: No script nor function specified");
        return 0;
    }
    if(!m_pEventMgr)
        return 0;
    //if(m_pEventMgr->isInit()) {}
    if(m_pEventMgr->getManagerType() != FG_MANAGER_EVENT)
        return 0;
    if(timeout < 0)
        timeout = FG_TIMEOUT_CALLBACK_DEFAULT_TIMEOUT;
    fgFunctionCallback *callback = NULL;
    if(script) {
        callback = new fgScriptCallback(L, script, 0, fgScriptCallback::SCRIPT);
    } else if(hasFunction) {
        callback = new fgScriptCallback(L, objFunction, argc, fgScriptCallback::EVENT_CALLBACK);
    }
    if(static_cast<fgEventManager *>(m_pEventMgr)->addTimeoutCallback(callback, timeout, NULL)) {
        FG_LOG_DEBUG("Script: Successfully added timeout callback");
    } else {
        FG_LOG_DEBUG("Script: Failed to add timeout callback");
    }
    // Can also return this pointer for future reference - so it is possible to remove
    // callback for given event type
#endif
    return 0;
}

/**
 * 
 * @param L
 * @return 
 */
int fgScriptSubsystem::addCyclicCallbackWrapper(lua_State *L) {
#if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    LuaPlus::LuaStack args(state);
    const char *script = NULL;
    int interval = -1;
    int repeats = 0;
    LuaPlus::LuaObject objFunction;
    fgBool hasFunction = FG_FALSE;
    int argc = 0;
    if(args.Count() == 0) {
        FG_LOG_DEBUG("Script: CyclicWrapper: empty argument list");
        return 0;
    }
    FG_LOG_DEBUG("Script: addCyclicCallbackWrapper: argc[%d]", args.Count());
    if(args.Count() >= 1) {
        int id = 1;
        // Function
        if(args[id].IsFunction()) {
            objFunction = args[id];
            hasFunction = FG_TRUE;
        } else if(args[id].IsString()) {
            script = args[id].GetString();
            FG_LOG_DEBUG("Script: CyclicWrapper: 1st argument is a string[%s]", script);
        }
        id++;
        // Repeats
        if(args.Count() >= 2) {
            if(args[id].IsInteger()) {
                repeats = abs(args[id].GetInteger());
                FG_LOG_DEBUG("Script: CyclicWrapper: 2nd argument: repeats[%d]", repeats);
            }
        }
        id++;
        // Interval
        if(args.Count() >= 2) {
            if(args[id].IsInteger()) {
                interval = abs(args[id].GetInteger());
                FG_LOG_DEBUG("Script: CyclicWrapper: 3rd argument: interval[%d]", interval);
            }
        }
    }
    if(!script && !hasFunction) {
        FG_LOG_DEBUG("Script: CyclicWrapper: No script nor function specified");
        return 0;
    }
    if(!m_pEventMgr)
        return 0;
    //if(m_pEventMgr->isInit()) {}
    if(m_pEventMgr->getManagerType() != FG_MANAGER_EVENT)
        return 0;
    if(interval < 0)
        interval = FG_CYCLIC_CALLBACK_DEFAULT_INTERVAL;
    if(!repeats)
        repeats = FG_CYCLIC_CALLBACK_DEFAULT_REPEAT;
    fgFunctionCallback *callback = NULL;
    if(script) {
        callback = new fgScriptCallback(L, script, 0, fgScriptCallback::SCRIPT);
    } else if(hasFunction) {
        callback = new fgScriptCallback(L, objFunction, argc, fgScriptCallback::EVENT_CALLBACK);
    }
    if(static_cast<fgEventManager *>(m_pEventMgr)->addCyclicCallback(callback, repeats, interval, NULL)) {
        FG_LOG_DEBUG("Script: Successfully added cyclic callback");
    } else {
        FG_LOG_DEBUG("Script: Failed to add cyclic callback");
    }
    // Can also return this pointer for future reference - so it is possible to remove
    // callback for given event type
#endif
    return 0;
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

    m_metatableEventMgr = m_globals.CreateTable(fgScriptMT::getMetatableName(fgScriptMT::EVENT_MANAGER_MT_ID));
    m_metatableEventMgr.SetObject("__index", m_metatableEventMgr);
    //m_metatableEventMgr.RegisterObjectDirect("");
    // Could use Register direct? hmm?
    m_metatableEventMgr.Register("addEventCallback", &addEventCallbackWrapper);
    m_metatableEventMgr.Register("addTimeoutCallback", &addTimeoutCallbackWrapper);
    m_metatableEventMgr.Register("addCyclicCallback", &addCyclicCallbackWrapper);

    uintptr_t offset = (uintptr_t)m_pEventMgr;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        // This pointer is already registered ?
        return FG_FALSE;
    }
    LuaPlus::LuaObject eventMgrObj = m_luaState->BoxPointer((void *)m_pEventMgr);
    // Some functions ? anyone ? need special helper static funcs for EventMgr
    eventMgrObj.SetMetatable(m_metatableEventMgr);
    m_globals.SetObject("EventManager", eventMgrObj);
    m_userDataObjectMap[offset] = eventMgrObj;

    // Event Base structure
    const char *metatableNameEventBase = fgScriptMT::getMetatableName(fgScriptMT::EVENT_BASE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableNameEventBase)
            .Property("eventType", &fgEventBase::eventType)
            // .Property("eventType", &fgEventBase::eventType)
            // .Property("timeStamp", &fgEventBase::timeStamp) // Time stamp should be float ?
            ;
    //.MetatableFunction("__gc", &fgScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<fgVector2i>
    //m_globals.Register("Vector2i", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector2i, VECTOR2I_MT_ID>);
    //FG_LOG_DEBUG("Script: Register metatable '%s' for Vector2i", fgScriptMetatables::getMetatableName(fgScriptMetatables::VECTOR2I_MT_ID));

    // Controller Device Event : EventBase
    const char *metatableName = fgScriptMT::getMetatableName(fgScriptMT::EVENT_CONTROLLER_DEVICE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("which", &fgControllerDeviceEvent::which);
    // __gc ? nope

    // Controller Button Event : EventBase
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::EVENT_CONTROLLER_BUTTON_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("which", &fgControllerButtonEvent::which)
            .Property("button", &fgControllerButtonEvent::button)
            .Property("state", &fgControllerButtonEvent::state)
            ;
    // __gc ? nope

    // Controller Axis Event : EventBase
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::EVENT_CONTROLLER_AXIS_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("which", &fgControllerAxisEvent::which)
            .Property("value", &fgControllerAxisEvent::axis)
            .Property("axis", &fgControllerAxisEvent::value)
            ;
    // __gc ? nope

    // Touch Event : EventBase
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::EVENT_TOUCH_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("x", &fgTouchEvent::x)
            .Property("y", &fgTouchEvent::y)
            .Property("touchID", &fgTouchEvent::touchID)
            .Property("pressed", &fgTouchEvent::pressed)
            ;
    // __gc ? nope

    // Mouse Event : EventBase
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::EVENT_MOUSE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("x", &fgMouseEvent::x)
            .Property("y", &fgMouseEvent::y)
            .Property("buttonID", &fgMouseEvent::buttonID)
            .Property("pressed", &fgMouseEvent::pressed)
            ;
    // __gc ? nope

    // Swipe Event : EventBase #FIXME #REFACTOR
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::EVENT_SWIPE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("swipeDirection", &fgSwipeEvent::swipeDirection)
            .Property("xStart", &fgSwipeEvent::xStart)
            .Property("yStart", &fgSwipeEvent::yStart)
            .Property("xEnd", &fgSwipeEvent::xEnd)
            .Property("yEnd", &fgSwipeEvent::yEnd)
            .Property("swipeXOffset", &fgSwipeEvent::swipeXOffset)
            .Property("swipeYOffset", &fgSwipeEvent::swipeYOffset)
            .Property("swipeXSteps", &fgSwipeEvent::swipeXSteps)
            .Property("swipeYSteps", &fgSwipeEvent::swipeYSteps)
            ;
    // __gc ? nope

    //
    // Swipe Pinch Event : EventBase #FIXME #REFACTOR
    //
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::EVENT_SWIPE_PINCH_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("pinchDirection", &fgSwipePinchEvent::pinchDirection)
            .Property("x", &fgSwipePinchEvent::x)
            .Property("y", &fgSwipePinchEvent::y)
            .Property("x2", &fgSwipePinchEvent::x2)
            .Property("y2", &fgSwipePinchEvent::y2)
            .Property("pinchXOffset", &fgSwipePinchEvent::pinchXOffset)
            .Property("pinchYOffset", &fgSwipePinchEvent::pinchYOffset)
            .Property("pinchSize", &fgSwipePinchEvent::pinchSize)
            ;
    // __gc ? nope

    //
    // Swipe Rotate Event : EventBase
    //
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::EVENT_SWIPE_ROTATE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("x", &fgSwipeRotateEvent::x)
            .Property("y", &fgSwipeRotateEvent::y)
            .Property("x2", &fgSwipeRotateEvent::x2)
            .Property("y2", &fgSwipeRotateEvent::y2)
            .Property("angle", &fgSwipeRotateEvent::angle)
            ;
    // __gc ? nope

    // Key Event : EventBase
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::EVENT_KEY_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("keyCode", &fgKeyEvent::keyCode)
            .Property("which", &fgKeyEvent::which)
            .Property("pressed", &fgKeyEvent::pressed)
            ;
    // __gc ? nope

    // Resource Event : EventBase
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::EVENT_RESOURCE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("status", &fgResourceEvent::status)
            .Property("resource", &fgResourceEvent::resource) // need LPCD for fgResource * + type check
            ;
    // __gc ? nope

    // Vertex Stream Event : EventBase
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::EVENT_VERTEX_STREAM_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            //.Property("which", &::which)
            ;
    // __gc ? nope

    //
    // Camera Event : EventBase
    //
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::EVENT_CAMERA_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            ;
    // __gc ? nope

    //
    // Sound Event : EventBase
    //
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::EVENT_SOUND_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            ;
    // __gc ? nope

    // Menu Changed Event : EventBase
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::EVENT_MENU_CHANGED_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            ;
    // __gc ? nope

    //
    // Widget Event : EventBase
    //
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::EVENT_WIDGET_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            ;
    // __gc ? nope

    // 
    // Sensors Event : EventBase
    //
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::EVENT_SENSORS_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("x", &fgSensorsEvent::x)
            .Property("y", &fgSensorsEvent::y)
            .Property("z", &fgSensorsEvent::z)
            ;
    // __gc ? nope

    // Event Main Union structure
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::EVENT_MAIN_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName)
            .Property("eventType", &fgEvent::eventType)
            .Property("touch", &fgEvent::touch)
            .Property("mouse", &fgEvent::mouse)
            .Property("swipe", &fgEvent::swipe)
            .Property("swipePinch", &fgEvent::swipePinch)
            .Property("swipeRotate", &fgEvent::swipeRotate)
            .Property("key", &fgEvent::key)
            .Property("resource", &fgEvent::resource)
            .Property("vertexStream", &fgEvent::vertexStream)
            .Property("camera", &fgEvent::camera)
            .Property("sound", &fgEvent::sound)
            .Property("menuChanged", &fgEvent::menuChanged)
            .Property("widget", &fgEvent::widget)
            .Property("sensors", &fgEvent::sensors)
            .Property("controller", &fgEvent::controller)
            .Property("controllerAxis", &fgEvent::controllerAxis)
            .Property("controllerButton", &fgEvent::controllerButton)
            ;
    // __gc ? nope

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
    FG_LOG_DEBUG("Script: New Resource: argc[%d]", args.Count());
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
    FG_LOG_DEBUG("Script: New Resource: ptr[%p], offset[%lu]", pResource, offset);
    fgResourceType resType = pResource->getResourceType();
    fgScriptMT::METAID metaID = fgScriptMT::getMetatableIDFromResourceType(resType);
    if(metaID == fgScriptMT::EMPTY_MT_ID) {
        resourceObj.SetMetatable(LuaPlus::LuaObject());
        resourceObj.AssignNil();
        status = FG_FALSE;
        FG_LOG_DEBUG("Script: New Resource: Unknown resource type requested / not supported: resType[%d]", resType);
    }
    const char *metatableName = fgScriptMT::getMetatableName(metaID);
    if(status) {
        resourceObj.SetMetatable(state->GetRegistry()[metatableName]);
        FG_LOG_DEBUG("Script: New Resource: metatable: id[%d], name[%s]", metaID, metatableName);
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
    m_metatableResourceMgr = m_globals.CreateTable(fgScriptMT::getMetatableName(fgScriptMT::RESOURCE_MANAGER_MT_ID));
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
    LPCD::Class(m_luaState->GetCState(), fgScriptMT::getMetatableName(fgScriptMT::RESOURCE_MT_ID))
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
    LPCD::Class(m_luaState->GetCState(), fgScriptMT::getMetatableName(fgScriptMT::TEXTURE_RESOURCE_MT_ID), fgScriptMT::getMetatableName(fgScriptMT::RESOURCE_MT_ID))
            .ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
            .ObjectDirect("getHeight", (fgTextureResource *)0, &fgTextureResource::getHeight)
            .ObjectDirect("getComponents", (fgTextureResource *)0, &fgTextureResource::getComponents)
            .MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent);

    // Register Font Resource metatable
    LPCD::Class(m_luaState->GetCState(), fgScriptMT::getMetatableName(fgScriptMT::FONT_RESOURCE_MT_ID), fgScriptMT::getMetatableName(fgScriptMT::TEXTURE_RESOURCE_MT_ID))
            .ObjectDirect("getFontType", (fgFontResource *)0, &fgFontResource::getFontType)
            .ObjectDirect("getStep", (fgFontResource *)0, &fgFontResource::getStep)
            .MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent);

    // Register Gfx Model Resource metatable
    LPCD::Class(m_luaState->GetCState(), fgScriptMT::getMetatableName(fgScriptMT::GFX_MODEL_RESOURCE_MT_ID), fgScriptMT::getMetatableName(fgScriptMT::RESOURCE_MT_ID))
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

    LPCD::Class(m_luaState->GetCState(), fgScriptMT::getMetatableName(fgScriptMT::PARTICLE_EFFECT_RESOURCE_MT_ID), fgScriptMT::getMetatableName(fgScriptMT::RESOURCE_MT_ID))
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

    // Particle system/manager metatable
    m_metatableParticleMgr = m_globals.CreateTable(fgScriptMT::getMetatableName(fgScriptMT::PARTICLE_SYSTEM_MT_ID));
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

    typedef fgBool(fgGuiWidgetManager::*GWM_Bool_Widget_IN)(fgGuiWidget *);
    typedef fgBool(fgGuiWidgetManager::*GWM_Bool_Widget_Widget_IN)(fgGuiWidget *, fgGuiWidget *);
    typedef fgBool(fgGuiWidgetManager::*GWM_Bool_C_STR_IN)(const char *);
    typedef fgGuiWidget * (fgGuiWidgetManager::*GWM_Widget_C_STR_IN)(const char *);

    // Widget manager metatable
    m_metatableWidgetMgr = m_globals.CreateTable(fgScriptMT::getMetatableName(fgScriptMT::WIDGET_MANAGER_MT_ID));
    m_metatableWidgetMgr.SetObject("__index", m_metatableWidgetMgr);
    m_metatableWidgetMgr.RegisterObjectDirect("addWidget",
                                              (fgGuiWidgetManager *)0,
                                              static_cast<GWM_Bool_Widget_IN>(&fgGuiWidgetManager::addWidget));

    m_metatableWidgetMgr.RegisterObjectDirect("addWidgetWithFather",
                                              (fgGuiWidgetManager *)0,
                                              static_cast<GWM_Bool_Widget_Widget_IN>(&fgGuiWidgetManager::addWidget));

    m_metatableWidgetMgr.RegisterObjectDirect("removeWidget",
                                              (fgGuiWidgetManager *)0,
                                              static_cast<GWM_Bool_Widget_IN>(&fgGuiWidgetManager::remove));

    m_metatableWidgetMgr.RegisterObjectDirect("removeWidgetByName",
                                              (fgGuiWidgetManager *)0,
                                              static_cast<GWM_Bool_C_STR_IN>(&fgGuiWidgetManager::remove));

    m_metatableWidgetMgr.RegisterObjectDirect("getWidget",
                                              (fgGuiWidgetManager *)0,
                                              static_cast<GWM_Widget_C_STR_IN>(&fgGuiWidgetManager::get));
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
    typedef void (fgGuiWidget::base_type::*GW_BASE_void_C_STR_IN)(const char *);
    typedef fgGuiWidget * (fgGuiWidget::*GW_Widget_void)(void)const;

    const char *metatableNameWidget = fgScriptMT::getMetatableName(fgScriptMT::GUI_WIDGET_MT_ID);
    const char *metatableName = NULL;
    // Register Base Widget metatable
    LPCD::Class(m_luaState->GetCState(), metatableNameWidget)
            .ObjectDirect("getName", (fgGuiWidget::base_type *)0, &fgGuiWidget::base_type::getNameStr)
            .ObjectDirect("setName",
                          (fgGuiWidget::base_type *)0,
                          static_cast<GW_BASE_void_C_STR_IN>(&fgGuiWidget::base_type::setName))

            .ObjectDirect("isManaged",
                          (fgGuiWidget::base_type *)0,
                          &fgGuiWidget::base_type::isManaged)

            .ObjectDirect("setFlags",
                          (fgGuiWidget *)0,
                          static_cast<GW_void_C_STR_IN>(&fgGuiWidget::setFlags))

            .ObjectDirect("refresh", (fgGuiWidget *)0, &fgGuiWidget::refresh)
            //.ObjectDirect("updateState", (fgGuiWidget *)0, &fgGuiWidget::updateState)
            .ObjectDirect("getFather",
                          (fgGuiWidget *)0,
                          static_cast<GW_Widget_void>(&fgGuiWidget::getFather))
            .ObjectDirect("getType", (fgGuiWidget *)0, &fgGuiWidget::getType)
            .ObjectDirect("getTypeTraits", (fgGuiWidget *)0, &fgGuiWidget::getTypeTraits)
            .ObjectDirect("getTypeName", (fgGuiWidget *)0, &fgGuiWidget::getTypeNameStr)
            .ObjectDirect("setVisible", (fgGuiWidget *)0, &fgGuiWidget::setVisible)
            .ObjectDirect("isVisible", (fgGuiWidget *)0, &fgGuiWidget::isVisible)
            .ObjectDirect("setActive", (fgGuiWidget *)0, &fgGuiWidget::setActive)
            .ObjectDirect("isActive", (fgGuiWidget *)0, &fgGuiWidget::isActive)
            .ObjectDirect("setIgnoreState", (fgGuiWidget *)0, &fgGuiWidget::setIgnoreState)
            .ObjectDirect("isIgnoreState", (fgGuiWidget *)0, &fgGuiWidget::isIgnoreState)
            //.ObjectDirect("doesIgnoreState", (fgGuiWidget *)0, &fgGuiWidget::doesIgnoreState)
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
            .ObjectDirect("getStyleContent", (fgGuiWidget *)0, &fgGuiWidget::getStyleContentPtr)
            //.ObjectDirect("refresh", (fgGuiWidget *)0, &fgGuiWidget::setOnFocusCallback)
            ;
    //.MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent);

    // Register Gui Button metatable
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_BUTTON_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Button", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiButton, fgScriptMT::GUI_BUTTON_MT_ID>);

    // Register Gui Toggle Button metatable
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_TOGGLE_BUTTON_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT::getMetatableName(fgScriptMT::GUI_BUTTON_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("ToggleButton", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiToggleButton, fgScriptMT::GUI_TOGGLE_BUTTON_MT_ID>);

    typedef fgBool(fgGuiContainer::*GCNT_Bool_C_STR_IN)(const char *);
    typedef fgBool(fgGuiContainer::*GCNT_Bool_Widget_IN)(fgGuiWidget *);

    // Register Gui Container metatable
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_CONTAINER_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            .ObjectDirect("addChild", (fgGuiContainer *)0, &fgGuiContainer::addChild)

            .ObjectDirect("removeChild",
                          (fgGuiContainer *)0,
                          static_cast<GCNT_Bool_Widget_IN>(&fgGuiContainer::removeChild))

            .ObjectDirect("removeChildByName",
                          (fgGuiContainer *)0,
                          static_cast<GCNT_Bool_C_STR_IN>(&fgGuiContainer::removeChild))

            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Container", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiContainer, fgScriptMT::GUI_CONTAINER_MT_ID>);

    // Register Gui Editable Text metatable
    //metatableName = fgScriptMetatables::getMetatableName(E);
    //LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
    //        //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
    //        .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    //m_globals.Register("EditableText", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiButton, fgScriptMetatables::GUI_CONSOLE_MT_ID>);

    // Register Gui Frame metatable
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_FRAME_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT::getMetatableName(fgScriptMT::GUI_CONTAINER_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Frame", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiFrame, fgScriptMT::GUI_FRAME_MT_ID>);

    // Register Gui Label metatable
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_LABEL_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Label", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiLabel, fgScriptMT::GUI_LABEL_MT_ID>);

    // Register Gui Loader metatable
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_LOADER_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Loader", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiLoader, fgScriptMT::GUI_LOADER_MT_ID>);

    // Register Gui Menu metatable
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_MENU_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT::getMetatableName(fgScriptMT::GUI_CONTAINER_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Menu", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiMenu, fgScriptMT::GUI_MENU_MT_ID>);

    // Register Gui Window metatable
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_WINDOW_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT::getMetatableName(fgScriptMT::GUI_CONTAINER_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Window", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiWindow, fgScriptMT::GUI_WINDOW_MT_ID>);

    // Register Gui MessageBox metatable
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_MESSAGE_BOX_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT::getMetatableName(fgScriptMT::GUI_WINDOW_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("MessageBox", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiMessageBox, fgScriptMT::GUI_MESSAGE_BOX_MT_ID>);

    // Register Gui Popup metatable
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_POPUP_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT::getMetatableName(fgScriptMT::GUI_WINDOW_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Popup", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiPopup, fgScriptMT::GUI_POPUP_MT_ID>);

    // Register Gui Progress Bar metatable
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_PROGRESS_BAR_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("ProgressBar", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiProgressBar, fgScriptMT::GUI_PROGRESS_BAR_MT_ID>);

    // Register Gui Scroll Area metatable
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_SCROLL_AREA_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT::getMetatableName(fgScriptMT::GUI_CONTAINER_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("ScrollArea", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiScrollArea, fgScriptMT::GUI_SCROLL_AREA_MT_ID>);

    // Register Gui Table metatable
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_TABLE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT::getMetatableName(fgScriptMT::GUI_CONTAINER_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Table", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiTable, fgScriptMT::GUI_TABLE_MT_ID>);

    // Register Gui TextArea metatable
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_TEXT_AREA_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT::getMetatableName(fgScriptMT::GUI_SCROLL_AREA_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("TextArea", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiTextArea, fgScriptMT::GUI_TEXT_AREA_MT_ID>);

    // Register Gui Console metatable
    metatableName = fgScriptMT::getMetatableName(fgScriptMT::GUI_CONSOLE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT::getMetatableName(fgScriptMT::GUI_TEXT_AREA_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_globals.Register("Console", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiConsole, fgScriptMT::GUI_CONSOLE_MT_ID>);

    //
    // Styles / Style Content and other builtin
    // Some of these (StyleContent and inside types) cannot be
    // created via constructor inside of the script, only referenced
    // The metatable for these will not have __gc function set
    // #SAFEDESIGN #FIXME #PTRSAFE
    //
    typedef void (fgGuiStyle::*GS_void_C_STR_IN)(const char *);
    typedef void (fgGuiStyle::base_type::base_type::*GS_BASE_void_C_STR_IN)(const char *);
    typedef fgGuiStyleContent * (fgGuiStyle::*GS_StyleContent_C_STR_IN)(const char *);

    // Register Gui Style metatable
    //
    // #FIXME - will need to create base metatable for ManagedObject
    // because there are many types that shader that base class
    // Thanks to this there will be less copy pasting of the same 
    // function pointers definitions ...
    // 
    const char *metatableNameStyle = fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableNameStyle)
            .ObjectDirect("getName",
                          (fgGuiStyle::base_type::base_type *)0,
                          &fgGuiStyle::base_type::base_type::getNameStr)
            .ObjectDirect("setName",
                          (fgGuiStyle::base_type::base_type *)0,
                          static_cast<GS_BASE_void_C_STR_IN>(&fgGuiStyle::base_type::base_type::setName))

            .ObjectDirect("getContentByName",
                          (fgGuiStyle *)0,
                          static_cast<GS_StyleContent_C_STR_IN>(&fgGuiStyle::getContentPtr))
            ;
    // fgGuiStyle FUBAR ^ ^ ^ ^ ^ ^ ^ ^ ^

    // Register Built in types for fgGuiStyleContent
    // Remember: Need definitions for special functions in LPCD namespace
    // Templates for Push/Match/Get -- types like: fgGuiSize/Background/Border
    // fgGuiAlign is an enum (not strong typed) so it will be implicitly cast to int

    // Register fgGuiSize structure ...
    // This structure cannot be created inside of lua, only received via reference
    // from style content obj
    LPCD::Class(m_luaState->GetCState(), fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_SIZE_MT_ID))
            .Property("style", &fgGuiSize::style)
            .Property("x", &fgGuiSize::x)
            .Property("y", &fgGuiSize::y)
            .Property("z", &fgGuiSize::z)
            .Property("w", &fgGuiSize::w)
            .Property("h", &fgGuiSize::h)
            .Property("d", &fgGuiSize::d);
    // MetatableFunction("__gc") // Nope

    // Register fgGuiBackground structure
    LPCD::Class(m_luaState->GetCState(), fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_BACKGROUND_MT_ID))
            .Property("texture", &fgGuiBackground::texture) // std::string
            .Property("color", &fgGuiBackground::color) // color is fgColor4f/fgVector4f (glm)
            .Property("style", &fgGuiBackground::style) // enum fgGuiBackgroundStyle (int)
            ;
    // MetatableFunction("__gc") // Nope

    // Register fgGuiForeground structure
    LPCD::Class(m_luaState->GetCState(), fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_FOREGROUND_MT_ID))
            .Property("font", &fgGuiForeground::font) // std::string - font name
            .Property("color", &fgGuiForeground::color) // color is fgColor4f/fgVector4f (glm)
            .Property("textSize", &fgGuiForeground::textSize) // float
            ;
    // MetatableFunction("__gc") // Nope

    // Register fgGuiMargin/fgGuiPadding structure
    LPCD::Class(m_luaState->GetCState(), fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_MARGIN_MT_ID))
            .Property("left", &fgGuiMargin::left) // float
            .Property("right", &fgGuiMargin::right) // float
            .Property("top", &fgGuiMargin::top) // float
            .Property("bottom", &fgGuiMargin::bottom) // float
            ;
    // MetatableFunction("__gc") // Nope

    // Register fgGuiBorder structure
    LPCD::Class(m_luaState->GetCState(), fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_BORDER_MT_ID))
            .Property("color", &fgGuiBorder::color) // color is fgColor4f/fgVector4f (glm)
            .Property("style", &fgGuiBorder::style) // enum fgGuiBorderStyle (int)
            .Property("width", &fgGuiBorder::width) // float
            ;
    // MetatableFunction("__gc") // Nope

    // Register fgGuiBorderInfo structure (stores info for all borders)
    LPCD::Class(m_luaState->GetCState(), fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_BORDER_INFO_MT_ID))
            .Property("left", &fgGuiBorderInfo::left) // structure fgGuiBorder
            .Property("right", &fgGuiBorderInfo::right) // structure fgGuiBorder 
            .Property("top", &fgGuiBorderInfo::top) // structure fgGuiBorder
            .Property("bottom", &fgGuiBorderInfo::bottom) // structure fgGuiBorder
            ;
    // MetatableFunction("__gc") // Nope

    // Register fgGuiPosition structure
    LPCD::Class(m_luaState->GetCState(), fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_POSITION_MT_ID))
            .Property("style", &fgGuiPosition::style) // enum fgGuiPositionStyle (int)
            .Property("unit", &fgGuiPosition::unit) // enum fgGuiUnitType (int)
            .Property("left", &fgGuiPosition::left) // float
            .Property("right", &fgGuiPosition::right) // float
            .Property("top", &fgGuiPosition::top) // float
            .Property("bottom", &fgGuiPosition::bottom) // float
            .Property("front", &fgGuiPosition::front) // float
            .Property("back", &fgGuiPosition::back) // float
            ;
    // MetatableFunction("__gc") // Nope

    // Register Gui Style Content metatable - this metatable is without GC ! ! !
    //    
    const char *metatableNameStyleContent = fgScriptMT::getMetatableName(fgScriptMT::GUI_STYLE_CONTENT_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableNameStyleContent)
            //.Property("shader", &fgGuiStyle) // NOPE ?
            .ObjectDirect("getBackground", (fgGuiStyleContent *)0, &fgGuiStyleContent::getBackground)
            .ObjectDirect("getForeground", (fgGuiStyleContent *)0, &fgGuiStyleContent::getForeground)
            .ObjectDirect("getMargin", (fgGuiStyleContent *)0, &fgGuiStyleContent::getMargin)
            .ObjectDirect("getPadding", (fgGuiStyleContent *)0, &fgGuiStyleContent::getPadding)
            .ObjectDirect("getBorderInfo", (fgGuiStyleContent *)0, &fgGuiStyleContent::getBorder)
            .ObjectDirect("getBorder", (fgGuiStyleContent *)0, &fgGuiStyleContent::getBorder)
            .ObjectDirect("getPosition", (fgGuiStyleContent *)0, &fgGuiStyleContent::getPosition)
            .ObjectDirect("getAlign", (fgGuiStyleContent *)0, &fgGuiStyleContent::getAlign)
            .ObjectDirect("getVAlign", (fgGuiStyleContent *)0, &fgGuiStyleContent::getVAlign)
            .ObjectDirect("getTextAlign", (fgGuiStyleContent *)0, &fgGuiStyleContent::getTextAlign)
            .ObjectDirect("getSize", (fgGuiStyleContent *)0, &fgGuiStyleContent::getSize)
            .ObjectDirect("getShaderStr", (fgGuiStyleContent *)0, &fgGuiStyleContent::getShaderStr)
            .ObjectDirect("getEffectStr", (fgGuiStyleContent *)0, &fgGuiStyleContent::getEffectStr)
            //.ObjectDirect("", (fgGuiStyleContent *)0, &fgGuiStyleContent::)
            // Will not add any other functions (setters) because they return reference to self
            // This will force Lua to create an object which will be GCed quite fast
            // Need to reinforce StyleContent somehow
            ;

    // MetatableFunction("__gc") // Nope
    // No GC for Style Content ....
    // Whenever ! Wherever !
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
