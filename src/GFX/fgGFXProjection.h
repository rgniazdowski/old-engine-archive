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
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

#define FG_GFX_PERSPECTIVE_ZNEAR_DEFAULT	0.01f
#define FG_GFX_PERSPECTIVE_ZFAR_DEFAULT		1024.0f

#define FG_GFX_PERSPECTIVE_FOVY_DEFAULT		90.0f
#define FG_GFX_PERSPECTIVE_FOV_DEFAULT		90.0f

#define FG_GFX_PERSPECTIVE_ASPECT_DEFAULT	(1024.0f/768.0f)

#define FG_GFX_ORTHO_ZNEAR_DEFAULT	-2048.0f
#define FG_GFX_ORTHO_ZFAR_DEFAULT	2048.0f
/*
 *
 */
class fgGfxProjection {
protected:
	///
	glm::mat4x4 m_matrix;
private:
public:
	//
	fgGfxProjection() {}
	//
	~fgGfxProjection() {}

	//
	inline void setPerspective(float fovY, float aspect, float zNear = FG_GFX_PERSPECTIVE_ZNEAR_DEFAULT, float zFar = FG_GFX_PERSPECTIVE_ZFAR_DEFAULT) {
		m_matrix = glm::perspective(fovY, aspect, zNear, zFar);
	}

	//
	inline void setOrtho(float left, float right, float bottom, float top, float zNear = FG_GFX_ORTHO_ZNEAR_DEFAULT, float zFar = FG_GFX_ORTHO_ZFAR_DEFAULT) {
		m_matrix = glm::ortho(left, right, bottom, top, zNear, zFar);
	}

	//
	glm::mat4x4 & getRefMatrix(void) {
		return m_matrix;
	}

	// 
	const float * getPointer(void) const {
		return glm::value_ptr(m_matrix);
	}

	// 
	float * getPointer(void) {
		return glm::value_ptr(m_matrix);
	}
};

#endif /* _FG_GFX_PROJECTION_H_ */
