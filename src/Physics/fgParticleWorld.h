/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/*
 * Interface file for the particle / mass aggregate world structure.
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
 * This file contains the definitions for a structure to hold any number o
 * particle masses, and their connections.
 */
#ifndef FG_INC_PARTICLE_WORLD
    #define FG_INC_PARTICLE_WORLD
    #define FG_INC_PARTICLE_WORLD_BLOCK

    #include "fgParticleForceGenerator.h"
    #include "fgParticleLink.h"
    #include "fgVector.h"
    #include "fgBool.h"

namespace fg {
    namespace physics {

        /**
         * Keeps track of a set of particles, and provides the means to
         * update them all.
         */
        class CParticleWorld {
        public:
            typedef CVector<CParticle*> Particles;
            typedef CVector<CParticleContactGenerator*> ContactGenerators;

        protected:
            /**
             * Holds the particles
             */
            Particles m_particles;

            /**
             * True if the world should calculate the number of iterations
             * to give the contact resolver at each frame.
             */
            fgBool m_isCalculateIterations;

            /**
             * Holds the force generators for the particles in this world.
             */
            CParticleForceRegistry m_registry;

            /**
             * Holds the resolver for contacts.
             */
            CParticleContactResolver m_resolver;

            /**
             * Contact generators.
             */
            ContactGenerators m_contactGenerators;

            /**
             * Holds the list of contacts.
             */
            CParticleContact *m_contacts;

            /**
             * Holds the maximum number of contacts allowed (i.e. the
             * size of the contacts array).
             */
            unsigned m_maxContacts;

        public:

            /**
             * Creates a new particle simulator that can handle up to the
             * given number of contacts per frame. You can also optionally
             * give a number of contact-resolution iterations to use. If you
             * don't give a number of iterations, then twice the number of
             * contacts will be used.
             */
            CParticleWorld(unsigned maxContacts, unsigned iterations = 0);

            /**
             * Deletes the simulator.
             */
            virtual ~CParticleWorld();

            /**
             * Calls each of the registered contact generators to report
             * their contacts. Returns the number of generated contacts.
             */
            unsigned generateContacts(void);

            /**
             * Integrates all the particles in this world forward in time
             * by the given duration.
             */
            void integrate(real duration);

            /**
             * Processes all the physics for the particle world.
             */
            void runPhysics(real duration);

            /**
             * Initializes the world for a simulation frame. This clears
             * the force accumulators for particles in the world. After
             * calling this, the particles can have their forces for this
             * frame added.
             */
            void startFrame(void);

            /**
             *  Returns the list of particles.
             */
            Particles& getParticles(void);

            /**
             * Returns the list of contact generators.
             */
            ContactGenerators& getContactGenerators(void);

            /**
             * Returns the force registry.
             */
            CParticleForceRegistry& getForceRegistry(void);
        };

        /**
         * A contact generator that takes an STL vector of particle pointers and
         * collides them against the ground.
         */
        class CGroundContacts : public physics::CParticleContactGenerator {
            physics::CParticleWorld::Particles *particles;

        public:
            void init(physics::CParticleWorld::Particles *particles);

            virtual unsigned addContact(physics::CParticleContact *contact,
                                        unsigned limit) const;
        };

    } // namespace physics
} // namespace fg

    #undef FG_INC_PARTICLE_WORLD_BLOCK
#endif /* FG_INC_PARTICLE_WORLD */
