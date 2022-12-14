/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgTextureManager.h"
#include "fgTextureResource.h"

#include "Hardware/fgQualityManager.h"
#include "Resource/fgResourceManager.h"
#include "Event/fgEventDefinitions.h"
#include "Event/fgEventManager.h"

using namespace fg;

//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

gfx::CTextureManager::~CTextureManager() {
    destroy();
}
//------------------------------------------------------------------------------

void gfx::CTextureManager::registerResourceCallbacks(void) {
    if(!m_pEventMgr)
        return;

    if(!m_resourceCreatedCallback)
        m_resourceCreatedCallback = new event::CMethodCallback<CTextureManager>(this, &gfx::CTextureManager::resourceCreatedHandler);

    static_cast<event::CEventManager *>(m_pEventMgr)->addCallback(event::RESOURCE_CREATED, m_resourceCreatedCallback);
    //m_pEventMgr->addEventCallback(event::TOUCH_RELEASED, m_gameTouchCallback);
    //m_pEventMgr->addEventCallback(event::TOUCH_MOTION, m_gameTouchCallback);
    //m_pEventMgr->addEventCallback(event::TOUCH_TAP_FINISHED, m_gameTouchCallback);

    /*if(!m_gameMouseCallback)
        m_gameMouseCallback = new fgClassCallback<fgGameMain>(this, &fgGameMain::gameMouseHandler);

    m_pEventMgr->addEventCallback(event::MOUSE_PRESSED, m_gameMouseCallback);
    m_pEventMgr->addEventCallback(event::MOUSE_RELEASED, m_gameMouseCallback);
    m_pEventMgr->addEventCallback(event::MOUSE_MOTION, m_gameMouseCallback);*/
}
//------------------------------------------------------------------------------

void gfx::CTextureManager::unregisterResourceCallbacks(void) {
    if(!m_pEventMgr)
        return;

    static_cast<event::CEventManager *>(m_pEventMgr)->removeCallback(event::RESOURCE_CREATED, m_resourceCreatedCallback);

    //m_pEventMgr->removeEventCallback(event::MOUSE_PRESSED, m_gameMouseCallback);
    //m_pEventMgr->removeEventCallback(event::MOUSE_RELEASED, m_gameMouseCallback);
    //m_pEventMgr->removeEventCallback(event::MOUSE_MOTION, m_gameMouseCallback);

}
//------------------------------------------------------------------------------

void gfx::CTextureManager::clear(void) {
    m_managerType = FG_MANAGER_TEXTURE;
}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

fgBool gfx::CTextureManager::initialize(void) {
    if(!m_pResourceMgr)
        return FG_FALSE;
    m_init = FG_TRUE;
    m_managerType = FG_MANAGER_TEXTURE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

fg::base::CManager* gfx::CTextureManager::getResourceManager(void) const {
    return m_pResourceMgr;
}
//------------------------------------------------------------------------------

gfx::STextureID& gfx::CTextureManager::getRefGfxID(const resource::ResourceHandle& texHandle) {
    if(!m_pResourceMgr)
        return m_emptyGfxID;
    gfx::CTextureResource *pTexture = (CTextureResource *)static_cast<resource::CResourceManager *>(m_pResourceMgr)->get(texHandle);
    if(!pTexture) {
        m_emptyGfxID.reset();
        return m_emptyGfxID;
    }
    return pTexture->getRefGfxID();
}
//------------------------------------------------------------------------------

gfx::STextureID& gfx::CTextureManager::getRefGfxID(const std::string& nameTag) {
    if(!m_pResourceMgr || nameTag.empty())
        return m_emptyGfxID;
    CTextureResource *pTexture = (CTextureResource *)static_cast<resource::CResourceManager *>(m_pResourceMgr)->get(nameTag);
    if(!pTexture) {
        m_emptyGfxID.reset();
        return m_emptyGfxID;
    }
    return pTexture->getRefGfxID();
}
//------------------------------------------------------------------------------

gfx::STextureID& gfx::CTextureManager::getRefGfxID(const char *nameTag) {
    if(!m_pResourceMgr || !nameTag)
        return m_emptyGfxID;
    CTextureResource *pTexture = (CTextureResource *)static_cast<resource::CResourceManager *>(m_pResourceMgr)->get(nameTag);
    if(!pTexture) {
        m_emptyGfxID.reset();
        return m_emptyGfxID;
    }
    return pTexture->getRefGfxID();
}
//------------------------------------------------------------------------------

fgBool gfx::CTextureManager::resourceCreatedHandler(event::CArgumentList * argv) {
    if(!argv)
        return FG_FALSE;
    event::SEvent *event_struct = (event::SEvent *)argv->getValueByID(0);
    if(!event_struct)
        return FG_FALSE;
    event::EventType type = event_struct->code;
    if(type != event::RESOURCE_CREATED)
        return FG_FALSE;
    event::SResource *resourceEvent = (event::SResource *)event_struct;
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
    return CTextureManager::uploadToVRAM(pTexture, FG_TRUE); // force flag
}
//------------------------------------------------------------------------------

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
            FG_LOG_ERROR("GFX: Loop in texture manager, resource is %p\n", resource);
            return FG_FALSE;
        }
        resource::ResourceType resType = resource->getResourceType();
        Quality quality = resource->getQuality();
        if((resType == resource::TEXTURE || resType == resource::FONT) &&
           (FG_TRUE/* #FIXME quality == FG_QualityManager->getQuality()*/ ||
            quality == Quality::UNIVERSAL)) {
            fgBool force = FG_FALSE;
            CTextureResource *textureResource = (CTextureResource *)resource;
            if(reupload && textureResource->isInVRAM()) {
                force = FG_TRUE;
            }
            gfx::CTextureManager::uploadToVRAM(textureResource, force);
        }
        ((resource::CResourceManager *)m_pResourceMgr)->goToNext(searchTypes, 3);
    }
    m_allInVRAM = FG_TRUE;
    return result;
}
//------------------------------------------------------------------------------

