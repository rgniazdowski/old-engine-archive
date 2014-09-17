/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_PROJECTION_H_
#define _FG_GFX_PROJECTION_H_

#include "fgBuildConfig.h"
#include "Math/fgMathLib.h"

#define FG_GFX_PERSPECTIVE_ZNEAR_DEFAULT	0.01f
#define FG_GFX_PERSPECTIVE_ZFAR_DEFAULT		1024.0f

#define FG_GFX_PERSPECTIVE_FOVY_DEFAULT		45.0f
#define FG_GFX_PERSPECTIVE_FOV_DEFAULT		45.0f

#define FG_GFX_PERSPECTIVE_ASPECT_DEFAULT	(1024.0f/768.0f)

#define FG_GFX_ORTHO_ZNEAR_DEFAULT	-2048.0f
#define FG_GFX_ORTHO_ZFAR_DEFAULT	2048.0f
/*
 *
 */
class fgGfxProjection 
{
protected:
	///
	fgMatrix4f m_projMatrix;
private:

public:
	//
	fgGfxProjection() {}
	//
	~fgGfxProjection() {}

	//
	inline void setPerspective(float fovY, float aspect, float zNear = FG_GFX_PERSPECTIVE_ZNEAR_DEFAULT, float zFar = FG_GFX_PERSPECTIVE_ZFAR_DEFAULT) {
		float properFOV;
#if defined GLM_FORCE_RADIANS
		properFOV = glm::radians(fovY);
#else
		properFOV = fovY;
#endif
		m_projMatrix = glm::perspective(properFOV, aspect, zNear, zFar);
	}

	//
	inline void setOrtho(float left, float right, float bottom, float top, float zNear = FG_GFX_ORTHO_ZNEAR_DEFAULT, float zFar = FG_GFX_ORTHO_ZFAR_DEFAULT) {
		m_projMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
	}

	//
	fgMatrix4f & getRefProjMatrix(void) {
		return m_projMatrix;
	}

	// 
	const float * getProjMatPtr(void) const {
		return glm::value_ptr(m_projMatrix);
	}

	// 
	float * getProjMatPtr(void) {
		return glm::value_ptr(m_projMatrix);
	}
};

#endif /* _FG_GFX_PROJECTION_H_ */
