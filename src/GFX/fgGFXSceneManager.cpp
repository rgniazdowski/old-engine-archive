/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
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

/**
 * 
 */
fgGfxSceneManager::fgGfxSceneManager() :
fgGfxDrawingBatch(),
m_MVP(),
m_camera(FG_GFX_CAMERA_FREE) {
    m_managerType = FG_MANAGER_SCENE;
}

/**
 * 
 */
fgGfxSceneManager::~fgGfxSceneManager() {
    fgGfxSceneManager::destroy();
}

/**
 *
 */
void fgGfxSceneManager::clear(void) {
    releaseAllHandles();
    m_managerType = FG_MANAGER_SCENE;
    m_pResourceMgr = NULL;
}

/**
 * 
 * @return 
 */
fgBool fgGfxSceneManager::destroy(void) {
    fgGfxDrawingBatch::flush();
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
    hmDataVecItor begin, end, itor;
    begin = getRefDataVector().begin();
    end = getRefDataVector().end();
    itor = begin;
    for(; itor != end; itor++) {
        fgGfxSceneNode *pObj = *itor;
        if(pObj == NULL)
            continue;
        if(pObj->isManaged())
            delete pObj;
        *itor = NULL;
    }
    fgGfxSceneManager::clear();
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool fgGfxSceneManager::initialize(void) {
    return FG_TRUE;
}

/**
 * 
 * @param shaderMgr
 */
void fgGfxSceneManager::setShaderManager(fgManagerBase* pShaderMgr) {
    fgGfxDrawingBatch::setShaderManager(pShaderMgr);
}

/**
 * 
 * @param pResourceMgr
 */
void fgGfxSceneManager::setResourceManager(fgManagerBase *pResourceMgr) {
    if(!pResourceMgr)
        return;
    if(pResourceMgr->getManagerType() == FG_MANAGER_RESOURCE)
        m_pResourceMgr = pResourceMgr;
}

/**
 * 
 */
void fgGfxSceneManager::flush(void) {
    fgGfxDrawingBatch::flush();
    while(!m_nodeQueue.empty())
        m_nodeQueue.pop();
}

/**
 * 
 */
void fgGfxSceneManager::sortCalls(void) {
    if(!getShaderManager())
        return;
    //printf("fgGfxSceneManager::sortCalls(void)\n");
    m_MVP.setCamera((fgGfxCamera *)(&m_camera));
    if(getRefPriorityQueue().empty())
        fgGfxDrawingBatch::sortCalls(); // NOPE
    while(!m_nodeQueue.empty())
        m_nodeQueue.pop();
    hmDataVecItor itor = getRefDataVector().begin(), end = getRefDataVector().end();
    //m_MVP.calculate(&m_camera, fgMatrix4f());
    //m_MVP.getRefFrustum().set(m_MVP.getRefProjMatrix() * m_MVP.getRefViewMatrix());
#if 1
    int idx = 0;
    for(; itor != end; itor++, idx++) {
        if(!(*itor))
            continue;
        fgGfxSceneNode *pNode = (*itor);
        fgGfxDrawCall *pDrawCall = pNode->getDrawCall();
#if defined(FG_DEBUG)
        if(g_fgDebugConfig.isDebugProfiling) {
            g_debugProfiling->begin("GFX::Scene::FrustumCheck");
        }
#endif
        // There is a problem because the bounding box needs to be modified by
        // the model matrix; maybe some operator ?
        pNode->updateAABB();

        //const char *msg[] = {"OUTSIDE", "INTERSECT", "INSIDE", "[null]", "\0"};
        int boxtest = m_MVP.getRefFrustum().testAABB(pNode->getRefAABB());
        //int spheretest = (int)m_MVP.getRefFrustum().testSphere(fgVector3f(pNode->getRefModelMatrix()[3]), 30.0f);
        if(!boxtest)
            pNode->setVisible(FG_FALSE);
        else
            pNode->setVisible(FG_TRUE);
#if defined(FG_DEBUG)
        if(g_fgDebugConfig.isDebugProfiling) {
            g_debugProfiling->end("GFX::Scene::FrustumCheck");
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
                pDrawCall->setShaderProgram(((fgGfxShaderManager *)getShaderManager())->getCurrentProgram());
            //pDrawCall->setModelMatrix(pObj->getRefModelMatrix());
            // getRefPriorityQueue().push(pDrawCall);
        }
    }
#endif
}

/**
 * 
 */
void fgGfxSceneManager::render(void) {
    //printf("fgGfxSceneManager::render(void)\n");
    //if(m_nodeQueue.empty())
    //    fgGfxSceneManager::sortCalls();
    fgGfxDrawingBatch::render(); // #NOPE ? i don't know what i'm doing
    while(!m_nodeQueue.empty()) {
#if defined(FG_DEBUG)
        if(g_fgDebugConfig.isDebugProfiling) {
            g_debugProfiling->begin("GFX::Scene::DrawNode");
        }
#endif
        fgGfxSceneNode *pSceneNode = m_nodeQueue.top();
        pSceneNode->draw();
#if defined(FG_DEBUG)
        if(g_fgDebugConfig.isDebugProfiling) {
            g_debugProfiling->end("GFX::Scene::DrawNode");
        }
#endif

#if defined(FG_DEBUG)
        if(g_fgDebugConfig.isDebugProfiling) {
            g_debugProfiling->begin("GFX::Scene::DrawAABBLines");
        }
        static_cast<fgGfxShaderManager *>(m_pShaderMgr)->getCurrentProgram()->setUniform(FG_GFX_USE_TEXTURE, 0.0f);
        if(FG_DEBUG_CFG_OPTION(gfxBBoxShow) && pSceneNode->getNodeType() == FG_GFX_SCENE_NODE_OBJECT) {

            fgGfxSceneNodeObject *pSceneObj = static_cast<fgGfxSceneNodeObject *>(pSceneNode);
            //g_fgDebugConfig.gfxBBoxShow
            // Current aabb - it's in model space (local)
            fgAABB3Df &modelBox = pSceneObj->getModel()->getRefAABB();
            // Initial Bounding box
            fgGfxPrimitives::drawAABBLines(modelBox);
            // Draw transformed bounding box #FIXME - colors FUBAR            
        }
        if(FG_DEBUG_CFG_OPTION(gfxBBoxShow)) {
            m_MVP.resetModelMatrix();
            static_cast<fgGfxShaderManager *>(m_pShaderMgr)->getCurrentProgram()->setUniform(&m_MVP);
            fgGfxPrimitives::drawAABBLines(pSceneNode->getRefAABB());
        }
        if(g_fgDebugConfig.isDebugProfiling) {
            g_debugProfiling->end("GFX::Scene::DrawAABBLines");
        }
#endif
        m_nodeQueue.pop();
    }
    //printf(".\n");
}

#if 0

/**
 * 
 * @param pObj
 * @param manage
 * @return 
 */
int fgGfxSceneManager::appendObject(fgGfxSceneNode *pObj, fgBool manage) {
    if(!pObj)
        return -1;
    if(m_objects.find(pObj) != -1)
        return -1;
    if(!pObj->getModel())
        return -1;

    fgGfxDrawCall *call = new fgGfxDrawCall(FG_GFX_DRAW_CALL_MODEL);
    call->setupFromModel(pObj->getModel());
    if(getShaderManager())
        call->setShaderProgram(((fgGfxShaderManager *)getShaderManager())->getCurrentProgram());
    if(m_resourceMgr) {
        fgGfxMaterial *pMainMaterial = pObj->getModel()->getMainMaterial();
        if(pMainMaterial) {
            fgTextureResource *pTexRes = (fgTextureResource *)((fgResourceManager *)m_resourceMgr)->get(pMainMaterial->ambientTexHandle);
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
    fgGfxDrawingBatch::appendDrawCall(call, FG_FALSE);

    return ((int)m_objects.size() - 1);
}

/**
 * 
 * @param index
 * @param pModelRes
 * @param manage
 * @return 
 */
fgGfxSceneNode *fgGfxSceneManager::appendModel(int& index,
                                               fgGfxModelResource* pModelRes,
                                               fgBool manage) {
    if(!pModelRes) {
        index = -1;
        return NULL;
    }
    fgGfxSceneNode *pObj = new fgGfxSceneNode();
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
fgBool fgGfxSceneManager::addNode(fgGfxSceneNodeHandle& nodeUniqueID,
                                  fgGfxSceneNode *pNode,
                                  fgGfxSceneNode *pFatherNode) {
    if(!pNode) {
        // Empty pointer - return
        FG_LOG_ERROR("GFX.SceneManager: // Empty pointer - exit... no addition made");
        return FG_FALSE;
    }

    if(fgHandleManager::isDataManaged(pNode)) {
        // Widget is already managed in the handle manager
        FG_LOG_ERROR("GFX.SceneManager: // Object is already managed in the handle manager: '%s'", pNode->getNameStr());
        return FG_FALSE;
    }

    if(!pNode->getHandle().isNull()) {
        // Widget has already initialized handle
        FG_LOG_ERROR("GFX.SceneManager: // Object has already initialized handle: '%s'", pNode->getNameStr());
        return FG_FALSE;
    }

    if(!fgHandleManager::acquireHandle(nodeUniqueID, pNode)) {
        // Could not aquire handle for the widget
        FG_LOG_ERROR("GFX.SceneManager: // Could not aquire handle for the object: '%s'", pNode->getNameStr());
        return FG_FALSE;
    }
    pNode->setHandle(nodeUniqueID);
    // By default object is set to be managed
    // However in some cases the 'managed' flag will
    // be set to FG_FALSE after addition
    pNode->setManaged(FG_TRUE);
    pNode->setManager(this); // Setup internal pointer to the manager
    pNode->setParent(pFatherNode); // Pointer to the parent (if any)

    if(!fgHandleManager::setupName(pNode->getName(), nodeUniqueID)) {
        // Could not setup handle string tag/name for the scene node
        // The handle name tag can be empty - sometimes it is not needed
        FG_LOG_ERROR("GFX.SceneManager: // Could not setup handle string tag/name for the object: '%s'", pNode->getNameStr());
    }
    //unsigned int index = pObj->getHandle().getIndex();

#if 1
    if(pNode->getNodeType() == FG_GFX_SCENE_NODE_OBJECT) {
        // #FIXME - this is total fubar
        fgGfxSceneNodeObject *pNodeObject = static_cast<fgGfxSceneNodeObject *>(pNode);
        fgGfxDrawCall *pDrawCall = (*pNodeObject->getChildren().begin())->getDrawCall();
        pDrawCall->setMVP(&m_MVP);
        if(pNodeObject->getModel()) {
            if(getShaderManager())
                pDrawCall->setShaderProgram(((fgGfxShaderManager *)getShaderManager())->getCurrentProgram());
            if(m_pResourceMgr) {
                fgGfxMaterial *pMainMaterial = pNodeObject->getModel()->getMainMaterial();
                if(pMainMaterial) {
                    fgTextureResource *pTexRes = (fgTextureResource *)((fgResourceManager *)m_pResourceMgr)->get(pMainMaterial->ambientTexHandle);
                    if(pTexRes)
                        pDrawCall->setTexture(pTexRes->getRefGfxID());
                }
            }
        }
    } else {
        fgGfxDrawCall *pDrawCall = pNode->getDrawCall();
        if(pDrawCall) {
            pDrawCall->setMVP(&m_MVP);
            if(getShaderManager())
                pDrawCall->setShaderProgram(((fgGfxShaderManager *)getShaderManager())->getCurrentProgram());
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
fgBool fgGfxSceneManager::addNode(fgGfxSceneNodeHandle& oUniqueID,
                                  fgGfxSceneNode *pObj,
                                  const fgGfxSceneNodeHandle& oFatherUniqueID) {
    return addNode(oUniqueID, pObj, fgHandleManager::dereference(oFatherUniqueID));
}

/**
 * 
 * @param oUniqueID
 * @param pObj
 * @param oFatherNameTag
 * @return 
 */
fgBool fgGfxSceneManager::addNode(fgGfxSceneNodeHandle& oUniqueID,
                                  fgGfxSceneNode *pObj,
                                  const std::string& oFatherNameTag) {
    return addNode(oUniqueID, pObj, fgHandleManager::dereference(oFatherNameTag));
}

/**
 * 
 * @param oUniqueID
 * @param pObj
 * @param oFatherNameTag
 * @return 
 */
fgBool fgGfxSceneManager::addNode(fgGfxSceneNodeHandle& oUniqueID,
                                  fgGfxSceneNode *pObj,
                                  const char* oFatherNameTag) {
    return addNode(oUniqueID, pObj, fgHandleManager::dereference(oFatherNameTag));
}

/**
 * 
 * @param pObj
 * @return 
 */
fgBool fgGfxSceneManager::remove(fgGfxSceneNode *pObj) {
    if(!pObj || !isManaged(pObj)) {
        return FG_FALSE;
    }
    pObj->setManaged(FG_FALSE);
    // Reset the manager pointer - object is not managed - it is no longer needed
    pObj->setManager(NULL);
    return fgHandleManager::releaseHandle(pObj->getHandle());
}

/**
 * 
 * @param oUniqueID
 * @return 
 */
fgBool fgGfxSceneManager::remove(const fgGfxSceneNodeHandle& oUniqueID) {
    return remove(fgHandleManager::dereference(oUniqueID));
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool fgGfxSceneManager::remove(const std::string& nameTag) {
    return remove(fgHandleManager::dereference(nameTag));
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool fgGfxSceneManager::remove(const char *nameTag) {
    return remove(fgHandleManager::dereference(nameTag));
}

/**
 * 
 * @param pObj
 * @return 
 */
fgBool fgGfxSceneManager::destroyNode(fgGfxSceneNode*& pObj) {
    if(!fgGfxSceneManager::remove(pObj)) {
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
fgBool fgGfxSceneManager::destroyNode(const fgGfxSceneNodeHandle& oUniqueID) {
    fgGfxSceneNode *pObj = fgHandleManager::dereference(oUniqueID);
    return destroyNode(pObj);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool fgGfxSceneManager::destroyNode(const std::string& nameTag) {
    fgGfxSceneNode *pObj = fgHandleManager::dereference(nameTag);
    return destroyNode(pObj);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool fgGfxSceneManager::destroyNode(const char *nameTag) {
    fgGfxSceneNode *pObj = fgHandleManager::dereference(nameTag);
    return destroyNode(pObj);
}

/**
 * 
 * @param oUniqueID
 * @return 
 */
fgGfxSceneNode* fgGfxSceneManager::get(const fgGfxSceneNodeHandle& oUniqueID) {
    return fgHandleManager::dereference(oUniqueID);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgGfxSceneNode* fgGfxSceneManager::get(const std::string& nameTag) {
    return fgHandleManager::dereference(nameTag);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgGfxSceneNode* fgGfxSceneManager::get(const char *nameTag) {
    return fgHandleManager::dereference(nameTag);
}

/**
 * 
 * @param pObj
 * @return 
 */
fgBool fgGfxSceneManager::isManaged(const fgGfxSceneNode *pObj) {
    if(!pObj) {
        return FG_FALSE;
    }
    if(FG_IS_INVALID_HANDLE(pObj->getHandle()) ||
       !fgHandleManager::isHandleValid(pObj->getHandle())) {
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
fgBool fgGfxSceneManager::isManaged(const fgGfxSceneNodeHandle& oUniqueID) {
    fgGfxSceneNode *pObj = get(oUniqueID);
    return (fgBool)(pObj != NULL);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool fgGfxSceneManager::isManaged(const std::string& nameTag) {
    fgGfxSceneNode *pObj = get(nameTag);
    return (fgBool)(pObj != NULL);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool fgGfxSceneManager::isManaged(const char *nameTag) {
    fgGfxSceneNode *pObj = get(nameTag);
    return (fgBool)(pObj != NULL);
}
