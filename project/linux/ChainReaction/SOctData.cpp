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
 * File:   SOctData.cpp
 * Author: vigilant
 * 
 * Created on July 28, 2015, 12:17 AM
 */

#include "SOctData.h"
#include "GFX/Scene/fgGfxSceneNode.h"

using namespace fg;
//------------------------------------------------------------------------------

SOctData::SOctData(fgBool isNG) : base_type() {
    if(isNG) {
        blockType = BLOCK_OCTAGON_NG;
    } else {
        blockType = BLOCK_OCTAGON;
    }
}
//------------------------------------------------------------------------------

SOctData::~SOctData() { }
//------------------------------------------------------------------------------

SBlockData* SOctData::left(fgBool rewind) {
    return NULL;
}
//------------------------------------------------------------------------------

SBlockData* SOctData::right(fgBool rewind) {
    return NULL;
}
//------------------------------------------------------------------------------

SBlockData* SOctData::up(fgBool rewind) {
    return NULL;
}
//------------------------------------------------------------------------------

SBlockData* SOctData::down(fgBool rewind) {
    return NULL;
}
//------------------------------------------------------------------------------

SBlockData* SOctData::upLeft(fgBool rewind) {
    if(!pCellHolder)
        return NULL;
    unsigned short _x;
    _x = pCellHolder->pos.x;
    fgBool isEven = FG_FALSE;
    if(_x % 2 == 0)
        isEven = FG_TRUE;
    game::CGrid::SCellHolder* pNeighbourCell = pCellHolder;
    if(isEven) {
        pNeighbourCell = pCellHolder->down(rewind); // REVERSED
        if(!pNeighbourCell)
            return NULL;
    }
    game::CGrid::SCellHolder* pCornerCell = pNeighbourCell->left(rewind); // LEFT
    if(!pCornerCell)
        return NULL;
    if(!pCornerCell->pData)
        return NULL;
    return (SBlockData*)pCornerCell->pData; // UP-LEFT
}
//------------------------------------------------------------------------------

SBlockData* SOctData::upRight(fgBool rewind) {
    if(!pCellHolder)
        return NULL;
    unsigned short _x;
    _x = pCellHolder->pos.x;
    fgBool isEven = FG_FALSE;
    if(_x % 2 == 0)
        isEven = FG_TRUE;
    game::CGrid::SCellHolder* pNeighbourCell = pCellHolder;
    if(isEven) {
        pNeighbourCell = pCellHolder->down(rewind); // REVERSED
        if(!pNeighbourCell)
            return NULL;
    }
    game::CGrid::SCellHolder* pCornerCell = pNeighbourCell->right(rewind); // RIGHT
    if(!pCornerCell)
        return NULL;
    if(!pCornerCell->pData)
        return NULL;
    return (SBlockData*)pCornerCell->pData; // UP-RIGHT
}
//------------------------------------------------------------------------------

SBlockData* SOctData::downLeft(fgBool rewind) {
    if(!pCellHolder)
        return NULL;
    unsigned short _x;
    _x = pCellHolder->pos.x;
    fgBool isEven = FG_FALSE;
    if(_x % 2 == 0)
        isEven = FG_TRUE;
    game::CGrid::SCellHolder* pNeighbourCell = pCellHolder;
    if(!isEven) {
        pNeighbourCell = pCellHolder->up(rewind); // REVERSED
        if(!pNeighbourCell)
            return NULL;
    }
    game::CGrid::SCellHolder* pCornerCell = pNeighbourCell->left(rewind); // LEFT
    if(!pCornerCell)
        return NULL;
    if(!pCornerCell->pData)
        return NULL;
    return (SBlockData*)pCornerCell->pData; // DOWN-LEFT
}
//------------------------------------------------------------------------------

