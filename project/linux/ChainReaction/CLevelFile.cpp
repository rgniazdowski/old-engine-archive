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
 * File:   CLevelFile.cpp
 * Author: vigilant
 * 
 * Created on July 15, 2015, 9:57 PM
 */

#include <climits>
#include "CLevelFile.h"

#include "GameLogic/fgGrid.h"
#include "Util/fgMemory.h"
#include "Util/fgFile.h"
#include "Util/fgStrings.h"
#include "fgLog.h"

using namespace fg;
//------------------------------------------------------------------------------

CLevelFile::CLevelFile(const char* filePath) :
m_filePath(),
m_blocks(),
m_levelIdx(-1),
m_type(LEVEL_QUADS),
m_size() {
    setFilePath(filePath);
    m_blocks.reserve(48);
    m_size.x = 0;
    m_size.y = 0;
    m_area.min.x = USHRT_MAX;
    m_area.min.y = USHRT_MAX;
    m_area.max.x = 0;
    m_area.max.y = 0;
    m_area.size.x = 0;
    m_area.size.y = 0;
}
//------------------------------------------------------------------------------

CLevelFile::CLevelFile(const std::string& filePath) :
m_levelIdx(-1),
m_filePath(),
m_blocks() {
    setFilePath(filePath);
    m_blocks.reserve(48);
    m_size.x = 0;
    m_size.y = 0;
    m_area.min.x = USHRT_MAX;
    m_area.min.y = USHRT_MAX;
    m_area.max.x = 0;
    m_area.max.y = 0;
    m_area.size.x = 0;
    m_area.size.y = 0;
}
//------------------------------------------------------------------------------

CLevelFile::CLevelFile(const CLevelFile& orig) {
    this->m_blocks.reserve(48);
    this->m_size.x = orig.m_size.x;
    this->m_size.y = orig.m_size.y;
    this->m_area = orig.m_area;
    this->m_levelIdx = orig.m_levelIdx;
    this->setFilePath(orig.m_filePath);
    unsigned int n = orig.m_blocks.size();
    for(unsigned int i = 0; i < n; i++) {
        this->m_blocks.push_back(orig.m_blocks[i]);
    }
}
//------------------------------------------------------------------------------

CLevelFile::~CLevelFile() {
    reset();
}
//------------------------------------------------------------------------------

fgBool CLevelFile::load(void) {
    if(m_filePath.empty()) {
        return FG_FALSE;
    }
    fgBool status = FG_TRUE;
    util::CFile levelFile;
    levelFile.setPath(m_filePath);
    char *fileData = levelFile.load();
    if(!fileData) {
        m_size.x = 0;
        m_size.y = 0;
        m_levelIdx = -1;
        return FG_FALSE;
    }
    CStringVector lines;
    strings::split(std::string(fileData), '\n', lines);
    unsigned int n = lines.size();
    int xPos = 0, yPos = 0;
    if(!n) {
        status = FG_FALSE;
    } else {
        clear();
    }
    for(unsigned int i = 0; i < n && status; i++) {
        std::string line = strings::trim(lines[i]);
        if(i == 0) {
            // the first line is supposed to contain full grid size
            int rx, ry;
            char mapType[16];
            memset(mapType, 0, 16);
            std::sscanf(line.c_str(), "%dx%d %d %s", &rx, &ry, &m_levelIdx, mapType);
            if(rx >= USHRT_MAX || ry >= USHRT_MAX) {
                status = FG_FALSE;
                continue;
            }
            if(strings::startsWith(mapType, "hex\0", FG_FALSE)) {
                m_type = LevelType::LEVEL_HEXAGONS;
            } else if(strings::startsWith(mapType, "quad\0", FG_FALSE)) {
                m_type = LevelType::LEVEL_QUADS;
            } else {
                m_type = LevelType::LEVEL_QUADS;
            }
            m_size.x = rx;
            m_size.y = ry;
            continue;
        }
        if(line.length() < m_size.x) {
            continue;
        }
        for(xPos = 0; xPos < m_size.x; xPos++) {
            int color = (int)line[xPos] - 48;
            if(color <= MIN_COLOR_ID || color > MAX_COLOR_ID) {
                // skip everything - except 1 and 2
                continue; // ?
            }
            SBlockInfo quadInfo;
            quadInfo.color = (VColor)color;
            quadInfo.pos.x = xPos;
            quadInfo.pos.y = yPos;
            m_area.max.x = MAX(m_area.max.x, xPos);
            m_area.max.y = MAX(m_area.max.y, yPos);
            m_area.min.x = MIN(m_area.min.x, xPos);
            m_area.min.y = MIN(m_area.min.y, yPos);
            m_blocks.push_back(quadInfo);
        }
        yPos++;
    }
    if(!status) {
        m_size.x = 0;
        m_size.y = 0;
        m_levelIdx = -1;
    } else {
        // this size tells the number of elements
        // min/max store indexes (start from 0)
        m_area.size.x = m_area.max.x - m_area.min.x + 1;
        m_area.size.y = m_area.max.y - m_area.min.y + 1;
    }
    return status;
}
//------------------------------------------------------------------------------

