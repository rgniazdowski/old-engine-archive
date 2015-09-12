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
 * File:   fgGFXSceneNodeMesh.cpp
 * Author: vigilant
 * 
 * Created on November 14, 2014, 11:30 PM
 */

#include "fgGfxSceneNodeMesh.h"
#include "fgGfxSceneManager.h"
#include "GFX/Animation/fgGfxAnimation.h"

using namespace fg;

//------------------------------------------------------------------------------

gfx::CSceneNodeMesh::CSceneNodeMesh(SMeshBase *pMesh, CSceneNode *pParent) :
CSceneNode(SCENE_NODE_MESH, pParent) {
    CSceneNode::setNodeType(SCENE_NODE_MESH);
    if(m_drawCall) {
        delete m_drawCall;
        m_drawCall = NULL;
    }
    // #FIXME - still draw call management needs some fixing - this is so awkward, I mean... srsly?
    m_drawCall = new CDrawCall(DRAW_CALL_MESH, ATTRIBUTE_POSITION_BIT | ATTRIBUTE_UVS_BIT | ATTRIBUTE_NORMAL_BIT);
    m_drawCall->setZIndex(Z_INDEX_OBJECTS_3D);
    setMesh(pMesh);
}
//------------------------------------------------------------------------------

gfx::CSceneNodeMesh::CSceneNodeMesh(const CSceneNodeMesh& orig) : base_type(orig) {
    if(this != &orig) {
        this->m_drawCall = NULL;
        CSceneNode::setNodeType(SCENE_NODE_MESH);
        this->m_drawCall = new CDrawCall(DRAW_CALL_MESH, ATTRIBUTE_POSITION_BIT | ATTRIBUTE_UVS_BIT | ATTRIBUTE_NORMAL_BIT);
        this->m_drawCall->setZIndex(Z_INDEX_OBJECTS_3D);
        this->setMesh(orig.m_pMesh);
        this->setMaterial(orig.m_pMaterial);
    }
}
//------------------------------------------------------------------------------

gfx::CSceneNodeMesh::~CSceneNodeMesh() {
    m_pMesh = NULL;
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeMesh::refreshGfxInternals(void) {
    if(!m_pManager)
        return;
    if(m_pManager->getManagerType() != FG_MANAGER_SCENE) {
        return;
    }
    if(m_drawCall) {
        m_drawCall->setupFromMesh(m_pMesh);
        m_drawCall->setupMaterial(m_pMaterial);
    }
}
//------------------------------------------------------------------------------

gfx::SSkinnedMesh* gfx::CSceneNodeMesh::getSkinnedMesh(void) const {
    if(!m_pMesh)
        return NULL;
    if(m_pMesh->isSkinnedMesh()) {
        if(m_pMesh->isSoA()) {
            return static_cast<SSkinnedMesh*>(static_cast<SSkinnedMeshSoA*>(m_pMesh));
        } else if(m_pMesh->isAoS()) {
            return static_cast<SSkinnedMesh*>(static_cast<SSkinnedMeshAoS*>(m_pMesh));
        }
    }
    return NULL;
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeMesh::setMesh(SMeshBase* pMesh) {
    m_pMesh = pMesh;
    if(!pMesh)
        return;
    base_type::setNodeType(SCENE_NODE_MESH);
    if(m_drawCall) {
        m_drawCall->setupFromMesh(pMesh);
    }
    setBoundingVolume(pMesh->aabb);
    m_modelMat = math::translate(Matrix4f(), pMesh->displacement);
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeMesh::setMaterial(SMaterial *pMaterial) {
    m_pMaterial = pMaterial;
    if(!pMaterial)
        return;
    if(m_drawCall) {
        m_drawCall->setupMaterial(pMaterial);
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeMesh::animate(float delta) {
    base_type::animate(delta);
    SSkinnedMesh *pSkinnedMesh = getSkinnedMesh();
    if(!pSkinnedMesh)
        return;
    animated_type::AnimationsVec& animations = getAnimations();
    if(animations.empty())
        return;
    const unsigned int nAnimations = animations.size();
    for(unsigned int animId = 0; animId < nAnimations; animId++) {
        anim::SAnimationInfo &info = animations[animId];
        // #FIXME - timesys
        // calculate will check if animation is compatible
        pSkinnedMesh->calculate(info.pAnimation, info.currentFrame, timesys::exact()/1.0f);
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeMesh::draw(const Matrix4f& modelMat) {
    if(!isVisible())
        return;
    if(m_drawCall) {
        animated_type::AnimationsVec& animations = getAnimations();
        const unsigned int nAnimations = animations.size();
        // should now use shader, check flags and push uniforms
        CShaderProgram* pProgram = m_drawCall->getShaderProgram();
        if(pProgram && nAnimations) {
            pProgram->use();
            // the index of animation should not be zero...
            pProgram->setUniform(shaders::UNIFORM_BONE_DUAL_QUATERNIONS,
                                 animations[0].currentFrame.dualQuaternions);
        }
    }
    base_type::draw(modelMat);
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeMesh::updateAABB(void) {

    physics::CCollisionBody *body = getCollisionBody();
    if(body) {
        if(m_pMesh && !isAutoScale()) {
            if(body->getBodyType() == physics::CCollisionBody::SPHERE) {
                body->setRadius(math::length(m_scale * m_pMesh->aabb.getExtent()));
            } else {
                body->setHalfSize(m_scale * (m_pMesh->aabb.getExtent()));
            }
            body->setInertiaTensor();
            body->calculateDerivedData();
        }
        // Well the collision body is present, so the base function can be called
        // it will do the required transformations (based on the physics)
        base_type::updateAABB();
    }
    if(m_pMesh) {
        if(!m_pMesh->isSkinnedMesh()) {
            m_aabb.min = m_pMesh->aabb.min;
            m_aabb.max = m_pMesh->aabb.max;
            m_aabb.transform(m_modelMat);
        } else {
            m_aabb.invalidate();
            animated_type::AnimationsVec& animations = getAnimations();
            if(animations.empty())
                return;
            // This still need fixing, need to interpolate animations
            // automatically, and use result here
            // (without traversing animations ...)

            SSkinnedMesh *pSkinnedMesh = this->getSkinnedMesh();
            const unsigned int nAnimations = animations.size();
            for(unsigned int animId = 0; animId < nAnimations; animId++) {
                anim::SAnimationInfo &info = animations[animId];
                if(!info.pAnimation)
                    continue;
                if(info.pAnimation->getType() != anim::Type::BONE)
                    continue;
                unsigned int nBones = pSkinnedMesh->boneEdges.size();
                for(unsigned int boneId = 0; boneId < nBones; boneId++) {
                    Vec3f min, max;
                    pSkinnedMesh->boneEdges[boneId].transform(pSkinnedMesh,
                                                              info.currentFrame.dualQuaternions,
                                                              min, max);
                    m_aabb.merge(min);
                    m_aabb.merge(max);
                }
                if(info.pAnimation->getType() == anim::Type::BONE)
                    break; // #FIXME - this seriously need to be better
                // also would really need some method in base class
                // that updates the aabb based on the children size
                // but too soon for that !TODO
            }
            m_aabb.transform(m_modelMat);
        }
        if(body && !isAutoScale()) {
            m_aabb.radius = body->getRadius();
        } else {
            m_aabb.radius = math::length(m_scale * m_pMesh->aabb.getExtent());
        }
    }
}
//------------------------------------------------------------------------------
