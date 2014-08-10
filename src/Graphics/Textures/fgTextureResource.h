/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_TEXTURE_RESOURCE_H
#define _FG_TEXTURE_RESOURCE_H

#include "../../fgBuildConfig.h"
#include "../../fgResource.h"

#include "fgTextureTypes.h"

#if defined FG_USING_MARMALADE

#if !defined FG_USING_MARMALADE_EGL && defined FG_USING_MARMALADE_IWGL
#include <IwGL.h>
#elif defined FG_USING_MARMALADE_OPENGL_ES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <EGL/egl.h>
#endif

#endif

typedef GLuint fgTextureGfxID;

/*
 *
 */
class fgTextureResource : public fgResource {
public:
	// Base constructor of the texture resource object
	fgTextureResource()	{  clear();  }
	// Base constructor with additional parameter (path)
	fgTextureResource(const char *path) { clear(); setFilePath(path); };
	// Base constructor with additional parameter (path)
	fgTextureResource(std::string& path) { clear(); setFilePath(path); };
	// Base destructor of the texture resource object
	~fgTextureResource()	{ destroy(); }

	// Clears the class data, this actually does not free allocated memory, just resets base class attributes
	virtual void clear(void);
	// Create function loads/interprets data from file in ROM and place it in RAM memory.
	virtual bool create(void);
	// Destroy all loaded data including additional metadata (called with deconstructor)
	virtual void destroy(void);
	// Reloads any data, recreates the resource (refresh)
	virtual bool recreate(void);
	// Dispose completely of the all loaded data, free all memory
	virtual void dispose(void);
	// Check if resource is disposed (not loaded yet or disposed after)
	virtual bool isDisposed(void) const;

protected:
	bool setFileTypeFromFilePath(std::string &path) {
		// #FIXME - this should be extracted to other file (used for some basic file operation, pathext or whatnot #P3 #TODO)
		std::string ext = path.substr(path.find_last_of(".") + 1);
		if(strnicmp(ext.c_str(), FG_TEXTURE_FILE_EXTENSION_BMP, strlen(FG_TEXTURE_FILE_EXTENSION_BMP)) == 0) {
			this->m_fileType = FG_TEXTURE_FILE_BMP;
		} else if(strnicmp(ext.c_str(), FG_TEXTURE_FILE_EXTENSION_RAW, strlen(FG_TEXTURE_FILE_EXTENSION_RAW)) == 0) {
			this->m_fileType = FG_TEXTURE_FILE_RAW;
		} else if(strnicmp(ext.c_str(), FG_TEXTURE_FILE_EXTENSION_JPEG, strlen(FG_TEXTURE_FILE_EXTENSION_JPEG)) == 0) {
			this->m_fileType = FG_TEXTURE_FILE_JPEG;
		} else if(strnicmp(ext.c_str(), FG_TEXTURE_FILE_EXTENSION_PNG, strlen(FG_TEXTURE_FILE_EXTENSION_PNG)) == 0) {
			this->m_fileType = FG_TEXTURE_FILE_PNG;
		} else if(strnicmp(ext.c_str(), FG_TEXTURE_FILE_EXTENSION_TGA, strlen(FG_TEXTURE_FILE_EXTENSION_TGA)) == 0) {
			this->m_fileType = FG_TEXTURE_FILE_TGA;
		} else {
			this->m_fileType = FG_TEXTURE_FILE_OTHER;
		}
		return true;
	}

	bool setFileTypeFromFilePath(void) {
		if(this->m_filePath.empty())
			return false;
		return setFileTypeFromFilePath(m_filePath);
	}

public:
	// Set file path to this resource
	virtual void setFilePath(const char *path) {
		fgResource::setFilePath(path);
		setFileTypeFromFilePath();
	}

	// Set file path to this resource
	virtual void setFilePath(std::string& path) {
		fgResource::setFilePath(path);
		setFileTypeFromFilePath();
	}

    // Releases non-GPU side of resources – should be
    // used to free data after uploading into VRAM
    void releaseNonGFX(void);

    // Checks whether RAM is owned by the object
    bool hasOwnedRAM(void) const {
        if( m_rawData == NULL ) {
			return false;
		}
		return true;
    }

	// Get the texture id used by the low level graphics system - handle in OpenGL
    fgTextureGfxID getTextureGfxID() const {
        return m_textureGfxID;
    }
	// Get reference tothe texture id used by the low level graphics system - handle in OpenGL
    fgTextureGfxID& getRefTextureGfxID() {
        return m_textureGfxID;
    }
	// Set the texture id used by the low level graphics system
	void setTextureGfxID(fgTextureGfxID id) {
		m_textureGfxID = id;
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

protected:
	// Texture file type (by extension)
	fgTextureFileType		m_fileType;
	// Texture type and possible usage
	fgTextureType			m_textureType;
	// Final texture pixel format (data pixel format)
	fgTexturePixelFormat	m_pixelFormat;
	// Storage for raw pixel data
    unsigned char*			m_rawData;
	// Width of the texture in pixels
    int m_width;
	// Height of the texture in pixels
	int m_height;
	// Number of color components (grayscale, RGB, RGBA)
    int m_components;
	// OpenGL texture id handle
	fgTextureGfxID m_textureGfxID;
};

#endif
