/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GAME_MAIN
    #define FG_INC_GAME_MAIN

    #include "fgBuildConfig.h"
    #include "fgCommon.h"
    #include "Util/fgSettings.h"
    #include "Util/fgConfig.h"
    #include "Util/fgTag.h"
    #include "Resource/fgResourceManager.h"
    #include "Resource/fgResourceFactory.h"
    #include "Input/fgPointerInputReceiver.h"
    #include "Input/fgJoypadController.h"
    #include "Audio/fgSFXManager.h"

    #include "GFX/fgGFXMain.h"
    #include "GUI/fgGuiMain.h"

    #include "Hardware/fgQualityManager.h"
    #include "Scripting/fgScriptSubsystem.h"
    #include "GameLogic/fgGameLogic.h"

class fgGameMain;
    #define FG_TAG_GAME_MAIN_NAME       "GameMain"
    #define FG_TAG_GAME_MAIN            FG_TAG_TYPE(fgGameMain)
FG_TAG_TEMPLATE_ID_AUTO(fgGameMain, FG_TAG_GAME_MAIN_NAME);
typedef FG_TAG_GAME_MAIN fgGameMainTag;

/*
 *
 */
class fgGameMain {
public:
    typedef fgGameMainTag tag_type;

public:
    /**
     * Default constructor for the Game Main object
     * @param pEventMgr
     */
    fgGameMain(fgEventManager* pEventMgr);
    /**
     * Default destructor for the Game Main object
     */
    virtual ~fgGameMain();

protected:
    /**
     *
     */
    void registerGameCallbacks(void);
    /**
     * 
     */
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
    /**
     * 
     * @return 
     */
    inline fgGfxMain *getGfxMain(void) const {
        return m_gfxMain;
    }
    /**
     * 
     * @return 
     */
    inline fgGuiMain *getGuiMain(void) const {
        return m_guiMain;
    }
    /**
     * 
     * @return 
     */
    inline fgSettings *getSettings(void) const {
        return m_settings;
    }
    /**
     * 
     * @return 
     */
    inline fgConfig *getMainConfig(void) const {
        return m_mainConfig;
    }
    /**
     * 
     * @return 
     */
    inline fgResourceManager *getResourceManager(void) const {
        return m_resourceMgr;
    }
    /**
     * 
     * @return 
     */
    inline fgEventManager *getEventManager(void) const {
        return m_pEventMgr;
    }
    /**
     * 
     * @return 
     */
    inline fgPointerInputReceiver *getPointerInputReceiver(void) const {
        return m_pointerInputReceiver;
    }
    /**
     * 
     * @return 
     */
    inline fgJoypadController *getJoypadController(void) const {
        return m_joypadController;
    }
    /**
     * 
     * @return 
     */
    inline fgScriptSubsystem *getScriptSubsystem(void) const {
        return m_scriptSubsystem;
    }
    /**
     * 
     * @return 
     */
    inline fgSFXManager *getSoundManager(void) const {
        return m_soundMgr;
    }
    /**
     * 
     * @return 
     */
    inline fg::game::Logic *getLogicManager(void) const {
        return m_logicMgr;
    }

protected:
    /**
     * 
     * @param argv
     * @return 
     */
    fgBool gameTouchHandler(fgArgumentList *argv);
    /**
     * 
     * @param argv
     * @return 
     */
    fgBool gameMouseHandler(fgArgumentList *argv);
    /**
     * 
     * @param argv
     * @return 
     */
    fgBool gameFreeLookHandler(fgArgumentList *argv);

protected:
    /**
     * 
     * @param eventMgr
     */
    void setEventManager(fgEventManager *pEventMgr);

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
    fgQualityManager *m_qualityMgr;
    ///
    fgResourceManager *m_resourceMgr;
    ///
    fgResourceFactory *m_resourceFactory;
    ///
    fgEventManager *m_pEventMgr;
    ///
    fgPointerInputReceiver *m_pointerInputReceiver;
    ///
    fgJoypadController *m_joypadController;
    ///
    fgScriptSubsystem *m_scriptSubsystem;
    ///
    fgSFXManager *m_soundMgr;
    ///
    fg::game::Logic *m_logicMgr;

    ///
    fgFunctionCallback *m_gameTouchCallback;
    ///
    fgFunctionCallback *m_gameMouseCallback;
    ///
    fgFunctionCallback *m_gameFreeLookCallback;
};

#endif /* FG_INC_GAME_MAIN */
