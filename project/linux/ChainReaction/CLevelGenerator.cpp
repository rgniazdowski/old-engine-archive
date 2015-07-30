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
 * File:   CLevelGenerator.cpp
 * Author: vigilant
 * 
 * Created on July 23, 2015, 9:52 PM
 */

#include "fgBuildConfig.h"
#include "CLevelGenerator.h"
#include "fgLog.h"

using namespace fg;
//------------------------------------------------------------------------------

CLevelGenerator::CLevelGenerator(StateFlags stateFlags) :
m_pGrid(NULL),
m_internalGrid(NULL),
m_pLevelData(NULL),
m_internalLevelData(NULL),
m_internalLevelFile(NULL),
m_colorTable(),
m_genLevelType(LevelType::LEVEL_QUADS),
m_genLevelIdx(1),
m_gridCoverage(0.5f),
m_stateFlags(stateFlags) {
    if(m_stateFlags == NO_FLAGS) {
        useBlackAndWhiteColors(); // enable black & white by default
        setFullyRandom(); // by default the generator is fully random
    }
    this->checkInternals();
}
//------------------------------------------------------------------------------

CLevelGenerator::CLevelGenerator(const CLevelGenerator& orig) {
    this->m_pGrid = orig.m_pGrid;
    this->m_pLevelData = orig.m_pLevelData;
    this->m_internalGrid = NULL;
    this->m_internalLevelData = NULL;
    this->m_internalLevelFile = NULL;
    this->m_genLevelType = orig.m_genLevelType;
    this->m_genLevelIdx = orig.m_genLevelIdx;
    this->m_gridCoverage = orig.m_gridCoverage;
    this->m_stateFlags = orig.m_stateFlags;
    this->checkInternals();
}
//------------------------------------------------------------------------------

CLevelGenerator::~CLevelGenerator() {

    if(m_pLevelData) {
        if(m_pLevelData->getGrid() == m_internalGrid && m_internalGrid) {
            m_pLevelData->setGrid(NULL);
        }
        if(m_pLevelData->getLevelFile() == m_internalLevelFile && m_internalLevelFile) {
            m_pLevelData->setLevelFile(NULL);
        }
        m_pLevelData = NULL;
    }
    m_pGrid = NULL;

    if(m_internalLevelData) {
        delete m_internalLevelData;
        m_internalLevelData = NULL;
    }
    if(m_internalGrid) {
        delete m_internalGrid;
        m_internalGrid = NULL;
    }
    if(m_internalLevelFile) {
        delete m_internalLevelFile;
        m_internalLevelFile = NULL;
    }

    m_genLevelIdx = 0;
    m_genLevelType = LevelType::LEVEL_INVALID;
    m_colorTable.clear();
}
//------------------------------------------------------------------------------

void CLevelGenerator::clear(void) {
    if(m_internalLevelData) {
        m_internalLevelData->clear();
    }
    getLevelData()->clear();
    if(m_internalGrid) {
        m_internalGrid->clear();
    }
    getGrid()->clear();

}
//------------------------------------------------------------------------------

