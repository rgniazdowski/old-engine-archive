/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXPlatform.h"
#include "Util/fgMemory.h"

/// Main gfx context (server/client state cache)
fgGfxContext *fgGfxPlatform::m_gfxContext = NULL;

/// Is platform initialized?
fgBool fgGfxPlatform::m_init = FG_FALSE;

/// Default display pointer // #FIXME
void *fgGfxPlatform::m_defaultDisplay = 0;

/// Default context pointer
void *fgGfxPlatform::m_defaultContext = 0;

/// Default config pointer
void *fgGfxPlatform::m_defaultConfig = 0;

#if defined FG_USING_MARMALADE
#include "s3e.h"
#include "s3eTypes.h"
#endif

fgGfxPlatform::fgGfxPlatform() { }

fgGfxPlatform::~fgGfxPlatform() {
    if(m_gfxContext)
        delete m_gfxContext;
    m_gfxContext = NULL;
}

/*
 *
 */
fgBool fgGfxPlatform::initialize(fgBool reinit) {
    if(fgGfxPlatform::m_init && !reinit)
        return FG_TRUE;
    if(reinit && fgGfxPlatform::m_init) {
        // Need to reinitialize
        fgGfxPlatform::quit(); // ?
    }
    fgBool status = FG_TRUE;
#if defined FG_USING_EGL || defined FG_USING_MARMALADE_EGL
    EGLint major;
    EGLint minor;
    EGLint numFound = 0;
    EGLConfig configList[FG_EGL_MAX_CONFIG];
    int glVersion = 0;
    int config = -1;

    // return an EGL display connection, EGL_DEFAULT_DISPLAY indicates the default display. 
    m_defaultDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if(!m_defaultDisplay) {
        fgEGLError("eglGetDisplay");
        return FG_FALSE;
    }
    //  initialize an EGL display connection 
    EGLBoolean eglStatus = eglInitialize(m_defaultDisplay, &major, &minor);
    if(!eglStatus) {
        fgEGLError("eglInitialize");
        return FG_FALSE;
    }

    // Returns a list of all EGL frame buffer configurations for a display 
    eglGetConfigs(m_defaultDisplay, configList, FG_EGL_MAX_CONFIG, &numFound);
    if(!numFound) {
        FG_LOG::PrintError("EGL: GetConfigs failed to find any configs");
        fgEGLError("eglGetConfigs");
        return FG_FALSE;
    }

    FG_LOG::PrintDebug("EGL: found %d configs", numFound);
    for(int i = 0; i < numFound; i++) {
        EGLint renderable = 0;
        EGLint depthSize = 0;
        EGLint surfacetype = 0;
        eglGetConfigAttrib(m_defaultDisplay, configList[i], EGL_RENDERABLE_TYPE, &renderable);
        eglGetConfigAttrib(m_defaultDisplay, configList[i], EGL_DEPTH_SIZE, &depthSize);
        eglGetConfigAttrib(m_defaultDisplay, configList[i], EGL_SURFACE_TYPE, &surfacetype);
        if((renderable & EGL_OPENGL_ES2_BIT) && config == -1 && depthSize >= 16 && (surfacetype & EGL_WINDOW_BIT)) {
            config = i;
            break;
        }
    }
    if(config == -1) {
        FG_LOG::PrintError("EGL: no GLES2 configs reported. Trying random config");
        config = 0;
    }
    // #FIXME !
#if defined FG_USING_MARMALADE
    glVersion = s3eGLGetInt(S3E_GL_VERSION) >> 8;
#else
    glVersion = 2; // FIXME
#endif
    if(glVersion != 2) {
        FG_LOG::PrintError("GFX: reported GL version: %d", glVersion);
        FG_LOG::PrintError("GFX: required GLES v2.x");
        return FG_FALSE;
    }
    FG_LOG::PrintDebug("EGL: requesting GL version: %d", glVersion);
    FG_LOG::PrintDebug("EGL: choosing config: %d", config);
    EGLint attribs[] = {EGL_CONTEXT_CLIENT_VERSION, glVersion, EGL_NONE,};
    m_defaultContext = eglCreateContext(m_defaultDisplay, configList[config], NULL, attribs);
    if(!m_defaultContext) {
        FG_LOG::PrintError("EGL: CreateContext failed");
        fgEGLError("eglCreateContext");
        return FG_FALSE;
    }
    m_defaultConfig = configList[config];
    _eglDumpConfig(m_defaultDisplay, m_defaultConfig);

    EGLenum boundAPI = eglQueryAPI();
    if(boundAPI != EGL_OPENGL_ES_API) {
        FG_LOG::PrintDebug("EGL is not bound to OpenGL ES api");
    } else {
        FG_LOG::PrintDebug("EGL bound to OpenGL ES api");
    }

    FG_LOG::PrintDebug("EGL vendor:      %s", eglQueryString(m_defaultDisplay, EGL_VENDOR));
    FG_LOG::PrintDebug("EGL version:     %s", eglQueryString(m_defaultDisplay, EGL_VERSION));
    FG_LOG::PrintDebug("EGL extensions:  %s", eglQueryString(m_defaultDisplay, EGL_EXTENSIONS));
    FG_LOG::PrintDebug("EGL client APIs: %s", eglQueryString(m_defaultDisplay, EGL_CLIENT_APIS));

#elif defined FG_USING_MARMALADE_IWGL

    status = IwGLInit();

#elif defined FG_USING_SDL2
    //#define SDL_MAIN_HANDLED
    //#include "SDL.h"
    // SDL_SetMainReady();
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        FG_LOG::PrintError("GFX: Couldn't initialize SDL2: '%s'", SDL_GetError());
        SDL_ClearError();
        return FG_FALSE;
    }

    SDL_DisplayMode *desktopMode;
    int displayCount = 0;

    if((displayCount = SDL_GetNumVideoDisplays()) < 1) {
        FG_LOG::PrintError("GFX: Couldn't retrieve number of displays: '%s'", SDL_GetError());
    }
    if(displayCount) {
        desktopMode = fgMalloc<SDL_DisplayMode>(displayCount);
    }
    for(int displayIdx = 0; displayIdx < displayCount; displayIdx++) {
        int modeCount;
        if(SDL_GetDesktopDisplayMode(0, &desktopMode[displayIdx]) != 0) {
            FG_LOG::PrintError("GFX: Couldn't get desktop display mode for display %d: '%s'", displayIdx, SDL_GetError());
        } else {
            const char *displayName = SDL_GetDisplayName(displayIdx);
            if(!displayName)
                displayName = "unknown";
            FG_LOG::PrintDebug("GFX: Display %d name: '%s'", displayIdx, displayName);
            FG_LOG::PrintDebug("GFX: Display %d current mode: %dx%d@%dHz\t%d BPP", displayIdx, desktopMode[displayIdx].w, desktopMode[displayIdx].h, desktopMode[displayIdx].refresh_rate, SDL_BITSPERPIXEL(desktopMode[displayIdx].format));
        }
        if((modeCount = SDL_GetNumDisplayModes(displayIdx)) < 0) {
            FG_LOG::PrintError("GFX: Couldn't retrieve number of display mode for display %d: '%s'", displayIdx, SDL_GetError());
            continue;
        } else {
            for(int modeIdx = 0; modeIdx < modeCount; modeIdx++) {
                SDL_DisplayMode displayMode;
                memset(&displayMode, 0, sizeof (SDL_DisplayMode));
                if(SDL_GetDisplayMode(displayIdx, modeIdx, &displayMode) != 0) {
                    FG_LOG::PrintError("GFX: Couldn't get display mode for display %d: '%s'", displayIdx, SDL_GetError());
                    continue;
                }
                FG_LOG::PrintDebug("GFX: Display %d, mode %.02d: %dx%d@%dHz\t%d BPP", displayIdx, modeIdx, displayMode.w, displayMode.h, displayMode.refresh_rate, SDL_BITSPERPIXEL(displayMode.format));
            }
        }
    }
    // SDL_bool SDL_GL_ExtensionSupported(const char* extension)
    // int SDL_GL_LoadLibrary(const char* path)
    // const char* SDL_GetError(void)
    // void SDL_ClearError(void)
    // const char *error = SDL_GetError();
    //if (*error) {
    //  SDL_Log("SDL error: %s", error);
    //  SDL_ClearError();
    //}
    // void SDL_GL_UnloadLibrary(void)
    // void* SDL_GL_GetProcAddress(const char* proc)

    //typedef void (APIENTRY * GL_ActiveTextureARB_Func)(unsigned int);
    //GL_ActiveTextureARB_Func glActiveTextureARB_ptr = 0;

    ///* Get function pointer */
    //glActiveTextureARB_ptr=(GL_ActiveTextureARB_Func) SDL_GL_GetProcAddress("glActiveTextureARB");

    ///* It was your responsibility to make sure this was a valid function to call! */
    //glActiveTextureARB_ptr(GL_TEXTURE0_ARB);

    //http://wiki.libsdl.org/SDL_GL_GetProcAddress
    //int SDL_InitSubSystem(Uint32 flags)

    // 

