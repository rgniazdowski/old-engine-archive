/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

/// Main include
#include "fgGameMain.h"
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
#include "GameLogic/fgGameLogic.h"
/// Resource management
#include "Resource/fgResourceManager.h"
#include "Resource/fgResourceFactory.h"
/// Hardware capabilities
#include "Hardware/fgSensors.h"
#include "Hardware/fgQualityManager.h"
#include "Hardware/fgHardwareState.h"
/// Required GFX modules
#include "GFX/fgGFXMain.h"
#include "GFX/fgGFXModelResource.h"
#include "GFX/Shaders/fgGFXShaderProgram.h"
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

/**
 * Default constructor for the Game Main object
 */
fgGameMain::fgGameMain(int argc, char **argv) :
m_argc(argc),
m_argv(argv),
m_gfxMain(NULL),
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
m_logicMgr(NULL),
m_gameTouchCallback(NULL),
m_gameMouseCallback(NULL),
m_gameFreeLookCallback(NULL) {
    if(!fg::event::CEventManager::initialize()) {

    }
    // #FIXME srand init ?
    srand(time(NULL));
    // #FIXME error codes registry place
    fgErrorCodes::registerAll();
    // Initialize colors here?
    fgColors::initialize();
    // #FIXME - getcwd / get exec path / paths management / etc
    FG_MessageSubsystem->initialize(); // ? #FIXME message subsystem
    FG_MessageSubsystem->setLogPaths("all.log", "error.log", "debug.log");
    m_inputHandler = new fg::event::CInputHandler();
    m_joypadController = new fg::event::CJoypadController(); // #FIXME - Joypad part of input receiver?
    m_scriptSubsystem = new fgScriptSubsystem();
    m_soundMgr = new fg::sfx::CSfxManager();
    this->setEventManager();
    m_joypadController->initialize(); // #FIXME
    registerGameCallbacks();
}

/**
 * Default destructor for the Game Main object
 */
fgGameMain::~fgGameMain() {
    // >> Main Game Object destruction - begin
    // Unregister any required callbacks
    unregisterGameCallbacks();
    // Main Game Logic Manager
    if(m_logicMgr)
        delete m_logicMgr;
    m_logicMgr = NULL;
    // Global Settings
    if(m_settings)
        delete m_settings;
    m_settings = NULL;
    // Main configuration file
    if(m_mainConfig)
        delete m_mainConfig;
    m_mainConfig = NULL;
    // GFX Main object
    if(m_gfxMain)
        delete m_gfxMain;
    m_gfxMain = NULL;
    m_guiMain->setShaderManager(NULL);
    // Destroy SFX/Sound manager object
    if(m_soundMgr)
        delete m_soundMgr;
    m_soundMgr = NULL;
    // Destroy Resource Manager object
    // This will also destroy any left resources
    if(m_resourceMgr)
        delete m_resourceMgr;
    m_resourceMgr = NULL;
    m_guiMain->setResourceManager(NULL);
    // Reset external pointers
    m_scriptSubsystem->setResourceManager(NULL);
    m_scriptSubsystem->setShaderManager(NULL);
    m_scriptSubsystem->set2DSceneManager(NULL);
    m_scriptSubsystem->set3DSceneManager(NULL);
    m_scriptSubsystem->setLogicManager(NULL);
    // Destroy the resource factory object
    if(m_resourceFactory)
        delete m_resourceFactory;
    m_resourceFactory = NULL;
    // Input Receiver object
    if(m_inputHandler)
        delete m_inputHandler;
    m_inputHandler = NULL;
    m_guiMain->setPointerInputReceiver(NULL);
    // Joystick Controller
    if(m_joypadController) {
        m_joypadController->quit();
        delete m_joypadController;
    }
    m_joypadController = NULL;
    // Remove any callbacks
    // They're already unregistered
    if(m_gameTouchCallback)
        delete m_gameTouchCallback;
    if(m_gameMouseCallback)
        delete m_gameMouseCallback;
    if(m_gameFreeLookCallback)
        delete m_gameFreeLookCallback;
    m_gameMouseCallback = NULL;
    m_gameTouchCallback = NULL;
    m_gameFreeLookCallback = NULL;
    // Destroy the quality manager
    if(m_qualityMgr)
        delete m_qualityMgr;
    m_qualityMgr = NULL;
    // Main GUI class 
    // Do not reset the pointer... needs it to unregister callbacks
    //m_guiMain->setEventManager(NULL);    
    if(m_guiMain) {
        delete m_guiMain;
    }
    m_guiMain = NULL;
    m_scriptSubsystem->setGuiMain(NULL);
    m_scriptSubsystem->setWidgetManager(NULL);
    m_scriptSubsystem->setStyleManager(NULL);
    // Destroy the Script Subsystem object
    delete m_scriptSubsystem;
    m_scriptSubsystem = NULL;
    // Free registered human readable colors - these are from HTML table
    fgColors::freeColors();
    // Unregister all error codes #FIXME
    fgErrorCodes::unregisterAll();
    // Delete the global instance of Message Subsystem singleton
    // MessageSubsystem is a special LOG wrapper
    FG_MessageSubsystem->deleteInstance();
    // >> Main Game object destruction - end
}

