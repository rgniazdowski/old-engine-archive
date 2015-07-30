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
 * File:   CLevelSolver.cpp
 * Author: vigilant
 * 
 * Created on July 23, 2015, 8:27 AM
 */

#include "fgBuildConfig.h"
#include "CLevelSolver.h"
#include "SHexData.h"
#include "SQuadData.h"
#include "fgLog.h"

using namespace fg;
//------------------------------------------------------------------------------

CLevelSolver::CLevelSolver(CLevelDataHolder* pLevelDataHolder) :
m_pLevelData(pLevelDataHolder),
m_finishedBlocks(),
m_rotatingBlocks(),
m_orphanBlocks(),
m_additionalBlocks(),
m_emergeBlocks(),
m_duplicates(),
m_coveredBlocks(),
m_stateFlags(NO_FLAGS),
m_scale(1.0f) {
    // Should level visualization have access to SceneManager?
    m_finishedBlocks.reserve(8);
    m_rotatingBlocks.reserve(8);
    m_orphanBlocks.reserve(8);
    m_additionalBlocks.reserve(8);
    m_emergeBlocks.reserve(8);
    m_duplicates.reserve(8);
    m_coveredBlocks.reserve(8);
}
//------------------------------------------------------------------------------

CLevelSolver::CLevelSolver(const CLevelSolver& orig) { }
//------------------------------------------------------------------------------

CLevelSolver::~CLevelSolver() { }
//------------------------------------------------------------------------------

void CLevelSolver::clear(void) {
    setChainReaction(FG_FALSE);
    setStepping(FG_FALSE);
    setStepOn(FG_FALSE);
    //setSimulation(FG_FALSE);
    m_rotatingBlocks.clear();
    m_finishedBlocks.clear();
    m_orphanBlocks.clear();
    m_additionalBlocks.clear();
    m_emergeBlocks.clear();
    m_duplicates.clear();
    m_coveredBlocks.clear();
}
//------------------------------------------------------------------------------

void CLevelSolver::setUserDisturbance(SBlockData* pBlockData) {
    if(!isChainReaction()) {
        m_finishedBlocks.push_back(pBlockData);
        setChainReaction();
    }
}
//------------------------------------------------------------------------------

