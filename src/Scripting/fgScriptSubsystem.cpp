/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

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
 * However there is a downside to everything:a  If something  big changes in the
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
#include "GFX/Scene/fgGfxSceneManager.h"
#include "GFX/Scene/fgGfx3DScene.h"
#include "GFX/Shaders/fgGfxShaderManager.h"
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
#include "Game/fgGameMain.h"
// Special Script Callback
#include "fgScriptCallback.h"
// Audio
#include "Audio/fgSFXMusicResource.h"
#include "Audio/fgSFXManager.h"
// Util
#include "Util/fgStrings.h"

using namespace fg;

//------------------------------------------------------------------------------

#if defined(FG_USING_LUA_PLUS)
LuaPlus::LuaState *script::CScriptSubsystem::m_luaState = NULL;
LuaPlus::LuaObject script::CScriptSubsystem::m_globals;
LuaPlus::LuaObject script::CScriptSubsystem::m_fgObj;
script::CScriptSubsystem::UserDataObjectMap script::CScriptSubsystem::m_userDataObjectMap;
#else
void *script::CScriptSubsystem::m_luaState = NULL;
#endif /* FG_USING_LUA_PLUS */

fgBool script::CScriptSubsystem::m_isBindingComplete = FG_FALSE;

fg::base::CManager *script::CScriptSubsystem::m_pGuiMain = NULL;
fg::base::CManager *script::CScriptSubsystem::m_pEventMgr = NULL;
fg::base::CManager *script::CScriptSubsystem::m_pResourceMgr = NULL;
fg::base::CManager *script::CScriptSubsystem::m_pShaderMgr = NULL;
fg::base::CManager *script::CScriptSubsystem::m_p2DSceneMgr = NULL;
fg::base::CManager *script::CScriptSubsystem::m_p3DSceneMgr = NULL;
fg::base::CManager *script::CScriptSubsystem::m_pParticleMgr = NULL;
fg::base::CManager *script::CScriptSubsystem::m_pWidgetMgr = NULL;
fg::base::CManager *script::CScriptSubsystem::m_pStyleMgr = NULL;
fg::base::CManager *script::CScriptSubsystem::m_pSoundMgr = NULL;
fg::base::CManager *script::CScriptSubsystem::m_pGameMainMgr = NULL;

//------------------------------------------------------------------------------

script::CScriptSubsystem::CScriptSubsystem()
#if defined(FG_USING_LUA_PLUS)
#endif /* FG_USING_LUA_PLUS */
{
    m_managerType = FG_MANAGER_SCRIPT;
    m_cyclicGCCallback = new event::CPlainFunctionCallback(&script::CScriptSubsystem::cyclicGCFunction, NULL);
}
//------------------------------------------------------------------------------

script::CScriptSubsystem::~CScriptSubsystem() {
    script::CScriptSubsystem::destroy();
}
//------------------------------------------------------------------------------

void script::CScriptSubsystem::clear(void) {
    m_cyclicGCCallback = NULL;
    m_managerType = FG_MANAGER_SCRIPT;
}
//------------------------------------------------------------------------------

