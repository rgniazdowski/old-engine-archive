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
 * File:   fgGfxBlendingInfo.cpp
 * Author: vigilant
 * 
 * Created on September 16, 2015, 6:12 PM
 */

#include "fgGfxBlendingInfo.h"
#include "fgGfxAnimation.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::anim::SWeightPair::SWeightPair() :
base_type(0.0f, 0.0f) { }
//------------------------------------------------------------------------------

gfx::anim::SWeightPair::SWeightPair(float _first, float _second) :
base_type(_first, _second) { }
//------------------------------------------------------------------------------

gfx::anim::SWeightPair::SWeightPair(const SWeightPair& other) {
    first = other.first;
    second = other.second;
}
//------------------------------------------------------------------------------

gfx::anim::SWeightPair& gfx::anim::SWeightPair::operator =(const SWeightPair& other) {
    if(this != &other) {
        first = other.first;
        second = other.second;
    }
    return *this;
}
//------------------------------------------------------------------------------

void gfx::anim::SWeightPair::getFlipped(float& _first, float& _second) const {
    _first = second;
    _second = first;
}
//------------------------------------------------------------------------------

void gfx::anim::SWeightPair::get(float& _first, float& _second) const {
    _first = this->first;
    _second = this->second;
}
//------------------------------------------------------------------------------

void gfx::anim::SWeightPair::getFlipped(float* _first, float* _second) const {
    if(_first) {
        *_first = this->second;
    }
    if(_second) {
        *_second = this->first;
    }
}
//------------------------------------------------------------------------------

void gfx::anim::SWeightPair::get(float* _first, float* _second) const {
    if(_first) {
        *_first = this->first;
    }
    if(_second) {
        *_second = this->second;
    }
}
//------------------------------------------------------------------------------

gfx::anim::SBlendingPair::SBlendingPair() : weights() {
    animation.first = NULL;
    animation.second = NULL;
}
//------------------------------------------------------------------------------

gfx::anim::SBlendingPair::SBlendingPair(const self_type& orig) {
    weights.append(orig.weights);
    animation.first = orig.animation.first;
    animation.second = orig.animation.second;
}
//------------------------------------------------------------------------------

gfx::anim::SBlendingPair::~SBlendingPair() { }
//------------------------------------------------------------------------------

fgBool gfx::anim::SBlendingPair::isFlipped(const CAnimation* pFirst,
                                           const CAnimation* pSecond) {
    if(this->animation.first == pSecond && this->animation.second == pFirst) {
        return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool gfx::anim::SBlendingPair::isFlipped(const AnimationPair& pair) {
    if(this->animation.first == pair.second && this->animation.second == pair.first) {
        return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

gfx::anim::SBlendingInfo::SBlendingInfo() : base_type() {
    this->reserve(2);
}
//------------------------------------------------------------------------------

gfx::anim::SBlendingInfo::SBlendingInfo(const SBlendingInfo& orig) {
    this->append(orig);
}
//------------------------------------------------------------------------------

gfx::anim::SBlendingInfo::~SBlendingInfo() { }
//------------------------------------------------------------------------------

fgBool gfx::anim::SBlendingInfo::hasPair(CAnimation* pFirst,
                                         CAnimation* pSecond) const {
    return (fgBool)!!(find(AnimationPair(pFirst, pSecond)) >= 0);
}
//------------------------------------------------------------------------------

fgBool gfx::anim::SBlendingInfo::hasPair(const AnimationPair& pair) const {
    return (fgBool)!!(find(pair) >= 0);
}
//------------------------------------------------------------------------------

int gfx::anim::SBlendingInfo::find(CAnimation* pFirst,
                                           CAnimation* pSecond) const {
    return find(AnimationPair(pFirst, pSecond));
}
//------------------------------------------------------------------------------

int gfx::anim::SBlendingInfo::find(const AnimationPair& pair) const {
    const unsigned int n = this->size();
    int index = -1;
    for(unsigned int i = 0; i < n; i++) {
        if((*this)[i].animation == pair) {
            index = i;
            break;
        }
        if((*this)[i].animation.first == pair.second &&
           (*this)[i].animation.second == pair.first) {
            index = i;
            break;
        }
    }
    return index;
}
//------------------------------------------------------------------------------

gfx::anim::SBlendingPair* gfx::anim::SBlendingInfo::get(const AnimationPair& pair) {
    int index = find(pair);
    if(index < 0)
        return NULL;
    return &((*this)[index]);
}
//------------------------------------------------------------------------------

gfx::anim::SBlendingPair const* gfx::anim::SBlendingInfo::get(const AnimationPair& pair) const {
    int index = find(pair);
    if(index < 0)
        return NULL;
    return &((*this)[index]);
}
//------------------------------------------------------------------------------

gfx::anim::SBlendingPair* gfx::anim::SBlendingInfo::get(CAnimation* pFirst,
                                                        CAnimation* pSecond) {
    int index = find(AnimationPair(pFirst, pSecond));
    if(index < 0)
        return NULL;
    return &((*this)[index]);
}
//------------------------------------------------------------------------------

gfx::anim::SBlendingPair const* gfx::anim::SBlendingInfo::get(CAnimation* pFirst, CAnimation* pSecond) const {
    int index = find(AnimationPair(pFirst, pSecond));
    if(index < 0)
        return NULL;
    return &((*this)[index]);
}
//------------------------------------------------------------------------------
