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
#include <ctime>
#include <cstring>

#if defined FG_USING_MARMALADE
#include "Hardware/fgDeviceQuery.h"
#endif // FG_USING_MARMALADE

#include "GameLogic/fgGameLogic.h"
#include "Util/fgSettings.h"
#include "Util/fgConfig.h"
#include "Hardware/fgSensors.h"
#include "Hardware/fgQualityManager.h"
#include "Hardware/fgHardwareState.h"
#include "GFX/fgGFXMain.h"
#include "GUI/fgFontResource.h"
#include "GFX/Textures/fgTextureManager.h"
#include "GFX/Particles/fgParticleSystem.h"
#include "Audio/fgSFXManager.h"
#include "Event/fgEventManager.h"
#include "Input/fgTouchReceiver.h"
#include "XML/fgXMLParser.h"
#include "Resource/fgResourceManager.h"
#include "Resource/fgResourceFactory.h"
#include "fgMessageSubsystem.h"

/*
 * Default constructor for the Game Main object
 */
fgGameMain::fgGameMain() :
	m_gfxMain(NULL),
	m_settings(NULL),
	m_mainConfig(NULL)
{
	srand(time(NULL));
}

/*
 * Default destructor for the Game Main object
 */
fgGameMain::~fgGameMain()
{
	if(m_settings)
		delete m_settings;
	m_settings = NULL;
	if(m_mainConfig)
		delete m_mainConfig;
	m_mainConfig = NULL;
	if(m_gfxMain)
		delete m_gfxMain;
	m_gfxMain = NULL;
}

/*
 * This needs to be called first before everything else.
 * Function creates and initializes subsystems
 */
fgBool fgGameMain::initSubsystems(void)
{
	if(m_gfxMain)
		return FG_FALSE;
	m_gfxMain = new fgGfxMain();
	// For other platforms need to pass some parameters
	// regarding screen resolution / full screen mode - etc
	if(!m_gfxMain->initGFX()) {
		// FIXME
		return FG_FALSE;
	}
#if defined FG_USING_MARMALADE
	FG_DeviceQuery->computeDevice();
#endif // FG_USING_MARMALADE

	int w = m_gfxMain->getScreenWidth();
	int h = m_gfxMain->getScreenHeight();

	FG_HardwareState->setScreenDimensions(w, h);
	FG_HardwareState->initDPI();

	FG_QualityManager->determineQuality();

	FG_EventManager->initialize();
	FG_TouchReceiver->initialize();

	FG_ResourceFactory->clear();
	FG_ResourceFactory->registerResource(FG_RESOURCE_TEXTURE, &fgTextureResource::createResource);
	FG_ResourceFactory->registerResource(FG_RESOURCE_FONT, &fgFontResource::createResource);
	FG_ResourceFactory->registerResource(FG_RESOURCE_GROUP, &fgResourceGroup::createResource);
	/* Useful for memory management
	s3eMemoryGetInt(S3E_MEMORY_USED);
	s3eMemoryGetInt(S3E_MEMORY_SIZE);
	s3eMemoryGetInt(S3E_MEMORY_FREE);*/
	// #FIXME - for linux/windows (non marmalade build) memory management would be useful, buckets anyone?
	// #FIXME
#ifdef FG_USING_MARMALADE
	FG_LOG::PrintDebug("MARMALADE CURRENT HEAP MEMORY: TOTAL: %.3f, FREE: %.3f, USED: %.3f, LARGEST FREE BLOCK: %.3f\n",
		(float)s3eMemoryGetInt(S3E_MEMORY_SIZE)/1024.0f/1024.0f, (float)s3eMemoryGetInt(S3E_MEMORY_FREE)/1024.0f/1024.0f, (float)s3eMemoryGetInt(S3E_MEMORY_USED)/1024.0f/1024.0f, (float)s3eMemoryGetInt(S3E_MEMORY_LFB)/1024.0f/1024.0f);
	FG_ResourceManager->setMaximumMemory(s3eMemoryGetInt(S3E_MEMORY_FREE)-1024*1024*10); // minus 10MB for the structures and other overheads
	FG_ResourceManager->initialize();
#else
    FG_ResourceManager->setMaximumMemory(128*1024*1024-1024*1024*10); // #FIXME #TODO
    FG_ResourceManager->initialize();
#endif // FG_USING_MARMALADE

	m_gfxMain->setResourceManager(FG_ResourceManager);

//	FG_GFX::setOrthoView(FG_OGL_ORTHO_ZNEAR_DEFAULT, FG_OGL_ORTHO_ZFAR_DEFAULT);
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	glShadeModel(GL_SMOOTH);
#if 0
	// FIXME well this functions should be just called elsewhere
	// also they should be wrapped - basically all functions gl* or
	// IwGL* need to be called in the OpenGL/OGL* code

	// Set the GL view port to be the entire screen
	//setViewport();

	// Texturing is enabled by default
	//glEnable(GL_TEXTURE_2D);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glShadeModel(GL_SMOOTH);
	//glClearDepthf(1.0f);

	// Ensure that Z-buffer is disabled
	//glDepthFunc(GL_ALWAYS);
	//glDisable(GL_DEPTH_TEST);
	//glDepthMask(false);

	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
#endif
	// #FIXME - this is not a place where this should be
	#if defined FG_USING_OPENGL_ES
        glClearDepthf(1.0f);
    #else
        glClearDepth(1.0f);
    #endif
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

#if 0
	fgConfig *config = new fgConfig("main.config.ini");
	config->setParameterBool("Settings.game", "programTitle", FG_TRUE);
	config->setParameterFloat("Settings.game", "defaultProfileName", 123.444555666f);
	config->setParameterInt("Settings.game", "defaultProfileNameASDASD", 1236666);
	config->setParameterString("Settings.game", "newEntry", "This is new entry. YOLO!");
	config->setParameterString("Settings.newEntry.YOLO", "YOLO1", "HAHAHAHA");
	config->save("test.new.config.ini");
	config->clearAll();
	delete config;
#endif
	return FG_TRUE;
}