fgBool script::CScriptSubsystem::cyclicGCFunction(void* systemData, void* userData) {
    if(!m_luaState)
        return FG_FALSE;
    if(!m_isBindingComplete)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    //m_luaState->GC();
    FG_LOG_DEBUG("Script: GC: Calling Garbage Collector...");
    int bytesBefore = m_luaState->GC(LUA_GCCOUNTB, 0);
    m_luaState->GC(LUA_GCCOLLECT, 0);
    m_luaState->GC(LUA_GCSTEP, 0);
    int bytesAfter = m_luaState->GC(LUA_GCCOUNTB, 0);
    FG_LOG_DEBUG("Script: GC: before[%d], after[%d]", bytesBefore, bytesAfter);
#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}
//------------------------------------------------------------------------------

int script::CScriptSubsystem::executeFile(const char* filePath) {
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
    if(!scriptFile.open(filePath, fg::util::CFile::Mode::READ)) {
        FG_LOG_ERROR("Script: Unable to open script file: '%s'", filePath);
        return 2;
    }
    char *buffer = scriptFile.load();
    if(!buffer) {
        FG_LOG_ERROR("Script: Unable to load script file into buffer: '%s'", filePath);
        return 2;
    }
    scriptFile.close();
    const char* fileName = fg::path::fileName(filePath);
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
//------------------------------------------------------------------------------

fgBool script::CScriptSubsystem::destroy(void) {
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
    m_fgObj.Reset();
    for(int i = 0; i < NUM_MGR_METATABLES; i++)
        m_mgrMetatables[i].Reset();
    UserDataObjectMapItor it = m_userDataObjectMap.begin(),
            end = m_userDataObjectMap.end();
    for(; it != end; it++) {
        UserDataObjectMap::value_type &pair = *it;
        pair.second.obj.Reset();
    }
    if(m_luaState)
        LuaPlus::LuaState::Destroy(m_luaState);
    m_luaState = NULL;
    m_userDataObjectMap.clear();
    UserDataObjectMap dmmap;
    m_userDataObjectMap.swap(dmmap);
#endif /* FG_USING_LUA_PLUS */

    m_isBindingComplete = FG_FALSE;
    m_init = FG_FALSE;

    fgScriptMT->deleteInstance();
    script::CScriptSubsystem::clear();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool script::CScriptSubsystem::initialize(void) {
    if(m_init)
        return m_init;
    if(m_isBindingComplete) {
        m_init = FG_TRUE;
        return m_init;
    }
    if(!m_pEventMgr || !m_pResourceMgr) {
        return FG_FALSE;
    }
    float t1 = timesys::ms();
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
        m_mgrMetatables[FG_NAMESPACE] = m_globals.CreateTable(fgScriptMT->getMetatableName(CMetatables::FG_NAMESPACE_MT_ID));
        m_mgrMetatables[FG_NAMESPACE].SetObject("__index", m_mgrMetatables[FG_NAMESPACE]);
        m_fgObj = m_luaState->CreateTable();
        m_fgObj.SetMetatable(m_mgrMetatables[FG_NAMESPACE]); // ? # ?
        m_globals.SetObject("fg", m_fgObj);
        m_globals.SetInteger("TRUE", 1);
        m_globals.SetInteger("FALSE", 0);
        m_globals.SetInteger("FG_TRUE", 1);
        m_globals.SetInteger("FG_FALSE", 0);
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

    if(!registerPhysics()) {
        FG_LOG_ERROR("Script: Failed to register Physical");
    }

    if(!registerGameEntities()) {
        FG_LOG_ERROR("Script: Failed to register Game Entities");
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

    if(!registerGameMainManager()) {
        FG_LOG_ERROR("Script: Failed to register GameManager object");
    }

    for(unsigned int i = 0; i < CMetatables::METATABLE_SIZE; i++) {
        const char* metatableName = fgScriptMT->getMetatableName(i);
        if(!metatableName)
            continue;
        LuaPlus::LuaObject metatable = m_luaState->GetRegistry().Get(metatableName);
        if(metatable.IsNil() || metatable.IsNone() || !metatable.IsTable())
            continue;
        fgScriptMT->getMetatable(i).metaObj = metatable;
        metatable.SetInteger("__meta_enum", i);
    }

    float t2 = timesys::ms();
    FG_LOG_DEBUG("Script: ScriptSubsystem initialized in %.2f seconds", (t2 - t1) / 1000.0f);
    m_init = FG_TRUE;
    m_isBindingComplete = FG_TRUE;
    m_managerType = FG_MANAGER_SCRIPT;

    if(m_cyclicGCCallback) {
        static_cast<fg::event::CEventManager *>(m_pEventMgr)->addCyclicCallback(m_cyclicGCCallback,
                                                                                FG_CYCLIC_CALLBACK_INFINITE_REPEAT,
                                                                                DEFAULT_GC_INTERVAL,
                                                                                NULL);
    }

    return FG_TRUE;
}
//------------------------------------------------------------------------------

int script::CScriptSubsystem::simpleFreeGCEvent(lua_State* L) {
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
    UserDataObjectMapItor it = m_userDataObjectMap.find(offset);
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
//------------------------------------------------------------------------------

int script::CScriptSubsystem::managedResourceGCEvent(lua_State* L) {
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
    CResource *pResource = (CResource *)unboxed;
    uintptr_t offset = (uintptr_t)pResource;
    UserDataObjectMapItor it = m_userDataObjectMap.find(offset);
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
//------------------------------------------------------------------------------

fgBool script::CScriptSubsystem::managedObjectDestructorCallback(void *systemData, void *userData) {
    if(!systemData)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    uintptr_t offset = (uintptr_t)systemData;
    UserDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        // This pointer was stored - erase it
        if(it->second.obj.GetRef() > 0 && it->second.isBound) {
            it->second.obj.SetMetatable(LuaPlus::LuaObject());
            it->second.obj.AssignNil();
        }
        it->second.obj.Reset();

        FG_LOG_DEBUG("GC: Managed Object Destructor Callback: pointer is registered - will be deleted: ptr[%p], offset[%lu]", systemData, offset);
        m_userDataObjectMap.erase(it);
    }
#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool script::CScriptSubsystem::registerConstants(void) {
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

    m_fgObj.SetInteger("TRUE", 1);
    m_fgObj.SetInteger("FALSE", 0);

    //
    // GUI STYLE CONSTANTS
    //
    m_fgObj.SetInteger("GUI_FLOAT_UNIT_INVALID", (float)FG_GUI_FLOAT_UNIT_INVALID);

    // fgGuiUnitType
    m_fgObj.SetInteger("GUI_PIXELS", (int)gui::Unit::PIXELS);
    m_fgObj.SetInteger("GUI_INCHES", (int)gui::Unit::INCHES);
    m_fgObj.SetInteger("GUI_BLOCKS", (int)gui::Unit::BLOCKS);
    m_fgObj.SetInteger("GUI_PERCENTS", (int)gui::Unit::PERCENTS);
    // fgGuiBorderStyle
    m_fgObj.SetInteger("GUI_BORDER_NONE", (int)gui::SBorder::Style::NONE);
    m_fgObj.SetInteger("GUI_BORDER_DOTTED", (int)gui::SBorder::Style::DOTTED);
    m_fgObj.SetInteger("GUI_BORDER_DASHED", (int)gui::SBorder::Style::DASHED);
    m_fgObj.SetInteger("GUI_BORDER_SOLID", (int)gui::SBorder::Style::SOLID);

    // fgGuiBorderWhich
    m_fgObj.SetInteger("GUI_BORDER_LEFT", (int)gui::SBorder::Which::LEFT);
    m_fgObj.SetInteger("GUI_BORDER_RIGHT", (int)gui::SBorder::Which::RIGHT);
    m_fgObj.SetInteger("GUI_BORDER_TOP", (int)gui::SBorder::Which::TOP);
    m_fgObj.SetInteger("GUI_BORDER_BOTTOM", (int)gui::SBorder::Which::BOTTOM);
    m_fgObj.SetInteger("GUI_BORDER_ALL", (int)gui::SBorder::Which::ALL);

    // fgGuiBackgroundStyle
    m_fgObj.SetInteger("GUI_BACKGROUND_NONE", (int)gui::SBackground::Style::NONE);
    m_fgObj.SetInteger("GUI_BACKGROUND_NORMAL", (int)gui::SBackground::Style::NORMAL);
    m_fgObj.SetInteger("GUI_BACKGROUND_MAX", (int)gui::SBackground::Style::MAX);
    m_fgObj.SetInteger("GUI_BACKGROUND_TILED", (int)gui::SBackground::Style::TILED);

    // fgGuiMarginWhich
    m_fgObj.SetInteger("GUI_MARGIN_LEFT", (int)gui::SMargin::Which::LEFT);
    m_fgObj.SetInteger("GUI_MARGIN_RIGHT", (int)gui::SMargin::Which::RIGHT);
    m_fgObj.SetInteger("GUI_MARGIN_TOP", (int)gui::SMargin::Which::TOP);
    m_fgObj.SetInteger("GUI_MARGIN_BOTTOM", (int)gui::SMargin::Which::BOTTOM);
    m_fgObj.SetInteger("GUI_MARGIN_ALL", (int)gui::SMargin::Which::ALL);

    // fgGuiPaddingWhich
    m_fgObj.SetInteger("GUI_PADDING_LEFT", (int)gui::SPadding::Which::LEFT);
    m_fgObj.SetInteger("GUI_PADDING_RIGHT", (int)gui::SPadding::Which::RIGHT);
    m_fgObj.SetInteger("GUI_PADDING_TOP", (int)gui::SPadding::Which::TOP);
    m_fgObj.SetInteger("GUI_PADDING_BOTTOM", (int)gui::SPadding::Which::BOTTOM);
    m_fgObj.SetInteger("GUI_PADDING_ALL", (int)gui::SPadding::Which::ALL);

    // fgGuiAlign
    m_fgObj.SetInteger("GUI_ALIGN_NONE", (int)gui::Align::NONE);
    m_fgObj.SetInteger("GUI_ALIGN_LEFT", (int)gui::Align::LEFT);
    m_fgObj.SetInteger("GUI_ALIGN_RIGHT", (int)gui::Align::RIGHT);
    m_fgObj.SetInteger("GUI_ALIGN_CENTER", (int)gui::Align::CENTER);
    m_fgObj.SetInteger("GUI_ALIGN_MIDDLE", (int)gui::Align::MIDDLE);
    m_fgObj.SetInteger("GUI_ALIGN_TOP", (int)gui::Align::TOP);
    m_fgObj.SetInteger("GUI_ALIGN_BOTTOM", (int)gui::Align::BOTTOM);

    // fgGuiPositionStyle
    m_fgObj.SetInteger("GUI_POS_STATIC", (int)gui::SPosition::Style::STATICPOS);
    m_fgObj.SetInteger("GUI_POS_FIXED", (int)gui::SPosition::Style::FIXED);
    m_fgObj.SetInteger("GUI_POS_RELATIVE", (int)gui::SPosition::Style::RELATIVE);
    m_fgObj.SetInteger("GUI_POS_ABSOLUTE", (int)gui::SPosition::Style::ABSOLUTE);

    // fgGuiSizeStyle
    m_fgObj.SetInteger("GUI_SIZE_PIXELS", (int)gui::SSize::Style::PIXELS);
    m_fgObj.SetInteger("GUI_SIZE_INCHES", (int)gui::SSize::Style::INCHES);
    m_fgObj.SetInteger("GUI_SIZE_BLOCKS", (int)gui::SSize::Style::BLOCKS);
    m_fgObj.SetInteger("GUI_SIZE_PERCENTS", (int)gui::SSize::Style::PERCENTS);
    m_fgObj.SetInteger("GUI_SIZE_MAX", (int)gui::SSize::Style::MAX);
    m_fgObj.SetInteger("GUI_SIZE_MIN", (int)gui::SSize::Style::MIN);

    //
    // GUI WIDGET CONSTANTS
    //
    m_fgObj.SetInteger("GUI_WIDGET_STATE_NONE", (int)gui::CWidget::STATE_NONE);
    m_fgObj.SetInteger("GUI_WIDGET_STATE_FOCUS", (int)gui::CWidget::STATE_FOCUS);
    m_fgObj.SetInteger("GUI_WIDGET_STATE_PRESSED", (int)gui::CWidget::STATE_PRESSED);
    m_fgObj.SetInteger("GUI_WIDGET_STATE_ACTIVATED", (int)gui::CWidget::STATE_ACTIVATED);
    m_fgObj.SetInteger("GUI_WIDGET_STATE_DEACTIVATED", (int)gui::CWidget::STATE_DEACTIVATED);
    m_fgObj.SetInteger("GUI_WIDGET_STATE_COUNT", (int)gui::CWidget::STATE_COUNT);

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

    m_fgObj.SetInteger("EVENT_INVALID", (int)event::INVALID);

    m_fgObj.SetInteger("EVENT_TOUCH_PRESSED", (int)event::TOUCH_PRESSED);
    m_fgObj.SetInteger("EVENT_TOUCH_RELEASED", (int)event::TOUCH_RELEASED);
    m_fgObj.SetInteger("EVENT_TOUCH_MOTION", (int)event::TOUCH_MOTION);
    m_fgObj.SetInteger("EVENT_TOUCH_TAP_FINISHED", (int)event::TOUCH_TAP_FINISHED);
    m_fgObj.SetInteger("EVENT_MOUSE_PRESSED", (int)event::MOUSE_PRESSED);
    m_fgObj.SetInteger("EVENT_MOUSE_RELEASED", (int)event::MOUSE_RELEASED);
    m_fgObj.SetInteger("EVENT_MOUSE_MOTION", (int)event::MOUSE_MOTION);
    m_fgObj.SetInteger("EVENT_SWIPE_X", (int)event::SWIPE_X);
    m_fgObj.SetInteger("EVENT_SWIPE_Y", (int)event::SWIPE_Y);
    m_fgObj.SetInteger("EVENT_SWIPE_XY", (int)event::SWIPE_XY);
    m_fgObj.SetInteger("EVENT_SWIPE_ANGLE", (int)event::SWIPE_ANGLE);
    m_fgObj.SetInteger("EVENT_SWIPE_PINCH", (int)event::SWIPE_PINCH);
    m_fgObj.SetInteger("EVENT_MULTI_SWIPE_ROTATE", (int)event::MULTI_SWIPE_ROTATE);
    m_fgObj.SetInteger("EVENT_KEY_DOWN", (int)event::KEY_DOWN);
    m_fgObj.SetInteger("EVENT_KEY_UP", (int)event::KEY_UP);

    m_fgObj.SetInteger("EVENT_RESOURCE_CREATED", (int)event::RESOURCE_CREATED);
    m_fgObj.SetInteger("EVENT_RESOURCE_REMOVED", (int)event::RESOURCE_REMOVED);
    m_fgObj.SetInteger("EVENT_RESOURCE_DISPOSED", (int)event::RESOURCE_DISPOSED);
    m_fgObj.SetInteger("EVENT_RESOURCE_DESTROYED", (int)event::RESOURCE_DESTROYED);
    m_fgObj.SetInteger("EVENT_RESOURCE_REQUESTED", (int)event::RESOURCE_REQUESTED);

    m_fgObj.SetInteger("EVENT_PROGRAM_INIT", (int)event::PROGRAM_INIT);
    m_fgObj.SetInteger("EVENT_VERTEX_STREAM_READY", (int)event::VERTEX_STREAM_READY);
    m_fgObj.SetInteger("EVENT_CAMERA_CHANGED", (int)event::CAMERA_CHANGED);
    m_fgObj.SetInteger("EVENT_SOUND_PLAYED", (int)event::SOUND_PLAYED);
    m_fgObj.SetInteger("EVENT_MENU_CHANGED", (int)event::MENU_CHANGED);
    m_fgObj.SetInteger("EVENT_WIDGET_STATE_CHANGED", (int)event::WIDGET_STATE_CHANGED);
    m_fgObj.SetInteger("EVENT_SENSORS_CHANGED", (int)event::SENSORS_CHANGED);

    m_fgObj.SetInteger("EVENT_GAME_CONTROLLER_ADDED", (int)event::GAME_CONTROLLER_ADDED);
    m_fgObj.SetInteger("EVENT_GAME_CONTROLLER_REMOVED", (int)event::GAME_CONTROLLER_REMOVED);
    m_fgObj.SetInteger("EVENT_GAME_CONTROLLER_BUTTON", (int)event::GAME_CONTROLLER_BUTTON);
    m_fgObj.SetInteger("EVENT_GAME_CONTROLLER_AXIS", (int)event::GAME_CONTROLLER_AXIS);

    //
    // GAME LOGIC EVENT TYPE CONSTANTS
    //
    m_fgObj.SetInteger("EVENT_GAME_STARTED", (int)game::GAME_STARTED);
    m_fgObj.SetInteger("EVENT_GAME_PAUSED", (int)game::GAME_PAUSED);
    m_fgObj.SetInteger("EVENT_GAME_STOPPED", (int)game::GAME_STOPPED);
    m_fgObj.SetInteger("EVENT_GAME_LOADING", (int)game::GAME_LOADING);
    m_fgObj.SetInteger("EVENT_GAME_RESTARTING", (int)game::GAME_RESTARTING);
    m_fgObj.SetInteger("EVENT_GAME_FINISHED", (int)game::GAME_FINISHED);
    m_fgObj.SetInteger("EVENT_GAME_WAITING", (int)game::GAME_WAITING);
    m_fgObj.SetInteger("EVENT_GAME_CONNECTED", (int)game::GAME_CONNECTED);
    m_fgObj.SetInteger("EVENT_GAME_DISCONNECTED", (int)game::GAME_DISCONNECTED);

    //
    // SWIPE DIRECTION
    //
    m_fgObj.SetInteger("SWIPE_INVALID", (int)event::SSwipe::INVALID);
    m_fgObj.SetInteger("SWIPE_LEFT", (int)event::SSwipe::LEFT);
    m_fgObj.SetInteger("SWIPE_RIGHT", (int)event::SSwipe::RIGHT);
    m_fgObj.SetInteger("SWIPE_UP", (int)event::SSwipe::UP);
    m_fgObj.SetInteger("SWIPE_DOWN", (int)event::SSwipe::DOWN);
    m_fgObj.SetInteger("SWIPE_ANGLE", (int)event::SSwipe::ANGLE);

    //
    // PINCH DIRECTION
    //
    m_fgObj.SetInteger("PINCH_INVALID", (int)event::SSwipePinch::INVALID);
    m_fgObj.SetInteger("PINCH_IN", (int)event::SSwipePinch::IN);
    m_fgObj.SetInteger("PINCH_OUT", (int)event::SSwipePinch::OUT);

    //
    // RESOURCE STATUS
    //
    m_fgObj.SetInteger("RESOURCE_CREATED", (int)event::SResource::CREATED);
    m_fgObj.SetInteger("RESOURCE_REMOVED", (int)event::SResource::REMOVED);
    m_fgObj.SetInteger("RESOURCE_DISPOSED", (int)event::SResource::DISPOSED);
    m_fgObj.SetInteger("RESOURCE_DESTROYED", (int)event::SResource::DESTROYED);
    m_fgObj.SetInteger("RESOURCE_REQUESTED", (int)event::SResource::REQUESTED);

    //
    // SCENE MANAGER EVENTS
    //
    m_fgObj.SetInteger("SCENE_NODE_COLLISION", (int)event::SCENE_NODE_COLLISION);
    m_fgObj.SetInteger("SCENE_NODE_TRIGGER_FIRED", (int)event::SCENE_NODE_TRIGGER_FIRED);
    m_fgObj.SetInteger("SCENE_NODE_INSERTED", (int)event::SCENE_NODE_INSERTED);
    m_fgObj.SetInteger("SCENE_NODE_REMOVED", (int)event::SCENE_NODE_REMOVED);
    m_fgObj.SetInteger("SCENE_NODE_DESTROYED", (int)event::SCENE_NODE_DESTROYED);
    m_fgObj.SetInteger("SCENE_CLEARED", (int)event::SCENE_CLEARED);
    m_fgObj.SetInteger("SCENE_DUMMY", (int)event::SCENE_DUMMY);

    m_fgObj.SetInteger("ON_COLLISION_BEGIN", (int)gfx::CSceneNodeTrigger::ON_COLLISION_BEGIN);
    m_fgObj.SetInteger("ON_COLLISION_END", (int)gfx::CSceneNodeTrigger::ON_COLLISION_END);

    //
    // PHYSICS CONSTANTS (COLLISION BODY/OTHER)
    //

    m_fgObj.SetInteger("BODY_INVALID", (int)physics::BODY_INVALID);
    m_fgObj.SetInteger("BODY_BOX", (int)physics::BODY_BOX);
    m_fgObj.SetInteger("BODY_CUBE", (int)physics::BODY_BOX);
    m_fgObj.SetInteger("BODY_SPHERE", (int)physics::BODY_SPHERE);
    m_fgObj.SetInteger("BODY_COMPLEX", (int)physics::BODY_COMPLEX);
    m_fgObj.SetInteger("BODY_TRIANGLE_MESH", (int)physics::BODY_TRIANGLE_MESH);
    m_fgObj.SetInteger("BODY_RAGDOLL", (int)physics::BODY_RAGDOLL);

#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool script::CScriptSubsystem::registerAdditionalTypes(void) {
    if(!m_luaState)
        return FG_FALSE;

    if(m_isBindingComplete)
        return FG_TRUE;

#if defined(FG_USING_LUA_PLUS)
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;

    // Vector2i | FG VECTOR 2I
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(CMetatables::VECTOR2I_MT_ID))
            .Property("x", &Vector2i::x)
            .Property("y", &Vector2i::y)
            .Property("s", &Vector2i::s)
            .Property("t", &Vector2i::t)
            .MetatableFunction("__gc", &script::CScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<Vector2i>
    m_fgObj.Register("Vector2i", &script::CScriptSubsystem::simpleTypedMallocEvent<Vector2i, CMetatables::VECTOR2I_MT_ID>);
    FG_LOG_DEBUG("Script: Register metatable '%s' for Vector2i", fgScriptMT->getMetatableName(CMetatables::VECTOR2I_MT_ID));

    // Vector2f | FG VECTOR 2F
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(CMetatables::VECTOR2F_MT_ID))
            .Property("x", &Vector2f::x)
            .Property("y", &Vector2f::y)
            .Property("s", &Vector2f::s)
            .Property("t", &Vector2f::t)
            .MetatableFunction("__gc", &script::CScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<Vector2f>
    m_fgObj.Register("Vector2f", &script::CScriptSubsystem::simpleTypedMallocEvent<Vector2f, CMetatables::VECTOR2F_MT_ID>);
    FG_LOG_DEBUG("Script: Register metatable '%s' for Vector2f", fgScriptMT->getMetatableName(CMetatables::VECTOR2F_MT_ID));

    // Vector3i | FG VECTOR 3I
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(CMetatables::VECTOR3I_MT_ID))
            .Property("x", &Vector3i::x)
            .Property("y", &Vector3i::y)
            .Property("z", &Vector3i::z)
            .Property("r", &Vector3i::r)
            .Property("g", &Vector3i::g)
            .Property("b", &Vector3i::b)
            .Property("s", &Vector3i::s)
            .Property("t", &Vector3i::t)
            .MetatableFunction("__gc", &script::CScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<Vector3i>
    m_fgObj.Register("Vector3i", &script::CScriptSubsystem::simpleTypedMallocEvent<Vector3i, CMetatables::VECTOR3I_MT_ID>);
    FG_LOG_DEBUG("Script: Register metatable '%s' for Vector3i", fgScriptMT->getMetatableName(CMetatables::VECTOR3I_MT_ID));

    // Vector3f | FG VECTOR 3F
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(CMetatables::VECTOR3F_MT_ID))
            .Property("x", &Vector3f::x)
            .Property("y", &Vector3f::y)
            .Property("z", &Vector3f::z)
            .Property("r", &Vector3f::r)
            .Property("g", &Vector3f::g)
            .Property("b", &Vector3f::b)
            .Property("s", &Vector3f::s)
            .Property("t", &Vector3f::t)
            .MetatableFunction("__gc", &script::CScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<Vector3f>
    m_fgObj.Register("Vector3f", &script::CScriptSubsystem::simpleTypedMallocEvent<Vector3f, CMetatables::VECTOR3F_MT_ID>);
    m_fgObj.Register("Color3f", &script::CScriptSubsystem::simpleTypedMallocEvent<Vector3f, CMetatables::VECTOR3F_MT_ID>);
    FG_LOG_DEBUG("Script: Register metatable '%s' for Vector3f", fgScriptMT->getMetatableName(CMetatables::VECTOR3F_MT_ID));

    // Vector4i | FG VECTOR 4I
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(CMetatables::VECTOR4I_MT_ID))
            .Property("x", &Vector4i::x)
            .Property("y", &Vector4i::y)
            .Property("z", &Vector4i::z)
            .Property("w", &Vector4i::w)
            .Property("r", &Vector4i::r)
            .Property("g", &Vector4i::g)
            .Property("b", &Vector4i::b)
            .Property("a", &Vector4i::a)
            .Property("s", &Vector4i::s)
            .Property("t", &Vector4i::t)
            .MetatableFunction("__gc", &script::CScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<Vector4i>
    m_fgObj.Register("Vector4i", &script::CScriptSubsystem::simpleTypedMallocEvent<Vector4i, CMetatables::VECTOR4I_MT_ID>);
    //m_fgObj.Register("Color4i", &fgScriptSubsystem::simpleTypedMallocEvent<Vector4i, fgScriptMetatables::VECTOR4I_MT_ID>);
    FG_LOG_DEBUG("Script: Register metatable '%s' for Vector4i", fgScriptMT->getMetatableName(CMetatables::VECTOR4I_MT_ID));

    // Vector4f | FG VECTOR 4F
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(CMetatables::VECTOR4F_MT_ID))
            .Property("x", &Vector4f::x)
            .Property("y", &Vector4f::y)
            .Property("z", &Vector4f::z)
            .Property("w", &Vector4f::w)
            .Property("r", &Vector4f::r)
            .Property("g", &Vector4f::g)
            .Property("b", &Vector4f::b)
            .Property("a", &Vector4f::a)
            .Property("s", &Vector4f::s)
            .Property("t", &Vector4f::t)
            .MetatableFunction("__gc", &script::CScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<Vector4f>
    m_fgObj.Register("Vector4f", &script::CScriptSubsystem::simpleTypedMallocEvent<Vector4f, CMetatables::VECTOR4F_MT_ID>);
    m_fgObj.Register("Color4f", &script::CScriptSubsystem::simpleTypedMallocEvent<Vector4f, CMetatables::VECTOR4F_MT_ID>);
    FG_LOG_DEBUG("Script: Register metatable '%s' for Vector4f", fgScriptMT->getMetatableName(CMetatables::VECTOR4F_MT_ID));
#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}
//------------------------------------------------------------------------------

int script::CScriptSubsystem::addEventCallbackWrapper(lua_State *L) {
#if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    LuaPlus::LuaStack args(state);
    const char* script = NULL;
    event::EventType eventType = event::INVALID;
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
    fgBool calledAsMethod = FG_FALSE, isValidObject = FG_FALSE;
    if(args.Count() >= 3) {
        int id = 1;
        if(args[id].IsUserdata()) {
            void* pUnboxed = state->UnBoxPointer(args[id].m_stackIndex);
            LuaPlus::LuaObject obj = args[id];
            if(obj.GetMetatable() == m_fgObj[fgScriptMT->getMetatableName(fg::script::CMetatables::EVENT_MANAGER_MT_ID)]) {
                event::CEventManager* pEventMgr = (event::CEventManager*)pUnboxed;
                if(pEventMgr->getManagerType() == FG_MANAGER_EVENT) {
                    isValidObject = FG_TRUE;
                }
                int value = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
                if(value == (int)fg::script::CMetatables::EVENT_MANAGER_MT_ID) {
                    isValidObject = FG_TRUE;
                }
            }
            calledAsMethod = FG_TRUE;
            id++;
        }
        if(calledAsMethod && !isValidObject) {
            // fail
            return 0;
        }

        if(args[id].IsInteger()) {
            int iVal = args[id].GetInteger();
            //if(iVal < (int)FG_NUM_EVENT_TYPES)
            eventType = (event::EventType)iVal;
            FG_LOG_DEBUG("Script: EventWrapper: eventType[%d]", iVal);
        }
        id++;
        if(args[id].IsFunction()) {
            objFunction = args[id];
            hasFunction = FG_TRUE;
        } else if(args[id].IsString() && !args[id].IsInteger() && !args[id].IsBoolean()) {
            script = args[id].GetString();
            FG_LOG_DEBUG("Script: EventWrapper: 2nd argument is a string[%s]", script);
        }
        id++;
        if(args.Count() >= 4) {
            if(args[id].IsInteger()) {
                argc = abs(args[id].GetInteger());
                FG_LOG_DEBUG("Script: EventWrapper: 3rd argument: argc[%d]", argc);
            }
        }
    }
    if(eventType == event::INVALID) {
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

    fg::event::CFunctionCallback *callback = NULL;
    if(script) {
        callback = new CScriptCallback(L, script, 0, CScriptCallback::SCRIPT);
    } else if(hasFunction) {
        callback = new CScriptCallback(L, objFunction, argc, CScriptCallback::EVENT_CALLBACK);
    }
    if(static_cast<fg::event::CEventManager *>(m_pEventMgr)->addCallback(eventType, callback)) {
        FG_LOG_DEBUG("Script: Successfully added callback for event[%d]", eventType);
    } else {
        FG_LOG_DEBUG("Script: Failed to add callback for event[%d]", eventType);
    }
    // Can also return this pointer for future reference - so it is possible to remove
    // callback for given event type
#endif
    return 0;
}
//------------------------------------------------------------------------------

int script::CScriptSubsystem::__isValid(lua_State *L) {
#if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    LuaPlus::LuaStack args(state);
    LuaPlus::LuaObject returnObj;
    int returnValue = 0;

    if(args.Count() > 0 && args[1].IsUserdata()) {
        LuaPlus::LuaObject obj = args[1];
        void* pUnboxed = state->UnBoxPointer(args[1].m_stackIndex);
        uintptr_t offset = (uintptr_t)pUnboxed;
        if(offset > 0)
            returnValue = 1; // #FIXME
        UserDataObjectMapItor itor = m_userDataObjectMap.find(offset);
        if(itor != m_userDataObjectMap.end() && offset > 0) {
            if(itor->second.obj == obj && itor->second.isBound) {
                returnValue = 1;
            }
        }
        //int metaEnum = (int)obj.GetMetatable().Get("__meta_enum").GetInteger();
        //const char* metatableName = fgScriptMT->getMetatableName(metaEnum);
    }
    returnObj.AssignBoolean(state, (bool)(returnValue > 0));
    returnObj.Push(state);
    return 1;
#else
    return 0;
#endif
}
//------------------------------------------------------------------------------

int script::CScriptSubsystem::__destroy(lua_State* L) {
#if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    LuaPlus::LuaStack args(state);
    //LuaPlus::LuaObject returnObj;
    if(!args.Count())
        return 0;
    if(!args[1].IsUserdata())
        return 0;

    void* pUnboxed = state->UnBoxPointer(args[1].m_stackIndex);
    fgBool isManaged = FG_FALSE;
    uintptr_t offset = (uintptr_t)pUnboxed;
    LuaPlus::LuaObject selfObj = args[1];
    UserDataObjectMapItor itor = m_userDataObjectMap.find(offset);
    if(itor != m_userDataObjectMap.end() && offset > 0) {
        if(itor->second.obj == selfObj && itor->second.isBound) {
            isManaged = FG_TRUE;
        }
    }
    if(isManaged) {
        void** pUserdata = (void **)selfObj.GetUserdata();
        //if(pUserdata)
        //    *pUserdata = NULL;
    }
#endif
    return 0;
}
//------------------------------------------------------------------------------

int script::CScriptSubsystem::addTimeoutCallbackWrapper(lua_State *L) {
#if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    LuaPlus::LuaStack args(state);
    const char* script = NULL;
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
    event::CFunctionCallback *callback = NULL;
    if(script) {
        callback = new CScriptCallback(L, script, 0, CScriptCallback::SCRIPT);
    } else if(hasFunction) {
        callback = new CScriptCallback(L, objFunction, argc, CScriptCallback::EVENT_CALLBACK);
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
//------------------------------------------------------------------------------

int script::CScriptSubsystem::addCyclicCallbackWrapper(lua_State *L) {
#if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    LuaPlus::LuaStack args(state);
    const char* script = NULL;
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
    if(args.Count() == 4) {
        if(args[1].IsUserdata()) {
            FG_LOG_DEBUG("Script -> first argument is Userdata\n");
        }
        if(args[1].IsTable()) {
        }

    }
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
    event::CFunctionCallback *callback = NULL;
    if(script) {
        callback = new CScriptCallback(L, script, 0, CScriptCallback::SCRIPT);
    } else if(hasFunction) {
        callback = new CScriptCallback(L, objFunction, argc, CScriptCallback::EVENT_CALLBACK);
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
//------------------------------------------------------------------------------

fgBool script::CScriptSubsystem::registerEventManager(void) {
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

    {
        LuaPlus::LuaAutoBlock block(m_luaState);
        //m_luaState->NewMetatable()

        m_mgrMetatables[EVENT_MGR] = m_fgObj.CreateTable(fgScriptMT->getMetatableName(CMetatables::EVENT_MANAGER_MT_ID));
        m_mgrMetatables[EVENT_MGR].SetObject("__index", m_mgrMetatables[EVENT_MGR]);
        //m_mgrMetatables[EVENT_MGR].RegisterObjectDirect("");
        // Could use Register direct? hmm?
        m_mgrMetatables[EVENT_MGR].SetInteger("__meta_enum", (int)CMetatables::EVENT_MANAGER_MT_ID);
        m_mgrMetatables[EVENT_MGR].Register("addEventCallback", &addEventCallbackWrapper);
        m_mgrMetatables[EVENT_MGR].Register("addTimeoutCallback", &addTimeoutCallbackWrapper);
        m_mgrMetatables[EVENT_MGR].Register("addCyclicCallback", &addCyclicCallbackWrapper);
        m_mgrMetatables[EVENT_MGR].Register("isValid", &__isValid);

        //m_mgrMetatables[EVENT_MGR].Register("destroy", &__destroy);

        uintptr_t offset = (uintptr_t)m_pEventMgr;
        UserDataObjectMapItor it = m_userDataObjectMap.find(offset);
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
    }
    // Event Base structure
    const char* metatableNameEventBase = fgScriptMT->getMetatableName(CMetatables::EVENT_BASE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableNameEventBase)
            .Property("eventType", &event::SEventBase::eventType)
            // .Property("eventType", &fgEventBase::eventType)
            // .Property("timeStamp", &fgEventBase::timeStamp) // Time stamp should be float ?
            .Function("isValid", &script::CScriptSubsystem::__isValid)
            ;
    //.MetatableFunction("__gc", &fgScriptSubsystem::simpleFreeGCEvent); // simpleTypedGCEvent<Vector2i>
    //m_fgObj.Register("Vector2i", &fgScriptSubsystem::simpleTypedMallocEvent<Vector2i, VECTOR2I_MT_ID>);
    //FG_LOG_DEBUG("Script: Register metatable '%s' for Vector2i", fgScriptMT->getMetatableName(fgScriptMetatables::VECTOR2I_MT_ID));

    // Controller Device Event : EventBase
    const char* metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_CONTROLLER_DEVICE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("which", &event::SControllerDevice::which);
    // __gc ? nope

    // Controller Button Event : EventBase
    metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_CONTROLLER_BUTTON_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("which", &event::SControllerButton::which)
            .Property("button", &event::SControllerButton::button)
            .Property("state", &event::SControllerButton::state)
            ;
    // __gc ? nope

    // Controller Axis Event : EventBase
    metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_CONTROLLER_AXIS_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("which", &event::SControllerAxis::which)
            .Property("value", &event::SControllerAxis::axis)
            .Property("axis", &event::SControllerAxis::value)

            ;
    // __gc ? nope

    // Touch Event : EventBase
    metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_TOUCH_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("x", &event::STouch::x)
            .Property("y", &event::STouch::y)
            .Property("touchID", &event::STouch::touchID)
            .Property("pressed", &event::STouch::pressed)
            ;
    // __gc ? nope

    // Mouse Event : EventBase
    metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_MOUSE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("x", &event::SMouse::x)
            .Property("y", &event::SMouse::y)
            .Property("buttonID", &event::SMouse::buttonID)
            .Property("pressed", &event::SMouse::pressed)
            ;
    // __gc ? nope

    // Swipe Event : EventBase #FIXME #REFACTOR
    metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_SWIPE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("swipeDirection", &event::SSwipe::swipeDirection)
            .Property("xStart", &event::SSwipe::xStart)
            .Property("yStart", &event::SSwipe::yStart)
            .Property("xEnd", &event::SSwipe::xEnd)
            .Property("yEnd", &event::SSwipe::yEnd)
            .Property("swipeXOffset", &event::SSwipe::swipeXOffset)
            .Property("swipeYOffset", &event::SSwipe::swipeYOffset)
            .Property("swipeXSteps", &event::SSwipe::swipeXSteps)
            .Property("swipeYSteps", &event::SSwipe::swipeYSteps)
            ;
    // __gc ? nope

    //
    // Swipe Pinch Event : EventBase #FIXME #REFACTOR
    //
    metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_SWIPE_PINCH_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("pinchDirection", &event::SSwipePinch::pinchDirection)
            .Property("x", &event::SSwipePinch::x)
            .Property("y", &event::SSwipePinch::y)
            .Property("x2", &event::SSwipePinch::x2)
            .Property("y2", &event::SSwipePinch::y2)
            .Property("pinchXOffset", &event::SSwipePinch::pinchXOffset)
            .Property("pinchYOffset", &event::SSwipePinch::pinchYOffset)
            .Property("pinchSize", &event::SSwipePinch::pinchSize)
            ;
    // __gc ? nope

    //
    // Swipe Rotate Event : EventBase
    //
    metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_SWIPE_ROTATE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("x", &event::SSwipeRotate::x)
            .Property("y", &event::SSwipeRotate::y)
            .Property("x2", &event::SSwipeRotate::x2)
            .Property("y2", &event::SSwipeRotate::y2)
            .Property("angle", &event::SSwipeRotate::angle)
            ;
    // __gc ? nope

    // Key Event : EventBase
    metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_KEY_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("keyCode", &event::SKey::keyCode)
            .Property("which", &event::SKey::which)
            .Property("pressed", &event::SKey::pressed)
            ;
    // __gc ? nope

    // Resource Event : EventBase
    metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_RESOURCE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("status", &event::SResource::status)
            .Property("resource", &event::SResource::resource) // need LPCD for fgResource * + type check
            ;
    // __gc ? nope

    // Vertex Stream Event : EventBase
    metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_VERTEX_STREAM_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            //.Property("which", &::which)
            ;
    // __gc ? nope

    //
    // Camera Event : EventBase
    //
    metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_CAMERA_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            ;
    // __gc ? nope

    //
    // Sound Event : EventBase
    //
    metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_SOUND_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            ;
    // __gc ? nope

    // Menu Changed Event : EventBase
    metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_MENU_CHANGED_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("prevMenuName", &event::SMenuChanged::prevMenuName)
            .Property("nextMenuName", &event::SMenuChanged::nextMenuName)
            .Property("didChange", &event::SMenuChanged::didChange)
            ;
    // __gc ? nope

    //
    // Widget Event : EventBase
    //
    metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_WIDGET_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            ;
    // __gc ? nope

    //
    // Sensors Event : EventBase
    //
    metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_SENSORS_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("x", &event::SSensors::x)
            .Property("y", &event::SSensors::y)
            .Property("z", &event::SSensors::z)
            ;
    // __gc ? nope

    // Event Main Union structure
    metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_MAIN_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName)
            .Property("eventType", &event::SEvent::code)
            .Property("touch", &event::SEvent::touch)
            .Property("mouse", &event::SEvent::mouse)
            .Property("swipe", &event::SEvent::swipe)
            .Property("swipePinch", &event::SEvent::swipePinch)
            .Property("swipeRotate", &event::SEvent::swipeRotate)
            .Property("key", &event::SEvent::key)
            .Property("resource", &event::SEvent::resource)
            .Property("vertexStream", &event::SEvent::vertexStream)
            .Property("camera", &event::SEvent::camera)
            .Property("sound", &event::SEvent::sound)
            .Property("menuChanged", &event::SEvent::menuChanged)
            .Property("widget", &event::SEvent::widget)
            .Property("sensors", &event::SEvent::sensors)
            .Property("controller", &event::SEvent::controller)
            .Property("controllerAxis", &event::SEvent::controllerAxis)
            .Property("controllerButton", &event::SEvent::controllerButton)
            .Function("isValid", &script::CScriptSubsystem::__isValid)
            ;
    // __gc ? nope

#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}
//------------------------------------------------------------------------------

int script::CScriptSubsystem::newResourceWrapper(lua_State* L) {
    if(!L)
        return 0;
#if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    LuaPlus::LuaStack args(state);
    const char* info = NULL;
    FG_LOG_DEBUG("Script: New Resource: argc[%d]", args.Count());
    if(args.Count()) {
        if(args[1].IsString()) {
            info = args[1].GetString();
        } else if(args[1].IsUserdata() && args.Count() == 2) {
            if(args[2].IsString()) {
                info = args[2].GetString();
            }
        }

    }
    fgBool status = FG_TRUE;
    if(!m_pResourceMgr)
        return 0;
    if(m_pResourceMgr->getManagerType() != FG_MANAGER_RESOURCE)
        return 0;
    fg::resource::CResource *pResource = static_cast<fg::resource::CResourceManager *>(m_pResourceMgr)->request(info);
    LuaPlus::LuaObject resourceObj = state->BoxPointer(pResource);
    if(!pResource) {
        //meta::get(meta::RESOURCE_MT_ID);
        //const char *metatableName = fgScriptMT->getMetatableName(CMetatables::RESOURCE_MT_ID);
        //resourceObj.SetMetatable(state->GetRegistry()[metatableName]);
        LuaPlus::LuaObject metaObj = fgScriptMT->getMetatable(CMetatables::RESOURCE_MT_ID).metaObj;
        resourceObj.SetMetatable(metaObj);
        return 1;
    }
    uintptr_t offset = (uintptr_t)pResource;
    UserDataObjectMapItor it = m_userDataObjectMap.find(offset);
    FG_LOG_DEBUG("Script: New Resource: ptr[%p], offset[%lu]", pResource, offset);
    resource::ResourceType resType = pResource->getResourceType();
    CMetatables::METAID metaID = fgScriptMT->getMetatableIDFromResourceType(resType);
    if(metaID == CMetatables::EMPTY_MT_ID) {
        //const char *metatableName = fgScriptMT->getMetatableName(CMetatables::RESOURCE_MT_ID);
        //resourceObj.SetMetatable(state->GetRegistry()[metatableName]);
        LuaPlus::LuaObject metaObj = fgScriptMT->getMetatable(CMetatables::RESOURCE_MT_ID).metaObj;
        resourceObj.SetMetatable(metaObj);
        status = FG_FALSE;
        FG_LOG_DEBUG("Script: New Resource: Unknown resource type requested / not supported: resType[%d]", resType);
    }
    const char* metatableName = fgScriptMT->getMetatableName(metaID);
    if(status) {
        //resourceObj.SetMetatable(state->GetRegistry()[metatableName]);
        LuaPlus::LuaObject metaObj = fgScriptMT->getMetatable(metaID).metaObj;
        resourceObj.SetMetatable(metaObj);
        //resourceObj.SetMetatable(fgScriptMT->getMetatable(metaID).metaObj);
        FG_LOG_DEBUG("Script: New Resource: metatable: id[%d], name[%s]", metaID, metatableName);
    }
    if(it == m_userDataObjectMap.end() && offset) {
        m_userDataObjectMap[offset] = SUserDataObject(resourceObj, FG_TRUE);
    }
    if(status) {
        pResource->registerOnDestruct(&script::CScriptSubsystem::managedObjectDestructorCallback, NULL);
    }
#endif /* FG_USING_LUA_PLUS */
    return 1;
}
//------------------------------------------------------------------------------

fgBool script::CScriptSubsystem::registerResourceManager(void) {
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
    m_mgrMetatables[RESOURCE_MGR] = m_fgObj.CreateTable(fgScriptMT->getMetatableName(CMetatables::RESOURCE_MANAGER_MT_ID));
    m_mgrMetatables[RESOURCE_MGR].SetObject("__index", m_mgrMetatables[RESOURCE_MGR]);
    m_mgrMetatables[RESOURCE_MGR].SetInteger("__meta_enum", (int)CMetatables::RESOURCE_MANAGER_MT_ID);
    m_mgrMetatables[RESOURCE_MGR].Register("isValid", &script::CScriptSubsystem::__isValid);
    m_mgrMetatables[RESOURCE_MGR].Register("request", &script::CScriptSubsystem::newResourceWrapper);

    uintptr_t offset = (uintptr_t)m_pResourceMgr;
    UserDataObjectMapItor it = m_userDataObjectMap.find(offset);
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
    typedef const char*(fg::resource::CResource::base_type::*getFilePathStrType)(void)const;
    // Register Base Resource metatable
    LPCD::Class(m_luaState->GetCState(),
                fgScriptMT->getMetatableName(CMetatables::RESOURCE_MT_ID))
            .ObjectDirect("getName", (resource::CResource::base_type::base_type *)0, &resource::CResource::base_type::base_type::getNameStr)
            .ObjectDirect("isManaged", (resource::CResource::base_type::base_type *)0, &resource::CResource::base_type::base_type::isManaged)
            .ObjectDirect("getFilePath",
                          (resource::CResource::base_type *)0,
                          static_cast<getFilePathStrType>(&resource::CResource::base_type::getFilePathStr))
            .ObjectDirect("getSize", (resource::CResource *)0, &resource::CResource::getSize)
            .ObjectDirect("getLastAccess", (resource::CResource *)0, &resource::CResource::getLastAccess)
            .ObjectDirect("isDisposed", (resource::CResource *)0, &resource::CResource::isDisposed)
            .ObjectDirect("isLocked", (resource::CResource *)0, &resource::CResource::isLocked)
            .ObjectDirect("dispose", (resource::CResource *)0, &resource::CResource::dispose)
            .Function("isValid", &script::CScriptSubsystem::__isValid);
    //.MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent); // #DELETE

    // Register Texture Resource metatable
    LPCD::Class(m_luaState->GetCState(),
                fgScriptMT->getMetatableName(CMetatables::TEXTURE_RESOURCE_MT_ID),
                fgScriptMT->getMetatableName(CMetatables::RESOURCE_MT_ID))
            .ObjectDirect("getWidth", (gfx::CTexture*)0, &gfx::CTexture::getWidth)
            .ObjectDirect("getHeight", (gfx::CTexture*)0, &gfx::CTexture::getHeight)
            .ObjectDirect("getComponents", (gfx::CTexture*)0, &gfx::CTexture::getComponents)
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedResourceGCEvent);

    // Register Font Resource metatable
    LPCD::Class(m_luaState->GetCState(),
                fgScriptMT->getMetatableName(CMetatables::FONT_RESOURCE_MT_ID),
                fgScriptMT->getMetatableName(CMetatables::TEXTURE_RESOURCE_MT_ID))
            .ObjectDirect("getFontType", (gui::CFontResource *)0, &gui::CFontResource::getFontType)
            .ObjectDirect("getStep", (gui::CFontResource *)0, &gui::CFontResource::getStep)
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedResourceGCEvent);

    // Register Gfx Model Resource metatable
    LPCD::Class(m_luaState->GetCState(),
                fgScriptMT->getMetatableName(CMetatables::GFX_MODEL_RESOURCE_MT_ID),
                fgScriptMT->getMetatableName(CMetatables::RESOURCE_MT_ID))
            .ObjectDirect("getModelType", (gfx::CModelResource *)0, &gfx::CModelResource::getModelType)
            .ObjectDirect("getNumIndices", (gfx::CModelResource *)0, &gfx::CModelResource::getNumIndices)
            .ObjectDirect("getNumMaterials", (gfx::CModelResource *)0, &gfx::CModelResource::getNumMaterials)
            .ObjectDirect("getNumNormals", (gfx::CModelResource *)0, &gfx::CModelResource::getNumNormals)
            .ObjectDirect("getNumPolygons", (gfx::CModelResource *)0, &gfx::CModelResource::getNumPolygons)
            .ObjectDirect("getNumShapes", (gfx::CModelResource *)0, &gfx::CModelResource::getNumShapes)
            .ObjectDirect("getNumTriangles", (gfx::CModelResource *)0, &gfx::CModelResource::getNumTriangles)
            .ObjectDirect("getNumUVs", (gfx::CModelResource *)0, &gfx::CModelResource::getNumUVs)
            .ObjectDirect("getNumVertices", (gfx::CModelResource *)0, &gfx::CModelResource::getNumVertices)
            .ObjectDirect("isInterleaved", (gfx::CModelResource *)0, &gfx::CModelResource::isInterleaved)
            .ObjectDirect("isTextured", (gfx::CModelResource *)0, &gfx::CModelResource::isTextured)
            .ObjectDirect("isMultitextured", (gfx::CModelResource *)0, &gfx::CModelResource::isMultitextured)
            .ObjectDirect("hasMaterial", (gfx::CModelResource *)0, &gfx::CModelResource::hasMaterial)
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedResourceGCEvent);

    typedef void (gfx::CParticleEffect::*PE_void_4X_INT_IN)(const int, const int, const int, const int);
    typedef void (gfx::CParticleEffect::*PE_void_2X_FLOAT_IN)(const float, const float);
    typedef void (gfx::CParticleEffect::*PE_void_Vec4f_IN)(const Vector4f&);
    typedef void (gfx::CParticleEffect::*PE_void_Vec3f_IN)(const Vector3f&);
    typedef void (gfx::CParticleEffect::*PE_void_Vec2f_IN)(const Vector2f&);
    typedef void (gfx::CParticleEffect::*PE_void_Vec2i_IN)(const Vector2i&);
    typedef void (gfx::CParticleEffect::*PE_void_C_STR_IN)(const char*);

    //
    // Register Particle Effect Resource metatable
    //
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(CMetatables::PARTICLE_EFFECT_RESOURCE_MT_ID), fgScriptMT->getMetatableName(CMetatables::RESOURCE_MT_ID))
            .ObjectDirect("setMaxCount", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::setMaxCount)
            .ObjectDirect("getMaxCount", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::getMaxCount)
            .ObjectDirect("isAreaCheck", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::isAreaCheck)
            .ObjectDirect("isAreaSet", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::isAreaSet)
            .ObjectDirect("unsetParticleArea", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::unsetParticleArea)
            //.ObjectDirect("setParticleArea", (fgParticleEffect *)0, &fgParticleEffect::setParticleArea)
            .ObjectDirect("setAreaCheck", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::setAreaCheck)
            .ObjectDirect("setTextureXSize", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::setTextureXSize)
            .ObjectDirect("setTextureYSize", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::setTextureYSize)
            //.ObjectDirect("setTextureIDRange", (fgParticleEffect *)0, &fgParticleEffect::setTextureIDRange)
            .ObjectDirect("setParamsActive", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::setParamsActive)
            .ObjectDirect("setRandomVelocity", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::setRandomVelocity)
            .ObjectDirect("setLifeAsSize", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::setLifeAsSize)
            .ObjectDirect("setFacingVelocity", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::setFacingVelocity)
            .ObjectDirect("setRandomAngle", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::setRandomAngle)
            .ObjectDirect("setSpreadSpeed", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::setSpreadSpeed)
            .ObjectDirect("setStartSize",
                          (gfx::CParticleEffect *)0,
                          static_cast<PE_void_Vec3f_IN>(&gfx::CParticleEffect::setStartSize))

            .ObjectDirect("setEndSize",
                          (gfx::CParticleEffect *)0,
                          static_cast<PE_void_Vec3f_IN>(&gfx::CParticleEffect::setEndSize))

            .ObjectDirect("setLowLife", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::setLowLife)
            .ObjectDirect("setHighLife", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::setHighLife)

            .ObjectDirect("setLifeRange",
                          (gfx::CParticleEffect *)0,
                          static_cast<PE_void_Vec2f_IN>(&gfx::CParticleEffect::setLifeRange))

            .ObjectDirect("setLifeRange2f",
                          (gfx::CParticleEffect *)0,
                          static_cast<PE_void_2X_FLOAT_IN>(&gfx::CParticleEffect::setLifeRange))

            .ObjectDirect("setTTLRange",
                          (gfx::CParticleEffect *)0,
                          static_cast<PE_void_Vec2i_IN>(&gfx::CParticleEffect::setTTLRange))

            .ObjectDirect("setStartColor",
                          (gfx::CParticleEffect *)0,
                          static_cast<PE_void_Vec4f_IN>(&gfx::CParticleEffect::setStartColor))

            .ObjectDirect("setStartColor4i",
                          (gfx::CParticleEffect *)0,
                          static_cast<PE_void_4X_INT_IN>(&gfx::CParticleEffect::setStartColor))

            .ObjectDirect("setEndColor",
                          (gfx::CParticleEffect *)0,
                          static_cast<PE_void_Vec4f_IN>(&gfx::CParticleEffect::setEndColor))

            .ObjectDirect("setEndColor4i",
                          (gfx::CParticleEffect *)0,
                          static_cast<PE_void_4X_INT_IN>(&gfx::CParticleEffect::setEndColor))

            .ObjectDirect("setFadeSpeedRange",
                          (gfx::CParticleEffect *)0,
                          static_cast<PE_void_Vec2f_IN>(&gfx::CParticleEffect::setFadeSpeedRange))

            .ObjectDirect("setFadeSpeedRange2f",
                          (gfx::CParticleEffect *)0,
                          static_cast<PE_void_2X_FLOAT_IN>(&gfx::CParticleEffect::setFadeSpeedRange))

            .ObjectDirect("setTextureName",
                          (gfx::CParticleEffect *)0,
                          static_cast<PE_void_C_STR_IN>(&gfx::CParticleEffect::setTextureName))

            //.ObjectDirect("getFlags", (fgParticleEffect *)0, &fgParticleEffect::getFlags)
            //.ObjectDirect("getParticleArea", (fgParticleEffect *)0, &fgParticleEffect::getParticleArea)
            .ObjectDirect("getTextureName", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::getTextureNameStr)
            .ObjectDirect("getTextureSheetSize", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::getTextureSheetSize)
            .ObjectDirect("getTextureIDRange", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::getTextureIDRange)
            .ObjectDirect("getStartSize", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::getStartSize)
            .ObjectDirect("getEndSize", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::getEndSize)
            .ObjectDirect("getSpreadSpeed", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::getSpreadSpeed)
            .ObjectDirect("getLifeRange", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::getLifeRange)
            .ObjectDirect("getTTLRange", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::getTTLRange)
            .ObjectDirect("getFadeSpeedRange", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::getFadeSpeedRange)
            .ObjectDirect("getStartColor", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::getStartColor)
            .ObjectDirect("getEndColor", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::getEndColor)
            .ObjectDirect("isParamsActive", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::isParamsActive)
            .ObjectDirect("isRandomVelocity", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::isRandomVelocity)
            .ObjectDirect("isLifeAsSize", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::isLifeAsSize)
            .ObjectDirect("isFacingVelocity", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::isFacingVelocity)
            .ObjectDirect("isRandomAngle", (gfx::CParticleEffect *)0, &gfx::CParticleEffect::isRandomAngle)
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedResourceGCEvent);

    //m_fgObj.Register("Texture", &fgScriptSubsystem::newResourceWrapper);

    //
    // Register Music (SFX) Resource metatable
    // AudioBase extends Resource (on the script level)
    // Music/Sound extends AudioBase
    //
    LPCD::Class(m_luaState->GetCState(),
                fgScriptMT->getMetatableName(CMetatables::AUDIO_BASE_RES_MT_ID),
                fgScriptMT->getMetatableName(CMetatables::RESOURCE_MT_ID))
            .ObjectDirect("play", (sfx::base::CAudio *)0, &sfx::base::CAudio::play)
            .ObjectDirect("pause", (sfx::base::CAudio *)0, &sfx::base::CAudio::pause)
            .ObjectDirect("resume", (sfx::base::CAudio *)0, &sfx::base::CAudio::resume)
            .ObjectDirect("rewind", (sfx::base::CAudio *)0, &sfx::base::CAudio::rewind)
            .ObjectDirect("stop", (sfx::base::CAudio *)0, &sfx::base::CAudio::stop)
            .ObjectDirect("halt", (sfx::base::CAudio *)0, &sfx::base::CAudio::halt)
            .ObjectDirect("isPaused", (sfx::base::CAudio *)0, &sfx::base::CAudio::isPaused)
            .ObjectDirect("setVolume", (sfx::base::CAudio *)0, &sfx::base::CAudio::setVolume)
            .ObjectDirect("getVolume", (sfx::base::CAudio *)0, &sfx::base::CAudio::getVolume);

    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(CMetatables::MUSIC_RESOURCE_MT_ID), fgScriptMT->getMetatableName(CMetatables::AUDIO_BASE_RES_MT_ID))
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedResourceGCEvent);

    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(CMetatables::SOUND_RESOURCE_MT_ID), fgScriptMT->getMetatableName(CMetatables::AUDIO_BASE_RES_MT_ID))
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedResourceGCEvent);

#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool script::CScriptSubsystem::registerShaderManager(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    if(!m_pShaderMgr)
        return FG_FALSE;
    if(m_pShaderMgr->getManagerType() != FG_MANAGER_GFX_SHADER)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    if(m_mgrMetatables[SHADER_MGR].GetRef() >= 0)
        return FG_TRUE;
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;

    typedef fgBool(gfx::CShaderManager::*SHADER_MGR_Bool_C_STR_IN)(const char*);
    typedef void(gfx::CShaderManager::*SHADER_MGR_void_C_STR_IN)(const char*);
    typedef gfx::CShaderProgram * (gfx::CShaderManager::*SHADER_MGR_ShaderProgram_C_STR_IN)(const char*);

    // GFX Shader Manager manager metatable
    m_mgrMetatables[SHADER_MGR] = m_fgObj.CreateTable(fgScriptMT->getMetatableName(CMetatables::SHADER_MANAGER_MT_ID));
    m_mgrMetatables[SHADER_MGR].SetObject("__index", m_mgrMetatables[SHADER_MGR]);
    m_mgrMetatables[SHADER_MGR].SetInteger("__meta_enum", (int)CMetatables::SHADER_MANAGER_MT_ID);
    m_mgrMetatables[SHADER_MGR].Register("isValid", &script::CScriptSubsystem::__isValid);

    m_mgrMetatables[SHADER_MGR].RegisterObjectDirect("compileShaders",
                                                     static_cast<gfx::CShaderManager *>(0),
                                                     &gfx::CShaderManager::compileShaders);

    m_mgrMetatables[SHADER_MGR].RegisterObjectDirect("linkShaders",
                                                     static_cast<gfx::CShaderManager *>(0),
                                                     &gfx::CShaderManager::linkShaders);

    m_mgrMetatables[SHADER_MGR].RegisterObjectDirect("allReleaseGFX",
                                                     static_cast<gfx::CShaderManager *>(0),
                                                     &gfx::CShaderManager::allReleaseGFX);

    m_mgrMetatables[SHADER_MGR].RegisterObjectDirect("isProgramUsed",
                                                     static_cast<gfx::CShaderManager *>(0),
                                                     static_cast<SHADER_MGR_Bool_C_STR_IN>(&gfx::CShaderManager::isProgramUsed));

    m_mgrMetatables[SHADER_MGR].RegisterObjectDirect("useProgram",
                                                     static_cast<gfx::CShaderManager *>(0),
                                                     static_cast<SHADER_MGR_Bool_C_STR_IN>(&gfx::CShaderManager::useProgram));

    m_mgrMetatables[SHADER_MGR].RegisterObjectDirect("setShadersPath",
                                                     static_cast<gfx::CShaderManager *>(0),
                                                     static_cast<SHADER_MGR_void_C_STR_IN>(&gfx::CShaderManager::setShadersPath));

    m_mgrMetatables[SHADER_MGR].RegisterObjectDirect("request",
                                                     static_cast<gfx::CShaderManager *>(0),
                                                     static_cast<SHADER_MGR_ShaderProgram_C_STR_IN>(&gfx::CShaderManager::request));

    m_mgrMetatables[SHADER_MGR].RegisterObjectDirect("isPreloadDone",
                                                     static_cast<gfx::CShaderManager *>(0),
                                                     &gfx::CShaderManager::isPreloadDone);

    intptr_t offset = (uintptr_t)m_pShaderMgr;
    UserDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        // This pointer is already registered ?
        return FG_FALSE;
    }
    LuaPlus::LuaObject shaderMgrObj = m_luaState->BoxPointer((void *)m_pShaderMgr);
    shaderMgrObj.SetMetatable(m_mgrMetatables[SHADER_MGR]);
    m_fgObj.SetObject("ShaderManager", shaderMgrObj);

    // Register ShaderProgram metatable
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(CMetatables::SHADER_PROGRAM_MT_ID))
            .ObjectDirect("getName", (gfx::CShaderProgram::base_type::base_type::base_type *)0, &gfx::CShaderProgram::base_type::base_type::base_type::getNameStr)
            .ObjectDirect("isManaged", (gfx::CShaderProgram::base_type::base_type::base_type *)0, &gfx::CShaderProgram::base_type::base_type::base_type::isManaged)
            .ObjectDirect("compile",
                          (gfx::CShaderProgram *)0,
                          &gfx::CShaderProgram::compile)
            .ObjectDirect("link",
                          (gfx::CShaderProgram *)0,
                          &gfx::CShaderProgram::compile)
            .ObjectDirect("use",
                          (gfx::CShaderProgram *)0,
                          &gfx::CShaderProgram::compile)
            .ObjectDirect("deleteProgram",
                          (gfx::CShaderProgram *)0,
                          &gfx::CShaderProgram::compile)
            .ObjectDirect("clearAll",
                          (gfx::CShaderProgram *)0,
                          &gfx::CShaderProgram::compile)
            .ObjectDirect("isUsed",
                          (gfx::CShaderProgram *)0,
                          &gfx::CShaderProgram::compile)
            .ObjectDirect("isLinked",
                          (gfx::CShaderProgram *)0,
                          &gfx::CShaderProgram::compile)
            .ObjectDirect("isCompiled",
                          (gfx::CShaderProgram *)0,
                          &gfx::CShaderProgram::compile)
            .Function("isValid", &script::CScriptSubsystem::__isValid);


#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}
//------------------------------------------------------------------------------

int script::CScriptSubsystem::addSceneEventCallbackWrapper(lua_State *L) {
#if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    LuaPlus::LuaStack args(state);
    const char* script = NULL;
    event::EventType eventType = event::INVALID;
    LuaPlus::LuaObject objFunction;
    fgBool hasFunction = FG_FALSE;
    int argc = 1;
    if(args.Count() == 0) {
        FG_LOG_DEBUG("Script: SceneEventWrapper: empty argument list");
        return 0;
    }
    if(args.Count() != 3 && args.Count() != 4) {
        FG_LOG_DEBUG("Script: SceneEventWrapper: wrong number of arguments");
        return 0;
    }
    if(args[1].GetType() != LUA_TUSERDATA) {
        FG_LOG_DEBUG("Script: SceneEventWrapper: first argument is not user data - should call with colon (:)");
        return 0;
    }
    gfx::CSceneManager *pSceneMgr = (gfx::CSceneManager *)state->UnBoxPointer(1);
    if(!pSceneMgr) {
        ///
        return 0;
    }
    uintptr_t offset = (uintptr_t)(void*)pSceneMgr;
    if(!m_userDataObjectMap[offset].isBound || !(pSceneMgr->getManagerType() == FG_MANAGER_SCENE)) {
        ///
        return 0;
    }

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
    FG_LOG_DEBUG("Script: addSceneEventCallbackWrapper: argc[%d]", args.Count());
    int id = 2;
    if(args[id].IsInteger()) {
        int iVal = args[id].GetInteger();
        eventType = (event::EventType)iVal;
        FG_LOG_DEBUG("Script: SceneEventWrapper: eventType[%d]", iVal);
    }
    id++;
    if(args[id].IsFunction()) {
        objFunction = args[id];
        hasFunction = FG_TRUE;
    } else if(args[id].IsString()) {
        script = args[id].GetString();
        FG_LOG_DEBUG("Script: SceneEventWrapper: 2nd argument is a string[%s]", script);
    }
    id++;
    if(args.Count() >= 3) {
        if(args[id].IsInteger()) {
            argc = abs(args[id].GetInteger());
            FG_LOG_DEBUG("Script: SceneEventWrapper: 3rd argument: argc[%d]", argc);
        }
    }

    if(eventType == event::INVALID) {
        FG_LOG_DEBUG("Script: SceneEventWrapper: event type is invalid");
        return 0;
    }
    if(!script && !hasFunction) {
        FG_LOG_DEBUG("Script: SceneEventWrapper: No script nor function specified");
        return 0;
    }
    fg::gfx::CSceneCallback *callback = NULL;
    if(script) {
        callback = new CScriptSceneCallback(L, script, 0);
    } else if(hasFunction) {
        callback = new CScriptSceneCallback(L, objFunction, argc);
    }
    if(pSceneMgr->addCallback(eventType, callback)) {
        FG_LOG_DEBUG("Script: Successfully added callback for scene event[%d]", eventType);
    } else {
        FG_LOG_DEBUG("Script: Failed to add callback for scene event[%d]", eventType);
    }
    // Can also return this pointer for future reference - so it is possible to remove
    // callback for given event type
#endif
    return 0;
}
//------------------------------------------------------------------------------

int script::CScriptSubsystem::addSceneTriggerCallbackWrapper(lua_State *L) {
#if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    LuaPlus::LuaStack args(state);
    const char* script = NULL, *triggerName = NULL;
    gfx::CSceneNodeTrigger::TriggerActivation activation = gfx::CSceneNodeTrigger::ON_COLLISION_BEGIN;
    LuaPlus::LuaObject objFunction;
    fgBool hasFunction = FG_FALSE;
    int argc = 1;
    if(args.Count() == 0) {
        FG_LOG_DEBUG("Script: SceneTriggerWrapper: empty argument list");
        return 0;
    }
    // ARGS: [1]SELF [2]ACTIVATION [3]TRIGGER_NAME [4]FUNCTION/SCRIPT [5] ARGC (optional)
    if(args.Count() != 4 && args.Count() != 5) {
        FG_LOG_DEBUG("Script: SceneTriggerWrapper: wrong number of arguments");
        return 0;
    }
    if(args[1].GetType() != LUA_TUSERDATA) {
        FG_LOG_DEBUG("Script: SceneTriggerWrapper: first argument is not user data - should call with colon (:)");
        return 0;
    }
    gfx::CSceneManager *pSceneMgr = (gfx::CSceneManager *)state->UnBoxPointer(1);
    if(!pSceneMgr) {
        ///
        return 0;
    }
    uintptr_t offset = (uintptr_t)(void*)pSceneMgr;
    if(!m_userDataObjectMap[offset].isBound || !(pSceneMgr->getManagerType() == FG_MANAGER_SCENE)) {
        ///
        return 0;
    }

    FG_LOG_DEBUG("Script: addSceneTriggerCallbackWrapper: argc[%d]", args.Count());
    int id = 2; // activation
    if(args[id].IsInteger()) {
        int iVal = args[id].GetInteger();
        activation = (gfx::CSceneNodeTrigger::TriggerActivation)iVal;
        if(iVal > 1)
            activation = gfx::CSceneNodeTrigger::ON_COLLISION_END;
        FG_LOG_DEBUG("Script: SceneTriggerWrapper: activation[%d]", (int)activation);
    }
    id++; // 3 // trigger name
    if(args[id].IsString()) {
        triggerName = args[id].GetString();
        FG_LOG_DEBUG("Script: SceneTriggerWrapper: 3rd argument is a string[%s]", triggerName);
    }
    id++; // 4 // function (lua) or script string
    if(args[id].IsFunction()) {
        objFunction = args[id];
        hasFunction = FG_TRUE;
        FG_LOG_DEBUG("Script: SceneTriggerWrapper: 4th argument is a function ptr");
    } else if(args[id].IsString()) {
        script = args[id].GetString();
        FG_LOG_DEBUG("Script: SceneTriggerWrapper: 4th argument is a string[%s]", script);
    }
    id++; // 5 -- optional - argc - 2 means function wants (nodeA, nodeB), 1 means (event)
    if(args.Count() == 5) {
        if(args[id].IsInteger()) {
            argc = abs(args[id].GetInteger());
            FG_LOG_DEBUG("Script: SceneTriggerWrapper: 5th argument: argc[%d]", argc);
        }
    }

    if(!script && !hasFunction) {
        FG_LOG_DEBUG("Script: SceneTriggerWrapper: No script nor function specified");
        return 0;
    }
    fg::gfx::CSceneCallback *callback = NULL;
    if(script) {
        callback = new CScriptSceneCallback(L, script, 0);
    } else if(hasFunction) {
        callback = new CScriptSceneCallback(L, objFunction, argc);
    }
    if(pSceneMgr->addTriggerCallback(activation, triggerName, callback)) {
        FG_LOG_DEBUG("Script: Successfully added callback for trigger[%s] activation[%d]", triggerName, activation);
    } else {
        FG_LOG_DEBUG("Script: Failed to add callback for trigger[%s] activation[%d]", triggerName, activation);
        delete callback;
        callback = NULL;
    }
    // Can also return this pointer for future reference - so it is possible to remove
    // callback for given event type
#endif
    return 0;
}
//------------------------------------------------------------------------------

#if defined(FG_USING_LUA_PLUS)

fgBool script::CScriptSubsystem::registerSceneManager(LuaPlus::LuaObject &metatable,
                                                      const unsigned short int metatableID,
                                                      fg::base::CManager *sceneManager,
                                                      const char* objectName) {
    if(m_isBindingComplete) {
        return FG_TRUE;
    }
    if(!sceneManager) {
        return FG_FALSE;
    }
    // Scene manager (2D or 3D) metatable
    metatable = m_fgObj.CreateTable(fgScriptMT->getMetatableName(metatableID));
    metatable.SetObject("__index", metatable);
    metatable.SetInteger("__meta_enum", (int)metatableID);
    metatable.Register("isValid", &script::CScriptSubsystem::__isValid);

    typedef gfx::CSceneNode * (gfx::CSceneManager::*SCENE_BASE_SceneNode_C_STR_IN)(const char*);
    typedef gfx::CSceneNode * (gfx::CSceneManager::*SCENE_BASE_SceneNode_C_STR_C_STR_IN)(const char*, const char*);
    typedef fgBool(gfx::CSceneManager::*SCENE_BASE_Bool_C_STR_IN)(const char*);
    typedef void(gfx::CSceneManager::*SCENE_BASE_void_2X_INT_IN)(int, int);

    typedef gfx::CSceneNode * (gfx::CSceneManager::*SCENE_BASE_SceneNode_C_STR_3X_FLOAT_IN)(const char*, float, float, float);
    typedef gfx::CSceneNode * (gfx::CSceneManager::*SCENE_BASE_SceneNode_C_STR_6X_FLOAT_IN)(const char*, float, float, float, float, float, float);

    metatable.RegisterObjectDirect("get",
                                   static_cast<gfx::CSceneManager *>(0),
                                   static_cast<SCENE_BASE_SceneNode_C_STR_IN>(&gfx::CSceneManager::get));

    metatable.RegisterObjectDirect("isManaged",
                                   static_cast<gfx::CSceneManager *>(0),
                                   static_cast<SCENE_BASE_Bool_C_STR_IN>(&gfx::CSceneManager::isManaged));

    metatable.RegisterObjectDirect("setLinearTraverse",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::setLinearTraverse);
    metatable.RegisterObjectDirect("isLinearTraverse",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::isLinearTraverse);
    metatable.RegisterObjectDirect("setIgnoreCollisions",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::setIgnoreCollisions);
    metatable.RegisterObjectDirect("isIgnoreCollisions",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::isIgnoreCollisions);
    metatable.RegisterObjectDirect("setHideNodes",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::setHideNodes);
    metatable.RegisterObjectDirect("isHideNodes",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::isHideNodes);
    metatable.RegisterObjectDirect("setHideSkyBox",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::setHideSkyBox);
    metatable.RegisterObjectDirect("isHideSkyBox",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::isHideSkyBox);
    metatable.RegisterObjectDirect("setHideShadows",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::setHideShadows);
    metatable.RegisterObjectDirect("isHideShadows",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::isHideShadows);
    metatable.RegisterObjectDirect("setHideAll",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::setHideAll);
    metatable.RegisterObjectDirect("isHideAll",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::isHideAll);
    metatable.RegisterObjectDirect("setFrustumCheck",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::setFrustumCheck);
    metatable.RegisterObjectDirect("isFrustumCheck",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::isFrustumCheck);
    metatable.RegisterObjectDirect("setFrustumCheckSphere",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::setFrustumCheckSphere);
    metatable.RegisterObjectDirect("isFrustumCheckSphere",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::isFrustumCheckSphere);
    metatable.RegisterObjectDirect("setOcclusionCheck",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::setOcclusionCheck);
    metatable.RegisterObjectDirect("isOcclusionCheck",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::isOcclusionCheck);


    metatable.RegisterObjectDirect("setPickSelectionOnClick",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::setPickSelectionOnClick);

    metatable.RegisterObjectDirect("isPickSelectionOnClick",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::isPickSelectionOnClick);

    metatable.RegisterObjectDirect("setPickSelectionOnHover",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::setPickSelectionOnHover);

    metatable.RegisterObjectDirect("isPickSelectionOnHover",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::isPickSelectionOnHover);

    metatable.RegisterObjectDirect("setPickSelectionAABBTriangles",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::setPickSelectionAABBTriangles);

    metatable.RegisterObjectDirect("isPickSelectionAABBTriangles",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::isPickSelectionAABBTriangles);

    metatable.RegisterObjectDirect("setPickSelectionGroup",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::setPickSelectionGroup);

    metatable.RegisterObjectDirect("isPickSelectionGroup",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::isPickSelectionGroup);

    metatable.RegisterObjectDirect("setPickSelectionToggle",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::setPickSelectionToggle);

    metatable.RegisterObjectDirect("isPickSelectionToggle",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::isPickSelectionToggle);

    metatable.RegisterObjectDirect("setPickSelectionBox",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::setPickSelectionBox);

    metatable.RegisterObjectDirect("isPickSelectionBox",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::isPickSelectionBox);


    metatable.RegisterObjectDirect("setShowGroundGrid",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::setShowGroundGrid);

    metatable.RegisterObjectDirect("isShowGroundGrid",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::isShowGroundGrid);


    metatable.RegisterObjectDirect("reportSelectionMove",
                                   static_cast<gfx::CSceneManager *>(0),
                                   static_cast<SCENE_BASE_void_2X_INT_IN>(&gfx::CSceneManager::reportSelectionMove));

    metatable.RegisterObjectDirect("reportSelectionClick",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::reportSelectionClick);

    metatable.RegisterObjectDirect("reportSelectionUnclick",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::reportSelectionUnclick);


    metatable.RegisterObjectDirect("destroyNode",
                                   static_cast<gfx::CSceneManager *>(0),
                                   static_cast<SCENE_BASE_Bool_C_STR_IN>(&gfx::CSceneManager::destroyNode));

    metatable.RegisterObjectDirect("addTrigger",
                                   static_cast<gfx::CSceneManager *>(0),
                                   static_cast<SCENE_BASE_SceneNode_C_STR_3X_FLOAT_IN>(&gfx::CSceneManager::addTrigger));

    metatable.RegisterObjectDirect("addTriggerWithExtent",
                                   static_cast<gfx::CSceneManager *>(0),
                                   static_cast<SCENE_BASE_SceneNode_C_STR_6X_FLOAT_IN>(&gfx::CSceneManager::addTrigger));

    metatable.RegisterObjectDirect("addDuplicate",
                                   static_cast<gfx::CSceneManager *>(0),
                                   static_cast<SCENE_BASE_SceneNode_C_STR_C_STR_IN>(&gfx::CSceneManager::addDuplicate));

    metatable.RegisterObjectDirect("addFromModel",
                                   static_cast<gfx::CSceneManager *>(0),
                                   static_cast<SCENE_BASE_SceneNode_C_STR_C_STR_IN>(&gfx::CSceneManager::addFromModel));

    metatable.RegisterObjectDirect("count",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::count);

    metatable.RegisterObjectDirect("size",
                                   static_cast<gfx::CSceneManager *>(0),
                                   &gfx::CSceneManager::size);

    metatable.Register("addEventCallback", &addSceneEventCallbackWrapper);

    metatable.Register("addTriggerCallback", &addSceneTriggerCallbackWrapper);

    //m_mgrMetatables[RESOURCE_MGR].Register("request", &fgScriptSubsystem::newResourceWrapper);

    uintptr_t offset = (uintptr_t)sceneManager;
    UserDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        return FG_FALSE;
    }
    // Create Lua object for scene manager global
    LuaPlus::LuaObject sceneManagerObj = m_luaState->BoxPointer((void *)sceneManager);
    sceneManagerObj.SetMetatable(metatable);
    m_fgObj.SetObject(objectName, sceneManagerObj);
    m_userDataObjectMap[offset].obj = sceneManagerObj;
    m_userDataObjectMap[offset].isBound = FG_TRUE;

    return FG_TRUE;
}
#else
#endif /* FG_USING_LUA_PLUS */
//------------------------------------------------------------------------------

