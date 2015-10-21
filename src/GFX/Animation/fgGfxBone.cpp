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
 * File:   fgGfxBone.cpp
 * Author: vigilant
 * 
 * Created on September 2, 2015, 3:52 PM
 */

#include <stack>
#include "fgGfxBone.h"
#include "fgVector.h"
#include "Util/fgStrings.h"
#include "Math/fgDualQuaternion.h"

namespace fg {
    namespace gfx {
        namespace anim {
            const BoneType g_BoneTypes[] = {
                                            BoneType::BONE_INVALID,

                                            BoneType::BONE_HEAD,
                                            BoneType::BONE_NECK,

                                            BoneType::BONE_ARM_LEFT,
                                            BoneType::BONE_ARM_RIGHT,

                                            BoneType::BONE_FOREARM_LEFT,
                                            BoneType::BONE_FOREARM_RIGHT,

                                            BoneType::BONE_HAND_LEFT,
                                            BoneType::BONE_HAND_RIGHT,

                                            BoneType::BONE_HAND_LEFT_THUMB,
                                            BoneType::BONE_HAND_LEFT_FINGER2,
                                            BoneType::BONE_HAND_LEFT_FINGER3,
                                            BoneType::BONE_HAND_LEFT_FINGER4,
                                            BoneType::BONE_HAND_LEFT_FINGER5,

                                            BoneType::BONE_HAND_RIGHT_THUMB,
                                            BoneType::BONE_HAND_RIGHT_FINGER2,
                                            BoneType::BONE_HAND_RIGHT_FINGER3,
                                            BoneType::BONE_HAND_RIGHT_FINGER4,
                                            BoneType::BONE_HAND_RIGHT_FINGER5,

                                            BoneType::BONE_SPINE,
                                            BoneType::BONE_PELVIS,
                                            BoneType::BONE_THIGH_LEFT,
                                            BoneType::BONE_THIGH_RIGHT,
                                            BoneType::BONE_LEG_LEFT,
                                            BoneType::BONE_LEG_RIGHT,
                                            BoneType::BONE_FOOT_LEFT,
                                            BoneType::BONE_FOOT_RIGHT,

                                            BoneType::BONE_FOOT_LEFT_TOE_BIG,
                                            BoneType::BONE_FOOT_LEFT_TOE2,
                                            BoneType::BONE_FOOT_LEFT_TOE3,
                                            BoneType::BONE_FOOT_LEFT_TOE4,
                                            BoneType::BONE_FOOT_LEFT_TOE5,

                                            BoneType::BONE_FOOT_RIGHT_TOE_BIG,
                                            BoneType::BONE_FOOT_RIGHT_TOE2,
                                            BoneType::BONE_FOOT_RIGHT_TOE3,
                                            BoneType::BONE_FOOT_RIGHT_TOE4,
                                            BoneType::BONE_FOOT_RIGHT_TOE5,

                                            BoneType::BONE_FACE_EXTRA,
                                            BoneType::BONE_BACK_EXTRA,
                                            BoneType::BONE_FRONT_EXTRA,
                                            BoneType::BONE_LEFT_EXTRA,
                                            BoneType::BONE_RIGHT_EXTRA,
                                            BoneType::BONE_UP_EXTRA,
                                            BoneType::BONE_DOWN_EXTRA,
            };
            const char * const g_BoneTypesText[] = {
                                                    "INVALID",

                                                    "HEAD",
                                                    "NECK",

                                                    "ARM_LEFT",
                                                    "ARM_RIGHT",

                                                    "FOREARM_LEFT",
                                                    "FOREARM_RIGHT",

                                                    "HAND_LEFT",
                                                    "HAND_RIGHT",

                                                    "HAND_LEFT_THUMB",
                                                    "HAND_LEFT_FINGER2",
                                                    "HAND_LEFT_FINGER3",
                                                    "HAND_LEFT_FINGER4",
                                                    "HAND_LEFT_FINGER5",

                                                    "HAND_RIGHT_THUMB",
                                                    "HAND_RIGHT_FINGER2",
                                                    "HAND_RIGHT_FINGER3",
                                                    "HAND_RIGHT_FINGER4",
                                                    "HAND_RIGHT_FINGER5",

                                                    "SPINE",
                                                    "PELVIS",
                                                    "THIGH_LEFT",
                                                    "THIGH_RIGHT",
                                                    "LEG_LEFT",
                                                    "LEG_RIGHT",
                                                    "FOOT_LEFT",
                                                    "FOOT_RIGHT",

                                                    "FOOT_LEFT_TOE_BIG",
                                                    "FOOT_LEFT_TOE2",
                                                    "FOOT_LEFT_TOE3",
                                                    "FOOT_LEFT_TOE4",
                                                    "FOOT_LEFT_TOE5",

                                                    "FOOT_RIGHT_TOE_BIG",
                                                    "FOOT_RIGHT_TOE2",
                                                    "FOOT_RIGHT_TOE3",
                                                    "FOOT_RIGHT_TOE4",
                                                    "FOOT_RIGHT_TOE5",

                                                    "FACE_EXTRA",
                                                    "BACK_EXTRA",
                                                    "FRONT_EXTRA",
                                                    "LEFT_EXTRA",
                                                    "RIGHT_EXTRA",
                                                    "UP_EXTRA",
                                                    "DOWN_EXTRA",
            };
        }
    }
}

