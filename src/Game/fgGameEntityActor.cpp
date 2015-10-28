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
 * File:   fgGameEntityActor.cpp
 * Author: vigilant
 *
 * Created on October 12, 2015, 11:13 PM
 */

#include "fgGameEntityActor.h"

#include "GFX/fgGfxModelResource.h"
#include "GFX/Animation/fgGfxArmature.h"
#include "GFX/Animation/fgGfxRagdollBoneAnimation.h"
#include "Physics/fgPhysics.h"
#include "GFX/Scene/fgGfxSceneNodeMesh.h"
#include <stack>

using namespace fg;
//------------------------------------------------------------------------------

game::CEntityActor::CEntityActor(gfx::CModelResource* pModel,
                                 gfx::CSceneNode* pParent) :
base_type(NULL, pParent),
physical_type(),
m_ragdollAnimation(NULL) {
    setNodeType(self_type::SELF_ENTITY_TYPE);
    setNodeTypeMask(self_type::SELF_ENTITY_TYPE);
    setNodeTrait(physical_type::SELF_TRAIT);
    // now will need to set model and collision body type
    // also depending on model type - ragdoll body

    // not GAME_ENTITY_MESH
    base_type::setDefaultMeshChildType(gfx::SCENE_NODE_MESH);
    this->setModel(pModel);
    // NOTE: presence of physical trait does not imply usage of collision body...
}
//------------------------------------------------------------------------------

game::CEntityActor::CEntityActor(const self_type& orig) : base_type(orig), physical_type() {
    setNodeType(self_type::SELF_ENTITY_TYPE);
    setNodeTypeMask(self_type::SELF_ENTITY_TYPE);
    setNodeTrait(physical_type::SELF_TRAIT);
    base_type::setDefaultMeshChildType(gfx::SCENE_NODE_MESH);
    // need a little hack here...
    //gfx::CModelResource* pModel = orig.getModel();
    //*((base_type*)this) = *((base_type*)&orig);
}
//------------------------------------------------------------------------------

game::CEntityActor::~CEntityActor() { }
//------------------------------------------------------------------------------

