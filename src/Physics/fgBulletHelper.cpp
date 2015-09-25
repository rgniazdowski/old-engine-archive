/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/* 
 * File:   fgBulletHelper.cpp
 * Author: vigilant
 * 
 * Created on September 24, 2015, 12:16 PM
 */

#include "fgBulletHelper.h"
#if defined(FG_USING_BULLET)
#include <cstring>
using namespace fg;
//------------------------------------------------------------------------------

void physics::bullet_helper::copyMatrix4x4(Matrix4f& dest, const btMatrix3x3& source) {
    float *m = math::value_ptr(dest);
    m[0] = float(source[0].x());
    m[1] = float(source[1].x());
    m[2] = float(source[2].x());
    m[3] = float(0.0);
    m[4] = float(source[0].y());
    m[5] = float(source[1].y());
    m[6] = float(source[2].y());
    m[7] = float(0.0);
    m[8] = float(source[0].z());
    m[9] = float(source[1].z());
    m[10] = float(source[2].z());
    m[11] = float(0.0);
    // #CHECK PLEASE!
}
//------------------------------------------------------------------------------

void physics::bullet_helper::copyMatrix4x4(Matrix4f& dest, const btTransform& source) {
    source.getOpenGLMatrix((btScalar*)math::value_ptr(dest));
}
//------------------------------------------------------------------------------

void physics::bullet_helper::copyMatrix4x4(btTransform& dest, const Matrix4f& source) {
    dest.setFromOpenGLMatrix((btScalar*)math::value_ptr(source));
}
//------------------------------------------------------------------------------

void physics::bullet_helper::copyMatrix3x3(Matrix3f& dest, const btMatrix3x3& source) {
    float *m = math::value_ptr(dest);
    //m_el[0].setValue(xx, xy, xz);
    //m_el[1].setValue(yx, yy, yz);
    //m_el[2].setValue(zx, zy, zz);

    m[0] = float(source[0].x());
    m[1] = float(source[1].x());
    m[2] = float(source[2].x());
    m[3] = float(source[0].y());
    m[4] = float(source[1].y());
    m[5] = float(source[2].y());
    m[6] = float(source[0].z());
    m[7] = float(source[1].z());
    m[8] = float(source[2].z());
}
//------------------------------------------------------------------------------

void physics::bullet_helper::copyMatrix3x3(btMatrix3x3& dest, const Matrix3f& source) {
    const float *m = math::value_ptr(source);
    /*dest[0].setX(m[0]);
    dest[1].setX(m[1]);
    dest[2].setX(m[2]);
    dest[0].setY(m[3]);
    dest[1].setY(m[4]);
    dest[2].setY(m[5]);
    dest[0].setZ(m[6]);
    dest[1].setZ(m[7]);
    dest[2].setZ(m[8]);*/

    dest[0].setValue(m[0], m[3], m[6]);
    dest[1].setValue(m[1], m[4], m[7]);
    dest[2].setValue(m[2], m[5], m[8]);
}
//------------------------------------------------------------------------------

void physics::bullet_helper::decompose(const btTransform& source,
                                       Vector3f& scale,
                                       Quaternionf& rotation,
                                       Vector3f& position) {
    copyQuat(rotation, source.getRotation());
    copyVector(position, source.getOrigin());
    scale = Vector3f(1.0f, 1.0f, 1.0f);
}
//------------------------------------------------------------------------------
#endif /* FG_USING_BULLET */