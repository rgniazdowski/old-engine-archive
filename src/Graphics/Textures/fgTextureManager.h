/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef FG_TEXTURE_MANAGER_H_
#define FG_TEXTURE_MANAGER_H_

#include "../../fgSingleton.h"
#include "fgTextureResource.h"
#include "fgTextureCommon.h"
#include "fgTextureTypes.h"

// #FIXME - now that class just retarded - but before it will load textures from XML/CSS/Lua files many other classes and functions are needed before it will be possible
typedef fgTextureResource * PfgTexture;

/**
 * COMPOSITE DESIGN PATTERN
 *
 * Class that allows to perform GROUP OPERATIONS
 * on all textures. 
 */
class fgTextureManager : public fgSingleton<fgTextureManager> {

	friend class fgSingleton<fgTextureManager>;

protected:
    fgTextureManager();
    ~fgTextureManager();

public:

    /**
     * Returns given fgTexture*
     * (does not use reference, so internal variable cannot be altered)
     */
    fgTextureResource* facade(Tex::ID TEX_ID) {
        return facadeReference(TEX_ID);
    }

    /**
     * Gets reference to THE variable holding fgTexture (one and only for the TEX_ID)
     */
    PfgTexture & facadeReference( Tex::ID TEX_ID );

	/**
	 * Set the number of thumbnails used in the game
	 */
	void setThumbnailsCount(int num_thumbnails);

	/**
	 * Getting the texture ID for the thumbnail
	 */
	int getThumbnailTextureID(int thumbnail_id);

    /**
     * DISK -> RAM: only if needed OR force given
     */
    bool allToRAM(bool force = false);

    /**
     * RAM -> VRAM.
     * Update of VRAM is unconditional. 
     * Update of RAM is dependent on:
     * - no image being already loaded,
     * - force option given.
     */
    bool allToVRAM(bool force = false);

    /**
     * Releases all NonGl (i.e. non VRAM) data
     */
    void allReleaseNonGl();

    /**
     * Releases all OpenGl (i.e. texture ids) data
     */
    void allReleaseGl();

    /**
     * Checks if the Tex::ID is FONT
     */
    bool isFont(Tex::ID theId) const {
        return ( theId == Tex::FONT_MAIN_TEXTURE ) || ( theId == Tex::FONT_SECONDARY_TEXTURE );
    }

	//////////////////////////
#if defined(FG_USING_OPENGL_ES) || defined(FG_USING_OPENGL)
	static GLint translatePixelFormat(fgTexturePixelFormat pixelFormat);
	static GLint translateInternalPixelFormat(fgTextureInternalPixelFormat internalPixelFormat);
#endif

private:
    /**
     * Loads texture of given ID
     */
    bool loadTexture( Tex::ID TEX_ID, bool force = false );

    /**
     * Uploads texture given via ID into VRAM.
     *
     * No force is possible – i.e. it is impossible to delete
     * texture through glDeleteTextures() and recreate it through
     * glGenTextures(). This is because OpenGL can UPDATE already
     * existing textures (i.e. use already generated texture IDs)
     *
     * (Still, fgTexture is capable of doing that: releaseAll() will
     * leave filename intact. It is however not needed, and should not
     * be used).
     */
    bool makeTexture( Tex::ID TEX_ID );

    friend class MainModule;
};

#define TEXTURE_PTR(TEX_ID) fgTextureManager::getInstance()->facade(TEX_ID)
#define TEXTURE_REF_PTR(TEX_ID) fgTextureManager::getInstance()->facadeReference(TEX_ID)

#endif
