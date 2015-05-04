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
 * File:   fgPluginResource.cpp
 * Author: vigilant
 * 
 * Created on May 4, 2015, 10:34 AM
 */

#include "fgBuildConfig.h"
#include "fgPluginResource.h"
#include "fgGameMain.h"
#include "Util/fgStrings.h"

#if defined(FG_USING_SDL2)
#include <SDL2/SDL_loadso.h>
#endif

#if !defined(FG_USING_SDL2) 
#if defined(FG_USING_PLATFORM_WINDOWS)
#include "fgWindowsStd.h"

static void* internal_LoadObject(const char* path) {
#ifdef __WINRT__
    void *handle = (void *)LoadPackagedLibrary(tpath, 0);
#else
    void *handle = (void *)LoadLibrary(tpath);
#endif
    return handle;
}

static void* internal_LoadFunction(void* handle, const char* name) {
    if(handle == NULL || !name)
        return NULL;
    void *symbol = (void *)GetProcAddress((HMODULE)handle, name);
    if(symbol == NULL) {
        // error
    }
    return symbol;
}

static void internal_UnloadObject(void *handle) {
    if(handle != NULL) {
        FreeLibrary((HMODULE)handle);
    }
}

#elif defined(FG_USING_PLATFORM_LINUX)
#include <dlfcn.h>

static void* internal_LoadObject(const char* path) {
    void *handle = dlopen(path, RTLD_NOW | RTLD_LOCAL);
    const char *loaderror = (char *)dlerror();
    return handle;
}

static void* internal_LoadFunction(void* handle, const char* name) { }

static void internal_UnloadObject(void* handle) {
    if(handle != NULL) {
        dlclose(handle);
    }
}
#endif

#else
#define internal_LoadFunction SDL_LoadFunction
#define internal_LoadObject SDL_LoadObject
#define internal_UnloadObject SDL_UnloadObject
#endif

using namespace fg;

//------------------------------------------------------------------------------

CPluginResource::CPluginResource() : base_type(),
m_internalInfo(),
m_pluginInitStatus(FG_FALSE),
m_initFuncName(),
m_exitFuncName(),
m_libHandle(NULL),
m_initFuncHandle(NULL),
m_exitFuncHandle(NULL) {
    m_resType = resource::PLUGIN;
}
//------------------------------------------------------------------------------

CPluginResource::CPluginResource(const char *path) : base_type(path),
m_internalInfo(),
m_pluginInitStatus(FG_FALSE),
m_initFuncName(),
m_exitFuncName(),
m_libHandle(NULL),
m_initFuncHandle(NULL),
m_exitFuncHandle(NULL) {
    m_resType = resource::PLUGIN;
}
//------------------------------------------------------------------------------

CPluginResource::CPluginResource(const std::string& path) : base_type(path),
m_internalInfo(),
m_pluginInitStatus(FG_FALSE),
m_initFuncName(),
m_exitFuncName(),
m_libHandle(NULL),
m_initFuncHandle(NULL),
m_exitFuncHandle(NULL) {
    m_resType = resource::PLUGIN;
}
//------------------------------------------------------------------------------

CPluginResource::~CPluginResource() {
    self_type::destroy();
}
//------------------------------------------------------------------------------

void CPluginResource::clear(void) {
    base_type::clear();
    m_internalInfo.pGameMain = NULL;
    m_initFuncName.clear();
    m_exitFuncName.clear();
    m_pluginInitStatus = FG_FALSE;
    m_libHandle = NULL;
    m_initFuncHandle = NULL;
    m_exitFuncHandle = NULL;
    m_resType = resource::PLUGIN;
}
//------------------------------------------------------------------------------

fgBool CPluginResource::create(void) {
    if(m_isReady || m_libHandle)
        return FG_TRUE;

    if(!m_internalInfo.pGameMain) {
        // Need to initialize pointer before create
        return FG_FALSE;
    }

    const char *path = getFilePathStr(m_quality);


    if(m_libHandle) {
        internal_UnloadObject(m_libHandle);
    }
    m_libHandle = internal_LoadObject(path);
    if(!m_libHandle) {
#if defined(FG_USING_SDL2)
        FG_LOG_ERROR("Plugin: Unable to load '%s' plugin: %s", getNameStr(), SDL_GetError());
#endif
        return FG_FALSE;
    }
    m_initFuncName.clear();
    m_initFuncName.append("fgInitPluginFunction_").append(strings::toUpper(getName()));

    m_initFuncHandle = (InitPluginFunction)internal_LoadFunction(m_libHandle, m_initFuncName.c_str());
    if(!m_initFuncHandle) {
#if defined(FG_USING_SDL2)
        FG_LOG_ERROR("Plugin: Unable to load init function '%s': %s", m_initFuncName.c_str(), SDL_GetError());
#endif
        internal_UnloadObject(m_libHandle);
        m_libHandle = NULL;
        m_size = 0;
        return FG_FALSE;
    }

    m_exitFuncName.clear();
    m_exitFuncName.append("fgExitPluginFunction_").append(strings::toUpper(getName()));

    m_exitFuncHandle = (InitPluginFunction)internal_LoadFunction(m_libHandle, m_exitFuncName.c_str());
    if(!m_exitFuncHandle) {
        internal_UnloadObject(m_libHandle);
        m_initFuncHandle = NULL;
        m_libHandle = NULL;
        m_size = 0;
        return FG_FALSE;
    }

    // Properly retrieved pointers - initialize !
    m_isReady = FG_TRUE;
    m_pluginInitStatus = m_initFuncHandle(&m_internalInfo);

    if(!m_pluginInitStatus) {
        // ooops ? still the library/plugin loaded fine - the plugin screwed up
        m_isReady = FG_FALSE;
    }

    return FG_TRUE;
}
//------------------------------------------------------------------------------

void CPluginResource::destroy(void) {
    // this should call dispose and unload the library
    dispose();
    self_type::clear();
}
//------------------------------------------------------------------------------

fgBool CPluginResource::recreate(void) {
    if(m_isReady) {
        dispose();
    }
    return create();
}
//------------------------------------------------------------------------------

void CPluginResource::dispose(void) {
    // this should call exit func (if init OK) and unload the library
    if(m_libHandle) {
        if(m_pluginInitStatus) {
            // init status was ok - call exit func
            if(m_exitFuncHandle) {
                m_exitFuncHandle(&m_internalInfo);
            }
        }
        internal_UnloadObject(m_libHandle);
    }
}
//------------------------------------------------------------------------------

fgBool CPluginResource::isDisposed(void) const {
    if(!m_libHandle || !m_initFuncHandle || !m_isReady) {
        return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------
