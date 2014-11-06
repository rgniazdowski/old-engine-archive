/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgTextureResource.h"
#include "fgTextureLoader.h"
#include "Util/fgPath.h"
#include "fgLog.h"

/**

 * Check for glGetError() and conditionally returns false
 * (but only for DEBUG builds)
 */
/*
bool fgTexture::checkGlError(const char* fname) {
    GLenum code;

    code = glGetError();
    if(GL_NO_ERROR != code) {
        FG_LOG::PrintError("%s() failed! Code=%d, TexId=%d",fname, code, m_texId);

#ifdef IW_DEBUG
        return false;
#endif

    }
    return true;
}
 */

/*
 * Base constructor of the texture resource object
 */
fgTextureResource::fgTextureResource() :
fgResource(),
m_fileType(FG_TEXTURE_FILE_INVALID),
m_textureType(FG_TEXTURE_PLAIN),
m_pixelFormat(FG_TEXTURE_PIXEL_INVALID),
m_rawData(NULL),
m_width(0),
m_height(0),
m_components(-1),
m_textureGfxID(0),
m_isInVRAM(FG_FALSE) {
    m_resType = FG_RESOURCE_TEXTURE;
}

/*
 *
 */
fgTextureResource::fgTextureResource(const char *path) :
fgResource(path),
m_fileType(FG_TEXTURE_FILE_INVALID),
m_textureType(FG_TEXTURE_PLAIN),
m_pixelFormat(FG_TEXTURE_PIXEL_INVALID),
m_rawData(NULL),
m_width(0),
m_height(0),
m_components(-1),
m_textureGfxID(0),
m_isInVRAM(FG_FALSE) {
    m_resType = FG_RESOURCE_TEXTURE;
    FG_LOG_DEBUG("fgTextureResource(const char *path)");
}

/*
 *
 */
fgTextureResource::fgTextureResource(std::string& path) :
fgResource(path),
m_fileType(FG_TEXTURE_FILE_INVALID),
m_textureType(FG_TEXTURE_PLAIN),
m_pixelFormat(FG_TEXTURE_PIXEL_INVALID),
m_rawData(NULL),
m_width(0),
m_height(0),
m_components(-1),
m_textureGfxID(0),
m_isInVRAM(FG_FALSE) {
    m_resType = FG_RESOURCE_TEXTURE;
    FG_LOG_DEBUG("fgTextureResource(std::string& path)");
}

/*
 * Clears the class data, this actually does not free allocated memory,
 * just resets base class attributes
 */
void fgTextureResource::clear(void) {
    FG_LOG_DEBUG("fgTextureResource::clear();");
    fgResource::clear();
    m_fileType = FG_TEXTURE_FILE_INVALID;
    m_textureType = FG_TEXTURE_INVALID;
    m_pixelFormat = FG_TEXTURE_PIXEL_INVALID;
    m_rawData = NULL; // #FIXME
    m_width = 0;
    m_height = 0;
    m_components = -1;
    m_textureGfxID = 0;
    m_resType = FG_RESOURCE_TEXTURE;
    m_isInVRAM = FG_FALSE;
}

/*
 * Create function loads/interprets data from file in ROM and place it in RAM memory.
 */
fgBool fgTextureResource::create(void) {
    if(m_rawData && m_isReady) {
        return FG_TRUE;
    }
    if(m_rawData && !m_isReady) {
        releaseNonGFX();
    }
    FG_LOG::PrintInfo("fgTextureResource::create(void)");
    if(getFilePath(m_quality).empty()) {
        FG_LOG::PrintError("%s(%d): file path is empty on create - in function %s.", fgPath::fileName(__FILE__), __LINE__ - 1, __FUNCTION__);
        // #TODO error handling / reporting
        return FG_FALSE;
    }
    setFileTypeFromFilePath();
    if(m_fileType == FG_TEXTURE_FILE_INVALID) {
        FG_LOG::PrintError("%s(%d): texture file type is invalid - in function %s.", fgPath::fileName(__FILE__), __LINE__ - 1, __FUNCTION__);
        // #TODO error handling / reporting
        return FG_FALSE;
    }
    switch(m_fileType) {
        case FG_TEXTURE_FILE_BMP:
            break;
        case FG_TEXTURE_FILE_RAW:
            break;
        case FG_TEXTURE_FILE_JPEG:
            m_rawData = fgTextureLoader::loadJPEG(getFilePathStr(m_quality), m_width, m_height);
            break;
        case FG_TEXTURE_FILE_PNG:
            m_rawData = fgTextureLoader::loadPNG(getFilePathStr(m_quality), m_width, m_height);
            break;
        case FG_TEXTURE_FILE_TGA:
            m_rawData = fgTextureLoader::loadTGA(getFilePathStr(m_quality), m_width, m_height);
            break;
        case FG_TEXTURE_FILE_OTHER:
            return FG_FALSE;
            break;
        default:
            return FG_FALSE;
            break;
    };

    if(!m_rawData) {
        FG_LOG::PrintError("%s(%d): raw data is NULL - failed to load texture - in function %s.", fgPath::fileName(__FILE__), __LINE__ - 1, __FUNCTION__);
        // #TODO error handling / reporting
        return FG_FALSE;
    }
    m_isReady = FG_TRUE;
    // #FIXME
    m_components = FG_TEXTURE_COMP_RGBA;
    // #FIXME size calculation
    m_size = sizeof (unsigned char) * m_width * m_height * m_components;
    return FG_TRUE;
}

