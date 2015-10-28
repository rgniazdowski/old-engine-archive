/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/*
 * Implementation file for the rigid body class.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under license. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software license.
 */
#include "fgBuildConfig.h"
#if !defined(FG_USING_BULLET) && defined(FG_USING_CYCLONE)
#include "Physics/Cyclone/fgPrecision.h"
#include "Physics/Cyclone/fgRigidBody.h"
#include "fgCycloneCoreMath.h"
#include "Math/fgMathLib.h"

#include <memory.h>
#if defined(FG_DEBUG)
#include <assert.h>
#endif

using namespace fg;
//------------------------------------------------------------------------------

/*
 * --------------------------------------------------------------------------
 * INTERNAL OR HELPER FUNCTIONS:
 * --------------------------------------------------------------------------
 */

/**
 * Internal function that checks the validity of an inverse inertia tensor.
 */
static inline void _checkInverseInertiaTensor(const Matrix3f &iitWorld) {
    // TODO: Perform a validity check in an assert.
}
//------------------------------------------------------------------------------

/**
 * Internal function to do an inertia tensor transform by a quaternion.
 * Note that the implementation of this function was created by an
 * automated code-generator and optimizer.
 */
static inline void _transformInertiaTensor(Matrix3f &iitWorld,
                                           const Quaternionf &q,
                                           const Matrix3f &iitBody,
                                           const Matrix4f &rotmat) {
#if !PHYS_USE_2D_MAPPING_ENABLED

    const float *iitBodydata = math::value_ptr(iitBody);
    const float *rotmatdata = math::value_ptr(rotmat);
    float *iitWorlddata = math::value_ptr(iitWorld);

    physics::real t4 = rotmatdata[0] * iitBodydata[0] +
            rotmatdata[1] * iitBodydata[3] +
            rotmatdata[2] * iitBodydata[6];
    physics::real t9 = rotmatdata[0] * iitBodydata[1] +
            rotmatdata[1] * iitBodydata[4] +
            rotmatdata[2] * iitBodydata[7];
    physics::real t14 = rotmatdata[0] * iitBodydata[2] +
            rotmatdata[1] * iitBodydata[5] +
            rotmatdata[2] * iitBodydata[8];
    physics::real t28 = rotmatdata[4] * iitBodydata[0] +
            rotmatdata[5] * iitBodydata[3] +
            rotmatdata[6] * iitBodydata[6];
    physics::real t33 = rotmatdata[4] * iitBodydata[1] +
            rotmatdata[5] * iitBodydata[4] +
            rotmatdata[6] * iitBodydata[7];
    physics::real t38 = rotmatdata[4] * iitBodydata[2] +
            rotmatdata[5] * iitBodydata[5] +
            rotmatdata[6] * iitBodydata[8];
    physics::real t52 = rotmatdata[8] * iitBodydata[0] +
            rotmatdata[9] * iitBodydata[3] +
            rotmatdata[10] * iitBodydata[6];
    physics::real t57 = rotmatdata[8] * iitBodydata[1] +
            rotmatdata[9] * iitBodydata[4] +
            rotmatdata[10] * iitBodydata[7];
    physics::real t62 = rotmatdata[8] * iitBodydata[2] +
            rotmatdata[9] * iitBodydata[5] +
            rotmatdata[10] * iitBodydata[8];

    iitWorlddata[0] = t4 * rotmatdata[0] +
            t9 * rotmatdata[1] +
            t14 * rotmatdata[2];
    iitWorlddata[1] = t4 * rotmatdata[4] +
            t9 * rotmatdata[5] +
            t14 * rotmatdata[6];
    iitWorlddata[2] = t4 * rotmatdata[8] +
            t9 * rotmatdata[9] +
            t14 * rotmatdata[10];
    iitWorlddata[3] = t28 * rotmatdata[0] +
            t33 * rotmatdata[1] +
            t38 * rotmatdata[2];
    iitWorlddata[4] = t28 * rotmatdata[4] +
            t33 * rotmatdata[5] +
            t38 * rotmatdata[6];
    iitWorlddata[5] = t28 * rotmatdata[8] +
            t33 * rotmatdata[9] +
            t38 * rotmatdata[10];
    iitWorlddata[6] = t52 * rotmatdata[0] +
            t57 * rotmatdata[1] +
            t62 * rotmatdata[2];
    iitWorlddata[7] = t52 * rotmatdata[4] +
            t57 * rotmatdata[5] +
            t62 * rotmatdata[6];
    iitWorlddata[8] = t52 * rotmatdata[8] +
            t57 * rotmatdata[9] +
            t62 * rotmatdata[10];
#else

    physics::real t4 =
            rotmat[0][0] * iitBody[0][0] + // 0 0
            rotmat[0][1] * iitBody[1][0] + // 1 3
            rotmat[0][2] * iitBody[2][0]; //  2 6
    physics::real t9 =
            rotmat[0][0] * iitBody[0][1] + // 0 1
            rotmat[0][1] * iitBody[1][1] + // 1 4
            rotmat[0][2] * iitBody[2][1]; //  2 7
    physics::real t14 =
            rotmat[0][0] * iitBody[0][2] + // 0 2
            rotmat[0][1] * iitBody[1][2] + // 1 5
            rotmat[0][2] * iitBody[2][2]; //  2 8
    physics::real t28 =
            rotmat[1][0] * iitBody[0][0] + // 4 0
            rotmat[1][1] * iitBody[1][0] + // 5 3
            rotmat[1][2] * iitBody[2][0]; //  6 6
    physics::real t33 =
            rotmat[1][0] * iitBody[0][1] + // 4 1
            rotmat[1][1] * iitBody[1][1] + // 5 4
            rotmat[1][2] * iitBody[2][1]; //  6 7
    physics::real t38 =
            rotmat[1][0] * iitBody[0][2] + // 4 2
            rotmat[1][1] * iitBody[1][2] + // 5 5
            rotmat[1][2] * iitBody[2][2]; //  6 8
    physics::real t52 =
            rotmat[2][0] * iitBody[0][0] + // 8  0
            rotmat[2][1] * iitBody[1][0] + // 9  3
            rotmat[2][2] * iitBody[2][0]; //  10 6
    physics::real t57 =
            rotmat[2][0] * iitBody[0][1] + // 8  1
            rotmat[2][1] * iitBody[1][1] + // 9  4
            rotmat[2][2] * iitBody[2][1]; //  10 7
    physics::real t62 =
            rotmat[2][0] * iitBody[0][2] + // 8  2
            rotmat[2][1] * iitBody[1][2] + // 9  5
            rotmat[2][2] * iitBody[2][2]; //  10 8

    iitWorld[0][0] = // 0
            t4 * rotmat[0][0] + // 0
            t9 * rotmat[0][1] + // 1
            t14 * rotmat[0][2]; // 2
    iitWorld[0][1] = // 1
            t4 * rotmat[1][0] + // 4
            t9 * rotmat[1][1] + // 5
            t14 * rotmat[1][2]; // 6
    iitWorld[0][2] = // 2
            t4 * rotmat[2][0] + //  8
            t9 * rotmat[2][1] + //  9
            t14 * rotmat[2][2]; // 10
    iitWorld[1][0] = // 3
            t28 * rotmat[0][0] + // 0
            t33 * rotmat[0][1] + // 1
            t38 * rotmat[0][2]; //  2
    iitWorld[1][1] = // 4
            t28 * rotmat[1][0] + // 4
            t33 * rotmat[1][1] + // 5
            t38 * rotmat[1][2]; //  6
    iitWorld[1][2] = // 5
            t28 * rotmat[2][0] + // 8
            t33 * rotmat[2][1] + // 9
            t38 * rotmat[2][2]; // 10
    iitWorld[2][0] = // 6
            t52 * rotmat[0][0] + // 0
            t57 * rotmat[0][1] + // 1
            t62 * rotmat[0][2]; //  2
    iitWorld[2][1] = // 7
            t52 * rotmat[1][0] + // 4
            t57 * rotmat[1][1] + // 5
            t62 * rotmat[1][2]; //  6
    iitWorld[2][2] = // 8
            t52 * rotmat[2][0] + // 8
            t57 * rotmat[2][1] + // 9
            t62 * rotmat[2][2]; // 10
#endif
    //iitWorld = math::transpose(iitWorld);
}
//------------------------------------------------------------------------------

