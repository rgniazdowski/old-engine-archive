/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgBuildConfig.h"
#include "fgCommon.h"
#include "fgGameMain.h"

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>

#if defined FG_USING_MARMALADE
#include "Hardware/fgDeviceQuery.h"
#endif // FG_USING_MARMALADE

#include "Util/fgSettings.h"
#include "Util/fgConfig.h"
#include "Util/fgTime.h"

#include "GameLogic/fgGameLogic.h"
#include "Resource/fgResourceManager.h"
#include "Resource/fgResourceFactory.h"

#include "Hardware/fgSensors.h"
#include "Hardware/fgQualityManager.h"
#include "Hardware/fgHardwareState.h"

#include "GFX/fgGFXMain.h"
#include "GFX/fgGFXModelResource.h"
#include "GFX/Textures/fgTextureManager.h"
#include "GFX/Particles/fgParticleSystem.h"
#include "GUI/Font/fgFontResource.h"

#include "Audio/fgSFXManager.h"
#include "Event/fgEventManager.h"
#include "Input/fgPointerInputReceiver.h"
#include "XML/fgXMLParser.h"

#include "fgMessageSubsystem.h"
#include "fgErrorCodes.h"

#include "GUI/Font/fgFontDrawer.h"
#include "GUI/Font/fgFontStbConsolasBold.h"
#include "GUI/Font/fgFontStbCourier.h"
#include "GUI/Font/fgFontStbCourierBold.h"
#include "GUI/Font/fgFontStbTimes.h"
#include "GUI/Font/fgFontStbArial.h"
#include "GUI/Font/fgFontStbArialBold.h"
#include "GUI/Font/fgFontBuiltIn.h"

/*
 * Default constructor for the Game Main object
 */
fgGameMain::fgGameMain(fgEventManager* eventMgr) :
m_gfxMain(NULL),
m_guiMain(NULL),
m_settings(NULL),
m_mainConfig(NULL),
m_resourceMgr(NULL),
m_resourceFactory(NULL),
m_eventMgr(NULL),
m_pointerInputReceiver(NULL) {
    srand(time(NULL)); // #FIXME srand init ?
    fgErrorCodes::registerAll(); // #FIXME error codes registry place
    // #FIXME - getcwd / get exec path / paths management / etc
    FG_MessageSubsystem->initialize(); // ? #FIXME message subsystem
    FG_MessageSubsystem->setLogPaths("all.log", "error.log", "debug.log");
    fgTime::init(); // #FIXME global time init?
    FG_LOG::PrintDebug("fgGameMain::fgGameMain();");
    m_pointerInputReceiver = new fgPointerInputReceiver();
    m_joypadController = new fgJoypadController();
    if(eventMgr) {
        this->setEventManager(eventMgr);
    }
    m_joypadController->initialize();
}

/*
 * Default destructor for the Game Main object
 */
fgGameMain::~fgGameMain() {
    FG_LOG::PrintDebug("BEGIN: fgGameMain::~fgGameMain();");
    if(m_settings)
        delete m_settings;
    m_settings = NULL;
    if(m_mainConfig)
        delete m_mainConfig;
    m_mainConfig = NULL;
    if(m_gfxMain)
        delete m_gfxMain;
    m_gfxMain = NULL;
    if(m_resourceMgr)
        delete m_resourceMgr;
    m_resourceMgr = NULL;
    if(m_resourceFactory)
        delete m_resourceFactory;
    m_resourceFactory = NULL;
    if(m_pointerInputReceiver)
        delete m_pointerInputReceiver;
    m_pointerInputReceiver = NULL;
    if(m_joypadController) {
        m_joypadController->quit();
        delete m_joypadController;
    }
    m_joypadController = NULL;
    m_eventMgr = NULL; // this event mgr is not owned by game main
    if(m_guiMain) {
        delete m_guiMain;
    }
    m_guiMain = NULL;
    fgErrorCodes::unregisterAll();
    FG_LOG::PrintDebug("END: fgGameMain::~fgGameMain();");
    FG_MessageSubsystem->deleteInstance();
}

