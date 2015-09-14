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
 * File:   fgGFXSceneNodeObject.cpp
 * Author: vigilant
 * 
 * Created on November 12, 2014, 6:08 PM
 */

#include "fgGfxSceneNodeObject.h"
#include "fgGfxSceneNodeMesh.h"
#include "fgGfxSceneManager.h"
#include "GFX/Shaders/fgGfxShaderManager.h"
#include "GFX/Animation/fgGfxAnimation.h"
#include "GFX/fgGfxModelResource.h"
#include "GFX/fgGfxSkinnedMesh.h"
#include "Util/fgStrings.h"
#include "fgLog.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::CSceneNodeObject::CSceneNodeObject(CModelResource* pModel, gfx::CSceneNode* pParent) :
CSceneNode(SCENE_NODE_OBJECT, pParent),
m_pModel(NULL) {
    CSceneNode::setNodeType(SCENE_NODE_OBJECT);
    // Now need to reset the draw call - this is object based on model
    // it has multiple children - they have their own draw calls
    // One drawcall for model/object is not needed - remove it just in case
    // -> Corresponding draw calls are managed via extending classes
    // GfxSceneNode is a base class however it is not abstract - so special
    // purpose SceneNode can be set externally - no within some kind of constructor
    // Scene node has special type id for that - scene node custom *
    if(m_drawCall)
        delete m_drawCall;
    m_drawCall = NULL;
    setModel(pModel);
}
//------------------------------------------------------------------------------

gfx::CSceneNodeObject::CSceneNodeObject(const CSceneNodeObject& orig) : base_type(orig) {
    if(this != &orig) {
        this->m_drawCall = NULL;
        this->setModel(orig.getModel());
        this->setNodeType(SCENE_NODE_OBJECT);
    }
}
//------------------------------------------------------------------------------

