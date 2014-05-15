/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_GFX_MAIN_H_
#define _FG_GFX_MAIN_H_

#include "MarmaladeOpenGL\OGLMain.h"

#include "fgGFXPerspectiveView.h"
#include "fgGFXOrthoView.h"

namespace FG_GFX {

	inline bool initGFX(void) {
		return OGL::initGL();
	}

	inline void closeGFX(void) {
		// FIXME
		OGL::closeGL();
	}
	
	inline void swapBuffers(void) {
		OGL::swapBuffers();
	}

	inline int getScreenHeight(void) {
		return OGL::getScreenHeight();
	}

	inline int getScreenWidth(void) {
		return OGL::getScreenWidth();
	}

	inline void clearScreen(void) {
		OGL::clearScreen();
	}
};

#endif
