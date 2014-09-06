/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgBuildConfig.h"
#include "fgCommon.h"

#include "fgTextureManager.h"

#include <map>

#include "fgTextureResource.h"

#include "Hardware/fgQualityManager.h"
#include "Resource/fgResourceManager.h"

/**
 * Protected constructor
 */
fgTextureManager::fgTextureManager(fgManagerBase *resourceManager) : 
	m_allInVRAM(FG_FALSE)
{
	fgStatusReporter::setReportToMsgSystem(FG_TRUE);
	if(!resourceManager) {
		setErrorCode(FG_ERRNO_WRONG_PARAM);
		m_init = FG_FALSE;
		m_resourceManager = NULL;
	} else {
		m_resourceManager = (fgResourceManager *) resourceManager;
	}
}

/**
 * Protected destructor
 */
fgTextureManager::~fgTextureManager()
{
	destroy();
}

/*
 *
 */
void fgTextureManager::clear(void) 
{
}

/*
 *
 */
void fgTextureManager::destroy(void) 
{
	m_resourceManager = NULL;
	m_init = FG_FALSE;
}

/*
 *
 */
fgBool fgTextureManager::initialize(void) 
{
	if(!m_resourceManager)
		return FG_FALSE;
	m_init = FG_TRUE;
	return FG_TRUE;
}

/**
 * UPLOAD to VRAM – skips reload from disk ONLY if possible
 */
fgBool fgTextureManager::allToVRAM(void)
{
	if(!m_init) {
		if(!initialize())
			return FG_FALSE;
	}
    fgBool result = FG_TRUE;
	fgResourceType searchTypes[] = {FG_RESOURCE_TEXTURE, FG_RESOURCE_FONT, FG_RESOURCE_INVALID};
	//
	// #FIXME #P1 - this needs more testing and should look quite different
	// right now it's just bollocks
	//
	m_resourceManager->goToBegin();
	while(m_resourceManager->isValid()) {
		fgResource *resource = m_resourceManager->getCurrentResource();
		if(!resource) {
			printf("ERROR: Loop in texture manager, resource is %p\n", resource);
			return FG_FALSE;
			// FAIL
		}
		fgResourceType resType = resource->getResourceType();
		fgQuality quality = resource->getQuality();
		if((resType == FG_RESOURCE_TEXTURE || resType == FG_RESOURCE_FONT) &&
			(quality == FG_QualityManager->getQuality() ||
			quality == FG_QUALITY_UNIVERSAL) ) 
		{
				// Check if resource is locked - if it is - it's quite possible
				// that it needs to be used in the future - so upload it
				if(resource->isLocked())
				{
					fgTextureResource *textureResource = (fgTextureResource *)resource;
					textureResource->setIsInVRAM(FG_FALSE);
					fgTextureGfxID& texGfxID = textureResource->getRefTextureGfxID();
					// #FIXME #P1 - i just don't know what I am doing... this all so blurry.
					if(glIsTexture(texGfxID) == GL_FALSE || !textureResource->hasOwnedRAM()) {
						if(!textureResource->recreate()) {
							FG_LOG::PrintError("Could not recrete texture '%s'\n", textureResource->getFilePathStr());
							// FAIL
							result = FG_FALSE;
						}
					} 
					
					if(textureResource->hasOwnedRAM())
					{
						if(!makeTexture(textureResource)) {
							result = FG_FALSE;
							// FAIL
							FG_LOG::PrintError("Could not upload texture '%s'\n", textureResource->getFilePathStr());
						} else {
							textureResource->setIsInVRAM(FG_TRUE); // #FIXME - this can be set in a better place
						}
					}
				} // else: if resource is not locked then most likely it is not needed
		}
		//FG_ResourceManager->goToNext(FG_RESOURCE_TEXTURE);
		m_resourceManager->goToNext(searchTypes, 3);
	}
	m_allInVRAM = FG_TRUE;
    return result;
}

/**
 * Releases all NonGl (i.e. non VRAM) data
 */
