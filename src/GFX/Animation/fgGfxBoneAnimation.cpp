/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written permission from the author.
 *******************************************************/
/* 
 * File:   fgGfxBoneAnimation.cpp
 * Author: vigilant
 * 
 * Created on September 2, 2015, 5:40 PM
 */

#include "fgGfxBoneAnimation.h"
#include "fgGfxAnimationInfo.h"
#include "fgGfxArmature.h"
#include "Util/fgTime.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::anim::CBoneAnimation::CBoneAnimation(CArmature* pArmature) :
base_type(),
m_pArmature(pArmature) {
    m_type = Type::BONE;
    m_intermediate.reserve(32);
}
//------------------------------------------------------------------------------

gfx::anim::CBoneAnimation::CBoneAnimation(const CBoneAnimation& orig) :
base_type(orig) {
    m_pArmature = orig.m_pArmature;
    m_type = Type::BONE;
    m_intermediate.append(orig.m_intermediate);
}
//------------------------------------------------------------------------------

gfx::anim::CBoneAnimation::~CBoneAnimation() {
    m_pArmature = NULL;
    m_intermediate.clear();
}
//------------------------------------------------------------------------------

void gfx::anim::CBoneAnimation::calculate(SAnimationFrameInfo& frameInfo,
                                          float elapsed) {
    if(!m_pArmature) {
        // nothing to do!
        return;
    }

    // time scale? elapsed is in seconds...
    const float currentTime = math::mod(elapsed, getDurationInSeconds());
    frameInfo.elapsed = currentTime;
    CArmature::BonesVec const& bones = m_pArmature->getBones();
    const unsigned int nBones = bones.size();
    frameInfo.transformations.reserve(nBones);
    frameInfo.transformations.resize(nBones);
    for(unsigned int i = 0; i < nBones; i++) {
        frameInfo.transformations[i] = bones[i]->bindPoseMatrix;
    }
    // frameInfo.transformations contains final bone matrices;
    // this vector will hold node transformation matrices #LOCK
    if(m_intermediate.capacity() < nBones)
        m_intermediate.reserve(nBones);
    m_intermediate.resize(nBones);

    ChannelsVec& channels = getChannels();
    const unsigned int nChannels = count();
    for(unsigned int i = 0; i < nChannels; i++) {
        SAnimationChannel& channel = channels[i];
        SBone* pBone = m_pArmature->get(channel.targetName);
        if(!pBone)
            continue;
        if(shouldInterpolate()) {
            channel.getMatrixInterpolated(m_intermediate[pBone->index],
                                          currentTime);
        } else {
            channel.getMatrix(m_intermediate[pBone->index],
                              currentTime);
        }
    }

    for(unsigned int i = 0; i < nBones; i++) {
        SBone* pBone = bones[i];
        // start with the mesh-to-bone matrix
        frameInfo.transformations[pBone->index] = pBone->offset;

        const SBone* pTmp = pBone;
        // append all node transformations down the parent chain
        // until we're back at mesh coordinates again
        while(pTmp) {
            frameInfo.transformations[pBone->index] *= m_intermediate[pTmp->index];
            pTmp = pTmp->pParent;
        }
    }
}
//------------------------------------------------------------------------------