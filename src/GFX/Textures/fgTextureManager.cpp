/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgTextureManager.h"
#include "fgTextureResource.h"

#include "Hardware/fgQualityManager.h"
#include "Hardware/fgHardwareState.h"
#include "Resource/fgResourceManager.h"
#include "Event/fgEventDefinitions.h"
#include "Event/fgEventManager.h"

using namespace fg;

/**
 * Protected constructor
 */
gfx::CTextureManager::CTextureManager(fg::base::CManager *pResourceMgr) :
m_pResourceMgr(NULL),
m_pEventMgr(NULL),
m_resourceCreatedCallback(NULL),
m_allInVRAM(FG_FALSE) {
    //    fgStatusReporter::setReportToMsgSystem(FG_TRUE);
    m_pResourceMgr = NULL;
    if(!pResourceMgr) {
        //setErrorCode(FG_ERRNO_WRONG_PARAM);
        m_init = FG_FALSE;
    } else if(pResourceMgr->getManagerType() == FG_MANAGER_RESOURCE) {
        m_pResourceMgr = pResourceMgr;
        m_pEventMgr = static_cast<resource::CResourceManager *>(pResourceMgr)->getEventManager();
        registerResourceCallbacks();
    }
    m_managerType = FG_MANAGER_TEXTURE;
}

/**
 * Protected destructor
 */
gfx::CTextureManager::~CTextureManager() {
    destroy();
}

/*
 *
 */
void gfx::CTextureManager::registerResourceCallbacks(void) {
    if(!m_pEventMgr)
        return;

    if(!m_resourceCreatedCallback)
        m_resourceCreatedCallback = new fg::event::CMethodCallback<CTextureManager>(this, &gfx::CTextureManager::resourceCreatedHandler);

    static_cast<fg::event::CEventManager *>(m_pEventMgr)->addCallback(FG_EVENT_RESOURCE_CREATED, m_resourceCreatedCallback);
    //m_pEventMgr->addEventCallback(FG_EVENT_TOUCH_RELEASED, m_gameTouchCallback);
    //m_pEventMgr->addEventCallback(FG_EVENT_TOUCH_MOTION, m_gameTouchCallback);
    //m_pEventMgr->addEventCallback(FG_EVENT_TOUCH_TAP_FINISHED, m_gameTouchCallback);

    /*if(!m_gameMouseCallback)
        m_gameMouseCallback = new fgClassCallback<fgGameMain>(this, &fgGameMain::gameMouseHandler);

    m_pEventMgr->addEventCallback(FG_EVENT_MOUSE_PRESSED, m_gameMouseCallback);
    m_pEventMgr->addEventCallback(FG_EVENT_MOUSE_RELEASED, m_gameMouseCallback);
    m_pEventMgr->addEventCallback(FG_EVENT_MOUSE_MOTION, m_gameMouseCallback);*/
}

/*
 *
 */
void gfx::CTextureManager::unregisterResourceCallbacks(void) {
    if(!m_pEventMgr)
        return;

    static_cast<fg::event::CEventManager *>(m_pEventMgr)->removeCallback(FG_EVENT_RESOURCE_CREATED, m_resourceCreatedCallback);

    //m_pEventMgr->removeEventCallback(FG_EVENT_MOUSE_PRESSED, m_gameMouseCallback);
    //m_pEventMgr->removeEventCallback(FG_EVENT_MOUSE_RELEASED, m_gameMouseCallback);
    //m_pEventMgr->removeEventCallback(FG_EVENT_MOUSE_MOTION, m_gameMouseCallback);

}

/**
 * 
 */
void gfx::CTextureManager::clear(void) {
    m_managerType = FG_MANAGER_TEXTURE;
}

/**
 * 
 * @return 
 */
