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
#include "GUI/Font/fgFontBuiltIn.h"

#include "fgColors.h"

/*
 * Default constructor for the Game Main object
 */
fgGameMain::fgGameMain(fgEventManager* pEventMgr) :
m_gfxMain(NULL),
m_guiMain(NULL),
m_settings(NULL),
m_mainConfig(NULL),
m_qualityMgr(NULL),
m_resourceMgr(NULL),
m_resourceFactory(NULL),
m_pEventMgr(NULL),
m_pointerInputReceiver(NULL),
m_gameTouchCallback(NULL),
m_gameMouseCallback(NULL),
m_gameFreeLookCallback(NULL) {
    // #FIXME srand init ?
    srand(time(NULL));
    // #FIXME error codes registry place
    fgErrorCodes::registerAll();
    // Initialize colors here?
    fgColors::initialize();
    // #FIXME - getcwd / get exec path / paths management / etc
    FG_MessageSubsystem->initialize(); // ? #FIXME message subsystem
    FG_MessageSubsystem->setLogPaths("all.log", "error.log", "debug.log");
    fgTime::init(); // #FIXME global time init?
    m_pointerInputReceiver = new fgPointerInputReceiver();
    m_joypadController = new fgJoypadController();
    if(pEventMgr) {
        this->setEventManager(pEventMgr);
    }
    m_joypadController->initialize(); // #FIXME

}

/*
 * Default destructor for the Game Main object
 */
fgGameMain::~fgGameMain() {
    unregisterGameCallbacks();
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
    if(m_gameTouchCallback)
        delete m_gameTouchCallback;
    if(m_gameMouseCallback)
        delete m_gameMouseCallback;
    if(m_gameFreeLookCallback)
        delete m_gameFreeLookCallback;
    m_gameMouseCallback = NULL;
    m_gameTouchCallback = NULL;
    m_gameFreeLookCallback = NULL;
    m_joypadController = NULL;
    if(m_qualityMgr)
        delete m_qualityMgr;
    m_qualityMgr = NULL;            
    // this event mgr is not owned by game main
    m_pEventMgr = NULL;
    if(m_guiMain) {
        delete m_guiMain;
    }
    m_guiMain = NULL;
    fgColors::freeColors();
    fgErrorCodes::unregisterAll();
    FG_MessageSubsystem->deleteInstance();
}

/*
 *
 */
void fgGameMain::registerGameCallbacks(void) {
    if(!m_pEventMgr)
        return;

    if(!m_gameTouchCallback)
        m_gameTouchCallback = new fgClassCallback<fgGameMain>(this, &fgGameMain::gameTouchHandler);

    m_pEventMgr->addEventCallback(FG_EVENT_TOUCH_PRESSED, m_gameTouchCallback);
    m_pEventMgr->addEventCallback(FG_EVENT_TOUCH_RELEASED, m_gameTouchCallback);
    m_pEventMgr->addEventCallback(FG_EVENT_TOUCH_MOTION, m_gameTouchCallback);
    m_pEventMgr->addEventCallback(FG_EVENT_TOUCH_TAP_FINISHED, m_gameTouchCallback);

    if(!m_gameMouseCallback)
        m_gameMouseCallback = new fgClassCallback<fgGameMain>(this, &fgGameMain::gameMouseHandler);

    m_pEventMgr->addEventCallback(FG_EVENT_MOUSE_PRESSED, m_gameMouseCallback);
    m_pEventMgr->addEventCallback(FG_EVENT_MOUSE_RELEASED, m_gameMouseCallback);
    m_pEventMgr->addEventCallback(FG_EVENT_MOUSE_MOTION, m_gameMouseCallback);

    if(!m_gameFreeLookCallback)
        m_gameFreeLookCallback = new fgClassCallback<fgGameMain>(this, &fgGameMain::gameFreeLookHandler);

    m_pEventMgr->addEventCallback(FG_EVENT_TOUCH_PRESSED, m_gameFreeLookCallback);
    m_pEventMgr->addEventCallback(FG_EVENT_TOUCH_RELEASED, m_gameFreeLookCallback);
    m_pEventMgr->addEventCallback(FG_EVENT_TOUCH_MOTION, m_gameFreeLookCallback);
    m_pEventMgr->addEventCallback(FG_EVENT_TOUCH_TAP_FINISHED, m_gameFreeLookCallback);
    m_pEventMgr->addEventCallback(FG_EVENT_MOUSE_PRESSED, m_gameFreeLookCallback);
    m_pEventMgr->addEventCallback(FG_EVENT_MOUSE_RELEASED, m_gameFreeLookCallback);
    m_pEventMgr->addEventCallback(FG_EVENT_MOUSE_MOTION, m_gameFreeLookCallback);
}

