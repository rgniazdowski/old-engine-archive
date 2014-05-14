#ifndef _FG_GFX_PERSPECTIVE_VIEW_H
#define _FG_GFX_PERSPECTIVE_VIEW_H

#include "MarmaladeOpenGL\OGLPerspectiveView.h"

namespace FG_GFX {

	inline void setPerspectiveView(float fovY, float zNear, float zFar)
	{
		OGL::setPerspectiveView(fovY, zNear, zFar);
	}

};

#endif