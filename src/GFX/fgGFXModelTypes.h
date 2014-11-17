/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_MODEL_TYPES_H_
    #define _FG_GFX_MODEL_TYPES_H_
    #define _FG_GFX_MODEL_TYPES_H_BLOCK_

    #ifndef _FG_GFX_TYPES_H_
        #include "fgGFXTypes.h"
    #endif
    #ifndef _FG_GFX_MATERIAL_H_
        #include "fgGFXMaterial.h"
    #endif
    #ifndef _FG_GFX_AA_BOUNDING_BOX_H_
        #include "fgGFXAABoundingBox.h"
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
inline void fgGfxComputeNormal(const fgVector3f & v1, const fgVector3f & v2, const fgVector3f & v3, fgVector3f & normal) {
    normal = glm::normalize(glm::cross(v3 - v1, v2 - v1));
}

/*
 * Base abstract class type for Mesh data
 */
struct fgGfxMeshBase : public fgVertexData {
    fgAABoundingBox3Df aabb;
    
    virtual ~fgGfxMeshBase() { };
    virtual void clear(void) = 0;
    virtual size_t getDataSize(void) = 0;
    virtual fgGFXuint getNumVertices(void) const = 0;
    virtual fgGFXuint getNumNormals(void) const = 0;
    virtual fgGFXuint getNumUVs(void) const = 0;
    virtual fgGFXuint getNumColors(void) const = 0;
    virtual fgGFXuint getNumIndices(void) const = 0;
    virtual void updateAABB(void) = 0;
};

/*
 * Special class for holding mesh data as SoA
 * - structure of arrays
 */
struct fgGfxMeshSoA : fgGfxMeshBase {
    /// Vector holding floats representing position (vertices)
    fgVector<fgGFXfloat> vertices; //3 fgVector3f
    /// Vector holding floats for normals
    fgVector<fgGFXfloat> normals; //3 fgVector3f
    /// Vector holding texture coords
    fgVector<fgGFXfloat> uvs; //2 fgVector2f
    /// Vector holding indices
    fgVector<fgGFXushort> indices;

    static const unsigned short POSITIONS_VBO_ARRAY_IDX;
    static const unsigned short VERTICES_VBO_ARRAY_IDX;
    static const unsigned short NORMALS_VBO_ARRAY_IDX;
    static const unsigned short TEX_COORDS_VBO_ARRAY_IDX;
    static const unsigned short UVS_VBO_ARRAY_IDX;
    static const unsigned short INDICES_VBO_ARRAY_IDX;

    // Default constructor
    fgGfxMeshSoA() { }

    #if 0
    fgGfxMeshSoA(tinyobj::mesh_t & mesh) {
        int n = mesh.positions.size();
        vertices.reserve(n);
        for(int i = 0; i < n; i++) {
            vertices.push_back(mesh.positions[i]);
        }
        n = mesh.normals.size();
        normals.reserve(n);
        for(int i = 0; i < n; i++) {
            normals.push_back(mesh.normals[i]);
        }
        if(normals.empty() && 0) {
            n = mesh.positions.size();
            for(int i = 0; i < n / 9; i += 9) {
                fgVector3f normal;
                fgVector3f v1(mesh.positions[i + 0], mesh.positions[i + 1], mesh.positions[i + 2]);
                fgVector3f v2(mesh.positions[i + 3], mesh.positions[i + 4], mesh.positions[i + 5]);
                fgVector3f v3(mesh.positions[i + 6], mesh.positions[i + 7], mesh.positions[i + 8]);
                fgGfxComputeNormal(v1, v2, v3, normal);
                normals.push_back(normal[0]);
                normals.push_back(normal[1]);
                normals.push_back(normal[2]);
            }
        }
        n = mesh.texcoords.size();
        uvs.reserve(n);
        for(int i = 0; i < n; i++) {
            uvs.push_back(mesh.texcoords[i]);
        }
        n = mesh.indices.size();
        indices.reserve(n);
        for(int i = 0; i < n; i++) {
            indices.push_back((fgGFXushort)mesh.indices[i]);
        }
    }
    #endif
    // Default virtual destructor
    virtual ~fgGfxMeshSoA() {
        clear();
        destroyBuffers();
    }