#include "GFX/Shaders/fgGFXShaderProgram.h"
#include "GUI/fgGuiStyle.h"
#include "GFX/Textures/fgTextureLoader.h"

/*
 * This needs to be called first before everything else.
 * Function creates and initializes subsystems
 */
fgBool fgGameMain::initSubsystems(void) {
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
    if(m_gfxMain)
        return FG_FALSE;
    m_gfxMain = new fgGfxMain();
    if(!m_gfxMain->initGFX()) {
        return FG_FALSE;
    }
    if(!m_guiMain)
        m_guiMain = new fgGuiMain();
#if defined FG_USING_MARMALADE
    FG_DeviceQuery->computeDevice();
#endif /* FG_USING_MARMALADE */
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
    int w = m_gfxMain->getMainWindow()->getWidth();
    int h = m_gfxMain->getMainWindow()->getHeight();
    FG_HardwareState->setScreenDimensions(w, h);
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
//#if defined(FG_USING_MARMALADE)
    FG_HardwareState->initDPI();
//#endif
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
    FG_QualityManager->determineQuality();
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
    if(m_pointerInputReceiver)
        m_pointerInputReceiver->initialize();
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
    if(!m_resourceFactory)
        m_resourceFactory = new fgResourceFactory();
    else
        m_resourceFactory->clear();
    m_resourceFactory->registerResource(FG_RESOURCE_TEXTURE, &fgTextureResource::createResource);
    m_resourceFactory->registerResource(FG_RESOURCE_FONT, &fgFontResource::createResource);
    m_resourceFactory->registerResource(FG_RESOURCE_GROUP, &fgResourceGroup::createResource);
    m_resourceFactory->registerResource(FG_RESOURCE_3D_MODEL, &fgGfxModelResource::createResource);
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
    if(!m_resourceMgr)
        m_resourceMgr = new fgResourceManager(m_resourceFactory);
    else
        m_resourceMgr->setResourceFactory(m_resourceFactory);
#ifdef FG_USING_MARMALADE
    m_resourceMgr->setMaximumMemory(s3eMemoryGetInt(S3E_MEMORY_FREE) - 1024 * 1024 * 10); // minus 10MB for the structures and other overheads
    m_resourceMgr->initialize();
#else
    m_resourceMgr->setMaximumMemory(128 * 1024 * 1024 - 1024 * 1024 * 10); // #FIXME #TODO
    m_resourceMgr->initialize();
#endif // FG_USING_MARMALADE

    m_gfxMain->setResourceManager(m_resourceMgr);
    m_guiMain->setResourceManager(m_resourceMgr);
    m_guiMain->setShaderManager(m_gfxMain->getShaderManager());
    m_guiMain->setPointerInputReceiver(m_pointerInputReceiver);
    if(m_eventMgr) {
        m_guiMain->setEventManager(m_eventMgr);
        m_pointerInputReceiver->setEventManager(m_eventMgr);
    }
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...

    /////////////////////////////////////////////////////
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...

    m_gfxMain->getShaderManager()->setShadersPath("shaders/");
    m_gfxMain->preLoadShaders();
    std::string sPlainEasyShaderName("sPlainEasy");
    fgGfxShaderProgram *program = m_gfxMain->getShaderManager()->get(sPlainEasyShaderName);
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
    FG_LOG::PrintDebug("Will now try to compile and link 'sPlainEasy' shader program");
    if(program) {
        program->compile();
        program->link(); // this will also bind attributes and after successfull link - bind uniforms
    }
    {
        std::string sOrthoEasyShaderName("sOrthoEasy");
        fgGfxShaderProgram *program = m_gfxMain->getShaderManager()->get(sOrthoEasyShaderName);
        FG_HardwareState->deviceYield(0); // #FIXME - device yield...
        FG_LOG::PrintDebug("Will now try to compile and link 'sOrthoEasyShader' shader program");
        if(program) {
            program->compile();
            program->link(); // this will also bind attributes and after successfull link - bind uniforms
        }
    }
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
#if 1
    float t1 = fgTime::ms();
    FG_LOG::PrintDebug("Will now try load object CobraBomber.obj");
    std::string modelname("CobraBomber");
    fgGfxModelResource *model = (fgGfxModelResource *)m_resourceMgr->get(modelname);
    model->create();
    if(model) {
        if(model->getRefShapes().size()) {
            model->getRefShapes()[0]->mesh->genBuffers();
        }
    }
    float t2 = fgTime::ms();
    FG_LOG::PrintDebug("WHOLE OBJECT CREATION TOOK: %.2f seconds", (t2 - t1) / 1000.0f);
#endif
    FG_LOG::PrintDebug("Will now try load texture for CobraBomber");

    std::string texname("CobraBomberTexture");
    fgTextureResource *texture = (fgTextureResource *)m_resourceMgr->get(texname);
    if(texture) {
        texture->create();
        m_gfxMain->getTextureManager()->uploadToVRAM(texture, FG_TRUE);
    }

    texname = "MainBackgroundTexture";
    texture = (fgTextureResource *)m_resourceMgr->get(texname);
    //texture = (fgTextureResource *) m_resourceMgr->request(std::string("loading_screen0"), FG_RESOURCE_TEXTURE);
    if(texture) {
        texture->create();
        m_gfxMain->getTextureManager()->uploadToVRAM(texture, FG_TRUE);
    }

    texname = "PopupBG";
    texture = (fgTextureResource *)m_resourceMgr->get(texname);
    if(texture) {
        texture->create();
        m_gfxMain->getTextureManager()->uploadToVRAM(texture, FG_TRUE);
    }
    texname = "MenuBG";
    texture = (fgTextureResource *)m_resourceMgr->get(texname);
    if(texture) {
        texture->create();
        m_gfxMain->getTextureManager()->uploadToVRAM(texture, FG_TRUE);
    }
    texname = "Splash";
    texture = (fgTextureResource *)m_resourceMgr->get(texname);
    if(texture) {
        texture->create();
        m_gfxMain->getTextureManager()->uploadToVRAM(texture, FG_TRUE);
    }

    texname = "Loaded";
    fgFontResource *font = (fgFontResource *)m_resourceMgr->get("Loaded");
    if(font) {
        font->create();
        m_gfxMain->getTextureManager()->uploadToVRAM(font, FG_TRUE);

    }

    {
        std::string top("HudTopTex");
        std::string bottom("HudBottomTex");
        std::string lines("HudLinesTex");
        fgTextureResource *textop = (fgTextureResource *)m_resourceMgr->get(top);
        fgTextureResource *texbottom = (fgTextureResource *)m_resourceMgr->get(bottom);
        fgTextureResource *texlines = (fgTextureResource *)m_resourceMgr->get(lines);

        if(textop && texbottom && texlines) {
            texlines->create();
            textop->create();
            texbottom->create();
            m_gfxMain->getTextureManager()->uploadToVRAM(texlines, FG_TRUE);
            m_gfxMain->getTextureManager()->uploadToVRAM(textop, FG_TRUE);
            m_gfxMain->getTextureManager()->uploadToVRAM(texbottom, FG_TRUE);
        }
    }
    fgGuiStyle *style = new fgGuiStyle();
    style->setName("DefaultStyle");
    if(!style->load("gui/main.style.ini")) {
        printf("FAILED TO LOAD MAIN STYLE\n");

    }

    fgFontBuiltInResource *consolasBold = new fgFontBuiltInResource(fgFontBuiltIn::StbConsolasBold::getRawData(32));
    consolasBold->setName("StbConsolasBold");
    consolasBold->create();
    m_resourceMgr->insertResource(consolasBold->getRefHandle(), consolasBold);
    m_gfxMain->getTextureManager()->uploadToVRAM(consolasBold, FG_TRUE);

    fgFontBuiltInResource *courier = new fgFontBuiltInResource(fgFontBuiltIn::StbCourier::getRawData(50));
    courier->setName("StbCourier");
    courier->create();
    fgTextureLoader::saveTGA("yolo1.tga", courier->getRawData(), courier->getWidth(), courier->getHeight());
    m_resourceMgr->insertResource(courier->getRefHandle(), courier);
    m_gfxMain->getTextureManager()->uploadToVRAM(courier, FG_TRUE);

    if(!m_guiMain->getStyleManager()->insertStyle(style->getRefHandle(), style)) {
        printf("FAILED TO INSERT MAIN STYLE\n");
    }
    if(!m_guiMain->getWidgetManager()->loadStructureSheet("gui/menu.xml")) {
        printf("FAILED TO LOAD MAIN MENU STRUCTURE SHEET\n");
    }
    return FG_TRUE;
}

