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

#include "CLevelGenerator.h"

using namespace fg;
//------------------------------------------------------------------------------

CLevelGenerator::CLevelGenerator() :
m_pGrid(NULL),
m_internalGrid(NULL),
m_pLevelData(NULL),
m_internalLevelData(NULL),
m_internalLevelFile(NULL),
m_colorTable(),
m_genLevelType(LevelType::LEVEL_QUADS),
m_genLevelIdx(1),
m_gridCoverage(0.5f),
m_stateFlags(NO_FLAGS) {
    useBlackAndWhiteColors();

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
}
//------------------------------------------------------------------------------

void CLevelGenerator::clear(void) {
 }
//------------------------------------------------------------------------------

fgBool CLevelGenerator::generate(void) {
    fgBool status = FG_TRUE;

    return status;
}
//------------------------------------------------------------------------------

fgBool CLevelGenerator::generateAndSaveToFile(const std::string& filePath) {
    if(filePath.empty())
        return FG_FALSE;
    fgBool status = FG_TRUE;

    return status;
}
//------------------------------------------------------------------------------

fgBool CLevelGenerator::generateAndSaveToFile(const char* filePath) {
    if(!filePath)
        return FG_FALSE;
    if(!filePath[0])
        return FG_FALSE;
    fgBool status = FG_TRUE;

    return status;
}
//------------------------------------------------------------------------------

fgBool CLevelGenerator::saveToFile(const std::string& filePath) {
    if(filePath.empty())
        return FG_FALSE;
    fgBool status = FG_TRUE;

    return status;
}
//------------------------------------------------------------------------------

fgBool CLevelGenerator::saveToFile(const char* filePath) {
    if(!filePath)
        return FG_FALSE;
    if(!filePath[0])
        return FG_FALSE;
    fgBool status = FG_TRUE;

    return status;
}
//------------------------------------------------------------------------------

void CLevelGenerator::setSize(unsigned short x, unsigned short y) {
    if(m_internalLevelFile) {
        m_internalLevelFile->setSize(x, y);
    }
    getLevelData()->getLevelFile()->setSize(x ,y);
}
//------------------------------------------------------------------------------

void CLevelGenerator::setSize(const CLevelFile::SSize& size) {
    if(m_internalLevelFile) {
        m_internalLevelFile->setSize(size);
    }
    getLevelData()->getLevelFile()->setSize(size);
}
//------------------------------------------------------------------------------

VColor CLevelGenerator::getRandomColor(void) const {
    unsigned int index = (unsigned int)FG_RAND(0, m_colorTable.size() - 1);
    return m_colorTable[index];
}
//------------------------------------------------------------------------------

void CLevelGenerator::checkInternals(void) {
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
}
//------------------------------------------------------------------------------