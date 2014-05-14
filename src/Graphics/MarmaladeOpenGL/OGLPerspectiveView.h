/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
 *******************************************************/

#ifndef _FG_OGL_PERSPECTIVE_VIEW_H
#define _FG_OGL_PERSPECTIVE_VIEW_H

#define FG_OGL_PERSPECTIVE_ZNEAR_DEFAULT	0.01f
#define FG_OGL_PERSPECTIVE_ZFAR_DEFAULT		1024.0f

#define FG_OGL_PERSPECTIVE_FOVY_DEFAULT		90.0f
#define FG_OGL_PERSPECTIVE_FOV_DEFAULT		90.0f

namespace OGL {

	void makeFrustum(float fovY, float aspectRatio, float zNear, float zFar);
	void setPerspectiveView(float fovY, float zNear, float zFar);

};

#endif