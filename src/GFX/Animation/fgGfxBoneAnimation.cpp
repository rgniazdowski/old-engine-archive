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
    if(!m_pArmature)
        return;
    // this is mostly undesired
    // this will calculate all the bones, when only leaf nodes are needed
    calculate(frameInfo, m_pArmature->getBones(), elapsed);

}
//------------------------------------------------------------------------------

void gfx::anim::CBoneAnimation::calculate(SAnimationFrameInfo& frameInfo,
                                          const BonesVec& bones,
                                          float elapsed) {
    if(!m_pArmature) {
        // nothing to do!
        return;
    }

    // time scale? elapsed is in seconds...
    const float currentTime = math::mod(elapsed*1000.0f, getDurationInMs());
    frameInfo.elapsed = (currentTime / getDurationInMs()) * getDurationInTicks();

    //CArmature::BonesVec const& bones = m_pArmature->getBones();
    const unsigned int nBones = bones.size();
    if(!nBones) {
        frameInfo.transformations.clear();
        return;
    }
    frameInfo.transformations.reserve(nBones);
    frameInfo.transformations.resize(nBones);    
    // frameInfo.transformations contains final bone matrices;
    // this vector will hold node transformation matrices #LOCK
    if(m_intermediate.capacity() < nBones)
        m_intermediate.reserve(m_pArmature->count());
    m_intermediate.resize(m_pArmature->count());
    for(unsigned int i = 0; i < m_intermediate.size(); i++) {
        m_intermediate[i] = m_pArmature->getBones()[i]->bindPoseMatrix;        
    }    
    ChannelsVec& channels = getChannels();
    const unsigned int nChannels = count();
    for(unsigned int i = 0; i < nChannels; i++) {
        SAnimationChannel& channel = channels[i];
        SBone* pBone = m_pArmature->get(channel.targetName);
        if(!pBone)
            continue;
        if(shouldInterpolate()) {
            channel.getMatrixInterpolated(m_intermediate[pBone->index],
                                          frameInfo.elapsed);
        } else {
            channel.getMatrix(m_intermediate[pBone->index],
                              frameInfo.elapsed);
        }
    }

    for(unsigned int i = 0; i < nBones; i++) {
        SBone* pBone = bones[i];
        // start with the mesh-to-bone matrix
        frameInfo.transformations[i] = pBone->offset;

        const SBone* pTmp = pBone;
        // append all node transformations down the parent chain
        // until we're back at mesh coordinates again
        while(pTmp) {
            frameInfo.transformations[i] = m_intermediate[pTmp->index] * frameInfo.transformations[i];
            pTmp = pTmp->pParent;
        }
    }
}
//------------------------------------------------------------------------------