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
#include "fgStatusReporter.h"
#include "Resource/fgResourceManager.h"
#include "Util/fgTag.h"

class fgTextureManager;

#define FG_TAG_TEXTURE_MANAGER_NAME		"GfxTextureManager"
//#define FG_TAG_MANAGER_BASE_ID		20 //#FIXME - something automatic maybe?
#define FG_TAG_TEXTURE_MANAGER			FG_TAG_TYPE(fgTextureManager)

//FG_TAG_TEMPLATE(fgResourceManager, FG_TAG_MANAGER_BASE_NAME, FG_TAG_MANAGER_BASE_ID);
FG_TAG_TEMPLATE_ID_AUTO(fgTextureManager, FG_TAG_TEXTURE_MANAGER_NAME);

// Special handle type for manager base
typedef FG_TAG_TEXTURE_MANAGER fgTextureManagerTag;

#define FG_MANAGER_TEXTURE	0x00000004

/**
 * Class that allows to perform GROUP OPERATIONS on all textures. 
 */
class fgTextureManager : public fgManagerBase, public fgStatusReporter<fgTextureManagerTag> {
    friend class MainModule; // ?? ?? ??
public:
	// Default constructor for Texture Manager object
    fgTextureManager(fgManagerBase *resourceManager);
	// Default destructor for Texture Manager object
    virtual ~fgTextureManager();

protected:
	virtual void clear(void);

public:
	//
	virtual fgBool destroy(void);
	//
	virtual fgBool initialize(void);

	void setResourceManager(fgManagerBase *resourceManager) {
		if(resourceManager)
			m_resourceManager = static_cast<fgResourceManager *>(resourceManager);
	}

	fgResourceManager *getResourceManager(void) const {
		return m_resourceManager;
	}

    /**
     * RAM -> VRAM.
     * Update of VRAM is unconditional. 
     * Update of RAM is dependent on:
     * - no image being already loaded,
     * - force option given.
     */
    fgBool allToVRAM(fgBool reupload = FG_FALSE);

    // Releases all non GFX (i.e. non VRAM) data
    void allReleaseNonGFX(void);

    // Releases all GFX (i.e. texture ids) data
    void allReleaseGFX(void);

	// #FIXME #TODO #P2
#if defined(FG_USING_OPENGL_ES) || defined(FG_USING_OPENGL)
	static GLint translatePixelFormat(fgTexturePixelFormat pixelFormat);
	static GLint translateInternalPixelFormat(fgTextureInternalPixelFormat internalPixelFormat);
#endif

	fgBool uploadToVRAM(fgTextureResource *texture, fgBool force = FG_FALSE);

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
