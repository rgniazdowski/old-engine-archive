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
#if 0
int gfx::anim::getBonesForStandardAction(StandardActionType action,
                                         CVector<BoneType>& boneTypes) {
    if(action == ACTION_NONE)
        return 0;
    boneTypes.clear();

    if(action == ACTION_IDLE) {
    } else if(action == ACTION_ATTACK) {
        boneTypes.push_back(BoneType::BONE_ARM_LEFT);
        boneTypes.push_back(BoneType::BONE_ARM_RIGHT);
        boneTypes.push_back(BoneType::BONE_FOREARM_LEFT);
        boneTypes.push_back(BoneType::BONE_FOREARM_RIGHT);
        boneTypes.push_back(BoneType::BONE_HAND_LEFT);
        boneTypes.push_back(BoneType::BONE_HAND_RIGHT);
        boneTypes.push_back(BoneType::BONE_PELVIS);
        boneTypes.push_back(BoneType::BONE_SPINE);
        boneTypes.push_back(BoneType::BONE_NECK);
        boneTypes.push_back(BoneType::BONE_HEAD);
    } else if(action == ACTION_MELEE) {
    } else if(action == ACTION_FIRE) {
    } else if(action == ACTION_RELOAD) {
    } else if(action == ACTION_RUN || action == ACTION_WALK) {
        boneTypes.push_back(BoneType::BONE_THIGH_LEFT);
        boneTypes.push_back(BoneType::BONE_THIGH_RIGHT);
        boneTypes.push_back(BoneType::BONE_LEG_LEFT);
        boneTypes.push_back(BoneType::BONE_LEG_RIGHT);
        boneTypes.push_back(BoneType::BONE_FOOT_LEFT);
        boneTypes.push_back(BoneType::BONE_FOOT_RIGHT);
        boneTypes.push_back(BoneType::BONE_PELVIS);
    } else if(action == ACTION_CROUCH) {

    } else if(action == ACTION_STRAFE_RIGHT || action == ACTION_STRAFE_LEFT) {

    } else if(action == ACTION_LEAN_RIGHT || action == ACTION_LEAN_LEFT) {

    } else if(action == ACTION_GRAB) {
    } else if(action == ACTION_JUMP) {
    } else if(action == ACTION_KICK) {
    } else if(action == ACTION_USE) {

    } else if(action == ACTION_DEATH) {
    }
    return boneTypes.size();
}
//------------------------------------------------------------------------------
#endif
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
    const unsigned int nBones = bones.size();
    if(!nBones) {
        animInfo.curFrame.clear();
        return;
    }
    animInfo.curFrame.resize(nBones);
    if(animInfo.isPaused() || animInfo.isStopped())
        return; // ignore
    animInfo.advanceTime(delta);
    // time scale? elapsed is in seconds...
    const float currentTime = math::mod(animInfo.curFrame.elapsed * 1000.0f, getDurationInMs());
    animInfo.curFrame.index = (currentTime / getDurationInMs()) * getDurationInTicks();

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
        Matrix4f& outMatrix = animInfo.curFrame.transformations[boneIdx];
        // start with the mesh-to-bone matrix
        outMatrix = pBone->offset; // Matrix4f(1.0f); //pBone->offset;
        const SBone* pTmp = pBone;
        // append all node transformations down the parent chain
        // until we're back at mesh coordinates again
        while(pTmp) {
            outMatrix = m_intermediate[pTmp->index] * outMatrix;
            pTmp = pTmp->pParent;
        }
        animInfo.curFrame.dualQuaternions[boneIdx].initializeFrom(outMatrix);
    }
}
//------------------------------------------------------------------------------
