/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "OGLOrthoView.h"
#include "OGLMain.h"

namespace OGL {

	void setOrthoView(float zNear, float zFar)
	{
		GLint width = (GLint)OGL::getScreenWidth();
		GLint height = (GLint)OGL::getScreenHeight();
#if 0
		// Set viewport and perspective.
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrthof(0.0f, (GLfloat)width, (GLfloat)height, 0.0f, (GLfloat)zNear, (GLfloat)zFar);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
#endif
	}

};
