/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXSceneNodeObject.cpp
 * Author: vigilant
 * 
 * Created on November 12, 2014, 6:08 PM
 */

#include "fgGFXSceneNodeObject.h"
#include "fgGFXSceneNodeMesh.h"
#include "fgGFXSceneManager.h"

/**
 * 
 */
fgGfxSceneNodeObject::fgGfxSceneNodeObject(fgGfxModel *pModel, fgGfxSceneNode *pParent) :
fgGfxSceneNode(FG_GFX_SCENE_NODE_OBJECT, pParent) {
    fgGfxSceneNode::setNodeType(FG_GFX_SCENE_NODE_OBJECT);
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

/**
 * 
 * @param orig
 */
fgGfxSceneNodeObject::fgGfxSceneNodeObject(const fgGfxSceneNodeObject& orig) { }

/**
 * 
 */
fgGfxSceneNodeObject::~fgGfxSceneNodeObject() {
    // Well there's no need to remove children from this destructor
    // The base class destructor (SceneNode) will take care of that
}

/**
 * 
 * @param pModel
 */
void fgGfxSceneNodeObject::setModel(fgGfxModel *pModel) {
    if(pModel) {
        if(m_pModel == pModel) {
            // No need to reinitialize #FIXME
            return;
        }
        m_pModel = pModel;
        setNodeType(FG_GFX_SCENE_NODE_OBJECT);
        // Now this object is made of some shapes/meshes
        // they have separate drawcalls so this one (NodeObject) does not
        // need any separate drawcall - just one for every mesh/shape
        if(m_drawCall) {
            delete m_drawCall;
            m_drawCall = NULL;
            // this is not needed
        }
        // Now setup draw call and children from every shape/mesh from given model
        // -- need some method for quick children removal - all of them
        childrenSetItor it = getChildren().begin(), end = getChildren().end();
        for(; it != end; it++) {
            if(!(*it))
                continue;
            // Would need to clear the children list?
        } // SRSLY? #FIXME

        fgGfxModel::modelShapes &shapes = pModel->getRefShapes();
        fgGfxModel::modelShapesItor sit = shapes.begin(), send = shapes.end();
        for(; sit != send; sit++) {
            if(!(*sit))
                continue;
            fgGfxMeshBase *pMesh = (*sit)->mesh;
            if(!pMesh)
                continue;
            fgGfxSceneNode *pChildNode = new fgGfxSceneNodeMesh(pMesh, this);
            // Should register it in a manager?
            if(m_pManager) {
                if(m_pManager->getManagerType() == FG_MANAGER_SCENE) {
                    //static_cast<fgGfxSceneManager *>(m_pManager)->addNode(pChildNode->getRefHandle(), pChildNode, this);
                }
            }
            // No need to check if it's inserted successfully
            getChildren().insert(pChildNode);
        }
        /// Maybe some children should not be accessible globally?
        /// Need to think about it - there can be many objects containing the 
        /// same meshes. And they will have the same name ? NOPE
        /// Randomize name tag? oh my... you could work at the coal mine you know?
        /// It would be ... easier?
    }
}
