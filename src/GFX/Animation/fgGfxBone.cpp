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
weights() { }
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
    clear();
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
