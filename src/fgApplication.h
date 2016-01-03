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
 * File:   fgApplication.h
 * Author: vigilant
 *
 * Created on January 3, 2016, 1:32 AM
 */

#ifndef FG_INC_APPLICATION
    #define FG_INC_APPLICATION
    #define FG_INC_APPLICATION_BLOCK

    #include "fgBool.h"
    #ifndef NULL
        #ifndef __cplusplus
            #define NULL ((void *)0)
        #else
            #define NULL 0
        #endif
    #endif
    
namespace fg {

    class CEngineMain;

    /**
     *
     */
    class CApplication {
    public:
        typedef CApplication self_type;
        typedef CApplication type;

    public:
        /**
         * 
         * @param argc
         * @param argv
         */
        CApplication(int argc, char *argv[]) :
        m_argc(argc),
        m_argv(argv),
        m_appInit(FG_FALSE),
        m_slow(FG_FALSE),
        m_isExit(FG_FALSE),
        m_isSuspend(FG_FALSE),
        m_isFrameFreeze(FG_FALSE),
        m_isMultithread(FG_FALSE),
        m_engineMain(NULL) { }
        /**
         * 
         */
        virtual ~CApplication() {
            m_isExit = FG_FALSE;
            m_appInit = FG_FALSE;
            m_engineMain = NULL;
        }

    private:
        CApplication(const CApplication& orig) { }

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
        fgBool isMultithread(void) const {
            return m_isMultithread;
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
        fgBool initProgram(void);
        fgBool mainLoopStep(void);
        void closeProgram(void);

    protected:
        virtual fgBool customPreInitStep(void) = 0;
        virtual void customPostInitStep(void) = 0;

        virtual void customPreLoopStep(void) = 0;
        virtual void customPostLoopStep(void) = 0;

        virtual void customPreQuitStep(void) = 0;
        virtual void customPostQuitStep(void) = 0;

    protected:
        /**
         * DEVICE pause event
         */
        virtual void suspendGfxEvent(void);
        /**
         * DEVICE un-pause event
         */
        virtual void resumeGfxEvent(void);
        /**
         * DEVICE PAUSE event - focus lost
         * (not the GL pause event)
         */
        virtual void focusLostEvent(void) { }
        /**
         * DEVICE un-pause event - focus gained
         * (not the GL un-pause event)
         */
        virtual void focusGainedEvent(void) { }

    protected:
        /// Number of arguments passed to program
        int m_argc;
        /// Array of arguments passed to program
        char** m_argv;
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
        ///
        fgBool m_isMultithread;
        /// Game main class - this is for initialization procedures        
        fg::CEngineMain* m_engineMain;
    }; // class CApplication

} // namespace fg

    #undef FG_INC_APPLICATION_BLOCK
#endif /* FG_INC_APPLICATION */
