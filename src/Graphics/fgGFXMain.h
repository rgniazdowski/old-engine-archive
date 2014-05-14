#ifndef _FG_GFX_MAIN_H
#define _FG_GFX_MAIN_H

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
