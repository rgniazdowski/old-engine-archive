/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgTextureResource.h"
#include "fgTextureLoader.h"

#include "Util/fgPath.h"
#include "Util/fgFile.h"
#include "Util/fgStrings.h"
#include "fgLog.h"

using namespace fg;

//------------------------------------------------------------------------------

gfx::CTextureResource::CTextureResource() :
base_type(),
m_fileType(texture::FILE_INVALID),
m_textureType(texture::PLAIN),
m_pixelFormat(texture::PIXEL_INVALID),
m_rawData(NULL),
m_width(0),
m_height(0),
m_components(-1),
m_textureGfxID(0),
m_isInVRAM(FG_FALSE) {
    this->m_resType = resource::TEXTURE;
    memset(m_cubeData, 0, sizeof (m_cubeData));
}
//------------------------------------------------------------------------------

gfx::CTextureResource::CTextureResource(const char *path) :
base_type(path),
m_fileType(texture::FILE_INVALID),
m_textureType(texture::PLAIN),
m_pixelFormat(texture::PIXEL_INVALID),
m_rawData(NULL),
m_width(0),
m_height(0),
m_components(-1),
m_textureGfxID(0),
m_isInVRAM(FG_FALSE) {
    this->m_resType = resource::TEXTURE;
    memset(m_cubeData, 0, sizeof (m_cubeData));
}
//------------------------------------------------------------------------------

gfx::CTextureResource::CTextureResource(std::string& path) :
base_type(path),
m_fileType(texture::FILE_INVALID),
m_textureType(texture::PLAIN),
m_pixelFormat(texture::PIXEL_INVALID),
m_rawData(NULL),
m_width(0),
m_height(0),
m_components(-1),
m_textureGfxID(0),
m_isInVRAM(FG_FALSE) {
    this->m_resType = resource::TEXTURE;
    memset(m_cubeData, 0, sizeof (m_cubeData));
}
//------------------------------------------------------------------------------

void gfx::CTextureResource::clear(void) {
    base_type::clear();
    m_fileType = texture::FILE_INVALID;
    m_textureType = texture::PLAIN;
    m_pixelFormat = texture::PIXEL_INVALID;
    m_rawData = NULL; // #FIXME
    m_cubeData[0] = NULL;
    m_width = 0;
    m_height = 0;
    m_components = -1;
    m_textureGfxID = 0;
    this->m_resType = resource::TEXTURE;
    m_isInVRAM = FG_FALSE;
    memset(m_cubeData, 0, sizeof (m_cubeData));
}
//------------------------------------------------------------------------------

