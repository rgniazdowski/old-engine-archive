/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GFX_MESH
    #define FG_INC_GFX_MESH
    #define FG_INC_GFX_MESH_BLOCK

    #ifndef FG_INC_GFX_TYPES
        #include "fgGfxTypes.h"
    #endif
    
    #ifndef FG_INC_GFX_AA_BOUNDING_BOX
        #include "fgGfxAABoundingBox.h"
    #endif

    #ifndef FG_INC_GFX_PRIMITIVES
        #include "fgGfxPrimitives.h"
    #endif

/*
Assuming the container has at least one element in it, you 
need to get the address of the initial element of the 
container, which you can get via:

(the address of the element at index 0)
        &something[0] or &something.front()

(the address of the element pointed to by the iterator returned by begin()).
        &*something.begin() 

 */

// #DAFUQ?
//inline void fgGfxComputeNormal(const fg::gfx::Vector3f & v1,
//                               const fg::gfx::Vector3f & v2,
//                               const fg::gfx::Vector3f & v3,
//                               fg::gfx::Vector3f & normal) {
//    normal = glm::normalize(glm::cross(v3 - v1, v2 - v1));
//}

namespace fg {
    namespace gfx {

        /**
         * Base abstract class type for Mesh data
         */
        struct SMeshBase : public CVertexData {
            ////
            AABoundingBox3Df aabb;
            ///
            Vector3f displacement;
            ////
            PrimitiveMode primMode;
            /**
             * 
             */
            SMeshBase() : aabb(), displacement(), primMode(PrimitiveMode::TRIANGLES) { }
            /**
             * 
             */
            virtual ~SMeshBase() { };
            /**
             * 
             */
            virtual void clear(void) = 0;
            /**
             * 
             * @return 
             */
            virtual size_t getDataSize(void) = 0;
            /**
             * 
             */
            virtual void updateAABB(void) = 0;
            /**
             * 
             */
            virtual void fixCenter(fgBool saveDisplacement = FG_TRUE) = 0;

            /**
             *
             * @return
             */
            virtual fgBool isSkinnedMesh(void) const {
                return FG_FALSE;
            }
        }; // struct SMeshBase

        /**
         * Special class for holding mesh data as SoA
         * - structure of arrays
         */
        struct SMeshSoA : SMeshBase {
            typedef SMeshBase base_type;
            typedef SMeshSoA self_type;

            /// Vector holding floats representing position (vertices)
            CVector<fgGFXfloat> vertices; //3 fgVector3f
            /// Vector holding floats for normals
            CVector<fgGFXfloat> normals; //3 fgVector3f
            /// Vector holding texture coords
            CVector<fgGFXfloat> uvs; //2 fgVector2f
            /// Vector holding indices
            CVector<fgGFXushort> indices;

            static const unsigned short POSITIONS_VBO_ARRAY_IDX;
            static const unsigned short VERTICES_VBO_ARRAY_IDX;
            static const unsigned short NORMALS_VBO_ARRAY_IDX;
            static const unsigned short TEX_COORDS_VBO_ARRAY_IDX;
            static const unsigned short UVS_VBO_ARRAY_IDX;
            static const unsigned short INDICES_VBO_ARRAY_IDX;
            static const unsigned short VBO_ARRAY_SIZE;

            /**
             * 
             */
            SMeshSoA() : base_type(), vertices(), normals(), uvs(), indices() { }
            /**
             * Destructor for the Mesh SoA object
             */
            virtual ~SMeshSoA() {
                clear();
                destroyBuffers();
            }
            /**
             * 
             */
            virtual void updateAABB(void) {
                const void *data = (const void *)&vertices.front();
                // divide vertices size by 3 
                this->aabb.setBoundsFromData(data, sizeof (Vector3f), vertices.size() / 3);
            }
            /**
             * 
             */
            virtual void fixCenter(fgBool saveDisplacement = FG_TRUE);
            /**
             * Returns whether the vertex data supports/generates VBOs
             * @return 
             */
            virtual fgBool supportsVBO(void) const {
                return FG_TRUE;
            }
            /**
             * Returns whether the vertex data superclass has information on indices
             * @return 
             */
            virtual fgBool hasIndices(void) const {
                return FG_TRUE;
            }