fgBool script::CScriptSubsystem::register2DSceneManager(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    if(!m_p2DSceneMgr)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    if(m_mgrMetatables[SCENE2D_MGR].GetRef() >= 0)
        return FG_TRUE;
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;

    if(!registerSceneManager(m_mgrMetatables[SCENE2D_MGR],
                             CMetatables::SCENE2D_MANAGER_MT_ID,
                             m_p2DSceneMgr, "Scene2D")) {
        FG_LOG_ERROR("Script: Unable to register common metatable for 2D Scene Manager");
        return FG_FALSE;
    }

#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool script::CScriptSubsystem::register3DSceneManager(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    if(!m_p3DSceneMgr)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    if(m_mgrMetatables[SCENE3D_MGR].GetRef() >= 0)
        return FG_TRUE;
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;

    if(!registerSceneManager(m_mgrMetatables[SCENE3D_MGR],
                             CMetatables::SCENE3D_MANAGER_MT_ID,
                             m_p3DSceneMgr,
                             "Scene3D")) {
        FG_LOG_ERROR("Script: Unable to register common metatable for 3D Scene Manager");
        return FG_FALSE;
    }

    // Register additional direct functions for 3D Scene Manager - they're specific for this class/object
    typedef gfx::CSceneNode * (gfx::CScene3D::*SCENE3D_SceneNode_C_STR_C_STR_IN)(const char*, const char*);
    typedef gfx::CSceneNode * (gfx::CScene3D::*SCENE3D_SceneNode_C_STR_IN)(const char*);
    typedef fgBool(gfx::CScene3D::*SCENE3D_Bool_C_STR_IN)(const char*);

    //m_mgrMetatables[SCENE3D_MGR].RegisterObjectDirect("addFromModel",
    //                                                  static_cast<gfx::CScene3D *>(0),
    //                                                  static_cast<SCENE3D_SceneNode_C_STR_C_STR_IN>(&gfx::CScene3D::addFromModel));

    ////////////////////////////////////////////////////////////////////////////
    //
    // Registering now metatables for various 3D/2D Scene types
    // Registration here for this types needs to be done once - it will be used
    // globally for 2D and 3D scene manipulations
    //

    typedef Vector3f & (gfx::CSceneNode::*SCENENODE_Vec3fref_void)(void);
    typedef Vector4f & (gfx::CSceneNode::*SCENENODE_Vec4fref_void)(void);
    typedef Vector3f(gfx::CSceneNode::*SCENENODE_Vec3f_void_const)(void)const;
    typedef void (gfx::CSceneNode::*SCENENODE_void_float_3X)(float, float, float);
    typedef void (gfx::CSceneNode::*SCENENODE_void_float_4X)(float, float, float, float);
    typedef fgBool(gfx::CSceneNode::*SCENENODE_Bool_C_STR_UINT_IN)(const char*, unsigned int);

    typedef Vector3f & (gfx::CSceneNode::*FUNC_getScale)(void);
    typedef void (gfx::CSceneNode::*FUNC_setScale)(float, float, float);

    const char* metatableSceneNodeName = fgScriptMT->getMetatableName(CMetatables::SCENE_NODE_MT_ID);
    const char* metatableSceneNodeObjectName = fgScriptMT->getMetatableName(CMetatables::SCENE_NODE_OBJECT_MT_ID);
    const char* metatableSceneNodeMeshName = fgScriptMT->getMetatableName(CMetatables::SCENE_NODE_MESH_MT_ID);
    const char* metatableSceneNodeTriggerName = fgScriptMT->getMetatableName(CMetatables::SCENE_NODE_TRIGGER_MT_ID);
    // Register Base GfxSceneNode metatable

    LPCD::Class(m_luaState->GetCState(), metatableSceneNodeName)
            .ObjectDirect("getName", (gfx::CSceneNode::base_type *)0, &gfx::CSceneNode::base_type::getNameStr)
            .ObjectDirect("isManaged", (gfx::CSceneNode::base_type *)0, &gfx::CSceneNode::base_type::isManaged)

            .ObjectDirect("update", (gfx::CSceneNode *)0, &gfx::CSceneNode::update)
            .ObjectDirect("setAnimation", (gfx::CSceneNode *)0, static_cast<SCENENODE_Bool_C_STR_UINT_IN>(&gfx::CSceneNode::setAnimation))

            .ObjectDirect("getPosition", (gfx::CSceneNode *)0, static_cast<SCENENODE_Vec4fref_void>(&gfx::CSceneNode::getPosition))
            .ObjectDirect("setPosition", (gfx::CSceneNode *)0, static_cast<SCENENODE_void_float_3X>(&gfx::CSceneNode::setPosition))

            .ObjectDirect("setRotation", (gfx::CSceneNode *)0, static_cast<SCENENODE_void_float_4X>(&gfx::CSceneNode::setRotation))
            //.ObjectDirect("getRotation", (gfx::CSceneNode *)0, static_cast<SCENENODE_Vec3f_void_const>(&gfx::CSceneNode::getRotation))
            //.ObjectDirect("setRotation", (gfx::CSceneNode *)0, static_cast<SCENENODE_void_float_3X>(&gfx::CSceneNode::setRotation))

            //.ObjectDirect("getVelocity", (gfx::CSceneNode *)0, static_cast<SCENENODE_Vec3f_void_const>(&gfx::CSceneNode::getVelocity))
            //.ObjectDirect("setVelocity", (gfx::CSceneNode *)0, static_cast<SCENENODE_void_float_3X>(&gfx::CSceneNode::setVelocity))

            //.ObjectDirect("getAcceleration", (gfx::CSceneNode *)0, static_cast<SCENENODE_Vec3f_void_const>(&gfx::CSceneNode::getAcceleration))
            //.ObjectDirect("setAcceleration", (gfx::CSceneNode *)0, static_cast<SCENENODE_void_float_3X>(&gfx::CSceneNode::setAcceleration))

            .ObjectDirect("translate", (gfx::CSceneNode *)0, static_cast<SCENENODE_void_float_3X>(&gfx::CSceneNode::translate))
            .ObjectDirect("translateMatrix", (gfx::CSceneNode *)0, static_cast<SCENENODE_void_float_3X>(&gfx::CSceneNode::translateMatrix))
            .ObjectDirect("rotate", (gfx::CSceneNode *)0, static_cast<SCENENODE_void_float_4X>(&gfx::CSceneNode::rotate))

            .ObjectDirect("setHalfSize", (gfx::CSceneNode *)0, static_cast<SCENENODE_void_float_3X>(&gfx::CSceneNode::setHalfSize))
            .ObjectDirect("setRadius", (gfx::CSceneNode *)0, &gfx::CSceneNode::setRadius)

            .ObjectDirect("isAutoScale", (gfx::CSceneNode *)0, &gfx::CSceneNode::isAutoScale)
            .ObjectDirect("setAutoScale", (gfx::CSceneNode *)0, &gfx::CSceneNode::setAutoScale)

            .ObjectDirect("getScale", (gfx::CSceneNode *)0,
                          static_cast<FUNC_getScale>(&gfx::CSceneNode::getScale))
            .ObjectDirect("setScale", (gfx::CSceneNode *)0,
                          static_cast<FUNC_setScale>(&gfx::CSceneNode::setScale))

            //.ObjectDirect("setMass", (gfx::CSceneNode *)0, &gfx::CSceneNode::setMass)
            //.ObjectDirect("getMass", (gfx::CSceneNode *)0, &gfx::CSceneNode::getMass)

            .ObjectDirect("isEmpty", (gfx::CSceneNode *)0, &gfx::CSceneNode::isEmpty)
            .ObjectDirect("hasChildren", (gfx::CSceneNode *)0, &gfx::CSceneNode::hasChildren)
            .ObjectDirect("getChildrenCount", (gfx::CSceneNode *)0, &gfx::CSceneNode::getChildrenCount)
            .ObjectDirect("getChildByIndex", (gfx::CSceneNode *)0, &gfx::CSceneNode::getChildByIndex)

            .ObjectDirect("isVisible", (gfx::CSceneNode *)0, &gfx::CSceneNode::isVisible)
            .ObjectDirect("setVisible", (gfx::CSceneNode *)0, &gfx::CSceneNode::setVisible)

            .ObjectDirect("isCollidable", (gfx::CSceneNode *)0, &gfx::CSceneNode::isCollidable)
            .ObjectDirect("setCollidable", (gfx::CSceneNode *)0, &gfx::CSceneNode::setCollidable)
#if 0
            .ObjectDirect("activateCollisionBody", (gfx::CSceneNode *)0, &gfx::CSceneNode::setCollisionBodyType)
            .ObjectDirect("removeCollisionBody", (gfx::CSceneNode *)0, &gfx::CSceneNode::removeCollisionBody)
            .ObjectDirect("setCollisionBodyType", (gfx::CSceneNode *)0, &gfx::CSceneNode::setCollisionBodyType)
#endif
            .Function("isValid", &script::CScriptSubsystem::__isValid)
            ;
    //.MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent); // #DELETE

    // Register GfxSceneNodeTrigger metatable (TRIGGER OBJECT)
    LPCD::Class(m_luaState->GetCState(), metatableSceneNodeTriggerName, metatableSceneNodeName)
            .ObjectDirect("numCallbacks", (gfx::CSceneNodeTrigger::triggerable_type*)0, &gfx::CSceneNodeTrigger::triggerable_type::getCallbacksCount)
            .ObjectDirect("hasCallbacks", (gfx::CSceneNodeTrigger::triggerable_type*)0, &gfx::CSceneNodeTrigger::triggerable_type::hasCallbacks)
            ;

    // Register GfxSceneNodeObject metatable
    LPCD::Class(m_luaState->GetCState(), metatableSceneNodeObjectName, metatableSceneNodeName)
            ;

    // Register GfxSceneNodeMesh metatable
    LPCD::Class(m_luaState->GetCState(), metatableSceneNodeMeshName, metatableSceneNodeName)
            ;

    ////////////////////////////////////////////////////////////////////////////
    // REGISTRATION OF SCENE MANAGER EVENT STRUCTURES

    // Event Base structure
    const char* metatableNameEventBase = fgScriptMT->getMetatableName(CMetatables::EVENT_BASE_MT_ID);

    // Scene Node Event : EventBase
    const char* metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_SCENE_NODE_MT_ID);
    const char* metatableNameSceneNode = metatableName;
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("node", &event::SSceneNode::pNodeA)
            .Property("nodeA", &event::SSceneNode::pNodeA)
            .Property("nodeB", &event::SSceneNode::pNodeB)
            ;
    // __gc ? nope

    // Scene Node Collision Event : Scene Node base event
    metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_SCENE_NODE_COLLISION_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameSceneNode)
            //.Property("which", &event::SControllerButton::which)
            ;
    // __gc ? nope

    // Scene Node Trigger : EventBase
    metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_SCENE_NODE_TRIGGER_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameEventBase)
            .Property("node", &event::SSceneNodeTrigger::pNodeTrigger)
            .Property("nodeA", &event::SSceneNodeTrigger::pNodeTrigger)
            .Property("nodeTrigger", &event::SSceneNodeTrigger::pNodeTrigger)
            .Property("nodeB", &event::SSceneNodeTrigger::pNodeB)
            ;
    // __gc ? nope

    // Scene Event Main Union structure
    metatableName = fgScriptMT->getMetatableName(CMetatables::EVENT_SCENE_MAIN_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName)
            .Property("eventType", &event::SSceneEvent::code)
            .Property("code", &event::SSceneEvent::code)
            .Property("node", &event::SSceneEvent::node)
            .Property("collision", &event::SSceneEvent::collision)
            .Property("trigger", &event::SSceneEvent::trigger)
            ;
    // __gc ? nope

    ////////////////////////////////////////////////////////////////////////////