/*
 * This loads main configuration files determining the next steps
 * of game initialization
 */
fgBool fgGameMain::loadConfiguration(void)
{
	// #FIXME - getcwd / get exec path / paths management / etc
	FG_MessageSubsystem->initialize(); // ?
	FG_MessageSubsystem->setLogPaths("all.log", "error.log", "debug.log");
	if(!m_settings)
		m_settings = new fgSettings();
	if(!m_settings->load("settings.xml")) { // #FIXME - universal, cross solution - path management
		return FG_FALSE;
	}
	return FG_TRUE;
}

/*
 * This loads resources specified in configuration files
 */
fgBool fgGameMain::loadResources(void)
{
	return FG_TRUE;
}

/*
 * This unloads, frees and deletes all data from fgResourceManager subsystem
 */
fgBool fgGameMain::releaseResources(void)
{
	FG_ResourceManager->destroy();
	return FG_TRUE;
}

/*
 * This frees the subsystems - simply deletes all singleton instances (every main subsystem is a singleton)
 * must be called after releaseResources
 */
fgBool fgGameMain::closeSybsystems(void)
{
	// #TODO - KILLALLSINGLETONS
	// KILL ALL SINGLETONS
	m_gfxMain->releaseTextures();

	FG_ResourceManager->deleteInstance();
	FG_HardwareState->deleteInstance();
	FG_TouchReceiver->deleteInstance();
	FG_EventManager->deleteInstance();
#if defined FG_USING_MARMALADE
	FG_DeviceQuery->deleteInstance();
#endif // FG_USING_MARMALADE
	FG_QualityManager->deleteInstance();
	FG_ResourceFactory->deleteInstance();
	FG_MessageSubsystem->deleteInstance();

	m_gfxMain->closeGFX();

	return FG_TRUE;
}

/*
 * This function releases the resources and closes the subsystems
 */
fgBool fgGameMain::quit(void)
{
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
void fgGameMain::display(void)
{
	m_gfxMain->display();
}

/*
 * Begins the proper render of the created buffers
 */
void fgGameMain::render(void)
{
	m_gfxMain->render();
}

/*
 * Update - all event handling, calling scripts, AI, game logic and etc
 * This happens for every frame (for iOS fps is hardcoded for 60, never more)
 */
void fgGameMain::update(void)
{
	FG_HardwareState->calculateDT();
	FG_HardwareState->calculateFPS();

	// TouchReceiver processes the data received from marmalade/system event
	// callbacks and throws proper events
	FG_TouchReceiver->processData();
	FG_HardwareState->deviceYield(0);
	// Well this is really useful system, in the end GUI and others will be hooked
	// to EventManager so everything what needs to be done is done in this function
	FG_EventManager->executeEvents();
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
int applicationInit(void)
{
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

/**
* End of the game, the exit from app.
*/
void applicationEnd(void)
{

	// FIXME - now that just needs fixing
	// everything (including singletons) needs to be freed in this function in proper order

	// Stop and release all audio
	fgSFXManager::getInstance()->deleteInstance();

	fgTouchReceiver::deleteInstance();
	fgQualityManager::deleteInstance();
	fgTextureManager::deleteInstance();
}

#endif
