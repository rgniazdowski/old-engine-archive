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
		m_resourceManager = static_cast<fgResourceManager *>(resourceManager);
	}
	m_managerType = FG_MANAGER_TEXTURE;
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
	m_managerType = FG_MANAGER_TEXTURE;
}

/*
 *
 */
fgBool fgTextureManager::destroy(void) 
{
	m_resourceManager = NULL;
	m_init = FG_FALSE;
	return FG_TRUE;
}

/*
 *
 */
fgBool fgTextureManager::initialize(void) 
{
	if(!m_resourceManager)
		return FG_FALSE;
	m_init = FG_TRUE;
	m_managerType = FG_MANAGER_TEXTURE;
	return FG_TRUE;
}

/**
 * UPLOAD to VRAM – skips reload from disk ONLY if needed
 */
fgBool fgTextureManager::allToVRAM(fgBool reupload)
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
	if(reupload) {
		FG_LOG::PrintDebug("GFX: Will now reupload textures that were previously in VRAM...");
	}
	m_resourceManager->goToBegin();
	while(m_resourceManager->isValid()) {
		fgResource *resource = m_resourceManager->getCurrentResource();
		if(!resource) {
			FG_LOG::PrintError("GFX: Loop in texture manager, resource is %p\n", resource);
			return FG_FALSE;
		}
		fgResourceType resType = resource->getResourceType();
		fgQuality quality = resource->getQuality();
		if((resType == FG_RESOURCE_TEXTURE || resType == FG_RESOURCE_FONT) &&
			(quality == FG_QualityManager->getQuality() ||
			quality == FG_QUALITY_UNIVERSAL) ) 
		{
			fgBool force = FG_FALSE;
			fgTextureResource *textureResource = (fgTextureResource *)resource;
			if(reupload && textureResource->isInVRAM())
				force = FG_TRUE;
			fgTextureManager::uploadToVRAM(textureResource, force);
		}
		m_resourceManager->goToNext(searchTypes, 3);
	}
	m_allInVRAM = FG_TRUE;
    return result;
}

/*
 *
 */
fgBool fgTextureManager::uploadToVRAM(fgTextureResource *texture, fgBool force)
{
	if(!m_resourceManager || !texture)
		return FG_FALSE;
	fgResourceType resType = texture->getResourceType();
	fgQuality quality = texture->getQuality();
	if( ! ((resType == FG_RESOURCE_TEXTURE || resType == FG_RESOURCE_FONT)) ) { 
		FG_LOG::PrintDebug("GFX: Resource '%s' is not texture?", texture->getNameStr());
		return FG_FALSE;
	}
	fgBool result = FG_TRUE;
	fgTextureGfxID& texGfxID = texture->getRefTextureGfxID();
	if(glIsTexture(texGfxID) == GL_TRUE && !force) {
		return result;
	}
	FG_LOG::PrintDebug("GFX: Is texture '%s' locked? [%d]", texture->getNameStr(), texture->isLocked());
	if(texture->isLocked() || force) {
		FG_LOG::PrintDebug("GFX: Going to upload texture to VRAM - '%s'", texture->getNameStr());
		FG_LOG::PrintDebug("GFX: Is Texture? [%d] ; Was in VRAM? [%d]", (int)glIsTexture(texGfxID), texture->isInVRAM());
		if(glIsTexture(texGfxID) == GL_TRUE) {
			releaseGFX(texture);
		}
		if(!texture->hasOwnedRAM()) {
			if(!texture->create()) {
				FG_LOG::PrintError("GFX: Could not recreate texture '%s'", texture->getFilePathStr());
				result = FG_FALSE;
			}
		} 
		if(texture->hasOwnedRAM())
		{
			if(!fgTextureManager::makeTexture(texture)) {
				result = FG_FALSE;
				FG_LOG::PrintError("GFX: Could not upload texture '%s' to VRAM", texture->getFilePathStr());
			} else {
				if(glIsTexture(texGfxID))
					texture->setIsInVRAM(FG_TRUE);
			}
		}
	} // else: if resource is not locked then most likely it is not needed
	return result;
}

/*
 *
 */
fgBool fgTextureManager::uploadToVRAM(const std::string& nameTag, fgBool force)
{
	if(!m_resourceManager)
		return FG_FALSE;
	
	return uploadToVRAM(nameTag.c_str(), force);
}

/*
 *
 */