#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool script::CScriptSubsystem::registerPhysics(void) {
    if(m_isBindingComplete)
        return FG_TRUE;

#if defined(FG_USING_LUA_PLUS)

    const char* metatableCollisionBodyName =
            fgScriptMT->getMetatableName(CMetatables::COLLISION_BODY_MT_ID);

    typedef void (physics::CCollisionBody::*FUNC_setHalfSize)(float, float, float);
    typedef void (physics::CCollisionBody::*FUNC_setLocalScaling)(float, float, float);
    typedef void (physics::CCollisionBody::*FUNC_activate)(bool) const;
    typedef void (physics::CCollisionBody::*FUNC_setRotation)(float, float, float, float);

    typedef physics::BodyType(physics::CCollisionBody::*FUNC_getBodyType)(void)const;
    typedef void (physics::CCollisionBody::*FUNC_setHalfSizeAndMass)(float, float, float, float);

    // Register physics::CCollisionBody
    LPCD::Class(m_luaState->GetCState(), metatableCollisionBodyName)
            .ObjectDirect("getBodyType",
                          (physics::CCollisionBody*)0,
                          static_cast<FUNC_getBodyType>
                          (&physics::CCollisionBody::getBodyType))
            .ObjectDirect("setHalfSize",
                          (physics::CCollisionBody*)0,
                          static_cast<FUNC_setHalfSize>
                          (&physics::CCollisionBody::setHalfSize))
            .ObjectDirect("setHalfSizeAndMass",
                          (physics::CCollisionBody*)0,
                          static_cast<FUNC_setHalfSizeAndMass>
                          (&physics::CCollisionBody::setHalfSizeAndMass))
            .ObjectDirect("setRadius",
                          (physics::CCollisionBody*)0,
                          &physics::CCollisionBody::setRadius)
            .ObjectDirect("setHeight",
                          (physics::CCollisionBody*)0,
                          &physics::CCollisionBody::setHeight)
            .ObjectDirect("setMass",
                          (physics::CCollisionBody*)0,
                          &physics::CCollisionBody::setMass)
            .ObjectDirect("setRotation",
                          (physics::CCollisionBody*)0,
                          static_cast<FUNC_setRotation>
                          (&physics::CCollisionBody::setRotation))
            .ObjectDirect("setLocalScaling",
                          (physics::CCollisionBody*)0,
                          static_cast<FUNC_setLocalScaling>
                          (&physics::CCollisionBody::setLocalScaling))
            .ObjectDirect("activate",
                          (physics::CCollisionBody*)0,
                          static_cast<FUNC_activate>
                          (&physics::CCollisionBody::activate))
            .Function("isValid", &script::CScriptSubsystem::__isValid);
    ;
