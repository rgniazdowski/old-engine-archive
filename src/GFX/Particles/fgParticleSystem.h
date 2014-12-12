/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/*
 * fgParticleSystem.h
 *
 *  Created on: 17-06-2012
 *      Author: Vigilant
 */

#ifndef FG_INC_PARTICLE_SYSTEM
    #define FG_INC_PARTICLE_SYSTEM

    #include "fgBool.h"
    #include "fgPsParticleEffect.h"
    #include "fgPsParticleEmitter.h"
    #include "Util/fgTag.h"
    
class fgParticleSystem;

    #define FG_TAG_PARTICLE_SYSTEM_NAME     "ParticleSystem"
    #define FG_TAG_PARTICLE_SYSTEM          FG_TAG_TYPE(fgParticleSystem)

FG_TAG_TEMPLATE_ID_AUTO(fgParticleSystem, FG_TAG_PARTICLE_SYSTEM_NAME);

// Special handle type for Particle Effect
typedef FG_TAG_PARTICLE_SYSTEM fgParticleSystemTag;

    #define FG_MANAGER_PARTICLE     0x00000800

/**
 *
 */
class fgParticleSystem : public fg::base::Manager  {
public:
    typedef fgVector<fgParticleEmitter *> emittersVec;
    typedef emittersVec::iterator emittersVecItor;
    
private:
    /// Pointer to the external resource manager
    fg::base::Manager *m_pResourceMgr;
    /// Pointer to the external scene manager
    fg::base::Manager *m_pSceneMgr;
    /// Emitters vector
    emittersVec m_emitters;
    
public:
    /**
     * 
     */
    fgParticleSystem(fg::base::Manager *pResourceMgr = NULL, fg::base::Manager *pSceneMgr = NULL);
    /**
     * 
     */
    virtual ~fgParticleSystem();

protected:
    /**
     * 
     */
    virtual void clear(void);
    
    /**
     * 
     * @param pEmitter
     * @return 
     */
    fgBool isEmitterInTheArray(fgParticleEmitter *pEmitter);
    
    /**
     * 
     * @param emitterNameTag
     * @return 
     */
    fgBool isEmitterInTheArray(const std::string& emitterNameTag);
    
    /**
     * 
     * @param emitterNameTag
     * @return 
     */
    fgBool isEmitterInTheArray(const char *emitterNameTag);
    
public:

    /**
     * 
     * @param pResourceMgr
     */
    inline void setResourceManager(fg::base::Manager *pResourceMgr) {
        m_pResourceMgr = pResourceMgr;
    }
    /**
     * 
     * @return 
     */
    inline fg::base::Manager *getResourceManager(void) const {
        return m_pResourceMgr;
    }
    /**
     * 
     * @param pSceneMgr
     */
    inline void setSceneManager(fg::base::Manager *pSceneMgr) {
        m_pSceneMgr = pSceneMgr;
    }
    /**
     * 
     * @return 
     */
    inline fg::base::Manager *getSceneManager(void) const {
        return m_pSceneMgr;
    }
    
    /**
     * 
     * @param pEmitter
     * @return 
     */
    fgBool isEmitterInTheScene(const fgParticleEmitter *pEmitter);
    
    /**
     * 
     * @param emitterNameTag
     * @return 
     */
    fgBool isEmitterInTheScene(const std::string& emitterNameTag);
    
    /**
     * 
     * @param emitterNameTag
     * @return 
     */
    fgBool isEmitterInTheScene(const char *emitterNameTag);
    
    /**
     * 
     * @param emitterNameTag
     * @return 
     */
    fgParticleEmitter *getParticleEmitter(const std::string& emitterNameTag);
    
    /**
     * 
     * @param emitterNameTag
     * @return 
     */
    fgParticleEmitter *getParticleEmitter(const char *emitterNameTag);
    
    /**
     * 
     * @return 
     */
    virtual fgBool destroy(void);
    /**
     * 
     * @return 
     */
    virtual fgBool initialize(void);

    /**
     * 
     * @param dhUniqueID
     * @param pData
     * @param nameTag
     * @return 
     */
    virtual fgBool insert(fgParticleEffect* pEffect, const std::string& nameTag);

    /**
     * 
     * @param shUniqueID
     * @param pStyle
     * @return 
     */
    virtual fgBool insertParticleEffect(fgParticleEffect *pEffect);

    /**
     * 
     * @param info
     * @return 
     */
    virtual fgParticleEffect* request(const std::string& info);
    /**
     * 
     * @param info
     * @return 
     */
    virtual fgParticleEffect* request(const char *info);
    
    /**
     * 
     * @param particleEffectNameTag
     * @param particleEmitterNameTag
     * @param emitterOrigin
     * @return 
     */
    virtual fgParticleEmitter* insertParticleEmitter(const std::string& particleEffectNameTag,
                                                     const std::string& particleEmitterNameTag,
                                                     const fgVector3f& emitterOrigin);
    
    /**
     * 
     * @param particleEffectNameTag
     * @param particleEmitterNameTag
     * @param emitterOrigin
     * @return 
     */
    virtual fgParticleEmitter* insertParticleEmitter(const char *particleEffectNameTag,
                                                     const char *particleEmitterNameTag,
                                                     const fgVector3f& emitterOrigin);
    
    /**
     * 
     * @param pParticleEmitter
     * @param particleEffectNameTag
     * @return 
     */
    virtual fgBool insertParticleEmitter(const fgParticleEmitter* pParticleEmitter,
                                         const std::string& particleEffectNameTag);
    
    /**
     * 
     */
    virtual void calculate(void);

};

#endif /* PARTICLESYSTEM */