/**
 * Inline function that creates a transform matrix from a
 * position and orientation.
 */
static inline void _calculateTransformMatrix(Matrix4f &transformMatrix,
                                             const Vector3f &position,
                                             const Quaternionf &orientation) {
#if PHYS_USE_2D_MAPPING_ENABLED
    transformMatrix[0][0] = 1 - 2 * orientation.y * orientation.y -
            2 * orientation.z * orientation.z; // 0
    transformMatrix[0][1] = 2 * orientation.x * orientation.y -
            2 * orientation.w * orientation.z; // 1
    transformMatrix[0][2] = 2 * orientation.x * orientation.z +
            2 * orientation.w * orientation.y; // 2
    transformMatrix[0][3] = position.x; // 3

    transformMatrix[1][0] = 2 * orientation.x * orientation.y +
            2 * orientation.w * orientation.z; // 4
    transformMatrix[1][1] = 1 - 2 * orientation.x * orientation.x -
            2 * orientation.z * orientation.z; // 5
    transformMatrix[1][2] = 2 * orientation.y * orientation.z -
            2 * orientation.w * orientation.x; // 6
    transformMatrix[1][3] = position.y; // 7

    transformMatrix[2][0] = 2 * orientation.x * orientation.z -
            2 * orientation.w * orientation.y; // 8
    transformMatrix[2][1] = 2 * orientation.y * orientation.z +
            2 * orientation.w * orientation.x; // 9
    transformMatrix[2][2] = 1 - 2 * orientation.x * orientation.x -
            2 * orientation.y * orientation.y; // 10
    transformMatrix[2][3] = position.z; // 11
#else
    float *transformMatrixdata = math::value_ptr(transformMatrix);
    transformMatrixdata[0] = 1 - 2 * orientation.y * orientation.y -
            2 * orientation.z * orientation.z;
    transformMatrixdata[1] = 2 * orientation.x * orientation.y -
            2 * orientation.w * orientation.z;
    transformMatrixdata[2] = 2 * orientation.x * orientation.z +
            2 * orientation.w * orientation.y;
    transformMatrixdata[3] = position.x;

    transformMatrixdata[4] = 2 * orientation.x * orientation.y +
            2 * orientation.w * orientation.z;
    transformMatrixdata[5] = 1 - 2 * orientation.x * orientation.x -
            2 * orientation.z * orientation.z;
    transformMatrixdata[6] = 2 * orientation.y * orientation.z -
            2 * orientation.w * orientation.x;
    transformMatrixdata[7] = position.y;

    transformMatrixdata[8] = 2 * orientation.x * orientation.z -
            2 * orientation.w * orientation.y;
    transformMatrixdata[9] = 2 * orientation.y * orientation.z +
            2 * orientation.w * orientation.x;
    transformMatrixdata[10] = 1 - 2 * orientation.x * orientation.x -
            2 * orientation.y * orientation.y;
    transformMatrixdata[11] = position.z;
#endif
}
//------------------------------------------------------------------------------