#endif

    //#if defined(FG_USING_GL_BINDING)
    //    glbinding::Binding::initialize();
    //#endif

#if !defined(FG_USING_SDL2)
    if(status) {
        if(!m_gfxContext)
            m_gfxContext = new fgGfxContext();
        m_gfxContext->initialize();
    }
#endif
    if(status)
        fgGfxPlatform::m_init = FG_TRUE;
    return status;
}

/*
 *
 */
fgBool fgGfxPlatform::quit(void) {
    fgBool status = FG_TRUE;
    if(m_init) {
#if defined FG_USING_EGL || defined FG_USING_MARMALADE_EGL
        // #FIXME
        if(m_defaultContext)
            eglDestroyContext(m_defaultDisplay, m_defaultContext);
        eglTerminate(m_defaultDisplay);
        m_defaultDisplay = 0;
        m_defaultConfig = 0;
        m_defaultConfig = 0;
        m_init = FG_FALSE;
        if(m_gfxContext)
            delete m_gfxContext;
        m_gfxContext = NULL;
#elif defined FG_USING_MARMALADE_IWGL
        IwGLTerminate();
#elif defined FG_USING_SDL2
        if(m_gfxContext)
            delete m_gfxContext;
        m_gfxContext = NULL;
        FG_LOG::PrintDebug("Quitting main SDL");
        SDL_Quit();
        //#define SDL_MAIN_HANDLED
        //#include "SDL.h"

        //int main(int argc, char *argv[])
        //{
        //	SDL_SetMainReady();
        //	SDL_Init(SDL_INIT_VIDEO);

        //	...

        //	return 0;
        //}
        //void SDL_QuitSubSystem(Uint32 flags)
#endif
    }
    return status;
}

