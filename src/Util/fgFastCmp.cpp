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
 * File:   fgFastCmp.cpp
 * Author: vigilant
 * 
 * Created on December 12, 2014, 8:44 AM
 */

#include "fgFastCmp.h"
#include <cstring>

///
//const fg::util::FastCmp::size_type fg::util::FastCmp::DATA_MAX_RAW_PARTS = 8;
///
//const fg::util::FastCmp::size_type fg::util::FastCmp::DATA_MAX_BITS = 64;

/**
 * 
 * @param numParts
 * @param dataSize
 */
fg::util::FastCmp::FastCmp(const size_type numParts, const DataSize dataSize) :
m_numParts(numParts),
m_data(0) {
    reset(numParts, dataSize);
}

/**
 * 
 * @param orig
 */
fg::util::FastCmp::FastCmp(const FastCmp& orig) {
   this->m_data = orig.m_data;
   this->m_numParts = orig.m_numParts;
   this->m_maxBits = orig.m_maxBits;
   this->m_numPartBits = orig.m_numPartBits;
}

/**
 * 
 */
fg::util::FastCmp::~FastCmp() {
    memset(this, 0, sizeof(FastCmp));
}

/**
 * 
 * @param numParts
 * @param dataSize
 */
void fg::util::FastCmp::reset(const size_type numParts, const DataSize dataSize) {
    if(dataSize == CMP_DATA_64) {
        m_maxBits = (size_type)sizeof(data_type_64)*8;
    } else if(dataSize == CMP_DATA_32) {
        m_maxBits = (size_type)sizeof(data_type_32)*8;
    } else if(dataSize == CMP_DATA_16) {
        m_maxBits = (size_type)sizeof(data_type_16)*8;
    } else {
        clear();
        m_maxBits = 0;
        m_numPartBits = 0;
        m_numParts = 0;
        return;
    }
    m_numParts = numParts;
    if(m_numParts > 64 && dataSize == CMP_DATA_64) {
        m_numParts = 64;
    } else if(m_numParts > 32 && dataSize == CMP_DATA_32) {
        m_numParts = 32;
    } else if(m_numParts > 16 && dataSize == CMP_DATA_16) {
        m_numParts = 16;
    }
    
    if(m_numParts < 2)
        m_numParts = 2;
    
    m_numPartBits = m_maxBits / m_numParts;
    clear();
}

/**
 * 
 * @param partID
 * @param partValue
 */
void fg::util::FastCmp::setPart(size_type partID, data_type_32 partValue) {
    if(partID >= m_numParts || !isValid())
        return;
    size_type shift = partID*m_numPartBits;
    data_type maxValueShifted = ((1 << m_numPartBits) - 1) << shift;
    data_type_32 maxValueShifted32 = (data_type_32)maxValueShifted;
    data_type_16 maxValueShifted16 = (data_type_16)maxValueShifted;
    
    if(m_maxBits == 64) {
        m_data64 |= maxValueShifted;
        m_data64 ^= maxValueShifted;
        m_data64 |= ((data_type_64)partValue) << shift;
    } else if(m_maxBits == 32) {
        m_data32 |= maxValueShifted32;
        m_data32 ^= maxValueShifted32;
        m_data32 |= ((data_type_32)partValue) << shift;
    } else if(m_maxBits == 16) {
        m_data16 |= maxValueShifted16;
        m_data16 ^= maxValueShifted16;
        m_data16 |= ((data_type_16)partValue) << shift;
    }
}
