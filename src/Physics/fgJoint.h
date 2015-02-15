/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/*
 * Interface file for joints between rigid bodies.
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
 * This file contains the definitions for joints that link together
 * different rigid bodies.
 */
#ifndef FG_INC_PHYSICS_JOINT
    #define FG_INC_PHYSICS_JOINT
    #define FG_INC_PHYSICS_JOINT_BLOCK

    #include "fgContact.h"
    #include "fgContactGenerator.h"

namespace fg {
    namespace physics {

        /**
         * Joints link together two rigid bodies and make sure they do not
         * separate.  In a general physics engine there may be many
         * different types of joint, that reduce the number of relative
         * degrees of freedom between two objects. This joint is a common
         * position joint: each object has a location (given in
         * body-coordinates) that will be kept at the same point in the
         * simulation.
         */
        class CJoint : public CContactGenerator {
        public:
            /**
             * Holds the two rigid bodies that are connected by this joint.
             */
            CRigidBody* body[2];

            /**
             * Holds the relative location of the connection for each
             * body, given in local coordinates.
             */
            Vector3f position[2];

            /**
             * Holds the maximum displacement at the joint before the
             * joint is considered to be violated. This is normally a
             * small, epsilon value.  It can be larger, however, in which
             * case the joint will behave as if an inelastic cable joined
             * the bodies at their joint locations.
             */
            real error;

            /**
             * Configures the joint in one go.
             */
            void set(CRigidBody *a, const Vector3f& a_pos,
                     CRigidBody *b, const Vector3f& b_pos,
                     real error);

            /**
             * Generates the contacts required to restore the joint if it
             * has been violated.
             */
            unsigned addContact(CContact *contact, unsigned limit) const;
        };

    } // namespace physics
} // namespace fg

    #undef FG_INC_PHYSICS_JOINT_BLOCK
#endif /* FG_INC_PHYSICS_JOINT */
