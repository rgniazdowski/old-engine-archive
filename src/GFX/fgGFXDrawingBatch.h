/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_DRAWING_BATCH_H_
    #define _FG_GFX_DRAWING_BATCH_H_

    #include "fgGFXDrawCall.h"
    #include "fgGFXLayer.h"

    #include <queue>
    #include <deque>

/*
 *
 */
class fgGfxDrawingBatch : public fgGfxLayer {
private:
    typedef std::priority_queue<fgGfxDrawCall*, std::deque<fgGfxDrawCall*>, fgPtrLessEq<fgGfxDrawCall*> > batchPriorityQueue;
    typedef fgVector<fgGfxDrawCall *>   drawCallVec;
    typedef drawCallVec::iterator   drawCallVecItor;
    
    ///
    batchPriorityQueue m_priorityBatch;
    ///
    drawCallVec m_drawCalls;
    ///
    drawCallVec m_duplicates;
    ///
    fgManagerBase *m_shaderMgr;

public:
    // 
    fgGfxDrawingBatch();
    // 
    virtual ~fgGfxDrawingBatch();

    //
    fgManagerBase *getShaderManager(void) const;
    //
    virtual void setShaderManager(fgManagerBase *shaderMgr);

    //
    fgGfxDrawCall *createDrawCall(int &index, fgGfxDrawCallType type = FG_GFX_DRAW_CALL_CUSTOM_ARRAY);
    //
    fgGfxDrawCall *getDrawCall(int index);
    //
    fgGfxDrawCall *getLastDrawCall(void);
    // Appends the specified draw call to the drawing batch
    // The check flag is used for
    int appendDrawCall(fgGfxDrawCall* drawCall, fgBool manage = FG_TRUE, fgBool check = FG_TRUE);
    /**
     * Removes the given draw call from the drawing batch
     * @param index Specifies the index of a draw call to remove
     * @return      Returns the pointer of the removed draw call or NULL 
     *              if index was out of bounds (or the batch is empty)
     */
    fgGfxDrawCall *removeDrawCall(int index);
    //
    fgBool removeDrawCall(fgGfxDrawCall *drawCall);
    //
    fgBool deleteDrawCall(int index);
    //
    fgBool deleteDrawCall(fgGfxDrawCall*& drawCall);

    //
    unsigned int count(void) const {
        return m_drawCalls.size();
    }

    //
    fgBool empty(void) const {
        return (fgBool)m_drawCalls.empty();
    }
    
    //
    virtual void flush(void);

    //
    virtual void sortCalls(void);

    //
    virtual void render(void);
    
    //
    fgGfxDrawCall *operator [](size_t n) {
        return m_drawCalls[n];
    }
    
    //
    const fgGfxDrawCall *operator [](size_t n) const {
        return m_drawCalls[n];
    }
    

};

#endif /* _FG_GFX_DRAWING_BATCH_H_ */
