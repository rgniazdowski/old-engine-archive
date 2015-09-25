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
 * Interface file for the particle links.
 *
 * Part of the Cyclone physics system.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under license. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software license.
 */

/**
 * @file
 *
 * This file contains classes representing the connections between
 * particles.
 */
#ifndef FG_INC_PHYSICS_PARTICLE_LINK
    #define FG_INC_PHYSICS_PARTICLE_LINK
    #define FG_INC_PHYSICS_PARTICLE_LINK_BLOCK

    #include "fgBuildConfig.h"
    #if !defined(FG_USING_BULLET)
        #include "fgParticleContact.h"
        #include "fgParticleContactResolver.h"

namespace fg {
    namespace physics {

        /**
         * Links connect two particles together, generating a contact if
         * they violate the constraints of their link. It is used as a
         * base class for cables and rods, and could be used as a base
         * class for springs with a limit to their extension..
         */
        class CParticleLink : public CParticleContactGenerator {
        public:
            /**
             * Holds the pair of particles that are connected by this link.
             */
            CParticle* particle[2];

        protected:
            /**
             * Returns the current length of the link.
             */
            real currentLength(void) const;

        public:
            /**
             * Geneates the contacts to keep this link from being
             * violated. This class can only ever generate a single
             * contact, so the pointer can be a pointer to a single
             * element, the limit parameter is assumed to be at least one
             * (zero isn't valid) and the return value is either 0, if the
             * cable wasn't over-extended, or one if a contact was needed.
             *
             * NB: This method is declared in the same way (as pure
             * virtual) in the parent class, but is replicated here for
             * documentation purposes.
             */
            virtual unsigned addContact(CParticleContact *contact,
                                        unsigned limit) const = 0;
        };

        /**
         * Cables link a pair of particles, generating a contact if they
         * stray too far apart.
         */
        class CParticleCable : public CParticleLink {
        public:
            /**
             * Holds the maximum length of the cable.
             */
            real maxLength;

            /**
             * Holds the restitution (bounciness) of the cable.
             */
            real restitution;

        public:
            /**
             * Fills the given contact structure with the contact needed
             * to keep the cable from over-extending.
             */
            virtual unsigned addContact(CParticleContact *contact,
                                        unsigned limit) const;
        };

        /**
         * Rods link a pair of particles, generating a contact if they
         * stray too far apart or too close.
         */
        class CParticleRod : public CParticleLink {
        public:
            /**
             * Holds the length of the rod.
             */
            real length;

        public:
            /**
             * Fills the given contact structure with the contact needed
             * to keep the rod from extending or compressing.
             */
            virtual unsigned addContact(CParticleContact *contact,
                                        unsigned limit) const;
        };

        /**
         * Constraints are just like links, except they connect a particle to
         * an immovable anchor point.
         */
        class CParticleConstraint : public CParticleContactGenerator {
        public:
            /**
             * Holds the particles connected by this constraint.
             */
            CParticle* particle;

            /**
             * The point to which the particle is anchored.
             */
            Vector3f anchor;

        protected:
            /**
             * Returns the current length of the link.
             */
            real currentLength() const;

        public:
            /**
             * Geneates the contacts to keep this link from being
             * violated. This class can only ever generate a single
             * contact, so the pointer can be a pointer to a single
             * element, the limit parameter is assumed to be at least one
             * (zero isn't valid) and the return value is either 0, if the
             * cable wasn't over-extended, or one if a contact was needed.
             *
             * NB: This method is declared in the same way (as pure
             * virtual) in the parent class, but is replicated here for
             * documentation purposes.
             */
            virtual unsigned addContact(CParticleContact *contact,
                                        unsigned limit) const = 0;
        };

        /**
         * Cables link a particle to an anchor point, generating a contact if they
         * stray too far apart.
         */
        class CParticleCableConstraint : public CParticleConstraint {
        public:
            /**
             * Holds the maximum length of the cable.
             */
            real maxLength;

            /**
             * Holds the restitution (bounciness) of the cable.
             */
            real restitution;

        public:
            /**
             * Fills the given contact structure with the contact needed
             * to keep the cable from over-extending.
             */
            virtual unsigned addContact(CParticleContact *contact,
                                        unsigned limit) const;
        };

        /**
         * Rods link a particle to an anchor point, generating a contact if they
         * stray too far apart or too close.
         */
        class CParticleRodConstraint : public CParticleConstraint {
        public:
            /**
             * Holds the length of the rod.
             */
            real length;

        public:
            /**
             * Fills the given contact structure with the contact needed
             * to keep the rod from extending or compressing.
             */
            virtual unsigned addContact(CParticleContact *contact,
                                        unsigned limit) const;
        };
    } // namespace physics
} // namespace fg
    #endif /* FG_USING_BULLET */
    #undef FG_INC_PHYSICS_PARTICLE_LINK_BLOCK
#endif /* FG_INC_PHYSICS_PARTICLE_LINK */
