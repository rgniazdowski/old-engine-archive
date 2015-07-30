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
 * File:   SBlockData.cpp
 * Author: vigilant
 * 
 * Created on July 21, 2015, 9:28 AM
 */

#include "SBlockData.h"
#include "GFX/Scene/fgGfxSceneNode.h"

using namespace fg;
//------------------------------------------------------------------------------

SBlockData::SBlockData() :
pSceneNode(NULL),
pCellHolder(NULL),
color(INVALID_COLOR),
isDragged(FG_FALSE),
isValid(FG_FALSE),
rotation(0.0f),
rotDir(NO_ROTATION),
blockType(BLOCK_INVALID),
//------------------------------------------------------------------------------

SBlockData::SBlockData(const SBlockData& orig) {
    this->pSceneNode = orig.pSceneNode;
    this->color = orig.color;
    this->pCellHolder = orig.pCellHolder;
    this->isDragged = orig.isDragged;
    this->isValid = orig.isValid;
    this->rotation = orig.rotation;
    this->rotDir = orig.rotDir;
}
//------------------------------------------------------------------------------

SBlockData::~SBlockData() {
    invalidate();
}
//------------------------------------------------------------------------------

void SBlockData::invalidate(void) {
    unbind();
    pSceneNode = NULL;
    color = INVALID_COLOR;
    pCellHolder = NULL;
    isDragged = FG_FALSE;
    isValid = FG_FALSE;
    rotation = 0.0f;
    rotDir = NO_ROTATION;
}
//------------------------------------------------------------------------------

void SBlockData::unbind(void) {
    if(pCellHolder) {
        pCellHolder->pData = NULL;
        pCellHolder->value = 0;
        pCellHolder = NULL;
    }
}
//------------------------------------------------------------------------------

void SBlockData::bind(game::CGrid::SCellHolder* _pCell) {
    if(_pCell) {
        unbind();
        pCellHolder = _pCell;
        pCellHolder->pData = (void *)this;
        pCellHolder->value = (unsigned short)this->color;
    }
}
//------------------------------------------------------------------------------

void SBlockData::setScale(float scale) {
    if(!pSceneNode)
        return;
    pSceneNode->setScale(scale, scale, 1.0f);
}
//------------------------------------------------------------------------------

void SBlockData::setScale(float xScale, float yScale, float zScale) {
    if(!pSceneNode)
        return;
    pSceneNode->setScale(xScale, yScale, zScale);
}
//------------------------------------------------------------------------------

void SBlockData::getScale(float& xScale, float& yScale, float& zScale) {
    if(!pSceneNode) {
        xScale = 0.0f;
        yScale = 0.0f;
        zScale = 0.0f;
    } else {
        const Vec3f& scale = pSceneNode->getScale();
        xScale = scale.x;
        yScale = scale.y;
        zScale = scale.z;
    }
}
//------------------------------------------------------------------------------

void SBlockData::getScale(float* xScale, float* yScale, float* zScale) {
    if(!pSceneNode) {
        if(xScale)
            *xScale = 0.0f;
        if(yScale)
            *yScale = 0.0f;
        if(zScale)
            *zScale = 0.0f;
    } else {
        const Vec3f& scale = pSceneNode->getScale();
        if(xScale)
            *xScale = scale.x;
        if(yScale)
            *yScale = scale.y;
        if(zScale)
            *zScale = scale.z;
    }
}
//------------------------------------------------------------------------------

RotationDirection SBlockData::getRandomValidRotation(void) {
    CVector<RotationDirection> rotations;
    RotationDirection rotationDir = NO_ROTATION;
    getValidRotations(rotations);
    if(!rotations.empty()) {
        const unsigned int n = rotations.size() - 1;
        const unsigned int nColor = FG_RAND(0, n);
        rotationDir = rotations[nColor];
    }
    return rotationDir;
}

VColor SBlockData::getOppositeColor(void) const {
    return self_type::getOppositeColor(color);
}
//------------------------------------------------------------------------------

VColor SBlockData::getOppositeColor(VColor color) {
    VColor rColor = VColor::INVALID_COLOR;
    switch(color) {
        case VColor::BLACK:
            rColor = VColor::WHITE;
            break;
        case VColor::WHITE:
            rColor = VColor::BLACK;
            break;
        case VColor::GRAY:
            rColor = VColor::GRAY;
            break;
        case VColor::RED:
            rColor = VColor::CYAN;
            break;
        case VColor::BLUE:
            rColor = VColor::YELLOW;
            break;
        case VColor::GREEN:
            rColor = VColor::MAGENTA;
            break;
        case VColor::CYAN:
            rColor = VColor::RED;
            break;
        case VColor::YELLOW:
            rColor = VColor::BLUE;
            break;
        case VColor::MAGENTA:
            rColor = VColor::GREEN;
            break;
        default:
            break;
    }
    return rColor;
}
//------------------------------------------------------------------------------

fgBool SBlockData::isRotating(void) const {
    return (fgBool)!!(rotDir != NO_ROTATION);
}
//------------------------------------------------------------------------------

