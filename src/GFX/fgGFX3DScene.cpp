/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFX3DScene.h"
#include "Shaders/fgGFXShaderManager.h"
#include "Textures/fgTextureResource.h"
#include "Resource/fgResourceManager.h"

/**
 * 
 */
fgGfx3DScene::fgGfx3DScene() :
fgGfxDrawingBatch(),
m_MVP(),
m_camera(FG_GFX_CAMERA_FREE),
m_objects(),
m_objDrawCalls() {
    m_MVP.setPerspective(45.0f, 4.0f / 3.0f);
}

/**
 * 
 */
fgGfx3DScene::~fgGfx3DScene() { 
    fgGfxDrawingBatch::flush();
    objectVecItor oit = m_objects.begin(), oend = m_objects.end();
    drawCallVecItor dit = m_objDrawCalls.begin(), dend = m_objDrawCalls.end();
    
    // Delete all gfx objects in the scene
    for(;oit!=oend;oit++) {
        if(*oit) {
            if((*oit)->isManaged() == FG_TRUE)
                delete (*oit);
            *oit = NULL;
        }
    }
    m_objects.clear_optimised();
    
    // Delete all gfx draw calls (they match objects in the scene)
    for(;dit!=dend;dit++) {
        if(*dit) {
            if((*dit)->isManaged() == FG_FALSE)
                delete (*dit);
            *dit = NULL;
        }
    }
    m_objDrawCalls.clear_optimised();
    m_resourceMgr = NULL;
}

/**
 * 
 * @param shaderMgr
 */
void fgGfx3DScene::setShaderManager(fgManagerBase* pShaderMgr) {
    fgGfxDrawingBatch::setShaderManager(pShaderMgr);
}

/**
 * 
 * @param pResourceMgr
 */
void fgGfx3DScene::setResourceManager(fgManagerBase *pResourceMgr) {
    if(!pResourceMgr)
        return;
    if(pResourceMgr->getManagerType() == FG_MANAGER_RESOURCE)
        m_resourceMgr = pResourceMgr;
}

/**
 * 
 * @return 
 */
fgManagerBase *fgGfx3DScene::getResourceManager(void) const {
    return m_resourceMgr;
}

/**
 * 
 */
void fgGfx3DScene::flush(void) { 
    fgGfxDrawingBatch::flush();
}

/**
 * 
 */
void fgGfx3DScene::sortCalls(void) {
    if(!getShaderManager())
        return;
    //fgGfxDrawingBatch::sortCalls();
    while(!getRefPriorityQueue().empty())
        getRefPriorityQueue().pop();
    drawCallVecItor objDrawIt = m_objDrawCalls.begin(), objDrawEnd = m_objDrawCalls.end();
    objectVecItor objVecIt = m_objects.begin(), objVecEnd = m_objects.end();
    
    for(; objDrawIt != objDrawEnd, objVecIt != objVecEnd; objDrawIt++, objVecIt++) {
        if(*objDrawIt && *objVecIt) {
            fgGfxObject *obj = (*objVecIt);
            fgGfxDrawCall *drawCall = (*objDrawIt);
            if(!drawCall->getShaderProgram())
                drawCall->setShaderProgram(((fgGfxShaderManager *)getShaderManager())->getCurrentProgram());
            drawCall->setModelMatrix(obj->getRefModelMatrix());
            getRefPriorityQueue().push(drawCall);
        }
    }
}

/**
 * 
 */
void fgGfx3DScene::render(void) {
    m_MVP.calculate(&m_camera, fgMatrix4f());
    fgGfxDrawingBatch::render();
}

/**
 * 
 * @param pObj
 * @param manage
 * @return 
 */
int fgGfx3DScene::appendObject(fgGfxObject *pObj, fgBool manage) {
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
fgGfxObject *fgGfx3DScene::appendModel(int& index, 
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
