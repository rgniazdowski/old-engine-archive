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

#if defined FG_USING_MARMALADE
#include "IwImage.h"
#if !defined FG_USING_MARMALADE_EGL && defined FG_USING_MARMALADE_IWGL
#include <IwGL.h>
#elif defined FG_USING_MARMALADE_OPENGL_ES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <EGL/egl.h>
#endif

#endif

class fgTextureResource;
typedef fgTextureResource* PfgTexture;

// Texture file type enumeration. Supported file formats (current & future):
// bmp, raw, jpg, png, tga
enum fgTextureFileType {
	FG_TEXTURE_FILE_BMP,
	FG_TEXTURE_FILE_RAW,
	FG_TEXTURE_FILE_JPG,
	FG_TEXTURE_FILE_PNG,
	FG_TEXTURE_FILE_TGA,

	FG_TEXTURE_FILE_OTHER,
	FG_TEXTURE_FILE_INVALID,

	FG_NUM_TEXTURE_FILE_TYPES
};

// Texture type enumeration, defines the type of the texture and
// possible usage because of this
enum fgTextureType {
	FG_TEXTURE_PLAIN,
	FG_TEXTURE_BUMP,
	FG_TEXTURE_NORMAL,
	FG_TEXTURE_RAW,
	FG_TEXTURE_FONT,

	FG_TEXTURE_INVALID,
	FG_NUM_TEXTURE_TYPES
};

/*
 *
 */
class fgTextureResource : public fgResource {

public:
	//
    fgTextureResource();
    //
	~fgTextureResource();

	// Clears the class data, this actually does not free allocated memory, just resets base class attributes
	virtual void clear(void);

	virtual bool create(void);
	virtual void destroy(void);
	virtual bool recreate(void);
	// Dispose completely of the all loaded data, free all memory
	virtual void dispose(void);
	virtual bool isDisposed(void) const;

	enum { NOTYPE = 0, TEXTURE = 1, UCDATA = 2 }; // #FIXME #P1
    /**
     * Loads texture using CIwImage. The image remains
     * in RAM until removed via releaseNonGl()
     */
    bool loadFromFile(const char* file);

    /*
     * Loads TGA image "by hand", with custom, non-Marmalade code.
     */
    bool prepareTgaFromFile(const char* file);

    /**
     * Releases non-GPU side of resources – should be
     * used to free data after uploading into VRAM
     */
    void releaseNonGl(void);

    /**
     * Releases OpenGL structures (i.e. the texture id)
     */
    void releaseGl(void);

    /**
     * Makes object fully EMPTY – structures in RAM and
     * in VRAM/OpenGL – all will get released, and object's
     * m_mode will be set to NOTYPE.
     */
	void releaseAll(void);

    /**
     * Checks whether RAM is owned by the object
     */
    bool hasOwnedRAM(void) const {
        bool result = true;

        if( m_ucdata == NULL ) {
            result = false;
        }

        return result;
    }

    /**
     * Uploads image to VRAM as a texture
     */
    bool makeTexture();

    int mode() const {
        return m_mode;
    }

    GLuint textureId() const {
        return m_texId;
    }

    int width() const {
        return m_width;
    }

    int height() const {
        return m_height;
    }

    int components() const {
        return m_comp;
    }

    unsigned char * ucdata() const {
        return m_ucdata;
    }

private:
	fgTextureFileType m_fileType;
	fgTextureType m_textureType;
	CIwImage *m_img;
    int m_mode;
    GLuint m_texId;
    int m_width;
    int m_height;
    int m_comp;
    unsigned char* m_ucdata;

    /// Allows ONE double init – i.e. the init
    /// when object already has m_mode set
    bool m_allowDoubleInit;

	
};


#endif
