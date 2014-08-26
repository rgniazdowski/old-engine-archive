/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GAME_MAIN_H_
#define _FG_GAME_MAIN_H_

#include "fgBuildConfig.h"
#include "fgCommon.h"
#include "fgSingleton.h"

#include <ctime>

#define FG_FRAMES_LIMIT		20
#define FG_MAX_FPS			60.0
#define FG_FPS_LIMIT		FG_MAX_FPS

#define FG_PKG			"unknown"
#define FG_TITLE		"unknown"

#define FG_VERSION		1.0f
#define FG_VERSION_NAME	"1.0"

/*
 *
 */
class fgGameMain : public fgSingleton<fgGameMain>
{
	friend class fgSingleton<fgGameMain>;
protected:
	// Default constructor for the Game Main object
	fgGameMain();
	// Default destructor for the Game Main object
	~fgGameMain();
public:
	
	// This needs to be called first before everything else.
	// Function creates and initializes subsystems
	fgBool initSubsystems(void);

	// Loads main configuration files determining the next steps
	// of game initialization
	fgBool loadConfiguration(void);

	// Loads resources specified in configuration files
	fgBool loadResources(void);

	// Unloads, frees and deletes all data from fgResourceManager subsystem
	fgBool releaseResources(void);

	// This frees the subsystems - simply deletes all singleton instances 
	// (every main subsystem is a singleton)
	fgBool closeSybsystems(void);

	// This function releases the resources and closes the subsystems
	fgBool quit(void);
	
	// Now main display function creates the buffer (vertex/color/texture coords buffers) 
	// to be displayed in current frame. The real drawing of created buffers is inside the
	// render function (which in the future should be in separate thread)
	void display(void);

	// Begins the proper render of the created buffers
	void render(void);
	
	// Update - all event handling, calling scripts, AI, game logic and etc
	void update(void);

};

#define FG_GameMain fgGameMain::getInstance()

#endif /* _FG_GAME_MAIN_H_ */
