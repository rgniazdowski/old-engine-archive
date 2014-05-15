/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_OGL_MAIN_H_
#define _FG_OGL_MAIN_H_

#include "../../fgBuildConfig.h"

#if defined FG_USING_MARMALADE

#if !defined FG_USING_MARMALADE_EGL && defined FG_USING_MARMALADE_IWGL
#include <IwGL.h>
#elif defined FG_USING_MARMALADE_OPENGL_ES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <EGL/egl.h>
#endif

#endif

#define FG_EGL_MAX_CONFIG 32

namespace OGL {

	bool initGL(void);
	void closeGL(void);
	
	void swapBuffers(void);

	int getScreenHeight(void);
	int getScreenWidth(void);

	void clearScreen(void);
};

#endif