/**
 *
 */
void fgGameMain::registerGameCallbacks(void) {
    if(!m_gameTouchCallback)
        m_gameTouchCallback = new fgClassCallback<fgGameMain>(this, &fgGameMain::gameTouchHandler);

    fg::event::CEventManager::addEventCallback(FG_EVENT_TOUCH_PRESSED, m_gameTouchCallback);
    fg::event::CEventManager::addEventCallback(FG_EVENT_TOUCH_RELEASED, m_gameTouchCallback);
    fg::event::CEventManager::addEventCallback(FG_EVENT_TOUCH_MOTION, m_gameTouchCallback);
    fg::event::CEventManager::addEventCallback(FG_EVENT_TOUCH_TAP_FINISHED, m_gameTouchCallback);

    if(!m_gameMouseCallback)
        m_gameMouseCallback = new fgClassCallback<fgGameMain>(this, &fgGameMain::gameMouseHandler);

    fg::event::CEventManager::addEventCallback(FG_EVENT_MOUSE_PRESSED, m_gameMouseCallback);
    fg::event::CEventManager::addEventCallback(FG_EVENT_MOUSE_RELEASED, m_gameMouseCallback);
    fg::event::CEventManager::addEventCallback(FG_EVENT_MOUSE_MOTION, m_gameMouseCallback);

    if(!m_gameFreeLookCallback)
        m_gameFreeLookCallback = new fgClassCallback<fgGameMain>(this, &fgGameMain::gameFreeLookHandler);

    fg::event::CEventManager::addEventCallback(FG_EVENT_TOUCH_PRESSED, m_gameFreeLookCallback);
    fg::event::CEventManager::addEventCallback(FG_EVENT_TOUCH_RELEASED, m_gameFreeLookCallback);
    fg::event::CEventManager::addEventCallback(FG_EVENT_TOUCH_MOTION, m_gameFreeLookCallback);
    fg::event::CEventManager::addEventCallback(FG_EVENT_TOUCH_TAP_FINISHED, m_gameFreeLookCallback);
    fg::event::CEventManager::addEventCallback(FG_EVENT_MOUSE_PRESSED, m_gameFreeLookCallback);
    fg::event::CEventManager::addEventCallback(FG_EVENT_MOUSE_RELEASED, m_gameFreeLookCallback);
    fg::event::CEventManager::addEventCallback(FG_EVENT_MOUSE_MOTION, m_gameFreeLookCallback);
}

/**
 *
 */