SBlockData* SOctData::downRight(fgBool rewind) {
    if(!pCellHolder)
        return NULL;
    unsigned short _x;
    _x = pCellHolder->pos.x;
    fgBool isEven = FG_FALSE;
    if(_x % 2 == 0)
        isEven = FG_TRUE;
    game::CGrid::SCellHolder* pNeighbourCell = pCellHolder;
    if(!isEven) {
        pNeighbourCell = pCellHolder->up(rewind); // REVERSED
        if(!pNeighbourCell)
            return NULL;
    }
    game::CGrid::SCellHolder* pCornerCell = pNeighbourCell->right(rewind); // RIGHT
    if(!pCornerCell)
        return NULL;
    if(!pCornerCell->pData)
        return NULL;
    return (SBlockData*)pCornerCell->pData; // DOWN-RIGHT
}
//------------------------------------------------------------------------------

int SOctData::getNeighbours(NeighbourInfoVec& neighbours, fgBool shouldRewind) {
    neighbours.clear();

    //neighbours.push_back(SNeighbourInfo(this->left(shouldRewind), LEFT));
    //neighbours.push_back(SNeighbourInfo(this->right(shouldRewind), RIGHT));
    SBlockData* pNeighbour = NULL;

    pNeighbour = this->upLeft(shouldRewind);
    if(pNeighbour)
        neighbours.push_back(SNeighbourInfo(pNeighbour, UP_LEFT));

    pNeighbour = this->upRight(shouldRewind);
    if(pNeighbour)
        neighbours.push_back(SNeighbourInfo(pNeighbour, UP_RIGHT));

    pNeighbour = this->downLeft(shouldRewind);
    if(pNeighbour)
        neighbours.push_back(SNeighbourInfo(pNeighbour, DOWN_LEFT));

    pNeighbour = this->downRight(shouldRewind);
    if(pNeighbour)
        neighbours.push_back(SNeighbourInfo(pNeighbour, DOWN_RIGHT));
    return neighbours.size();
}
//------------------------------------------------------------------------------

void SOctData::rotate(RotationDirection direction, float amount) {
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
        if(isRotationValid(direction)) {
            rotDir = direction;
        } else {
            return; // not a valid direction - probably left/right
        }
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
    // height = a*(1+sqrt(2))/2.0    
    const float a_f = 1.0f / (1.0f + (float)M_SQRT2);
    const float trans_f = a_f / (float)M_SQRT2 / 2.0f + a_f / 2.0f;
    if(direction == UP_LEFT) {
        // Y bigger (more minus) -> UP
        translationAxis.y = trans_f; // plus
        rotationAxis.x = -1.0f;
        // X bigger (more minus) -> LEFT
        translationAxis.x = -trans_f; // minus
        rotationAxis.y = -1.0f;
    } else if(direction == UP_RIGHT) {
        // Y bigger (more minus) -> UP
        translationAxis.y = trans_f;
        rotationAxis.x = -1.0f;
        // X bigger -> RIGHT
        translationAxis.x = trans_f; // plus
        rotationAxis.y = 1.0f;
    } else if(direction == DOWN_LEFT) {
        // Y bigger -> DOWN
        translationAxis.y = -trans_f; // minus
        rotationAxis.x = 1.0f;
        // X bigger (more minus) -> LEFT
        translationAxis.x = -trans_f; // minus
        rotationAxis.y = -1.0f;
    } else if(direction == DOWN_RIGHT) {
        // Y bigger -> DOWN
        translationAxis.y = -trans_f; // minus
        rotationAxis.x = 1.0f;
        // X bigger -> RIGHT
        translationAxis.x = trans_f; // plus
        rotationAxis.y = 1.0f;
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
            this->pSceneNode->rotate(amount, rotationAxis);
            this->pSceneNode->translateMatrix(-1.0f * translationAxis * reverse);
        }
        this->rotation += amount * reverse;
    }
}
//------------------------------------------------------------------------------

