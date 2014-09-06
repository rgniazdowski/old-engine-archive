/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_MAIN_H_
#define _FG_GFX_MAIN_H_

#include "fgBuildConfig.h"
#include "fgCommon.h"
#include "fgStatusReporter.h"
#include "Util/fgTag.h"
#include "fgManagerBase.h"
#include "Textures/fgTextureManager.h"

#if defined FG_USING_MARMALADE

#if !defined FG_USING_MARMALADE_OPENGL_ES && defined FG_USING_MARMALADE_IWGL
#include <IwGL.h>
#endif // FG_USING_MARMALADE_OPENGL_ES

#elif defined FG_USING_PLATFORM_LINUX

#ifdef FG_USING_OPENGL
#include <GL/gl.h>
#endif // FG_USING_OPENGL

#endif // FG_USING_MARMALADE

#if defined FG_USING_OPENGL_ES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>

#if defined FG_USING_EGL
#include <EGL/egl.h>
#define FG_EGL_MAX_CONFIG 32
#endif // FG_USING_EGL
#endif // FG_USING_OPENGL_ES

class fgGfxMain;
#define FG_TAG_GFX_MAIN_NAME	"fgGfxMain"
#define FG_TAG_GFX_MAIN			FG_TAG_TYPE(fgGfxMain)
FG_TAG_TEMPLATE_ID_AUTO(fgGfxMain, FG_TAG_GFX_MAIN_NAME);
typedef FG_TAG_GFX_MAIN fgGfxMainTag;

/*
 *
 */
class fgGfxMain : public fgStatusReporter<fgGfxMainTag>
{
protected:
	// fgGfxRenderer *m_renderer; // #TODO ?
	// should gfx main contain pointers to outside managers? like...
	// resource manager / texture manager
	// hardware state?
	// quality manager?

public:
	// 
	fgGfxMain();
	// 
	//fgGfxMain();
	// 
	~fgGfxMain();

	// 
	fgBool setResourceManager(fgManagerBase *resourceManager);

	// Init the whole GFX subsystem - set the screen and other
	fgBool initGFX(void);
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

	// Now main display function creates the buffer (vertex/color/texture coords buffers) 
	// to be displayed in current frame. The real drawing of created buffers is inside the
	// render function (which in the future should be in separate thread)
	// This will generate the list of visible objects, do frustum culling
	void display(void);

	// Begins the proper render of the created buffers
	void render(void);

	//
	fgTextureManager *getTextureManager(void) const;

	fgBool releaseTextures(void);

private:
	// 
	fgBool m_init;
	// 
	fgTextureManager *m_textureManager;
	// 
	fgManagerBase *m_resourceManager;
};

#endif /* _FG_GFX_MAIN_H_ */
