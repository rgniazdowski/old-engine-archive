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

/**
 * 
 */
fg::gfx::CSceneNodeMesh::CSceneNodeMesh(SMeshBase *pMesh, CSceneNode *pParent) :
CSceneNode(FG_GFX_SCENE_NODE_MESH, pParent) {
    CSceneNode::setNodeType(FG_GFX_SCENE_NODE_MESH);
    if(m_drawCall) {
        delete m_drawCall;
        m_drawCall = NULL;
    }
    // #FIXME - still draw call management needs some fixing - this is so awkward, I mean... srsly?
    m_drawCall = new CDrawCall(FG_GFX_DRAW_CALL_MESH, FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT | FG_GFX_NORMAL_BIT);
    setMesh(pMesh);
}

/**
 * 
 * @param orig
 */
fg::gfx::CSceneNodeMesh::CSceneNodeMesh(const CSceneNodeMesh& orig) { }

/**
 * 
 */
fg::gfx::CSceneNodeMesh::~CSceneNodeMesh() { }

/**
 * 
 * @param pMesh
 */
void fg::gfx::CSceneNodeMesh::setMesh(SMeshBase* pMesh) {
    if(!pMesh)
        return;
    CSceneNode::setNodeType(FG_GFX_SCENE_NODE_MESH);
    if(m_drawCall) {
        m_drawCall->setupFromMesh(pMesh);
    }
}
