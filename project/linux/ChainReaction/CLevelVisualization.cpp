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
 * File:   CLevelVisualization.cpp
 * Author: vigilant
 * 
 * Created on July 16, 2015, 2:13 PM
 */

#include "CLevelVisualization.h"

#include "SQuadData.h"
#include "SHexData.h"
#include "fgVector.h"
#include "GameLogic/fgGrid.h"

#include "Resource/fgResourceManager.h"
#include "GFX/Scene/fgGfxSceneManager.h"
#include "GFX/Scene/fgGfxSceneNodeMesh.h"

using namespace fg;
//------------------------------------------------------------------------------

CLevelVisualization::CLevelVisualization(CLevelSolver* pLevelSolver) :
m_pLevelSolver(pLevelSolver),
m_pSceneMgr(NULL),
m_pDraggedNode(NULL),
m_scale(1.0f),
m_speed(1.0f),
m_draggedCoord() {
    registerCallbacks();
    memset(m_pMaterials, 0, sizeof (m_pMaterials));
}
//------------------------------------------------------------------------------

CLevelVisualization::CLevelVisualization(const CLevelVisualization& orig) {
    // do not copy all data?    
}
//------------------------------------------------------------------------------

CLevelVisualization::~CLevelVisualization() {
    clear();
    unregisterCallbacks();
    m_pLevelSolver = NULL;
    m_pSceneMgr = NULL;
    memset(m_pMaterials, 0, sizeof (m_pMaterials));
}
//------------------------------------------------------------------------------

void CLevelVisualization::registerCallbacks(void) {
    if(!m_pLevelSolver)
        return;
    if(!m_pLevelSolver->getLevelDataHolder())
        return;
    CLevelDataHolder* pLevelData = m_pLevelSolver->getLevelDataHolder();

    pLevelData->registerCallback(CLevelDataHolder::ACTION_BLOCK_ADDED,
                                 &self_type::actionBlockAddedCallback,
                                 (void*)this);
    pLevelData->registerCallback(CLevelDataHolder::ACTION_BLOCK_MOVED,
                                 &self_type::actionBlockMovedCallback,
                                 (void*)this);

    pLevelData->registerCallback(CLevelDataHolder::ACTION_BLOCK_DESTROYED,
                                 &self_type::actionBlockDestroyedCallback,
                                 (void*)this);

    pLevelData->registerCallback(CLevelDataHolder::ACTION_GRID_CLEARED,
                                 &self_type::actionGridClearedCallback,
                                 (void*)this);

    pLevelData->registerCallback(CLevelDataHolder::ACTION_LEVEL_DATA_DESTROYED,
                                 &self_type::actionLevelDataDestroyedCallback,
                                 (void*)this);

}
//------------------------------------------------------------------------------

void CLevelVisualization::unregisterCallbacks(void) {
    if(!m_pLevelSolver)
        return;
    if(!m_pLevelSolver->getLevelDataHolder())
        return;
    CLevelDataHolder* pLevelData = m_pLevelSolver->getLevelDataHolder();
    pLevelData->removeCallback(&self_type::actionBlockAddedCallback);
    pLevelData->removeCallback(&self_type::actionBlockMovedCallback);
    pLevelData->removeCallback(&self_type::actionBlockDestroyedCallback);
    pLevelData->removeCallback(&self_type::actionGridClearedCallback);
    pLevelData->removeCallback(&self_type::actionLevelDataDestroyedCallback);
}
//------------------------------------------------------------------------------

