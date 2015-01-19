/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXSceneManager.h"
#include "Shaders/fgGFXShaderManager.h"
#include "Textures/fgTextureResource.h"
#include "Resource/fgResourceManager.h"
#include "fgDebugConfig.h"
#include "fgGFXFrustum.h"

#if defined(FG_DEBUG)
#include "Util/fgProfiling.h"
#endif

using namespace fg;

/**
 * 
 */
gfx::CSceneManager::CSceneManager() :
CDrawingBatch(),
m_MVP(),
m_camera(FG_GFX_CAMERA_FREE) {
    m_managerType = FG_MANAGER_SCENE;
}

/**
 * 
 */
gfx::CSceneManager::~CSceneManager() {
    gfx::CSceneManager::destroy();
}

/**
 *
 */
void gfx::CSceneManager::clear(void) {
    releaseAllHandles();
    m_managerType = FG_MANAGER_SCENE;
    m_pResourceMgr = NULL;
}

/**
 * 
 * @return 
 */
fgBool gfx::CSceneManager::destroy(void) {
    CDrawingBatch::flush();
    //objectVecItor oit = m_objects.begin(), oend = m_objects.end();

    // Delete all gfx objects in the scene
    /*for(;oit!=oend;oit++) {
        if(*oit) {
            if((*oit)->isManaged() == FG_TRUE)
                delete (*oit);
     *oit = NULL;
        }
    }
    m_objects.clear_optimised(); */

    // The piece of code seems to repeat itself
    // Maybe even the handle manager can have this piece of code?
    // Delete all gfx objects in the scene
    DataVecItor begin, end, itor;
    begin = getRefDataVector().begin();
    end = getRefDataVector().end();
    itor = begin;
    for(; itor != end; itor++) {
        CSceneNode *pObj = (*itor).data;
        if(pObj == NULL)
            continue;
        if(pObj->isManaged())
            delete pObj;        
        (*itor).clear();
    }
    gfx::CSceneManager::clear();
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool gfx::CSceneManager::initialize(void) {
    return FG_TRUE;
}

/**
 * 
 * @param shaderMgr
 */
void gfx::CSceneManager::setShaderManager(fg::base::CManager* pShaderMgr) {
    CDrawingBatch::setShaderManager(pShaderMgr);
}

/**
 * 
 * @param pResourceMgr
 */
void gfx::CSceneManager::setResourceManager(fg::base::CManager *pResourceMgr) {
    if(!pResourceMgr)
        return;
    if(pResourceMgr->getManagerType() == FG_MANAGER_RESOURCE)
        m_pResourceMgr = pResourceMgr;
}

/**
 * 
 */
void gfx::CSceneManager::flush(void) {
    CDrawingBatch::flush();
    while(!m_nodeQueue.empty())
        m_nodeQueue.pop();
}

/**
 * 
 */
void gfx::CSceneManager::sortCalls(void) {
    if(!getShaderManager())
        return;
    m_MVP.setCamera((CCamera *)(&m_camera));
    if(getRefPriorityQueue().empty())
        CDrawingBatch::sortCalls(); // NOPE
    while(!m_nodeQueue.empty())
        m_nodeQueue.pop();
    DataVecItor itor = getRefDataVector().begin(), end = getRefDataVector().end();
#if 1
    int idx = 0;
    for(; itor != end; itor++, idx++) {
        if(!(*itor).data)
            continue;
        CSceneNode *pNode = (*itor).data;
        CDrawCall *pDrawCall = pNode->getDrawCall();
#if defined(FG_DEBUG)
        if(g_fgDebugConfig.isDebugProfiling) {
            profile::g_debugProfiling->begin("GFX::Scene::FrustumCheck");
        }
#endif
        // There is a problem because the bounding box needs to be modified by
        // the model matrix; maybe some operator ?
        pNode->updateAABB();

        //const char *msg[] = {"OUTSIDE", "INTERSECT", "INSIDE", "[null]", "\0"};
        int boxtest = m_MVP.getRefFrustum().testVolume(pNode->getRefBoundingVolume());
        //int spheretest = (int)m_MVP.getRefFrustum().testSphere(fgVector3f(pNode->getRefModelMatrix()[3]), 30.0f);
        if(!boxtest)
            pNode->setVisible(FG_FALSE);
        else
            pNode->setVisible(FG_TRUE);
#if defined(FG_DEBUG)
        if(g_fgDebugConfig.isDebugProfiling) {
            profile::g_debugProfiling->end("GFX::Scene::FrustumCheck");
        }
#endif
        //FG_LOG_DEBUG("[%d] -> AABBox[%s] -- -- Sphere.30.0f[%s] %s\n", idx, msg[boxtest], msg[spherestatus], pNode->getNameStr());
        g_fgDebugConfig.gfxBBoxShow = true;
        // ? also need to push to queue more than one draw call
        // And i mean... wait wut? All children are registered
        // This is a tree - that needs to be traversed
        // There is no need to go through all (linear) objects through the scene
        // The aabb for each object is updated based on the children
        // Need some standard for manipulating this objects, and also for traversing
        // the tree. Also one would need some standard for special kind of tree - loose octrees? bitch?
        if(pNode->isVisible()) {
            m_nodeQueue.push(pNode);
        }
        if(pDrawCall) {
            if(!pDrawCall->getShaderProgram())
                pDrawCall->setShaderProgram(((gfx::CShaderManager *)getShaderManager())->getCurrentProgram());
            //pDrawCall->setModelMatrix(pObj->getRefModelMatrix());
            // getRefPriorityQueue().push(pDrawCall);
        }
    }
#endif
}

/**
 * 
 */
void gfx::CSceneManager::render(void) {
    //printf("fgGfxSceneManager::render(void)\n");
    CDrawingBatch::render(); // #NOPE ? i don't know what i'm doing
    while(!m_nodeQueue.empty()) {
#if defined(FG_DEBUG)
        if(g_fgDebugConfig.isDebugProfiling) {
            profile::g_debugProfiling->begin("GFX::Scene::DrawNode");
        }
#endif
        CSceneNode *pSceneNode = m_nodeQueue.top();
        pSceneNode->draw();
#if defined(FG_DEBUG)
        if(g_fgDebugConfig.isDebugProfiling) {
            profile::g_debugProfiling->end("GFX::Scene::DrawNode");
        }
#endif

#if defined(FG_DEBUG)
        CShaderProgram *pProgram = static_cast<gfx::CShaderManager *>(m_pShaderMgr)->getCurrentProgram();
        pProgram->setUniform(FG_GFX_USE_TEXTURE, 0.0f);
        if(FG_DEBUG_CFG_OPTION(gfxBBoxShow) && pSceneNode->getNodeType() == FG_GFX_SCENE_NODE_OBJECT) {
            CSceneNodeObject *pSceneObj = static_cast<CSceneNodeObject *>(pSceneNode);
            // Current aabb - it's in model space (local)
            AABB3Df &modelBox = pSceneObj->getModel()->getRefAABB();
            // Initial Bounding box
            CPrimitives::drawAABBLines(modelBox, fgColor4f(1.0f, 0.0f, 0.0f, 1.0f));
            // Draw transformed bounding box #FIXME - colors FUBAR            
        }
        if(FG_DEBUG_CFG_OPTION(gfxBBoxShow)) {
            m_MVP.resetModelMatrix();
            pProgram->setUniform(&m_MVP);
            CPrimitives::drawAABBLines(pSceneNode->getRefBoundingVolume(), fgColor4f(0.5f, 0.5f, 1.0f, 1.0f));
        }
#endif
        m_nodeQueue.pop();
    }
}

#if 0

/**
 * 
 * @param pObj
 * @param manage
 * @return 
 */
int gfx::CSceneManager::appendObject(CSceneNode *pObj, fgBool manage) {
    if(!pObj)
        return -1;
    if(m_objects.find(pObj) != -1)
        return -1;
    if(!pObj->getModel())
        return -1;

    CDrawCall *call = new CDrawCall(FG_GFX_DRAW_CALL_MODEL);
    call->setupFromModel(pObj->getModel());
    if(getShaderManager())
        call->setShaderProgram(((CShaderManager *)getShaderManager())->getCurrentProgram());
    if(m_resourceMgr) {
        SMaterial *pMainMaterial = pObj->getModel()->getMainMaterial();
        if(pMainMaterial) {
            CTextureResource *pTexRes = (CTextureResource *)((CResourceManager *)m_resourceMgr)->get(pMainMaterial->ambientTexHandle);
            if(pTexRes)
                call->setTexture(pTexRes->getRefGfxID());
        }
    }
    call->setMVP(&m_MVP);
    call->setModelMatrix(pObj->getRefModelMatrix());
    pObj->setManaged(manage);
    m_objects.push_back(pObj);
    m_objDrawCalls.push_back(call);
    // 2nd argument tells that this draw call should not be managed
    // meaning: destructor wont be called on flush()
    CDrawingBatch::appendDrawCall(call, FG_FALSE);

    return ((int)m_objects.size() - 1);
}

/**
 * 
 * @param index
 * @param pModelRes
 * @param manage
 * @return 
 */
CSceneNode *gfx::CSceneManager::appendModel(int& index,
                                            CModelResource* pModelRes,
                                            fgBool manage) {
    if(!pModelRes) {
        index = -1;
        return NULL;
    }
    CSceneNode *pObj = new CSceneNode();
    //pObj->setName();
    pObj->setModel(pModelRes);
    index = appendObject(pObj, manage);
    return pObj;
}
#endif

/**
 * 
 * @param oUniqueID
 * @param pObj
 * @param oFatherObj
 * @return 
 */
fgBool gfx::CSceneManager::addNode(fgGfxSceneNodeHandle& nodeUniqueID,
                                   CSceneNode *pNode,
                                   CSceneNode *pFatherNode) {
    if(!pNode) {
        // Empty pointer - return
        FG_LOG_ERROR("GFX.SceneManager: Empty pointer - exit... no addition made");
        return FG_FALSE;
    }

    if(handle_mgr_type::isDataManaged(pNode)) {
        // Widget is already managed in the handle manager
        FG_LOG_ERROR("GFX.SceneManager: Object is already managed in the handle manager: '%s'", pNode->getNameStr());
        return FG_FALSE;
    }

    if(!pNode->getHandle().isNull()) {
        // Widget has already initialized handle
        FG_LOG_ERROR("GFX.SceneManager: Object has already initialized handle: '%s'", pNode->getNameStr());
        return FG_FALSE;
    }

    if(!handle_mgr_type::acquireHandle(nodeUniqueID, pNode)) {
        // Could not aquire handle for the widget
        FG_LOG_ERROR("GFX.SceneManager: Could not aquire handle for the object: '%s'", pNode->getNameStr());
        return FG_FALSE;
    }
    pNode->setHandle(nodeUniqueID);
    // By default object is set to be managed
    // However in some cases the 'managed' flag will
    // be set to FG_FALSE after addition
    pNode->setManaged(FG_TRUE);
    pNode->setManager(this); // Setup internal pointer to the manager
    pNode->setParent(pFatherNode); // Pointer to the parent (if any)

    if(!handle_mgr_type::setupName(pNode->getName().c_str(), nodeUniqueID)) {
        // Could not setup handle string tag/name for the scene node
        // The handle name tag can be empty - sometimes it is not needed
        FG_LOG_ERROR("GFX.SceneManager: Could not setup handle string tag/name for the object: '%s'", pNode->getNameStr());
    }
    //unsigned int index = pObj->getHandle().getIndex();

#if 1
    if(pNode->getNodeType() == FG_GFX_SCENE_NODE_OBJECT) {
        // #FIXME - this is total fubar
        CSceneNodeObject *pNodeObject = static_cast<CSceneNodeObject *>(pNode);
        CDrawCall *pDrawCall = (*pNodeObject->getChildren().begin())->getDrawCall();
        pDrawCall->setMVP(&m_MVP);
        if(pNodeObject->getModel()) {
            if(getShaderManager())
                pDrawCall->setShaderProgram(((gfx::CShaderManager *)getShaderManager())->getCurrentProgram());
            if(m_pResourceMgr) {
                SMaterial *pMainMaterial = pNodeObject->getModel()->getMainMaterial();
                if(pMainMaterial) {
                    CTextureResource *pTexRes = (CTextureResource *)((fg::resource::CResourceManager *)m_pResourceMgr)->get(pMainMaterial->ambientTexHandle);
                    if(pTexRes)
                        pDrawCall->setTexture(pTexRes->getRefGfxID());
                }
            }
        }
    } else {
        CDrawCall *pDrawCall = pNode->getDrawCall();
        if(pDrawCall) {
            pDrawCall->setMVP(&m_MVP);
            if(getShaderManager())
                pDrawCall->setShaderProgram(((gfx::CShaderManager *)getShaderManager())->getCurrentProgram());
        }
    }
#endif

    // 2nd argument tells that this draw call should not be managed
    // meaning: destructor wont be called on flush()
    //fgGfxDrawingBatch::appendDrawCall(drawCall, FG_FALSE); // Don't know if needed...
    return FG_TRUE;
}

/**
 * 
 * @param oUniqueID
 * @param pObj
 * @param oFatherUniqueID
 * @return 
 */
fgBool gfx::CSceneManager::addNode(fgGfxSceneNodeHandle& oUniqueID,
                                   CSceneNode *pObj,
                                   const fgGfxSceneNodeHandle& oFatherUniqueID) {
    return addNode(oUniqueID, pObj, handle_mgr_type::dereference(oFatherUniqueID));
}

/**
 * 
 * @param oUniqueID
 * @param pObj
 * @param oFatherNameTag
 * @return 
 */
fgBool gfx::CSceneManager::addNode(fgGfxSceneNodeHandle& oUniqueID,
                                   CSceneNode *pObj,
                                   const std::string& oFatherNameTag) {
    return addNode(oUniqueID, pObj, handle_mgr_type::dereference(oFatherNameTag));
}

/**
 * 
 * @param oUniqueID
 * @param pObj
 * @param oFatherNameTag
 * @return 
 */
fgBool gfx::CSceneManager::addNode(fgGfxSceneNodeHandle& oUniqueID,
                                   CSceneNode *pObj,
                                   const char* oFatherNameTag) {
    return addNode(oUniqueID, pObj, handle_mgr_type::dereference(oFatherNameTag));
}

/**
 * 
 * @param pObj
 * @return 
 */
fgBool gfx::CSceneManager::remove(CSceneNode *pObj) {
    if(!pObj || !isManaged(pObj)) {
        return FG_FALSE;
    }
    pObj->setManaged(FG_FALSE);
    // Reset the manager pointer - object is not managed - it is no longer needed
    pObj->setManager(NULL);
    return handle_mgr_type::releaseHandle(pObj->getHandle());
}

/**
 * 
 * @param oUniqueID
 * @return 
 */
fgBool gfx::CSceneManager::remove(const fgGfxSceneNodeHandle& oUniqueID) {
    return remove(handle_mgr_type::dereference(oUniqueID));
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gfx::CSceneManager::remove(const std::string& nameTag) {
    return remove(handle_mgr_type::dereference(nameTag));
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gfx::CSceneManager::remove(const char *nameTag) {
    return remove(handle_mgr_type::dereference(nameTag));
}

/**
 * 
 * @param pObj
 * @return 
 */
fgBool gfx::CSceneManager::destroyNode(CSceneNode*& pObj) {
    if(!gfx::CSceneManager::remove(pObj)) {
        return FG_FALSE;
    }
    delete pObj;
    pObj = NULL;
    return FG_TRUE;
}

/**
 * 
 * @param oUniqueID
 * @return 
 */
fgBool gfx::CSceneManager::destroyNode(const fgGfxSceneNodeHandle& oUniqueID) {
    CSceneNode *pObj = handle_mgr_type::dereference(oUniqueID);
    return destroyNode(pObj);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gfx::CSceneManager::destroyNode(const std::string& nameTag) {
    CSceneNode *pObj = handle_mgr_type::dereference(nameTag);
    return destroyNode(pObj);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gfx::CSceneManager::destroyNode(const char *nameTag) {
    CSceneNode *pObj = handle_mgr_type::dereference(nameTag);
    return destroyNode(pObj);
}

/**
 * 
 * @param oUniqueID
 * @return 
 */
gfx::CSceneNode* gfx::CSceneManager::get(const fgGfxSceneNodeHandle& oUniqueID) {
    return handle_mgr_type::dereference(oUniqueID);
}

/**
 * 
 * @param nameTag
 * @return 
 */
gfx::CSceneNode* gfx::CSceneManager::get(const std::string& nameTag) {
    return handle_mgr_type::dereference(nameTag);
}

/**
 * 
 * @param nameTag
 * @return 
 */
gfx::CSceneNode* gfx::CSceneManager::get(const char *nameTag) {
    return handle_mgr_type::dereference(nameTag);
}

/**
 * 
 * @param pObj
 * @return 
 */
fgBool gfx::CSceneManager::isManaged(const CSceneNode *pObj) {
    if(!pObj) {
        return FG_FALSE;
    }
    if(FG_IS_INVALID_HANDLE(pObj->getHandle()) ||
       !handle_mgr_type::isHandleValid(pObj->getHandle())) {
        return FG_FALSE;
    }
    // This last check is an overkill
    //if(!fgHandleManager::isDataManaged(pObj)) {
    //    return FG_FALSE;
    //}
    return FG_TRUE;
}

/**
 * 
 * @param oUniqueID
 * @return 
 */
fgBool gfx::CSceneManager::isManaged(const fgGfxSceneNodeHandle& oUniqueID) {
    CSceneNode *pObj = get(oUniqueID);
    return (fgBool)(pObj != NULL);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gfx::CSceneManager::isManaged(const std::string& nameTag) {
    CSceneNode *pObj = get(nameTag);
    return (fgBool)(pObj != NULL);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool gfx::CSceneManager::isManaged(const char *nameTag) {
    CSceneNode *pObj = get(nameTag);
    return (fgBool)(pObj != NULL);
}
