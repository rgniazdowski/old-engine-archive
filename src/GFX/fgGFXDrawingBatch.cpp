/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXDrawingBatch.h"
#include "GFX/Shaders/fgGFXShaderManager.h"

/*
 *
 */
fgGfxDrawingBatch::fgGfxDrawingBatch() :
m_shaderMgr(NULL) { }

/*
 *
 */
fgGfxDrawingBatch::~fgGfxDrawingBatch() {
    fgGfxDrawingBatch::flush();
}

/*
 *
 */
fgManagerBase *fgGfxDrawingBatch::getShaderManager(void) const {
    return m_shaderMgr;
}

/*
 *
 */
void fgGfxDrawingBatch::setShaderManager(fgManagerBase *pShaderMgr) {
    if(pShaderMgr) {
        if(pShaderMgr->getManagerType() != FG_MANAGER_GFX_SHADER)
            return;
    }
    m_shaderMgr = pShaderMgr;
}

/*
 *
 */
fgGfxDrawCall *fgGfxDrawingBatch::createDrawCall(int &index, fgGfxDrawCallType type) {
    fgGfxDrawCall *drawCall = new fgGfxDrawCall();
    if(m_shaderMgr) {
        fgGfxShaderManager *shaderMgrPtr = (fgGfxShaderManager *)getShaderManager();
        drawCall->setShaderProgram(shaderMgrPtr->getCurrentProgram());
    }
    drawCall->setDrawCallType(type);
    drawCall->setZIndex(m_zIndex);
    drawCall->setManaged(FG_TRUE);
    index = m_drawCalls.size();
    m_drawCalls.push_back(drawCall);
    return drawCall;
}

/*
 *
 */
fgGfxDrawCall *fgGfxDrawingBatch::getDrawCall(int index) {
    if(index < 0 || index >= (int)m_drawCalls.size())
        return NULL;
    return m_drawCalls[index];
}

/*
 *
 */
fgGfxDrawCall *fgGfxDrawingBatch::getLastDrawCall(void) {
    if(m_drawCalls.empty())
        return NULL;
    return m_drawCalls.back();
}

/*
 *
 */
int fgGfxDrawingBatch::appendDrawCall(fgGfxDrawCall* drawCall, fgBool manage, fgBool check) {
    if(!drawCall)
        return -1;
    if(check && !m_drawCalls.empty()) {
        if(m_drawCalls.find(drawCall) != -1)
            return -1;
    } 
    
    drawCall->setZIndex(m_zIndex);
    drawCall->setManaged(manage);
    int index = m_drawCalls.size();
    m_drawCalls.push_back(drawCall);
    if(!check) {
        // This draw call will not be checked for repetition in the batch
        // Need to remember this draw call to manage erasing/deletion
        if(m_duplicates.find(drawCall) == -1)
            m_duplicates.push_back(drawCall);
    }
    return index;
}

/*
 *
 */
fgGfxDrawCall *fgGfxDrawingBatch::removeDrawCall(int index) {
    if(index >= (int)m_drawCalls.size() || index < 0)
        return NULL;
    fgVector<fgGfxDrawCall *>::iterator itor = m_drawCalls.begin() + index;
    fgGfxDrawCall *drawCall = *itor;
    removeDrawCall(drawCall);
    return drawCall;
}

/**
 * Removes the specified draw call from the drawing batch
 * @param drawCall
 * @return 
 */
fgBool fgGfxDrawingBatch::removeDrawCall(fgGfxDrawCall *drawCall) {
    if(!drawCall)
        return FG_FALSE;
    int dupIdx = -1;
    if((dupIdx = m_duplicates.find(drawCall)) != -1) {
        m_duplicates[dupIdx] = NULL;
    }
    drawCallVecItor itor = m_drawCalls.begin(), end = m_drawCalls.end();
    for(; itor != end; itor++) {
        if(*itor == drawCall) {
            drawCall->setManaged(FG_FALSE);
            m_drawCalls.erase(itor);
            if(dupIdx < 0) {
                return FG_TRUE;
            } else {
                itor--;
                end = m_drawCalls.end();
            }
        }
    }
    return FG_FALSE;
}

/*
 *
 */
fgBool fgGfxDrawingBatch::deleteDrawCall(int index) {
    fgGfxDrawCall *drawCall = fgGfxDrawingBatch::removeDrawCall(index);
    if(!drawCall)
        return FG_FALSE;
    if(drawCall->isManaged()) {
        delete drawCall;
    } else {
        return FG_FALSE;
    }
    return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxDrawingBatch::deleteDrawCall(fgGfxDrawCall*& drawCall) {
    if(!drawCall || !fgGfxDrawingBatch::removeDrawCall(drawCall)) {
        return FG_FALSE;
    }
    if(drawCall->isManaged()) {
        delete drawCall;
        drawCall = NULL;
    } else {
        return FG_FALSE;
    }
    return FG_TRUE;
}

/*
 *
 */
void fgGfxDrawingBatch::flush(void) {
    while(!m_priorityBatch.empty())
        m_priorityBatch.pop();
    
    drawCallVecItor it = m_duplicates.begin(), end = m_duplicates.end();
    for(;it!=end;it++) {
        fgBool managed = FG_FALSE;
        if(*it) {
            fgGfxDrawCall *drawCall = *it;
            if(drawCall->isManaged())
                managed = FG_TRUE;
            removeDrawCall(drawCall);
            if(managed)
                delete drawCall;
            m_duplicates.erase(it);
            it--;
            end = m_duplicates.end();
        }
    }
    while(!m_drawCalls.empty()) {
        fgGfxDrawCall *& drawCall = m_drawCalls.back();
        if(drawCall->isManaged())
            delete drawCall;
        drawCall = NULL;
        m_drawCalls.pop_back();
    }
    m_zIndex = 0;
}

/*
 *
 */
void fgGfxDrawingBatch::sortCalls(void) {
    while(!m_priorityBatch.empty())
        m_priorityBatch.pop();
    drawCallVecItor itor = m_drawCalls.begin(), end = m_drawCalls.end();
    for(; itor != end; itor++) {
        if(*itor)
            m_priorityBatch.push(*itor);
    }
}

/*
 *
 */
void fgGfxDrawingBatch::render(void) {
    if(m_priorityBatch.empty())
        sortCalls();

    while(!m_priorityBatch.empty()) {
        fgGfxDrawCall *drawCall = m_priorityBatch.top();
        drawCall->draw(); // YOLO
        m_priorityBatch.pop();
    }
}
