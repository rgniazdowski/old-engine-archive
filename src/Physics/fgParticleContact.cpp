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
 * Implementation file for the particle contact resolution system.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under license. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software license.
 */

#include "fgParticleContact.h"

using namespace fg;

//------------------------------------------------------------------------------

void physics::CParticleContact::resolve(real duration) {
    resolveVelocity(duration);
    resolveInterpenetration(duration);
}
//------------------------------------------------------------------------------

physics::real physics::CParticleContact::calculateSeparatingVelocity() const {
    Vector3f relativeVelocity = particle[0]->getVelocity();
    if(particle[1]) relativeVelocity -= particle[1]->getVelocity();
    return math::dot(relativeVelocity, contactNormal);
}
//------------------------------------------------------------------------------

void physics::CParticleContact::resolveVelocity(real duration) {
    // Find the velocity in the direction of the contact
    real separatingVelocity = calculateSeparatingVelocity();

    // Check if it needs to be resolved
    if(separatingVelocity > 0) {
        // The contact is either separating, or stationary - there's
        // no impulse required.
        return;
    }

    // Calculate the new separating velocity
    real newSepVelocity = -separatingVelocity * restitution;

    // Check the velocity build-up due to acceleration only
    Vector3f accCausedVelocity = particle[0]->getAcceleration();
    if(particle[1]) accCausedVelocity -= particle[1]->getAcceleration();
    real accCausedSepVelocity = math::dot(accCausedVelocity, contactNormal) * duration;

    // If we've got a closing velocity due to acceleration build-up,
    // remove it from the new separating velocity
    if(accCausedSepVelocity < 0) {
        newSepVelocity += restitution * accCausedSepVelocity;

        // Make sure we haven't removed more than was
        // there to remove.
        if(newSepVelocity < 0) newSepVelocity = 0;
    }

    real deltaVelocity = newSepVelocity - separatingVelocity;

    // We apply the change in velocity to each object in proportion to
    // their inverse mass (i.e. those with lower inverse mass [higher
    // actual mass] get less change in velocity)..
    real totalInverseMass = particle[0]->getInverseMass();
    if(particle[1]) totalInverseMass += particle[1]->getInverseMass();

    // If all particles have infinite mass, then impulses have no effect
    if(totalInverseMass <= 0) return;

    // Calculate the impulse to apply
    real impulse = deltaVelocity / totalInverseMass;

    // Find the amount of impulse per unit of inverse mass
    Vector3f impulsePerIMass = contactNormal * impulse;

    // Apply impulses: they are applied in the direction of the contact,
    // and are proportional to the inverse mass.
    particle[0]->setVelocity(particle[0]->getVelocity() +
                             impulsePerIMass * particle[0]->getInverseMass()
                             );
    if(particle[1]) {
        // Particle 1 goes in the opposite direction
        particle[1]->setVelocity(particle[1]->getVelocity() +
                                 impulsePerIMass * -particle[1]->getInverseMass()
                                 );
    }
}
//------------------------------------------------------------------------------

void physics::CParticleContact::resolveInterpenetration(real duration) {
    // If we don't have any penetration, skip this step.
    if(penetration <= 0) return;

    // The movement of each object is based on their inverse mass, so
    // total that.
    real totalInverseMass = particle[0]->getInverseMass();
    if(particle[1]) totalInverseMass += particle[1]->getInverseMass();

    // If all particles have infinite mass, then we do nothing
    if(totalInverseMass <= 0) return;

    // Find the amount of penetration resolution per unit of inverse mass
    Vector3f movePerIMass = contactNormal * (penetration / totalInverseMass);

    // Calculate the the movement amounts
    particleMovement[0] = movePerIMass * particle[0]->getInverseMass();
    if(particle[1]) {
        particleMovement[1] = movePerIMass * -particle[1]->getInverseMass();
    } else {
        particleMovement[1] = Vector3f();
    }

    // Apply the penetration resolution
    particle[0]->setPosition(particle[0]->getPosition() + particleMovement[0]);
    if(particle[1]) {
        particle[1]->setPosition(particle[1]->getPosition() + particleMovement[1]);
    }
}
//------------------------------------------------------------------------------

physics::CParticleContactResolver::CParticleContactResolver(unsigned iterations) : iterations(iterations) { }
//------------------------------------------------------------------------------

void physics::CParticleContactResolver::setIterations(unsigned iterations) {
    CParticleContactResolver::iterations = iterations;
}
//------------------------------------------------------------------------------

void physics::CParticleContactResolver::resolveContacts(CParticleContact *contactArray,
                                                        unsigned numContacts,
                                                        real duration) {
    unsigned i;

    iterationsUsed = 0;
    while(iterationsUsed < iterations) {
        // Find the contact with the largest closing velocity;
        real max = REAL_MAX;
        unsigned maxIndex = numContacts;
        for(i = 0; i < numContacts; i++) {
            real sepVel = contactArray[i].calculateSeparatingVelocity();
            if(sepVel < max &&
               (sepVel < 0 || contactArray[i].penetration > 0)) {
                max = sepVel;
                maxIndex = i;
            }
        }

        // Do we have anything worth resolving?
        if(maxIndex == numContacts) break;

        // Resolve this contact
        contactArray[maxIndex].resolve(duration);

        // Update the interpenetrations for all particles
        Vector3f *move = contactArray[maxIndex].particleMovement;
        for(i = 0; i < numContacts; i++) {
            if(contactArray[i].particle[0] == contactArray[maxIndex].particle[0]) {
                contactArray[i].penetration -= math::dot(move[0], contactArray[i].contactNormal);
            } else if(contactArray[i].particle[0] == contactArray[maxIndex].particle[1]) {
                contactArray[i].penetration -= math::dot(move[1], contactArray[i].contactNormal);
            }
            if(contactArray[i].particle[1]) {
                if(contactArray[i].particle[1] == contactArray[maxIndex].particle[0]) {
                    contactArray[i].penetration += math::dot(move[0], contactArray[i].contactNormal);
                } else if(contactArray[i].particle[1] == contactArray[maxIndex].particle[1]) {
                    contactArray[i].penetration += math::dot(move[1], contactArray[i].contactNormal);
                }
            }
        }

        iterationsUsed++;
    }
}
//------------------------------------------------------------------------------
