/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_PLATFORM
    #define FG_INC_GFX_PLATFORM

    #ifndef FG_INC_GFX_CONTEXT
        #include "fgGFXContext.h"
    #endif

/*
 *
 */
class fgGfxPlatform {
protected:
    //
    fgGfxPlatform();
    //
    virtual ~fgGfxPlatform();

public:
    //
    static fgBool initialize(fgBool reinit = FG_FALSE);
    //
    static fgBool quit(void);

    //
    static fgBool isInit(void);

    //
    static void* getDefaultDisplay(void);
    //
    static void* getDefaultContext(void);
    //
    static void *getDefaultConfig(void);
    //
    static fgGfxContext* context(void);

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
    /// Main gfx context (server/client state cache)
    static fgGfxContext *m_gfxContext;
    /// Is platform initialized?
    static fgBool m_init;
    /// Default display pointer 
    static void* m_defaultDisplay; // it's for egl only...
    /// Default context pointer
    static void* m_defaultContext; // it's for egl only...
    /// Default config pointer
    static void* m_defaultConfig; // it's for egl only...
};

#endif /* FG_INC_GFX_PLATFORM */
