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
 * File:   CLevelVis.cpp
 * Author: vigilant
 * 
 * Created on July 16, 2015, 2:13 PM
 */

#include "CLevelVis.h"
#include "GameLogic/fgGrid.h"
#include "GFX/Scene/fgGfxSceneManager.h"
#include "Resource/fgResourceManager.h"
#include "GFX/Scene/fgGfxSceneNodeMesh.h"

using namespace fg;

//------------------------------------------------------------------------------

CLevelVis::CLevelVis(game::CGrid* pGrid, CLevelFile* pLvlFile) :
m_pGrid(pGrid),
m_pLevelFile(pLvlFile),
m_pSceneMgr(NULL),
m_pDraggedNode(NULL),
m_pMaterialBlack(NULL),
m_pMaterialWhite(NULL),
m_quadsData(),
m_scale(1.0f),
m_draggedCoord() {
    if(m_pLevelFile) {
        unsigned int n = m_pLevelFile->getQuadsCount();
        if(n) {
            unsigned int nReserve = (unsigned int)(n * 1.5f);
            m_quadsData.reserve(nReserve);
            for(unsigned int i = 0; i < nReserve; i++) {
                m_quadsData[i] = NULL;
            }
        }
    } else {
        unsigned int nReserve = 48;
        m_quadsData.reserve(nReserve);
        for(unsigned int i = 0; i < nReserve; i++) {
            m_quadsData[i] = NULL;
        }
    }
    // Should level visualization have access to SceneManager?
}
//------------------------------------------------------------------------------

CLevelVis::CLevelVis(const CLevelVis& orig) {
    // do not copy all data?
    this->m_pGrid = orig.m_pGrid;
    this->m_pLevelFile = orig.m_pLevelFile;
    this->m_quadsData.reserve(orig.m_quadsData.capacity());
}
//------------------------------------------------------------------------------

CLevelVis::~CLevelVis() {
    clear();
    m_quadsData.clear_optimised();
    m_pGrid->clear();
    m_pGrid = NULL;
    m_pLevelFile = NULL;
}
//------------------------------------------------------------------------------

SQuadData* CLevelVis::insertNewQuad(unsigned short x,
                                    unsigned short y,
                                    SQuadData::QuadColor color) {
    if(!m_pGrid) {
        return NULL;
    }
    if(!m_pGrid->isValidAddress(x, y)) {
        return NULL;
    }
    int index = destroyQuad(x, y); // this destroy any original in that place
    gfx::CSceneNode* pRootNode = m_pSceneMgr->getActiveRootNode();
    // now need to insert new quad in that place
    // allocate new quad data
    SQuadData* pQuadData = new SQuadData();
    pQuadData->color = color;
    pQuadData->pSceneNode = prepareSceneNode(x, y, pQuadData->color);
    if(!m_pSceneMgr->addNode(pQuadData->pSceneNode->getRefHandle(), pQuadData->pSceneNode,
                             pRootNode)) {
        // adding of the node failed?
        delete pQuadData->pSceneNode;
        pQuadData->pSceneNode = NULL;
        delete pQuadData;
        pQuadData = NULL;
        return NULL;
    }
    game::CGrid::SCellHolder* pCellHolder = m_pGrid->atPtr(x, y);
    if(!pCellHolder) {
        // probably game::CGrid is not prepared - should call applyToGrid
        // destroy the scene node
        m_pSceneMgr->destroyNode(pQuadData->pSceneNode);
        pQuadData->pSceneNode = NULL;
        delete pQuadData;
        pQuadData = NULL;
        return NULL;
    }
    pQuadData->bind(pCellHolder);
    pQuadData->isValid = FG_TRUE;
    pQuadData->isDragged = FG_FALSE;
    pQuadData->activate();
    pQuadData->show();
    m_quadsData.push_back(pQuadData);
}
//------------------------------------------------------------------------------

int CLevelVis::destroyQuad(unsigned short x, unsigned short y) {
    if(!m_pGrid) {
        return -1;
    }
    if(!m_pGrid->isValidAddress(x, y)) {
        return -1;
    }
    SQuadData* pQuadData = NULL;
    // need also to find SQuadData that already resides on this address
    int index = getQuadDataIndex(x, y);
    if(index != -1) {
        unsigned int nQuads = m_quadsData.size();
        // there already is a quad data in that place
        // need to destroy it completely
        pQuadData = m_quadsData[index];
        pQuadData->deactivate();
        pQuadData->unbind();
        if(m_pSceneMgr) {
            gfx::CSceneNode* pDelNode = pQuadData->pSceneNode;
            m_pSceneMgr->destroyNode(pQuadData->pSceneNode);
            pDelNode = NULL;
            pQuadData->pSceneNode = NULL;
        }
        delete pQuadData;
        pQuadData = NULL;
        //m_quadsData[index] = NULL;
        m_quadsData[index] = m_quadsData[nQuads - 1];
        m_quadsData[nQuads - 1] = NULL;
        m_quadsData.resize(nQuads - 1);
        // previous quad is now completely removed
    }
    return index; // return the index from which the quad was destroyed
}
//------------------------------------------------------------------------------

