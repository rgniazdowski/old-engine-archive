/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written permission from the author.
 *******************************************************/
/* 
 * File:   fgGfxObjectAnimation.cpp
 * Author: vigilant
 * 
 * Created on September 2, 2015, 5:41 PM
 */

#include "fgGfxObjectAnimation.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::anim::CObjectAnimation::CObjectAnimation() : base_type() { }
//------------------------------------------------------------------------------

gfx::anim::CObjectAnimation::CObjectAnimation(const CObjectAnimation& orig) :
base_type(orig) { }
//------------------------------------------------------------------------------

gfx::anim::CObjectAnimation::~CObjectAnimation() { }
//------------------------------------------------------------------------------

void gfx::anim::CObjectAnimation::calculate(SAnimationInfo& animationInfo,
                                            float delta) {
 }
//------------------------------------------------------------------------------

