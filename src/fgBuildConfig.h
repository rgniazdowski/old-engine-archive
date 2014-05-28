/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

// The build config is used to configure the whole engine at compile time.
// The whole idea of using macros to add or remove big chunks of code is to
// generate different executables depending on the target platform, build platform
// and libraries availability on the current system. 
//
// Also after this config file other config files can be included to alter defined macros.
//
// Build config can be also used to build dynamic or static library, and use parts
// of the engine like plugins or in a different build.
#ifndef _FG_BUILD_CONFIG_H_
#define _FG_BUILD_CONFIG_H_

#undef FG_USING_MARMALADE				//	Is Marmalade framework used in this build?
#undef FG_USING_MARMALADE_SENSORS		//	Is Marmalades' sensor subsystem used?
#undef FG_USING_MARMALADE_KEYBOARD		//	Is Marmalades' keyboard event handled in this build?
#undef FG_USING_MARMALADE_SOUND			//	Is the s3eSound used?
#undef FG_USING_MARMALADE_AUDIO			//	Is the s3eAudio used?
#undef FG_USING_MARMALADE_THREADS		//	Are Marmalades' threads used in this build?
#undef FG_USING_MARMALADE_IWGX			//	Is the IwGX subproject used?
#undef FG_USING_MARMALADE_IWGL			//	Is the IwGL subproject used in this build?
#undef FG_USING_MARMALADE_OPENGL_ES		//	Is the OpenGL ES used via Marmalade?
#undef FG_USING_OPENGL_ES				//	Is the OpenGL ES used (will be also set when using OpenGL ES via Marmalade)?
#undef FG_USING_OPENGL					//	Is the plain OpenGL used in this build?
#undef FG_USING_OPENGL_GLU				//	Is the GLU library used in this build?
#undef FG_USING_OPENGL_GLUT				//	Is the GLUT library used?
#undef FG_USING_OPENGL_GLEW				//	Is the GLEW library used?
#undef FG_USING_SDL
#undef FG_USING_SDL2
#undef FG_USING_OPENAL					//	Is the OpenAL library used (for sound system) in this build?
#undef FG_USING_MARMALADE_EGL			//	Is the EGL used via Marmalade in this build?
#undef FG_USING_EGL						//	Is the EGL library used in this build?
#undef FG_USING_SENSORS					//	Are sensors used in this build?
#undef FG_USING_AUDIO					//	Is audio used at all?
#undef FG_USING_THREADS					//	Are threads (non-Marmalade) used at all?
#undef FG_USING_DIRECTX					//	Is the DirectX (any version) used in this build?
#undef FG_USING_DIRECTSOUND				//	Is the DirectSound used?
#undef FG_USING_DPI_INFO				//	Is the DPI Info extension used (Marmalade needed)?
#undef FG_USING_TINYXML					//	Is the tinyxml library used in this build?
#undef FG_USING_LUA_PLUS				//	Is the enhanced Lua C API used?
#undef FG_USING_LUA						//	Is the original Lua C API used?
#undef FG_USING_BULLET					//	Is the Bullet (physics engine) library used in this build?
#undef FG_USING_PLATFORM_WINDOWS		//	Is the target platform Windows in this build?
#undef FG_USING_PLATFORM_LINUX			//	Is the target platform Linux?
#undef FG_USING_PLATFORM_ANDROID		//	Is the target platform Android?
#undef FG_USING_PLATFORM_IOS			//	Is the target platform iOS?
#undef FG_USING_PLATFORM_MACOS			//	Is the target platform MACOS/X
#undef FG_USING_CYGWIN					//	Is Cygwin used for current build?
#undef FG_USING_MINGW					//	Is MinGW used for current build?
#undef FG_USING_VISUAL_STUDIO			//  Does the build system run under Visual Studio (any version)?
#undef FG_USING_QT						//	Does the build system run under QtCreator (any version)?


/*************************** CURRENT TARGET PLATFORM / BUILD SYSTEM ***************************/

// Well this build of course is using Marmalade, need to define it to use properly in the code, which needs to be multiplatform
// (not only via marmalade - this means also windows and linux)
#if defined IW_PLATFORM_S3E || defined I3D_PLATFORM_S3E || defined I3D_OS_S3E || defined IW_SDK
#define FG_USING_MARMALADE
#endif

