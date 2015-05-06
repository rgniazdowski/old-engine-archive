/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
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
        #include "fgGfxGL.h"
    #endif

    #ifndef FG_INC_GFX_BUFFERID
        #include "fgGfxBufferID.h"
    #endif

    #ifndef FG_INC_VECTOR
        #include "fgVector.h"
    #endif

    #ifndef FG_INC_GFX_VERTEX
        #include "fgGfxVertex.h"
    #endif

    #ifndef FG_INC_GFX_ATTRIBUTE_DATA
        #include "fgGfxAttributeData.h"
    #endif

namespace fg {
    namespace gfx {

        /**
         *
         */
        class CVertexData {
        private:
            /// Array holding information about generated VBOs
            SBufferID *m_VBO;
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
            virtual SBufferID* getPtrVBO(void) const {
                return m_VBO;
            }
            /**
             * 
             * @return 
             */
            virtual SBufferID*& getRefPtrVBO(void) {
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
                                const Color3f &color) = 0;
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
                                const Color4f &color) = 0;

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
        class CVertexData2v : public CVertexData, public CVector<Vertex2v> {
        public:
            typedef CVertexData2v type;
            typedef CVertexData2v self_type;
            typedef CVertexData base_type;
            typedef Vertex2v vertex_type;
            typedef CVector<Vertex2v> base_vec_type;

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
                base_vec_type::push_back(vertex);
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
                base_vec_type::push_back(vertex);
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
                                const Color3f &color) {
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
                                const Color4f &color) {
                append(pos, uv);
            }
            /**
             * 
             */
            virtual void pop_back(void) {
                base_vec_type::pop_back();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXvoid *back(void) const {
                return (fgGFXvoid *)(&base_vec_type::back());
            }
            /**
             * 
             */
            virtual void clear(void) {
                base_vec_type::clear();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXvoid *front(void) const {
    #if defined(FG_USING_MARMALADE)
                return (fgGFXvoid *)(base_vec_type::begin());
    #else
                return (fgGFXvoid *)(&base_vec_type::front());
    #endif /* FG_USING_MARMALADE */
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint size(void) const {
                return base_vec_type::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumVertices(void) const {
                return base_vec_type::size();
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
                return base_vec_type::size();
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
                base_vec_type::reserve(newSize);
            }
            /**
             * 
             * @return 
             */
            virtual void resize(const unsigned int newSize) {
                base_vec_type::resize(newSize);
            }
            /**
             * 
             * @return
             */
            virtual fgGFXsizei stride(void) const {
                return sizeof (vertex_type);
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint attribMask(void) const {
                return (fgGFXuint)vertex_type::attribMask();
            }
            /**
             * 
             * @return 
             */
            virtual bool empty(void) const {
                return (bool) base_vec_type::empty();
            }
        };

        /**
         *
         */
        class CVertexData3v : public CVertexData, public CVector<Vertex3v> {
        public:
            typedef CVertexData3v type;
            typedef CVertexData3v self_type;
            typedef CVertexData base_type;
            typedef Vertex3v vertex_type;
            typedef CVector<Vertex3v> base_vec_type;

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
                base_vec_type::push_back(vertex);
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
                base_vec_type::push_back(vertex);
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
                base_vec_type::push_back(vertex);
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
                                const Color3f &color) {
                append(pos, normal, uv);
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
                                const Color4f &color) {
                append(pos, normal, uv);
            }
            /**
             * 
             */
            virtual void pop_back(void) {
                base_vec_type::pop_back();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXvoid *back(void) const {
                return (fgGFXvoid *)(&base_vec_type::back());
            }
            /**
             * 
             */
            virtual void clear(void) {
                base_vec_type::clear();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXvoid *front(void) const {
    #if defined(FG_USING_MARMALADE)
                return (fgGFXvoid *)(base_vec_type::begin());
    #else
                return (fgGFXvoid *)(&base_vec_type::front());
    #endif /* FG_USING_MARMALADE */
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint size(void) const {
                return base_vec_type::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumVertices(void) const {
                return base_vec_type::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumNormals(void) const {
                return base_vec_type::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumUVs(void) const {
                return base_vec_type::size();
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
                base_vec_type::reserve(newSize);
            }
            /**
             * 
             * @param newSize
             */
            virtual void resize(const unsigned int newSize) {
                base_vec_type::resize(newSize);
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXsizei stride(void) const {
                return sizeof (vertex_type);
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint attribMask(void) const {
                return (fgGFXuint)vertex_type::attribMask();
            }
            /**
             * 
             * @return 
             */
            virtual bool empty(void) const {
                return (bool) base_vec_type::empty();
            }
        };

        /**
         *
         */
        class CVertexData4v : public CVertexData, public CVector<Vertex4v> {
        public:
            typedef CVertexData4v type;
            typedef CVertexData4v self_type;
            typedef CVertexData base_type;
            typedef Vertex4v vertex_type;
            typedef CVector<Vertex4v> base_vec_type;

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
                base_vec_type::clear_optimised();
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
                vertex.color = Color4f(1.0f, 1.0f, 1.0f, 1.0f);
                base_vec_type::push_back(vertex);
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
                vertex.color = Color4f(1.0f, 1.0f, 1.0f, 1.0f);
                base_vec_type::push_back(vertex);
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
                vertex.color = Color4f(1.0f, 1.0f, 1.0f, 1.0f);
                base_vec_type::push_back(vertex);
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
                                const Color3f &color) {
                Vertex4v vertex;
                vertex.position = pos;
                vertex.normal = normal;
                vertex.uv = uv;
                vertex.color = Color4f(color.r, color.g, color.b, 1.0f);
                base_vec_type::push_back(vertex);
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
                                const Color4f &color) {
                Vertex4v vertex;
                vertex.position = pos;
                vertex.normal = normal;
                vertex.uv = uv;
                vertex.color = color;
                base_vec_type::push_back(vertex);
            }
            /**
             * 
             */
            virtual void pop_back(void) {
                base_vec_type::pop_back();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXvoid *back(void) const {
                return (fgGFXvoid *)(&base_vec_type::back());
            }
            /**
             * 
             */
            virtual void clear(void) {
                base_vec_type::clear();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXvoid *front(void) const {
    #if defined(FG_USING_MARMALADE)
                return (fgGFXvoid *)(base_vec_type::begin());
    #else
                return (fgGFXvoid *)(&base_vec_type::front());
    #endif /* FG_USING_MARMALADE */
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint size(void) const {
                return base_vec_type::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumVertices(void) const {
                return base_vec_type::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumNormals(void) const {
                return base_vec_type::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumUVs(void) const {
                return base_vec_type::size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumColors(void) const {
                return base_vec_type::size();
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
            virtual void appendIndice(fgGFXushort indice) {
                // empty
            }
            /**
             * 
             * @param newSize
             */
            virtual void reserve(const unsigned int newSize) {
                base_vec_type::reserve(newSize);
            }
            /**
             * 
             * @param newSize
             */
            virtual void resize(const unsigned int newSize) {
                base_vec_type::resize(newSize);
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXsizei stride(void) const {
                return sizeof (vertex_type);
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint attribMask(void) const {
                return (fgGFXuint)vertex_type::attribMask();
            }
            /**
             * 
             * @return 
             */
            virtual bool empty(void) const {
                return (bool) base_vec_type::empty();
            }
        };
    };
};

    #undef FG_INC_GFX_VERTEX_DATA_BLOCK
#endif	/* FG_INC_GFX_VERTEX_DATA */
