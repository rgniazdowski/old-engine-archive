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
void fgGfxDrawingBatch::setShaderManager(fgManagerBase *shaderMgr) {
    if(shaderMgr) {
        if(shaderMgr->getManagerType() != FG_MANAGER_GFX_SHADER)
            return;
    }
    m_shaderMgr = shaderMgr;
}

/*
 *
 */
fgGfxDrawCall *fgGfxDrawingBatch::createDrawCall(int &index, fgGfxDrawCallType type) {
    fgGfxDrawCall *drawCall = new fgGfxDrawCall();
    if(m_shaderMgr) {
        fgGfxShaderManager *shaderMgrPtr = (fgGfxShaderManager *)getShaderManager();
        drawCall->setShaderProgram(shaderMgrPtr->getCurrentProgram());
        static int i = 0;
        i++;
        if(i > 300) {
            if(shaderMgrPtr->getCurrentProgram())
                //printf("Setting shader in draw call to: '%s'\n", shaderMgrPtr->getCurrentProgram()->getNameStr());
            i = 0;

        }
    }
    drawCall->setDrawCallType(type);
    drawCall->setZIndex(m_zIndex);
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
int fgGfxDrawingBatch::appendDrawCall(fgGfxDrawCall* drawCall, fgBool check) {
    if(!drawCall)
        return -1;
    if(check && !m_drawCalls.empty()) {
        if(m_drawCalls.find(drawCall) != -1)
            return -1;
    }
    drawCall->setZIndex(m_zIndex);
    int index = m_drawCalls.size();
    m_drawCalls.push_back(drawCall);
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
    *itor = NULL;
    m_drawCalls.erase(itor);
    return drawCall;
}

/*
 *
 */
fgBool fgGfxDrawingBatch::removeDrawCall(fgGfxDrawCall *drawCall) {
    if(!drawCall)
        return FG_FALSE;
    fgVector<fgGfxDrawCall *>::iterator itor = m_drawCalls.begin(), end = m_drawCalls.end();
    for(; itor != end; itor++) {
        if(*itor == drawCall) {
            m_drawCalls.erase(itor);
            return FG_TRUE;
            break;
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
    delete drawCall;
    return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxDrawingBatch::deleteDrawCall(fgGfxDrawCall*& drawCall) {
    if(!drawCall || !fgGfxDrawingBatch::removeDrawCall(drawCall)) {
        return FG_FALSE;
    }
    delete drawCall;
    drawCall = NULL;
    return FG_TRUE;
}

/*
 *
 */
void fgGfxDrawingBatch::flush(void) {
    while(!m_priorityBatch.empty())
        m_priorityBatch.pop();

    for(int i = 0; i < (int)m_drawCalls.size(); i++) {
        fgGfxDrawCall *drawCall = m_drawCalls[i];
        m_drawCalls[i] = NULL;
        if(drawCall)
            delete drawCall;
    }
    m_drawCalls.clear();
    m_zIndex = 0;
}

/*
 *
 */
void fgGfxDrawingBatch::sortCalls(void) {
    while(!m_priorityBatch.empty())
        m_priorityBatch.pop();
    fgVector<fgGfxDrawCall *>::iterator itor = m_drawCalls.begin(), end = m_drawCalls.end();
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
        fgGfxDrawingBatch::sortCalls();

    while(!m_priorityBatch.empty()) {
        fgGfxDrawCall *drawCall = m_priorityBatch.top();
        drawCall->draw(); // YOLO
        m_priorityBatch.pop();
    }
}