    /**
     * 
     */
    virtual void updateAABB(void) {        
        const void *data = (const void *)&vertices.front();
        // divide vertices size by 3 
        this->aabb.setBoundsFromData(data, sizeof(fgVector3f), vertices.size()/3);
    }
    
    // Returns whether the vertex data supports/generates VBOs
    virtual fgBool supportsVBO(void) const {
        return FG_TRUE;
    }

    // Returns whether the vertex data superclass has information on indices
    virtual fgBool hasIndices(void) const {
        return FG_TRUE;
    }

    // Returns raw ID for indices VBO (0 if invalid or not generated)
    virtual fgGFXuint getIndicesVBO(void) const;

    // Return GFX pointer to indices array, may be 0 if VBO
    // is generated or there are no indices at all
    virtual fgGFXvoid *getIndicesPointer(void) const;

    //
    virtual fgGFXboolean refreshAttributes(fgGfxAttributeData *pDataArray) const;
    
    //
    virtual fgGFXboolean setupAttributes(fgGfxAttributeData *pDataArray) const;

    // Generates the GFX buffers (VBO)
    virtual fgGFXboolean genBuffers(void);

    // Deletes/releases the GFX buffers (VBO)
    virtual fgGFXboolean deleteBuffers(void);

    // Releases the GFX buffers and frees the ID array
    virtual fgGFXboolean destroyBuffers(void);

    // Clears the vertex data
    virtual void clear(void) {
        vertices.clear_optimised();
        normals.clear_optimised();
        uvs.clear_optimised();
        indices.clear_optimised();
    }

    // Returns whether the vertex data is SoA (structure of arrays)
    virtual fgBool isSoA(void) const {
        return FG_TRUE;
    }

    // Returns whether the vertex data is AoS (array of structures)
    virtual fgBool isAoS(void) const {
        return FG_FALSE;
    }

    // Returns the data size in bytes (something like sizeof) 
    virtual size_t getDataSize(void) {
        size_t size = 0;
        size += sizeof (vertices) + sizeof (normals) + sizeof (uvs) + sizeof (indices);
        size += sizeof (fgGFXfloat) * vertices.size();
        size += sizeof (fgGFXfloat) * normals.size();
        size += sizeof (fgGFXfloat) * uvs.size();
        size += sizeof (fgGFXushort) * indices.size();
        return size;
    }

    // Returns the number of vertices
    virtual fgGFXuint getNumVertices(void) const {
        return (fgGFXuint)vertices.size();
    }

    // Returns the number of normals
    virtual fgGFXuint getNumNormals(void) const {
        return (fgGFXuint)normals.size();
    }

    // Returns the number of texture coords
    virtual fgGFXuint getNumUVs(void) const {
        return (fgGFXuint)uvs.size();
    }

    // Returns the number of colors in the data
    virtual fgGFXuint getNumColors(void) const {
        return 0;
    }

    // Returns the number of indices
    virtual fgGFXuint getNumIndices(void) const {
        return (fgGFXuint)indices.size();
    }

    // Append the vertex data (position)
    virtual void append(const fgVector3f &pos) {
        vertices.push_back(pos.x);
        vertices.push_back(pos.y);
        vertices.push_back(pos.z);
        //fgVertex3 vertex;
        //vertex.position = pos;
        //vertex.normal = fgVector3f(1.0f, 1.0f, 1.0f);
        //vertex.uv = fgVector2f(1.0f, 1.0f);
        //fgVector<fgVertex3>::push_back(vertex);
    }