/*
 * This loads main configuration files determining the next steps
 * of game initialization
 */
fgBool fgGameMain::loadConfiguration(void) {
    FG_LOG::PrintDebug("Loading configuration...");
    if(!m_settings)
        m_settings = new fgSettings();
    if(!m_settings->load("settings.xml")) { // #FIXME - universal, cross solution - path management
        FG_LOG::PrintError("Failed to load main settings ...");
        return FG_FALSE;
    }
    return FG_TRUE;
}

/*
 * This loads resources specified in configuration files
 */
fgBool fgGameMain::loadResources(void) {
    FG_LOG::PrintDebug("Loading resources...");
    return FG_TRUE;
}

/*
 * This unloads, frees and deletes all data from fgResourceManager subsystem
 */
fgBool fgGameMain::releaseResources(void) {
    if(m_resourceMgr) {
        FG_LOG::PrintDebug("Releasing resources...");
        return m_resourceMgr->destroy();
    }
    return FG_FALSE;
}

/*
 * This frees the subsystems - simply deletes all singleton instances (every main subsystem is a singleton)
 * must be called after releaseResources
 */
fgBool fgGameMain::closeSybsystems(void) {
    // #TODO - KILLALLSINGLETONS
    // KILL ALL SINGLETONS
    if(m_gfxMain)
        m_gfxMain->releaseTextures();

    fgGameMain::releaseResources();
    if(m_pointerInputReceiver)
        m_pointerInputReceiver->setEventManager(NULL);
    FG_HardwareState->deleteInstance();
#if defined FG_USING_MARMALADE
    FG_DeviceQuery->deleteInstance();
#endif // FG_USING_MARMALADE
    FG_QualityManager->deleteInstance();
    if(m_gfxMain)
        m_gfxMain->closeGFX();

    return FG_TRUE;
}

