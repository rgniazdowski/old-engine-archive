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
#include "Util/fgStrings.h"

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
    memset(m_cubeData, 0, sizeof (m_cubeData));
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
    memset(m_cubeData, 0, sizeof (m_cubeData));
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
    memset(m_cubeData, 0, sizeof (m_cubeData));
}

/*
 * Clears the class data, this actually does not free allocated memory,
 * just resets base class attributes
 */
void fgTextureResource::clear(void) {
    fgResource::clear();
    m_fileType = FG_TEXTURE_FILE_INVALID;
    m_textureType = FG_TEXTURE_PLAIN;
    m_pixelFormat = FG_TEXTURE_PIXEL_INVALID;
    m_rawData = NULL; // #FIXME
    m_cubeData[0] = NULL;
    m_width = 0;
    m_height = 0;
    m_components = -1;
    m_textureGfxID = 0;
    m_resType = FG_RESOURCE_TEXTURE;
    m_isInVRAM = FG_FALSE;
    memset(m_cubeData, 0, sizeof (m_cubeData));
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
        FG_LOG_ERROR("GFX: texture file path is empty on create");
        // #TODO error handling / reporting
        return FG_FALSE;
    }
    const char *filePathStr = getFilePathStr(m_quality);
    char filePathBuf[FG_FILE_PATH_MAX];
    memset(filePathBuf, 0, FG_FILE_PATH_MAX);
    const char *filePathPtr = filePathStr;
    setFileTypeFromFilePath();
    if(m_fileType == FG_TEXTURE_FILE_INVALID) {
        FG_LOG_ERROR("GFX: texture file type is invalid - on create for '%s'", filePathPtr);
        // #TODO error handling / reporting
        return FG_FALSE;
    }
    unsigned char **targetRawData = NULL;
    int maxRawDataID = 0, i = 0;

    if(m_textureType == FG_TEXTURE_PLAIN) { // 2D texture - single file, (x,y) coords
        maxRawDataID = 1;
        targetRawData = &m_rawData;
        filePathPtr = filePathStr;
    } else if(m_textureType == FG_TEXTURE_CUBE) {
        maxRawDataID = FG_NUM_TEXTURE_CUBE_MAPS;
        targetRawData = m_cubeData; // ? the fuck is that?
        filePathPtr = filePathBuf;
    } else {
        FG_LOG_DEBUG("GFX: Texture type is not supported");
        maxRawDataID = 1;
        targetRawData = &m_rawData;
    }
    // #FIXME
    m_components = FG_TEXTURE_COMP_RGBA;
    m_size = 0;
    const char *cubeSuffix[6] = {"px", "nx", "py", "ny", "pz", "nz"};
    for(i = 0; i < maxRawDataID; i++) {
        if(m_textureType == FG_TEXTURE_CUBE) {
            targetRawData = &m_cubeData[i];
            snprintf(filePathBuf, FG_FILE_PATH_MAX - 1, filePathStr, cubeSuffix[i]);
        }
        switch(m_fileType) {
            case FG_TEXTURE_FILE_BMP:
                FG_LOG_ERROR("GFX: texture file type (BMP) is not yet supported!");
                break;
            case FG_TEXTURE_FILE_RAW:
                FG_LOG_ERROR("GFX: texture file type (RAW) is not yet supported!");
                break;
            case FG_TEXTURE_FILE_JPEG:
                *targetRawData = fgTextureLoader::loadJPEG(filePathPtr, m_width, m_height);
                break;
            case FG_TEXTURE_FILE_PNG:
                *targetRawData = fgTextureLoader::loadPNG(filePathPtr, m_width, m_height);
                break;
            case FG_TEXTURE_FILE_TGA:
                *targetRawData = fgTextureLoader::loadTGA(filePathPtr, m_width, m_height);
                break;
            case FG_TEXTURE_FILE_OTHER:
                FG_LOG_ERROR("GFX: texture file type (OTHER) is not yet supported!");
                return FG_FALSE;
                break;
            default:
                FG_LOG_ERROR("GFX: texture file type not recognized");
                return FG_FALSE;
                break;
        };
        if(!(*targetRawData)) {
            FG_LOG_ERROR("GFX: raw data is NULL - failed to load texture '%s'", filePathPtr);
            // #TODO error handling / reporting
            return FG_FALSE;
        }
        // #FIXME - texture raw data size calculation!
        m_size += sizeof (unsigned char) * m_width * m_height * m_components;
        FG_LOG_DEBUG("GFX: texture [%s] current size (KB): %.1f [MB=%.2f]", m_nameTag.c_str(), m_size/1024.0f, m_size/1024.0f/1024.0f);
    }

    m_isReady = FG_TRUE;
    // #FIXME size calculation

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
    FG_LOG_DEBUG("fgTextureResource::recreate(void)");
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

    for(int i = 0; i < FG_NUM_TEXTURE_CUBE_MAPS; i++) {
        if(m_cubeData[i]) {
            delete [] m_cubeData[i];
        }
        m_cubeData[i] = NULL;
    }
    //if(m_rawData)
    //    delete [] m_rawData;
    //m_rawData = NULL;
    m_width = 0;
    m_height = 0;
    m_components = 0;
    m_size = 0;
    m_isReady = FG_FALSE;
}

/**
 * 
 * @param flags
 */
void fgTextureResource::setFlags(const std::string& flags) {
    if(flags.empty() || flags.length() < 2)
        return;
    // This is important - always call setFlags for the base class
    fgResource::setFlags(flags);
    fgStringVector flagsVec;
    fgStrings::split(flags, ' ', flagsVec);
    if(flagsVec.empty())
        return;
    //    FG_TEXTURE_BUMP = 2,
    //    FG_TEXTURE_NORMAL = 3,
    //    FG_TEXTURE_RAW = 4,
    //    FG_TEXTURE_FONT = 5,
    //    FG_TEXTURE_CUBE = 6,
    //    FG_TEXTURE_3D = 7,
    unsigned int n = (unsigned int)flagsVec.size();
    for(unsigned int i = 0; i < n; i++) {
        if(fgStrings::isEqual(flagsVec[i].c_str(), "cube", FG_FALSE)) {
            m_textureType = FG_TEXTURE_CUBE;
        } else if(fgStrings::isEqual(flagsVec[i].c_str(), "2D", FG_FALSE)) {
            m_textureType = FG_TEXTURE_PLAIN;
        } else if(fgStrings::isEqual(flagsVec[i].c_str(), "3D", FG_FALSE)) {
            m_textureType = FG_TEXTURE_3D;
        } else if(fgStrings::isEqual(flagsVec[i].c_str(), "bump", FG_FALSE)) {
            m_textureType = FG_TEXTURE_BUMP;
        } else if(fgStrings::isEqual(flagsVec[i].c_str(), "normal", FG_FALSE)) {
            m_textureType = FG_TEXTURE_NORMAL;
        }
    }
}