void fgGameMain::unregisterGameCallbacks(void) {
    fg::event::CEventManager::removeEventCallback(FG_EVENT_TOUCH_PRESSED, m_gameTouchCallback);
    fg::event::CEventManager::removeEventCallback(FG_EVENT_TOUCH_RELEASED, m_gameTouchCallback);
    fg::event::CEventManager::removeEventCallback(FG_EVENT_TOUCH_MOTION, m_gameTouchCallback);
    fg::event::CEventManager::removeEventCallback(FG_EVENT_TOUCH_TAP_FINISHED, m_gameTouchCallback);

    fg::event::CEventManager::removeEventCallback(FG_EVENT_MOUSE_PRESSED, m_gameMouseCallback);
    fg::event::CEventManager::removeEventCallback(FG_EVENT_MOUSE_RELEASED, m_gameMouseCallback);
    fg::event::CEventManager::removeEventCallback(FG_EVENT_MOUSE_MOTION, m_gameMouseCallback);

    fg::event::CEventManager::removeEventCallback(FG_EVENT_TOUCH_PRESSED, m_gameFreeLookCallback);
    fg::event::CEventManager::removeEventCallback(FG_EVENT_TOUCH_RELEASED, m_gameFreeLookCallback);
    fg::event::CEventManager::removeEventCallback(FG_EVENT_TOUCH_MOTION, m_gameFreeLookCallback);
    fg::event::CEventManager::removeEventCallback(FG_EVENT_TOUCH_TAP_FINISHED, m_gameFreeLookCallback);
    fg::event::CEventManager::removeEventCallback(FG_EVENT_MOUSE_PRESSED, m_gameFreeLookCallback);
    fg::event::CEventManager::removeEventCallback(FG_EVENT_MOUSE_RELEASED, m_gameFreeLookCallback);
    fg::event::CEventManager::removeEventCallback(FG_EVENT_MOUSE_MOTION, m_gameFreeLookCallback);
}

/**
 * 
 * @param eventMgr
 */
void fgGameMain::setEventManager() {
    //registerGameCallbacks();
    if(m_inputHandler)
        m_inputHandler->setEventManager(this);
    if(m_joypadController)
        m_joypadController->setEventManager(this);
    if(m_guiMain) {
        m_guiMain->setEventManager(this);
        m_guiMain->setPointerInputReceiver(m_inputHandler);
    }
    if(m_resourceMgr) {
        m_resourceMgr->setEventManager(this);
    }
    if(m_scriptSubsystem) {
        m_scriptSubsystem->setEventManager(this);
    }
}

/**
 * This needs to be called first before everything else.
 * Function creates and initializes subsystems
 * @return
 */
