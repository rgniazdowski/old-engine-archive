/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXCameraAnimation.h"

/*
 *
 */
fgGfxCameraAnimation::fgGfxCameraAnimation() : 
	m_type(FG_GFX_CAMERA_FREE),
	m_hAngle((fgGFXfloat)M_PI),
	m_vAngle(0.0f),
	m_speed(0.15f),
	m_mouseSpeed(0.002f),
	m_zoom(1.0f),
	m_distance(1.0f),
	m_dt(0.0f),
	m_screenW(1024),
	m_screenH(768)
{
	glm::vec3 position = glm::vec3( 0, 0, 55 ); 
	m_eye = position;
}

/*
 *
 */
fgGfxCameraAnimation::~fgGfxCameraAnimation()
{
}

/*
 *
 */
float *fgGfxCameraAnimation::update(void)
{
	if(m_type == FG_GFX_CAMERA_FREE)
	{
		m_direction = fgVec3f(
			cos(m_vAngle) * sin(m_hAngle),
			sin(m_vAngle),
			cos(m_vAngle) * cos(m_hAngle)
		);

		m_right = fgVec3f(
			sin(m_hAngle - M_PI_2), 
			0,
			cos(m_hAngle - M_PI_2)
		);

		m_up = glm::cross(m_right, m_direction);
		m_center = m_eye + m_direction;
	}
	return fgGfxCamera::update();
}

/*
 *
 */
float *fgGfxCameraAnimation::update(fgGFXfloat mouseXrel, fgGFXfloat mouseYrel)
{
	if(m_type == FG_GFX_CAMERA_FREE)
	{
		m_hAngle += m_mouseSpeed * mouseXrel;
		m_vAngle += m_mouseSpeed * mouseYrel;

		//printf("Camera anim updated: h:%.3f v:%.3f\n", m_hAngle, m_vAngle);
	}
	return fgGfxCameraAnimation::update();
}

/*
 *
 */
void fgGfxCameraAnimation::moveLeft(void)
{
	m_eye -= m_right * m_dt * m_speed;
	//printf("EYE: %.2f %.2f %.2f\n", m_eye[0], m_eye[1], m_eye[2]);
}

/*
 *
 */
void fgGfxCameraAnimation::moveRight(void)
{
	m_eye += m_right * m_dt * m_speed;
	//printf("EYE: %.2f %.2f %.2f\n", m_eye[0], m_eye[1], m_eye[2]);
}

/*
 *
 */
void fgGfxCameraAnimation::moveForward(void)
{
	m_eye += m_direction * m_dt * m_speed;
	//printf("EYE: %.2f %.2f %.2f\n", m_eye[0], m_eye[1], m_eye[2]);
}

/*
 *
 */
void fgGfxCameraAnimation::moveBackward(void)
{
	m_eye -= m_direction * m_dt * m_speed;
	//printf("EYE: %.2f %.2f %.2f\n", m_eye[0], m_eye[1], m_eye[2]);
}

/*
 *
 */
void fgGfxCameraAnimation::moveUp(void)
{

}

/*
 *
 */
void fgGfxCameraAnimation::moveDown(void)
{

}
