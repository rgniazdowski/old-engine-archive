/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_MV_MATRIX_H_
#define _FG_GFX_MV_MATRIX_H_

#include "fgGFXCamera.h"
#include "fgBool.h"

class fgGfxMVMatrix : public fgGfxCamera
{
public:
	// 
	fgGfxMVMatrix() { }
	// 
	virtual ~fgGfxMVMatrix() { }

	// 
	virtual float *calculate(fgMatrix4f & modelMatrix)
	{
		m_modelViewMatrix = m_viewMatrix * modelMatrix;
		return getModelViewMatPtr();
	}

	//
	virtual float *calculate(fgGfxCamera *camera, fgMatrix4f & modelMatrix, fgBool updateMatrix = FG_TRUE)
	{
		if(camera) {
			m_eye = camera->getRefEye();
			m_center = camera->getRefCenter();
			m_up = camera->getRefUp();
			fgGfxMVMatrix::update();
			//m_viewMatrix = camera->getRefViewMatrix();
		}
		if(updateMatrix)
			m_modelViewMatrix = m_viewMatrix * modelMatrix;
		return getModelViewMatPtr();
	}

	//
	fgMatrix4f & getRefMVMatrix(void) {
		return m_modelViewMatrix;
	}

	// 
	const float * getModelViewMatPtr(void) const {
		return glm::value_ptr(m_modelViewMatrix);
	}

	// 
	float * getModelViewMatPtr(void) {
		return glm::value_ptr(m_modelViewMatrix);
	}

protected:
	/// 
	fgMatrix4f m_modelViewMatrix;
};

#endif /* _FG_GFX_MV_MATRIX_H_ */
