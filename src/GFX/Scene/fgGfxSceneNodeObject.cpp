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
#include "fgGfxNodeFactory.h"
#include "GFX/Shaders/fgGfxShaderManager.h"
#include "GFX/Animation/fgGfxAnimation.h"
#include "GFX/fgGfxModelResource.h"
#include "GFX/fgGfxSkinnedMesh.h"
#include "Util/fgStrings.h"
#include "fgLog.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::CSceneNodeObject::CSceneNodeObject(CModelResource* pModel, gfx::CSceneNode* pParent) :
base_type(SCENE_NODE_OBJECT, pParent),
m_pModel(NULL),
m_defaultMeshChildType(SCENE_NODE_MESH) {
    // Now need to reset the draw call - this is object based on model
    // it has multiple children - they have their own draw calls
    // One drawcall for model/object is not needed - remove it just in case
    // -> Corresponding draw calls are managed via extending classes
    // GfxSceneNode is a base class however it is not abstract - so special
    // purpose SceneNode can be set externally - no within some kind of constructor
    // Scene node has special type id for that - scene node custom *
    setModel(pModel);
    setNodeTypeMask(SCENE_NODE_OBJECT);
}
//------------------------------------------------------------------------------

gfx::CSceneNodeObject::CSceneNodeObject(const CSceneNodeObject& orig) : base_type(orig) {
    if(this != &orig) {
        this->setName(orig.getName());
        this->getName().append("_copy");
        this->setModel(orig.getModel());
        this->setNodeType(SCENE_NODE_OBJECT);
        this->setNodeTypeMask(SCENE_NODE_OBJECT);
        this->setDefaultMeshChildType(orig.getDefaultMeshChildType());
    }
}
//------------------------------------------------------------------------------

