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
    #include "fgGfxStdInc.h"

    #include "fgGfxWindow.h"
    #include "fgGfxCameraAnimation.h"
    #include "Shaders/fgGfxShaderManager.h"
    #include "Textures/fgTextureManager.h"

    #include "Scene/fgGfx3DScene.h"
    #include "Scene/fgGfx2DScene.h"

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
            class CLoader;

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
             * @param pSystemData
             * @param pUserData
             * @return
             */
            static fgBool handleMainWindowBufferSwap(void *pSystemData, void *pUserData);

            ////////////////////////////////////////////////////////////////////

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
            void closeGFX(fgBool suspend = FG_FALSE);

            /**
             * 
             */
            void generateBuiltInData(void);

            ////////////////////////////////////////////////////////////////////

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

            ////////////////////////////////////////////////////////////////////

            /**
             * Now main display function creates the buffer (vertex/color/texture coords buffers)
             * to be displayed in current frame. The real drawing of created buffers is inside the
             * render function (which in the future should be in separate thread)
             * This will generate the list of visible objects, do frustum culling
             */
            void preRender(void);

            /**
             * Begins the proper render of the created buffers
             */
            void render(void);

            fgBool prepareFrame(void);

            ////////////////////////////////////////////////////////////////////

            /**
             * This will preload needed textures for the GFX::Loader - splash/progress
             */
            void setupLoader(void);
            /**
             * Releases all textures - the GFX side and nonGFX (meaning internal RAM)
             * @return 
             */
            fgBool releaseTextures(void);
            /**
             * Pre loads all shaders - caches the specific configs
             * @return 
             */
            fgBool preLoadShaders(void);

            ////////////////////////////////////////////////////////////////////
            /**
             * Returns the pointer to the Texture Manager
             * @return
             */
            inline CTextureManager* getTextureManager(void) const {
                return m_textureMgr;
            }
            /**
             *
             * @return
             */
            inline fg::base::CManager* getResourceManager(void) const {
                return m_pResourceMgr;
            }
            /**
             *
             * @return
             */
            inline fg::base::CManager* getEventManager(void) const {
                return m_pEventMgr;
            }
            /**
             * Returns the pointer to the shader manager
             * @return
             */
            inline CShaderManager* getShaderManager(void) const {
                return m_shaderMgr;
            }
            /**
             * Returns the pointer to the main GFX windows - OS specific main window
             * @return 
             */
            inline CWindow* getMainWindow(void) const {
                return m_mainWindow;
            }
            /**
             * Getter for the Scene3D object
             * @return 
             */
            inline CScene3D* get3DScene(void) const {
                return m_3DScene;
            }
            /**
             * Returns the pointer to the main 2D scene - may be NULL
             * @return 
             */
            inline CScene2D* get2DScene(void) const {
                return m_2DScene;
            }
            /**
             * Returns the pointer to the main 3D scene camera - may be NULL
             * @return 
             */
            inline CCameraAnimation* get3DSceneCamera(void) const {
                if(!m_3DScene)
                    return NULL;
                return m_3DScene->getCamera();
            }
            /**
             * 
             * @return 
             */
            inline CParticleSystem* getParticleSystem(void) const {
                return m_particleSystem;
            }
            /**
             * 
             * @return 
             */
            inline ::fg::gfx::CGfxMain::CLoader* getLoader(void) {
                return m_loader;
            }
            /**
             * 
             * @return 
             */
            inline fgBool isInit(void) const {
                return m_init;
            }

            ////////////////////////////////////////////////////////////////////
            /**
             * 
             * @param w
             * @param h
             */
            inline void setScreenSize(int w, int h) {
                context::setScreenSize(w, h);
            }

        public:

            /**
             *
             */
            class CLoader {
                friend class ::fg::gfx::CGfxMain;

            public:
                /**
                 *
                 */
                CLoader(CGfxMain* pGfxMain);
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
                void setSplashTexture(CTextureResource *pSplashTex) {
                    m_pSplashTex = pSplashTex;
                }
                /**
                 *
                 * @param pProgressTex
                 */
                void setProgressTexture(CTextureResource *pProgressTex) {
                    m_pProgressTex = pProgressTex;
                }
                /**
                 * 
                 */
                void setupMVP(void) {
                    if(m_pGfxMain) {
                        m_mvp.setOrtho(0.0f,
                                       (float)context::getScreenSize().x,
                                       (float)context::getScreenSize().y,
                                       0.0f);
                    }
                }

            public:
                /**
                 * Update the screen - draw the splash screen with the progress bar
                 * updated by the specified difference - progress is from 0 to 100
                 * @param diff
                 */
                void update(const float diff = 0.0f);

            private:
                /// Pointer to the splash texture to display as the background
                /// Please note that this textures need to be uploaded to the GFX
                CTextureResource *m_pSplashTex;
                /// Pointer to the progress texture - used to draw the simple bar
                /// This can be NULL - if so, no progress bar will be displayed
                CTextureResource *m_pProgressTex;
                /// Pointer to the gfx main class
                CGfxMain* m_pGfxMain;
                /// Main Model-Projection-View matrix to use with shader
                CMVPMatrix m_mvp;
                /// 4x4 matrix to hold translation and scale transformations
                Matrix4f m_mat;
                /// Progress of the loading - from 0 to 100
                float m_progress;
            };

        private:
            /// Loader object - displays splash screen and progress bar at the early 
            /// stages of initialization - before GUI subsystem full initialization
            CLoader* m_loader;
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
            /// Main 3D scene management
            CScene3D *m_3DScene;
            /// Main 2D scene management
            CScene2D *m_2DScene;
            /// Main Particle System
            CParticleSystem *m_particleSystem;
            /// 
            fg::event::CFunctionCallback *m_resourceCreatedCallback;
            ///
            fg::event::CFunctionCallback *m_sceneNodeInsertedCallback;
            /// Is GFX init properly?
            fgBool m_init;
        };
    };
};

    #undef FG_INC_GFX_MAIN_BLOCK
#endif /* FG_INC_GFX_MAIN */
