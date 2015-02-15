/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/*
 * Implementation file for the rigid body force generators.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under license. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software license.
 */

#include "fgForceGenerator.h"

using namespace fg;

void physics::CForceRegistry::updateForces(real duration) {
    Registry::iterator i = registrations.begin();
    for(; i != registrations.end(); i++) {
        i->forcegen->updateForce(i->body, duration);
    }
}

void physics::CForceRegistry::add(CRigidBody *body, CForceGenerator *forcegen) {
    CForceRegistry::SForceRegistration registration;
    registration.body = body;
    registration.forcegen = forcegen;
    registrations.push_back(registration);
}

void physics::CForceRegistry::remove(CRigidBody* body, CForceGenerator* forcegen) {
    Registry::iterator i = registrations.begin();
    for(; i != registrations.end(); i++) {
        if(i->forcegen == forcegen && i->body == body) {
            registrations.erase(i);
            break;
        }
    }
}

physics::CBuoyancy::CBuoyancy(const Vector3f &cOfB, real maxDepth, real volume,
                              real waterHeight, real liquidDensity /* = 1000.0f */) {
    centreOfBuoyancy = cOfB;
    CBuoyancy::liquidDensity = liquidDensity;
    CBuoyancy::maxDepth = maxDepth;
    CBuoyancy::volume = volume;
    CBuoyancy::waterHeight = waterHeight;
}

void physics::CBuoyancy::updateForce(CRigidBody *body, real duration) {
    // Calculate the submersion depth
    Vector3f pointInWorld = body->getPointInWorldSpace(centreOfBuoyancy);
    real depth = pointInWorld.y;

    // Check if we're out of the water
    if(depth >= waterHeight + maxDepth) return;
    Vector3f force(0, 0, 0);

    // Check if we're at maximum depth
    if(depth <= waterHeight - maxDepth) {
        force.y = liquidDensity * volume;
        body->addForceAtBodyPoint(force, centreOfBuoyancy);
        return;
    }

    // Otherwise we are partly submerged
    force.y = liquidDensity * volume *
            (depth - maxDepth - waterHeight) / 2 * maxDepth;
    body->addForceAtBodyPoint(force, centreOfBuoyancy);
}

physics::CGravity::CGravity(const Vector3f& gravity) : gravity(gravity) { }

void physics::CGravity::updateForce(CRigidBody* body, real duration) {
    // Check that we do not have infinite mass
    if(!body->hasFiniteMass()) return;

    // Apply the mass-scaled force to the body
    body->addForce(gravity * body->getMass());
}

physics::CSpring::CSpring(const Vector3f &localConnectionPt,
                          CRigidBody *other,
                          const Vector3f &otherConnectionPt,
                          real springConstant,
                          real restLength)
: connectionPoint(localConnectionPt),
otherConnectionPoint(otherConnectionPt),
other(other),
springConstant(springConstant),
restLength(restLength) { }

void physics::CSpring::updateForce(CRigidBody* body, real duration) {
    // Calculate the two ends in world space
    Vector3f lws = body->getPointInWorldSpace(connectionPoint);
    Vector3f ows = other->getPointInWorldSpace(otherConnectionPoint);

    // Calculate the vector of the spring
    Vector3f force = lws - ows;

    // Calculate the magnitude of the force
    real magnitude = math::length(force); //force.magnitude();
    magnitude = real_abs(magnitude - restLength);
    magnitude *= springConstant;

    // Calculate the final force and apply it
    //force.normalise();
    force = math::normalize(force);
    force *= -magnitude;
    body->addForceAtPoint(force, lws);
}

physics::CAero::CAero(const Matrix3f &tensor, const Vector3f &position, const Vector3f *windspeed) {
    CAero::tensor = tensor;
    CAero::position = position;
    CAero::windspeed = windspeed;
}

void physics::CAero::updateForce(CRigidBody *body, real duration) {
    CAero::updateForceFromTensor(body, duration, tensor);
}

void physics::CAero::updateForceFromTensor(CRigidBody *body, real duration,
                                           const Matrix3f &tensor) {
    // Calculate total velocity (windspeed and body's velocity).
    Vector3f velocity = body->getVelocity();
    velocity += *windspeed;

    // Calculate the velocity in body coordinates
    Vector3f bodyVel = physics::transformInverseDirection(body->getTransform(), velocity);

    // Calculate the force in body coordinates
    Vector3f bodyForce = physics::transform(tensor, bodyVel);
    Vector3f force = physics::transformDirection(body->getTransform(), bodyForce);

    // Apply the force
    body->addForceAtBodyPoint(force, position);
}

physics::CAeroControl::CAeroControl(const Matrix3f &base, const Matrix3f &min, const Matrix3f &max,
                                    const Vector3f &position, const Vector3f *windspeed)
:
CAero(base, position, windspeed) {
    CAeroControl::minTensor = min;
    CAeroControl::maxTensor = max;
    controlSetting = 0.0f;
}

Matrix3f physics::CAeroControl::getTensor() {

    if(controlSetting <= -1.0f) return minTensor;
    else if(controlSetting >= 1.0f) return maxTensor;
    else if(controlSetting < 0) {
        return physics::linearInterpolate(minTensor, tensor, controlSetting + 1.0f);
    } else if(controlSetting > 0) {
        return physics::linearInterpolate(tensor, maxTensor, controlSetting);
    } else return tensor;
}

void physics::CAeroControl::setControl(real value) {
    controlSetting = value;
}

void physics::CAeroControl::updateForce(CRigidBody *body, real duration) {
    Matrix3f tensor = getTensor();
    CAero::updateForceFromTensor(body, duration, tensor);
}

void physics::CExplosion::updateForce(CRigidBody* body, real duration) { }