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

gfx::anim::CAnimation* gfx::traits::CAnimated::getAnimation(const std::string& name,
                                                            strings::MatchMode mode) {
    if(name.empty())
        return NULL;
    return getAnimation(name.c_str(), mode);
}
//------------------------------------------------------------------------------

gfx::anim::CAnimation* gfx::traits::CAnimated::getAnimation(const char* name,
                                                            strings::MatchMode mode) {
    if(!name)
        return NULL;
    if(!name[0])
        return NULL;
    anim::CAnimation* pAnimation = NULL;
    const unsigned int n = m_animations.size();
    for(unsigned int i = 0; i < n; i++) {
        if(strings::doesMatch(m_animations[i].pAnimation->getNameStr(), name, mode)) {
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

gfx::anim::SAnimationInfo* gfx::traits::CAnimated::getAnimationInfo(const std::string& name,
                                                                    strings::MatchMode mode) {
    if(name.empty())
        return NULL;
    return getAnimationInfo(name.c_str(), mode);
}
//------------------------------------------------------------------------------

gfx::anim::SAnimationInfo* gfx::traits::CAnimated::getAnimationInfo(const char* name,
                                                                    strings::MatchMode mode) {
    if(!name)
        return NULL;
    if(!name[0])
        return NULL;
    anim::SAnimationInfo* pAnimationInfo = NULL;
    const unsigned int n = m_animations.size();
    for(unsigned int i = 0; i < n; i++) {
        if(strings::doesMatch(m_animations[i].pAnimation->getNameStr(), name, mode)) {
            pAnimationInfo = &m_animations[i];
            break;
        }
    }
    return pAnimationInfo;
}
//------------------------------------------------------------------------------

gfx::anim::SAnimationInfo* gfx::traits::CAnimated::getAnimationInfo(const std::string& name,
                                                                    const std::string& mode) {
    if(name.empty())
        return NULL;
    const strings::MatchMode modeEnum = strings::getMatchModeFromText(mode);
    return getAnimationInfo(name.c_str(), modeEnum);
}
//------------------------------------------------------------------------------

gfx::anim::SAnimationInfo* gfx::traits::CAnimated::getAnimationInfo(const char* name,
                                                                    const char* mode) {
    if(!name)
        return NULL;
    const strings::MatchMode modeEnum = strings::getMatchModeFromText(mode);
    return getAnimationInfo(name, modeEnum);
}
//------------------------------------------------------------------------------

gfx::anim::SAnimationInfo* gfx::traits::CAnimated::getAnimationInfoBySlot(unsigned int slot) {
    if(slot >= m_animations.size())
        return NULL;
    return &m_animations[slot];
}
//------------------------------------------------------------------------------

int gfx::traits::CAnimated::getAnimationSlot(anim::CAnimation* pAnimation) {
    if(!pAnimation)
        return -1;
    int slot = -1;
    const unsigned int n = m_animations.size();
    for(unsigned int i = 0; i < n; i++) {
        if(m_animations[i].pAnimation == pAnimation) {
            slot = (int)i;
            break;
        }
    }
    return slot;
}
//------------------------------------------------------------------------------

int gfx::traits::CAnimated::getAnimationSlot(const std::string& name,
                                             strings::MatchMode mode) {
    if(name.empty())
        return -1;
    return getAnimationSlot(name.c_str(), mode);
}
//------------------------------------------------------------------------------

int gfx::traits::CAnimated::getAnimationSlot(const char* name,
                                             strings::MatchMode mode) {
    if(!name)
        return -1;
    if(!name[0])
        return -1;
    int slot = -1;
    const unsigned int n = m_animations.size();
    for(unsigned int i = 0; i < n; i++) {
        if(strings::doesMatch(m_animations[i].pAnimation->getNameStr(), name, mode)) {
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

fgBool gfx::traits::CAnimated::hasAnimation(const std::string& name,
                                            strings::MatchMode mode) {
    if(name.empty())
        return FG_FALSE;

    return hasAnimation(name.c_str(), mode);
}
//------------------------------------------------------------------------------

fgBool gfx::traits::CAnimated::hasAnimation(const char* name,
                                            strings::MatchMode mode) {
    if(!name)
        return FG_FALSE;
    if(!name[0])
        return FG_FALSE;
    fgBool found = FG_FALSE;
    const unsigned int n = m_animations.size();
    for(unsigned int i = 0; i < n; i++) {
        if(strings::doesMatch(m_animations[i].pAnimation->getNameStr(), name, mode)) {
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
    int index = getAnimationSlot(pAnimation);
    if(index >= 0) {
        m_animations[index].stop();
        m_animations.remove(index);
    }
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::removeAnimation(const std::string& name,
                                             strings::MatchMode mode) {
    if(name.empty())
        return;
    removeAnimation(name.c_str(), mode);
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::removeAnimation(const char* name,
                                             strings::MatchMode mode) {
    if(!name)
        return;
    if(!name[0])
        return;
    int index = getAnimationSlot(name, mode);
    if(index >= 0) {
        m_animations[index].stop();
        m_animations.remove(index);
    }
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::removeAnimation(const std::string& name,
                                             const std::string& mode) {
    if(name.empty())
        return;
    const strings::MatchMode modeEnum = strings::getMatchModeFromText(mode);
    removeAnimation(name.c_str(), modeEnum);
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::removeAnimation(const char* name, const char* mode) {
    if(!name)
        return;
    const strings::MatchMode modeEnum = strings::getMatchModeFromText(mode);
    removeAnimation(name, modeEnum);
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::removeAnimations(void) {
    stopAnimations();
    m_animations.clear();
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::playAnimations(void) {
    const unsigned int n = getAnimationsCount();
    for(unsigned int i = 0; i < n; i++) {
        anim::SAnimationInfo* pInfo = getAnimationInfoBySlot(i);
        if(pInfo)
            pInfo->play();
    }
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::stopAnimations(void) {
    const unsigned int n = getAnimationsCount();
    for(unsigned int i = 0; i < n; i++) {
        anim::SAnimationInfo* pInfo = getAnimationInfoBySlot(i);
        if(pInfo)
            pInfo->stop();
    }
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::pauseAnimations(fgBool toggle) {
    const unsigned int n = getAnimationsCount();
    for(unsigned int i = 0; i < n; i++) {
        anim::SAnimationInfo* pInfo = getAnimationInfoBySlot(i);
        if(pInfo) {
            if(toggle)
                pInfo->togglePause();
            else
                pInfo->pause();
        }
    }
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::resumeAnimations(void) {
    const unsigned int n = getAnimationsCount();
    for(unsigned int i = 0; i < n; i++) {
        anim::SAnimationInfo* pInfo = getAnimationInfoBySlot(i);
        if(pInfo)
            pInfo->resume();
    }
}
//------------------------------------------------------------------------------

void gfx::traits::CAnimated::rewindAnimations(void) {
    const unsigned int n = getAnimationsCount();
    for(unsigned int i = 0; i < n; i++) {
        anim::SAnimationInfo* pInfo = getAnimationInfoBySlot(i);
        if(pInfo)
            pInfo->rewind();
    }
}
//------------------------------------------------------------------------------
