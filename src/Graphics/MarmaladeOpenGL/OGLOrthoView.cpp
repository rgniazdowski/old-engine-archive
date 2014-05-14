#include "OGLOrthoView.h"
#include "OGLMain.h"
#include <IwGL.h>

namespace OGL {

	void setOrthoView(float zNear, float zFar)
	{
		GLint width = (GLint)OGL::getScreenWidth();
		GLint height = (GLint)OGL::getScreenHeight();

		// Set viewport and perspective.
		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrthof(0.0f, (GLfloat)width, (GLfloat)height, 0.0f, (GLfloat)zNear, (GLfloat)zFar);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

};
