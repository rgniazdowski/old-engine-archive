/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_DRAWING_BATCH
    #define FG_INC_GFX_DRAWING_BATCH

    #include "fgGFXDrawCall.h"
    #include "fgGFXLayer.h"

    #include <queue>
    #include <deque>

/*
 *
 */
class fgGfxDrawingBatch : public fgGfxLayer {
protected:
    typedef std::priority_queue<fgGfxDrawCall *, std::deque<fgGfxDrawCall *>, fgPtrLessEq<fgGfxDrawCall *> > batchPriorityQueue;
    typedef fgVector<fgGfxDrawCall *> drawCallVec;
    typedef drawCallVec::iterator drawCallVecItor;

private:
    ///
    batchPriorityQueue m_priorityBatch;
    ///
    drawCallVec m_drawCalls;
    ///
    drawCallVec m_duplicates;

protected:
    ///
    fgManagerBase *m_pShaderMgr;

protected:
    /**
     * 
     * @return 
     */
    inline batchPriorityQueue& getRefPriorityQueue(void) {
        return m_priorityBatch;
    }
    /**
     * 
     * @return 
     */
    inline drawCallVec& getRefDrawCalls(void) {
        return m_drawCalls;
    }

public:
    /**
     * 
     */
    fgGfxDrawingBatch();
    /**
     * 
     */
    virtual ~fgGfxDrawingBatch();
    /**
     * 
     * @return 
     */
    inline fgManagerBase *getShaderManager(void) const {
        return m_pShaderMgr;
    }

    /**
     * 
     * @param pShaderMgr
     */
    virtual void setShaderManager(fgManagerBase *pShaderMgr);

    /**
     * 
     * @param index
     * @return 
     */
    fgGfxDrawCall *createDrawCall(int &index,
                                  const fgGfxDrawCallType type = FG_GFX_DRAW_CALL_CUSTOM_ARRAY,
                                  const fgGFXuint attribMask = FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT);
    /**
     * 
     * @param index
     * @return 
     */
    fgGfxDrawCall *getDrawCall(int index);
    /**
     * 
     * @return 
     */
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
    /**
     * 
     * @param drawCall
     * @return 
     */
    fgBool removeDrawCall(fgGfxDrawCall *drawCall);
    /**
     * 
     * @param index
     * @return 
     */
    fgBool deleteDrawCall(int index);
    /**
     * 
     * @param drawCall
     * @return 
     */
    fgBool deleteDrawCall(fgGfxDrawCall*& drawCall);
    /**
     * 
     * @return 
     */
    unsigned int count(void) const {
        return m_drawCalls.size();
    }
    /**
     * 
     * @return 
     */
    unsigned int size(void) const {
        return m_drawCalls.size();
    }
    /**
     * 
     * @return 
     */
    fgBool empty(void) const {
        return (fgBool)m_drawCalls.empty();
    }

    /**
     * 
     */
    virtual void flush(void);
    /**
     * 
     */
    virtual void sortCalls(void);
    /**
     * 
     */
    virtual void render(void);
    /**
     * 
     * @param n
     * @return 
     */
    fgGfxDrawCall *operator [](size_t n) {
        return m_drawCalls[n];
    }
    /**
     * 
     * @param n
     * @return 
     */
    const fgGfxDrawCall *operator [](size_t n) const {
        return m_drawCalls[n];
    }
};

#endif /* FG_INC_GFX_DRAWING_BATCH */