void physics::CRigidBody::calculateDerivedData(void) {
    //orientation.normalise();
    orientation = math::normalize(orientation);

    // Calculate the transform matrix for the body.
    _calculateTransformMatrix(transformMatrix, position, orientation);

    // Calculate the inertiaTensor in world space.
    _transformInertiaTensor(inverseInertiaTensorWorld,
                            orientation,
                            inverseInertiaTensor,
                            transformMatrix);

}
//------------------------------------------------------------------------------

void physics::CRigidBody::integrate(real duration) {
    if(!isAwake) return;

    // Calculate linear acceleration from force inputs.
    lastFrameAcceleration = acceleration;
    ///lastFrameAcceleration.addScaledVector(forceAccum, inverseMass);
    lastFrameAcceleration += forceAccum * inverseMass;

    // Calculate angular acceleration from torque inputs.
    //Vector3f angularAcceleration = inverseInertiaTensorWorld.transform(torqueAccum);
    Vector3f angularAcceleration = physics::transform(inverseInertiaTensorWorld, torqueAccum);
    //Vector3f angularAcceleration = inverseInertiaTensor * torqueAccum;

    // Adjust velocities
    // Update linear velocity from both acceleration and impulse.
    //velocity.addScaledVector(lastFrameAcceleration, duration);
    velocity += lastFrameAcceleration * duration;

    // Update angular velocity from both acceleration and impulse.
    //rotation.addScaledVector(angularAcceleration, duration);
    rotation += angularAcceleration * duration;

    // Impose drag.
    velocity *= math::pow(linearDamping, duration);
    rotation *= math::pow(angularDamping, duration);

    // Adjust positions
    // Update linear position.
    //position.addScaledVector(velocity, duration);
    position += velocity * duration;

    // Update angular position.
    //orientation.addScaledVector(rotation, duration);
    //orientation += rotation * duration;
    //orientation += (Quaternionf(0, rotation * duration) * orientation) * 0.5f;

    orientation = physics::addScaledVector(orientation, rotation, duration);

    // Normalise the orientation, and update the matrices with the new
    // position and orientation
    calculateDerivedData();

    // Clear accumulators.
    clearAccumulators();

    // Update the kinetic energy store, and possibly put the body to
    // sleep.
    if(canSleep) {
        real currentMotion = math::dot(velocity, velocity) +
                math::dot(rotation, rotation);

        real bias = real_pow(0.5, duration);
        motion = bias * motion + (1 - bias) * currentMotion;

        if(motion < sleepEpsilon) setAwake(false);
        else if(motion > 10 * sleepEpsilon) motion = 10 * sleepEpsilon;
    }
}
//------------------------------------------------------------------------------

