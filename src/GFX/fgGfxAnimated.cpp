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
 * File:   fgGfxAnimated.cpp
 * Author: vigilant
 *
 * Created on September 9, 2015, 13:02 PM
 */

#include "fgGfxAnimated.h"
#include "GFX/Animation/fgGfxAnimation.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::traits::CAnimated::CAnimated() : m_animations() { }
//------------------------------------------------------------------------------

fgBool gfx::traits::CAnimated::setAnimation(anim::CAnimation* pAnimation, unsigned int slot) {
    if(!pAnimation)
        return FG_FALSE;
    if(m_animations.capacity() <= slot)
        m_animations.reserve(slot + 1);
    m_animations.resize(slot + 1);

    if(m_animations[slot].pAnimation == pAnimation) {
        return FG_TRUE;
    } else {
        m_animations[slot].clear();
        m_animations[slot].pAnimation = pAnimation;
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::traits::CAnimated::setAnimation(anim::SAnimationInfo* pAnimationInfo, unsigned int slot) {
    if(!pAnimationInfo)
        return FG_FALSE;
    if(!pAnimationInfo->pAnimation)
        return FG_FALSE;
    if(m_animations.capacity() <= slot)
        m_animations.reserve(slot + 1);
    m_animations.resize(slot + 1);

    // copy everything
    m_animations[slot] = *pAnimationInfo;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

int gfx::traits::CAnimated::pushAnimation(anim::CAnimation* pAnimation) {
    if(!pAnimation)
        return -1;
    if(hasAnimation(pAnimation))
        return -1;

    m_animations.push_back(anim::SAnimationInfo(pAnimation));
    return m_animations.size() - 1; // current slot
}
//------------------------------------------------------------------------------

int gfx::traits::CAnimated::pushAnimation(anim::SAnimationInfo* pAnimationInfo) {
    if(!pAnimationInfo)
        return -1;
    if(!pAnimationInfo->pAnimation)
        return -1;
    if(hasAnimation(pAnimationInfo->pAnimation))
        return -1;

    m_animations.push_back(*pAnimationInfo);
    return m_animations.size() - 1;
}
//------------------------------------------------------------------------------

gfx::anim::CAnimation* gfx::traits::CAnimated::getAnimation(const std::string& name) {
    if(name.empty())
        return NULL;
    return getAnimation(name.c_str());
}
//------------------------------------------------------------------------------

gfx::anim::CAnimation* gfx::traits::CAnimated::getAnimation(const char* name) {
    if(!name)
        return NULL;
    if(!name[0])
        return NULL;
    anim::CAnimation* pAnimation = NULL;
    const unsigned int n = m_animations.size();
    for(unsigned int i = 0; i < n; i++) {
        if(m_animations[i].pAnimation->getName().compare(name) == 0) {
            pAnimation = m_animations[i].pAnimation;
            break;
        }
    }
    return pAnimation;
}
//------------------------------------------------------------------------------

gfx::anim::CAnimation* gfx::traits::CAnimated::getAnimation(unsigned int slot) {
    if(slot >= m_animations.size())
        return NULL;
    return m_animations[slot].pAnimation;
}
//------------------------------------------------------------------------------

gfx::anim::SAnimationInfo* gfx::traits::CAnimated::getAnimationInfo(anim::CAnimation* pAnimation) {
    if(!pAnimation)
        return NULL;
    const unsigned int n = m_animations.size();
    for(unsigned int i = 0; i < n; i++) {
        if(m_animations[i].pAnimation == pAnimation) {
            return &m_animations[i];
        }
    }
    return NULL;
}
//------------------------------------------------------------------------------

gfx::anim::SAnimationInfo* gfx::traits::CAnimated::getAnimationInfo(const std::string& name) {
    if(name.empty())
        return NULL;
    return getAnimationInfo(name.c_str());
}
//------------------------------------------------------------------------------

gfx::anim::SAnimationInfo* gfx::traits::CAnimated::getAnimationInfo(const char* name) {
    if(!name)
        return NULL;
    if(!name[0])
        return NULL;
    anim::SAnimationInfo* pAnimationInfo = NULL;
    const unsigned int n = m_animations.size();
    for(unsigned int i = 0; i < n; i++) {
        if(m_animations[i].pAnimation->getName().compare(name) == 0) {
            pAnimationInfo = &m_animations[i];
            break;
        }
    }
    return pAnimationInfo;
}
//------------------------------------------------------------------------------

gfx::anim::SAnimationInfo* gfx::traits::CAnimated::getAnimationInfo(unsigned int slot) {
    if(slot >= m_animations.size())
        return NULL;
    return &m_animations[slot];
}
//------------------------------------------------------------------------------

int gfx::traits::CAnimated::getAnimationSlot(anim::CAnimation* pAnimation) {
    if(!pAnimation)
        return -1;
    return getAnimationSlot(pAnimation->getNameStr());
}
//------------------------------------------------------------------------------

int gfx::traits::CAnimated::getAnimationSlot(const std::string& name) {
    if(name.empty())
        return -1;
    return getAnimationSlot(name.c_str());
}
//------------------------------------------------------------------------------

int gfx::traits::CAnimated::getAnimationSlot(const char* name) {
    if(!name)
        return -1;
    if(!name[0])
        return -1;
    int slot = -1;
    const unsigned int n = m_animations.size();
    for(unsigned int i = 0; i < n; i++) {
        if(m_animations[i].pAnimation->getName().compare(name) == 0) {
            slot = (int)i;
            break;
        }
    }
    return slot;
}
//------------------------------------------------------------------------------

fgBool gfx::traits::CAnimated::hasAnimation(anim::CAnimation* pAnimation) {
    if(!pAnimation)
        return FG_FALSE;
    fgBool found = FG_FALSE;
    const unsigned int n = m_animations.size();
    for(unsigned int i = 0; i < n; i++) {
        if(m_animations[i].pAnimation == pAnimation) {
            found = FG_TRUE;
            break;
        }
    }
    return found;
}
//------------------------------------------------------------------------------

fgBool gfx::traits::CAnimated::hasAnimation(const std::string& name) {
    if(name.empty())
        return FG_FALSE;

    return hasAnimation(name.c_str());
}
//------------------------------------------------------------------------------

fgBool gfx::traits::CAnimated::hasAnimation(const char* name) {
    if(!name)
        return FG_FALSE;
    if(!name[0])
        return FG_FALSE;
    fgBool found = FG_FALSE;
    const unsigned int n = m_animations.size();
    for(unsigned int i = 0; i < n; i++) {
        if(m_animations[i].pAnimation->getName().compare(name) == 0) {
            found = FG_TRUE;
            break;
        }
    }
    return found;
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::removeAnimation(anim::CAnimation* pAnimation) {
    if(!pAnimation)
        return;
    int index = getAnimationSlot(pAnimation->getNameStr());
    if(index >= 0) {
        m_animations.remove(index);
    }
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::removeAnimation(const std::string& name) {
    if(name.empty())
        return;
    removeAnimation(name.c_str());
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::removeAnimation(const char* name) {
    if(!name)
        return;
    if(!name[0])
        return;
    int index = getAnimationSlot(name);
    if(index >= 0) {
        m_animations.remove(index);
    }
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::pauseAnimation(anim::CAnimation* pAnimation) {
    if(!pAnimation)
        return;
    anim::SAnimationInfo* pInfo = getAnimationInfo(pAnimation);
    if(!pInfo)
        return;
    // TODO
    // pInfo->pause();
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::pauseAnimation(const std::string& name) {
    if(name.empty())
        return;
    pauseAnimation(name.c_str());
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::pauseAnimation(const char* name) {
    if(!name)
        return;
    if(!name[0])
        return;
    anim::SAnimationInfo* pInfo = getAnimationInfo(name);
    if(!pInfo)
        return;
    // TODO
    // pInfo->pause();
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::resumeAnimation(anim::CAnimation* pAnimation) {
    if(!pAnimation)
        return;
    anim::SAnimationInfo* pInfo = getAnimationInfo(pAnimation);
    if(!pInfo)
        return;
    // TODO
    // pInfo->resume();
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::resumeAnimation(const std::string& name) {
    if(name.empty())
        return;
    resumeAnimation(name.c_str());
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::resumeAnimation(const char* name) {
    if(!name)
        return;
    if(!name[0])
        return;
    anim::SAnimationInfo* pInfo = getAnimationInfo(name);
    if(!pInfo)
        return;
    // TODO
    // pInfo->resume();
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::restartAnimation(anim::CAnimation* pAnimation) {
    if(!pAnimation)
        return;
    anim::SAnimationInfo* pInfo = getAnimationInfo(pAnimation);
    if(!pInfo)
        return;
    // TODO
    // pInfo->restart();
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::restartAnimation(const std::string& name) {
    if(name.empty())
        return;
    restartAnimation(name.c_str());
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::restartAnimation(const char* name) {
    if(!name)
        return;
    if(!name[0])
        return;
    anim::SAnimationInfo* pInfo = getAnimationInfo(name);
    if(!pInfo)
        return;
    // TODO
    // pInfo->restart();
}
//------------------------------------------------------------------------------
