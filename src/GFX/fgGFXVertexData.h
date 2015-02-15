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

namespace fg {
    namespace gfx {

        /**
         *
         */
        class CVertexData {
        private:
            /// Array holding information about generated VBOs
            fgGfxBufferID *m_VBO;
            /// Number of VBO objects within this vertex data
            int m_VBOCount;

        public:
            /**
             * 
             */
            CVertexData() : m_VBO(NULL), m_VBOCount(0) { }
            /**
             * 
             */
            virtual ~CVertexData() { }

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
            virtual fgGFXboolean refreshAttributes(SAttributeData *pDataArray) const = 0;
            /**
             * 
             * @param pDataArray
             * @return 
             */
            virtual fgGFXboolean setupAttributes(SAttributeData *pDataArray) const = 0;
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
            virtual void append(const Vector3f &pos) = 0;
            /**
             * 
             * @param pos
             * @param uv
             */
            virtual void append(const Vector3f &pos,
                                const Vector2f &uv) = 0;
            /**
             * 
             * @param pos
             * @param normal
             * @param uv
             */
            virtual void append(const Vector3f &pos,
                                const Vector3f &normal,
                                const Vector2f &uv) = 0;
            /**
             * 
             * @param pos
             * @param normal
             * @param uv
             * @param color
             */
            virtual void append(const Vector3f &pos,
                                const Vector3f &normal,
                                const Vector2f &uv,
                                const fgColor3f &color) = 0;
            /**
             * 
             * @param pos
             * @param normal
             * @param uv
             * @param color
             */
            virtual void append(const Vector3f &pos,
                                const Vector3f &normal,
                                const Vector2f &uv,
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
             * @return 
             */
            virtual fgGFXuint getNumVertices(void) const = 0;
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumNormals(void) const = 0;
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumUVs(void) const = 0;
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumColors(void) const = 0;
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumIndices(void) const = 0;
            /**
             *
             */
            virtual void appendIndice(fgGFXushort indice) = 0;
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

        /**
         *
         */
        class CVertexData2v : public CVertexData, public fg::CVector<Vertex2v> {
        public:
            /**
             * 
             */
            CVertexData2v() : CVertexData(), CVector() {
                reserve(4);
            }
            /**
             * 
             */
            virtual ~CVertexData2v() {
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
            virtual fgGFXboolean refreshAttributes(SAttributeData *pDataArray) const;
            /**
             * 
             * @param pDataArray
             * @return 
             */
            virtual fgGFXboolean setupAttributes(SAttributeData *pDataArray) const;

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
            virtual void append(const Vector3f &pos) {
                Vertex2v vertex;
                vertex.position = pos;
                vertex.uv = Vector2f(1.0f, 1.0f);
                fg::CVector<Vertex2v>::push_back(vertex);
            }
            /**
             * 
             * @param pos
             * @param uv
             */
            virtual void append(const Vector3f &pos,
                                const Vector2f &uv) {
                Vertex2v vertex;
                vertex.position = pos;
                vertex.uv = uv;
                fg::CVector<Vertex2v>::push_back(vertex);
            }
            /**
             * 
             * @param pos
             * @param normal
             * @param uv
             */
            virtual void append(const Vector3f &pos,
                                const Vector3f &normal,
                                const Vector2f &uv) {
                append(pos, uv);
            }
            /**
             * 
             * @param pos
             * @param normal
             * @param uv
             * @param color
             */
            virtual void append(const Vector3f &pos,
                                const Vector3f &normal,
                                const Vector2f &uv,
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
            virtual void append(const Vector3f &pos,
                                const Vector3f &normal,
                                const Vector2f &uv,
                                const fgColor4f &color) {
                append(pos, uv);
            }
            /**
             * 
             */
            virtual void pop_back(void) {
                CVector<Vertex2v>::pop_back();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXvoid *back(void) const {
                return (fgGFXvoid *)(&CVector<Vertex2v>::back());
            }
            /**
             * 
             */
            virtual void clear(void) {
                CVector<Vertex2v>::clear();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXvoid *front(void) const {
    #if defined(FG_USING_MARMALADE)
                return (fgGFXvoid *)(fg::CVector<Vertex2v>::begin());
    #else
                return (fgGFXvoid *)(&fg::CVector<Vertex2v>::front());
    #endif /* FG_USING_MARMALADE */
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint size(void) const {
                return CVector<Vertex2v>::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumVertices(void) const {
                return CVector<Vertex2v>::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumNormals(void) const {
                return 0;
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumUVs(void) const {
                return CVector<Vertex2v>::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumColors(void) const {
                return 0;
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumIndices(void) const {
                return 0;
            }
            /**
             *
             */
            virtual void appendIndice(fgGFXushort indice) { }
            /**
             * 
             * @param newSize
             */
            virtual void reserve(const unsigned int newSize) {
                CVector<Vertex2v>::reserve(newSize);
            }
            /**
             * 
             * @return 
             */
            virtual void resize(const unsigned int newSize) {
                fg::CVector<Vertex2v>::resize(newSize);
            }
            /**
             */
            virtual fgGFXsizei stride(void) const {
                return sizeof (Vertex2v);
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint attribMask(void) const {
                return (fgGFXuint)Vertex2v::attribMask();
            }
            /**
             * 
             * @return 
             */
            virtual bool empty(void) const {
                return (bool) CVector<Vertex2v>::empty();
            }
        };

        /**
         *
         */
        class CVertexData3v : public CVertexData, public fg::CVector<Vertex3v> {
        public:
            /**
             * 
             */
            CVertexData3v() : CVertexData(), CVector() {
                reserve(4);
            }
            /**
             * 
             */
            virtual ~CVertexData3v() {
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
            virtual fgGFXboolean refreshAttributes(SAttributeData *pDataArray) const;
            /**
             * 
             * @param pDataArray
             * @return 
             */
            virtual fgGFXboolean setupAttributes(SAttributeData *pDataArray) const;

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
            virtual void append(const Vector3f &pos) {
                Vertex3v vertex;
                vertex.position = pos;
                vertex.normal = Vector3f(1.0f, 1.0f, 1.0f);
                vertex.uv = Vector2f(1.0f, 1.0f);
                fg::CVector<Vertex3v>::push_back(vertex);
            }
            /**
             * 
             * @param pos
             * @param uv
             */
            virtual void append(const Vector3f &pos,
                                const Vector2f &uv) {
                Vertex3v vertex;
                vertex.position = pos;
                vertex.normal = Vector3f(1.0f, 1.0f, 1.0f);
                vertex.uv = uv;
                fg::CVector<Vertex3v>::push_back(vertex);
            }
            /**
             * 
             * @param pos
             * @param normal
             * @param uv
             */
            virtual void append(const Vector3f &pos,
                                const Vector3f &normal,
                                const Vector2f &uv) {
                Vertex3v vertex;
                vertex.position = pos;
                vertex.normal = normal;
                vertex.uv = uv;
                CVector<Vertex3v>::push_back(vertex);
            }
            /**
             * 
             * @param pos
             * @param normal
             * @param uv
             * @param color
             */
            virtual void append(
                                const Vector3f &pos,
                                const Vector3f &normal,
                                const Vector2f &uv,
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
                                const Vector3f &pos,
                                const Vector3f &normal,
                                const Vector2f &uv,
                                const fgColor4f &color) {
                append(pos, normal, uv);
            }
            /**
             * 
             */
            virtual void pop_back(void) {
                fg::CVector<Vertex3v>::pop_back();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXvoid *back(void) const {
                return (fgGFXvoid *)(&fg::CVector<Vertex3v>::back());
            }
            /**
             * 
             */
            virtual void clear(void) {
                CVector<Vertex3v>::clear();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXvoid *front(void) const {
    #if defined(FG_USING_MARMALADE)
                return (fgGFXvoid *)(CVector<Vertex3v>::begin());
    #else
                return (fgGFXvoid *)(&CVector<Vertex3v>::front());
    #endif /* FG_USING_MARMALADE */
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint size(void) const {
                return CVector<Vertex3v>::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumVertices(void) const {
                return CVector<Vertex3v>::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumNormals(void) const {
                return CVector<Vertex3v>::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumUVs(void) const {
                return CVector<Vertex3v>::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumColors(void) const {
                return 0;
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumIndices(void) const {
                return 0;
            }
            /**
             *
             */
            virtual void appendIndice(fgGFXushort indice) { }
            /**
             * 
             * @param newSize
             */
            virtual void reserve(const unsigned int newSize) {
                fg::CVector<Vertex3v>::reserve(newSize);
            }
            /**
             * 
             * @param newSize
             */
            virtual void resize(const unsigned int newSize) {
                fg::CVector<Vertex3v>::resize(newSize);
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXsizei stride(void) const {
                return sizeof (Vertex3v);
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint attribMask(void) const {
                return (fgGFXuint)Vertex3v::attribMask();
            }
            /**
             * 
             * @return 
             */
            virtual bool empty(void) const {
                return (bool) fg::CVector<Vertex3v>::empty();
            }
        };

        /**
         *
         */
        class CVertexData4v : public CVertexData, public fg::CVector<Vertex4v> {
        public:
            /**
             * 
             */
            CVertexData4v() : CVertexData(), CVector() {
                reserve(4);
            }
            /**
             * 
             */
            virtual ~CVertexData4v() {
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
            virtual fgGFXboolean refreshAttributes(SAttributeData *pDataArray) const;
            /**
             * 
             * @param pDataArray
             * @return 
             */
            virtual fgGFXboolean setupAttributes(SAttributeData *pDataArray) const;

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
            virtual void append(const Vector3f &pos) {
                Vertex4v vertex;
                vertex.position = pos;
                vertex.uv = Vector2f(1.0f, 1.0f);
                vertex.normal = Vector3f(1.0f, 1.0f, 1.0f);
                vertex.color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
                CVector<Vertex4v>::push_back(vertex);
            }
            /**
             * 
             * @param pos
             * @param uv
             */
            virtual void append(const Vector3f &pos,
                                const Vector2f &uv) {
                Vertex4v vertex;
                vertex.position = pos;
                vertex.uv = uv;
                vertex.normal = Vector3f(1.0f, 1.0f, 1.0f);
                vertex.color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
                CVector<Vertex4v>::push_back(vertex);
            }
            /**
             * 
             * @param pos
             * @param normal
             * @param uv
             */
            virtual void append(const Vector3f &pos,
                                const Vector3f &normal,
                                const Vector2f &uv) {
                Vertex4v vertex;
                vertex.position = pos;
                vertex.normal = normal;
                vertex.uv = uv;
                vertex.color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
                CVector<Vertex4v>::push_back(vertex);
            }
            /**
             * 
             * @param pos
             * @param normal
             * @param uv
             * @param color
             */
            virtual void append(const Vector3f &pos,
                                const Vector3f &normal,
                                const Vector2f &uv,
                                const fgColor3f &color) {
                Vertex4v vertex;
                vertex.position = pos;
                vertex.normal = normal;
                vertex.uv = uv;
                vertex.color = fgColor4f(color.r, color.g, color.b, 1.0f);
                CVector<Vertex4v>::push_back(vertex);
            }
            /**
             * 
             * @param pos
             * @param normal
             * @param uv
             * @param color
             */
            virtual void append(const Vector3f &pos,
                                const Vector3f &normal,
                                const Vector2f &uv,
                                const fgColor4f &color) {
                Vertex4v vertex;
                vertex.position = pos;
                vertex.normal = normal;
                vertex.uv = uv;
                vertex.color = color;
                CVector<Vertex4v>::push_back(vertex);
            }
            /**
             * 
             */
            virtual void pop_back(void) {
                CVector<Vertex4v>::pop_back();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXvoid *back(void) const {
                return (fgGFXvoid *)(&CVector<Vertex4v>::back());
            }
            /**
             * 
             */
            virtual void clear(void) {
                CVector<Vertex4v>::clear();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXvoid *front(void) const {
    #if defined(FG_USING_MARMALADE)
                return (fgGFXvoid *)(CVector<Vertex4v>::begin());
    #else
                return (fgGFXvoid *)(&CVector<Vertex4v>::front());
    #endif /* FG_USING_MARMALADE */
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint size(void) const {
                return CVector<Vertex4v>::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumVertices(void) const {
                return CVector<Vertex4v>::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumNormals(void) const {
                return CVector<Vertex4v>::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumUVs(void) const {
                return CVector<Vertex4v>::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumColors(void) const {
                return CVector<Vertex4v>::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumIndices(void) const {
                return 0;
            }
            /**
             *
             */
            virtual void appendIndice(fgGFXushort indice) { }
            /**
             * 
             * @param newSize
             */
            virtual void reserve(const unsigned int newSize) {
                CVector<Vertex4v>::reserve(newSize);
            }
            /**
             * 
             * @param newSize
             */
            virtual void resize(const unsigned int newSize) {
                CVector<Vertex4v>::resize(newSize);
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXsizei stride(void) const {
                return sizeof (Vertex4v);
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint attribMask(void) const {
                return (fgGFXuint)Vertex4v::attribMask();
            }
            /**
             * 
             * @return 
             */
            virtual bool empty(void) const {
                return (bool) CVector<Vertex4v>::empty();
            }
        };
    };
};

    #undef FG_INC_GFX_VERTEX_DATA_BLOCK
#endif	/* FG_INC_GFX_VERTEX_DATA */