/*
 * Destroy all loaded data including additional metadata (called with destructor)
 */
void fgTextureResource::destroy(void) {
    FG_LOG_DEBUG("fgTextureResource::destroy();");
    releaseNonGFX();
    fgTextureResource::clear();
}

/*
 * Reloads any data, recreates the resource (refresh)
 */
fgBool fgTextureResource::recreate(void) {
    FG_LOG::PrintInfo("fgTextureResource::recreate(void)");
    if(m_isReady || m_rawData)
        releaseNonGFX();
    m_isReady = FG_FALSE;
    return create();
}

/*
 * Dispose completely of the all loaded data, free all memory
 * Releases non-GPU side of resources
 */
void fgTextureResource::dispose(void) {
    FG_LOG_DEBUG("fgTextureResource::~dispose();");
    releaseNonGFX();
}

/*
 * Check if resource is disposed (not loaded yet or disposed after)
 */
fgBool fgTextureResource::isDisposed(void) const {
    // #FIXME ?
    // This should also check if texture (GL/GFX) ID is valid.
    // If it is, then it means that the texture is uploaded and
    // ready to use. If GfxID is invalid than we can assume that
    // resource is disposed. This is kinda tricky one.
    //FG_LOG_DEBUG("fgTextureResource::isDisposed();   p_rawData=%p;", m_rawData);
    if(m_isInVRAM)
        return FG_FALSE;
    else
        return !this->hasOwnedRAM();
}

/*
 *
 */
fgBool fgTextureResource::setFileTypeFromFilePath(std::string &path) {
    if(path.empty())
        return FG_FALSE;
    // #FIXME - this should be extracted to other file (used for some basic file operation, pathext or whatnot #P3 #TODO)
    const char *ext = fgPath::fileExt(path.c_str(), FG_TRUE);
    if(strncasecmp(ext, FG_TEXTURE_FILE_EXTENSION_BMP, strlen(FG_TEXTURE_FILE_EXTENSION_BMP)) == 0) {
        this->m_fileType = FG_TEXTURE_FILE_BMP;
    } else if(strncasecmp(ext, FG_TEXTURE_FILE_EXTENSION_RAW, strlen(FG_TEXTURE_FILE_EXTENSION_RAW)) == 0) {
        this->m_fileType = FG_TEXTURE_FILE_RAW;
    } else if(strncasecmp(ext, FG_TEXTURE_FILE_EXTENSION_JPEG, strlen(FG_TEXTURE_FILE_EXTENSION_JPEG)) == 0) {
        this->m_fileType = FG_TEXTURE_FILE_JPEG;
    } else if(strncasecmp(ext, FG_TEXTURE_FILE_EXTENSION_PNG, strlen(FG_TEXTURE_FILE_EXTENSION_PNG)) == 0) {
        this->m_fileType = FG_TEXTURE_FILE_PNG;
    } else if(strncasecmp(ext, FG_TEXTURE_FILE_EXTENSION_TGA, strlen(FG_TEXTURE_FILE_EXTENSION_TGA)) == 0) {
        this->m_fileType = FG_TEXTURE_FILE_TGA;
    } else {
        this->m_fileType = FG_TEXTURE_FILE_OTHER;
    }
    return FG_TRUE;
}

/*
 * Releases non-GPU side of resources
 */
void fgTextureResource::releaseNonGFX(void) {
    FG_LOG_DEBUG("fgTextureResource::releaseNonGFX();   p_rawData=%p;", m_rawData);

    if(m_rawData)
        delete [] m_rawData;
    m_rawData = NULL;
    m_width = 0;
    m_height = 0;
    m_components = 0;
    m_size = 0;
    m_isReady = FG_FALSE;
}
