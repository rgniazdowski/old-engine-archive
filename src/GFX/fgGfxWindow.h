/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_WINDOW
    #define FG_INC_GFX_WINDOW
    #define FG_INC_GFX_WINDOW_BLOCK

    #ifdef FG_INC_GFX_TYPES_BLOCK__
        #error "FG_GFX_TYPES_BLOCK constant is defined. Do not include GfxWindow inside of GfxTypes header."
    #endif

    #ifndef FG_INC_GFX_GL
        #include "fgGfxGL.h"
    #endif

namespace fg {
    namespace gfx {

        /**
         *
         */
        class CWindow {
        public:
            /**
             *
             */
            CWindow();
            /**
             * 
             * @param title
             * @param width
             * @param height
             */
            CWindow(const char *title, unsigned int width, unsigned int height);

            /**
             * 
             */
            virtual ~CWindow();

            /**
             * 
             * @param title
             * @param width
             * @param height
             * @return 
             */
            fgBool setup(const char *title, unsigned int width, unsigned int height);

            /**
             * 
             * @return 
             */
            fgBool close(void);
            /**
             * 
             * @return 
             */
            int getWidth(void) const {
                return m_width;
            }
            /**
             * 
             * @return 
             */
            int getHeight(void) const {
                return m_height;
            }
            /**
             * 
             * @return 
             */
            float getAspect(void) const {
                return (float)m_width / (float)m_height;
            }

            /**
             * 
             * @param toggle
             */
            void setFullscreen(fgBool toggle = FG_TRUE);

            /**
             * 
             * @return 
             */
            fgBool swapBuffers(void);

            /**
             * 
             */
            void clearColor(void);
            /**
             * 
             * @return 
             */
            fgBool isOpen(void) const {
                return m_isOpen;
            }

    #if defined(FG_USING_SDL2)
            SDL_Window* getSysPtr(void) const {
                return m_sdlWindow;
            }
    #elif defined(FG_USING_EGL)
            EGLSurface getSysPtr(void) const {
                return m_EGLSurface;
            }
    #else
            void *getSysPtr(void) const {
                return NULL;
            }
    #endif

        private:
            //
            fgBool refreshFS(void);

        private:
            /// 
            std::string m_title;
    #if defined FG_USING_EGL
            EGLSurface m_EGLSurface;
    #elif defined FG_USING_SDL2
            SDL_Window* m_sdlWindow;
            Uint32 m_sdlFlags;
    #endif
            /// 
            unsigned int m_width;
            /// 
            unsigned int m_height;
            ///
            fgBool m_isFullscreen;
            ///
            fgBool m_isHW;
            ///
            fgBool m_isDB;
            ///
            fgBool m_isOpen;
        };
    };
};

    #undef FG_INC_GFX_WINDOW_BLOCK
#endif /* FG_INC_GFX_WINDOW */
