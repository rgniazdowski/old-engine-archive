/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgPsParticleEmitter.cpp
 * Author: vigilant
 * 
 * Created on October 24, 2014, 4:31 PM
 */

#include "fgPsParticleEmitter.h"

/**
 * 
 */
fgParticleEmitter::fgParticleEmitter() { }

/**
 * 
 */
fgParticleEmitter::~fgParticleEmitter() {
    m_particles.clear_optimised();
    m_effects.clear_optimised();
}

/**
 * 
 * @param which
 */
void fgParticleEmitter::removeParticle(const unsigned int which) {
    if(which >= m_particles.size())
        return;
    m_particles[which] = m_particles.back();
    m_particles.resize(m_particles.size() - 1);
}

/**
 * 
 * @param count
 */
void fgParticleEmitter::addParticles(const unsigned int count, const fgVector3f& customOrigin) {
    if(!count)
        return;
    if(m_effects.empty())
        return;
    fgParticleEffect *pParticleEffect = m_effects.back();
    if(!pParticleEffect) {
        return;
    }
    fgParticle particle;
    for(unsigned int i = 0; i < count; i++) {
        if(m_particles.size() >= m_maxCount)
            return;
        pParticleEffect->initializeParticle(&particle, FG_FALSE, customOrigin);
        m_particles.push_back(particle);
    }
}

/**
 * 
 * @param pParticleEffect
 * @return
 */
fgBool fgParticleEmitter::setupFromParticleEffect(fgParticleEffect *pParticleEffect) {
    if(!pParticleEffect) {
        return FG_FALSE;
    }
    if(m_effects.find(pParticleEffect) != -1) {
        return FG_FALSE;
    }
    m_effects.push_back(pParticleEffect);
    setMaxCount(pParticleEffect->getMaxCount());
    return FG_TRUE;
}

/**
 *
 */
void fgParticleEmitter::calculate(fgVertexData *pVertexData) {
    if(!pVertexData) {
        return;
    }
    // The particle vertex data needs to be 4V - with color
    if(pVertexData->attribMask() != fgVertex4v::attribMask()) {
        return;
    }
    if(m_effects.empty()) {
        return;
    }
    // #FIXME
    fgParticleEffect *pEffect = m_effects.back();
    fgVertexData4v *pData4v = static_cast<fgVertexData4v *>(pVertexData);

    unsigned int nParticles = m_particles.size();
    for(int i = 0; i < (unsigned int)nParticles; i++) {
        fgParticle &particle = m_particles[i];
        pEffect->basicCalculate(&m_particles[i]);
        
        
        fgVector2i &texSheetSize = pEffect->getTextureSheetSize();
        if(particle.texIndex < 0)
            particle.texIndex = 0;
        if(particle.texIndex >= texSheetSize.x * texSheetSize.y)
            particle.texIndex = 0;
        int x = particle.texIndex % texSheetSize.x;
        int y = particle.texIndex / texSheetSize.y;
        float s = (float)x / texSheetSize.x;
        float t = (float)y / texSheetSize.y;
        float ds = 1.0f / (float)texSheetSize.x;
        float dt = 1.0f / (float)texSheetSize.y;

        // Setting up the UV STREAM
        //m_UVStream[i * 4 + 0] = fgVector2f(s, t);
        //m_UVStream[i * 4 + 1] = fgVector2f(s, t + dt);
        //m_UVStream[i * 4 + 2] = fgVector2f(s + ds, t + dt);
        //m_UVStream[i * 4 + 3] = fgVector2f(s + ds, t);
        
        //
        // Update the vertex data
        //
        int j = i * 6;
        if(pData4v->size() <= j)
            break;
        fgVertex4v &v1 = pData4v->at(j + 0);
        fgVertex4v &v2 = pData4v->at(j + 1);
        fgVertex4v &v3 = pData4v->at(j + 2);
        fgVertex4v &v4 = pData4v->at(j + 3);
        fgVertex4v &v5 = pData4v->at(j + 4);
        fgVertex4v &v6 = pData4v->at(j + 5);

        float x1 = particle.bbox.pos.x;
        float y1 = particle.bbox.pos.y;
        fgVector3f &size = particle.bbox.size;
        fgVector2f uv1 = fgVec2f(s, t + dt);
        fgVector2f uv2 = fgVec2f(s + ds, t);
        float w2 = size.x / 2.0f;
        float h2 = size.y / 2.0f;

        v1.position = fgVec3f(x1 - w2, y1 - h2, 0.0f);
        v1.uv = fgVec2f(uv1.x, 1.0f - uv1.y);

        v2.position = fgVec3f(x1 - w2, y1 + h2, 0.0f);
        v2.uv = fgVec2f(uv1.x, 1.0f - uv2.y);

        v3.position = fgVec3f(x1 + w2, y1 - h2, 0.0f);
        v3.uv = fgVec2f(uv2.x, 1.0f - uv1.y);

        v4.position = fgVec3f(x1 - w2, y1 + h2, 0.0f);
        v4.uv = fgVec2f(uv1.x, 1.0f - uv2.y);

        v5.position = fgVec3f(x1 + w2, y1 + h2, 0.0f);
        v5.uv = fgVec2f(uv2.x, 1.0f - uv2.y);

        v6.position = fgVec3f(x1 + w2, y1 - h2, 0.0f);
        v6.uv = fgVec2f(uv2.x, 1.0f - uv1.y);

        v1.color = particle.color;
        v2.color = particle.color;
        v3.color = particle.color;
        v4.color = particle.color;
        v5.color = particle.color;
        v6.color = particle.color;
        
        if(particle.life <= 0.0f) {
            removeParticle(i);
            nParticles--;
            continue;
        }
    }
}