fgBool gfx::CTextureManager::uploadToVRAM(CTexture *texture, fgBool force) {
    if(!((resource::CResourceManager *)m_pResourceMgr) || !texture)
        return FG_FALSE;
    // DEVICE YIELD
    resource::ResourceType resType = texture->getResourceType();
    Quality quality = texture->getQuality();
    if(!((resType == resource::TEXTURE || resType == resource::FONT))) {
        FG_LOG_DEBUG("GFX: Resource '%s' is not texture?", texture->getNameStr());
        return FG_FALSE;
    }
    fgBool result = FG_TRUE;
    STextureID& texGfxID = texture->getRefGfxID();
    if(gfx::context::isTexture(texGfxID) == FG_GFX_TRUE && !force) {
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
                if(gfx::context::isTexture(texGfxID) == FG_GFX_TRUE)
                    texture->setIsInVRAM(FG_TRUE);
            }
        }
    } // else: if resource is not locked then most likely it is not needed
    return result;
}
//------------------------------------------------------------------------------

fgBool gfx::CTextureManager::uploadToVRAM(const std::string& nameTag, fgBool force) {
    if(!m_pResourceMgr)
        return FG_FALSE;

    return uploadToVRAM(nameTag.c_str(), force);
}
//------------------------------------------------------------------------------

fgBool gfx::CTextureManager::uploadToVRAM(const char *nameTag, fgBool force) {
    if(!m_pResourceMgr)
        return FG_FALSE;
    // DEVICE YIELD
    resource::CResource *resource = ((resource::CResourceManager *)m_pResourceMgr)->get(nameTag);
    if(!resource)
        return FG_FALSE;
    if(resource->getResourceType() != resource::TEXTURE || resource->getResourceType() != resource::FONT)
        return FG_FALSE;
    gfx::CTexture *texture = (gfx::CTexture *)resource;
    return uploadToVRAM(texture, force);
}
//------------------------------------------------------------------------------

void gfx::CTextureManager::allReleaseNonGFX(void) {
    if(!m_pResourceMgr)
        return;
    resource::ResourceType searchTypes[] = {resource::TEXTURE,
                                            resource::FONT,
                                            resource::INVALID};
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
            if(gfx::context::isTexture(textureResource->getRefGfxID()) == GL_TRUE)
                textureResource->setIsInVRAM(FG_TRUE);
        }
        ((resource::CResourceManager *)m_pResourceMgr)->goToNext(searchTypes, 3);
    }
    ((resource::CResourceManager *)m_pResourceMgr)->refreshMemory();
}
//------------------------------------------------------------------------------

