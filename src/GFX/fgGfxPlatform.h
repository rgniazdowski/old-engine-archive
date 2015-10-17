/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_PLATFORM
    #define FG_INC_GFX_PLATFORM
    #define FG_INC_GFX_PLATFORM_BLOCK

    #include "fgGfxContext.h"

namespace fg {
    namespace gfx {

        /**
         *
         */
        class CPlatform {
        protected:
            /**
             * 
             */
            CPlatform();
            /**
             * 
             */
            virtual ~CPlatform();

        public:
            /**
             * 
             * @param reinit
             * @return 
             */
            static fgBool initialize(fgBool reinit = FG_FALSE);
            /**
             * 
             * @return 
             */
            static fgBool quit(fgBool suspend = FG_FALSE);

            /**
             * 
             * @return 
             */
            static fgBool isInit(void);

            /**
             * 
             * @return 
             */
            static void* getDefaultDisplay(void);
            /**
             * 
             * @return 
             */
            static void *getDefaultConfig(void);

    #if defined(FG_USING_SDL2)
            // initializing main context with sdl window
            static fgBool initializeMainContext(SDL_Window* sdlWindow);
    #endif
        private:
    #if defined FG_USING_EGL

            struct fgEGLCfgAttrib {
                EGLint id; // enumeration id value
                const char *enumName;
                const char *comment;
                EGLint value;
            };
            static void _eglDumpConfig(EGLDisplay display, EGLConfig config);
    #endif

        private:
            /// Is platform initialized?
            static fgBool m_init;
            /// Default display pointer 
            static void* m_defaultDisplay; // it's for egl only...    
            /// Default config pointer
            static void* m_defaultConfig; // it's for egl only...
        }; // class CPlatform

    } // namespace gfx
} // namespace fg

    #undef FG_INC_GFX_PLATFORM_BLOCK
#endif /* FG_INC_GFX_PLATFORM */
