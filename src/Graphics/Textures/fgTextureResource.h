/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
 *******************************************************/

#ifndef _FG_TEXTURE_RESOURCE_H
#define _FG_TEXTURE_RESOURCE_H

#include "IwImage.h"
#include "IwGL.h"

class fgTexture;

typedef fgTexture* PfgTexture;

class fgTexture {

//
// MARK: -
// MARK: Utils
//

    /**
     * Check for glGetError() and conditionally returns false
     * (but only for DEBUG builds)
     */
    //bool checkGlError(const char* fname);

public:

//
// MARK: -
// MARK: Initializers & destroyers
//

    /**
     * Public constructor
     */
    fgTexture();

    /**
     * Public destructor
     */
    ~fgTexture();

//
// MARK: -
// MARK: Business – initialize & destroy
//

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
     * used to free data after uploading int oVRAM
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

//
// MARK: -
// MARK: Business
//

    /**
     * Uploads image to VRAM as a texture
     */
    bool makeTexture();

    //
    // MARK: Getters
    //

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

    //
    // MARK: Setters
    //

    /// Set ONE double initialization allowed
    void setAllowDoubleInit() {
        m_allowDoubleInit = true;
    }

private:
	CIwImage *m_img;
    int m_mode;
    GLuint m_texId;
    int m_width;
    int m_height;
    int m_comp;
    unsigned char* m_ucdata;
    const char* m_filename;

    /// Allows ONE double init – i.e. the init
    /// when object already has m_mode set
    bool m_allowDoubleInit;
public:
    // The object can either represent a texture, or an
    // UCDATA used by Font manager to create font textures
    enum { NOTYPE = 0, TEXTURE = 1, UCDATA = 2 };
};


#endif
