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
    #include "fgAbstractCollisionBody.h"
    #include "fgBool.h"

    #if defined(FG_USING_BULLET)
        #include "Math/fgMathLib.h"
        #include "Math/fgDualQuaternion.h"
        #include "BulletDynamics/Dynamics/btRigidBody.h"
        #include "BulletCollision/CollisionShapes/btCollisionShape.h"

class btDynamicsWorld;

namespace fg {

    namespace physics {
        class CPhysicalWorld;
        namespace traits {
            class CPhysical;
        } // namespace traits

        const float DEFAULT_LINEAR_DAMPING = 0.95f;
        const float DEFAULT_ANGULAR_DAMPING = 0.8f;

        /**
         *
         */
        class CCollisionBody : public CAbstractCollisionBody, public CRigidBody {
            friend class traits::CPhysical;
            friend class CPhysicalWorld;
        public:
            ///
            typedef CAbstractCollisionBody base_type;
            ///
            typedef CRigidBody rigid_body;
            ///
            typedef CCollisionBody self_type;
            ///
            typedef CCollisionBody type;

        public:
            /**
             *
             */
            CCollisionBody(const BodyType bodyType = BODY_BOX);
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
            static self_type* upcast(base_type* pBase) {
                if(!pBase)
                    return NULL;
                const BodyType bodyType = pBase->getBodyType();
                if(bodyType != BODY_INVALID &&
                        bodyType != BODY_COMPLEX &&
                        bodyType != BODY_RAGDOLL) {
                    return static_cast<self_type*>(pBase);
                }
                return NULL;
            }
            static self_type const* upcast(base_type const* pBase) {
                if(!pBase)
                    return NULL;
                const BodyType bodyType = pBase->getBodyType();
                if(bodyType != BODY_INVALID &&
                        bodyType != BODY_COMPLEX &&
                        bodyType != BODY_RAGDOLL) {
                    return static_cast<self_type const*>(pBase);
                }
                return NULL;
            }

        public:

            virtual CCollisionBox* getCollisionBox(void) const;
            virtual CCollisionSphere* getCollisionSphere(void) const;
            virtual CCollisionCapsule* getCollisionCapsule(void) const;
            //CCollisionComplex* getCollisionComplex(void) const;
            virtual CCollisionTriangleMesh* getCollisionTriangleMesh(void) const;
            virtual CRigidBody* getRigidBody(void);
            virtual CRigidBody const* getRigidBody(void) const;
            virtual fgBool hasCollisionShape(void) const {
                return (fgBool)(getCollisionShape() != NULL);
            }
            virtual fgBool hasRigidBody(void) const {
                return FG_TRUE;
            }
            virtual fgBool hasRigidBodies(void) const {
                // this collision body has only one rigid body (self)
                // so return false
                return FG_FALSE;
            }
            virtual fgBool isBodyTypeCompatible(const BodyType bodyType) const {
                return (fgBool)(bodyType != BODY_INVALID &&
                        bodyType != BODY_COMPLEX &&
                        bodyType != BODY_RAGDOLL);
            }

        public:
            using base_type::setHalfSize;
            virtual void setHalfSize(const Vector3f& halfExtent);
            virtual void setRadius(const float radius);
            virtual void setHeight(const float height);
            virtual void setMass(float mass);

            void setMassProps(btScalar mass, const btVector3& inertia);

            using base_type::setLocalScaling;
            virtual void setLocalScaling(const Vector3f& scale);

        public:
            // // //void setAcceleration(const Vector3f& acceleration);

            //------------------------------------------------------------------
            using rigid_body::setAngularVelocity;
            void setAngularVelocity(const Vector3f& velocity);
            void setAngularVelocity(float x, float y = 0.0f, float z = 0.0f);

            //------------------------------------------------------------------
            using rigid_body::getAngularVelocity;
            void getAngularVelocity(Vector3f& outVelocity) const;
            void getAngularVelocity(float& x, float& y, float& z) const;