fgBool CLevelGenerator::generate(void) {
    checkInternals();
    clear();

    if(m_gridCoverage > 1.0f)
        m_gridCoverage = 1.0f;
    if(m_gridCoverage < 0.1f)
        m_gridCoverage = 0.1f; // minimum 10%
    fgBool status = FG_TRUE;
    fgBool shouldRewind = FG_FALSE;
    unsigned short sizeX = getLevelFile()->getSize().x;
    unsigned short sizeY = getLevelFile()->getSize().y;
    getLevelData()->getGrid()->resize(sizeX, sizeY);
    const int gridCapacity = m_size.x * m_size.y;
    unsigned int numTotalBlocks = (int)(((float)gridCapacity) * m_gridCoverage);
    unsigned int numOrphans = 0; // number of added orphans (fix)
    CLevelDataHolder::BlockDataVec orphans;
    int blocksDiff = (gridCapacity - numTotalBlocks);
    NeighbourInfoVec neighbours;
    CLevelDataHolder* pLevelData = getLevelData();
    CLevelDataHolder::BlockDataVec& refLevelBlocks = pLevelData->getBlocks();
    CVector<SBlockInfo> tPositions;
    CVector<VColor> usedColors;
    tPositions.reserve(gridCapacity + 1);
    usedColors.reserve(8);
    orphans.reserve(8);

    // Need to populate tPositions completely
    for(unsigned int y = 0; y < sizeY; y++) {
        for(unsigned int x = 0; x < sizeX; x++) {
            SBlockInfo blockInfo;
            blockInfo.pos.x = x;
            blockInfo.pos.y = y;
            if(isFullyRandom()) {
                blockInfo.color = VColor::INVALID_COLOR;
            } else if(isRegularCheckerboard()) {
                // now with the regular checkerboard active
                const fgBool isEven = (fgBool)!!(x % 2 == 0);
                const unsigned int maxColorIdx = m_colorTable.size();
                unsigned int colorIdx = 0;
                if(isEven) {
                    colorIdx = maxColorIdx - ((y + 1) % maxColorIdx) - 1;
                } else {
                    colorIdx = maxColorIdx - ((y) % maxColorIdx) - 1;
                }
                blockInfo.color = m_colorTable[colorIdx];
            }
            tPositions.push_back(blockInfo);
        }
    }
    tPositions.reverse();

    if(isFullyRandom() || isRegularCheckerboard()) {

        // then remove some of the positions to fit the grid coverage limit
        for(unsigned int i = 0; i < blocksDiff; i++) {
            unsigned int index = FG_RAND(0, tPositions.size() - 1);
            tPositions.remove(index);
        }

        //int numFixedBlocks = 0;

        for(unsigned int i = 0; i < numTotalBlocks; i++) {
            // first insert blocks, use invalid colour
            CLevelFile::SSize const& pos = tPositions[i].pos;
            VColor color = tPositions[i].color;
            SBlockData* pBlock = pLevelData->insertNewBlock(pos.x, pos.y, color);
            if(!pBlock) {
                // For some reason insertion failed
                tPositions.remove(i, numTotalBlocks);
                continue;
            }
        }

        // check for orphans
        for(unsigned int i = 0; i < numTotalBlocks; i++) {
            SBlockData* pBlock = refLevelBlocks[i];
            if(!pBlock->isOrphan()) {
                continue;
            }
            if(isRemoveOrphans()) {
                pLevelData->destroyBlock(pBlock);
                numTotalBlocks--;
                i--;
            } else if(isFixOrphans()) {
                // need to fix this orphan
                // will add any neighbour, wont matter
                RotationDirection anyRot = NO_ROTATION;
                CVector<RotationDirection> rotations;
                unsigned int nRots = pBlock->getValidRotations(rotations);
                unsigned short neighbourX, neighbourY;
                fgBool nSearchStatus = FG_FALSE;
                for(unsigned int rotIdx = 0; rotIdx < nRots; rotIdx++) {
                    nSearchStatus =
                            pBlock->getPotentialNeighbourCoord(rotations[rotIdx],
                                                               neighbourX,
                                                               neighbourY);
                    if(nSearchStatus) {
                        // the coordinate is valid
                        break;
                    }
                }
                SBlockData* pNeighbour = pLevelData->insertNewBlock(neighbourX,
                                                                    neighbourY,
                                                                    VColor::INVALID_COLOR);
                if(pNeighbour) {
                    orphans.push_back(pNeighbour);
                    numOrphans++;
                    numTotalBlocks++;
                }
            } // if(isFixOrphans())
        } // for(i<numTotalBlocks) // orphans
    }
    if(isRegularCheckerboard()) {
        for(unsigned int i = 0; i < numOrphans; i++) {
            SBlockData* pOrphan = orphans[i];
            if(!pOrphan)
                continue;
            unsigned short x = pOrphan->pCellHolder->pos.x;
            unsigned short y = pOrphan->pCellHolder->pos.y;
            // now with the regular checkerboard active
            const fgBool isEven = (fgBool)!!(x % 2 == 0);
            const unsigned int maxColorIdx = m_colorTable.size();
            unsigned int colorIdx = 0;
            if(isEven) {
                colorIdx = maxColorIdx - ((y + 1) % maxColorIdx) - 1;
            } else {
                colorIdx = maxColorIdx - ((y) % maxColorIdx) - 1;
            }
            pOrphan->changeColor(m_colorTable[colorIdx]);
        }
    }
    if(isFullyRandom()) {
        for(unsigned int i = 0; i < numTotalBlocks; i++) {
            SBlockData* pNeighbour = NULL;
            SBlockData* pBlock = refLevelBlocks[i];
            VColor selectedColor = getRandomColor();
            usedColors.clear();
            if(pBlock->color == VColor::INVALID_COLOR) {
                pBlock->changeColor(selectedColor);
                usedColors.push_back(selectedColor);
            }

            // check for color conflicts
            pBlock->getNeighbours(neighbours);
            // need to check for color conflicts
            // if the color does not fit select the opposite
            // if the opposite does not fit - select random, different than
            // opposite and original            
            unsigned int nFails = 0;
            for(unsigned int iN = 0; iN < neighbours.size(); iN++) {
                SNeighbourInfo& nInfo = neighbours[iN];
                if(!nInfo.isValid()) {
                    continue;
                }
                if(pBlock->isRotationValid(nInfo.direction) &&
                   nInfo.ptr->color == pBlock->color) {
                    pNeighbour = nInfo.ptr;

                    FG_LOG_DEBUG("ChainReaction: Generator: Color conflict (%s)->%dx%d",
                                 getColorName(pBlock->color),
                                 pBlock->pCellHolder->pos.x,
                                 pBlock->pCellHolder->pos.y);
                    //VColor opposite = pNeighbour->getOppositeColor();
                    VColor newColor = getRandomColor();
                    //if(usedColors.contains(opposite) || !m_colorTable.contains(opposite)) {
                    if(1) {
                        unsigned int countSearch = 0;
                        while(1) {
                            VColor randomColor = m_colorTable.at(countSearch);
                            if(!usedColors.contains(randomColor)) {
                                newColor = randomColor;
                                break;
                            }
                            countSearch++;
                            if(countSearch >= m_colorTable.size()) {
                                nFails++;
                                FG_LOG_DEBUG("ChainReaction: Generator: Cant select proper color for this node: %dx%d", pBlock->pCellHolder->pos.x, pBlock->pCellHolder->pos.y);
                                break; // ?
                            }
                        }
                    }
                    pBlock->changeColor(newColor);
                    if(!usedColors.contains(newColor)) {
                        usedColors.push_back(newColor);
                    } else {
                        // there is a problem
                        if(!isUsingGrayColor()) {
                            // Gray as a rescue
                            pBlock->changeColor(VColor::GRAY); // #FIXME
                            if(!usedColors.contains(VColor::GRAY))
                                usedColors.push_back(VColor::GRAY);

                            FG_LOG_DEBUG("ChainReaction: Generator: Using gray as a rescue!");
                        }
                        if(nFails > 1 && !isUsingCmyColors() && usedColors.contains(VColor::GRAY)) {
                            pBlock->changeColor(VColor::CYAN);
                            if(!usedColors.contains(VColor::CYAN))
                                usedColors.push_back(pBlock->color);
                            else {
                                pBlock->changeColor(VColor::MAGENTA);
                                if(!usedColors.contains(VColor::MAGENTA))
                                    usedColors.push_back(pBlock->color);
                                else {
                                    pBlock->changeColor(VColor::YELLOW);
                                    if(!usedColors.contains(VColor::YELLOW))
                                        usedColors.push_back(VColor::YELLOW);
                                }
                            }

                            FG_LOG_DEBUG("ChainReaction: Generator: Using %s as a rescue!", getColorName(pBlock->color));
                        }
                        if(nFails > 2) {
                            FG_LOG_DEBUG("ChainReaction: Generator: Number of fails exceeded for this node: %dx%d", pBlock->pCellHolder->pos.x, pBlock->pCellHolder->pos.y);
                            break;
                        }
                    }
                    iN = -1;
                    continue;

                } // if(isRotationValid())
            } // for(iN < neighbours.size())
        } // for(i < numTotalBlocks)

    } // if(isFullyRandom())

    if(status) {
        getLevelFile()->clearBlocks();
        status = (fgBool)!!(getLevelData()->appendTo(getLevelFile()->getBlocks()) > 0);
        getLevelFile()->refreshArea();
    }

    return status;
}
//------------------------------------------------------------------------------