            /**
             * Returns raw ID for indices VBO (0 if invalid or not generated)
             * @return 
             */
            virtual fgGFXuint getIndicesVBO(void) const;

            // Return GFX pointer to indices array, may be 0 if VBO
            // is generated or there are no indices at all
            virtual fgGFXvoid *getIndicesPointer(void) const;

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
             * Generates the GFX buffers (VBO)
             * @return 
             */
            virtual fgGFXboolean genBuffers(void);

            /**
             * Deletes/releases the GFX buffers (VBO)
             * @return 
             */
            virtual fgGFXboolean deleteBuffers(void);

            /**
             * Releases the GFX buffers and frees the ID array
             * @return 
             */
            virtual fgGFXboolean destroyBuffers(void);
            /**
             * Clears the vertex data
             */
            virtual void clear(void) {
                vertices.clear_optimised();
                normals.clear_optimised();
                uvs.clear_optimised();
                indices.clear_optimised();
            }
            /**
             * Returns whether the vertex data is SoA (structure of arrays)
             * @return 
             */
            virtual fgBool isSoA(void) const {
                return FG_TRUE;
            }
            /**
             * Returns whether the vertex data is AoS (array of structures)
             * @return 
             */
            virtual fgBool isAoS(void) const {
                return FG_FALSE;
            }
            /**
             * Returns the data size in bytes
             * @return 
             */
            virtual size_t getDataSize(void) {
                size_t size = 0;
                size += sizeof (vertices) + sizeof (normals) + sizeof (uvs) + sizeof (indices);
                size += sizeof (fgGFXfloat) * vertices.size();
                size += sizeof (fgGFXfloat) * normals.size();
                size += sizeof (fgGFXfloat) * uvs.size();
                size += sizeof (fgGFXushort) * indices.size();
                return size;
            }
            /**
             *  Returns the number of vertices
             * @return 
             */
            virtual fgGFXuint getNumVertices(void) const {
                return (fgGFXuint)vertices.size();
            }
            /**
             * Returns the number of normals
             * @return 
             */
            virtual fgGFXuint getNumNormals(void) const {
                return (fgGFXuint)normals.size();
            }
            /**
             * Returns the number of texture coords
             * @return 
             */
            virtual fgGFXuint getNumUVs(void) const {
                return (fgGFXuint)uvs.size();
            }
            /**
             * Returns the number of colors in the data
             * @return 
             */
            virtual fgGFXuint getNumColors(void) const {
                return 0;
            }
            /**
             * Returns the number of indices
             * @return 
             */
            virtual fgGFXuint getNumIndices(void) const {
                return (fgGFXuint)indices.size();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumTangents(void) const {
                return 0;
            }
            /**
             *
             * @param indice
             */
            virtual fgGFXuint getNumBitangents(void) const {
                return 0;
            }
            /**
             *
             */
            virtual void appendIndice(fgGFXushort indice) {
                indices.push_back(indice);
            }
            /**
             * Append the vertex data (position)
             * @param pos
             */
            virtual void append(const Vector3f &pos) {
                vertices.push_back(pos.x);
                vertices.push_back(pos.y);
                vertices.push_back(pos.z);
            }
            /**
             * Append to the vertex data (position and uv)
             * @param pos
             * @param uv
             */
            virtual void append(const Vector3f &pos,
                                const Vector2f &uv) {
                vertices.push_back(pos.x);
                vertices.push_back(pos.y);
                vertices.push_back(pos.z);
                uvs.push_back(uv.x);
                uvs.push_back(uv.y);
            }
            /**
             * Append to the vertex data (position, normal and uv)
             * @param pos
             * @param normal
             * @param uv
             */
            virtual void append(const Vector3f &pos,
                                const Vector3f &normal,
                                const Vector2f &uv) {
                vertices.push_back(pos.x);
                vertices.push_back(pos.y);
                vertices.push_back(pos.z);
                normals.push_back(normal.x);
                normals.push_back(normal.y);
                normals.push_back(normal.z);
                uvs.push_back(uv.x);
                uvs.push_back(uv.y);
            }
            /**
             * Append to the vertex data (position, normal and uv). Color will be ignored
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
             * Append to the vertex data (position, normal and uv). Color will be ignored
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
             * @param pos
             * @param normal
             * @param uv
             * @param tangent
             * @param bitangent
             */
            virtual void append(const Vector3f& pos,
                                const Vector3f& normal,
                                const Vector2f& uv,
                                const Vector3f& tangent,
                                const Vector3f& bitangent) {
                append(pos, normal, uv);
            }
            /**
             * Remove one vertex (removes positions, normals and uv)
             */
            virtual void pop_back(void) {
                vertices.pop_back();
                vertices.pop_back();
                vertices.pop_back();
                normals.pop_back();
                normals.pop_back();
                normals.pop_back();
                uvs.pop_back();
                uvs.pop_back();
            }
            /**
             * Pointer to the back (vertices array - positions)
             * @return 
             */
            virtual fgGFXvoid *back(void) const {
                //return (fgGFXvoid *)(&fgVector<fgVertex3>::front());
                return (fgGFXvoid *)(&vertices.back());
            }
            /**
             * Pointer to the front (vertices array - positions)
             * @return 
             */
            virtual fgGFXvoid *front(void) const {
                //return (fgGFXvoid *)(&fgVector<fgVertex3>::front());
                return (fgGFXvoid *)(&vertices.front());
            }
            /**
             * Returns the size of the data (here: number of positions)
             * @return 
             */
            virtual fgGFXuint size(void) const {
                return vertices.size();
            }
            /**
             * 
             * @param newSize
             */
            virtual void reserve(const unsigned int newSize) {
                this->vertices.reserve(newSize);
                //this->indices.reserve(newSize);
                this->normals.reserve(newSize);
                this->uvs.reserve(newSize);
            }
            /**
             * 
             * @param newSize
             */
            virtual void resize(const unsigned int newSize) {
                this->vertices.resize(newSize);
                //this->indices.resize(newSize);
                this->normals.resize(newSize);
                this->uvs.resize(newSize);
            }
            /**
             * 
             * @param diff
             */
            virtual void translate(const Vector3f& diff);
            /**
             * Returns the stride of the data (here: 0)
             * @return 
             */
            virtual fgGFXsizei stride(void) const {
                return 0; //sizeof(fgVertex3);
            }
            /**
             * Returns the attribute mask
             * @return 
             */
            virtual AttributeMask attribMask(void) const {
                return (ATTRIBUTE_POSITION_BIT | ATTRIBUTE_NORMAL_BIT | ATTRIBUTE_UVS_BIT);
            }
            /**
             *
             * @return
             */
            virtual fgGFXuint components(void) const {
                return 3;
            }

            /**
             * Returns whether the data is empty (positions)
             * @return 
             */
            virtual bool empty(void) const {
                return (bool) vertices.empty();
            }
        }; // struct SMeshSoA