using namespace fg;
//------------------------------------------------------------------------------

gfx::anim::BoneType gfx::anim::getBoneTypeFromText(const std::string& text) {
    if(text.empty())
        return BoneType::BONE_INVALID;
    return getBoneTypeFromText(text.c_str());
}
//------------------------------------------------------------------------------

gfx::anim::BoneType gfx::anim::getBoneTypeFromText(const char* text) {
    if(!text)
        return BoneType::BONE_INVALID;
    const unsigned int n = sizeof (g_BoneTypes) / sizeof (BoneType);
    BoneType result = BoneType::BONE_INVALID;
    for(unsigned int i = 0; i < n; i++) {
        if(strings::isEqual(text, g_BoneTypesText[i], FG_FALSE)) {
            result = g_BoneTypes[i];
            break;
        }
    }
    return result;
}
//------------------------------------------------------------------------------

const char* gfx::anim::getTextFromBoneType(BoneType boneType) {
    if(boneType == BoneType::BONE_INVALID)
        return NULL;
    const unsigned int n = sizeof (g_BoneTypes) / sizeof (BoneType);
    const char* result = NULL;
    for(unsigned int i = 0; i < n; i++) {
        if(boneType == g_BoneTypes[i]) {
            result = g_BoneTypesText[i];
            break;
        }
    }
    return result;
}
//------------------------------------------------------------------------------

gfx::anim::SBone::SBone() :
base_type(),
pParent(NULL),
bindPoseMatrix(),
offset(),
weights(),
children() {
    weights.reserve(8);
    children.reserve(2);
}
//------------------------------------------------------------------------------

gfx::anim::SBone::SBone(const self_type& orig) : base_type(orig) {
    pParent = orig.pParent;
    bindPoseMatrix = orig.bindPoseMatrix;
    offset = orig.offset;
    weights.append(orig.weights);
}
//------------------------------------------------------------------------------

gfx::anim::SBone::~SBone() {
    if(pParent) {
        int index = pParent->children.find(this);
        if(index >= 0)
            pParent->children[index] = NULL;
    }
    // this node is being removed
    // need to nullify pointers to parent for every child
    const unsigned int n = children.size();
    for(unsigned int i = 0; i < n; i++) {
        if(children[i] == NULL)
            continue;
        children[i]->pParent = NULL;
        children[i]->parentIdx = -1;
    }
    //destroyChildren();
    clear();
    children.clear();
}
//------------------------------------------------------------------------------

void gfx::anim::SBone::clear(void) {
    name.clear();
    offset = Matrix4f();
    pParent = NULL;
    parentIdx = -1;
    bindPoseMatrix = Matrix4f();
    offset = Matrix4f();
    weights.clear();
}
//------------------------------------------------------------------------------

void gfx::anim::SBone::destroyChildren(void) {
    const unsigned int n = children.size();
    for(unsigned int i = 0; i < n; i++) {
        SBone* pBone = children[i];
        if(!pBone)
            continue;
        delete pBone;
        pBone = NULL;
    }
    children.clear();
}
//------------------------------------------------------------------------------

gfx::anim::SBone* gfx::anim::SBone::findBone(const std::string& name) {
    if(name.empty())
        return NULL;
    return findBone(name.c_str());
}
//------------------------------------------------------------------------------

gfx::anim::SBone* gfx::anim::SBone::findBone(const char* name) {
    if(!name)
        return NULL;
    if(!name[0])
        return NULL;
    SBone* pBone = NULL;
    std::stack<SBone* > stack;
    stack.push(this);
    while(!stack.empty()) {
        pBone = stack.top();
        stack.pop();
        if(!pBone)
            continue;
        if(pBone->name.compare(name) == 0) {
            break;
        }
        const unsigned int n = pBone->children.size();
        for(unsigned int i = 0; i < n; i++) {
            stack.push(pBone->children[i]);
        }
    }
    return pBone;
}
//------------------------------------------------------------------------------

fgBool gfx::anim::SBone::hasChild(SBone* pBone) {
    if(!pBone)
        return FG_FALSE;
    return (fgBool)children.contains(pBone);
}
//------------------------------------------------------------------------------

fgBool gfx::anim::SBone::hasChild(const std::string& name) {
    if(name.empty())
        return FG_FALSE;
    return hasChild(name.c_str());
}
//------------------------------------------------------------------------------

