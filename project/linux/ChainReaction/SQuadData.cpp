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
        pCellHolder->value = 0;
        pCellHolder = NULL;
    }
}
//------------------------------------------------------------------------------

void SQuadData::bind(game::CGrid::SCellHolder* _pCell) {
    if(_pCell) {
        unbind();
        pCellHolder = _pCell;
        pCellHolder->pData = (void *)this;
        pCellHolder->value = (unsigned short)this->color;
    }
}
//------------------------------------------------------------------------------

SQuadData* SQuadData::left(fgBool rewind) {
    if(!pCellHolder)
        return NULL;
    game::CGrid::SCellHolder* pNeighbourCell = pCellHolder->left(rewind);
    if(!pNeighbourCell)
        return NULL;
    if(!pNeighbourCell->pData)
        return NULL;
    return (SQuadData*)pNeighbourCell->pData;
}
//------------------------------------------------------------------------------

SQuadData* SQuadData::right(fgBool rewind) {
    if(!pCellHolder)
        return NULL;
    game::CGrid::SCellHolder* pNeighbourCell = pCellHolder->right(rewind);
    if(!pNeighbourCell)
        return NULL;
    if(!pNeighbourCell->pData)
        return NULL;
    return (SQuadData*)pNeighbourCell->pData;
}
//------------------------------------------------------------------------------

SQuadData* SQuadData::up(fgBool rewind) {
    if(!pCellHolder)
        return NULL;
    game::CGrid::SCellHolder* pNeighbourCell = pCellHolder->down(rewind); // REVERSED
    if(!pNeighbourCell)
        return NULL;
    if(!pNeighbourCell->pData)
        return NULL;
    return (SQuadData*)pNeighbourCell->pData;
}
//------------------------------------------------------------------------------

SQuadData* SQuadData::down(fgBool rewind) {
    if(!pCellHolder)
        return NULL;
    game::CGrid::SCellHolder* pNeighbourCell = pCellHolder->up(rewind); // REVERSED
    if(!pNeighbourCell)
        return NULL;
    if(!pNeighbourCell->pData)
        return NULL;
    return (SQuadData*)pNeighbourCell->pData;
}
//------------------------------------------------------------------------------

SQuadData* SQuadData::upLeft(fgBool rewind) {
    if(!pCellHolder)
        return NULL;
    game::CGrid::SCellHolder* pNeighbourCell = pCellHolder->down(rewind); // REVERSED
    if(!pNeighbourCell)
        return NULL;
    game::CGrid::SCellHolder* pCornerCell = pNeighbourCell->left(rewind); // LEFT
    if(!pCornerCell)
        return NULL;
    if(!pCornerCell->pData)
        return NULL;
    return (SQuadData*)pCornerCell->pData; // UP-LEFT
}
//------------------------------------------------------------------------------

SQuadData* SQuadData::upRight(fgBool rewind) {
    if(!pCellHolder)
        return NULL;
    game::CGrid::SCellHolder* pNeighbourCell = pCellHolder->down(rewind); // REVERSED
    if(!pNeighbourCell)
        return NULL;
    game::CGrid::SCellHolder* pCornerCell = pNeighbourCell->right(rewind); // RIGHT
    if(!pCornerCell)
        return NULL;
    if(!pCornerCell->pData)
        return NULL;
    return (SQuadData*)pCornerCell->pData; // UP-RIGHT
}
//------------------------------------------------------------------------------

SQuadData* SQuadData::downLeft(fgBool rewind) {
    if(!pCellHolder)
        return NULL;
    game::CGrid::SCellHolder* pNeighbourCell = pCellHolder->up(rewind); // REVERSED
    if(!pNeighbourCell)
        return NULL;
    game::CGrid::SCellHolder* pCornerCell = pNeighbourCell->left(rewind); // LEFT
    if(!pCornerCell)
        return NULL;
    if(!pCornerCell->pData)
        return NULL;
    return (SQuadData*)pCornerCell->pData; // DOWN-LEFT
}
//------------------------------------------------------------------------------

SQuadData* SQuadData::downRight(fgBool rewind) {
    if(!pCellHolder)
        return NULL;
    game::CGrid::SCellHolder* pNeighbourCell = pCellHolder->up(rewind); // REVERSED
    if(!pNeighbourCell)
        return NULL;
    game::CGrid::SCellHolder* pCornerCell = pNeighbourCell->right(rewind); // RIGHT
    if(!pCornerCell)
        return NULL;
    if(!pCornerCell->pData)
        return NULL;
    return (SQuadData*)pCornerCell->pData; // DOWN-RIGHT
}
//------------------------------------------------------------------------------