void CLevelSolver::update(float elapsed) {
    // special update procedure - rotate/animate - check for rule breaking
    if(!isChainReaction() || !m_pLevelData) {
        return;
    }
    // the rotation speed in RADIANS/SECOND
    const float rotSpeed = M_PIF * 2.01f; // need to adjust externally
    // the scale speed in UNITS/SECOND
    const float scaleSpeed = m_scale * 0.75f; // need to adjust externally
    // the scale speed in UNITS/SECOND
    const float scaleUpSpeed = m_scale * 0.75f; // need to adjust externally

    NeighbourInfoVec neighbours;
    SBlockData* pNeighbour = NULL;
    fgBool canStep = (fgBool)((isStepOn() && isStepping()) || !isStepping());
    // checking the finished quads - adding quads to chain reaction
    while(!m_finishedBlocks.empty() && canStep) {
        SBlockData* pBlockData = m_finishedBlocks.back();
        m_finishedBlocks.pop_back();
        if(!pBlockData)
            continue;
        // should rewind?
        fgBool shouldRewind = FG_FALSE;
        // check neighbours for rule breaking (for now only by edge)
        pBlockData->getNeighbours(neighbours, shouldRewind);

        for(unsigned int iN = 0; iN < neighbours.size(); iN++) {
            SNeighbourInfo& nInfo = neighbours[iN];
            if(!nInfo.isValid())
                continue;
            if(pBlockData->isRotationValid(nInfo.direction)) {
                pNeighbour = nInfo.ptr;
                if(pNeighbour->color == pBlockData->color) {
                    // the color of the neighbour is the same
                    // need to select the rotation direction and add to special vec
                    pNeighbour->rotDir = nInfo.direction;
                    pNeighbour->rotate(RotationDirection::AUTO_ROTATION, 0.001f);
                    pNeighbour->setScale(m_scale + 0.05f, m_scale + 0.05f, 1.5f);
                    if(!m_rotatingBlocks.contains(pNeighbour))
                        m_rotatingBlocks.push_back(pNeighbour);
                }
            }
        }
    }
    pNeighbour = NULL;
    // now check and animate rotating quads
    unsigned int n = m_rotatingBlocks.size();
    //--------------------------------------------------------------------------
    // Rotating quads - rotate and add to finished vec
    for(unsigned int i = 0; i < n; i++) {
        SBlockData* pBlockData = m_rotatingBlocks[i];
        if(!pBlockData) {
            // This should not occur - however for safety...
            // if the NULL entry would not be removed
            // the chain reaction would not end automatically:
            // the flag will remain TRUE
            m_rotatingBlocks.remove(i, n); // notice that 'i' and 'n' will update
            continue;
        }
        pBlockData->rotate(AUTO_ROTATION, rotSpeed * elapsed);
        if(pBlockData->isRotationFinished()) {
            // rotation finished
            // need to move to the new position
            RotationDirection rotDir = pBlockData->rotDir;
            unsigned short x = 0, y = 0;
            pBlockData->getCoveredNeighbourCoord(x, y);
            FG_LOG_DEBUG("ChainReaction: Moving block %dx%d -> %dx%d", pBlockData->pCellHolder->pos.x,
                         pBlockData->pCellHolder->pos.y, x, y);
            int idxTest = m_finishedBlocks.find(pBlockData->getCoveredNeighbourBlockData());
            {
                SBlockData* pNewBlock = m_pLevelData->moveBlockToNewPlace(pBlockData, x, y);
                if(!pNewBlock) {
                    // adding new quad failed
                    if(m_finishedBlocks.find(pBlockData) < 0) {
                        // need to destroy this quad - gradually
                        if(m_orphanBlocks.find(pBlockData) < 0) {
                            m_orphanBlocks.push_back(pBlockData);
                            FG_LOG_DEBUG("ChainReaction: Unable to move: Adding Orphan[%p]@[%dx%d]",
                                         pBlockData,
                                         pBlockData->pCellHolder->pos.x,
                                         pBlockData->pCellHolder->pos.y);
                        }
                    }
                } else {
                    if(m_finishedBlocks.find(pNewBlock) < 0) {
                        // add the quad to finished vec
                        m_finishedBlocks.push_back(pNewBlock);
                    }
                    SCoverInfo coverInfo;
                    coverInfo.x = x;
                    coverInfo.y = y;
                    coverInfo.color = pNewBlock->color;
                    coverInfo.direction = rotDir;
                    m_coveredBlocks.push_back(coverInfo);
                }
            }
            if(idxTest >= 0) {
                FG_LOG_DEBUG("ChainReaction: Two quads are rotating to position: [%dx%d]", x, y);
                if(m_duplicates.find(Vec2i(x, y)) < 0) {
                    m_duplicates.push_back(Vec2i(x, y));
                } else {
                    // Such position already is in duplicates?
                    // this would mean that three blocks are rotating into this
                    // position
                    FG_LOG_DEBUG("ChainReaction: Third quad is rotating to position: [%dx%d]", x, y);
                }
                // Well this is some kind of special case -
                // maybe can create some kind of chain reaction
                // add additional blocks ?
                unsigned int nCovered = m_coveredBlocks.size();
                for(unsigned int k = 0; k < nCovered; k++) {
                    SCoverInfo& coverInfo = m_coveredBlocks[k];
                    if(!coverInfo.isValid()) {
                        m_coveredBlocks.remove(k, nCovered);
                        continue;
                    }
                    if(coverInfo.x == x && coverInfo.y == y) {
                        unsigned short newX, newY;
                        VColor qColor = coverInfo.color;
                        BlockInfo qInfo = BlockInfo(x, y, qColor);
                        getCoveringCoord(CLevelDataHolder::getBlockTypeFromLevelType(getLevelType()),
                                         coverInfo.direction,
                                         x, y, qInfo.pos.x, qInfo.pos.y);
                        if(m_additionalBlocks.find(qInfo) < 0)
                            m_additionalBlocks.push_back(qInfo);
                        m_coveredBlocks.remove(k, nCovered);
                    }
                }
            }
            // remove the quad from rotation vec
            m_rotatingBlocks.remove(i, n); // 'i' and 'n' will update
        } // isRotationFinished()
    }
    //--------------------------------------------------------------------------
    // Check and animate orphans (scaling down and removal)
    n = m_orphanBlocks.size();
    //unsigned int nOrphansBefore = n;
    fgBool canDissolve = (fgBool)!!(m_rotatingBlocks.empty() && m_finishedBlocks.empty());
    for(unsigned int i = 0; i < n && canDissolve; i++) {
        SBlockData* pBlockData = m_orphanBlocks[i];
        if(!pBlockData) {
            // This should not occur - however for safety...
            // if the NULL entry would not be removed
            // the chain reaction would not end automatically:
            // the flag will remain TRUE
            m_orphanBlocks.remove(i, n); // 'i' and 'n' will update
            continue;
        }
        Vector3f scale;
        pBlockData->getScale(scale.x, scale.y, scale.z);
        scale.x -= scaleSpeed * elapsed;
        scale.y -= scaleSpeed * elapsed;
        if(scale.x < 0.0f || scale.y < 0.0f) {
            m_pLevelData->destroyBlock(pBlockData->pCellHolder->pos.x,
                                       pBlockData->pCellHolder->pos.y);
            // remove the quad from orphan vec | func will decrease 'i' and 'n'
            m_orphanBlocks.remove(i, n);
        } else {
            pBlockData->setScale(scale.x, scale.y, scale.z);
        }
    }
    //--------------------------------------------------------------------------
    // Checking for additional quads (insertion)
    if(canDissolve && m_orphanBlocks.empty()) {
        unsigned int nAdditional = m_additionalBlocks.size();
        unsigned int nConflicts = 0;
        for(unsigned int i = 0; i < nAdditional; i++) {
            unsigned short x = m_additionalBlocks[i].pos.x;
            unsigned short y = m_additionalBlocks[i].pos.y;
            // need to check whether or not this position is empty
            SBlockData* pBlockData = m_pLevelData->getBlockData(x, y);
            if(pBlockData) {
                nConflicts++;
                m_orphanBlocks.push_back(pBlockData);
                FG_LOG_DEBUG("ChainReaction: Conflict: Adding Orphan[%p]@[%dx%d]",
                             pBlockData,
                             pBlockData->pCellHolder->pos.x,
                             pBlockData->pCellHolder->pos.y);
            }
        }
        for(unsigned int i = 0; i < nAdditional && !nConflicts; i++) {
            unsigned short x = m_additionalBlocks[i].pos.x;
            unsigned short y = m_additionalBlocks[i].pos.y;
            VColor color = m_additionalBlocks[i].color;
            color = SBlockData::getOppositeColor(color);            
            SBlockData* pBlockData = m_pLevelData->insertNewBlock(x, y, color);
            if(pBlockData) {
                pBlockData->setScale(0.001f, 0.001f, 1.0f);
                m_emergeBlocks.push_back(pBlockData);
            }
        }
        if(!nConflicts) {
            m_additionalBlocks.clear();
        }
        if(m_orphanBlocks.empty() && !m_emergeBlocks.empty()) {
            unsigned int nEmerge = m_emergeBlocks.size();
            for(unsigned int i = 0; i < nEmerge; i++) {
                SBlockData* pBlockData = m_emergeBlocks[i];
                if(!pBlockData) {
                    // remove from emerge
                    m_emergeBlocks.remove(i, nEmerge); // 'i' and 'nEmerge' -> -1
                    continue;
                }
                Vector3f scale;
                pBlockData->getScale(scale.x, scale.y, scale.z);
                const float scaleDiff = scaleUpSpeed * elapsed;
                scale.x += scaleDiff;
                scale.y += scaleDiff;
                if(scale.x > m_scale) {
                    scale.x = m_scale;
                    scale.y = m_scale;
                    scale.z = 1.0f;
                    // remove from emerge | this function will also decrease
                    // the index 'i' and 'nEmerge'
                    m_emergeBlocks.remove(i, nEmerge);
                    // add to finished
                    m_finishedBlocks.push_back(pBlockData);
                }
                pBlockData->setScale(scale.x, scale.y, scale.z);
            }
        }
        if(m_orphanBlocks.empty() && m_emergeBlocks.empty()) {
            m_duplicates.clear();
        }
    }
    //--------------------------------------------------------------------------
    // Checking for the orphans stage-wide
    if(areAllReactionVectorsEmpty()) {
        //printf("NEXT SEARCH - checking for orphans - whole stage !! !! !!\n");
        unsigned int nAllQuads = m_pLevelData->getBlocksCount();
        for(unsigned int i = 0; i < nAllQuads; i++) {
            SBlockData* pBlockData = m_pLevelData->at(i);
            if(!pBlockData)
                continue;
            if(pBlockData->isOrphan() && !pBlockData->isDragged) {
                m_orphanBlocks.push_back(pBlockData);
                FG_LOG_DEBUG("ChainReaction: Stage wide: Adding Orphan[%p]@[%dx%d]",
                             pBlockData,
                             pBlockData->pCellHolder->pos.x,
                             pBlockData->pCellHolder->pos.y);
            }
        }
    }
    // End the chain reaction
    if(areAllReactionVectorsEmpty()) {
        setChainReaction(FG_FALSE);
        m_coveredBlocks.clear();
    }
    setStepOn(FG_FALSE);
}
//------------------------------------------------------------------------------

void CLevelSolver::getCoveringCoord(BlockType blockType,
                                    RotationDirection direction,
                                    unsigned int x,
                                    unsigned int y,
                                    unsigned short& newX,
                                    unsigned short& newY) {
    if(blockType == BlockType::BLOCK_INVALID)
        return;
    if(direction == NO_ROTATION || direction == AUTO_ROTATION ||
       direction == OPPOSITE_ROTATION)
        return;
    if(blockType == BlockType::BLOCK_QUAD) {
        SQuadData::getCoveringCoord(direction, x, y, newX, newY);
    } else if(blockType == BlockType::BLOCK_HEXAGON) {
        SHexData::getCoveringCoord(direction, x, y, newX, newY);
    }
}
//------------------------------------------------------------------------------
