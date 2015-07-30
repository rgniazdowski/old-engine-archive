/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "AdditionalTypes.h"
#include "SBlockData.h"
#include "SQuadData.h"
#include "SHexData.h"
#include "SOctData.h"
#include <cstring>

using namespace fg;
//------------------------------------------------------------------------------

SBlockMoveInfo::SBlockMoveInfo(BlockType _blockType) :
pos(),
target(),
moveDir(NO_ROTATION),
blockType(_blockType),
pData(NULL) { }
//------------------------------------------------------------------------------

SBlockMoveInfo::SBlockMoveInfo(SPosition _position,
                               RotationDirection _moveDir,
                               BlockType _blockType) :
pos(_position),
target(),
moveDir(NO_ROTATION),
blockType(_blockType),
pData(NULL) {
    setDirection(_moveDir);
}
//------------------------------------------------------------------------------

SBlockMoveInfo::~SBlockMoveInfo() {
    self_type::clear();
}
//------------------------------------------------------------------------------

void SBlockMoveInfo::clear(void) {
    pos.zero();
    target.zero();
    moveDir = NO_ROTATION;
    blockType = BlockType::BLOCK_INVALID;
    pData = NULL;
}
//------------------------------------------------------------------------------

void SBlockMoveInfo::setDirection(RotationDirection _moveDir) {
    if(_moveDir == NO_ROTATION || _moveDir == AUTO_ROTATION || _moveDir == OPPOSITE_ROTATION)
        return;
    if(this->blockType == BLOCK_INVALID)
        return;
    this->moveDir = _moveDir;
    if(blockType == BLOCK_QUAD) {
        SQuadData::getCoveringCoord(_moveDir, pos.x, pos.y, target.x, target.y);
    } else if(blockType == BLOCK_HEXAGON) {
        SHexData::getCoveringCoord(_moveDir, pos.x, pos.y, target.x, target.y);
    } else if(blockType == BLOCK_OCTAGON) {
        SOctData::getCoveringCoord(_moveDir, pos.x, pos.y, target.x, target.y);
    }
}
//------------------------------------------------------------------------------

fgBool SBlockMoveInfo::isValid(void) const {
    if(moveDir == NO_ROTATION) {
        return FG_FALSE;
    }
    if(blockType == BLOCK_INVALID) {
        return FG_FALSE;
    }
    if(pos.x == target.x && pos.y == target.y) {
        return FG_FALSE;
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

SBlockMoveStep::SBlockMoveStep(BlockType _blockType) : base_type(_blockType),
moveIdx(0),
moveDepth(0),
steps(),
levelState(),
currentStep() {
    steps.reserve(16);
    currentStep = steps.end();
}
//------------------------------------------------------------------------------

SBlockMoveStep::SBlockMoveStep(SPosition _position,
                               RotationDirection _moveDir,
                               BlockType _blockType) : base_type(_position, _moveDir, _blockType),
moveIdx(0),
moveDepth(0),
steps(),
currentStep() {
    steps.reserve(16);
    levelState.reserve(8);
    rewind();
}
//------------------------------------------------------------------------------

SBlockMoveStep::~SBlockMoveStep() {
    this->clear();
}
//------------------------------------------------------------------------------

void SBlockMoveStep::clear(void) {
    base_type::clear();
    self_type::clearSteps();
    this->levelState.clear();
}
//------------------------------------------------------------------------------

void SBlockMoveStep::clearSteps(void) {
    unsigned int n = this->steps.size();
    for(unsigned int i = 0; i < n; i++) {
        self_type* pStep = this->steps[i];
        if(pStep)
            delete pStep;
        pStep = NULL;
        this->steps[i] = NULL;
    }
    this->steps.clear();
}
//------------------------------------------------------------------------------

void SBlockMoveStep::rewind(void) {
    currentStep = steps.end();
}
//------------------------------------------------------------------------------

SBlockMoveStep::self_type* SBlockMoveStep::next(fgBool shouldClearPrevious) {
    if(!isItorValid()) {
        currentStep = steps.begin();
    } else {
        currentStep++;
        if(shouldClearPrevious) {
            Iterator itor = steps.begin();
            for(; itor != currentStep; itor++) {
                (*itor)->clearSteps();
            }
        }
    }
    return current();
}
//------------------------------------------------------------------------------

SBlockMoveStep::self_type& SBlockMoveStep::nextRef(void) {
    if(!isItorValid()) {
        currentStep = steps.begin();
    } else {
        currentStep++;
    }
    return currentRef();
}
//------------------------------------------------------------------------------

SBlockMoveStep::self_type* SBlockMoveStep::current(void) {
    if(!isItorValid())
        return NULL;
    return (*currentStep)->self();
}
//------------------------------------------------------------------------------

SBlockMoveStep::self_type& SBlockMoveStep::currentRef(void) {
    if(!isItorValid())
        return (*this);
    return (*currentStep)->selfRef();
}
//------------------------------------------------------------------------------

SBlockMoveStep::self_type const& SBlockMoveStep::currentRef(void) const {
    if(!isItorValid())
        return (*this);
    return (*currentStep)->selfRef();
}
//------------------------------------------------------------------------------

fgBool SBlockMoveStep::isItorValid(void) const {
    return (fgBool)!!(currentStep != steps.end());
}
//------------------------------------------------------------------------------

fgBool SBlockMoveStep::isValid(void) const {
    if(!base_type::isValid())
        return FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

int SBlockMoveStep::addStep(SPosition _position, RotationDirection _moveDir) {
    if(_moveDir == NO_ROTATION || _moveDir == AUTO_ROTATION || _moveDir == OPPOSITE_ROTATION)
        return -1;
    steps.push_back(new self_type(_position, _moveDir, this->blockType));
    self_type* latest = steps.back();
    latest->moveDepth = this->moveDepth + 1;
    latest->moveIdx = this->steps.size() - 1;
#if 1
    if(latest->target == this->pos &&
       this->target == latest->pos) { // this step is just the opposite of this
        steps.back()->clear();
        delete latest;
        steps.pop_back();
        return -1;
    }
#endif
    return (int)this->steps.size() - 1;
}
//------------------------------------------------------------------------------

#if defined(DEBUG) || defined(FG_DEBUG)

void SBlockMoveStep::dump(void) {
    printf("MoveStep[%p]: Move block from [%dx%d] to [%dx%d] -> %s | depth[%d] index[%d]\n",
           this,
           pos.x,
           pos.y,
           target.x,
           target.y,
           getRotationName(moveDir),
           moveDepth,
           moveIdx);
}
#endif
//------------------------------------------------------------------------------