/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXVertexData.h
 * Author: vigilant
 *
 * Created on October 17, 2014, 12:21 PM
 */

#ifndef FG_INC_GFX_VERTEX_DATA
    #define FG_INC_GFX_VERTEX_DATA
    #define FG_INC_GFX_VERTEX_DATA_BLOCK

    #ifndef FG_INC_GFX_GL
        #include "fgGFXGL.h"
    #endif

    #ifndef FG_INC_GFX_BUFFERID
        #include "fgGFXBufferID.h"
    #endif

    #ifndef FG_INC_VECTOR
        #include "fgVector.h"
    #endif

    #ifndef FG_INC_GFX_VERTEX
        #include "fgGFXVertex.h"
    #endif

    #ifndef FG_INC_GFX_ATTRIBUTE_DATA
        #include "fgGFXAttributeData.h"
    #endif

/**
 *
 */
class fgVertexData {
private:
    /// Array holding information about generated VBOs
    fgGfxBufferID *m_VBO;
    /// Number of VBO objects within this vertex data
    int m_VBOCount;

public:
    /**
     * 
     */
    fgVertexData() : m_VBO(NULL), m_VBOCount(0) { }
    /**
     * 
     */
    virtual ~fgVertexData() { }

    /**
     * Returns whether the superclass supports/generates VBOs
     * @return 
     */
    virtual fgBool supportsVBO(void) const = 0;

    /**
     * Returns whether VBOs were generated (are valid somehow)
     * @return 
     */
    virtual fgBool hasVBO(void) const {
        if(!m_VBO)
            return FG_FALSE;
        if(!m_VBOCount)
            return FG_FALSE;
        return FG_TRUE;
    }

    /**
     * Returns whether the vertex data superclass has information on indices
     * @return 
     */
    virtual fgBool hasIndices(void) const {
        return FG_FALSE;
    }
    /**
     * Returns raw ID for indices VBO (0 if invalid or not generated)
     * @return 
     */
    virtual fgGFXuint getIndicesVBO(void) const {
        return 0;
    }

    /**
     * Return GFX pointer to indices array, may be 0 if VBO
     * is generated or there are no indices at all
     * @return 
     */
    virtual fgGFXvoid *getIndicesPointer(void) const {
        return (fgGFXvoid *)0;
    }

    /**
     * 
     * @return 
     */
    virtual int getVBOCount(void) const {
        return m_VBOCount;
    }
public: // #FIXME? #FUBAR
    /**
     * Returns the reference to the number of VBOs
     * @return 
     */
    virtual int& getRefVBOCount(void) {
        return m_VBOCount;
    }

public:
    /**
     * 
     * @return 
     */
    virtual fgGfxBufferID* getPtrVBO(void) const {
        return m_VBO;
    }
    /**
     * 
     * @return 
     */
    virtual fgGfxBufferID*& getRefPtrVBO(void) {
        return m_VBO;
    }

    /**
     * 
     * @param pDataArray
     * @return 
     */
    virtual fgGFXboolean refreshAttributes(fgGfxAttributeData *pDataArray) const = 0;
    /**
     * 
     * @param pDataArray
     * @return 
     */
    virtual fgGFXboolean setupAttributes(fgGfxAttributeData *pDataArray) const = 0;
    /**
     * 
     * @return 
     */
    virtual fgGFXboolean genBuffers(void) = 0;
    /**
     * 
     * @return 
     */
    virtual fgGFXboolean deleteBuffers(void) = 0;
    /**
     * 
     * @return 
     */
    virtual fgGFXboolean destroyBuffers(void) = 0;
    /**
     * 
     * @return 
     */
    virtual fgBool isSoA(void) const = 0;
    /**
     * 
     * @return 
     */
    virtual fgBool isAoS(void) const = 0;

    /**
     * 
     * @param pos
     */
    virtual void append(const fgVector3f &pos) = 0;
    /**
     * 
     * @param pos
     * @param uv
     */
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector2f &uv) = 0;
    /**
     * 
     * @param pos
     * @param normal
     * @param uv
     */
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv) = 0;
    /**
     * 
     * @param pos
     * @param normal
     * @param uv
     * @param color
     */
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv,
                        const fgColor3f &color) = 0;
    /**
     * 
     * @param pos
     * @param normal
     * @param uv
     * @param color
     */
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv,
                        const fgColor4f &color) = 0;

    /**
     * 
     */
    virtual void pop_back(void) = 0;

    /**
     * 
     * @return 
     */
    virtual fgGFXvoid *back(void) const = 0;

    /**
     * 
     */
    virtual void clear(void) = 0;

    /**
     * 
     * @return 
     */
    virtual fgGFXvoid *front(void) const = 0;

    /**
     * 
     * @return 
     */
    virtual fgGFXuint size(void) const = 0;
    
    /**
     * 
     * @param newSize
     */
    virtual void reserve(const unsigned int newSize) = 0;
    /**
     * 
     * @param newSize
     */
    virtual void resize(const unsigned int newSize) = 0;

    /**
     * 
     * @return 
     */
    virtual fgGFXsizei stride(void) const = 0;

    /**
     * 
     * @return 
     */
    virtual fgGFXuint attribMask(void) const = 0;

    /**
     * 
     * @return 
     */
    virtual bool empty(void) const = 0;
};