    // Append to the vertex data (position and uv)
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector2f &uv) {
        vertices.push_back(pos.x);
        vertices.push_back(pos.y);
        vertices.push_back(pos.z);
        uvs.push_back(uv.x);
        uvs.push_back(uv.y);
        /*fgVertex3 vertex;
        vertex.position = pos;
        vertex.normal = fgVector3f(1.0f, 1.0f, 1.0f);
        vertex.uv = uv;
        fgVector<fgVertex3>::push_back(vertex);*/
    }

    // Append to the vertex data (position, normal and uv)
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv) {
        vertices.push_back(pos.x);
        vertices.push_back(pos.y);
        vertices.push_back(pos.z);
        normals.push_back(normal.x);
        normals.push_back(normal.y);
        normals.push_back(normal.z);
        uvs.push_back(uv.x);
        uvs.push_back(uv.y);
        /*fgVertex3 vertex;
        vertex.position = pos;
        vertex.normal = normal;
        vertex.uv = uv;
        fgVector<fgVertex3>::push_back(vertex);*/
    }

    // Append to the vertex data (position, normal and uv). Color will be ignored
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv,
                        const fgColor3f &color) {
        append(pos, normal, uv);
    }

    // Append to the vertex data (position, normal and uv). Color will be ignored
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv,
                        const fgColor4f &color) {
        append(pos, normal, uv);
    }

    // Remove one vertex (removes positions, normals and uv)
    virtual void pop_back(void) {
        vertices.pop_back();
        vertices.pop_back();
        vertices.pop_back();
        normals.pop_back();
        normals.pop_back();
        normals.pop_back();
        uvs.pop_back();
        uvs.pop_back();
        //fgVector<fgVertex3>::pop_back();
    }

    // Pointer to the back (vertices array - positions)
    virtual fgGFXvoid *back(void) const {
        //return (fgGFXvoid *)(&fgVector<fgVertex3>::front());
        return (fgGFXvoid *)(&vertices.back());
    }

    // Pointer to the front (vertices array - positions)
    virtual fgGFXvoid *front(void) const {
        //return (fgGFXvoid *)(&fgVector<fgVertex3>::front());
        return (fgGFXvoid *)(&vertices.front());
    }

    // Returns the size of the data (here: number of positions)
    virtual fgGFXuint size(void) const {
        return vertices.size();
    }
    
    //
    virtual void reserve(const unsigned int newSize) {
        this->vertices.reserve(newSize);
        //this->indices.reserve(newSize);
        this->normals.reserve(newSize);
        this->uvs.reserve(newSize);
    }
    
    //
    virtual void resize(const unsigned int newSize) {
        this->vertices.resize(newSize);
        //this->indices.resize(newSize);
        this->normals.resize(newSize);
        this->uvs.resize(newSize);
    }

    // Returns the stride of the data (here: 0)
    virtual fgGFXsizei stride(void) const {
        return 0; //sizeof(fgVertex3);
    }

    // Returns the attribute mask
    virtual fgGFXuint attribMask(void) const {
        return FG_GFX_POSITION_BIT | FG_GFX_NORMAL_BIT | FG_GFX_UVS_BIT;
    }

    // Returns whether the data is empty (positions)
    virtual bool empty(void) const {
        return (bool) vertices.empty();
    }
};

/*
 *
 */
struct fgGfxMeshAoS : fgGfxMeshBase {
    /// Vertex data - AoS
    fgVertexData3v vertices;
    /// Special indices array
    // #FIXME Need to check for OGL version, ushort is mandatory on ES2
    fgVector<fgGFXushort> indices;


    static const unsigned short POSITIONS_VBO_ARRAY_IDX;
    static const unsigned short VERTICES_VBO_ARRAY_IDX;
    static const unsigned short NORMALS_VBO_ARRAY_IDX;
    static const unsigned short TEX_COORDS_VBO_ARRAY_IDX;
    static const unsigned short UVS_VBO_ARRAY_IDX;
    static const unsigned short INDICES_VBO_ARRAY_IDX;

    // Default empty constructor for Mesh AoS object
    fgGfxMeshAoS() { }

