/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgBuildConfig.h"

struct fgBuildConfig g_fgBuildConfig = {
#ifdef FG_DEBUG
	true,
#else
	false,
#endif
#ifdef FG_VERBOSE
	true,
#else
	false,
#endif
#ifdef FG_VERBOSE_LEVEL
	FG_VERBOSE_LEVEL,
#else
	0,
#endif
#ifdef FG_USING_MARMALADE
	true,
#else
	false,
#endif
#ifdef FG_USING_MARMALADE_SENSORS
	true,
#else
	false,
#endif
#ifdef FG_USING_MARMALADE_KEYBOARD
	true,
#else
	false,
#endif
#ifdef FG_USING_MARMALADE_SOUND
	true,
#else
	false,
#endif
#ifdef FG_USING_MARMALADE_AUDIO
	true,
#else
	false,
#endif
#ifdef FG_USING_MARMALADE_THREADS
	true,
#else
	false,
#endif
#ifdef FG_USING_MARMALADE_IWGX
	true,
#else
	false,
#endif
#ifdef FG_USING_MARMALADE_IWGL
	true,
#else
	false,
#endif
#ifdef FG_USING_MARMALADE_OPENGL_ES
	true,
#else
	false,
#endif
#ifdef FG_USING_OPENGL_ES
	true,
#else
	false,
#endif
#ifdef FG_USING_OPENGL
	true,
#else
	false,
#endif
#ifdef FG_USING_OPENGL_GLU
	true,
#else
	false,
#endif
#ifdef FG_USING_OPENGL_GLUT
	true,
#else
	false,
#endif
#ifdef FG_USING_OPENGL_GLEW
	true,
#else
	false,
#endif
#ifdef FG_USING_GLM
	true,
#else
	false,
#endif
#ifdef FG_USING_SDL
	true,
#else
	false,
#endif
#ifdef FG_USING_SDL2
	true,
#else
	false,
#endif
#ifdef FG_USING_OPENAL
	true,
#else
	false,
#endif
#ifdef FG_USING_MARMALADE_EGL
	true,
#else
	false,
#endif
#ifdef FG_USING_EGL
	true,
#else
	false,
#endif
#ifdef FG_USING_SENSORS
	true,
#else
	false,
#endif
#ifdef FG_USING_AUDIO
	true,
#else
	false,
#endif
#ifdef FG_USING_THREADS
	true,
#else
	false,
#endif
#ifdef FG_USING_DIRECTX
	true,
#else
	false,
#endif
#ifdef FG_USING_DIRECTSOUND
	true,
#else
	false,
#endif
#ifdef FG_USING_DPI_INFO
	true,
#else
	false,
#endif
#ifdef FG_USING_TINYXML
	true,
#else
	false,
#endif
#ifdef FG_USING_LUA_PLUS
	true,
#else
	false,
#endif
#ifdef FG_USING_LUA
	true,
#else
	false,
#endif
#ifdef FG_USING_BULLET
	true,
#else
	false,
#endif
#ifdef FG_USING_PLATFORM_WINDOWS
	true,
#else
	false,
#endif
#ifdef FG_USING_PLATFORM_LINUX
	true,
#else
	false,
#endif
#ifdef FG_USING_PLATFORM_ANDROID
	true,
#else
	false,
#endif
#ifdef FG_USING_PLATFORM_IOS
	true,
#else
	false,
#endif
#ifdef FG_USING_PLATFORM_MACOSX
	true,
#else
	false,
#endif
#ifdef FG_USING_CYGWIN
	true,
#else
	false,
#endif
#ifdef FG_USING_MINGW
	true,
#else
	false,
#endif
#ifdef FG_USING_VISUAL_STUDIO
	true,
#else
	false,
#endif
#ifdef FG_USING_QT
	true,
#else
	false,
#endif
#ifdef FG_USING_PLUGINS
	true,
#else
	false,
#endif
#ifdef FG_USING_WXWIDGETS
	true,
#else
	false,
#endif
#ifdef FG_SUPPORT_WXWIDGETS
	true,
#else
	false,
#endif
	FG_BUILD_VERSION,		// Build version number (for example 100)
	FG_BUILD_VERSION_MAJ,	// Major part of version
	FG_BUILD_VERSION_MIN,	// Minor part
	FG_BUILD_VERSION_REV,	// Revision
	FG_BUILD_DATE,		// date
	FG_BUILD_TIME,		// local time
	FG_BUILD_VERSION_TEXT,
	FG_PACKAGE_NAME,
	FG_PACKAGE_FULL_TEXT,
	///
	0 // empty
};
