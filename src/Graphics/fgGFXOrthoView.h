#ifndef _FG_GFX_ORTHO_VIEW_H
#define _FG_GFX_ORTHO_VIEW_H

#include "MarmaladeOpenGL\OGLOrthoView.h"

namespace FG_GFX {

	inline void setOrthoView(float zNear, float zFar)
	{
		OGL::setOrthoView(zNear, zFar);
	}
};

#endif