void SOctData::getCoveringCoord(RotationDirection direction,
                                unsigned short x,
                                unsigned short y,
                                unsigned short& newX,
                                unsigned short& newY) {
    // this function always returns something - even if the rotation is not complete
    if(direction == NO_ROTATION || direction == AUTO_ROTATION || direction == OPPOSITE_ROTATION) {
        return;
    }
    unsigned short _x = x, _y = y;
    fgBool isEven = FG_FALSE;
    if(_x % 2 == 0)
        isEven = FG_TRUE;
    switch(direction) {
        case UP_LEFT:
            if(isEven) {
                _y--;
                _x--;
            } else {
                _x--;
            }
            break;
        case UP_RIGHT:
            if(isEven) {
                _y--;
                _x++;
            } else {
                _x++;
            }
            break;
        case DOWN_LEFT:
            if(isEven) {
                _x--;
            } else {
                _y++;
                _x--;
            }
            break;
        case DOWN_RIGHT:
            if(isEven) {
                _x++;
            } else {
                _y++;
                _x++;
            }
            break;
        default:
            break;
    }
    newX = _x;
    newY = _y;
}
//------------------------------------------------------------------------------

void SOctData::getCoveredNeighbourCoord(unsigned short& x, unsigned short& y) {
    if(!pCellHolder) {
        // no cell holder pointer available - no way to determine the neighbour
        return;
    }
    getCoveringCoord(rotDir, pCellHolder->pos.x, pCellHolder->pos.y, x, y);
}
//------------------------------------------------------------------------------

fgBool SOctData::getPotentialNeighbourCoord(RotationDirection direction,
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

int SOctData::getValidRotations(CVector<RotationDirection>& rotations) {
    rotations.clear();
    //rotations.push_back(LEFT);
    //rotations.push_back(RIGHT);
    //rotations.push_back(UP);
    //rotations.push_back(DOWN);
    rotations.push_back(UP_LEFT);
    rotations.push_back(UP_RIGHT);
    rotations.push_back(DOWN_LEFT);
    rotations.push_back(DOWN_RIGHT);
    return rotations.size();
}
//------------------------------------------------------------------------------

SOctData* SOctData::getCoveredNeighbourOctData(void) {
    if(!isRotationFinished()) {
        return NULL;
    }
    game::CGrid::SCellHolder* neighbourCell = getCoveredNeighbourCellHolder();
    if(neighbourCell) {
        SOctData* pOctagonData = (SOctData*)neighbourCell->pData;
        return pOctagonData;
    } else {
        return NULL;
    }
}
//------------------------------------------------------------------------------

game::CGrid::SCellHolder* SOctData::getCoveredNeighbourCellHolder(void) {
    if(!isRotationFinished()) {
        return NULL;
    }
    if(!pCellHolder)
        return NULL;
    unsigned short _x;
    _x = pCellHolder->pos.x;
    fgBool isEven = FG_FALSE;
    if(_x % 2 == 0)
        isEven = FG_TRUE;
    // rotation has finished
    switch(rotDir) {
        case UP_LEFT:
            if(isEven) {
                game::CGrid::SCellHolder* pCell = pCellHolder->up(); // REVERSE
                if(pCell)
                    return pCell->left();
            } else {
                return pCellHolder->left();
            }
            break;
        case UP_RIGHT:
            if(isEven) {
                game::CGrid::SCellHolder* pCell = pCellHolder->down(); // REVERSE
                if(pCell)
                    return pCell->right();
            } else {
                return pCellHolder->right();
            }
            break;
        case DOWN_LEFT:
            if(isEven) {
                return pCellHolder->left();
            } else {
                game::CGrid::SCellHolder* pCell = pCellHolder->up(); // REVERSE
                if(pCell)
                    return pCell->left();
            }
            break;
        case DOWN_RIGHT:
            if(isEven) {
                return pCellHolder->right();
            } else {
                game::CGrid::SCellHolder* pCell = pCellHolder->up(); // REVERSE
                if(pCell)
                    return pCell->right();
            }
            break;
        default:
            return NULL;
            break;
    }
    return NULL;
}
//------------------------------------------------------------------------------

fgBool SOctData::isRotationValid(RotationDirection direction) const {
    if(direction == AUTO_ROTATION || direction == OPPOSITE_ROTATION)
        return FG_FALSE;
    // These are not valid rotation directions for octagon
    if(direction == LEFT || direction == RIGHT)
        return FG_FALSE;
    if(direction == UP || direction == LEFT)
        return FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool SOctData::isNG(void) const {
    return (fgBool)(this->blockType == BlockType::BLOCK_OCTAGON_NG);
}
//------------------------------------------------------------------------------