fgBool gfx::CTextureManager::destroy(void) {
    unregisterResourceCallbacks();
    if(m_resourceCreatedCallback)
        delete m_resourceCreatedCallback;
    m_resourceCreatedCallback = NULL;
    m_pResourceMgr = NULL;
    m_pEventMgr = NULL;
    m_init = FG_FALSE;
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool gfx::CTextureManager::initialize(void) {
    if(!m_pResourceMgr)
        return FG_FALSE;
    m_init = FG_TRUE;
    m_managerType = FG_MANAGER_TEXTURE;
    return FG_TRUE;
}

/**
 * 
 * @param pResourceMgr
 */
void gfx::CTextureManager::setResourceManager(fg::base::CManager* pResourceMgr) {
    if(!pResourceMgr)
        return;
    if(pResourceMgr->getManagerType() == FG_MANAGER_RESOURCE) {
        m_pResourceMgr = pResourceMgr;
        fg::base::CManager *pEventMgr = static_cast<resource::CResourceManager *>(m_pResourceMgr)->getEventManager();
        if(!pEventMgr) {
            unregisterResourceCallbacks();
            m_pEventMgr = NULL;
        } else if(m_pEventMgr && m_pEventMgr != pEventMgr) {
            unregisterResourceCallbacks();
        }
        m_pEventMgr = pEventMgr;
        if(m_pEventMgr)
            registerResourceCallbacks();
    }
}

/**
 * 
 * @return 
 */
fg::base::CManager* gfx::CTextureManager::getResourceManager(void) const {
    return m_pResourceMgr;
}

/**
 * 
 * @param texHandle
 * @return 
 */
fgGfxTextureID& gfx::CTextureManager::getRefGfxID(const fgResourceHandle& texHandle) {
    if(!m_pResourceMgr)
        return m_emptyGfxID;
    gfx::CTextureResource *pTexture = (CTextureResource *)static_cast<resource::CResourceManager *>(m_pResourceMgr)->get(texHandle);
    if(!pTexture) {
        m_emptyGfxID.reset();
        return m_emptyGfxID;
    }
    return pTexture->getRefGfxID();
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgGfxTextureID& gfx::CTextureManager::getRefGfxID(const std::string& nameTag) {
    if(!m_pResourceMgr || nameTag.empty())
        return m_emptyGfxID;
    gfx::CTextureResource *pTexture = (CTextureResource *)static_cast<resource::CResourceManager *>(m_pResourceMgr)->get(nameTag);
    if(!pTexture) {
        m_emptyGfxID.reset();
        return m_emptyGfxID;
    }
    return pTexture->getRefGfxID();
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgGfxTextureID& gfx::CTextureManager::getRefGfxID(const char *nameTag) {
    if(!m_pResourceMgr || !nameTag)
        return m_emptyGfxID;
    gfx::CTextureResource *pTexture = (CTextureResource *)static_cast<resource::CResourceManager *>(m_pResourceMgr)->get(nameTag);
    if(!pTexture) {
        m_emptyGfxID.reset();
        return m_emptyGfxID;
    }
    return pTexture->getRefGfxID();
}

/**
 * 
 * @param argv
 * @return 
 */
fgBool gfx::CTextureManager::resourceCreatedHandler(fg::event::CArgumentList * argv) {
    if(!argv)
        return FG_FALSE;
    fgEventBase *event = (fgEventBase *)argv->getValueByID(0);
    if(!event)
        return FG_FALSE;
    fgEventType type = event->eventType;
    if(type != FG_EVENT_RESOURCE_CREATED)
        return FG_FALSE;
    fgResourceEvent *resourceEvent = (fgResourceEvent *)event;
    resource::CResource *pResource = resourceEvent->resource;
    if(!pResource)
        return FG_FALSE;
    // Some of those checks are not necessary because
    // the same checks are performed inside of uploadToVRAM()
    // function and makeTexture(). Also uploadToVRAM() may call
    // recreate function itself - in that case no additional
    // event is being thrown. CREATE RESOURCE event is thrown
    // at the resource manager. Resources can't do that.
    if(pResource->getResourceType() != resource::FONT &&
       pResource->getResourceType() != resource::TEXTURE)
        return FG_FALSE;
    CTexture *pTexture = (CTexture *)pResource;
    //if(!pTexture->getRawData() || pTexture->isDisposed())
    //    return FG_FALSE;
    // Normally this should work without the force flag...
    // It's needed because for now resource lock/unlock 
    // is not working completely...
    return gfx::CTextureManager::uploadToVRAM(pTexture, FG_TRUE);
}

/**
 * UPLOAD to VRAM – skips reload from disk ONLY if needed
 */
fgBool gfx::CTextureManager::allToVRAM(fgBool reupload) {
    if(!m_init) {
        if(!initialize())
            return FG_FALSE;
    }
    fgBool result = FG_TRUE;
    resource::ResourceType searchTypes[] = {resource::TEXTURE, resource::FONT, resource::INVALID};
    //
    // #FIXME #P1 - this needs more testing and should look quite different
    // right now it's just bollocks
    //
    if(reupload) {
        FG_LOG_DEBUG("GFX: Will now re-upload textures that were previously in VRAM...");
    }
    ((resource::CResourceManager *)m_pResourceMgr)->goToBegin();
    while(((resource::CResourceManager *)m_pResourceMgr)->isValid()) {
        resource::CResource *resource = ((resource::CResourceManager *)m_pResourceMgr)->getCurrentResource();
        if(!resource) {
            FG_LOG::PrintError("GFX: Loop in texture manager, resource is %p\n", resource);
            return FG_FALSE;
        }
        resource::ResourceType resType = resource->getResourceType();
        fgQuality quality = resource->getQuality();
        if((resType == resource::TEXTURE || resType == resource::FONT) &&
           (FG_TRUE/* #FIXME quality == FG_QualityManager->getQuality()*/ ||
            quality == FG_QUALITY_UNIVERSAL)) {
            fgBool force = FG_FALSE;
            CTextureResource *textureResource = (CTextureResource *)resource;
            if(reupload && textureResource->isInVRAM())
                force = FG_TRUE;
            gfx::CTextureManager::uploadToVRAM(textureResource, force);
        }
        ((resource::CResourceManager *)m_pResourceMgr)->goToNext(searchTypes, 3);
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
fgBool gfx::CTextureManager::uploadToVRAM(CTexture *texture, fgBool force) {
    if(!((resource::CResourceManager *)m_pResourceMgr) || !texture)
        return FG_FALSE;
    FG_HardwareState->deviceYield();
    resource::ResourceType resType = texture->getResourceType();
    fgQuality quality = texture->getQuality();
    if(!((resType == resource::TEXTURE || resType == resource::FONT))) {
        FG_LOG_DEBUG("GFX: Resource '%s' is not texture?", texture->getNameStr());
        return FG_FALSE;
    }
    fgBool result = FG_TRUE;
    fgGfxTextureID& texGfxID = texture->getRefGfxID();
    if(gfx::CPlatform::context()->isTexture(texGfxID) == FG_GFX_TRUE && !force) {
        return result;
    }
    FG_LOG_DEBUG("GFX: Is texture '%s' locked? [%d]", texture->getNameStr(), texture->isLocked());
    if(texture->isLocked() || force) {
        FG_LOG_DEBUG("GFX: Going to upload texture to VRAM - '%s'", texture->getNameStr());
        FG_LOG_DEBUG("GFX: Is Texture? [%d] ; Was in VRAM? [%d]", (int)glIsTexture(texGfxID), texture->isInVRAM());
        if(glIsTexture(texGfxID) == GL_TRUE) {
            gfx::CTextureManager::releaseGFX(texture);
        }
        if(!texture->hasOwnedRAM()) {
            if(!texture->create()) {
                FG_LOG_ERROR("GFX: Could not recreate texture '%s'", texture->getFilePathStr());
                result = FG_FALSE;
            }
        }
        if(texture->hasOwnedRAM()) {
            if(!gfx::CTextureManager::makeTexture(texture)) {
                result = FG_FALSE;
                FG_LOG_ERROR("GFX: Could not upload texture '%s' to VRAM", texture->getFilePathStr());
            } else {
                if(gfx::CPlatform::context()->isTexture(texGfxID) == FG_GFX_TRUE)
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
fgBool gfx::CTextureManager::uploadToVRAM(const std::string& nameTag, fgBool force) {
    if(!m_pResourceMgr)
        return FG_FALSE;

    return uploadToVRAM(nameTag.c_str(), force);
}

/**
 * 
 * @param nameTag
 * @param force
 * @return 
 */
fgBool gfx::CTextureManager::uploadToVRAM(const char *nameTag, fgBool force) {
    if(!m_pResourceMgr)
        return FG_FALSE;
    FG_HardwareState->deviceYield();
    resource::CResource *resource = ((resource::CResourceManager *)m_pResourceMgr)->get(nameTag);
    if(!resource)
        return FG_FALSE;
    if(resource->getResourceType() != resource::TEXTURE || resource->getResourceType() != resource::FONT)
        return FG_FALSE;
    gfx::CTexture *texture = (gfx::CTexture *)resource;
    return uploadToVRAM(texture, force);
}

/**
 * Releases all NonGl (i.e. non VRAM) data
 */
void gfx::CTextureManager::allReleaseNonGFX(void) {
    if(!m_pResourceMgr)
        return;
    resource::ResourceType searchTypes[] = {resource::TEXTURE, resource::FONT, resource::INVALID};
    //
    // #FIXME #P1 - this needs more testing and should look quite different
    // right now it's just bollocks
    //
    ((resource::CResourceManager *)m_pResourceMgr)->goToBegin();
    while(((resource::CResourceManager *)m_pResourceMgr)->isValid()) {
        resource::CResource *resource = ((resource::CResourceManager *)m_pResourceMgr)->getCurrentResource();
        if(!resource) {
            return;
            // FAIL
        }
        resource::ResourceType resType = resource->getResourceType();
        if(resType == resource::TEXTURE || resType == resource::FONT) {
            CTextureResource *textureResource = (CTextureResource *)resource;
            textureResource->releaseNonGFX();
            if(gfx::CPlatform::context()->isTexture(textureResource->getRefGfxID()) == GL_TRUE)
                textureResource->setIsInVRAM(FG_TRUE);
        }
        ((resource::CResourceManager *)m_pResourceMgr)->goToNext(searchTypes, 3);
    }
    ((resource::CResourceManager *)m_pResourceMgr)->refreshMemory();
}

/**
 * Releases all OpenGL (i.e. texture ids) data
 */
void gfx::CTextureManager::allReleaseGFX(void) {
    if(!m_pResourceMgr)
        return;
    resource::ResourceType searchTypes[] = {resource::TEXTURE, resource::FONT, resource::INVALID};
    //
    // #FIXME #P1 - this needs more testing and should look quite different
    // right now it's just bollocks
    //
    ((resource::CResourceManager *)m_pResourceMgr)->goToBegin();
    while(((resource::CResourceManager *)m_pResourceMgr)->isValid()) {
        resource::CResource *resource = ((resource::CResourceManager *)m_pResourceMgr)->getCurrentResource();
        if(!resource) {
            return;
        }
        resource::ResourceType resType = resource->getResourceType();
        if(resType == resource::TEXTURE || resType == resource::FONT) {
            CTextureResource *textureResource = (CTextureResource *)resource;
            fgGfxTextureID& texGfxID = textureResource->getRefGfxID();
            gfx::CPlatform::context()->deleteTexture(texGfxID);
            //textureResource->releaseNonGFX();
        }
        ((resource::CResourceManager *)m_pResourceMgr)->goToNext(searchTypes, 3);
    }
    ((resource::CResourceManager *)m_pResourceMgr)->refreshMemory();
}

/**
 * 
 * @param texture
 */
void gfx::CTextureManager::releaseGFX(CTextureResource * texture) {
    if(!texture)
        return;
    resource::ResourceType resType = texture->getResourceType();
    if(resType == resource::TEXTURE || resType == resource::FONT) {
        fgGfxTextureID& texGfxID = texture->getRefGfxID();
        gfx::CPlatform::context()->deleteTexture(texGfxID);
    }
}

/**
 * Uploads image to VRAM as a texture
 *
 * TODO: mozliwa jest optymalizacja: gdy wymiary tekstury
 * uploadowanej drugi raz sa takie same, mozna uzyc
 * glTexSubImage2D zamiast glTexImage2D
 */
fgBool gfx::CTextureManager::makeTexture(CTextureResource * pTexture) {
    if(!m_pResourceMgr)
        return FG_FALSE;
    FG_HardwareState->deviceYield();
    if(!pTexture) {
        FG_LOG_ERROR("GFX: Cannot upload texture - texture resource is NULL");
        return FG_FALSE;
    }
    if(!((resource::CResourceManager *)m_pResourceMgr)->isManaged(pTexture)) {
        FG_LOG_ERROR("GFX: Cannot upload texture - texture resource is not managed by Resource Manager");
        return FG_FALSE;
    }
    ((resource::CResourceManager *)m_pResourceMgr)->lockResource(pTexture);

    if(!pTexture->getRawData() || !pTexture->hasOwnedRAM()) {
        FG_LOG_ERROR("GFX: Cannot upload texture - texture resource is disposed / empty");
        return FG_FALSE;
    }
    FG_LOG_DEBUG("GFX: Preparing for texture upload [%s]...", pTexture->getNameStr());
    fgGfxTextureID& texGfxID = pTexture->getRefGfxID();
    // Generate texture object ONLY IF NEEDED
    if(FG_GFX_FALSE == gfx::CPlatform::context()->isTexture(texGfxID)) {
        gfx::CPlatform::context()->genTexture(pTexture->getPtrGfxID());
    }
    fgBool status = FG_TRUE;
    std::string failedFuncs;
    gfx::CPlatform::context()->bindTexture(texGfxID);
    if(fgGLError("glBindTexture")) {
        status = FG_FALSE;
        failedFuncs.append("glBindTexture, ");
    }

    fgGFXuint target = 0;
    fgGFXuint cubeTargets[] = {GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                               GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                               GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z};
    fgTextureType textureType = pTexture->getTextureType();
    if(textureType == FG_TEXTURE_PLAIN || textureType == FG_TEXTURE_FONT) {
        target = GL_TEXTURE_2D;
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, (fgGFXint)GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, (fgGFXint)GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_WRAP_S, (fgGFXint)GL_MIRRORED_REPEAT);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, (fgGFXint)GL_MIRRORED_REPEAT);
    } else if(textureType == FG_TEXTURE_CUBE) {
        target = GL_TEXTURE_CUBE_MAP;
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, (fgGFXint)GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, (fgGFXint)GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_WRAP_S, (fgGFXint)GL_MIRRORED_REPEAT);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, (fgGFXint)GL_MIRRORED_REPEAT);
        //glTexParameteri(target, GL_TEXTURE_WRAP_R, (fgGFXint)GL_MIRRORED_REPEAT); // _R is not in ES 2.0 :( #FIXME
    }

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
    if(textureType == FG_TEXTURE_PLAIN || textureType == FG_TEXTURE_FONT) {
        glTexImage2D(target, 0, (fgGFXint)internalformat, pTexture->getWidth(), pTexture->getHeight(), 0, (fgGFXenum)dataformat, GL_UNSIGNED_BYTE, pTexture->getRawData());
    } else if(textureType == FG_TEXTURE_CUBE) {
        target = GL_TEXTURE_CUBE_MAP;
        for(int i = 0; i < FG_NUM_TEXTURE_CUBE_MAPS; i++) {
            glTexImage2D(cubeTargets[i], 0,
                         (fgGFXint)internalformat,
                         pTexture->getWidth(),
                         pTexture->getHeight(),
                         0,
                         (fgGFXenum)dataformat,
                         GL_UNSIGNED_BYTE,
                         pTexture->getCubeData((fgTextureCubeMapID)i));
        }
    }
    if(fgGLError("glTexImage2D")) {
        status = FG_FALSE;
        failedFuncs.append("glTexImage2D, ");
    }
    ((resource::CResourceManager *)m_pResourceMgr)->unlockResource(pTexture);
    if(!status) {
        FG_LOG_ERROR("GFX: Errors on texture '%s' upload. Failing functions: %s", pTexture->getNameStr(), failedFuncs.substr(0, failedFuncs.length() - 2).c_str());
        failedFuncs.clear();
    } else {
        FG_LOG_DEBUG("GFX: Texture [%s] uploaded successfully: gfxID=%d;", pTexture->getNameStr(), pTexture->getRefGfxID().id);
        FG_LOG_DEBUG("GFX: Texture [%s] dimensions: %dx%d", pTexture->getNameStr(), pTexture->getWidth(), pTexture->getHeight());
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    FG_HardwareState->deviceYield();
    return status;
}
