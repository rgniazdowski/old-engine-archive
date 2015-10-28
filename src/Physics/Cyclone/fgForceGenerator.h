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
#ifndef FG_INC_PHYSICS_FORCE_GENERATOR
    #define FG_INC_PHYSICS_FORCE_GENERATOR
    #define FG_INC_PHYSICS_FORCE_GENERATOR_BLOCK

    #include "fgBuildConfig.h"
    #if !defined(FG_USING_BULLET) && defined(FG_USING_CYCLONE)
        #include "fgRigidBody.h"
        #include "fgParticleForceGenerator.h"
        #include "fgVector.h"

namespace fg {
    namespace physics {

        /**
         * A force generator can be asked to add a force to one or more
         * bodies.
         */
        class CForceGenerator {
        public:

            /**
             * Overload this in implementations of the interface to calculate
             * and update the force applied to the given rigid body.
             */
            virtual void updateForce(CRigidBody *body, real duration) = 0;
        };

        /**
         * A force generator that applies a gravitational force. One instance
         * can be used for multiple rigid bodies.
         */
        class CGravity : public CForceGenerator {
            /** Holds the acceleration due to gravity. */
            Vector3f gravity;

        public:

            /** Creates the generator with the given acceleration. */
            CGravity(const Vector3f &gravity);

            /** Applies the gravitational force to the given rigid body. */
            virtual void updateForce(CRigidBody *body, real duration);
        };

        /**
         * A force generator that applies a Spring force.
         */
        class CSpring : public CForceGenerator {
            /**
             * The point of connection of the spring, in local
             * coordinates.
             */
            Vector3f connectionPoint;

            /**
             * The point of connection of the spring to the other object,
             * in that object's local coordinates.
             */
            Vector3f otherConnectionPoint;

            /** The particle at the other end of the spring. */
            CRigidBody *other;

            /** Holds the sprint constant. */
            real springConstant;

            /** Holds the rest length of the spring. */
            real restLength;

        public:

            /** Creates a new spring with the given parameters. */
            CSpring(const Vector3f &localConnectionPt,
                    CRigidBody *other,
                    const Vector3f &otherConnectionPt,
                    real springConstant,
                    real restLength);

            /** Applies the spring force to the given rigid body. */
            virtual void updateForce(CRigidBody *body, real duration);
        };

        /**
         * A force generator showing a three component explosion effect.
         * This force generator is intended to represent a single
         * explosion effect for multiple rigid bodies. The force generator
         * can also act as a particle force generator.
         */
        class CExplosion : public CForceGenerator,
        public CParticleForceGenerator {
            /**
             * Tracks how long the explosion has been in operation, used
             * for time-sensitive effects.
             */
            real timePassed;

        public:
            // Properties of the explosion, these are public because
            // there are so many and providing a suitable constructor
            // would be cumbersome:

            /**
             * The location of the detonation of the weapon.
             */
            Vector3f detonation;

            // ... Other Explosion code as before ...


            /**
             * The radius up to which objects implode in the first stage
             * of the explosion.
             */
            real implosionMaxRadius;

            /**
             * The radius within which objects don't feel the implosion
             * force. Objects near to the detonation aren't sucked in by
             * the air implosion.
             */
            real implosionMinRadius;

            /**
             * The length of time that objects spend imploding before the
             * concussion phase kicks in.
             */
            real implosionDuration;

            /**
             * The maximal force that the implosion can apply. This should
             * be relatively small to avoid the implosion pulling objects
             * through the detonation point and out the other side before
             * the concussion wave kicks in.
             */
            real implosionForce;

            /**
             * The speed that the shock wave is traveling, this is related
             * to the thickness below in the relationship:
             *
             * thickness >= speed * minimum frame duration
             */
            real shockwaveSpeed;

            /**
             * The shock wave applies its force over a range of distances,
             * this controls how thick. Faster waves require larger
             * thicknesses.
             */
            real shockwaveThickness;

            /**
             * This is the force that is applied at the very centre of the
             * concussion wave on an object that is stationary. Objects
             * that are in front or behind of the wavefront, or that are
             * already moving outwards, get proportionally less
             * force. Objects moving in towards the centre get
             * proportionally more force.
             */
            real peakConcussionForce;

            /**
             * The length of time that the concussion wave is active.
             * As the wave nears this, the forces it applies reduces.
             */
            real concussionDuration;

            /**
             * This is the peak force for stationary objects in
             * the centre of the convection chimney. Force calculations
             * for this value are the same as for peakConcussionForce.
             */
            real peakConvectionForce;

            /**
             * The radius of the chimney cylinder in the xz plane.
             */
            real chimneyRadius;

            /**
             * The maximum height of the chimney.
             */
            real chimneyHeight;

            /**
             * The length of time the convection chimney is active. Typically
             * this is the longest effect to be in operation, as the heat
             * from the explosion outlives the shock wave and implosion
             * itself.
             */
            real convectionDuration;

        public:
            /**
             * Creates a new explosion with sensible default values.
             */
            CExplosion();

            /**
             * Calculates and applies the force that the explosion
             * has on the given rigid body.
             */
            virtual void updateForce(CRigidBody* body, real duration);

            /**
             * Calculates and applies the force that the explosion has
             * on the given particle.
             */
            virtual void updateForce(CParticle* particle, real duration) = 0;

        };

        /**
         * A force generator that applies an aerodynamic force.
         */
        class CAero : public CForceGenerator {
        protected:
            /**
             * Holds the aerodynamic tensor for the surface in body
             * space.
             */
            Matrix3f tensor;

            /**
             * Holds the relative position of the aerodynamic surface in
             * body coordinates.
             */
            Vector3f position;

