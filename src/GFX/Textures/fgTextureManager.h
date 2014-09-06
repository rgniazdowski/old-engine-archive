/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_TEXTURE_MANAGER_H_
#define _FG_TEXTURE_MANAGER_H_

#include "fgCommon.h"
#include "fgManagerBase.h"
#include "fgTextureResource.h"
#include "fgTextureTypes.h"
#include "Resource/fgResourceManager.h"

/**
 * Class that allows to perform GROUP OPERATIONS on all textures. 
 */
class fgTextureManager : public fgManagerBase {
    friend class MainModule; // ?? ?? ??
public:
	// Default constructor for Texture Manager object
    fgTextureManager(fgManagerBase *resourceManager);
	// Default destructor for Texture Manager object
    virtual ~fgTextureManager();

	void clear(void);
	void destroy(void);

	fgBool initialize(void);

    /**
     * RAM -> VRAM.
     * Update of VRAM is unconditional. 
     * Update of RAM is dependent on:
     * - no image being already loaded,
     * - force option given.
     */
    fgBool allToVRAM(void);

    // Releases all non GFX (i.e. non VRAM) data
    void allReleaseNonGFX(void);

    // Releases all GFX (i.e. texture ids) data
    void allReleaseGFX(void);

	// #FIXME #TODO #P2
#if defined(FG_USING_OPENGL_ES) || defined(FG_USING_OPENGL)
	static GLint translatePixelFormat(fgTexturePixelFormat pixelFormat);
	static GLint translateInternalPixelFormat(fgTextureInternalPixelFormat internalPixelFormat);
#endif

private:
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
    fgBool makeTexture(fgTextureResource *textureResource);

private:
	fgResourceManager *m_resourceManager;
	fgBool m_allInVRAM;
};

#endif /* _FG_TEXTURE_MANAGER_H_ */
