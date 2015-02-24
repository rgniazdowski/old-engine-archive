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
 * Implementation file for the particle class.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under license. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software license.
 */

#include <assert.h>
#include "fgParticle.h"

using namespace fg;

/*
 * --------------------------------------------------------------------------
 * FUNCTIONS DECLARED IN HEADER:
 * --------------------------------------------------------------------------
 */

void physics::CParticle::integrate(real duration)
{
    // We don't integrate things with zero mass.
    if (inverseMass <= 0.0f) return;

    assert(duration > 0.0);

    // Update linear position.
    //position.addScaledVector(velocity, duration);
    position += velocity * duration;

    // Work out the acceleration from the force
    Vector3f resultingAcc = acceleration;
    //resultingAcc.addScaledVector(forceAccum, inverseMass);
    resultingAcc += forceAccum * inverseMass;

    // Update linear velocity from the acceleration.
    //velocity.addScaledVector(resultingAcc, duration);
    velocity += resultingAcc * duration;

    // Impose drag.
    velocity *= real_pow(damping, duration);

    // Clear the forces.
    clearAccumulator();
}



void physics::CParticle::setMass(const real mass)
{
    assert(mass != 0);
    physics::CParticle::inverseMass = ((real)1.0)/mass;
}

physics::real physics::CParticle::getMass() const
{
    if (inverseMass == 0) {
        return REAL_MAX;
    } else {
        return ((real)1.0)/inverseMass;
    }
}

void physics::CParticle::setInverseMass(const real inverseMass)
{
    physics::CParticle::inverseMass = inverseMass;
}

physics::real physics::CParticle::getInverseMass() const
{
    return inverseMass;
}

bool physics::CParticle::hasFiniteMass() const
{
    return inverseMass >= 0.0f;
}

void physics::CParticle::setDamping(const real damping)
{
    physics::CParticle::damping = damping;
}

physics::real physics::CParticle::getDamping() const
{
    return damping;
}

void physics::CParticle::setPosition(const Vector3f &position)
{
    physics::CParticle::position = position;
}

void physics::CParticle::setPosition(const real x, const real y, const real z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

void physics::CParticle::getPosition(Vector3f *position) const
{
    *position = physics::CParticle::position;
}

Vector3f physics::CParticle::getPosition() const
{
    return position;
}

void physics::CParticle::setVelocity(const Vector3f &velocity)
{
    physics::CParticle::velocity = velocity;
}

void physics::CParticle::setVelocity(const real x, const real y, const real z)
{
    velocity.x = x;
    velocity.y = y;
    velocity.z = z;
}

void physics::CParticle::getVelocity(Vector3f *velocity) const
{
    *velocity = physics::CParticle::velocity;
}

Vector3f physics::CParticle::getVelocity() const
{
    return velocity;
}

void physics::CParticle::setAcceleration(const Vector3f &acceleration)
{
    physics::CParticle::acceleration = acceleration;
}

void physics::CParticle::setAcceleration(const real x, const real y, const real z)
{
    acceleration.x = x;
    acceleration.y = y;
    acceleration.z = z;
}

void physics::CParticle::getAcceleration(Vector3f *acceleration) const
{
    *acceleration = physics::CParticle::acceleration;
}

Vector3f physics::CParticle::getAcceleration() const
{
    return acceleration;
}

void physics::CParticle::clearAccumulator()
{
    forceAccum = Vector3f();
}

void physics::CParticle::addForce(const Vector3f &force)
{
    forceAccum += force;
}