/*
 *
 */
void fgGameMain::unregisterGameCallbacks(void) {
    if(!m_pEventMgr)
        return;

    m_pEventMgr->removeEventCallback(FG_EVENT_TOUCH_PRESSED, m_gameTouchCallback);
    m_pEventMgr->removeEventCallback(FG_EVENT_TOUCH_RELEASED, m_gameTouchCallback);
    m_pEventMgr->removeEventCallback(FG_EVENT_TOUCH_MOTION, m_gameTouchCallback);
    m_pEventMgr->removeEventCallback(FG_EVENT_TOUCH_TAP_FINISHED, m_gameTouchCallback);

    m_pEventMgr->removeEventCallback(FG_EVENT_MOUSE_PRESSED, m_gameMouseCallback);
    m_pEventMgr->removeEventCallback(FG_EVENT_MOUSE_RELEASED, m_gameMouseCallback);
    m_pEventMgr->removeEventCallback(FG_EVENT_MOUSE_MOTION, m_gameMouseCallback);

    m_pEventMgr->removeEventCallback(FG_EVENT_TOUCH_PRESSED, m_gameFreeLookCallback);
    m_pEventMgr->removeEventCallback(FG_EVENT_TOUCH_RELEASED, m_gameFreeLookCallback);
    m_pEventMgr->removeEventCallback(FG_EVENT_TOUCH_MOTION, m_gameFreeLookCallback);
    m_pEventMgr->removeEventCallback(FG_EVENT_TOUCH_TAP_FINISHED, m_gameFreeLookCallback);
    m_pEventMgr->removeEventCallback(FG_EVENT_MOUSE_PRESSED, m_gameFreeLookCallback);
    m_pEventMgr->removeEventCallback(FG_EVENT_MOUSE_RELEASED, m_gameFreeLookCallback);
    m_pEventMgr->removeEventCallback(FG_EVENT_MOUSE_MOTION, m_gameFreeLookCallback);
}

/**
 * 
 * @param eventMgr
 */
