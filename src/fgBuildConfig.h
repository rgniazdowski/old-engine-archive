/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 * ______  _              _  _____                         
 * |  ___|| |            (_)|  __ \                        
 * | |_   | |  ___ __  __ _ | |  \/  __ _  _ __ ___    ___ 
 * |  _|  | | / _ \\ \/ /| || | __  / _` || '_ ` _ \  / _ \
 * | |    | ||  __/ >  < | || |_\ \| (_| || | | | | ||  __/
 * \_|    |_| \___|/_/\_\|_| \____/ \__,_||_| |_| |_| \___|
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

// The build config is used to configure the whole engine at compile time.
// The whole idea of using macros to add or remove big chunks of code is to
// generate different executables depending on the target platform, build platform
// and libraries availability on the current system.
//
// Also after this config file other config files can be included to alter defined macros.
//
// Build config can be also used to build dynamic or static library, and use parts
// of the engine like plugins or in a different build.
#ifndef FG_INC_BUILD_CONFIG
    #define FG_INC_BUILD_CONFIG
    #define FG_INC_BUILD_CONFIG_BLOCK


    #define FG_VERBOSE_LVL_NONE		0 // report only critical errors - no warnings, info, status etc
    #define FG_VERBOSE_LVL_LOW		1 // report only errors
    #define FG_VERBOSE_LVL_MEDIUM	2 // report only errors and warnings (+info, success)
    #define FG_VERBOSE_LVL_HIGH		3 // report everything: Info, Status, Warning, Debug, Errors and others

// #FIXME
//#define FG_MESSAGES

    #ifndef FG_NO_UNDEF

        #undef FG_VERBOSE
        #undef FG_VERBOSE_LEVEL

        #undef FG_USING_MARMALADE                       //  Is Marmalade framework used in this build?
        #undef FG_USING_MARMALADE_SENSORS               //  Is Marmalades' sensor subsystem used?
        #undef FG_USING_MARMALADE_KEYBOARD              //  Is Marmalades' keyboard event handled in this build?
        #undef FG_USING_MARMALADE_SOUND                 //  Is the s3eSound used?
        #undef FG_USING_MARMALADE_AUDIO                 //  Is the s3eAudio used?
        #undef FG_USING_MARMALADE_THREADS               //  Are Marmalades' threads used in this build?
        #undef FG_USING_MARMALADE_IWGX                  //  Is the IwGX subproject used?
        #undef FG_USING_MARMALADE_IWGL                  //  Is the IwGL subproject used in this build?
        #undef FG_USING_MARMALADE_OPENGL_ES             //  Is the OpenGL ES used via Marmalade?
        #undef FG_USING_OPENGL_ES                       //  Is the OpenGL ES used (will be also set when using OpenGL ES via Marmalade)?
        #undef FG_USING_OPENGL                          //  Is the plain OpenGL used in this build?
        #undef FG_USING_OPENGL_GLU                      //  Is the GLU library used in this build?
        #undef FG_USING_OPENGL_GLUT                     //  Is the GLUT library used?
        #undef FG_USING_OPENGL_GLEW                     //  Is the GLEW library used?
        #undef FG_USING_GL_BINDING                      //  Is the glbinding module used?
        #undef FG_USING_GLM                             //  Is the OpenGL Mathemathics library (GLM) used? 
        #undef FG_USING_SDL                             //  Is the SDL1.x used?
        #undef FG_USING_SDL2                            //  Is the latest SDL2 used in this build?
        #undef FG_USING_SDL_MIXER                       //  Is the latest SDL/SDL2 mixer library used in this build?
        #undef FG_USING_OPENAL                          //  Is the OpenAL library used (for sound system) in this build?
        #undef FG_USING_MARMALADE_EGL                   //  Is the EGL used via Marmalade in this build?
        #undef FG_USING_EGL                             //  Is the EGL library used in this build?
        #undef FG_USING_SENSORS                         //  Are sensors used in this build?
        #undef FG_USING_AUDIO                           //  Is audio used at all?
        #undef FG_USING_THREADS                         //  Are threads (non-Marmalade) used at all?
        #undef FG_USING_DIRECTX                         //  Is the DirectX (any version) used in this build?
        #undef FG_USING_DIRECTSOUND                     //  Is the DirectSound used?
        #undef FG_USING_DPI_INFO                        //  Is the DPI Info extension used (Marmalade needed)?
        #undef FG_USING_TINYXML                         //  Is the tinyxml library used in this build?
        #undef FG_USING_LUA_PLUS                        //  Is the enhanced Lua C API used?
        #undef FG_USING_LUA                             //  Is the original Lua C API used?
        #undef FG_USING_BULLET                          //  Is the Bullet (physics engine) library used in this build?
        #undef FG_USING_ASSIMP                          //  Is the Open Asset Import Library used in this build?
        #undef FG_USING_PLATFORM_WINDOWS                //  Is the target platform Windows in this build?
        #undef FG_USING_PLATFORM_LINUX                  //  Is the target platform Linux?
        #undef FG_USING_PLATFORM_ANDROID                //  Is the target platform Android?
        #undef FG_USING_PLATFORM_IOS                    //  Is the target platform iOS?
        #undef FG_USING_PLATFORM_MOBILE                 //  Is the target platform mobile? (Android/iOS/Other)
        #undef FG_USING_PLATFORM_MACOSX                 //  Is the target platform MACOS/X
        #undef FG_USING_CYGWIN                          //  Is Cygwin used for current build?
        #undef FG_USING_MINGW                           //  Is MinGW used for current build?
        #undef FG_USING_VISUAL_STUDIO                   //  Does the build system run under Visual Studio (any version)?
        #undef FG_USING_QT                              //  Does the build system run under QtCreator (any version)?
        #undef FG_USING_PLUGINS                         //  Is Plugin Subsystem used in this build?
        #undef FG_USING_WXWIDGETS                       //  Is wxWidgets GUI library used in this build?
        #undef FG_SUPPORT_WXWIDGETS                     //  Is wxWidgets enabled/supported in this build?

    #endif /* FG_NO_UNDEF */
/*************************** CURRENT TARGET PLATFORM / BUILD SYSTEM ***************************/

// Well this build of course is using Marmalade, need to define it to use properly in the code, which needs to be multiplatform
// (not only via marmalade - this means also windows and linux)
    #if defined IW_PLATFORM_S3E || defined I3D_PLATFORM_S3E || defined I3D_OS_S3E || defined IW_SDK
        #define FG_USING_MARMALADE
    #endif

    #if defined(I3D_ARCH_X86)
        #define FG_USING_X86
    #endif

    #if defined(S3E_ANDROID_X86)
        #define FG_USING_PLATFORM_ANDROID
    #endif

    #if defined(__gnu_linux__) || defined(__linux__) || defined(linux) || defined(__linux)
        #define FG_USING_PLATFORM_LINUX
    #endif

    #if defined(ANDROID) || defined(__ANDROID__)
        #undef ANDROID
        #undef __ANDROID__
        #define ANROID 1
        #define __ANDROID__ 1
        #define FG_USING_PLATFORM_ANDROID
        #undef FG_USING_PLATFORM_LINUX
        #undef linux
        #undef __LINUX__
        #undef LINUX        
    #endif

    #if defined(__CYGWIN__)
        #define FG_USING_CYGWIN
    #endif

    #if defined(__MINGW__) || defined(__MINGW32__) || defined(__MINGW64__)
        #define FG_USING_MINGW
    #endif

    #if (defined(__APPLE__) && defined(__MACH__)) || defined(Macintosh) || defined (macintosh)
        #define FG_USING_PLATFORM_MACOSX
    #endif

    #if !defined(FG_USING_MARMALADE) && ( defined __WINDOWS__ || defined __WIN32__ || defined _WIN32 || defined _WIN64 || defined __TOS_WIN__ || defined WIN32 || defined win32)
        #define FG_USING_PLATFORM_WINDOWS
    #endif

    #if defined(_MSC_VER)
        #define FG_USING_VISUAL_STUDIO
    #endif

    #if defined(_DEBUG) || defined(DEBUG) || defined(IW_DEBUG)
        #undef	DEBUG
        #define DEBUG		1
        #undef FG_DEBUG
        #define FG_DEBUG	1
    #endif

    #if defined(FG_DEBUG)
        #ifndef FG_VERBOSE_LEVEL
            #define FG_VERBOSE_LEVEL FG_VERBOSE_LVL_HIGH
            #define FG_VERBOSE
        #endif
    #else
        #ifndef FG_VERBOSE_LEVEL
            #define FG_VERBOSE_LEVEL FG_VERBOSE_LVL_LOW
            #define FG_VERBOSE
        #endif
    #endif

    #if defined(_RELEASE) || defined(__release) || !defined(FG_DEBUG)
        #undef FG_RELEASE
        #define FG_RELEASE 1
        #undef FG_DEBUG
        #undef _DEBUG
        #undef DEBUG
    #endif

/*************************** SUBSYSTEM / INPUT / AUDIO SUPPORT ***************************/


// This defines whether Marmalade's sensors will be used in the project
    #if defined(FG_USING_MARMALADE)
        #define FG_USING_MARMALADE_SENSORS
// This defines whether Marmalade's event subsystem should be used for getting the keyboard events
        #define FG_USING_MARMALADE_KEYBOARD
    #endif

// Marmalade's sounds subsystem
    #if defined(FG_USING_MARMALADE)
        #define FG_USING_MARMALADE_SOUND
// Marmalade's audio subsystem, used along with s3eSound *FIXME*
        #define FG_USING_MARMALADE_AUDIO
// This tells the game engine that sound/audio will be used (any type)
        #define FG_USING_AUDIO
    #endif

// Marmalade's implementation of Threads need's to be used in the project
    #if defined(FG_USING_MARMALADE)
        #define FG_USING_MARMALADE_THREADS
    #endif

// This tells the game engine that OpenGL/ES is used via Marmalade API
    #if defined(FG_USING_MARMALADE)
//#define FG_USING_MARMALADE_IWGL // #FIXME
        #define FG_USING_MARMALADE_OPENGL_ES
// FlexiGame will be using Marmalade's EGL instead of calling IwGL functions
        #if !defined(FG_USING_MARMALADE_IWGX)
            #define FG_USING_MARMALADE_EGL
        #endif
    #endif

// Compatibility for sensors
    #if defined(FG_USING_MARMALADE_SENSORS)
        #define FG_USING_SENSORS
    #endif

    #if defined(FG_USING_MARMALADE_THREADS)
        #ifndef FG_USING_THREADS
            #define FG_USING_THREADS
        #endif
    #endif

/*************************** GRAPHICS SPECIFIC ***************************/

    #if defined(FG_USING_MARMALADE_OPENGL_ES)
        #if !defined(FG_USING_OPENGL_ES)
// This for compability as some parts using OpenGL ES will be just the same as the parts 'depending' on Marmalade
            #define FG_USING_OPENGL_ES
        #endif
    #endif

    #if defined(FG_USING_MARMALADE_EGL)
        #if !defined(FG_USING_EGL)
// This for compability as some parts using EGL will be just the same as the parts (if not all) 'depending' on Marmalade
            #define FG_USING_EGL
        #endif
    #endif

// Under linux - use plain GL
    #if defined(FG_USING_PLATFORM_LINUX)
        #if !defined(FG_USING_OPENGL)
            #define FG_USING_OPENGL
        #endif
    #endif

///////////////// ANDROID DEFAULTS ////////////////////////////////////////////

// Under android - use OGLES2 - 2.0 is default - 1.0 unused/unsupported
    #if defined(FG_USING_PLATFORM_ANDROID)
        #undef FG_USING_OPENGL_ES
        #define FG_USING_OPENGL_ES
        #undef FG_USING_EGL
        #undef FG_USING_MARMALADE_EGL
    #endif

// Under android - almost certain that build using Android SDK
// Usage only with SDL2
    #if defined(FG_USING_PLATFORM_ANDROID)
        #undef FG_USING_SDL2
        #define FG_USING_SDL2
    #endif

// Under android - always use lua plus - hard coded
    #if defined(FG_USING_PLATFORM_ANDROID)
        #undef FG_USING_LUA_PLUS
        #define FG_USING_LUA_PLUS
    #endif

// Android
    #if defined(FG_USING_PLATFORM_ANDROID)
        #define FG_USING_TINYXML
        #undef TIXML_USE_STL // When using Android - do not use STL in TinyXML
    #endif

/*************************** EXTENSIONS / PLUGINS SUPPORT ***************************/


// Now this is just a general define for threads, I think it wont be used as more specific defines will occur in the future
// (depending on the OS and available API) // #FIXME
//#define FG_USING_THREADS

// Engine will include the DPI info extension, but only if Marmalade is activated for this code build
    #if defined(FG_USING_MARMALADE)
        #if defined(IW_MKF_DPIEXT) || defined(IW_MKF_DPI)
            #define FG_USING_DPI_INFO
        #endif
// Engine will use the tiny xml lib - #FIXME tinyxml should also be used for other builds, but currently there is no config for that at all...
        #if defined(IW_MKF_TINYXML)
            #define FG_USING_TINYXML
        #endif
    #endif

//#define FG_USING_LUA
// Engine for scripting will be using the Lua Plus extension
//#define FG_USING_LUA_PLUS
// For handling physics the Bullet library will be used
//#define FG_USING_BULLET

// Use TinyXML even on Linux
    #if defined(FG_USING_PLATFORM_LINUX)
        #if !defined(FG_USING_TINYXML)
            #define FG_USING_TINYXML
        #endif
    #endif

// Use TinyXML also on Android
    #if defined(FG_USING_PLATFORM_ANDROID)
        #if !defined(FG_USING_TINYXML)
            #define FG_USING_TINYXML
            #undef TIXML_USE_STL // on android TinyXML should not use STL
        #endif
    #endif

/**************************** CROSS PLATFORM COMPATIBILITY ****************************/

// Always (as default) us OpenGL Mathemathics library
    #ifndef FG_USING_GLM
        #define FG_USING_GLM
    #endif
// As default force radians as standard paramater type for angles
    #ifdef FG_USING_GLM
        #ifndef GLM_FORCE_RADIANS
            #define GLM_FORCE_RADIANS
        #endif
        #if !defined(GLM_MESSAGES) && defined(FG_DEBUG) && defined(FG_MESSAGES)
            #define GLM_MESSAGES
        #endif
    #endif

// Build for marmalade needs to use pure GLM
    #ifdef FG_USING_MARMALADE
        #if defined FG_USING_GLM
            #define GLM_FORCE_PURE
            #ifdef I3D_ARCH_ARM
                #define GLM_FORCE_CXX03
            #endif
        #endif
    #endif

// Force TinyXml to use STL
    #if defined(FG_USING_TINYXML)
        #if !defined(TIXML_USE_STL) && !defined(FG_USING_PLATFORM_ANDROID)
            #define TIXML_USE_STL
        #endif
    #endif

// No profiling in Bullet physics engine
    #if defined(FG_USING_BULLET)
        // if btScalar was 'double' instead of 'float' there would be a problem
        // with data copying from btTransform to fg::Matrix4f
        #undef BT_USE_DOUBLE_PRECISION // just floats for now...
        #undef BT_NO_PROFILE
        #define BT_NO_PROFILE 1
    #endif

/************************************* AUDIO / SOUND FIX ******************************/

    #if defined(FG_USING_SDL2)
        #if !defined(FG_USING_AUDIO)
            #define FG_USING_AUDIO
            #define FG_USING_SDL_MIXER
        #endif
    #endif

    #if defined(FG_USING_SDL)
        #if !defined(FG_USING_AUDIO)
            #define FG_USING_AUDIO
            #define FG_USING_SDL_MIXER
        #endif
    #endif

/********************************* SCRIPTING / LUA SUPPORT ****************************/

    #if defined(FG_USING_LUA_PLUS)
        #if !defined(LUAPLUS_DUMPOBJECT)
            #define LUAPLUS_DUMPOBJECT 1
        #endif
    #endif

    #if defined(FG_USING_LUA) || defined(FG_USING_LUA_PLUS)
        #if !defined(LUA_OPNAMES)
            #define LUA_OPNAMES 1
        #endif
        #if !defined(LUA_COMPAT_APIINTCASTS)
            #define LUA_COMPAT_APIINTCASTS 1
        #endif
        #if !defined(LUA_USE_MKSTEMP) && defined(FG_USING_PLATFORM_LINUX)
            #define LUA_USE_MKSTEMP 1
        #endif
    #endif

/*************************** OTHER DEFINITIONS / STRUCTURES ***************************/

    #if defined(FG_USING_PLATFORM_ANDROID) || defined(FG_USING_PLATFORM_IOS) || defined(FG_USING_MARMALADE)
        #undef FG_USING_PLATFORM_MOBILE
        #define FG_USING_PLATFORM_MOBILE
    #endif

//
// SPECIAL STRUCT DEFINITION - EASY ACCESS
//
namespace fg {

    struct SBuildConfig {
        bool isDebug;
        bool isVerbose;
        int verboseLevel;
        bool usingMarmalade; //     Is Marmalade framework used in this build?
        bool usingMarmaladeSensors; //  Is Marmalade sensor subsystem used?
        bool usingMarmaladeKeyboard; // Is Marmalade keyboard event handled in this build?
        bool usingMarmaladeSound; //	Is the s3eSound used?
        bool usingMarmaladeAudio; //Is the s3eAudio used?
        bool usingMarmaladeThreads; //  Are Marmalade threads used in this build?
        bool usingMarmaladeIwGX; // Is the IwGX subproject used?
        bool usingMarmaladeIwGL; // Is the IwGL subproject used in this build?
        bool usingMarmaladeOpenGLES; // Is the OpenGL ES used via Marmalade?
        bool usingOpenGLES; //      Is the OpenGL ES used (will be also set when using OpenGL ES via Marmalade)?
        bool usingOpenGL; //        Is the plain OpenGL used in this build?
        bool usingOpenGLGLU; //	Is the GLU library used in this build?
        bool usingOpenGLGLUT; //    Is the GLUT library used?
        bool usingOpenGLGLEW; //    Is the GLEW library used?
        bool usingGLM; //           Is the OpenGL Mathemathics library (GLM) used?
        bool usingSDL;
        bool usingSDL2;
        bool usingSDLMixer; //      Is the latest SDL/SDL2 mixer library used in this build?
        bool usingOpenAL; //        Is the OpenAL library used (for sound system) in this build?
        bool usingMarmaladeEGL; //  Is the EGL used via Marmalade in this build?
        bool usingEGL; //           Is the EGL library used in this build?
        bool usingSensors; //	Are sensors used in this build?
        bool usingAudio; //         Is audio used at all?
        bool usingThreads; //       Are threads (non-Marmalade) used at all?
        bool usingDirectX; //       Is the DirectX (any version) used in this build?
        bool usingDirectSound; //   Is the DirectSound used?
        bool usingDPIInfo; //       Is the DPI Info extension used (Marmalade needed)?
        bool usingTinyXML; //       Is the tinyxml library used in this build?
        bool usingLUAPlus; //       Is the enhanced Lua C API used?
        bool usingLUA; //           Is the original Lua C API used?
        bool usingBullet; //        Is the Bullet (physics engine) library used in this build?
        bool usingAssimp; //        Is the Open Asset Import Library used in this build?
        bool isPlatformWindows; //  Is the target platform Windows in this build?
        bool isPlatformLinux; //    Is the target platform Linux?
        bool isPlatformAndroid; //  Is the target platform Android?
        bool isPlatformIOS; //      Is the target platform iOS?
        bool isPlatformMobile; //   Is the target platform mobile?
        bool isPlatformMACOSX; //   Is the target platform MACOS/X
        bool usingCygwin; //        Is Cygwin used for current build?
        bool usingMinGW; //         Is MinGW used for current build?
        bool usingVisualStudio; //  Does the build system run under Visual Studio (any version)?
        bool usingQT; //            Does the build system run under QtCreator (any version)?
        bool usingPlugins; //       Is Plugin Subsystem used in this build?
        bool using_wxWidgets; //    Is wxWidgets GUI library used in this build?
        bool support_wxWidgets; //  Is wxWidgets enabled/supported in this build?
        int version;
        int versionMajor;
        int versionMinor;
        int versionRevision;
        const char *buildDate;
        const char *buildTime;
        const char *buildVersionText;
        const char *packageName;
        const char *packageFullText;
        int empty;
    };

    extern struct SBuildConfig g_BuildConfig;
}

    #define FG_BUILD		::fg::g_BuildConfig
    #define FG_BUILD_CONFIG	::fg::g_BuildConfig

    #define FG_BUILD_DATE	__DATE__
    #define FG_BUILD_TIME	__TIME__

    #define FG_XSTR(S)	FG_STR(S)
    #define FG_STR(S)	#S

// Major part of the version
    #define FG_BUILD_VERSION_MAJ	0
// Minor part of the version
    #define FG_BUILD_VERSION_MIN	10
// Revision part
    #define FG_BUILD_VERSION_REV	0

// #FIXME
// Build version number [Major]*.[Minor].[Revision]
// Build version as number, 100 means 0.10.0;
// 1000 means 1.0.0, 1010 means 1.1.0, 1011 means: 1.1.1
// Last digit means revision (it is always one digit)
// next two digits (from back) are minor part of version, so 01 is 1, 10 is 10
// first digits (if any) are always version.
// To wrap it up: last 3 digits are: MM.R, if no Major number is specified
// It means that Major is 0.
    #define FG_BUILD_VERSION		(FG_BUILD_VERSION_MAJ*1000+FG_BUILD_VERSION_MIN*10+FG_BUILD_VERSION_REV)
// Stringified version number
    #define FG_BUILD_VERSION_STR	FG_XSTR(FG_BUILD_VERSION)
// Version text, parts separated by .
    #define FG_BUILD_VERSION_TEXT	FG_XSTR(FG_BUILD_VERSION_MAJ)"." FG_XSTR(FG_BUILD_VERSION_MIN)"." FG_XSTR(FG_BUILD_VERSION_REV)

// Package name - name of the engine
    #define FG_PACKAGE_NAME		"FlexiGame"
// Code name of this version
    #define FG_PROJECT_CODE_NAME	"Infinium"
    #define FG_PREFIX                   "fg"

// Package name with version and codename
    #define FG_PACKAGE_FULL_TEXT            FG_PACKAGE_NAME" v" FG_BUILD_VERSION_TEXT" codename: " FG_PROJECT_CODE_NAME

// Full name of the project
    #define FG_FULL_NAME                "Flexible Game Engine"
    #define FG_AUTHOR_ALIAS		"Vigilant One"
    #define FG_PACKAGE_ALIAS		"FG:E"

// Copyright text
    #define FG_COPYRIGHT		"Copyright (C) Radoslaw Gniazdowski. All rights reserved."
// Copying text
    #define FG_COPYING			FG_PACKAGE_NAME" source code and any related files can not be copied, modified and/or distributed without the express or written permission from the author."
// License type
    #define FG_LICENSE			"Proprietary license" 
// Home page address
    #define FG_HOMEPAGE			"http://flexigame.com"

    #define FG_ENGINE                   "FG Engine"
    #define FG_FLEXIGAME                "FlexiGame"
    #define FG_JUST_FOR_FUN             "Just for fun"

    #define FG_MOTTO			"The spice is vital for space travel"

    #undef FG_INC_BUILD_CONFIG_BLOCK
#endif /* FG_INC_BUILD_CONFIG */
/*************************** END MAIN MARMALADE BUILD CONFIG ***************************/
