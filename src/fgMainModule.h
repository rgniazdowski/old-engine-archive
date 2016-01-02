/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/* 
 * File:   fgMainModule.h
 * Author: vigilant
 *
 * Created on January 14, 2015, 7:57 AM
 */

#ifndef FG_INC_MAIN_MODULE
    #define FG_INC_MAIN_MODULE
    #define FG_INC_MAIN_MODULE_BLOCK

    #if !defined(FG_STATIC_LIBRARY)

        #include "fgBuildConfig.h"
        #include "fgCommon.h"
        #include "fgEngineMain.h"

        #include <cstdlib>
        #include <cstdio>
        #include <cmath>
        #include <map>

namespace fg {
    class CMainModule;
} // namespace fg

        #if defined(FG_USING_PLATFORM_ANDROID) && defined(FG_USING_SDL2)
extern "C" int SDL_main(int argc, char **argv);
        #else
extern "C" int main(int argc, char *argv[]);
        #endif /* FG_USING_PLATFORM_ANDROID */

namespace fg {

    /**
     *
     */
    class CMainModule {
        #if defined(FG_USING_PLATFORM_ANDROID) && defined(FG_USING_SDL2)
        friend int ::SDL_main(int argc, char **argv);
        #else
        friend int ::main(int argc, char *argv[]);
        #endif /* FG_USING_PLATFORM_ANDROID */

    public:
        /**
         * Initialize main module
         */
        CMainModule(int argc, char *argv[]);
        /**
         * 
         */
        virtual ~CMainModule();


    protected:
        #if defined(FG_USING_SDL2)

        static int SDLCALL filterSDLEvents(void* userdata, SDL_Event* event);


        static event::KeyVirtualCode translateKeyboardCode(const SDL_KeyboardEvent& event);

        /**
         * #FIXME - this needs to be maintained differently
         * - maybe add some SDL2 event watches?
         * @return 
         */
        SDL_EventType checkSDLEvents(void);
        #endif

    public:
        /**
         * 
         * @return 
         */
        fgBool isSlow(void) const {
            return m_slow;
        }
        /**
         * 
         * @return 
         */
        fgBool isExit(void) const {
            return m_isExit;
        }
        /**
         *
         * @return
         */
        fgBool isFrameFreeze(void) const {
            return m_isFrameFreeze;
        }

    private:
        /**
         * 
         * @param slow
         */
        void setSlow(fgBool slow = FG_TRUE) {
            m_slow = slow;
        }
        /**
         * 
         * @param exit
         */
        void setExit(fgBool exit = FG_TRUE) {
            m_isExit = exit;
        }
        /**
         *
         * @param freeze
         */
        void setFrameFreeze(fgBool freeze = FG_TRUE) {
            m_isFrameFreeze = freeze;
        }
    public:
        /**
         * Called when a fullscreen window with an OpenGL context
         * has been created and is ready to be used.
         * 
         * @return 
         */
        fgBool initProgram(void);
        /**
         * Applications main loop step (one thread)
         */
        fgBool mainLoopStep(void);
        /**
         * The way to exit from the application
         */
        void closeProgram(void);

    private:
        /**
         * DEVICE pause event
         */
        void suspendGfxEvent(void);
        /**
         * DEVICE un-pause event
         */
        void resumeGfxEvent(void);
        /**
         * DEVICE PAUSE event - focus lost
         * (not the GL pause event)
         */
        void focusLostEvent(void);
        /**
         * DEVICE un-pause event - focus gained
         * (not the GL un-pause event)
         */
        void focusGainedEvent(void);

    private:
        /// Number of arguments passed to program
        int m_argc;
        /// Array of arguments passed to program
        char **m_argv;
        /// Is app fully initialized?
        fgBool m_appInit;
        /// Is the device slow?
        fgBool m_slow;
        /// Is exit activated?
        fgBool m_isExit;
        ///
        fgBool m_isSuspend;
        ///
        fgBool m_isFrameFreeze;
        /// Game main class - this is for initialization procedures
        /// contains also functions for handling events, drawing, etc #TODO
        /// Needs refactoring, some level of merging within main module or
        /// changing name to fgApplication - or extending fgApplication class
        /// #TODO - support threads
        fg::CEngineMain *m_engineMain;
    }; // class CMainModule
} // namespace fg

    #endif /* !defined FG_STATIC_LIBRARY */

    #undef FG_INC_MAIN_MODULE_BLOCK
#endif /* FG_INC_MAIN_MODULE */
