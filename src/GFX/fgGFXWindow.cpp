/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXWindow.h"
#include "fgGFXPlatform.h"

#if defined FG_USING_MARMALADE
#include "s3e.h"
#include "s3eTypes.h"
#endif

/**
 * 
 */
fg::gfx::CWindow::CWindow() :
m_title(),
#if defined(FG_USING_EGL)
m_EGLSurface(0),
#elif defined(FG_USING_SDL2)
m_sdlWindow(NULL),
m_sdlFlags(0),
#endif
m_width(0),
m_height(0),
m_isFullscreen(FG_FALSE),
m_isHW(FG_FALSE),
m_isDB(FG_FALSE),
m_isOpen(FG_FALSE) { }

/**
 * 
 * @param title
 * @param width
 * @param height
 */
fg::gfx::CWindow::CWindow(const char *title, unsigned int width, unsigned int height) :
m_title(),
#if defined(FG_USING_EGL)
m_EGLSurface(0),
#elif defined(FG_USING_SDL2)
m_sdlWindow(NULL),
m_sdlFlags(0),
#endif
m_width(0),
m_height(0),
m_isFullscreen(FG_FALSE),
m_isHW(FG_FALSE),
m_isDB(FG_FALSE),
m_isOpen(FG_FALSE) {
    CWindow::setup(title, width, height);
}

/**
 * 
 */
fg::gfx::CWindow::~CWindow() {
    close();
}

/**
 * 
 * @param title
 * @param width
 * @param height
 * @return 
 */
fgBool fg::gfx::CWindow::setup(const char *title, unsigned int width, unsigned int height) {
    if(!CPlatform::isInit()) {
        FG_LOG::PrintError("GFX: Cannot setup window without platform initialized.");
        return FG_FALSE;
    }
    if(m_isOpen) {
        CWindow::close();
    }
    fgBool status = FG_TRUE;
#if defined FG_USING_EGL || defined FG_USING_MARMALADE_EGL
    EGLDisplay eglDisplay = (EGLDisplay)CPlatform::getDefaultDisplay();
    EGLContext eglContext = (EGLContext)CPlatform::context()->getGLContext();
    EGLConfig eglConfig = (EGLConfig)CPlatform::getDefaultConfig();
    EGLNativeWindowType eglNativeWindow = 0;

    if(!eglDisplay || !eglContext || !eglConfig) {
        FG_LOG_ERROR("GfxWindow: Current configuration is malformed");
        return FG_FALSE;
    }

#if defined FG_USING_MARMALADE
    eglNativeWindow = s3eGLGetNativeWindow();
#else
    // FIXME
    return FG_FALSE;
#endif
    m_EGLSurface = eglCreateWindowSurface(eglDisplay, eglConfig, eglNativeWindow, NULL);
    fgEGLError("eglCreateWindowSurface");
    eglMakeCurrent(eglDisplay, m_EGLSurface, m_EGLSurface, eglContext);
    fgEGLError("eglMakeCurrent");
    EGLint w = -1, h = -1;
    eglQuerySurface(eglDisplay, m_EGLSurface, EGL_HEIGHT, &h);
    fgEGLError("eglQuerySurface");
    eglQuerySurface(eglDisplay, m_EGLSurface, EGL_WIDTH, &w);
    fgEGLError("eglQuerySurface");
    if(w < 0 || h < 0) {
#if defined FG_USING_MARMALADE
        FG_LOG::PrintError("EGL: query surface failed, falling back to S3E...");
        w = s3eSurfaceGetInt(S3E_SURFACE_WIDTH);
        h = s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);
#else 
        // #FIXME
#endif 
    }
    m_width = w;
    m_height = h;

    FG_LOG_DEBUG("EGL: Window surface created. Dimensions: %dx%d", w, h);

#elif defined FG_USING_MARMALADE_IWGL
    m_width = IwGLGetInt(IW_GL_WIDTH);
    m_height = IwGLGetInt(IW_GL_HEIGHT);

#elif defined FG_USING_SDL2

    m_width = width;
    m_height = height;
    if(!title)
        title = FG_PACKAGE_FULL_TEXT;

    //SDL_InitSubSystem() // SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK 
    m_sdlFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    m_sdlWindow = SDL_CreateWindow(title,
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   m_width,
                                   m_height,
                                   m_sdlFlags);

    if(!m_sdlWindow) {
        FG_LOG_ERROR("GFX: Couldn't create SDL window: '%s'", SDL_GetError());
        SDL_ClearError();
        return FG_FALSE;
    }

#endif
    if(status)
        m_isOpen = FG_TRUE;
    return status;
}

/**
 * 
 * @return 
 */
fgBool fg::gfx::CWindow::close(void) {
    if(!CPlatform::isInit()) {
        FG_LOG_ERROR("GFX: Platform not initialized.");
        return FG_FALSE;
    }
    fgBool status = FG_TRUE;
#if defined FG_USING_EGL
    EGLDisplay eglDisplay = (EGLDisplay)CPlatform::getDefaultDisplay();
    // Getting context in the gfx window makes sense under EGL - it's safe
    // to asume (for now) that there's just one context and one window
    // It supposed to be more flexible though
    EGLContext eglContext = (EGLContext)CPlatform::context()->getGLContext();
    if(eglDisplay) {
        eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if(m_EGLSurface)
            eglDestroySurface(eglDisplay, m_EGLSurface);
        m_EGLSurface = NULL;
    }

#elif defined FG_USING_SDL2

    if(m_sdlWindow) {
        SDL_DestroyWindow(m_sdlWindow);
        m_sdlWindow = NULL;
        m_sdlFlags = 0;
    }
#elif defined FG_USING_IWGL
    //
#endif
    //m_width = 0;
    //m_height = 0;
    m_isFullscreen = FG_FALSE;
    m_isHW = FG_FALSE;
    m_isDB = FG_FALSE;
    m_isOpen = FG_FALSE;
    //m_title.clear(); // ?
    return status;
}

/**
 * 
 * @param toggle
 */
void fg::gfx::CWindow::setFullscreen(fgBool toggle) {
    if(m_isFullscreen != toggle) {
        m_isFullscreen = toggle;
        refreshFS();
    }
}

/**
 * 
 * @return 
 */
fgBool fg::gfx::CWindow::refreshFS(void) {
    // #FIXME
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool fg::gfx::CWindow::swapBuffers(void) {
#if defined FG_USING_MARMALADE_EGL
    EGLDisplay eglDisplay = (EGLDisplay)CPlatform::getDefaultDisplay();
    if(eglDisplay && m_EGLSurface)
        eglSwapBuffers(eglDisplay, m_EGLSurface);
#elif defined FG_USING_MARMALADE_IWGL
    IwGLSwapBuffers();
#elif defined FG_USING_SDL2
    if(m_sdlWindow)
        SDL_GL_SwapWindow(m_sdlWindow);
#endif
    return FG_TRUE;
}

/**
 *
 */
void fg::gfx::CWindow::clearColor(void) {
#if defined FG_USING_OPENGL || defined FG_USING_OPENGL_ES
    // #FIXME ?
    CPlatform::context()->clearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif
}
