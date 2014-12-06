/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
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
fgGfxSceneNodeMesh::fgGfxSceneNodeMesh(fgGfxMeshBase *pMesh, fgGfxSceneNode *pParent) :
fgGfxSceneNode(FG_GFX_SCENE_NODE_MESH, pParent) {
    fgGfxSceneNode::setNodeType(FG_GFX_SCENE_NODE_MESH);
    if(m_drawCall) {
        delete m_drawCall;
        m_drawCall = NULL;
    }
    // #FIXME - still draw call management needs some fixing - this is so awkward, I mean... srsly?
    m_drawCall = new fgGfxDrawCall(FG_GFX_DRAW_CALL_MESH, FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT | FG_GFX_NORMAL_BIT);
    setMesh(pMesh);
}

/**
 * 
 * @param orig
 */
fgGfxSceneNodeMesh::fgGfxSceneNodeMesh(const fgGfxSceneNodeMesh& orig) { }

/**
 * 
 */
fgGfxSceneNodeMesh::~fgGfxSceneNodeMesh() { }

/**
 * 
 * @param pMesh
 */
void fgGfxSceneNodeMesh::setMesh(fgGfxMeshBase* pMesh) {
    if(!pMesh)
        return;
    fgGfxSceneNode::setNodeType(FG_GFX_SCENE_NODE_MESH);
    if(m_drawCall) {
        m_drawCall->setupFromMesh(pMesh);
    }
}