typedef fgVertexData fgGfxVertexData;

/**
 *
 */
class fgVertexData2v : public fgVertexData, public fg::CVector<fgVertex2v> {
public:
    /**
     * 
     */
    fgVertexData2v() : fgVertexData(), CVector() {
        reserve(4);
    }
    /**
     * 
     */
    virtual ~fgVertexData2v() {
        destroyBuffers();
        clear_optimised();
    }

    /**
     * 
     * @return 
     */
    virtual fgBool supportsVBO(void) const {
        return FG_TRUE;
    }
    /**
     * 
     * @return 
     */
    virtual fgBool isSoA(void) const {
        return FG_FALSE;
    }
    /**
     * 
     * @return 
     */
    virtual fgBool isAoS(void) const {
        return FG_TRUE;
    }
    
    /**
     * 
     * @param pDataArray
     * @return 
     */
    virtual fgGFXboolean refreshAttributes(fgGfxAttributeData *pDataArray) const;
    /**
     * 
     * @param pDataArray
     * @return 
     */
    virtual fgGFXboolean setupAttributes(fgGfxAttributeData *pDataArray) const;

    /**
     * 
     * @return 
     */
    virtual fgGFXboolean genBuffers(void);
    /**
     * 
     * @return 
     */
    virtual fgGFXboolean deleteBuffers(void);
    /**
     * 
     * @param pos
     */
    virtual fgGFXboolean destroyBuffers(void);

    /**
     * 
     * @param pos
     */
    virtual void append(const fgVector3f &pos) {
        fgVertex2v vertex;
        vertex.position = pos;
        vertex.uv = fgVector2f(1.0f, 1.0f);
        fg::CVector<fgVertex2v>::push_back(vertex);
    }
    /**
     * 
     * @param pos
     * @param uv
     */
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector2f &uv) {
        fgVertex2v vertex;
        vertex.position = pos;
        vertex.uv = uv;
        fg::CVector<fgVertex2v>::push_back(vertex);
    }
    /**
     * 
     * @param pos
     * @param normal
     * @param uv
     */
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv) {
        append(pos, uv);
    }
    /**
     * 
     * @param pos
     * @param normal
     * @param uv
     * @param color
     */
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv,
                        const fgColor3f &color) {
        append(pos, uv);
    }
    /**
     * 
     * @param pos
     * @param normal
     * @param uv
     * @param color
     */
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv,
                        const fgColor4f &color) {
        append(pos, uv);
    }

    /**
     * 
     */
    virtual void pop_back(void) {
        fg::CVector<fgVertex2v>::pop_back();
    }

    /**
     * 
     * @return 
     */
    virtual fgGFXvoid *back(void) const {
        return (fgGFXvoid *)(&CVector<fgVertex2v>::back());
    }
    /**
     * 
     */
    virtual void clear(void) {
        fg::CVector<fgVertex2v>::clear();
    }

    /**
     * 
     * @return 
     */
    virtual fgGFXvoid *front(void) const {
    #if defined(FG_USING_MARMALADE)
        return (fgGFXvoid *)(fg::CVector<fgVertex2v>::begin());
    #else
        return (fgGFXvoid *)(&fg::CVector<fgVertex2v>::front());
    #endif /* FG_USING_MARMALADE */
    }

    /**
     * 
     * @return 
     */
    virtual fgGFXuint size(void) const {
        return fg::CVector<fgVertex2v>::size();
    }
    /**
     * 
     * @param newSize
     */
    virtual void reserve(const unsigned int newSize) {
        fg::CVector<fgVertex2v>::reserve(newSize);
    }
    /**
     * 
     * @return 
     */
    virtual void resize(const unsigned int newSize) {
        fg::CVector<fgVertex2v>::resize(newSize);
    }

    /**
     */
    virtual fgGFXsizei stride(void) const {
        return sizeof (fgVertex2v);
    }
    /**
     * 
     * @return 
     */
    virtual fgGFXuint attribMask(void) const {
        return (fgGFXuint)fgVertex2v::attribMask();
    }
    /**
     * 
     * @return 
     */
    virtual bool empty(void) const {
        return (bool) CVector<fgVertex2v>::empty();
    }
};

typedef fgVertexData2v fgGfxVertexData2v;

/**
 *
 */