            //------------------------------------------------------------------
            using rigid_body::setLinearVelocity;
            void setLinearVelocity(const Vector3f& velocity);
            void setVelocity(const Vector3f& velocity);
            void setVelocity(float x, float y = 0.0f, float z = 0.0f);

            //------------------------------------------------------------------
            using rigid_body::getLinearVelocity;
            const Vector3f& getVelocity(void) const;
            void getVelocity(Vector3f& outVelocity) const;
            void getVelocity(float& x, float& y, float& z) const;

            void setRotation(const Quaternionf& rotation);
            void setRotation(float angle, const Vector3f& axis);
            void setRotation(float angle, float x, float y, float z);

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
            using rigid_body::translate;
            void translate(const Vector3f& translation);
            void translate(float x, float y, float z);

            //------------------------------------------------------------------
            const Matrix4f& getWorldMatrix(void) const;

            using rigid_body::getWorldTransform;
            void getWorldTransform(DualQuaternionf& outDQ) const;
            void getWorldTransform(Matrix4f& outMatrix) const;
            void getWorldTransform(float *outMatrix) const;

            using rigid_body::setWorldTransform;
            void setWorldTransform(const Matrix4f& matrix);
            void setWorldTransform(const DualQuaternionf& dq);
            void setWorldTransform(float* matrix);

            //------------------------------------------------------------------
        protected:
            virtual void setupBody(BodyType bodyType);

        private:
            ///
            float m_mass;
            ///
            btMotionState* m_motionState;
        }; // class CCollisionBody

    } // namespace physics
} // namespace fg
    #endif /* FG_USING_BULLET */

//------------------------------------------------------------------------------

    #if !defined(FG_USING_BULLET) && !defined(FG_USING_CYCLONE)
namespace fg {
    namespace physics {
        class CPhysicalWorld;
        namespace traits {
            class CPhysical;
        } // namespace traits

        const float DEFAULT_LINEAR_DAMPING = 0.95f;
        const float DEFAULT_ANGULAR_DAMPING = 0.8f;

        /**
         *
         */
        class CCollisionBody : public CAbstractCollisionBody, public CRigidBody {
            friend class traits::CPhysical;
            friend class CPhysicalWorld;
        public:
            ///
            typedef CAbstractCollisionBody base_type;
            ///
            typedef CRigidBody rigid_body;
            ///
            typedef CCollisionBody self_type;
            ///
            typedef CCollisionBody type;

        public:
            /**
             *
             */
            CCollisionBody(const BodyType bodyType = BODY_INVALID) : base_type(BODY_INVALID) { }
            /**
             *
             * @param orig
             */
            CCollisionBody(const self_type& orig) : base_type(orig.getBodyType()) { }
            /**
             *
             */
            virtual ~CCollisionBody() { }

        public:
            static self_type* upcast(base_type* pBase) {
                return NULL;
            }
            static self_type const* upcast(base_type const* pBase) {
                return NULL;
            }

        public:
            virtual CCollisionBox* getCollisionBox(void) const {
                return NULL;
            }
            virtual CCollisionSphere* getCollisionSphere(void) const {
                return NULL;
            }
            virtual CCollisionCapsule* getCollisionCapsule(void) const {
                return NULL;
            }
            //CCollisionComplex* getCollisionComplex(void) const { return NULL; }
            virtual CCollisionTriangleMesh* getCollisionTriangleMesh(void) const {
                return NULL;
            }
            virtual CRigidBody* getRigidBody(void) {
                return NULL;
            }
            virtual CRigidBody const* getRigidBody(void) const {
                return NULL;
            }
            virtual fgBool hasCollisionShape(void) const {
                return FG_FALSE;
            }
            virtual fgBool hasRigidBody(void) const {
                return FG_TRUE;
            }
            virtual fgBool hasRigidBodies(void) const {
                return FG_FALSE;
            }
            virtual fgBool isBodyTypeCompatible(const BodyType bodyType) const {
                return FG_FALSE;
            }