fgBool CLevelVisualization::actionBlockAddedCallback(void* systemData, void* userData) {
    if(!systemData || !userData)
        return FG_FALSE;
    typedef CLevelDataHolder::SActionInfo SActionInfo;
    SActionInfo* pActionInfo = (SActionInfo*)systemData;
    SActionInfo& actionInfo = *pActionInfo;
    CLevelVisualization* pThis = (CLevelVisualization*)userData;
    SBlockData* pBlockData = actionInfo.pOriginal;
    fgBool status = FG_FALSE;
    if(!pBlockData) {
        return FG_FALSE;
    }
    if(!pThis->m_pSceneMgr) {
        return FG_FALSE;
    }
#define _this pThis
    _this->fixRootNode();
    gfx::CSceneNode* pRootNode = _this->m_pSceneMgr->getActiveRootNode(); // #CALLBACK
    // #CALLBACK_INTERNAL
    unsigned short x, y;
    if(pBlockData->pCellHolder) {
        x = pBlockData->pCellHolder->pos.x;
        y = pBlockData->pCellHolder->pos.y;
    }
    pBlockData->pSceneNode = _this->prepareSceneNode(x, y, pBlockData->color);
    if(!_this->m_pSceneMgr->addNode(pBlockData->pSceneNode->getRefHandle(), pBlockData->pSceneNode,
                                    pRootNode)) {
        // adding of the node failed?
        delete pBlockData->pSceneNode;
        pBlockData->pSceneNode = NULL;
        //delete pBlockData;
        //pBlockData = NULL; // should force removal?
        status = FG_FALSE;
    } else {
        status = FG_TRUE;
    }
#undef _this
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CLevelVisualization::actionBlockMovedCallback(void* systemData, void* userData) {
    if(!systemData || !userData)
        return FG_FALSE;

    typedef CLevelDataHolder::SActionInfo SActionInfo;
    SActionInfo* pActionInfo = (SActionInfo*)systemData;
    SActionInfo& actionInfo = *pActionInfo;
    CLevelVisualization* pThis = (CLevelVisualization*)userData;
    SBlockData* original = actionInfo.pOriginal;
    SBlockData* pNewPlace = actionInfo.pNew;
    fgBool status = FG_FALSE;
    if(!pThis->m_pSceneMgr) {
        return FG_FALSE;
    }
#define _this pThis
    _this->fixRootNode();
    if(pNewPlace) {
        // replace the color and material in the new location
        if(pNewPlace->pSceneNode && pNewPlace->pSceneNode->getNodeType() == gfx::SCENE_NODE_OBJECT) {
            gfx::CSceneNodeObject* pNodeObj = (gfx::CSceneNodeObject*)pNewPlace->pSceneNode;
            gfx::CDrawCall* pDrawCall = pNewPlace->pSceneNode->getDrawCall();
            if(pDrawCall) {
                if(_this->getMaterial(pNewPlace->color) != NULL) {
                    ((gfx::CSceneNodeMesh*)pNodeObj->getChild())->setMaterial(_this->getMaterial(pNewPlace->color));
                    pDrawCall->setupMaterial(_this->getMaterial(pNewPlace->color));
                }
                status = FG_TRUE;
            }
        } else if(!pNewPlace->pSceneNode && pNewPlace->pCellHolder) {
            const unsigned short x = pNewPlace->pCellHolder->pos.x;
            const unsigned short y = pNewPlace->pCellHolder->pos.y;
            // should create proper scene node?
            gfx::CSceneNode* pRootNode = _this->m_pSceneMgr->getActiveRootNode();
            pNewPlace->pSceneNode = _this->prepareSceneNode(x, y, pNewPlace->color);
            if(!_this->m_pSceneMgr->addNode(pNewPlace->pSceneNode->getRefHandle(),
                                            pNewPlace->pSceneNode,
                                            pRootNode)) {
                // adding of the node failed?
                delete pNewPlace->pSceneNode;
                pNewPlace->pSceneNode = NULL;
            } else {
                pNewPlace->show();
                pNewPlace->activate();
                status = FG_TRUE;
            }
        }
    } else if(original && original->pCellHolder) {
        const unsigned short x = original->pCellHolder->pos.x;
        const unsigned short y = original->pCellHolder->pos.y;
        gfx::CSceneNode* pRootNode = _this->m_pSceneMgr->getActiveRootNode();
        _this->m_pSceneMgr->destroyNode(original->pSceneNode);
        // #FIXME - prepareSceneNode could take additional parameter for
        // existing node 
        original->pSceneNode = _this->prepareSceneNode(x, y, original->color);
        if(!_this->m_pSceneMgr->addNode(original->pSceneNode->getRefHandle(),
                                        original->pSceneNode,
                                        pRootNode)) {
            // adding of the node failed?
            delete pNewPlace->pSceneNode;
            original->pSceneNode = NULL;
        } else {
            original->show();
            original->activate();
            status = FG_TRUE;
        }
    }
    if(original == pNewPlace || original == NULL) {
        status = FG_FALSE;
        ;
    }
#undef _this
    return status;
}
//------------------------------------------------------------------------------

fgBool CLevelVisualization::actionBlockDestroyedCallback(void* systemData, void* userData) {
    if(!systemData || !userData)
        return FG_FALSE;
    typedef CLevelDataHolder::SActionInfo SActionInfo;
    SActionInfo* pActionInfo = (SActionInfo*)systemData;
    SActionInfo& actionInfo = *pActionInfo;
    CLevelVisualization* pThis = (CLevelVisualization*)userData;
    if(!pThis->m_pSceneMgr) {
        return FG_FALSE;
    }
    SBlockData* pBlockData = actionInfo.pOriginal;
    gfx::CSceneNode* pDelNode = pBlockData->pSceneNode;
    pThis->m_pSceneMgr->destroyNode(pBlockData->pSceneNode);
    pDelNode = NULL;
    pBlockData->pSceneNode = NULL;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CLevelVisualization::actionGridClearedCallback(void* systemData, void* userData) {
    if(!systemData || !userData)
        return FG_FALSE;
    typedef CLevelDataHolder::SActionInfo SActionInfo;
    SActionInfo* pActionInfo = (SActionInfo*)systemData;
    SActionInfo& actionInfo = *pActionInfo;
    CLevelVisualization* pThis = (CLevelVisualization*)userData;

    return FG_TRUE;
}

//------------------------------------------------------------------------------

fgBool CLevelVisualization::actionLevelDataDestroyedCallback(void* systemData, void* userData) {
    if(!systemData || !userData)
        return FG_FALSE;
    typedef CLevelDataHolder::SActionInfo SActionInfo;
    SActionInfo* pActionInfo = (SActionInfo*)systemData;
    SActionInfo& actionInfo = *pActionInfo;
    CLevelVisualization* pThis = (CLevelVisualization*)userData;

    return FG_TRUE;
}
//------------------------------------------------------------------------------

void CLevelVisualization::calculateNodePosition(unsigned short x,
                                                unsigned short y,
                                                Vec2f& nodePos,
                                                fgBool* isEven,
                                                fgBool* isHex,
                                                fgBool* isOct) {
    Vec2f startPos;
    fgBool internalIsEven = FG_FALSE;
    unsigned short areaSX, areaSY;
    getLevelFile()->getAreaSize(areaSX, areaSY);
    unsigned short areaMinX, areaMaxX;
    unsigned short areaMinY, areaMaxY;
    getLevelFile()->getAreaMin(areaMinX, areaMinY);
    getLevelFile()->getAreaMax(areaMaxX, areaMaxY);
    float scaleX = m_scale;
    float scaleY = m_scale;
    const fgBool internalIsHex = (fgBool)(getLevelFile()->getLevelType() == LevelType::LEVEL_HEXAGONS);
    const fgBool internalIsOct = (fgBool)(getLevelFile()->getLevelType() == LevelType::LEVEL_OCTAGONS);
    if(internalIsHex) {
        scaleX = m_scale * 0.75f;
        scaleY = m_scale * M_SQRT3F * 0.5f;
        internalIsEven = (fgBool)!!(x % 2 == 0);
    } else if(internalIsOct) {
        float a_f = (1.0f / (1.0f + (float)M_SQRT2));
        scaleX = m_scale * (1.0f + a_f) / 2.0f;
        scaleY = m_scale * (1.0f + a_f);
        internalIsEven = (fgBool)!!(x % 2 == 0);
    }
    startPos.x = -1.0f * (float)areaSX / 2.0f * scaleX + scaleX / 2.0f;
    startPos.y = (float)areaSY / 2.0f * scaleY - scaleY / 2.0f;
    nodePos.x = startPos.x + (float)(x - areaMinX) * (scaleX);
    nodePos.y = startPos.y - 1.0f * (float)(y - areaMinY) * (scaleY);
    if(!internalIsEven && internalIsHex) {
        nodePos.y -= m_scale * 0.5f * M_SQRT3F * 0.5f;
    } else if(!internalIsEven && internalIsOct) {
        float a_f = (1.0f / (1.0f + (float)M_SQRT2));
        nodePos.y -= m_scale * (1.0f + a_f) / 2.0f;
    }
    if(isEven)
        *isEven = internalIsEven;
    if(isHex)
        *isHex = internalIsHex;
    if(isOct)
        *isOct = internalIsOct;
}
//------------------------------------------------------------------------------

gfx::CSceneNode* CLevelVisualization::prepareSceneNode(unsigned short x,
                                                       unsigned short y,
                                                       VColor color) {
    if(!m_pLevelSolver) {
        return NULL;
    }
    Vec2f nodePos;
    fgBool isHex = FG_FALSE;
    fgBool isOct = FG_FALSE;
    const char* modelNameStr = "builtinCube1x1";
    char quadNodeName[64];
    gfx::CModelResource* pModelRes = NULL;
    gfx::CSceneNodeObject* pNodeObj = NULL;
    gfx::CDrawCall* pDrawCall = NULL;
    calculateNodePosition(x, y, nodePos, NULL, &isHex, &isOct);
    if(isHex) {
        modelNameStr = "builtinHexagonalPrism";
    } else if(isOct) {
        modelNameStr = "builtinOctagonalPrism";
    }

    std::sprintf(quadNodeName, "cr_node_%dx%d", x, y);
    pModelRes = (gfx::CModelResource*)(((resource::CResourceManager*)m_pSceneMgr->getResourceManager())->get(modelNameStr));
    if(!pModelRes) {
        return NULL;
    }
    pNodeObj = new gfx::CSceneNodeObject(pModelRes, NULL);
    pNodeObj->setName(quadNodeName);
    pNodeObj->setScale(m_scale, m_scale, 1.0f);
    pNodeObj->setPosition(nodePos.x, nodePos.y, 0.0f);
    pDrawCall = pNodeObj->getDrawCall();
    if(pDrawCall) {
        if(getMaterial(color) != NULL) {
            ((gfx::CSceneNodeMesh*)pNodeObj->getChild())->setMaterial(m_pMaterials[(unsigned int)color]);
            pDrawCall->setupMaterial(m_pMaterials[(unsigned int)color]);
        }
    }
    pNodeObj->refreshGfxInternals();
    return pNodeObj;
}
//------------------------------------------------------------------------------

fgBool CLevelVisualization::fixRootNode(void) {
    if(!m_pSceneMgr || !getLevelFile()) {
        return FG_FALSE;
    }
    // need to check for root node
    char rootNodeName[64];
    fgBool status = FG_TRUE;
    std::sprintf(rootNodeName, "cr_root_n_%d", getLevelFile()->getLevelIndex());
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
            status = m_pSceneMgr->selectActiveRootNode(pRootNode);
        }
    } else {
        // select as this root node
        status = m_pSceneMgr->selectActiveRootNode(pRootNode);
    }
    return status;
}
//------------------------------------------------------------------------------

