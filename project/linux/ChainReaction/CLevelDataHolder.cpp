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
 * File:   CLevelDataHolder.cpp
 * Author: vigilant
 * 
 * Created on July 23, 2015, 8:47 AM
 */

#include "CLevelDataHolder.h"
#include "SHexData.h"
#include "SQuadData.h"
#include "fgLog.h"

using namespace fg;
//------------------------------------------------------------------------------

CLevelDataHolder::CLevelDataHolder(game::CGrid* pGrid, CLevelFile* pLvlFile) :
m_actionCallbacks(),
m_pGrid(pGrid),
m_pLevelFile(pLvlFile),
m_blocksData() {
    if(m_pLevelFile) {
        unsigned int n = m_pLevelFile->getBlocksCount();
        if(n) {
            unsigned int nReserve = (unsigned int)(n * 1.5f);
            m_blocksData.reserve(nReserve);
            for(unsigned int i = 0; i < nReserve; i++) {
                m_blocksData[i] = NULL;
            }
        }
    } else {
        unsigned int nReserve = 48;
        m_blocksData.reserve(nReserve);
        for(unsigned int i = 0; i < nReserve; i++) {
            m_blocksData[i] = NULL;
        }
    }
    for(unsigned int i = 0; i < NUM_ACTIONS; i++) {
        m_actionCallbacks[i].reserve(2);
    }
}
//------------------------------------------------------------------------------

CLevelDataHolder::CLevelDataHolder(const CLevelDataHolder& orig) { }
//------------------------------------------------------------------------------

CLevelDataHolder::~CLevelDataHolder() {
    internalCall(ACTION_LEVEL_DATA_DESTROYED, NULL, NULL);
    clearCallbacks();
    clear();
    m_pLevelFile = NULL;
    m_pGrid = NULL;
    m_blocksData.clear();
}
//------------------------------------------------------------------------------