        public:
            using base_type::setHalfSize;
            virtual void setHalfSize(const Vector3f& halfExtent) { }
            virtual void setRadius(const float radius) { }
            virtual void setHeight(const float height) { }
            virtual void setMass(float mass) { }
            void setMassProps(float mass, const Vector3f& inertia) { }

            using base_type::setLocalScaling;
            virtual void setLocalScaling(const Vector3f& scale) { }

        public:

            //------------------------------------------------------------------
            //using rigid_body::setAngularVelocity;
            void setAngularVelocity(const Vector3f& velocity) { }
            void setAngularVelocity(float x, float y = 0.0f, float z = 0.0f) { }

            //------------------------------------------------------------------
            //using rigid_body::getAngularVelocity;
            void getAngularVelocity(Vector3f& outVelocity) const { }
            void getAngularVelocity(float& x, float& y, float& z) const { }

            //------------------------------------------------------------------
            //using rigid_body::setLinearVelocity;
            void setLinearVelocity(const Vector3f& velocity) { }
            void setVelocity(const Vector3f& velocity) { }
            void setVelocity(float x, float y = 0.0f, float z = 0.0f) { }

            //------------------------------------------------------------------
            //using rigid_body::getLinearVelocity;
            const Vector3f& getVelocity(void) const {
                static Vector3f velocity;
                velocity = Vec3f();
                return velocity;
            }
            void getVelocity(Vector3f& outVelocity) const { }
            void getVelocity(float& x, float& y, float& z) const { }
            void setRotation(const Quaternionf& rotation) { }
            void setRotation(float angle, const Vector3f& axis) { }
            void setRotation(float angle, float x, float y, float z) { }

            //------------------------------------------------------------------
            const Quaternionf& getRotation(void) const {
                static Quaternionf quat;
                quat = Quatf();
                return quat;
            }
            void getRotation(Matrix3f& outMatrix) const { }
            void getRotation(Quaternionf& outRotation) const { }
            void getRotation(Vector3f& outRotation) const { }
            void getRotation(float& x, float& y, float& z) const { }

            //------------------------------------------------------------------
            void setPosition(const Vector3f& position) { }
            void setPosition(float x, float y, float z) { }

            //------------------------------------------------------------------
            //const Vector3f& getPosition(void) const;
            void getPosition(Vector3f& outPosition) const { }
            void getPosition(float& x, float& y, float& z) const { }

            //------------------------------------------------------------------
            //using rigid_body::translate;
            void translate(const Vector3f& translation) { }
            void translate(float x, float y, float z) { }

            //------------------------------------------------------------------
            const Matrix4f& getWorldMatrix(void) const {
                static Matrix4f matrix;
                matrix = Matrix4f();
                return matrix;
            }

            //using rigid_body::getWorldTransform;
            void getWorldTransform(DualQuaternionf& outDQ) const { }
            void getWorldTransform(Matrix4f& outMatrix) const { }
            void getWorldTransform(float *outMatrix) const { }

            //using rigid_body::setWorldTransform;
            void setWorldTransform(const Matrix4f& matrix) { }
            void setWorldTransform(const DualQuaternionf& dq) { }
            void setWorldTransform(float* matrix) { }
            //------------------------------------------------------------------

            fgBool isActive(void) const {
                return FG_FALSE;
            }

            fgBool isStaticObject(void) const {
                return FG_TRUE;
            }
        protected:
            virtual void setupBody(BodyType bodyType) { }
        }; // class CCollisionBody

    } // namespace physics
} // namespace fg
    #endif /* not using Bullet && not using Cyclone */

    #undef FG_INC_COLLISION_BODY_BLOCK
#endif	/* FG_INC_COLLISION_BODY */