#if defined(FG_USING_SDL2)

fgBool fgGfxPlatform::initializeMainContext(SDL_Window* sdlWindow) {
    if(!m_gfxContext)
        m_gfxContext = new fgGfxContext(sdlWindow);
    if(!m_gfxContext->isInit())
        return FG_FALSE;
    m_gfxContext->initialize();
    return FG_TRUE;
}
#endif

/*
 *
 */
fgGfxContext *fgGfxPlatform::context(void) {
    return m_gfxContext;
}

/*
 *
 */
fgBool fgGfxPlatform::isInit(void) {
    return fgGfxPlatform::m_init;
}

/*
 *
 */
void *fgGfxPlatform::getDefaultDisplay(void) {
    return fgGfxPlatform::m_defaultDisplay;
}

/*
 *
 */
void *fgGfxPlatform::getDefaultContext(void) {
    return fgGfxPlatform::m_defaultContext;
}

/*
 *
 */
void *fgGfxPlatform::getDefaultConfig(void) {
    return fgGfxPlatform::m_defaultConfig;
}

#if defined FG_USING_EGL

/*
 *
 */
void fgGfxPlatform::_eglDumpConfig(EGLDisplay display, EGLConfig config) {
    if(!display || !config)
        return;

    fgEGLCfgAttrib attribs[] = {
        {EGL_BUFFER_SIZE, "EGL_BUFFER_SIZE", "The depth of the color buffer", 0},
        {EGL_ALPHA_SIZE, "EGL_ALPHA_SIZE", "Number of bits of alpha in the color buffer", 0},
        {EGL_BLUE_SIZE, "EGL_BLUE_SIZE", "Number of bits of blue in the color buffer", 0},
        {EGL_GREEN_SIZE, "EGL_GREEN_SIZE", "Number of bits of green in the color buffer", 0},
        {EGL_RED_SIZE, "EGL_RED_SIZE", "Number of bits of red in the color buffer", 0},
        {EGL_DEPTH_SIZE, "EGL_DEPTH_SIZE", "Number of bits in the depth buffer", 0},
        {EGL_STENCIL_SIZE, "EGL_STENCIL_SIZE", "Number of bits in the stencil buffer", 0},
                                // Possible caveat values are EGL_NONE, EGL_SLOW_CONFIG, and EGL_NON_CONFORMANT. 
        {EGL_CONFIG_CAVEAT, "EGL_CONFIG_CAVEAT", "The caveats for the frame buffer configuration", 0},
        {EGL_CONFIG_ID, "EGL_CONFIG_ID", "ID of the frame buffer configuration", 0},
                                //Returns the frame buffer level. Level zero is the default frame buffer.
                                // Positive levels correspond to frame buffers that overlay the default buffer
                                // and negative levels correspond to frame buffers that underlay the default buffer. 
        {EGL_LEVEL, "EGL_LEVEL", "The frame buffer level", 0},
        {EGL_MAX_PBUFFER_HEIGHT, "EGL_MAX_PBUFFER_HEIGHT", "Max height of a pixel buffer surface in pixels", 0},
        {EGL_MAX_PBUFFER_PIXELS, "EGL_MAX_PBUFFER_PIXELS", "Max size of a pixel buffer surface in pixels", 0},
        {EGL_MAX_PBUFFER_WIDTH, "EGL_MAX_PBUFFER_WIDTH", "Max width of a pixel buffer surface in pixels", 0},
        {EGL_NATIVE_RENDERABLE, "EGL_NATIVE_RENDERABLE", "Can native rendering APIs can render into the surface?", 0},
        {EGL_NATIVE_VISUAL_ID, "EGL_NATIVE_VISUAL_ID", "ID of the associated native visual", 0},
        {EGL_NATIVE_VISUAL_TYPE, "EGL_NATIVE_VISUAL_TYPE", "Type of the associated native visual", 0},
        {EGL_PRESERVED_RESOURCES, "EGL_PRESERVED_RESOURCES", "", 0},
        {EGL_SAMPLES, "EGL_SAMPLES", "Number of samples per pixel", 0},
        {EGL_SAMPLE_BUFFERS, "EGL_SAMPLE_BUFFERS", "Number of multisample buffers", 0},
                                // Supported surface type
        {EGL_SURFACE_TYPE, "EGL_SURFACE_TYPE", "Surface type", 0},
                                // Returns the type of supported transparency. Possible transparency values are: EGL_NONE, and EGL_TRANSPARENT_RGB. 
        {EGL_TRANSPARENT_TYPE, "EGL_TRANSPARENT_TYPE", "Type of supported transparency", 0},
        {EGL_TRANSPARENT_BLUE_VALUE, "EGL_TRANSPARENT_BLUE_VALUE", "Transparent blue value", 0},
        {EGL_TRANSPARENT_GREEN_VALUE, "EGL_TRANSPARENT_GREEN_VALUE", "Transparent green value", 0},
        {EGL_TRANSPARENT_RED_VALUE, "EGL_TRANSPARENT_RED_VALUE", "Transparent red value", 0},
        {EGL_BIND_TO_TEXTURE_RGB, "EGL_BIND_TO_TEXTURE_RGB", "Can color buffers can be bound to an RGB texture?", 0},
        {EGL_BIND_TO_TEXTURE_RGBA, "EGL_BIND_TO_TEXTURE_RGBA", "Can color buffers can be bound to an RGBA texture?", 0},
        {EGL_MIN_SWAP_INTERVAL, "EGL_MIN_SWAP_INTERVAL", "Minimum value for eglSwapInterval", 0},
        {EGL_MAX_SWAP_INTERVAL, "EGL_MAX_SWAP_INTERVAL", "Maximum value for eglSwapInterval", 0},
        {EGL_LUMINANCE_SIZE, "EGL_LUMINANCE_SIZE", "Number of bits of luminance stored in the luminance buffer", 0},
        {EGL_ALPHA_MASK_SIZE, "EGL_ALPHA_MASK_SIZE", "Number of bits in the alpha mask buffer", 0},
                                // Returns the color buffer type. Possible types are EGL_RGB_BUFFER and EGL_LUMINANCE_BUFFER. 
        {EGL_COLOR_BUFFER_TYPE, "EGL_COLOR_BUFFER_TYPE", "Type of the color buffer", 0},
                                // Bitmask indicating the types of supported client API contexts. 
        {EGL_RENDERABLE_TYPE, "EGL_RENDERABLE_TYPE", "Supported client API contexts", 0},
        {EGL_CONFORMANT, "EGL_CONFORMANT", "Bitmask indicating which client API contexts created with respect to this config are conformant.", 0},
        {0, 0, 0, 0}
    };
    FG_LOG::PrintDebug("EGL: Attributes for currently selected config:");
    int nAttribs = sizeof (attribs) / sizeof (attribs[0]);
    for(int i = 0; i < nAttribs; i++) {
        EGLBoolean status = eglGetConfigAttrib(display, config, attribs[i].id, &attribs[i].value);
        if(!status)
            continue;
        EGLint id = attribs[i].id;
        fgEGLCfgAttrib &attrib = attribs[i];
        std::string _tmp;
        switch(id) {
            case EGL_RENDERABLE_TYPE:
                _tmp.clear();
                if(attrib.value & EGL_OPENGL_ES_BIT)
                    _tmp.append("OpenGL ES 1.x, ");
                if(attrib.value & EGL_OPENGL_ES2_BIT)
                    _tmp.append("OpenGL ES 2.x, ");
                if(attrib.value & EGL_OPENGL_BIT)
                    _tmp.append("OpenGL, ");
                if(attrib.value & EGL_OPENVG_BIT)
                    _tmp.append("OpenGL, ");
                if(!_tmp.empty())
                    _tmp = _tmp.substr(0, _tmp.length() - 2);
                FG_LOG::PrintDebug("EGL: [%s] %s: %s", attrib.enumName, attrib.comment, _tmp.c_str());
                break;
            case EGL_COLOR_BUFFER_TYPE:
                _tmp.clear();
                if(attrib.value == EGL_RGB_BUFFER)
                    _tmp.append("RGB");
                else if(attrib.value == EGL_LUMINANCE_BUFFER)
                    _tmp.append("Luminance");
                else
                    _tmp.append("None");
                FG_LOG::PrintDebug("EGL: [%s] %s: %s", attrib.enumName, attrib.comment, _tmp.c_str());
                break;
            case EGL_TRANSPARENT_TYPE:
                _tmp.clear();
                if(attrib.value == EGL_TRANSPARENT_RGB)
                    _tmp.append("Transparent RGB");
                else if(attrib.value == EGL_NONE)
                    _tmp.append("None");
                FG_LOG::PrintDebug("EGL: [%s] %s: %s", attrib.enumName, attrib.comment, _tmp.c_str());
                break;
            case EGL_CONFIG_CAVEAT:
                //EGL_NONE, EGL_SLOW_CONFIG, and EGL_NON_CONFORMANT
                _tmp.clear();
                if(attrib.value == EGL_NON_CONFORMANT_CONFIG)
                    _tmp.append("Transparent RGB");
                else if(attrib.value == EGL_SLOW_CONFIG)
                    _tmp.append("Slow config");
                else if(attrib.value == EGL_NONE)
                    _tmp.append("None");
                FG_LOG::PrintDebug("EGL: [%s] %s: %s", attrib.enumName, attrib.comment, _tmp.c_str());
                break;
            case EGL_SURFACE_TYPE:
                if(attrib.value & EGL_PBUFFER_BIT)
                    _tmp.append("pixel buffer, ");
                if(attrib.value & EGL_PIXMAP_BIT)
                    _tmp.append("pixmap, ");
                if(attrib.value & EGL_WINDOW_BIT)
                    _tmp.append("window, ");
                if(attrib.value & EGL_VG_COLORSPACE_LINEAR_BIT)
                    _tmp.append("VG colorspace linear, ");
                if(attrib.value & EGL_VG_ALPHA_FORMAT_PRE_BIT)
                    _tmp.append("VG alpha format, ");
                if(attrib.value & EGL_MULTISAMPLE_RESOLVE_BOX_BIT)
                    _tmp.append("multisample resolve box, ");
                if(attrib.value & EGL_SWAP_BEHAVIOR_PRESERVED_BIT)
                    _tmp.append("swap preserved, ");

                if(!_tmp.empty())
                    _tmp = _tmp.substr(0, _tmp.length() - 2);
                FG_LOG::PrintDebug("EGL: [%s] %s: %s", attrib.enumName, attrib.comment, _tmp.c_str());
                break;
            case EGL_CONFORMANT:
                // ?
                break;
            default:
                FG_LOG::PrintDebug("EGL: [%s] %s: %d", attrib.enumName, attrib.comment, (int)attrib.value);
                break;
        };
    }
}

#endif /* FG_USING_EGL */