/*
 * This function releases the resources and closes the subsystems
 */
fgBool fgGameMain::quit(void) {
    FG_LOG::PrintDebug("Game main quit requested");
    fgBool status = FG_TRUE;
    if(!releaseResources())
        status = FG_FALSE;
    if(!closeSybsystems())
        status = FG_FALSE;
    return status;
}

/*
 * Main display function creates the buffer (vertex/color/texture coords buffers) to be
 * displayed in current frame; the real drawing of created buffers is inside the render
 * function (which in the future should be in separate thread)
 */
void fgGameMain::display(void) {
    m_gfxMain->display();
    m_guiMain->display();
}

/*
 * Begins the proper render of the created buffers
 */
void fgGameMain::render(void) {
    m_gfxMain->render();
    fgGfxPlatform::context()->setBlend(FG_TRUE);    
    //fgGfxPlatform::context()->setDepthTest(FG_FALSE);
    m_guiMain->render();
    fgGfxPlatform::context()->setBlend(FG_FALSE);  
    //fgGfxPlatform::context()->setDepthTest(FG_TRUE);
    m_gfxMain->getMainWindow()->swapBuffers();
}

/*
 * Update - all event handling, calling scripts, AI, game logic and etc
 * This happens for every frame (for iOS fps is hardcoded for 60, never more)
 */
