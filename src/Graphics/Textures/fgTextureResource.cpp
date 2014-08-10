/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgTextureResource.h"
#include "fgTextureLoader.h"

/**

 * Check for glGetError() and conditionally returns false
 * (but only for DEBUG builds)
 */
/*
bool fgTexture::checkGlError(const char* fname) {
    GLenum code;

    code = glGetError();
    if(GL_NO_ERROR != code) {
        FG_ErrorLog("%s() failed! Code=%d, TexId=%d",fname, code, m_texId);

#ifdef IW_DEBUG
        return false;
#endif

    }
    return true;
}
*/

/*
 * Clears the class data, this actually does not free allocated memory, just resets base class attributes
 */
void fgTextureResource::clear(void)
{
	FG_WriteLog("fgTextureResource::clear();");
	fgResource::clear();
	m_fileType = FG_TEXTURE_FILE_INVALID;
	m_textureType = FG_TEXTURE_INVALID;
	m_pixelFormat = FG_TEXTURE_PIXEL_INVALID;
    m_rawData = NULL;
    m_width = 0;
	m_height = 0;
    m_components = -1;
	m_textureGfxID = 0;
	m_resType = FG_RESOURCE_TEXTURE;
}

/*
 * Create function loads/interprets data from file in ROM and place it in RAM memory.
 */
bool fgTextureResource::create(void)
{
	if(m_filePath.empty()) {
		// #TODO error handling / reporting
		return false;
	}
	if(m_fileType == FG_TEXTURE_FILE_INVALID) {
		// #TODO error handling / reporting
		return false;
	}
	switch(m_fileType)
	{
	case FG_TEXTURE_FILE_BMP:
		break;
	case FG_TEXTURE_FILE_RAW:
		break;
	case FG_TEXTURE_FILE_JPEG:
		m_rawData = fgTextureLoader::loadJPEG(m_filePath.c_str(), m_width, m_height);
		break;
	case FG_TEXTURE_FILE_PNG:
		m_rawData = fgTextureLoader::loadPNG(m_filePath.c_str(), m_width, m_height);
		break;
	case FG_TEXTURE_FILE_TGA:
		m_rawData = fgTextureLoader::loadTGA(m_filePath.c_str(), m_width, m_height);
		break;
	case FG_TEXTURE_FILE_OTHER:
		return false;
		break;
	default:
		return false;
		break;
	};

	if(!m_rawData) {
		// #TODO error handling / reporting
		return false;
	}
	m_isReady = true;
	// #FIXME
	m_components = FG_TEXTURE_COMP_RGBA;
	// #FIXME size calculation
	m_size = sizeof(unsigned char) * m_width * m_height * m_components;
	return true;
}

/*
 * Destroy all loaded data including additional metadata (called with deconstructor)
 */
void fgTextureResource::destroy(void)
{
	FG_WriteLog("fgTextureResource::destroy();");
	releaseNonGFX();
	clear();
}

/*
 * Reloads any data, recreates the resource (refresh)
 */
bool fgTextureResource::recreate(void)
{
	releaseNonGFX();
	return create();
}

/*
 * Dispose completely of the all loaded data, free all memory
 * Releases non-GPU side of resources
 */
void fgTextureResource::dispose(void)
{
	FG_WriteLog("fgTextureResource::~dispose();");
	releaseNonGFX();
}

/*
 * Check if resource is disposed (not loaded yet or disposed after)
 */
bool fgTextureResource::isDisposed(void) const
{
	// #FIXME ?
	// This should also check if texture (GL/GFX) ID is valid.
	// If it is, then it means that the texture is uploaded and
	// ready to use. If GfxID is invalid than we can assume that
	// resource is disposed. This is kinda tricky one.
	
	return !this->hasOwnedRAM();
}

/*
 * Releases non-GPU side of resources
 */
void fgTextureResource::releaseNonGFX(void) 
{
	if(m_rawData)
		delete [] m_rawData;
	m_width = 0;
	m_height = 0;
	m_components = 0;
	m_size = 0;
	m_isReady = false;
}
