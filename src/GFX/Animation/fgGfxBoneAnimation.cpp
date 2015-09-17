/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written permission from the author.
 ******************************************************************************/
/* 
 * File:   fgGfxBoneAnimation.cpp
 * Author: vigilant
 * 
 * Created on September 2, 2015, 5:40 PM
 */

#include "fgGfxBoneAnimation.h"
#include "fgGfxAnimationInfo.h"
#include "fgGfxArmature.h"
#include "Util/fgStrings.h"
#include "Util/fgTime.h"

namespace fg {
    namespace gfx {
        namespace anim {
            const StandardActionType g_StandardActionTypes[] = {
                                                                ACTION_NONE,
                                                                ACTION_IDLE,
                                                                ACTION_ATTACK,
                                                                ACTION_MELEE,
                                                                ACTION_FIRE,
                                                                ACTION_RELOAD,
                                                                ACTION_RUN,
                                                                ACTION_WALK,
                                                                ACTION_CROUCH,

                                                                ACTION_STRAFE_LEFT,
                                                                ACTION_STRAFE_RIGHT,

                                                                ACTION_LEAN_LEFT,
                                                                ACTION_LEAN_RIGHT,

                                                                ACTION_GRAB,
                                                                ACTION_JUMP,
                                                                ACTION_KICK,
                                                                ACTION_USE,

                                                                ACTION_DEATH,

                                                                ACTION_OTHER
            };

            const char * const g_StandardActionTypesText[] = {
                                                              "none",
                                                              "idle",
                                                              "attack",
                                                              "melee",
                                                              "fire",
                                                              "reload",
                                                              "run",
                                                              "walk",
                                                              "crouch",

                                                              "strafe_left",
                                                              "strafe_right",

                                                              "lean_left",
                                                              "lean_right",

                                                              "grab",
                                                              "jump",
                                                              "kick",
                                                              "use",

                                                              "death",
                                                              "other"
            };
        }
    }
}

using namespace fg;
//------------------------------------------------------------------------------

gfx::anim::StandardActionType gfx::anim::getActionTypeFromText(const std::string& text) {
    if(text.empty())
        return ACTION_NONE;
    return getActionTypeFromText(text.c_str());
}
//------------------------------------------------------------------------------

gfx::anim::StandardActionType gfx::anim::getActionTypeFromText(const char* text) {
    if(!text)
        return ACTION_NONE;
    StandardActionType result = ACTION_NONE;
    const unsigned int n = sizeof (g_StandardActionTypes) / sizeof (StandardActionType);
    for(unsigned int i = 0; i < n; i++) {
        if(strings::isEqual(text, g_StandardActionTypesText[i], FG_FALSE)) {
            result = g_StandardActionTypes[i];
            break;
        }
    }
    return result;

}
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

void gfx::anim::CBoneAnimation::calculate(SAnimationInfo& animationInfo,
                                          float delta) {
    if(!m_pArmature)
        return;
    // this is mostly undesired
    // this will calculate all the bones
    // calculate(frameInfo, m_pArmature->getBones(), elapsed);

    // For bone animation one should not call base version of calculate()
    // Need to use it with only subset of all bones
}
//------------------------------------------------------------------------------

void gfx::anim::CBoneAnimation::calculate(SAnimationInfo& animInfo,
                                          const BonesVec& bones,
                                          float delta) {
    if(!m_pArmature) {
        // nothing to do!
        return;
    }
    animInfo.advanceTime(delta);
    // time scale? elapsed is in seconds...
    const float currentTime = math::mod(animInfo.curFrame.elapsed * 1000.0f, getDurationInMs());
    animInfo.curFrame.index = (currentTime / getDurationInMs()) * getDurationInTicks();

    //CArmature::BonesVec const& bones = m_pArmature->getBones();
    const unsigned int nBones = bones.size();
    if(!nBones) {
        animInfo.curFrame.clear();
        return;
    }
    animInfo.curFrame.resize(nBones);
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
                                          animInfo.curFrame.index);
        } else {
            channel.getMatrix(m_intermediate[pBone->index],
                              animInfo.curFrame.index);
        }
    }
    for(unsigned int boneIdx = 0; boneIdx < nBones; boneIdx++) {
        SBone* pBone = bones[boneIdx];
        // start with the mesh-to-bone matrix
        animInfo.curFrame.transformations[boneIdx] = pBone->offset;
        const SBone* pTmp = pBone;
        // append all node transformations down the parent chain
        // until we're back at mesh coordinates again
        while(pTmp) {
            animInfo.curFrame.transformations[boneIdx] =
                    m_intermediate[pTmp->index] *
                    animInfo.curFrame.transformations[boneIdx];
            pTmp = pTmp->pParent;
        }
        //frameInfo.transformations[i] = Matrix4f();
        // now frameInfo contains proper matrix transformations
        // these matrices are not optimal (4x4 is too big)
        // convert mat4 to dual quaternion
        animInfo.curFrame.dualQuaternions[boneIdx].initializeFrom(animInfo.curFrame.transformations[boneIdx]);
    }
}
//------------------------------------------------------------------------------