fgBool CLevelVisualization::restart(void) {
    // apply the quad data to the grid
    // this will reset the grid state to the beginning of the level
    // also will reset the scene manager (if set)

    // need to have some swith to determine which direction is scene up (camera)
    // Y+ (then quads are rotated so they spread in +x+z)
    // Z+ (quads spread in +x+y)
    // X+ (quads spread in +y+z)

    if(!getLevelDataHolder() || !getLevelFile() || !m_pSceneMgr) {
        return FG_FALSE;
    }

    if(m_pLevelSolver) {
        m_pLevelSolver->clear();
        m_pLevelSolver->setScale(m_scale);
    }
    fixRootNode();
    getLevelDataHolder()->restart();
    refreshBlocks();
    prepareSceneManager();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void CLevelVisualization::clear(void) {
    // reset the game grid (to zero)
    // zeroes binded pointers and
    // releases the data in quad vector
    if(getLevelSolver())
        getLevelSolver()->clear();
    if(getLevelDataHolder())
        getLevelDataHolder()->clear();
    m_draggedCoord = Vec2i();
    m_pDraggedNode = NULL;
}
//------------------------------------------------------------------------------

fgBool CLevelVisualization::prepareSceneManager(void) {
    if(!m_pSceneMgr)
        return FG_FALSE;
    // set some initial state for the scene manager
    m_pSceneMgr->setPickSelectionGroup(FG_FALSE);
    m_pSceneMgr->setPickSelectionToggle(FG_FALSE);
    m_pSceneMgr->setPickSelectionAABBTriangles(FG_TRUE);
    m_pSceneMgr->setPickSelectionOnHover(FG_TRUE);
    m_pSceneMgr->setFrustumCheckSphere(FG_TRUE);
    m_pSceneMgr->setLinearTraverse(FG_TRUE);
    //m_pSceneMgr->setPickSelectionOnClick(FG_TRUE);
    m_pSceneMgr->setIgnoreCollisions(FG_TRUE);
    //m_pSceneMgr->setShowGroundGrid(FG_TRUE); // TESTING
    m_pSceneMgr->setGroundLevel(0.0f);
    m_pSceneMgr->setGroundPlane(gfx::Planef::Z, 0.0f);
    m_pSceneMgr->getSkyBox()->setScale(1250.0f);
    m_pSceneMgr->setSkyBoxFollowsCamera(FG_FALSE);
    float zDistance = 250.0f; // this should change based on scale and size

    gfx::CCameraAnimation* pCamera = m_pSceneMgr->getCamera();
    pCamera->setType(gfx::CCameraAnimation::CENTER_LOCKED);
    pCamera->setCenter(Vec3f(0.0f, 0.0f, 0.0f));
    pCamera->setEye(Vec3f(0.0f, 0.0f, zDistance));
    // moar?

    m_pSceneMgr->refreshGfxInternals();

    return FG_TRUE;
}
//------------------------------------------------------------------------------

void CLevelVisualization::refreshBlocks(void) {
    if(!getLevelDataHolder())
        return;
    CLevelDataHolder* pHolder = getLevelDataHolder();
    BlockDataVec& blocks = pHolder->getBlocks();
    const unsigned int nBlocks = blocks.size();
    Vec2f nodePos;
    for(unsigned int i = 0; i < nBlocks; i++) {
        SBlockData* pBlock = blocks[i];
        if(!pBlock)
            continue;
        gfx::CSceneNodeObject* pNodeObj = (gfx::CSceneNodeObject*)pBlock->pSceneNode;
        if(!pNodeObj)
            continue;
        calculateNodePosition(pBlock->pCellHolder->pos.x,
                              pBlock->pCellHolder->pos.y,
                              nodePos);
        pNodeObj->setPosition(nodePos.x, nodePos.y, 0.0f);
        gfx::CDrawCall* pDrawCall = pBlock->pSceneNode->getDrawCall();
        gfx::SMaterial* pMaterial = this->getMaterial(pBlock->color);
        if(!pMaterial)
            continue;

        if(pDrawCall) {
            if(pDrawCall->getMaterial() != pMaterial) {
                pDrawCall->setupMaterial(pMaterial);
            }
        }
        gfx::CSceneNodeMesh* pNodeMesh = (gfx::CSceneNodeMesh*)pNodeObj->getChild();
        if(pNodeMesh) {
            if(pNodeMesh->getMaterial() != pMaterial) {
                pNodeMesh->setMaterial(pMaterial);
            }
        }
    }
}
//------------------------------------------------------------------------------

void CLevelVisualization::preRender(void) {
    if(m_pLevelSolver) {
        // elapsed is in seconds - 0.001f means one millisecond (0.01f - 10ms)
        const float elapsed = timesys::elapsed(timesys::TICK_PRERENDER) * m_speed;
        m_pLevelSolver->update(elapsed);
    }
}
//------------------------------------------------------------------------------

void CLevelVisualization::setLevelSolver(CLevelSolver* pLevelSolver) {
    if(pLevelSolver != m_pLevelSolver) {
        unregisterCallbacks();
    }
    m_pLevelSolver = pLevelSolver;
    registerCallbacks();
}
//------------------------------------------------------------------------------