    // #FIXME #SERIOUSLY
    #if 0
    fgGfxMeshAoS(tinyobj::mesh_t & mesh) {
        // pos, norm, uv
        int npos = mesh.positions.size();
        int nnorm = mesh.normals.size();
        int nuvs = mesh.texcoords.size();
        int nind = mesh.indices.size();
        vertices.reserve(npos / 3);
        for(int i = 0, k = 0; i < npos; i += 3, k += 2) {
            fgVertex3v vertex;
            for(int j = 0; j < 3; j++)
                vertex.position[j] = mesh.positions[i + j];

            for(int j = 0; j < 3 && i + j < nnorm; j++)
                vertex.normal[j] = mesh.normals[i + j];

            for(int j = 0; j < 2 && k + j < nuvs; j++) {
                vertex.uv[j] = mesh.texcoords[k + j];
                // FLIP TEXTURE
                vertex.uv[j + 1] = 1.0f - mesh.texcoords[k + j + 1];
                break;
            }
            vertices.push_back(vertex);
        }
        if(nnorm == 0) {
            // FIXME - this is soooo fucked up ....
            for(int i = 2; i < npos; i++) {
                fgGfxComputeNormal(vertices[i].position, vertices[i - 1].position, vertices[i - 2].position, vertices[i].normal);
            }
        }
        indices.reserve(nind);
        for(int i = 0; i < nind; i++) {
            indices.push_back((fgGFXushort)mesh.indices[i]);
        }
    }
    #endif
    // Default destructor for Mesh AoS object
    virtual ~fgGfxMeshAoS() {
        clear();
        destroyBuffers();
    }
    
    /**
     * 
     */
    virtual void updateAABB(void) {        
        const void *data = (const void *)vertices.front();
        // Here size does not need to be divided - AoS
        this->aabb.setBoundsFromData(data, vertices.stride(), vertices.size());
    }

    // Clear the internal data arrays
    virtual void clear(void) {
        vertices.clear_optimised();
        indices.clear_optimised();
    }

    // Returns true if this vertex data structure supports VBOs
    virtual fgBool supportsVBO(void) const {
        return FG_TRUE;
    }

    // Returns whether the vertex data superclass has information on indices
    virtual fgBool hasIndices(void) const {
        return FG_TRUE;
    }

    // Returns raw ID for indices VBO (0 if invalid or not generated)
    virtual fgGFXuint getIndicesVBO(void) const;

    // Return GFX pointer to indices array, may be 0 if VBO
    // is generated or there are no indices at all
    virtual fgGFXvoid *getIndicesPointer(void) const;

    //
    virtual fgGFXboolean refreshAttributes(fgGfxAttributeData *pDataArray) const {
        return vertices.refreshAttributes(pDataArray);
    }
    
    // Attributes for mesh AoS is done the same way as for vertexData v3
    // There is still needed fix for indices special array. It's because
    // indices are not treated as an attribute. It's a special parameter
    // used directly with drawing function (as pointer to array or VBOs)
    virtual fgGFXboolean setupAttributes(fgGfxAttributeData *pDataArray) const {
        return vertices.setupAttributes(pDataArray);
    }

    //
    virtual fgBool hasVBO(void) const {
        return vertices.hasVBO();
    }

    //
    virtual int getVBOCount(void) const {
        return vertices.getVBOCount();
    }

    //
    virtual int& getRefVBOCount(void) {
        return vertices.getRefVBOCount();
    }

    //
    virtual fgGfxBufferID* getPtrVBO(void) const {
        return vertices.getPtrVBO();
    }

    //
    virtual fgGfxBufferID*& getRefPtrVBO(void) {
        return vertices.getRefPtrVBO();
    }

    //
    virtual fgGFXboolean genBuffers(void);

    //
    virtual fgGFXboolean deleteBuffers(void);

    //
    virtual fgGFXboolean destroyBuffers(void);

    //
    virtual fgBool isSoA(void) const {
        return FG_FALSE;
    }

    // 
    virtual fgBool isAoS(void) const {
        return FG_TRUE;
    }