fgBool CLevelDataHolder::registerCallback(InternalActionType actionType,
                                          CallbackFuncPtr pCallback,
                                          void* pUserData) {
    if(actionType == ACTION_INVALID || !pCallback || isRegistered(pCallback, actionType)) {
        return FG_FALSE;
    }
    SCallbackData callbackInfo(actionType, pCallback, pUserData);
    m_actionCallbacks[(unsigned int)actionType].push_back(callbackInfo);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CLevelDataHolder::isRegistered(CallbackFuncPtr pCallback, InternalActionType actionType) {
    if(!pCallback)
        return FG_FALSE;
    fgBool status = FG_FALSE;
    unsigned int i = 0;
    unsigned int n = NUM_ACTIONS;
    if(actionType != ACTION_INVALID) {
        i = (unsigned int)actionType;
        n = i + 1;
    }
    for(; i < n && !status; i++) {
        for(unsigned int j = 0; j < m_actionCallbacks[i].size() && !status; j++) {
            SCallbackData& info = m_actionCallbacks[i][j];
            if(info.callback == pCallback) {
                status = FG_TRUE;
                break;
            }
        }
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool CLevelDataHolder::removeCallback(CallbackFuncPtr pCallback) {
    fgBool status = FG_FALSE;
    for(unsigned int i = 0; i < NUM_ACTIONS; i++) {
        unsigned int n = m_actionCallbacks[i].size();
        for(unsigned int j = 0; j < n && !status; j++) {
            SCallbackData& info = m_actionCallbacks[i][j];
            if(info.callback == pCallback) {
                info.clear();
                m_actionCallbacks[i].remove(j, n);
                status = FG_TRUE;
                continue;
            }
        }
    }
    return status;
}
//------------------------------------------------------------------------------

void CLevelDataHolder::clearCallbacks(void) {
    for(unsigned int i = 0; i < NUM_ACTIONS; i++) {
        m_actionCallbacks[i].clear();
    }
}
//------------------------------------------------------------------------------

fgBool CLevelDataHolder::internalCall(InternalActionType actionType,
                                      SBlockData* pOriginal,
                                      SBlockData* pNew) {
    if(actionType == ACTION_INVALID)
        return FG_FALSE;
    fgBool status = FG_TRUE;
    unsigned int n = m_actionCallbacks[(unsigned int)actionType].size();
    for(unsigned int i = 0; i < n; i++) {
        SCallbackData& info = m_actionCallbacks[(unsigned int)actionType][i];
        //info.action.actionType = actionType;
        info.action.pOriginal = pOriginal;
        info.action.pNew = pNew;
        status = (fgBool)!!(status && info.call());
    }
    return status;
}

//------------------------------------------------------------------------------

SBlockData* CLevelDataHolder::insertNewBlock(unsigned short x,
                                             unsigned short y,
                                             VColor color) {
    if(!m_pGrid) {
        return NULL;
    }
    if(!m_pGrid->isValidAddress(x, y)) {
        return NULL;
    }
    int index = destroyBlock(x, y); // this destroy any original in that place
    // now need to insert new quad in that place
    // allocate new quad data
    SBlockData* pBlockData = NULL;
    if(m_pLevelFile->getLevelType() == CLevelFile::LEVEL_QUADS) {
        pBlockData = new SQuadData();
    } else if(m_pLevelFile->getLevelType() == CLevelFile::LEVEL_HEXAGONS) {
        pBlockData = new SHexData();
    } else {
        pBlockData = new SQuadData();
    }
    pBlockData->color = color;
    game::CGrid::SCellHolder* pCellHolder = m_pGrid->atPtr(x, y);
    if(!pCellHolder) {
        // probably game::CGrid is not prepared - should call applyToGrid
        // destroy the scene node
        internalCall(ACTION_BLOCK_DESTROYED, pBlockData, NULL);
        delete pBlockData;
        pBlockData = NULL;
        return NULL;
    }
    pBlockData->bind(pCellHolder);
    pBlockData->isValid = FG_TRUE;
    pBlockData->isDragged = FG_FALSE;
    pBlockData->activate();
    pBlockData->show();
    m_blocksData.push_back(pBlockData);
    // should check the return value of the callback func?
    internalCall(ACTION_BLOCK_ADDED, pBlockData, NULL);
    return pBlockData;
}
//------------------------------------------------------------------------------

int CLevelDataHolder::destroyBlock(SBlockData* pBlockData) {
    if(!m_pGrid || !pBlockData) {
        return -1;
    }
    int index = m_blocksData.find(pBlockData);
    if(index != -1) {
        m_blocksData[index] = NULL;
        pBlockData->deactivate();
        pBlockData->unbind();
        internalCall(ACTION_BLOCK_DESTROYED, pBlockData, NULL);
        // need to destroy it completely
        delete pBlockData;
        pBlockData = NULL;
        m_blocksData.remove(index);
        // previous block is now completely removed
    }
    return index;
}
//------------------------------------------------------------------------------

int CLevelDataHolder::destroyBlock(unsigned int index) {
    if(index >= m_blocksData.size()) {
        return -1;
    }
    SBlockData* pBlockData = m_blocksData[index];
    if(!pBlockData)
        return -1;
    m_blocksData[index] = NULL;
    pBlockData->deactivate();
    pBlockData->unbind();
    internalCall(ACTION_BLOCK_DESTROYED, pBlockData, NULL);
    // need to destroy it completely
    delete pBlockData;
    pBlockData = NULL;
    m_blocksData.remove(index);
    // previous block is now completely removed
    return (int)index;
}
//------------------------------------------------------------------------------

int CLevelDataHolder::destroyBlock(unsigned short x, unsigned short y) {
    if(!m_pGrid) {
        return -1;
    }
    if(!m_pGrid->isValidAddress(x, y)) {
        return -1;
    }
    // need also to find SBlockData that already resides on this address
    int index = getBlockDataIndex(x, y);
    if(index != -1) {
        destroyBlock((unsigned int)index);
    }
    return index; // return the index from which the quad was destroyed
}
//------------------------------------------------------------------------------

SBlockData* CLevelDataHolder::moveBlockToNewPlace(SBlockData* original,
                                                  unsigned short newX,
                                                  unsigned short newY) {
    if(!m_pGrid || !original) {
        return NULL;
    }
    if(!original->pCellHolder) {
        FG_LOG_DEBUG("ChainReaction[CLevelVis]: Unable to move quad[%p] to new place[%dx%d]: cell holder is NULL - quad probably is not bound");
        return NULL;
    }
    if(!m_pGrid->isValidAddress(newX, newX)) {
        FG_LOG_DEBUG("ChainReaction[CLevelVis]: Unable to move quad[%p@%dx%d] to new place[%dx%d]: address is not valid",
                     original,
                     original->pCellHolder->pos.x,
                     original->pCellHolder->pos.y,
                     newX, newY);
        return NULL;
    }
    // the quad moves to the new place
    // if something already exists in that place
    // there must be a way to preserve as much memory as possible.
    // the scene node with valid name (cr_node_XxY) cannot have the name changed
    // need to replace material

    if(original->pCellHolder->pos.x == newX && original->pCellHolder->pos.y == newY) {
        return original; // nothing to do
    }
    // determine if there is something in that place
    SBlockData* pNewPlace = getBlockData(newX, newY);
    if(pNewPlace == original) {
        return original; // nothing to do
    }
    if(pNewPlace) {
        // replace the color, value and material in the new location
        // change the value
        pNewPlace->pCellHolder->value = original->pCellHolder->value;
        // change the color
        pNewPlace->color = original->color;
        internalCall(ACTION_BLOCK_MOVED, original, pNewPlace);
        // now need to remove the original
        // this will also destroy the original scene node and unbind
        //destroyBlock(original->pCellHolder->pos.x, original->pCellHolder->pos.y);
        destroyBlock(original);
        original = NULL;
        pNewPlace->isValid = FG_TRUE;
        pNewPlace->isDragged = FG_FALSE;
        pNewPlace->rotation = 0.0f;
        pNewPlace->rotDir = NO_ROTATION;
        return pNewPlace; // return the quad pointer after move
    }
    // if there is nothing in the target location
    // need to unbind the old block data
    // the original SBlockData is reused
    original->unbind();
    // can retain the old SBlockData - just replace the pointers and bind again
    original->bind(m_pGrid->atPtr(newX, newY));
    original->isValid = FG_TRUE;
    original->isDragged = FG_FALSE;
    original->rotation = 0.0f;
    original->rotDir = NO_ROTATION;
    internalCall(ACTION_BLOCK_MOVED, original, NULL);
    return original;
}
//------------------------------------------------------------------------------

void CLevelDataHolder::clear(void) {
    unsigned int n = m_blocksData.size();
    for(unsigned int i = 0; i < n; i++) {
        SBlockData* pBlockData = m_blocksData[i];
        if(!pBlockData) {
            continue;
        }        
        internalCall(ACTION_BLOCK_DESTROYED, pBlockData);
        pBlockData->deactivate();
        pBlockData->unbind();
        delete pBlockData;
        pBlockData = NULL;
        m_blocksData[i] = NULL;
    }
    n = m_blocksData.capacity();
    for(unsigned int i = 0; i < n; i++) {
        m_blocksData[i] = NULL;
    }
    if(m_pGrid) {
        m_pGrid->clear();
    }
    m_blocksData.clear_optimised();
    internalCall(ACTION_GRID_CLEARED, NULL, NULL);
}
//------------------------------------------------------------------------------

fgBool CLevelDataHolder::restart(void) {
    if(!m_pLevelFile || !m_pGrid)
        return FG_FALSE;
    // delete all old nodes, quad data, unbind all and clear the grid
    // better to start over >> #FIXME - maybe some optimization, without so many
    // reallocs
    clear();
    CLevelFile::BlockInfoVec& blocks = m_pLevelFile->getBlocks();
    unsigned int n = blocks.size();
    if(!n) {
        return FG_FALSE;
    }
    // need to reserve proper size
    unsigned int nReserve = (unsigned int)(n * 1.5f);
    m_blocksData.reserve(nReserve);
    // Quad vector from level file contains just info about position and color.
    // Quad data vector is more detailed, contains scene node, draw call, and
    // cell holder from game logical grid.
    m_pLevelFile->applyToGrid(m_pGrid);
    // Prepare new number of quads
    for(unsigned int i = 0; i < n; i++) {
        insertNewBlock(blocks[i].pos.x,
                       blocks[i].pos.y,
                       (VColor)blocks[i].color);
    }
}

//------------------------------------------------------------------------------

SBlockData* CLevelDataHolder::at(unsigned int index) {
    if(index >= m_blocksData.size())
        return NULL;
    return m_blocksData[index];
}
//------------------------------------------------------------------------------

SBlockData* CLevelDataHolder::getBlockData(unsigned short x, unsigned short y) {
    if(m_pGrid) {
        void *cellData = m_pGrid->getCellData(x, y);
        if(!cellData) {
            return NULL;
        }
        return (SBlockData*)cellData;
    } else {
        unsigned int n = m_blocksData.size();
        for(unsigned int i = 0; i < n; i++) {
            SBlockData* pBlockData = m_blocksData[i];
            if(!pBlockData) {
                continue;
            }
            if(!pBlockData->pCellHolder) {
                continue;
            }
            if(pBlockData->pCellHolder->pos.x == x &&
               pBlockData->pCellHolder->pos.y == y) {
                if(((SBlockData*)pBlockData->pCellHolder->pData) == pBlockData) {
                    return pBlockData;
                }
            }
        }
        return NULL;
    }
}
//------------------------------------------------------------------------------

int CLevelDataHolder::getBlockDataIndex(unsigned short x, unsigned short y) {
    unsigned int n = m_blocksData.size();
    for(unsigned int i = 0; i < n; i++) {
        SBlockData *pBlockData = m_blocksData[i];
        if(!pBlockData) {
            continue;
        }
        if(!pBlockData->pCellHolder) {
            continue;
        }
        if(pBlockData->pCellHolder->pos.x == x &&
           pBlockData->pCellHolder->pos.y == y) {
            if(((SBlockData*)pBlockData->pCellHolder->pData) == pBlockData) {
                return i;
            }
        }
    }
    return -1;
}
//------------------------------------------------------------------------------

void CLevelDataHolder::setLevelFile(CLevelFile* pLvlFile) {
    m_pLevelFile = pLvlFile;
}
//------------------------------------------------------------------------------

void CLevelDataHolder::getSize(unsigned short& x, unsigned short& y) {
    if(m_pLevelFile) {
        m_pLevelFile->getSize(x, x);
    }
}
//------------------------------------------------------------------------------

void CLevelDataHolder::getSize(unsigned short* x, unsigned short* y) {
    if(m_pLevelFile) {
        m_pLevelFile->getSize(x, x);
    }
}