fgBool fgGameMain::initSubsystems(void) {
    float t1 = fgTime::ms();
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
    if(m_gfxMain)
        return FG_FALSE;
    m_gfxMain = new fgGfxMain();
    if(!m_gfxMain->initGFX()) {
        return FG_FALSE;
    }
    if(!m_guiMain) {
        // Provide styles and widgets path
        std::string mainModPath = m_settings->getMainModPath();
        std::string modPath = m_settings->getCurrentModPath();
        fg::path::join(mainModPath, mainModPath, "gui");
        fg::path::join(modPath, modPath, "gui");
        std::string guiPath;
        guiPath.append(mainModPath);
        guiPath.append(";");
        guiPath.append(modPath);
        m_guiMain = new fgGuiMain(guiPath, guiPath);
    }
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
    int w = m_gfxMain->getMainWindow()->getWidth();
    int h = m_gfxMain->getMainWindow()->getHeight();
    m_guiMain->setScreenSize(w, h);
    FG_HardwareState->setScreenDimensions(w, h);
    FG_HardwareState->initDPI();
    if(!m_qualityMgr)
        m_qualityMgr = new fgQualityManager(w * h);
    if(!m_resourceFactory)
        m_resourceFactory = new fgResourceFactory();
    else
        m_resourceFactory->clear();
    m_resourceFactory->registerResource(FG_RESOURCE_TEXTURE, &fg::gfx::CTexture::createResource);
    m_resourceFactory->registerResource(FG_RESOURCE_FONT, &fgFontResource::createResource);
    m_resourceFactory->registerResource(FG_RESOURCE_GROUP, &fg::resource::CResourceGroup::createResource);
    m_resourceFactory->registerResource(FG_RESOURCE_3D_MODEL, &fg::gfx::CModelResource::createResource);
    m_resourceFactory->registerResource(FG_RESOURCE_PARTICLE_EFFECT, &fgParticleEffect::createResource);
    m_resourceFactory->registerResource(FG_RESOURCE_MUSIC, &fg::sfx::CMusic::createResource);
    m_resourceFactory->registerResource(FG_RESOURCE_SOUND, &fg::sfx::CSound::createResource);
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
    if(!m_resourceMgr)
        m_resourceMgr = new fg::resource::CResourceManager(m_resourceFactory, m_qualityMgr, this);
#if defined(FG_USING_MARMALADE)
    m_resourceMgr->setMaximumMemory(s3eMemoryGetInt(S3E_MEMORY_FREE) - 1024 * 1024 * 10); // minus 10MB for the structures and other overheads
    m_resourceMgr->initialize();
#else
    m_resourceMgr->setMaximumMemory(128 * 1024 * 1024 - 1024 * 1024 * 10); // #FIXME #TODO
    m_resourceMgr->initialize();
#endif // FG_USING_MARMALADE
    // Setup GFX Main external pointers
    m_gfxMain->setupResourceManager(m_resourceMgr);
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
    ////////////////////////////////////////////////////////////////////////////
    // Resource Manager and GFX is now fully initialized (with default shader)
    // Now is the moment to display something on screen - preload some texture
    // This will preload any required textures and upload them to the GFX
    m_gfxMain->setupLoader();
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
    m_gfxMain->getLoader()->update(0.0f);
    ////////////////////////////////////////////////////////////////////////////
    // Setup SFX manager external pointer - resource manager
    if(m_soundMgr)
        m_soundMgr->setResourceManager(m_resourceMgr);
    if(!m_soundMgr->initialize()) {
        FG_LOG_ERROR("SFX: Initialization of Sound module finished with errors");
    }
    m_gfxMain->getLoader()->update(10.0f);
    // Create object for Game Logic Manager
    if(!m_logicMgr)
        m_logicMgr = new fg::game::Logic(NULL);
    // Setup Game Logic external pointers
    if(m_logicMgr) {
        m_logicMgr->setEventManager(this);
        // Initialize the Game Logic object
        if(!m_logicMgr->initialize()) {
            FG_LOG_ERROR("Logic: Main Game Logic module initialized with errors");
        }
    }
    if(m_inputHandler)
        m_inputHandler->initialize();
    m_gfxMain->getLoader()->update(10.0f);
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
    // Setup GUI Main external pointers
    m_guiMain->setResourceManager(m_resourceMgr);
    m_guiMain->setShaderManager(m_gfxMain->getShaderManager());
    m_guiMain->setPointerInputReceiver(m_inputHandler);
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
    m_scriptSubsystem->setLogicManager(static_cast<fg::base::CManager *>(m_logicMgr));
    m_gfxMain->getLoader()->update(10.0f);
    if(!m_scriptSubsystem->initialize()) {
        FG_LOG_ERROR("Script: Initialization of Script module finished with errors");
    }
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
    float t2 = fgTime::ms();
    FG_LOG_DEBUG("Main: All subsystems initialized in %.2f seconds", (t2 - t1) / 1000.0f);
    m_gfxMain->getLoader()->update(10.0f);
    return FG_TRUE;
}

/**
 * This loads main configuration files determining the next steps
 * of game initialization
 * @return 
 */