void fgGameMain::update(void) {
    fgTime::markTick();
    FG_HardwareState->calculateDT();
    FG_HardwareState->calculateFPS();

    // TouchReceiver processes the data received from marmalade/system event
    // callbacks and throws proper events
    if(m_pointerInputReceiver)
        m_pointerInputReceiver->processData();
    FG_HardwareState->deviceYield(0);
    // Well this is really useful system, in the end GUI and others will be hooked
    // to EventManager so everything what needs to be done is done in this function
    if(m_eventMgr)
        m_eventMgr->executeEvents();
    FG_HardwareState->deviceYield(0);
    // This must be called  when you wish the manager to check for discardable
    // resources.  Resources will only be swapped out if the maximum allowable
    // limit has been reached, and it will discard them from lowest to highest
    // priority, determined by the resource class's < operator.  Function will
    // fail if requested memory cannot be freed.
    // The question is should this function be called  in every frame, well it
    // should not - other option is to create cyclic event running  once every
    // 500-1000ms or even more, something like that...
    // While function checks for overallocation it will also release every resource
    // that is no longer needed regardless of the actual overallocation - resources
    // can be tagged for deletion when no longer needed (eg. new map/level is loaded)
    //FG_ResourceManager->checkForOverallocation();
}

#if 0

// FIXME retarded file - retarded functions

/* Game initialization.
 * @return Successful or not.
 */
int applicationInit(void) {
    srand(time(NULL));

    // FIXME
    // This function is just wrong
    // Loading procedures should look different
    // Methods used in this function are just not actual - it will look different in the end

    // Besides this function is global - it needs to be in ProgramMain class as a method.
    // Object of ProgramMain class will be created in MainModule etc.

    /// SENSORS
    FG_LOG::PrintDebug("Initializing Sensors..");
    fgSensors::getInstance()->startSensors();

    // FIXME - Initialization of TouchReceiver needed :D

    // FIXME: Textures need to be loaded in different way
    // For now textures (file names etc.) are hardcoded within the source code - file names and handles should be read from XML/CSS configuration files
    // TEXTURES
    FG_LOG::PrintDebug("Initializing textures..");
    if(!fgTextureManager::getInstance()->allToVRAM()) {
        FG_LOG::PrintError("diskToVram failed");
        return false;
    }

    // FONTS - FIXME
    /*FG_LOG::PrintDebug("Initializing fonts..");
    if(!loadFonts()) {
    FG_LOG::PrintError("loadFonts failed");
    return false;
    }
     */

    // FIXME - texture manager is just wrong
    // UNUSED MEMORY – after textures and fonts are uploaded to VRAM
    FG_LOG::PrintDebug("Initializing releasing non-GL memory..");
    fgTextureManager::getInstance()->allReleaseNonGl();

    // AUDIO - FIXME - now that just needs a lot of fixing (personally I would just delete it and rewrote it from scratch using s3eSound)
    // actually now the Audio subsystem loads the .raw (sfx) and .mp3 (music) files
    // it needs to work like new texture subsystem - load audio file names and handles from XML files
    // also it should be dependent (like other file loading subsystems) from fgResourceManager main class
    //FG_LOG::PrintDebug( "Initializing Audio.." );
    /*fgSFXManager *audio = fgSFXManager::getInstance();
    if( !audio ) {
    FG_LOG::PrintError( "init_audio failed" );
    return false;
    } else {
    // LOAD MUS & SFX
    FG_LOG::PrintDebug( "Initializing SFX & MUS.." );
    if( !audio->loadMusFiles() || !audio->loadSfxFiles() ) {
    FG_LOG::PrintError( "load{Mus,Sfx}Files failed!" );
    return false;
    }

    // PLAY SFX FILES TO MAKE THEM TRULY READY
    audio->setSfxVolume( 0.005f );
    for( int i = 0; i < fgSFXManager::SFX_COUNT; i++ ) {
    audio->play(i);
    }

    // MUSIC VOLUME
    audio->playMus( fgSFXManager::MUS_TRACK_AMBIENT1 );
    // audio->setMusVolume( g_settings_new->musicVolume() );

    // NORMAL SFX STATE - after 1 second, inside a callback
    s3eDeviceYield(0);
    audio->stopAll();
    }*/

    // FIXME - although particle system initialization is OK, particle emitters configuration needs to be loaded from XML files or Lua
    // and also textures used in particles also need to be specified within XML/Lua files for further loading/processing.

    // PARTICLE SYSTEM
    //FG_LOG::PrintDebug("Initializing fgParticleSystem.."); // FIXME - also all debug text messages printed to the console need to be stored in internal buffer for further processing and display (in-program console)
    //g_particleSystem = fgParticleSystem::getInstance(); // FIXME

    return true;
}

#endif