fgBool game::CEntityActor::queryTrait(const fg::traits::SceneNode trait, void **pObj) {
    fgBool status = hasTraits(trait);
    status = (fgBool)(status && (pObj != NULL));
    if(status) {
        if(trait & physical_type::SELF_TRAIT) {
            *pObj = static_cast<physical_type*>(this);
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

void game::CEntityActor::setModel(gfx::CModelResource* pModel) {
    if(!pModel)
        return;
    // using low-level type for mesh children - these do not have physical properties
    // they are not needed as this class contains physical traits designed for ragdolls
    base_type::setDefaultMeshChildType(gfx::SCENE_NODE_MESH);
    // rigged means that this model contains bones information
    if(!pModel->isRigged() || !pModel->getArmature()) {
        // ignore not rigged models - this entity type is for animated characters (mostly)
        // cars or other (non-humanoid) objects can also be rigged for animation
        return;
    }
    base_type::setModel(pModel);

    gfx::anim::CArmature* pArmature = pModel->getArmature();
    physical_type::setupCollisionBody(physics::BODY_RAGDOLL);
    if(!physical_type::isRagdoll())
        return;
    physics::CRagdollCollisionBody* pRagdoll = physical_type::getRagdollCollisionBody();
    pRagdoll->stopRagdolling(); // just in case
    typedef CVector<physics::SBoneSmallInfo> BonesInfoVec;
    typedef std::stack<gfx::anim::SBone*> stack_type;
    BonesInfoVec bonesInfo;
    // now need to get list of all non-leaf bones (also excluding Armature & ArmatureRoot)
    gfx::anim::SBone* pRoot = pArmature->get("Armature");
    if(!pRoot)
        return;
    stack_type stack;
    stack.push(pRoot);
    while(!stack.empty()) {
        gfx::anim::SBone* pBone = stack.top();
        stack.pop();
        if(!pBone)
            continue;
        if(pBone->hasChildren()) {
            for(int i = pBone->count() - 1; i >= 0; i--) {
                // will not add leaf bones... no need
                if(pBone->children[i]->hasChildren())
                    stack.push(pBone->children[i]);
            }
        }
        if(pBone == pRoot)
            continue;
        bonesInfo.push_back(pBone->getBoneSmallInfo());
    } // while stack not empty

    if(m_ragdollAnimation) {
        this->removeAnimation(m_ragdollAnimation);
        delete m_ragdollAnimation;
    }
    //--------------------------------
    if(!pRagdoll->initializeFrom(bonesInfo, pArmature->count())) {
        // FAIL!
        return;
    }
    m_ragdollAnimation = new gfx::anim::CRagdollBoneAnimation(pArmature);
    m_ragdollAnimation->setModelMatrix(&m_finalModelMat);
    const unsigned int nArmatureBones = pArmature->count();
    for(unsigned int i = 0; i < nArmatureBones; i++) {
        // Some of this pointers will always be NULL -- however it is important
        // that indexes in universal transforms array match the ones in armature,
        // not the ones in skinned mesh (which may use only a subset of non-leaf bones).
        m_ragdollAnimation->setTransform(i, pRagdoll->getUniversalTransform(i));
        // UniversalTransform is special abstract wrapper - allows quick access
        // to up-to-date transformation
    }
}
//------------------------------------------------------------------------------

fgBool game::CEntityActor::copyAnimationToRagdoll(gfx::anim::SAnimationInfo* pInfo,
                                                  const gfx::SSkinnedMesh::BonesVec& bones) {
    if(!pInfo)
        return FG_FALSE;
    if(!pInfo->pAnimation)
        return FG_FALSE;
    if(bones.empty())
        return FG_FALSE;
    physics::CRagdollCollisionBody* pBody = getRagdollCollisionBody();
    if(!pBody)
        return FG_FALSE;
    // get transformations of each bone from currently active animation (if any)
    // active animations are stored for each mesh (because given mesh can be affected
    // by different set of bones).
    // #FIXME - This will need quite fixing - for now just select first child mesh

    // Need armature bone indexes
    const unsigned int nBones = bones.size();
    for(unsigned int i = 0; i < nBones; i++) {
        gfx::anim::SBone* pBone = bones[i];
        if(!pBone)
            continue;
        // should invert by bone offset?
        pBody->setInitialTransform(pBone->index,
                                   math::scale(pInfo->curFrame.transformations[i] * math::inverse(pBone->offset), pBone->getOffsetScale()));
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void game::CEntityActor::startRagdolling(void) {
    if(isRagdolling()) //&& this->getAnimation((unsigned int)0)->getType() == gfx::anim::Type::BONE_RAGDOLL)
        return; // ignore;
    fgBool status = FG_FALSE;
    ChildrenVec& children = this->getChildren();
    const unsigned int n = children.size();
    if(isRagdoll()) {
        //if(this->setAnimation(m_ragdollAnimation, 0)) {
        //    this->getAnimationInfoBySlot(0)->play(); // activate
        //}
        physics::CRagdollCollisionBody* pBody = getRagdollCollisionBody();
        pBody->setModelMatrix(this->getFinalModelMatrix());
        //pBody->

        for(unsigned int i = 0; i < n; i++) {
            CSceneNode* pChild = children[i];
            if(!pChild->checkNodeType(gfx::SCENE_NODE_MESH))
                continue;
            copyAnimationToRagdoll(pChild->getAnimationInfoBySlot(0),
                                   static_cast<gfx::CSceneNodeMesh*>(pChild)->getSkinnedMesh()->bones);
            break; // ooops! #FIXME need to get merged animation and list of bones
        }
        pBody->startRagdolling();
#if 0
        btVector3 deathV;
        deathV.setX(-150.0f);
        deathV.setY(300.0f);
        deathV.setZ(-1500.0f);
        pBody->getBoneBodies()[0]->applyCentralImpulse(deathV);
        pBody->getBoneBodies()[1]->applyCentralImpulse(deathV);
        pBody->getBoneBodies()[2]->applyCentralImpulse(deathV);
        //pBody->getBoneBodies()[3]->applyCentralImpulse(btVector3(deathV.x, deathV.y, deathV.z));
        //pBody->getBoneBodies()[4]->applyCentralImpulse(btVector3(deathV.x, deathV.y, deathV.z));

        pBody->getBoneBodies()[8]->applyCentralImpulse(deathV);
        pBody->getBoneBodies()[9]->applyCentralImpulse(deathV);
        pBody->getBoneBodies()[10]->applyCentralImpulse(deathV);
        pBody->getBoneBodies()[11]->applyCentralImpulse(deathV);
#endif
        status = pBody->isRagdolling();
    }
    if(!status)
        return;


    for(unsigned int i = 0; i < n; i++) {
        CSceneNode* pChild = children[i];
        if(!pChild->checkNodeType(gfx::SCENE_NODE_MESH))
            continue;
        pChild->removeAnimations();
        pChild->setAnimation(m_ragdollAnimation, 0);
        pChild->getAnimationInfoBySlot(0)->play();
    }
}
//------------------------------------------------------------------------------

void game::CEntityActor::stopRagdolling(void) {
    if(isRagdoll()) {
        getRagdollCollisionBody()->stopRagdolling();
        this->removeAnimation(m_ragdollAnimation);
        ChildrenVec& children = this->getChildren();
        const unsigned int n = children.size();
        for(unsigned int i = 0; i < n; i++) {
            CSceneNode* pChild = children[i];
            if(!pChild->checkNodeType(gfx::SCENE_NODE_MESH))
                continue;
            pChild->removeAnimation(m_ragdollAnimation);
        }
    }
}
//------------------------------------------------------------------------------

fgBool game::CEntityActor::isRagdolling(void) const {
    if(!isRagdoll())
        return FG_FALSE;
    return getRagdollCollisionBody()->isRagdolling();
}
//------------------------------------------------------------------------------

fgBool game::CEntityActor::setupCollisionBody(physics::BodyType bodyType) {
    // need to detect here if body is changing - or just assume that it is anyway
    if(m_ragdollAnimation) {
        m_ragdollAnimation->getUniversalTransforms().clear();
        m_ragdollAnimation->getUniversalTransforms().resize(m_ragdollAnimation->getArmature()->count(), NULL);
    }
    fgBool status = physical_type::setupCollisionBody(bodyType);
    if(m_ragdollAnimation && physical_type::isRagdoll()) {
        physics::CRagdollCollisionBody* pRagdoll = physical_type::getRagdollCollisionBody();
        const unsigned int nArmatureBones = m_ragdollAnimation->getArmature()->count();
        for(unsigned int i = 0; i < nArmatureBones; i++) {
            m_ragdollAnimation->setTransform(i, pRagdoll->getUniversalTransform(i));
        }
    }
    return status;
}
//------------------------------------------------------------------------------

void game::CEntityActor::updateAABB(void) {
    base_type::updateAABB();
    if(isRagdolling()) {
        Matrix4f pelvisMatrix;
        physical_type::getRagdollCollisionBody()->getBoneBodies()[0]->getWorldTransform(pelvisMatrix);
        float pelvisOffset = (-1.0f) * physical_type::getRagdollCollisionBody()->getBonesInfo()[0].length / 2.0f;
        pelvisMatrix = math::translate(pelvisMatrix, Vec3f(0.0f, pelvisOffset, 0.0f));

        m_modelMat = math::inverse(getParent()->getFinalModelMatrix()) * pelvisMatrix;
    }
}
//------------------------------------------------------------------------------
