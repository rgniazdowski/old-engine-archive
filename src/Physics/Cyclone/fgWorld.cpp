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
#include "fgBuildConfig.h"
#if !defined(FG_USING_BULLET)
#include "fgWorld.h"
#include "Util/fgTime.h"

using namespace fg;
//------------------------------------------------------------------------------

physics::CWorld::CWorld(unsigned maxContacts, unsigned iterations) :
m_isCalculateIterations(FG_FALSE),
m_resolver(iterations),
m_collisionData(),
m_groundPlane(),
m_useGroundPlane(FG_TRUE),
m_contacts(NULL),
m_maxContacts(maxContacts),
m_maxIterations(iterations) {
    m_contacts = new CContact[maxContacts];
    m_isCalculateIterations = (iterations == 0);
    m_groundPlane.direction.y = 1.0f;
    m_collisionData.contacts = m_contacts;
    m_collisionData.contactArray = m_contacts;
    m_collisionData.reset(m_maxContacts);
}
//------------------------------------------------------------------------------

physics::CWorld::~CWorld() {
    delete[] m_contacts;
}
//------------------------------------------------------------------------------

void physics::CWorld::setGroundPlane(float offset) {
    m_groundPlane.offset = offset;
    m_useGroundPlane = FG_TRUE;
}
//------------------------------------------------------------------------------

void physics::CWorld::setMaxContacts(unsigned int maxContacts) {
    if(maxContacts > 0) {
        if(m_contacts)
            delete[] m_contacts;
        m_contacts = new CContact[maxContacts];
        m_maxContacts = maxContacts;
        m_collisionData.contacts = m_contacts;
        m_collisionData.contactArray = m_contacts;
        m_collisionData.reset(m_maxContacts);
    }
}
//------------------------------------------------------------------------------

void physics::CWorld::startFrame(void) {
    m_collisionData.reset(m_maxContacts);
    // This should be set individually for every different colliding object
    // Dependent on the material used #FIXME
    m_collisionData.friction = 0.6f; // #FIXME
    m_collisionData.restitution = 0.1f;
    m_collisionData.tolerance = 0.1f;
}
//------------------------------------------------------------------------------

void physics::CWorld::finishFrame(void) {
    if (m_isCalculateIterations) { 
        m_resolver.setIterations(m_collisionData.contactCount * 3); // 4? 2?
    }
    m_resolver.resolveContacts(m_collisionData.contactArray,
                               m_collisionData.contactCount,
                               timesys::elapsed());
}
//------------------------------------------------------------------------------


/*
void physics::CWorld::startFrame()
{
    SBodyRegistration *reg = m_firstBody;
    while (reg)
    {
        // Remove all forces from the accumulator
        reg->body->clearAccumulators();
        reg->body->calculateDerivedData();

        // Get the next registration
        reg = reg->next;
    }
}*/
/*
 
unsigned physics::CWorld::generateContacts()
{
    unsigned limit = maxContacts;
    CContact *nextContact = contacts;

    SContactGenRegistration * reg = m_firstContactGen;
    while (reg)
    {
        unsigned used = reg->gen->addContact(nextContact, limit);
        limit -= used;
        nextContact += used;

        // We've run out of contacts to fill. This means we're missing
        // contacts.
        if (limit <= 0) break;

        reg = reg->next;
    }

    // Return the number of contacts used.
    return maxContacts - limit;
}
 */
/*
void physics::CWorld::runPhysics(real duration)
{
    // First apply the force generators
    //registry.updateForces(duration);

    // Then integrate the objects
    SBodyRegistration *reg = m_firstBody;
    while (reg)
    {
        // Remove all forces from the accumulator
        reg->body->integrate(duration);

        // Get the next registration
        reg = reg->next;
    }

    // Generate contacts
    unsigned usedContacts = generateContacts();

    // And process them
    if (m_isCalculateIterations) m_resolver.setIterations(usedContacts * 4);
    m_resolver.resolveContacts(contacts, usedContacts, duration);
}
 */
#endif /* FG_USING_BULLET */