void fgTextureManager::allReleaseNonGFX(void)
{
	if(!m_resourceManager)
		return;
	fgResourceType searchTypes[] = {FG_RESOURCE_TEXTURE, FG_RESOURCE_FONT, FG_RESOURCE_INVALID};
	//
	// #FIXME #P1 - this needs more testing and should look quite different
	// right now it's just bollocks
	//
	m_resourceManager->goToBegin();
	while(m_resourceManager->isValid()) {
		fgResource *resource = m_resourceManager->getCurrentResource();
		if(!resource) {
			return;
			// FAIL
		}
		fgResourceType resType = resource->getResourceType();
		if(resType == FG_RESOURCE_TEXTURE || resType == FG_RESOURCE_FONT) {
			fgTextureResource *textureResource = (fgTextureResource *)resource;
			textureResource->releaseNonGFX();
			fgTextureGfxID& texGfxID = textureResource->getRefTextureGfxID();
			if(glIsTexture(texGfxID) == GL_TRUE)
				textureResource->setIsInVRAM(FG_TRUE);

		}
		//FG_ResourceManager->goToNext(FG_RESOURCE_TEXTURE);
		m_resourceManager->goToNext(searchTypes, 3);
	}
	m_resourceManager->refreshMemory();
}

/**
 * Releases all OpenGl (i.e. texture ids) data
 */
void fgTextureManager::allReleaseGFX(void) {
	if(!m_resourceManager)
		return;
	fgResourceType searchTypes[] = {FG_RESOURCE_TEXTURE, FG_RESOURCE_FONT, FG_RESOURCE_INVALID};
	//
	// #FIXME #P1 - this needs more testing and should look quite different
	// right now it's just bollocks
	//
	m_resourceManager->goToBegin();
	while(m_resourceManager->isValid()) {
		fgResource *resource = m_resourceManager->getCurrentResource();
		if(!resource) {
			return;
			// FAIL
		}
		fgResourceType resType = resource->getResourceType();
		fgQuality quality = resource->getQuality();
		if(resType == FG_RESOURCE_TEXTURE || resType == FG_RESOURCE_FONT) {
			fgTextureResource *textureResource = (fgTextureResource *)resource;
			fgTextureGfxID& texGfxID = textureResource->getRefTextureGfxID();
			if(glIsTexture(texGfxID) == GL_TRUE) {
				// There is a texture to release from GFX
				glDeleteTextures(1, &texGfxID);
				texGfxID = 0;
				textureResource->setTextureGfxID(0);
				textureResource->setIsInVRAM(FG_FALSE);
			}
			textureResource->releaseNonGFX();
		}
		//FG_ResourceManager->goToNext(FG_RESOURCE_TEXTURE);
		m_resourceManager->goToNext(searchTypes, 3);
	}
	m_resourceManager->refreshMemory();
}

/**
 * Uploads image to VRAM as a texture
 *
 * TODO: mozliwa jest optymalizacja: gdy wymiary tekstury
 * uploadowanej drugi raz sa takie same, mozna uzyc
 * glTexSubImage2D zamiast glTexImage2D
 */
fgBool fgTextureManager::makeTexture(fgTextureResource *pTexture) 
{
	if(!m_resourceManager)
		return FG_FALSE;

    if(!pTexture) {
        FG_LOG::PrintError("Cannot upload texture - texture resource is NULL");
        return FG_FALSE;
    }
	if(!m_resourceManager->isResourceManaged(pTexture)) {
		FG_LOG::PrintError("Cannot upload texture - texture resource is not managed by Resource Manager");
		return FG_FALSE;
	}
    // Supports creation of texture, and update of texture
	/*if ( !tex_facade->makeGFXTexture() ) {
		FG_LOG::PrintError("Making texture [%d] failed", TEX_ID);
		return false;
	}*/

	m_resourceManager->lockResource(pTexture);

	if(!pTexture->getRawData() || !pTexture->hasOwnedRAM()) {
        FG_LOG::PrintError("Cannot upload texture - texture resource is disposed / empty");
        return FG_FALSE;
    }

	GLuint &idRef = pTexture->getRefTextureGfxID();

    glEnable(GL_TEXTURE_2D);
    // Generate texture object ONLY IF NEEDED
	if( !idRef ) {
        glGenTextures(1, &idRef);
       // if(!checkGlError("glGenTextures")) {
       //     return FG_FALSE;
       // }
    }

    glBindTexture(GL_TEXTURE_2D, idRef);
    //if(!checkGlError("glBindTexture")) {
    //    return FG_FALSE;
    //}

    // Disable mipmapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //if(!checkGlError("[various GL]")) {
    //    return FG_FALSE;
    //}

	// #TODO
	// #FIXME check for quick pixel format in/out

    // Upload
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pTexture->getWidth(), pTexture->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, pTexture->getRawData());
    //if(!checkGlError("glTexImage2D")) {
    //    return false;
    //}

    // FIXME should truly do this
    //if( 0 && tex_facade->mode() == fgTextureResource::TEXTURE )
	//	tex_facade->releaseNonGFX();
	m_resourceManager->unlockResource(pTexture);

    return FG_TRUE;
}