void CLevelFile::refreshArea(void) {
    if(m_blocks.empty())
        return;

    m_area.min.x = USHRT_MAX;
    m_area.min.y = USHRT_MAX;
    m_area.max.x = 0;
    m_area.max.y = 0;
    m_area.size.x = 0;
    m_area.size.y = 0;
    const unsigned int n = m_blocks.size();
    for(unsigned int i = 0; i < n; i++) {
        const SBlockInfo& blockInfo = m_blocks[i];
        const unsigned short xPos = blockInfo.pos.x;
        const unsigned short yPos = blockInfo.pos.y;
        m_area.max.x = MAX(m_area.max.x, xPos);
        m_area.max.y = MAX(m_area.max.y, yPos);
        m_area.min.x = MIN(m_area.min.x, xPos);
        m_area.min.y = MIN(m_area.min.y, yPos);
    }
    m_area.size.x = m_area.max.x - m_area.min.x + 1;
    m_area.size.y = m_area.max.y - m_area.min.y + 1;
}
//------------------------------------------------------------------------------

fgBool CLevelFile::load(const char* filePath) {
    if(!filePath) {
        return FG_FALSE;
    }
    if(!filePath[0])
        return FG_FALSE;
    setFilePath(filePath);
    return load();
}
//------------------------------------------------------------------------------

fgBool CLevelFile::load(const std::string& filePath) {
    if(filePath.empty()) {
        return FG_FALSE;
    }
    setFilePath(filePath);
    return load();
}

//------------------------------------------------------------------------------

fgBool CLevelFile::save(void) {
    if(m_filePath.empty() || m_blocks.empty()) {
        return FG_FALSE;
    }
    const unsigned short x = m_size.x;
    const unsigned short y = m_size.y;
    if(!x || !y) {
        FG_LOG_DEBUG("ChainReaction: Failed to save level file: '%s'. Level size is not set.", m_filePath.c_str());
        return FG_FALSE;
    }
    fgBool status = FG_TRUE;
    util::CFile levelFile;
    levelFile.setPath(m_filePath);
    status = levelFile.open(util::CFile::Mode::WRITE);
    if(!status) {
        FG_LOG_DEBUG("ChainReaction: Failed to save level file: '%s'", m_filePath.c_str());
        return status;
    }
    char** strData;
    strData = (char **)fgMalloc<char*>(y);
    if(strData) {
        for(unsigned short i = 0; i < y; i++) {
            strData[i] = (char*)fgMalloc<char>(x + 1);
            for(unsigned short c = 0; c < x; c++) {
                strData[i][c] = '0';
            }
            strData[i][x] = '\0';
        }
    } else {
        status = FG_FALSE;
        levelFile.close();
    }
    const unsigned int n = m_blocks.size();
    for(unsigned int i = 0; i < n; i++) {
        SBlockInfo const& blockInfo = m_blocks[i];
        if(blockInfo.pos.x >= x || blockInfo.pos.y >= y)
            continue;
        const char numC = '0' + (char)blockInfo.color;
        strData[blockInfo.pos.y][blockInfo.pos.x] = numC;
    }
    const char* levelType = NULL;
    if(m_type == LevelType::LEVEL_QUADS) {
        levelType = "quads\0";
    } else if(m_type == LevelType::LEVEL_HEXAGONS) {
        levelType = "hexagons\0";
    } else {
        levelType = "quads\0"; // Force quads
    }

    levelFile.print("%dx%d %d %s\n", x, y, m_levelIdx, levelType);
    for(unsigned short i = 0; i < y; i++) {
        levelFile.print("%s\n", strData[i]);
        memset(strData[i], 0, x + 1);
        fgFree<char>(strData[i]);
        strData[i] = NULL;
    }
    fgFree<char *>(strData);
    strData = NULL;
    levelFile.flush();
    levelFile.close();

    return status;
}
//------------------------------------------------------------------------------

