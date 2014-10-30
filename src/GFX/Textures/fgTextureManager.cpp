/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgTextureManager.h"
#include "fgTextureResource.h"

#include "Hardware/fgQualityManager.h"
#include "Resource/fgResourceManager.h"

/**
 * Protected constructor
 */
fgTextureManager::fgTextureManager(fgManagerBase *pResourceMgr) :
m_allInVRAM(FG_FALSE) {
    fgStatusReporter::setReportToMsgSystem(FG_TRUE);
    m_resourceMgr = NULL;
    if(!pResourceMgr) {
        setErrorCode(FG_ERRNO_WRONG_PARAM);
        m_init = FG_FALSE;
    } else if(pResourceMgr->getManagerType() == FG_MANAGER_RESOURCE) {
        m_resourceMgr = pResourceMgr;
    }
    m_managerType = FG_MANAGER_TEXTURE;
}

/**
 * Protected destructor
 */
fgTextureManager::~fgTextureManager() {
    destroy();
}

/**
 * 
 */
void fgTextureManager::clear(void) {
    m_managerType = FG_MANAGER_TEXTURE;
}

/**
 * 
 * @return 
 */
fgBool fgTextureManager::destroy(void) {
    m_resourceMgr = NULL;
    m_init = FG_FALSE;
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool fgTextureManager::initialize(void) {
    if(!m_resourceMgr)
        return FG_FALSE;
    m_init = FG_TRUE;
    m_managerType = FG_MANAGER_TEXTURE;
    return FG_TRUE;
}

/**
 * 
 * @param pResourceMgr
 */
void fgTextureManager::setResourceManager(fgManagerBase *pResourceMgr) {
    if(!pResourceMgr)
        return;
    if(pResourceMgr->getManagerType() == FG_MANAGER_RESOURCE)
        m_resourceMgr = pResourceMgr;
}

/**
 * 
 * @return 
 */
fgManagerBase *fgTextureManager::getResourceManager(void) const {
    return m_resourceMgr;
}

/**
 * UPLOAD to VRAM – skips reload from disk ONLY if needed
 */
fgBool fgTextureManager::allToVRAM(fgBool reupload) {
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
    ((fgResourceManager *)m_resourceMgr)->goToBegin();
    while(((fgResourceManager *)m_resourceMgr)->isValid()) {
        fgResource *resource = ((fgResourceManager *)m_resourceMgr)->getCurrentResource();
        if(!resource) {
            FG_LOG::PrintError("GFX: Loop in texture manager, resource is %p\n", resource);
            return FG_FALSE;
        }
        fgResourceType resType = resource->getResourceType();
        fgQuality quality = resource->getQuality();
        if((resType == FG_RESOURCE_TEXTURE || resType == FG_RESOURCE_FONT) &&
           (FG_TRUE/* #FIXME quality == FG_QualityManager->getQuality()*/ ||
            quality == FG_QUALITY_UNIVERSAL)) {
            fgBool force = FG_FALSE;
            fgTextureResource *textureResource = (fgTextureResource *)resource;
            if(reupload && textureResource->isInVRAM())
                force = FG_TRUE;
            fgTextureManager::uploadToVRAM(textureResource, force);
        }
        ((fgResourceManager *)m_resourceMgr)->goToNext(searchTypes, 3);
    }
    m_allInVRAM = FG_TRUE;
    return result;
}

/**
 * 
 * @param texture
 * @param force
 * @return 
 */
fgBool fgTextureManager::uploadToVRAM(fgTextureResource *texture, fgBool force) {
    if(!((fgResourceManager *)m_resourceMgr) || !texture)
        return FG_FALSE;
    fgResourceType resType = texture->getResourceType();
    fgQuality quality = texture->getQuality();
    if(!((resType == FG_RESOURCE_TEXTURE || resType == FG_RESOURCE_FONT))) {
        FG_LOG::PrintDebug("GFX: Resource '%s' is not texture?", texture->getNameStr());
        return FG_FALSE;
    }
    fgBool result = FG_TRUE;
    fgGfxTextureID& texGfxID = texture->getRefGfxID();
    if(fgGfxPlatform::context()->isTexture(texGfxID) == FG_GFX_TRUE && !force) {
        return result;
    }
    FG_LOG::PrintDebug("GFX: Is texture '%s' locked? [%d]", texture->getNameStr(), texture->isLocked());
    if(texture->isLocked() || force) {
        FG_LOG::PrintDebug("GFX: Going to upload texture to VRAM - '%s'", texture->getNameStr());
        FG_LOG::PrintDebug("GFX: Is Texture? [%d] ; Was in VRAM? [%d]", (int)glIsTexture(texGfxID), texture->isInVRAM());
        if(glIsTexture(texGfxID) == GL_TRUE) {
            fgTextureManager::releaseGFX(texture);
        }
        if(!texture->hasOwnedRAM()) {
            if(!texture->create()) {
                FG_LOG::PrintError("GFX: Could not recreate texture '%s'", texture->getFilePathStr());
                result = FG_FALSE;
            }
        }
        if(texture->hasOwnedRAM()) {
            if(!fgTextureManager::makeTexture(texture)) {
                result = FG_FALSE;
                FG_LOG::PrintError("GFX: Could not upload texture '%s' to VRAM", texture->getFilePathStr());
            } else {
                if(fgGfxPlatform::context()->isTexture(texGfxID) == FG_GFX_TRUE)
                    texture->setIsInVRAM(FG_TRUE);
            }
        }
    } // else: if resource is not locked then most likely it is not needed
    return result;
}

/**
 * 
 * @param nameTag
 * @param force
 * @return 
 */
fgBool fgTextureManager::uploadToVRAM(const std::string& nameTag, fgBool force) {
    if(!m_resourceMgr)
        return FG_FALSE;

    return uploadToVRAM(nameTag.c_str(), force);
}

/**
 * 
 * @param nameTag
 * @param force
 * @return 
 */
fgBool fgTextureManager::uploadToVRAM(const char *nameTag, fgBool force) {
    if(!m_resourceMgr)
        return FG_FALSE;
    fgResource *resource = ((fgResourceManager *)m_resourceMgr)->get(nameTag);
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
void fgTextureManager::allReleaseNonGFX(void) {
    if(!m_resourceMgr)
        return;
    fgResourceType searchTypes[] = {FG_RESOURCE_TEXTURE, FG_RESOURCE_FONT, FG_RESOURCE_INVALID};
    //
    // #FIXME #P1 - this needs more testing and should look quite different
    // right now it's just bollocks
    //
    ((fgResourceManager *)m_resourceMgr)->goToBegin();
    while(((fgResourceManager *)m_resourceMgr)->isValid()) {
        fgResource *resource = ((fgResourceManager *)m_resourceMgr)->getCurrentResource();
        if(!resource) {
            return;
            // FAIL
        }
        fgResourceType resType = resource->getResourceType();
        if(resType == FG_RESOURCE_TEXTURE || resType == FG_RESOURCE_FONT) {
            fgTextureResource *textureResource = (fgTextureResource *)resource;
            textureResource->releaseNonGFX();
            if(fgGfxPlatform::context()->isTexture(textureResource->getRefGfxID()) == GL_TRUE)
                textureResource->setIsInVRAM(FG_TRUE);
        }
        ((fgResourceManager *)m_resourceMgr)->goToNext(searchTypes, 3);
    }
    ((fgResourceManager *)m_resourceMgr)->refreshMemory();
}

/**
 * Releases all OpenGl (i.e. texture ids) data
 */
void fgTextureManager::allReleaseGFX(void) {
    if(!m_resourceMgr)
        return;
    fgResourceType searchTypes[] = {FG_RESOURCE_TEXTURE, FG_RESOURCE_FONT, FG_RESOURCE_INVALID};
    //
    // #FIXME #P1 - this needs more testing and should look quite different
    // right now it's just bollocks
    //
    ((fgResourceManager *)m_resourceMgr)->goToBegin();
    while(((fgResourceManager *)m_resourceMgr)->isValid()) {
        fgResource *resource = ((fgResourceManager *)m_resourceMgr)->getCurrentResource();
        if(!resource) {
            return;
        }
        fgResourceType resType = resource->getResourceType();
        if(resType == FG_RESOURCE_TEXTURE || resType == FG_RESOURCE_FONT) {
            fgTextureResource *textureResource = (fgTextureResource *)resource;
            fgGfxTextureID& texGfxID = textureResource->getRefGfxID();
            fgGfxPlatform::context()->deleteTexture(texGfxID);
            //textureResource->releaseNonGFX();
        }
        ((fgResourceManager *)m_resourceMgr)->goToNext(searchTypes, 3);
    }
    ((fgResourceManager *)m_resourceMgr)->refreshMemory();
}

/**
 * 
 * @param texture
 */
void fgTextureManager::releaseGFX(fgTextureResource *texture) {
    if(!texture)
        return;
    fgResourceType resType = texture->getResourceType();
    if(resType == FG_RESOURCE_TEXTURE || resType == FG_RESOURCE_FONT) {
        fgGfxTextureID& texGfxID = texture->getRefGfxID();
        fgGfxPlatform::context()->deleteTexture(texGfxID);
    }
}

/**
 * Uploads image to VRAM as a texture
 *
 * TODO: mozliwa jest optymalizacja: gdy wymiary tekstury
 * uploadowanej drugi raz sa takie same, mozna uzyc
 * glTexSubImage2D zamiast glTexImage2D
 */
fgBool fgTextureManager::makeTexture(fgTextureResource *pTexture) {
    if(!m_resourceMgr)
        return FG_FALSE;

    if(!pTexture) {
        FG_LOG::PrintError("GFX: Cannot upload texture - texture resource is NULL");
        return FG_FALSE;
    }
    if(!((fgResourceManager *)m_resourceMgr)->isManaged(pTexture)) {
        FG_LOG::PrintError("GFX: Cannot upload texture - texture resource is not managed by Resource Manager");
        return FG_FALSE;
    }
    ((fgResourceManager *)m_resourceMgr)->lockResource(pTexture);

    if(!pTexture->getRawData() || !pTexture->hasOwnedRAM()) {
        FG_LOG::PrintError("GFX: Cannot upload texture - texture resource is disposed / empty");
        return FG_FALSE;
    }
    FG_LOG::PrintDebug("GFX: Preparing for texture upload [%s]...", pTexture->getNameStr());
    fgGfxTextureID& texGfxID = pTexture->getRefGfxID();
    // Generate texture object ONLY IF NEEDED
    if(FG_GFX_FALSE == fgGfxPlatform::context()->isTexture(texGfxID)) {
        fgGfxPlatform::context()->genTexture(pTexture->getPtrGfxID());
    }
    fgBool status = FG_TRUE;
    std::string failedFuncs;
    fgGfxPlatform::context()->bindTexture(texGfxID);
    if(fgGLError("glBindTexture")) {
        status = FG_FALSE;
        failedFuncs.append("glBindTexture, ");
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (fgGFXint)GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (fgGFXint)GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (fgGFXint)GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (fgGFXint)GL_MIRRORED_REPEAT);
    if(fgGLError("glTexParameteri")) {
        status = FG_FALSE;
        failedFuncs.append("glTexParameteri, ");
    }
    // Upload
    fgGFXint internalformat = (fgGFXint)GL_RGBA;
    fgGFXint dataformat = (fgGFXint)GL_RGBA;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    if(pTexture->getComponents() == 4) {
        internalformat = (fgGFXint)GL_RGBA;
        dataformat = (fgGFXint)GL_RGBA;
    } else if(pTexture->getComponents() == 3) {
        internalformat = (fgGFXint)GL_RGB;
        dataformat = (fgGFXint)GL_RGB;
    } else if(pTexture->getComponents() == 1) {
        internalformat = (fgGFXint)GL_ALPHA;
        dataformat = (fgGFXint)GL_ALPHA;
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, (fgGFXint)internalformat, pTexture->getWidth(), pTexture->getHeight(), 0, (fgGFXenum)dataformat, GL_UNSIGNED_BYTE, pTexture->getRawData());
    if(fgGLError("glTexImage2D")) {
        status = FG_FALSE;
        failedFuncs.append("glTexImage2D, ");
    }
    ((fgResourceManager *)m_resourceMgr)->unlockResource(pTexture);
    if(!status) {
        FG_LOG::PrintError("GFX: Errors on texture '%s' upload. Failing functions: %s", pTexture->getNameStr(), failedFuncs.substr(0, failedFuncs.length() - 2).c_str());
        failedFuncs.clear();
    } else {
        FG_LOG::PrintDebug("GFX: Texture [%s] uploaded successfully: gfxID=%d;", pTexture->getNameStr(), pTexture->getRefGfxID().id);
        FG_LOG::PrintDebug("GFX: Texture [%s] dimensions: %dx%d", pTexture->getNameStr(), pTexture->getWidth(), pTexture->getHeight());
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    return status;
}
