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
 * File:   fgCollisionBody.cpp
 * Author: vigilant
 *
 * Created on September 24, 2015, 12:16 PM
 */

#include "Physics/fgCollisionBody.h"
#if defined(FG_USING_BULLET)
#include "BulletCollision/CollisionShapes/btSphereShape.h"
#include "BulletCollision/CollisionShapes/btBoxShape.h"
#include "BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h"
#include "BulletCollision/CollisionShapes/btCapsuleShape.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"
#include "LinearMath/btDefaultMotionState.h"
#include "fgBulletHelper.h"
#include "Math/fgDualQuaternion.h"
using namespace fg;
//------------------------------------------------------------------------------

physics::CCollisionBody::CCollisionBody(const BodyType bodyType) :
base_type(bodyType),
rigid_body(CRigidBody::btRigidBodyConstructionInfo(1.0f, NULL, NULL)),
m_mass(1.0),
m_motionState(NULL) {
    m_motionState = new btDefaultMotionState();
    this->setMotionState(m_motionState);
    if(bodyType != BODY_INVALID)
        setupBody(bodyType);
    //this->getMotionState()->getWorldTransform();
    //this->setGravity(btVector3(0.0f, -0.8f, 0.0f));
    //this->setLinearVelocity(Vector3f(1.0f, 0.0f, 2.0f));
    //this->setAngularVelocity(5.0f, 1.0f, 2.0f);
}
//------------------------------------------------------------------------------

physics::CCollisionBody::CCollisionBody(const self_type& orig) :
base_type(orig.getBodyType()),
rigid_body(orig) { }
//------------------------------------------------------------------------------

physics::CCollisionBox* physics::CCollisionBody::getCollisionBox(void) const {
    if(m_bodyType == BODY_BOX) {
        return static_cast<CCollisionBox*>(m_collisionShape);
    }
    return NULL;
}
//------------------------------------------------------------------------------

physics::CCollisionSphere* physics::CCollisionBody::getCollisionSphere(void) const {
    if(m_bodyType == BODY_SPHERE) {
        return static_cast<CCollisionSphere*>(m_collisionShape);
    }
    return NULL;
}
//------------------------------------------------------------------------------

physics::CCollisionCapsule* physics::CCollisionBody::getCollisionCapsule(void) const {
    if(m_bodyType == BODY_CAPSULE) {
        return static_cast<CCollisionCapsule*>(m_collisionShape);
    }
    return NULL;
}
//------------------------------------------------------------------------------

physics::CCollisionTriangleMesh* physics::CCollisionBody::getCollisionTriangleMesh(void) const {
    if(m_bodyType == BODY_TRIANGLE_MESH) {
        return static_cast<CCollisionTriangleMesh*>(m_collisionShape);
    }
    return NULL;
}
//------------------------------------------------------------------------------

physics::CRigidBody* physics::CCollisionBody::getRigidBody(void) {
    return static_cast<CRigidBody*>(this);
}
//------------------------------------------------------------------------------