class fgVertexData3v : public fgVertexData, public fg::CVector<fgVertex3v> {
public:
    /**
     * 
     */
    fgVertexData3v() : fgVertexData(), CVector() {
        reserve(4);
    }
    /**
     * 
     */
    virtual ~fgVertexData3v() {
        destroyBuffers();
        clear_optimised();
    }

    /**
     * 
     * @return 
     */
    virtual fgBool supportsVBO(void) const {
        return FG_TRUE;
    }
    /**
     * 
     * @return 
     */
    virtual fgBool isSoA(void) const {
        return FG_FALSE;
    }
    /**
     * 
     * @return 
     */
    virtual fgBool isAoS(void) const {
        return FG_TRUE;
    }

    /**
     * 
     * @param pDataArray
     * @return 
     */
    virtual fgGFXboolean refreshAttributes(fgGfxAttributeData *pDataArray) const;
    /**
     * 
     * @param pDataArray
     * @return 
     */
    virtual fgGFXboolean setupAttributes(fgGfxAttributeData *pDataArray) const;

    /**
     * 
     * @return 
     */
    virtual fgGFXboolean genBuffers(void);
    /**
     * 
     * @return 
     */
    virtual fgGFXboolean deleteBuffers(void);
    /**
     * 
     * @return 
     */
    virtual fgGFXboolean destroyBuffers(void);

    /**
     * 
     * @param pos
     */
    virtual void append(const fgVector3f &pos) {
        fgVertex3v vertex;
        vertex.position = pos;
        vertex.normal = fgVector3f(1.0f, 1.0f, 1.0f);
        vertex.uv = fgVector2f(1.0f, 1.0f);
        fg::CVector<fgVertex3v>::push_back(vertex);
    }
    /**
     * 
     * @param pos
     * @param uv
     */
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector2f &uv) {
        fgVertex3v vertex;
        vertex.position = pos;
        vertex.normal = fgVector3f(1.0f, 1.0f, 1.0f);
        vertex.uv = uv;
        fg::CVector<fgVertex3v>::push_back(vertex);
    }
    /**
     * 
     * @param pos
     * @param normal
     * @param uv
     */
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv) {
        fgVertex3v vertex;
        vertex.position = pos;
        vertex.normal = normal;
        vertex.uv = uv;
        CVector<fgVertex3v>::push_back(vertex);
    }
    /**
     * 
     * @param pos
     * @param normal
     * @param uv
     * @param color
     */
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv,
                        const fgColor3f &color) {
        append(pos, normal, uv);
    }
    /**
     * 
     * @param pos
     * @param normal
     * @param uv
     * @param color
     */
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv,
                        const fgColor4f &color) {
        append(pos, normal, uv);
    }

    /**
     * 
     */
    virtual void pop_back(void) {
        fg::CVector<fgVertex3v>::pop_back();
    }
    /**
     * 
     * @return 
     */
    virtual fgGFXvoid *back(void) const {
        return (fgGFXvoid *)(&fg::CVector<fgVertex3v>::back());
    }
    /**
     * 
     */
    virtual void clear(void) {
        fg::CVector<fgVertex3v>::clear();
    }

    /**
     * 
     * @return 
     */
    virtual fgGFXvoid *front(void) const {
    #if defined(FG_USING_MARMALADE)
        return (fgGFXvoid *)(fg::CVector<fgVertex3v>::begin());
    #else
        return (fgGFXvoid *)(&fg::CVector<fgVertex3v>::front());
    #endif /* FG_USING_MARMALADE */
    }

    /**
     * 
     * @return 
     */
    virtual fgGFXuint size(void) const {
        return fg::CVector<fgVertex3v>::size();
    }
    
    /**
     * 
     * @param newSize
     */
    virtual void reserve(const unsigned int newSize) {
        fg::CVector<fgVertex3v>::reserve(newSize);
    }
    /**
     * 
     * @param newSize
     */
    virtual void resize(const unsigned int newSize) {
        fg::CVector<fgVertex3v>::resize(newSize);
    }

    /**
     * 
     * @return 
     */
    virtual fgGFXsizei stride(void) const {
        return sizeof (fgVertex3v);
    }

    /**
     * 
     * @return 
     */
    virtual fgGFXuint attribMask(void) const {
        return (fgGFXuint)fgVertex3v::attribMask();
    }

    /**
     * 
     * @return 
     */
    virtual bool empty(void) const {
        return (bool) fg::CVector<fgVertex3v>::empty();
    }
};

typedef fgVertexData3v fgGfxVertexData3v;

/**
 *
 */
class fgVertexData4v : public fgVertexData, public fg::CVector<fgVertex4v> {
public:
    /**
     * 
     */
    fgVertexData4v() : fgVertexData(), CVector() {
        reserve(4);
    }
    /**
     * 
     */
    virtual ~fgVertexData4v() {
        destroyBuffers();
        clear_optimised();
    }

