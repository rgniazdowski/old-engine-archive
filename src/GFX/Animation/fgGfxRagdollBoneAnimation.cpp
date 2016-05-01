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
 * File:   fgGfxRagdollBoneAnimation.cpp
 * Author: vigilant
 *
 * Created on October 10, 2015, 2:04 AM
 */

#include "fgGfxRagdollBoneAnimation.h"
#include "fgGfxArmature.h"
#include "fgGfxAnimationInfo.h"
#include "Physics/fgBulletHelper.h"
#include "GFX/fgGfxAssimpHelper.h"
#include "Math/fgMatrixOperations.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::anim::CRagdollBoneAnimation::CRagdollBoneAnimation(CArmature* pArmature) :
base_type(pArmature),
m_transforms(),
m_pModelMat(NULL) {
    if(pArmature) {
        m_transforms.reserve(pArmature->count());
        m_transforms.resize(pArmature->count(), NULL);
    }
    // 10 ticks & 10 ticks per second
    // duration is one second - it's not needed for now
    this->setTimeData(10.0f, 10.0f);
    // this animation also will not contain any channel info
    this->m_type = Type::BONE_RAGDOLL;
}
//------------------------------------------------------------------------------

gfx::anim::CRagdollBoneAnimation::CRagdollBoneAnimation(const CRagdollBoneAnimation& orig) :
base_type(orig) {
    this->m_type = Type::BONE_RAGDOLL;
}
//------------------------------------------------------------------------------

gfx::anim::CRagdollBoneAnimation::~CRagdollBoneAnimation() {
    m_transforms.clear();
}
//------------------------------------------------------------------------------

void gfx::anim::CRagdollBoneAnimation::calculate(SAnimationInfo& animationInfo,
                                                 float delta) { }
//------------------------------------------------------------------------------

void gfx::anim::CRagdollBoneAnimation::calculate(SAnimationInfo& animInfo,
                                                 const BonesVec& bones,
                                                 float delta) {
    // without pointer to model matrix cannot create valid transformations table
    if(!getArmature() || !m_pModelMat)
        return;
    // now also need some info on ragdoll collision body
    // 'bones' contains list of bones that need to be updated
    // this will be just simple copy operation (+ generate dual quaternions)
    // data will be copied from world transform matrices of each bone collision body
    // Need to convert transformations to model space.
    // Need also some fast way to determine which matrix to copy
    // as it is highly probable that the list of bones passed to function
    // will differ in content and order from list in CRagdollCollisionBody
    // #TODO
    const unsigned int nBones = bones.size();
    if(!nBones) {
        animInfo.curFrame.clear();
    }
    animInfo.curFrame.resize(nBones);
    if(m_intermediate.capacity() < nBones)
        m_intermediate.reserve(getArmature()->count());
    m_intermediate.resize(getArmature()->count());
    for(unsigned int i = 0; i < m_intermediate.size(); i++) {
        m_intermediate[i] = getArmature()->getBones()[i]->bindPoseMatrix;
    }
    const math::SUniversalTransform* pTransform = NULL, *pParentTransform = NULL;
    Matrix4f boneBodyMatrix, parentBoneBodyMatrix;
    Vec3f offsetScale, translation;
    //--------------------------------------------------------------------------
    /**
     * Create local bone transformation matrices (in bone space).
     * Derived from relative rotation between bone rigid bodies.
     * This data will simulate the one that is normally retrieved from animation
     * channel keys (rotations and positions).
     */
    for(unsigned int boneIdx = 0; boneIdx < nBones; boneIdx++) {
        SBone* pBone = bones[boneIdx];
        if(!pBone)
            continue; // ignore
        // table has size of the whole armature - easier
        pTransform = getTransform(pBone->index);
        pParentTransform = getTransform(pBone->parentIdx);
        if(!pTransform)
            continue; // ignore this bone - there is no information
        if(boneIdx == 0 || !pParentTransform) {
            // ignore pelvis
            m_intermediate[pBone->index] = Matrix4f();
            continue;
        }
        //SBone* pParentBone = pBone->pParent;
        pTransform->getTransform(boneBodyMatrix);
        pParentTransform->getTransform(parentBoneBodyMatrix);
        const Quatf parentBoneQuat = math::toQuat(parentBoneBodyMatrix);
        const Quatf boneQuat = math::toQuat(boneBodyMatrix);

        // Now this is a valid relative rotation (relative to parent!)
        // However if this bone is not first child... what then?
        const Quatf newRotQuat = math::inverse(parentBoneQuat) * boneQuat;
        const Matrix4f boneRelativeRotMat = math::toMat4(newRotQuat);
        pBone->getOffsetScale(offsetScale);
        // Rotation is local - now need to properly translate the bone - local bone space.
        // This translation will be scaled.
        pBone->getDirectionFromParent(translation);
        m_intermediate[pBone->index] = math::translate(Matrix4f(), translation * (offsetScale));
        m_intermediate[pBone->index] *= boneRelativeRotMat;
        // m_intermediate now contains local translation and rotation of the bone
        // just like it was read from animations key data.
    } // for each bone in array
    //--------------------------------------------------------------------------
    /**
     * Create final bone transformation matrices
     */
    for(unsigned int boneIdx = 0; boneIdx < nBones; boneIdx++) {
        SBone* pBone = bones[boneIdx];
        Vec3f matScale;
        pBone->getOffsetScale(matScale);
        Matrix4f& outMatrix = animInfo.curFrame.transformations[boneIdx];
        // start with the mesh-to-bone matrix
        outMatrix = pBone->offset;
        const SBone* pTmp = pBone;
        // append all node transformations down the parent chain
        // until we're back at mesh coordinates again
        while(pTmp) {
            outMatrix =
                    m_intermediate[pTmp->index] *
                    outMatrix;
            pTmp = pTmp->pParent;
            if(pTmp) {
                if(pTmp->name.compare("Armature") == 0) {
                    outMatrix = math::scale(Matrix4f(), 1.0f / matScale) * outMatrix;
                    break;
                }
            }
        }
        animInfo.curFrame.dualQuaternions[boneIdx].initializeFrom(outMatrix);
    } // for each bone in array
}
//------------------------------------------------------------------------------

void gfx::anim::CRagdollBoneAnimation::setTransform(unsigned int index,
                                                    math::SUniversalTransform* pTransform) {
    if(index >= m_transforms.size())
        return;
    m_transforms[index] = pTransform;
}
//------------------------------------------------------------------------------

math::SUniversalTransform* gfx::anim::CRagdollBoneAnimation::getTransform(unsigned int index) {
    if(index >= m_transforms.size())
        return NULL;
    return m_transforms[index];
}
//------------------------------------------------------------------------------

math::SUniversalTransform const* gfx::anim::CRagdollBoneAnimation::getTransform(unsigned int index) const {
    if(index >= m_transforms.size())
        return NULL;
    return m_transforms[index];
}
//------------------------------------------------------------------------------
