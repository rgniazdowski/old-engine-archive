/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/*
 * fgParticleSystem.cpp
 *
 *  Created on: 17-06-2012
 *      Author: Vigilant
 */

#include "fgParticleSystem.h"
#include "Resource/fgResourceManager.h"
#include "GFX/fgGFXSceneManager.h"
#include "GFX/Textures/fgTextureResource.h"

/**
 * 
 */
fgParticleSystem::fgParticleSystem(fgManagerBase *pResourceMgr, fgManagerBase *pSceneMgr) {
    setResourceManager(pResourceMgr);
    setSceneManager(pSceneMgr);
}

/**
 * 
 */
fgParticleSystem::~fgParticleSystem() {
    fgParticleSystem::destroy();
}

/**
 * 
 */
void fgParticleSystem::clear() {
    // ?
}

/**
 * 
 * @param pEmitter
 * @return 
 */
fgBool fgParticleSystem::isEmitterInTheArray(fgParticleEmitter *pEmitter) {
    if(!pEmitter || m_emitters.empty()) {
        return FG_FALSE;
    }
    if(m_emitters.find(pEmitter) != -1) {
        return FG_TRUE;
    }
    return FG_FALSE;
}

/**
 * 
 * @param emitterNameTag
 * @return 
 */
fgBool fgParticleSystem::isEmitterInTheArray(const std::string& emitterNameTag) {
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

/**
 * 
 * @param emitterNameTag
 * @return 
 */
fgBool fgParticleSystem::isEmitterInTheArray(const char *emitterNameTag) {
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

/**
 * 
 * @param pEmitter
 * @return 
 */
fgBool fgParticleSystem::isEmitterInTheScene(const fgParticleEmitter *pEmitter) {
    if(!pEmitter || !m_pSceneMgr)
        return FG_FALSE;

    //if(m_emitters.find(pEmitter))

    return static_cast<fgGfxSceneManager *>(m_pSceneMgr)->isManaged(pEmitter);
}

/**
 * 
 * @param emitterNameTag
 * @return 
 */
fgBool fgParticleSystem::isEmitterInTheScene(const std::string& emitterNameTag) {
    if(emitterNameTag.empty() || !m_pSceneMgr)
        return FG_FALSE;

    return static_cast<fgGfxSceneManager *>(m_pSceneMgr)->isManaged(emitterNameTag);
}

/**
 * 
 * @param emitterNameTag
 * @return 
 */
fgBool fgParticleSystem::isEmitterInTheScene(const char *emitterNameTag) {
    if(!emitterNameTag || !m_pSceneMgr)
        return FG_FALSE;

    return static_cast<fgGfxSceneManager *>(m_pSceneMgr)->isManaged(emitterNameTag);
}

/**
 * 
 * @param emitterNameTag
 * @return 
 */
fgParticleEmitter *fgParticleSystem::getParticleEmitter(const std::string& emitterNameTag) {
    if(emitterNameTag.empty() || !m_pSceneMgr)
        return NULL;

    fgParticleEmitter *pEmitter = (fgParticleEmitter *)static_cast<fgGfxSceneManager *>(m_pSceneMgr)->get(emitterNameTag);
    if(pEmitter) {
        if(m_emitters.find(pEmitter) != -1)
            return pEmitter;
    }
    return NULL;
}

/**
 * 
 * @param emitterNameTag
 * @return 
 */
fgParticleEmitter *fgParticleSystem::getParticleEmitter(const char *emitterNameTag) {
    if(!emitterNameTag || !m_pSceneMgr)
        return NULL;

    fgParticleEmitter *pEmitter = (fgParticleEmitter *)static_cast<fgGfxSceneManager *>(m_pSceneMgr)->get(emitterNameTag);
    if(pEmitter) {
        if(m_emitters.find(pEmitter) != -1)
            return pEmitter;
    }
    return NULL;
}

/**
 * 
 * @return 
 */
fgBool fgParticleSystem::destroy(void) {
    m_init = FG_FALSE;
    int n = m_emitters.size();
    for(int i = 0; i < n; i++) {
        if(!m_emitters[i]) {
            continue;
        }
        if(!m_emitters[i]->isManaged()) {
            static_cast<fgGfxSceneManager *>(m_pSceneMgr)->remove(static_cast<fgGfxSceneNode *>(m_emitters[i]));
            delete m_emitters[i];
            m_emitters[i] = NULL;
        }
    }
    m_emitters.clear_optimised();
    //m_emitters.resize(0);
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool fgParticleSystem::initialize(void) {
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

/**
 * 
 * @param dhUniqueID
 * @param pData
 * @param nameTag
 * @return 
 */
fgBool fgParticleSystem::insert(fgParticleEffect* pEffect, const std::string& nameTag) {
    if(nameTag.empty() || !pEffect)
        return FG_FALSE;
    if(!m_pResourceMgr)
        return FG_FALSE;
    if(static_cast<fgResourceManager *>(m_pResourceMgr)->insert(pEffect, nameTag)) {
        pEffect->setManaged(FG_TRUE);
        return FG_TRUE;
    }
    return FG_FALSE;
}

/**
 * 
 * @param shUniqueID
 * @param pStyle
 * @return 
 */
fgBool fgParticleSystem::insertParticleEffect(fgParticleEffect *pEffect) {
    if(!pEffect)
        return FG_FALSE;
    return insert(pEffect, pEffect->getName());
}

/**
 * 
 * @param info
 * @return 
 */
fgParticleEffect* fgParticleSystem::request(const std::string& info) {
    if(!m_pResourceMgr || info.empty())
        return NULL;
    return (fgParticleEffect *)(static_cast<fgResourceManager *>(m_pResourceMgr)->request(info));
}

/**
 * 
 * @param info
 * @return 
 */
fgParticleEffect* fgParticleSystem::request(const char *info) {
    if(!m_pResourceMgr || !info)
        return NULL;
    if(strlen(info) < 1)
        return NULL;
    return (fgParticleEffect *)(static_cast<fgResourceManager *>(m_pResourceMgr)->request(info));
}

/**
 * 
 * @param particleEffectNameTag
 * @param particleEmitterNameTag
 * @param emitterOrigin
 * @return 
 */
fgParticleEmitter* fgParticleSystem::insertParticleEmitter(const std::string& particleEffectNameTag,
                                                           const std::string& particleEmitterNameTag,
                                                           const fgVector3f& emitterOrigin) {
    if(!m_pSceneMgr || !m_pResourceMgr) {
        FG_LOG::PrintError("GFX: Unable to add ParticleEmitter - Particle System is not set up");
        return NULL;
    }
    if(particleEffectNameTag.empty() || particleEmitterNameTag.empty()) {
        FG_LOG::PrintError("GFX: Unable to add ParticleEmitter - name tags are empty");
        return NULL;
    }
    if(isEmitterInTheScene(particleEmitterNameTag)) {
        FG_LOG::PrintError("GFX: Particle emitter '%s' is already in the Scene Manager", particleEmitterNameTag.c_str());
        return NULL;
    }
    if(isEmitterInTheArray(particleEmitterNameTag)) {
        FG_LOG::PrintError("GFX: Particle emitter '%s' is already in the Scene Manager", particleEmitterNameTag.c_str());
        return NULL;
    }
    fgParticleEffect *pEffect = (fgParticleEffect *)(static_cast<fgResourceManager *>(m_pResourceMgr)->request(particleEffectNameTag));
    if(!pEffect) {
        FG_LOG::PrintError("GFX: Unable to find particle effect: '%s'", particleEffectNameTag.c_str());
        return NULL;
    }
    if(pEffect->isDisposed())
        pEffect->create();
    fgTextureResource *pTexture = (fgTextureResource *)(static_cast<fgResourceManager *>(m_pResourceMgr)->request(pEffect->getTextureName()));
    if(pTexture) {
        pEffect->setTextureGfxID(pTexture->getRefGfxID());
    }
    fgParticleEmitter *pEmitter = new fgParticleEmitter(pEffect);
    pEmitter->setName(particleEmitterNameTag);
    //pEmitter->setOrigin()

    static_cast<fgGfxSceneManager *>(m_pSceneMgr)->addNode(pEmitter->getRefHandle(),
                                                           pEmitter,
                                                           (fgGfxSceneNode *)NULL);

    // Set particle emitter as not managed
    // This means that particle emitter object must be freed
    // by the particle manager
    pEmitter->setManaged(FG_FALSE);
    m_emitters.push_back(pEmitter);
    // Should now set managed to false
    // Store it in some array ?
    // Refresh?

    return pEmitter;
}

/**
 * 
 * @param particleEffectNameTag
 * @param particleEmitterNameTag
 * @param emitterOrigin
 * @return 
 */
fgParticleEmitter* fgParticleSystem::insertParticleEmitter(const char *particleEffectNameTag,
                                                           const char *particleEmitterNameTag,
                                                           const fgVector3f& emitterOrigin) {

    if(!particleEffectNameTag || !particleEmitterNameTag) {
        FG_LOG::PrintError("GFX: Unable to add ParticleEmitter - name tags are empty");
        return NULL;
    }
    if(!strlen(particleEffectNameTag) || !strlen(particleEmitterNameTag)) {
        FG_LOG::PrintError("GFX: Unable to add ParticleEmitter - name tags are empty");
        return NULL;
    }

    return insertParticleEmitter(std::string(particleEffectNameTag),
                                 std::string(particleEmitterNameTag),
                                 emitterOrigin);
}

/**
 * 
 * @param pParticleEmitter
 * @param particleEffectNameTag
 * @return 
 */
fgBool fgParticleSystem::insertParticleEmitter(const fgParticleEmitter* pParticleEmitter,
                                               const std::string& particleEffectNameTag) {
    if(!pParticleEmitter || !m_pSceneMgr) {
        return FG_FALSE;
    }

    return FG_TRUE;
}

/**
 * 
 */
void fgParticleSystem::calculate(void) {
    if(!m_pSceneMgr)
        return;

    int n = m_emitters.size();
    for(int i = 0; i < n; i++) {
        fgParticleEmitter *pEmitter = m_emitters[i];
        if(!pEmitter) {
            continue;
        }
        fgParticleEffect *pEffect = pEmitter->getParticleEffect();
        if(!pEffect) {
            continue;
        }
        // Need also to update vertex data in every draw call
        fgGfxDrawCall *pDrawCall = pEmitter->getDrawCall(); //static_cast<fgGfxSceneManager *>(m_pSceneMgr)->getDrawCall(static_cast<fgGfxSceneNode *>(pEmitter));
        fgVertexData *pVertexData = NULL;
        if(pDrawCall) {
            // #FIXME
            fgTextureResource *pTexture = (fgTextureResource *)(static_cast<fgResourceManager *>(m_pResourceMgr)->request(pEffect->getTextureName()));
            if(pTexture) {
                pEffect->setTextureGfxID(pTexture->getRefGfxID());
            }
            pDrawCall->setTexture(pEffect->getTextureGfxID());
            // Just in case?
            pDrawCall->setPrimitiveMode(fgGfxPrimitiveMode::FG_GFX_TRIANGLES);
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