#if defined I3D_ARCH_X86
#define FG_USING_X86
#endif

#if defined S3E_ANDROID_X86
#define FG_USING_PLATFORM_ANDROID
#endif

#if defined __gnu_linux__
#define FG_USING_PLATFORM_LINUX
#endif

#if defined __CYGWIN__
#define FG_USING_CYGWIN
#endif

#if defined __MINGW__
#define FG_USING_MINGW
#endif

#if (defined __APPLE__ && defined __MACH__) || defined Macintosh || defined macintosh
#define FG_USING_PLATFORM_MACOS
#endif

#if !defined FG_USING_MARMALADE && ( defined __WINDOWS__ || defined __WIN32__ || defined _WIN32 || defined _WIN64 || defined __TOS_WIN__ || defined WIN32 || defined win32)
#define FG_USING_PLATFORM_WINDOWS
#endif

#if defined _MSC_VER
#define FG_USING_VISUAL_STUDIO
#endif

#if defined _DEBUG && !defined DEBUG
#define DEBUG
#endif

#if defined IW_DEBUG
#undef DEBUG
#define DEBUG 1
#define FG_DEBUG 1
#endif


/*************************** SUBSYSTEM / INPUT / AUDIO SUPPORT ***************************/


// This defines whether Marmalade's sensors will be used in the project
#ifdef FG_USING_MARMALADE
#define FG_USING_MARMALADE_SENSORS
// This defines whether Marmalade's event subsystem should be used for getting the keyboard events
#define FG_USING_MARMALADE_KEYBOARD
#endif

// Marmalade's sounds subsystem 
#ifdef FG_USING_MARMALADE
#define FG_USING_MARMALADE_SOUND
// Marmalade's audio subsystem, used along with s3eSound *FIXME*
#define FG_USING_MARMALADE_AUDIO
// This tells the game engine that sound/audio will be used (any type)
#define FG_USING_AUDIO
#endif

// Marmalade's implementation of Threads need's to be used in the project
#ifdef FG_USING_MARMALADE
#define FG_USING_MARMALADE_THREADS
#endif

// This tells the game engine that OpenGL/ES is used via Marmalade API
#ifdef FG_USING_MARMALADE
//#define FG_USING_MARMALADE_IWGL // #FIXME
#define FG_USING_MARMALADE_OPENGL_ES
// FlexiGame will be using Marmalade's EGL instead of calling IwGL functions
#ifndef FG_USING_MARMALADE_IWGX
#define FG_USING_MARMALADE_EGL
#endif
#endif


/*************************** GRAPHICS SPECIFIC ***************************/

#ifdef FG_USING_MARMALADE_OPENGL_ES
#ifndef FG_USING_OPENGL_ES
// This for compability as some parts using OpenGL ES will be just the same as the parts 'depending' on Marmalade
#define FG_USING_OPENGL_ES
#endif
#endif

#ifdef FG_USING_MARMALADE_EGL
#ifndef FG_USING_EGL
// This for compability as some parts using EGL will be just the same as the parts (if not all) 'depending' on Marmalade
#define FG_USING_EGL
#endif
#endif


/*************************** EXTENSIONS / PLUGINS SUPPORT ***************************/


// Now this is just a general define for threads, I think it wont be used as more specific defines will occur in the future
// (depending on the OS and available API) // #FIXME
//#define FG_USING_THREADS

// Engine will include the DPI info extension, but only if Marmalade is activated for this code build
#ifdef FG_USING_MARMALADE
#if defined IW_MKF_DPIEXT || IW_MKF_DPI
#define FG_USING_DPI_INFO
#endif
// Engine will use the tiny xml lib - #FIXME tinyxml should also be used for other builds, but currently there is no config for that at all...
#if defined IW_MKF_TINYXML
#define FG_USING_TINYXML
#endif
#endif

//#define FG_USING_LUA
// Engine for scripting will be using the Lua Plus extension
//#define FG_USING_LUA_PLUS
// For handling physics the Bullet library will be used
//#define FG_USING_BULLET

#endif
/*************************** END MAIN BUILD CONFIG ***************************/
