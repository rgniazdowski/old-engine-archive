/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
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
 * However there is a downside to everything:a  If  something  big changes in the 
 * system (some refactoring, new classes, different mechanism, addition of smart
 * pointer, custom new/delete, different memory management, etc) - those changes
 * will need  to be  reflected in here also.  It could be  different name of the 
 * some property, different function name, whatever.
 * 
 * This binding is not automated,  there is no generator to create some classes.
 * Good. Some mechanisms in here are  not universal for  every object. Not every
 * property needs to be accessible from scratch  and not every method() needs to
 * be available. 
 ******************************************************************************/

// All metatables info - just names / ids generation
//#include "fgScriptMetatables.h"
// Callback dispatcher template specializations
#include "fgScriptCD.h"
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
#include "GUI/fgGuiMain.h"
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
// Game Logic / etc
#include "GameLogic/fgGameLogic.h"
// Special Script Callback
#include "fgScriptCallback.h"
#include "Audio/fgSFXMusicResource.h"
#include "Audio/fgSFXManager.h"
#include "Util/fgStrings.h"
#include "GFX/fgGFX3DScene.h"

#if defined(FG_USING_LUA_PLUS)
///
LuaPlus::LuaState *fgScriptSubsystem::m_luaState = NULL;
///
LuaPlus::LuaObject fgScriptSubsystem::m_globals;
///
LuaPlus::LuaObject fgScriptSubsystem::m_fgObj;
///
fgScriptSubsystem::userDataObjectMap fgScriptSubsystem::m_userDataObjectMap;
#else 
void *fgScriptSubsystem::m_luaState = NULL;
#endif /* FG_USING_LUA_PLUS */

///
fgBool fgScriptSubsystem::m_isBindingComplete = FG_FALSE;

/// Pointer to the external GUI Main object
fg::base::CManager *fgScriptSubsystem::m_pGuiMain = NULL;
/// Pointer to the external Event manager
fg::base::CManager *fgScriptSubsystem::m_pEventMgr = NULL;
/// Pointer to the external Resource manager
fg::base::CManager *fgScriptSubsystem::m_pResourceMgr = NULL;
/// Pointer to the external GFX Shader manager
fg::base::CManager *fgScriptSubsystem::m_pShaderMgr = NULL;
/// Pointer to the external 2D Scene manager
fg::base::CManager *fgScriptSubsystem::m_p2DSceneMgr = NULL;
/// Pointer to the external 3D Scene manager
fg::base::CManager *fgScriptSubsystem::m_p3DSceneMgr = NULL;
/// Pointer to the external Particle manager
fg::base::CManager *fgScriptSubsystem::m_pParticleMgr = NULL;
/// Pointer to the external GUI Widget manager
fg::base::CManager *fgScriptSubsystem::m_pWidgetMgr = NULL;
/// Pointer to the external GUI Style manager
fg::base::CManager *fgScriptSubsystem::m_pStyleMgr = NULL;
/// Pointer to the external Sound manager
fg::base::CManager *fgScriptSubsystem::m_pSoundMgr = NULL;
/// Pointer to the external Game Logic manager
fg::base::CManager *fgScriptSubsystem::m_pLogicMgr = NULL;

/**
 * 
 */
fgScriptSubsystem::fgScriptSubsystem()
#if defined(FG_USING_LUA_PLUS)
#endif /* FG_USING_LUA_PLUS */
{
    m_managerType = FG_MANAGER_SCRIPT;
    m_cyclicGCCallback = new fgPlainFunctionCallback(&fgScriptSubsystem::cyclicGCFunction, NULL);
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
    m_cyclicGCCallback = NULL;
    m_managerType = FG_MANAGER_SCRIPT;
}

/**
 * 
 * @param systemData
 * @param userData
 * @return 
 */
fgBool fgScriptSubsystem::cyclicGCFunction(void* systemData, void* userData) {
    if(!m_luaState)
        return FG_FALSE;
    if(!m_isBindingComplete)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    //m_luaState->GC();
    FG_LOG_DEBUG("Script: GC: Calling Garbage Collector...");
    int bytesBefore = m_luaState->GC(LUA_GCCOUNTB, 0);
    m_luaState->GC(LUA_GCCOLLECT, 0);
    int bytesAfter = m_luaState->GC(LUA_GCCOUNTB, 0);
    FG_LOG_DEBUG("Script: GC: before[%d], after[%d]", bytesBefore, bytesAfter);
#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}

/**
 * 
 * @param filePath
 * @return 
 */
int fgScriptSubsystem::executeFile(const char *filePath) {
    if(!m_luaState || !filePath) {
        return 2;
    }
    /**
     *  LUA_OK		0
     *  LUA_YIELD	1
     *  LUA_ERRRUN	2
     *  LUA_ERRSYNTAX	3
     *  LUA_ERRMEM	4
     *  LUA_ERRGCMM	5
     *  LUA_ERRERR	6
     */
    if(!m_isBindingComplete) {
        return 2;
    }
    fg::util::DataFile scriptFile;
    if(!scriptFile.open(filePath, fg::util::File::Mode::READ)) {
        FG_LOG_ERROR("Script: Unable to open script file: '%s'", filePath);
        return 2;
    }
    char *buffer = scriptFile.load();
    if(!buffer) {
        FG_LOG_ERROR("Script: Unable to load script file into buffer: '%s'", filePath);
        return 2;
    }
    scriptFile.close();
    const char *fileName = fg::path::fileName(filePath);
    int size = strlen(buffer), status = 0;
#if defined(FG_USING_LUA_PLUS)
    status = m_luaState->DoBuffer(buffer, size, fileName);
    if(status != 0) {
        int top = m_luaState->GetTop();
        if(m_luaState->IsString(top)) {
            FG_LOG_ERROR("Script: Error occurred while running script: '%s'", filePath);
            FG_LOG_ERROR("Script: Script trace: %s", m_luaState->CheckString(top));
        }
    }
#elif defined(FG_USING_LUA)
    status = (luaL_loadbuffer(m_luaState, buffer, size, fileName) || lua_pcall(m_luaState, 0, 0, 0));
#endif    
    fgFree(buffer);
    return status;
}

/**
 * 
 * @return 
 */
fgBool fgScriptSubsystem::destroy(void) {
    if(!m_init)
        return FG_FALSE;

    if(m_pEventMgr) {
        if(m_cyclicGCCallback) {
            static_cast<fg::event::CEventManager *>(m_pEventMgr)->removeCyclicCallback(m_cyclicGCCallback);
            delete m_cyclicGCCallback;
        }
        m_cyclicGCCallback = NULL;
    }

#if defined(FG_USING_LUA_PLUS)
    m_globals.Reset();
    for(int i = 0; i < NUM_MGR_METATABLES; i++)
        m_mgrMetatables[i].Reset();
    userDataObjectMapItor it = m_userDataObjectMap.begin(),
            end = m_userDataObjectMap.end();
    for(; it != end; it++) {
        userDataObjectMap::value_type &pair = *it;
        pair.second.obj.Reset();
    }
    if(m_luaState)
        LuaPlus::LuaState::Destroy(m_luaState);
    m_luaState = NULL;
    m_userDataObjectMap.clear();
    userDataObjectMap dmmap;
    m_userDataObjectMap.swap(dmmap);
#endif /* FG_USING_LUA_PLUS */

    m_isBindingComplete = FG_FALSE;
    m_init = FG_FALSE;

    fgScriptMT->deleteInstance();
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
        FG_LOG_ERROR("Script: Failed to initialize main state");
        return FG_FALSE;
    }
    m_globals = m_luaState->GetGlobals();
#endif /* FG_USING_LUA_PLUS */

    fgScriptMT->generateMetatableNames();

    // Register main 'fg' global object (namespace)
    {
        m_mgrMetatables[FG_NAMESPACE] = m_globals.CreateTable(fgScriptMT->getMetatableName(fgScriptMetatables::FG_NAMESPACE_MT_ID));
        m_mgrMetatables[FG_NAMESPACE].SetObject("__index", m_mgrMetatables[FG_NAMESPACE]);
        m_fgObj = m_luaState->CreateTable();
        m_fgObj.SetMetatable(m_mgrMetatables[FG_NAMESPACE]); // ? # ?
        m_globals.SetObject("fg", m_fgObj);
    }

    if(!registerConstants()) {
        FG_LOG_ERROR("Script: Failed to register global constants");
    }

    if(!registerAdditionalTypes()) {
        FG_LOG_ERROR("Script: Failed to register additional types");
    }

    if(!registerEventManager()) {
        FG_LOG_ERROR("Script: Failed to register EventManager object");
    }

    if(!registerResourceManager()) {
        FG_LOG_ERROR("Script: Failed to register ResourceManager object");
    }

    if(!registerShaderManager()) {
        FG_LOG_ERROR("Script: Failed to register ShaderManager object");
    }

    if(!register2DSceneManager()) {
        FG_LOG_ERROR("Script: Failed to register 2DSceneManager object");
    }

    if(!register3DSceneManager()) {
        FG_LOG_ERROR("Script: Failed to register 3DSceneManager object");
    }

    if(!registerParticleSystem()) {
        FG_LOG_ERROR("Script: Failed to register ParticleSystem object");
    }

    if(!registerGuiMain()) {
        FG_LOG_ERROR("Script: Failed to register GuiMain object");
    }

    if(!registerWidgetManager()) {
        FG_LOG_ERROR("Script: Failed to register WidgetManager object");
    }

    if(!registerStyleManager()) {
        FG_LOG_ERROR("Script: Failed to register StyleManager object");
    }

    if(!registerSoundManager()) {
        FG_LOG_ERROR("Script: Failed to register SoundManager object");
    }

    if(!registerLogicManager()) {
        FG_LOG_ERROR("Script: Failed to register GameLogicManager object");
    }

    float t2 = fgTime::ms();
    FG_LOG_DEBUG("Script: ScriptSubsystem initialized in %.2f seconds", (t2 - t1) / 1000.0f);
    m_init = FG_TRUE;
    m_isBindingComplete = FG_TRUE;
    m_managerType = FG_MANAGER_SCRIPT;

    if(m_cyclicGCCallback) {
        static_cast<fg::event::CEventManager *>(m_pEventMgr)->addCyclicCallback(m_cyclicGCCallback,
                                                                                FG_CYCLIC_CALLBACK_INFINITE_REPEAT,
                                                                                FG_SCRIPT_DEFAULT_GC_INTERVAL,
                                                                                NULL);
    }

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
    // It's quite possible that Resource do not need any kind of management from the script level
    // They're always loaded/created using external ResMgr functions
    // ResourceManager manages the data so...
    return 0; // # RESOURCE GC EVENT - EMPTY
#if 0
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    //get the pointer Lua is trying to delete.
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
    fgBool isRegistered = FG_TRUE;
    fgResource *pResource = (fgResource *)unboxed;
    uintptr_t offset = (uintptr_t)pResource;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it == m_userDataObjectMap.end()) {
        isRegistered = FG_FALSE;
    }
    if(isRegistered) {
        if(!((*it).second.isBound)) {
            isRegistered = FG_FALSE;
        }
    }
    if(!isRegistered) {
        // The pointer is not registered
        FG_LOG_DEBUG("Script: Managed Resource GC: pointer is not registered: ptr[%p], offset[%lu]", unboxed, offset);
        return 0;
    }
    //pResource->dispose();
    //FG_LOG_DEBUG("Script: Managed Resource GC: called dispose: name[%s], ptr[%p], offset[%lu]", pResource->getNameStr(), pResource, offset);