void gfx::CTextureManager::allReleaseGFX(void) {
    if(!m_pResourceMgr)
        return;
    resource::ResourceType searchTypes[] = {resource::TEXTURE,
                                            resource::FONT,
                                            resource::INVALID};
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
            CTextureResource* textureResource = (CTextureResource *)resource;
            STextureID& texGfxID = textureResource->getRefGfxID();
            gfx::context::deleteTexture(texGfxID);
            //textureResource->releaseNonGFX();
        }
        ((resource::CResourceManager *)m_pResourceMgr)->goToNext(searchTypes, 3);
    }
    ((resource::CResourceManager *)m_pResourceMgr)->refreshMemory();
}
//------------------------------------------------------------------------------

void gfx::CTextureManager::releaseGFX(CTextureResource * texture) {
    if(!texture)
        return;
    resource::ResourceType resType = texture->getResourceType();
    if(resType == resource::TEXTURE || resType == resource::FONT) {
        STextureID& texGfxID = texture->getRefGfxID();
        gfx::context::deleteTexture(texGfxID);
    }
}
//------------------------------------------------------------------------------

fgBool gfx::CTextureManager::makeTexture(CTextureResource * pTexture) {
    if(!m_pResourceMgr)
        return FG_FALSE;
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
    STextureID& texGfxID = pTexture->getRefGfxID();
    // Generate texture object ONLY IF NEEDED
    if(FG_GFX_FALSE == context::isTexture(texGfxID)) {
        context::genTexture(pTexture->getPtrGfxID());
    }
    fgBool status = FG_TRUE;
    std::string failedFuncs;
    context::bindTexture(texGfxID);
    if(GLCheckError("glBindTexture")) {
        status = FG_FALSE;
        failedFuncs.append("glBindTexture, ");
    }

    fgGFXuint target = 0;
    fgGFXuint cubeTargets[] = {GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                               GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                               GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z};
    texture::Type textureType = pTexture->getTextureType();
    if(textureType == texture::PLAIN || textureType == texture::FONT) {
        target = GL_TEXTURE_2D;
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, (fgGFXint)GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, (fgGFXint)GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_WRAP_S, (fgGFXint)GL_MIRRORED_REPEAT);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, (fgGFXint)GL_MIRRORED_REPEAT);
    } else if(textureType == texture::CUBE) {
        target = GL_TEXTURE_CUBE_MAP;
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, (fgGFXint)GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, (fgGFXint)GL_LINEAR);
        glTexParameteri(target, GL_TEXTURE_WRAP_S, (fgGFXint)GL_MIRRORED_REPEAT);
        glTexParameteri(target, GL_TEXTURE_WRAP_T, (fgGFXint)GL_MIRRORED_REPEAT);
        //glTexParameteri(target, GL_TEXTURE_WRAP_R, (fgGFXint)GL_MIRRORED_REPEAT); // _R is not in ES 2.0 :( #FIXME
    }

    if(GLCheckError("glTexParameteri")) {
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
    if(textureType == texture::PLAIN || textureType == texture::FONT) {
        glTexImage2D(target,
                     0,
                     (fgGFXint)internalformat,
                     pTexture->getWidth(),
                     pTexture->getHeight(),
                     0,
                     (fgGFXenum)dataformat,
                     GL_UNSIGNED_BYTE,
                     pTexture->getRawData());
    } else if(textureType == texture::CUBE) {
        target = GL_TEXTURE_CUBE_MAP;
        for(int i = 0; i < texture::NUM_CUBE_MAPS; i++) {
            glTexImage2D(cubeTargets[i],
                         0,
                         (fgGFXint)internalformat,
                         pTexture->getWidth(),
                         pTexture->getHeight(),
                         0,
                         (fgGFXenum)dataformat,
                         GL_UNSIGNED_BYTE,
                         pTexture->getCubeData((texture::CubeMapID)i));
        }
    }
    if(GLCheckError("glTexImage2D")) {
        status = FG_FALSE;
        failedFuncs.append("glTexImage2D, ");
    }
    ((resource::CResourceManager *)m_pResourceMgr)->unlockResource(pTexture);
    if(!status) {
        FG_LOG_ERROR("GFX: Errors on texture '%s' upload. Failing functions: %s", pTexture->getNameStr(), failedFuncs.substr(0, failedFuncs.length() - 2).c_str());
        failedFuncs.clear();
    } else {
        FG_LOG_DEBUG("GFX: Texture [%s] uploaded successfully: gfxID=%d; size=%dx%d;",
                     pTexture->getNameStr(),
                     pTexture->getRefGfxID().id,
                     pTexture->getWidth(),
                     pTexture->getHeight());
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    // DEVICE YIELD
    return status;
}
//------------------------------------------------------------------------------
