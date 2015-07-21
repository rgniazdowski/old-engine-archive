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
#include "Util/fgFile.h"
#include "Util/fgStrings.h"

using namespace fg;
//------------------------------------------------------------------------------

CLevelFile::CLevelFile(const char* filePath) :
m_levelIdx(-1),
m_type(LEVEL_QUADS),
m_filePath(),
m_size(),
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
            std::sscanf(line.c_str(), "%dx%d", &rx, &ry);
            if(rx >= USHRT_MAX || ry >= USHRT_MAX) {
                status = FG_FALSE;
                continue;
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
            quadInfo.color = (BlockColor)color;
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

fgBool CLevelFile::applyToGrid(game::CGrid* pGrid) {
    if(!pGrid || !isValid()) {
        return FG_FALSE;
    }
    fgBool status = FG_TRUE;
    unsigned int n = getBlocksCount();
    pGrid->resize(m_size.x, m_size.y);
    for(unsigned int i = 0; i < n && status; i++) {
        SBlockInfo& quadInfo = m_blocks[i];
        status = pGrid->setCellValue((unsigned short)quadInfo.color,
                                     quadInfo.pos.x,
                                     quadInfo.pos.y);
        // cell additional data?
    }
    return status;
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
    x = m_area.size.x;
    y = m_area.size.y;
}
//------------------------------------------------------------------------------

void CLevelFile::getAreaSize(unsigned short* x, unsigned short* y) {
    if(x)
        *x = m_area.size.x;
    if(y)
        *y = m_area.size.y;
}
//------------------------------------------------------------------------------

void CLevelFile::getAreaMin(unsigned short& x, unsigned short& y) {
    x = m_area.min.x;
    y = m_area.min.y;
}
//------------------------------------------------------------------------------

void CLevelFile::getAreaMin(unsigned short* x, unsigned short* y) {
    if(x)
        *x = m_area.min.x;
    if(y)
        *y = m_area.min.y;
}
//------------------------------------------------------------------------------

void CLevelFile::getAreaMax(unsigned short& x, unsigned short& y) {
    x = m_area.max.x;
    y = m_area.max.y;
}
//------------------------------------------------------------------------------

void CLevelFile::getAreaMax(unsigned short* x, unsigned short* y) {
    if(x)
        *x = m_area.max.x;
    if(y)
        *y = m_area.max.y;
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