fgBool fgTextureManager::uploadToVRAM(const char *nameTag, fgBool force)
{
	if(!m_resourceManager)
		return FG_FALSE;
	fgResource *resource = m_resourceManager->get(nameTag);
	if(!resource)
		return FG_FALSE;
	if(resource->getResourceType() != FG_RESOURCE_TEXTURE || resource->getResourceType() != FG_RESOURCE_FONT)
		return FG_FALSE;
	fgTextureResource *texture = (fgTextureResource *)resource;
	return uploadToVRAM(texture, force);
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
		}
		fgResourceType resType = resource->getResourceType();
		if(resType == FG_RESOURCE_TEXTURE || resType == FG_RESOURCE_FONT) {
			fgTextureResource *textureResource = (fgTextureResource *)resource;
			fgTextureGfxID& texGfxID = textureResource->getRefTextureGfxID();
			if(glIsTexture(texGfxID) == GL_TRUE) {
				// There is a texture to release from GFX
				glDeleteTextures(1, &texGfxID);
				texGfxID = 0;
				textureResource->setTextureGfxID(0);
				//textureResource->setIsInVRAM(FG_FALSE);
			}
			textureResource->releaseNonGFX();
		}
		m_resourceManager->goToNext(searchTypes, 3);
	}
	m_resourceManager->refreshMemory();
}

/*
 *
 */
void fgTextureManager::releaseGFX(fgTextureResource *texture)
{
	if(!texture)
		return;
	fgResourceType resType = texture->getResourceType();
	if(resType == FG_RESOURCE_TEXTURE || resType == FG_RESOURCE_FONT) {
		fgTextureGfxID& texGfxID = texture->getRefTextureGfxID();
		if(glIsTexture(texGfxID) == GL_TRUE) {
			// There is a texture to release from GFX
			glDeleteTextures(1, &texGfxID);
			texGfxID = 0;
			texture->setTextureGfxID(0);
		}
	}
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
        FG_LOG::PrintError("GFX: Cannot upload texture - texture resource is NULL");
        return FG_FALSE;
    }
	if(!m_resourceManager->isManaged(pTexture)) {
		FG_LOG::PrintError("GFX: Cannot upload texture - texture resource is not managed by Resource Manager");
		return FG_FALSE;
	}
	m_resourceManager->lockResource(pTexture);

	if(!pTexture->getRawData() || !pTexture->hasOwnedRAM()) {
        FG_LOG::PrintError("GFX: Cannot upload texture - texture resource is disposed / empty");
        return FG_FALSE;
    }
	FG_LOG::PrintDebug("GFX: Preparing for texture upload [%s]...", pTexture->getNameStr());
	GLuint &idRef = pTexture->getRefTextureGfxID();
    // Generate texture object ONLY IF NEEDED
	if( !glIsTexture(idRef) ) {
        glGenTextures(1, &idRef);
    }
	fgBool status = FG_TRUE;
	std::string failedFuncs;
	fgGfxPlatform::context()->bindTexture2D(idRef);
	if(fgGLError("glBindTexture")) {
		status = FG_FALSE;
		failedFuncs.append("glBindTexture, ");
	}

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	if(fgGLError("glTexParameteri")) {
		status = FG_FALSE;
		failedFuncs.append("glTexParameteri, ");
	}
    // Upload
	fgGFXint internalformat = GL_RGBA;
	fgGFXint dataformat = GL_RGBA;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	if(pTexture->getComponents() == 4) {
		internalformat = GL_RGBA;
		dataformat = GL_RGBA;
	} else if(pTexture->getComponents() == 3) {
		internalformat = GL_RGB;
		dataformat = GL_RGB;
	} else if(pTexture->getComponents() == 1) {
		internalformat = GL_ALPHA;
		dataformat = GL_ALPHA;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, internalformat, pTexture->getWidth(), pTexture->getHeight(), 0, dataformat, GL_UNSIGNED_BYTE, pTexture->getRawData());
	if(fgGLError("glTexImage2D")) {
		status = FG_FALSE;
		failedFuncs.append("glTexImage2D, ");
	}
	m_resourceManager->unlockResource(pTexture);
	if(!status) {
		FG_LOG::PrintError("GFX: Errors occured on texture '%s' upload. Failing functions: %s", pTexture->getNameStr(), failedFuncs.substr(0, failedFuncs.length()-2).c_str());
		failedFuncs.clear();
	} else {
		FG_LOG::PrintDebug("GFX: Texture [%s] uploaded successfully: gfxID=%d;", pTexture->getNameStr(), pTexture->getTextureGfxID());
		FG_LOG::PrintDebug("GFX: Texture [%s] dimensions: %dx%d", pTexture->getNameStr(), pTexture->getWidth(), pTexture->getHeight());
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    return status;
}
