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
 * Interface file for the force generators.
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
 * This file contains the interface and sample force generators.
 */
#ifndef FG_INC_PHYSICS_PARTICLE_FORCE_GENERATOR
    #define FG_INC_PHYSICS_PARTICLE_FORCE_GENERATOR
    #define FG_INC_PHYSICS_PARTICLE_FORCE_GENERATOR_BLOCK

    #include "fgParticle.h"
    #if !defined(FG_USING_BULLET)
        #include <vector>

namespace fg {
    namespace physics {

        /**
         * A force generator can be asked to add a force to one or more
         * particles.
         */
        class CParticleForceGenerator {
        public:

            /**
             * Overload this in implementations of the interface to calculate
             * and update the force applied to the given particle.
             */
            virtual void updateForce(CParticle *particle, real duration) = 0;
        };

        /**
         * A force generator that applies a gravitational force. One instance
         * can be used for multiple particles.
         */
        class CParticleGravity : public CParticleForceGenerator {
            /** Holds the acceleration due to gravity. */
            Vector3f gravity;

        public:

            /** Creates the generator with the given acceleration. */
            CParticleGravity(const Vector3f &gravity);

            /** Applies the gravitational force to the given particle. */
            virtual void updateForce(CParticle *particle, real duration);
        };

        /**
         * A force generator that applies a drag force. One instance
         * can be used for multiple particles.
         */
        class CParticleDrag : public CParticleForceGenerator {
            /** Holds the velocity drag coeffificent. */
            real k1;

            /** Holds the velocity squared drag coeffificent. */
            real k2;

        public:

            /** Creates the generator with the given coefficients. */
            CParticleDrag(real k1, real k2);

            /** Applies the drag force to the given particle. */
            virtual void updateForce(CParticle *particle, real duration);
        };

        /**
         * A force generator that applies a Spring force, where
         * one end is attached to a fixed point in space.
         */
        class CParticleAnchoredSpring : public CParticleForceGenerator {
        protected:
            /** The location of the anchored end of the spring. */
            Vector3f *anchor;

            /** Holds the sprint constant. */
            real springConstant;

            /** Holds the rest length of the spring. */
            real restLength;

        public:
            CParticleAnchoredSpring();

            /** Creates a new spring with the given parameters. */
            CParticleAnchoredSpring(Vector3f *anchor,
                                    real springConstant,
                                    real restLength);
            /** Retrieve the anchor point. */
            const Vector3f* getAnchor() const {
                return anchor;
            }

            /** Set the spring's properties. */
            void init(Vector3f *anchor,
                      real springConstant,
                      real restLength);

            /** Applies the spring force to the given particle. */
            virtual void updateForce(CParticle *particle, real duration);
        };

        /**
         * A force generator that applies a bungee force, where
         * one end is attached to a fixed point in space.
         */
        class CParticleAnchoredBungee : public CParticleAnchoredSpring {
        public:
            /** Applies the spring force to the given particle. */
            virtual void updateForce(CParticle *particle, real duration);
        };

        /**
         * A force generator that fakes a stiff spring force, and where
         * one end is attached to a fixed point in space.
         */
        class CParticleFakeSpring : public CParticleForceGenerator {
            /** The location of the anchored end of the spring. */
            Vector3f *anchor;

            /** Holds the sprint constant. */
            real springConstant;

            /** Holds the damping on the oscillation of the spring. */
            real damping;

        public:

            /** Creates a new spring with the given parameters. */
            CParticleFakeSpring(Vector3f *anchor, real springConstant,
                                real damping);

            /** Applies the spring force to the given particle. */
            virtual void updateForce(CParticle *particle, real duration);
        };

        /**
         * A force generator that applies a Spring force.
         */
        class CParticleSpring : public CParticleForceGenerator {
            /** The particle at the other end of the spring. */
            CParticle *other;

            /** Holds the sprint constant. */
            real springConstant;

            /** Holds the rest length of the spring. */
            real restLength;

        public:

            /** Creates a new spring with the given parameters. */
            CParticleSpring(CParticle *other,
                            real springConstant, real restLength);

            /** Applies the spring force to the given particle. */
            virtual void updateForce(CParticle *particle, real duration);
        };

        /**
         * A force generator that applies a spring force only
         * when extended.
         */
        class CParticleBungee : public CParticleForceGenerator {
            /** The particle at the other end of the spring. */
            CParticle *other;

            /** Holds the sprint constant. */
            real springConstant;

            /**
             * Holds the length of the bungee at the point it begins to
             * generator a force.
             */
            real restLength;

        public:

            /** Creates a new bungee with the given parameters. */
            CParticleBungee(CParticle *other,
                            real springConstant, real restLength);

            /** Applies the spring force to the given particle. */
            virtual void updateForce(CParticle *particle, real duration);
        };

        /**
         * A force generator that applies a buoyancy force for a plane of
         * liquid parrallel to XZ plane.
         */
        class CParticleBuoyancy : public CParticleForceGenerator {
            /**
             * The maximum submersion depth of the object before
             * it generates its maximum boyancy force.
             */
            real maxDepth;

            /**
             * The volume of the object.
             */
            real volume;

            /**
             * The height of the water plane above y=0. The plane will be
             * parrallel to the XZ plane.
             */
            real waterHeight;

            /**
             * The density of the liquid. Pure water has a density of
             * 1000kg per cubic meter.
             */
            real liquidDensity;

        public:

            /** Creates a new buoyancy force with the given parameters. */
            CParticleBuoyancy(real maxDepth, real volume, real waterHeight,
                              real liquidDensity = 1000.0f);

            /** Applies the buoyancy force to the given particle. */
            virtual void updateForce(CParticle *particle, real duration);
        };

        /**
         * Holds all the force generators and the particles they apply to.
         */
        class CParticleForceRegistry {
        protected:

            /**
             * Keeps track of one force generator and the particle it
             * applies to.
             */
            struct ParticleForceRegistration {
                CParticle *particle;
                CParticleForceGenerator *forcegen;
            };

            /**
             * Holds the list of registrations.
             */
            typedef std::vector<ParticleForceRegistration> Registry;
            Registry registrations;

        public:
            /**
             * Registers the given force generator to apply to the
             * given particle.
             */
            void add(CParticle* particle, CParticleForceGenerator *fg);

            /**
             * Removes the given registered pair from the registry.
             * If the pair is not registered, this method will have
             * no effect.
             */
            void remove(CParticle* particle, CParticleForceGenerator *fg);

            /**
             * Clears all registrations from the registry. This will
             * not delete the particles or the force generators
             * themselves, just the records of their connection.
             */
            void clear();

            /**
             * Calls all the force generators to update the forces of
             * their corresponding particles.
             */
            void updateForces(real duration);
        };
    } // namespace physics
} // namespace fg
    #endif /* FG_USING_BULLET */
    #undef FG_INC_PHYSICS_PARTICLE_FORCE_GENERATOR_BLOCK
#endif /* FG_INC_PHYSICS_PARTICLE_FORCE_GENERATOR */