SQuadData* CLevelVis::moveQuadToNewPlace(SQuadData* original,
                                         unsigned short newX,
                                         unsigned short newY) {
    if(!m_pGrid || !original) {
        return NULL;
    }
    if(!m_pGrid->isValidAddress(newX, newX)) {
        return NULL;
    }
    // the quad moves to the new place
    // if something already exists in that place
    // there must be a way to preserve as much memory as possible.
    // the scene node with valid name (cr_node_XxY) cannot have the name changed
    // need to replace material

    if(original->pCellHolder->pos.x == newX && original->pCellHolder->pos.y == newY) {
        return original; // nothing to do
    }
    // determine if there is something in that place
    SQuadData* pNewPlace = getQuadData(newX, newY);
    if(pNewPlace == original) {
        return original; // nothing to do
    }
    if(pNewPlace) {
        // replace the color, value and material in the new location
        // change the value
        pNewPlace->pCellHolder->value = original->pCellHolder->value;
        // change the color
        pNewPlace->color = original->color;
        // replace the material in scene node
        if(pNewPlace->pSceneNode && pNewPlace->pSceneNode->getNodeType() == gfx::SCENE_NODE_OBJECT) {
            gfx::CSceneNodeObject* pNodeObj = (gfx::CSceneNodeObject*)pNewPlace->pSceneNode;
            gfx::CDrawCall* pDrawCall = pNewPlace->pSceneNode->getDrawCall();
            if(pDrawCall) {
                if(pNewPlace->color == SQuadData::BLACK) {
                    if(m_pMaterialBlack) {
                        ((gfx::CSceneNodeMesh*)pNodeObj->getChild())->setMaterial(m_pMaterialBlack);
                        pDrawCall->setupMaterial(m_pMaterialBlack);
                    }
                } else if(pNewPlace->color == SQuadData::WHITE) {
                    if(m_pMaterialWhite) {
                        ((gfx::CSceneNodeMesh*)pNodeObj->getChild())->setMaterial(m_pMaterialWhite);
                        pDrawCall->setupMaterial(m_pMaterialWhite);
                    }
                }
            }
        }
        // now need to remove the original
        // this will also destroy the original scene node and unbind
        destroyQuad(original->pCellHolder->pos.x, original->pCellHolder->pos.y);
        original = NULL;
        pNewPlace->isValid = FG_TRUE;
        pNewPlace->isDragged = FG_FALSE;
        pNewPlace->rotation = 0.0f;
        return pNewPlace; // return the quad pointer after move
    }
    // if there is nothing in the target location
    // need to create new scene node
    gfx::CSceneNode* pNode = prepareSceneNode(newX, newY, original->color);    
    m_pSceneMgr->destroyNode(original->pSceneNode);
    if(!m_pSceneMgr->addNode(pNode->getRefHandle(), pNode)) {
        // adding of the node failed?
        delete pNode;
        pNode = NULL;
        original->pSceneNode = NULL;
        return NULL;
    }
    // need to remove the old scene node
    original->deactivate();
    // need to unbind the old quad data
    original->unbind();
    original->pSceneNode = pNode; // replace the scene node
    // can retain the old SQuadData - just replace the pointers and bind again
    original->bind(m_pGrid->atPtr(newX, newY));
    original->isValid = FG_TRUE;
    original->isDragged = FG_FALSE;
    original->rotation = 0.0f;
    original->show();
    original->activate();
    return original;
}

//------------------------------------------------------------------------------

