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

#include "fgGFXWindow.h"
#include "fgGFXCameraAnimation.h"
#include "Shaders/fgGFXShaderManager.h"
#include "Textures/fgTextureManager.h"

#include "fgStatusReporter.h"
#include "Util/fgTag.h"

class fgGfxMain;
#define FG_TAG_GFX_MAIN_NAME	"GfxMain"
#define FG_TAG_GFX_MAIN			FG_TAG_TYPE(fgGfxMain)
FG_TAG_TEMPLATE_ID_AUTO(fgGfxMain, FG_TAG_GFX_MAIN_NAME);
typedef FG_TAG_GFX_MAIN fgGfxMainTag;

extern fgGfxCameraAnimation * cameraAnim;
extern fgGFXuint vboIds[4];

/*
 *
 */
class fgGfxMain : public fgStatusReporter<fgGfxMainTag>
{
public:
	// 
	fgGfxMain();
	// 
	virtual ~fgGfxMain();

	// 
	fgBool setResourceManager(fgManagerBase *resourceManager);

	// Init the whole GFX subsystem - set the screen
	fgBool initGFX(void);
	// Close the subsystem - destroy the graphics context
	void closeGFX(void);

	// Suspend event
	fgBool suspendGFX(void);
	// Resume event, restore state & context
	fgBool resumeGFX(void);

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
	//
	fgGfxWindow *getMainWindow(void) const;

private:
	/// 
	fgTextureManager	*m_textureMgr;
	///
	fgManagerBase		*m_resourceMgr;
	///
	fgGfxShaderManager	*m_shaderMgr;
	///
	fgGfxWindow			*m_mainWindow;
	///
	fgGfxContext		*m_gfxContext;
	///
	fgBool m_init;	
};

#endif /* _FG_GFX_MAIN_H_ */
