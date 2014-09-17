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
#include "fgGFXStdInc.h"

#include "fgStatusReporter.h"
#include "Util/fgTag.h"
#include "fgManagerBase.h"
#include "Textures/fgTextureManager.h"
#include "Shaders/fgGFXShaderManager.h"

class fgGfxMain;
#define FG_TAG_GFX_MAIN_NAME	"GfxMain"
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
	~fgGfxMain();

	// 
	fgBool setResourceManager(fgManagerBase *resourceManager);

	// Init the whole GFX subsystem - set the screen
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
	// 
	fgBool releaseTextures(void);
	//
	fgGfxShaderManager *getShaderManager(void) const;
	//
	fgBool preLoadShaders(void) const;

private:
	/// 
	fgTextureManager *m_textureMgr;
	///
	fgManagerBase *m_resourceMgr;
	///
	fgGfxShaderManager *m_shaderMgr;
#if defined FG_USING_EGL
	EGLSurface m_EGLSurface;
	EGLDisplay m_EGLDisplay;
	EGLContext m_EGLContext;
#endif
	// FIXME
	int m_screenW;
	// FIXME
	int m_screenH;
	// 
	fgBool m_init;
	
};

#endif /* _FG_GFX_MAIN_H_ */
