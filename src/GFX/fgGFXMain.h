/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_MAIN
    #define FG_INC_GFX_MAIN
    #define FG_INC_GFX_MAIN_BLOCK

    #include "fgBuildConfig.h"
    #include "fgGFXStdInc.h"

    #include "fgGFXWindow.h"
    #include "fgGFXLoader.h"
    #include "fgGFXCameraAnimation.h"
    #include "Shaders/fgGFXShaderManager.h"
    #include "Textures/fgTextureManager.h"

    #include "Scene/fgGFX3DScene.h"
    #include "Scene/fgGFX2DScene.h"

    #include "Util/fgTag.h"
    #include "Particles/fgParticleSystem.h"
    #include "Event/fgArgumentList.h"
    #include "Event/fgCallback.h"

namespace fg {
    namespace gfx {
        class CGfxMain;
    };
};

    #define FG_TAG_GFX_MAIN_NAME	"GfxMain"
    #define FG_TAG_GFX_MAIN		FG_TAG_TYPE(fg::gfx::CGfxMain)
FG_TAG_TEMPLATE_ID_AUTO(fg::gfx::CGfxMain, FG_TAG_GFX_MAIN_NAME);

namespace fg {
    namespace gfx {
        ///
        typedef FG_TAG_GFX_MAIN GfxMainTag;
        
        /**
         *
         */
        class CGfxMain {
        public:
            ///
            typedef CGfxMain type;
            ///
            typedef GfxMainTag tag_type;

        public:
            /**
             * Default constructor for the GFX main object
             */
            CGfxMain();
            /**
             * Destructor for the GFX main object
             */
            virtual ~CGfxMain();

        protected:
            /**
             * 
             */
            void registerResourceCallbacks(void);
            /**
             * 
             */
            void unregisterResourceCallbacks(void);
            
            /**
             * 
             */
            void registerSceneCallbacks(void);
            
            /**
             * 
             * @param argv
             */
            void unregisterSceneCallbacks(void);

            /**
             * 
             * @param argv
             * @return 
             */
            fgBool resourceCreatedHandler(fg::event::CArgumentList *argv);
            
            /**
             * 
             * @param argv
             * @return 
             */
            fgBool sceneNodeInsertedHandler(fg::event::CArgumentList * argv);

        public:

            /**
             * Sets the pointer to the external resource manager
             * @param pResourceManager
             * @return 
             */
            fgBool setupResourceManager(fg::base::CManager *pResourceManager);

            /**
             * Init the whole GFX subsystem - set the screen
             * @return 
             */
            fgBool initGFX(void);
            /**
             * Close the subsystem - destroy the graphics context
             */
            void closeGFX(void);
            
            /**
             * 
             */
            void generateBuiltInData(void);

            /**
             * 
             * @return 
             */
            fgBool suspendGFX(void);
            /**
             * Resume event, restore state & context
             * @return 
             */
            fgBool resumeGFX(void);

            // Now main display function creates the buffer (vertex/color/texture coords buffers) 
            // to be displayed in current frame. The real drawing of created buffers is inside the
            // render function (which in the future should be in separate thread)
            // This will generate the list of visible objects, do frustum culling
            void display(void);

            // Begins the proper render of the created buffers
            void render(void);

            /**
             * This will preload needed textures for the GFX::Loader - splash/progress
             */
            void setupLoader(void);

            /**
             * Returns the pointer to the Texture Manager
             * @return 
             */
            CTextureManager *getTextureManager(void) const;
            /**
             * Releases all textures - the GFX side and nonGFX (meaning internal RAM)
             * @return 
             */
            fgBool releaseTextures(void);
            /**
             * Returns the pointer to the shader manager
             * @return 
             */
            CShaderManager *getShaderManager(void) const;
            /**
             * Pre loads all shaders - caches the specific configs
             * @return 
             */
            fgBool preLoadShaders(void) const;
            /**
             * Returns the pointer to the main GFX windows - OS specific main window
             * @return 
             */
            CWindow *getMainWindow(void) const;
            /**
             * Getter for the Scene3D object
             * @return 
             */
            CScene3D *get3DScene(void) const;
            /**
             * Returns the pointer to the main 2D scene - may be NULL
             * @return 
             */
            CScene2D *get2DScene(void) const;
            /**
             * Returns the pointer to the main 3D scene camera - may be NULL
             * @return 
             */
            CCameraAnimation *get3DSceneCamera(void) const;
            /**
             * 
             * @return 
             */
            CParticleSystem *getParticleSystem(void) const;
            /**
             * 
             * @return 
             */
            CLoader *getLoader(void) {
                return &m_loader;
            }
            /**
             * 
             * @return 
             */
            CContext *context(void) const {
                return m_gfxContext;
            }

        private:
            /// Loader object - displays splash screen and progress bar at the early 
            /// stages of initialization - before GUI subsystem full initialization
            CLoader m_loader;
            /// Texture manager for GFX upload/reload - works with Resource manager
            CTextureManager *m_textureMgr;
            /// Pointer to the resource manager - defined and managed outside
            fg::base::CManager *m_pResourceMgr;
            /// Pointer to the external event manager
            fg::base::CManager *m_pEventMgr;
            /// Main GFX shader manager
            CShaderManager *m_shaderMgr;
            /// Main GFX OS specific window
            CWindow *m_mainWindow;
            /// Main GFX context - it's directly connected to the GFX window
            CContext *m_gfxContext;
            /// Main 3D scene management
            CScene3D *m_3DScene;
            /// Main 2D scene management
            CScene2D *m_2DScene;
            /// Main Particle System
            CParticleSystem *m_particleSystem;
            /// 
            fg::event::CFunctionCallback *m_resourceCreatedCallback;
            ///
            fg::event::CFunctionCallback *m_sceneNodeInsertedCallback;;
            /// Is GFX init properly?
            fgBool m_init;
        };
    };
};

    #undef FG_INC_GFX_MAIN_BLOCK
#endif /* FG_INC_GFX_MAIN */
