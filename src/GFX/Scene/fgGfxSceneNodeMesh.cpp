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
#include "GFX/Animation/fgGfxBlending.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::CSceneNodeMesh::CSceneNodeMesh(SMeshBase *pMesh, CSceneNode *pParent) :
base_type(SCENE_NODE_MESH, pParent),
drawable_type() {
    if(!m_drawCall) {
        m_drawCall = new CDrawCall(DRAW_CALL_MESH,
                                   ATTRIBUTE_POSITION_BIT |
                                   ATTRIBUTE_UVS_BIT |
                                   ATTRIBUTE_NORMAL_BIT);
    }
    m_drawCall->setZIndex(Z_INDEX_OBJECTS_3D);
    setMesh(pMesh);
    setNodeTrait(drawable_type::SELF_TRAIT);
    setNodeTypeMask(SCENE_NODE_MESH);
}
//------------------------------------------------------------------------------

gfx::CSceneNodeMesh::CSceneNodeMesh(const CSceneNodeMesh& orig) : base_type(orig) {
    if(this != &orig) {
        this->m_drawCall = NULL;
        setNodeType(SCENE_NODE_MESH);
        setNodeTypeMask(SCENE_NODE_MESH);
        this->m_drawCall = new CDrawCall(DRAW_CALL_MESH,
                                         ATTRIBUTE_POSITION_BIT |
                                         ATTRIBUTE_UVS_BIT |
                                         ATTRIBUTE_NORMAL_BIT);
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

fgBool gfx::CSceneNodeMesh::queryTrait(const fg::traits::SceneNode trait, void **pObj) {
    fgBool status = hasTraits(trait);
    status = (fgBool)(status && (pObj != NULL));
    if(status) {
        if(trait & drawable_type::SELF_TRAIT) {
            *pObj = static_cast<drawable_type*>(this);
        } else {
            status = FG_FALSE;
        }
    }
    if(!status) {
        status = base_type::queryTrait(trait, pObj);
    }
    return status;
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeMesh::animate(float delta) {
    SSkinnedMesh *pSkinnedMesh = getSkinnedMesh();
    if(!pSkinnedMesh)
        return;
    animated_type::AnimationsVec& animations = getAnimations();
    if(animations.empty())
        return;
    const unsigned int nAnimations = animations.size();
    for(unsigned int animId = 0; animId < nAnimations; animId++) {
        anim::SAnimationInfo &animationInfo = animations[animId];
        // calculate will check if animation is compatible
        pSkinnedMesh->calculate(animationInfo, delta);
    }
    // Base function version will merge all compatible animations into one.
    // Merged animations can be retrieved by their type.
    // Bone animations can be applied only to skinned mesh.
    // Node animations contain only one transformation which is the final model
    // matrix used to transform the node. This matrix is simply copied into
    // m_modelMatrix. NOTE: Node transformation matrix is relative to the parent.
    base_type::animate(delta);
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeMesh::draw(const Matrix4f& modelMat) {
    if(!isVisible() || !m_drawCall)
        return;
    animated_type::AnimationsVec& animations = getAnimations();
    const unsigned int nAnimations = animations.size();
    // should now use shader, check flags and push uniforms
    CShaderProgram* pProgram = m_drawCall->getShaderProgram();
    if(pProgram && nAnimations) {
        pProgram->use();
            // the index of animation should not be zero...
            pProgram->setUniform(shaders::UNIFORM_BONE_DUAL_QUATERNIONS,
                                 animations[0].curFrame.dualQuaternions);
        }
    }
    m_drawCall->draw(math::scale(m_finalModelMat, getScale()) * modelMat);
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeMesh::updateAABB(void) {
#if 0
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
#endif
    if(m_pMesh) {
        if(!m_pMesh->isSkinnedMesh()) {
            m_aabb.min = m_pMesh->aabb.min;
            m_aabb.max = m_pMesh->aabb.max;
            m_aabb.transform(m_finalModelMat, m_scale);
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
                                                              info.curFrame.dualQuaternions,
                                                              min, max);
                    m_aabb.merge(min);
                    m_aabb.merge(max);
                }
                if(info.pAnimation->getType() == anim::Type::BONE);
                //break; // #FIXME - this seriously need to be better
                // also would really need some method in base class
                // that updates the aabb based on the children size
                // but too soon for that !TODO
            }
            m_aabb.transform(m_finalModelMat, m_scale);
        }
        //if(body && !isAutoScale()) {
        //    m_aabb.radius = body->getRadius();
        //} else {
        m_aabb.radius = math::length(m_aabb.getExtent());
        //}
    }
}
//------------------------------------------------------------------------------
