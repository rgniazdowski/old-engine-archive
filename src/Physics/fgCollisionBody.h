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
 * File:   fgCollisionBody.h
 * Author: vigilant
 *
 * Created on September 24, 2015, 12:16 PM
 */

#ifndef FG_INC_COLLISION_BODY
    #define FG_INC_COLLISION_BODY
    #define FG_INC_COLLISION_BODY_BLOCK

    #include "fgBulletMaskTypes.h"
    #include "fgBool.h"
    #if defined(FG_USING_BULLET)
        #include "Math/fgMathLib.h"
        #include "Math/fgDualQuaternion.h"
        #include "BulletDynamics/Dynamics/btRigidBody.h"
        #include "BulletCollision/CollisionShapes/btCollisionShape.h"

namespace fg {

    namespace physics {

        namespace traits {
            class CPhysical;
        } // namespace traits

        const float DEFAULT_LINEAR_DAMPING = 0.95f;
        const float DEFAULT_ANGULAR_DAMPING = 0.8f;

        /**
         *
         */
        class CCollisionBody : public CRigidBody {
            friend class traits::CPhysical;
        public:
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
            }; // enum BodyType

        public:
            /**
             *
             */
            CCollisionBody(const BodyType bodyType = BOX);
            /**
             *
             * @param orig
             */
            CCollisionBody(const self_type& orig);
            /**
             *
             */
            virtual ~CCollisionBody();

        public:
            BodyType getBodyType(void) const {
                return m_bodyType;
            }
            CCollisionBox* getCollisionBox(void) const;
            CCollisionSphere* getCollisionSphere(void) const;
            CCollisionCapsule* getCollisionCapsule(void) const;
            //CCollisionComplex* getCollisionComplex(void) const;
            CCollisionTriangleMesh* getCollisionTriangleMesh(void) const;
            CRigidBody* getRigidBody(void);
            CRigidBody const* getRigidBody(void) const;

        public:
            void setHalfSize(const Vector3f& halfExtent);
            void setHalfSizeAndMass(const Vector3f& halfExtent, float mass);
            void setRadius(const float radius);
            void setMass(float mass);

        public:
            void setAcceleration(const Vector3f& acceleration);

            //------------------------------------------------------------------
            using base_type::setAngularVelocity;
            void setAngularVelocity(const Vector3f& velocity);
            void setAngularVelocity(float x, float y = 0.0f, float z = 0.0f);

            //------------------------------------------------------------------
            using base_type::getAngularVelocity;
            void getAngularVelocity(Vector3f& outVelocity) const;
            void getAngularVelocity(float& x, float& y, float& z) const;

            //------------------------------------------------------------------
            using base_type::setLinearVelocity;
            void setLinearVelocity(const Vector3f& velocity);
            void setVelocity(const Vector3f& velocity);
            void setVelocity(float x, float y = 0.0f, float z = 0.0f);

            //------------------------------------------------------------------
            using base_type::getLinearVelocity;
            const Vector3f& getVelocity(void) const;
            void getVelocity(Vector3f& outVelocity) const;
            void getVelocity(float& x, float& y, float& z) const;

            //------------------------------------------------------------------
            const Quaternionf& getRotation(void) const;
            void getRotation(Matrix3f& outMatrix) const;
            void getRotation(Quaternionf& outRotation) const;
            void getRotation(Vector3f& outRotation) const;
            void getRotation(float& x, float& y, float& z) const;

            //------------------------------------------------------------------
            void setPosition(const Vector3f& position);
            void setPosition(float x, float y, float z);

            //------------------------------------------------------------------
            const Vector3f& getPosition(void) const;
            void getPosition(Vector3f& outPosition) const;
            void getPosition(float& x, float& y, float& z) const;

            //------------------------------------------------------------------
            using base_type::translate;
            void translate(const Vector3f& translation);
            void translate(float x, float y, float z);

            //------------------------------------------------------------------
            const Matrix4f& getWorldMatrix(void) const;

            using base_type::getWorldTransform;
            void getWorldTransform(DualQuaternionf& outDQ) const;
            void getWorldTransform(Matrix4f& outMatrix) const;
            void getWorldTransform(float *outMatrix) const;

            using base_type::setWorldTransform;
            void setWorldTransform(const Matrix4f& matrix);
            void setWorldTransform(const DualQuaternionf& dq);
            void setWorldTransform(float* matrix);

            //------------------------------------------------------------------
        protected:
            void setupBody(BodyType bodyType);

        private:
            ///
            BodyType m_bodyType;
            ///
            btMotionState* m_motionState;
        }; // class CCollisionBody

    } // namespace physics
} // namespace fg

    #endif /* FG_USING_BULLET */
    #undef FG_INC_COLLISION_BODY_BLOCK
#endif	/* FG_INC_COLLISION_BODY */
