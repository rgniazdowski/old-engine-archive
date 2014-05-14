#ifndef _FG_GAME_MAIN_H_
#define _FG_GAME_MAIN_H_

#include "fgCommon.h"

#include <ctime>

#define FG_FRAMES_LIMIT		20
#define FG_MAX_FPS			60.0
#define FG_FPS_LIMIT		MAX_FPS

#define FG_PKG		"unknown"
#define FG_TITLE	"unknown"

#define FG_VERSION		1.0f
#define FG_CVERSION	"1.0"

#include "fgSingleton.h"

class fgGameMain : public fgSingleton<fgGameMain>
{
	friend class fgSingleton<fgGameMain>;
protected:
	fgGameMain();
	~fgGameMain();
public:
	
	/*
	 * This needs to be called first before everything else.
	 * Function creates and initializes subsystems
	 */
	bool initSubsystems(void);

	/*
	 * This loads main configuration files determining the next steps
	 * of game initialization
	 */
	bool loadConfiguration(void);

	/*
	 * This loads resources specified in configuration files
	 */
	bool loadResources(void);

	/*
	 * This unloads, frees and deletes all data from fgResourceManager subsystem
	 */
	bool releaseResources(void);

	/*
	 * This frees the subsystems - simply deletes all singleton instances (every main subsystem is a singleton)
	 */
	bool closeSybsystems(void);

	/*
	 * This function releases the resources and closes the subsystems
	 */
	bool quit(void);
	
	/*
	 * Now main display function creates the buffer (vertex/color/texture coords buffers) to be displayed in current frame
	 * The real drawing of created buffers in inside the render function (which in the future should be in separate thread)
	 */
	void display(void);

	/*
	 * Begins the proper render of the created buffers
	 */
	void render(void);
	
	/*
	 * Update - all event handling, calling scripts, AI, game logic and etc
	 */
	void update(void);

};

#define FG_GameMain fgGameMain::getInstance()

#endif /* _FG_GAME_MAIN_H */
