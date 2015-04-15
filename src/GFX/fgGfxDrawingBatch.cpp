/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGfxDrawingBatch.h"
#include "GFX/Shaders/fgGfxShaderManager.h"

using namespace fg;

gfx::CDrawingBatch::CDrawingBatch(const unsigned int reservedSize,
                                  const fgGfxDrawCallType drawCallType,
                                  const fgGFXuint attribMask) :
m_numDrawCalls(0),
m_reservedSize(0),
m_numNotManaged(0),
m_defaultDrawCallType(drawCallType),
m_defaultAttribMask(attribMask),
m_scissorBox(0, 0, 0, 0),
m_relMove(),
m_pShaderMgr(NULL) {
    reserve(reservedSize);
}

gfx::CDrawingBatch::~CDrawingBatch() {
    gfx::CDrawingBatch::flush();
    reserve(0, FG_TRUE); // force down-resize
    /*for(unsigned int i=0;i<m_reservedSize;i++) {
        if(m_drawCalls[i] == NULL)
            continue;
        if(m_drawCalls[i]->isManaged()) {
            reserve(0);
        } 
    }*/
    m_freeSlots.clear_optimised();
    m_drawCalls.clear_optimised();
}

void gfx::CDrawingBatch::setShaderManager(fg::base::CManager *pShaderMgr) {
    if(pShaderMgr) {
        if(pShaderMgr->getManagerType() != FG_MANAGER_GFX_SHADER)
            return;
    }
    m_pShaderMgr = pShaderMgr;
}

gfx::CDrawCall *gfx::CDrawingBatch::requestDrawCall(int &index,
                                                    const fgGfxDrawCallType type,
                                                    const fgGFXuint attribMask,
                                                    gfx::CShaderProgram *pProgram) {
    CDrawCall *drawCall = NULL;
    if(m_freeSlots.empty()) {
        // Increase the number of drawcalls, get the next drawcall index
        drawCall = m_drawCalls[m_numDrawCalls];
        index = m_numDrawCalls;
        m_numDrawCalls++;
        if(m_numDrawCalls >= m_reservedSize) {
            // Reserved size exceeded, realloc giving 30% more
            reserve((unsigned int)((float)m_reservedSize * 1.3f));
        }
    } else {
        index = getFreeSlot(-1);
        drawCall = new CDrawCall(type, attribMask);
        m_drawCalls[index] = drawCall;
    }
    // fgGfxDrawCall *drawCall = new fgGfxDrawCall(type, attribMask);
    if(m_pShaderMgr && !pProgram) {
        gfx::CShaderManager *shaderMgrPtr = static_cast<gfx::CShaderManager *>(getShaderManager());
        drawCall->setShaderProgram(shaderMgrPtr->getCurrentProgram());
    } else {
        drawCall->setShaderProgram(pProgram);
    }
    drawCall->setDrawCallType(type);
    drawCall->setComponentActive(attribMask, FG_TRUE);
    drawCall->setZIndex(m_zIndex);
    drawCall->setManaged(FG_TRUE);
    drawCall->setTexture(STextureID());
    drawCall->setColor(fgColor3f(1.0f, 1.0f, 1.0f));
    drawCall->setRelMove(m_relMove);
    drawCall->setScissorBox(m_scissorBox);
    //m_drawCalls.push_back(drawCall);
    return drawCall;
}

gfx::CDrawCall *gfx::CDrawingBatch::getDrawCall(int index) {
    if(index < 0 || index >= (int)m_drawCalls.size())
        return NULL;
    return m_drawCalls[index];
}

gfx::CDrawCall *gfx::CDrawingBatch::getLastDrawCall(void) {
    if(m_numDrawCalls == 0)
        return NULL;
    //return m_drawCalls.back();
    return m_drawCalls[m_numDrawCalls - 1];
}

int gfx::CDrawingBatch::appendDrawCall(CDrawCall* drawCall,
                                       fgBool manage,
                                       fgBool check) {
    if(!drawCall)
        return -1;
    if(check && !m_drawCalls.empty()) {
        if(m_drawCalls.find(drawCall) != -1)
            return -1;
    }
    if(!manage)
        m_numNotManaged++;
    int index = -1;
    drawCall->setZIndex(m_zIndex);
    drawCall->setManaged(manage);
    if(!m_freeSlots.empty()) {
        index = getFreeSlot(-1);
        m_drawCalls[index] = drawCall;
    } else {
        delete m_drawCalls[m_numDrawCalls];
        m_drawCalls[m_numDrawCalls] = drawCall;
        index = m_numDrawCalls;
        m_numDrawCalls++;
        if(m_numDrawCalls >= m_reservedSize) {
            // Reserved size exceeded, realloc giving 30% more
            reserve((unsigned int)((float)m_reservedSize * 1.3f));
        }
        //index = m_drawCalls.size();
        //m_drawCalls.push_back(drawCall);
    }
    if(!check) {
        // This draw call will not be checked for repetition in the batch
        // Need to remember this draw call to manage erasing/deletion
        if(m_duplicates.find(drawCall) == -1)
            m_duplicates.push_back(drawCall);
    }
    drawCall->setRelMove(m_relMove);
    drawCall->setScissorBox(m_scissorBox);
    return index;
}

