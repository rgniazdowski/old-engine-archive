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
 * Interface file for the contact resolution system.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under license. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software license.
 */

#include "fgContactResolver.h"

using namespace fg;

physics::CContactResolver::CContactResolver(unsigned iterations,
                                            real velocityEpsilon,
                                            real positionEpsilon) {
    setIterations(iterations, iterations);
    setEpsilon(velocityEpsilon, positionEpsilon);
}

physics::CContactResolver::CContactResolver(unsigned velocityIterations,
                                            unsigned positionIterations,
                                            real velocityEpsilon,
                                            real positionEpsilon) {
    setIterations(velocityIterations);
    setEpsilon(velocityEpsilon, positionEpsilon);
}

void physics::CContactResolver::setIterations(unsigned iterations) {
    setIterations(iterations, iterations);
}

void physics::CContactResolver::setIterations(unsigned velocityIterations,
                                              unsigned positionIterations) {
    CContactResolver::m_velocityIterations = velocityIterations;
    CContactResolver::m_positionIterations = positionIterations;
}

void physics::CContactResolver::setEpsilon(real velocityEpsilon,
                                           real positionEpsilon) {
    CContactResolver::m_velocityEpsilon = velocityEpsilon;
    CContactResolver::m_positionEpsilon = positionEpsilon;
}

void physics::CContactResolver::resolveContacts(CContact *contacts,
                                                unsigned numContacts,
                                                real duration) {
    // Make sure we have something to do.
    if(numContacts == 0) return;
    if(!isValid()) return;

    // Prepare the contacts for processing
    prepareContacts(contacts, numContacts, duration);

    // Resolve the interpenetration problems with the contacts.
    adjustPositions(contacts, numContacts, duration);

    // Resolve the velocity problems with the contacts.
    adjustVelocities(contacts, numContacts, duration);
}

void physics::CContactResolver::prepareContacts(CContact* contacts,
                                                unsigned numContacts,
                                                real duration) {
    // Generate contact velocity and axis information.
    CContact* lastContact = contacts + numContacts;
    for(CContact* contact = contacts; contact < lastContact; contact++) {
        // Calculate the internal contact data (inertia, basis, etc).
        contact->calculateInternals(duration);
    }
}

void physics::CContactResolver::adjustVelocities(CContact *c,
                                                 unsigned numContacts,
                                                 real duration) {
    Vector3f velocityChange[2], rotationChange[2];
    Vector3f deltaVel;

    // iteratively handle impacts in order of severity.
    m_velocityIterationsUsed = 0;
    while(m_velocityIterationsUsed < m_velocityIterations) {
        // Find contact with maximum magnitude of probable velocity change.
        real max = m_velocityEpsilon;
        unsigned index = numContacts;
        for(unsigned i = 0; i < numContacts; i++) {
            if(c[i].m_desiredDeltaVelocity > max) {
                max = c[i].m_desiredDeltaVelocity;
                index = i;
            }
        }
        if(index == numContacts) break;

        // Match the awake state at the contact
        c[index].matchAwakeState();

        // Do the resolution on the contact that came out top.
        c[index].applyVelocityChange(velocityChange, rotationChange);

        // With the change in velocity of the two bodies, the update of
        // contact velocities means that some of the relative closing
        // velocities need recomputing.
        for(unsigned i = 0; i < numContacts; i++) {
            // Check each body in the contact
            for(unsigned b = 0; b < 2; b++) if(c[i].body[b]) {
                    // Check for a match with each body in the newly
                    // resolved contact
                    for(unsigned d = 0; d < 2; d++) {
                        if(c[i].body[b] == c[index].body[d]) {
                            deltaVel = velocityChange[d] +
                                    math::cross(rotationChange[d], c[i].m_relativeContactPosition[b]);

                            // The sign of the change is negative if we're dealing
                            // with the second body in a contact.
                            c[i].m_contactVelocity +=
                                    physics::transformTranspose(c[i].m_contactToWorld, deltaVel)
                                    * (real)(b ? -1 : 1);
                            c[i].calculateDesiredDeltaVelocity(duration);
                        }
                    }
                }
        }
        m_velocityIterationsUsed++;
    }
}

void physics::CContactResolver::adjustPositions(CContact *c,
                                                unsigned numContacts,
                                                real duration) {
    unsigned i, index;
    Vector3f linearChange[2], angularChange[2];
    real max;
    Vector3f deltaPosition;

    // iteratively resolve interpenetrations in order of severity.
    m_positionIterationsUsed = 0;
    while(m_positionIterationsUsed < m_positionIterations) {
        // Find biggest penetration
        max = m_positionEpsilon;
        index = numContacts;
        for(i = 0; i < numContacts; i++) {
            if(c[i].penetration > max) {
                max = c[i].penetration;
                index = i;
            }
        }
        if(index == numContacts) break;

        // Match the awake state at the contact
        c[index].matchAwakeState();

        // Resolve the penetration.
        c[index].applyPositionChange(linearChange,
                                     angularChange,
                                     max);

        // Again this action may have changed the penetration of other
        // bodies, so we update contacts.
        for(i = 0; i < numContacts; i++) {
            // Check each body in the contact
            for(unsigned b = 0; b < 2; b++) if(c[i].body[b]) {
                    // Check for a match with each body in the newly
                    // resolved contact
                    for(unsigned d = 0; d < 2; d++) {
                        if(c[i].body[b] == c[index].body[d]) {
                            deltaPosition = linearChange[d] +
                                    math::cross(angularChange[d], c[i].m_relativeContactPosition[b]);

                            // The sign of the change is positive if we're
                            // dealing with the second body in a contact
                            // and negative otherwise (because we're
                            // subtracting the resolution)..
                            c[i].penetration +=
                                    math::dot(deltaPosition, c[i].contactNormal)
                                    * (b ? 1 : -1);
                        }
                    }
                }
        }
        m_positionIterationsUsed++;
    }
}