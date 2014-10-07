/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_WINDOW_H_
#define _FG_GFX_WINDOW_H_

#include "fgGFXStdInc.h"

/*
 *
 */
class fgGfxWindow
{
public:
	// 
	fgGfxWindow();
	// 
	fgGfxWindow(const char *title, unsigned int width, unsigned int height);

	//
	~fgGfxWindow();

	//
	fgBool setup(const char *title, unsigned int width, unsigned int height);

	//
	fgBool close(void);

	//
	int getWidth(void) const {
		return m_width;
	}
	//
	int getHeight(void) const {
		return m_height;
	}
	//
	float getAspect(void) const {
		return (float)m_width/(float)m_height;
	}

	//
	void setFullscreen(fgBool toggle = FG_TRUE);

	// #FIXME
	fgBool swapBuffers(void);
	//
	void clearColor(void);

	fgBool isOpen(void) const {
		return m_isOpen;
	}

private:
	//
	fgBool refreshFS(void);

private:
	/// 
	std::string m_title;
#if defined FG_USING_EGL
	EGLSurface	m_EGLSurface;
#elif defined FG_USING_SDL2
	SDL_Window*		m_sdlWindow;
	SDL_GLContext	m_GLContext;	// FIXME - context can be separate? ... P4
	Uint32			m_sdlFlags;
#endif
	/// 
	unsigned int m_width;
	/// 
	unsigned int m_height;
	///
	fgBool m_isFullscreen;
	///
	fgBool m_isHW;
	///
	fgBool m_isDB;
	///
	fgBool m_isOpen;
};

#endif /* _FG_GFX_WINDOW_H_ */
