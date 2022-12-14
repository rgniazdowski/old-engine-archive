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
#include "GFX/fgGfxSkinnedMesh.h"
#include "GFX/fgGfxShape.h"
#include "GFX/Animation/fgGfxAnimation.h"
#include "GFX/Animation/fgGfxBlending.h"
#include "Math/fgMatrixOperations.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::CSceneNodeMesh::CSceneNodeMesh(SMeshBase *pMesh, CSceneNode *pParent) :
base_type(SCENE_NODE_MESH, pParent),
drawable_type(),
m_pMesh(NULL),
m_pMaterial(NULL) {
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

fgBool gfx::CSceneNodeMesh::isSkinnedMesh(void) const {
    if(!m_pMesh)
        return FG_FALSE;
    return m_pMesh->isSkinnedMesh();
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
    unsigned int nBoneAnims = 0;
    int nFirstId = -1;
    const unsigned int nAnimations = animations.size();
    for(unsigned int animId = 0; animId < nAnimations; animId++) {
        anim::SAnimationInfo &animationInfo = animations[animId];
        // calculate will check if animation is compatible
        // #FIXME - this will recalculate animation step if the model has
        // two or more shapes with the same animation - need to check it somehow
        if(animationInfo.pAnimation->getType() == anim::Type::BONE ||
           animationInfo.pAnimation->getType() == anim::Type::BONE_RAGDOLL) {
            pSkinnedMesh->calculate(animationInfo, delta);
            nBoneAnims++;
            if(nBoneAnims == 1)
                nFirstId = (int)animId;
        }
    }
    // Base function version will merge all compatible animations into one.
    // Merged animations can be retrieved by their type.
    // Bone animations can be applied only to skinned mesh.
    // Node animations contain only one transformation which is the final model
    // matrix used to transform the node. This matrix is simply copied into
    // m_modelMatrix. NOTE: Node transformation matrix is relative to the parent.
    base_type::animate(delta);

    // Now for merging part
    if(nBoneAnims > 1) {
        anim::SAnimationFrameInfo* pInfo =
                animated_type::prepareBlendedFrame(anim::Type::BONE);
        const anim::SBlendingInfo& pBlendInfo = pSkinnedMesh->blendingInfo;

        int blendCount = anim::blendAnimations(animations,
                                               anim::Type::BONE,
                                               pBlendInfo,
                                               pInfo);
        if(!blendCount)
            animated_type::setFinalDQs(&animations[nFirstId].curFrame.dualQuaternions);
        else
            animated_type::setFinalDQs(&pInfo->dualQuaternions);

    } else if(nBoneAnims == 1) {
        animated_type::setFinalDQs(&animations[nFirstId].curFrame.dualQuaternions);
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeMesh::draw(const Matrix4f& modelMat) {
    if(!isVisible() || !m_drawCall)
        return;
    // should now use shader, check flags and push uniforms
    CShaderProgram* pProgram = m_drawCall->getShaderProgram();
    if(pProgram) {
        pProgram->use();
        if(animated_type::getFinalDQs()) {
            pProgram->setUniform(shaders::UNIFORM_BONE_DUAL_QUATERNIONS,
                                 *animated_type::getFinalDQs());
        }
    }
    m_drawCall->draw(math::scale(m_finalModelMat, getFinalScale()) * modelMat);
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeMesh::updateAABB(void) {
    if(!m_pMesh) {
        return;
    }
    if(!m_pMesh->isSkinnedMesh()) {
        m_aabb.min = m_pMesh->aabb.min;
        m_aabb.max = m_pMesh->aabb.max;
        m_aabb.transform(m_finalModelMat, m_scale);
    } else {
        SSkinnedMesh *pSkinnedMesh = this->getSkinnedMesh();
        m_aabb.invalidate();
        if(animated_type::getFinalDQs()) {            
            unsigned int nBones = pSkinnedMesh->boneEdges.size();
            for(unsigned int boneId = 0; boneId < nBones; boneId++) {
                Vec3f min, max;
                pSkinnedMesh->boneEdges[boneId].transform(pSkinnedMesh,
                                                          *animated_type::getFinalDQs(),
                                                          min, max);
                m_aabb.merge(min);
                m_aabb.merge(max);
            }
            m_aabb.transform(m_finalModelMat, m_scale);            
        }        
    }
    m_aabb.radius = math::length(m_aabb.getExtent());
}
//------------------------------------------------------------------------------
