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
    #define FG_INC_GAME_MAIN_BLOCK

    #include "fgBuildConfig.h"
    #include "fgCommon.h"
    #include "Util/fgSettings.h"
    #include "Util/fgConfig.h"
    #include "Util/fgTag.h"
    #include "Resource/fgResourceManager.h"
    #include "Resource/fgResourceFactory.h"
    #include "Event/fgInputHandler.h"
    #include "Event/fgJoypadController.h"
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

/**
 *
 */
class fgGameMain : public fg::event::CEventManager {
public:
    ///
    typedef fgGameMainTag tag_type;

public:
    /**
     * Default constructor for the Game Main object
     * @param pEventMgr
     */
    fgGameMain(int argc, char **argv);
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

    /**
     * This needs to be called first before everything else.
     * Function creates and initializes various subsystems
     * @return  FG_TRUE if everything was initialized successfully, FG_FALSE otherwise
     */
    fgBool initSubsystems(void);

    /**
     *  Loads main configuration files determining the next steps of game initialization
     * @return 
     */
    fgBool loadConfiguration(void);

    /**
     * Loads resources specified in configuration files (pre load phase)
     * @return 
     */
    fgBool loadResources(void);

    /**
     * Unloads, frees and deletes all data from fgResourceManager subsystem
     * @return 
     */
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

    // Update - all event handling, calling scripts, AI, game logic and others
    void update(void);
    
public:
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
    inline CEventManager *getEventManager(void) {
        return static_cast<CEventManager *>(this);
    }
    /**
     * 
     * @return 
     */
    inline fg::event::CInputHandler *getInputHandler(void) const {
        return m_inputHandler;
    }
    /**
     * 
     * @return 
     */
    inline fg::event::CJoypadController *getJoypadController(void) const {
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
     * @param pEventMgr
     */
    void setEventManager(void);

private:
    /// Number of the arguments passed to program
    int m_argc;
    /// Array of arguments passed to program
    char **m_argv;
    /// Main GFX subsystem object
    fgGfxMain *m_gfxMain;
    /// Main GUI (User Interface))
    fgGuiMain *m_guiMain;
    /// Main, hard settings
    fgSettings *m_settings;
    /// Main config 
    fgConfig *m_mainConfig;
    /// Main Quality Manager
    fgQualityManager *m_qualityMgr;
    /// Main Resource Manager
    fgResourceManager *m_resourceMgr;
    /// Resource factory object - registers create() methods for Resource Objects
    fgResourceFactory *m_resourceFactory;
    /// 
    fg::event::CInputHandler *m_inputHandler;
    /// Joypad/Joystick controller object
    fg::event::CJoypadController *m_joypadController;
    /// Builtin script subsystem - it needs access to all main managers
    fgScriptSubsystem *m_scriptSubsystem;
    /// Sound manager - loading, playing sounds
    fgSFXManager *m_soundMgr;
    /// Inner game logic
    fg::game::Logic *m_logicMgr;
    
    /// Callback for Touch events
    fgFunctionCallback *m_gameTouchCallback;
    /// Callback for Mouse events
    fgFunctionCallback *m_gameMouseCallback;
    /// Special callback for game free look (controlling camera via touch/click)
    fgFunctionCallback *m_gameFreeLookCallback;
};

    #undef FG_INC_GAME_MAIN_BLOCK
#endif /* FG_INC_GAME_MAIN */
