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
#include "fgGFXDrawableObject.h"
#include "fgDebugConfig.h"

/**
 * 
 */
fgGfxSceneManager::fgGfxSceneManager() :
fgGfxDrawingBatch(),
m_MVP(),
m_camera(FG_GFX_CAMERA_FREE),
m_objDrawCalls() {
    m_objDrawCalls.reserve(16);
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
    m_objDrawCalls.clear_optimised();
    m_objDrawCalls.reserve(0);
    m_objDrawCalls.resize(0);
}

/**
 * 
 * @return 
 */
fgBool fgGfxSceneManager::destroy(void) {
    fgGfxDrawingBatch::flush();
    //objectVecItor oit = m_objects.begin(), oend = m_objects.end();
    drawCallVecItor dit = m_objDrawCalls.begin(), dend = m_objDrawCalls.end();

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
        fgGfxObject *pObj = *itor;
        if(pObj == NULL)
            continue;
        if(pObj->getType() == FG_GFX_OBJECT_DRAWABLE_MODEL) {
            //fgGfxDrawCall *pDrawCall = getDrawCall(pObj);
            unsigned int index = pObj->getHandle().getIndex();
            if(index < m_objDrawCalls.size()) {
                m_objDrawCalls[index] = NULL;
            }
        }
        if(pObj->isManaged())
            delete pObj;
        *itor = NULL;
    }
    // Delete all gfx draw calls (they match objects in the scene)
    for(; dit != dend; dit++) {
        if(*dit) {
            if((*dit)->isManaged() == FG_FALSE)
                delete (*dit);
            *dit = NULL;
        }
    }
    fgGfxSceneManager::clear();
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool fgGfxSceneManager::initialize(void) {
    m_objDrawCalls.reserve(16);
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
    while(!m_drawableQueue.empty())
        m_drawableQueue.pop();
}

/**
 * 
 */
void fgGfxSceneManager::sortCalls(void) {
    if(!getShaderManager())
        return;
    //fgGfxDrawingBatch::sortCalls();
    while(!getRefPriorityQueue().empty())
        getRefPriorityQueue().pop();
    while(!m_drawableQueue.empty())
        m_drawableQueue.pop();
    drawCallVecItor objDrawIt = m_objDrawCalls.begin(), objDrawEnd = m_objDrawCalls.end();
    //objectVecItor objVecIt = m_objects.begin(), objVecEnd = m_objects.end();
    hmDataVecItor itor = getRefDataVector().begin(), end = getRefDataVector().end();

#if 1
    for(; itor != end; itor++) {
        if(!(*itor))
            continue;
        fgGfxObject *pObj = (*itor);
        fgGfxDrawableObject *pDrawableObj = NULL;
        fgGfxDrawCall *pDrawCall = NULL;
        if(pObj->getType() == FG_GFX_OBJECT_DRAWABLE_MODEL) {
            pDrawableObj = static_cast<fgGfxDrawableObject *>(pObj);
            m_drawableQueue.push(pDrawableObj);
            //pDrawableObj->setManaged();            
            pDrawCall = NULL;//static_cast<fgGfxDrawCall *>(pDrawableObj);
        } else {
            pDrawCall = m_objDrawCalls[pObj->getHandle().getIndex()];
        }
        if(!pDrawCall)
            continue;
        if(!pDrawCall->getShaderProgram())
            pDrawCall->setShaderProgram(((fgGfxShaderManager *)getShaderManager())->getCurrentProgram());
        //pDrawCall->setModelMatrix(pObj->getRefModelMatrix());
        getRefPriorityQueue().push(pDrawCall);
    }
#endif
    //for(; itor != end; itor++)

    /*for(; objDrawIt != objDrawEnd, objVecIt != objVecEnd; objDrawIt++, objVecIt++) {
        if(*objDrawIt && *objVecIt) {
            fgGfxObject *obj = (*objVecIt);
            fgGfxDrawCall *drawCall = (*objDrawIt);
            if(!drawCall->getShaderProgram())
                drawCall->setShaderProgram(((fgGfxShaderManager *)getShaderManager())->getCurrentProgram());
            drawCall->setModelMatrix(obj->getRefModelMatrix());
            getRefPriorityQueue().push(drawCall);
        }
    }*/
}

/**
 * 
 */