gfx::CDrawCall *gfx::CDrawingBatch::removeDrawCall(int index) {
    if(index >= (int)m_numDrawCalls || index < 0)
        return NULL;
    CDrawCall *drawCall = m_drawCalls[index];
    //removeDrawCall(drawCall);
    int dupIdx = -1;
    if((dupIdx = m_duplicates.find(drawCall)) != -1) {
        m_duplicates[dupIdx] = NULL;
    }
    if(m_freeSlots.find(index) == -1)
        m_freeSlots.push_back(index);
    m_drawCalls[index] = NULL;
    if(drawCall->isManaged() == FG_FALSE && m_numNotManaged)
        m_numNotManaged--;
    else
        drawCall->setManaged(FG_FALSE);

    if(!dupIdx)
        return drawCall;
    // If there are duplicates - they need to be removed also
    for(unsigned int i = 0; i < m_numDrawCalls; i++) {
        if(m_drawCalls[i] == drawCall) {
            m_drawCalls[i] = NULL;
            m_freeSlots.push_back(index);
            if(!drawCall->isManaged() && m_numNotManaged)
                m_numNotManaged--;
        }
    }
    return drawCall;
}

fgBool gfx::CDrawingBatch::removeDrawCall(CDrawCall *drawCall) {
    if(!drawCall)
        return FG_FALSE;
    int dupIdx = -1;
    if((dupIdx = m_duplicates.find(drawCall)) != -1) {
        m_duplicates[dupIdx] = NULL;
    }
    int index = 0;
    DrawCallVecItor itor = m_drawCalls.begin(), end = m_drawCalls.end();
    for(; itor != end; itor++) {
        if(*itor == drawCall) {
            if(!drawCall->isManaged() && m_numNotManaged)
                m_numNotManaged--;
            drawCall->setManaged(FG_FALSE);
            m_freeSlots.push_back(index);
            *itor = NULL;
            m_drawCalls[index] = NULL; // what?
            //m_drawCalls.erase(itor);
            if(dupIdx < 0) {
                return FG_TRUE;
            } else {
                // itor--;
                // index--;
                // end = m_drawCalls.end();
            }
        }
        index++;
    }
    return FG_FALSE;
}

fgBool gfx::CDrawingBatch::deleteDrawCall(int index) {
    fgBool isManaged = FG_FALSE;
    if(index < (int)m_numDrawCalls && index >= 0) {
        if(m_drawCalls[index]) {
            if(m_drawCalls[index]->isManaged() == FG_TRUE)
                isManaged = FG_TRUE;
        }
    }
    CDrawCall *drawCall = gfx::CDrawingBatch::removeDrawCall(index);
    if(!drawCall)
        return FG_FALSE;
    if(isManaged) {
        delete drawCall;
    } else {
        return FG_FALSE;
    }
    return FG_TRUE;
}

fgBool gfx::CDrawingBatch::deleteDrawCall(CDrawCall*& drawCall) {
    if(!drawCall) {
        return FG_FALSE;
    }
    // Need to remember the 'isManaged' flag before removal
    // - when draw call is removed the flag is automaticall set to false
    fgBool isManaged = drawCall->isManaged();
    if(!gfx::CDrawingBatch::removeDrawCall(drawCall)) {
        return FG_FALSE;
    }
    if(isManaged) {
        delete drawCall;
        drawCall = NULL;
    } else {
        return FG_FALSE;
    }
    return FG_TRUE;
}

int gfx::CDrawingBatch::getFreeSlot(int maximum) {
    if(m_freeSlots.empty())
        return -1; // ?
    if(maximum < 0) {
        int index = m_freeSlots.back();
        m_freeSlots.pop_back();
        return index;
    }
    FreeSlotsVecItor it = m_freeSlots.begin(), end = m_freeSlots.end();
    for(; it != end; it++) {
        if(*it <= (unsigned int)maximum) {
            int index = *it;
            m_freeSlots.erase(it);
            return index;
        }
    }
    return -1;
}

