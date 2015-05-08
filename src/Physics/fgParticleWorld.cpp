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
 * Implementation file for random number generation.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under license. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software license.
 */

#include <cstddef>
#include "fgParticleWorld.h"

using namespace fg;

//------------------------------------------------------------------------------

physics::CParticleWorld::CParticleWorld(unsigned maxContacts, unsigned iterations) :
m_resolver(iterations),
m_maxContacts(maxContacts) {
    m_contacts = new CParticleContact[maxContacts];
    m_isCalculateIterations = (iterations == 0);

}
//------------------------------------------------------------------------------

physics::CParticleWorld::~CParticleWorld() {
    delete[] m_contacts;
}
//------------------------------------------------------------------------------

void physics::CParticleWorld::startFrame() {
    for(Particles::iterator p = m_particles.begin();
        p != m_particles.end();
        p++) {
        // Remove all forces from the accumulator
        (*p)->clearAccumulator();
    }
}
//------------------------------------------------------------------------------

unsigned physics::CParticleWorld::generateContacts() {
    unsigned limit = m_maxContacts;
    CParticleContact *nextContact = m_contacts;

    for(ContactGenerators::iterator g = m_contactGenerators.begin();
        g != m_contactGenerators.end();
        g++) {
        unsigned used = (*g)->addContact(nextContact, limit);
        limit -= used;
        nextContact += used;

        // We've run out of contacts to fill. This means we're missing
        // contacts.
        if(limit <= 0) break;
    }

    // Return the number of contacts used.
    return m_maxContacts - limit;
}
//------------------------------------------------------------------------------

void physics::CParticleWorld::integrate(real duration) {
    for(Particles::iterator p = m_particles.begin();
        p != m_particles.end();
        p++) {
        // Remove all forces from the accumulator
        (*p)->integrate(duration);
    }
}
//------------------------------------------------------------------------------

void physics::CParticleWorld::runPhysics(real duration) {
    // First apply the force generators
    m_registry.updateForces(duration);

    // Then integrate the objects
    integrate(duration);

    // Generate contacts
    unsigned usedContacts = generateContacts();

    // And process them
    if(usedContacts) {
        if(m_isCalculateIterations) m_resolver.setIterations(usedContacts * 2);
        m_resolver.resolveContacts(m_contacts, usedContacts, duration);
    }
}
//------------------------------------------------------------------------------

physics::CParticleWorld::Particles& physics::CParticleWorld::getParticles() {
    return m_particles;
}
//------------------------------------------------------------------------------

physics::CParticleWorld::ContactGenerators& physics::CParticleWorld::getContactGenerators() {
    return m_contactGenerators;
}
//------------------------------------------------------------------------------

physics::CParticleForceRegistry& physics::CParticleWorld::getForceRegistry() {
    return m_registry;
}
//------------------------------------------------------------------------------

void physics::CGroundContacts::init(physics::CParticleWorld::Particles *particles) {
    physics::CGroundContacts::particles = particles;
}
//------------------------------------------------------------------------------

unsigned physics::CGroundContacts::addContact(physics::CParticleContact *contact,
                                              unsigned limit) const {
    unsigned count = 0;
    for(physics::CParticleWorld::Particles::iterator p = particles->begin();
        p != particles->end();
        p++) {
        physics::real y = (*p)->getPosition().y;
        if(y < 0.0f) {
            contact->contactNormal = physics::UP;
            contact->particle[0] = *p;
            contact->particle[1] = NULL;
            contact->penetration = -y;
            contact->restitution = 0.2f;
            contact++;
            count++;
        }

        if(count >= limit) return count;
    }
    return count;
}
//------------------------------------------------------------------------------