            /**
             * Holds a pointer to a vector containing the windspeed of the
             * environment. This is easier than managing a separate
             * windspeed vector per generator and having to update it
             * manually as the wind changes.
             */
            const Vector3f* windspeed;

        public:
            /**
             * Creates a new aerodynamic force generator with the
             * given properties.
             */
            CAero(const Matrix3f &tensor,
                  const Vector3f &position,
                  const Vector3f *windspeed);

            /**
             * Applies the force to the given rigid body.
             */
            virtual void updateForce(CRigidBody *body, real duration);

        protected:
            /**
             * Uses an explicit tensor matrix to update the force on
             * the given rigid body. This is exactly the same as for updateForce
             * only it takes an explicit tensor.
             */
            void updateForceFromTensor(CRigidBody *body,
                                       real duration,
                                       const Matrix3f &tensor);
        };

        /**
         * A force generator with a control aerodynamic surface. This
         * requires three inertia tensors, for the two extremes and
         * 'resting' position of the control surface.  The latter tensor is
         * the one inherited from the base class, the two extremes are
         * defined in this class.
         */
        class CAeroControl : public CAero {
        protected:
            /**
             * The aerodynamic tensor for the surface, when the control is at
             * its maximum value.
             */
            Matrix3f maxTensor;

            /**
             * The aerodynamic tensor for the surface, when the control is at
             * its minimum value.
             */
            Matrix3f minTensor;

            /**
             * The current position of the control for this surface. This
             * should range between -1 (in which case the minTensor value
             * is used), through 0 (where the base-class tensor value is
             * used) to +1 (where the maxTensor value is used).
             */
            real controlSetting;

        private:
            /**
             * Calculates the final aerodynamic tensor for the current
             * control setting.
             */
            Matrix3f getTensor(void);

        public:
            /**
             * Creates a new aerodynamic control surface with the given
             * properties.
             */
            CAeroControl(const Matrix3f &base,
                         const Matrix3f &min, const Matrix3f &max,
                         const Vector3f &position, const Vector3f *windspeed);

            /**
             * Sets the control position of this control. This * should
            range between -1 (in which case the minTensor value is *
            used), through 0 (where the base-class tensor value is used) *
            to +1 (where the maxTensor value is used). Values outside that
             * range give undefined results.
             */
            void setControl(real value);

            /**
             * Applies the force to the given rigid body.
             */
            virtual void updateForce(CRigidBody *body, real duration);
        };

        /**
         * A force generator with an aerodynamic surface that can be
         * re-oriented relative to its rigid body. This derives the
         */
        class CAngledAero : public CAero {
            /**
             * Holds the orientation of the aerodynamic surface relative
             * to the rigid body to which it is attached.
             */
            Quaternionf orientation;

        public:
            /**
             * Creates a new aerodynamic surface with the given properties.
             */
            CAngledAero(const Matrix3f &tensor,
                        const Vector3f &position,
                        const Vector3f *windspeed);

            /**
             * Sets the relative orientation of the aerodynamic surface,
             * relative to the rigid body it is attached to. Note that
             * this doesn't affect the point of connection of the surface
             * to the body.
             */
            void setOrientation(const Quaternionf &quat);

            /**
             * Applies the force to the given rigid body.
             */
            virtual void updateForce(CRigidBody *body, real duration);
        };

        /**
         * A force generator to apply a buoyant force to a rigid body.
         */
        class CBuoyancy : public CForceGenerator {
            /**
             * The maximum submersion depth of the object before
             * it generates its maximum buoyancy force.
             */
            real maxDepth;

            /**
             * The volume of the object.
             */
            real volume;

            /**
             * The height of the water plane above y=0. The plane will be
             * parallel to the XZ plane.
             */
            real waterHeight;

            /**
             * The density of the liquid. Pure water has a density of
             * 1000kg per cubic meter.
             */
            real liquidDensity;

            /**
             * The centre of buoyancy of the rigid body, in body coordinates.
             */
            Vector3f centreOfBuoyancy;

        public:

            /** Creates a new buoyancy force with the given parameters. */
            CBuoyancy(const Vector3f &cOfB,
                      real maxDepth, real volume, real waterHeight,
                      real liquidDensity = 1000.0f);

            /**
             * Applies the force to the given rigid body.
             */
            virtual void updateForce(CRigidBody *body, real duration);
        };

        /**
         * Holds all the force generators and the bodies they apply to.
         */
        class CForceRegistry {
        protected:

            /**
             * Keeps track of one force generator and the body it
             * applies to.
             */
            struct SForceRegistration {
                CRigidBody *body;
                CForceGenerator *forcegen;
            };

            /**
             * Holds the list of registrations.
             */
            typedef CVector<SForceRegistration> Registry;
            Registry registrations;

        public:
            /**
             * Registers the given force generator to apply to the
             * given body.
             */
            void add(CRigidBody* body, CForceGenerator *forcegen);

            /**
             * Removes the given registered pair from the registry.
             * If the pair is not registered, this method will have
             * no effect.
             */
            void remove(CRigidBody* body, CForceGenerator *forcegen);

            /**
             * Clears all registrations from the registry. This will
             * not delete the bodies or the force generators
             * themselves, just the records of their connection.
             */
            void clear();

            /**
             * Calls all the force generators to update the forces of
             * their corresponding bodies.
             */
            void updateForces(real duration);
        };
    } // namespace physics
} // namespace fg 
    #endif /* FG_USING_BULLET */
    #undef FG_INC_PHYSICS_FORCE_GENERATOR_BLOCK
#endif /* FG_INC_PHYSICS_FORCE_GENERATOR */