#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool script::CScriptSubsystem::registerGameEntities(void) {
    if(m_isBindingComplete)
        return FG_TRUE;

#if defined(FG_USING_LUA_PLUS)
    const char* metatableSceneNodeName = fgScriptMT->getMetatableName(CMetatables::SCENE_NODE_MT_ID);
    const char* metatableSceneNodeObjectName = fgScriptMT->getMetatableName(CMetatables::SCENE_NODE_OBJECT_MT_ID);
    const char* metatableSceneNodeMeshName = fgScriptMT->getMetatableName(CMetatables::SCENE_NODE_MESH_MT_ID);
    const char* metatableGameEntityName = fgScriptMT->getMetatableName(CMetatables::GAME_ENTITY_MT_ID);
    const char* metatableGameEntityMeshName = fgScriptMT->getMetatableName(CMetatables::GAME_ENTITY_MESH_MT_ID);

    // Register game::CEntity metatable
    LPCD::Class(m_luaState->GetCState(), metatableGameEntityName, metatableSceneNodeObjectName)
            ;

    // need to statically cast function pointers to be called from CEntityMesh pointer type
    // even if they belong to secondary base class (in this case physics::traits::CPhysical)
    // it is because most functions return CSceneNode as pointer and from this level it's
    // impossible to call functions of physical traits class.
    // game::CEntityMesh extends CSceneNodeMesh and physical traits, it's quite problematic.
    // Another reason for such hax is that Lua does not support something like type casting.
    // Need to add functions for checking specific type of the object and
    // up-casting it manually if needed - up-casting in this case means changing the
    // metatable of the given Lua side object.
    typedef physics::CCollisionBody * (game::CEntityMesh::*FUNC_getCollisionBody)(void);
    typedef fgBool(game::CEntityMesh::*FUNC_hasCollisionBody)(void)const;
    typedef physics::BodyType(game::CEntityMesh::*FUNC_getBodyType)(void)const;
    // Register game::CEntityMesh metatable
    LPCD::Class(m_luaState->GetCState(), metatableGameEntityMeshName, metatableSceneNodeMeshName)
            .ObjectDirect("hasCollisionBody",
                          (game::CEntityMesh *)0,
                          static_cast<FUNC_hasCollisionBody>
                          (&game::CEntityMesh::hasCollisionBody))
            .ObjectDirect("getBodyType",
                          (game::CEntityMesh*)0,
                          static_cast<FUNC_getBodyType>
                          (&game::CEntityMesh::getBodyType))
            .ObjectDirect("getCollisionBody",
                          (game::CEntityMesh*)0,
                          static_cast<FUNC_getCollisionBody>
                          (&game::CEntityMesh::getCollisionBody))
            ;