    //
    virtual size_t getDataSize(void) {
        size_t size = 0;
        size += sizeof (vertices) + sizeof (indices);
        size += sizeof (fgVertex3v) * vertices.size();
        size += sizeof (fgGFXuint) * indices.size();
        return size;
    }

    //
    virtual fgGFXuint getNumVertices(void) const {
        return (fgGFXuint)vertices.size();
    }

    //
    virtual fgGFXuint getNumNormals(void) const {
        return (fgGFXuint)vertices.size();
    }

    //
    virtual fgGFXuint getNumUVs(void) const {
        return (fgGFXuint)vertices.size();
    }

    //
    virtual fgGFXuint getNumColors(void) const {
        return 0;
    }

    //
    virtual fgGFXuint getNumIndices(void) const {
        return (fgGFXuint)indices.size();
    }

    //
    virtual fgGFXuint attribMask(void) const {
        return vertices.attribMask();
    }

    //
    virtual void append(const fgVector3f &pos) {
        vertices.append(pos);
    }

    //
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector2f &uv) {
        vertices.append(pos, uv);
    }

    //
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv) {
        vertices.append(pos, normal, uv);
    }

    //
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv,
                        const fgColor3f &color) {
        vertices.append(pos, normal, uv);
    }

    //
    virtual void append(
                        const fgVector3f &pos,
                        const fgVector3f &normal,
                        const fgVector2f &uv,
                        const fgColor4f &color) {
        vertices.append(pos, normal, uv);
    }

    //
    virtual void pop_back(void) {
        vertices.pop_back();
    }

    //
    virtual fgGFXvoid *back(void) const {
        return vertices.back();
    }

    //
    virtual fgGFXvoid *front(void) const {
        return vertices.front();
    }

    //
    virtual fgGFXuint size(void) const {
        return vertices.size();
    }

    //
    virtual void reserve(const unsigned int newSize) {
        this->vertices.reserve(newSize);
        //this->indices.reserve(newSize);
        //this->normals.reserve(newSize);
        //this->uvs.reserve(newSize);
    }
    
    //
    virtual void resize(const unsigned int newSize) {
        this->vertices.resize(newSize);
        //this->indices.resize(newSize);
        //this->normals.resize(newSize);
        //this->uvs.resize(newSize);
    }
    
    //
    virtual fgGFXsizei stride(void) const {
        return vertices.stride();
    }

    //
    virtual bool empty(void) const {
        return (bool) vertices.empty();
    }
};

/*
 *
 */
struct fgGfxShape {
    ///
    std::string name;
    ///
    fgGfxMaterial* material;
    ///
    fgGfxMeshBase* mesh;

    //
    fgGfxShape() : name(), material(NULL), mesh(NULL) { }

    //
    virtual ~fgGfxShape() {
        clear();
    }
    
    void updateAABB(void) {
        if(mesh)
            mesh->updateAABB();        
    }
    
    //
    void clear(void) {
        if(material)
            delete material;
        material = NULL;

        if(mesh)
            delete mesh;
        mesh = NULL;
        name.clear();
    }

    //
    size_t getDataSize(void) {
        size_t size = 0;
        size += name.length();
        size += sizeof (fgGfxShape);
        if(material)
            size += material->getDataSize();
        if(mesh)
            size += mesh->getDataSize();
        return size;
    }
};

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
// FBX - Autodesk exchange - exchange format, in particular for interoperability between Autodesk products and other Digital content creation (DCC) software packages
    #define	FG_GFX_MODEL_RES_FBX_EXTENSION		"fbx"
// LWO - Lightwave - LightWave high-end software file format
    #define	FG_GFX_MODEL_RES_LWO_EXTENSION		"lwo"
// OFF - Object File Format 
    #define	FG_GFX_MODEL_RES_OFF_EXTENSION		"off"
// X - DirectX 3D Model
    #define	FG_GFX_MODEL_RES_X_EXTENSION		"x"

    #undef _FG_GFX_MODEL_TYPES_H_BLOCK_
#endif /* _FG_GFX_MODEL_TYPES_H_ */
