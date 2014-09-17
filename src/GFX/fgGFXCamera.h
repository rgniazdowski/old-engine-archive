/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_CAMERA_H_
#define _FG_GFX_CAMERA_H_

#include "Math/fgMathLib.h"

class fgGfxCamera
{
public:
	fgGfxCamera() : m_up(0.0f, 1.0f, 0.0f) { }
	virtual ~fgGfxCamera() { }

	//
	fgMatrix4f & getRefViewMatrix(void) {
		return m_viewMatrix;
	}

	virtual float * update(void) {
		static int i = 0;
		i++;
		m_viewMatrix = glm::lookAt(m_eye, m_center, m_up);
		if(i==1000) {
			printf("update camera: %.2f\n", getViewMatPtr()[0]);
			i = 0;
		}
		return getViewMatPtr();
	}

	// 
	const float * getViewMatPtr(void) const {
		return glm::value_ptr(m_viewMatrix);
	}
	// 
	float * getViewMatPtr(void) {
		return glm::value_ptr(m_viewMatrix);
	}

	//
	fgVec3f & getRefEye(void) {
		return m_eye;
	}
	//
	fgVec3f & getRefCenter(void) {
		return m_center;
	}
	//
	fgVec3f & getRefUp(void) {
		return m_up;
	}

	// 
	const float * getPtrEye(void) const {
		return glm::value_ptr(m_eye);
	}
	// 
	float * getPtrEye(void) {
		return glm::value_ptr(m_eye);
	}

	// 
	const float * getPtrCenter(void) const {
		return glm::value_ptr(m_center);
	}
	// 
	float * getPtrCenter(void) {
		return glm::value_ptr(m_center);
	}

	// 
	const float * getPtrUp(void) const {
		return glm::value_ptr(m_up);
	}
	// 
	float * getPtrUp(void) {
		return glm::value_ptr(m_up);
	}

protected:
	fgMatrix4f	m_viewMatrix;	// The view matrix of this camera
	fgVec3f		m_eye;		// Position of the camera in world space
	fgVec3f		m_center;	// Where the camera is looking?
	fgVec3f		m_up;		// Head by default will be up (0,1,0)
};

#endif /* _FG_GFX_CAMERA_H_ */
