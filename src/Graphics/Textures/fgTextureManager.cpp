/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include <map>

#include "../../fgCommon.h"
#include "../../Hardware/fgQualityManager.h"

#include "fgTextureCommon.h"
#include "fgTextureResource.h"
#include "fgTextureManager.h"
#include "../../fgResourceManager.h"

template <>
bool fgSingleton<fgTextureManager>::instanceFlag = false;

template <>
fgTextureManager *fgSingleton<fgTextureManager>::instance = NULL;

/**
 * Protected constructor
 */
fgTextureManager::fgTextureManager() {
}

/**
 * Protected destructor
 */
fgTextureManager::~fgTextureManager() {
}

/*
 *
 */
void fgTextureManager::clear(void) {
}

/*
 *
 */
void fgTextureManager::destroy(void) {
}

/*
 *
 */
fgBool fgTextureManager::initialize(void) {
	return FG_TRUE;
}

/**
 * UPLOAD to VRAM – skips reload from disk ONLY if possible
 */
fgBool fgTextureManager::allToVRAM(void) {
    fgBool result = FG_TRUE;
	fgResourceType searchTypes[] = {FG_RESOURCE_TEXTURE, FG_RESOURCE_FONT, FG_RESOURCE_INVALID};
	//
	// #FIXME #P1 - this needs more testing and should look quite different
	// right now it's just bollocks
	//
	FG_ResourceManager->goToBegin();
	while(FG_ResourceManager->isValid()) {
		fgResource *resource = FG_ResourceManager->getCurrentResource();
		if(!resource) {
			return FG_FALSE;
			// FAIL
		}
		fgResourceType resType = resource->getResourceType();
		fgQuality quality = resource->getQuality();
		if((resType == FG_RESOURCE_TEXTURE || resType == FG_RESOURCE_FONT) && 
			(quality == FG_QualityManager->getQuality() || 
			quality == FG_QUALITY_UNIVERSAL) ) {
				// Check if resource is locked - if it is - it's quite possible
				// that it needs to be used in the future - so upload it
				if(resource->isLocked()) {
					fgTextureResource *textureResource = (fgTextureResource *)resource;
					fgTextureGfxID& texGfxID = textureResource->getRefTextureGfxID();
					// #FIXME #P1 - i just don't know what I am doing... this all so blurry.
					if(glIsTexture(texGfxID) == GL_FALSE || !textureResource->isDisposed()) {
						if(!textureResource->recreate()) {
							FG_ErrorLog("Could not recrete texture '%s'\n", textureResource->getFilePathStr());
							// FAIL
							result = FG_FALSE;
						}
					} else {
						// SUCCESS
						if(!makeTexture(textureResource)) {
							result = FG_FALSE;
							// FAIL
							FG_ErrorLog("Could not upload texture '%s'\n", textureResource->getFilePathStr());
						}
					}
				} // else: if resource is not locked then most likely it is not needed
		}
		//FG_ResourceManager->goToNext(FG_RESOURCE_TEXTURE);
		FG_ResourceManager->goToNext(searchTypes, 3);
	}

    return result;
}

/**
 * Releases all NonGl (i.e. non VRAM) data
 */
void fgTextureManager::allReleaseNonGFX(void) 
{
	fgResourceType searchTypes[] = {FG_RESOURCE_TEXTURE, FG_RESOURCE_FONT, FG_RESOURCE_INVALID};
	//
	// #FIXME #P1 - this needs more testing and should look quite different
	// right now it's just bollocks
	//
	FG_ResourceManager->goToBegin();
	while(FG_ResourceManager->isValid()) {
		fgResource *resource = FG_ResourceManager->getCurrentResource();
		if(!resource) {
			return;
			// FAIL
		}
		fgResourceType resType = resource->getResourceType();
		if(resType == FG_RESOURCE_TEXTURE || resType == FG_RESOURCE_FONT) {
			fgTextureResource *textureResource = (fgTextureResource *)resource;
			textureResource->releaseNonGFX();
		}
		//FG_ResourceManager->goToNext(FG_RESOURCE_TEXTURE);
		FG_ResourceManager->goToNext(searchTypes, 3);
	}
	FG_ResourceManager->refreshMemory();
}

/**
 * Releases all OpenGl (i.e. texture ids) data
 */
void fgTextureManager::allReleaseGFX(void) {
	fgResourceType searchTypes[] = {FG_RESOURCE_TEXTURE, FG_RESOURCE_FONT, FG_RESOURCE_INVALID};
	//
	// #FIXME #P1 - this needs more testing and should look quite different
	// right now it's just bollocks
	//
	FG_ResourceManager->goToBegin();
	while(FG_ResourceManager->isValid()) {
		fgResource *resource = FG_ResourceManager->getCurrentResource();
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
			}
			textureResource->releaseNonGFX();
		}
		//FG_ResourceManager->goToNext(FG_RESOURCE_TEXTURE);
		FG_ResourceManager->goToNext(searchTypes, 3);
	}
	FG_ResourceManager->refreshMemory();
}

/**
 * Uploads image to VRAM as a texture
 *
 * TODO: mozliwa jest optymalizacja: gdy wymiary tekstury
 * uploadowanej drugi raz sa takie same, mozna uzyc
 * glTexSubImage2D zamiast glTexImage2D
 */
fgBool fgTextureManager::makeTexture(fgTextureResource *pTexture) {

    if(!pTexture) {
        FG_ErrorLog("Cannot upload texture - texture resource is NULL");
        return FG_FALSE;
    }
	if(!FG_ResourceManager->isResourceManaged(pTexture)) {
		FG_ErrorLog("Cannot upload texture - texture resource is not managed by Resource Manager");
		return FG_FALSE;
	}
    // Supports creation of texture, and update of texture
	/*if ( !tex_facade->makeGFXTexture() ) {
		FG_ErrorLog("Making texture [%d] failed", TEX_ID);
		return false;
	}*/

	FG_ResourceManager->lockResource(pTexture);

	if(!pTexture->getRawData() || pTexture->isDisposed()) {
        FG_ErrorLog("Cannot upload texture - texture resource is disposed / empty");
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
	FG_ResourceManager->unlockResource(pTexture);

    return FG_TRUE;
}
