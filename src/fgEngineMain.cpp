/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

/// Main include
#include "fgEngineMain.h"
/// Standard includes
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>
/// Various utilities
#include "Util/fgSettings.h"
#include "Util/fgConfig.h"
#include "Util/fgTime.h"
#include "Util/fgProfiling.h"
/// Game logic
#include "Game/fgGameMain.h"
/// Resource management
#include "Resource/fgResourceManager.h"
#include "Resource/fgResourceFactory.h"
/// Hardware capabilities
#include "Hardware/fgSensors.h"
#include "Hardware/fgQualityManager.h"
#include "Hardware/fgHardwareState.h"
/// Required GFX modules
#include "GFX/fgGfxMain.h"
#include "GFX/fgGfxModelResource.h"
#include "GFX/Shaders/fgGfxShaderProgram.h"
#include "GFX/Textures/fgTextureManager.h"
#include "GFX/Textures/fgTextureLoader.h"
#include "GFX/Particles/fgParticleSystem.h"
/// GUI Fonts
#include "GUI/Font/fgFontResource.h"
#include "GUI/Font/fgFontDrawer.h"
#include "GUI/Font/fgFontBuiltIn.h"
#include "GUI/fgGuiStyle.h"
/// Event management
#include "Event/fgEventManager.h"
/// User raw input (mouse/touch/)
#include "Event/fgInputHandler.h"
/// XML parsing
#include "XML/fgXMLParser.h"
/// Message subsystem
#include "fgMessageSubsystem.h"
/// Error codes
#include "fgErrorCodes.h"
/// Standard color array - format based on GFX color/vec4
#include "fgColors.h"
#include "fgDebugConfig.h"
/// Simple options management
#include "SimpleOpt.h"
/// Unistd
#include "fgUnistd.h"
/// Plugin resource
#include "fgPluginResource.h"
#include "Game/fgGameEntityType.h"
#include "Game/fgGameEntity.h"
#include "Game/fgGameEntityMesh.h"
#include "Game/fgGameEntityActor.h"

using namespace fg;
//------------------------------------------------------------------------------

CEngineMain::CEngineMain(int argc, char **argv) :
m_isFpsLocked(FG_TRUE),
m_fixedFPS(DEFAULT_FIXED_FPS),
m_updateFixedFPS(DEFAULT_UPDATE_FIXED_FPS),
m_argc(argc),
m_argv(argv),
m_gfxMain(NULL),
m_pShaderMgr(NULL),
m_pNodeFactory(NULL),
m_guiMain(NULL),
m_settings(NULL),
m_mainConfig(NULL),
m_qualityMgr(NULL),
m_resourceMgr(NULL),
m_resourceFactory(NULL),
m_inputHandler(NULL),
m_joypadController(NULL),
m_scriptSubsystem(NULL),
m_soundMgr(NULL),
m_gameMain(NULL),
m_3DGameWorld(NULL),
m_2DGameWorld(NULL),
m_gameTouchCallback(NULL),
m_gameMouseCallback(NULL),
m_gameFreeLookCallback(NULL),
m_gameKeyboardCallback(NULL) {
    if(!base_type::initialize()) {

    }
    // #FIXME srand init ?
    srand(time(NULL));
    // #FIXME error codes registry place
    fgErrorCodes::registerAll();
    // Initialize colors here?
    colors::initialize();
    // #FIXME - getcwd / get exec path / paths management / etc
    FG_MessageSubsystem->initialize(); // ? #FIXME message subsystem
    FG_MessageSubsystem->setLogPaths("all.log", "error.log", "debug.log");
    m_inputHandler = new event::CInputHandler();
#if !defined(FG_USING_PLATFORM_ANDROID)
    m_joypadController = new event::CJoypadController(); // #FIXME - Joypad part of input receiver?
#endif
    m_scriptSubsystem = new script::CScriptSubsystem();
    m_soundMgr = new sfx::CSfxManager();
    this->setEventManager();
#if !defined(FG_USING_PLATFORM_ANDROID)
    m_joypadController->initialize(); // #FIXME
#endif
    m_hardwareState = new CHardwareState();
    m_init = FG_FALSE;
    registerGameCallbacks();
}
//------------------------------------------------------------------------------

CEngineMain::~CEngineMain() {
    // >> Main Game Object destruction - begin
    // Unregister any required callbacks
    unregisterGameCallbacks();
    // Main Game Logic Manager
    if(m_gameMain) {
        FG_LOG_DEBUG("Destroying the Main Game Logic Manager...");
        delete m_gameMain;
        m_gameMain = NULL;
    }
    // Global Settings
    if(m_settings) {
        delete m_settings;
        m_settings = NULL;
    }
    // Main configuration file
    if(m_mainConfig) {
        delete m_mainConfig;
        m_mainConfig = NULL;
    }
    // GFX Main object
    if(m_gfxMain) {
        FG_LOG_DEBUG("Destroying the GFX Subsystem...");
        delete m_gfxMain;
        m_gfxMain = NULL;
    }
    m_pShaderMgr = NULL;
    m_pNodeFactory = NULL;
    if(m_3DGameWorld) {
        FG_LOG_DEBUG("GFX: Destroying the 3D Game World...");
        delete m_3DGameWorld;
        m_3DGameWorld = NULL;
    }
    if(m_2DGameWorld) {
        FG_LOG_DEBUG("GFX: Destroying the 2D Game World...");
        delete m_2DGameWorld;
        m_2DGameWorld = NULL;
    }
    if(m_guiMain) {
        m_guiMain->setShaderManager(NULL);
    }
    // Destroy SFX/Sound manager object
    if(m_soundMgr) {
        FG_LOG_DEBUG("Destroying the SFX Subsystem...");
        delete m_soundMgr;
        m_soundMgr = NULL;
    }
    // Destroy Resource Manager object
    // This will also destroy any left resources
    if(m_resourceMgr) {
        FG_LOG_DEBUG("Destroying the Resource Manager...");
        delete m_resourceMgr;
        m_resourceMgr = NULL;
    }
    if(m_guiMain) {
        m_guiMain->setResourceManager(NULL);
    }
    // Reset external pointers
    if(m_scriptSubsystem) {
        m_scriptSubsystem->setResourceManager(NULL);
        m_scriptSubsystem->setShaderManager(NULL);
        m_scriptSubsystem->set2DSceneManager(NULL);
        m_scriptSubsystem->set3DSceneManager(NULL);
        m_scriptSubsystem->setGameMainManager(NULL);
    }
    // Destroy the resource factory object
    if(m_resourceFactory) {
        delete m_resourceFactory;
        m_resourceFactory = NULL;
    }
    // Input Receiver object
    if(m_inputHandler) {
        FG_LOG_DEBUG("Destroying the Input Handler...");
        delete m_inputHandler;
        m_inputHandler = NULL;
    }
    if(m_guiMain) {
        m_guiMain->setInputHandler(NULL);
    }
    // Joystick Controller
    if(m_joypadController) {
        m_joypadController->quit();
        delete m_joypadController;
        m_joypadController = NULL;
    }
    // Remove any callbacks
    // They're already unregistered
    if(m_gameTouchCallback) {
        delete m_gameTouchCallback;
        m_gameTouchCallback = NULL;
    }
    if(m_gameMouseCallback) {
        delete m_gameMouseCallback;
        m_gameMouseCallback = NULL;
    }
    if(m_gameFreeLookCallback) {
        delete m_gameFreeLookCallback;
        m_gameFreeLookCallback = NULL;
    }
    if(m_gameKeyboardCallback) {
        delete m_gameKeyboardCallback;
        m_gameKeyboardCallback = NULL;
    }
    // Destroy the quality manager
    if(m_qualityMgr) {
        delete m_qualityMgr;
        m_qualityMgr = NULL;
    }
    // Main GUI class 
    // Do not reset the pointer... needs it to unregister callbacks
    //m_guiMain->setEventManager(NULL);    
    if(m_guiMain) {
        FG_LOG_DEBUG("Destroying the main GUI...");
        delete m_guiMain;
        m_guiMain = NULL;
    }
    if(m_scriptSubsystem) {
        m_scriptSubsystem->setGuiMain(NULL);
        m_scriptSubsystem->setWidgetManager(NULL);
        m_scriptSubsystem->setStyleManager(NULL);
        FG_LOG_DEBUG("Destroying the Script Subsystem...");
        // Destroy the Script Subsystem object
        delete m_scriptSubsystem;
        m_scriptSubsystem = NULL;
    }
    if(m_hardwareState) {
        FG_LOG_DEBUG("Destroying hardware state instance...");
        delete m_hardwareState;
        m_hardwareState = NULL;
    }
    // Free registered human readable colors - these are from HTML table
    colors::freeColors();
    // Unregister all error codes #FIXME
    fgErrorCodes::unregisterAll();
    //error_codes::unregisterAll();
    // Delete the global instance of Message Subsystem singleton
    // MessageSubsystem is a special LOG wrapper
    FG_MessageSubsystem->deleteInstance();
    // >> Main Game object destruction - end
    FG_LOG_DEBUG("FlexiGame::Engine object is destroyed.");

}
//------------------------------------------------------------------------------

