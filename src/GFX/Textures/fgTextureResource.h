/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_TEXTURE_RESOURCE
    #define FG_INC_TEXTURE_RESOURCE

    #include "fgBuildConfig.h"
    #include "Resource/fgResource.h"
    #include "Resource/fgResourceFactoryTypes.h"

    #include "fgTextureTypes.h"
    #include "GFX/fgGFXStdInc.h"

/*
 *
 */
class fgTextureResource : public fgResource {
    friend class fgTextureManager;
public:
    // Base constructor of the texture resource object
    fgTextureResource();
    // Constructor with additional parameter (path)
    fgTextureResource(const char *path);
    // Constructor with additional parameter (path)
    fgTextureResource(std::string& path);
    // Base destructor of the texture resource object
    virtual ~fgTextureResource() {
        fgTextureResource::destroy();
    }

    FG_RESOURCE_FACTORY_CREATE_FUNCTION(fgTextureResource)
protected:
    // Clears the class data, this actually does not free allocated memory,
    // just resets base class attributes
    virtual void clear(void);
public:
    // Create function loads/interprets data from file in ROM and place it in RAM memory.
    virtual fgBool create(void);
    // Destroy all loaded data including additional metadata (called with destructor)
    virtual void destroy(void);
    // Reloads any data, recreates the resource (refresh)
    virtual fgBool recreate(void);
    // Dispose completely of the all loaded data, free all memory
    virtual void dispose(void);
    // Check if resource is disposed (not loaded yet or disposed after)
    virtual fgBool isDisposed(void) const;

protected:
    // 
    fgBool setFileTypeFromFilePath(std::string &path);

    //
    fgBool setFileTypeFromFilePath(void) {
        if(getFilePath(m_quality).empty())
            return FG_FALSE;
        return setFileTypeFromFilePath(getFilePath(m_quality));
    }

public:
    virtual void setFlags(const std::string& flags);
    
    // Releases non-GPU side of resources – should be
    // used to free data after uploading into VRAM
    void releaseNonGFX(void);

    // Checks whether RAM is owned by the object
    fgBool hasOwnedRAM(void) const {
        if(m_rawData == NULL) {
            return FG_FALSE;
        }
        return FG_TRUE;
    }

    // Get reference tothe texture id used by the low level graphics system - handle in OpenGL
    fgGfxTextureID& getRefGfxID() {
        return m_textureGfxID;
    }
    fgGfxTextureID* getPtrGfxID() {
        return &m_textureGfxID;
    }

    // Set the texture id used by the low level graphics system
    void setGfxID(fgGFXuint id) {
        m_textureGfxID.id = id;
    }

    // Get width of the texture in pixels
    int getWidth() const {
        return m_width;
    }
    // Get height of the texture in pixels
    int getHeight(void) const {
        return m_height;
    }
    // Get number of color components
    int getComponents(void) const {
        return m_components;
    }
    // Return pointer to raw pixel data (unsigned char array)
    unsigned char* getRawData(void) const {
        return m_rawData;
    }
    unsigned char *getCubeData(const fgTextureCubeMapID id) const {
        if((int)id >= FG_NUM_TEXTURE_CUBE_MAPS || (int)id < 0)
            return NULL;
        return m_cubeData[id];
    }
    // Get texture file type (determined from extension)
    fgTextureFileType getFileType(void) const {
        return m_fileType;
    }
    // Get texture type
    fgTextureType getTextureType(void) const {
        return m_textureType;
    }
    // Get texture pixel format
    fgTexturePixelFormat getPixelFormat(void) const {
        return m_pixelFormat;
    }
    // Set the texture type (usage)
    void setTextureType(fgTextureType textureType) {
        m_textureType = textureType;
    }
    // Set the final texture pixel format
    void setPixelFormat(fgTexturePixelFormat pixelFormat) {
        m_pixelFormat = pixelFormat;
    }

    //
    fgBool isInVRAM(void) const {
        return m_isInVRAM;
    }

protected:
    //
    void setIsInVRAM(fgBool toggle) {
        m_isInVRAM = toggle;
    }

protected:
    /// Texture file type (by extension)
    fgTextureFileType m_fileType;
    /// Texture type and possible usage
    fgTextureType m_textureType;
    /// Final texture pixel format (data pixel format)
    fgTexturePixelFormat m_pixelFormat;
    union {
        struct {
            unsigned char* px;
            unsigned char* nx;
            unsigned char* py;
            unsigned char* ny;
            unsigned char* pz;
            unsigned char* nz;
        } m_cube;
    /// Storage for raw pixel data
        unsigned char* m_rawData;
        unsigned char* m_cubeData[FG_NUM_TEXTURE_CUBE_MAPS];
        unsigned char* m_texelsVec[8]; // #FIXME
    };
    /// Width of the texture in pixels
    int m_width;
    /// Height of the texture in pixels
    int m_height;
    /// Number of color components (gray scale, RGB, RGBA)
    int m_components;
    /// OpenGL texture id handle
    fgGfxTextureID m_textureGfxID;
private:
    /// This is special trigger, it tells if texture was uploaded to VRAM
    /// When set to TRUE, even if gfxID is invalid it tells that texture
    /// needs to be re-uploaded
    ///
    /// On GL suspend all gfx IDs (including shaders, vbo's and others become invalid)
    fgBool m_isInVRAM;
};

typedef fgTextureResource fgGfxTexture;

#endif /* FG_INC_TEXTURE_RESOURCE */