#endif /* if 0 */
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

#if defined(FG_USING_LUA_PLUS)
    uintptr_t offset = (uintptr_t)systemData;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        // This pointer was stored - erase it

        if((*it).second.obj.GetRef() > 0 && (*it).second.isBound) {
            (*it).second.obj.SetMetatable(LuaPlus::LuaObject());
            (*it).second.obj.AssignNil();
        }
        (*it).second.obj.Reset();

        FG_LOG_DEBUG("GC: Managed Object Destructor Callback: pointer is registered - will be deleted: ptr[%p], offset[%lu]", systemData, offset);
        m_userDataObjectMap.erase(it);
    }
#endif /* FG_USING_LUA_PLUS */
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
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;

    //
    // #STRINGS #OBFUSCATION #FIXME #TODO
    //

    m_fgObj.SetInteger("BUILD_VERSION", (int)FG_BUILD_VERSION);

    //
    // GUI STYLE CONSTANTS
    //
    m_fgObj.SetInteger("GUI_FLOAT_UNIT_INVALID", (float)FG_GUI_FLOAT_UNIT_INVALID);

    // fgGuiUnitType
    m_fgObj.SetInteger("GUI_PIXELS", (int)FG_GUI_PIXELS);
    m_fgObj.SetInteger("GUI_INCHES", (int)FG_GUI_INCHES);
    m_fgObj.SetInteger("GUI_BLOCKS", (int)FG_GUI_BLOCKS);
    m_fgObj.SetInteger("GUI_PERCENTS", (int)FG_GUI_PERCENTS);
    // fgGuiBorderStyle
    m_fgObj.SetInteger("GUI_BORDER_NONE", (int)FG_GUI_BORDER_NONE);
    m_fgObj.SetInteger("GUI_BORDER_DOTTED", (int)FG_GUI_BORDER_DOTTED);
    m_fgObj.SetInteger("GUI_BORDER_DASHED", (int)FG_GUI_BORDER_DASHED);
    m_fgObj.SetInteger("GUI_BORDER_SOLID", (int)FG_GUI_BORDER_SOLID);

    // fgGuiBorderWhich
    m_fgObj.SetInteger("GUI_BORDER_LEFT", (int)FG_GUI_BORDER_LEFT);
    m_fgObj.SetInteger("GUI_BORDER_RIGHT", (int)FG_GUI_BORDER_RIGHT);
    m_fgObj.SetInteger("GUI_BORDER_TOP", (int)FG_GUI_BORDER_TOP);
    m_fgObj.SetInteger("GUI_BORDER_BOTTOM", (int)FG_GUI_BORDER_BOTTOM);
    m_fgObj.SetInteger("GUI_BORDER_ALL", (int)FG_GUI_BORDER_ALL);

    // fgGuiBackgroundStyle
    m_fgObj.SetInteger("GUI_BACKGROUND_NONE", (int)FG_GUI_BACKGROUND_NONE);
    m_fgObj.SetInteger("GUI_BACKGROUND_NORMAL", (int)FG_GUI_BACKGROUND_NORMAL);
    m_fgObj.SetInteger("GUI_BACKGROUND_MAX", (int)FG_GUI_BACKGROUND_MAX);
    m_fgObj.SetInteger("GUI_BACKGROUND_TILED", (int)FG_GUI_BACKGROUND_TILED);

    // fgGuiMarginWhich
    m_fgObj.SetInteger("GUI_MARGIN_LEFT", (int)FG_GUI_MARGIN_LEFT);
    m_fgObj.SetInteger("GUI_MARGIN_RIGHT", (int)FG_GUI_MARGIN_RIGHT);
    m_fgObj.SetInteger("GUI_MARGIN_TOP", (int)FG_GUI_MARGIN_TOP);
    m_fgObj.SetInteger("GUI_MARGIN_BOTTOM", (int)FG_GUI_MARGIN_BOTTOM);
    m_fgObj.SetInteger("GUI_MARGIN_ALL", (int)FG_GUI_MARGIN_ALL);

    // fgGuiPaddingWhich
    m_fgObj.SetInteger("GUI_PADDING_LEFT", (int)FG_GUI_PADDING_LEFT);
    m_fgObj.SetInteger("GUI_PADDING_RIGHT", (int)FG_GUI_PADDING_RIGHT);
    m_fgObj.SetInteger("GUI_PADDING_TOP", (int)FG_GUI_PADDING_TOP);
    m_fgObj.SetInteger("GUI_PADDING_BOTTOM", (int)FG_GUI_PADDING_BOTTOM);
    m_fgObj.SetInteger("GUI_PADDING_ALL", (int)FG_GUI_PADDING_ALL);

    // fgGuiAlign
    m_fgObj.SetInteger("GUI_ALIGN_NONE", (int)FG_GUI_ALIGN_NONE);
    m_fgObj.SetInteger("GUI_ALIGN_LEFT", (int)FG_GUI_ALIGN_LEFT);
    m_fgObj.SetInteger("GUI_ALIGN_RIGHT", (int)FG_GUI_ALIGN_RIGHT);
    m_fgObj.SetInteger("GUI_ALIGN_CENTER", (int)FG_GUI_ALIGN_CENTER);
    m_fgObj.SetInteger("GUI_ALIGN_MIDDLE", (int)FG_GUI_ALIGN_MIDDLE);
    m_fgObj.SetInteger("GUI_ALIGN_TOP", (int)FG_GUI_ALIGN_TOP);
    m_fgObj.SetInteger("GUI_ALIGN_BOTTOM", (int)FG_GUI_ALIGN_BOTTOM);

    // fgGuiPositionStyle
    m_fgObj.SetInteger("GUI_POS_STATIC", (int)FG_GUI_POS_STATIC);
    m_fgObj.SetInteger("GUI_POS_FIXED", (int)FG_GUI_POS_FIXED);
    m_fgObj.SetInteger("GUI_POS_RELATIVE", (int)FG_GUI_POS_RELATIVE);
    m_fgObj.SetInteger("GUI_POS_ABSOLUTE", (int)FG_GUI_POS_ABSOLUTE);

    // fgGuiSizeStyle
    m_fgObj.SetInteger("GUI_SIZE_PIXELS", (int)FG_GUI_SIZE_PIXELS);
    m_fgObj.SetInteger("GUI_SIZE_INCHES", (int)FG_GUI_SIZE_INCHES);
    m_fgObj.SetInteger("GUI_SIZE_BLOCKS", (int)FG_GUI_SIZE_BLOCKS);
    m_fgObj.SetInteger("GUI_SIZE_PERCENTS", (int)FG_GUI_SIZE_PERCENTS);
    m_fgObj.SetInteger("GUI_SIZE_MAX", (int)FG_GUI_SIZE_MAX);
    m_fgObj.SetInteger("GUI_SIZE_MIN", (int)FG_GUI_SIZE_MIN);

    //
    // GUI WIDGET CONSTANTS
    //
    m_fgObj.SetInteger("GUI_WIDGET_STATE_NONE", (int)FG_GUI_WIDGET_STATE_NONE);
    m_fgObj.SetInteger("GUI_WIDGET_STATE_FOCUS", (int)FG_GUI_WIDGET_STATE_FOCUS);
    m_fgObj.SetInteger("GUI_WIDGET_STATE_PRESSED", (int)FG_GUI_WIDGET_STATE_PRESSED);
    m_fgObj.SetInteger("GUI_WIDGET_STATE_ACTIVATED", (int)FG_GUI_WIDGET_STATE_ACTIVATED);
    m_fgObj.SetInteger("GUI_WIDGET_STATE_DEACTIVATED", (int)FG_GUI_WIDGET_STATE_DEACTIVATED);
    m_fgObj.SetInteger("GUI_WIDGET_STATE_COUNT", (int)FG_GUI_WIDGET_STATE_COUNT);

    //
    // GUI WIDGET CALLBACK TYPE CONSTANTS        
    //
    m_fgObj.SetInteger("GUI_WIDGET_CALLBACK_INVALID", (int)FG_GUI_WIDGET_CALLBACK_INVALID);
    m_fgObj.SetInteger("GUI_WIDGET_CALLBACK_ON_FOCUS", (int)FG_GUI_WIDGET_CALLBACK_ON_FOCUS);
    m_fgObj.SetInteger("GUI_WIDGET_CALLBACK_ON_FOCUS_GAIN", (int)FG_GUI_WIDGET_CALLBACK_ON_FOCUS_GAIN);
    m_fgObj.SetInteger("GUI_WIDGET_CALLBACK_ON_FOCUS_LOST", (int)FG_GUI_WIDGET_CALLBACK_ON_FOCUS_LOST);
    m_fgObj.SetInteger("GUI_WIDGET_CALLBACK_ON_CLICK", (int)FG_GUI_WIDGET_CALLBACK_ON_CLICK);
    m_fgObj.SetInteger("GUI_WIDGET_CALLBACK_ON_ACTIVATE", (int)FG_GUI_WIDGET_CALLBACK_ON_ACTIVATE);
    m_fgObj.SetInteger("GUI_WIDGET_CALLBACK_ON_DEACTIVATE", (int)FG_GUI_WIDGET_CALLBACK_ON_DEACTIVATE);
    m_fgObj.SetInteger("GUI_WIDGET_CALLBACK_ON_KEY", (int)FG_GUI_WIDGET_CALLBACK_ON_KEY);
    m_fgObj.SetInteger("GUI_WIDGET_CALLBACK_ON_MOUSE", (int)FG_GUI_WIDGET_CALLBACK_ON_KEY);
    m_fgObj.SetInteger("GUI_WIDGET_CALLBACK_ON_CHANGE_STATE", (int)FG_GUI_WIDGET_CALLBACK_ON_KEY);
    m_fgObj.SetInteger("GUI_WIDGET_CALLBACK_NUM", (int)FG_GUI_WIDGET_CALLBACK_ON_KEY);


    //
    // EVENT TYPE CONSTANTS #FIXME #STRING #OBFUSCATION
    //

    m_fgObj.SetInteger("EVENT_INVALID", (int)FG_EVENT_INVALID);

    m_fgObj.SetInteger("EVENT_TOUCH_PRESSED", (int)FG_EVENT_TOUCH_PRESSED);
    m_fgObj.SetInteger("EVENT_TOUCH_RELEASED", (int)FG_EVENT_TOUCH_RELEASED);
    m_fgObj.SetInteger("EVENT_TOUCH_MOTION", (int)FG_EVENT_TOUCH_MOTION);
    m_fgObj.SetInteger("EVENT_TOUCH_TAP_FINISHED", (int)FG_EVENT_TOUCH_TAP_FINISHED);
    m_fgObj.SetInteger("EVENT_MOUSE_PRESSED", (int)FG_EVENT_MOUSE_PRESSED);
    m_fgObj.SetInteger("EVENT_MOUSE_RELEASED", (int)FG_EVENT_MOUSE_RELEASED);
    m_fgObj.SetInteger("EVENT_MOUSE_MOTION", (int)FG_EVENT_MOUSE_MOTION);
    m_fgObj.SetInteger("EVENT_SWIPE_X", (int)FG_EVENT_SWIPE_X);
    m_fgObj.SetInteger("EVENT_SWIPE_Y", (int)FG_EVENT_SWIPE_Y);
    m_fgObj.SetInteger("EVENT_SWIPE_XY", (int)FG_EVENT_SWIPE_XY);
    m_fgObj.SetInteger("EVENT_SWIPE_ANGLE", (int)FG_EVENT_SWIPE_ANGLE);
    m_fgObj.SetInteger("EVENT_SWIPE_PINCH", (int)FG_EVENT_SWIPE_PINCH);
    m_fgObj.SetInteger("EVENT_MULTI_SWIPE_ROTATE", (int)FG_EVENT_MULTI_SWIPE_ROTATE);
    m_fgObj.SetInteger("EVENT_KEY_DOWN", (int)FG_EVENT_KEY_DOWN);
    m_fgObj.SetInteger("EVENT_KEY_UP", (int)FG_EVENT_KEY_UP);

    m_fgObj.SetInteger("EVENT_RESOURCE_CREATED", (int)FG_EVENT_RESOURCE_CREATED);
    m_fgObj.SetInteger("EVENT_RESOURCE_REMOVED", (int)FG_EVENT_RESOURCE_REMOVED);
    m_fgObj.SetInteger("EVENT_RESOURCE_DISPOSED", (int)FG_EVENT_RESOURCE_DISPOSED);
    m_fgObj.SetInteger("EVENT_RESOURCE_DESTROYED", (int)FG_EVENT_RESOURCE_DESTROYED);
    m_fgObj.SetInteger("EVENT_RESOURCE_REQUESTED", (int)FG_EVENT_RESOURCE_REQUESTED);

    m_fgObj.SetInteger("EVENT_PROGRAM_INIT", (int)FG_EVENT_PROGRAM_INIT);
    m_fgObj.SetInteger("EVENT_VERTEX_STREAM_READY", (int)FG_EVENT_VERTEX_STREAM_READY);
    m_fgObj.SetInteger("EVENT_CAMERA_CHANGED", (int)FG_EVENT_CAMERA_CHANGED);
    m_fgObj.SetInteger("EVENT_SOUND_PLAYED", (int)FG_EVENT_SOUND_PLAYED);
    m_fgObj.SetInteger("EVENT_MENU_CHANGED", (int)FG_EVENT_MENU_CHANGED);
    m_fgObj.SetInteger("EVENT_WIDGET_STATE_CHANGED", (int)FG_EVENT_WIDGET_STATE_CHANGED);
    m_fgObj.SetInteger("EVENT_SENSORS_CHANGED", (int)FG_EVENT_SENSORS_CHANGED);

    m_fgObj.SetInteger("EVENT_GAME_CONTROLLER_ADDED", (int)FG_EVENT_GAME_CONTROLLER_ADDED);
    m_fgObj.SetInteger("EVENT_GAME_CONTROLLER_REMOVED", (int)FG_EVENT_GAME_CONTROLLER_REMOVED);
    m_fgObj.SetInteger("EVENT_GAME_CONTROLLER_BUTTON", (int)FG_EVENT_GAME_CONTROLLER_BUTTON);
    m_fgObj.SetInteger("EVENT_GAME_CONTROLLER_AXIS", (int)FG_EVENT_GAME_CONTROLLER_AXIS);

    //
    // GAME LOGIC EVENT TYPE CONSTANTS
    //
    m_fgObj.SetInteger("EVENT_GAME_STARTED", (int)FG_EVENT_GAME_STARTED);
    m_fgObj.SetInteger("EVENT_GAME_PAUSED", (int)FG_EVENT_GAME_PAUSED);
    m_fgObj.SetInteger("EVENT_GAME_STOPPED", (int)FG_EVENT_GAME_STOPPED);
    m_fgObj.SetInteger("EVENT_GAME_LOADING", (int)FG_EVENT_GAME_LOADING);
    m_fgObj.SetInteger("EVENT_GAME_RESTARTING", (int)FG_EVENT_GAME_RESTARTING);
    m_fgObj.SetInteger("EVENT_GAME_FINISHED", (int)FG_EVENT_GAME_FINISHED);
    m_fgObj.SetInteger("EVENT_GAME_WAITING", (int)FG_EVENT_GAME_WAITING);
    m_fgObj.SetInteger("EVENT_GAME_CONNECTED", (int)FG_EVENT_GAME_CONNECTED);
    m_fgObj.SetInteger("EVENT_GAME_DISCONNECTED", (int)FG_EVENT_GAME_DISCONNECTED);

    //
    // SWIPE DIRECTION
    //
    m_fgObj.SetInteger("SWIPE_INVALID", (int)FG_SWIPE_INVALID);
    m_fgObj.SetInteger("SWIPE_LEFT", (int)FG_SWIPE_LEFT);
    m_fgObj.SetInteger("SWIPE_RIGHT", (int)FG_SWIPE_RIGHT);
    m_fgObj.SetInteger("SWIPE_UP", (int)FG_SWIPE_UP);
    m_fgObj.SetInteger("SWIPE_DOWN", (int)FG_SWIPE_DOWN);
    m_fgObj.SetInteger("SWIPE_ANGLE", (int)FG_SWIPE_ANGLE);

    //
    // PINCH DIRECTION
    //
    m_fgObj.SetInteger("PINCH_INVALID", (int)FG_PINCH_INVALID);
    m_fgObj.SetInteger("PINCH_IN", (int)FG_PINCH_IN);
    m_fgObj.SetInteger("PINCH_OUT", (int)FG_PINCH_OUT);

    //
    // RESOURCE STATUS
    //
    m_fgObj.SetInteger("RESOURCE_CREATED", (int)FG_RESOURCE_CREATED);
    m_fgObj.SetInteger("RESOURCE_REMOVED", (int)FG_RESOURCE_REMOVED);
    m_fgObj.SetInteger("RESOURCE_DISPOSED", (int)FG_RESOURCE_DISPOSED);
    m_fgObj.SetInteger("RESOURCE_DESTROYED", (int)FG_RESOURCE_DESTROYED);
    m_fgObj.SetInteger("RESOURCE_REQUESTED", (int)FG_RESOURCE_REQUESTED);

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
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;

    // fgVector2i | FG VECTOR 2I    
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::VECTOR2I_MT_ID))
            .Property("x", &fgVector2i::x)
            .Property("y", &fgVector2i::y)
            .Property("s", &fgVector2i::s)
            .Property("t", &fgVector2i::t)
            .MetatableFunction("__gc", &fgScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<fgVector2i>
    m_fgObj.Register("Vector2i", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector2i, fgScriptMetatables::VECTOR2I_MT_ID>);
    FG_LOG_DEBUG("Script: Register metatable '%s' for Vector2i", fgScriptMT->getMetatableName(fgScriptMetatables::VECTOR2I_MT_ID));

    // fgVector2f | FG VECTOR 2F
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::VECTOR2F_MT_ID))
            .Property("x", &fgVector2f::x)
            .Property("y", &fgVector2f::y)
            .Property("s", &fgVector2f::s)
            .Property("t", &fgVector2f::t)
            .MetatableFunction("__gc", &fgScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<fgVector2f>
    m_fgObj.Register("Vector2f", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector2f, fgScriptMetatables::VECTOR2F_MT_ID>);
    FG_LOG_DEBUG("Script: Register metatable '%s' for Vector2f", fgScriptMT->getMetatableName(fgScriptMetatables::VECTOR2F_MT_ID));

    // fgVector3i | FG VECTOR 3I    
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::VECTOR3I_MT_ID))
            .Property("x", &fgVector3i::x)
            .Property("y", &fgVector3i::y)
            .Property("z", &fgVector3i::z)
            .Property("r", &fgVector3i::r)
            .Property("g", &fgVector3i::g)
            .Property("b", &fgVector3i::b)
            .Property("s", &fgVector3i::s)
            .Property("t", &fgVector3i::t)
            .MetatableFunction("__gc", &fgScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<fgVector3i>
    m_fgObj.Register("Vector3i", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector3i, fgScriptMetatables::VECTOR3I_MT_ID>);
    FG_LOG_DEBUG("Script: Register metatable '%s' for Vector3i", fgScriptMT->getMetatableName(fgScriptMetatables::VECTOR3I_MT_ID));

    // fgVector3f | FG VECTOR 3F    
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::VECTOR3F_MT_ID))
            .Property("x", &fgVector3f::x)
            .Property("y", &fgVector3f::y)
            .Property("z", &fgVector3f::z)
            .Property("r", &fgVector3f::r)
            .Property("g", &fgVector3f::g)
            .Property("b", &fgVector3f::b)
            .Property("s", &fgVector3f::s)
            .Property("t", &fgVector3f::t)
            .MetatableFunction("__gc", &fgScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<fgVector3f>
    m_fgObj.Register("Vector3f", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector3f, fgScriptMetatables::VECTOR3F_MT_ID>);
    m_fgObj.Register("Color3f", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector3f, fgScriptMetatables::VECTOR3F_MT_ID>);
    FG_LOG_DEBUG("Script: Register metatable '%s' for Vector3f", fgScriptMT->getMetatableName(fgScriptMetatables::VECTOR3F_MT_ID));

    // fgVector4i | FG VECTOR 4I 
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::VECTOR4I_MT_ID))
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
    m_fgObj.Register("Vector4i", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector4i, fgScriptMetatables::VECTOR4I_MT_ID>);
    //m_fgObj.Register("Color4i", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector4i, fgScriptMetatables::VECTOR4I_MT_ID>);
    FG_LOG_DEBUG("Script: Register metatable '%s' for Vector4i", fgScriptMT->getMetatableName(fgScriptMetatables::VECTOR4I_MT_ID));

    // fgVector4f | FG VECTOR 4F    
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::VECTOR4F_MT_ID))
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
    m_fgObj.Register("Vector4f", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector4f, fgScriptMetatables::VECTOR4F_MT_ID>);
    m_fgObj.Register("Color4f", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector4f, fgScriptMetatables::VECTOR4F_MT_ID>);
    FG_LOG_DEBUG("Script: Register metatable '%s' for Vector4f", fgScriptMT->getMetatableName(fgScriptMetatables::VECTOR4F_MT_ID));
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
            //if(iVal < (int)FG_NUM_EVENT_TYPES)
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
    if(static_cast<fg::event::CEventManager *>(m_pEventMgr)->addEventCallback(eventType, callback)) {
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
    if(static_cast<fg::event::CEventManager *>(m_pEventMgr)->addTimeoutCallback(callback, timeout, NULL)) {
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
    if(static_cast<fg::event::CEventManager *>(m_pEventMgr)->addCyclicCallback(callback, repeats, interval, NULL)) {
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
    if(m_mgrMetatables[EVENT_MGR].GetRef() >= 0)
        return FG_TRUE;
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;

    m_mgrMetatables[EVENT_MGR] = m_fgObj.CreateTable(fgScriptMT->getMetatableName(fgScriptMetatables::EVENT_MANAGER_MT_ID));
    m_mgrMetatables[EVENT_MGR].SetObject("__index", m_mgrMetatables[EVENT_MGR]);
    //m_mgrMetatables[EVENT_MGR].RegisterObjectDirect("");
    // Could use Register direct? hmm?
    m_mgrMetatables[EVENT_MGR].Register("addEventCallback", &addEventCallbackWrapper);
    m_mgrMetatables[EVENT_MGR].Register("addTimeoutCallback", &addTimeoutCallbackWrapper);
    m_mgrMetatables[EVENT_MGR].Register("addCyclicCallback", &addCyclicCallbackWrapper);

    uintptr_t offset = (uintptr_t)m_pEventMgr;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        // This pointer is already registered ?
        return FG_FALSE;
    }
    LuaPlus::LuaObject eventMgrObj = m_luaState->BoxPointer((void *)m_pEventMgr);
    // Some functions ? anyone ? need special helper static funcs for EventMgr
    eventMgrObj.SetMetatable(m_mgrMetatables[EVENT_MGR]);
    m_fgObj.SetObject("EventManager", eventMgrObj);

    m_userDataObjectMap[offset].obj = eventMgrObj;
    m_userDataObjectMap[offset].isBound = FG_TRUE;

    // Event Base structure
    const char *metatableNameEventBase = fgScriptMT->getMetatableName(fgScriptMetatables::EVENT_BASE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableNameEventBase)
            .Property("eventType", &fgEventBase::eventType)
            // .Property("eventType", &fgEventBase::eventType)
            // .Property("timeStamp", &fgEventBase::timeStamp) // Time stamp should be float ?
            ;
    //.MetatableFunction("__gc", &fgScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<fgVector2i>
    //m_fgObj.Register("Vector2i", &fgScriptSubsystem::simpleTypedMallocEvent<fgVector2i, VECTOR2I_MT_ID>);
    //FG_LOG_DEBUG("Script: Register metatable '%s' for Vector2i", fgScriptMT->getMetatableName(fgScriptMetatables::VECTOR2I_MT_ID));

    // Controller Device Event : EventBase
    const char *metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::EVENT_CONTROLLER_DEVICE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("which", &fgControllerDeviceEvent::which);
    // __gc ? nope

    // Controller Button Event : EventBase
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::EVENT_CONTROLLER_BUTTON_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("which", &fgControllerButtonEvent::which)
            .Property("button", &fgControllerButtonEvent::button)
            .Property("state", &fgControllerButtonEvent::state)
            ;
    // __gc ? nope

    // Controller Axis Event : EventBase
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::EVENT_CONTROLLER_AXIS_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("which", &fgControllerAxisEvent::which)
            .Property("value", &fgControllerAxisEvent::axis)
            .Property("axis", &fgControllerAxisEvent::value)
            ;
    // __gc ? nope

    // Touch Event : EventBase
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::EVENT_TOUCH_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("x", &fgTouchEvent::x)
            .Property("y", &fgTouchEvent::y)
            .Property("touchID", &fgTouchEvent::touchID)
            .Property("pressed", &fgTouchEvent::pressed)
            ;
    // __gc ? nope

    // Mouse Event : EventBase
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::EVENT_MOUSE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("x", &fgMouseEvent::x)
            .Property("y", &fgMouseEvent::y)
            .Property("buttonID", &fgMouseEvent::buttonID)
            .Property("pressed", &fgMouseEvent::pressed)
            ;
    // __gc ? nope

    // Swipe Event : EventBase #FIXME #REFACTOR
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::EVENT_SWIPE_MT_ID);
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
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::EVENT_SWIPE_PINCH_MT_ID);
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
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::EVENT_SWIPE_ROTATE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("x", &fgSwipeRotateEvent::x)
            .Property("y", &fgSwipeRotateEvent::y)
            .Property("x2", &fgSwipeRotateEvent::x2)
            .Property("y2", &fgSwipeRotateEvent::y2)
            .Property("angle", &fgSwipeRotateEvent::angle)
            ;
    // __gc ? nope

    // Key Event : EventBase
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::EVENT_KEY_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("keyCode", &fgKeyEvent::keyCode)
            .Property("which", &fgKeyEvent::which)
            .Property("pressed", &fgKeyEvent::pressed)
            ;
    // __gc ? nope

    // Resource Event : EventBase
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::EVENT_RESOURCE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("status", &fgResourceEvent::status)
            .Property("resource", &fgResourceEvent::resource) // need LPCD for fgResource * + type check
            ;
    // __gc ? nope

    // Vertex Stream Event : EventBase
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::EVENT_VERTEX_STREAM_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            //.Property("which", &::which)
            ;
    // __gc ? nope

    //
    // Camera Event : EventBase
    //
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::EVENT_CAMERA_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            ;
    // __gc ? nope

    //
    // Sound Event : EventBase
    //
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::EVENT_SOUND_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            ;
    // __gc ? nope

    // Menu Changed Event : EventBase
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::EVENT_MENU_CHANGED_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            ;
    // __gc ? nope

    //
    // Widget Event : EventBase
    //
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::EVENT_WIDGET_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            ;
    // __gc ? nope

    // 
    // Sensors Event : EventBase
    //
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::EVENT_SENSORS_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("x", &fgSensorsEvent::x)
            .Property("y", &fgSensorsEvent::y)
            .Property("z", &fgSensorsEvent::z)
            ;
    // __gc ? nope

    // Event Main Union structure
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::EVENT_MAIN_MT_ID);
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
    fgScriptMetatables::METAID metaID = fgScriptMT->getMetatableIDFromResourceType(resType);
    if(metaID == fgScriptMetatables::EMPTY_MT_ID) {
        resourceObj.SetMetatable(LuaPlus::LuaObject());
        resourceObj.AssignNil();
        status = FG_FALSE;
        FG_LOG_DEBUG("Script: New Resource: Unknown resource type requested / not supported: resType[%d]", resType);
    }
    const char *metatableName = fgScriptMT->getMetatableName(metaID);
    if(status) {
        resourceObj.SetMetatable(state->GetRegistry()[metatableName]);
        FG_LOG_DEBUG("Script: New Resource: metatable: id[%d], name[%s]", metaID, metatableName);
    }
    if(it == m_userDataObjectMap.end() && offset) {
        m_userDataObjectMap[offset] = userDataObject(resourceObj, FG_TRUE);
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
    if(m_mgrMetatables[RESOURCE_MGR].GetRef() >= 0)
        return FG_TRUE;
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;

    // Resource manager metatable
    m_mgrMetatables[RESOURCE_MGR] = m_fgObj.CreateTable(fgScriptMT->getMetatableName(fgScriptMetatables::RESOURCE_MANAGER_MT_ID));
    m_mgrMetatables[RESOURCE_MGR].SetObject("__index", m_mgrMetatables[RESOURCE_MGR]);
    m_mgrMetatables[RESOURCE_MGR].Register("request", &fgScriptSubsystem::newResourceWrapper);

    uintptr_t offset = (uintptr_t)m_pResourceMgr;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        return FG_FALSE;
    }
    // Create lua object for resource manager global
    LuaPlus::LuaObject resourceMgrObj = m_luaState->BoxPointer((void *)m_pResourceMgr);
    resourceMgrObj.SetMetatable(m_mgrMetatables[RESOURCE_MGR]);
    m_fgObj.SetObject("ResourceManager", resourceMgrObj);
    m_userDataObjectMap[offset] = resourceMgrObj;

    //
    // Registering now metatables for various resource types
    //

    typedef const char*(fgResource::base_type::*getFilePathStrType)(void)const;
    // Register Base Resource metatable
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::RESOURCE_MT_ID))
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
    //.MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent); // #DELETE

    // Register Texture Resource metatable
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::TEXTURE_RESOURCE_MT_ID), fgScriptMT->getMetatableName(fgScriptMetatables::RESOURCE_MT_ID))
            .ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
            .ObjectDirect("getHeight", (fgTextureResource *)0, &fgTextureResource::getHeight)
            .ObjectDirect("getComponents", (fgTextureResource *)0, &fgTextureResource::getComponents)
            .MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent);

    // Register Font Resource metatable
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::FONT_RESOURCE_MT_ID), fgScriptMT->getMetatableName(fgScriptMetatables::TEXTURE_RESOURCE_MT_ID))
            .ObjectDirect("getFontType", (fgFontResource *)0, &fgFontResource::getFontType)
            .ObjectDirect("getStep", (fgFontResource *)0, &fgFontResource::getStep)
            .MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent);

    // Register Gfx Model Resource metatable
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::GFX_MODEL_RESOURCE_MT_ID), fgScriptMT->getMetatableName(fgScriptMetatables::RESOURCE_MT_ID))
            .ObjectDirect("getModelType", (fg::gfx::CModelResource *)0, &fg::gfx::CModelResource::getModelType)
            .ObjectDirect("getNumIndices", (fg::gfx::CModelResource *)0, &fg::gfx::CModelResource::getNumIndices)
            .ObjectDirect("getNumMaterials", (fg::gfx::CModelResource *)0, &fg::gfx::CModelResource::getNumMaterials)
            .ObjectDirect("getNumNormals", (fg::gfx::CModelResource *)0, &fg::gfx::CModelResource::getNumNormals)
            .ObjectDirect("getNumPolygons", (fg::gfx::CModelResource *)0, &fg::gfx::CModelResource::getNumPolygons)
            .ObjectDirect("getNumShapes", (fg::gfx::CModelResource *)0, &fg::gfx::CModelResource::getNumShapes)
            .ObjectDirect("getNumTriangles", (fg::gfx::CModelResource *)0, &fg::gfx::CModelResource::getNumTriangles)
            .ObjectDirect("getNumUVs", (fg::gfx::CModelResource *)0, &fg::gfx::CModelResource::getNumUVs)
            .ObjectDirect("getNumVertices", (fg::gfx::CModelResource *)0, &fg::gfx::CModelResource::getNumVertices)
            .ObjectDirect("isInterleaved", (fg::gfx::CModelResource *)0, &fg::gfx::CModelResource::isInterleaved)
            .ObjectDirect("isTextured", (fg::gfx::CModelResource *)0, &fg::gfx::CModelResource::isTextured)
            .ObjectDirect("isMultitextured", (fg::gfx::CModelResource *)0, &fg::gfx::CModelResource::isMultitextured)
            .ObjectDirect("hasMaterial", (fg::gfx::CModelResource *)0, &fg::gfx::CModelResource::hasMaterial)
            .MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent);

    typedef void (fgParticleEffect::*PE_void_4X_INT_IN)(const int, const int, const int, const int);
    typedef void (fgParticleEffect::*PE_void_2X_FLOAT_IN)(const float, const float);
    typedef void (fgParticleEffect::*PE_void_Vec4f_IN)(const fgVector4f&);
    typedef void (fgParticleEffect::*PE_void_Vec3f_IN)(const fgVector3f&);
    typedef void (fgParticleEffect::*PE_void_Vec2f_IN)(const fgVector2f&);
    typedef void (fgParticleEffect::*PE_void_Vec2i_IN)(const fgVector2i&);
    typedef void (fgParticleEffect::*PE_void_C_STR_IN)(const char *);

    //
    // Register Particle Effect Resource metatable
    //
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::PARTICLE_EFFECT_RESOURCE_MT_ID), fgScriptMT->getMetatableName(fgScriptMetatables::RESOURCE_MT_ID))
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

    //m_fgObj.Register("Texture", &fgScriptSubsystem::newResourceWrapper);

    //
    // Register Music (SFX) Resource metatable
    //
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::AUDIO_BASE_RES_MT_ID), fgScriptMT->getMetatableName(fgScriptMetatables::RESOURCE_MT_ID))
            .ObjectDirect("play", (fgAudioBase *)0, &fgAudioBase::play)
            .ObjectDirect("pause", (fgAudioBase *)0, &fgAudioBase::pause)
            .ObjectDirect("resume", (fgAudioBase *)0, &fgAudioBase::resume)
            .ObjectDirect("rewind", (fgAudioBase *)0, &fgAudioBase::rewind)
            .ObjectDirect("stop", (fgAudioBase *)0, &fgAudioBase::stop)
            .ObjectDirect("halt", (fgAudioBase *)0, &fgAudioBase::halt)
            .ObjectDirect("isPaused", (fgAudioBase *)0, &fgAudioBase::isPaused)
            .ObjectDirect("setVolume", (fgAudioBase *)0, &fgAudioBase::setVolume)
            .ObjectDirect("getVolume", (fgAudioBase *)0, &fgAudioBase::getVolume);

    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::MUSIC_RESOURCE_MT_ID), fgScriptMT->getMetatableName(fgScriptMetatables::AUDIO_BASE_RES_MT_ID))
            .MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent);

    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::SOUND_RESOURCE_MT_ID), fgScriptMT->getMetatableName(fgScriptMetatables::AUDIO_BASE_RES_MT_ID))
            .MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent);

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
    if(m_mgrMetatables[SHADER_MGR].GetRef() >= 0)
        return FG_TRUE;
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;