fgBool SBlockData::isRotationFinished(void) const {
    if(rotDir != NO_ROTATION) {
        if(rotation <= (M_PIF + FG_EPSILON*2.0f) && rotation >= (M_PIF - FG_EPSILON)) {
            return FG_TRUE;
        }
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool SBlockData::doesCoverNeighbour(void) {
    if(!isRotationFinished()) {
        // if the rotation does not have the required angle
        // there is no need to do further checking
        return FG_FALSE;
    }
    game::CGrid::SCellHolder* neighbourCell = getCoveredNeighbourCellHolder();
    if(neighbourCell) {
        return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool SBlockData::doesCoverEmpty(void) {
    if(!isRotationFinished()) {
        return FG_FALSE;
    }
    return !doesCoverNeighbour();
}

void SBlockData::getCoveredNeighbourCoord(unsigned short* x, unsigned short* y) {
    unsigned short _x = 0, _y = 0;
    getCoveredNeighbourCoord(_x, _y);
    if(x)
        *x = _x;
    if(y)
        *y = _y;
}
//------------------------------------------------------------------------------

SBlockData* SBlockData::getCoveredNeighbourBlockData(void) {
    if(!isRotationFinished()) {
        return NULL;
    }
    game::CGrid::SCellHolder* neighbourCell = getCoveredNeighbourCellHolder();
    if(neighbourCell) {
        SBlockData* pBlockData = (SBlockData*)neighbourCell->pData;
        return pBlockData;
    } else {
        return NULL;
    }
}
//------------------------------------------------------------------------------

gfx::CSceneNode* SBlockData::getCoveredNeighbourNode(void) {
    if(!isRotationFinished()) {
        return NULL;
    }
    game::CGrid::SCellHolder* neighbourCell = getCoveredNeighbourCellHolder();
    if(neighbourCell) {
        SBlockData* pQuadData = (SBlockData*)neighbourCell->pData;
        if(!pQuadData) {
            return NULL;
        }
        return pQuadData->pSceneNode;
    } else {
        return NULL;
    }
}
//------------------------------------------------------------------------------

void SBlockData::hide(void) {
    if(pSceneNode) {
        pSceneNode->setVisible(FG_FALSE);
    }
}
//------------------------------------------------------------------------------

void SBlockData::show(fgBool shouldShow) {
    if(pSceneNode) {
        pSceneNode->setVisible(shouldShow);
    }
}
//------------------------------------------------------------------------------

void SBlockData::deactivate(void) {
    if(pSceneNode) {
        pSceneNode->setActive(FG_FALSE);
    }
}
//------------------------------------------------------------------------------

void SBlockData::activate(fgBool shouldActivate) {
    if(pSceneNode) {
        pSceneNode->setActive(shouldActivate);
    }
}
//------------------------------------------------------------------------------

fgBool SBlockData::isOrphan(void) {
    fgBool status = FG_TRUE;
    fgBool rewind = FG_FALSE; // ?
    status = (status && this->left(rewind) == NULL);
    status = (status && this->right(rewind) == NULL);
    status = (status && this->up(rewind) == NULL);
    status = (status && this->down(rewind) == NULL);

    status = (status && this->upLeft(rewind) == NULL);
    status = (status && this->upRight(rewind) == NULL);
    status = (status && this->downLeft(rewind) == NULL);
    status = (status && this->downRight(rewind) == NULL);
    status = (status && this->isBound());
    return status;
}
//------------------------------------------------------------------------------

fgBool SBlockData::isBound(void) const {
    if(!pCellHolder)
        return FG_FALSE;
    if(((SBlockData*)pCellHolder->pData) == this) {
        return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool SBlockData::isSelected(void) const {
    if(pSceneNode) {
        pSceneNode->isSelected();
    }
}
//------------------------------------------------------------------------------

fgBool SBlockData::isActive(void) const {
    if(pSceneNode) {
        pSceneNode->isActive();
    }
}
//------------------------------------------------------------------------------

fgBool SBlockData::isVisible(void) const {
    if(pSceneNode) {
        pSceneNode->isVisible();
    }
}
//------------------------------------------------------------------------------

fgBool SBlockData::isOppositeRotation(RotationDirection direction) const {
    if(this->rotDir == NO_ROTATION) {
        return FG_FALSE;
    }
    if((this->rotDir == LEFT && direction == RIGHT) ||
       (this->rotDir == RIGHT && direction == LEFT)) {
        return FG_TRUE;
    }
    if((this->rotDir == UP && direction == DOWN) ||
       (this->rotDir == DOWN && direction == UP)) {
        return FG_TRUE;
    }

    if((this->rotDir == UP_RIGHT && direction == DOWN_LEFT) ||
       (this->rotDir == DOWN_LEFT && direction == UP_RIGHT)) {
        return FG_TRUE;
    }

    if((this->rotDir == UP_LEFT && direction == DOWN_RIGHT) ||
       (this->rotDir == DOWN_RIGHT && direction == UP_LEFT)) {
        return FG_TRUE;
    }

    return FG_FALSE;
}
//------------------------------------------------------------------------------

RotationDirection SBlockData::getOppositeRotation(RotationDirection direction) {
    RotationDirection test, result = NO_ROTATION;
    if(this->rotDir == NO_ROTATION) {
        return NO_ROTATION;
    }
    if(direction == AUTO_ROTATION) {
        test = this->rotDir;
    } else {
        test = direction;
    }

    switch(test) {
        case LEFT:
            result = RIGHT;
            break;
        case RIGHT:
            result = LEFT;
            break;
        case UP:
            result = DOWN;
            break;
        case DOWN:
            result = UP;
            break;
        case UP_LEFT:
            result = DOWN_RIGHT;
            break;
        case UP_RIGHT:
            result = DOWN_LEFT;
            break;
        case DOWN_LEFT:
            result = UP_RIGHT;
            break;
        case DOWN_RIGHT:
            result = UP_LEFT;
            break;
    };

    return result;
}
//------------------------------------------------------------------------------
