/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGfxWindow.h"
#include "fgGfxContext.h"
#include "fgColors.h"

using namespace fg;

//------------------------------------------------------------------------------

gfx::CWindow::CWindow() :
m_onSwapCallbacks(),
m_title(),
#if defined(FG_USING_SDL2)
m_sdlWindow(NULL),
m_sdlFlags(0),
#endif
m_width(0),
m_height(0),
m_isFullscreen(FG_FALSE),
m_isHW(FG_FALSE),
m_isDB(FG_FALSE),
m_isOpen(FG_FALSE) { }
//------------------------------------------------------------------------------

gfx::CWindow::CWindow(const char *title, unsigned int width, unsigned int height) :
m_onSwapCallbacks(),
m_title(),
#if defined(FG_USING_SDL2)
m_sdlWindow(NULL),
m_sdlFlags(0),
#endif
m_width(0),
m_height(0),
m_isFullscreen(FG_FALSE),
m_isHW(FG_FALSE),
m_isDB(FG_FALSE),
m_isOpen(FG_FALSE) {
    self_type::setup(title, width, height);
}
//------------------------------------------------------------------------------

gfx::CWindow::~CWindow() {
    this->close();
    int n = m_onSwapCallbacks.size();
    for(int i = 0; i < n; i++) {
        CallbackData &info = m_onSwapCallbacks[i];
        info.callback = NULL;
        info.userData = NULL;
    }
    m_onSwapCallbacks.clear_optimised();
}
//------------------------------------------------------------------------------

fgBool gfx::CWindow::setup(const char *title, unsigned int width, unsigned int height) {    
    if(m_isOpen) {
#if !defined(FG_USING_SDL2)
        m_width = width;
        m_height = height;
#elif defined(FG_STATIC_LIBRARY)
        m_width = width;
        m_height = height;
#endif
        return FG_TRUE;
    }
    fgBool status = FG_TRUE;
#if defined(FG_USING_SDL2)
    m_width = width;
    m_height = height;
    if(!title)
        title = FG_PACKAGE_FULL_TEXT;
#if defined(FG_USING_PLATFORM_ANDROID)
    m_isFullscreen = FG_TRUE;
#endif

    //SDL_InitSubSystem() // SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK 
    m_sdlFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    if(m_isFullscreen)
        m_sdlFlags |= SDL_WINDOW_FULLSCREEN;
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
    } else {
        FG_LOG_DEBUG("GFX: Successfully created SDL2 window %dx%d", m_width, m_height);
    }
#else
    m_width = width;
    m_height = height;
#endif
    if(status)
        m_isOpen = FG_TRUE;
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CWindow::close(void) {
    fgBool status = FG_TRUE;
#if defined(FG_USING_SDL2)
    if(m_sdlWindow) {
        SDL_DestroyWindow(m_sdlWindow);
        m_sdlWindow = NULL;
        m_sdlFlags = 0;
    }
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
//------------------------------------------------------------------------------

void gfx::CWindow::setFullscreen(fgBool toggle) {
#if !defined(FG_USING_PLATFORM_ANDROID)
    if(m_isFullscreen != toggle) {
        m_isFullscreen = toggle;
        refreshFS();
    }
#else
    m_isFullscreen = FG_TRUE;
#endif
}
//------------------------------------------------------------------------------

fgBool gfx::CWindow::refreshFS(void) {
#if !defined(FG_USING_PLATFORM_ANDROID) && defined(FG_USING_SDL2)
    if(m_isFullscreen) {
        // #FIXME
        //m_sdlFlags |= SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN_DESKTOP;
        if(SDL_SetWindowFullscreen(m_sdlWindow, SDL_WINDOW_FULLSCREEN_DESKTOP) != 0) {
            FG_LOG_ERROR("GFX: Couldn't change to fullscreen mode window: '%s'", SDL_GetError());
            SDL_ClearError();
            return FG_FALSE;
        }
        SDL_DisplayMode mode;
        mode.w = 1920;
        mode.h = 1080;
        mode.refresh_rate = 60;
        mode.format = SDL_PIXELFORMAT_RGB24;
        m_width = 1920;
        m_height = 1080;
        SDL_SetWindowDisplayMode(m_sdlWindow, &mode);
    }
#endif
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CWindow::swapBuffers(void) {
    if(!m_isOpen)
        return FG_FALSE;
#if defined(FG_USING_SDL2)
    if(m_sdlWindow)
        SDL_GL_SwapWindow(m_sdlWindow);
#endif
    // Now call the special on swap callbacks
    int n = m_onSwapCallbacks.size();
    for(int i = 0; i < n; i++) {
        CallbackData &info = m_onSwapCallbacks[i];
        if(info.callback) {
            // systemData = this, userData 
            info.callback((void *)this, (void *)info.userData);
        }
    }

    return FG_TRUE;
}
//------------------------------------------------------------------------------

void gfx::CWindow::clearColor(void) {
#if defined(FG_USING_OPENGL) || defined(FG_USING_OPENGL_ES)
    // #FIXME ?
    Color4f color = colors::getColor("Gray");
    context::clearColor(color.x, color.y, color.z, 1.0f);
    //context::clearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif
}
//------------------------------------------------------------------------------

fgBool gfx::CWindow::registerOnSwap(CallbackFuncPtr pCallback,
                                    void* pUserData) {
    if(!pCallback || isRegistered(pCallback))
        return FG_FALSE;
    CallbackData callbackInfo(pCallback, pUserData);
    m_onSwapCallbacks.push_back(callbackInfo);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CWindow::isRegistered(CallbackFuncPtr pCallback) {
    if(!pCallback)
        return FG_FALSE;
    int n = m_onSwapCallbacks.size();
    // Check for duplicates
    for(int i = 0; i < n; i++) {
        CallbackData &info = m_onSwapCallbacks[i];
        if(info.callback == pCallback)
            return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------