#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}

/**
 * 
 * @param metatable
 * @param sceneManager
 * @return 
 */
#if defined(FG_USING_LUA_PLUS)

fgBool fgScriptSubsystem::registerSceneManager(LuaPlus::LuaObject &metatable,
                                               const unsigned short int metatableID,
                                               fg::base::CManager *sceneManager,
                                               const char *objectName) {
    if(m_isBindingComplete) {
        return FG_TRUE;
    }
    if(!sceneManager) {
        return FG_FALSE;
    }
    // Scene manager (2D or 3D) metatable
    metatable = m_fgObj.CreateTable(fgScriptMT->getMetatableName(metatableID));
    metatable.SetObject("__index", metatable);
    //m_mgrMetatables[RESOURCE_MGR].Register("request", &fgScriptSubsystem::newResourceWrapper);

    uintptr_t offset = (uintptr_t)sceneManager;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        return FG_FALSE;
    }
    // Create Lua object for scene manager global
    LuaPlus::LuaObject sceneManagerObj = m_luaState->BoxPointer((void *)sceneManager);
    sceneManagerObj.SetMetatable(metatable);
    m_fgObj.SetObject(objectName, sceneManagerObj);
    m_userDataObjectMap[offset] = sceneManagerObj;

    return FG_TRUE;
}
#else
#endif /* FG_USING_LUA_PLUS */

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
    if(m_mgrMetatables[SCENE2D_MGR].GetRef() >= 0)
        return FG_TRUE;
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;

    if(!registerSceneManager(m_mgrMetatables[SCENE2D_MGR], fgScriptMetatables::SCENE2D_MANAGER_MT_ID, m_p2DSceneMgr, "Scene2D")) {
        FG_LOG_ERROR("Script: Unable to register common metatable for 2D Scene Manager");
        return FG_FALSE;
    }

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
    if(m_mgrMetatables[SCENE3D_MGR].GetRef() >= 0)
        return FG_TRUE;
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;

    if(!registerSceneManager(m_mgrMetatables[SCENE3D_MGR], fgScriptMetatables::SCENE3D_MANAGER_MT_ID, m_p3DSceneMgr, "Scene3D")) {
        FG_LOG_ERROR("Script: Unable to register common metatable for 3D Scene Manager");
        return FG_FALSE;
    }

    // Register additional direct functions for 3D Scene Manager - they're specific for this class/object
    typedef fg::gfx::CSceneNode * (fg::gfx::CScene3D::*SCENE3D_SceneNode_C_STR_IN_C_STR_IN)(const char *, const char *);

    m_mgrMetatables[SCENE3D_MGR].RegisterObjectDirect("addFromModel",
                                                      static_cast<fg::gfx::CScene3D *>(0),
                                                      static_cast<SCENE3D_SceneNode_C_STR_IN_C_STR_IN>(&fg::gfx::CScene3D::addFromModel));

    ////////////////////////////////////////////////////////////////////////////
    //
    // Registering now metatables for various 3D/2D Scene types
    // Registration here for this types needs to be done once - it will be used
    // globally for 2D and 3D scene manipulations
    //

    // Register Base GfxSceneNode metatable
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::SCENE_NODE_MT_ID))
            .ObjectDirect("getName", (fg::gfx::CSceneNode::base_type *)0, &fg::gfx::CSceneNode::base_type::getNameStr)
            .ObjectDirect("isManaged", (fg::gfx::CSceneNode::base_type *)0, &fg::gfx::CSceneNode::base_type::isManaged)
            .ObjectDirect("isEmpty", (fg::gfx::CSceneNode *)0, &fg::gfx::CSceneNode::isEmpty)
            .ObjectDirect("hasChildren", (fg::gfx::CSceneNode *)0, &fg::gfx::CSceneNode::hasChildren)
            .ObjectDirect("getChildrenCount", (fg::gfx::CSceneNode *)0, &fg::gfx::CSceneNode::getChildrenCount)
            .ObjectDirect("isVisible", (fg::gfx::CSceneNode *)0, &fg::gfx::CSceneNode::isVisible)
            .ObjectDirect("setVisible", (fg::gfx::CSceneNode *)0, &fg::gfx::CSceneNode::setVisible);
    //.MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent); // #DELETE

    ////////////////////////////////////////////////////////////////////////////

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
    if(m_mgrMetatables[PARTICLE_MGR].GetRef() >= 0)
        return FG_TRUE;
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;

    // Particle system/manager metatable
    m_mgrMetatables[PARTICLE_MGR] = m_fgObj.CreateTable(fgScriptMT->getMetatableName(fgScriptMetatables::PARTICLE_SYSTEM_MT_ID));
    m_mgrMetatables[PARTICLE_MGR].SetObject("__index", m_mgrMetatables[PARTICLE_MGR]);
    //m_metatableParticleMgr.Register("request", &fgScriptSubsystem::newResourceWrapper);

    uintptr_t offset = (uintptr_t)m_pParticleMgr;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        return FG_FALSE;
    }
    // Create lua object for particle system/manager global
    LuaPlus::LuaObject particleMgrObj = m_luaState->BoxPointer((void *)m_pParticleMgr);
    particleMgrObj.SetMetatable(m_mgrMetatables[PARTICLE_MGR]);
    m_fgObj.SetObject("ParticleSystem", particleMgrObj);
    m_userDataObjectMap[offset].obj = particleMgrObj;
    m_userDataObjectMap[offset].isBound = FG_TRUE;

