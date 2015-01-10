 /*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_MAIN
    #define FG_INC_GFX_MAIN

    #include "fgBuildConfig.h"
    #include "fgGFXStdInc.h"

    #include "fgGFXWindow.h"
    #include "fgGFXLoader.h"
    #include "fgGFXCameraAnimation.h"
    #include "Shaders/fgGFXShaderManager.h"
    #include "Textures/fgTextureManager.h"

    #include "fgGFX3DScene.h"
    #include "fgGFX2DScene.h"

    #include "Util/fgTag.h"

    #include "Particles/fgParticleSystem.h"
    #include "Event/fgArgumentList.h"
    #include "Event/fgCallback.h"
    
class fgGfxMain;
    #define FG_TAG_GFX_MAIN_NAME	"GfxMain"
    #define FG_TAG_GFX_MAIN		FG_TAG_TYPE(fgGfxMain)
FG_TAG_TEMPLATE_ID_AUTO(fgGfxMain, FG_TAG_GFX_MAIN_NAME);
typedef FG_TAG_GFX_MAIN fgGfxMainTag;

// Manager base?

/**
 *
 */
class fgGfxMain {
public:
    ///
    typedef fgGfxMain type;
    ///
    typedef fgGfxMainTag tag_type;
public:
    /**
     * Default constructor for the GFX main object
     */
    fgGfxMain();
    /**
     * Default destructor for the GFX main object
     */
    virtual ~fgGfxMain();

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
     * @param argv
     * @return 
     */
    fgBool resourceCreatedHandler(fgArgumentList *argv);
    
public:
    
    // Sets the pointer to the external resource manager
    fgBool setupResourceManager(fg::base::CManager *pResourceManager);

    // Init the whole GFX subsystem - set the screen
    fgBool initGFX(void);
    // Close the subsystem - destroy the graphics context
    void closeGFX(void);

    // Suspend event
    fgBool suspendGFX(void);
    // Resume event, restore state & context
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
    
    // Returns the pointer to the Texture Manager
    fgTextureManager *getTextureManager(void) const;
    // Releases all textures - the GFX side and nonGFX (meaning internal RAM)
    fgBool releaseTextures(void);
    // Returns the pointer to the shader manager
    fg::gfx::CShaderManager *getShaderManager(void) const;
    // Pre loads all shaders - caches the specific configs
    fgBool preLoadShaders(void) const;
    // Returns the pointer to the main GFX windows - OS specific main window
    fg::gfx::CWindow *getMainWindow(void) const;
    // Returns the pointer to the main 3D scene - may be NULL
    fg::gfx::CScene3D *get3DScene(void) const;
    // Returns the pointer to the main 2D scene - may be NULL
    fg::gfx::CScene2D *get2DScene(void) const;
    // Returns the pointer to the main 3D scene camera - may be NULL
    fgGfxCameraAnimation *get3DSceneCamera(void) const;
    //
    fg::gfx::CParticleSystem *getParticleSystem(void) const;
    //
    fg::gfx::CLoader *getLoader(void) {
        return &m_loader;
    }
    /**
     * 
     * @return 
     */
    fg::gfx::CContext *context(void) const {
        return m_gfxContext;
    }
    
private:
    /// Loader object - displays splash screen and progress bar at the early 
    /// stages of initialization - before GUI subsystem full initialization
    fg::gfx::CLoader m_loader;
    /// Texture manager for GFX upload/reload - works with Resource manager
    fgTextureManager *m_textureMgr;
    /// Pointer to the resource manager - defined and managed outside
    fg::base::CManager *m_pResourceMgr;
    /// Pointer to the external event manager
    fg::base::CManager *m_pEventMgr;
    /// Main GFX shader manager
    fg::gfx::CShaderManager *m_shaderMgr;
    /// Main GFX OS specific window
    fg::gfx::CWindow *m_mainWindow;
    /// Main GFX context - it's directly connected to the GFX window
    fg::gfx::CContext *m_gfxContext;
    /// Main 3D scene management
    fg::gfx::CScene3D *m_3DScene;
    /// Main 2D scene management
    fg::gfx::CScene2D *m_2DScene;
    /// Main Particle System
    fg::gfx::CParticleSystem *m_particleSystem;
    /// 
    fgFunctionCallback *m_resourceCreatedCallback;
    /// Is GFX init properly?
    fgBool m_init;
};

#endif /* FG_INC_GFX_MAIN */
