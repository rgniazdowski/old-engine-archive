/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGfxCameraAnimation.h"
#include "Util/fgTime.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::CCameraAnimation::CCameraAnimation(const Type cameraType) : base_type(),
m_type(cameraType),
m_hAngle((fgGFXfloat)M_PI),
m_vAngle(0.0f),
m_speed(150.0f),
m_mouseSpeed(0.002f),
m_zoom(1.0f),
m_groundLevel(0.01f),
m_distance(1.0f) {
    Vector3f position = Vector3f(0, 20.0f, 300.0f);
    m_eye = position;
}
//------------------------------------------------------------------------------

gfx::CCameraAnimation::~CCameraAnimation() { }
//------------------------------------------------------------------------------

float *gfx::CCameraAnimation::update(void) {
    if(m_type == FREE || m_type == FPS_STANDARD) {
        m_direction = Vector3f(cos(m_vAngle) * sin(m_hAngle),
                               sin(m_vAngle),
                               cos(m_vAngle) * cos(m_hAngle)
                               );

        m_right = Vector3f(sin(m_hAngle - M_PI_2),
                           0,
                           cos(m_hAngle - M_PI_2)
                           );

        if(m_type == FPS_STANDARD) {
            m_eye.y = m_groundLevel;
        }

        m_up = math::cross(m_right, m_direction);
        m_center = m_eye + m_direction * 10.0f;
    } else if(m_type == CENTER_LOCKED) {
        Vector3f diff = m_center - m_eye;
        if(diff.x < 0.5f && diff.x >= 0.0f) {
            diff.x = 0.5f;
            m_eye.x = m_center.x - diff.x;
        }
        if(diff.y < 0.5f && diff.y >= 0.0f) {
            diff.y = 0.5f;
            m_eye.y = m_center.y - diff.y;
        }
        if(diff.z < 0.5f && diff.z >= 0.0f) {
            diff.z = 0.5f;
            m_eye.z = m_center.z - diff.z;
        }
        m_direction = math::normalize(diff);
        m_right = math::normalize(math::cross(m_direction, m_up));
        //m_up = Vector3f(0.0f, 1.0f, 0.0f);
    } else if(m_type == FOLLOW) {

    } else if(m_type == PATH) {

    }
    //printf("eye:{%.2f,%.2f,%.2f}, center:{%.2f,%.2f,%.2f}, up:{%.2f,%.2f,%.2f}, m_direction:{%.2f,%.2f,%.2f}\n",
    //       m_eye.x, m_eye.y, m_eye.z,
    //       m_center.x, m_center.y, m_center.z,
    //       m_up.x, m_up.y, m_up.z,
    //       m_direction.x, m_direction.y, m_direction.z);
    return CCamera::update();
}
//------------------------------------------------------------------------------

float *gfx::CCameraAnimation::update(fgGFXfloat mouseXrel, fgGFXfloat mouseYrel) {
    if(m_type == FREE || m_type == FPS_STANDARD) {
        m_hAngle += m_mouseSpeed * mouseXrel;
        m_vAngle += m_mouseSpeed * mouseYrel;
    }
    return CCameraAnimation::update();
}
//------------------------------------------------------------------------------

void gfx::CCameraAnimation::moveLeft(void) {
    m_eye -= m_right * timesys::elapsed() * m_speed;
}
//------------------------------------------------------------------------------

void gfx::CCameraAnimation::moveRight(void) {
    m_eye += m_right * timesys::elapsed() * m_speed;
}
//------------------------------------------------------------------------------

void gfx::CCameraAnimation::moveForward(void) {
    m_eye += m_direction * timesys::elapsed() * m_speed;
}
//------------------------------------------------------------------------------

void gfx::CCameraAnimation::moveBackward(void) {
    m_eye -= m_direction * timesys::elapsed() * m_speed;
}
//------------------------------------------------------------------------------

void gfx::CCameraAnimation::moveUp(void) {
    m_eye += m_up * timesys::elapsed() * m_speed;
}
//------------------------------------------------------------------------------

void gfx::CCameraAnimation::moveDown(void) {
    m_eye -= m_up * timesys::elapsed() * m_speed;
}
//------------------------------------------------------------------------------