void fgGfxSceneManager::render(void) {
    m_MVP.calculate(&m_camera, fgMatrix4f());
    //fgGfxDrawingBatch::render();

    if(getRefPriorityQueue().empty())
        sortCalls();

    if(true) {
        while(!getRefPriorityQueue().empty()) {
            fgGfxDrawCall *pDrawCall = getRefPriorityQueue().top();
            pDrawCall->draw(); // YOLO
            getRefPriorityQueue().pop();
        }
    }
    while(!m_drawableQueue.empty()) {
        fgGfxDrawableObject *pDrawableObj = m_drawableQueue.top();
        pDrawableObj->draw(pDrawableObj->getRefModelMatrix());
#if defined(FG_DEBUG)
        if(FG_DEBUG_CFG_OPTION(gfxBBoxShow)) {
            //g_fgDebugConfig.gfxBBoxShow
            fgGfxPrimitives::drawAABBLines(pDrawableObj->getModel()->getRefAABB());
        }
#endif
        m_drawableQueue.pop();        
    }
}

#if 0

/**
 * 
 * @param pObj
 * @param manage
 * @return 
 */
int fgGfxSceneManager::appendObject(fgGfxObject *pObj, fgBool manage) {
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
fgGfxObject *fgGfxSceneManager::appendModel(int& index,
                                            fgGfxModelResource* pModelRes,
                                            fgBool manage) {
    if(!pModelRes) {
        index = -1;
        return NULL;
    }
    fgGfxObject *pObj = new fgGfxObject();
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
fgBool fgGfxSceneManager::addObject(fgGfxObjectHandle& oUniqueID,
                                    fgGfxObject *pObj,
                                    fgGfxObject *oFatherObj) {
    if(!pObj) {
        // Empty pointer - return
        FG_LOG_ERROR("GFX.SceneManager: // Empty pointer - exit... no addition made");
        return FG_FALSE;
    }

    if(fgHandleManager::isDataManaged(pObj)) {
        // Widget is already managed in the handle manager
        FG_LOG_ERROR("GFX.SceneManager: // Object is already managed in the handle manager: '%s'", pObj->getNameStr());
        return FG_FALSE;
    }

    if(!pObj->getHandle().isNull()) {
        // Widget has already initialized handle
        FG_LOG_ERROR("GFX.SceneManager: // Object has already initialized handle: '%s'", pObj->getNameStr());
        return FG_FALSE;
    }

    if(!fgHandleManager::acquireHandle(oUniqueID, pObj)) {
        // Could not aquire handle for the widget
        FG_LOG_ERROR("GFX.SceneManager: // Could not aquire handle for the object: '%s'", pObj->getNameStr());
        return FG_FALSE;
    }
    pObj->setHandle(oUniqueID);
    // By default object is set to be managed
    // However in some cases the 'managed' flag will
    // be set to FG_FALSE after addition
    pObj->setManaged(FG_TRUE);

    if(!fgHandleManager::setupName(pObj->getName(), oUniqueID)) {
        // Could not setup handle string tag/name for the widget
        FG_LOG_ERROR("GFX.SceneManager: // Could not setup handle string tag/name for the object: '%s'", pObj->getNameStr());
    }
    unsigned int index = pObj->getHandle().getIndex();

    // #FIXME 

    fgGfxDrawCall *drawCall = NULL;
    // FIXME
    if(pObj->getModel() && pObj->getType() == FG_GFX_OBJECT_DRAWABLE_MODEL) {
        // #FIXME ... need some mechanism for up/down casting
        fgGfxDrawableObject *pDrawableObj = static_cast<fgGfxDrawableObject *>(pObj);
        pDrawableObj->setManaged(FG_TRUE);
        drawCall = static_cast<fgGfxDrawCall *>(pDrawableObj);
    } else if(pObj->getModel() && pObj->getType() == FG_GFX_OBJECT_MODEL) {
        drawCall = new fgGfxDrawCall(FG_GFX_DRAW_CALL_MODEL);
        drawCall->setupFromModel(pObj->getModel());
    }
    if(pObj->getModel()) {
        if(getShaderManager())
            drawCall->setShaderProgram(((fgGfxShaderManager *)getShaderManager())->getCurrentProgram());
        if(m_pResourceMgr) {
            fgGfxMaterial *pMainMaterial = pObj->getModel()->getMainMaterial();
            if(pMainMaterial) {
                fgTextureResource *pTexRes = (fgTextureResource *)((fgResourceManager *)m_pResourceMgr)->get(pMainMaterial->ambientTexHandle);
                if(pTexRes)
                    drawCall->setTexture(pTexRes->getRefGfxID());
            }
        }
    } else {
        drawCall = new fgGfxDrawCall(FG_GFX_DRAW_CALL_CUSTOM_ARRAY);
    }

    drawCall->setMVP(&m_MVP);
    if(index >= m_objDrawCalls.size()) {
#if defined(FG_USING_MARMALADE)
        m_objDrawCalls.resize((unsigned int)(index + 1));
#else
        m_objDrawCalls.resize((unsigned int)(index + 1), NULL);
#endif
    }
    m_objDrawCalls[index] = drawCall;
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
fgBool fgGfxSceneManager::addObject(fgGfxObjectHandle& oUniqueID,
                                    fgGfxObject *pObj,
                                    const fgGfxObjectHandle& oFatherUniqueID) {
    return addObject(oUniqueID, pObj, fgHandleManager::dereference(oFatherUniqueID));
}

/**
 * 
 * @param oUniqueID
 * @param pObj
 * @param oFatherNameTag
 * @return 
 */
fgBool fgGfxSceneManager::addObject(fgGfxObjectHandle& oUniqueID,
                                    fgGfxObject *pObj,
                                    const std::string& oFatherNameTag) {
    return addObject(oUniqueID, pObj, fgHandleManager::dereference(oFatherNameTag));
}

/**
 * 
 * @param oUniqueID
 * @param pObj
 * @param oFatherNameTag
 * @return 
 */
fgBool fgGfxSceneManager::addObject(fgGfxObjectHandle& oUniqueID,
                                    fgGfxObject *pObj,
                                    const char* oFatherNameTag) {
    return addObject(oUniqueID, pObj, fgHandleManager::dereference(oFatherNameTag));
}

/**
 * 
 * @param pObj
 * @return 
 */
fgBool fgGfxSceneManager::remove(fgGfxObject *pObj) {
    if(!pObj || !isManaged(pObj)) {
        return FG_FALSE;
    }
    pObj->setManaged(FG_FALSE);
    unsigned int index = (unsigned int)pObj->getHandle().getIndex();
    removeDrawCall(m_objDrawCalls[index]);
    delete m_objDrawCalls[index];
    m_objDrawCalls[index] = NULL;
    return fgHandleManager::releaseHandle(pObj->getHandle());
}

/**
 * 
 * @param oUniqueID
 * @return 
 */
fgBool fgGfxSceneManager::remove(const fgGfxObjectHandle& oUniqueID) {
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
fgBool fgGfxSceneManager::destroyObject(fgGfxObject*& pObj) {
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
fgBool fgGfxSceneManager::destroyObject(const fgGfxObjectHandle& oUniqueID) {
    fgGfxObject *pObj = fgHandleManager::dereference(oUniqueID);
    return destroyObject(pObj);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool fgGfxSceneManager::destroyObject(const std::string& nameTag) {
    fgGfxObject *pObj = fgHandleManager::dereference(nameTag);
    return destroyObject(pObj);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool fgGfxSceneManager::destroyObject(const char *nameTag) {
    fgGfxObject *pObj = fgHandleManager::dereference(nameTag);
    return destroyObject(pObj);
}

/**
 * 
 * @param oUniqueID
 * @return 
 */
fgGfxObject* fgGfxSceneManager::get(const fgGfxObjectHandle& oUniqueID) {
    return fgHandleManager::dereference(oUniqueID);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgGfxObject* fgGfxSceneManager::get(const std::string& nameTag) {
    return fgHandleManager::dereference(nameTag);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgGfxObject* fgGfxSceneManager::get(const char *nameTag) {
    return fgHandleManager::dereference(nameTag);
}

/**
 * 
 * @param pObj
 * @return 
 */
fgBool fgGfxSceneManager::isManaged(const fgGfxObject *pObj) {
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
fgBool fgGfxSceneManager::isManaged(const fgGfxObjectHandle& oUniqueID) {
    fgGfxObject *pObj = get(oUniqueID);
    return (fgBool)(pObj != NULL);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool fgGfxSceneManager::isManaged(const std::string& nameTag) {
    fgGfxObject *pObj = get(nameTag);
    return (fgBool)(pObj != NULL);
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgBool fgGfxSceneManager::isManaged(const char *nameTag) {
    fgGfxObject *pObj = get(nameTag);
    return (fgBool)(pObj != NULL);
}

/**
 * 
 * @param pObj
 * @return 
 */
fgGfxDrawCall *fgGfxSceneManager::getDrawCall(const fgGfxObject* pObj) {
    if(!isManaged(pObj))
        return NULL;

    unsigned int index = pObj->getHandle().getIndex();
    if(index >= m_objDrawCalls.size())
        return NULL;
    return m_objDrawCalls[index];
}

/**
 * 
 * @param oUniqueID
 * @return 
 */
fgGfxDrawCall *fgGfxSceneManager::getDrawCall(const fgGfxObjectHandle& oUniqueID) {
    return getDrawCall(dereference(oUniqueID));
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgGfxDrawCall *fgGfxSceneManager::getDrawCall(const std::string& nameTag) {
    return getDrawCall(dereference(nameTag));
}

/**
 * 
 * @param nameTag
 * @return 
 */
fgGfxDrawCall *fgGfxSceneManager::getDrawCall(const char *nameTag) {
    return getDrawCall(dereference(nameTag));
}