void gfx::CDrawingBatch::reserve(unsigned int reservedSize, fgBool force) {
    if(m_reservedSize > reservedSize && force) {
        int remaining = m_numNotManaged;
        std::stack<CDrawCall *> notManagedCalls;
        // The drawing batch preallocates the drawcalls for usage
        // any drawcall can have parameters changed
        // When the capacity of the drawing batch changes some of the remaining
        // drawcalls need to freed (delete). Not managed drawcalls need to find
        // some free spots
        for(unsigned int i = reservedSize; i < m_reservedSize; i++) {
            if(m_drawCalls[i]) {
                if(m_drawCalls[i]->isManaged() == FG_FALSE && reservedSize) {
                    // This drawcall is not managed so it needs to be retained
                    int index = getFreeSlot(reservedSize - 1);
                    if(index != -1) {
                        m_drawCalls[index] = m_drawCalls[i];
                        m_drawCalls[i] = NULL;
                        remaining--;
                    } else {
                        notManagedCalls.push(m_drawCalls[i]);
                        // ?
                    }
                } else if(m_drawCalls[i]->isManaged()) {
                    // draw call is managed - just delete it
                    delete m_drawCalls[i];
                    m_drawCalls[i] = NULL;
                }
            }
        }
        // This will be useful to reset number of not managed draw calls 
        m_numNotManaged = 0;
        if(remaining > 0) {
            // Now will need to search for any managed call
            for(unsigned int i = 0; i < reservedSize; i++) {
                if(m_drawCalls[i]->isManaged() && !notManagedCalls.empty()) {
                    delete m_drawCalls[i];
                    m_drawCalls[i] = notManagedCalls.top();
                    notManagedCalls.pop();
                    m_numNotManaged++;
                } else if(!m_drawCalls[i]->isManaged()) {
                    m_numNotManaged++;
                }
            }
        }
        m_drawCalls.reserve(reservedSize);
        m_drawCalls.resize(reservedSize);
        m_reservedSize = reservedSize;
        if(m_numDrawCalls > reservedSize)
            m_numDrawCalls = reservedSize;
    } else if(m_reservedSize < reservedSize) {
        m_drawCalls.reserve(reservedSize);
        m_drawCalls.resize(reservedSize);
        for(unsigned int i = m_reservedSize; i < reservedSize; i++) {
            m_drawCalls[i] = new CDrawCall(m_defaultDrawCallType, m_defaultAttribMask); // Preallocate space for draw calls
            m_drawCalls[i]->setManaged(FG_TRUE);
        }
        m_reservedSize = reservedSize;

    } else /*equal*/ {
        // do nothing
    }
}

void gfx::CDrawingBatch::flush(void) {
    while(!m_priorityBatch.empty())
        m_priorityBatch.pop();

    // With preallocation just remove not managed drawcalls

    int nDuplicates = m_duplicates.size();
    for(int i = 0; i < nDuplicates; i++) {
        CDrawCall *drawCall = m_duplicates[i];
        if(drawCall) {
            if(drawCall->isManaged() == FG_FALSE)
                removeDrawCall(drawCall);
            m_duplicates[i] = NULL;
        }
    }

    for(unsigned int i = 0; i < m_numDrawCalls; i++) {
        if(m_drawCalls[i] == NULL)
            continue;
        if(m_drawCalls[i]->isManaged() == FG_FALSE) {
            removeDrawCall(m_drawCalls[i]);
        } else {
            m_drawCalls[i]->flush();
        }
    }
    m_numDrawCalls = 0;
    m_zIndex = 0;
    m_relMove = Vector3f();
    m_scissorBox = Vector4i();
    /*
    int nDuplicates = m_duplicates.size();
    for(int i=0;i<nDuplicates;i++) {
        fgBool managed = FG_FALSE;
        fgGfxDrawCall *drawCall = m_duplicates[i];
        if(drawCall) {
            if(drawCall->isManaged())
                managed = FG_TRUE;
            removeDrawCall(drawCall);
            if(managed)
                delete drawCall;
            m_duplicates[i] = NULL;
        }
    }
    while(!m_drawCalls.empty()) {
        fgGfxDrawCall *& drawCall = m_drawCalls.back();
        if(drawCall->isManaged())
            delete drawCall;
        drawCall = NULL;
        m_drawCalls.pop_back();
    }
    m_zIndex = 0; */
}

void gfx::CDrawingBatch::sortCalls(void) {
    while(!m_priorityBatch.empty())
        m_priorityBatch.pop();
    //drawCallVecItor itor = m_drawCalls.begin(), end = m_drawCalls.end();
    //for(; itor != end; itor++) {
    for(unsigned int i = 0; i < m_numDrawCalls; i++) {
        //    if(*itor)
        CDrawCall *drawCall = m_drawCalls[i];
        if(drawCall)
            m_priorityBatch.push(drawCall);
    }
}

void gfx::CDrawingBatch::render(void) {
    if(m_priorityBatch.empty())
        gfx::CDrawingBatch::sortCalls(); // #FIX - need to call via fgGfxDrawingBatch to avoid duplicate call (virtual)
    int i = 0;
    while(!m_priorityBatch.empty()) {
        CDrawCall *pDrawCall = m_priorityBatch.top();
        //static_cast<CShaderManager *>(m_pShaderMgr)->useProgram(pDrawCall->getShaderProgram());
        pDrawCall->draw();
        m_priorityBatch.pop();
        i++;
    }
}