#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}

/**
 * 
 * @param L
 * @return 
 */
int fgScriptSubsystem::addWidgetCallbackWrapper(lua_State *L) {
#if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    LuaPlus::LuaStack args(state);
    const char *script = NULL;
    unsigned int callbackType = FG_GUI_WIDGET_CALLBACK_INVALID;
    LuaPlus::LuaObject objFunction;
    fgBool hasFunction = FG_FALSE;
    const char *widgetName = NULL;
    fgGuiWidget *pWidget = NULL;
    int argc = 1;
    if(args.Count() == 0) {
        FG_LOG_DEBUG("Script: WidgetCallbackWrapper: empty argument list");
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

    // arguments [WidgetName/WidgetPointer][CallbackType/CallbackActionName][FunctionPointer/StringScript]
    FG_LOG_DEBUG("Script: WidgetCallbackWrapper: argc[%d]", args.Count());
    if(args.Count() >= 2) {
        int id = 1;
        // [1] Widget name or widget pointer (user data)
        if(args[id].IsUserdata()) {
            void *unboxed = args[id].GetUserdata();
            if(!unboxed) {
                FG_LOG_DEBUG("Script: WidgetCallbackWrapper: 1st argument: userdata is nil");
                return 0;
            }
            pWidget = (fgGuiWidget *)unboxed;
            FG_LOG_DEBUG("Script: WidgetCallbackWrapper: 1st argument: userData[%s]", pWidget->getNameStr());
        } else if(args[id].IsString()) {
            widgetName = args[id].GetString();
            FG_LOG_DEBUG("Script: WidgetCallbackWrapper: 1st argument: widgetName[%s]", widgetName);

        }
        // [2] Callback type - integer
        id++;
        if(args[id].IsInteger()) {
            int iVal = args[id].GetInteger();
            if(iVal < (int)FG_GUI_WIDGET_CALLBACK_MAX_ID)
                callbackType = (unsigned int)iVal;
            FG_LOG_DEBUG("Script: WidgetCallbackWrapper: 2nd argument: callbackType[%d]", callbackType);
        } else if(args[id].IsString()) {
            // [2] callback type - as name (string)
            const char *ctype = args[id].GetString();
            if(fgStrings::isEqual(ctype, "onFocus", FG_FALSE)) {
                callbackType = FG_GUI_WIDGET_CALLBACK_ON_FOCUS;

            } else if(fgStrings::isEqual(ctype, "onFocusLost", FG_FALSE)) {
                callbackType = FG_GUI_WIDGET_CALLBACK_ON_FOCUS_LOST;

            } else if(fgStrings::isEqual(ctype, "onClick", FG_FALSE)) {
                callbackType = FG_GUI_WIDGET_CALLBACK_ON_CLICK;

            } else if(fgStrings::isEqual(ctype, "onActivate", FG_FALSE)) {
                callbackType = FG_GUI_WIDGET_CALLBACK_ON_ACTIVATE;

            } else if(fgStrings::isEqual(ctype, "onDeactivate", FG_FALSE)) {
                callbackType = FG_GUI_WIDGET_CALLBACK_ON_DEACTIVATE;

            } else if(fgStrings::isEqual(ctype, "onKey", FG_FALSE)) {
                callbackType = FG_GUI_WIDGET_CALLBACK_ON_KEY;

            } else if(fgStrings::isEqual(ctype, "onMouse", FG_FALSE)) {
                callbackType = FG_GUI_WIDGET_CALLBACK_ON_MOUSE;

            } else if(fgStrings::isEqual(ctype, "onChangeState", FG_FALSE)) {
                callbackType = FG_GUI_WIDGET_CALLBACK_ON_CHANGE_STATE;
            }
            FG_LOG_DEBUG("Script: WidgetCallbackWrapper: 2nd argument: callbackType[%d][%s]", callbackType, ctype);
        }
        // [3] Function pointer or string script
        id++;
        if(args[id].IsFunction()) {
            objFunction = args[id];
            hasFunction = FG_TRUE;
            FG_LOG_DEBUG("Script: WidgetCallbackWrapper: 3rd argument is a function pointer");
        } else if(args[id].IsString()) {
            script = args[id].GetString();
            FG_LOG_DEBUG("Script: WidgetCallbackWrapper: 3rd argument is a string[%s]", script);
        }
    }
    if(callbackType == FG_GUI_WIDGET_CALLBACK_INVALID) {
        FG_LOG_DEBUG("Script: WidgetCallbackWrapper: callback type is invalid");
        return 0;
    }
    if(!script && !hasFunction) {
        FG_LOG_DEBUG("Script: WidgetCallbackWrapper: No script nor function specified");
        return 0;
    }
    if(!widgetName && !pWidget) {
        FG_LOG_DEBUG("Script: WidgetCallbackWrapper: No widget name nor pointer specified");
        return 0;
    }
    if(!m_pGuiMain) {
        FG_LOG_DEBUG("Script: WidgetCallbackWrapper: GUI Main is not specified");
        return 0;
    }
    if(m_pGuiMain->getManagerType() != FG_MANAGER_GUI_MAIN) {
        FG_LOG_DEBUG("Script: WidgetCallbackWrapper: GUI Main is not proper manager");
        return 0;
    }
    // #FIXME - sometimes passed Lua function pointer will be the same for different widgets
    // Well then there has to be some kind of check to  determine if new allocation is
    // really needed - some script callback objects need to be reusable
    // #UPDATE - well it looks like that it is not possible because the LuaFunction
    // object does not provide getter function for the inner LuaObject which stores Lua function
    //
    fgGuiCallback *callback = NULL;
    if(script) {
        callback = new fgScriptGuiCallback(static_cast<fgGuiMain *>(m_pGuiMain), L, script, argc);
    } else if(hasFunction) {
        callback = new fgScriptGuiCallback(static_cast<fgGuiMain *>(m_pGuiMain), L, objFunction, argc);
    }
    fgBool status = FG_FALSE;
    if(pWidget)
        status = static_cast<fgGuiMain *>(m_pGuiMain)->addWidgetCallback(pWidget, callback, callbackType);
    else if(widgetName)
        status = static_cast<fgGuiMain *>(m_pGuiMain)->addWidgetCallback(widgetName, callback, callbackType);
    if(status) {
        FG_LOG_DEBUG("Script: Successfully added callback for widget[%s]", (pWidget ? pWidget->getNameStr() : widgetName));
    } else {
        FG_LOG_DEBUG("Script: Failed to add callback for widget[%s]", (pWidget ? pWidget->getNameStr() : widgetName));
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
fgBool fgScriptSubsystem::registerGuiMain(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    if(!m_pGuiMain)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    if(m_mgrMetatables[GUI_MAIN].GetRef() >= 0)
        return FG_TRUE;
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;

    // Gui main/manager metatable
    m_mgrMetatables[GUI_MAIN] = m_fgObj.CreateTable(fgScriptMT->getMetatableName(fgScriptMetatables::GUI_MAIN_MT_ID));
    m_mgrMetatables[GUI_MAIN].SetObject("__index", m_mgrMetatables[GUI_MAIN]);
    m_mgrMetatables[GUI_MAIN].Register("addWidgetCallback", &fgScriptSubsystem::addWidgetCallbackWrapper);

    uintptr_t offset = (uintptr_t)m_pGuiMain;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        return FG_FALSE;
    }
    // Create lua object for gui main/manager global
    LuaPlus::LuaObject guiMainObj = m_luaState->BoxPointer((void *)m_pGuiMain);
    guiMainObj.SetMetatable(m_mgrMetatables[GUI_MAIN]);
    m_fgObj.SetObject("GuiMain", guiMainObj);
    //m_fgObj.SetObject("GUI", guiMainObj);
    m_userDataObjectMap[offset].obj = guiMainObj;
    m_userDataObjectMap[offset].isBound = FG_TRUE;
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
    if(m_mgrMetatables[WIDGET_MGR].GetRef() >= 0)
        return FG_TRUE;
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;

    typedef fgBool(fgGuiWidgetManager::*GWM_Bool_Widget_IN)(fgGuiWidget *);
    typedef fgBool(fgGuiWidgetManager::*GWM_Bool_Widget_Widget_IN)(fgGuiWidget *, fgGuiWidget *);
    typedef fgBool(fgGuiWidgetManager::*GWM_Bool_C_STR_IN)(const char *);
    typedef fgGuiWidget * (fgGuiWidgetManager::*GWM_Widget_C_STR_IN)(const char *);

    // Widget manager metatable
    m_mgrMetatables[WIDGET_MGR] = m_fgObj.CreateTable(fgScriptMT->getMetatableName(fgScriptMetatables::WIDGET_MANAGER_MT_ID));
    m_mgrMetatables[WIDGET_MGR].SetObject("__index", m_mgrMetatables[WIDGET_MGR]);
    m_mgrMetatables[WIDGET_MGR].RegisterObjectDirect("addWidget",
                                                     (fgGuiWidgetManager *)0,
                                                     static_cast<GWM_Bool_Widget_IN>(&fgGuiWidgetManager::addWidget));

    m_mgrMetatables[WIDGET_MGR].RegisterObjectDirect("addWidgetWithFather",
                                                     (fgGuiWidgetManager *)0,
                                                     static_cast<GWM_Bool_Widget_Widget_IN>(&fgGuiWidgetManager::addWidget));

    m_mgrMetatables[WIDGET_MGR].RegisterObjectDirect("removeWidget",
                                                     (fgGuiWidgetManager *)0,
                                                     static_cast<GWM_Bool_Widget_IN>(&fgGuiWidgetManager::remove));

    m_mgrMetatables[WIDGET_MGR].RegisterObjectDirect("removeWidgetByName",
                                                     (fgGuiWidgetManager *)0,
                                                     static_cast<GWM_Bool_C_STR_IN>(&fgGuiWidgetManager::remove));

    m_mgrMetatables[WIDGET_MGR].RegisterObjectDirect("getWidget",
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
    widgetMgrObj.SetMetatable(m_mgrMetatables[WIDGET_MGR]);
    m_fgObj.SetObject("WidgetManager", widgetMgrObj);
    m_userDataObjectMap[offset].obj = widgetMgrObj;
    m_userDataObjectMap[offset].isBound = FG_TRUE;


    typedef void (fgGuiWidget::*GW_void_C_STR_IN)(const char *);
    typedef void (fgGuiWidget::base_type::*GW_BASE_void_C_STR_IN)(const char *);
    typedef fgGuiWidget * (fgGuiWidget::*GW_Widget_void)(void)const;

    const char *metatableNameWidget = fgScriptMT->getMetatableName(fgScriptMetatables::GUI_WIDGET_MT_ID);
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
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::GUI_BUTTON_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_fgObj.Register("Button", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiButton, fgScriptMetatables::GUI_BUTTON_MT_ID>);

    // Register Gui Toggle Button metatable
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::GUI_TOGGLE_BUTTON_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(fgScriptMetatables::GUI_BUTTON_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_fgObj.Register("ToggleButton", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiToggleButton, fgScriptMetatables::GUI_TOGGLE_BUTTON_MT_ID>);

    typedef fgBool(fgGuiContainer::*GCNT_Bool_C_STR_IN)(const char *);
    typedef fgBool(fgGuiContainer::*GCNT_Bool_Widget_IN)(fgGuiWidget *);

    // Register Gui Container metatable
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::GUI_CONTAINER_MT_ID);
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
    m_fgObj.Register("Container", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiContainer, fgScriptMetatables::GUI_CONTAINER_MT_ID>);

    // Register Gui Editable Text metatable
    //metatableName = fgScriptMT->getMetatableName(E);
    //LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
    //        //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
    //        .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    //m_fgObj.Register("EditableText", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiButton, fgScriptMetatables::GUI_CONSOLE_MT_ID>);

    // Register Gui Frame metatable
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::GUI_FRAME_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(fgScriptMetatables::GUI_CONTAINER_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_fgObj.Register("Frame", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiFrame, fgScriptMetatables::GUI_FRAME_MT_ID>);

    // Register Gui Label metatable
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::GUI_LABEL_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_fgObj.Register("Label", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiLabel, fgScriptMetatables::GUI_LABEL_MT_ID>);

    // Register Gui Loader metatable
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::GUI_LOADER_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_fgObj.Register("Loader", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiLoader, fgScriptMetatables::GUI_LOADER_MT_ID>);

    // Register Gui Menu metatable
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::GUI_MENU_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(fgScriptMetatables::GUI_CONTAINER_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_fgObj.Register("Menu", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiMenu, fgScriptMetatables::GUI_MENU_MT_ID>);

    // Register Gui Window metatable
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::GUI_WINDOW_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(fgScriptMetatables::GUI_CONTAINER_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_fgObj.Register("Window", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiWindow, fgScriptMetatables::GUI_WINDOW_MT_ID>);

    // Register Gui MessageBox metatable
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::GUI_MESSAGE_BOX_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(fgScriptMetatables::GUI_WINDOW_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_fgObj.Register("MessageBox", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiMessageBox, fgScriptMetatables::GUI_MESSAGE_BOX_MT_ID>);

    // Register Gui Popup metatable
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::GUI_POPUP_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(fgScriptMetatables::GUI_WINDOW_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_fgObj.Register("Popup", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiPopup, fgScriptMetatables::GUI_POPUP_MT_ID>);

    // Register Gui Progress Bar metatable
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::GUI_PROGRESS_BAR_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_fgObj.Register("ProgressBar", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiProgressBar, fgScriptMetatables::GUI_PROGRESS_BAR_MT_ID>);

    // Register Gui Scroll Area metatable
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::GUI_SCROLL_AREA_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(fgScriptMetatables::GUI_CONTAINER_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_fgObj.Register("ScrollArea", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiScrollArea, fgScriptMetatables::GUI_SCROLL_AREA_MT_ID>);

    // Register Gui Table metatable
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::GUI_TABLE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(fgScriptMetatables::GUI_CONTAINER_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_fgObj.Register("Table", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiTable, fgScriptMetatables::GUI_TABLE_MT_ID>);

    // Register Gui TextArea metatable
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::GUI_TEXT_AREA_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(fgScriptMetatables::GUI_SCROLL_AREA_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_fgObj.Register("TextArea", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiTextArea, fgScriptMetatables::GUI_TEXT_AREA_MT_ID>);

    // Register Gui Console metatable
    metatableName = fgScriptMT->getMetatableName(fgScriptMetatables::GUI_CONSOLE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(fgScriptMetatables::GUI_TEXT_AREA_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)            
            .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    m_fgObj.Register("Console", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiConsole, fgScriptMetatables::GUI_CONSOLE_MT_ID>);

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
    const char *metatableNameStyle = fgScriptMT->getMetatableName(fgScriptMetatables::GUI_STYLE_MT_ID);
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
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::GUI_STYLE_SIZE_MT_ID))
            .Property("style", &fgGuiSize::style)
            .Property("x", &fgGuiSize::x)
            .Property("y", &fgGuiSize::y)
            .Property("z", &fgGuiSize::z)
            .Property("w", &fgGuiSize::w)
            .Property("h", &fgGuiSize::h)
            .Property("d", &fgGuiSize::d);
    // MetatableFunction("__gc") // Nope

    // Register fgGuiBackground structure
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::GUI_STYLE_BACKGROUND_MT_ID))
            .Property("texture", &fgGuiBackground::texture) // std::string
            .Property("color", &fgGuiBackground::color) // color is fgColor4f/fgVector4f (glm)
            .Property("style", &fgGuiBackground::style) // enum fgGuiBackgroundStyle (int)
            ;
    // MetatableFunction("__gc") // Nope

    // Register fgGuiForeground structure
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::GUI_STYLE_FOREGROUND_MT_ID))
            .Property("font", &fgGuiForeground::font) // std::string - font name
            .Property("color", &fgGuiForeground::color) // color is fgColor4f/fgVector4f (glm)
            .Property("textSize", &fgGuiForeground::textSize) // float
            ;
    // MetatableFunction("__gc") // Nope

    // Register fgGuiMargin/fgGuiPadding structure
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::GUI_STYLE_MARGIN_MT_ID))
            .Property("left", &fgGuiMargin::left) // float
            .Property("right", &fgGuiMargin::right) // float
            .Property("top", &fgGuiMargin::top) // float
            .Property("bottom", &fgGuiMargin::bottom) // float
            ;
    // MetatableFunction("__gc") // Nope

    // Register fgGuiBorder structure
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::GUI_STYLE_BORDER_MT_ID))
            .Property("color", &fgGuiBorder::color) // color is fgColor4f/fgVector4f (glm)
            .Property("style", &fgGuiBorder::style) // enum fgGuiBorderStyle (int)
            .Property("width", &fgGuiBorder::width) // float
            ;
    // MetatableFunction("__gc") // Nope

    // Register fgGuiBorderInfo structure (stores info for all borders)
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::GUI_STYLE_BORDER_INFO_MT_ID))
            .Property("left", &fgGuiBorderInfo::left) // structure fgGuiBorder
            .Property("right", &fgGuiBorderInfo::right) // structure fgGuiBorder 
            .Property("top", &fgGuiBorderInfo::top) // structure fgGuiBorder
            .Property("bottom", &fgGuiBorderInfo::bottom) // structure fgGuiBorder
            ;
    // MetatableFunction("__gc") // Nope

    // Register fgGuiPosition structure
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(fgScriptMetatables::GUI_STYLE_POSITION_MT_ID))
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
    const char *metatableNameStyleContent = fgScriptMT->getMetatableName(fgScriptMetatables::GUI_STYLE_CONTENT_MT_ID);
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
    if(m_mgrMetatables[STYLE_MGR].GetRef() >= 0)
        return FG_TRUE;
    if(m_fgObj.GetRef() < 0)
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
    if(m_pSoundMgr->getManagerType() != FG_MANAGER_SOUND)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    if(m_mgrMetatables[SOUND_MGR].GetRef() >= 0)
        return FG_TRUE;
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;
    typedef fgBool(fgSFXManager::*SFX_Bool_C_STR_IN)(const char *);

    // Sound manager metatable
    m_mgrMetatables[SOUND_MGR] = m_fgObj.CreateTable(fgScriptMT->getMetatableName(fgScriptMetatables::SOUND_MANAGER_MT_ID));
    m_mgrMetatables[SOUND_MGR].SetObject("__index", m_mgrMetatables[SOUND_MGR]);
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("play",
                                                    static_cast<fgSFXManager *>(0),
                                                    static_cast<SFX_Bool_C_STR_IN>(&fgSFXManager::play));
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("pause",
                                                    static_cast<fgSFXManager *>(0),
                                                    static_cast<SFX_Bool_C_STR_IN>(&fgSFXManager::pause));
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("resume",
                                                    static_cast<fgSFXManager *>(0),
                                                    static_cast<SFX_Bool_C_STR_IN>(&fgSFXManager::resume));
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("rewind",
                                                    static_cast<fgSFXManager *>(0),
                                                    static_cast<SFX_Bool_C_STR_IN>(&fgSFXManager::rewind));
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("stop",
                                                    static_cast<fgSFXManager *>(0),
                                                    static_cast<SFX_Bool_C_STR_IN>(&fgSFXManager::stop));
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("isPlaying",
                                                    static_cast<fgSFXManager *>(0),
                                                    static_cast<SFX_Bool_C_STR_IN>(&fgSFXManager::isPlaying));
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("isPaused",
                                                    static_cast<fgSFXManager *>(0),
                                                    static_cast<SFX_Bool_C_STR_IN>(&fgSFXManager::isPaused));
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("stopAll",
                                                    static_cast<fgSFXManager *>(0),
                                                    &fgSFXManager::stopAll);
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("setSfxVolume",
                                                    static_cast<fgSFXManager *>(0),
                                                    &fgSFXManager::setSfxVolume);
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("getSfxVolume",
                                                    static_cast<fgSFXManager *>(0),
                                                    &fgSFXManager::getSfxVolume);
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("setMusicVolume",
                                                    static_cast<fgSFXManager *>(0),
                                                    &fgSFXManager::setMusicVolume);
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("getMusicVolume",
                                                    static_cast<fgSFXManager *>(0),
                                                    &fgSFXManager::getMusicVolume);

    uintptr_t offset = (uintptr_t)m_pSoundMgr;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        return FG_FALSE;
    }
    // Create lua object for Sound manager global
    LuaPlus::LuaObject soundMgrObj = m_luaState->BoxPointer((void *)m_pSoundMgr);
    soundMgrObj.SetMetatable(m_mgrMetatables[SOUND_MGR]);
    m_fgObj.SetObject("SoundManager", soundMgrObj);
    m_userDataObjectMap[offset].obj = soundMgrObj;
    m_userDataObjectMap[offset].isBound = FG_TRUE;

