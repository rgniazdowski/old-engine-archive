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
currentFrame() { }
//------------------------------------------------------------------------------

gfx::anim::SAnimationInfo::SAnimationInfo(const SAnimationInfo& orig) {
    pAnimation = orig.pAnimation;
    currentFrame.elapsed = orig.currentFrame.elapsed;
    currentFrame.index = orig.currentFrame.index;
    currentFrame.transformations.append(orig.currentFrame.transformations);
}
//------------------------------------------------------------------------------

gfx::anim::SAnimationInfo::~SAnimationInfo() {
    currentFrame.reset();
    pAnimation = NULL;
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationInfo::clear(void) {
    currentFrame.clear();
}
//------------------------------------------------------------------------------

void gfx::anim::SAnimationInfo::calculate(float elapsed) {
    // elapsed is current time measured from program start
    if(!pAnimation)
        return;
    pAnimation->calculate(currentFrame, elapsed);
}
//------------------------------------------------------------------------------