    /**
     * 
     * @return 
     */
    virtual fgBool supportsVBO(void) const {
        return FG_TRUE;
    }
    /**
     * 
     * @return 
     */
    virtual fgBool isSoA(void) const {
        return FG_FALSE;
    }
    /**
     * 
     * @return 
     */
    virtual fgBool isAoS(void) const {
        return FG_TRUE;
    }

    /**
     * 
     * @param pDataArray
     * @return 
     */
    virtual fgGFXboolean refreshAttributes(fgGfxAttributeData *pDataArray) const;
    /**
     * 
     * @param pDataArray
     * @return 
     */
    virtual fgGFXboolean setupAttributes(fgGfxAttributeData *pDataArray) const;

    /**
     * 
     * @return 
     */
    virtual fgGFXboolean genBuffers(void);
    /**
     * 
     * @return 
     */
    virtual fgGFXboolean deleteBuffers(void);
    /**
     * 
     * @return 
     */
    virtual fgGFXboolean destroyBuffers(void);

    /**
     * 
     * @param pos
     */
    virtual void append(const fgVector3f &pos) {
        fgVertex4v vertex;
        vertex.position = pos;
        vertex.uv = fgVector2f(1.0f, 1.0f);
        vertex.normal = fgVector3f(1.0f, 1.0f, 1.0f);
        vertex.color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        CVector<fgVertex4v>::push_back(vertex);
    }
    /**
     * 
     * @param pos
     * @param uv
     */
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector2f &uv) {
        fgVertex4v vertex;
        vertex.position = pos;
        vertex.uv = uv;
        vertex.normal = fgVector3f(1.0f, 1.0f, 1.0f);
        vertex.color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        CVector<fgVertex4v>::push_back(vertex);
    }
    /**
     * 
     * @param pos
     * @param normal
     * @param uv
     */
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv) {
        fgVertex4v vertex;
        vertex.position = pos;
        vertex.normal = normal;
        vertex.uv = uv;
        vertex.color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        CVector<fgVertex4v>::push_back(vertex);
    }
    /**
     * 
     * @param pos
     * @param normal
     * @param uv
     * @param color
     */
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv,
                        const fgColor3f &color) {
        fgVertex4v vertex;
        vertex.position = pos;
        vertex.normal = normal;
        vertex.uv = uv;
        vertex.color = fgColor4f(color.r, color.g, color.b, 1.0f);
        CVector<fgVertex4v>::push_back(vertex);
    }
    /**
     * 
     * @param pos
     * @param normal
     * @param uv
     * @param color
     */
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv,
                        const fgColor4f &color) {
        fgVertex4v vertex;
        vertex.position = pos;
        vertex.normal = normal;
        vertex.uv = uv;
        vertex.color = color;
        CVector<fgVertex4v>::push_back(vertex);
    }
    /**
     * 
     */
    virtual void pop_back(void) {
        CVector<fgVertex4v>::pop_back();
    }
    /**
     * 
     * @return 
     */
    virtual fgGFXvoid *back(void) const {
        return (fgGFXvoid *)(&CVector<fgVertex4v>::back());
    }
    /**
     * 
     */
    virtual void clear(void) {
        CVector<fgVertex4v>::clear();
    }
    /**
     * 
     * @return 
     */
    virtual fgGFXvoid *front(void) const {
    #if defined(FG_USING_MARMALADE)
        return (fgGFXvoid *)(CVector<fgVertex4v>::begin());
    #else
        return (fgGFXvoid *)(&CVector<fgVertex4v>::front());
    #endif /* FG_USING_MARMALADE */
    }

    /**
     * 
     * @return 
     */
    virtual fgGFXuint size(void) const {
        return CVector<fgVertex4v>::size();
    }
    /**
     * 
     * @param newSize
     */
    virtual void reserve(const unsigned int newSize) {
        CVector<fgVertex4v>::reserve(newSize);
    }
    /**
     * 
     * @param newSize
     */
    virtual void resize(const unsigned int newSize) {
        CVector<fgVertex4v>::resize(newSize);
    }
    /**
     * 
     * @return 
     */
    virtual fgGFXsizei stride(void) const {
        return sizeof (fgVertex4v);
    }
    /**
     * 
     * @return 
     */
    virtual fgGFXuint attribMask(void) const {
        return (fgGFXuint)fgVertex4v::attribMask();
    }
    /**
     * 
     * @return 
     */
    virtual bool empty(void) const {
        return (bool) CVector<fgVertex4v>::empty();
    }
};

typedef fgVertexData4v fgGfxVertexData4v;

    #undef FG_INC_GFX_VERTEX_DATA_BLOCK
#endif	/* FG_INC_GFX_VERTEX_DATA */
