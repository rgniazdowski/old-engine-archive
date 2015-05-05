/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
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

    #include "GFX/fgGfxMain.h"
    #include "GUI/fgGuiMain.h"

    #include "Hardware/fgQualityManager.h"
    #include "Scripting/fgScriptSubsystem.h"
    #include "GameLogic/fgGameLogic.h"

namespace fg {
    class CEngineMain;
};
    #define FG_TAG_ENGINE_MAIN_NAME       "EngineMain"
    #define FG_TAG_ENGINE_MAIN            FG_TAG_TYPE(fg::CEngineMain)
FG_TAG_TEMPLATE_ID_AUTO(fg::CEngineMain, FG_TAG_ENGINE_MAIN_NAME);

namespace fg {

    /// Tag type for the GameMain class
    typedef FG_TAG_ENGINE_MAIN EngineMainTag;

    const unsigned short MAX_FIXED_FPS = 120;
    const unsigned short MIN_FIXED_FPS = 24;
    const unsigned short DEFAULT_FIXED_FPS = 60;
    const unsigned short MAX_UPDATE_FIXED_FPS = 120;
    const unsigned short MIN_UPDATE_FIXED_FPS = 48;
    const unsigned short DEFAULT_UPDATE_FIXED_FPS = 120;

    /**
     *
     */
    class CEngineMain : public event::CEventManager {
    public:
        ///
        typedef CEngineMain self_type;
        ///
        typedef CEngineMain type;
        ///
        typedef event::CEventManager base_type;
        ///
        typedef EngineMainTag tag_type;

    public:
        /**
         * Default constructor for the Game Main object
         * @param pEventMgr
         */
        CEngineMain(int argc, char **argv);
        /**
         * Default destructor for the Game Main object
         */
        virtual ~CEngineMain();

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

        /**
         * This frees the subsystems - simply deletes all singleton instances
         * (every main subsystem is a singleton) #FIXME #KILLALLSINGLETONS
         * @return
         */
        fgBool closeSybsystems(void);

        /**
         * This function releases the resources and closes the subsystems
         * @return
         */
        fgBool quit(void);

        /**
         * Now main display function creates the buffer (vertex/color/texture
         * coords buffers) to be displayed in current frame. The real drawing of
         * created buffers is inside the render function (which in the future
         * should be in separate thread)
         * @return  Returns FG_TRUE if the function was executed fully, FG_FALSE
         *          if otherwise -- meaning that not enough time has elapsed for
         *          the next execution (fixed FPS)
         */
        fgBool display(void);

        /**
         * Begins the proper render of the created buffers
         * @return  Returns FG_TRUE if the function was executed fully, FG_FALSE
         *          if otherwise -- meaning that not enough time has elapsed for
         *          the next execution (fixed FPS)
         */
        fgBool render(void);

        /**
         * Update - all event handling, calling scripts, AI, game logic and others
         * @return  Returns FG_TRUE if the function was executed fully, FG_FALSE
         *          if otherwise -- meaning that not enough time has elapsed for
         *          the next execution (fixed update - 120FPS)
         */
        fgBool update(fgBool force = FG_FALSE);

    public:
        /**
         * 
         * @return 
         */
        inline gfx::CGfxMain *getGfxMain(void) const {
            return m_gfxMain;
        }
        /**
         * 
         * @return 
         */
        inline gui::CGuiMain *getGuiMain(void) const {
            return m_guiMain;
        }
        /**
         * 
         * @return 
         */
        inline CSettings *getSettings(void) const {
            return m_settings;
        }
        /**
         * 
         * @return 
         */
        inline util::CConfig *getMainConfig(void) const {
            return m_mainConfig;
        }
        /**
         * 
         * @return 
         */
        inline resource::CResourceManager *getResourceManager(void) const {
            return m_resourceMgr;
        }
        /**
         * 
         * @return 
         */
        inline event::CEventManager *getEventManager(void) {
            return static_cast<event::CEventManager *>(this);
        }
        /**
         * 
         * @return 
         */
        inline event::CInputHandler *getInputHandler(void) const {
            return m_inputHandler;
        }
        /**
         * 
         * @return 
         */
        inline event::CJoypadController *getJoypadController(void) const {
            return m_joypadController;
        }
        /**
         * 
         * @return 
         */
        inline script::CScriptSubsystem *getScriptSubsystem(void) const {
            return m_scriptSubsystem;
        }
        /**
         * 
         * @return 
         */
        inline sfx::CSfxManager *getSoundManager(void) const {
            return m_soundMgr;
        }
        /**
         * 
         * @return 
         */
        inline game::CLogic *getLogicManager(void) const {
            return m_logicMgr;
        }

