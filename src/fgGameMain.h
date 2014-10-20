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
    #include "fgStatusReporter.h"
    #include "Util/fgSettings.h"
    #include "Util/fgConfig.h"
    #include "Util/fgTag.h"
    #include "Resource/fgResourceManager.h"
    #include "Resource/fgResourceFactory.h"
    #include "Input/fgPointerInputReceiver.h"
    #include "Input/fgJoypadController.h"

    #include "GFX/fgGFXMain.h"
    #include "GUI/fgGuiMain.h"

class fgGameMain;
    #define FG_TAG_GAME_MAIN_NAME		"GameMain"
    #define FG_TAG_GAME_MAIN			FG_TAG_TYPE(fgGameMain)
FG_TAG_TEMPLATE_ID_AUTO(fgGameMain, FG_TAG_GAME_MAIN_NAME);
typedef FG_TAG_GAME_MAIN fgGameMainTag;

/*
 *
 */
class fgGameMain : public fgStatusReporter<fgGameMainTag> {
public:
    // Default constructor for the Game Main object
    fgGameMain(fgEventManager* eventMgr = NULL);
    // Default destructor for the Game Main object
    virtual ~fgGameMain();

protected:
    //
    void registerGameCallbacks(void);
    //
    void unregisterGameCallbacks(void);
    
public:
    
    // This needs to be called first before everything else.
    // Function creates and initializes subsystems
    fgBool initSubsystems(void);

    // Loads main configuration files determining the next steps
    // of game initialization
    fgBool loadConfiguration(void);

    // Loads resources specified in configuration files (pre load phase ?)
    fgBool loadResources(void);

    // Unloads, frees and deletes all data from fgResourceManager subsystem
    fgBool releaseResources(void);

    // This frees the subsystems - simply deletes all singleton instances 
    // (every main subsystem is a singleton) #FIXME #KILLALLSINGLETONS
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

    //
    inline fgGfxMain *getGfxMain(void) const {
        return m_gfxMain;
    }
    
    //
    inline fgGuiMain *getGuiMain(void) const {
        return m_guiMain;
    }

    //
    inline fgSettings *getSettings(void) const {
        return m_settings;
    }

    //
    inline fgConfig *getMainConfig(void) const {
        return m_mainConfig;
    }

    //
    inline fgResourceManager *getResourceManager(void) const {
        return m_resourceMgr;
    }

    //
    inline fgEventManager *getEventManager(void) const {
        return m_eventMgr;
    }

    //
    void setEventManager(fgEventManager *eventMgr);

    //
    inline fgPointerInputReceiver *getPointerInputReceiver(void) const {
        return m_pointerInputReceiver;
    }
    
    //
    inline fgJoypadController *getJoypadController(void) const {
        return m_joypadController;
    }
    
    //
    fgBool gameTouchHandler(fgArgumentList *argv);
    //
    fgBool gameMouseHandler(fgArgumentList *argv);
    //
    fgBool gameFreeLookHandler(fgArgumentList *argv);

private:
    /// 
    fgGfxMain *m_gfxMain;
    ///
    fgGuiMain *m_guiMain;
    /// 
    fgSettings *m_settings;
    /// 
    fgConfig *m_mainConfig;
    ///
    fgResourceManager *m_resourceMgr;
    ///
    fgResourceFactory *m_resourceFactory;
    ///
    fgEventManager *m_eventMgr;
    ///
    fgPointerInputReceiver *m_pointerInputReceiver;
    ///
    fgJoypadController *m_joypadController;
    
    ///
    fgFunctionCallback *m_gameTouchCallback;
    ///
    fgFunctionCallback *m_gameMouseCallback;
    ///
    fgFunctionCallback *m_gameFreeLookCallback;
};

#endif /* _FG_GAME_MAIN_H_ */
