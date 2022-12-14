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
 * File:   fgPsParticleEmitter.cpp
 * Author: vigilant
 * 
 * Created on October 24, 2014, 4:31 PM
 */

#include "fgPsParticleEmitter.h"
#include "GFX/fgGfxCameraAnimation.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::CParticleEmitter::CParticleEmitter(CParticleEffect *pEffect) :
base_type(SCENE_NODE_PARTICLE_EMITTER, NULL),
drawable_type(),
m_effects(),
m_origin(),
m_particles(),
m_numParticles(0),
m_maxCount(0),
m_pCamera(NULL) {
    if(!m_drawCall) {
        m_drawCall = new CDrawCall();
    }

    setCollidable(FG_FALSE);
    setupFromParticleEffect(pEffect);
    setNodeTypeMask(SCENE_NODE_PARTICLE_EMITTER);
}
//------------------------------------------------------------------------------

gfx::CParticleEmitter::~CParticleEmitter() {
    m_particles.clear_optimised();
    m_effects.clear_optimised();
}
//------------------------------------------------------------------------------

fgBool gfx::CParticleEmitter::queryTrait(const fg::traits::SceneNode trait, void **pObj) {
    fgBool status = hasTraits(trait);
    status = (fgBool)(status && (pObj != NULL));
    if(status) {
        if(trait & fg::traits::DRAWABLE) {
            *pObj = static_cast<traits::CDrawable*>(this);
        }
    } else {
        status = base_type::queryTrait(trait, pObj);
    }
    return status;
}
//------------------------------------------------------------------------------

void gfx::CParticleEmitter::removeParticle(const unsigned int which) {
    if(which >= m_numParticles)
        return;
    m_particles[which] = m_particles[(m_numParticles - 1)];
    //m_particles.resize(m_particles.size() - 1);
    m_numParticles--;
}
//------------------------------------------------------------------------------

