/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
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

    #define FG_GFX_DRAWING_BATCH_DEFAULT_RESERVE 64

/*
 *
 */
class fgGfxDrawingBatch : public fgGfxLayer {
public:
    typedef fgGfxLayer base_type;

protected:
    typedef std::priority_queue<fgGfxDrawCall *, std::deque<fgGfxDrawCall *>, fgPtrLessEq<fgGfxDrawCall *> > batchPriorityQueue;
    typedef fgVector<fgGfxDrawCall *> drawCallVec;
    typedef drawCallVec::iterator drawCallVecItor;
    typedef fgVector<unsigned int> dbFreeSlotsVec;
    typedef dbFreeSlotsVec::iterator dbFreeSlotsVecItor;

private:
    ///
    batchPriorityQueue m_priorityBatch;
    ///
    drawCallVec m_drawCalls;
    ///
    drawCallVec m_duplicates;
    ///
    dbFreeSlotsVec m_freeSlots;
    ///
    unsigned int m_numDrawCalls;
    ///
    unsigned int m_reservedSize;
    ///
    unsigned int m_numNotManaged;
    ///
    fgGfxDrawCallType m_defaultDrawCallType;
    ///
    fgGFXuint m_defaultAttribMask;
    ///
    fgVector4i m_scissorBox;

protected:
    ///
    fgVector3f m_relMove;
    ///
    fg::base::CManager *m_pShaderMgr;

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

    int getFreeSlot(int maximum);

public:
    /**
     * 
     */
    fgGfxDrawingBatch(const unsigned int reservedSize = FG_GFX_DRAWING_BATCH_DEFAULT_RESERVE,
                      const fgGfxDrawCallType drawCallType = FG_GFX_DRAW_CALL_CUSTOM_ARRAY,
                      const fgGFXuint attribMask = FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT);
    /**
     * 
     */
    virtual ~fgGfxDrawingBatch();
    /**
     * 
     * @return 
     */
    inline fg::base::CManager *getShaderManager(void) const {
        return m_pShaderMgr;
    }

    /**
     * 
     * @param pShaderMgr
     */
    virtual void setShaderManager(fg::base::CManager *pShaderMgr);

    /**
     * 
     * @param index
     * @return 
     */
    fgGfxDrawCall *requestDrawCall(int &index,
                                   const fgGfxDrawCallType type = FG_GFX_DRAW_CALL_CUSTOM_ARRAY,
                                   const fgGFXuint attribMask = FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT,
                                   fgGfxShaderProgram *pProgram = NULL);
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
    // The check flag is used for duplicates
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
        return m_numDrawCalls;
    }
    /**
     * 
     * @return 
     */
    unsigned int size(void) const {
        return m_numDrawCalls;
    }
    /**
     *
     * @return
     */
    unsigned int capacity(void) const {
        return m_reservedSize;
    }

    void reserve(unsigned int reservedSize, fgBool force = FG_FALSE);
    /**
     * 
     * @return 
     */
    fgBool empty(void) const {
        return (fgBool)(m_numDrawCalls == 0);
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
    /**
     * 
     * @return 
     */
    fgVector3f const & getRelMove(void) const {
        return m_relMove;
    }
    /**
     * 
     * @param relMove
     */
    void setRelMove(const fgVector3f& relMove) {
        m_relMove = relMove;
    }
    /**
     * 
     * @param relMove
     */
    void setRelMove(const fgVector2f& relMove) {
        m_relMove.x = relMove.x;
        m_relMove.y = relMove.y;
        m_relMove.z = 0.0f;
    }
    /**
     * 
     * @return 
     */
    fgVector4i const & getScissorBox(void) const {
        return m_scissorBox;
    }
    /**
     * 
     * @return 
     */
    fgVector2i const & getScreenSize(void) const {
        return fgGfxPlatform::context()->getScreenSize();
    }
    /**
     * 
     * @param x
     * @param y
     * @param width
     * @param height
     */
    void setScissorBox(const fgGFXint x, const fgGFXint y, const fgGFXint width, const fgGFXint height) {
        m_scissorBox.x = x;
        m_scissorBox.y = y;
        m_scissorBox.z = width;
        m_scissorBox.w = height;
    }
    /**
     * 
     * @param pos
     * @param size
     */
    void setScissorBox(const fgVector2i& pos, const fgVector2i & size) {
        m_scissorBox.x = pos.x;
        m_scissorBox.y = pos.y;
        m_scissorBox.z = size.x;
        m_scissorBox.w = size.y;
    }
    /**
     * 
     * @param dimensions
     */
    void setScissorBox(const fgVector4i & dimensions) {
        m_scissorBox = dimensions;
    }

};

#endif /* FG_INC_GFX_DRAWING_BATCH */
