/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
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
fg::gfx::CCameraAnimation::CCameraAnimation(const fgGfxCameraType type) :
m_type(type),
m_hAngle((fgGFXfloat)M_PI),
m_vAngle(0.0f),
m_speed(0.15f),
m_mouseSpeed(0.002f),
m_zoom(1.0f),
m_distance(1.0f),
m_dt(0.0f) {
    fgVector3f position = fgVector3f(0, 20.0f, 300.0f);
    m_eye = position;
}

/*
 *
 */
fg::gfx::CCameraAnimation::~CCameraAnimation() { }

/*
 *
 */
float *fg::gfx::CCameraAnimation::update(void) {
    if(m_type == FG_GFX_CAMERA_FREE) {
        m_direction = fgVec3f(cos(m_vAngle) * sin(m_hAngle),
                              sin(m_vAngle),
                              cos(m_vAngle) * cos(m_hAngle)
                              );

        m_right = fgVec3f(sin(m_hAngle - M_PI_2),
                          0,
                          cos(m_hAngle - M_PI_2)
                          );

        m_up = fgMath::cross(m_right, m_direction);
        m_center = m_eye + m_direction;
    }
    //printf("eye:{%.2f,%.2f,%.2f}, center:{%.2f,%.2f,%.2f}, up:{%.2f,%.2f,%.2f}, m_direction:{%.2f,%.2f,%.2f}\n",
    //       m_eye.x, m_eye.y, m_eye.z,
    //       m_center.x, m_center.y, m_center.z,
    //       m_up.x, m_up.y, m_up.z,
    //       m_direction.x, m_direction.y, m_direction.z);
    return CCamera::update();
}

/*
 *
 */
float *fg::gfx::CCameraAnimation::update(fgGFXfloat mouseXrel, fgGFXfloat mouseYrel) {
    if(m_type == FG_GFX_CAMERA_FREE) {
        m_hAngle += m_mouseSpeed * mouseXrel;
        m_vAngle += m_mouseSpeed * mouseYrel;
    }
    return CCameraAnimation::update();
}

/*
 *
 */
void fg::gfx::CCameraAnimation::moveLeft(void) {
    m_eye -= m_right * m_dt * m_speed;
}

/*
 *
 */
void fg::gfx::CCameraAnimation::moveRight(void) {
    m_eye += m_right * m_dt * m_speed;
}

/*
 *
 */
void fg::gfx::CCameraAnimation::moveForward(void) {
    m_eye += m_direction * m_dt * m_speed;
}

/*
 *
 */
void fg::gfx::CCameraAnimation::moveBackward(void) {
    m_eye -= m_direction * m_dt * m_speed;
}

/*
 *
 */
void fg::gfx::CCameraAnimation::moveUp(void) {
    m_eye += m_up * m_dt * m_speed;
}

/*
 *
 */
void fg::gfx::CCameraAnimation::moveDown(void) {
    m_eye -= m_up * m_dt * m_speed;
}
