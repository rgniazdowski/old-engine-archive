/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
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

#include "../fgCommon.h"
#include "fgHardwareState.h"

template <>
bool fgSingleton<fgQualityManager>::instanceFlag = false;

template <>
fgQualityManager *fgSingleton<fgQualityManager>::instance = NULL;


// FIXME
// Well this class is quite needed for quality management but it uses predefined texture files which is unacceptable in professional game engine 

fgQualityManager::fgQualityManager()
{
}

fgQualityManager::~fgQualityManager()
{
}

void fgQualityManager::determineQuality(void)
{
	int DispArea = FG_HardwareState->dispArea();
	/*
	#low
	240×320		{[S3E]DispAreaQ==76800}
	320x480		{[S3E]DispAreaQ==153600}
	400x800		{[S3E]DispAreaQ==320000}
	480x800		{[S3E]DispAreaQ==384000}
	#medium
	540x960		{[S3E]DispAreaQ==518400}
	640x960		{[S3E]DispAreaQ==614400}
	600x1024	{[S3E]DispAreaQ==614400}
	768x1024	{[S3E]DispAreaQ==786432}
	768x1280	{[S3E]DispAreaQ==983040}
	800x1280	{[S3E]DispAreaQ==1024000}
	#high
	1200x1920	{[S3E]DispAreaQ==2304000}
	1536x2048	{[S3E]DispAreaQ==3145728}
	*/
	m_displayAreaQuality[76800] = Tex::QUALITY_LOW;
	m_displayAreaQuality[153600] = Tex::QUALITY_LOW;
	m_displayAreaQuality[320000] = Tex::QUALITY_LOW;
	m_displayAreaQuality[384000] = Tex::QUALITY_LOW;

	m_displayAreaQuality[518400] = Tex::QUALITY_MEDIUM;
	m_displayAreaQuality[614400] = Tex::QUALITY_MEDIUM;
	m_displayAreaQuality[786432] = Tex::QUALITY_MEDIUM;
	m_displayAreaQuality[983040] = Tex::QUALITY_MEDIUM;
	m_displayAreaQuality[1024000] = Tex::QUALITY_MEDIUM;

	m_displayAreaQuality[2304000] = Tex::QUALITY_HIGH;
	m_displayAreaQuality[3145728] = Tex::QUALITY_HIGH;

	m_selectedQuality = Tex::QUALITY_MEDIUM;

    // PRETEND insertion of the SEARCHED key
    std::pair<int, Tex::Quality> query_pair;
    query_pair.first = DispArea;
    query_pair.second = Tex::QUALITY_MEDIUM;
    typedef std::map<int, Tex::Quality> MyMap;
    std::pair<MyMap::iterator, bool> result = m_displayAreaQuality.insert(query_pair);

    MyMap::iterator it = result.first;
    if ( false == result.second ) {
        // EXISTED
        m_selectedQuality = it->second;
    } else {
        // NEW INSERTION
        MyMap::iterator it_offset = it;
        it_offset ++;
        if ( it_offset != m_displayAreaQuality.end() ) {
            // NEXT IS FINE
            m_selectedQuality = it_offset->second;
        } else {
            // USE PREVIOUS
            it_offset --;
            it_offset --;
            m_selectedQuality = it_offset->second;
        }

        // Store newly deduced value! In the new place.
        it->second = m_selectedQuality;
    }

//	m_textureFileName[Tex::ARROW1_TEXTURE]		= "arrow1_32.tga";
//	m_textureFileName[Tex::BLOCK_TEXTURE]		= "block0.tga";
	m_textureFileName[Tex::PULSE_TEXTURE]		= "shockwave1.tga";
	m_textureFileName[Tex::DEBRIS_SHEET_TEXTURE]= "debris0_sheet.tga";	// DEBRIS_SHEET_TEXTURE (3x3)
	m_textureFileName[Tex::FLAME_SHEET_TEXTURE]	= "flame0_sheet.tga";	// FLAME_SHEET_TEXTURE (2x2)
	m_textureFileName[Tex::FLASH_SHEET_TEXTURE]	= "flash0_sheet.tga";	// FLASH_SHEET_TEXTURE (2x2)
	m_textureFileName[Tex::SMOKETRAIL_TEXTURE]	= "smoketrail0.tga";	// SMOKETRAIL_TEXTURE (1x1)
	m_textureFileName[Tex::ROUNDSPARK_TEXTURE]	= "roundspark0.tga";	// ROUNDSPARK_TEXTURE	(1x1)
	m_textureFileName[Tex::SHOCKWAVE_TEXTURE]	= "shockwave0.tga";		// SHOCKWAVE_TEXTURE	(1x1)
	m_textureFileName[Tex::SPARK_TEXTURE]		= "spark0.tga";			// SPARK_TEXTURE (1x1)
	m_textureFileName[Tex::EXPLOSION_SEQUENCE_TEXTURE] = "explosion1_1024.tga"; // EXPLOSION_SEQUENCE_TEXTURE (8x8 -> 8x6)
	m_textureFileName[Tex::FIRE_SEQUENCE_TEXTURE]	= "fire1_512.tga";	// FIRE_SEQUENCE_TEXTURE (5x5)
	m_textureFileName[Tex::SKYBOX_TEXTURE]			= "plasma_galaxy_1024.jpg";		// SKYBOX_TEXTURE FIXME
	m_textureFileName[Tex::HUD_BOTTOM_TEXTURE]		= "hud_bottom_1024.tga";	// HUD_BOTTOM_TEXTURE
	m_textureFileName[Tex::HUD_CENTER_TEXTURE]		= "hud_center_512.tga";		// HUD_CENTER_TEXTURE
	m_textureFileName[Tex::HUD_LINES_TEXTURE]		= "hud_lines_1024.tga";		// HUD_LINES_TEXTURE
	m_textureFileName[Tex::HUD_TOP_TEXTURE]			= "hud_top_1024.tga";		// HUD_TOP_TEXTURE
	//m_textureFileName[Tex::LEVEL_TEXTURE]			= "level/ImageEmpty.tga";	// LEVEL_TEXTURE

	switch(m_selectedQuality)
	{
	case Tex::QUALITY_LOW:
		FG_WriteLog("SELECTED LOW QUALITY (DispArea: %d)", DispArea);
		m_textureFileName[Tex::BACKGROUND_TEXTURE]	= "BackgroundCrate_1024x512.jpg";
		m_textureFileName[Tex::FONT_MAIN_TEXTURE]	= "CarbonType_512.tga";
		m_textureFileName[Tex::FONT_SECONDARY_TEXTURE] = "CaptureIt_512.tga";
            
		break;
	case Tex::QUALITY_MEDIUM:
		FG_WriteLog("SELECTED MEDIUM QUALITY (DispArea: %d)", DispArea);
		m_textureFileName[Tex::BACKGROUND_TEXTURE]	= "BackgroundCrate_1024x512.jpg";
		m_textureFileName[Tex::FONT_MAIN_TEXTURE]	= "CarbonType_1024.tga";
		m_textureFileName[Tex::FONT_SECONDARY_TEXTURE] = "CaptureIt_1024.tga";

		break;
	case Tex::QUALITY_HIGH:
		FG_WriteLog("SELECTED HIGH QUALITY (DispArea: %d)", DispArea);
		m_textureFileName[Tex::BACKGROUND_TEXTURE]	= "BackgroundCrate_1024x512.jpg";
		m_textureFileName[Tex::FONT_MAIN_TEXTURE]	= "CarbonType_2048.tga";
		m_textureFileName[Tex::FONT_SECONDARY_TEXTURE] = "CaptureIt_2048.tga";

		break;
	default:
		break;
	}
}

std::string & fgQualityManager::getFileName(int texture_id)
{
	static std::string filename;
	filename = "\0";
	std::map<int, std::string>::iterator found = m_textureFileName.find(texture_id);
	if(found != m_textureFileName.end())
		return found->second;
	return filename;
}

void fgQualityManager::setFileName(int texture_id, const char *filename)
{
	m_textureFileName[texture_id] = std::string(filename);
	FG_WriteLog("fgQualityManager::setFileName(): ID: %d, filename: '%s'", texture_id, filename);
}

int fgQualityManager::getTextureID(const char *filename)
{
	typedef std::map<int, std::string> MyMap;
	for(MyMap::iterator it = m_textureFileName.begin();
		it != m_textureFileName.end();
		it++)
	{
		if(strcmp(it->second.c_str(), filename) == 0)
		{
			FG_WriteLog("fgQualityManager::getTextureID() found the texture ID for '%s': %d", filename, it->first);
			return it->first;
		}
	}
	return 0;
}