void fgGameMain::setEventManager(fgEventManager *pEventMgr) {
    if(!pEventMgr) {
        unregisterGameCallbacks();
    } else if(m_pEventMgr && m_pEventMgr != pEventMgr) {
        unregisterGameCallbacks();
    }
    m_pEventMgr = pEventMgr;
    if(m_pointerInputReceiver)
        m_pointerInputReceiver->setEventManager(m_pEventMgr);
    if(m_joypadController)
        m_joypadController->setEventManager(m_pEventMgr);
    if(m_guiMain) {
        m_guiMain->setEventManager(m_pEventMgr);
        m_guiMain->setPointerInputReceiver(m_pointerInputReceiver);
    }
    if(m_resourceMgr) {
        m_resourceMgr->setEventManager(pEventMgr);
    }
    if(m_pEventMgr) {
        registerGameCallbacks();
    }
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
    m_guiMain->setScreenSize(w, h);
    FG_HardwareState->setScreenDimensions(w, h);
    FG_HardwareState->initDPI();
    if(!m_qualityMgr)
        m_qualityMgr = new fgQualityManager(w * h);
    if(m_pointerInputReceiver)
        m_pointerInputReceiver->initialize();
    if(!m_resourceFactory)
        m_resourceFactory = new fgResourceFactory();
    else
        m_resourceFactory->clear();
    m_resourceFactory->registerResource(FG_RESOURCE_TEXTURE, &fgTextureResource::createResource);
    m_resourceFactory->registerResource(FG_RESOURCE_FONT, &fgFontResource::createResource);
    m_resourceFactory->registerResource(FG_RESOURCE_GROUP, &fgResourceGroup::createResource);
    m_resourceFactory->registerResource(FG_RESOURCE_3D_MODEL, &fgGfxModelResource::createResource);
    m_resourceFactory->registerResource(FG_RESOURCE_PARTICLE_EFFECT, &fgParticleEffect::createResource);
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
    if(!m_resourceMgr)
        m_resourceMgr = new fgResourceManager(m_resourceFactory, m_qualityMgr, m_pEventMgr);
#ifdef FG_USING_MARMALADE
    m_resourceMgr->setMaximumMemory(s3eMemoryGetInt(S3E_MEMORY_FREE) - 1024 * 1024 * 10); // minus 10MB for the structures and other overheads
    m_resourceMgr->initialize();
#else
    m_resourceMgr->setMaximumMemory(128 * 1024 * 1024 - 1024 * 1024 * 10); // #FIXME #TODO
    m_resourceMgr->initialize();
#endif // FG_USING_MARMALADE

    // Setup GFX Main external pointers
    m_gfxMain->setResourceManager(m_resourceMgr);
    // Setup GUI Main external pointers
    m_guiMain->setResourceManager(m_resourceMgr);
    m_guiMain->setShaderManager(m_gfxMain->getShaderManager());
    m_guiMain->setPointerInputReceiver(m_pointerInputReceiver);
    if(m_pEventMgr) {
        m_guiMain->setEventManager(m_pEventMgr);
        m_pointerInputReceiver->setEventManager(m_pEventMgr);
        m_resourceMgr->setEventManager(m_pEventMgr);
    }
    // When GUI MAIN has set the resource manager - it can preload builtin fonts
    if(!m_guiMain->initialize()) {
        FG_LOG::PrintError("GUI: Main module initialized with errors");
    }
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...

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
    std::string texname;
    fgTextureResource *texture = NULL;

    ////////////////////////////////////////////////////////////////////////////
    m_gfxMain->getShaderManager()->setShadersPath("shaders/");
    m_gfxMain->preLoadShaders();
    std::string sPlainEasyShaderName("sPlainEasy");
    fgGfxShaderProgram *program = m_gfxMain->getShaderManager()->get(sPlainEasyShaderName);
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
    FG_LOG::PrintDebug("Will now try to compile and link 'sPlainEasy' shader program");
    if(program) {
        program->compile();
        program->link(); // this will also bind attributes and after successful link - bind uniforms
    }
    {
        std::string sOrthoEasyShaderName("sOrthoEasy");
        fgGfxShaderProgram *program = m_gfxMain->getShaderManager()->get(sOrthoEasyShaderName);
        FG_HardwareState->deviceYield(0); // #FIXME - device yield...
        FG_LOG::PrintDebug("Will now try to compile and link 'sOrthoEasyShader' shader program");
        if(program) {
            program->compile();
            program->link(); // this will also bind attributes and after successful link - bind uniforms
        }
    }
    FG_HardwareState->deviceYield(0); // #FIXME - device yield...
#if 1
    ////////////////////////////////////////////////////////////////////////////
    {
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
    }
    ////////////////////////////////////////////////////////////////////////////
#endif
    {
        FG_LOG::PrintDebug("Will now try load texture for CobraBomber");
        texname = "CobraBomberTexture";
        texture = (fgTextureResource *)m_resourceMgr->get(texname);
        if(texture) {
            texture->create();
            m_gfxMain->getTextureManager()->uploadToVRAM(texture, FG_TRUE);
        }
    }
    {
        texname = "MainBackgroundTexture";
        texture = (fgTextureResource *)m_resourceMgr->get(texname);
        //texture = (fgTextureResource *) m_resourceMgr->request(std::string("loading_screen0"), FG_RESOURCE_TEXTURE);
        if(texture) {
            texture->create();
            m_gfxMain->getTextureManager()->uploadToVRAM(texture, FG_TRUE);
        }
    }
    {
        texname = "PopupBG";
        texture = (fgTextureResource *)m_resourceMgr->get(texname);
        if(texture) {
            texture->create();
            m_gfxMain->getTextureManager()->uploadToVRAM(texture, FG_TRUE);
        }
    }
    {
        texname = "MenuBG";
        texture = (fgTextureResource *)m_resourceMgr->get(texname);
        if(texture) {
            texture->create();
            m_gfxMain->getTextureManager()->uploadToVRAM(texture, FG_TRUE);
        }
    }
    {
        texname = "Splash";
        texture = (fgTextureResource *)m_resourceMgr->get(texname);
        if(texture) {
            texture->create();
            m_gfxMain->getTextureManager()->uploadToVRAM(texture, FG_TRUE);
        }
    }
    {
        texname = "Loaded";
        fgFontResource *font = (fgFontResource *)m_resourceMgr->get(texname);
        if(font) {
            font->create();
            m_gfxMain->getTextureManager()->uploadToVRAM(font, FG_TRUE);

        }
    }
    ////////////////////////////////////////////////////////////////////////////
    // #FIXME #OMG #BULLSHIT detector is off the charts!
    const char * particleTex[] = {
                                  "PulseTex",
                                  "DebrisSheetTex",
                                  "FlameSheetTex",
                                  "FlashSheetTex",
                                  "SmokeTrailTex",
                                  "RoundSparkTex",
                                  "ShockWaveTex",
                                  "SparkTex",
                                  "ExplosionSeqTex",
                                  "FireSequenceTex"
    };
    int n = 10;
    for(int i = 0; i < n; i++) {
        texname = particleTex[i];
        texture = (fgTextureResource *)m_resourceMgr->get(texname);
        if(texture) {
            texture->create();
            m_gfxMain->getTextureManager()->uploadToVRAM(texture, FG_TRUE);
        }
    }
    ////////////////////////////////////////////////////////////////////////////
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
    ////////////////////////////////////////////////////////////////////////////

    // Upload to VRAM - #FIXME
    {
        fgFontBuiltInResource *consolasBold = (fgFontBuiltInResource *)m_resourceMgr->get("StbConsolasBold");
        if(consolasBold) {
            m_gfxMain->getTextureManager()->uploadToVRAM(consolasBold, FG_TRUE);
        }
    }
    {
        fgFontBuiltInResource *courier = (fgFontBuiltInResource *)m_resourceMgr->get("StbCourier");
        if(courier) {
            m_gfxMain->getTextureManager()->uploadToVRAM(courier, FG_TRUE);
        }
    }

    m_gfxMain->getParticleSystem()->insertParticleEmitter("ExplosionEffect", "ExplosionEffect", fgVector3f(0.0f, 0.0f, 0.0f));

    m_gfxMain->getParticleSystem()->insertParticleEmitter("ExplosionDebris", "ExplosionDebris", fgVector3f(0.0f, 0.0f, 0.0f));
    m_gfxMain->getParticleSystem()->insertParticleEmitter("ExplosionFlash", "ExplosionFlash", fgVector3f(0.0f, 0.0f, 0.0f));
    m_gfxMain->getParticleSystem()->insertParticleEmitter("ExplosionRoundSparks", "ExplosionRoundSparks", fgVector3f(0.0f, 0.0f, 0.0f));
    m_gfxMain->getParticleSystem()->insertParticleEmitter("ExplosionShockwave", "ExplosionShockwave", fgVector3f(0.0f, 0.0f, 0.0f));
    m_gfxMain->getParticleSystem()->insertParticleEmitter("ExplosionSmoke", "ExplosionSmoke", fgVector3f(0.0f, 0.0f, 0.0f));
    m_gfxMain->getParticleSystem()->insertParticleEmitter("ExplosionSmokeTrails", "ExplosionSmokeTrails", fgVector3f(0.0f, 0.0f, 0.0f));
    m_gfxMain->getParticleSystem()->insertParticleEmitter("ExplosionSparks", "ExplosionSparks", fgVector3f(0.0f, 0.0f, 0.0f));
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
    FG_LOG::PrintDebug("Closing subsystems...");
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
    if(m_pEventMgr)
        m_pEventMgr->executeEvents();
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

/*
 *
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
        fgParticleEmitter *pEmitter = this->m_gfxMain->getParticleSystem()->getParticleEmitter("ExplosionEffect");
        if(pEmitter) {
            //return FG_FALSE;
            //pEmitter->addParticles(50, fgVector3f((float)touch->x, (float)touch->y, 0.0f));
        }
        {
            pEmitter = this->m_gfxMain->getParticleSystem()->getParticleEmitter("ExplosionDebris");
            if(pEmitter) {
                pEmitter->addParticles(20, fgVector3f((float)touch->x, (float)touch->y, 0.0f));
            }
        }
        {
            pEmitter = this->m_gfxMain->getParticleSystem()->getParticleEmitter("ExplosionFlash");
            if(pEmitter) {
                pEmitter->addParticles(1, fgVector3f((float)touch->x, (float)touch->y, 0.0f));
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
                pEmitter->addParticles(16, fgVector3f((float)touch->x, (float)touch->y, 0.0f));
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
                pEmitter->addParticles(32, fgVector3f((float)touch->x, (float)touch->y, 0.0f));
            }
        }

    }
    return FG_TRUE;
}

/*
 *
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

    if(type == FG_EVENT_TOUCH_MOTION ||
       type == FG_EVENT_TOUCH_PRESSED ||
       type == FG_EVENT_TOUCH_RELEASED) {
        fgTouchEvent *touch = (fgTouchEvent *)event;
        x = touch->x;
        y = touch->y;
        pressed = touch->pressed;
    } else if(type == FG_EVENT_MOUSE_MOTION ||
              type == FG_EVENT_MOUSE_PRESSED ||
              type == FG_EVENT_MOUSE_RELEASED) {
        fgMouseEvent *mouse = (fgMouseEvent *)event;
        x = mouse->x;
        y = mouse->y;
        pressed = mouse->pressed;
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

    return true;
}

#endif