gfx::CSceneNodeObject::~CSceneNodeObject() {
    // Well there's no need to remove children from this destructor
    // The base class destructor (SceneNode) will take care of that
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
        if(!pChildNode->checkNodeType(SCENE_NODE_MESH)) {
            continue;
        }
        CSceneNodeMesh *pMeshNode = static_cast<CSceneNodeMesh *>(pChildNode);
        CDrawCall *pDrawCall = pMeshNode->getDrawCall();
        if(!pDrawCall) {
            continue;
        }
        if(pMainMaterial && !pDrawCall->getMaterial())
            pDrawCall->setupMaterial(pMainMaterial);
        // #FIXME
        if(pMainMaterial->shaderProgram) {
            if(!pDrawCall->getShaderProgram())
                pDrawCall->setShaderProgram(pMainMaterial->shaderProgram);
        }
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeObject::updateAABB(void) {
#if 0
    physics::CCollisionBody *body = getCollisionBody();
    if(body) {
        if(m_pModel && !isAutoScale()) {
            if(body->getBodyType() == physics::CCollisionBody::BODY_SPHERE) {
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
#endif 
    if(m_pModel) {
        if(!m_pModel->isAnimated()) {
            m_aabb.min = m_pModel->getAABB().min;
            m_aabb.max = m_pModel->getAABB().max;
            m_aabb.transform(m_finalModelMat, m_scale);
        } else {
            m_aabb.invalidate();
            // should now just merge with aabb's of the meshes? lol
            // this begins to suck beyond comprehension.
            const unsigned int nChildren = getChildrenCount();
            for(unsigned int childId = 0; childId < nChildren; childId++) {
                CSceneNode* pNode = getChildByIndex(childId);
                if(!pNode)
                    continue;
                if(!pNode->checkNodeType(gfx::SCENE_NODE_MESH)) {
                    continue;
                }
                CSceneNodeMesh* pNodeMesh = static_cast<CSceneNodeMesh*>(pNode);
                m_aabb.merge(pNodeMesh->getBoundingVolume());
            }
        }
        //if(body && !isAutoScale()) {
        //    m_aabb.radius = body->getRadius();
        //} else {
        m_aabb.radius = math::length(m_aabb.extent);
        //}
    }
}
//------------------------------------------------------------------------------

void gfx::CSceneNodeObject::setModel(gfx::CModel *pModel) {
    if(!pModel) {
        return;
    }
    if(m_pModel == pModel) {
        // No need to reinitialize #FIXME
        return;
    }
    CSceneManager *pSceneMgr = NULL;
    if(m_pManager) {
        if(m_pManager->getManagerType() == FG_MANAGER_SCENE)
            pSceneMgr = static_cast<CSceneManager *>(m_pManager);
    }
    m_pModel = pModel;
    // Now this object is made of some shapes/meshes
    // they have separate drawcalls so this one (NodeObject) does not
    // need any separate drawcall - just one for every mesh/shape
    // Now setup draw call and children from every shape/mesh from given model
    // -- need some method for quick children removal - all of them
    gfx::CModel::ShapesVec oldShapes;
    oldShapes.reserve(getChildrenCount());
    ChildrenVecItor it = getChildren().begin(), end = getChildren().end();
    for(; it != end; it++) {
        if(!(*it))
            continue;
        CSceneNode* pNode = (*it);
        if(!pNode->checkNodeType(SCENE_NODE_MESH)/* ||
           !pNode->checkNodeType(m_defaultMeshChildType)*/) {
            // no need to check
            continue;
        }
        CSceneNodeMesh* pNodeMesh = static_cast<CSceneNodeMesh*>(pNode);
        if(!pModel->hasMesh(pNodeMesh->getMesh())) {
            continue;
        }
        oldShapes.push_back(pModel->getShape(pNodeMesh->getMesh()));
        if(!pNodeMesh->isManaged() && isManaged()) {
            // if child node is not managed, can add it
            // .. .. merging
            if(pSceneMgr) {
                pSceneMgr->addNode(pNodeMesh->getRefHandle(), pNodeMesh, this);
            }
        }
    } // for every child in this node

    gfx::CModel::ShapesVec &shapes = pModel->getShapes();
    setBoundingVolume(pModel->getAABB());
    gfx::CModel::ShapesVecItor sit = shapes.begin(), send = shapes.end();
    unsigned int sIdx = 0;
    for(; sit != send; sit++) {
        sIdx = getChildrenCount() + 1;
        if(!(*sit))
            continue;
        SShape* pShape = (*sit);
        SMeshBase* pMesh = (*sit)->mesh;
        if(!pMesh)
            continue;
        if(oldShapes.contains(pShape)) {
            continue; // there is already a child with this idx
        }
        // will need to access node factory here
        // node factory is accessible from manager level
        // so this can only work when node is already managed
        CSceneNode *pChildNode = NULL;
        if(pSceneMgr) {
            CNodeFactory *pNodeFactory = pSceneMgr->getNodeFactory();
            if(pNodeFactory)
                pChildNode = pNodeFactory->create(m_defaultMeshChildType);
        }
        if(pChildNode) {
            // need to check whether or not created node is valid
            // this can only happen when defaultMeshChildType is wrong...
            if(!pChildNode->doesExtend(SCENE_NODE_MESH)) {
                // this node does not extend mesh sub-type
                delete pChildNode;
                pChildNode = NULL;
            } else {
                // does extend
                pChildNode->setParent(this);
                pChildNode->setManager(m_pManager);
                static_cast<CSceneNodeMesh *>(pChildNode)->setMesh(pMesh);
            }
        }
        if(!pChildNode) {
            pChildNode = new CSceneNodeMesh(pMesh, this);
        }
        static_cast<CSceneNodeMesh *>(pChildNode)->setMaterial(pShape->material);
        std::string childName = this->getName();
        childName.append("_");
        childName.append(pShape->name);
        childName.append("_");
        childName.append(1, (char)('0' + (sIdx / 10)));
        childName.append(1, (char)('0' + (sIdx % 10)));
        pChildNode->setName(childName);

        // Should register it in a manager? #NOPE
        // There is no need to register this NodeMesh - it's immediate child
        // required to do the drawing - however this is about to change
        // What if Object is made from many meshes, +explosion effect,
        // The meshes spread through the scene - need to be managed
        // If so the drawing procedures for object should be empty - not include
        // the children. The children would be drawn via the scene manager/octree
        // #FIXME #P2 #IMPORTANT
        if(pSceneMgr && isManaged()) {
            // add children to the manager only when this node is managed
            // pointer to the manager can be set also when the node is not yet
            // in the manager
            pSceneMgr->addNode(pChildNode->getRefHandle(), pChildNode, this);
        } else {
            // FALLBACK
            // No need to check if it's inserted successfully
            getChildren().push_back(pChildNode);
        }
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
            if(!pNode->checkNodeType(gfx::SCENE_NODE_MESH)) {
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
        if(!pNode->checkNodeType(gfx::SCENE_NODE_MESH)) {
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
        if(!pNode->checkNodeType(gfx::SCENE_NODE_MESH)) {
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
        if(!pNode->checkNodeType(gfx::SCENE_NODE_MESH)) {
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
        if(!pNode->checkNodeType(gfx::SCENE_NODE_MESH)) {
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
        if(!pNode->checkNodeType(gfx::SCENE_NODE_MESH)) {
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
        if(!pNode->checkNodeType(gfx::SCENE_NODE_MESH)) {
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
            }
        }
    }
}
//------------------------------------------------------------------------------