fgBool CLevelGenerator::generateAndSaveToFile(const std::string& filePath) {
    if(filePath.empty())
        return FG_FALSE;
    return generateAndSaveToFile(filePath.c_str());
}
//------------------------------------------------------------------------------

fgBool CLevelGenerator::generateAndSaveToFile(const char* filePath) {
    if(!filePath)
        return FG_FALSE;
    if(!filePath[0])
        return FG_FALSE;
    fgBool status = generate();
    if(status) {
        status = saveToFile(filePath);
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool CLevelGenerator::saveToFile(const std::string& filePath) {
    if(filePath.empty())
        return FG_FALSE;
    return saveToFile(filePath.c_str());
}
//------------------------------------------------------------------------------

fgBool CLevelGenerator::saveToFile(const char* filePath) {
    if(!filePath)
        return FG_FALSE;
    if(!filePath[0])
        return FG_FALSE;
    fgBool status = FG_TRUE;
    m_internalLevelFile->clearBlocks();
    status = (fgBool)!!(getLevelData()->appendTo(m_internalLevelFile->getBlocks()) > 0);
    if(status) {
        m_internalLevelFile->setSize(getLevelFile()->getSize());
        m_internalLevelFile->setLevelIndex(m_genLevelIdx);
        m_internalLevelFile->setLevelType(m_genLevelType);
        status = m_internalLevelFile->save(filePath);
    }
    return status;
}
//------------------------------------------------------------------------------

void CLevelGenerator::setSize(unsigned short x, unsigned short y) {
    if(m_internalLevelFile) {
        m_internalLevelFile->setSize(x, y);
    }
    checkInternals();
    getLevelFile()->setSize(x, y);
}
//------------------------------------------------------------------------------

void CLevelGenerator::setSize(const SSize& size) {
    if(m_internalLevelFile) {
        m_internalLevelFile->setSize(size);
    }
    checkInternals();
    getLevelFile()->setSize(size);
}
//------------------------------------------------------------------------------

VColor CLevelGenerator::getRandomColor(void) const {
    unsigned int index = (unsigned int)FG_RAND(0, m_colorTable.size() - 1);
    return m_colorTable[index];
}
//------------------------------------------------------------------------------

void CLevelGenerator::checkInternals(void) {
    refreshColorTable();
    // now validate color table
    int nMinColors = 2; // minimum of 2 colors for quads
    if(m_genLevelType == LevelType::LEVEL_HEXAGONS) {
        nMinColors = 3;
    }
    int nDiff = m_colorTable.size() - nMinColors;
    if(nDiff < 0) {
        // means that there is not enough colors
        if(!isUsingBlackAndWhiteColors()) {
            useBlackAndWhiteColors();
            refreshColorTable();
        } else if(!isUsingGrayColor() && nDiff == -1) {
            // missing just one color
            useGrayColor();
            refreshColorTable();
        } else if(!isUsingRgbColors()) {
            useRgbColors();
            refreshColorTable();
        } else if(!isUsingCmyColors()) {
            useCmyColors();
            refreshColorTable();
        }
    }
    if(!m_internalLevelFile) {
        m_internalLevelFile = new CLevelFile();
    }
    m_internalLevelFile->setLevelIndex(m_genLevelIdx);
    m_internalLevelFile->setLevelType(m_genLevelType);
    if(isUsingInternalGameGrid()) {
        if(!m_internalGrid) {
            m_internalGrid = new game::CGrid();
        }
    }
    if(isUsingInternalLevelData()) {
        if(!m_internalLevelData) {
            m_internalLevelData = new CLevelDataHolder();
            if(isUsingInternalGameGrid()) {
                m_internalLevelData->setGrid(m_internalGrid);
            } else {
                m_internalLevelData->setGrid(m_pGrid);
            }
            m_internalLevelData->setLevelFile(m_internalLevelFile);
        }
    }
    if(getLevelData()) {
        if(!getLevelData()->getLevelFile()) {
            getLevelData()->setLevelFile(m_internalLevelFile);
        }
        getLevelFile()->setLevelIndex(m_genLevelIdx);
        getLevelFile()->setLevelType(m_genLevelType);
    }
}
//------------------------------------------------------------------------------

void CLevelGenerator::refreshColorTable(void) {
    m_colorTable.clear();
    if(isUsingBlackAndWhiteColors()) {
        m_colorTable.push_back(VColor::BLACK);
        m_colorTable.push_back(VColor::WHITE);
    }
    if(isUsingGrayColor()) {
        m_colorTable.push_back(VColor::GRAY);
    }
    if(isUsingRgbColors()) {
        m_colorTable.push_back(VColor::RED);
        m_colorTable.push_back(VColor::GREEN);
        m_colorTable.push_back(VColor::BLUE);
    }
    if(isUsingCmyColors()) {
        m_colorTable.push_back(VColor::CYAN);
        m_colorTable.push_back(VColor::MAGENTA);
        m_colorTable.push_back(VColor::YELLOW);
    }
}
//------------------------------------------------------------------------------
