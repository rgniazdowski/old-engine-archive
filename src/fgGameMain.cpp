/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
 *******************************************************/

#include "fgGameMain.h"

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>

#include "Graphics/fgGFXMain.h"

#include "fgSettings.h"
#include "fgResourceManager.h"
#include "Hardware/fgDeviceQuery.h"
#include "Hardware/fgSensors.h"
#include "Hardware/fgQualityManager.h"
#include "Hardware/fgHardwareState.h"
#include "Graphics/Textures/fgTextureManager.h"
#include "Audio/fgSFXManager.h"
#include "Graphics/Particles/fgParticleSystem.h"
#include "Event/fgEventManager.h"
#include "Input/fgTouchReceiver.h"
#include "GameLogic/fgGameLogic.h"
#include "fgXMLParser.h"

template <>
bool fgSingleton<fgGameMain>::instanceFlag = false;

template <>
fgGameMain *fgSingleton<fgGameMain>::instance = NULL;

fgGameMain::fgGameMain()
{
	srand(time(NULL));
}

fgGameMain::~fgGameMain()
{
}

/*
* This needs to be called first before everything else.
* Function creates and initializes subsystems
*/
bool fgGameMain::initSubsystems(void)
{
	if(!FG_GFX::initGFX()) {
		// FIXME 
		return false;
	}
	
	FG_DeviceQuery->computeDevice();
	
	int w = FG_GFX::getScreenWidth();
	int h = FG_GFX::getScreenHeight();

	FG_HardwareState->setScreenDimensions(w, h);
	FG_HardwareState->initDPI();

	FG_QualityManager->determineQuality();
	
	FG_EventManager->initialize();
	FG_TouchReceiver->initialize();
	
	/* Useful for memory management
	s3eMemoryGetInt(S3E_MEMORY_USED);
	s3eMemoryGetInt(S3E_MEMORY_SIZE);
	s3eMemoryGetInt(S3E_MEMORY_FREE);*/ 
	// FIXME
	FG_ResourceManager->setMaximumMemory(s3eMemoryGetInt(S3E_MEMORY_FREE)-1024*1024*3); // minus 3MB for the structures and other overheads

	/*fgXMLParser *parser = new fgXMLParser();

	parser->loadXML("test2.xml");
	printf("Root node name: '%s'\n", parser->getRootElementValue());
	if(parser->isXMLLoaded())
	{
		parser->goDeeper();
		do {
			printf("Roots' child node name: '%s'\n", parser->getCurrentNodeValue());
			const char *childName = parser->getCurrentNodeValue();

			// Parsing attributes
			if(parser->setFirstAttribute())
			{
				do {
					printf(" %ss' attribute '%s' value: '%s\n", childName, parser->getCurrentAttributeName(), parser->getCurrentAttributeValue());
				} while(parser->goToNextAttribute());
			}

			// Parsing children nodes
			if(parser->getCurrentNodeChildrenPresence())
			{
				parser->goDeeper();
				do {
					printf("   %ss' child node (%s) name: '%s'\n", childName, (parser->isCurrentElement() ? "ELEMENT" : "TEXT"), parser->getCurrentNodeValue());
				} while(parser->goToNextNode());
				parser->goHigher();
			}
		} while(parser->goToNextNode());
	}

	delete parser;
	parser = NULL;*/

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

	return true;
}

/*
* This loads main configuration files determining the next steps
* of game initialization
*/
bool fgGameMain::loadConfiguration(void)
{
	return true;
}

/*
* This loads resources specified in configuration files
*/
bool fgGameMain::loadResources(void)
{
	return true;
}

/*
* This unloads, frees and deletes all data from fgResourceManager subsystem
*/
bool fgGameMain::releaseResources(void)
{
	FG_ResourceManager->destroy();
	return true;
}

/*
* This frees the subsystems - simply deletes all singleton instances (every main subsystem is a singleton)
* must be called after releaseResources
*/
bool fgGameMain::closeSybsystems(void)
{
	FG_ResourceManager->deleteInstance();
	FG_HardwareState->deleteInstance();
	FG_TouchReceiver->deleteInstance();
	FG_EventManager->deleteInstance();
	FG_DeviceQuery->deleteInstance();
	FG_QualityManager->deleteInstance();

	FG_GFX::closeGFX();

	return true;
}

/*
* This function releases the resources and closes the subsystems
*/
bool fgGameMain::quit(void)
{
	bool status = true;
	if(!releaseResources())
		status = false;
	if(!closeSybsystems())
		status = false;
	return status;
}

