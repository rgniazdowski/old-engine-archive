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

namespace fg {
    namespace gfx {
        namespace anim {
            const BoneType g_BoneTypes[] = {
                                            BONE_INVALID,

                                            BONE_HEAD,
                                            BONE_NECK,

                                            BONE_ARM_LEFT,
                                            BONE_ARM_RIGHT,

                                            BONE_FOREARM_LEFT,
                                            BONE_FOREARM_RIGHT,

                                            BONE_HAND_LEFT,
                                            BONE_HAND_RIGHT,

                                            BONE_HAND_LEFT_THUMB,
                                            BONE_HAND_LEFT_FINGER2,
                                            BONE_HAND_LEFT_FINGER3,
                                            BONE_HAND_LEFT_FINGER4,
                                            BONE_HAND_LEFT_FINGER5,

                                            BONE_HAND_RIGHT_THUMB,
                                            BONE_HAND_RIGHT_FINGER2,
                                            BONE_HAND_RIGHT_FINGER3,
                                            BONE_HAND_RIGHT_FINGER4,
                                            BONE_HAND_RIGHT_FINGER5,

                                            BONE_SPINE,
                                            BONE_PELVIS,
                                            BONE_THIGH_LEFT,
                                            BONE_THIGH_RIGHT,
                                            BONE_LEG_LEFT,
                                            BONE_LEG_RIGHT,
                                            BONE_FOOT_LEFT,
                                            BONE_FOOT_RIGHT,

                                            BONE_FOOT_LEFT_TOE_BIG,
                                            BONE_FOOT_LEFT_TOE2,
                                            BONE_FOOT_LEFT_TOE3,
                                            BONE_FOOT_LEFT_TOE4,
                                            BONE_FOOT_LEFT_TOE5,

                                            BONE_FOOT_RIGHT_TOE_BIG,
                                            BONE_FOOT_RIGHT_TOE2,
                                            BONE_FOOT_RIGHT_TOE3,
                                            BONE_FOOT_RIGHT_TOE4,
                                            BONE_FOOT_RIGHT_TOE5,

                                            BONE_FACE_EXTRA,
                                            BONE_BACK_EXTRA,
                                            BONE_FRONT_EXTRA,
                                            BONE_LEFT_EXTRA,
                                            BONE_RIGHT_EXTRA,
                                            BONE_UP_EXTRA,
                                            BONE_DOWN_EXTRA,
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
        return BONE_INVALID;
    return getBoneTypeFromText(text.c_str());
}
//------------------------------------------------------------------------------

gfx::anim::BoneType gfx::anim::getBoneTypeFromText(const char* text) {
    if(!text)
        return BONE_INVALID;
    const unsigned int n = sizeof (g_BoneTypes) / sizeof (BoneType);
    BoneType result = BONE_INVALID;
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
    if(boneType == BONE_INVALID)
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
mType(BONE_INVALID),
name(),
pParent(NULL),
parentIdx(-1),
index(0),
bindPoseMatrix(),
offset(),
weights(),
children() {
    weights.reserve(8);
    children.reserve(2);
}
//------------------------------------------------------------------------------

gfx::anim::SBone::SBone(const SBone& orig) {
    name.append(orig.name);
    pParent = orig.pParent;
    parentIdx = orig.parentIdx;
    index = orig.index;
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
