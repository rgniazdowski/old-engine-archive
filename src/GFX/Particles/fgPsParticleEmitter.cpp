/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
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

using namespace fg;

/**
 * 
 */
gfx::CParticleEmitter::CParticleEmitter(CParticleEffect *pEffect) :
CSceneNode(SCENE_NODE_CUSTOM, NULL),
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
gfx::CParticleEmitter::~CParticleEmitter() {
    m_particles.clear_optimised();
    m_effects.clear_optimised();
}

/**
 * 
 * @param which
 */
void gfx::CParticleEmitter::removeParticle(const unsigned int which) {
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
void gfx::CParticleEmitter::addParticles(const unsigned int count, const Vector3f& customOrigin) {
    if(!count)
        return;
    if(m_effects.empty())
        return;
    CParticleEffect *pParticleEffect = m_effects.back();
    if(!pParticleEffect) {
        return;
    }
    SParticle particle;
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
fgBool gfx::CParticleEmitter::setupFromParticleEffect(CParticleEffect *pParticleEffect) {
    if(!pParticleEffect) {
        return FG_FALSE;
    }
    if(m_effects.find(pParticleEffect) != -1) {
        return FG_FALSE;
    }
    m_effects.push_back(pParticleEffect);
    setMaxCount(pParticleEffect->getMaxCount());
    if(m_drawCall) {
        m_drawCall->setComponentActive(Vertex4v::attribMask());
        // Two triangles
        m_drawCall->getVertexData()->reserve(this->getMaxCount()*6);
    }
    return FG_TRUE;
}

/**
 *
 */
void gfx::CParticleEmitter::calculate(void) {
    CVertexData *pVertexData = NULL;
    if(m_drawCall) {
        pVertexData = m_drawCall->getVertexData();
    }
    if(!pVertexData) {
        return;
    }
    // The particle vertex data needs to be 4V - with color
    if(pVertexData->attribMask() != Vertex4v::attribMask()) {
        return;
    }
    if(m_effects.empty()) {
        return;
    }
    // #FIXME just one effect ? :(
    CParticleEffect *pEffect = m_effects.back();
    CVertexData4v *pData4v = static_cast<CVertexData4v *>(pVertexData);
    m_aabb.invalidate();
    m_aabb.min.z = 0.0f;

    for(int i = 0; i < (int)m_numParticles; i++) {
        pEffect->basicCalculate(&m_particles[i]);
        if(m_particles[i].life <= 0.0f) {
            removeParticle(i);
            //continue;
        }
        SParticle &particle = m_particles[i];
        //
        // Calculate the texture coords based on texture sheet parameters
        //
        Vector2i &texSheetSize = pEffect->getTextureSheetSize();
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
        Vertex4v &v1 = pData4v->at(j + 0);
        Vertex4v &v2 = pData4v->at(j + 1);
        Vertex4v &v3 = pData4v->at(j + 2);
        Vertex4v &v4 = pData4v->at(j + 3);
        Vertex4v &v5 = pData4v->at(j + 4);
        Vertex4v &v6 = pData4v->at(j + 5);

        float x1 = particle.bbox.pos.x;
        float y1 = particle.bbox.pos.y;
        Vector3f &size = particle.bbox.size;
        Vector2f uv1 = Vector2f(s, t + dt);
        Vector2f uv2 = Vector2f(s + ds, t);

        float w2 = size.x / 2.0f;
        float h2 = size.y / 2.0f;
        m_aabb.merge(BoundingBox3Df(Vector3f(x1 - w2, y1 - h2, 0.0f), size));
        float z = -1.0f;

        Vector4f V1(0 * x1 - w2, 0 * y1 - h2, z, 0.0f); // V1
        Vector4f V2(0 * x1 - w2, 0 * y1 + h2, z, 0.0f); // V2 = V4
        Vector4f V3(0 * x1 + w2, 0 * y1 - h2, z, 0.0f); // V3 = V6
        Vector4f V5(0 * x1 + w2, 0 * y1 + h2, z, 0.0f); // V5

        //Vector3f V1(0 * x1 - w2, 0 * y1 - h2, z); // V1
        //Vector3f V2(0 * x1 - w2, 0 * y1 + h2, z); // V2 = V4
        //Vector3f V3(0 * x1 + w2, 0 * y1 - h2, z); // V3 = V6
        //Vector3f V5(0 * x1 + w2, 0 * y1 + h2, z); // V5

        if(pEffect->isFacingVelocity()) {
            Matrix4f mat;
            Vector3f direction = math::normalize(particle.velocity);
            // This will only rotate in Z axis
            // It's suitable only for 2D
            mat[0].x = direction.y;
            mat[0].y = -direction.x;
            mat[1].x = direction.x;
            mat[1].y = direction.y;
#if 0
            //mat = fgMath::rotate(mat, particle.rotation.z, Vectortor3f(0.0f, 0.0f, 1.0f));
            //mat = fgMath::lookAt(Vector3f(), particle.velocity, Vectortor3f(1.0f, 0.0f, 0.0f));
            /*
             detail::tvec3<T, P> f(normalize(center - eye));
                detail::tvec3<T, P> s(normalize(cross(f, up)));
                detail::tvec3<T, P> u(cross(s, f));

                detail::tmat4x4<T, P> Result(1);
                Result[0][0] = s.x;
                Result[1][0] = s.y;
                Result[2][0] = s.z;
                Result[0][1] = u.x;
                Result[1][1] = u.y;
                Result[2][1] = u.z;
                Result[0][2] =-f.x;
                Result[1][2] =-f.y;
                Result[2][2] =-f.z;
                Result[3][0] =-dot(s, eye);
                Result[3][1] =-dot(u, eye);
                Result[3][2] = dot(f, eye);
             */
            /*
            Vector3f center = particle.bbox.pos+particle.velocity, eye = particle.bbox.pos;
            Vector3f up(0, 1, 0);
            Vector3f side = fgMath::normalize(fgMath::cross(direction, up));
            up = fgMath::cross(side, direction);

            mat[0].x = side.x;
            mat[0].y = side.y;
            mat[0].z = size.z;

            mat[1].x = up.x;
            mat[1].y = up.y;
            mat[1].z = up.z;

            mat[2].x = -direction.x;
            mat[2].y = -direction.y;
            mat[2].z = -direction.z;


            Vector3f f(fgMath::normalize(center - eye));
            Vector3f s(fgMath::normalize(fgMath::cross(f, up)));
            Vector3f u(fgMath::cross(s, f));

            mat = fgMat4f(1);
            mat[0][0] = s.x;
            mat[1][0] = s.y;
            mat[2][0] = s.z;
            mat[0][1] = u.x;
            mat[1][1] = u.y;
            mat[2][1] = u.z;
            mat[0][2] = -f.x;
            mat[1][2] = -f.y;
            mat[2][2] = -f.z;
            mat[3][0] = -fgMath::dot(s, eye);
            mat[3][1] = -fgMath::dot(u, eye);
            mat[3][2] = fgMath::dot(f, eye);
             */
#endif
            V1 = mat * V1;
            V2 = mat * V2;
            V3 = mat * V3;
            V5 = mat * V5;
        }

        //v1.position = Vector3f(x1 - w2, y1 - h2, z); // V1
        v1.uv = Vector2f(uv1.x, uv1.y); // V1
        //v2.position = Vector3f(x1 - w2, y1 + h2, z); // V2 = V4
        v2.uv = Vector2f(uv1.x, uv2.y); // V2 = V4
        //v3.position = Vector3f(x1 + w2, y1 - h2, z); // V3 = V6
        v3.uv = Vector2f(uv2.x, uv1.y); // V3 = V6
        //v4.position = Vector3f(x1 - w2, y1 + h2, z); // V2 = V4
        v4.uv = Vector2f(uv1.x, uv2.y); // V2 = V4
        //v5.position = Vector3f(x1 + w2, y1 + h2, z); // V5
        v5.uv = Vector2f(uv2.x, uv2.y); // V5
        //v6.position = Vector3f(x1 + w2, y1 - h2, z); // V3 = V6
        v6.uv = Vector2f(uv2.x, uv1.y); // V3 = V6

        v1.position = Vector3f(x1 + V1.x, y1 + V1.y, V1.z); // V1
        v2.position = Vector3f(x1 + V2.x, y1 + V2.y, V2.z); // V2 = V4
        v3.position = Vector3f(x1 + V3.x, y1 + V3.y, V3.z); // V3 = V6
        v4.position = v2.position; // V2 = V4
        v5.position = Vector3f(x1 + V5.x, y1 + V5.y, V5.z); // V5
        v6.position = v3.position; // V3 = V6

        //The variable ranges from zero (trans-parency blending) to one (additive blending).
        float burn = particle.burn; // #FIXME

        Vector4f rgb = particle.color;
        float alpha = rgb.a;
        Vector4f fgc = rgb * alpha;
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