fgBool gfx::anim::SBone::hasChild(const char* name) {
    if(!name)
        return FG_FALSE;
    if(!name[0])
        return FG_FALSE;
    fgBool status = FG_FALSE;
    const unsigned int n = children.size();
    for(unsigned int i = 0; i < n; i++) {
        SBone* pBone = children[i];
        if(!pBone)
            continue;
        if(pBone->name.compare(name) == 0) {
            status = FG_TRUE;
            break;
        }
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::anim::SBone::removeChild(SBone* pBone) {
    if(!pBone)
        return FG_FALSE;
    fgBool status = FG_FALSE;
    int index = children.find(pBone);
    if(index >= 0)
        children.remove(index);
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::anim::SBone::removeChild(const std::string& name) {
    if(name.empty())
        return FG_FALSE;
    return removeChild(name.c_str());
}
//------------------------------------------------------------------------------

fgBool gfx::anim::SBone::removeChild(const char* name) {
    if(!name)
        return FG_FALSE;
    if(!name[0])
        return FG_FALSE;
    SBone* pBone = findBone(name);
    if(!pBone)
        return FG_FALSE;
    return removeChild(pBone);
}
//------------------------------------------------------------------------------

void gfx::anim::SBone::getFinalBindPose(Matrix4f& outMatrix) const {
    outMatrix = Matrix4f(1.0f);
    //outMatrix = this->offset;
    const SBone* pTmp = this;
    // append all node transformations down the parent chain
    // until we're back at mesh coordinates again
    while(pTmp) {
        outMatrix = pTmp->bindPoseMatrix * outMatrix;
        pTmp = pTmp->pParent;
    }
}
//------------------------------------------------------------------------------

Vector3f gfx::anim::SBone::getOffsetScale(void) const {
    Vector3f result;
    getOffsetScale(result);
    return result;
}
//------------------------------------------------------------------------------

void gfx::anim::SBone::getOffsetScale(Vector3f& outScale) const {
    outScale.x = math::length(this->offset[0]);
    outScale.y = math::length(this->offset[1]);
    outScale.z = math::length(this->offset[2]);
}
//------------------------------------------------------------------------------

void gfx::anim::SBone::getFinalBindPose(DualQuaternionf& outDQuat) const {
    Matrix4f matrix;
    getFinalBindPose(matrix);
    outDQuat.initializeFrom(matrix);
}
//------------------------------------------------------------------------------

void gfx::anim::SBone::getDirectionFromParent(Vector3f& direction) const {
    if(isFirstChild()) {
        direction = Vec3f(0.0f, pParent->length, 0.0f);
    } else if(pParent) {
        //direction = (this->startPoint - pParent->startPoint);
        //direction = (pParent->startPoint - this->endPoint);
        //direction = this->endPoint - pParent->startPoint;
        //direction.y -= this->length;
        direction = this->startPoint - pParent->endPoint;
        direction.y += pParent->length;
    } else {
        direction = Vec3f();
    }
}
//------------------------------------------------------------------------------

Vector3f gfx::anim::SBone::getDirectionFromParent(void) const {
    Vector3f direction;
    getDirectionFromParent(direction);
    return direction;
}
//------------------------------------------------------------------------------

void gfx::anim::SBone::refreshLength(void) {
    if(this->children.empty())
        return;
    // first child needed
    Vec4f position4f;
    Matrix4f finalBindPoseMat, finalRestPoseMat;
    Vec3f matScale;
    getOffsetScale(matScale);
    // better boneBox goes here
    this->children[0]->getFinalBindPose(finalBindPoseMat);
    position4f = finalBindPoseMat * Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
    this->endPoint = Vec3f(position4f); // * matScale;

    this->getFinalBindPose(finalBindPoseMat);
    position4f = finalBindPoseMat * Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
    this->startPoint = Vec3f(position4f); // * matScale;
    // have start and end point
    // get length?    
    this->length = math::abs(math::length(this->startPoint - this->endPoint));

    this->getFinalRestPose(finalRestPoseMat);
    position4f = finalRestPoseMat * Vec4f(0.0f, 0.0f, 0.0f, 1.0f);
    this->startPoint = Vec3f(position4f);
    position4f = finalRestPoseMat * Vec4f(0.0f, this->length * matScale.y, 0.0f, 1.0f);
    this->endPoint = Vec3f(position4f);
    finalRestPoseMat = math::scale(finalRestPoseMat, matScale);
    rotDir = math::toQuat(finalRestPoseMat); // rotation in inverse offset
    angles = math::eulerAngles(rotDir);
    this->rotation = rotDir; // #IMPORTANT! - using inverse bone offset rotation (matrix scaled to 1.0f)
    this->angles = angles; // #IMPORTANT!
}
//------------------------------------------------------------------------------

fgBool gfx::anim::SBone::hasLength(void) const {
    if(this->length < FG_EPSILON)
        return FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------