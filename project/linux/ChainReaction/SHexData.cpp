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
 * File:   SHexData.cpp
 * Author: vigilant
 * 
 * Created on July 21, 2015, 9:28 AM
 */

#include "SHexData.h"
#include "GFX/Scene/fgGfxSceneNode.h"

using namespace fg;
//------------------------------------------------------------------------------

SHexData::SHexData() : base_type() {
    blockType = HEXAGON;
}
//------------------------------------------------------------------------------

SHexData::~SHexData() { }
//------------------------------------------------------------------------------

SBlockData* SHexData::left(fgBool rewind) {
    return NULL;
}
//------------------------------------------------------------------------------

SBlockData* SHexData::right(fgBool rewind) {
    return NULL;
}
//------------------------------------------------------------------------------

SBlockData* SHexData::up(fgBool rewind) {
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

SBlockData* SHexData::down(fgBool rewind) {
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

SBlockData* SHexData::upLeft(fgBool rewind) {
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

SBlockData* SHexData::upRight(fgBool rewind) {
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

SBlockData* SHexData::downLeft(fgBool rewind) {
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

SBlockData* SHexData::downRight(fgBool rewind) {
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

void SHexData::rotate(RotationDirection direction, float amount) {
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
        if(isRotationValid(direction)) {
            rotDir = direction;
        } else {
            //return; // not a valid direction - probably left/right
            rotDir = direction;
        }
    }
    fgBool isOpposite = isOppositeRotation(direction);
    if(!isOpposite && direction != rotDir) {
        //return;
    }

    Vec3f translationAxis;
    Vec3f rotationAxis;
    float reverse = 1.0f;
    if(isOpposite) {
        reverse = -1.0f;
    }
    Matrix4f rotMat;
    if(direction == LEFT) {
        // X bigger (more minus) -> LEFT
        translationAxis.x = -HEX_HALF_SIZE * 0.75f;
        rotationAxis.y = -1.0f;
    } else if(direction == RIGHT) {
        // X bigger -> RIGHT
        translationAxis.x = HEX_HALF_SIZE * 0.75f;
        rotationAxis.y = 1.0f;
    } else if(direction == UP) {
        // Y bigger (more minus) -> UP
        translationAxis.y = HEX_HALF_SIZE * M_SQRT3F * 0.5f;
        rotationAxis.x = -1.0f;
    } else if(direction == DOWN) {
        // Y bigger -> DOWN
        translationAxis.y = -HEX_HALF_SIZE * M_SQRT3F * 0.5f;
        rotationAxis.x = 1.0f;
    } else if(direction == UP_LEFT) {
        // Y bigger (more minus) -> UP
        translationAxis.y = HEX_HALF_SIZE * M_SQRT3F * 0.25f;
        rotationAxis.x = -1.0f;
        // X bigger (more minus) -> LEFT
        translationAxis.x = -HEX_HALF_SIZE * 0.75f;
        rotationAxis.y = -M_SQRT3F;
    } else if(direction == UP_RIGHT) {
        // Y bigger (more minus) -> UP
        translationAxis.y = HEX_HALF_SIZE * M_SQRT3F * 0.25f;
        rotationAxis.x = -1.0f;
        // X bigger -> RIGHT
        translationAxis.x = HEX_HALF_SIZE * 0.75f;
        rotationAxis.y = M_SQRT3F;
    } else if(direction == DOWN_LEFT) {
        // Y bigger -> DOWN
        translationAxis.y = -HEX_HALF_SIZE * M_SQRT3F * 0.25f;
        rotationAxis.x = 1.0f;
        // X bigger (more minus) -> LEFT
        translationAxis.x = -HEX_HALF_SIZE * 0.75f;
        rotationAxis.y = -M_SQRT3F;
    } else if(direction == DOWN_RIGHT) {
        // Y bigger -> DOWN
        translationAxis.y = -HEX_HALF_SIZE * M_SQRT3F * 0.25f;        
        rotationAxis.x = 1.0f;        
        // X bigger -> RIGHT
        translationAxis.x = HEX_HALF_SIZE * 0.75f;
        rotationAxis.y = M_SQRT3F;
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
    if(shouldRotate || 1) {

        this->pSceneNode->translateMatrix(reverse * translationAxis);
        //Matrix4f& refModMatrix = this->pSceneNode->getModelMatrix();
        //Vec3f oldScale = this->pSceneNode->getScale();
        //this->pSceneNode->setScale(1.0f, 1.0f, 1.0f);
        //refModMatrix = refModMatrix * rotMat;
        //this->pSceneNode->setScale(oldScale);
        //this->pSceneNode->rotate(-M_PIF / 2.0f, 1.0f, 0.0f, 0.0f);
        this->pSceneNode->rotate(amount, rotationAxis);
        //this->pSceneNode->rotate(amount * reverse, reverse * Vec3f(0.5f, 0.0f, 0.0f));
        //this->pSceneNode->rotate(amount * reverse, reverse * Vec3f(0.0f, 0.5f, 0.0f));
        //this->pSceneNode->rotate(M_PIF / 2.0f, 1.0f, 0.0f, 0.0f);
        this->pSceneNode->translateMatrix(-1.0f * translationAxis * reverse);

        this->rotation += amount * reverse;
    }
}
//------------------------------------------------------------------------------

void SHexData::getCoveringCoord(RotationDirection direction,
                                unsigned short x,
                                unsigned short y,
                                unsigned short& newX,
                                unsigned short& newY) {
    // this function always returns something - even if the rotation is not complete
    if(direction == STATIC || direction == AUTO || direction == OPPOSITE) {
        return;
    }
    unsigned short _x = x, _y = y;
    fgBool isEven = FG_FALSE;
    if(_x % 2 == 0)
        isEven = FG_TRUE;
    switch(direction) {
        case UP:
            // up so the grid Y coords go down
            _y--;
            break;
        case DOWN:
            _y++;
            break;
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

void SHexData::getCoveredNeighbourCoord(unsigned short& x, unsigned short& y) {
    if(!pCellHolder) {
        // no cell holder pointer available - no way to determine the neighbour
        return;
    }
    getCoveringCoord(rotDir, pCellHolder->pos.x, pCellHolder->pos.y, x, y);
}
//------------------------------------------------------------------------------

SHexData* SHexData::getCoveredNeighbourHexData(void) {
    if(!isRotationFinished()) {
        return NULL;
    }
    game::CGrid::SCellHolder* neighbourCell = getCoveredNeighbourCellHolder();
    if(neighbourCell) {
        SHexData* pHexagonData = (SHexData*)neighbourCell->pData;
        return pHexagonData;
    } else {
        return NULL;
    }
}
//------------------------------------------------------------------------------

game::CGrid::SCellHolder* SHexData::getCoveredNeighbourCellHolder(void) {
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
        case UP:
            // up so the grid Y coords go down
            return pCellHolder->down(); // REVERSE
            break;
        case DOWN:
            return pCellHolder->up(); // REVERSE
            break;
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

fgBool SHexData::isRotationValid(RotationDirection direction) const {
    if(direction == AUTO || direction == OPPOSITE)
        return FG_FALSE;
    // These are not valid rotation directions for quad
    if(direction == LEFT || direction == RIGHT)
        return FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------