fgBool fgGameMain::loadConfiguration(void) {
    FG_LOG_DEBUG("Loading configuration...");
    if(!m_settings)
        m_settings = new fgSettings();
    if(!m_settings->load("settings.xml")) { // #FIXME - universal, cross solution - path management
        FG_LOG_ERROR("Main: Failed to load main settings...");
        return FG_FALSE;
    }
    if(m_settings->getMainConfigPath().length()) {
        if(!m_mainConfig)
            m_mainConfig = new fgConfig();
        if(!m_mainConfig->load(m_settings->getMainConfigPathStr())) {
            FG_LOG_ERROR("Main: Failed to load main configuration file...");
            return FG_FALSE;
        }
    }
    // #FIXME
    CSimpleOpt::SOption gameOptions[] = {
        {0, "--mod", SO_REQ_SEP},
        { -1, NULL, SO_NONE}
    };

    CSimpleOpt args;
    args.Init(m_argc, m_argv, gameOptions, SO_O_NOERR | SO_O_EXACT);
    while(args.Next()) {
        switch(args.OptionId()) {
            case 0:
                if(args.OptionArg()) {
                    if(strlen(args.OptionArg())) {
                        m_settings->setCurrentModPath(args.OptionArg());
                        FG_LOG_DEBUG("SETUP: Setting new current mod path: '%s'", args.OptionArg());
                    }
                }
                break;
            default:
                break;
        };
    }
    return FG_TRUE;
}

/**
 * This loads resources specified in configuration files
 * @return
 */
fgBool fgGameMain::loadResources(void) {
    float t1 = fgTime::ms();
    FG_LOG_DEBUG("Loading resources...");
#if defined(FG_USING_LUA_PLUS)
    //LuaPlus::LuaState *state = m_scriptSubsystem->getLuaState();
    std::string mainScriptPath, modScriptPath;
    fg::path::join(mainScriptPath, m_settings->getMainModPath(), std::string("main.lua"));
    FG_LOG_DEBUG("Main: Loading and executing script file: '%s'", mainScriptPath.c_str());
    m_scriptSubsystem->executeFile(mainScriptPath);
    
    fg::path::join(modScriptPath, m_settings->getCurrentModPath(), std::string("main.lua"));
    FG_LOG_DEBUG("Main: Loading and executing script file: '%s'", modScriptPath.c_str());
    m_scriptSubsystem->executeFile(modScriptPath);
#endif
    m_gfxMain->getLoader()->update(10.0f);
    ////////////////////////////////////////////////////////////////////////////
    m_gfxMain->getShaderManager()->setShadersPath("shaders/");
    m_gfxMain->preLoadShaders();
    std::string sPlainEasyShaderName("sPlainEasy");
    fg::gfx::CShaderProgram *program = m_gfxMain->getShaderManager()->get(sPlainEasyShaderName);
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
    FG_LOG_DEBUG("Will now try to compile and link 'sPlainEasy' shader program");
    if(program) {
        // Compile all required shaders
        program->compile();
        // this will also bind attributes and after successful link - bind uniforms
        program->link();
    }
    m_gfxMain->getLoader()->update(10.0f);
    {
        std::string sOrthoEasyShaderName("sOrthoEasy");
        fg::gfx::CShaderProgram *program = m_gfxMain->getShaderManager()->get(sOrthoEasyShaderName);
        FG_HardwareState->deviceYield(0); // #FIXME - device yield...
        FG_LOG_DEBUG("Init: Will now try to compile and link 'sOrthoEasyShader' shader program");
        if(program) {
            program->compile();
            program->link(); // this will also bind attributes and after successful link - bind uniforms
        }
    }
    m_gfxMain->getLoader()->update(10.0f);
    {
        std::string sSkyBoxEasyShaderName("sSkyBoxEasy");
        fg::gfx::CShaderProgram *program = m_gfxMain->getShaderManager()->get(sSkyBoxEasyShaderName);
        FG_HardwareState->deviceYield(0); // #FIXME - device yield...
        FG_LOG_DEBUG("Init: Will now try to compile and link 'sSkyBoxEasyShader' shader program");
        if(program) {
            program->compile();
            program->link(); // this will also bind attributes and after successful link - bind uniforms
        }
    }
    m_gfxMain->getLoader()->update(10.0f);
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
#if 1
    ////////////////////////////////////////////////////////////////////////////
    // Can also create special event for GFX - upload static vertex data
    // Create vertex buffers on event - not explicitly 
    {
        float t1 = fgTime::ms();
        FG_LOG_DEBUG("Init: Will now try load object CobraBomber.obj");
        std::string modelname("CobraBomber");
        fg::gfx::CModelResource *model = (fg::gfx::CModelResource *)m_resourceMgr->get(modelname);
        float t2 = fgTime::ms();
        FG_LOG_DEBUG("WHOLE OBJECT CREATION TOOK: %.2f seconds", (t2 - t1) / 1000.0f);
    }
    FG_HardwareState->deviceYield(0);
    m_gfxMain->getLoader()->update(10.0f);
    ////////////////////////////////////////////////////////////////////////////
#endif

    m_gfxMain->getParticleSystem()->insertParticleEmitter("ExplosionDebris", "ExplosionDebris", fgVector3f(0.0f, 0.0f, 0.0f));
    m_gfxMain->getParticleSystem()->insertParticleEmitter("ExplosionFlash", "ExplosionFlash", fgVector3f(0.0f, 0.0f, 0.0f));
    m_gfxMain->getParticleSystem()->insertParticleEmitter("ExplosionRoundSparks", "ExplosionRoundSparks", fgVector3f(0.0f, 0.0f, 0.0f));
    m_gfxMain->getParticleSystem()->insertParticleEmitter("ExplosionShockwave", "ExplosionShockwave", fgVector3f(0.0f, 0.0f, 0.0f));
    m_gfxMain->getParticleSystem()->insertParticleEmitter("ExplosionSmoke", "ExplosionSmoke", fgVector3f(0.0f, 0.0f, 0.0f));
    m_gfxMain->getParticleSystem()->insertParticleEmitter("ExplosionSmokeTrails", "ExplosionSmokeTrails", fgVector3f(0.0f, 0.0f, 0.0f));
    m_gfxMain->getParticleSystem()->insertParticleEmitter("ExplosionSparks", "ExplosionSparks", fgVector3f(0.0f, 0.0f, 0.0f));
    float t2 = fgTime::ms();
    FG_LOG_DEBUG("Main: Resources loaded in %.2f seconds", (t2 - t1) / 1000.0f);
    m_gfxMain->getLoader()->update(10.0f);
#if !defined(FG_USING_MARMALADE)
    usleep(500 * 1000);
#endif
    return FG_TRUE;
}

