/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgPsParticleEmitter.h
 * Author: vigilant
 *
 * Created on October 24, 2014, 4:30 PM
 */

#ifndef _FG_PS_PARTICLE_EMITTER_H_
    #define	_FG_PS_PARTICLE_EMITTER_H_

    #include "fgVector.h"
    #include "GFX/fgGFXObject.h"
    #include "fgPsParticleEffect.h"
    
/**
 * 
 */
class fgParticleEmitter : public fgGfxObject {
public:
    typedef fgVector<fgParticleEffect *> particleEffects;
    typedef particleEffects::iterator    particleEffectsItor;
    
    typedef fgVector<fgParticle> particleData;
    typedef particleData::iterator particleDataItor;
private:
    /// Pointers to the particle effects to which
    /// this particle emitter is bound
    particleEffects m_effects;
    /// 
    fgVector3f m_origin;
    ///
    particleData m_particles;
    ///
    unsigned int m_maxCount;
    
public:
    /**
     * 
     */
    fgParticleEmitter();
    
    /**
     * 
     */
    virtual ~fgParticleEmitter();

    /**
     * 
     * @param maxCount
     */
    void setMaxCount(const unsigned int maxCount) {
        if(maxCount) {
            m_particles.reserve(maxCount);
            m_maxCount = maxCount;
        }
    }
    
    /**
     * 
     * @return 
     */
    inline unsigned int getMaxCount(void) const {
        return m_maxCount;
    }
    
    /**
     * 
     * @return 
     */
    inline fgParticleEffect* getParticleEffect(void) const {
        if(m_effects.size())
            return m_effects.back();
        return NULL;
    }
    
    /**
     * 
     * @return 
     */
    inline particleData& getParticleData(void) {
        return m_particles;
    }
    
    /**
     * 
     * @return 
     */
    inline unsigned int getParticleCount(void) const {
        return m_particles.size();
    }
    
    /**
     * 
     * @param which
     */
    void removeParticle(const unsigned int which);
    
    /**
     * 
     * @param count
     */
    void addParticles(const unsigned int count, const fgVector3f& customOrigin);
    
    /**
     * 
     * @param pParticleEffect
     * @return
     */
    fgBool setupFromParticleEffect(fgParticleEffect *pParticleEffect);
    
    /**
     * 
     */
    virtual void calculate(fgVertexData *pVertexData);
    
    
    
};

#endif	/* _FG_PS_PARTICLE_EMITTER_H_ */

