/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

// #FIXME - need to determine if this kind of header (along with ortho) is even needed
// considering the mathlib header

#ifndef _FG_GFX_PERSPECTIVE_VIEW_H
#define _FG_GFX_PERSPECTIVE_VIEW_H

#define FG_OGL_PERSPECTIVE_ZNEAR_DEFAULT	0.01f
#define FG_OGL_PERSPECTIVE_ZFAR_DEFAULT		1024.0f

#define FG_OGL_PERSPECTIVE_FOVY_DEFAULT		90.0f
#define FG_OGL_PERSPECTIVE_FOV_DEFAULT		90.0f

namespace FG_GFX {

	inline void setPerspectiveView(float fovY, float zNear, float zFar)
	{
		// #FIXME - perspective view and shit
	}

};

#endif
