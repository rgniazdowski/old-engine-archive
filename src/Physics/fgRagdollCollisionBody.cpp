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
 * File:   fgRagdollCollisionBody.cpp
 * Author: vigilant
 *
 * Created on October 10, 2015, 12:47 AM
 */

#include "fgRagdollCollisionBody.h"
#include "fgCollisionBody.h"
#include <stack>

#if defined(FG_USING_BULLET)
#include "BulletDynamics/ConstraintSolver/btConeTwistConstraint.h"
#include "BulletDynamics/ConstraintSolver/btHingeConstraint.h"
#include "BulletDynamics/Dynamics/btDynamicsWorld.h"

using namespace fg;
//------------------------------------------------------------------------------

physics::CRagdollCollisionBody::CRagdollCollisionBody() : base_type(BODY_RAGDOLL),
m_bones(),
m_bonesInfo(),
m_transforms(),
m_boneMapping(),
m_typeMapping(),
m_initialTransforms(),
m_initialRotations(),
m_modelMat(),
m_joints(),
m_mass(100.0f),
m_isRagdolling(FG_FALSE) { }
//------------------------------------------------------------------------------

physics::CRagdollCollisionBody::CRagdollCollisionBody(const self_type& orig) :
base_type(BODY_RAGDOLL) { }
//------------------------------------------------------------------------------

physics::CRagdollCollisionBody::~CRagdollCollisionBody() {
    // destroy some stuff
    destroyData();
}
//------------------------------------------------------------------------------

void physics::CRagdollCollisionBody::setHalfSize(const Vector3f& halfExtent) {
    // IGNORE
}
//------------------------------------------------------------------------------

void physics::CRagdollCollisionBody::setRadius(const float radius) {
    // IGNORE
}
//------------------------------------------------------------------------------

void physics::CRagdollCollisionBody::setHeight(const float height) {
    // IGNORE
}
//------------------------------------------------------------------------------

void physics::CRagdollCollisionBody::setMass(float mass) {
    m_mass = mass;
    // ? should ignore? or set mass for each bone/body (proportionally)
    if(m_bonesInfo.empty() || m_bones.empty() || m_transforms.empty())
        return;
    float totalLength = 0;
    const unsigned int nBones = m_bonesInfo.size();
    for(unsigned int boneIdx = 0; boneIdx < nBones; boneIdx++) {
        SBoneSmallInfo const& boneInfo = m_bonesInfo[boneIdx];
        if(boneInfo.length < FG_EPSILON) {
            totalLength += 1.0f;
        } else {
            totalLength += boneInfo.length;
        }
    }
    for(unsigned int boneIdx = 0; boneIdx < nBones; boneIdx++) {
        SBoneSmallInfo const& boneInfo = m_bonesInfo[boneIdx];
        CCollisionBody* pBody = m_bones[boneIdx]; // same positioning
        if(!pBody) {
            continue;
        }
        float bodyMass;
        if(boneInfo.length < FG_EPSILON) {
            bodyMass = this->m_mass * 1.0f / totalLength;
        } else {
            bodyMass = this->m_mass * boneInfo.length / totalLength;
        }
        pBody->setMass(bodyMass);
    }
}
//------------------------------------------------------------------------------

void physics::CRagdollCollisionBody::setLocalScaling(const Vector3f& scale) {
    // IGNORE ?
}
//------------------------------------------------------------------------------

void physics::CRagdollCollisionBody::setupBody(BodyType bodyType) {
    m_bodyType = BODY_RAGDOLL;
}
//------------------------------------------------------------------------------

