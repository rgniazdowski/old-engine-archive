/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
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

#ifndef _FG_GFX_VERTEX_DATA_H_
    #define	_FG_GFX_VERTEX_DATA_H_

    #ifndef _FG_GFX_GL_H_
        #include "fgGFXGL.h"
    #endif

    #ifndef _FG_GFX_BUFFERID_H_
        #include "fgGFXBufferID.h"
    #endif

    #ifndef _FG_VECTOR_H_
        #include "fgVector.h"
    #endif

    #ifndef _FG_GFX_VERTEX_H_
        #include "fgGFXVertex.h"
    #endif

    #ifndef _FG_GFX_ATTRIBUTE_DATA_H_
        #include "fgGFXAttributeData.h"
    #endif

/*
 *
 */
class fgVertexData {
private:
    /// Array holding information about generated VBOs
    fgGfxBufferID *m_VBO;
    /// Number of VBO objects within this vertex data
    int m_VBOCount;

public:
    //
    fgVertexData() : m_VBO(NULL), m_VBOCount(0) { }
    //
    virtual ~fgVertexData() { }

    // Returns whether the superclass supports/generates VBOs
    virtual fgBool supportsVBO(void) const = 0;

    // Returns whether VBOs were generated (are valid somehow)
    virtual fgBool hasVBO(void) const {
        if(!m_VBO)
            return FG_FALSE;
        if(!m_VBOCount)
            return FG_FALSE;
        return FG_TRUE;
    }

    // Returns whether the vertex data superclass has information on indices
    virtual fgBool hasIndices(void) const {
        return FG_FALSE;
    }

    // Returns raw ID for indices VBO (0 if invalid or not generated)
    virtual fgGFXuint getIndicesVBO(void) const {
        return 0;
    }

    // Return GFX pointer to indices array, may be 0 if VBO
    // is generated or there are no indices at all
    virtual fgGFXvoid *getIndicesPointer(void) const {
        return (fgGFXvoid *)0;
    }

    //
    virtual int getVBOCount(void) const {
        return m_VBOCount;
    }
public: // #FIXME? #FUBAR
    // Returns the reference to the number of VBOs
    virtual int& getRefVBOCount(void) {
        return m_VBOCount;
    }

public:
    //
    virtual fgGfxBufferID* getPtrVBO(void) const {
        return m_VBO;
    }

    //
    virtual fgGfxBufferID*& getRefPtrVBO(void) {
        return m_VBO;
    }

    //
    virtual fgGFXboolean setupAttributes(fgGfxAttributeData *pDataArray) const = 0;

    //
    virtual fgGFXboolean genBuffers(void) = 0;

    //
    virtual fgGFXboolean deleteBuffers(void) = 0;

    //
    virtual fgGFXboolean destroyBuffers(void) = 0;

    //
    virtual fgBool isSoA(void) const = 0;

    //
    virtual fgBool isAoS(void) const = 0;

    //
    virtual void append(const fgVector3f &pos) = 0;

    //
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector2f &uv) = 0;

    //
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv) = 0;

    //
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv,
                        const fgColor3f &color) = 0;

    //
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv,
                        const fgColor4f &color) = 0;

    //
    virtual void pop_back(void) = 0;

    //
    virtual fgGFXvoid *back(void) const = 0;

    //
    virtual void clear(void) = 0;

    //
    virtual fgGFXvoid *front(void) const = 0;

    //
    virtual fgGFXuint size(void) const = 0;
    
    //
    virtual void reserve(const unsigned int newSize) = 0;
    
    //
    virtual void resize(const unsigned int newSize) = 0;

    //
    virtual fgGFXsizei stride(void) const = 0;

    //
    virtual fgGFXuint attribMask(void) const = 0;

    //
    virtual bool empty(void) const = 0;
};

typedef fgVertexData fgGfxVertexData;

/*
 *
 */
class fgVertexData2v : public fgVertexData, public fgVector<fgVertex2v> {
public:
    //
    virtual ~fgVertexData2v() {
        destroyBuffers();
    }

    //
    virtual fgBool supportsVBO(void) const {
        return FG_TRUE;
    }

    //
    virtual fgBool isSoA(void) const {
        return FG_FALSE;
    }

