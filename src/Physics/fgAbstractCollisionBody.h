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
 * File:   fgAbstractCollisionBody.h
 * Author: vigilant
 *
 * Created on October 10, 2015, 12:29 AM
 */

#ifndef FG_INC_ABSTRACT_COLLISION_BODY
    #define FG_INC_ABSTRACT_COLLISION_BODY
    #define FG_INC_ABSTRACT_COLLISION_BODY_BLOCK

    #include "fgBulletMaskTypes.h"
    #include "fgVector.h"
    #include "fgBool.h"
    #include "Math/fgMathLib.h"

namespace fg {
    namespace physics {

        /**
         *
         */
        enum BodyType {
            ///
            BODY_INVALID = 0,
            ///
            BODY_BOX = 1,
            ///
            BODY_SPHERE = 2,
            ///
            BODY_CAPSULE = 3,
            ///
            BODY_TRIANGLE_MESH = 4,
            /// Collision body is complex - build from many rigid bodies
            /// and collision shapes (with optional constraints)
            BODY_COMPLEX = 5,
            /// Special collision body type used for ragdolls
            BODY_RAGDOLL = 6,
        }; // enum BodyType

    } // namespace physics
} // namespace fg

    #if defined(FG_USING_BULLET)

class btDynamicsWorld;

    #endif /* FG_USING_BULLET */

namespace fg {
    namespace physics {
        class CPhysicalWorld;
        namespace traits {
            class CPhysical;
        } // namespace traits        

        class CRagdollCollisionBody;
        class CCollisionBody;

        /**
         *
         */
        class CAbstractCollisionBody {
            friend class traits::CPhysical;
            friend class CPhysicalWorld;
            friend class CRagdollCollisionBody;
        public:
            typedef CAbstractCollisionBody self_type;
            typedef CAbstractCollisionBody type;

            typedef CVector<CRigidBody *> RigidBodiesVec;
            typedef RigidBodiesVec::iterator RigidBodiesVecItor;
            typedef RigidBodiesVec::const_iterator RigidBodiesVecConstItor;

            typedef CVector<CCollisionPrimitive *> CollisionShapesVec;
            typedef CollisionShapesVec::iterator CollisionShapesVecItor;
            typedef CollisionShapesVec::const_iterator CollisionShapesVecConstItor;

        public:
            /**
             *
             */
            CAbstractCollisionBody(const BodyType bodyType);
            /**
             *
             * @param orig
             */
            CAbstractCollisionBody(const self_type& orig);
            /**
             *
             */
            virtual ~CAbstractCollisionBody();

        public:
            virtual CCollisionBox* getCollisionBox(void) const = 0;
            virtual CCollisionSphere* getCollisionSphere(void) const = 0;
            virtual CCollisionCapsule* getCollisionCapsule(void) const = 0;
            //CCollisionComplex* getCollisionComplex(void) const;
            virtual CCollisionTriangleMesh* getCollisionTriangleMesh(void) const = 0;
            virtual CRigidBody* getRigidBody(void) = 0;
            virtual CRigidBody const* getRigidBody(void) const = 0;

            virtual fgBool hasCollisionShape(void) const = 0;
            virtual fgBool hasRigidBody(void) const = 0;
            virtual fgBool hasRigidBodies(void) const = 0;

            virtual fgBool isBodyTypeCompatible(const BodyType bodyType) const = 0;

        public:
            inline fgBool isBox(void) const {
                return (fgBool)(m_bodyType == BODY_BOX);
            }
            inline fgBool isSphere(void) const {
                return (fgBool)(m_bodyType == BODY_SPHERE);
            }
            inline fgBool isCapsule(void) const {
                return (fgBool)(m_bodyType == BODY_CAPSULE);
            }
            inline fgBool isTriangleMesh(void) const {
                return (fgBool)(m_bodyType == BODY_TRIANGLE_MESH);
            }
            inline fgBool isComplex(void) const {
                return (fgBool)(m_bodyType == BODY_COMPLEX);
            }
            inline fgBool isRagdoll(void) const {
                return (fgBool)(m_bodyType == BODY_RAGDOLL);
            }

        public:
            virtual void setHalfSize(const Vector3f& halfExtent) = 0;
            inline void setHalfSize(float x, float y, float z) {
                setHalfSize(Vector3f(x, y, z));
            }
            inline void setHalfSizeAndMass(const Vector3f& halfExtent, float mass) {
                setHalfSize(halfExtent);
                setMass(mass);
            }
            inline void setHalfSizeAndMass(float x, float y, float z, float mass) {
                setHalfSize(Vector3f(x, y, z));
                setMass(mass);
            }
            virtual void setRadius(const float radius) = 0;
            virtual void setHeight(const float height) = 0;
            virtual void setMass(float mass) = 0;

            virtual void setLocalScaling(const Vector3f& scale) = 0;
            inline void setLocalScaling(float x, float y, float z) {
                setLocalScaling(Vector3f(x, y, z));
            }

        public:
            BodyType getBodyType(void) const {
                return m_bodyType;
            }

        protected:
            virtual void setupBody(BodyType bodyType) = 0;
    #if defined(FG_USING_BULLET)
            /**
             *
             * @return
             */
            btDynamicsWorld* getOwner(void) const {
                return m_pOwner;
            }
            /**
             *
             * @param pOwner
             */
            void setOwner(btDynamicsWorld* pOwner) {
                m_pOwner = pOwner;
            }
    #else
            void* getOwner(void) const {
                return m_pOwner;
            }
            void setOwner(void* pOwner) {
                m_pOwner = pOwner;
            }
    #endif

        protected:
            ///
            BodyType m_bodyType;
    #if defined(FG_USING_BULLET)
            ///
            btDynamicsWorld* m_pOwner;
    #else
            void* m_pOwner;
    #endif

        private:

        }; // class CAbstractCollisionBody

    } // namespace physics
} // namespace fg

    #undef FG_INC_ABSTRACT_COLLISION_BODY_BLOCK
#endif	/* FG_INC_ABSTRACT_COLLISION_BODY */