/*
* Now main display function creates the buffer (vertex/color/texture coords buffers) to be displayed in current frame
* The real drawing of created buffers in inside the render function (which in the future should be in separate thread)
*/
void fgGameMain::display(void)
{
	// #TROLOLO
}

/*
* Begins the proper render of the created buffers
*/
void fgGameMain::render(void)
{
	// #TODO / #FIXME - all the crap with FG_GFX namespace should be somehow put into classes
	// currently the model for handling different rendering APIs sux so much its too hard
	// to put it in words - however its still not clear whether to stay with the namespace tag name
	FG_GFX::clearScreen();

	// #MARKED
	// proper rendering calls go here
	// render something and shit

	// #CRAP
	// the code below should be removed 
#if 0
	// V- & T-database INDEXES
	GLushort defaultIndices[] = { 0, 1, 3, 2 };

	float size_x = 100.0f;
	float size_y = 150.0f;

	Vector2f vertexArray[] = {
		Vector2f(0.0f, 0.0f),
		Vector2f(size_x, 0.0f),
		Vector2f(size_x, size_y),
		Vector2f(0.0f, size_y)
	};

	glLoadIdentity();
	glTranslatef(FG_GFX::getScreenWidth()/2.0f, FG_GFX::getScreenHeight()/2.0f, 0.0f);
	glRotatef((FG_GetTicks()/4)%360, 0.0f, 0.0f, 1.0f);
	// Activate and specify pointer to vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor4f(1.0f, 0.25f, 0.25f, 1.0f);
	glVertexPointer(2, GL_FLOAT, 0, (GLvoid *)vertexArray);

    // DRAW
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, defaultIndices);

	// glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	// Deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
#endif
	// After rendering swap buffers so the changes are visible on the screen
	FG_GFX::swapBuffers();
}

/*
 * Update - all event handling, calling scripts, AI, game logic and etc
 * This happens for every frame (for iOS fps is hardcoded for 60, never more)
 */
void fgGameMain::update(void)
{
	FG_HardwareState->calculateDT();
	FG_HardwareState->calculateFPS();

	// TouchReceiver processes the data received from marmalade event callbacks and throws proper events
	FG_TouchReceiver->processData();
	s3eDeviceYield(0);
	// Well this is really useful system, in the end GUI and others will be hooked to EventManager so
	// everything what needs to be done is done in this function
	FG_EventManager->executeEvents();
	s3eDeviceYield(0);
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
	FG_WriteLog("Initializing Sensors..");
	fgSensors::getInstance()->startSensors();

	// FIXME - Initialization of TouchReceiver needed :D

	// FIXME: Textures need to be loaded in different way
	// For now textures (file names etc.) are hardcoded within the source code - file names and handles should be read from XML/CSS configuration files
	// TEXTURES
	FG_WriteLog("Initializing textures..");
	if(!fgTextureManager::getInstance()->allToVRAM()) {
		FG_ErrorLog("diskToVram failed");
		return false;
	}

	// FONTS - FIXME
	/*FG_WriteLog("Initializing fonts..");
	if(!loadFonts()) {
	FG_ErrorLog("loadFonts failed");
	return false;
	}
	*/

	// FIXME - texture manager is just wrong
	// UNUSED MEMORY – after textures and fonts are uploaded to VRAM
	FG_WriteLog("Initializing releasing non-GL memory..");
	fgTextureManager::getInstance()->allReleaseNonGl();

	// AUDIO - FIXME - now that just needs a lot of fixing (personally I would just delete it and rewrote it from scratch using s3eSound)
	// actually now the Audio subsystem loads the .raw (sfx) and .mp3 (music) files
	// it needs to work like new texture subsystem - load audio file names and handles from XML files
	// also it should be dependent (like other file loading subsystems) from fgResourceManager main class
	//FG_WriteLog( "Initializing Audio.." );
	/*fgSFXManager *audio = fgSFXManager::getInstance();
	if( !audio ) {
	FG_ErrorLog( "init_audio failed" );
	return false;
	} else {
	// LOAD MUS & SFX
	FG_WriteLog( "Initializing SFX & MUS.." );
	if( !audio->loadMusFiles() || !audio->loadSfxFiles() ) {
	FG_ErrorLog( "load{Mus,Sfx}Files failed!" );
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
	//FG_WriteLog("Initializing fgParticleSystem.."); // FIXME - also all debug text messages printed to the console need to be stored in internal buffer for further processing and display (in-program console)
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