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
fgParticleEmitter::fgParticleEmitter(fgParticleEffect *pEffect) :
fgGfxSceneNode(FG_GFX_SCENE_NODE_CUSTOM, NULL),
m_effects(),
m_origin(),
m_particles(),
m_numParticles(0),
m_maxCount(0) {
    setupFromParticleEffect(pEffect);
}

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
    if(which >= m_numParticles)
        return;
    m_particles[which] = m_particles[(m_numParticles - 1)];
    //m_particles.resize(m_particles.size() - 1);
    m_numParticles--;
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
        if(m_numParticles >= m_maxCount)
            return;
        pParticleEffect->initializeParticle(&particle, FG_FALSE, customOrigin);
        m_particles[m_numParticles] = particle;
        m_numParticles++;
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
    if(m_drawCall) {
        m_drawCall->setComponentActive(fgVertex4v::attribMask());
        // Two triangles
        m_drawCall->getVertexData()->reserve(this->getMaxCount()*6);
    }
    return FG_TRUE;
}

/**
 *
 */
void fgParticleEmitter::calculate(void) {
    fgVertexData *pVertexData = NULL;
    if(m_drawCall) {
        pVertexData = m_drawCall->getVertexData();
    }
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
    // #FIXME just one effect ? :(
    fgParticleEffect *pEffect = m_effects.back();
    fgVertexData4v *pData4v = static_cast<fgVertexData4v *>(pVertexData);
    m_aabb.invalidate();
    m_aabb.min.z = 0.0f;
    
    for(int i = 0; i < (int)m_numParticles; i++) {
        pEffect->basicCalculate(&m_particles[i]);
        if(m_particles[i].life <= 0.0f) {
            removeParticle(i);
            //continue;
        }
        fgParticle &particle = m_particles[i];
        //
        // Calculate the texture coords based on texture sheet parameters
        //
        fgVector2i &texSheetSize = pEffect->getTextureSheetSize();
        if(particle.texIndex < 0)
            particle.texIndex = 0;
        if(particle.texIndex >= (unsigned int)texSheetSize.x * texSheetSize.y)
            particle.texIndex = 0;
        int x = particle.texIndex % texSheetSize.x;
        int y = particle.texIndex / texSheetSize.y;
        float s = (float)x / texSheetSize.x;
        float t = (float)y / texSheetSize.y;
        float ds = 1.0f / (float)texSheetSize.x;
        float dt = 1.0f / (float)texSheetSize.y;

        //
        // Update the vertex data
        //
        int j = i * 6;
        if(pData4v->size() <= (unsigned int)j)
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
        m_aabb.merge(fgBoundingBox3Df(fgVec3f(x1-w2,y1-h2,0.0f),size));
        
        fgMatrix4f mat;
        mat = glm::rotate(mat, particle.rotation.z, fgVector3f(0.0f, 0.0f, 1.0f));
        //mat = glm::lookAt(particle.bbox.pos, particle.bbox.pos + particle.velocity, particle.velocity);
        float z = -1.0f;

        fgVec4f V1(0 * x1 - w2, 0 * y1 - h2, z, 0.0f); // V1
        fgVec4f V2(0 * x1 - w2, 0 * y1 + h2, z, 0.0f); // V2 = V4
        fgVec4f V3(0 * x1 + w2, 0 * y1 - h2, z, 0.0f); // V3 = V6
        fgVec4f V5(0 * x1 + w2, 0 * y1 + h2, z, 0.0f); // V5

        //fgVec3f V1(0 * x1 - w2, 0 * y1 - h2, z); // V1
        //fgVec3f V2(0 * x1 - w2, 0 * y1 + h2, z); // V2 = V4
        //fgVec3f V3(0 * x1 + w2, 0 * y1 - h2, z); // V3 = V6
        //fgVec3f V5(0 * x1 + w2, 0 * y1 + h2, z); // V5

        V1 = mat * V1;
        V2 = mat * V2;
        V3 = mat * V3;
        V5 = mat * V5;

        //v1.position = fgVec3f(x1 - w2, y1 - h2, z); // V1
        v1.uv = fgVec2f(uv1.x, 1.0f - uv1.y); // V1
        //v2.position = fgVec3f(x1 - w2, y1 + h2, z); // V2 = V4
        v2.uv = fgVec2f(uv1.x, 1.0f - uv2.y); // V2 = V4
        //v3.position = fgVec3f(x1 + w2, y1 - h2, z); // V3 = V6
        v3.uv = fgVec2f(uv2.x, 1.0f - uv1.y); // V3 = V6
        //v4.position = fgVec3f(x1 - w2, y1 + h2, z); // V2 = V4
        v4.uv = fgVec2f(uv1.x, 1.0f - uv2.y); // V2 = V4
        //v5.position = fgVec3f(x1 + w2, y1 + h2, z); // V5
        v5.uv = fgVec2f(uv2.x, 1.0f - uv2.y); // V5
        //v6.position = fgVec3f(x1 + w2, y1 - h2, z); // V3 = V6
        v6.uv = fgVec2f(uv2.x, 1.0f - uv1.y); // V3 = V6

        v1.position = fgVec3f(x1 + V1.x, y1 + V1.y, V1.z); // V1
        v2.position = fgVec3f(x1 + V2.x, y1 + V2.y, V2.z); // V2 = V4
        v3.position = fgVec3f(x1 + V3.x, y1 + V3.y, V3.z); // V3 = V6
        v4.position = v2.position; // V2 = V4
        v5.position = fgVec3f(x1 + V5.x, y1 + V5.y, V5.z); // V5
        v6.position = v3.position; // V3 = V6

        //The variable ranges from zero (trans-parency blending) to one (additive blending).
        float burn = particle.burn; // #FIXME

        fgVector4f rgb = particle.color;
        float alpha = rgb.a;
        fgVector4f fgc = rgb * alpha;
        float alphac = alpha * (1.0f - burn);
        fgColor4f color(fgc[0], fgc[1], fgc[2], alphac);
        v1.color = color; // V1
        v2.color = color; // V2 = V4
        v4.color = color; // V2 = V4
        v5.color = color; // V5
        v3.color = color; // V3 = V6
        v6.color = color; // V3 = V6
        
    }
    pData4v->resize(m_numParticles * 6);
}