fgBool gfx::CTextureResource::create(void) {
    if(m_rawData && base_type::m_isReady) {
        return FG_TRUE;
    }
    if(m_rawData && !base_type::m_isReady) {
        releaseNonGFX();
    }
    FG_LOG_DEBUG("GFX: Creating texture [%s]", m_nameTag.c_str());
    if(getFilePath(base_type::m_quality).empty()) {
        FG_LOG_ERROR("GFX: texture file path is empty on create");
        // #TODO error handling / reporting
        return FG_FALSE;
    }
    const char *filePathStr = getFilePathStr(base_type::m_quality);
    char filePathBuf[FG_FILE_PATH_MAX];
    memset(filePathBuf, 0, FG_FILE_PATH_MAX);
    const char *filePathPtr = filePathStr;
    setFileTypeFromFilePath();
    if(m_fileType == texture::FILE_INVALID) {
        FG_LOG_ERROR("GFX: texture file type is invalid - on create for '%s'", filePathPtr);
        // #TODO error handling / reporting
        return FG_FALSE;
    }
    unsigned char **targetRawData = NULL;
    int maxRawDataID = 0, i = 0;

    // 2D texture - single file, (x,y) coords
    if(m_textureType == texture::PLAIN || m_textureType == texture::FONT) {
        maxRawDataID = 1;
        targetRawData = &m_rawData;
        filePathPtr = filePathStr;
    } else if(m_textureType == texture::CUBE) {
        maxRawDataID = texture::NUM_CUBE_MAPS;
        targetRawData = m_cubeData; // ? the fuck is that?
        filePathPtr = filePathBuf;
    } else {
        FG_LOG_DEBUG("GFX: Texture type is not supported [%d]", m_textureType);
        maxRawDataID = 1;
        targetRawData = &m_rawData;
    }
    // #FIXME
    m_components = FG_TEXTURE_COMP_RGBA;
    this->m_size = 0;
    const char *cubeSuffix[6] = {"px", "nx", "py", "ny", "pz", "nz"};
    for(i = 0; i < maxRawDataID; i++) {
        if(m_textureType == texture::CUBE) {
            targetRawData = &m_cubeData[i];
            snprintf(filePathBuf, FG_FILE_PATH_MAX - 1, filePathStr, cubeSuffix[i]);
        }
        switch(m_fileType) {
            case texture::FILE_BMP:
                FG_LOG_ERROR("GFX: texture file type (BMP) is not yet supported!");
                break;
            case texture::FILE_RAW:
                FG_LOG_ERROR("GFX: texture file type (RAW) is not yet supported!");
                break;
            case texture::FILE_JPEG:
                *targetRawData = texture::loadJPEG(filePathPtr, m_width, m_height);
                break;
            case texture::FILE_PNG:
                *targetRawData = texture::loadPNG(filePathPtr, m_width, m_height);
                break;
            case texture::FILE_TGA:
                *targetRawData = texture::loadTGA(filePathPtr, m_width, m_height);
                break;
            case texture::FILE_OTHER:
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
        } else {
            FG_LOG_DEBUG("GFX: Successfully loaded texture nameTag[%s], path[%s]", m_nameTag.c_str(), filePathStr);
        }
        // #FIXME - texture raw data size calculation!
        this->m_size += sizeof (unsigned char) * m_width * m_height * m_components;
        FG_LOG_DEBUG("GFX: texture [%s] current size (KB): %.1f [MB=%.2f]", m_nameTag.c_str(), m_size / 1024.0f, m_size / 1024.0f / 1024.0f);
    }

    this->m_isReady = FG_TRUE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void gfx::CTextureResource::destroy(void) {
    releaseNonGFX();
    self_type::clear();
}
//------------------------------------------------------------------------------

fgBool gfx::CTextureResource::recreate(void) {
    FG_LOG_DEBUG("fgTextureResource::recreate(void)");
    if(this->m_isReady || m_rawData)
        dispose();
    this->m_isReady = FG_FALSE;
    return create();
}
//------------------------------------------------------------------------------

void gfx::CTextureResource::dispose(void) {
    releaseNonGFX();
}
//------------------------------------------------------------------------------

fgBool gfx::CTextureResource::isDisposed(void) const {
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
//------------------------------------------------------------------------------

fgBool gfx::CTextureResource::setFileTypeFromFilePath(std::string &path) {
    if(path.empty())
        return FG_FALSE;
    // #FIXME - this should be extracted to other file (used for some basic file operation, pathext or whatnot #P3 #TODO)
    const char *ext = fg::path::fileExt(path.c_str(), FG_TRUE);

    if(strings::endsWith(ext, FG_TEXTURE_FILE_EXTENSION_BMP, FG_FALSE)) {
        this->m_fileType = texture::FILE_BMP;
    } else if(strings::endsWith(ext, FG_TEXTURE_FILE_EXTENSION_RAW, FG_FALSE)) {
        this->m_fileType = texture::FILE_RAW;
    } else if(strings::endsWith(ext, FG_TEXTURE_FILE_EXTENSION_JPEG, FG_FALSE)) {
        this->m_fileType = texture::FILE_JPEG;
    } else if(strings::endsWith(ext, FG_TEXTURE_FILE_EXTENSION_PNG, FG_FALSE)) {
        this->m_fileType = texture::FILE_PNG;
    } else if(strings::endsWith(ext, FG_TEXTURE_FILE_EXTENSION_TGA, FG_FALSE)) {
        this->m_fileType = texture::FILE_TGA;
    } else {
        this->m_fileType = texture::FILE_OTHER;
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void gfx::CTextureResource::releaseNonGFX(void) {
    if(m_rawData) {
        FG_LOG_DEBUG("GFX:Texture: release nonGFX: rawData[%p];", m_rawData);
    }
    for(int i = 0; i < texture::NUM_CUBE_MAPS; i++) {
        if(m_cubeData[i]) {
            delete [] m_cubeData[i];
        }
        m_cubeData[i] = NULL;
    }
    m_rawData = NULL;
    m_width = 0;
    m_height = 0;
    m_components = 0;
    this->m_size = 0;
    this->m_isReady = FG_FALSE;
}
//------------------------------------------------------------------------------

void gfx::CTextureResource::setFlags(const std::string& flags) {
    if(flags.empty() || flags.length() < 2)
        return;
    // This is important - always call setFlags for the base class
    base_type::setFlags(flags);
    fg::CStringVector flagsVec;
    strings::split(flags, ' ', flagsVec);
    if(flagsVec.empty())
        return;
    unsigned int n = (unsigned int)flagsVec.size();
    for(unsigned int i = 0; i < n; i++) {
        if(strings::isEqual(flagsVec[i].c_str(), "2D", FG_FALSE) ||
           strings::isEqual(flagsVec[i].c_str(), "diffuse", FG_FALSE)) {
            m_textureType = texture::PLAIN;
        } else if(strings::isEqual(flagsVec[i].c_str(), "ambient", FG_FALSE)) {
            m_textureType = texture::AMBIENT;
        } else if(strings::isEqual(flagsVec[i].c_str(), "specular", FG_FALSE)) {
            m_textureType = texture::SPECULAR;
        } else if(strings::isEqual(flagsVec[i].c_str(), "normal", FG_FALSE)) {
            m_textureType = texture::NORMAL;
        } else if(strings::isEqual(flagsVec[i].c_str(), "bump", FG_FALSE)) {
            m_textureType = texture::BUMP;
        } else if(strings::isEqual(flagsVec[i].c_str(), "environment", FG_FALSE)) {
            m_textureType = texture::ENVIRONMENT;
        } else if(strings::isEqual(flagsVec[i].c_str(), "cube", FG_FALSE)) {
            m_textureType = texture::CUBE;
        } else if(strings::isEqual(flagsVec[i].c_str(), "3D", FG_FALSE)) {
            m_textureType = texture::T_3D;
        }
    }
}
//------------------------------------------------------------------------------
