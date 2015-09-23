/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxSceneEvent.h"
#include "fgGfxSceneNodeTrigger.h"

using namespace fg;

//------------------------------------------------------------------------------

void event::SSceneNode::reset(void) {
    pNodeA = NULL;
    pNodeB = NULL;
    handleNodeA = FG_INVALID_HANDLE;
    handleNodeB = FG_INVALID_HANDLE;
}

void event::SSceneNode::setFirstNode(gfx::CSceneNode* _pNodeA) {
    this->pNodeA = _pNodeA;
    if(this->pNodeA) {
        this->handleNodeA = this->pNodeA->getHandle();
    } else {
        this->handleNodeA = FG_INVALID_HANDLE;
    }
}
//------------------------------------------------------------------------------

void event::SSceneNode::setSecondNode(gfx::CSceneNode* _pNodeB) {
    this->pNodeB = _pNodeB;
    if(this->pNodeB) {
        this->handleNodeB = this->pNodeB->getHandle();
    } else {
        this->handleNodeB = FG_INVALID_HANDLE;
    }
}
//------------------------------------------------------------------------------

void event::SSceneNodeTrigger::reset(void) {
    pNodeA = NULL;
    pNodeB = NULL;
    handleNodeA = FG_INVALID_HANDLE;
    handleNodeB = FG_INVALID_HANDLE;
}
//------------------------------------------------------------------------------

void event::SSceneNodeTrigger::setFirstNode(gfx::CSceneNode* _pNodeA) {
    if(_pNodeA) {
        if(_pNodeA->checkNodeType(gfx::SCENE_NODE_TRIGGER)) {
            this->pNodeA = static_cast<gfx::CSceneNodeTrigger*>(_pNodeA);
        }
    } else {
        this->pNodeA = NULL;
    }
    if(this->pNodeA) {
        this->handleNodeA = this->pNodeA->getHandle();
    } else {
        this->handleNodeA = FG_INVALID_HANDLE;
    }
}
//------------------------------------------------------------------------------

void event::SSceneNodeTrigger::setSecondNode(gfx::CSceneNode* _pNodeB) {
    if(_pNodeB) {
        if(_pNodeB->checkNodeType(gfx::SCENE_NODE_TRIGGER)) {
            this->pNodeB = static_cast<gfx::CSceneNodeTrigger*>(_pNodeB);
        }
    } else {
        this->pNodeB = NULL;
    }
    if(this->pNodeB) {
        this->handleNodeB = this->pNodeB->getHandle();
    } else {
        this->handleNodeB = FG_INVALID_HANDLE;
    }
}
//------------------------------------------------------------------------------
