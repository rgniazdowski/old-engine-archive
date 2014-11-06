/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/*
 * fgQualityManager.cpp
 *
 *  Created on: 02-07-2012
 *      Author: Vigilant
 */

#include "fgQualityManager.h"

#include <cstdlib>
#include <ctime>
#include <cstring>
#include "fgLog.h"
#include "fgHardwareState.h"

/*
 * Default constructor for Quality Manager object
 */
fgQualityManager::fgQualityManager(const int dispArea) :
m_hardwareQuality(FG_QUALITY_DEFAULT),
m_forcedQuality(FG_QUALITY_DEFAULT),
m_selectedQuality(FG_QUALITY_DEFAULT),
m_currentDispArea(dispArea) {

    if(dispArea < 0)
        m_currentDispArea = 1024 * 768;
    m_managerType = FG_MANAGER_QUALITY;
    initialize();
}

/*
 * Default destructor for Quality Manager object
 */
fgQualityManager::~fgQualityManager() {
    destroy();
}

/**
 * 
 */
void fgQualityManager::clear(void) {
    m_displayAreaQuality.clear();
    m_managerType = FG_MANAGER_QUALITY;
}

/**
 * 
 * @return 
 */
fgBool fgQualityManager::destroy(void) {
    fgQualityManager::clear();
    m_init = FG_FALSE;
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool fgQualityManager::initialize(void) {
    determineQuality();
    m_init = FG_TRUE;
    return FG_TRUE;
}

/*
 * Determine quality via screen resolution (this is bound to change in the future)
 */
void fgQualityManager::determineQuality(void) {
    /*
    #low
    240�320     {[S3E]DispAreaQ==76800}
    320x480     {[S3E]DispAreaQ==153600}
    400x800     {[S3E]DispAreaQ==320000}
    480x800     {[S3E]DispAreaQ==384000}
    #medium
    540x960     {[S3E]DispAreaQ==518400}
    640x960     {[S3E]DispAreaQ==614400}
    600x1024    {[S3E]DispAreaQ==614400}
    768x1024    {[S3E]DispAreaQ==786432}
    768x1280    {[S3E]DispAreaQ==983040}
    800x1280    {[S3E]DispAreaQ==1024000}
    #high
    1200x1920   {[S3E]DispAreaQ==2304000}
    1536x2048   {[S3E]DispAreaQ==3145728}
     */
    // 320x240
    m_displayAreaQuality[76800] = FG_QUALITY_LOW;
    // 480x320
    m_displayAreaQuality[153600] = FG_QUALITY_LOW;
    // 400x800
    m_displayAreaQuality[320000] = FG_QUALITY_LOW;
    // 800x480
    m_displayAreaQuality[384000] = FG_QUALITY_LOW;

    // X
    m_displayAreaQuality[400000] = FG_QUALITY_MEDIUM;
    // 800x600
    m_displayAreaQuality[480000] = FG_QUALITY_MEDIUM;
    // 960x540
    m_displayAreaQuality[518400] = FG_QUALITY_MEDIUM;
    // 1024x600 / 960x640
    m_displayAreaQuality[614400] = FG_QUALITY_MEDIUM;
    // 1024x768
    m_displayAreaQuality[786432] = FG_QUALITY_MEDIUM;
    // 1280x768
    m_displayAreaQuality[983040] = FG_QUALITY_MEDIUM;
    // 1280x800
    m_displayAreaQuality[1024000] = FG_QUALITY_MEDIUM;

    // 1920x1080
    m_displayAreaQuality[2073600] = FG_QUALITY_HIGH;
    // 1920x1200
    m_displayAreaQuality[2304000] = FG_QUALITY_HIGH;
    // 2048x1536
    m_displayAreaQuality[3145728] = FG_QUALITY_HIGH;

    // PRETEND insertion of the SEARCHED key
    std::pair<int, fgQuality> query_pair;
    query_pair.first = m_currentDispArea;
    query_pair.second = FG_QUALITY_MEDIUM;
    std::pair < areaQMapItor, bool> result = m_displayAreaQuality.insert(query_pair);

    areaQMapItor it = result.first;
    if(false == result.second) {
        // EXISTED
        m_selectedQuality = it->second;
    } else {
        // NEW INSERTION
        areaQMapItor it_offset = it;
        it_offset++;
        if(it_offset != m_displayAreaQuality.end()) {
            // NEXT IS FINE
            m_selectedQuality = it_offset->second;
        } else {
            // USE PREVIOUS
            it_offset--;
            it_offset--;
            m_selectedQuality = it_offset->second;
        }

        // Store newly deduced value! In the new place.
        it->second = m_selectedQuality;
    }
    m_hardwareQuality = m_selectedQuality;
    std::string qualityname;
    qualityname.clear();
    if(m_hardwareQuality == FG_QUALITY_LOW)
        qualityname = "FG_QUALITY_LOW";
    else if(m_hardwareQuality == FG_QUALITY_MEDIUM)
        qualityname = "FG_QUALITY_MEDIUM";
    else if(m_hardwareQuality == FG_QUALITY_HIGH)
        qualityname = "FG_QUALITY_HIGH";
    else
        qualityname = "FG_QUALITY_INVALID";
    FG_LOG_DEBUG("QUALITY MANAGER - Detected quality: %s, Area: %d", qualityname.c_str(), it->first);
    qualityname.clear();
}