/**
 * This unloads, frees and deletes all data from fgResourceManager subsystem
 * @return
 */
fgBool fgGameMain::releaseResources(void) {
    if(m_resourceMgr) {
        FG_LOG_DEBUG("Releasing resources...");
        return m_resourceMgr->destroy();
    }
    return FG_FALSE;
}

/**
 * This frees the subsystems - simply deletes all singleton instances (every main subsystem is a singleton)
 * must be called after releaseResources
 * @return
 */
fgBool fgGameMain::closeSybsystems(void) {
    FG_LOG_DEBUG("Closing subsystems...");
    if(m_gfxMain)
        m_gfxMain->releaseTextures();

    fgGameMain::releaseResources();
    if(m_inputHandler)
        m_inputHandler->setEventManager(NULL);
    FG_HardwareState->deleteInstance(); // #KILL_ALL_SINGLETONS
    if(m_gfxMain)
        m_gfxMain->closeGFX();

    return FG_TRUE;
}

/**
 * This function releases the resources and closes the subsystems
 * @return
 */
fgBool fgGameMain::quit(void) {
    FG_LOG_DEBUG("Game main quit requested");
    fgBool status = FG_TRUE;
    if(!releaseResources())
        status = FG_FALSE;
    if(!closeSybsystems())
        status = FG_FALSE;
    return status;
}

