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
 * File:   fgGfxAnimation.cpp
 * Author: vigilant
 * 
 * Created on September 2, 2015, 3:47 PM
 */

#include "fgGfxAnimation.h"
#include "fgGfxAnimationInfo.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::anim::CAnimation::CAnimation() :
m_type(Type::INVALID),
m_name(),
m_channels(),
m_duration(0.0f),
m_durationMs(0.0f),
m_durationS(0.0f),
m_ticksPerSecond(0.0f),
m_shouldInterpolate(FG_TRUE) {
    m_channels.reserve(32);
}
//------------------------------------------------------------------------------

gfx::anim::CAnimation::CAnimation(const CAnimation& orig) {
    m_channels.reserve(32);
    m_channels.append(orig.m_channels);
    m_duration = orig.m_duration;
    m_durationS = orig.m_durationS;
    m_durationMs = orig.m_durationMs;
    m_ticksPerSecond = orig.m_ticksPerSecond;
    m_name.append(orig.m_name);
    m_type = Type::INVALID; // ?
    m_shouldInterpolate = orig.m_shouldInterpolate;
}
//------------------------------------------------------------------------------

gfx::anim::CAnimation::~CAnimation() {
    m_name.clear();
    clear();
    m_duration = 0.0f;
    m_durationS = 0.0f;
    m_durationMs = 0.0f;
    m_ticksPerSecond = 0.0f;
}
//------------------------------------------------------------------------------

void gfx::anim::CAnimation::clear(void) {
    m_channels.clear();
}
//------------------------------------------------------------------------------

gfx::anim::SAnimationChannel* gfx::anim::CAnimation::getChannel(const std::string& name) {
    if(name.empty() || isEmpty())
        return NULL;
    SAnimationChannel* pChannel = NULL;
    const unsigned int n = count();
    for(unsigned int i =0;i<n;i++) {
        if(m_channels[i].targetName.compare(name) == 0) {
            pChannel = &m_channels[i];
            break;
        }
    }
    return pChannel;
}
//------------------------------------------------------------------------------

gfx::anim::SAnimationChannel* gfx::anim::CAnimation::getChannel(const char* name) {
    if(!name || isEmpty())
        return NULL;
    SAnimationChannel* pChannel = NULL;
    const unsigned int n = count();
    for(unsigned int i=0;i<n;i++) {
        if(m_channels[i].targetName.compare(name) == 0) {
            pChannel = &m_channels[i];
            break;
        }
    }
    return pChannel;
}
//------------------------------------------------------------------------------

const gfx::anim::SAnimationChannel* gfx::anim::CAnimation::getChannel(const std::string& name) const {
    if(name.empty() || isEmpty())
        return NULL;
    const SAnimationChannel* pChannel = NULL;
    const unsigned int n = count();
    for(unsigned int i =0;i<n;i++) {
        if(m_channels[i].targetName.compare(name) == 0) {
            pChannel = &m_channels[i];
            break;
        }
    }
    return pChannel;
}
//------------------------------------------------------------------------------

const gfx::anim::SAnimationChannel* gfx::anim::CAnimation::getChannel(const char* name) const {
    if(!name || isEmpty())
        return NULL;
    const SAnimationChannel* pChannel = NULL;
    const unsigned int n = count();
    for(unsigned int i=0;i<n;i++) {
        if(m_channels[i].targetName.compare(name) == 0) {
            pChannel = &m_channels[i];
            break;
        }
    }
    return pChannel;
}
//------------------------------------------------------------------------------

fgBool gfx::anim::CAnimation::hasChannel(const std::string& name) const {
    return (fgBool)(getChannel(name) != NULL);
}
//------------------------------------------------------------------------------

fgBool gfx::anim::CAnimation::hasChannel(const char* name) const {
    return (fgBool)(getChannel(name) != NULL);
}
//------------------------------------------------------------------------------

/*fgBool gfx::anim::CAnimation::addChannel(gfx::anim::SAnimationChannel* pChannel) {
    if(!pChannel)
        return FG_FALSE;
    if(pChannel->targetName.empty())
        return FG_FALSE;
    m_channels.push_back(*pChannel);
    return FG_TRUE;
}*/
//------------------------------------------------------------------------------

fgBool gfx::anim::CAnimation::addChannel(const gfx::anim::SAnimationChannel& channel) {
    if(channel.targetName.empty())
        return FG_FALSE;
    m_channels.push_back(channel);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::anim::CAnimation::removeChannel(const std::string& name) {
    if(name.empty() || isEmpty())
        return FG_FALSE;
    unsigned int n = count();
    fgBool status = FG_FALSE;
    for(unsigned int i =0;i<n;i++) {
        if(m_channels[i].targetName.compare(name) == 0) {
            m_channels.remove(i, n);
            status = FG_TRUE;
        }
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::anim::CAnimation::removeChannel(const char* name) {
    if(!name)
        return FG_FALSE;
    if(!name[0])
        return FG_FALSE;
    return removeChannel(std::string(name));
}
//------------------------------------------------------------------------------

void gfx::anim::CAnimation::setTimeData(float duration, float ticksPerSecond) {
    m_duration = duration;
    m_ticksPerSecond = ticksPerSecond;
    m_durationMs = m_duration / m_ticksPerSecond * 1000.0f;
    m_durationS = m_duration / m_ticksPerSecond;
}
//------------------------------------------------------------------------------

void gfx::anim::CAnimation::setTicksPerSecond(float ticksPerSecond) {
    m_ticksPerSecond = ticksPerSecond;
}
//------------------------------------------------------------------------------

void gfx::anim::CAnimation::setDuration(float duration) {
    m_duration = duration;
}
//------------------------------------------------------------------------------
