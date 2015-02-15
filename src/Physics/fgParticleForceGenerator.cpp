/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/*
 * Implementation file for the particle force generators.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under license. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software license.
 */

#include "fgParticleForceGenerator.h"

using namespace fg;

void physics::CParticleForceRegistry::updateForces(real duration) {
    Registry::iterator i = registrations.begin();
    for(; i != registrations.end(); i++) {
        i->forcegen->updateForce(i->particle, duration);
    }
}

void physics::CParticleForceRegistry::add(CParticle* particle, CParticleForceGenerator* forcegen) {
    CParticleForceRegistry::ParticleForceRegistration registration;
    registration.particle = particle;
    registration.forcegen = forcegen;
    registrations.push_back(registration);
}

void physics::CParticleForceRegistry::remove(CParticle* particle, CParticleForceGenerator* forcegen) {
    Registry::iterator i = registrations.begin();
    for(; i != registrations.end(); i++) {
        if(i->forcegen == forcegen && i->particle == particle) {
            registrations.erase(i);
            break;
        }
    }
}

physics::CParticleGravity::CParticleGravity(const Vector3f& gravity) : gravity(gravity) { }

void physics::CParticleGravity::updateForce(CParticle* particle, real duration) {
    // Check that we do not have infinite mass
    if(!particle->hasFiniteMass()) return;

    // Apply the mass-scaled force to the particle
    particle->addForce(gravity * particle->getMass());
}

physics::CParticleDrag::CParticleDrag(real k1, real k2) : k1(k1), k2(k2) { }

void physics::CParticleDrag::updateForce(CParticle* particle, real duration) {
    Vector3f force;
    particle->getVelocity(&force);
    
    // Calculate the total drag coefficient
    real dragCoeff = math::length(force);
    
    dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

    // Calculate the final force and apply it
    //force.normalise();
    force = math::normalize(force);
    force *= -dragCoeff;
    particle->addForce(force);
}

physics::CParticleSpring::CParticleSpring(CParticle *other, real sc, real rl) :
other(other), springConstant(sc), restLength(rl) { }

void physics::CParticleSpring::updateForce(CParticle* particle, real duration) {
    // Calculate the vector of the spring
    Vector3f force;
    particle->getPosition(&force);
    force -= other->getPosition();

    // Calculate the magnitude of the force
    real magnitude = math::length(force);
    magnitude = real_abs(magnitude - restLength);
    magnitude *= springConstant;

    // Calculate the final force and apply it
    //force.normalise();
    force = math::normalize(force);
    force *= -magnitude;
    particle->addForce(force);
}

physics::CParticleBuoyancy::CParticleBuoyancy(real maxDepth,
                                   real volume,
                                   real waterHeight,
                                   real liquidDensity) :
maxDepth(maxDepth), volume(volume),
waterHeight(waterHeight), liquidDensity(liquidDensity) { }

void physics::CParticleBuoyancy::updateForce(CParticle* particle, real duration) {
    // Calculate the submersion depth
    real depth = particle->getPosition().y;

    // Check if we're out of the water
    if(depth >= waterHeight + maxDepth) return;
    Vector3f force(0, 0, 0);

    // Check if we're at maximum depth
    if(depth <= waterHeight - maxDepth) {
        force.y = liquidDensity * volume;
        particle->addForce(force);
        return;
    }

    // Otherwise we are partly submerged
    force.y = liquidDensity * volume *
            (depth - maxDepth - waterHeight) / 2 * maxDepth;
    particle->addForce(force);
}

physics::CParticleBungee::CParticleBungee(CParticle *other, real sc, real rl)
: other(other), springConstant(sc), restLength(rl) { }

void physics::CParticleBungee::updateForce(CParticle* particle, real duration) {
    // Calculate the vector of the spring
    Vector3f force;
    particle->getPosition(&force);
    force -= other->getPosition();

    // Check if the bungee is compressed
    real magnitude = math::length(force);
    if(magnitude <= restLength) return;

    // Calculate the magnitude of the force
    magnitude = springConstant * (restLength - magnitude);

    // Calculate the final force and apply it
    //force.normalise();
    force = math::normalize(force);
    force *= -magnitude;
    particle->addForce(force);
}

physics::CParticleFakeSpring::CParticleFakeSpring(Vector3f *anchor, real sc, real d)
: anchor(anchor), springConstant(sc), damping(d) { }

void physics::CParticleFakeSpring::updateForce(CParticle* particle, real duration) {
    // Check that we do not have infinite mass
    if(!particle->hasFiniteMass()) return;

    // Calculate the relative position of the particle to the anchor
    Vector3f position;
    particle->getPosition(&position);
    position -= *anchor;

    // Calculate the constants and check they are in bounds.
    real gamma = 0.5f * real_sqrt(4 * springConstant - damping * damping);
    if(gamma == 0.0f) return;
    Vector3f c = position * (damping / (2.0f * gamma)) +
            particle->getVelocity() * (1.0f / gamma);

    // Calculate the target position
    Vector3f target = position * real_cos(gamma * duration) +
            c * real_sin(gamma * duration);
    target *= real_exp(-0.5f * duration * damping);

    // Calculate the resulting acceleration and therefore the force
    Vector3f accel = (target - position) * ((real)1.0 / (duration * duration)) -
            particle->getVelocity() * ((real)1.0 / duration);
    particle->addForce(accel * particle->getMass());
}

physics::CParticleAnchoredSpring::CParticleAnchoredSpring() { }

physics::CParticleAnchoredSpring::CParticleAnchoredSpring(Vector3f *anchor,
                                               real sc, real rl)
: anchor(anchor), springConstant(sc), restLength(rl) { }

void physics::CParticleAnchoredSpring::init(Vector3f *anchor, real springConstant,
                                  real restLength) {
    CParticleAnchoredSpring::anchor = anchor;
    CParticleAnchoredSpring::springConstant = springConstant;
    CParticleAnchoredSpring::restLength = restLength;
}

void physics::CParticleAnchoredBungee::updateForce(CParticle* particle, real duration) {
    // Calculate the vector of the spring
    Vector3f force;
    particle->getPosition(&force);
    force -= *anchor;

    // Calculate the magnitude of the force
    real magnitude = math::length(force);//force.magnitude();
    if(magnitude < restLength) return;

    magnitude = magnitude - restLength;
    magnitude *= springConstant;

    // Calculate the final force and apply it
    force = math::normalize(force); //force.normalise();
    force *= -magnitude;
    particle->addForce(force);
}

void physics::CParticleAnchoredSpring::updateForce(CParticle* particle, real duration) {
    // Calculate the vector of the spring
    Vector3f force;
    particle->getPosition(&force);
    force -= *anchor;

    // Calculate the magnitude of the force
    real magnitude = math::length(force);//force.magnitude();
    magnitude = (restLength - magnitude) * springConstant;

    // Calculate the final force and apply it
    //force.normalise();
    force = math::normalize(force);
    force *= magnitude;
    particle->addForce(force);
}
