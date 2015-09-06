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

using namespace fg;
//------------------------------------------------------------------------------

gfx::anim::SBone::SBone() :
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
    for(unsigned int i = 0;i<n;i++) {
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