fgBool physics::CRagdollCollisionBody::initializeFrom(const BonesInfoVec& bonesInfo,
                                                      unsigned int armatureSize,
                                                      fgBool initInRestPose) {

    if(!armatureSize)
        return FG_FALSE;

    if(bonesInfo.empty())
        return FG_FALSE;

    if(m_bonesInfo.size()) {
        // ? should revert all changes, destroy data and reinitialize...
        destroyData();
        return FG_FALSE; // #FIXME
    }
    // initialize some stuff with armatureSize (number of all bones !)
    m_transforms.resize(armatureSize, NULL);
    m_boneMapping.clear(); // ?
    m_boneMapping.resize(armatureSize, -1);
    m_typeMapping.clear();
    const unsigned int nBonesInfo = bonesInfo.size();
    fgBool hasHead = FG_FALSE,
            hasNeck = FG_FALSE,
            hasSpine = FG_FALSE,
            hasPelvis = FG_FALSE;
    for(unsigned int i = 0; i < nBonesInfo; i++) {
        const SBoneSmallInfo& info = bonesInfo[i];
        if(info.boneType == BONE_INVALID)
            continue;
        // should create collision bodies here?
        CCollisionBody* pBoneBody = new CCollisionBody(BODY_CAPSULE);
        // complete height is radius * 2 + height
        // height = halfHeight * 2.0
        float length = info.length;
        //length = 20.0f;
        float height = 0.0f, radius = 0.0f;
        if(length < FG_EPSILON)
            length = 1.0f;
        if(length == 1.0f) {
            radius = 0.1f;
            height = 0.8f;
        } else {
            radius = 0.1f * length;
            if(radius > 5.0f)
                radius = 5.0f;
            height = length - radius * 2.0f;
        }
        if(info.boneType == BONE_PELVIS)
            hasPelvis = FG_TRUE;
        else if(info.boneType == BONE_SPINE)
            hasSpine = FG_TRUE;
        else if(info.boneType == BONE_NECK)
            hasNeck = FG_TRUE;
        else if(info.boneType == BONE_HEAD)
            hasHead = FG_TRUE;

        // need to create capsule shapes for each bone
        // useful info is from bone length
        // however also useful would be start and end point...
        pBoneBody->setHeight(height);
        pBoneBody->setRadius(radius);
        m_bones.push_back(pBoneBody);
        // map bone index to bone rigid body index in the array
        m_boneMapping[info.index] = m_bones.size() - 1;
        m_bonesInfo.push_back(info); // copy for future reference
        //m_bonesInfo[m_bonesInfo.size() - 1].length = 20.0f;
        // now can easily access bone information by bone type
        m_typeMapping[info.boneType].push_back(m_bonesInfo.size() - 1);
        if(m_transforms[info.index]) {
            delete m_transforms[info.index];
        }
        m_transforms[info.index] = new SBulletUniTransform(&pBoneBody->getWorldTransform());
    } // for each bone small info
    m_initialTransforms.resize(m_bones.size());
    m_initialRotations.resize(m_bones.size());
    this->setMass(m_mass);
    // now need to pre-transform rigid bodies into some pose
    // need to access them via bone type (that's what local infoMap is for)

    BonesTypeMap::iterator bimIt = m_typeMapping.begin(), bimEnd = m_typeMapping.end();
    for(; bimIt != bimEnd; bimIt++) {
        //const RagdollBoneType boneType = bimIt->first;
        unsigned int nBonesIdx = bimIt->second.size();
        for(unsigned int idx = 0; idx < nBonesIdx; idx++) {
            const int boneInfoIdx = bimIt->second.at(idx);
            const SBoneSmallInfo& info = m_bonesInfo[boneInfoIdx];
            const int boneIndex = info.index;
            const int bodyBoneIdx = m_boneMapping[boneIndex];
            //CCollisionBody* pBoneBody = m_bones[bodyBoneIdx];

            // direction towards endPoint
            const Vector3f direction = info.endPoint - info.startPoint;
            Vector3f offCenter = direction / 2.0f;
            // Rotation based on inversed offset matrix
            helper_initializeBone(bodyBoneIdx, info.startPoint + offCenter, info.rotation);
        } // for each bone index

        // now all bones are initialized with starting position and rotation
        // need to connect them by joints

    } // for each bone info map entry    
    // there are standard joint pairs can create array with joint chains...

    // Need to traverse the whole bone structure.
    // Keep in mind that this will be tricky as there is no list of children,
    // only information about parent for each bone.
    // Will use stack for this and array with visited ids.
    std::stack<int> bStack;
    CVector<int> bVisited;
    bVisited.reserve(armatureSize); // ?
    const int nBones = (int)m_bonesInfo.size();
    // traverse the bone list starting from the last one
    for(int idxBone = nBones - 1; idxBone >= 0; idxBone--) {
        if(bVisited.contains(idxBone))
            continue;
        bStack.push(idxBone);
        while(!bStack.empty()) {
            int childBoneIdx = bStack.top();
            bStack.pop();
            // mark the bone as visited
            bVisited.push_back(childBoneIdx);

            // now need to get type of the first bone
            // get parent idx ; get type for each one of them
            // and call initialize_Joint (which needs to get different parameters)
            SBoneSmallInfo* pChildBone = &m_bonesInfo[childBoneIdx];
            if(pChildBone->parentIdx < 0) {
                // no parent? well...
                continue;
            }
            int parentBoneIdx = m_boneMapping[pChildBone->parentIdx];
            if(parentBoneIdx < 0) {
                continue;
            }
            SBoneSmallInfo* pParentBone = &m_bonesInfo[parentBoneIdx];
            if(pParentBone->boneType == BONE_INVALID) {
                continue;
            }
            helper_initializeJoint(pParentBone->boneType,
                                   parentBoneIdx,
                                   pChildBone->boneType,
                                   childBoneIdx);
        } // while stack not empty
    } // reverse traversal
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool physics::CRagdollCollisionBody::helper_initializeJoint(const RagdollBoneType boneA,
                                                              int boneAIndex,
                                                              const RagdollBoneType boneB,
                                                              int boneBIndex) {
    fgBool status = FG_FALSE,
            isEqual = (fgBool)(boneA == boneB),
            isFlipped = FG_FALSE,
            useHinge = FG_FALSE; // when false - will use cone

    if(boneB == BONE_INVALID || boneAIndex < 0 || boneBIndex < 0) {
        return FG_FALSE;
    }
    if(boneA == BONE_INVALID)
        return FG_FALSE;
    
    if(m_typeMapping.find(boneA) == m_typeMapping.end()) {
        // no such bone in the armature? ignore!
        return FG_FALSE;
    }
    if(m_bones.empty() || m_bonesInfo.empty()) {
        return FG_FALSE; // nothing to do
    }
    JointID jointID = JointID(boneA, boneB);
    btHingeConstraint* pHinge = NULL;
    btConeTwistConstraint* pCone = NULL;
    btTypedConstraint* pTypedConstraint = NULL;
    btTransform localA, localB;
    Vec3f limit;
    {
        localA.setIdentity();
        localB.setIdentity();

        SBoneSmallInfo* infoA = &m_bonesInfo[boneAIndex];
        SBoneSmallInfo* infoB = &m_bonesInfo[boneBIndex];
        CCollisionBody* pBoneBodyA = m_bones[boneAIndex];
        CCollisionBody* pBoneBodyB = m_bones[boneBIndex];
        Matrix4f* pMatrixA = &m_initialTransforms[boneAIndex];
        Matrix4f* pMatrixB = &m_initialTransforms[boneBIndex];
        Vector3f* pRotationA = &m_initialRotations[boneAIndex];
        Vector3f* pRotationB = &m_initialRotations[boneBIndex];
        //-------------------------------------------
        // now this part of code will be long... need to check for almost
        // every possible bone pair and select proper constraint type;
        if(jointID.check(BONE_PELVIS, BONE_SPINE, &isFlipped)) {
            useHinge = FG_TRUE;
            limit.x = -math::quarter_pi<float>();
            limit.y = math::quarter_pi<float>();
            limit.z = 0.0f;
        } else if(jointID.check(BONE_SPINE, BONE_NECK, &isFlipped)) {
            useHinge = FG_TRUE;
            limit.x = -math::quarter_pi<float>();
            limit.y = math::quarter_pi<float>();
            limit.z = 0.0f;
        } else if(jointID.check(BONE_NECK, BONE_HEAD, &isFlipped) ||
                  jointID.check(BONE_SPINE, BONE_HEAD, &isFlipped)) {
            useHinge = FG_FALSE; // will use cone-twist
            limit.x = math::radians(55.0f);
            limit.y = math::radians(55.0f); // up-down
            limit.z = math::radians(45.0f);

        } else if(jointID.check(BONE_PELVIS, BONE_THIGH_LEFT, &isFlipped)) {
            // LEFT HIP
            useHinge = FG_FALSE; // will use cone-twist
            limit.x = math::radians(55.0f);
            limit.y = math::radians(55.0f);
            limit.z = math::radians(0.0f);
        } else if(jointID.check(BONE_THIGH_LEFT, BONE_LEG_LEFT, &isFlipped)) {
            // LEFT KNEE
            useHinge = FG_TRUE;
            limit.x = -math::half_pi<float>();
            limit.y = math::half_pi<float>()*0;
            limit.z = 0.0f;
        } else if(jointID.check(BONE_LEG_LEFT, BONE_FOOT_LEFT, &isFlipped)) {
            // LEFT ANKLE
            useHinge = FG_TRUE;
            limit.x = -math::half_pi<float>()*0;
            limit.y = math::half_pi<float>();
            limit.z = 0.0f;
        } else if(jointID.check(BONE_PELVIS, BONE_THIGH_RIGHT, &isFlipped)) {
            // RIGHT HIP
            useHinge = FG_FALSE; // will use cone-twist
            limit.x = math::radians(55.0f);
            limit.y = math::radians(55.0f);
            limit.z = math::radians(0.0f);
        } else if(jointID.check(BONE_THIGH_RIGHT, BONE_LEG_RIGHT, &isFlipped)) {
            // RIGHT KNEE
            useHinge = FG_TRUE;
            limit.x = -math::half_pi<float>();
            limit.y = math::half_pi<float>()*0;
            limit.z = 0.0f;
        } else if(jointID.check(BONE_LEG_RIGHT, BONE_FOOT_RIGHT, &isFlipped)) {
            // RIGHT ANKLE
            useHinge = FG_TRUE;
            limit.x = -math::half_pi<float>()*0;
            limit.y = math::half_pi<float>();
            limit.z = 0.0f;
        } else if(jointID.check(BONE_SPINE, BONE_ARM_LEFT, &isFlipped)) {
            // LEFT SHOULDER
            useHinge = FG_FALSE; // will use cone-twist
            limit.x = math::radians(50.0f); // left/right
            limit.y = math::radians(50.0f); // up/down
            limit.z = math::radians(0.0f); // twist            
        } else if(jointID.check(BONE_ARM_LEFT, BONE_FOREARM_LEFT, &isFlipped)) {
            // LEFT ELBOW
            useHinge = FG_TRUE; // true
            //limit.x = math::quarter_pi<float>();
            limit.x = -math::half_pi<float>()*0;
            limit.y = math::half_pi<float>();
            limit.z = 0.0f;
        } else if(jointID.check(BONE_FOREARM_LEFT, BONE_HAND_LEFT, &isFlipped)) {
            // LEFT WRIST
            useHinge = FG_TRUE; // will use cone-twist
            limit.x = math::radians(-90.0f);
            limit.y = math::radians(45.0f);
            limit.z = 0.0f;

        } else if(jointID.check(BONE_SPINE, BONE_ARM_RIGHT, &isFlipped)) {
            // RIGHT SHOULDER
            useHinge = FG_FALSE; // will use cone-twist
            limit.x = math::radians(50.0f); // left/right
            limit.y = math::radians(50.0f); // up/down
            limit.z = math::radians(0.0f); // twist            
        } else if(jointID.check(BONE_ARM_RIGHT, BONE_FOREARM_RIGHT, &isFlipped)) {
            // RIGHT ELBOW
            useHinge = FG_TRUE;
            limit.x = -math::half_pi<float>()*0;
            limit.y = math::half_pi<float>();
            limit.z = 0.0f;
        } else if(jointID.check(BONE_FOREARM_RIGHT, BONE_HAND_RIGHT, &isFlipped)) {
            // RIGHT WRIST
            useHinge = FG_TRUE; // will use cone-twist
            limit.x = math::radians(-90.0f);
            limit.y = math::radians(45.0f);
            limit.z = 0.0f;
        } else {// if(isEqual || 1) {
            // this is more universal, if connecting two bones with the same type
            // just use hinge constraint...
            useHinge = FG_TRUE;
            // need to check which one comes first (as A) and which one as second (as B)
            // this depends on relative position between start/end/center points of each bones
            // don't know if need to check bone hierarchy just yet.
            // a-start - distance to a-end | a-start - distance to b-end
            //float distanceA = infoA->length;
            //float distanceB = math::length(infoB->endPoint - infoA->startPoint);
            // fuck...
            limit.x = -math::quarter_pi<float>();
            limit.y = math::quarter_pi<float>();
            limit.z = 0.0f;
        }
        // need to know what to use and how, also need to perform flipping
        if(isFlipped) {
            std::swap<int>(boneAIndex, boneBIndex);
            std::swap<SBoneSmallInfo*>(infoA, infoB);
            std::swap<CCollisionBody*>(pBoneBodyA, pBoneBodyB);
            std::swap<Matrix4f*>(pMatrixA, pMatrixB);
            std::swap<Vector3f*>(pRotationA, pRotationB);
        } // now know what comes before and what after <- this is proper English :)

        if(useHinge) {
            {
                btTransform globalFrame;
                globalFrame.setOrigin(btVector3(infoB->startPoint.x,
                                                infoB->startPoint.y,
                                                infoB->startPoint.z));
                globalFrame.getBasis().setEulerZYX(0.0f, -math::half_pi<float>(), 0.0f);
                localA = pBoneBodyA->getWorldTransform().inverse() * globalFrame;
                localB = pBoneBodyB->getWorldTransform().inverse() * globalFrame;

                pHinge = new btHingeConstraint(*pBoneBodyA->getRigidBody(),
                                               *pBoneBodyB->getRigidBody(),
                                               localA, localB, true);
            }
            pTypedConstraint = pHinge;
            pCone = NULL;
            pHinge->setLimit(limit.x, limit.y);
            pHinge->setEnabled(false);
        } else {
            {
                btTransform globalFrame;
                globalFrame.setOrigin(btVector3(infoB->startPoint.x,
                                                infoB->startPoint.y,
                                                infoB->startPoint.z));
                // need to rotate properly - twist axis needs to be along the bone
                globalFrame.getBasis().setEulerZYX(pRotationB->x, pRotationB->y, pRotationB->z);
                btMatrix3x3 rot;
                rot.setEulerZYX(0.0f, math::radians(0.0f), math::radians(90.0f));
                globalFrame.getBasis() *= rot;
                localA = pBoneBodyA->getWorldTransform().inverse() * globalFrame;
                localB = pBoneBodyB->getWorldTransform().inverse() * globalFrame;
            }
            pCone = new btConeTwistConstraint(*pBoneBodyA->getRigidBody(),
                                              *pBoneBodyB->getRigidBody(),
                                              localA, localB);
            pTypedConstraint = pCone;
            pHinge = NULL;
            pCone->setLimit(limit.x, limit.y, limit.z, 0.9f, 0.3f, 0.9f);
            pCone->setEnabled(false);
        }
        pTypedConstraint->setDbgDrawSize(10.0f);
        m_joints.addConstraint(jointID, pTypedConstraint);
        status = FG_TRUE;
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool physics::CRagdollCollisionBody::helper_initializeBone(unsigned int bodyBoneIdx,
                                                             const Vec3f& position,
                                                             const Quatf& rotation) {

    if(bodyBoneIdx >= m_bones.size())
        return FG_FALSE;
    CCollisionBody* pBoneBody = m_bones[bodyBoneIdx];
    pBoneBody->setRotation(rotation);
    pBoneBody->setPosition(position);
    pBoneBody->getWorldTransform(m_initialTransforms[bodyBoneIdx]);
    pBoneBody->getWorldTransform().getBasis().getEulerZYX(m_initialRotations[bodyBoneIdx].z,
                                                          m_initialRotations[bodyBoneIdx].y,
                                                          m_initialRotations[bodyBoneIdx].x);
    pBoneBody->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
    pBoneBody->setDamping(0.05, 0.85);
    pBoneBody->setDeactivationTime(3.0);
    pBoneBody->setSleepingThresholds(5.6, 5.5);
    pBoneBody->setContactProcessingThreshold(0.25f);
    pBoneBody->setCcdMotionThreshold(0.05f);
    pBoneBody->setCcdSweptSphereRadius(0.06f);
    pBoneBody->setGravity(btVector3(0.0f, -9.8f, 0.0f));
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void physics::CRagdollCollisionBody::setInitialTransform(unsigned int armatureBoneIndex,
                                                         const Matrix4f& inBoneMatrix) {
    if(armatureBoneIndex >= m_boneMapping.size())
        return;
    const int bodyIndex = m_boneMapping[armatureBoneIndex];
    if(bodyIndex < 0) {
        return;
    }
    CCollisionBody* pBoneBody = m_bones[bodyIndex];
    if(!pBoneBody)
        return;
    Vec3f startPoint, endPoint;
    Vec4f position4f;
    position4f = inBoneMatrix * Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
    startPoint = Vec3f(position4f);
    position4f = inBoneMatrix * Vec4f(0.0f, m_bonesInfo[bodyIndex].length, 0.0f, 1.0f);
    endPoint = Vec3f(position4f);
    // direction towards endPoint
    const Vector3f direction = endPoint - startPoint;
    const Vector3f offCenter = direction / 2.0f;
    //const Vec3f& position = Vec3f(inBoneMatrix[3]);
    const Quatf& rotation = math::toQuat(inBoneMatrix);
    pBoneBody->setRotation(rotation);
    pBoneBody->setPosition(startPoint + offCenter);
    pBoneBody->getWorldTransform(m_initialTransforms[bodyIndex]);
    pBoneBody->getWorldTransform().getBasis().getEulerZYX(m_initialRotations[bodyIndex].z,
                                                          m_initialRotations[bodyIndex].y,
                                                          m_initialRotations[bodyIndex].x);
}
//------------------------------------------------------------------------------

void physics::CRagdollCollisionBody::setDefaultInitialTransforms(void) { }
//------------------------------------------------------------------------------

void physics::CRagdollCollisionBody::startRagdolling(void) {
    if(m_isRagdolling || !m_pOwner) { // can't start ragdolling
        return; // ignore
    }
    if(!addRigidBodiesToOwner())
        return;
    if(!registerJoints())
        return;
    if(m_bones.empty() || !m_pOwner)
        return;
    const unsigned int nBones = m_bones.size();
    for(unsigned int i = 0; i < nBones; i++) {
        CCollisionBody* pBoneBody = m_bones[i];
        if(!pBoneBody)
            continue;
        pBoneBody->setWorldTransform(m_modelMat * m_initialTransforms[i]);
        pBoneBody->clearForces();
        pBoneBody->setAngularVelocity(0.0f);
        pBoneBody->setVelocity(0.0f);
        pBoneBody->activate();
    }
    m_isRagdolling = FG_TRUE;
}
//------------------------------------------------------------------------------

void physics::CRagdollCollisionBody::stopRagdolling(void) {
    if(!m_isRagdolling) {
        return; // ignore
    }
    // first unregister joints
    unregisterJoints();
    removeRigidBodiesFromOwner();
    m_isRagdolling = FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool physics::CRagdollCollisionBody::isRagdolling(void) const {
    return m_isRagdolling;
}
//------------------------------------------------------------------------------

physics::CCollisionBody* physics::CRagdollCollisionBody::getBoneBody(unsigned int armatureBoneIndex,
                                                                     int* outIndex) {
    if(m_boneMapping.size() <= armatureBoneIndex) {
        return NULL;
    }
    const int index = m_boneMapping[armatureBoneIndex];
    if(index >= 0 && index < (int)m_bones.size()) {
        if(outIndex)
            *outIndex = index;
        return m_bones.at(index);
    }
    if(outIndex)
        *outIndex = -1;
    return NULL;
}
//------------------------------------------------------------------------------

physics::CCollisionBody* physics::CRagdollCollisionBody::getBoneBody(const char *name,
                                                                     int* outIndex) {
    if(!name)
        return NULL;
    if(!name[0])
        return NULL;
    if(m_bones.empty() || m_bonesInfo.empty())
        return NULL;
    const unsigned int n = m_bonesInfo.size();
    unsigned int found = n;
    for(unsigned int i = 0; i < n; i++) {
        if(m_bonesInfo[i].name.compare(name) == 0) {
            found = i;
            break;
        }
    }
    if(found < m_bones.size()) {
        if(outIndex)
            *outIndex = (int)found;
        return m_bones[found];
    }
    if(outIndex)
        *outIndex = -1;
    return NULL;
}
//------------------------------------------------------------------------------

physics::CCollisionBody* physics::CRagdollCollisionBody::getBoneBody(RagdollBoneType boneType) {
    if(boneType == BONE_INVALID)
        return NULL;
    BonesTypeMap::iterator itor = m_typeMapping.find(boneType);
    if(itor == m_typeMapping.end())
        return NULL;
    if(itor->second.empty())
        return NULL;
    unsigned int boneBodyIdx = itor->second.at(0);
    if(m_bones.size() <= boneBodyIdx)
        return NULL;
    return m_bones[boneBodyIdx];
}
//------------------------------------------------------------------------------

physics::CCollisionBody* physics::CRagdollCollisionBody::getParentBoneBody(CCollisionBody* pBoneBody) {
    const unsigned int n = m_bones.size();
    if(!n)
        return NULL;
    int bodyIndex = m_bones.find(pBoneBody);
    if(bodyIndex < 0)
        return NULL;
    int parentBoneIndex = m_bonesInfo[bodyIndex].parentIdx;
    if(parentBoneIndex < 0) {
        return NULL;
    }
    int parentBodyIndex = m_boneMapping[parentBoneIndex];
    if(parentBodyIndex < 0 || parentBodyIndex >= (int)m_bones.size()) {
        return NULL;
    }
    return m_bones[parentBodyIndex];
}
//------------------------------------------------------------------------------

physics::CCollisionBody* physics::CRagdollCollisionBody::getParentBoneBody(unsigned int armatureBoneIndex) {
    if(armatureBoneIndex >= m_boneMapping.size())
        return NULL;
    int bodyIndex = m_boneMapping[armatureBoneIndex];
    if(bodyIndex < 0) {
        return NULL;
    }
    int parentBoneIndex = m_bonesInfo[bodyIndex].parentIdx;
    if(parentBoneIndex < 0) {
        return NULL;
    }
    int parentBodyIndex = m_boneMapping[parentBoneIndex];
    if(parentBodyIndex < 0 || parentBodyIndex >= (int)m_bones.size()) {
        return NULL;
    }
    return m_bones[parentBodyIndex];
}
//------------------------------------------------------------------------------

physics::CCollisionBody* physics::CRagdollCollisionBody::getParentBoneBody(const char* name,
                                                                           int* outIndex) {
    int bodyIndex = -1;
    CCollisionBody* pBody = getBoneBody(name, &bodyIndex);
    if(outIndex)
        *outIndex = -1;
    if(!pBody)
        return NULL;
    int parentBoneIndex = m_bonesInfo[bodyIndex].parentIdx;
    if(parentBoneIndex < 0) {
        return NULL;
    }
    int parentBodyIndex = m_boneMapping[parentBoneIndex];
    if(parentBodyIndex < 0 || parentBodyIndex >= (int)m_bones.size()) {
        return NULL;
    }
    if(outIndex)
        *outIndex = parentBodyIndex;
    return m_bones[parentBodyIndex];
}
//------------------------------------------------------------------------------

void physics::CRagdollCollisionBody::alignBone(unsigned int armatureBoneIndex,
                                               const Vector3f& direction) {
    CCollisionBody* pBoneBody = getBoneBody(armatureBoneIndex);
    if(!pBoneBody)
        return;
    const float yaw = atan2(direction.x, direction.z);
    const float padj = sqrt(pow(direction.x, 2) + pow(direction.z, 2));
    const float pitch = atan2(padj, direction.y);
    Vec3f eulerRots = Vec3f(pitch, yaw, 0.0f);
    pBoneBody->getWorldTransform().getBasis().setEulerZYX(eulerRots.x, eulerRots.y, eulerRots.z);
}
//------------------------------------------------------------------------------

void physics::CRagdollCollisionBody::rotateBone(unsigned int armatureBoneIndex,
                                                const Quaternionf& rotation) {
    CCollisionBody* pBoneBody = getBoneBody(armatureBoneIndex);
    if(!pBoneBody)
        return;
    pBoneBody->setRotation(rotation);
}
//------------------------------------------------------------------------------

void physics::CRagdollCollisionBody::rotateBone(unsigned int armatureBoneIndex,
                                                const Vector3f& direction) {
    CCollisionBody* pBoneBody = getBoneBody(armatureBoneIndex);
    if(!pBoneBody)
        return;
    const Quaternionf rotation = math::rotation(Vec3f(0.0f, 1.0f, 0.0f),
                                                math::normalize(direction));
    pBoneBody->setRotation(rotation);
}
//------------------------------------------------------------------------------

math::SUniversalTransform* physics::CRagdollCollisionBody::getUniversalTransform(unsigned int armatureBoneIndex) {
    if(armatureBoneIndex >= m_transforms.size()) {
        return NULL;
    }
    return m_transforms[armatureBoneIndex];
}
//------------------------------------------------------------------------------

void physics::CRagdollCollisionBody::getUniversalTransform(unsigned int armatureBoneIndex,
                                                           Matrix4f& outMatrix) {
    if(armatureBoneIndex >= m_transforms.size()) {
        return;
    }
    if(!m_transforms[armatureBoneIndex])
        return;
    m_transforms[armatureBoneIndex]->getTransform(outMatrix);
}
//------------------------------------------------------------------------------

void physics::CRagdollCollisionBody::setUniversalTransform(unsigned int armatureBoneIndex,
                                                           const Matrix4f& inMatrix) {
    // if such transformation does not exist?
    if(armatureBoneIndex >= m_transforms.size()) {
        return;
    }
    if(m_transforms[armatureBoneIndex] == NULL) {

        return;
    }
    m_transforms[armatureBoneIndex]->setTransform(inMatrix);
}
//------------------------------------------------------------------------------

fgBool physics::CRagdollCollisionBody::addRigidBodiesToOwner(void) {
    if(m_bones.empty() || !m_pOwner)
        return FG_FALSE;
    const unsigned int nBones = m_bones.size();
    btCollisionObjectArray & objects = m_pOwner->getCollisionObjectArray();
    for(unsigned int i = 0; i < nBones; i++) {
        CCollisionBody* pBoneBody = m_bones[i];
        if(!pBoneBody)
            continue;
        if(!pBoneBody->getRigidBody())
            continue;
        if(objects.findLinearSearch(pBoneBody->getRigidBody()) != objects.size())
            continue; // object already exists - ignore
        //pBoneBody->activate();
        pBoneBody->setOwner(m_pOwner);
        m_pOwner->addRigidBody(pBoneBody->getRigidBody());
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool physics::CRagdollCollisionBody::removeRigidBodiesFromOwner(void) {
    if(!m_pOwner)
        return FG_FALSE;
    if(m_bones.empty())
        return FG_TRUE;
    const unsigned int nBones = m_bones.size();
    for(unsigned int i = 0; i < nBones; i++) {
        CCollisionBody* pBoneBody = m_bones[i];
        if(!pBoneBody)
            continue;
        if(!pBoneBody->getRigidBody())
            continue;
        m_pOwner->removeRigidBody(pBoneBody->getRigidBody());
        pBoneBody->setOwner(NULL);
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool physics::CRagdollCollisionBody::registerJoints(void) {
    if(m_joints.isEmpty())
        return FG_FALSE;
    if(!m_pOwner)
        return FG_FALSE;
    JointsMap::iterator itor = m_joints.begin(), end = m_joints.end();
    for(; itor != end; itor++) {
        ConstraintsVec& constraints = itor->second;
        const unsigned int n = constraints.size();
        for(unsigned int i = 0; i < n; i++) {
            if(!constraints[i])
                continue;
            // enabled flag means that the constraint is already in the world
            if(constraints[i]->isEnabled() == false)
                m_pOwner->addConstraint(constraints[i], true);
            constraints[i]->setEnabled(true);
        }
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool physics::CRagdollCollisionBody::unregisterJoints(void) {
    if(m_joints.isEmpty())
        return FG_TRUE; // nothing to unregister.. success
    if(!m_pOwner)
        return FG_FALSE;
    JointsMap::iterator itor = m_joints.begin(), end = m_joints.end();
    for(; itor != end; itor++) {
        ConstraintsVec& constraints = itor->second;
        const unsigned int n = constraints.size();
        for(unsigned int i = 0; i < n; i++) {
            if(!constraints[i])
                continue;
            m_pOwner->removeConstraint(constraints[i]);
            constraints[i]->setEnabled(false);
        }
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool physics::CRagdollCollisionBody::destroyJoints(void) {
    fgBool status = unregisterJoints();
    if(!status)
        return FG_FALSE;
    if(m_joints.count() == 0)
        return FG_TRUE;
    // destroy
    JointsMap::iterator itor = m_joints.begin(), end = m_joints.end();
    for(; itor != end; itor++) {
        ConstraintsVec& constraints = itor->second;
        const unsigned int n = constraints.size();
        for(unsigned int i = 0; i < n; i++) {
            if(constraints[i])
                delete constraints[i];
            constraints[i] = NULL;
        }
        constraints.clear();
    }
    m_joints.clear();
    return status;
}
//------------------------------------------------------------------------------

fgBool physics::CRagdollCollisionBody::destroyBones(void) {
    fgBool status = removeRigidBodiesFromOwner();
    if(!status)
        return FG_FALSE;
    // need also to destroy joints
    status = destroyJoints();
    if(!status) {
        // ignore?
    }
    // destroy
    const unsigned int nBones = m_bones.size();
    for(unsigned int i = 0; i < nBones; i++) {
        if(m_bones[i])
            delete m_bones[i];
        m_bones[i] = NULL;
    }
    m_bones.clear();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool physics::CRagdollCollisionBody::destroyData(void) {
    // this will destroy everything - no double checks
    stopRagdolling();
    destroyJoints();
    destroyBones();
    m_bonesInfo.clear();
    unsigned int n = m_transforms.size();
    for(unsigned int i = 0; i < n; i++) {
        if(m_transforms[i])
            delete m_transforms[i];
        m_transforms[i] = NULL;
    }
    m_transforms.clear();
    m_boneMapping.clear();
    BonesTypeMap::iterator itor = m_typeMapping.begin(), end = m_typeMapping.end();
    for(; itor != end; itor++) {
        itor->second.clear();
    }
    m_typeMapping.clear();
    m_initialTransforms.clear();
    //m_mass = 1.0f;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

#endif /* FG_USING_BULLET */