#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}

/**
 * 
 */
fgBool fgScriptSubsystem::registerLogicManager(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    if(!m_pLogicMgr)
        return FG_FALSE;
    if(m_pLogicMgr->getManagerType() != FG_MANAGER_LOGIC)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    if(m_mgrMetatables[LOGIC_MGR].GetRef() >= 0)
        return FG_TRUE;
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;

    typedef fgBool(fg::game::Logic::*LOGIC_Bool_C_STR_IN)(const char *);
    typedef void(fg::game::Logic::*LOGIC_void_C_STR_IN)(const char *);
    typedef void(fg::game::Logic::*LOGIC_void_UINT_IN)(const unsigned int);

    // Game Logic manager metatable
    m_mgrMetatables[LOGIC_MGR] = m_fgObj.CreateTable(fgScriptMT->getMetatableName(fgScriptMetatables::LOGIC_MANAGER_MT_ID));
    m_mgrMetatables[LOGIC_MGR].SetObject("__index", m_mgrMetatables[LOGIC_MGR]);
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("startGameDefault",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::startGameDefault);
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("startGameStageID",
                                                    static_cast<fg::game::Logic *>(0),
                                                    static_cast<LOGIC_void_UINT_IN>(&fg::game::Logic::startGame));
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("startGameStageName",
                                                    static_cast<fg::game::Logic *>(0),
                                                    static_cast<LOGIC_void_C_STR_IN>(&fg::game::Logic::startGame));
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("stopGame",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::stopGame);
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("pauseGame",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::pauseGame);
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("restartGame",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::restartGame);

    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("getCurrentStageID",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::getCurrentStageID);
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("getCurrentStageName",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::getCurrentStageNameStr);
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("getStageScore",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::getStageScore);
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("getGlobalScore",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::getGlobalScore);
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("increaseStageScore",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::increaseStageScore);
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("resetStageScore",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::resetStageScore);

    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("setPlayerName",
                                                    static_cast<fg::game::Logic *>(0),
                                                    static_cast<LOGIC_void_C_STR_IN>(&fg::game::Logic::setPlayerName));
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("getPlayerName",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::getPlayerNameStr);

    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("isActive",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::isActive);
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("isPaused",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::isPaused);
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("isStopped",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::isStopped);
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("isLoading",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::isLoading);
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("isRestarting",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::isRestarting);
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("isStopping",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::isStopping);
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("isFinishing",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::isFinishing);
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("isFinished",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::isFinished);
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("isConnecting",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::isConnecting);
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("isWaiting",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::isWaiting);
    m_mgrMetatables[LOGIC_MGR].RegisterObjectDirect("isDisconnected",
                                                    static_cast<fg::game::Logic *>(0),
                                                    &fg::game::Logic::isDisconnected);
    uintptr_t offset = (uintptr_t)m_pLogicMgr;
    userDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        return FG_FALSE;
    }
    // Create lua object for Game Logic manager global
    LuaPlus::LuaObject logicMgrObj = m_luaState->BoxPointer((void *)m_pLogicMgr);
    logicMgrObj.SetMetatable(m_mgrMetatables[LOGIC_MGR]);


    // #FIXME - create in script proper structure as in C++ -> fg.game.Logic, etc
    m_fgObj.SetObject("LogicManager", logicMgrObj);
    m_fgObj.SetObject("GameLogic", logicMgrObj);
    m_userDataObjectMap[offset].obj = logicMgrObj;
    m_userDataObjectMap[offset].isBound = FG_TRUE;

#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}