physics::CRigidBody const* physics::CCollisionBody::getRigidBody(void) const {
    return static_cast<CRigidBody const*>(this);
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::setHalfSize(const Vector3f& halfExtent) {
    btVector3 bt_ext;
    bt_ext.setValue(halfExtent.x, halfExtent.y, halfExtent.z);
    if(m_bodyType == BODY_BOX) {
        getCollisionBox()->setImplicitShapeDimensions(bt_ext);
        //getCollisionBox()->setLocalScaling() // ?
    } else if(m_bodyType == BODY_SPHERE) {
        btVector3 localScaling = getCollisionSphere()->getLocalScaling();
        float newRadius = math::length(halfExtent) * localScaling.getX();
        getCollisionSphere()->setUnscaledRadius(newRadius);
        //getCollisionSphere()->setLocalScaling()
    } else if(m_bodyType == BODY_CAPSULE) {
        // tricky
        getCollisionCapsule()->setImplicitShapeDimensions(bt_ext);
    } else if(m_bodyType == BODY_TRIANGLE_MESH) {
        // ignore
    }
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::setRadius(const float radius) {
    float newRadius = math::abs(radius);
    if(m_bodyType == BODY_SPHERE) {
        btVector3 localScaling = getCollisionSphere()->getLocalScaling();
        newRadius *= localScaling.getX();
        getCollisionSphere()->setUnscaledRadius(newRadius);
    } else if(m_bodyType == BODY_BOX) {
        getCollisionBox()->setImplicitShapeDimensions(btVector3(newRadius, newRadius, newRadius));
    } else if(m_bodyType == BODY_CAPSULE) {
        // tricky
        CCollisionCapsule* pCapsule = getCollisionCapsule();
        const btVector3& dimensions = pCapsule->getImplicitShapeDimensions();
        int upAxis = pCapsule->getUpAxis();
        //float radius = pCapsule->getRadius();
        int radiusAxis = (upAxis + 2) % 3;
        //float radius = dimensions[radiusAxis]; // current radius
        // capsule true half size is radius + half height,
        // and complete height is radius*2 + half height*2
        btVector3 newDimensions = dimensions;
        newDimensions[radiusAxis] = newRadius;
        pCapsule->setImplicitShapeDimensions(newDimensions);
    } else if(m_bodyType == BODY_TRIANGLE_MESH) {
        // ignore
    }
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::setHeight(const float height) {
    float newHeight = math::abs(height);
    if(m_bodyType == BODY_SPHERE) {
        btVector3 localScaling = getCollisionSphere()->getLocalScaling();
        newHeight *= localScaling.getX();
        getCollisionSphere()->setUnscaledRadius(newHeight / 2.0f);
    } else if(m_bodyType == BODY_BOX) {
        const btVector3& dimensions = getCollisionBox()->getImplicitShapeDimensions();
        getCollisionBox()->setImplicitShapeDimensions(btVector3(dimensions.getX(),
                                                                newHeight,
                                                                dimensions.getZ()));
    } else if(m_bodyType == BODY_CAPSULE) {
        CCollisionCapsule* pCapsule = getCollisionCapsule();
        const btVector3& dimensions = pCapsule->getImplicitShapeDimensions();
        int upAxis = pCapsule->getUpAxis();
        //float radius = pCapsule->getRadius();
        //int radiusAxis = (upAxis + 2) % 3;
        //float radius = dimensions[radiusAxis]; // current radius
        // capsule true half size is radius + half height,
        // and complete height is radius*2 + half height*2
        btVector3 newDimensions = dimensions;
        newDimensions[upAxis] = newHeight / 2.0f;
        pCapsule->setImplicitShapeDimensions(newDimensions);
    } else if(m_bodyType == BODY_TRIANGLE_MESH) {

    }
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::setMass(float mass) {
    if(!getCollisionShape())
        return;
    btVector3 inertia;
    getCollisionShape()->calculateLocalInertia(mass, inertia);
    getRigidBody()->setMassProps(mass, inertia);
    getRigidBody()->updateInertiaTensor();
    m_mass = mass;
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::setMassProps(btScalar mass, const btVector3& inertia) {
    rigid_body::setMassProps(mass, inertia);
    m_mass = mass;
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::setLocalScaling(const Vector3f& scale) {
    if(!getCollisionShape())
        return;
    if(m_pOwner) {
        m_pOwner->getBroadphase()->
                getOverlappingPairCache()->
                cleanProxyFromPairs(this->getBroadphaseHandle(),
                                    m_pOwner->getDispatcher());
        m_pOwner->removeRigidBody(getRigidBody());
    }
    getCollisionShape()->setLocalScaling(btVector3(scale.x, scale.y, scale.z));
    // this for quick update of local inertia
    setMass(m_mass); // is this an overkill?
    if(m_pOwner) {
        m_pOwner->addRigidBody(getRigidBody());
    }
}
//------------------------------------------------------------------------------

//void physics::CCollisionBody::setAcceleration(const Vector3f& acceleration) {
// manipulate the gravity?
// #FIXME
//}
//------------------------------------------------------------------------------

void physics::CCollisionBody::setAngularVelocity(const Vector3f& velocity) {
    rigid_body::setAngularVelocity(btVector3(velocity.x, velocity.y, velocity.z));
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::setAngularVelocity(float x, float y, float z) {
    rigid_body::setAngularVelocity(btVector3(x, y, z));
}
//------------------------------------------------------------------

void physics::CCollisionBody::getAngularVelocity(Vector3f& outVelocity) const {
    const btVector3& a_vec = rigid_body::getAngularVelocity();
    outVelocity.x = a_vec.x();
    outVelocity.y = a_vec.y();
    outVelocity.z = a_vec.z();
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::getAngularVelocity(float& x, float& y, float& z) const {
    const btVector3& a_vec = rigid_body::getAngularVelocity();
    x = a_vec.x();
    y = a_vec.y();
    z = a_vec.z();
}
//------------------------------------------------------------------

void physics::CCollisionBody::setLinearVelocity(const Vector3f& velocity) {
    rigid_body::setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::setVelocity(const Vector3f& velocity) {
    rigid_body::setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::setVelocity(float x, float y, float z) {
    rigid_body::setLinearVelocity(btVector3(x, y, z));
}
//------------------------------------------------------------------

const Vector3f& physics::CCollisionBody::getVelocity(void) const {
    static Vector3f velocity = Vector3f();
    this->getVelocity(velocity);
    return velocity;
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::getVelocity(Vector3f& outVelocity) const {
    const btVector3& velocity = rigid_body::getLinearVelocity();
    outVelocity.x = velocity.x();
    outVelocity.y = velocity.y();
    outVelocity.z = velocity.z();
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::getVelocity(float& x, float& y, float& z) const {
    const btVector3& velocity = rigid_body::getLinearVelocity();
    x = velocity.x();
    y = velocity.y();
    z = velocity.z();
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::setRotation(const Quaternionf& rotation) {
    btTransform& trans = this->getWorldTransform();
    trans.getBasis().setRotation(*((btQuaternion*) & rotation));
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::setRotation(float angle, const Vector3f& axis) {
    btTransform& trans = this->getWorldTransform();
    Quaternionf rotation = math::rotate(Quaternionf(), angle, axis);
    // fast copy
    trans.getBasis().setRotation(*((btQuaternion*) & rotation));
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::setRotation(float angle, float x, float y, float z) {
    btTransform& trans = this->getWorldTransform();
    Quaternionf rotation = math::rotate(Quaternionf(), angle, Vec3f(x, y, z));
    // fast copy
    trans.setRotation(*((btQuaternion*) & rotation));
}
//------------------------------------------------------------------------------

const Quaternionf& physics::CCollisionBody::getRotation(void) const {
    static Quaternionf quat = Quaternionf();
    bullet_helper::copyQuat(quat, m_worldTransform.getRotation());
    return quat;
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::getRotation(Matrix3f& outMatrix) const {
    btTransform trans;
    this->getMotionState()->getWorldTransform(trans);
    bullet_helper::copyMatrix3x3(outMatrix, trans.getBasis());
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::getRotation(Quaternionf& outRotation) const {
    //btTransform trans;
    //btQuaternion q;
    //this->getWorldTransform(trans);
    this->getWorldTransform().getBasis().getRotation(*((btQuaternion*) & outRotation));
    //bullet_helper::copyQuat(outRotation, trans.getRotation());
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::getRotation(Vector3f& outRotation) const {
    getRotation(outRotation.x, outRotation.y, outRotation.z);
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::getRotation(float& x, float& y, float& z) const {
    // #FIXME
    // need to return all three angles in radians
}
//------------------------------------------------------------------

void physics::CCollisionBody::setPosition(const Vector3f& position) {
    m_worldTransform.getOrigin().setValue(position.x, position.y, position.z);
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::setPosition(float x, float y, float z) {
    m_worldTransform.getOrigin().setValue(x, y, z);
}

//------------------------------------------------------------------

const Vector3f& physics::CCollisionBody::getPosition(void) const {
    static Vector3f position = Vector3f();
    const btVector3& translation = m_worldTransform.getOrigin();
    position.x = translation.x();
    position.y = translation.y();
    position.z = translation.z();
    return position;
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::getPosition(Vector3f& outPosition) const {
    const btVector3& translation = m_worldTransform.getOrigin();
    outPosition.x = translation.x();
    outPosition.y = translation.y();
    outPosition.z = translation.z();
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::getPosition(float& x, float& y, float& z) const {
    const btVector3& translation = m_worldTransform.getOrigin();
    x = translation.x();
    y = translation.y();
    z = translation.z();
}
//------------------------------------------------------------------

void physics::CCollisionBody::translate(const Vector3f& translation) {
    m_worldTransform.getOrigin() += btVector3(translation.x,
                                              translation.y,
                                              translation.z);
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::translate(float x, float y, float z) {
    m_worldTransform.getOrigin() += btVector3(x, y, z);
}
//------------------------------------------------------------------

const Matrix4f& physics::CCollisionBody::getWorldMatrix(void) const {
    static Matrix4f matrix = Matrix4f();
    getWorldTransform(matrix);
    return matrix;
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::getWorldTransform(DualQuaternionf& outDQ) const {
    static Matrix4f matrix = Matrix4f();
    bullet_helper::copyMatrix4x4(matrix, m_worldTransform);
    outDQ.initializeFrom(matrix);
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::getWorldTransform(Matrix4f& outMatrix) const {
    bullet_helper::copyMatrix4x4(outMatrix, m_worldTransform);
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::getWorldTransform(float* outMatrix) const {
    m_worldTransform.getOpenGLMatrix(outMatrix);
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::setWorldTransform(const Matrix4f& matrix) {
    m_worldTransform.setFromOpenGLMatrix(&(matrix[0].x));
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::setWorldTransform(const DualQuaternionf& dq) {
    static Matrix4f matrix;
    dq.toMat4(matrix);
    m_worldTransform.setFromOpenGLMatrix(&(matrix[0].x));
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::setWorldTransform(float* matrix) {
    if(!matrix)
        return;
    m_worldTransform.setFromOpenGLMatrix((btScalar*)matrix);
}
//------------------------------------------------------------------------------

void physics::CCollisionBody::setupBody(BodyType bodyType) {
    if(m_bodyType == bodyType && this->getCollisionShape())
        return;
    float invMass = this->getInvMass();
    float mass = 0.0f;
    if(invMass != 0.0f)
        mass = 1.0f / invMass;
    btCollisionShape *pOriginalShape = this->getCollisionShape();
    if(pOriginalShape) {
        this->setCollisionShape(NULL);
        delete pOriginalShape;
        m_collisionShape = NULL;
    }
    m_bodyType = bodyType;
    fgBool isDynamic = (fgBool)(mass != 0.f);
    btVector3 localInertia(0, 0, 0);

    btCollisionShape* pNewShape = NULL;
    if(m_bodyType == BODY_BOX) {
        pNewShape = new CCollisionBox(btVector3(1.0f, 1.0f, 1.0f));
    } else if(m_bodyType == BODY_SPHERE) {
        pNewShape = new CCollisionSphere(1.0f);
    } else if(m_bodyType == BODY_CAPSULE) {
        // mostly for bones...
        pNewShape = new CCollisionCapsule(0.1f, 0.8f);
    } else if(m_bodyType == BODY_TRIANGLE_MESH) {
        //pNewShape = new CCollisionTriangleMesh();
    }

    if(isDynamic && pNewShape)
        pNewShape->calculateLocalInertia(mass, localInertia);
    if(pNewShape) {
        this->setCollisionShape(pNewShape);
        pNewShape->setMargin(0.01f);
        if(isDynamic) {
            this->setMassProps(mass, localInertia);
            this->updateInertiaTensor();
        }
    }
}
//------------------------------------------------------------------------------

physics::CCollisionBody::~CCollisionBody() {
    if(m_pOwner) {
        // ?
        //m_pOwner->removeRigidBody(getRigidBody());
    }
    m_pOwner = NULL;
    if(this->getMotionState()) {
        delete this->getMotionState();
        this->setMotionState(NULL);
    }
    m_motionState = NULL;
    btCollisionShape *pShape = getRigidBody()->getCollisionShape();
    if(pShape) {
        getRigidBody()->setCollisionShape(NULL);
        delete pShape;
        m_bodyType = BODY_INVALID;
    }
}
//------------------------------------------------------------------------------
#endif /* FG_USING_BULLET */