#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool script::CScriptSubsystem::registerParticleSystem(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    if(!m_pParticleMgr)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    if(m_mgrMetatables[PARTICLE_MGR].GetRef() >= 0)
        return FG_TRUE;
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;

    typedef void (gfx::CParticleSystem::*PS_void_C_STR__uint_float_3X_IN)(const char*, unsigned int, float, float, float);

    // Particle system/manager metatable
    m_mgrMetatables[PARTICLE_MGR] = m_fgObj.CreateTable(fgScriptMT->getMetatableName(CMetatables::PARTICLE_SYSTEM_MT_ID));
    m_mgrMetatables[PARTICLE_MGR].SetObject("__index", m_mgrMetatables[PARTICLE_MGR]);
    m_mgrMetatables[PARTICLE_MGR].SetInteger("__meta_enum", (int)CMetatables::PARTICLE_SYSTEM_MT_ID);
    m_mgrMetatables[PARTICLE_MGR].Register("isValid", &script::CScriptSubsystem::__isValid);

    m_mgrMetatables[PARTICLE_MGR].
            RegisterObjectDirect("addParticles",
                                 (gfx::CParticleSystem *)0,
                                 static_cast<PS_void_C_STR__uint_float_3X_IN>(&gfx::CParticleSystem::addParticles));


    //m_metatableParticleMgr.Register("request", &fgScriptSubsystem::newResourceWrapper);

    uintptr_t offset = (uintptr_t)m_pParticleMgr;
    UserDataObjectMapItor it = m_userDataObjectMap.find(offset);
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
//------------------------------------------------------------------------------

