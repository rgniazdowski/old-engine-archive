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
 * File:   fgGfxArmature.cpp
 * Author: vigilant
 * 
 * Created on September 2, 2015, 3:50 PM
 */

#include "fgGfxArmature.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::anim::CArmature::CArmature() : m_bones(), m_bonesMap() {
    m_bones.reserve(24);
}
//------------------------------------------------------------------------------

gfx::anim::CArmature::CArmature(const CArmature& orig) {
    const unsigned int n = orig.m_bones.size();
    m_bones.reserve(n + 1);
    for(unsigned int i = 0; i < n; i++) {
        SBone* pBone = new SBone(*orig.m_bones[i]);
        m_bones.push_back(pBone);
        m_bonesMap.insert(std::make_pair(pBone->name, pBone));
    }
    for(unsigned int i = 0; i < n; i++) {
        m_bones[i]->pParent = m_bones[m_bones[i]->parentIdx];
        m_bones[i]->index = i;
    }
}
//------------------------------------------------------------------------------

gfx::anim::CArmature::~CArmature() {
    clear();
}
//------------------------------------------------------------------------------

gfx::anim::SBone* gfx::anim::CArmature::at(unsigned int index) {
    if(index >= m_bones.size())
        return NULL;
    return m_bones[index];
}
//------------------------------------------------------------------------------

gfx::anim::SBone const* gfx::anim::CArmature::at(unsigned int index) const {
    if(index >= m_bones.size())
        return NULL;
    return m_bones[index];
}
//------------------------------------------------------------------------------

gfx::anim::SBone* gfx::anim::CArmature::get(const char* name) {
    if(!name)
        return NULL;
    if(!name[0])
        return NULL;
    BonesMapItor itor = m_bonesMap.find(std::string(name));
    if(itor != m_bonesMap.end()) {
        return itor->second;
    }
    return NULL;
}
//------------------------------------------------------------------------------

gfx::anim::SBone* gfx::anim::CArmature::get(const std::string& name) {
    if(name.empty())
        return NULL;
    BonesMapItor itor = m_bonesMap.find(name);
    if(itor != m_bonesMap.end()) {
        return itor->second;
    }
    return NULL;
}
//------------------------------------------------------------------------------

fgBool gfx::anim::CArmature::add(const SBone& bone) {
    if(get(bone.name) != NULL) {
        // Such bone already exists
        return FG_FALSE;
    }
    if(bone.name.empty()) {
        // empty name not allowed
        return FG_FALSE;
    }
    SBone* pBone = new SBone(bone);
    m_bones.push_back(pBone);
    const unsigned int n = m_bones.size();
    for(unsigned int i = 0; i < n; i++) {
        m_bones[i]->pParent = m_bones[m_bones[i]->parentIdx];
        m_bones[i]->index = i;
    }
    m_bonesMap.insert(std::make_pair(pBone->name, pBone));
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::anim::CArmature::remove(const char* name) {
    if(!name || isEmpty())
        return FG_FALSE;
    if(!name[0])
        return FG_FALSE;
    return remove(std::string(name));
}
//------------------------------------------------------------------------------

fgBool gfx::anim::CArmature::remove(const std::string& name) {
    if(name.empty() || isEmpty())
        return FG_FALSE;
    fgBool status = FG_TRUE;
    BonesMapItor itor = m_bonesMap.find(name);
    if(itor != m_bonesMap.end()) {
        m_bonesMap.erase(itor);
    }
    unsigned int n = m_bones.size();
    for(unsigned int i = 0;i<n;i++) {
        if(m_bones[i]->name.compare(name) == 0) {
            delete m_bones[i];
            m_bones[i] = NULL;
            m_bones.remove(i, n);
            status = FG_TRUE;
            continue;
        }
    }
    return status;
}
//------------------------------------------------------------------------------

void gfx::anim::CArmature::clear(void) {
    m_bonesMap.clear();
    const unsigned int n = m_bones.size();
    for(unsigned int i = 0; i < n; i++) {
        if(m_bones[i])
            delete m_bones[i];
        m_bones[i] = NULL;
    }
    m_bones.clear();
}
//------------------------------------------------------------------------------
