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
 * File:   fgPhysicalWorld.h
 * Author: vigilant
 *
 * Created on September 24, 2015, 12:15 PM
 */

#ifndef FG_INC_PHYSICS_PHYSICAL_WORLD
    #define FG_INC_PHYSICS_PHYSICAL_WORLD
    #define FG_INC_PHYSICS_PHYSICAL_WORLD_BLOCK

    #include "fgBuildConfig.h"
    #if defined(FG_USING_BULLET)
        #include "fgBulletMaskTypes.h"
        #include "LinearMath/btAlignedObjectArray.h"
    #endif /* FG_USING_BULLET */

    #include "fgBool.h"
    #include "fgVector.h"
    #include "Physics/fgCollisionBody.h"

namespace fg {
    namespace physics {

        /**
         * 
         */
        class CPhysicalWorld {
        public:
            typedef CPhysicalWorld self_type;
            typedef CPhysicalWorld type;
            typedef CVector<CCollisionBody*> CollisionBodiesVec;
            typedef CollisionBodiesVec::iterator CollisionBodiesVecItor;

        public:
            /**
             *
             */
            CPhysicalWorld();
            /**
             *
             * @param orig
             */
            CPhysicalWorld(const self_type& orig);
            /**
             *
             */
            virtual ~CPhysicalWorld();

        protected:
    #if defined(FG_USING_BULLET)
            btDiscreteDynamicsWorld* getDynamicsWorld(void) const {
                return m_dynamicsWorld;
            }
    #else
            void* getDynamicsWorld(void) const {
                return NULL;
            }
    #endif /* FG_USING_BULLET */


        public:
            /**
             *
             */
            virtual fgBool initialize(void);
            /**
             *
             * @param delta
             */
            virtual fgBool destroy(void);
            /**
             *
             * @param delta
             */
            virtual void update(float delta = 0.0f);

            //------------------------------------------------------------------
        public:
            /**
             *
             * @param pBody
             */
            void setupOwnerFor(CAbstractCollisionBody* pBody);
            /**
             *
             * @param pBody
             * @return
             */
            int add(CCollisionBody* pBody);
            /**
             *
             * @param pBody
             * @return
             */
            fgBool remove(CCollisionBody* pBody);
            /**
             *
             * @return
             */
            fgBool removeAllCollisionBodies(void);
            /**
             * 
             * @return 
             */
            unsigned int getCollisionBodiesCount(void) const {
                return (unsigned int)m_collisionBodies.size();
            }
            /**
             *
             * @param index
             * @return
             */
            CCollisionBody* at(unsigned int index) {
                return m_collisionBodies.at((int)index);
            }
            /**
             * 
             * @param index
             * @return
             */
            CCollisionBody const* at(unsigned int index) const {
                return m_collisionBodies.at((int)index);
            }

        private:
            ///
            CollisionBodiesVec m_collisionBodies;
    #if defined(FG_USING_BULLET)
            ///
            btDefaultCollisionConfiguration* m_collisionConfig;
            ///
            btDiscreteDynamicsWorld* m_dynamicsWorld;
            ///
            btBroadphaseInterface* m_broadphase;
            ///
            btCollisionDispatcher* m_dispatcher;
            ///
            btConstraintSolver* m_solver;
    #endif
            ///
            fgBool m_init;
        }; // class CPhysicalWorld

    } // namespace physics
} // namespace fg


    #undef FG_INC_PHYSICS_PHYSICAL_WORLD_BLOCK
#endif /* FG_INC_PHYSICS_PHYSICAL_WORLD */
