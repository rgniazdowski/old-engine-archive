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
 * File:   SQuadData.cpp
 * Author: vigilant
 * 
 * Created on July 16, 2015, 11:28 AM
 */

#include "SQuadData.h"
#include "GFX/Scene/fgGfxSceneNode.h"

using namespace fg;
//------------------------------------------------------------------------------

SQuadData::SQuadData() :
pSceneNode(NULL),
pCellHolder(NULL),
color(NONE),
isDragged(FG_FALSE),
isValid(FG_FALSE),
rotation(0.0f),
rotDir(STATIC) { }
//------------------------------------------------------------------------------

SQuadData::SQuadData(const SQuadData& orig) {
    this->pSceneNode = orig.pSceneNode;
    this->color = orig.color;
    this->pCellHolder = orig.pCellHolder;
    this->isDragged = orig.isDragged;
    this->isValid = orig.isValid;
    this->rotation = orig.rotation;
    this->rotDir = orig.rotDir;
}
//------------------------------------------------------------------------------

SQuadData::~SQuadData() {
    invalidate();
}
//------------------------------------------------------------------------------

void SQuadData::invalidate(void) {
    pSceneNode = NULL;
    color = NONE;
    pCellHolder = NULL;
    isDragged = FG_FALSE;
    isValid = FG_FALSE;
    rotation = 0.0f;
    rotDir = STATIC;
}
//------------------------------------------------------------------------------

void SQuadData::unbind(void) {
    if(pCellHolder) {
        pCellHolder->pData = NULL;
        pCellHolder = NULL;
    }
}
//------------------------------------------------------------------------------

void SQuadData::bind(game::CGrid::SCellHolder* _pCell) {
    if(_pCell) {
        unbind();
        pCellHolder = _pCell;
        pCellHolder->pData = (void *)this;
    }
}
//------------------------------------------------------------------------------

void SQuadData::hide(void) {
    if(pSceneNode) {
        pSceneNode->setVisible(FG_FALSE);
    }
}
//------------------------------------------------------------------------------

void SQuadData::show(fgBool shouldShow) {
    if(pSceneNode) {
        pSceneNode->setVisible(shouldShow);
    }
}
//------------------------------------------------------------------------------

void SQuadData::deactivate(void) {
    if(pSceneNode) {
        pSceneNode->setActive(FG_FALSE);
    }
}
//------------------------------------------------------------------------------

void SQuadData::activate(fgBool shouldActivate) {
    if(pSceneNode) {
        pSceneNode->setActive(shouldActivate);
    }
}
//------------------------------------------------------------------------------

fgBool SQuadData::isSelected(void) const {
    if(pSceneNode) {
        pSceneNode->isSelected();
    }
}
//------------------------------------------------------------------------------

fgBool SQuadData::isActive(void) const {
    if(pSceneNode) {
        pSceneNode->isActive();
    }
}
//------------------------------------------------------------------------------

fgBool SQuadData::isVisible(void) const {
    if(pSceneNode) {
        pSceneNode->isVisible();
    }
}
//------------------------------------------------------------------------------

fgBool SQuadData::isOppositeRotation(RotationDirection _oppoDir) const {
    if(rotDir == STATIC)
        return FG_FALSE;
    if((rotDir == LEFT && _oppoDir == RIGHT) || (rotDir == RIGHT && _oppoDir == LEFT))
        return FG_TRUE;
    if((rotDir == UP && _oppoDir == DOWN) || (rotDir == DOWN && _oppoDir == UP))
        return FG_TRUE;
    return FG_FALSE;
}
//------------------------------------------------------------------------------