/**
 * Main display function creates the buffer (vertex/color/texture coords buffers) to be
 * displayed in current frame; the real drawing of created buffers is inside the render
 * function (which in the future should be in separate thread)
 */
void fgGameMain::display(void) {
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling)
        g_debugProfiling->begin("GFX::display");
#endif
    m_gfxMain->display();
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        g_debugProfiling->end("GFX::display");
        g_debugProfiling->begin("GUI::display");
    }
#endif
    m_guiMain->display();
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        g_debugProfiling->end("GUI::display");
    }
#endif
}

/**
 * Begins the proper render of the created buffers
 */
void fgGameMain::render(void) {
    // #FIXME
    static int fpsc = 0;
    if(fpsc == FG_FRAMES_COUNT_LIMIT + 2) {
        printf("# FPS: %.2f\n", FG_HardwareState->getFPS());
    }
    if(fpsc > 256) {
        fpsc = 0;
    }
    fpsc++;
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        g_debugProfiling->begin("GFX::render");
    }
#endif
    m_gfxMain->render();
    FG_HardwareState->deviceYield();
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        g_debugProfiling->end("GFX::render");
    }
#endif
    fg::gfx::CPlatform::context()->setBlend(FG_TRUE); // #FIXME
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        g_debugProfiling->begin("GUI::render");
    }
#endif
    m_guiMain->render();
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        g_debugProfiling->end("GUI::render");
    }
#endif
    fg::gfx::CPlatform::context()->setBlend(FG_FALSE); // #FIXME
    FG_HardwareState->deviceYield();
    m_gfxMain->getMainWindow()->swapBuffers();
}

/**
 * Update - all event handling, calling scripts, AI, game logic and etc
 * This happens for every frame (for iOS fps is hardcoded for 60, never more)
 */
void fgGameMain::update(void) {
    fgTime::markTick();
    FG_HardwareState->calculateDT(); // #FIXME
    FG_HardwareState->calculateFPS(); // #FIXME

    // Update logic manager
    if(m_logicMgr)
        m_logicMgr->update();
    // TouchReceiver processes the data received from marmalade/system event
    // callbacks and throws proper events
    // Pointer input receiver needs name change #FIXME - need some
    // special object for managing input - mouse / joystick / keyboard / touch
    // InputReceiver ? #FIXME
    // Also SDL events throwing needs some fixing
    if(m_inputHandler)
        m_inputHandler->processData();
    FG_HardwareState->deviceYield(0);
    // Well this is really useful system, in the end GUI and others will be hooked
    // to EventManager so everything what needs to be done is done in this function
    fg::event::CEventManager::executeEvents();
    FG_HardwareState->deviceYield(0);
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
}

/**
 * 
 * @param argv
 * @return 
 */