gfx::CSceneNodeObject::~CSceneNodeObject() {
    //FG_LOG_DEBUG("fgGfxSceneNodeObject destructor %s", this->m_nameTag.c_str());
    // Well there's no need to remove children from this destructor
    // The base class destructor (SceneNode) will take care of that
    m_drawCall = NULL;
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeObject::refreshGfxInternals(void) {
    if(!m_pManager)
        return;
    if(m_pManager->getManagerType() != FG_MANAGER_SCENE) {
        return;
    }
    //CSceneManager *pSceneMgr = static_cast<CSceneManager *>(m_pManager);
    if(!m_pModel) {
        return;
    }
    m_pModel->genBuffers();
    SMaterial* pMainMaterial = m_pModel->getMainMaterial();
    CModel::ShapesVecItor sit = m_pModel->getShapes().begin(),
            send = m_pModel->getShapes().end();

    for(; sit != send; sit++) {
        if(!(*sit))
            continue;
        SShape* pShape = (*sit);
        if(!pShape->material->shaderProgram) {
            pShape->material->shaderProgram = pMainMaterial->shaderProgram;
        }
    }

    ChildrenVecItor it = getChildren().begin(), end = getChildren().end();
    for(; it != end; it++) {
        if(!(*it))
            continue;
        CSceneNode *pChildNode = (*it);
        pChildNode->refreshGfxInternals();
        if(getManager())
            pChildNode->setManager(getManager());
        if(pChildNode->getNodeType() == SCENE_NODE_MESH) {
            CSceneNodeMesh *pMeshNode = static_cast<CSceneNodeMesh *>(pChildNode);
            CDrawCall *pDrawCall = pMeshNode->getDrawCall();
            if(pDrawCall) {
                if(pMainMaterial && !pDrawCall->getMaterial())
                    pDrawCall->setupMaterial(pMainMaterial);
                // #FIXME
                if(pMainMaterial->shaderProgram) {
                    if(!pDrawCall->getShaderProgram())
                        pDrawCall->setShaderProgram(pMainMaterial->shaderProgram);
                }
                //pDrawCall->setTexture()
            }
        }
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeObject::updateAABB(void) {

    physics::CCollisionBody *body = getCollisionBody();
    if(body) {
        if(m_pModel && !isAutoScale()) {
            if(body->getBodyType() == physics::CCollisionBody::SPHERE) {
                body->setRadius(math::length(m_scale * m_pModel->getAABB().getExtent()));
            } else {
                body->setHalfSize(m_scale * (m_pModel->getAABB().getExtent()));
            }
            body->setInertiaTensor();
            body->calculateDerivedData();
        }
        // Well the collision body is present, so the base function can be called
        // it will do the required transformations (based on the physics)
        base_type::updateAABB();
    }
    if(m_pModel) {
        if(!m_pModel->isAnimated()) {
            m_aabb.min = m_pModel->getAABB().min;
            m_aabb.max = m_pModel->getAABB().max;
            m_aabb.transform(m_modelMat);
        } else {
            m_aabb.invalidate();
            // should now just merge with aabb's of the meshes? lol
            // this begins to suck beyond comprehension.
            const unsigned int nChildren = getChildrenCount();
            for(unsigned int childId = 0; childId < nChildren; childId++) {
                CSceneNode* pNode = getChildByIndex(childId);
                if(!pNode)
                    continue;
                if(pNode->getNodeType() != gfx::SCENE_NODE_MESH) {
                    continue;
                }
                CSceneNodeMesh* pNodeMesh = static_cast<CSceneNodeMesh*>(pNode);
                m_aabb.merge(pNodeMesh->getBoundingVolume());
            }
            m_aabb.transform(m_modelMat);
        }
        if(body && !isAutoScale()) {
            m_aabb.radius = body->getRadius();
        } else {
            m_aabb.radius = math::length(m_scale * m_pModel->getAABB().getExtent());
        }
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeObject::setModel(gfx::CModel *pModel) {
    if(pModel) {
        if(m_pModel == pModel) {
            // No need to reinitialize #FIXME
            return;
        }

        m_pModel = pModel;
        setNodeType(SCENE_NODE_OBJECT);
        // Now this object is made of some shapes/meshes
        // they have separate drawcalls so this one (NodeObject) does not
        // need any separate drawcall - just one for every mesh/shape
        // Now setup draw call and children from every shape/mesh from given model
        // -- need some method for quick children removal - all of them
        ChildrenVecItor it = getChildren().begin(), end = getChildren().end();
        for(; it != end; it++) {
            if(!(*it))
                continue;
            // Would need to clear the children list?
        } // SRSLY? #FIXME

        gfx::CModel::ShapesVec &shapes = pModel->getShapes();
        setBoundingVolume(pModel->getAABB());
        gfx::CModel::ShapesVecItor sit = shapes.begin(), send = shapes.end();
        unsigned int sIdx = 0;
        for(; sit != send; sit++) {

            if(!(*sit))
                continue;
            SShape *pShape = (*sit);
            SMeshBase *pMesh = (*sit)->mesh;
            if(!pMesh)
                continue;
            CSceneNode *pChildNode = new CSceneNodeMesh(pMesh, this);
            static_cast<CSceneNodeMesh *>(pChildNode)->setMaterial(pShape->material);
            std::string childName = this->getName();
            sIdx = getChildrenCount() + 1;
            childName.append("_");
            childName.append(pShape->name);
            childName.append("_");
            childName.append(1, (char)('0' + (sIdx / 10)));
            childName.append(1, (char)('0' + (sIdx % 10)));
            pChildNode->setName(childName);

            //pChildNode->getDrawCall()->setupMaterial(pShape->material);
            // Should register it in a manager? #NOPE
            // There is no need to register this NodeMesh - it's immediate child
            // required to do the drawing - however this is about to change
            // What if Object is made from many meshes, +explosion effect,
            // The meshes spread through the scene - need to be managed
            // If so the drawing procedures for object should be empty - not include
            // the children. The children would be drawn via the scene manager/octree
            // #FIXME #P2 #IMPORTANT
            //if(m_pManager) {
            //if(m_pManager->getManagerType() == FG_MANAGER_SCENE) {
            //static_cast<fgGfxSceneManager *>(m_pManager)->addNode(pChildNode->getRefHandle(), pChildNode, this);
            //}
            //}
            // No need to check if it's inserted successfully
            getChildren().push_back(pChildNode);
        }
        /// Maybe some children should not be accessible globally?
        /// Need to think about it - there can be many objects containing the 
        /// same meshes. And they will have the same name ? NOPE
        /// Randomize name tag? oh my... you could work at the coal mine you know?
        /// It would be ... easier?
    }
}
//------------------------------------------------------------------------------

fgBool gfx::CSceneNodeObject::setAnimation(const char* name, unsigned int slot) {
    if(!name)
        return FG_FALSE;
    if(!name[0])
        return FG_FALSE;
    fgBool status = base_type::setAnimation(name, slot);
    if(status) {
        // the base type did not fail - ?
        return FG_TRUE;
    }
    // now this function is quite tricky
    // will need to search for animations inside the armature (if any)
    if(!m_pModel)
        return status;
    if(!m_pModel->isAnimated() || !m_pModel->isRigged())
        return status;
    CModel::AnimationsVec& animations = m_pModel->getAnimations();
    const unsigned int nAnims = animations.size();
    anim::CAnimation* pAnimation = NULL;
    for(unsigned int i = 0; i < nAnims; i++) {
        pAnimation = animations[i];
        if(!pAnimation)
            continue;
        if(pAnimation->getType() != anim::Type::BONE)
            continue;
        if(strings::isEqual(pAnimation->getNameStr(), name, FG_FALSE) ||
           strings::stristr(pAnimation->getNameStr(), name) != NULL) {
            status = FG_TRUE;
            break;
        } else {
            pAnimation = NULL;
        }
    }
    if(pAnimation) {
        // now need to set this for all skinned meshes        
        const unsigned int nChildren = getChildrenCount();
        for(unsigned int childId = 0; childId < nChildren; childId++) {
            CSceneNode* pNode = getChildByIndex(childId);
            if(!pNode)
                continue;
            if(pNode->getNodeType() != gfx::SCENE_NODE_MESH) {
                continue;
            }

            CSceneNodeMesh* pNodeMesh = static_cast<CSceneNodeMesh*>(pNode);
            SSkinnedMesh* pSkinnedMesh = pNodeMesh->getSkinnedMesh();
            if(!pSkinnedMesh)
                continue;
            if(!pSkinnedMesh->isAnimationCompatible(pAnimation))
                continue;
            // animation is found and compatible
            pNodeMesh->setAnimation(pAnimation, slot);
        }
    }
    return status;
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeObject::removeAnimations(void) {
    animated_type::removeAnimations();
    // SceneNodeObject is a special node type
    // when added to the scene, children are added automatically
    // based on the shapes of the model.
    if(!m_pModel)
        return;
    if(!m_pModel->isAnimated())
        return;
    const unsigned int nChildren = getChildrenCount();
    for(unsigned int childId = 0; childId < nChildren; childId++) {
        CSceneNode* pNode = getChildByIndex(childId);
        if(!pNode) {
            continue;
        }
        if(pNode->getNodeType() != SCENE_NODE_MESH) {
            continue;
        }
        CSceneNodeMesh* pNodeMesh = static_cast<CSceneNodeMesh*>(pNode);
        if(!m_pModel->hasMesh(pNodeMesh->getMesh())) {
            continue;
        }
        // now it is know that this mesh node is based on this objects' model;
        // need to remove animations that are also based on this model
        animated_type::AnimationsVec& animations = pNodeMesh->getAnimations();
        unsigned int nAnimations = animations.size();
        for(unsigned int animId = 0; animId < nAnimations; animId++) {
            anim::SAnimationInfo* pInfo = &animations[animId];
            if(m_pModel->hasAnimation(pInfo->pAnimation)) {
                pNodeMesh->removeAnimation(pInfo->pAnimation);
                animId--;
                nAnimations--;
                continue;
            }
        }
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeObject::playAnimations(void) {
    animated_type::playAnimations();
    if(!m_pModel)
        return;
    if(!m_pModel->isAnimated())
        return;
    const unsigned int nChildren = getChildrenCount();
    for(unsigned int childId = 0; childId < nChildren; childId++) {
        CSceneNode* pNode = getChildByIndex(childId);
        if(!pNode) {
            continue;
        }
        if(pNode->getNodeType() != SCENE_NODE_MESH) {
            continue;
        }
        CSceneNodeMesh* pNodeMesh = static_cast<CSceneNodeMesh*>(pNode);
        if(!m_pModel->hasMesh(pNodeMesh->getMesh())) {
            continue;
        }
        animated_type::AnimationsVec& animations = pNodeMesh->getAnimations();
        const unsigned int nAnimations = animations.size();
        for(unsigned int animId = 0; animId < nAnimations; animId++) {
            anim::SAnimationInfo* pInfo = &animations[animId];
            if(m_pModel->hasAnimation(pInfo->pAnimation)) {
                pInfo->play();
                break;
            }
        }
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeObject::stopAnimations(void) {
    animated_type::stopAnimations();
    if(!m_pModel)
        return;
    if(!m_pModel->isAnimated())
        return;
    const unsigned int nChildren = getChildrenCount();
    for(unsigned int childId = 0; childId < nChildren; childId++) {
        CSceneNode* pNode = getChildByIndex(childId);
        if(!pNode) {
            continue;
        }
        if(pNode->getNodeType() != SCENE_NODE_MESH) {
            continue;
        }
        CSceneNodeMesh* pNodeMesh = static_cast<CSceneNodeMesh*>(pNode);
        if(!m_pModel->hasMesh(pNodeMesh->getMesh())) {
            continue;
        }
        animated_type::AnimationsVec& animations = pNodeMesh->getAnimations();
        const unsigned int nAnimations = animations.size();
        for(unsigned int animId = 0; animId < nAnimations; animId++) {
            anim::SAnimationInfo* pInfo = &animations[animId];
            if(m_pModel->hasAnimation(pInfo->pAnimation)) {
                pInfo->stop();
                break;
            }
        }
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeObject::pauseAnimations(fgBool toggle) {
    animated_type::pauseAnimations();
    if(!m_pModel)
        return;
    if(!m_pModel->isAnimated())
        return;
    const unsigned int nChildren = getChildrenCount();
    for(unsigned int childId = 0; childId < nChildren; childId++) {
        CSceneNode* pNode = getChildByIndex(childId);
        if(!pNode) {
            continue;
        }
        if(pNode->getNodeType() != SCENE_NODE_MESH) {
            continue;
        }
        CSceneNodeMesh* pNodeMesh = static_cast<CSceneNodeMesh*>(pNode);
        if(!m_pModel->hasMesh(pNodeMesh->getMesh())) {
            continue;
        }
        animated_type::AnimationsVec& animations = pNodeMesh->getAnimations();
        const unsigned int nAnimations = animations.size();
        for(unsigned int animId = 0; animId < nAnimations; animId++) {
            anim::SAnimationInfo* pInfo = &animations[animId];
            if(m_pModel->hasAnimation(pInfo->pAnimation)) {
                if(toggle) {
                    pInfo->togglePause();
                } else {
                    pInfo->pause();
                }
                continue;
            }
        }
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeObject::resumeAnimations(void) {
    animated_type::resumeAnimations();
    if(!m_pModel)
        return;
    if(!m_pModel->isAnimated())
        return;
    const unsigned int nChildren = getChildrenCount();
    for(unsigned int childId = 0; childId < nChildren; childId++) {
        CSceneNode* pNode = getChildByIndex(childId);
        if(!pNode) {
            continue;
        }
        if(pNode->getNodeType() != SCENE_NODE_MESH) {
            continue;
        }
        CSceneNodeMesh* pNodeMesh = static_cast<CSceneNodeMesh*>(pNode);
        if(!m_pModel->hasMesh(pNodeMesh->getMesh())) {
            continue;
        }
        animated_type::AnimationsVec& animations = pNodeMesh->getAnimations();
        const unsigned int nAnimations = animations.size();
        for(unsigned int animId = 0; animId < nAnimations; animId++) {
            anim::SAnimationInfo* pInfo = &animations[animId];
            if(m_pModel->hasAnimation(pInfo->pAnimation)) {
                pInfo->resume();
                continue;
            }
        }
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeObject::rewindAnimations(void) {
    animated_type::rewindAnimations();
    if(!m_pModel)
        return;
    if(!m_pModel->isAnimated())
        return;
    const unsigned int nChildren = getChildrenCount();
    for(unsigned int childId = 0; childId < nChildren; childId++) {
        CSceneNode* pNode = getChildByIndex(childId);
        if(!pNode) {
            continue;
        }
        if(pNode->getNodeType() != SCENE_NODE_MESH) {
            continue;
        }
        CSceneNodeMesh* pNodeMesh = static_cast<CSceneNodeMesh*>(pNode);
        if(!m_pModel->hasMesh(pNodeMesh->getMesh())) {
            continue;
        }
        animated_type::AnimationsVec& animations = pNodeMesh->getAnimations();
        const unsigned int nAnimations = animations.size();
        for(unsigned int animId = 0; animId < nAnimations; animId++) {
            anim::SAnimationInfo* pInfo = &animations[animId];
            if(m_pModel->hasAnimation(pInfo->pAnimation)) {
                pInfo->rewind();
                continue;
            }
        }
    }
}
//------------------------------------------------------------------------------
