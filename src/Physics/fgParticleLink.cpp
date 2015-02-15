/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/*
 * Implementation file for particle links.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under license. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software license.
 */

#include "fgParticleLink.h"

using namespace fg;

physics::real physics::CParticleLink::currentLength() const {
    Vector3f relativePos = particle[0]->getPosition() -
            particle[1]->getPosition();
    return math::length(relativePos);
}

unsigned physics::CParticleCable::addContact(CParticleContact *contact,
                                   unsigned limit) const {
    // Find the length of the cable
    real length = currentLength();

    // Check if we're over-extended
    if(length < maxLength) {
        return 0;
    }

    // Otherwise return the contact
    contact->particle[0] = particle[0];
    contact->particle[1] = particle[1];

    // Calculate the normal
    Vector3f normal = particle[1]->getPosition() - particle[0]->getPosition();
    //normal.normalise();
    normal = math::normalize(normal);
    contact->contactNormal = normal;

    contact->penetration = length - maxLength;
    contact->restitution = restitution;

    return 1;
}

unsigned physics::CParticleRod::addContact(CParticleContact *contact,
                                 unsigned limit) const {
    // Find the length of the rod
    real currentLen = currentLength();

    // Check if we're over-extended
    if(currentLen == length) {
        return 0;
    }

    // Otherwise return the contact
    contact->particle[0] = particle[0];
    contact->particle[1] = particle[1];

    // Calculate the normal
    Vector3f normal = particle[1]->getPosition() - particle[0]->getPosition();
    //normal.normalise();
    normal = math::normalize(normal);

    // The contact normal depends on whether we're extending or compressing
    if(currentLen > length) {
        contact->contactNormal = normal;
        contact->penetration = currentLen - length;
    } else {
        contact->contactNormal = normal * ((real)-1.0);
        contact->penetration = length - currentLen;
    }

    // Always use zero restitution (no bounciness)
    contact->restitution = 0;

    return 1;
}

physics::real physics::CParticleConstraint::currentLength() const {
    Vector3f relativePos = particle->getPosition() - anchor;
    return math::length(relativePos); // magnitude()
}

unsigned physics::CParticleCableConstraint::addContact(CParticleContact *contact,
                                             unsigned limit) const {
    // Find the length of the cable
    real length = currentLength();

    // Check if we're over-extended
    if(length < maxLength) {
        return 0;
    }

    // Otherwise return the contact
    contact->particle[0] = particle;
    contact->particle[1] = 0;

    // Calculate the normal
    Vector3f normal = anchor - particle->getPosition();
    //normal.normalise();
    normal = math::normalize(normal);
    contact->contactNormal = normal;

    contact->penetration = length - maxLength;
    contact->restitution = restitution;

    return 1;
}

unsigned physics::CParticleRodConstraint::addContact(CParticleContact *contact,
                                           unsigned limit) const {
    // Find the length of the rod
    real currentLen = currentLength();

    // Check if we're over-extended
    if(currentLen == length) {
        return 0;
    }

    // Otherwise return the contact
    contact->particle[0] = particle;
    contact->particle[1] = 0;

    // Calculate the normal
    Vector3f normal = anchor - particle->getPosition();
    //normal.normalise();
    normal = math::normalize(normal);

    // The contact normal depends on whether we're extending or compressing
    if(currentLen > length) {
        contact->contactNormal = normal;
        contact->penetration = currentLen - length;
    } else {
        contact->contactNormal = normal * ((real)-1.0);
        contact->penetration = length - currentLen;
    }

    // Always use zero restitution (no bounciness)
    contact->restitution = 0;

    return 1;
}