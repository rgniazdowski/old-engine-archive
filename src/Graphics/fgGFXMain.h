/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_GFX_MAIN_H_
#define _FG_GFX_MAIN_H_

#include "../fgBuildConfig.h"

#if defined FG_USING_MARMALADE

#if !defined FG_USING_MARMALADE_EGL && defined FG_USING_MARMALADE_IWGL
#include <IwGL.h>
#elif defined FG_USING_MARMALADE_OPENGL_ES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <EGL/egl.h>

#define FG_EGL_MAX_CONFIG 32
#endif

#endif

#include "fgGFXPerspectiveView.h"
#include "fgGFXOrthoView.h" // is this really necessary?

// This namespace contains all required drawing related functions, structures and classes, usage within other parts of the engine
// should be quite straighforward and giving the feeling of platform independence
namespace FG_GFX {

	// Init the whole GFX subsystem - set the screen and other
	bool initGFX(void);
	// Close the subsystem - destroy the graphics context
	void closeGFX(void);
	// Swap the screen buffers
	void swapBuffers(void);
	// Return the screen height in pixels
	int getScreenHeight(void);
	// Return the screen width in pixels
	int getScreenWidth(void);
	// Clear the screen and depth buffer
	void clearScreen(void);
};

#endif /* _FG_GFX_MAIN_H_ */ 