void gfx::CParticleEmitter::addParticles(const unsigned int count,
                                         const Vector3f& customOrigin) {
    if(!count)
        return;
    if(m_effects.empty())
        return;
    // #FIXME 
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
//------------------------------------------------------------------------------

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
        m_drawCall->setZIndex(Z_INDEX_PARTICLES);
        m_drawCall->setComponentActive(Vertex4v::attribMask());
        // Two triangles
        m_drawCall->getVertexData()->reserve(this->getMaxCount()*6);
        if(pParticleEffect->getShaderProgram())
            m_drawCall->setShaderProgram(pParticleEffect->getShaderProgram());
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

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

    // This runs through the particles and updates the vertex data
    // Given particle effect is allowed to use just the one texture
    // To use different representations for particles, texture sheet is used
    // The whole vertex, uv, color, ... data is passed as a single AoS stream
    for(int i = 0; i < (int)m_numParticles; i++) {
        pEffect->basicCalculate(&m_particles[i]);
        if(m_particles[i].life <= 0.0f) {
            removeParticle(i);
            //continue;
        }
#if 0
        else if(m_isAreaCheck == false && m_drawMode == MODE_2D) {
            if(m_particles[i].bbox.pos.x + m_particles[i].bbox.size.x / 2 >= float(screenArea.x) && m_particles[i].bbox.pos.x - m_particles[i].bbox.size.x / 2 <= float(screenArea.x + screenArea.w)) {
                // The UPPER and LOWER boundary
                if(m_particles[i].bbox.pos.y + m_particles[i].bbox.size.y / 2 <= float(screenArea.y) || m_particles[i].bbox.pos.y - m_particles[i].bbox.size.y / 2 >= float(screenArea.y + screenArea.h))
                    remove(i);
                // Particle X position is out of boundaries so we can delete it
            } else {
                remove(i);
            }
        }
#endif
        SParticle &particle = m_particles[i];
        //
        // Calculate the texture coords based on texture sheet parameters
        // Maybe there is a way to do this more quickly?
        // Would need to pre-calculate this data, store it in some kind of object
        // CTextureSheet or what-not
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

        Vector3f position = particle.bbox.pos;
        Vector3f &size = particle.bbox.size;
        Vector2f uv1 = Vector2f(s, t + dt);
        Vector2f uv2 = Vector2f(s + ds, t);

        const float w2 = size.x / 2.0f;
        const float h2 = size.y / 2.0f;
        const float d2 = size.z / 2.0f;

        // Resize the axis aligned bound box of the scene node (particle emitter)
        m_aabb.merge(BoundingBox3Df(Vector3f(position.x - w2, position.y - h2, position.z - d2), size));
        float z = -1.0f;

        //
        // This still would need optimization
        // More optimal would be different primitive (different than quad, 2 tris)
        // Would need some kind of optimizer (different shape yields faster results)
        // Next: need to pass some data to the shader, some calculations should
        // be done on the gpu (matrix mult, usage of quaternions)
        //
        // This would need to be done as shader attribute, for every vertex
        // maybe along with the burn parameter
        //

        Vector3f V1(-w2, -h2, z); // V1
        Vector3f V2(-w2, h2, z); // V2 = V4
        Vector3f V3(w2, -h2, z); // V3 = V6
        Vector3f V5(w2, +h2, z); // V5

        // This will rotate the particle so it will point in the direction
        // of flying, useful for sparks, long smoke, debris
        if(pEffect->isFacingVelocity()) {
            Matrix3f mat;
            Vector3f direction = math::normalize(particle.velocity);

            // Find the rotation between the front of the object (that we assume towards +Z, 
            // but this depends on your model) and the desired direction 
            Quatf rot1 = math::rotation(Vec3f(0.0f, 1.0f, 0.0f), direction);
#if 0
            // Recompute desiredUp so that it's perpendicular to the direction
            // You can skip that part if you really want to force desiredUp
            Vec3f desiredUp = math::cross(direction, Vec3f(0.0f, 0.0f, 1.0f));
            Vec3f right = math::cross(direction, desiredUp);
            desiredUp = math::cross(right, direction);

            // Because of the 1rst rotation, the up is probably completely screwed up. 
            // Find the rotation between the "up" of the rotated object, and the desired up
            Vec3f newUp = rot1 * Vec3f(0.0f, 1.0f, 0.0f);
            Quaternionf rot2 = RotationBetweenVectors(newUp, desiredUp);
#endif           
            mat = math::toMat3(rot1);
            //mat = math::rotate(mat, M_PIF, direction);

            V1 = mat * V1;
            V2 = mat * V2;
            V3 = mat * V3;
            V5 = mat * V5;
        } else if(pEffect->isFacingCamera() && m_pCamera) {
            // For now the particles can face camera or velocity/direction
            // not both
            Matrix3f mat;
            Vector3f &center = m_pCamera->getCenter();
            Vector3f &eye = m_pCamera->getEye();
            const Vector3f direction = math::normalize(center - eye);

            // Find the rotation between the front of the object (that we assume towards +Z, 
            // but this depends on your model) and the desired direction 
            Quatf rot1 = math::rotation(Vec3f(0.0f, 0.0f, 1.0f), direction);
            mat = math::toMat3(rot1);

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

        v1.position = Vector3f(position.x + V1.x, position.y + V1.y, position.z + V1.z); // V1
        v2.position = Vector3f(position.x + V2.x, position.y + V2.y, position.z + V2.z); // V2 = V4
        v3.position = Vector3f(position.x + V3.x, position.y + V3.y, position.z + V3.z); // V3 = V6
        v4.position = v2.position; // V2 = V4
        v5.position = Vector3f(position.x + V5.x, position.y + V5.y, position.z + V5.z); // V5
        v6.position = v3.position; // V3 = V6

        // This is special blending between transparency & additive 
        // Requires additional parameter - burn
        // This needs to be moved to the shader
        // Will cause data repeat (burn parameter will be passed for every vertex)
        // The variable ranges from zero (transparency blending) to one (additive blending).
        float burn = particle.burn; // #FIXME
        Vector4f rgb = particle.color;
        float alpha = rgb.a;
        Vector4f fgc = rgb * alpha;
        float alphac = alpha * (1.0f - burn);
        Color4f color(fgc[0], fgc[1], fgc[2], alphac);
        v1.color = color; // V1
        v2.color = color; // V2 = V4
        v4.color = color; // V2 = V4
        v5.color = color; // V5
        v3.color = color; // V3 = V6
        v6.color = color; // V3 = V6

    }
    m_aabb.radius = math::length(m_aabb.extent); // why radius is not updated?
    pData4v->resize(m_numParticles * 6);
}
//------------------------------------------------------------------------------

void gfx::CParticleEmitter::draw(const Matrix4f& modelMat) {
    //glEnable(GL_POLYGON_OFFSET_FILL);
    //glPolygonOffset(1.0f, 2.0f);
    if(!isVisible() || !m_drawCall)
        return;
    // #FIXME - such things should be set inside of a material
    context::blendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    context::setBlend(FG_TRUE);
    context::setCullFace(FG_FALSE);
    context::disable(gfx::DEPTH_WRITEMASK);

    m_drawCall->draw(m_finalModelMat * modelMat);

    context::enable(gfx::DEPTH_WRITEMASK);
    context::setCullFace(FG_TRUE);
    context::setBlend(FG_FALSE);

    //glDisable(GL_POLYGON_OFFSET_FILL);
}
//------------------------------------------------------------------------------