void SQuadData::rotate(RotationDirection direction, float amount) {
    if(direction == STATIC && rotDir == STATIC || !pSceneNode)
        return;
    if(rotDir == OPPOSITE) // ?
        return;
    fgBool shouldRotate = FG_TRUE;
    if(rotDir != STATIC && direction == AUTO) {
        direction = rotDir;
    }
    if(rotDir != STATIC && direction == OPPOSITE) {
        direction = getOppositeRotation(rotDir);
    }
    if(rotDir == STATIC && direction != OPPOSITE && direction != AUTO) {
        rotDir = direction;
    }
    fgBool isOpposite = isOppositeRotation(direction);
    if(!isOpposite && direction != rotDir) {
        return;
    }

    Vec3f translationAxis;
    Vec3f rotationAxis;
    float reverse = 1.0f;
    if(isOpposite) {
        reverse = -1.0f;
    }

    if(direction == LEFT) {
        // X bigger (more minus) -> LEFT
        translationAxis.x = -QUAD_HALF_SIZE;
        rotationAxis.y = -1.0f;
    } else if(direction == RIGHT) {
        // X bigger -> RIGHT
        translationAxis.x = QUAD_HALF_SIZE;
        rotationAxis.y = 1.0f;
    } else if(direction == UP) {
        // Y bigger (more minus) -> UP
        translationAxis.y = QUAD_HALF_SIZE;
        rotationAxis.x = -1.0f;
    } else if(direction == DOWN) {
        // Y bigger -> DOWN
        translationAxis.y = -QUAD_HALF_SIZE;
        rotationAxis.x = 1.0f;
    } else {
        shouldRotate = FG_FALSE;
    }

    float newRotation = this->rotation + amount * reverse;
    if(newRotation >= M_PIF) {
        // exceed
        amount -= (newRotation - M_PIF) * reverse;
        if(shouldRotate && isRotationFinished()) {
            shouldRotate = FG_FALSE;
        }
    } else if(newRotation < 0.0f) {
        // exceed
        amount -= newRotation * reverse;
    }
    if(shouldRotate) {
        this->pSceneNode->translateMatrix(reverse * translationAxis);
        this->pSceneNode->rotate(amount * reverse, reverse * rotationAxis);
        this->pSceneNode->translateMatrix(-1.0f * translationAxis * reverse);
        this->rotation += amount * reverse;
    }
}
//------------------------------------------------------------------------------

fgBool SQuadData::isRotationFinished(void) const {
    if(rotDir != STATIC) {
        if(rotation <= M_PIF && rotation >= (M_PIF - FG_EPSILON)) {
            return FG_TRUE;
        }
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool SQuadData::doesCoverNeighbour(void) {
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

fgBool SQuadData::doesCoverEmpty(void) {
    if(!isRotationFinished()) {
        return FG_FALSE;
    }
    return !doesCoverNeighbour();
}
//------------------------------------------------------------------------------

void SQuadData::getCoveredNeighbourCoord(unsigned short& x, unsigned short& y) {
    // this function always returns something - even if the rotation is not complete
    if(rotDir == STATIC || rotDir == AUTO || rotDir == OPPOSITE) {
        // those are not valid directions
        return;
    }
    if(!pCellHolder) {
        // no cell holder pointer available - no way to determine the neighbour
        return;
    }
    unsigned short _x, _y;
    _x = pCellHolder->pos.x;
    _y = pCellHolder->pos.y;
    switch(rotDir) {
        case LEFT:
            _x--;
            break;
        case RIGHT:
            _x++;
            break;
        case UP:
            // up so the grid Y coords go down
            _y--;
            break;
        case DOWN:
            _y++;
            break;
    }
    x = _x;
    y = _y;
}
//------------------------------------------------------------------------------

void SQuadData::getCoveredNeighbourCoord(unsigned short* x, unsigned short* y) {
    unsigned short _x = 0, _y = 0;
    getCoveredNeighbourCoord(_x, _y);
    if(x)
        *x = _x;
    if(y)
        *y = _y;
}
//------------------------------------------------------------------------------

SQuadData* SQuadData::getCoveredNeighbourQuadData(void) {
    if(!isRotationFinished()) {
        return NULL;
    }
    game::CGrid::SCellHolder* neighbourCell = getCoveredNeighbourCellHolder();
    if(neighbourCell) {
        SQuadData* pQuadData = (SQuadData*)neighbourCell->pData;
        return pQuadData;
    } else {
        return NULL;
    }
}
//------------------------------------------------------------------------------

game::CGrid::SCellHolder* SQuadData::getCoveredNeighbourCellHolder(void) {
    if(!isRotationFinished()) {
        return NULL;
    }
    // rotation has finished
    switch(rotDir) {
        case LEFT:
            return pCellHolder->left();
            break;
        case RIGHT:
            return pCellHolder->right();
            break;
        case UP:
            // up so the grid Y coords go down
            return pCellHolder->down();
            break;
        case DOWN:
            return pCellHolder->up();
            break;
        default:
            return NULL;
            break;
    }
}
//------------------------------------------------------------------------------

gfx::CSceneNode* SQuadData::getCoveredNeighbourNode(void) {
    if(!isRotationFinished()) {
        return NULL;
    }
    game::CGrid::SCellHolder* neighbourCell = getCoveredNeighbourCellHolder();
    if(neighbourCell) {
        SQuadData* pQuadData = (SQuadData*)neighbourCell->pData;
        if(!pQuadData) {
            return NULL;
        }
        return pQuadData->pSceneNode;
    } else {
        return NULL;
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

fgBool SQuadData::isOrphan(void) {
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

fgBool SQuadData::isBound(void) const {
    if(!pCellHolder)
        return FG_FALSE;
    if(((SQuadData*)pCellHolder->pData) == this) {
        return FG_TRUE;
    }
    return FG_FALSE;
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

fgBool SQuadData::isOppositeRotation(RotationDirection direction) const {
    if(this->rotDir == STATIC) {
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
    return FG_FALSE;
}
//------------------------------------------------------------------------------

SQuadData::RotationDirection SQuadData::getOppositeRotation(RotationDirection direction) {
    RotationDirection test, result = STATIC;
    if(this->rotDir == STATIC) {
        return STATIC;
    }
    if(direction == AUTO) {
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
    };

    return result;
}
