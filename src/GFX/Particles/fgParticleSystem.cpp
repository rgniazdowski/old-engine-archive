/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/*
 * fgParticleSystem.cpp
 *
 *  Created on: 17-06-2012
 *      Author: Vigilant
 */

#include "fgParticleSystem.h"

#include "Resource/fgResourceManager.h"

#include "GFX/Textures/fgTextureResource.h"
#include "GFX/Shaders/fgGfxShaderManager.h"
#include "GFX/Scene/fgGfxSceneEvent.h"
#include "GFX/Scene/fgGfxSceneCallback.h"
#include "GFX/Scene/fgGfxSceneManager.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::CParticleSystem::CParticleSystem(fg::base::CManager *pResourceMgr,
                                      fg::base::CManager *pSceneMgr) :
m_pResourceMgr(NULL),
m_pSceneMgr(NULL),
m_emitters() {
    setResourceManager(pResourceMgr);
    setSceneManager(pSceneMgr);
}
//------------------------------------------------------------------------------

gfx::CParticleSystem::~CParticleSystem() {
    gfx::CParticleSystem::destroy();
}
//------------------------------------------------------------------------------

void gfx::CParticleSystem::clear() {
    // ?
}
//------------------------------------------------------------------------------

fgBool gfx::CParticleSystem::managedObjectDestructorCallback(void *systemData, void *userData) {
    if(!systemData || !userData)
        return FG_FALSE;

    // systemData is pointer to the object being destroyed
    // userData - is the pointer to the particle system instance, 
    // it was passed to the registering function

    CParticleEmitter *pEmitter = (CParticleEmitter *)systemData;
    CParticleSystem *pSystem = (CParticleSystem *)userData;

    if(!pEmitter->isRegistered(&CParticleSystem::managedObjectDestructorCallback)) {
        // If this function is not registered - this is not a valid call to the
        // destructor callback
        return FG_FALSE;
    }

    int index = pSystem->m_emitters.find(pEmitter);
    unsigned int n = pSystem->m_emitters.size();
    if(index != -1) {
        pSystem->m_emitters[index] = NULL;
    }

    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CParticleSystem::sceneClearedCallback(CSceneNode* pNodeA, CSceneNode* pNodeB) {
    // The scene was cleared - destroy all emitters
    if(m_init) {
        this->destroy(); // #FIXME
        m_init = FG_TRUE;
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void gfx::CParticleSystem::setSceneManager(fg::base::CManager* pSceneMgr) {
    if(m_pSceneMgr != pSceneMgr && pSceneMgr) {
        if(pSceneMgr->getManagerType() == FG_MANAGER_SCENE) {
            //static_cast<CSceneManager *>(pSceneMgr)->getEventManager()->
            CSceneCallback *pCallback = new CSceneMethodCallback<gfx::CParticleSystem>(this, &CParticleSystem::sceneClearedCallback);
            //pCallback->setFunction(&CParticleSystem());
            static_cast<CSceneManager *>(pSceneMgr)->addCallback(event::SCENE_CLEARED, pCallback);
        }
    }
    m_pSceneMgr = pSceneMgr;
}
//------------------------------------------------------------------------------

fgBool gfx::CParticleSystem::isEmitterInTheArray(CParticleEmitter *pEmitter) {
    if(!pEmitter || m_emitters.empty()) {
        return FG_FALSE;
    }
    if(m_emitters.find(pEmitter) != -1) {
        return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool gfx::CParticleSystem::isEmitterInTheArray(const std::string& emitterNameTag) {
    if(emitterNameTag.empty() || m_emitters.empty()) {
        return FG_FALSE;
    }
    int n = m_emitters.size();
    for(int i = 0; i < n; i++) {
        if(!m_emitters[i])
            continue;
        if(m_emitters[i]->getName().compare(emitterNameTag) == 0) {
            return FG_TRUE;
        }
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool gfx::CParticleSystem::isEmitterInTheArray(const char *emitterNameTag) {
    if(!emitterNameTag || m_emitters.empty()) {
        return FG_FALSE;
    }
    int n = m_emitters.size();
    for(int i = 0; i < n; i++) {
        if(!m_emitters[i])
            continue;
        if(m_emitters[i]->getName().compare(emitterNameTag) == 0) {
            return FG_TRUE;
        }
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool gfx::CParticleSystem::isEmitterInTheScene(const CParticleEmitter *pEmitter) {
    if(!pEmitter || !m_pSceneMgr)
        return FG_FALSE;

    return static_cast<CSceneManager *>(m_pSceneMgr)->isManaged(pEmitter);
}
//------------------------------------------------------------------------------

fgBool gfx::CParticleSystem::isEmitterInTheScene(const std::string& emitterNameTag) {
    if(emitterNameTag.empty() || !m_pSceneMgr)
        return FG_FALSE;

    return static_cast<CSceneManager *>(m_pSceneMgr)->isManaged(emitterNameTag);
}
//------------------------------------------------------------------------------

fgBool gfx::CParticleSystem::isEmitterInTheScene(const char *emitterNameTag) {
    if(!emitterNameTag || !m_pSceneMgr)
        return FG_FALSE;

    return static_cast<CSceneManager *>(m_pSceneMgr)->isManaged(emitterNameTag);
}
//------------------------------------------------------------------------------

gfx::CParticleEmitter *gfx::CParticleSystem::getParticleEmitter(const std::string& emitterNameTag) {
    if(emitterNameTag.empty() || !m_pSceneMgr)
        return NULL;

    CParticleEmitter *pEmitter = (CParticleEmitter *)static_cast<CSceneManager *>(m_pSceneMgr)->get(emitterNameTag);
    if(pEmitter) {
        if(m_emitters.find(pEmitter) != -1)
            return pEmitter;
    }
    return NULL;
}
//------------------------------------------------------------------------------

gfx::CParticleEmitter *gfx::CParticleSystem::getParticleEmitter(const char *emitterNameTag) {
    if(!emitterNameTag || !m_pSceneMgr)
        return NULL;

    CParticleEmitter *pEmitter = (CParticleEmitter *)static_cast<CSceneManager *>(m_pSceneMgr)->get(emitterNameTag);
    if(pEmitter) {
        if(m_emitters.find(pEmitter) != -1)
            return pEmitter;
    }
    return NULL;
}
//------------------------------------------------------------------------------

fgBool gfx::CParticleSystem::destroy(void) {
    m_init = FG_FALSE;
    int n = m_emitters.size();
    for(int i = 0; i < n; i++) {
        if(!m_emitters[i]) {
            continue;
        }
        if(!m_emitters[i]->isManaged()) {
            static_cast<CSceneManager *>(m_pSceneMgr)->remove(static_cast<CSceneNode *>(m_emitters[i]));
            delete m_emitters[i];
            m_emitters[i] = NULL;
        }
    }
    m_emitters.clear_optimised();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CParticleSystem::initialize(void) {
    if(m_init)
        return FG_TRUE;
    if(!m_pResourceMgr || !m_pSceneMgr) {
        // #ERROR
        return FG_FALSE;
    }
    m_init = FG_TRUE;
    m_managerType = FG_MANAGER_PARTICLE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CParticleSystem::insert(CParticleEffect* pEffect, const std::string& nameTag) {
    if(nameTag.empty() || !pEffect)
        return FG_FALSE;
    if(!m_pResourceMgr)
        return FG_FALSE;
    pEffect->setName(nameTag);
    if(static_cast<resource::CResourceManager *>(m_pResourceMgr)->insert(pEffect)) {
        pEffect->setManaged(FG_TRUE);
        return FG_TRUE;
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool gfx::CParticleSystem::insertParticleEffect(CParticleEffect *pEffect) {
    if(!pEffect)
        return FG_FALSE;
    return insert(pEffect, pEffect->getName());
}
//------------------------------------------------------------------------------

gfx::CParticleEffect* gfx::CParticleSystem::request(const std::string& info) {
    if(!m_pResourceMgr || info.empty())
        return NULL;
    return (CParticleEffect *)(static_cast<resource::CResourceManager *>(m_pResourceMgr)->request(info));
}
//------------------------------------------------------------------------------

gfx::CParticleEffect* gfx::CParticleSystem::request(const char *info) {
    if(!m_pResourceMgr || !info)
        return NULL;
    if(strlen(info) < 1)
        return NULL;
    return (CParticleEffect *)(static_cast<resource::CResourceManager *>(m_pResourceMgr)->request(info));
}
//------------------------------------------------------------------------------

gfx::CParticleEmitter* gfx::CParticleSystem::insertParticleEmitter(const std::string& particleEffectNameTag,
                                                                   const std::string& particleEmitterNameTag,
                                                                   const Vector3f& emitterOrigin) {
    if(!m_pSceneMgr || !m_pResourceMgr) {
        FG_LOG_ERROR("GFX: Unable to add ParticleEmitter - Particle System is not set up");
        return NULL;
    }
    resource::CResourceManager *pResourceMgr = static_cast<resource::CResourceManager *>(m_pResourceMgr);
    CSceneManager *pSceneMgr = static_cast<CSceneManager*>(m_pSceneMgr);
    CShaderManager *pShaderMgr = static_cast<CShaderManager*>(pSceneMgr->getShaderManager());

    if(particleEffectNameTag.empty() || particleEmitterNameTag.empty()) {
        FG_LOG_ERROR("GFX: Unable to add ParticleEmitter - name tags are empty");
        return NULL;
    }
    if(isEmitterInTheScene(particleEmitterNameTag)) {
        FG_LOG_ERROR("GFX: Particle emitter '%s' is already in the Scene Manager", particleEmitterNameTag.c_str());
        return NULL;
    }
    if(isEmitterInTheArray(particleEmitterNameTag)) {
        FG_LOG_ERROR("GFX: Particle emitter '%s' is already in the Scene Manager", particleEmitterNameTag.c_str());
        return NULL;
    }
    CParticleEffect *pEffect = (CParticleEffect *)(pResourceMgr->request(particleEffectNameTag));
    if(!pEffect) {
        FG_LOG_ERROR("GFX: Unable to find particle effect: '%s'", particleEffectNameTag.c_str());
        return NULL;
    }
    if(pEffect->isDisposed()) {
        pEffect->create();
    }
    CTextureResource *pTexture = (CTextureResource *)(pResourceMgr->request(pEffect->getTextureName()));
    if(pTexture) {
        pEffect->setTextureGfxID(pTexture->getRefGfxID());
    }
    if(pShaderMgr && !pEffect->getShaderProgram()) {
        pEffect->setShaderProgram(pShaderMgr->get(pEffect->getShaderName()));
    }
    CParticleEmitter *pEmitter = new CParticleEmitter(pEffect);
    pEmitter->setName(particleEmitterNameTag);
    //pEmitter->setOrigin()

    pSceneMgr->addNode(pEmitter->getRefHandle(),
                       pEmitter,
                       (gfx::CSceneNode *)NULL);


    CCamera *pCamera = (CCamera *)pSceneMgr->getCamera();
    pEmitter->setCamera(pCamera); // Set pointer for the camera
    // Set particle emitter as not managed
    // This means that particle emitter object must be freed
    // by the particle manager // #FIXME - this needs be more obvious
    pEmitter->setManaged(FG_FALSE);
    m_emitters.push_back(pEmitter);
    pEmitter->registerOnDestruct(&CParticleSystem::managedObjectDestructorCallback, (void *)this);
    // Should now set managed to false
    // Store it in some array ?
    // Refresh?
    return pEmitter;
}
//------------------------------------------------------------------------------

gfx::CParticleEmitter* gfx::CParticleSystem::insertParticleEmitter(const char *particleEffectNameTag,
                                                                   const char *particleEmitterNameTag,
                                                                   const Vector3f& emitterOrigin) {

    if(!particleEffectNameTag || !particleEmitterNameTag) {
        FG_LOG_ERROR("GFX: Unable to add ParticleEmitter - name tags are empty");
        return NULL;
    }
    if(!strlen(particleEffectNameTag) || !strlen(particleEmitterNameTag)) {
        FG_LOG_ERROR("GFX: Unable to add ParticleEmitter - name tags are empty");
        return NULL;
    }

    return insertParticleEmitter(std::string(particleEffectNameTag),
                                 std::string(particleEmitterNameTag),
                                 emitterOrigin);
}
//------------------------------------------------------------------------------

fgBool gfx::CParticleSystem::insertParticleEmitter(const CParticleEmitter* pParticleEmitter,
                                                   const std::string& particleEffectNameTag) {
    if(!pParticleEmitter || !m_pSceneMgr) {
        return FG_FALSE;
    }

    return FG_TRUE;
}
//------------------------------------------------------------------------------

void gfx::CParticleSystem::calculate(void) {
    if(!m_pSceneMgr)
        return;

    int n = m_emitters.size();
    for(int i = 0; i < n; i++) {
        CParticleEmitter *pEmitter = m_emitters[i];
        if(!pEmitter) {
            continue;
        }
        CParticleEffect *pEffect = pEmitter->getParticleEffect();
        if(!pEffect) {
            continue;
        }
        // Need also to update vertex data in every draw call
        gfx::CDrawCall *pDrawCall = pEmitter->getDrawCall(); //static_cast<fgGfxSceneManager *>(m_pSceneMgr)->getDrawCall(static_cast<fgGfxSceneNode *>(pEmitter));
        CVertexData *pVertexData = NULL;
        if(pDrawCall) {
            // #FIXME
            CTextureResource *pTexture = (CTextureResource *)(static_cast<resource::CResourceManager *>(m_pResourceMgr)->request(pEffect->getTextureName()));
            if(pTexture) {
                pEffect->setTextureGfxID(pTexture->getRefGfxID());
            }
            pDrawCall->setTexture(pEffect->getTextureGfxID());
            // Just in case?
            pDrawCall->setPrimitiveMode(PrimitiveMode::TRIANGLES);
            pVertexData = pDrawCall->getVertexData();
            if(pVertexData) {
                // #FIXME
                // multiply by 6 - two triangles per particle
                pVertexData->reserve(pEmitter->getMaxCount()*6);
                //pVertexData->
            }
        }
        pEmitter->calculate();
    }
}
//------------------------------------------------------------------------------

void gfx::CParticleSystem::addParticles(const std::string& emitterNameTag,
                                        unsigned int numParticles,
                                        const Vector3f& origin) {
    CParticleEmitter *pEmitter = (CParticleEmitter *)static_cast<CSceneManager *>(m_pSceneMgr)->get(emitterNameTag);
    if(pEmitter) {
        pEmitter->addParticles(numParticles, origin);
    }
}
//------------------------------------------------------------------------------

void gfx::CParticleSystem::addParticles(const char* emitterNameTag,
                                        unsigned int numParticles,
                                        const Vector3f& origin) {
    CParticleEmitter *pEmitter = (CParticleEmitter *)static_cast<CSceneManager *>(m_pSceneMgr)->get(emitterNameTag);
    if(pEmitter) {
        pEmitter->addParticles(numParticles, origin);
    }
}
//------------------------------------------------------------------------------

void gfx::CParticleSystem::addParticles(const std::string& emitterNameTag,
                                        unsigned int numParticles,
                                        float x, float y, float z) {
    CParticleEmitter *pEmitter = (CParticleEmitter *)static_cast<CSceneManager *>(m_pSceneMgr)->get(emitterNameTag);
    if(pEmitter) {
        pEmitter->addParticles(numParticles, Vector3f(x, y, z));
    }
}
//------------------------------------------------------------------------------

void gfx::CParticleSystem::addParticles(const char* emitterNameTag,
                                        unsigned int numParticles,
                                        float x, float y, float z) {
    CParticleEmitter *pEmitter = (CParticleEmitter *)static_cast<CSceneManager *>(m_pSceneMgr)->get(emitterNameTag);
    if(pEmitter) {
        pEmitter->addParticles(numParticles, Vector3f(x, y, z));
    }
}
//------------------------------------------------------------------------------
