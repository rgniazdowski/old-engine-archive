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
 * File:   CLevelSolution.cpp
 * Author: vigilant
 * 
 * Created on July 28, 2015, 6:10 PM
 */

#include "CLevelSolution.h"
#include "Util/fgFile.h"
#include "fgLog.h"

using namespace fg;
//------------------------------------------------------------------------------

CLevelSolution::CLevelSolution() :
m_levelType(LEVEL_INVALID),
m_levelIdx(-1),
m_size(),
m_filePath(),
m_moves() {
    m_moves.reserve(16);
}
//------------------------------------------------------------------------------

CLevelSolution::CLevelSolution(const CLevelSolution& orig) {
    this->m_levelType = orig.m_levelType;
    this->m_levelIdx = orig.m_levelIdx;
    this->m_size = orig.m_size;
    this->m_filePath = orig.m_filePath;
    this->m_moves.append(orig.m_moves);
}
//------------------------------------------------------------------------------

CLevelSolution::~CLevelSolution() {
    clear();
}
//------------------------------------------------------------------------------

void CLevelSolution::clear(void) {
    m_moves.clear();
}
//------------------------------------------------------------------------------

fgBool CLevelSolution::load(void) {
    if(m_filePath.empty()) {
        return FG_FALSE;
    }
    fgBool status = FG_TRUE;
    clear();
    unsigned int nMoves = 0;
    util::CFile solutionFile;
    solutionFile.setPath(m_filePath);
    status = solutionFile.open(util::CFile::Mode::BINARY | util::CFile::Mode::READ);
    if(status) {
        status = status && (solutionFile.read((void*)&m_levelType, sizeof (LevelType), 1) == 1);
        status = status && (solutionFile.read((void*)&m_levelIdx, sizeof (int), 1) == 1);
        status = status && (solutionFile.read((void*)&m_size, sizeof (SSize), 1) == 1);
        status = status && (solutionFile.read((void*)&nMoves, sizeof (unsigned int), 1) == 1);
    }
    if(nMoves < 1 || nMoves > USHRT_MAX) {
        status = FG_FALSE;
        solutionFile.close();
    }
    if(status) {
        if(m_moves.capacity() < nMoves)
            m_moves.reserve(nMoves + 1);
        void* dataPtr = (void*)(&m_moves.front());
        status = status && (solutionFile.read((void*)dataPtr, sizeof (ElementType), nMoves) == nMoves);
    }

    status = status && solutionFile.close();
    return status;
}
//------------------------------------------------------------------------------

fgBool CLevelSolution::load(const std::string& filePath) {
    if(filePath.empty()) {
        return FG_FALSE;
    }
    setFilePath(filePath);
    return load();
}
//------------------------------------------------------------------------------

fgBool CLevelSolution::load(const char* filePath) {
    if(!filePath) {
        return FG_FALSE;
    }
    if(!filePath[0]) {
        return FG_FALSE;
    }
    setFilePath(filePath);
    return load();
}
//------------------------------------------------------------------------------

fgBool CLevelSolution::save(void) {
    if(m_filePath.empty()) {
        return FG_FALSE;
    }
    if(isEmpty())
        return FG_FALSE;
    fgBool status = FG_TRUE;
    const unsigned int nMoves = this->count();
    util::CFile solutionFile;
    solutionFile.setPath(m_filePath);
    status = solutionFile.open(util::CFile::Mode::BINARY | util::CFile::Mode::WRITE);

    if(status) {
        status = status && (solutionFile.write((void*)&m_levelType, sizeof (LevelType), 1) == 1);
        status = status && (solutionFile.write((void*)&m_levelIdx, sizeof (int), 1) == 1);
        status = status && (solutionFile.write((void*)&m_size, sizeof (SSize), 1) == 1);
        status = status && (solutionFile.write((void*)&nMoves, sizeof (unsigned int), 1) == 1);
    }

    if(status) {
        void* dataPtr = (void*)(&m_moves.front());
        status = status && (solutionFile.write((void*)dataPtr, sizeof (ElementType), nMoves) == nMoves);
    }

    status = status && solutionFile.close();
    return status;
}
//------------------------------------------------------------------------------

fgBool CLevelSolution::save(const std::string& filePath) {
    if(filePath.empty()) {
        return FG_FALSE;
    }
    setFilePath(filePath);
    return save();
}
//------------------------------------------------------------------------------

fgBool CLevelSolution::save(const char* filePath) {
    if(!filePath) {
        return FG_FALSE;
    }
    if(!filePath[0]) {
        return FG_FALSE;
    }
    setFilePath(filePath);
    return save();
}
//------------------------------------------------------------------------------

fgBool CLevelSolution::setFromSearchSteps(const MoveStepsVec& searchSteps) {
    if(searchSteps.empty()) {
        return FG_FALSE;
    }
    unsigned int n = searchSteps.size();
    m_moves.clear();
    if(m_moves.capacity() < n)
        m_moves.reserve(n + 1);
    for(unsigned int i = 0; i < n; i++) {
        SBlockMoveStep* pStep = searchSteps[i];
        if(!pStep)
            continue;
        if(!pStep->isValid())
            continue;
        SBlockMoveInfo* pInfo = pStep;
        m_moves.push_back(*pInfo);
        m_moves.back().pData = NULL;
    }
    BlockType blockType = m_moves[0].blockType;
    m_levelType = cr::getLevelTypeFromBlockType(blockType);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

BlockType CLevelSolution::getBlockType(void) const {
    BlockType blockType = BlockType::BLOCK_INVALID;
    if(m_moves.empty()) {
        blockType = cr::getBlockTypeFromLevelType(m_levelType);
    } else {
        blockType = m_moves[0].blockType;
    }
    return blockType;
}
//------------------------------------------------------------------------------

#if defined(DEBUG) || defined(FG_DEBUG)

void CLevelSolution::dump(void) {
    if(m_moves.empty())
        return;
    const unsigned int n = count();
    FG_LOG_DEBUG("CR: Solution has %d steps:", n);
    for(unsigned int i=0;i<n;i++) {
        ElementType& moveInfo = m_moves[i];
        FG_LOG_DEBUG("CR: %d: move block from [%dx%d] to [%dx%d] -> %s", i,
                     moveInfo.pos.x,
                     moveInfo.pos.y,
                     moveInfo.target.x,
                     moveInfo.target.y,
                     cr::getRotationName(moveInfo.moveDir));
    }
}
#endif
//------------------------------------------------------------------------------