    // 
    virtual fgBool isAoS(void) const {
        return FG_TRUE;
    }

    //
    virtual fgGFXboolean setupAttributes(fgGfxAttributeData *pDataArray) const;

    //
    virtual fgGFXboolean genBuffers(void);

    //
    virtual fgGFXboolean deleteBuffers(void);

    //
    virtual fgGFXboolean destroyBuffers(void);

    //
    virtual void append(const fgVector3f &pos) {
        fgVertex2v vertex;
        vertex.position = pos;
        vertex.uv = fgVector2f(1.0f, 1.0f);
        fgVector<fgVertex2v>::push_back(vertex);
    }

    //
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector2f &uv) {
        fgVertex2v vertex;
        vertex.position = pos;
        vertex.uv = uv;
        fgVector<fgVertex2v>::push_back(vertex);
    }

    //
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv) {
        append(pos, uv);
    }

    //
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv,
                        const fgColor3f &color) {
        append(pos, uv);
    }

    //
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv,
                        const fgColor4f &color) {
        append(pos, uv);
    }

    //
    virtual void pop_back(void) {
        fgVector<fgVertex2v>::pop_back();
    }

    //
    virtual fgGFXvoid *back(void) const {
        return (fgGFXvoid *)(&fgVector<fgVertex2v>::back());
    }

    //
    virtual void clear(void) {
        fgVector<fgVertex2v>::clear();
    }

    //
    virtual fgGFXvoid *front(void) const {
        return (fgGFXvoid *)(&fgVector<fgVertex2v>::front());
    }

    //
    virtual fgGFXuint size(void) const {
        return fgVector<fgVertex2v>::size();
    }
    
    //
    virtual void reserve(const unsigned int newSize) {
        fgVector<fgVertex2v>::reserve(newSize);
    }
    
    //
    virtual void resize(const unsigned int newSize) {
        fgVector<fgVertex2v>::resize(newSize);
    }

    //
    virtual fgGFXsizei stride(void) const {
        return sizeof (fgVertex2v);
    }

    //
    virtual fgGFXuint attribMask(void) const {
        return (fgGFXuint)fgVertex2v::attribMask();
    }

    //
    virtual bool empty(void) const {
        return (bool) fgVector<fgVertex2v>::empty();
    }
};

typedef fgVertexData2v fgGfxVertexData2v;

/*
 *
 */
class fgVertexData3v : public fgVertexData, public fgVector<fgVertex3v> {
public:
    //
    virtual ~fgVertexData3v() {
        destroyBuffers();
    }

    //
    virtual fgBool supportsVBO(void) const {
        return FG_TRUE;
    }

    //
    virtual fgBool isSoA(void) const {
        return FG_FALSE;
    }

    // 
    virtual fgBool isAoS(void) const {
        return FG_TRUE;
    }

    //
    virtual fgGFXboolean setupAttributes(fgGfxAttributeData *pDataArray) const;

    //
    virtual fgGFXboolean genBuffers(void);

    //
    virtual fgGFXboolean deleteBuffers(void);

    //
    virtual fgGFXboolean destroyBuffers(void);

    //
    virtual void append(const fgVector3f &pos) {
        fgVertex3v vertex;
        vertex.position = pos;
        vertex.normal = fgVector3f(1.0f, 1.0f, 1.0f);
        vertex.uv = fgVector2f(1.0f, 1.0f);
        fgVector<fgVertex3v>::push_back(vertex);
    }