        //----------------------------------------------------------------------

        /**
         *
         */
        struct SMeshAoS : SMeshBase {
            typedef SMeshBase base_type;
            typedef SMeshAoS self_type;

            /// Vertex data - AoS
            CVertexData* vertices;
            /// Special indices array
            /// #FIXME Need to check for OGL version, ushort is mandatory on ES2
            CVector<fgGFXushort> indices;            

            static const unsigned short POSITIONS_VBO_ARRAY_IDX;
            static const unsigned short VERTICES_VBO_ARRAY_IDX;
            static const unsigned short NORMALS_VBO_ARRAY_IDX;
            static const unsigned short TEX_COORDS_VBO_ARRAY_IDX;
            static const unsigned short UVS_VBO_ARRAY_IDX;
            static const unsigned short INDICES_VBO_ARRAY_IDX;
            static const unsigned short VBO_ARRAY_SIZE;
            /**
             * Default constructor for Mesh AoS object
             */
            SMeshAoS();
            /**
             *
             * @param vertexType
             */
            SMeshAoS(VertexType vertexType);
            /**
             *
             * @param attribMask
             */
            SMeshAoS(AttributeMask attribMask);
            /**
             * Destructor for Mesh AoS object
             */
            virtual ~SMeshAoS();
            /**
             *
             * @param attribMask
             * @return
             */
            fgBool convertVertexData(AttributeMask attribMask);
            /**
             *
             * @param vertexType
             * @return
             */
            fgBool convertVertexData(VertexType vertexType);
            /**
             *
             * @return
             */
            VertexType getVertexType(void) const;
            /**
             * 
             */
            virtual void updateAABB(void) {
                const void *data = (const void *)this->vertices->front();
                // Here size does not need to be divided - AoS
                this->aabb.setBoundsFromData(data, this->vertices->stride(), this->vertices->size());
            }
            /**
             *
             */
            virtual void fixCenter(fgBool saveDisplacement = FG_TRUE);
            /**
             * Clear the internal data arrays
             */
            virtual void clear(void) {
                if(this->vertices)
                    this->vertices->clear();
                this->indices.clear_optimised();
            }
            /**
             * Returns true if this vertex data structure supports VBOs
             * @return 
             */
            virtual fgBool supportsVBO(void) const {
                return FG_TRUE;
            }
            /**
             * Returns whether the vertex data superclass has information on indices
             * @return 
             */
            virtual fgBool hasIndices(void) const {
                return FG_TRUE;
            }

