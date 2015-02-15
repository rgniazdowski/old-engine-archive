/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
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

/**
 * @file
 *
 * This file contains the contact resolution system for cyclone,
 * although it is called the contact resolution system, it handles
 * collisions, contacts (sliding and resting), and constraints (such
 * as joints).
 *
 * The resolver uses an iterative satisfaction algorithm; it loops
 * through each contact and tries to resolve it. This is a very fast
 * algorithm but can be unstable when the contacts are highly
 * inter-related.
 */

#ifndef FG_INC_PHYSICS_CONTACT
    #define FG_INC_PHYSICS_CONTACT
    #define FG_INC_PHYSICS_CONTACT_BLOCK

    #include "fgRigidBody.h"

namespace fg {
    namespace physics {

        /*
         * Forward declaration, see full declaration below for complete
         * documentation.
         */
        class CContactResolver;

        /**
         * A contact represents two bodies in contact. Resolving a
         * contact removes their interpenetration, and applies sufficient
         * impulse to keep them apart. Colliding bodies may also rebound.
         * Contacts can be used to represent positional joints, by making
         * the contact constraint keep the bodies in their correct
         * orientation.
         *
         * It can be a good idea to create a contact object even when the
         * contact isn't violated. Because resolving one contact can violate
         * another, contacts that are close to being violated should be
         * sent to the resolver; that way if one resolution moves the body,
         * the contact may be violated, and can be resolved. If the contact
         * is not violated, it will not be resolved, so you only loose a
         * small amount of execution time.
         *
         * The contact has no callable functions, it just holds the contact
         * details. To resolve a set of contacts, use the contact resolver
         * class.
         */
        class CContact {
            // ... Other data as before ...

            /**
             * The contact resolver object needs access into the contacts to
             * set and effect the contact.
             */
            friend class CContactResolver;

        public:
            /**
             * Holds the bodies that are involved in the contact. The
             * second of these can be NULL, for contacts with the scenery.
             */
            CRigidBody* body[2];

            /**
             * Holds the lateral friction coefficient at the contact.
             */
            real friction;

            /**
             * Holds the normal restitution coefficient at the contact.
             */
            real restitution;

            /**
             * Holds the position of the contact in world coordinates.
             */
            Vector3f contactPoint;

            /**
             * Holds the direction of the contact in world coordinates.
             */
            Vector3f contactNormal;

            /**
             * Holds the depth of penetration at the contact point. If both
             * bodies are specified then the contact point should be midway
             * between the inter-penetrating points.
             */
            real penetration;

            /**
             * Sets the data that doesn't normally depend on the position
             * of the contact (i.e. the bodies, and their material properties).
             */
            void setBodyData(CRigidBody* one, CRigidBody *two,
                             real friction, real restitution);

        protected:

            /**
             * A transform matrix that converts coordinates in the contact's
             * frame of reference to world coordinates. The columns of this
             * matrix form an orthonormal set of vectors.
             */
            Matrix3f m_contactToWorld;

            /**
             * Holds the closing velocity at the point of contact. This is set
             * when the calculateInternals function is run.
             */
            Vector3f m_contactVelocity;

            /**
             * Holds the required change in velocity for this contact to be
             * resolved.
             */
            real m_desiredDeltaVelocity;

            /**
             * Holds the world space position of the contact point relative to
             * centre of each body. This is set when the calculateInternals
             * function is run.
             */
            Vector3f m_relativeContactPosition[2];

        protected:
            /**
             * Calculates internal data from state data. This is called before
             * the resolution algorithm tries to do any resolution. It should
             * never need to be called manually.
             */
            void calculateInternals(real duration);

            /**
             * Reverses the contact. This involves swapping the two rigid bodies
             * and reversing the contact normal. The internal values should then
             * be recalculated using calculateInternals (this is not done
             * automatically).
             */
            void swapBodies();

            /**
             * Updates the awake state of rigid bodies that are taking
             * place in the given contact. A body will be made awake if it
             * is in contact with a body that is awake.
             */
            void matchAwakeState();

            /**
             * Calculates and sets the internal value for the desired delta
             * velocity.
             */
            void calculateDesiredDeltaVelocity(real duration);

            /**
             * Calculates and returns the velocity of the contact
             * point on the given body.
             */
            Vector3f calculateLocalVelocity(unsigned bodyIndex, real duration);

            /**
             * Calculates an orthonormal basis for the contact point, based on
             * the primary friction direction (for anisotropic friction) or
             * a random orientation (for isotropic friction).
             */
            void calculateContactBasis();

            /**
             * Applies an impulse to the given body, returning the
             * change in velocities.
             */
            void applyImpulse(const Vector3f &impulse, CRigidBody *body,
                              Vector3f *velocityChange, Vector3f *rotationChange);

            /**
             * Performs an inertia-weighted impulse based resolution of this
             * contact alone.
             */
            void applyVelocityChange(Vector3f velocityChange[2],
                                     Vector3f rotationChange[2]);

            /**
             * Performs an inertia weighted penetration resolution of this
             * contact alone.
             */
            void applyPositionChange(Vector3f linearChange[2],
                                     Vector3f angularChange[2],
                                     real penetration);

            /**
             * Calculates the impulse needed to resolve this contact,
             * given that the contact has no friction. A pair of inertia
             * tensors - one for each contact object - is specified to
             * save calculation time: the calling function has access to
             * these anyway.
             */
            Vector3f calculateFrictionlessImpulse(Matrix3f *inverseInertiaTensor);

            /**
             * Calculates the impulse needed to resolve this contact,
             * given that the contact has a non-zero coefficient of
             * friction. A pair of inertia tensors - one for each contact
             * object - is specified to save calculation time: the calling
             * function has access to these anyway.
             */
            Vector3f calculateFrictionImpulse(Matrix3f *inverseInertiaTensor);
        };

    } // namespace physics
} // namespace fg

    #undef FG_INC_PHYSICS_CONTACT_BLOCK
#endif /* FG_INC_PHYSICS_CONTACT */