int script::CScriptSubsystem::addWidgetCallbackWrapper(lua_State *L) {
#if defined(FG_USING_LUA_PLUS)
    LuaPlus::LuaState* state = lua_State_to_LuaState(L);
    LuaPlus::LuaStack args(state);
    const char* script = NULL;
    unsigned int callbackType = FG_GUI_WIDGET_CALLBACK_INVALID;
    LuaPlus::LuaObject objFunction;
    fgBool hasFunction = FG_FALSE;
    const char*widgetName = NULL;
    gui::CWidget *pWidget = NULL;
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
            pWidget = (gui::CWidget *)unboxed;
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
            const char*ctype = args[id].GetString();
            if(strings::isEqual(ctype, "onFocus", FG_FALSE)) {
                callbackType = FG_GUI_WIDGET_CALLBACK_ON_FOCUS;

            } else if(strings::isEqual(ctype, "onFocusLost", FG_FALSE)) {
                callbackType = FG_GUI_WIDGET_CALLBACK_ON_FOCUS_LOST;

            } else if(strings::isEqual(ctype, "onClick", FG_FALSE)) {
                callbackType = FG_GUI_WIDGET_CALLBACK_ON_CLICK;

            } else if(strings::isEqual(ctype, "onActivate", FG_FALSE)) {
                callbackType = FG_GUI_WIDGET_CALLBACK_ON_ACTIVATE;

            } else if(strings::isEqual(ctype, "onDeactivate", FG_FALSE)) {
                callbackType = FG_GUI_WIDGET_CALLBACK_ON_DEACTIVATE;

            } else if(strings::isEqual(ctype, "onKey", FG_FALSE)) {
                callbackType = FG_GUI_WIDGET_CALLBACK_ON_KEY;

            } else if(strings::isEqual(ctype, "onMouse", FG_FALSE)) {
                callbackType = FG_GUI_WIDGET_CALLBACK_ON_MOUSE;

            } else if(strings::isEqual(ctype, "onChangeState", FG_FALSE)) {
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
    gui::CGuiCallback *callback = NULL;
    if(script) {
        callback = new CScriptGuiCallback(static_cast<gui::CGuiMain *>(m_pGuiMain), L, script, argc);
    } else if(hasFunction) {
        callback = new CScriptGuiCallback(static_cast<gui::CGuiMain *>(m_pGuiMain), L, objFunction, argc);
    }
    fgBool status = FG_FALSE;
    if(pWidget)
        status = static_cast<gui::CGuiMain *>(m_pGuiMain)->addWidgetCallback(pWidget, callback, callbackType);
    else if(widgetName)
        status = static_cast<gui::CGuiMain *>(m_pGuiMain)->addWidgetCallback(widgetName, callback, callbackType);
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
//------------------------------------------------------------------------------

fgBool script::CScriptSubsystem::registerGuiMain(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    if(!m_pGuiMain)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    if(m_mgrMetatables[GUI_MAIN].GetRef() >= 0)
        return FG_TRUE;
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;

    typedef void(gui::CGuiMain::*GM_void_C_STR_IN)(const char*);
    typedef void(gui::CGuiMain::*GM_void_C_STR_Bool_IN)(const char*, fgBool);

    // Gui main/manager metatable
    m_mgrMetatables[GUI_MAIN] = m_fgObj.CreateTable(fgScriptMT->getMetatableName(CMetatables::GUI_MAIN_MT_ID));
    m_mgrMetatables[GUI_MAIN].SetObject("__index", m_mgrMetatables[GUI_MAIN]);
    m_mgrMetatables[GUI_MAIN].SetInteger("__meta_enum", (int)CMetatables::GUI_MAIN_MT_ID);
    m_mgrMetatables[GUI_MAIN].Register("isValid", &script::CScriptSubsystem::__isValid);
    m_mgrMetatables[GUI_MAIN].RegisterObjectDirect("changeMenu",
                                                   (gui::CGuiMain *)0,
                                                   static_cast<GM_void_C_STR_IN>(&gui::CGuiMain::changeMenu));
    m_mgrMetatables[GUI_MAIN].RegisterObjectDirect("setCurrentMenu",
                                                   (gui::CGuiMain *)0,
                                                   static_cast<GM_void_C_STR_Bool_IN>(&gui::CGuiMain::setCurrentMenu));
    m_mgrMetatables[GUI_MAIN].Register("addWidgetCallback", &script::CScriptSubsystem::addWidgetCallbackWrapper);

    uintptr_t offset = (uintptr_t)m_pGuiMain;
    UserDataObjectMapItor it = m_userDataObjectMap.find(offset);
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
//------------------------------------------------------------------------------

fgBool script::CScriptSubsystem::registerWidgetManager(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    if(!m_pWidgetMgr)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    if(m_mgrMetatables[WIDGET_MGR].GetRef() >= 0)
        return FG_TRUE;
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;

    typedef fgBool(gui::CWidgetManager::*GWM_Bool_Widget_IN)(gui::CWidget *);
    typedef fgBool(gui::CWidgetManager::*GWM_Bool_Widget_Widget_IN)(gui::CWidget *, gui::CWidget *);
    typedef fgBool(gui::CWidgetManager::*GWM_Bool_C_STR_IN)(const char*);
    typedef gui::CWidget * (gui::CWidgetManager::*GWM_Widget_C_STR_IN)(const char*);

    // Widget manager metatable
    m_mgrMetatables[WIDGET_MGR] = m_fgObj.CreateTable(fgScriptMT->getMetatableName(CMetatables::WIDGET_MANAGER_MT_ID));
    m_mgrMetatables[WIDGET_MGR].SetObject("__index", m_mgrMetatables[WIDGET_MGR]);
    m_mgrMetatables[WIDGET_MGR].SetInteger("__meta_enum", (int)CMetatables::WIDGET_MANAGER_MT_ID);
    m_mgrMetatables[WIDGET_MGR].Register("isValid", &script::CScriptSubsystem::__isValid);
    m_mgrMetatables[WIDGET_MGR].RegisterObjectDirect("addWidget",
                                                     (gui::CWidgetManager *)0,
                                                     static_cast<GWM_Bool_Widget_IN>(&gui::CWidgetManager::addWidget));

    m_mgrMetatables[WIDGET_MGR].RegisterObjectDirect("addWidgetWithFather",
                                                     (gui::CWidgetManager *)0,
                                                     static_cast<GWM_Bool_Widget_Widget_IN>(&gui::CWidgetManager::addWidget));

    m_mgrMetatables[WIDGET_MGR].RegisterObjectDirect("removeWidget",
                                                     (gui::CWidgetManager *)0,
                                                     static_cast<GWM_Bool_Widget_IN>(&gui::CWidgetManager::remove));

    m_mgrMetatables[WIDGET_MGR].RegisterObjectDirect("removeWidgetByName",
                                                     (gui::CWidgetManager *)0,
                                                     static_cast<GWM_Bool_C_STR_IN>(&gui::CWidgetManager::remove));

    m_mgrMetatables[WIDGET_MGR].RegisterObjectDirect("getWidget",
                                                     (gui::CWidgetManager *)0,
                                                     static_cast<GWM_Widget_C_STR_IN>(&gui::CWidgetManager::get));
    //m_mgrMetatables[WIDGET_MGR].
    //m_metatableWidgetMgr.Register("request", &fgScriptSubsystem::newResourceWrapper);

    uintptr_t offset = (uintptr_t)m_pWidgetMgr;
    UserDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        return FG_FALSE;
    }
    // Create lua object for particle system/manager global
    LuaPlus::LuaObject widgetMgrObj = m_luaState->BoxPointer((void *)m_pWidgetMgr);
    widgetMgrObj.SetMetatable(m_mgrMetatables[WIDGET_MGR]);
    m_fgObj.SetObject("WidgetManager", widgetMgrObj);
    m_userDataObjectMap[offset].obj = widgetMgrObj;
    m_userDataObjectMap[offset].isBound = FG_TRUE;


    typedef void (gui::CWidget::*GW_void_C_STR_IN)(const char*);
    typedef void (gui::CWidget::base_type::*GW_BASE_void_C_STR_IN)(const char*);
    typedef gui::CWidget * (gui::CWidget::*GW_Widget_void)(void)const;

    const char* metatableNameWidget = fgScriptMT->getMetatableName(CMetatables::GUI_WIDGET_MT_ID);
    const char* metatableName = NULL;
    // Register Base Widget metatable
    LPCD::Class(m_luaState->GetCState(), metatableNameWidget)
            .ObjectDirect("getName", (gui::CWidget::base_type *)0, &gui::CWidget::base_type::getNameStr)
            .ObjectDirect("setName",
                          (gui::CWidget::base_type *)0,
                          static_cast<GW_BASE_void_C_STR_IN>(&gui::CWidget::base_type::setName))

            .ObjectDirect("isManaged",
                          (gui::CWidget::base_type *)0,
                          &gui::CWidget::base_type::isManaged)

            .ObjectDirect("setFlags",
                          (gui::CWidget *)0,
                          static_cast<GW_void_C_STR_IN>(&gui::CWidget::setFlags))

            .ObjectDirect("refresh", (gui::CWidget *)0, &gui::CWidget::refresh)
            //.ObjectDirect("updateState", (gui::CWidget *)0, &fgGuiWidget::updateState)
            .ObjectDirect("getFather",
                          (gui::CWidget *)0,
                          static_cast<GW_Widget_void>(&gui::CWidget::getFather))
            .ObjectDirect("getType", (gui::CWidget *)0, &gui::CWidget::getType)
            .ObjectDirect("getTypeTraits", (gui::CWidget *)0, &gui::CWidget::getTypeTraits)
            .ObjectDirect("getTypeName", (gui::CWidget *)0, &gui::CWidget::getTypeNameStr)
            .ObjectDirect("setVisible", (gui::CWidget *)0, &gui::CWidget::setVisible)
            .ObjectDirect("isVisible", (gui::CWidget *)0, &gui::CWidget::isVisible)
            .ObjectDirect("setActive", (gui::CWidget *)0, &gui::CWidget::setActive)
            .ObjectDirect("isActive", (gui::CWidget *)0, &gui::CWidget::isActive)
            .ObjectDirect("setIgnoreState", (gui::CWidget *)0, &gui::CWidget::setIgnoreState)
            .ObjectDirect("isIgnoreState", (gui::CWidget *)0, &gui::CWidget::isIgnoreState)
            //.ObjectDirect("doesIgnoreState", (gui::CWidget *)0, &fgGuiWidget::doesIgnoreState)
            .ObjectDirect("getState", (gui::CWidget *)0, &gui::CWidget::getState)
            .ObjectDirect("setPosition", (gui::CWidget *)0, &gui::CWidget::setPosition)
            .ObjectDirect("getPosition", (gui::CWidget *)0, &gui::CWidget::getPosition)
            .ObjectDirect("getRelativePos", (gui::CWidget *)0, &gui::CWidget::getRelativePos)
            .ObjectDirect("setRelativePos", (gui::CWidget *)0, &gui::CWidget::setRelativePos)
            .ObjectDirect("setSize", (gui::CWidget *)0, &gui::CWidget::setSize)
            .ObjectDirect("getSize", (gui::CWidget *)0, &gui::CWidget::getSize)
            .ObjectDirect("getLink", (gui::CWidget *)0, &gui::CWidget::getLinkStr)
            .ObjectDirect("getScript", (gui::CWidget *)0, &gui::CWidget::getScriptStr)
            .ObjectDirect("getAction", (gui::CWidget *)0, &gui::CWidget::getActionStr)
            .ObjectDirect("getConfig", (gui::CWidget *)0, &gui::CWidget::getConfigStr)
            .ObjectDirect("getText", (gui::CWidget *)0, &gui::CWidget::getTextStr)
            .ObjectDirect("setLink", (gui::CWidget *)0, static_cast<GW_void_C_STR_IN>(&gui::CWidget::setLink))
            .ObjectDirect("setScript", (gui::CWidget *)0, static_cast<GW_void_C_STR_IN>(&gui::CWidget::setScript))
            .ObjectDirect("setAction", (gui::CWidget *)0, static_cast<GW_void_C_STR_IN>(&gui::CWidget::setAction))
            .ObjectDirect("setConfig", (gui::CWidget *)0, static_cast<GW_void_C_STR_IN>(&gui::CWidget::setConfig))
            .ObjectDirect("setText", (gui::CWidget *)0, static_cast<GW_void_C_STR_IN>(&gui::CWidget::setText))
            .ObjectDirect("getStyleName", (gui::CWidget *)0, &gui::CWidget::getStyleNameStr)
            .ObjectDirect("setStyleName", (gui::CWidget *)0, static_cast<GW_void_C_STR_IN>(&gui::CWidget::setStyleName))
            //.ObjectDirect("getStyleContents", (gui::CWidget *)0, &fgGuiWidget::getStyleContents)
            .ObjectDirect("getStyleContent", (gui::CWidget *)0, &gui::CWidget::getStyleContentPtr)
            //.ObjectDirect("refresh", (gui::CWidget *)0, &fgGuiWidget::setOnFocusCallback)
            .Function("isValid", &script::CScriptSubsystem::__isValid)
            ;
    //.MetatableFunction("__gc", &fgScriptSubsystem::managedResourceGCEvent);

    // Register Gui Button metatable
    metatableName = fgScriptMT->getMetatableName(CMetatables::GUI_BUTTON_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedObjectTypedGCEvent<fg::gui::WidgetHandle>);
    m_fgObj.Register("Button", &script::CScriptSubsystem::managedObjectTypedNewEvent<gui::CButton, CMetatables::GUI_BUTTON_MT_ID>);

    // Register Gui Toggle Button metatable
    metatableName = fgScriptMT->getMetatableName(CMetatables::GUI_TOGGLE_BUTTON_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(CMetatables::GUI_BUTTON_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedObjectTypedGCEvent<fg::gui::WidgetHandle>);
    m_fgObj.Register("ToggleButton", &script::CScriptSubsystem::managedObjectTypedNewEvent<gui::CToggleButton, CMetatables::GUI_TOGGLE_BUTTON_MT_ID>);

    typedef fgBool(gui::CContainer::*GCNT_Bool_C_STR_IN)(const char*);
    typedef fgBool(gui::CContainer::*GCNT_Bool_Widget_IN)(gui::CWidget *);

    // Register Gui Container metatable
    metatableName = fgScriptMT->getMetatableName(CMetatables::GUI_CONTAINER_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            .ObjectDirect("addChild", (gui::CContainer *)0, &gui::CContainer::addChild)

            .ObjectDirect("removeChild",
                          (gui::CContainer *)0,
                          static_cast<GCNT_Bool_Widget_IN>(&gui::CContainer::removeChild))

            .ObjectDirect("removeChildByName",
                          (gui::CContainer *)0,
                          static_cast<GCNT_Bool_C_STR_IN>(&gui::CContainer::removeChild))

            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedObjectTypedGCEvent<fg::gui::WidgetHandle>);
    m_fgObj.Register("Container",
                     &script::CScriptSubsystem::managedObjectTypedNewEvent<gui::CContainer, CMetatables::GUI_CONTAINER_MT_ID>);

    // Register Gui Editable Text metatable
    //metatableName = fgScriptMT->getMetatableName(E);
    //LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
    //        //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
    //        .MetatableFunction("__gc", &fgScriptSubsystem::managedObjectTypedGCEvent<fgGuiWidgetHandle>);
    //m_fgObj.Register("EditableText", &fgScriptSubsystem::managedObjectTypedNewEvent<fgGuiButton, fgScriptMetatables::GUI_CONSOLE_MT_ID>);

    // Register Gui Frame metatable
    metatableName = fgScriptMT->getMetatableName(CMetatables::GUI_FRAME_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(CMetatables::GUI_CONTAINER_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedObjectTypedGCEvent<fg::gui::WidgetHandle>);
    m_fgObj.Register("Frame",
                     &script::CScriptSubsystem::managedObjectTypedNewEvent<gui::CFrame, CMetatables::GUI_FRAME_MT_ID>);

    // Register Gui Label metatable
    metatableName = fgScriptMT->getMetatableName(CMetatables::GUI_LABEL_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedObjectTypedGCEvent<fg::gui::WidgetHandle>);
    m_fgObj.Register("Label",
                     &script::CScriptSubsystem::managedObjectTypedNewEvent<gui::CLabel, CMetatables::GUI_LABEL_MT_ID>);

    // Register Gui Loader metatable
    metatableName = fgScriptMT->getMetatableName(CMetatables::GUI_LOADER_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedObjectTypedGCEvent<fg::gui::WidgetHandle>);
    m_fgObj.Register("Loader",
                     &script::CScriptSubsystem::managedObjectTypedNewEvent<gui::CLoaderSub, CMetatables::GUI_LOADER_MT_ID>);

    // Register Gui Menu metatable
    metatableName = fgScriptMT->getMetatableName(CMetatables::GUI_MENU_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(CMetatables::GUI_CONTAINER_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedObjectTypedGCEvent<fg::gui::WidgetHandle>);
    m_fgObj.Register("Menu",
                     &script::CScriptSubsystem::managedObjectTypedNewEvent<gui::CMenu, CMetatables::GUI_MENU_MT_ID>);

    // Register Gui Window metatable
    metatableName = fgScriptMT->getMetatableName(CMetatables::GUI_WINDOW_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(CMetatables::GUI_CONTAINER_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedObjectTypedGCEvent<fg::gui::WidgetHandle>);
    m_fgObj.Register("Window",
                     &script::CScriptSubsystem::managedObjectTypedNewEvent<gui::CWindow, CMetatables::GUI_WINDOW_MT_ID>);

    // Register Gui MessageBox metatable
    metatableName = fgScriptMT->getMetatableName(CMetatables::GUI_MESSAGE_BOX_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(CMetatables::GUI_WINDOW_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedObjectTypedGCEvent<fg::gui::WidgetHandle>);
    m_fgObj.Register("MessageBox",
                     &script::CScriptSubsystem::managedObjectTypedNewEvent<gui::CMessageBox, CMetatables::GUI_MESSAGE_BOX_MT_ID>);

    // Register Gui Popup metatable
    metatableName = fgScriptMT->getMetatableName(CMetatables::GUI_POPUP_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(CMetatables::GUI_WINDOW_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedObjectTypedGCEvent<fg::gui::WidgetHandle>);
    m_fgObj.Register("Popup",
                     &script::CScriptSubsystem::managedObjectTypedNewEvent<gui::CPopup, CMetatables::GUI_POPUP_MT_ID>);

    // Register Gui Progress Bar metatable
    metatableName = fgScriptMT->getMetatableName(CMetatables::GUI_PROGRESS_BAR_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, metatableNameWidget)
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedObjectTypedGCEvent<fg::gui::WidgetHandle>);
    m_fgObj.Register("ProgressBar",
                     &script::CScriptSubsystem::managedObjectTypedNewEvent<gui::CProgressBar, CMetatables::GUI_PROGRESS_BAR_MT_ID>);

    // Register Gui Scroll Area metatable
    metatableName = fgScriptMT->getMetatableName(CMetatables::GUI_SCROLL_AREA_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(CMetatables::GUI_CONTAINER_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedObjectTypedGCEvent<fg::gui::WidgetHandle>);
    m_fgObj.Register("ScrollArea",
                     &script::CScriptSubsystem::managedObjectTypedNewEvent<gui::CScrollArea, CMetatables::GUI_SCROLL_AREA_MT_ID>);

    // Register Gui Table metatable
    metatableName = fgScriptMT->getMetatableName(CMetatables::GUI_TABLE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(CMetatables::GUI_CONTAINER_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedObjectTypedGCEvent<fg::gui::WidgetHandle>);
    m_fgObj.Register("Table",
                     &script::CScriptSubsystem::managedObjectTypedNewEvent<gui::CTable, CMetatables::GUI_TABLE_MT_ID>);

    // Register Gui TextArea metatable
    metatableName = fgScriptMT->getMetatableName(CMetatables::GUI_TEXT_AREA_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(CMetatables::GUI_SCROLL_AREA_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedObjectTypedGCEvent<fg::gui::WidgetHandle>);
    m_fgObj.Register("TextArea",
                     &script::CScriptSubsystem::managedObjectTypedNewEvent<gui::CTextArea, CMetatables::GUI_TEXT_AREA_MT_ID>);

    // Register Gui Console metatable
    metatableName = fgScriptMT->getMetatableName(CMetatables::GUI_CONSOLE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableName, fgScriptMT->getMetatableName(CMetatables::GUI_TEXT_AREA_MT_ID))
            //.ObjectDirect("getWidth", (fgTextureResource *)0, &fgTextureResource::getWidth)
            .MetatableFunction("__gc", &script::CScriptSubsystem::managedObjectTypedGCEvent<fg::gui::WidgetHandle>);
    m_fgObj.Register("Console",
                     &script::CScriptSubsystem::managedObjectTypedNewEvent<gui::CConsole, CMetatables::GUI_CONSOLE_MT_ID>);

    //
    // Styles / Style Content and other builtin
    // Some of these (StyleContent and inside types) cannot be
    // created via constructor inside of the script, only referenced
    // The metatable for these will not have __gc function set
    // #SAFEDESIGN #FIXME #PTRSAFE
    //
    typedef void (gui::CStyle::*GS_void_C_STR_IN)(const char*);
    typedef void (gui::CStyle::base_type::base_type::*GS_BASE_void_C_STR_IN)(const char*);
    typedef gui::CStyleContent * (gui::CStyle::*GS_StyleContent_C_STR_IN)(const char*);

    // Register Gui Style metatable
    //
    // #FIXME - will need to create base metatable for ManagedObject
    // because there are many types that shader that base class
    // Thanks to this there will be less copy pasting of the same
    // function pointers definitions ...
    //
    const char* metatableNameStyle = fgScriptMT->getMetatableName(CMetatables::GUI_STYLE_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableNameStyle)
            .ObjectDirect("getName",
                          (gui::CStyle::base_type::base_type *)0,
                          &gui::CStyle::base_type::base_type::getNameStr)
            .ObjectDirect("setName",
                          (gui::CStyle::base_type::base_type *)0,
                          static_cast<GS_BASE_void_C_STR_IN>(&gui::CStyle::base_type::base_type::setName))

            .ObjectDirect("getContentByName",
                          (gui::CStyle *)0,
                          static_cast<GS_StyleContent_C_STR_IN>(&gui::CStyle::getContentPtr))
            .Function("isValid", &script::CScriptSubsystem::__isValid)
            ;
    // fgGuiStyle FUBAR ^ ^ ^ ^ ^ ^ ^ ^ ^

    // Register Built in types for fgGuiStyleContent
    // Remember: Need definitions for special functions in LPCD namespace
    // Templates for Push/Match/Get -- types like: fgGuiSize/Background/Border
    // fgGuiAlign is an enum (not strong typed) so it will be implicitly cast to int

    // Register fgGuiSize structure ...
    // This structure cannot be created inside of lua, only received via reference
    // from style content obj
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(CMetatables::GUI_STYLE_SIZE_MT_ID))
            .Property("style", &gui::SSize::style)
            .Property("x", &gui::SSize::x)
            .Property("y", &gui::SSize::y)
            .Property("z", &gui::SSize::z)
            .Property("w", &gui::SSize::w)
            .Property("h", &gui::SSize::h)
            .Property("d", &gui::SSize::d)
            .Function("isValid", &script::CScriptSubsystem::__isValid);
    // MetatableFunction("__gc") // Nope

    // Register fgGuiBackground structure
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(CMetatables::GUI_STYLE_BACKGROUND_MT_ID))
            .Property("texture", &gui::SBackground::texture) // std::string
            .Property("color", &gui::SBackground::color) // color is fgColor4f/Vector4f (glm)
            .Property("style", &gui::SBackground::style) // enum fgGuiBackgroundStyle (int)
            .Function("isValid", &script::CScriptSubsystem::__isValid);
    // MetatableFunction("__gc") // Nope

    // Register fgGuiForeground structure
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(CMetatables::GUI_STYLE_FOREGROUND_MT_ID))
            .Property("font", &gui::SForeground::font) // std::string - font name
            .Property("color", &gui::SForeground::color) // color is fgColor4f/Vector4f (glm)
            .Property("textSize", &gui::SForeground::textSize) // float
            .Function("isValid", &script::CScriptSubsystem::__isValid);
    // MetatableFunction("__gc") // Nope

    // Register fgGuiMargin structure
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(CMetatables::GUI_STYLE_MARGIN_MT_ID))
            .Property("left", &gui::SMargin::left) // float
            .Property("right", &gui::SMargin::right) // float
            .Property("top", &gui::SMargin::top) // float
            .Property("bottom", &gui::SMargin::bottom) // float
            .Function("isValid", &script::CScriptSubsystem::__isValid);
    // MetatableFunction("__gc") // Nope

    // Register fgGuiPadding structure
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(CMetatables::GUI_STYLE_PADDING_MT_ID))
            .Property("left", &gui::SPadding::left) // float
            .Property("right", &gui::SPadding::right) // float
            .Property("top", &gui::SPadding::top) // float
            .Property("bottom", &gui::SPadding::bottom) // float
            .Function("isValid", &script::CScriptSubsystem::__isValid);
    // MetatableFunction("__gc") // Nope

    // Register fgGuiBorder structure
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(CMetatables::GUI_STYLE_BORDER_MT_ID))
            .Property("color", &gui::SBorder::color) // color is fgColor4f/Vector4f (glm)
            .Property("style", &gui::SBorder::style) // enum fgGuiBorderStyle (int)
            .Property("width", &gui::SBorder::width) // float
            .Function("isValid", &script::CScriptSubsystem::__isValid);
    // MetatableFunction("__gc") // Nope

    // Register fgGuiBorderInfo structure (stores info for all borders)
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(CMetatables::GUI_STYLE_BORDER_INFO_MT_ID))
            .Property("left", &gui::SBorderGroup::left) // structure fgGuiBorder
            .Property("right", &gui::SBorderGroup::right) // structure fgGuiBorder
            .Property("top", &gui::SBorderGroup::top) // structure fgGuiBorder
            .Property("bottom", &gui::SBorderGroup::bottom) // structure fgGuiBorder
            ;
    // MetatableFunction("__gc") // Nope

    // Register fgGuiPosition structure
    LPCD::Class(m_luaState->GetCState(), fgScriptMT->getMetatableName(CMetatables::GUI_STYLE_POSITION_MT_ID))
            .Property("style", &gui::SPosition::style) // enum fgGuiPositionStyle (int)
            .Property("unit", &gui::SPosition::unit) // enum fgGuiUnitType (int)
            .Property("left", &gui::SPosition::left) // float
            .Property("right", &gui::SPosition::right) // float
            .Property("top", &gui::SPosition::top) // float
            .Property("bottom", &gui::SPosition::bottom) // float
            .Property("front", &gui::SPosition::front) // float
            .Property("back", &gui::SPosition::back) // float
            .Function("isValid", &script::CScriptSubsystem::__isValid);
    // MetatableFunction("__gc") // Nope

    // Register Gui Style Content metatable - this metatable is without GC ! ! !
    //
    const char* metatableNameStyleContent = fgScriptMT->getMetatableName(CMetatables::GUI_STYLE_CONTENT_MT_ID);
    LPCD::Class(m_luaState->GetCState(), metatableNameStyleContent)
            //.Property("shader", &fgGuiStyle) // NOPE ?
            .ObjectDirect("getBackground", (gui::CStyleContent *)0, &gui::CStyleContent::getBackground)
            .ObjectDirect("getForeground", (gui::CStyleContent *)0, &gui::CStyleContent::getForeground)
            .ObjectDirect("getMargin", (gui::CStyleContent *)0, &gui::CStyleContent::getMargin)
            .ObjectDirect("getPadding", (gui::CStyleContent *)0, &gui::CStyleContent::getPadding)
            .ObjectDirect("getBorderInfo", (gui::CStyleContent *)0, &gui::CStyleContent::getBorder)
            .ObjectDirect("getBorder", (gui::CStyleContent *)0, &gui::CStyleContent::getBorder)
            .ObjectDirect("getPosition", (gui::CStyleContent *)0, &gui::CStyleContent::getPosition)
            .ObjectDirect("getAlign", (gui::CStyleContent *)0, &gui::CStyleContent::getAlign)
            .ObjectDirect("getVAlign", (gui::CStyleContent *)0, &gui::CStyleContent::getVAlign)
            .ObjectDirect("getTextAlign", (gui::CStyleContent *)0, &gui::CStyleContent::getTextAlign)
            .ObjectDirect("getSize", (gui::CStyleContent *)0, &gui::CStyleContent::getSize)
            .ObjectDirect("getShaderStr", (gui::CStyleContent *)0, &gui::CStyleContent::getShaderStr)
            .ObjectDirect("getEffectStr", (gui::CStyleContent *)0, &gui::CStyleContent::getEffectStr)
            //.ObjectDirect("", (fgGuiStyleContent *)0, &fgGuiStyleContent::)
            // Will not add any other functions (setters) because they return reference to self
            // This will force Lua to create an object which will be GCed quite fast
            // Need to reinforce StyleContent somehow
            .Function("isValid", &script::CScriptSubsystem::__isValid);

    // MetatableFunction("__gc") // Nope
    // No GC for Style Content ....
    // Whenever ! Wherever !
#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool script::CScriptSubsystem::registerStyleManager(void) {
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
//------------------------------------------------------------------------------

fgBool script::CScriptSubsystem::registerSoundManager(void) {
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
    typedef fgBool(sfx::CSfxManager::*SFX_Bool_C_STR_IN)(const char*);
    typedef sfx::base::CAudio * (sfx::CSfxManager::*SFX_CAudio_C_STR_IN)(const char*);

    // Sound manager metatable
    m_mgrMetatables[SOUND_MGR] = m_fgObj.CreateTable(fgScriptMT->getMetatableName(CMetatables::SOUND_MANAGER_MT_ID));
    m_mgrMetatables[SOUND_MGR].SetObject("__index", m_mgrMetatables[SOUND_MGR]);
    m_mgrMetatables[SOUND_MGR].SetInteger("__meta_enum", (int)CMetatables::SOUND_MANAGER_MT_ID);
    m_mgrMetatables[SOUND_MGR].Register("isValid", &script::CScriptSubsystem::__isValid);
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("play",
                                                    static_cast<sfx::CSfxManager *>(0),
                                                    static_cast<SFX_Bool_C_STR_IN>(&sfx::CSfxManager::play));
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("pause",
                                                    static_cast<sfx::CSfxManager *>(0),
                                                    static_cast<SFX_Bool_C_STR_IN>(&sfx::CSfxManager::pause));
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("resume",
                                                    static_cast<sfx::CSfxManager *>(0),
                                                    static_cast<SFX_Bool_C_STR_IN>(&sfx::CSfxManager::resume));
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("rewind",
                                                    static_cast<sfx::CSfxManager *>(0),
                                                    static_cast<SFX_Bool_C_STR_IN>(&sfx::CSfxManager::rewind));
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("stop",
                                                    static_cast<sfx::CSfxManager *>(0),
                                                    static_cast<SFX_Bool_C_STR_IN>(&sfx::CSfxManager::stop));
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("isPlaying",
                                                    static_cast<sfx::CSfxManager *>(0),
                                                    static_cast<SFX_Bool_C_STR_IN>(&sfx::CSfxManager::isPlaying));
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("isPaused",
                                                    static_cast<sfx::CSfxManager *>(0),
                                                    static_cast<SFX_Bool_C_STR_IN>(&sfx::CSfxManager::isPaused));
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("stopAll",
                                                    static_cast<sfx::CSfxManager *>(0),
                                                    &sfx::CSfxManager::stopAll);
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("setSfxVolume",
                                                    static_cast<sfx::CSfxManager *>(0),
                                                    &sfx::CSfxManager::setSfxVolume);
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("getSfxVolume",
                                                    static_cast<sfx::CSfxManager *>(0),
                                                    &sfx::CSfxManager::getSfxVolume);
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("setMusicVolume",
                                                    static_cast<sfx::CSfxManager *>(0),
                                                    &sfx::CSfxManager::setMusicVolume);
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("getMusicVolume",
                                                    static_cast<sfx::CSfxManager *>(0),
                                                    &sfx::CSfxManager::getMusicVolume);
    m_mgrMetatables[SOUND_MGR].RegisterObjectDirect("request",
                                                    static_cast<sfx::CSfxManager *>(0),
                                                    static_cast<SFX_CAudio_C_STR_IN>(&sfx::CSfxManager::request));

    uintptr_t offset = (uintptr_t)m_pSoundMgr;
    UserDataObjectMapItor it = m_userDataObjectMap.find(offset);
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
//------------------------------------------------------------------------------

fgBool script::CScriptSubsystem::registerGameMainManager(void) {
    if(m_isBindingComplete)
        return FG_TRUE;
    if(!m_pGameMainMgr)
        return FG_FALSE;
    if(m_pGameMainMgr->getManagerType() != FG_MANAGER_GAME_MAIN)
        return FG_FALSE;

#if defined(FG_USING_LUA_PLUS)
    if(m_mgrMetatables[GAME_MAIN_MGR].GetRef() >= 0)
        return FG_TRUE;
    if(m_fgObj.GetRef() < 0)
        return FG_FALSE;

    typedef fgBool(fg::game::CGameMain::*LOGIC_Bool_C_STR_IN)(const char*);
    typedef void(fg::game::CGameMain::*LOGIC_void_C_STR_IN)(const char*);
    typedef void(fg::game::CGameMain::*LOGIC_void_UINT_IN)(const unsigned int);

    // Game Logic manager metatable
    m_mgrMetatables[GAME_MAIN_MGR] = m_fgObj.CreateTable(fgScriptMT->getMetatableName(CMetatables::GAME_MAIN_MGR_MT_ID));
    m_mgrMetatables[GAME_MAIN_MGR].SetObject("__index", m_mgrMetatables[GAME_MAIN_MGR]);
    m_mgrMetatables[GAME_MAIN_MGR].SetInteger("__meta_enum", (int)CMetatables::GAME_MAIN_MGR_MT_ID);
    m_mgrMetatables[GAME_MAIN_MGR].Register("isValid", &script::CScriptSubsystem::__isValid);
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("startGameDefault",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::startGameDefault);
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("startGameStageID",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        static_cast<LOGIC_void_UINT_IN>(&fg::game::CGameMain::startGame));
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("startGameStageName",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        static_cast<LOGIC_void_C_STR_IN>(&fg::game::CGameMain::startGame));
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("stopGame",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::stopGame);
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("pauseGame",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::pauseGame);
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("restartGame",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::restartGame);

    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("getCurrentStageID",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::getCurrentStageID);
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("getCurrentStageName",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::getCurrentStageNameStr);
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("getStageScore",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::getStageScore);
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("getGlobalScore",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::getGlobalScore);
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("increaseStageScore",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::increaseStageScore);
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("resetStageScore",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::resetStageScore);

    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("setPlayerName",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        static_cast<LOGIC_void_C_STR_IN>(&fg::game::CGameMain::setPlayerName));
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("getPlayerName",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::getPlayerNameStr);

    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("isActive",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::isActive);
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("isPaused",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::isPaused);
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("isStopped",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::isStopped);
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("isLoading",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::isLoading);
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("isRestarting",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::isRestarting);
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("isStopping",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::isStopping);
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("isFinishing",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::isFinishing);
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("isFinished",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::isFinished);
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("isConnecting",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::isConnecting);
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("isWaiting",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::isWaiting);
    m_mgrMetatables[GAME_MAIN_MGR].RegisterObjectDirect("isDisconnected",
                                                        static_cast<fg::game::CGameMain *>(0),
                                                        &fg::game::CGameMain::isDisconnected);
    uintptr_t offset = (uintptr_t)m_pGameMainMgr;
    UserDataObjectMapItor it = m_userDataObjectMap.find(offset);
    if(it != m_userDataObjectMap.end()) {
        return FG_FALSE;
    }
    // Create lua object for Game Logic manager global
    LuaPlus::LuaObject logicMgrObj = m_luaState->BoxPointer((void *)m_pGameMainMgr);
    logicMgrObj.SetMetatable(m_mgrMetatables[GAME_MAIN_MGR]);


    // #FIXME - create in script proper structure as in C++ -> fg.game.Logic, etc
    m_fgObj.SetObject("LogicManager", logicMgrObj);
    m_fgObj.SetObject("GameLogic", logicMgrObj);
    m_userDataObjectMap[offset].obj = logicMgrObj;
    m_userDataObjectMap[offset].isBound = FG_TRUE;

#endif /* FG_USING_LUA_PLUS */
    return FG_TRUE;
}
//------------------------------------------------------------------------------
