/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXLoader.h
 * Author: vigilant
 *
 * Created on January 6, 2015, 11:12 PM
 */

#ifndef FG_INC_GFX_LOADER
    #define FG_INC_GFX_LOADER
    #define FG_INC_GFX_LOADER_BLOCK

    #include "fgTypes.h"
    #include "fgGFXStdInc.h"
    #include "Textures/fgTextureResource.h"

    #if !defined(FG_INC_GFX_WINDOW)
        #include "fgGFXWindow.h"
    #endif
    #if !defined(FG_INC_GFX_MVP_MATRIX)
        #include "fgGFXMVPMatrix.h"

    #endif
    #if !defined(FG_INC_GFX_SHADER_PROGRAM)
        #include "Shaders/fgGFXShaderProgram.h"
    #endif

namespace fg {
    namespace gfx {

        /**
         * #FIXME - some base class for gfx ?
         */
        class CLoader {
        public:
            ///
            typedef void base_type; // #FIXME

        private:
            /// Pointer to the splash texture to display as the background
            /// Please note that this textures need to be uploaded to the GFX
            fgTextureResource *m_pSplashTex;
            /// Pointer to the progress texture - used to draw the simple bar
            /// This can be NULL - if so, no progress bar will be displayed
            fgTextureResource *m_pProgressTex;
            /// Pointer to the currently used program -- needed to set MVP
            fgGfxShaderProgram *m_pProgram;
            /// Pointer to the main gfx window object
            CWindow *m_pWindow;
            /// Pointer to the external context currently used
            /// Probably passed down from GFX::MAIN
            fgGfxContext *m_pContext;
            /// Main Model-Projection-View matrix to use with shader
            fgGfxMVPMatrix m_mvp;
            /// 4x4 matrix to hold translation and scale transformations
            fgMatrix4f m_mat;
            /// Progress of the loading - from 0 to 100
            float m_progress;

        public:
            /**
             * 
             */
            CLoader();
            /**
             * 
             * @param orig
             */
            CLoader(const CLoader& orig);
            /**
             * 
             */
            virtual ~CLoader();

        public:
            /**
             * 
             * @param pSplashTex
             */
            void setSplashTexture(fgTextureResource *pSplashTex) {
                m_pSplashTex = pSplashTex;
            }
            /**
             * 
             * @param pProgressTex
             */
            void setProgressTexture(fgTextureResource *pProgressTex) {
                m_pProgressTex = pProgressTex;
            }
            /**
             * 
             * @param pProgram
             */
            void setProgram(fgGfxShaderProgram *pProgram) {
                m_pProgram = pProgram;
            }
            /**
             * 
             * @param pWindow
             */
            void setMainWindow(fg::gfx::CWindow *pWindow) {
                m_pWindow = pWindow;
                if(m_pWindow) {
                    m_mvp.setOrtho(0.0f,
                                   (float)m_pWindow->getWidth(),
                                   (float)m_pWindow->getHeight(),
                                   0.0f);
                }
            }
            /**
             * 
             * @param pContext
             */
            void setContext(fgGfxContext *pContext) {
                m_pContext = pContext;
            }

        public:
            /**
             * Update the screen - draw the splash screen with the progress bar
             * updated by the specified difference - progress is from 0 to 100
             * @param diff
             */
            void update(const float diff = 0.0f);
        };
    };
};

    #undef FG_INC_GFX_LOADER_BLOCK
#endif	/* FG_INC_GFX_LOADER */