gfx::CSceneNode* CLevelVis::prepareSceneNode(unsigned short x,
                                             unsigned short y,
                                             SQuadData::QuadColor color) {
    if(!m_pLevelFile) {
        return NULL;
    }
    Vec2f startPos;
    unsigned short areaSX, areaSY;
    m_pLevelFile->getAreaSize(areaSX, areaSY);
    unsigned short areaMinX, areaMaxX;
    unsigned short areaMinY, areaMaxY;
    m_pLevelFile->getAreaMin(areaMinX, areaMinY);
    m_pLevelFile->getAreaMax(areaMaxX, areaMaxY);
    startPos.x = -1.0f * (float)areaSX / 2.0f * m_scale + m_scale / 2.0f;
    startPos.y = (float)areaSY / 2.0f * m_scale - m_scale / 2.0f;
    char quadNodeName[64];
    //const char* modelNameStr = "builtinQuad1x1";
    const char* modelNameStr = "builtinCube1x1";

    std::sprintf(quadNodeName, "cr_node_%dx%d", x, y);
    gfx::CModelResource* pModelRes = (gfx::CModelResource*)(((resource::CResourceManager*)m_pSceneMgr->getResourceManager())->get(modelNameStr));
    if(!pModelRes) {
        return NULL;
    }
    gfx::CSceneNodeObject* pNodeObj = new gfx::CSceneNodeObject(pModelRes, NULL);
    pNodeObj->setName(quadNodeName);
    pNodeObj->setScale(m_scale, m_scale, 1.0f);
    pNodeObj->setPosition(startPos.x + (float)(x - areaMinX) * (m_scale),
                          startPos.y - 1.0f * (float)(y - areaMinY) * (m_scale),
                          0.0f);
    gfx::CDrawCall* pDrawCall = pNodeObj->getDrawCall();
    if(pDrawCall) {
        if(color == SQuadData::BLACK) {
            if(m_pMaterialBlack) {
                ((gfx::CSceneNodeMesh*)pNodeObj->getChild())->setMaterial(m_pMaterialBlack);
                pDrawCall->setupMaterial(m_pMaterialBlack);
            }
        } else if(color == SQuadData::WHITE) {
            if(m_pMaterialWhite) {
                ((gfx::CSceneNodeMesh*)pNodeObj->getChild())->setMaterial(m_pMaterialWhite);
                pDrawCall->setupMaterial(m_pMaterialWhite);
            }
        }
    }
    pNodeObj->refreshGfxInternals();
    return pNodeObj;
}
//------------------------------------------------------------------------------