            /**
             * Returns raw ID for indices VBO (0 if invalid or not generated)
             * @return 
             */
            virtual fgGFXuint getIndicesVBO(void) const;

            /**
             * Return GFX pointer to indices array, may be 0 if VBO
             * is generated or there are no indices at all
             * @return 
             */
            virtual fgGFXvoid* getIndicesPointer(void) const;
            /**
             * 
             * @param pDataArray
             * @return 
             */
            virtual fgGFXboolean refreshAttributes(SAttributeData* pDataArray) const {
                return this->vertices->refreshAttributes(pDataArray);
            }
            /**
             * Attributes for mesh AoS is done the same way as for vertexData v3
             * There is still needed fix for indices special array. It's because
             * indices are not treated as an attribute. It's a special parameter
             * used directly with drawing function (as pointer to array or VBOs)
             * @param pDataArray
             * @return 
             */
            virtual fgGFXboolean setupAttributes(SAttributeData* pDataArray) const {
                return this->vertices->setupAttributes(pDataArray);
            }
            /**
             * 
             * @return 
             */
            virtual fgBool hasVBO(void) const {
                return this->vertices->hasVBO();
            }
            /**
             * 
             * @return 
             */
            virtual int getVBOCount(void) const {
                return this->vertices->getVBOCount();
            }
            /**
             * 
             * @return 
             */
            virtual int& getRefVBOCount(void) {
                return this->vertices->getRefVBOCount();
            }
            /**
             * 
             * @return 
             */
            virtual SBufferID* getPtrVBO(void) const {
                return this->vertices->getPtrVBO();
            }
            /**
             * 
             * @return 
             */
            virtual SBufferID*& getRefPtrVBO(void) {
                return this->vertices->getRefPtrVBO();
            }

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
             * @return 
             */
            virtual size_t getDataSize(void) {
                size_t size = 0;
                size += sizeof (this->vertices) + sizeof (this->indices);
                size += this->vertices->stride() * this->vertices->size();
                size += sizeof (fgGFXuint) * this->indices.size();
                return size;
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumVertices(void) const {
                return (fgGFXuint)this->vertices->getNumVertices();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumNormals(void) const {
                return (fgGFXuint)this->vertices->getNumNormals();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumUVs(void) const {
                return (fgGFXuint)this->vertices->getNumUVs();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumColors(void) const {
                return (fgGFXuint)this->vertices->getNumColors();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint getNumIndices(void) const {
                return (fgGFXuint)this->indices.size();
            }
            /**
             *
             * @return
             */
            virtual fgGFXuint getNumTangents(void) const {
                return this->vertices->getNumTangents();
            }
            /**
             *
             * @return
             */
            virtual fgGFXuint getNumBitangents(void) const {
                return this->vertices->getNumBitangents();
            }
            /**
             * 
             * @return 
             */
            virtual AttributeMask attribMask(void) const {
                if(this->vertices)
                    return this->vertices->attribMask();
                else
                    return ATTRIBUTE_ZERO_BIT;
            }
            /**
             *
             */
            virtual void appendIndice(fgGFXushort indice) {
                this->indices.push_back(indice);
            }
            /**
             * 
             * @param pos
             */
            virtual void append(const Vector3f& pos) {
                vertices->append(pos);
            }
            /**
             * 
             * @param pos
             * @param uv
             */
            virtual void append(const Vector3f& pos,
                                const Vector2f& uv) {
                this->vertices->append(pos, uv);
            }
            /**
             * 
             * @param pos
             * @param normal
             * @param uv
             */
            virtual void append(const Vector3f& pos,
                                const Vector3f& normal,
                                const Vector2f& uv) {
                this->vertices->append(pos, normal, uv);
            }
            /**
             * 
             * @param pos
             * @param normal
             * @param uv
             * @param color
             */
            virtual void append(const Vector3f& pos,
                                const Vector3f& normal,
                                const Vector2f& uv,
                                const Color3f& color) {
                this->vertices->append(pos, normal, uv);
            }
            /**
             * 
             * @param pos
             * @param normal
             * @param uv
             * @param color
             */
            virtual void append(const Vector3f& pos,
                                const Vector3f& normal,
                                const Vector2f& uv,
                                const Color4f& color) {
                this->vertices->append(pos, normal, uv);
            }
            /**
             * 
             * @param pos
             * @param normal
             * @param uv
             * @param tangent
             * @param bitangent
             */
            virtual void append(const Vector3f& pos,
                                const Vector3f& normal,
                                const Vector2f& uv,
                                const Vector3f& tangent,
                                const Vector3f& bitangent) {
                this->vertices->append(pos, normal, uv);
            }
            /**
             * 
             */
            virtual void pop_back(void) {
                this->vertices->pop_back();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXvoid *back(void) const {
                return this->vertices->back();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXvoid *front(void) const {
                return this->vertices->front();
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXuint size(void) const {
                return this->vertices->size();
            }
            /**
             * 
             * @param newSize
             */
            virtual void reserve(const unsigned int newSize) {
                this->vertices->reserve(newSize);
            }
            /**
             * 
             * @param newSize
             */
            virtual void resize(const unsigned int newSize) {
                this->vertices->resize(newSize);
            }
            /**
             *
             * @param diff
             */
            virtual void translate(const Vector3f& diff) {
                this->vertices->translate(diff);
            }
            /**
             * 
             * @return 
             */
            virtual fgGFXsizei stride(void) const {
                return this->vertices->stride();
            }
            /**
             * 
             * @return
             */
            virtual fgGFXuint components(void) const {
                return this->vertices->components();
            }

            /**
             * 
             * @return 
             */
            virtual bool empty(void) const {
                return (bool) this->vertices->empty();
            }
        }; // struct SMeshAoS

        //----------------------------------------------------------------------

    } // namespace gfx
} // namespace fg

// Custom 3d model file format
//#define	FG_GFX_MODEL_RES_CUSTOM		0x0F0
// 3DS - Autodesk 3ds Max 3D
    #define	FG_GFX_MODEL_RES_3DS_EXTENSION		"3ds"
// OBJ - Wavefront Technologies
    #define	FG_GFX_MODEL_RES_OBJ_EXTENSION		"obj"
// BLEND - Blender file database
    #define	FG_GFX_MODEL_RES_BLEND_EXTENSION	"blend"
// DAE - COLLADA
    #define	FG_GFX_MODEL_RES_DAE_EXTENSION		"dae"
// DXF - AutoCAD, Drawing Exchange Format - CAD data file format developed by Autodesk
    #define	FG_GFX_MODEL_RES_DXF_EXTENSION		"dxf"
// FBX - Autodesk exchange - exchange format, in particular for inter-operability between Autodesk products and other Digital content creation (DCC) software packages
    #define	FG_GFX_MODEL_RES_FBX_EXTENSION		"fbx"
// LWO - Lightwave - LightWave high-end software file format
    #define	FG_GFX_MODEL_RES_LWO_EXTENSION		"lwo"
// OFF - Object File Format 
    #define	FG_GFX_MODEL_RES_OFF_EXTENSION		"off"
// X - DirectX 3D Model
    #define	FG_GFX_MODEL_RES_X_EXTENSION		"x"

    #undef FG_INC_GFX_MESH_BLOCK
#endif /* FG_INC_GFX_MESH */
