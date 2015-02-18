/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXSceneNodeMesh.cpp
 * Author: vigilant
 * 
 * Created on November 14, 2014, 11:30 PM
 */

#include "fgGFXSceneNodeMesh.h"
#include "fgGFXSceneManager.h"

using namespace fg;

/**
 * 
 */
gfx::CSceneNodeMesh::CSceneNodeMesh(SMeshBase *pMesh, CSceneNode *pParent) :
CSceneNode(SCENE_NODE_MESH, pParent) {
    CSceneNode::setNodeType(SCENE_NODE_MESH);
    if(m_drawCall) {
        delete m_drawCall;
        m_drawCall = NULL;
    }
    // #FIXME - still draw call management needs some fixing - this is so awkward, I mean... srsly?
    m_drawCall = new CDrawCall(FG_GFX_DRAW_CALL_MESH, FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT | FG_GFX_NORMAL_BIT);
    m_drawCall->setZIndex(Z_INDEX_OBJECTS_3D);
    setMesh(pMesh);
}

/**
 * 
 * @param orig
 */
gfx::CSceneNodeMesh::CSceneNodeMesh(const CSceneNodeMesh& orig) { }

/**
 * 
 */
gfx::CSceneNodeMesh::~CSceneNodeMesh() { }

/**
 * 
 */
void gfx::CSceneNodeMesh::refreshGfxInternals(void) {
   if(!m_pManager)
       return;
   if(m_pManager->getManagerType() != FG_MANAGER_SCENE) {
       return;
   }
   // ?? #FIXME
}

/**
 * 
 * @param pMesh
 */
void gfx::CSceneNodeMesh::setMesh(SMeshBase* pMesh) {
    if(!pMesh)
        return;
    base_type::setNodeType(SCENE_NODE_MESH);
    if(m_drawCall) {
        m_drawCall->setupFromMesh(pMesh);
    }
    setBoundingVolume(pMesh->aabb);
}
