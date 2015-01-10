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
fg::gfx::CParticleSystem::CParticleSystem(fg::base::CManager *pResourceMgr, fg::base::CManager *pSceneMgr) {
    setResourceManager(pResourceMgr);
    setSceneManager(pSceneMgr);
}

/**
 * 
 */
fg::gfx::CParticleSystem::~CParticleSystem() {
    fg::gfx::CParticleSystem::destroy();
}

/**
 * 
 */
void fg::gfx::CParticleSystem::clear() {
    // ?
}

/**
 * 
 * @param pEmitter
 * @return 
 */
fgBool fg::gfx::CParticleSystem::isEmitterInTheArray(fgParticleEmitter *pEmitter) {
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
fgBool fg::gfx::CParticleSystem::isEmitterInTheArray(const std::string& emitterNameTag) {
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
fgBool fg::gfx::CParticleSystem::isEmitterInTheArray(const char *emitterNameTag) {
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
fgBool fg::gfx::CParticleSystem::isEmitterInTheScene(const fgParticleEmitter *pEmitter) {
    if(!pEmitter || !m_pSceneMgr)
        return FG_FALSE;

    //if(m_emitters.find(pEmitter))

    return static_cast<CSceneManager *>(m_pSceneMgr)->isManaged(pEmitter);
}

/**
 * 
 * @param emitterNameTag
 * @return 
 */
fgBool fg::gfx::CParticleSystem::isEmitterInTheScene(const std::string& emitterNameTag) {
    if(emitterNameTag.empty() || !m_pSceneMgr)
        return FG_FALSE;

    return static_cast<CSceneManager *>(m_pSceneMgr)->isManaged(emitterNameTag);
}

/**
 * 
 * @param emitterNameTag
 * @return 
 */
fgBool fg::gfx::CParticleSystem::isEmitterInTheScene(const char *emitterNameTag) {
    if(!emitterNameTag || !m_pSceneMgr)
        return FG_FALSE;

    return static_cast<CSceneManager *>(m_pSceneMgr)->isManaged(emitterNameTag);
}

/**
 * 
 * @param emitterNameTag
 * @return 
 */
fgParticleEmitter *fg::gfx::CParticleSystem::getParticleEmitter(const std::string& emitterNameTag) {
    if(emitterNameTag.empty() || !m_pSceneMgr)
        return NULL;

    fgParticleEmitter *pEmitter = (fgParticleEmitter *)static_cast<CSceneManager *>(m_pSceneMgr)->get(emitterNameTag);
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
fgParticleEmitter *fg::gfx::CParticleSystem::getParticleEmitter(const char *emitterNameTag) {
    if(!emitterNameTag || !m_pSceneMgr)
        return NULL;

    fgParticleEmitter *pEmitter = (fgParticleEmitter *)static_cast<CSceneManager *>(m_pSceneMgr)->get(emitterNameTag);
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
fgBool fg::gfx::CParticleSystem::destroy(void) {
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
    //m_emitters.resize(0);
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool fg::gfx::CParticleSystem::initialize(void) {
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
fgBool fg::gfx::CParticleSystem::insert(fgParticleEffect* pEffect, const std::string& nameTag) {
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
fgBool fg::gfx::CParticleSystem::insertParticleEffect(fgParticleEffect *pEffect) {
    if(!pEffect)
        return FG_FALSE;
    return insert(pEffect, pEffect->getName());
}

/**
 * 
 * @param info
 * @return 
 */
fgParticleEffect* fg::gfx::CParticleSystem::request(const std::string& info) {
    if(!m_pResourceMgr || info.empty())
        return NULL;
    return (fgParticleEffect *)(static_cast<fgResourceManager *>(m_pResourceMgr)->request(info));
}

/**
 * 
 * @param info
 * @return 
 */
fgParticleEffect* fg::gfx::CParticleSystem::request(const char *info) {
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
fgParticleEmitter* fg::gfx::CParticleSystem::insertParticleEmitter(const std::string& particleEffectNameTag,
                                                                   const std::string& particleEmitterNameTag,
                                                                   const fgVector3f& emitterOrigin) {
    if(!m_pSceneMgr || !m_pResourceMgr) {
        FG_LOG_ERROR("GFX: Unable to add ParticleEmitter - Particle System is not set up");
        return NULL;
    }
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
    fgParticleEffect *pEffect = (fgParticleEffect *)(static_cast<fgResourceManager *>(m_pResourceMgr)->request(particleEffectNameTag));
    if(!pEffect) {
        FG_LOG_ERROR("GFX: Unable to find particle effect: '%s'", particleEffectNameTag.c_str());
        return NULL;
    }
    if(pEffect->isDisposed()) {
        pEffect->create();
    }
    fgTextureResource *pTexture = (fgTextureResource *)(static_cast<fgResourceManager *>(m_pResourceMgr)->request(pEffect->getTextureName()));
    if(pTexture) {
        pEffect->setTextureGfxID(pTexture->getRefGfxID());
    }
    fgParticleEmitter *pEmitter = new fgParticleEmitter(pEffect);
    pEmitter->setName(particleEmitterNameTag);
    //pEmitter->setOrigin()

    static_cast<fg::gfx::CSceneManager *>(m_pSceneMgr)->addNode(pEmitter->getRefHandle(),
                                                                pEmitter,
                                                                (fg::gfx::CSceneNode *)NULL);

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
fgParticleEmitter* fg::gfx::CParticleSystem::insertParticleEmitter(const char *particleEffectNameTag,
                                                                   const char *particleEmitterNameTag,
                                                                   const fgVector3f& emitterOrigin) {

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

/**
 * 
 * @param pParticleEmitter
 * @param particleEffectNameTag
 * @return 
 */
fgBool fg::gfx::CParticleSystem::insertParticleEmitter(const fgParticleEmitter* pParticleEmitter,
                                                       const std::string& particleEffectNameTag) {
    if(!pParticleEmitter || !m_pSceneMgr) {
        return FG_FALSE;
    }

    return FG_TRUE;
}

/**
 * 
 */
void fg::gfx::CParticleSystem::calculate(void) {
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
        fg::gfx::CDrawCall *pDrawCall = pEmitter->getDrawCall(); //static_cast<fgGfxSceneManager *>(m_pSceneMgr)->getDrawCall(static_cast<fgGfxSceneNode *>(pEmitter));
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