    //
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector2f &uv) {
        fgVertex3v vertex;
        vertex.position = pos;
        vertex.normal = fgVector3f(1.0f, 1.0f, 1.0f);
        vertex.uv = uv;
        fgVector<fgVertex3v>::push_back(vertex);
    }

    //
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv) {
        fgVertex3v vertex;
        vertex.position = pos;
        vertex.normal = normal;
        vertex.uv = uv;
        fgVector<fgVertex3v>::push_back(vertex);
    }

    //
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv,
                        const fgColor3f &color) {
        append(pos, normal, uv);
    }

    //
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv,
                        const fgColor4f &color) {
        append(pos, normal, uv);
    }

    //
    virtual void pop_back(void) {
        fgVector<fgVertex3v>::pop_back();
    }

    //
    virtual fgGFXvoid *back(void) const {
        return (fgGFXvoid *)(&fgVector<fgVertex3v>::back());
    }

    //
    virtual void clear(void) {
        fgVector<fgVertex3v>::clear();
    }

    //
    virtual fgGFXvoid *front(void) const {
        return (fgGFXvoid *)(&fgVector<fgVertex3v>::front());
    }

    //
    virtual fgGFXuint size(void) const {
        return fgVector<fgVertex3v>::size();
    }
    
    //
    virtual void reserve(const unsigned int newSize) {
        fgVector<fgVertex3v>::reserve(newSize);
    }
    
    //
    virtual void resize(const unsigned int newSize) {
        fgVector<fgVertex3v>::resize(newSize);
    }

    //
    virtual fgGFXsizei stride(void) const {
        return sizeof (fgVertex3v);
    }

    //
    virtual fgGFXuint attribMask(void) const {
        return (fgGFXuint)fgVertex3v::attribMask();
    }

    //
    virtual bool empty(void) const {
        return (bool) fgVector<fgVertex3v>::empty();
    }
};

typedef fgVertexData3v fgGfxVertexData3v;

/*
 *
 */
class fgVertexData4v : public fgVertexData, public fgVector<fgVertex4v> {
public:
    //
    virtual ~fgVertexData4v() {
        destroyBuffers();
    }

    //
    virtual fgBool supportsVBO(void) const {
        return FG_TRUE;
    }

    //
    virtual fgBool isSoA(void) const {
        return FG_FALSE;
    }

    // 
    virtual fgBool isAoS(void) const {
        return FG_TRUE;
    }

    //
    virtual fgGFXboolean setupAttributes(fgGfxAttributeData *pDataArray) const;

    //
    virtual fgGFXboolean genBuffers(void);

    //
    virtual fgGFXboolean deleteBuffers(void);

    //
    virtual fgGFXboolean destroyBuffers(void);

    //
    virtual void append(const fgVector3f &pos) {
        fgVertex4v vertex;
        vertex.position = pos;
        vertex.uv = fgVector2f(1.0f, 1.0f);
        vertex.normal = fgVector3f(1.0f, 1.0f, 1.0f);
        vertex.color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        fgVector<fgVertex4v>::push_back(vertex);
    }

    //
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector2f &uv) {
        fgVertex4v vertex;
        vertex.position = pos;
        vertex.uv = uv;
        vertex.normal = fgVector3f(1.0f, 1.0f, 1.0f);
        vertex.color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        fgVector<fgVertex4v>::push_back(vertex);
    }

    //
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv) {
        fgVertex4v vertex;
        vertex.position = pos;
        vertex.normal = normal;
        vertex.uv = uv;
        vertex.color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        fgVector<fgVertex4v>::push_back(vertex);
    }

    //
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
        fgVector<fgVertex4v>::push_back(vertex);
    }

    //
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
        fgVector<fgVertex4v>::push_back(vertex);
    }

    //
    virtual void pop_back(void) {
        fgVector<fgVertex4v>::pop_back();
    }

    //
    virtual fgGFXvoid *back(void) const {
        return (fgGFXvoid *)(&fgVector<fgVertex4v>::back());
    }

    //
    virtual void clear(void) {
        fgVector<fgVertex4v>::clear();
    }

    //
    virtual fgGFXvoid *front(void) const {
        return (fgGFXvoid *)(&fgVector<fgVertex4v>::front());
    }

    //
    virtual fgGFXuint size(void) const {
        return fgVector<fgVertex4v>::size();
    }

    //
    virtual void reserve(const unsigned int newSize) {
        fgVector<fgVertex4v>::reserve(newSize);
    }
    
    //
    virtual void resize(const unsigned int newSize) {
        fgVector<fgVertex4v>::resize(newSize);
    }
    
    //
    virtual fgGFXsizei stride(void) const {
        return sizeof (fgVertex4v);
    }

    //
    virtual fgGFXuint attribMask(void) const {
        return (fgGFXuint)fgVertex4v::attribMask();
    }

    //
    virtual bool empty(void) const {
        return (bool) fgVector<fgVertex4v>::empty();
    }
};

typedef fgVertexData4v fgGfxVertexData4v;


#endif	/* _FG_GFX_VERTEX_DATA_H_ */

