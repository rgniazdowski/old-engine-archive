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
 * fgQualityManager.cpp
 *
 *  Created on: 02-07-2012
 *      Author: Vigilant
 */

#include "fgQualityManager.h"
#include "fgHardwareState.h"
#include "fgLog.h"

using namespace fg;

//------------------------------------------------------------------------------

CQualityManager::CQualityManager(const int dispArea) :
m_hardwareQuality(FG_QUALITY_DEFAULT),
m_forcedQuality(FG_QUALITY_DEFAULT),
m_selectedQuality(FG_QUALITY_DEFAULT),
m_currentDispArea(dispArea) {

    if(dispArea < 0)
        m_currentDispArea = 1024 * 768;
    m_managerType = FG_MANAGER_QUALITY;
    initialize();
}
//------------------------------------------------------------------------------

CQualityManager::~CQualityManager() {
    destroy();
}
//------------------------------------------------------------------------------

void CQualityManager::clear(void) {
    m_displayAreaQuality.clear();
    m_managerType = FG_MANAGER_QUALITY;
}
//------------------------------------------------------------------------------

fgBool CQualityManager::destroy(void) {
    CQualityManager::clear();
    m_init = FG_FALSE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CQualityManager::initialize(void) {
    determineQuality();
    m_init = FG_TRUE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void CQualityManager::determineQuality(void) {
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
    m_displayAreaQuality[76800] = Quality::LOW;
    // 480x320
    m_displayAreaQuality[153600] = Quality::LOW;
    // 400x800
    m_displayAreaQuality[320000] = Quality::LOW;
    // 800x480
    m_displayAreaQuality[384000] = Quality::LOW;

    // X
    m_displayAreaQuality[400000] = Quality::MEDIUM;
    // 800x600
    m_displayAreaQuality[480000] = Quality::MEDIUM;
    // 960x540
    m_displayAreaQuality[518400] = Quality::MEDIUM;
    // 1024x600 / 960x640
    m_displayAreaQuality[614400] = Quality::MEDIUM;
    // 1024x768
    m_displayAreaQuality[786432] = Quality::MEDIUM;
    // 1280x768
    m_displayAreaQuality[983040] = Quality::MEDIUM;
    // 1280x800
    m_displayAreaQuality[1024000] = Quality::MEDIUM;

    // 1920x1080
    m_displayAreaQuality[2073600] = Quality::HIGH;
    // 1920x1200
    m_displayAreaQuality[2304000] = Quality::HIGH;
    // 2048x1536
    m_displayAreaQuality[3145728] = Quality::HIGH;

    // PRETEND insertion of the SEARCHED key
    std::pair<int, Quality> query_pair;
    query_pair.first = m_currentDispArea;
    query_pair.second = Quality::MEDIUM;
    std::pair < AreaQMapItor, bool> result = m_displayAreaQuality.insert(query_pair);

    AreaQMapItor it = result.first;
    if(false == result.second) {
        // EXISTED
        m_selectedQuality = it->second;
    } else {
        // NEW INSERTION
        AreaQMapItor it_offset = it;
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
    if(m_hardwareQuality == Quality::LOW)
        qualityname = "Quality::LOW";
    else if(m_hardwareQuality == Quality::MEDIUM)
        qualityname = "Quality::MEDIUM";
    else if(m_hardwareQuality == Quality::HIGH)
        qualityname = "Quality::HIGH";
    else
        qualityname = "FG_QUALITY_INVALID";
    FG_LOG_DEBUG("QUALITY MANAGER - Detected quality: %s, Area: %d", qualityname.c_str(), it->first);
    qualityname.clear();
}
//------------------------------------------------------------------------------
