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

SQuadData::SQuadData() : base_type() {
    blockType = BLOCK_QUAD;
}
//------------------------------------------------------------------------------

SQuadData::~SQuadData() { }
//------------------------------------------------------------------------------

SBlockData* SQuadData::left(fgBool rewind) {
    if(!pCellHolder)
        return NULL;
    game::CGrid::SCellHolder* pNeighbourCell = pCellHolder->left(rewind);
    if(!pNeighbourCell)
        return NULL;
    if(!pNeighbourCell->pData)
        return NULL;
    return (SBlockData*)pNeighbourCell->pData;
}
//------------------------------------------------------------------------------

SBlockData* SQuadData::right(fgBool rewind) {
    if(!pCellHolder)
        return NULL;
    game::CGrid::SCellHolder* pNeighbourCell = pCellHolder->right(rewind);
    if(!pNeighbourCell)
        return NULL;
    if(!pNeighbourCell->pData)
        return NULL;
    return (SBlockData*)pNeighbourCell->pData;
}
//------------------------------------------------------------------------------

SBlockData* SQuadData::up(fgBool rewind) {
    if(!pCellHolder)
        return NULL;
    game::CGrid::SCellHolder* pNeighbourCell = pCellHolder->down(rewind); // REVERSED
    if(!pNeighbourCell)
        return NULL;
    if(!pNeighbourCell->pData)
        return NULL;
    return (SBlockData*)pNeighbourCell->pData;
}
//------------------------------------------------------------------------------

SBlockData* SQuadData::down(fgBool rewind) {
    if(!pCellHolder)
        return NULL;
    game::CGrid::SCellHolder* pNeighbourCell = pCellHolder->up(rewind); // REVERSED
    if(!pNeighbourCell)
        return NULL;
    if(!pNeighbourCell->pData)
        return NULL;
    return (SBlockData*)pNeighbourCell->pData;
}
//------------------------------------------------------------------------------

SBlockData* SQuadData::upLeft(fgBool rewind) {
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
    return (SBlockData*)pCornerCell->pData; // UP-LEFT
}
//------------------------------------------------------------------------------

SBlockData* SQuadData::upRight(fgBool rewind) {
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
    return (SBlockData*)pCornerCell->pData; // UP-RIGHT
}
//------------------------------------------------------------------------------

SBlockData* SQuadData::downLeft(fgBool rewind) {
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
    return (SBlockData*)pCornerCell->pData; // DOWN-LEFT
}
//------------------------------------------------------------------------------

SBlockData* SQuadData::downRight(fgBool rewind) {
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
    return (SBlockData*)pCornerCell->pData; // DOWN-RIGHT
}
//------------------------------------------------------------------------------

int SQuadData::getNeighbours(NeighbourInfoVec& neighbours, fgBool shouldRewind) {
    neighbours.clear();
    SBlockData* pNeighbour = NULL;
    pNeighbour = this->left(shouldRewind);
    if(pNeighbour)
        neighbours.push_back(SNeighbourInfo(pNeighbour, LEFT));

    pNeighbour = this->right(shouldRewind);
    if(pNeighbour)
        neighbours.push_back(SNeighbourInfo(pNeighbour, RIGHT));

    pNeighbour = this->up(shouldRewind);
    if(pNeighbour)
        neighbours.push_back(SNeighbourInfo(pNeighbour, UP));

    pNeighbour = this->down(shouldRewind);
    if(pNeighbour)
        neighbours.push_back(SNeighbourInfo(pNeighbour, DOWN));

    return neighbours.size();
}

//------------------------------------------------------------------------------

void SQuadData::rotate(RotationDirection direction, float amount) {
    if(direction == NO_ROTATION && rotDir == NO_ROTATION)
        return;
    if(rotDir == OPPOSITE_ROTATION) // ?
        return;
    fgBool shouldRotate = FG_TRUE;
    if(rotDir != NO_ROTATION && direction == AUTO_ROTATION) {
        direction = rotDir;
    }
    if(rotDir != NO_ROTATION && direction == OPPOSITE_ROTATION) {
        direction = getOppositeRotation(rotDir);
    }
    if(rotDir == NO_ROTATION && direction != OPPOSITE_ROTATION && direction != AUTO_ROTATION) {
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
        if(this->pSceneNode) {
            this->pSceneNode->translateMatrix(reverse * translationAxis);
            this->pSceneNode->rotate(amount * reverse, reverse * rotationAxis);
            this->pSceneNode->translateMatrix(-1.0f * translationAxis * reverse);
        }
        this->rotation += amount * reverse;
    }
}
//------------------------------------------------------------------------------

void SQuadData::getCoveringCoord(RotationDirection direction,
                                 unsigned short x,
                                 unsigned short y,
                                 unsigned short& newX,
                                 unsigned short& newY) {
    if(direction == NO_ROTATION || direction == AUTO_ROTATION || direction == OPPOSITE_ROTATION) {
        return;
    }
    // this function always returns something - even if the rotation is not complete
    unsigned short _x = x, _y = y;
    switch(direction) {
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
    newX = _x;
    newY = _y;
}
//------------------------------------------------------------------------------

void SQuadData::getCoveredNeighbourCoord(unsigned short& x, unsigned short& y) {
    if(!pCellHolder) {
        // no cell holder pointer available - no way to determine the neighbour
        return;
    }
    getCoveringCoord(rotDir, pCellHolder->pos.x, pCellHolder->pos.y, x, y);
}
//------------------------------------------------------------------------------

fgBool SQuadData::getPotentialNeighbourCoord(RotationDirection direction,
                                             unsigned short& x,
                                             unsigned short& y) {
    if(!pCellHolder) {
        return FG_FALSE;
    }
    fgBool status = FG_TRUE;
    getCoveringCoord(direction, pCellHolder->pos.x, pCellHolder->pos.y, x, y);
    if(pCellHolder->pParent) {
        status = pCellHolder->pParent->isValidAddress(x, y);
    } else {
        status = FG_FALSE;
        x = 0;
        y = 0;
    }
    return status;
}
//------------------------------------------------------------------------------

int SQuadData::getValidRotations(CVector<RotationDirection>& rotations) {
    rotations.clear();
    rotations.push_back(LEFT);
    rotations.push_back(RIGHT);
    rotations.push_back(UP);
    rotations.push_back(DOWN);
    return rotations.size();
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

fgBool SQuadData::isRotationValid(RotationDirection direction) const {
    if(direction == AUTO_ROTATION || direction == OPPOSITE_ROTATION)
        return FG_FALSE;
    // These are not valid rotation directions for quad
    if(direction == UP_LEFT || direction == UP_RIGHT)
        return FG_FALSE;
    if(direction == DOWN_LEFT || direction == DOWN_RIGHT)
        return FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------