fgBool fgGameMain::gameTouchHandler(fgArgumentList *argv) {
    if(!argv)
        return FG_FALSE;
    fgEventBase *event = (fgEventBase *)argv->getArgumentValueByID(0);
    if(!event)
        return FG_FALSE;
    fgEventType type = event->eventType;
    if(type == FG_EVENT_TOUCH_TAP_FINISHED && this->m_gfxMain) {

        fgTouchEvent *touch = (fgTouchEvent *)event;
        fgParticleEmitter *pEmitter = NULL;
        {
            pEmitter = this->m_gfxMain->getParticleSystem()->getParticleEmitter("ExplosionDebris");
            if(pEmitter) {
                pEmitter->addParticles(20, fgVector3f((float)touch->x, (float)touch->y, 0.0f));
            }
        }
        {
            pEmitter = this->m_gfxMain->getParticleSystem()->getParticleEmitter("ExplosionFlash");
            if(pEmitter) {
                pEmitter->addParticles(2, fgVector3f((float)touch->x, (float)touch->y, 0.0f));
            }
        }
        {
            pEmitter = this->m_gfxMain->getParticleSystem()->getParticleEmitter("ExplosionRoundSparks");
            if(pEmitter) {
                pEmitter->addParticles(6, fgVector3f((float)touch->x, (float)touch->y, 0.0f));
            }
        }
        {
            pEmitter = this->m_gfxMain->getParticleSystem()->getParticleEmitter("ExplosionShockwave");
            if(pEmitter) {
                pEmitter->addParticles(1, fgVector3f((float)touch->x, (float)touch->y, 0.0f));
            }
        }
        {
            pEmitter = this->m_gfxMain->getParticleSystem()->getParticleEmitter("ExplosionSmoke");
            if(pEmitter) {
                pEmitter->addParticles(20, fgVector3f((float)touch->x, (float)touch->y, 0.0f));
            }
        }
        {
            pEmitter = this->m_gfxMain->getParticleSystem()->getParticleEmitter("ExplosionSmokeTrails");
            if(pEmitter) {
                pEmitter->addParticles(32, fgVector3f((float)touch->x, (float)touch->y, 0.0f));
            }
        }
        {
            pEmitter = this->m_gfxMain->getParticleSystem()->getParticleEmitter("ExplosionSparks");
            if(pEmitter) {
                pEmitter->addParticles(48, fgVector3f((float)touch->x, (float)touch->y, 0.0f));
            }
        }
    }
    return FG_TRUE;
}

/**
 * 
 * @param argv
 * @return 
 */
fgBool fgGameMain::gameMouseHandler(fgArgumentList *argv) {
    if(!argv)
        return FG_FALSE;
    fgEventBase *event = (fgEventBase *)argv->getArgumentValueByID(0);
    if(!event)
        return FG_FALSE;
    //fgEventType type = event->eventType;
    //fgMouseEvent *mouseEvent = (fgMouseEvent *)event;
    //this->updateState();
    return FG_TRUE;
}

/**
 * 
 * @param argv
 * @return 
 */
fgBool fgGameMain::gameFreeLookHandler(fgArgumentList* argv) {
    if(!argv || !this->m_gfxMain)
        return FG_FALSE;
    if(!this->m_gfxMain->get3DSceneCamera())
        return FG_FALSE;
    fgEventBase *event = (fgEventBase *)argv->getArgumentValueByID(0);
    if(!event)
        return FG_FALSE;
    fgEventType type = event->eventType;
    static int lastx = 128000;
    static int lasty = 128000;
    int xRel = 0, yRel = 0, x = 0, y = 0;
    fgBool pressed = FG_FALSE;

    // #FIXME - camera free management
    if(type == FG_EVENT_TOUCH_MOTION ||
       type == FG_EVENT_TOUCH_PRESSED ||
       type == FG_EVENT_TOUCH_RELEASED) {
        fgTouchEvent *touch = (fgTouchEvent *)event;
        x = touch->x;
        y = touch->y;
        pressed = touch->pressed;
        if(touch->touchID > FG_POINTER_BUTTON_SELECT)
            return FG_TRUE;
    } else if(type == FG_EVENT_MOUSE_MOTION ||
              type == FG_EVENT_MOUSE_PRESSED ||
              type == FG_EVENT_MOUSE_RELEASED) {
        fgMouseEvent *mouse = (fgMouseEvent *)event;
        x = mouse->x;
        y = mouse->y;
        pressed = mouse->pressed;
        if(mouse->buttonID > FG_POINTER_BUTTON_SELECT)
            return FG_TRUE;
    } else {
        return FG_FALSE;
    }
    if(lastx > 100000 && lasty > 100000) {
        lastx = x;
        lasty = y;
    }
    xRel = -(lastx - x);
    yRel = -(lasty - y);
    lastx = x;
    lasty = y;
    if(pressed)
        this->m_gfxMain->get3DSceneCamera()->update((float)xRel, (float)yRel);
    if(type == FG_EVENT_TOUCH_RELEASED || type == FG_EVENT_MOUSE_RELEASED) {
        lastx = 128000;
        lasty = 128000;
    }
    return FG_TRUE;
}
