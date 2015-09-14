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
 * File:   fgGfxAnimationInfo.cpp
 * Author: vigilant
 * 
 * Created on September 2, 2015, 3:51 PM
 */

#include "fgGfxAnimationInfo.h"
#include "fgGfxAnimation.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::anim::SAnimationFrameInfo::SAnimationFrameInfo() :
index(0),
elapsed(0.0f),
transformations() {
    transformations.reserve(2);
}
//------------------------------------------------------------------------------

gfx::anim::SAnimationFrameInfo::SAnimationFrameInfo(const self_type& other) {
    transformations.append(other.transformations);
    elapsed = other.elapsed;
    index = other.index;
}
//------------------------------------------------------------------------------

gfx::anim::SAnimationFrameInfo::~SAnimationFrameInfo() {
    reset();
}
//------------------------------------------------------------------------------

gfx::anim::SAnimationInfo::SAnimationInfo(CAnimation* _pAnimation) :
pAnimation(_pAnimation),
curFrame(),
tempo(1.0f),
m_stateFlags(NO_FLAGS),
m_loopCount(0) { }
//------------------------------------------------------------------------------

gfx::anim::SAnimationInfo::SAnimationInfo(const SAnimationInfo& orig) {
    this->pAnimation = orig.pAnimation;
    this->curFrame.elapsed = orig.curFrame.elapsed;
    this->curFrame.index = orig.curFrame.index;
    this->curFrame.transformations.append(orig.curFrame.transformations);
    this->tempo = orig.tempo;
    this->m_stateFlags = orig.m_stateFlags;
    this->m_loopCount = orig.m_loopCount;
}
//------------------------------------------------------------------------------

gfx::anim::SAnimationInfo::~SAnimationInfo() {
    curFrame.reset();
    pAnimation = NULL;
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationInfo::clear(void) {
    curFrame.clear();
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationInfo::calculate(float delta) {
    // elapsed is current time measured from program start
    if(!pAnimation)
        return;
    pAnimation->calculate(*this, delta);
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationInfo::advanceTime(float delta) {
    if(isStopped() || isPaused())
        return;
    if(isPlayingReversed()) {
        curFrame.elapsed -= delta;
        if(pAnimation) {
            const float durationS = pAnimation->getDurationInSeconds();
            if(isReverseLooped() && m_loopCount != 0) {
                if(curFrame.elapsed <= 0.0f) {
                    curFrame.elapsed += durationS;
                    if(m_loopCount > 0)
                        m_loopCount--;
                }
            } else {
                if(curFrame.elapsed <= 0.0f) {
                    curFrame.elapsed = 0.0f;
                    stop();
                }
            }
        }

    } else if(isPlaying()) {
        curFrame.elapsed += delta;
        if(pAnimation) {
            const float durationS = pAnimation->getDurationInSeconds();
            if(isLooped() && m_loopCount != 0) {
                if(curFrame.elapsed >= durationS) {
                    curFrame.elapsed -= durationS;
                    if(m_loopCount > 0)
                        m_loopCount--;
                }
            } else {
                if(curFrame.elapsed >= durationS) {
                    curFrame.elapsed = durationS - 0.0025f;
                    setFlag(STOPPED, FG_TRUE);
                    setFlag(PAUSED, FG_FALSE);
                    setFlag(PLAYING, FG_FALSE);
                }
            }
        }
    }
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationInfo::play(void) {
    if(isReverseLooped()) {
        setFlag(PLAYING_REVERSED, FG_TRUE);
        setFlag(PLAYING, FG_FALSE);
        if(pAnimation)
            curFrame.elapsed = pAnimation->getDurationInSeconds() - 0.0025f;
    } else {
        setFlag(PLAYING, FG_TRUE);
        setFlag(PLAYING_REVERSED, FG_FALSE);
        curFrame.elapsed = 0.0f;
    }
    setFlag(PAUSED, FG_FALSE);
    setFlag(STOPPED, FG_FALSE);
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationInfo::stop(void) {
    setFlag(STOPPED, FG_TRUE);
    setFlag(PLAYING, FG_FALSE);
    setFlag(PAUSED, FG_FALSE);
    setFlag(PLAYING_REVERSED, FG_FALSE);
    rewind();
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationInfo::pause(void) {
    setFlag(PAUSED, FG_TRUE);
    setFlag(PLAYING, FG_FALSE);
    setFlag(PLAYING_REVERSED, FG_FALSE);
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationInfo::togglePause(void) {
    if(isPaused()) {
        resume();
    } else {
        pause();
    }
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationInfo::resume(void) {
    if(isReverseLooped()) {
        setFlag(PLAYING_REVERSED, FG_TRUE);
    } else {
        setFlag(PLAYING, FG_TRUE);
    }
    setFlag(PAUSED, FG_FALSE);
    setFlag(STOPPED, FG_FALSE);
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationInfo::rewind(void) {
    if(isReverseLooped()) {
        if(pAnimation)
            curFrame.elapsed = pAnimation->getDurationInSeconds() - 0.0025f;
    } else {
        curFrame.elapsed = 0.0f;
    }
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationInfo::loop(int counter, fgBool shouldPlay) {
    setFlag(LOOPED, FG_TRUE);
    setFlag(REVERSE_LOOPED, FG_FALSE);
    if(shouldPlay) {
        play();
    }
    m_loopCount = counter;
    if(m_loopCount < -1)
        m_loopCount = -1;
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationInfo::reloop(int counter, fgBool shouldPlay) {
    setFlag(REVERSE_LOOPED, FG_TRUE);
    setFlag(LOOPED, FG_FALSE);
    if(shouldPlay) {
        play();
    }
    m_loopCount = counter;
    if(m_loopCount < -1)
        m_loopCount = -1;
}
//------------------------------------------------------------------------------