fgBool CLevelFile::save(const char* filePath) {
    if(!filePath) {
        return FG_FALSE;
    }
    if(!filePath[0])
        return FG_FALSE;
    setFilePath(filePath);
    return save();
}
//------------------------------------------------------------------------------

fgBool CLevelFile::save(const std::string& filePath) {
    if(filePath.empty()) {
        return FG_FALSE;
    }
    setFilePath(filePath);
    return save();
}
//------------------------------------------------------------------------------

fgBool CLevelFile::applyToGrid(game::CGrid* pGrid) {
    if(!pGrid || !isValid()) {
        return FG_FALSE;
    }
    fgBool status = FG_TRUE;
    const unsigned int n = getBlocksCount();
    pGrid->resize(m_size.x, m_size.y);
    for(unsigned int i = 0; i < n && status; i++) {
        SBlockInfo& blockInfo = m_blocks[i];
        status = pGrid->setCellValue((unsigned short)blockInfo.color,
                                     blockInfo.pos.x,
                                     blockInfo.pos.y);
        // cell additional data?
    }
    return status;
}
//------------------------------------------------------------------------------

void CLevelFile::setSize(unsigned short x, unsigned short y) {
    m_size.x = x;
    m_size.y = y;
}
//------------------------------------------------------------------------------

void CLevelFile::setSize(const SSize& size) {
    m_size.x = size.x;
    m_size.y = size.y;
}
//------------------------------------------------------------------------------

void CLevelFile::getSize(unsigned short& x, unsigned short& y) {
    x = m_size.x;
    y = m_size.y;
}
//------------------------------------------------------------------------------

void CLevelFile::getSize(unsigned short* x, unsigned short* y) {
    if(x)
        *x = m_size.x;
    if(y)
        *y = m_size.y;
}
//------------------------------------------------------------------------------

void CLevelFile::getAreaSize(unsigned short& x, unsigned short& y) {
    const fgBool dummy = (fgBool)!!(m_blocks.empty() && m_size.x != 0 && m_size.y != 0);
    if(!dummy) {
        x = m_area.size.x;
        y = m_area.size.y;
    } else {
        x = m_size.x;
        y = m_size.y;
    }
}
//------------------------------------------------------------------------------

void CLevelFile::getAreaSize(unsigned short* x, unsigned short* y) {
    const fgBool dummy = (fgBool)!!(m_blocks.empty() && m_size.x != 0 && m_size.y != 0);
    if(x) {
        if(!dummy)
            *x = m_area.size.x;
        else
            *x = m_size.x;
    }
    if(y) {
        if(!dummy)
            *y = m_area.size.y;
        else
            *y = m_size.y;
    }
}
//------------------------------------------------------------------------------

void CLevelFile::getAreaMin(unsigned short& x, unsigned short& y) {
    const fgBool dummy = (fgBool)!!(m_blocks.empty() && m_size.x != 0 && m_size.y != 0);
    if(!dummy) {
        x = m_area.min.x;
        y = m_area.min.y;
    } else {
        x = 0;
        y = 0;
    }
}
//------------------------------------------------------------------------------

