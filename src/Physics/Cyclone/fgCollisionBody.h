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
 * Interface file for the collision body class.
 *
 * Copyright (c) Icosagon 2003. All Rights Reserved.
 *
 * This software is distributed under license. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software license.
 */
/* 
 * File:   fgCollisionBody.h
 * Author: vigilant
 *
 * Created on February 7, 2015, 1:31 PM
 */

#ifndef FG_INC_COLLISION_BODY
    #define FG_INC_COLLISION_BODY
    #define FG_INC_COLLISION_BODY_BLOCK
    #include "fgBuildConfig.h"
    #if !defined(FG_USING_BULLET) && defined(FG_USING_CYCLONE)
        #include "fgRigidBody.h"
        #include "fgCollisionFine.h"
        #include "fgBool.h"

namespace fg {

    namespace physics {

        const real DEFAULT_LINEAR_DAMPING = 0.95f;
        const real DEFAULT_ANGULAR_DAMPING = 0.8f;

        /**
         *
         */
        class CCollisionBody : public CRigidBody {
            ///
            typedef CRigidBody base_type;
            ///
            typedef CCollisionBody self_type;
            ///
            typedef CCollisionBody type;

        public:

            /**
             *
             */
            enum BodyType {
                ///
                INVALID,
                ///
                BOX,
                ///
                SPHERE,
                ///
                CAPSULE,
                ///
                COMPLEX,
                ///
                TRIANGLE_MESH
            };
        public:
            /**
             * 
             */
            CCollisionBody(const BodyType bodyType = BOX);
            /**
             * 
             * @param orig
             */
            CCollisionBody(const CCollisionBody& orig);
            /**
             * 
             */
            virtual ~CCollisionBody();

        public:
            /**
             * 
             * @param duration
             */
            virtual void integrate(real duration) {
                CRigidBody::integrate(duration);
                if(m_collisionShape) {
                    m_collisionShape->calculateInternals();
                }
            }
            /**
             * 
             */
            virtual void calculateDerivedData(void) {
                CRigidBody::calculateDerivedData();
                if(m_collisionShape) {
                    m_collisionShape->calculateInternals();
                }
            }

        public:
            using base_type::setInertiaTensor;

            /**
             * 
             */
            void setInertiaTensor(void);

            /**
             * 
             * @param halfSize
             * @param mass
             */
            void setInertiaTensor(const Vector3f& halfSize, float mass);

            /**
             * 
             * @param halfSize
             * @param mass
             */
            void setInertiaTensor(float radius, float mass);
            /**
             * 
             * @param halfSize
             * @param mass
             */
            inline void setHalfSizeAndMass(const Vector3f& halfSize, float mass) {
                setInertiaTensor(halfSize, mass);
            }

            /**
             * 
             * @param mass
             */
            void setMassPerUnit(float mass);
            /**
             * 
             * @param halfSize
             */
            void setHalfSize(const Vector3f& halfSize);
            /**
             * 
             * @return 
             */
            Vector3f getHalfSize(void) const;
            /**
             * 
             * @param radius
             */
            void setRadius(real radius);

            /**
             * 
             * @param bodyType
             */
            float getRadius(void) const;
            /**
             * 
             * @param gravity
             */
            void setGravity(real gravity) {
                this->acceleration.y = gravity;
            }

        public:
            /**
             * 
             * @param bodyType
             */
            void setBodyType(const BodyType bodyType);
            /**
             * 
             * @return 
             */
            BodyType getBodyType(void) const {
                return m_bodyType;
            }
            /**
             * 
             * @return 
             */
            CCollisionPrimitive *getCollisionPrimitive(void) const {
                return m_collisionShape;
            }
            /**
             * 
             * @return 
             */
            CCollisionBox *getCollisionBox(void) const {
                if(m_bodyType == BOX) {
                    return static_cast<CCollisionBox *>(m_collisionShape);
                } else {
                    return NULL;
                }
            }
            /**
             * 
             * @return 
             */
            CCollisionSphere *getCollisionSphere(void) const {
                if(m_bodyType == SPHERE) {
                    return static_cast<CCollisionSphere *>(m_collisionShape);
                } else {
                    return NULL;
                }
            }

        public:
            /**
             * 
             * @param body
             * @param cData
             * @return 
             */
            fgBool checkCollision(CCollisionBody *body, SCollisionData *cData);
            /**
             * 
             * @param plane
             * @param cData
             * @return 
             */
            fgBool checkCollision(const CCollisionPlane& plane, SCollisionData *cData);

        private:
            ///
            CCollisionPrimitive *m_collisionShape;
            ///
            BodyType m_bodyType;

        };

    } // namespace physics
} // namespace fg

    #endif /* FG_USING_BULLET */

    #undef FG_INC_COLLISION_BODY_BLOCK
#endif	/* FG_INC_COLLISION_BODY */
