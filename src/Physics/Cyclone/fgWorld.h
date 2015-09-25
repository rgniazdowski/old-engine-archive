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
 * Interface file for the rigid body world structure.
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
 * This file contains the definitions for a structure to hold any
 * number of rigid bodies, and to manage their simulation.
 */
#ifndef FG_INC_PHYSICS_WORLD
    #define FG_INC_PHYSICS_WORLD
    #define FG_INC_PHYSICS_WORLD_BLOCK

    #include "fgBuildConfig.h"
        #if !defined(FG_USING_BULLET)

    #include "Physics/Cyclone/fgRigidBody.h"
    #include "Physics/Cyclone/fgContact.h"
    #include "Physics/Cyclone/fgContactGenerator.h"
    #include "Physics/Cyclone/fgContactResolver.h"
    #include "Physics/Cyclone/fgCollisionFine.h"

namespace fg {
    namespace physics {

        const unsigned int DEFAULT_MAX_CONTACTS = 256;
        const unsigned int DEFAULT_MAX_ITERATIONS = 512;
        
        /**
         * The world represents an independent simulation of physics.  It
         * keeps track of a set of rigid bodies, and provides the means to
         * update them all. #FIXME
         */
        class CWorld {
        public:
            /**
             * Creates a new simulator that can handle up to the given
             * number of contacts per frame. You can also optionally give
             * a number of contact-resolution iterations to use. If you
             * don't give a number of iterations, then four times the
             * number of detected contacts will be used for each frame. 
             * #FIXME
             * 
             * FG UPDATE: This will work as some kind of helper class
             * There is no need to register Rigid/CollisionBody objects with 
             * this class - coarse/fine collision detection and update,
             * integration of the objects will be inside the scene manager.
             * 
             * This may change in time...
             */
            CWorld(unsigned maxContacts, unsigned iterations = 0);
            /**
             * 
             */
            virtual ~CWorld();
    #if 0
            /**
             * Calls each of the registered contact generators to report
             * their contacts. Returns the number of generated contacts.
             */
            unsigned generateContacts(void);

            /**
             * Processes all the physics for the world.
             */
            void runPhysics(real duration);

            /**
             * Initializes the world for a simulation frame. This clears
             * the force and torque accumulators for bodies in the
             * world. After calling this, the bodies can have their forces
             * and torques for this frame added.
             */
            void startFrame(void);
    #endif
        public:            
            /**
             * 
             */
            void startFrame(void);
            /**
             * 
             */
            void finishFrame(void);
            
        public:
            /**
             * 
             * @param maxContacts
             */
            void setMaxContacts(unsigned int maxContacts = DEFAULT_MAX_CONTACTS);
            /**
             * 
             * @return 
             */
            unsigned int getMaxContacts(void) const {
                return m_maxContacts;
            }
            
            /**
             * 
             * @param maxIterations
             */
            void setMaxIterations(unsigned int maxIterations = DEFAULT_MAX_ITERATIONS) {
                m_maxIterations = maxIterations;
            }
            /**
             * 
             * @return 
             */
            unsigned int getMaxIterations(void) const {
                return m_maxIterations;
            }
            
            /**
             * 
             * @param offset
             */
            void setGroundPlane(float offset);
            /**
             * 
             * @param active
             */
            inline void setGroundPlane(fgBool toggle = FG_TRUE) {
                m_useGroundPlane = toggle;
            }
            
            /**
             * 
             * @return 
             */
            fgBool isGroundPlane(void) const {
                return m_useGroundPlane;
            }
            
            /**
             * 
             * @return 
             */
            inline CCollisionPlane& getGroundPlane(void) {
                return m_groundPlane;
            }
            /**
             * 
             * @return 
             */
            inline CCollisionPlane const& getGroundPlane(void) const {
                return m_groundPlane;
            }
            
            /**
             * 
             * @return 
             */
            inline CContactResolver& getContactResolver(void) {
                return m_resolver;
            }
            /**
             * 
             * @return 
             */
            inline CContactResolver const& getContactResolver(void) const {
                return m_resolver;
            }
            
            /**
             * 
             * @return 
             */
            inline SCollisionData& getCollisionData(void) {
                return m_collisionData;
            }
            /**
             * 
             * @return 
             */
            inline SCollisionData const& getCollisionData(void) const {
                return m_collisionData;
            }
            
            /**
             * 
             * @return 
             */
            inline CContact* getContacts(void) const {
                return m_contacts;
            }
            
            /**
             * 
             * @return 
             */
            inline fgBool hasMoreContacts(void) const {
                return m_collisionData.hasMoreContacts();
            }
            
        private:
            /**
             * True if the world should calculate the number of iterations
             * to give the contact resolver at each frame.
             */
            fgBool m_isCalculateIterations;
    #if 0

            /**
             * Holds a single rigid body in a linked list of bodies.
             */
            struct SBodyRegistration {
                CRigidBody *body;
                SBodyRegistration * next;
            };

            /**
             * Holds the head of the list of registered bodies.
             */
            SBodyRegistration *m_firstBody;
    #endif
            /**
             * Holds the resolver for sets of contacts.
             */
            CContactResolver m_resolver;
    #if 0

            /**
             * Holds one contact generators in a linked list.
             */
            struct SContactGenRegistration {
                CContactGenerator *gen;
                SContactGenRegistration *next;
            };

            /**
             * Holds the head of the list of contact generators.
             */
            SContactGenRegistration *m_firstContactGen;
    #endif
            /**
             *
             */
            SCollisionData m_collisionData;
            /**
             *
             */
            CCollisionPlane m_groundPlane;
            
            /**
             *
             */
            fgBool m_useGroundPlane;

            /**
             * Holds an array of contacts, for filling by the contact
             * generators.
             */
            CContact *m_contacts;

            /**
             * Holds the maximum number of contacts allowed (i.e. the size
             * of the contacts array).
             */
            unsigned int m_maxContacts;
            
            /**
             *
             */
            unsigned int m_maxIterations;
        };

    } // namespace physics
} // namespace fg
#endif /* FG_USING_BULLET */
    #undef FG_INC_PHYSICS_WORLD_BLOCK
#endif /* FG_INC_PHYSICS_WORLD */