void CLevelFile::getAreaMin(unsigned short* x, unsigned short* y) {
    const fgBool dummy = (fgBool)!!(m_blocks.empty() && m_size.x != 0 && m_size.y != 0);
    if(x) {
        if(!dummy)
            *x = m_area.min.x;
        else
            *x = 0;
    }
    if(y) {
        if(!dummy)
            *y = m_area.min.y;
        else
            *y = 0;
    }
}
//------------------------------------------------------------------------------

void CLevelFile::getAreaMax(unsigned short& x, unsigned short& y) {
    const fgBool dummy = (fgBool)!!(m_blocks.empty() && m_size.x != 0 && m_size.y != 0);
    if(!dummy) {
        x = m_area.max.x;
        y = m_area.max.y;
    } else {
        x = m_size.x - 1;
        y = m_size.y - 1;
    }
}
//------------------------------------------------------------------------------

void CLevelFile::getAreaMax(unsigned short* x, unsigned short* y) {
    const fgBool dummy = (fgBool)!!(m_blocks.empty() && m_size.x != 0 && m_size.y != 0);
    if(x) {
        if(!dummy)
            *x = m_area.max.x;
        else
            *x = m_size.y - 1;
    }
    if(y) {
        if(!dummy)
            *y = m_area.max.y;
        else
            *y = m_size.y - 1;
    }
}
//------------------------------------------------------------------------------

void CLevelFile::clear(void) {
    m_levelIdx = -1;
    m_size.x = 0;
    m_size.y = 0;
    m_area.min.x = USHRT_MAX;
    m_area.min.y = USHRT_MAX;
    m_area.max.x = 0;
    m_area.max.y = 0;
    m_area.size.x = 0;
    m_area.size.y = 0;
    m_blocks.clear();
}
//------------------------------------------------------------------------------

void CLevelFile::clearBlocks(void) {
    m_blocks.clear();
}
//------------------------------------------------------------------------------

int CLevelFile::appendBlocks(BlockInfoVec const& inBlocks, fgBool shouldResize) {
    if(m_size.x == 0 | m_size.y == 0) {
        return -1;
    }
    int nAppend = 0;
    unsigned int n = inBlocks.size();
    for(unsigned int i = 0; i < n; i++) {
        SBlockInfo const& blockInfo = inBlocks[i];
        if(blockInfo.pos.x < m_size.x &&
           blockInfo.pos.y < m_size.y) {
            if(!contains(blockInfo.pos)) {
                m_blocks.push_back(blockInfo);
                nAppend++;
            }
        }
    }

    return nAppend;
}
//------------------------------------------------------------------------------

fgBool CLevelFile::contains(unsigned short x, unsigned short y) const {
    if(m_blocks.empty())
        return FG_FALSE;
    fgBool status = FG_FALSE;
    BlockInfoVecConstItor itor = m_blocks.begin();
    BlockInfoVecConstItor end = m_blocks.end();
    for(; itor != end; itor++) {
        SBlockInfo const& blockInfo = *itor;
        if(blockInfo.pos.x == x && blockInfo.pos.y == y) {
            status = FG_TRUE;
            break;
        }
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool CLevelFile::contains(const SSize& pos) const {
    if(m_blocks.empty())
        return FG_FALSE;
    fgBool status = FG_FALSE;
    BlockInfoVecConstItor itor = m_blocks.begin();
    BlockInfoVecConstItor end = m_blocks.end();
    for(; itor != end; itor++) {
        SBlockInfo const& blockInfo = *itor;
        if(blockInfo.pos == pos) {
            status = FG_TRUE;
            break;
        }
    }
    return status;
}
//------------------------------------------------------------------------------

void CLevelFile::setFilePath(const char* filePath) {
    if(filePath) {
        m_filePath.clear();
        m_filePath.append(filePath);
    }
}
//------------------------------------------------------------------------------

void CLevelFile::setFilePath(const std::string& filePath) {
    if(!filePath.empty()) {
        m_filePath.clear();
        m_filePath.append(filePath);
    }
}
//------------------------------------------------------------------------------
