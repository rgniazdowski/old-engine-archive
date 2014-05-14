/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
 *******************************************************/

#include "OGLPerspectiveView.h"
#include "OGLMain.h"

#include <cmath>

namespace OGL {
	void makeFrustum(float fovY, float aspectRatio, float zNear, float zFar)
	{
		const double DEG2RAD = M_PI / 180;

		float tangent = tanf(float(fovY/2) * float(DEG2RAD));   // tangent of half fovY
		float height = zNear * tangent;          // half height of near plane
		float width = height * aspectRatio;      // half width of near plane

		// params: left, right, bottom, top, near, far
		//glFrustumf(GLfloat(-width), GLfloat(width), GLfloat(-height), GLfloat(height), zNear, zFar);
		// #FIXME
	}

	void setPerspectiveView(float fovY, float zNear, float zFar)
	{
		GLint width = (GLint)OGL::getScreenWidth();
		GLint height = (GLint)OGL::getScreenHeight();
#if 0
		// Set viewport and perspective.
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		makeFrustum(fovY, GLfloat(width)/GLfloat(height), zNear, zFar);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
#endif
	}
};