    public:
        /**
         *
         * @return
         */
        inline fgBool isFpsLocked(void) const {
            return m_isFpsLocked;
        }
        /**
         * 
         * @param toggle
         */
        inline void lockFps(fgBool toggle = FG_TRUE) {
            m_isFpsLocked = toggle;
        }
        /**
         * 
         * @return
         */
        inline unsigned short getFixedFps(void) const {
            return m_fixedFPS;
        }
        /**
         *
         * @param fixedFPS
         */
        inline void setFixedFps(unsigned short fixedFPS) {
            if(fixedFPS > MAX_FIXED_FPS) {
                fixedFPS = MAX_FIXED_FPS;
            } else if(fixedFPS < MIN_FIXED_FPS) {
                fixedFPS = MIN_FIXED_FPS;
            }
            m_fixedFPS = fixedFPS;
        }
        /**
         *
         * @return
         */
        inline unsigned short getUpdateFixedFps(void) const {
            return m_updateFixedFPS;
        }
        /**
         *
         * @param fixedFPS
         */
        inline void setUpdateFixedFps(unsigned short fixedFPS) {
            if(fixedFPS > MAX_UPDATE_FIXED_FPS) {
                fixedFPS = MAX_UPDATE_FIXED_FPS;
            } else if(fixedFPS < MIN_UPDATE_FIXED_FPS) {
                fixedFPS = MIN_UPDATE_FIXED_FPS;
            }
            m_updateFixedFPS = fixedFPS;
        }

    protected:
        /**
         * 
         * @param argv
         * @return 
         */
        fgBool gameTouchHandler(event::CArgumentList *argv);
        /**
         * 
         * @param argv
         * @return 
         */
        fgBool gameMouseHandler(event::CArgumentList *argv);
        /**
         * 
         * @param argv
         * @return 
         */
        fgBool gameFreeLookHandler(event::CArgumentList *argv);

    protected:
        /**
         * 
         * @param pEventMgr
         */
        void setEventManager(void);

    private:
        ///
        fgBool m_isFpsLocked;
        /// Fixed FPS
        unsigned short m_fixedFPS;
        /// Fixed FPS for update procedure (events)
        unsigned short m_updateFixedFPS;
        /// Number of the arguments passed to program
        int m_argc;
        /// Array of arguments passed to program
        char **m_argv;
        /// Main GFX subsystem object
        gfx::CGfxMain *m_gfxMain;
        /// Main GUI (User Interface))
        gui::CGuiMain *m_guiMain;
        /// Main, hard settings
        CSettings *m_settings;
        /// Main config 
        util::CConfig *m_mainConfig;
        /// Main Quality Manager
        CQualityManager *m_qualityMgr;
        /// Main Resource Manager
        resource::CResourceManager *m_resourceMgr;
        /// Resource factory object - registers create() methods for Resource Objects
        resource::CResourceFactory *m_resourceFactory;
        /// 
        event::CInputHandler *m_inputHandler;
        /// Joypad/Joystick controller object
        event::CJoypadController *m_joypadController;
        /// Builtin script subsystem - it needs access to all main managers
        script::CScriptSubsystem *m_scriptSubsystem;
        /// Sound manager - loading, playing sounds
        sfx::CSfxManager *m_soundMgr;
        /// Inner game logic
        game::CLogic *m_logicMgr;

        /// Callback for Touch events
        event::CFunctionCallback *m_gameTouchCallback;
        /// Callback for Mouse events
        event::CFunctionCallback *m_gameMouseCallback;
        /// Special callback for game free look (controlling camera via touch/click)
        event::CFunctionCallback *m_gameFreeLookCallback;

    };
};

    #undef FG_INC_GAME_MAIN_BLOCK
#endif /* FG_INC_GAME_MAIN */