void physics::CRigidBody::setMass(const real mass) {
#if defined(FG_DEBUG)
    assert(mass != 0);
#endif
    CRigidBody::inverseMass = ((real)1.0) / mass;
}
//------------------------------------------------------------------------------

physics::real physics::CRigidBody::getMass(void) const {
    if(inverseMass == 0) {
        return REAL_MAX;
    } else {
        return ((real)1.0) / inverseMass;
    }
}
//------------------------------------------------------------------------------

void physics::CRigidBody::setInverseMass(const real inverseMass) {
    CRigidBody::inverseMass = inverseMass;
}
//------------------------------------------------------------------------------

physics::real physics::CRigidBody::getInverseMass(void) const {
    return inverseMass;
}
//------------------------------------------------------------------------------

bool physics::CRigidBody::hasFiniteMass(void) const {
    //return (fgBool)(inverseMass >= 0.0f);
    return (inverseMass >= 0.0f);
}
//------------------------------------------------------------------------------

void physics::CRigidBody::setInertiaTensor(const Matrix3f &inertiaTensor) {
    //inverseInertiaTensor.setInverse(inertiaTensor);
    inverseInertiaTensor = physics::setInverse(inertiaTensor);
    _checkInverseInertiaTensor(inverseInertiaTensor);
}
//------------------------------------------------------------------------------

