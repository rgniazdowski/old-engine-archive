#ifndef _FG_OGL_ORTHO_VIEW_H
#define _FG_OGL_ORTHO_VIEW_H

#define FG_OGL_ORTHO_ZNEAR_DEFAULT	-2048.0f
#define FG_OGL_ORTHO_ZFAR_DEFAULT	2048.0f

namespace OGL {

	void setOrthoView(float zNear, float zFar);
};

#endif