fgBool CLevelVis::prepareQuads(void) {
    // this will reset the main root node children
    // also prepare the quadData
    if(!m_pGrid || !m_pLevelFile || !m_pSceneMgr) {
        return FG_FALSE;
    }
    // need to check for root node
    char rootNodeName[64];
    
    std::sprintf(rootNodeName, "cr_root_n_%d", m_pLevelFile->getLevelIndex());
    gfx::CSceneNode* pRootNode = m_pSceneMgr->get(rootNodeName);
    if(!pRootNode) {
        pRootNode = new gfx::CSceneNode(gfx::SCENE_NODE_ROOT, NULL);
        if(!pRootNode) {
            return FG_FALSE;
        }
        pRootNode->setName(rootNodeName);
        fgBool rootStatus = m_pSceneMgr->addNode(pRootNode->getRefHandle(),
                                                 pRootNode,
                                                 (gfx::CSceneNode*)NULL);
        if(rootStatus) {
            m_pSceneMgr->selectActiveRootNode(pRootNode);
        }
    } else {
        // select as this root node
        m_pSceneMgr->selectActiveRootNode(pRootNode);
    }
    // delete all old nodes, quad data, unbind all and clear the grid
    // better to start over >> #FIXME - maybe some optimization, without so many
    // reallocs
    clear();
    CLevelFile::QuadVec& quads = m_pLevelFile->getQuads();
    unsigned int n = quads.size();
    if(!n) {
        return FG_FALSE;
    }
    // need to reserve proper size
    unsigned int nReserve = (unsigned int)(n * 1.5f);
    m_quadsData.reserve(nReserve);
    //m_quadsData.resize(n); // no need to resize now
    // Quad vector from level file contains just info about position and color.
    // Quad data vector is more detailed, contains scene node, draw call, and
    // cell holder from game logical grid.

    // Prepare new number of quads
    for(unsigned int i = 0; i < n; i++) {
        insertNewQuad(quads[i].pos.x,
                      quads[i].pos.y,
                      (SQuadData::QuadColor)quads[i].color);
    }
    m_pSceneMgr->refreshGfxInternals();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CLevelVis::restart(void) {
    // apply the quad data to the grid
    // this will reset the grid state to the beginning of the level
    // also will reset the scene manager (if set)

    // need to have some swith to determine which direction is scene up (camera)
    // Y+ (then quads are rotated so they spread in +x+z)
    // Z+ (quads spread in +x+y)
    // X+ (quads spread in +y+z)

    if(!m_pGrid || !m_pLevelFile) {
        return FG_FALSE;
    }
    m_pLevelFile->applyToGrid(m_pGrid);
    if(!prepareQuads()) {
        return FG_FALSE;
    }
    if(m_pSceneMgr) {
        // set some initial state for the scene manager
        m_pSceneMgr->setPickSelectionGroup(FG_FALSE);
        m_pSceneMgr->setPickSelectionToggle(FG_FALSE);
        m_pSceneMgr->setPickSelectionAABBTriangles(FG_TRUE);
        m_pSceneMgr->setPickSelectionOnHover(FG_TRUE);
        //m_pSceneMgr->setPickSelectionOnClick(FG_TRUE);
        m_pSceneMgr->setIgnoreCollisions(FG_TRUE);
        //m_pSceneMgr->setShowGroundGrid(FG_TRUE); // TESTING
        m_pSceneMgr->setGroundLevel(0.0f);
        m_pSceneMgr->setGroundPlane(gfx::Planef::Z, 0.0f);

        float zDistance = 250.0f; // this should change based on scale and size

        gfx::CCameraAnimation* pCamera = m_pSceneMgr->getCamera();
        pCamera->setType(gfx::CCameraAnimation::CENTER_LOCKED);
        pCamera->setCenter(Vec3f(0.0f, 0.0f, 0.0f));
        pCamera->setEye(Vec3f(0.0f, 0.0f, zDistance));
        // moar?
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void CLevelVis::clear(void) {
    // reset the game grid (to zero)
    // zeroes binded pointers and
    // releases the data in quad vector
    unsigned int n = m_quadsData.size();
    for(unsigned int i = 0; i < n; i++) {
        SQuadData* pQuadData = m_quadsData[i];
        if(!pQuadData) {
            continue;
        }
        pQuadData->deactivate();
        pQuadData->unbind();
        if(m_pSceneMgr) {
            m_pSceneMgr->destroyNode(pQuadData->pSceneNode);
            pQuadData->pSceneNode = NULL;
        }
        delete pQuadData;
        pQuadData = NULL;
        m_quadsData[i] = NULL;
    }
    n = m_quadsData.capacity();
    for(unsigned int i = 0; i < n; i++) {
        m_quadsData[i] = NULL;
    }
    if(m_pGrid) {
        m_pGrid->clear();
    }
    m_quadsData.clear_optimised();
}
//------------------------------------------------------------------------------

SQuadData* CLevelVis::getQuadData(unsigned short x, unsigned short y) {
    if(m_pGrid) {
        void *cellData = m_pGrid->getCellData(x, y);
        if(!cellData) {
            return NULL;
        }
        return (SQuadData*)cellData;
    } else {
        unsigned int n = m_quadsData.size();
        for(unsigned int i = 0; i < n; i++) {
            SQuadData *pQuadData = m_quadsData[i];
            if(!pQuadData) {
                continue;
            }
            if(!pQuadData->pCellHolder) {
                continue;
            }
            if(pQuadData->pCellHolder->pos.x == x &&
               pQuadData->pCellHolder->pos.y == y) {
                if(((SQuadData*)pQuadData->pCellHolder->pData) == pQuadData) {
                    return pQuadData;
                }
            }
        }
        return NULL;
    }
}
//------------------------------------------------------------------------------

int CLevelVis::getQuadDataIndex(unsigned short x, unsigned short y) {
    unsigned int n = m_quadsData.size();
    for(unsigned int i = 0; i < n; i++) {
        SQuadData *pQuadData = m_quadsData[i];
        if(!pQuadData) {
            continue;
        }
        if(!pQuadData->pCellHolder) {
            continue;
        }
        if(pQuadData->pCellHolder->pos.x == x &&
           pQuadData->pCellHolder->pos.y == y) {
            if(((SQuadData*)pQuadData->pCellHolder->pData) == pQuadData) {
                return i;
            }
        }
    }
    return -1;
}
//------------------------------------------------------------------------------

void CLevelVis::setLevelFile(CLevelFile* pLvlFile) {
    m_pLevelFile = pLvlFile;
}
//------------------------------------------------------------------------------

void CLevelVis::getSize(unsigned short& x, unsigned short& y) {
    if(m_pLevelFile) {
        m_pLevelFile->getSize(x, x);
    }
}
//------------------------------------------------------------------------------

void CLevelVis::getSize(unsigned short* x, unsigned short* y) {
    if(m_pLevelFile) {
        m_pLevelFile->getSize(x, x);
    }
}
//------------------------------------------------------------------------------
