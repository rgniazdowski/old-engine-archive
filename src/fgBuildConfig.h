/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine™
 * ______  _              _  _____                         
 * |  ___|| |            (_)|  __ \                        
 * | |_   | |  ___ __  __ _ | |  \/  __ _  _ __ ___    ___ 
 * |  _|  | | / _ \\ \/ /| || | __  / _` || '_ ` _ \  / _ \
 * | |    | ||  __/ >  < | || |_\ \| (_| || | | | | ||  __/
 * \_|    |_| \___|/_/\_\|_| \____/ \__,_||_| |_| |_| \___|
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
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

#undef FG_VERBOSE
#undef FG_VERBOSE_LEVEL

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
#undef FG_USING_SDL						//  Is the SDL1.x used?
#undef FG_USING_SDL2					//  Is the latest SDL2 used in this build?
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
#undef FG_USING_PLATFORM_MACOSX			//	Is the target platform MACOS/X
#undef FG_USING_CYGWIN					//	Is Cygwin used for current build?
#undef FG_USING_MINGW					//	Is MinGW used for current build?
#undef FG_USING_VISUAL_STUDIO			//  Does the build system run under Visual Studio (any version)?
#undef FG_USING_QT						//	Does the build system run under QtCreator (any version)?
#undef FG_USING_PLUGINS					//	Is Plugin Subsystem used in this build?
#undef FG_USING_WXWIDGETS				//  Is wxWidgets GUI library used in this build?
#undef FG_SUPPORT_WXWIDGETS				//  Is wxWidgets enabled/supported in this build?

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

#if defined __gnu_linux__ || defined __linux__ || defined linux || defined __linux
#define FG_USING_PLATFORM_LINUX
#endif

#if defined __CYGWIN__
#define FG_USING_CYGWIN
#endif

#if defined __MINGW__ || defined __MINGW32__ || defined __MINGW64__
#define FG_USING_MINGW
#endif

#if (defined __APPLE__ && defined __MACH__) || defined Macintosh || defined macintosh
#define FG_USING_PLATFORM_MACOSX
#endif

#if !defined FG_USING_MARMALADE && ( defined __WINDOWS__ || defined __WIN32__ || defined _WIN32 || defined _WIN64 || defined __TOS_WIN__ || defined WIN32 || defined win32)
#define FG_USING_PLATFORM_WINDOWS
#endif

#if defined _MSC_VER
#define FG_USING_VISUAL_STUDIO
#endif

#if defined _DEBUG && !defined DEBUG
#define DEBUG 1
#endif

#if defined IW_DEBUG
#undef DEBUG
#define DEBUG 1
#define FG_DEBUG 1
#endif

#if defined FG_DEBUG
#define FG_VERBOSE_LEVEL 3
#define FG_VERBOSE
#else
#define FG_VERBOSE_LEVEL 1
#define FG_VERBOSE
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

// Compatibility for sensors
#ifdef FG_USING_MARMALADE_SENSORS
#define FG_USING_SENSORS
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

// Under linux - use plain GL
#ifdef FG_USING_PLATFORM_LINUX
#ifndef FG_USING_OPENGL
#define FG_USING_OPENGL
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

// Use TinyXML even on Linux
#ifdef FG_USING_PLATFORM_LINUX
#define FG_USING_TINYXML
#endif

/**************************** CROSS PLATFORM COMPATIBILITY ****************************/

#ifdef FG_USING_MARMALADE
#define GLM_FORCE_PURE
#endif

/*************************** OTHER DEFINITIONS / STRUCTURES ***************************/

//
// SPECIAL STRUCT DEFINITION - EASY ACCESS
//
struct fgBuildConfig {
	bool isDebug;
	bool isVerbose;
	int verboseLevel;
	bool usingMarmalade;			//	Is Marmalade framework used in this build?
	bool usingMarmaladeSensors;		//	Is Marmalades' sensor subsystem used?
	bool usingMarmaladeKeyboard;	//	Is Marmalades' keyboard event handled in this build?
	bool usingMarmaladeSound;		//	Is the s3eSound used?
	bool usingMarmaladeAudio;		//	Is the s3eAudio used?
	bool usingMarmaladeThreads;		//	Are Marmalades' threads used in this build?
	bool usingMarmaladeIwGX;		//	Is the IwGX subproject used?
	bool usingMarmaladeIwGL;		//	Is the IwGL subproject used in this build?
	bool usingMarmaladeOpenGLES;	//	Is the OpenGL ES used via Marmalade?
	bool usingOpenGLES;			//	Is the OpenGL ES used (will be also set when using OpenGL ES via Marmalade)?
	bool usingOpenGL;			//	Is the plain OpenGL used in this build?
	bool usingOpenGLGLU;		//	Is the GLU library used in this build?
	bool usingOpenGLGLUT;		//	Is the GLUT library used?
	bool usingOpenGLGLEW;		//	Is the GLEW library used?
	bool usingSDL;
	bool usingSDL2;
	bool usingOpenAL;			//	Is the OpenAL library used (for sound system) in this build?
	bool usingMarmaladeEGL;		//	Is the EGL used via Marmalade in this build?
	bool usingEGL;				//	Is the EGL library used in this build?
	bool usingSensors;			//	Are sensors used in this build?
	bool usingAudio;			//	Is audio used at all?
	bool usingThreads;			//	Are threads (non-Marmalade) used at all?
	bool usingDirectX;			//	Is the DirectX (any version) used in this build?
	bool usingDirectSound;		//	Is the DirectSound used?
	bool usingDPIInfo;			//	Is the DPI Info extension used (Marmalade needed)?
	bool usingTinyXML;			//	Is the tinyxml library used in this build?
	bool usingLUAPlus;			//	Is the enhanced Lua C API used?
	bool usingLUA;				//	Is the original Lua C API used?
	bool usingBullet;			//	Is the Bullet (physics engine) library used in this build?
	bool isPlatformWindows;		//	Is the target platform Windows in this build?
	bool isPlatformLinux;		//	Is the target platform Linux?
	bool isPlatformAndroid;		//	Is the target platform Android?
	bool isPlatformIOS;			//	Is the target platform iOS?
	bool isPlatformMACOSX;		//	Is the target platform MACOS/X
	bool usingCygwin;			//	Is Cygwin used for current build?
	bool usingMinGW;			//	Is MinGW used for current build?
	bool usingVisualStudio;		//  Does the build system run under Visual Studio (any version)?
	bool usingQT;				//	Does the build system run under QtCreator (any version)?
	bool usingPlugins;			//	Is Plugin Subsystem used in this build?
	bool using_wxWidgets;		//  Is wxWidgets GUI library used in this build?
	bool support_wxWidgets;		//  Is wxWidgets enabled/supported in this build?
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

extern struct fgBuildConfig g_fgBuildConfig;

#define FG_BUILD		g_fgBuildConfig
#define FG_BUILD_CONFIG	g_fgBuildConfig

#define FG_BUILD_DATE			__DATE__
#define FG_BUILD_TIME			__TIME__

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
#define FG_BUILD_VERSION_TEXT	FG_XSTR(FG_BUILD_VERSION_MAJ)"."FG_XSTR(FG_BUILD_VERSION_MIN)"."FG_XSTR(FG_BUILD_VERSION_REV)

// Package name - name of the engine
#define FG_PACKAGE_NAME			"FlexiGame"
// Code name of this version
#define FG_PROJECT_CODE_NAME	"Infinium"
#define FG_PREFIX				"fg"

// Package name with version and codename
#define FG_PACKAGE_FULL_TEXT	FG_PACKAGE_NAME" v"FG_BUILD_VERSION_TEXT" codename: "FG_PROJECT_CODE_NAME

// Full name of the project
#define FG_FULL_NAME			"Flexible Game Engine"
#define FG_AUTHOR_ALIAS			""
#define FG_PACKAGE_ALIAS		""

// Copyright text
#define FG_COPYRIGHT			"Copyright (C) Radoslaw Gniazdowski. All rights reserved."
// Copying text
#define FG_COPYING				FG_PACKAGE_NAME" source code and any related files can not be copied, modified and/or distributed without the express or written permission from the author."
// License type
#define FG_LICENSE				"Proprietary license" 
// Home page address
#define FG_HOMEPAGE				"http://flexigame.com"

#define FG_ENGINE
#define FG_FLEXIGAME
#define FG_JUST_FOR_FUN

#define FG_MOTTO				"Per aspera ad astra"

#endif /* _FG_BUILD_CONFIG_H_ */
/*************************** END MAIN MARMALADE BUILD CONFIG ***************************/