fgBool CEngineMain::releaseResources(void) {
    if(m_resourceMgr) {
        FG_LOG_DEBUG("Releasing resources...");
        return m_resourceMgr->destroy();
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool CEngineMain::closeSybsystems(void) {
    FG_LOG_DEBUG("Closing subsystems...");
    if(m_gfxMain)
        m_gfxMain->releaseTextures();

    self_type::releaseResources();
    if(m_inputHandler)
        m_inputHandler->setEventManager(NULL);
    // DEVICE YIELD
    if(m_gfxMain)
        m_gfxMain->closeGFX();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CEngineMain::destroy(void) {
    FG_LOG_DEBUG("Game main quit requested");
    executeEvent(event::PROGRAM_QUIT);
    this->update(FG_TRUE);
    fgBool status = FG_TRUE;
    if(!releaseResources())
        status = FG_FALSE;
    if(!closeSybsystems())
        status = FG_FALSE;
    unregisterGameCallbacks();
    return status;
}
//------------------------------------------------------------------------------

void CEngineMain::registerGameCallbacks(void) {
    if(!m_gameTouchCallback)
        m_gameTouchCallback = new event::CMethodCallback<CEngineMain>(this, &CEngineMain::gameTouchHandler);

    event::CEventManager::addCallback(event::TOUCH_PRESSED, m_gameTouchCallback);
    event::CEventManager::addCallback(event::TOUCH_RELEASED, m_gameTouchCallback);
    event::CEventManager::addCallback(event::TOUCH_MOTION, m_gameTouchCallback);
    event::CEventManager::addCallback(event::TOUCH_TAP_FINISHED, m_gameTouchCallback);

    if(!m_gameMouseCallback)
        m_gameMouseCallback = new event::CMethodCallback<CEngineMain>(this, &CEngineMain::gameMouseHandler);

    event::CEventManager::addCallback(event::MOUSE_PRESSED, m_gameMouseCallback);
    event::CEventManager::addCallback(event::MOUSE_RELEASED, m_gameMouseCallback);
    event::CEventManager::addCallback(event::MOUSE_MOTION, m_gameMouseCallback);

    if(!m_gameFreeLookCallback)
        m_gameFreeLookCallback = new event::CMethodCallback<CEngineMain>(this, &CEngineMain::gameFreeLookHandler);

    event::CEventManager::addCallback(event::TOUCH_PRESSED, m_gameFreeLookCallback);
    event::CEventManager::addCallback(event::TOUCH_RELEASED, m_gameFreeLookCallback);
    event::CEventManager::addCallback(event::TOUCH_MOTION, m_gameFreeLookCallback);
    event::CEventManager::addCallback(event::TOUCH_TAP_FINISHED, m_gameFreeLookCallback);
    event::CEventManager::addCallback(event::MOUSE_PRESSED, m_gameFreeLookCallback);
    event::CEventManager::addCallback(event::MOUSE_RELEASED, m_gameFreeLookCallback);
    event::CEventManager::addCallback(event::MOUSE_MOTION, m_gameFreeLookCallback);

    if(!m_gameKeyboardCallback)
        m_gameKeyboardCallback = new event::CMethodCallback<CEngineMain>(this, &CEngineMain::gameKeyboardHandler);

    event::CEventManager::addCallback(event::KEY_UP, m_gameKeyboardCallback);
    event::CEventManager::addCallback(event::KEY_DOWN, m_gameKeyboardCallback);
    event::CEventManager::addCallback(event::KEY_PRESSED, m_gameKeyboardCallback);

}
//------------------------------------------------------------------------------

void CEngineMain::unregisterGameCallbacks(void) {
    event::CEventManager::removeCallback(event::TOUCH_PRESSED, m_gameTouchCallback);
    event::CEventManager::removeCallback(event::TOUCH_RELEASED, m_gameTouchCallback);
    event::CEventManager::removeCallback(event::TOUCH_MOTION, m_gameTouchCallback);
    event::CEventManager::removeCallback(event::TOUCH_TAP_FINISHED, m_gameTouchCallback);

    event::CEventManager::removeCallback(event::MOUSE_PRESSED, m_gameMouseCallback);
    event::CEventManager::removeCallback(event::MOUSE_RELEASED, m_gameMouseCallback);
    event::CEventManager::removeCallback(event::MOUSE_MOTION, m_gameMouseCallback);

    event::CEventManager::removeCallback(event::TOUCH_PRESSED, m_gameFreeLookCallback);
    event::CEventManager::removeCallback(event::TOUCH_RELEASED, m_gameFreeLookCallback);
    event::CEventManager::removeCallback(event::TOUCH_MOTION, m_gameFreeLookCallback);
    event::CEventManager::removeCallback(event::TOUCH_TAP_FINISHED, m_gameFreeLookCallback);
    event::CEventManager::removeCallback(event::MOUSE_PRESSED, m_gameFreeLookCallback);
    event::CEventManager::removeCallback(event::MOUSE_RELEASED, m_gameFreeLookCallback);
    event::CEventManager::removeCallback(event::MOUSE_MOTION, m_gameFreeLookCallback);

    event::CEventManager::removeCallback(event::KEY_UP, m_gameKeyboardCallback);
    event::CEventManager::removeCallback(event::KEY_DOWN, m_gameKeyboardCallback);
    event::CEventManager::removeCallback(event::KEY_PRESSED, m_gameKeyboardCallback);
}
//------------------------------------------------------------------------------

void CEngineMain::setEventManager(void) {
    //registerGameCallbacks();
    if(m_inputHandler)
        m_inputHandler->setEventManager(this);
    if(m_joypadController)
        m_joypadController->setEventManager(this);
    if(m_guiMain) {
        m_guiMain->setEventManager(this);
        m_guiMain->setInputHandler(m_inputHandler);
    }
    if(m_resourceMgr) {
        m_resourceMgr->setEventManager(this);
    }
    if(m_scriptSubsystem) {
        m_scriptSubsystem->setEventManager(this);
    }
}
//------------------------------------------------------------------------------

fgBool CEngineMain::initialize(void) {
    float t1 = timesys::ms();
    // DEVICE YIELD
    if(m_gfxMain)
        return FG_FALSE;
    m_gfxMain = new gfx::CGfxMain();
    int w, h;
    w = m_mainConfig->getParameterInt("MainConfig.hardware", "screenWidth");
    h = m_mainConfig->getParameterInt("MainConfig.hardware", "screenHeight");
    m_gfxMain->setScreenSize(w, h);
    if(!m_gfxMain->initGFX()) {
        return FG_FALSE;
    }
    m_pShaderMgr = m_gfxMain->getShaderManager();
    m_pNodeFactory = m_gfxMain->getNodeFactory();
    if(!m_guiMain) {
        // Provide styles and widgets path
        std::string mainModPath = m_settings->getMainModPath();
        std::string modPath = m_settings->getCurrentModPath();
        path::join(mainModPath, mainModPath, "gui");
        path::join(modPath, modPath, "gui");
        std::string guiPath;
        guiPath.append(mainModPath);
        guiPath.append(";");
        guiPath.append(modPath);
        m_guiMain = new gui::CGuiMain(guiPath, guiPath);
    }
    m_guiMain->setScreenSize(w, h);
    // #FIXME #HARDWARE_STATE #SCREENSIZE
    m_hardwareState->setScreenDimensions(w, h);
    m_hardwareState->initDPI();
    if(!m_qualityMgr)
        m_qualityMgr = new CQualityManager(w * h);
    if(!m_resourceFactory)
        m_resourceFactory = new resource::CResourceFactory();
    else
        m_resourceFactory->destroy();
    m_resourceFactory->registerObject(resource::SOUND, new util::CFactoryObject<sfx::CSound>());
    m_resourceFactory->registerObject(resource::MUSIC, new util::CFactoryObject<sfx::CMusic>());
    m_resourceFactory->registerObject(resource::MODEL3D, new util::CFactoryObject<gfx::CModel>());
    m_resourceFactory->registerObject(resource::TEXTURE, new util::CFactoryObject<gfx::CTexture>());
    m_resourceFactory->registerObject(resource::FONT, new util::CFactoryObject<gui::CFont>());
    //m_resourceFactory->registerObject(resource::SAVE_FILE, &);
    //m_resourceFactory->registerObject(resource::GUI_STRUCTURE_SHEET, &);
    //m_resourceFactory->registerObject(resource::GUI_STYLE_SHEET, &);
    //m_resourceFactory->registerObject(resource::SHADER, &);
    //m_resourceFactory->registerObject(resource::SCENE, &);
    //m_resourceFactory->registerObject(resource::SCRIPT, &);
    m_resourceFactory->registerObject(resource::GROUP, new util::CFactoryObject<resource::CResourceGroup>());
    //m_resourceFactory->registerObject(resource::VARIA, &);
    //m_resourceFactory->registerObject(resource::BINARY, &);
    //m_resourceFactory->registerObject(resource::LIBRARY, &);
    m_resourceFactory->registerObject(resource::PLUGIN, new util::CFactoryObject<CPlugin>());
    //m_resourceFactory->registerObject(resource::CUSTOM, &);
    //m_resourceFactory->registerObject(resource::ZIP_PACK, &);
    m_resourceFactory->registerObject(resource::PARTICLE_EFFECT, new util::CFactoryObject<gfx::CParticleEffect>());


    // DEVICE YIELD
    if(!m_resourceMgr)
        m_resourceMgr = new resource::CResourceManager(m_resourceFactory, m_qualityMgr, this);
#if 1
    m_resourceMgr->setMaximumMemory(128 * 1024 * 1024 - 1024 * 1024 * 10); // #FIXME #TODO
    m_resourceMgr->initialize();
#endif
    {
        // Register additional game entity objects
        m_pNodeFactory->registerObject(game::GAME_ENTITY, new util::CFactoryObject<game::CEntity>());
        m_pNodeFactory->registerObject(game::GAME_ENTITY_MESH, new util::CFactoryObject<game::CEntityMesh>());
        m_pNodeFactory->registerObject(game::GAME_ENTITY_ACTOR, new util::CFactoryObject<game::CEntityActor>());
        if(!m_3DGameWorld)
            m_3DGameWorld = new game::CGameWorld3D();
        m_3DGameWorld->setShaderManager(m_pShaderMgr);
        m_3DGameWorld->getMVP()->setPerspective(45.0f, m_gfxMain->getMainWindow()->getAspect());
        if(!m_2DGameWorld)
            m_2DGameWorld = new game::CGameWorld2D();
        m_2DGameWorld->setShaderManager(m_pShaderMgr);
        m_2DGameWorld->getMVP()->setOrtho(0.0f,
                                          (float)gfx::context::getScreenSize().x,
                                          (float)gfx::context::getScreenSize().y, 0.0f);

        m_gfxMain->set3DScene(m_3DGameWorld);
        m_gfxMain->set2DScene(m_2DGameWorld);
        m_gfxMain->getParticleSystem()->setSceneManager(m_3DGameWorld);
        m_3DGameWorld->initialize();
        m_2DGameWorld->initialize();
        m_gfxMain->addLayer(m_3DGameWorld);
        m_gfxMain->addLayer(m_2DGameWorld);

        m_guiMain->getDrawer()->getMVP()->setOrtho(0.0f,
                                                   (float)gfx::context::getScreenSize().x,
                                                   (float)gfx::context::getScreenSize().y, 0.0f);
    }
    // Setup GFX Main external pointers
    m_gfxMain->setupResourceManager(m_resourceMgr);
    //m_gfxMain->generateBuiltInData();
    // DEVICE YIELD
    ////////////////////////////////////////////////////////////////////////////
    // Resource Manager and GFX is now fully initialized (with default shader)
    // Now is the moment to display something on screen - preload some texture
    // This will preload any required textures and upload them to the GFX
    m_gfxMain->setupLoader();
    // DEVICE YIELD
    m_gfxMain->getLoader()->update(5.0f); // 5

    ////////////////////////////////////////////////////////////////////////////
    // Setup SFX manager external pointer - resource manager
    if(m_soundMgr)
        m_soundMgr->setResourceManager(m_resourceMgr);
    if(!m_soundMgr->initialize()) {
        FG_LOG_ERROR("SFX: Initialization of Sound module finished with errors");
    }
    m_gfxMain->getLoader()->update(10.0f); // 15
    // Create object for Game Logic Manager
    if(!m_gameMain)
        m_gameMain = new game::CGameMain(this);
    // Setup Game Logic external pointers
    if(m_gameMain) {
        m_gameMain->setEventManager(this);
        // Initialize the Game Logic object
        if(!m_gameMain->initialize()) {
            FG_LOG_ERROR("Logic: Main Game Logic module initialized with errors");
        }
    }
    if(m_inputHandler)
        m_inputHandler->initialize(m_hardwareState);
    m_gfxMain->getLoader()->update(15.0f); // 30
    // DEVICE YIELD
    // Setup GUI Main external pointers
    m_guiMain->setResourceManager(m_resourceMgr);
    m_guiMain->setShaderManager(m_gfxMain->getShaderManager());
    m_guiMain->setInputHandler(m_inputHandler);
    m_guiMain->setEventManager(this);
    m_inputHandler->setEventManager(this);
    m_resourceMgr->setEventManager(this);
    // When GUI MAIN has set the resource manager - it can preload builtin fonts
    if(!m_guiMain->initialize()) {
        FG_LOG_ERROR("GUI: Main module initialized with errors");
    }
    // Setup Script Subsystem external pointers
    m_scriptSubsystem->setEventManager(this);
    m_scriptSubsystem->setResourceManager(m_resourceMgr);
    m_scriptSubsystem->setParticleSystem(m_gfxMain->getParticleSystem());
    m_scriptSubsystem->set2DSceneManager(m_gfxMain->get2DScene());
    m_scriptSubsystem->set3DSceneManager(m_gfxMain->get3DScene());
    m_scriptSubsystem->setGuiMain(static_cast<fg::base::CManager *>(m_guiMain));
    m_scriptSubsystem->setShaderManager(static_cast<fg::base::CManager *>(m_gfxMain->getShaderManager()));
    m_scriptSubsystem->setSoundManager(static_cast<fg::base::CManager *>(m_soundMgr));
    m_scriptSubsystem->setStyleManager(static_cast<fg::base::CManager *>(m_guiMain->getStyleManager()));
    m_scriptSubsystem->setWidgetManager(static_cast<fg::base::CManager *>(m_guiMain->getWidgetManager()));
    m_scriptSubsystem->setGameMainManager(static_cast<fg::base::CManager *>(m_gameMain));
    m_gfxMain->getLoader()->update(10.0f); // 40
    if(!m_scriptSubsystem->initialize()) {
        FG_LOG_ERROR("Script: Initialization of Script module finished with errors");
    }
    // DEVICE YIELD
    float t2 = timesys::ms();
    FG_LOG_DEBUG("Main: All subsystems initialized in %.2f seconds", (t2 - t1) / 1000.0f);
    m_gfxMain->getLoader()->update(10.0f); // 50
    m_init = FG_TRUE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CEngineMain::loadConfiguration(void) {
    FG_LOG_DEBUG("Loading configuration...");
    fgBool status = FG_TRUE;
    if(!m_settings)
        m_settings = new CSettings();
    if(!m_settings->load("settings.xml")) { // #FIXME - universal, cross solution - path management
        FG_LOG_ERROR("Main: Failed to load main settings...");
        return FG_FALSE;
    }
    if(m_settings->getMainConfigPath().length()) {
        if(!m_mainConfig)
            m_mainConfig = new util::CConfig();
        if(!m_mainConfig->load(m_settings->getMainConfigPathStr())) {
            FG_LOG_ERROR("Main: Failed to load main configuration file...");
            return FG_FALSE;
        }
    }
#if !defined(FG_USING_PLATFORM_ANDROID) && !defined(FG_USING_PLATFORM_IOS)
    path::changeCurrentWorkingDir(m_settings->getInstallationPath());
    path::changeCurrentWorkingDir(m_settings->getDefaultDataPath());
#endif
    // #FIXME enumeration

    enum
    {
        OPT_MOD = 0,
        OPT_HELP,
        OPT_VERBOSE_LEVEL,
        OPT_PHYSICS_BBOX,
        OPT_PHYSICS_WIREFRAME,
        OPT_GUI_BBOX,
        OPT_GFX_BBOX,
        OPT_GFX_SPHERE,
        OPT_GFX_TREE_BBOX,
        OPT_GFX_FRUSTUM,
        OPT_GFX_LIGHT,
        OPT_GFX_DUMP_CONFIG,
        OPT_GFX_DUMP_DISPLAY,
        OPT_GFX_DUMP_SHADERS,
        OPT_GAME_FREE_LOOK,
        OPT_LABELS,
        OPT_DUMP_CONFIG,
        OPT_FORCE_FULLSCREEN,
        OPT_DEBUG_PROFILING,
        OPT_SHOW_CONSOLE
    };
    //
    // SO_NONE - No argument. Just the option flags. e.g. -o --opt
    //
    // SO_REQ_SEP - Required separate argument.  e.g. -o ARG --opt ARG
    //
    // SO_REQ_CMB - Required combined argument.  e.g. -oARG -o=ARG --opt=ARG
    //
    // SO_OPT - Optional combined argument.  e.g. -o[ARG]    -o[=ARG]    --opt[=ARG]
    //
    // SO_MULTI - Multiple separate arguments. The actual number of arguments is
    // determined at the time the argument is processed.
    // e.g. -o N ARG1 ARG2 ... ARGN    --opt N ARG1 ARG2 ... ARGN
    //
    // #FIXME
    CSimpleOpt::SOption gameOptions[] = {
        {OPT_MOD, "--mod", SO_REQ_SEP},
        {OPT_HELP, "--help", SO_NONE},
        {OPT_VERBOSE_LEVEL, "--verbose", SO_OPT},
        {OPT_PHYSICS_BBOX, "--physics-bbox", SO_OPT},
        {OPT_PHYSICS_BBOX, "--physics-bbox-show", SO_NONE},
        {OPT_PHYSICS_WIREFRAME, "--physics-wireframe", SO_OPT},
        {OPT_PHYSICS_WIREFRAME, "--physics-wireframe-show", SO_NONE},
        {OPT_GUI_BBOX, "--gui-bbox", SO_OPT},
        {OPT_GUI_BBOX, "--gui-bbox-show", SO_NONE},
        {OPT_GFX_BBOX, "--gfx-bbox", SO_OPT},
        {OPT_GFX_BBOX, "--gfx-bbox-show", SO_NONE},
        {OPT_GFX_SPHERE, "--gfx-sphere", SO_OPT},
        {OPT_GFX_SPHERE, "--gfx-sphere-show", SO_NONE},
        {OPT_GFX_TREE_BBOX, "--gfx-tree-bbox", SO_OPT},
        {OPT_GFX_TREE_BBOX, "--gfx-tree-bbox-show", SO_NONE},
        {OPT_GFX_FRUSTUM, "--gfx-frustum-show", SO_OPT},
        {OPT_GFX_LIGHT, "--gfx-light-show", SO_OPT},
        {OPT_GFX_DUMP_CONFIG, "--gfx-dump-config", SO_OPT},
        {OPT_GFX_DUMP_DISPLAY, "--gfx-dump-display", SO_OPT},
        {OPT_GFX_DUMP_SHADERS, "--gfx-dump-shaders", SO_OPT},
        {OPT_GAME_FREE_LOOK, "--game-free-look", SO_OPT},
        {OPT_LABELS, "--show-labels", SO_OPT},
        {OPT_DUMP_CONFIG, "--dump-config", SO_OPT},
        {OPT_FORCE_FULLSCREEN, "--fullscreen", SO_NONE},
        {OPT_FORCE_FULLSCREEN, "--fs", SO_NONE},
        {OPT_DEBUG_PROFILING, "--profiling-debug", SO_NONE},
        {OPT_SHOW_CONSOLE, "--console", SO_NONE},
        {OPT_SHOW_CONSOLE, "--show-console", SO_NONE},
        { -1, NULL, SO_NONE}
    };
    CSimpleOpt args;
    args.Init(m_argc, m_argv, gameOptions, SO_O_NOERR | SO_O_EXACT);
    while(args.Next()) {
        const char* pArgStr = NULL;
        fgBool hasArgument = (fgBool)!!(args.OptionArg() && strlen(args.OptionArg()));
        if(hasArgument)
            pArgStr = args.OptionArg();
        switch(args.OptionId()) {
            case OPT_MOD:
                if(hasArgument) {
                    m_settings->setCurrentModPath(pArgStr);
                    FG_LOG_DEBUG("SETUP: Setting new current mod path: '%s'", pArgStr);
                }
                break;
#if defined(FG_DEBUG)
            case OPT_HELP:
                printf("Available options (only in DEBUG build):\n");
                printf("--verbose                 Select verbosity level for all messages\n"
                       "--physics-bbox-show       Display physical bounding boxes\n"
                       "--physics-wireframe-show  Display wireframe of physical collision bodies\n"
                       "--gui-bbox-show           Display bounding boxes for GUI elements\n"
                       "--gfx-bbox-show           Display bounding boxes for 3D scene objects\n"
                       "--gfx-sphere-show         Display bounding spheres for 3D scene objects\n"
                       "--gfx-tree-bbox-show      Display bounding boxes for spatial tree nodes\n"
                       "--gfx-frustum-show        Display frustum box\n"
                       "--gfx-light-show          Show light sources\n"
                       "--gfx-dump-config         Whether or not to dump graphics configuration\n"
                       "--gfx-dump-display        Whether or not to dump all available screen resolutions\n"
                       "--gfx-dump-shaders        Whether or not to dump every compiled shader\n"
                       "--game-free-look          Whether or not to activate free look camera (no-clip like)\n"
                       "--show-labels             Whether or not to show labels for 3D scene objects\n"
                       "--dump-config             Dump .ini configuration files\n"
                       "--fullscreen, --fs        Force fullscreen mode\n"
                       "--profiling-debug         Activate profiling in DEBUG mode\n"
                       "--console, --show-console Show built-in console after startup\n"
                       "\n");
                status = FG_FALSE; // FIXME - this is bad
                break;
            case OPT_VERBOSE_LEVEL:
                if(hasArgument) {
                    // #FIXME - need to check for more than just numbers
                    const unsigned char high = FG_VERBOSE_LVL_HIGH;
                    const unsigned char none = FG_VERBOSE_LVL_NONE;
                    const unsigned char low = FG_VERBOSE_LVL_LOW;
                    char verboseLevel = (char)std::atoi(pArgStr);
                    if(verboseLevel > high)
                        verboseLevel = high;
                    if(verboseLevel < none)
                        verboseLevel = none;
                    g_DebugConfig.verboseLevel = verboseLevel;
                } else {
                    g_DebugConfig.verboseLevel = FG_VERBOSE_LVL_HIGH;
                }
                break;

            case OPT_PHYSICS_BBOX:
                if(hasArgument) {
                    fgBool boolValue = FG_BOOL_FROM_TEXT(pArgStr);
                    g_DebugConfig.physicsBBoxShow = (bool)boolValue;
                } else {
                    g_DebugConfig.physicsBBoxShow = true;
                }
                break;

            case OPT_PHYSICS_WIREFRAME:
                if(hasArgument) {
                    fgBool boolValue = FG_BOOL_FROM_TEXT(pArgStr);
                    g_DebugConfig.physicsWireframeShow = (bool)boolValue;
                } else {
                    g_DebugConfig.physicsWireframeShow = true;
                }
                break;

            case OPT_GUI_BBOX:
                if(hasArgument) {
                    fgBool boolValue = FG_BOOL_FROM_TEXT(pArgStr);
                    g_DebugConfig.guiBBoxShow = (bool)boolValue;
                } else {
                    g_DebugConfig.guiBBoxShow = true;
                }
                break;

            case OPT_GFX_BBOX:
                if(hasArgument) {
                    fgBool boolValue = FG_BOOL_FROM_TEXT(pArgStr);
                    g_DebugConfig.gfxBBoxShow = (bool)boolValue;
                } else {
                    g_DebugConfig.gfxBBoxShow = true;
                }
                break;

            case OPT_GFX_SPHERE:
                if(hasArgument) {
                    fgBool boolValue = FG_BOOL_FROM_TEXT(pArgStr);
                    g_DebugConfig.gfxSphereShow = (bool)boolValue;
                } else {
                    g_DebugConfig.gfxSphereShow = true;
                }
                break;

            case OPT_GFX_TREE_BBOX:
                if(hasArgument) {
                    fgBool boolValue = FG_BOOL_FROM_TEXT(pArgStr);
                    g_DebugConfig.gfxTreeBBoxShow = (bool)boolValue;
                } else {
                    g_DebugConfig.gfxTreeBBoxShow = true;
                }
                break;

            case OPT_GFX_FRUSTUM:
                if(hasArgument) {
                    fgBool boolValue = FG_BOOL_FROM_TEXT(pArgStr);
                    g_DebugConfig.gfxTreeBBoxShow = (bool)boolValue;
                } else {
                    g_DebugConfig.gfxTreeBBoxShow = true;
                }
                break;

            case OPT_GFX_LIGHT:
                if(hasArgument) {
                    fgBool boolValue = FG_BOOL_FROM_TEXT(pArgStr);
                    g_DebugConfig.gfxLightShow = (bool)boolValue;
                } else {
                    g_DebugConfig.gfxLightShow = true;
                }
                break;

            case OPT_GFX_DUMP_CONFIG:
                if(hasArgument) {
                    fgBool boolValue = FG_BOOL_FROM_TEXT(pArgStr);
                    g_DebugConfig.gfxDumpConfig = (bool)boolValue;
                } else {
                    g_DebugConfig.gfxDumpConfig = true;
                }
                break;

            case OPT_GFX_DUMP_DISPLAY:
                if(hasArgument) {
                    fgBool boolValue = FG_BOOL_FROM_TEXT(pArgStr);
                    g_DebugConfig.gfxDumpDisplay = (bool)boolValue;
                } else {
                    g_DebugConfig.gfxDumpDisplay = true;
                }
                break;

            case OPT_GFX_DUMP_SHADERS:
                if(hasArgument) {
                    fgBool boolValue = FG_BOOL_FROM_TEXT(pArgStr);
                    g_DebugConfig.gfxDumpShaders = (bool)boolValue;
                } else {
                    g_DebugConfig.gfxDumpShaders = true;
                }
                break;

            case OPT_GAME_FREE_LOOK:
                if(hasArgument) {
                    fgBool boolValue = FG_BOOL_FROM_TEXT(pArgStr);
                    g_DebugConfig.gameFreeLook = (bool)boolValue;
                } else {
                    g_DebugConfig.gameFreeLook = true;
                }
                break;

            case OPT_LABELS:
                if(hasArgument) {
                    fgBool boolValue = FG_BOOL_FROM_TEXT(pArgStr);
                    g_DebugConfig.labelsShow = (bool)boolValue;
                } else {
                    g_DebugConfig.labelsShow = true;
                }
                break;

            case OPT_DUMP_CONFIG:
                if(hasArgument) {
                    fgBool boolValue = FG_BOOL_FROM_TEXT(pArgStr);
                    g_DebugConfig.dumpConfig = (bool)boolValue;
                } else {
                    g_DebugConfig.dumpConfig = true;
                }
                break;

            case OPT_FORCE_FULLSCREEN:
                if(hasArgument) {
                    fgBool boolValue = FG_BOOL_FROM_TEXT(pArgStr);
                    g_DebugConfig.forceFullscreen = (bool)boolValue;
                } else {
                    g_DebugConfig.forceFullscreen = true;
                }
                break;

            case OPT_DEBUG_PROFILING:
                if(hasArgument) {
                    fgBool boolValue = FG_BOOL_FROM_TEXT(pArgStr);
                    g_DebugConfig.isDebugProfiling = (bool)boolValue;
                } else {
                    g_DebugConfig.isDebugProfiling = true;
                }
                break;

            case OPT_SHOW_CONSOLE:
                if(hasArgument) {
                    fgBool boolValue = FG_BOOL_FROM_TEXT(pArgStr);
                    g_DebugConfig.consoleShow = (bool)boolValue;
                } else {

                    g_DebugConfig.consoleShow = true;
                }
                break;
#endif
            default:
                break;
        };
    }
    FG_LOG_DEBUG("Main: Selected current mod: '%s'", m_settings->getCurrentModPathStr());
    return status;
}
//------------------------------------------------------------------------------

fgBool CEngineMain::loadResources(void) {
    float t1 = timesys::ms();
    FG_LOG_DEBUG("Loading resources...");
    m_gfxMain->getShaderManager()->setShadersPath("shaders/");
    m_gfxMain->preLoadShaders();
    m_gfxMain->generateBuiltInData();
    {
        gfx::CShaderProgram* pSkyBoxProgram = m_gfxMain->getShaderManager()->request(gfx::shaders::USAGE_SKYBOX_RENDER_BIT);
        m_gfxMain->get3DScene()->setSkyBoxShader(pSkyBoxProgram);
        m_gfxMain->get2DScene()->setSkyBoxShader(pSkyBoxProgram);
    }
    m_gfxMain->getShaderManager()->setLinkOnUse(FG_TRUE);
    m_gfxMain->getShaderManager()->setLinkOnRequest(FG_TRUE);
    //#if defined(FG_USING_OPENGL_ES)
    m_gfxMain->getShaderManager()->setUniformAutoUpdate(FG_TRUE);
    //#endif
    {
        if(m_3DGameWorld && m_pShaderMgr) {
            m_3DGameWorld->setDefaultShader(m_pShaderMgr->request(gfx::shaders::USAGE_DEFAULT_BIT | gfx::shaders::USAGE_LOW_QUALITY_BIT));
            if(!m_3DGameWorld->getDefaultShader())
                m_3DGameWorld->setDefaultShader(m_pShaderMgr->request(gfx::shaders::USAGE_FALLBACK_BIT));
        }
        if(m_2DGameWorld && m_pShaderMgr) {
            m_2DGameWorld->setDefaultShader(m_pShaderMgr->request(gfx::shaders::USAGE_2D_RENDER_BIT));
            if(!m_2DGameWorld->getDefaultShader())
                m_2DGameWorld->setDefaultShader(m_pShaderMgr->request(gfx::shaders::USAGE_FALLBACK_BIT));
        }
        if(m_guiMain && m_pShaderMgr) {
            gfx::CShaderProgram* pGuiProgram = m_gfxMain->getShaderManager()->request(gfx::shaders::USAGE_GUI_RENDER_BIT);
            m_guiMain->getDrawer()->setDefaultShader(pGuiProgram);
        }
    }

#if defined(FG_USING_LUA_PLUS)
    //LuaPlus::LuaState *state = m_scriptSubsystem->getLuaState();
    std::string mainScriptPath, modScriptPath;
    path::join(mainScriptPath, m_settings->getMainModPath(), std::string("main.lua"));
    FG_LOG_DEBUG("Main: Loading and executing script file: '%s'", mainScriptPath.c_str());
    m_scriptSubsystem->executeFile(mainScriptPath);

    path::join(modScriptPath, m_settings->getCurrentModPath(), std::string("main.lua"));
    FG_LOG_DEBUG("Main: Loading and executing script file: '%s'", modScriptPath.c_str());
    m_scriptSubsystem->executeFile(modScriptPath);
#endif
    m_gfxMain->getLoader()->update(10.0f); // 60

    m_gfxMain->getLoader()->update(15.0f); // 75
    // DEVICE YIELD
    ////////////////////////////////////////////////////////////////////////////
    // Can also create special event for GFX - upload static vertex data
    // Create vertex buffers on event - not explicitly
    // DEVICE YIELD
    m_gfxMain->getLoader()->update(15.0f); // 90
    ////////////////////////////////////////////////////////////////////////////

    //m_gfxMain->getShaderManager()->get(sPlainEasyShaderName)->use();
    this->update(FG_TRUE);
    float t2 = timesys::ms();
    FG_LOG_DEBUG("Main: Resources loaded in %.2f seconds", (t2 - t1) / 1000.0f);

    FG_LOG_DEBUG("Main: Initializing mod plugin: '%s'", m_settings->getCurrentModPathStr());
    // Name of the plugin resource should have the same name as mod
    resource::CResource *pPluginRes = m_resourceMgr->request(m_settings->getCurrentModPathStr());
    if(pPluginRes && pPluginRes->getResourceType() == resource::PLUGIN) {

        CPluginResource *plugin = (CPluginResource *)pPluginRes;
        plugin->setInternalInfo(this); // setting pointer to the CGameMain
        plugin->create(); // Loading the shared object | should initialize the plugin
    }
    this->update(FG_TRUE);
    m_gfxMain->getLoader()->update(10.0f); // 100
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CEngineMain::preRender(void) {
    if(!m_init)
        return FG_FALSE;
    static float t1 = -1.0f;
    float t2 = fg::timesys::ms();
    float dt = 0.0f;
    const float msPerFrame = 1000.0f / (float)m_fixedFPS;
    if(t1 < 0.0f) {
        t1 = fg::timesys::ms();
    }
    dt = t2 - t1;
    if(dt > msPerFrame) {
        t1 = t2;
    } else if(m_isFpsLocked) {
        return FG_FALSE;
    }
    // This should be synchronized to 60FPS, meaning that should be called in display / render
    // maybe should give some categories ?
    timesys::markTick(timesys::TICK_PRERENDER);
    executeEvent(event::PRERENDER_SHOT, (void*)this);
#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling)
        profile::g_debugProfiling->begin("GFX::preRender");
#endif
    m_gfxMain->preRender();
#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("GFX::preRender");
        profile::g_debugProfiling->begin("GUI::preRender");
    }
#endif
    m_guiMain->preRender();
#if defined(FG_DEBUG)
    gui::CDrawer* pDrawer = m_guiMain->getDrawer();
    pDrawer->setColor(Color3f(1.0f, 1.0f, 1.0f));
    pDrawer->setFont("StbConsolasBold");
    pDrawer->print(20, 20, 20, "%.2f", m_hardwareState->getFPS());
#endif
#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {

        profile::g_debugProfiling->end("GUI::preRender");
    }
#endif    
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CEngineMain::render(void) {
    if(!m_init) {
        return FG_FALSE;
    }
    if(!m_gfxMain->isInit()) {
        return FG_FALSE;
    }
    static int fpsc = -1;
    static float t1 = -1.0f;
    float t2 = fg::timesys::ms();
    float dt = 0.0f;
    const float msPerFrame = 1000.0f / (float)m_fixedFPS;
    if(t1 < 0.0f) {
        t1 = fg::timesys::ms();
    }
    dt = t2 - t1;
    if(dt > msPerFrame) {
        t1 = t2;
    } else if(m_isFpsLocked) {
        return FG_FALSE;
    }
    timesys::markTick(timesys::TICK_RENDER);
    m_hardwareState->calculateFPS();
#if 1
    if(fpsc < 0) {
        usleep(50 * 1000);
    }
#endif
    fpsc++;
    if(fpsc > 256) {
        fpsc = 0;
    }
#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->begin("GFX::render");
    }
#endif

    fgBool status = m_gfxMain->prepareFrame();
    if(status) {
        executeEvent(event::RENDER_SHOT, (void*)this);
        m_gfxMain->render();
    }

    // DEVICE YIELD
#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("GFX::render");
    }
#endif
    if(!status) {
        return FG_FALSE;
    }
    gfx::context::setBlend(FG_TRUE); // #FIXME
    gfx::context::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    gfx::context::scissor();
#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->begin("GUI::render");
    }
#endif
    m_guiMain->render();

#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {

        profile::g_debugProfiling->end("GUI::render");
    }
#endif
    gfx::context::setBlend(FG_FALSE); // #FIXME
    // DEVICE YIELD
    m_gfxMain->getMainWindow()->swapBuffers();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CEngineMain::update(fgBool force) {
    if(!m_init) {
        return FG_FALSE;
    }
    static float t1 = -1.0f;
    float t2 = fg::timesys::ms();
    float dt = 0.0f;
    const float msPerFrame = 1000.0f / (float)m_updateFixedFPS;
    if(t1 < 0.0f) {
        t1 = fg::timesys::ms();
    }
    dt = t2 - t1;
    if(dt > msPerFrame) {
        t1 = t2;
    } else if(!force) {
        return FG_FALSE;
    }
    timesys::markTick(timesys::TICK_UPDATE);
    int screenW = 1024, screenH = 600;
    if(m_gfxMain && m_gfxMain->getMainWindow()) {
        screenW = m_gfxMain->getMainWindow()->getWidth();
        screenH = m_gfxMain->getMainWindow()->getHeight();
    }
    if(m_guiMain)
        m_guiMain->setScreenSize(screenW,
                                 screenH);

    // Update logic manager
    if(m_gameMain)
        m_gameMain->update();
    // Handler for input events (touch, mouse, keys)
    if(m_inputHandler) {
        m_inputHandler->processData();

#if defined(FG_DEBUG)
        if(fg::g_DebugConfig.gameFreeLook) {
            if(m_inputHandler->isKeyDown(event::FG_KEY_W)) {
                this->m_gfxMain->get3DSceneCamera()->moveForward();
            }
            if(m_inputHandler->isKeyDown(event::FG_KEY_S)) {
                this->m_gfxMain->get3DSceneCamera()->moveBackward();
            }
            if(m_inputHandler->isKeyDown(event::FG_KEY_A)) {
                this->m_gfxMain->get3DSceneCamera()->moveLeft();
            }
            if(m_inputHandler->isKeyDown(event::FG_KEY_D)) {
                this->m_gfxMain->get3DSceneCamera()->moveRight();
            }
            if(m_inputHandler->isKeyDown(event::FG_KEY_SPACE)) {
                this->m_gfxMain->get3DSceneCamera()->moveUp();
            }
            if(m_inputHandler->isKeyDown(event::FG_KEY_LCTRL)) {
                this->m_gfxMain->get3DSceneCamera()->moveDown();
            }
        }
#endif
    }
    // Well this is really useful system, in the end GUI and others will be hooked
    // to EventManager so everything what needs to be done is done in this function
    event::CEventManager::executeEvents();
    // DEVICE YIELD
    // This must be called  when you wish the manager to check for discardable
    // resources.  Resources will only be swapped out if the maximum allowable
    // limit has been reached, and it will discard them from lowest to highest
    // priority, determined by the resource class < operator.  Function will
    // fail if requested memory cannot be freed.
    // The question is should this function be called  in every frame, well it
    // should not - other option is to create cyclic event running  once every
    // 500-1000ms or even more, something like that...
    // While function checks for overallocation it will also release every resource
    // that is no longer needed regardless of the actual overallocation - resources
    // can be tagged for deletion when no longer needed (eg. new map/level is loaded)
    //FG_ResourceManager->checkForOverallocation();

    // special callbacks for update - at the end
    executeEvent(event::UPDATE_SHOT, (void*)this);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CEngineMain::gameTouchHandler(event::CArgumentList* argv) {
    if(!argv)
        return FG_FALSE;
    event::SEvent* pEvent = (event::SEvent *)argv->getValueByID(0);
    if(!pEvent)
        return FG_FALSE;
    event::EventType type = pEvent->code;
    if(this->m_gfxMain) {
        if(type == event::TOUCH_MOTION) {
            event::STouch *touch = (event::STouch *)pEvent;
            this->m_gfxMain->get3DScene()->reportSelectionMove(touch->x, touch->y);
            this->m_gfxMain->get2DScene()->reportSelectionMove(touch->x, touch->y);
        } else if(type == event::TOUCH_PRESSED) {
            this->m_gfxMain->get3DScene()->reportSelectionClick(FG_TRUE);
            this->m_gfxMain->get2DScene()->reportSelectionClick(FG_TRUE);
        } else if(type == event::TOUCH_RELEASED) {

            this->m_gfxMain->get3DScene()->reportSelectionClick(FG_FALSE);
            this->m_gfxMain->get2DScene()->reportSelectionClick(FG_FALSE);
        }
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CEngineMain::gameMouseHandler(event::CArgumentList* argv) {
    if(!argv)
        return FG_FALSE;
    event::SEvent* pEvent = (event::SEvent *)argv->getValueByID(0);
    if(!pEvent)
        return FG_FALSE;
    event::EventType type = pEvent->code;
    if(this->m_gfxMain) {
        if(type == event::MOUSE_MOTION) {
            event::SMouse *mouse = (event::SMouse *)pEvent;
            this->m_gfxMain->get3DScene()->reportSelectionMove(mouse->x, mouse->y);
            this->m_gfxMain->get2DScene()->reportSelectionMove(mouse->x, mouse->y);
        } else if(type == event::MOUSE_PRESSED) {
            this->m_gfxMain->get3DScene()->reportSelectionClick(FG_TRUE);
            this->m_gfxMain->get2DScene()->reportSelectionClick(FG_TRUE);
        } else if(type == event::MOUSE_RELEASED) {

            this->m_gfxMain->get3DScene()->reportSelectionClick(FG_FALSE);
            this->m_gfxMain->get2DScene()->reportSelectionClick(FG_FALSE);
        }
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CEngineMain::gameFreeLookHandler(event::CArgumentList* argv) {
    if(!argv || !this->m_gfxMain)
        return FG_FALSE;
    if(!this->m_gfxMain->get3DSceneCamera())
        return FG_FALSE;
    event::SEvent* pEvent = (event::SEvent*)argv->getValueByID(0);
    if(!pEvent)
        return FG_FALSE;
    if(!fg::g_DebugConfig.gameFreeLook)
        return FG_FALSE;
    event::EventType type = pEvent->code;
    int xRel = 0, yRel = 0, x = 0, y = 0;
    fgBool pressed = FG_FALSE;

    // #FIXME - camera free management
    if(type == event::TOUCH_MOTION ||
       type == event::TOUCH_PRESSED ||
       type == event::TOUCH_RELEASED) {
        event::STouch *touch = (event::STouch *)pEvent;
        x = touch->x;
        y = touch->y;
        xRel = touch->relX;
        yRel = touch->relY;
        pressed = touch->pressed;
        if(touch->touchID > FG_POINTER_BUTTON_SELECT)
            return FG_TRUE;
    } else if(type == event::MOUSE_MOTION ||
              type == event::MOUSE_PRESSED ||
              type == event::MOUSE_RELEASED) {
        event::SMouse *mouse = (event::SMouse *)pEvent;
        x = mouse->x;
        y = mouse->y;
        xRel = mouse->relX;
        yRel = mouse->relY;
        pressed = mouse->pressed;
        if(mouse->buttonID > FG_POINTER_BUTTON_SELECT)
            return FG_TRUE;
    } else {
        return FG_FALSE;
    }

    if(pressed)
        this->m_gfxMain->get3DSceneCamera()->update((float)xRel, (float)yRel);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CEngineMain::gameKeyboardHandler(event::CArgumentList* argv) {
    if(!argv || !this->m_gfxMain)
        return FG_FALSE;
    event::SEvent* pEvent = (event::SEvent*)argv->getValueByID(0);
    if(!pEvent)
        return FG_FALSE;
    event::SKey* pKey = (event::SKey*)pEvent;
    if(pKey->eventType == event::KEY_PRESSED) {
        if(pKey->keyCode == event::FG_KEY_1) {
            FG_LOG_DEBUG("GFX SUSPEND FORCED!\n");
            this->m_gfxMain->suspendGFX();
        }
        if(pKey->keyCode == event::FG_KEY_2) {
            FG_LOG_DEBUG("GFX RESUME FORCED!\n");
            this->m_gfxMain->resumeGFX();
        }
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------