void physics::CRigidBody::getInertiaTensor(Matrix3f *inertiaTensor) const {
    //inertiaTensor->setInverse(inverseInertiaTensor);
    if(inertiaTensor) {
        *inertiaTensor = physics::setInverse(inverseInertiaTensor);
    }
}
//------------------------------------------------------------------------------

Matrix3f physics::CRigidBody::getInertiaTensor(void) const {
    Matrix3f it;
    getInertiaTensor(&it);
    return it;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::getInertiaTensorWorld(Matrix3f *inertiaTensor) const {
    //inertiaTensor->setInverse(inverseInertiaTensorWorld);
    if(inertiaTensor) {
        *inertiaTensor = physics::setInverse(inverseInertiaTensorWorld);
    }
}
//------------------------------------------------------------------------------

Matrix3f physics::CRigidBody::getInertiaTensorWorld(void) const {
    Matrix3f it;
    getInertiaTensorWorld(&it);
    return it;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::setInverseInertiaTensor(const Matrix3f &inverseInertiaTensor) {
    _checkInverseInertiaTensor(inverseInertiaTensor);
    CRigidBody::inverseInertiaTensor = inverseInertiaTensor;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::getInverseInertiaTensor(Matrix3f *inverseInertiaTensor) const {
    *inverseInertiaTensor = CRigidBody::inverseInertiaTensor;
}
//------------------------------------------------------------------------------

Matrix3f physics::CRigidBody::getInverseInertiaTensor(void) const {
    return inverseInertiaTensor;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::getInverseInertiaTensorWorld(Matrix3f *inverseInertiaTensor) const {
    *inverseInertiaTensor = inverseInertiaTensorWorld;
}
//------------------------------------------------------------------------------

Matrix3f physics::CRigidBody::getInverseInertiaTensorWorld(void) const {
    return inverseInertiaTensorWorld;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::setDamping(const real linearDamping,
                                     const real angularDamping) {
    CRigidBody::linearDamping = linearDamping;
    CRigidBody::angularDamping = angularDamping;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::setLinearDamping(const real linearDamping) {
    CRigidBody::linearDamping = linearDamping;
}
//------------------------------------------------------------------------------

physics::real physics::CRigidBody::getLinearDamping(void) const {
    return linearDamping;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::setAngularDamping(const real angularDamping) {
    CRigidBody::angularDamping = angularDamping;
}
//------------------------------------------------------------------------------

physics::real physics::CRigidBody::getAngularDamping(void) const {
    return angularDamping;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::setPosition(const Vector3f &position) {
    CRigidBody::position = position;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::setPosition(const real x, const real y, const real z) {
    position.x = x;
    position.y = y;
    position.z = z;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::getPosition(Vector3f *position) const {
    *position = CRigidBody::position;
}
//------------------------------------------------------------------------------

Vector3f physics::CRigidBody::getPosition(void) const {
    return position;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::setOrientation(const Quaternionf &orientation) {
    CRigidBody::orientation = math::normalize(orientation);
    //RigidBody::orientation.normalise();
}
//------------------------------------------------------------------------------

void physics::CRigidBody::setOrientation(const real r, const real i,
                                         const real j, const real k) {
    orientation.w = r; // r / w
    orientation.x = i; // i / x
    orientation.y = j; // j / y
    orientation.z = k; // k / z
    //::physics::Quaternion
    //orientation.normalise();
    orientation = math::normalize(orientation);
}
//------------------------------------------------------------------------------

void physics::CRigidBody::getOrientation(Quaternionf *orientation) const {
    *orientation = CRigidBody::orientation;
}
//------------------------------------------------------------------------------

Quaternionf physics::CRigidBody::getOrientation(void) const {
    return orientation;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::getOrientation(Matrix3f *matrix) const {
    Matrix3f &mat = *matrix;
    mat[0][0] = transformMatrix[0][0];
    mat[0][1] = transformMatrix[0][1];
    mat[0][2] = transformMatrix[0][2];

    mat[1][0] = transformMatrix[1][0];
    mat[1][1] = transformMatrix[1][1];
    mat[1][2] = transformMatrix[1][2];

    mat[2][0] = transformMatrix[2][0];
    mat[2][1] = transformMatrix[2][1];
    mat[2][2] = transformMatrix[2][2];
}
//------------------------------------------------------------------------------

void physics::CRigidBody::getOrientation(real matrix[9]) const {
    matrix[0] = transformMatrix[0][0]; // 0
    matrix[1] = transformMatrix[0][1]; // 1
    matrix[2] = transformMatrix[0][2]; // 2

    matrix[3] = transformMatrix[1][0]; // 4
    matrix[4] = transformMatrix[1][1]; // 5
    matrix[5] = transformMatrix[1][2]; // 6

    matrix[6] = transformMatrix[2][0]; // 8
    matrix[7] = transformMatrix[2][1]; // 9
    matrix[8] = transformMatrix[2][2]; // 10
}
//------------------------------------------------------------------------------

void physics::CRigidBody::getTransform(Matrix4f *transform) const {
    //memcpy(transform, &transformMatrix.data, sizeof (Matrix4f));
    *transform = transformMatrix;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::getTransform(real *matrix) const {
    //memcpy(matrix, transformMatrix.data, sizeof (real)*12);
    matrix[0] = transformMatrix[0][0];
    matrix[1] = transformMatrix[0][1];
    matrix[2] = transformMatrix[0][2];
    matrix[3] = transformMatrix[0][3];

    matrix[4] = transformMatrix[1][0];
    matrix[5] = transformMatrix[1][1];
    matrix[6] = transformMatrix[1][2];
    matrix[7] = transformMatrix[1][3];

    matrix[8] = transformMatrix[2][0];
    matrix[9] = transformMatrix[2][1];
    matrix[10] = transformMatrix[2][2];
    matrix[11] = transformMatrix[2][3];

    matrix[12] = matrix[13] = matrix[14] = 0;
    matrix[15] = 1;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::getGLTransform(float *matrix) const {
    if(!matrix)
        return;
    //getTransform(matrix);
    //return;
    matrix[0] = (float)transformMatrix[0][0]; // 0
    matrix[1] = (float)transformMatrix[1][0]; // 4
    matrix[2] = (float)transformMatrix[2][0]; // 8
    matrix[3] = 0;

    matrix[4] = (float)transformMatrix[0][1]; // 1
    matrix[5] = (float)transformMatrix[1][1]; // 5
    matrix[6] = (float)transformMatrix[2][1]; // 9
    matrix[7] = 0;

    matrix[8] = (float)transformMatrix[0][2]; // 2
    matrix[9] = (float)transformMatrix[1][2]; // 6
    matrix[10] = (float)transformMatrix[2][2]; // 10
    matrix[11] = 0;

    matrix[12] = (float)transformMatrix[0][3]; // 3
    matrix[13] = (float)transformMatrix[1][3]; // 7
    matrix[14] = (float)transformMatrix[2][3]; // 11
    matrix[15] = 1;
}
//------------------------------------------------------------------------------

Matrix4f physics::CRigidBody::getTransform(void) const {
    return transformMatrix;
}
//------------------------------------------------------------------------------

Vector3f physics::CRigidBody::getPointInLocalSpace(const Vector3f &point) const {
    //return transformMatrix.transformInverse(point);
    return physics::transformInverse(transformMatrix, point);
}
//------------------------------------------------------------------------------

Vector3f physics::CRigidBody::getPointInWorldSpace(const Vector3f &point) const {
    //return transformMatrix.transform(point);    
    return physics::transform(transformMatrix, point);
}
//------------------------------------------------------------------------------

Vector3f physics::CRigidBody::getDirectionInLocalSpace(const Vector3f &direction) const {
    //return transformMatrix.transformInverseDirection(direction);
    return physics::transformInverseDirection(transformMatrix, direction);
}
//------------------------------------------------------------------------------

Vector3f physics::CRigidBody::getDirectionInWorldSpace(const Vector3f &direction) const {
    //return transformMatrix.transformDirection(direction);
    return physics::transformDirection(transformMatrix, direction);
}
//------------------------------------------------------------------------------

void physics::CRigidBody::setVelocity(const Vector3f &velocity) {
    CRigidBody::velocity = velocity;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::setVelocity(const real x, const real y, const real z) {
    velocity.x = x;
    velocity.y = y;
    velocity.z = z;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::getVelocity(Vector3f *velocity) const {
    *velocity = CRigidBody::velocity;
}
//------------------------------------------------------------------------------

Vector3f physics::CRigidBody::getVelocity(void) const {
    return velocity;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::addVelocity(const Vector3f &deltaVelocity) {
    velocity += deltaVelocity;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::setRotation(const Vector3f &rotation) {
    CRigidBody::rotation = rotation;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::setRotation(const real x, const real y, const real z) {
    rotation.x = x;
    rotation.y = y;
    rotation.z = z;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::getRotation(Vector3f *rotation) const {
    *rotation = CRigidBody::rotation;
}
//------------------------------------------------------------------------------

Vector3f physics::CRigidBody::getRotation(void) const {
    return rotation;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::addRotation(const Vector3f &deltaRotation) {
    rotation += deltaRotation;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::setAwake(const bool awake) {
    if(awake) {
        isAwake = true;

        // Add a bit of motion to avoid it falling asleep immediately.
        motion = sleepEpsilon * 2.0f;
    } else {
        isAwake = false;
        velocity = Vector3f();
        rotation = Vector3f();
    }
}
//------------------------------------------------------------------------------

void physics::CRigidBody::setCanSleep(const bool canSleep) {
    CRigidBody::canSleep = canSleep;

    if(!canSleep && !isAwake) setAwake();
}
//------------------------------------------------------------------------------

void physics::CRigidBody::getLastFrameAcceleration(Vector3f *acceleration) const {
    *acceleration = lastFrameAcceleration;
}
//------------------------------------------------------------------------------

Vector3f physics::CRigidBody::getLastFrameAcceleration(void) const {
    return lastFrameAcceleration;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::clearAccumulators(void) {
    forceAccum = Vector3f();
    torqueAccum = Vector3f();
}
//------------------------------------------------------------------------------

void physics::CRigidBody::addForce(const Vector3f &force) {
    forceAccum += force;
    isAwake = true;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::addForceAtBodyPoint(const Vector3f &force,
                                              const Vector3f &point) {
    // Convert to coordinates relative to center of mass.
    Vector3f pt = getPointInWorldSpace(point);
    addForceAtPoint(force, pt);

}
//------------------------------------------------------------------------------

void physics::CRigidBody::addForceAtPoint(const Vector3f &force,
                                          const Vector3f &point) {
    // Convert to coordinates relative to center of mass.
    Vector3f pt = point;
    pt -= position;

    forceAccum += force;
    //torqueAccum += pt % force; // vector product

    torqueAccum += math::cross(pt, force);

    isAwake = true;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::addTorque(const Vector3f &torque) {
    torqueAccum += torque;
    isAwake = true;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::setAcceleration(const Vector3f &acceleration) {
    CRigidBody::acceleration = acceleration;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::setAcceleration(const real x, const real y, const real z) {
    acceleration.x = x;
    acceleration.y = y;
    acceleration.z = z;
}
//------------------------------------------------------------------------------

void physics::CRigidBody::getAcceleration(Vector3f *acceleration) const {
    *acceleration = CRigidBody::acceleration;
}
//------------------------------------------------------------------------------

Vector3f physics::CRigidBody::getAcceleration(void) const {
    return acceleration;
}
//------------------------------------------------------------------------------
#endif /* FG_USING_BULLET */