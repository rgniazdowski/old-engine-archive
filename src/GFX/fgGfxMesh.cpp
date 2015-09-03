/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxMesh.h"
#include "fgGfxPlatform.h"
#include "Util/fgMemory.h"

using namespace fg;
//------------------------------------------------------------------------------

const unsigned short gfx::SMeshSoA::POSITIONS_VBO_ARRAY_IDX = 0;
const unsigned short gfx::SMeshSoA::VERTICES_VBO_ARRAY_IDX = 0;
const unsigned short gfx::SMeshSoA::NORMALS_VBO_ARRAY_IDX = 1;
const unsigned short gfx::SMeshSoA::TEX_COORDS_VBO_ARRAY_IDX = 2;
const unsigned short gfx::SMeshSoA::UVS_VBO_ARRAY_IDX = 2;
const unsigned short gfx::SMeshSoA::INDICES_VBO_ARRAY_IDX = 3;

/******************************************************************************
 * MESH SOA FUNCTIONS - STRUCTURE OF ARRAYS
 ******************************************************************************/

void gfx::SMeshSoA::fixCenter(fgBool saveDisplacement) {
    const unsigned int n = this->vertices.size();
    if(!n)
        return;
    const Vector3f center = this->aabb.getCenter();
    //const void *data = (const void *) & this->vertices.front();
    for(unsigned int i = 0; i < n; i += 3) {
        for(unsigned int j = 0; j < 3; j++) {
            this->vertices[i + j] -= center[j];
        }
    }
    if(saveDisplacement) {
        this->displacement += center;
    }
    this->aabb.min -= center;
    this->aabb.max -= center;
    //this->aabb.setBoundsFromData(data, sizeof (Vector3f), n);
}
//------------------------------------------------------------------------------

fgGFXuint gfx::SMeshSoA::getIndicesVBO(void) const {
    if(!hasVBO())
        return 0;
    return getPtrVBO()[INDICES_VBO_ARRAY_IDX].id;
}
//------------------------------------------------------------------------------

fgGFXvoid *gfx::SMeshSoA::getIndicesPointer(void) const {
    if(!hasVBO())
        return (fgGFXvoid *)((unsigned int*)&indices.front());
    return (fgGFXvoid *)0;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SMeshSoA::refreshAttributes(SAttributeData *pDataArray) const {
    if(!pDataArray)
        return FG_GFX_FALSE;
    // 3V - pos + norm + uv
    fgGFXint index = 0;
    // If VBO is used, offset is 0 because it'll be separate VBO
    // Set pointer to front of vertices array (positions)
    uintptr_t offset = 0;
    uintptr_t pointer = (uintptr_t)((unsigned int *)&vertices.front());
    const fgBool b_hasVBO = hasVBO();
    // Position coordinates - activated
    index = FG_GFX_ATTRIB_POS_LOCATION;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[POSITIONS_VBO_ARRAY_IDX].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Set pointer to normals array
    // Offset is 0 because it is a separate VBO
    offset = 0;
    pointer = (uintptr_t)((unsigned int*)&normals.front());
    // Normals coords - activated
    index = FG_GFX_ATTRIB_NORM_LOCATION;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[NORMALS_VBO_ARRAY_IDX].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to UVs (second is normal of type fgVector3f)
    offset = 0;
    pointer = (uintptr_t)((unsigned int*)&uvs.front());
    // Texture coordinates
    index = FG_GFX_ATTRIB_UVS_LOCATION;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[TEX_COORDS_VBO_ARRAY_IDX].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Colors = there are no colors, this attribute will be disabled
    pDataArray[FG_GFX_ATTRIB_COLOR_LOCATION] = SAttributeData(ATTRIBUTE_COLOR);
    pDataArray[FG_GFX_ATTRIB_COLOR_LOCATION].isInterleaved = FG_FALSE;

    // Tangents - this attribute will be disabled
    pDataArray[FG_GFX_ATTRIB_TANGENT_LOCATION] = SAttributeData(ATTRIBUTE_TANGENT);
    pDataArray[FG_GFX_ATTRIB_TANGENT_LOCATION].isInterleaved = FG_FALSE;

    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SMeshSoA::setupAttributes(SAttributeData *pDataArray) const {
    if(!pDataArray)
        return FG_GFX_FALSE;
    // 3V - pos + norm + uv
    fgGFXint index = 0;
    // If VBO is used, offset is 0 because it'll be separate VBO
    // Set pointer to front of vertices array (positions)
    uintptr_t offset = 0;
    uintptr_t pointer = (uintptr_t)((unsigned int *)&vertices.front());
    const fgBool b_hasVBO = hasVBO();
    // Position coordinates - activated
    index = FG_GFX_ATTRIB_POS_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 3;
    pDataArray[index].type = ATTRIBUTE_POSITION;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = sizeof (Vector3f);
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_FALSE; // SoA is not interleaved
    pDataArray[index].isNormalized = FG_FALSE;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[POSITIONS_VBO_ARRAY_IDX].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Set pointer to normals array
    // Offset is 0 because it is a separate VBO
    offset = 0;
    pointer = (uintptr_t)((unsigned int*)&normals.front());
    // Normals coords - activated
    index = FG_GFX_ATTRIB_NORM_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 3;
    pDataArray[index].type = ATTRIBUTE_NORMAL;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = sizeof (Vector3f);
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_FALSE; // SoA is not interleaved
    pDataArray[index].isNormalized = FG_FALSE;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[NORMALS_VBO_ARRAY_IDX].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to UVs (second is normal of type fgVector3f)
    offset = 0;
    pointer = (uintptr_t)((unsigned int*)&uvs.front());
    // Texture coordinates
    index = FG_GFX_ATTRIB_UVS_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 2;
    pDataArray[index].type = ATTRIBUTE_TEXTURE_COORD;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = sizeof (Vector2f);
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_FALSE; // SoA is not interleaved
    pDataArray[index].isNormalized = FG_FALSE;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[TEX_COORDS_VBO_ARRAY_IDX].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Colors = there are no colors, this attribute will be disabled
    pDataArray[FG_GFX_ATTRIB_COLOR_LOCATION] = SAttributeData(ATTRIBUTE_COLOR);
    pDataArray[FG_GFX_ATTRIB_COLOR_LOCATION].isInterleaved = FG_FALSE;

    // Tangents - this attribute will be disabled
    pDataArray[FG_GFX_ATTRIB_TANGENT_LOCATION] = SAttributeData(ATTRIBUTE_TANGENT);
    pDataArray[FG_GFX_ATTRIB_TANGENT_LOCATION].isInterleaved = FG_FALSE;

    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SMeshSoA::genBuffers(void) {
    if(!gfx::CPlatform::isInit())
        return FG_GFX_FALSE;
    int &count = getRefVBOCount();
    count = 4;

    FG_LOG_DEBUG("GFX: MESH SoA: generating %d buffers - static draw", count);
    context::genBuffers(count, getRefPtrVBO(), GL_STATIC_DRAW);

    context::bindBuffer(getRefPtrVBO()[POSITIONS_VBO_ARRAY_IDX],
                        GL_ARRAY_BUFFER);
    context::bufferData(getRefPtrVBO()[POSITIONS_VBO_ARRAY_IDX],
                        sizeof (fgGFXfloat) * vertices.size(),
                        (fgGFXvoid *)(&vertices.front()));
    FG_LOG_DEBUG("GFX: MESH SoA: buffer id[positions][%d], data[%p], size[%d]",
                 (int)getRefPtrVBO()[POSITIONS_VBO_ARRAY_IDX].id,
                 (fgGFXvoid *)(&vertices.front()), vertices.size());

    context::bindBuffer(getRefPtrVBO()[NORMALS_VBO_ARRAY_IDX],
                        GL_ARRAY_BUFFER);
    context::bufferData(getRefPtrVBO()[NORMALS_VBO_ARRAY_IDX],
                        sizeof (fgGFXfloat) * normals.size(),
                        (fgGFXvoid *)(&normals.front()));
    FG_LOG_DEBUG("GFX: MESH SoA: buffer id[normals][%d], data[%p], size[%d]",
                 (int)getRefPtrVBO()[NORMALS_VBO_ARRAY_IDX].id,
                 (fgGFXvoid *)(&normals.front()), normals.size());

    context::bindBuffer(getRefPtrVBO()[TEX_COORDS_VBO_ARRAY_IDX],
                        GL_ARRAY_BUFFER);
    context::bufferData(getRefPtrVBO()[TEX_COORDS_VBO_ARRAY_IDX],
                        sizeof (fgGFXfloat) * uvs.size(),
                        (fgGFXvoid *)(&uvs.front()));
    FG_LOG_DEBUG("GFX: MESH SoA: buffer id[uvs][%d], data[%p], size[%d]",
                 (int)getRefPtrVBO()[TEX_COORDS_VBO_ARRAY_IDX].id,
                 (fgGFXvoid *)(&uvs.front()), uvs.size());

    context::bindBuffer(getRefPtrVBO()[INDICES_VBO_ARRAY_IDX],
                        GL_ELEMENT_ARRAY_BUFFER);
    context::bufferData(getRefPtrVBO()[INDICES_VBO_ARRAY_IDX],
                        sizeof (fgGFXushort) * indices.size(),
                        (fgGFXvoid *)(&indices.front()));
    FG_LOG_DEBUG("GFX: MESH SoA: buffer id[indices][%d], data[%p], size[%d], size(B)[%d]",
                 (int)getRefPtrVBO()[INDICES_VBO_ARRAY_IDX].id, (fgGFXvoid *)(&indices.front()),
                 indices.size(), sizeof (fgGFXushort) * indices.size());

    return FG_GFX_TRUE;

}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SMeshSoA::deleteBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    FG_LOG_DEBUG("GFX: MESH SoA: removing %d buffers [%p]", getVBOCount(), getPtrVBO());
    context::deleteBuffers(getVBOCount(), getPtrVBO());
    return FG_GFX_TRUE;

}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SMeshSoA::destroyBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    gfx::context::deleteBuffers(getVBOCount(), getPtrVBO());
    SBufferID *& refBuf = getRefPtrVBO();
    fgFree<SBufferID>(refBuf);
    refBuf = NULL;
    int& count = getRefVBOCount();
    count = 0;
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

void gfx::SMeshSoA::translate(const Vector3f& diff) {
    const unsigned int n = this->vertices.size();
    const unsigned int count = n / 3;
    for(unsigned int i = 0; i < count; i++) {
        this->vertices[i * 3 + 0] += diff.x;
        this->vertices[i * 3 + 1] += diff.y;
        this->vertices[i * 3 + 2] += diff.z;
    }
}
//------------------------------------------------------------------------------

/******************************************************************************
 * MESH AOS FUNCTION - ARRAY OF STRUCTURES
 ******************************************************************************/

const unsigned short gfx::SMeshAoS::POSITIONS_VBO_ARRAY_IDX = 0;
const unsigned short gfx::SMeshAoS::VERTICES_VBO_ARRAY_IDX = 0;
const unsigned short gfx::SMeshAoS::NORMALS_VBO_ARRAY_IDX = 0;
const unsigned short gfx::SMeshAoS::TEX_COORDS_VBO_ARRAY_IDX = 0;
const unsigned short gfx::SMeshAoS::UVS_VBO_ARRAY_IDX = 0;
const unsigned short gfx::SMeshAoS::INDICES_VBO_ARRAY_IDX = 1;

//------------------------------------------------------------------------------

gfx::SMeshAoS::SMeshAoS() :
base_type(),
vertices(NULL),
indices() {
    //vertices.reserve(4);
    convertVertexData(VERTEX_3);
    indices.reserve(4);
}

gfx::SMeshAoS::SMeshAoS(VertexType vertexType) :
base_type(),
vertices(NULL),
indices() {
    convertVertexData(vertexType);
    indices.reserve(4);
}
//------------------------------------------------------------------------------

gfx::SMeshAoS::SMeshAoS(AttributeMask attribMask) :
base_type(),
vertices(NULL),
indices() {
    convertVertexData(attribMask);
    indices.reserve(4);
}
//------------------------------------------------------------------------------

gfx::SMeshAoS::~SMeshAoS() {
    destroyBuffers();
    clear();
    if(vertices)
        delete vertices;
    vertices = NULL;
}
//------------------------------------------------------------------------------

fgBool gfx::SMeshAoS::convertVertexData(AttributeMask attribMask) {
    CVertexData* pNewVertexData = NULL;

    if(this->attribMask() == attribMask)
        return FG_TRUE;

    if(attribMask == Vertex5HQv::attribMask() || (attribMask & ATTRIBUTE_BITANGENT_BIT)
       || (attribMask & ATTRIBUTE_TANGENT_BIT)) {
        pNewVertexData = new CVertexData5HQv();
    } else if(attribMask == Vertex4v::attribMask() || (attribMask & ATTRIBUTE_COLOR_BIT)) {
        pNewVertexData = new CVertexData4v();
    } else if(attribMask == Vertex3v::attribMask() || (attribMask & ATTRIBUTE_NORMAL_BIT)) {
        pNewVertexData = new CVertexData3v();
    } else {
        pNewVertexData = new CVertexData2v();
    }

    if(pNewVertexData && this->vertices) {
        delete this->vertices;
        this->vertices = NULL;
    }
    // #TODO - copy data procedures
    if(pNewVertexData) {
        this->vertices = pNewVertexData;
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::SMeshAoS::convertVertexData(VertexType vertexType) {
    if(vertexType == VERTEX_INVALID)
        return FG_FALSE;
    if(this->getVertexType() == vertexType)
        return FG_TRUE;
    CVertexData* pNewVertexData = NULL;
    if(vertexType == VERTEX_5_HQ) {
        pNewVertexData = new CVertexData5HQv();
    } else if(vertexType == VERTEX_4) {
        pNewVertexData = new CVertexData4v();
    } else if(vertexType == VERTEX_3) {
        pNewVertexData = new CVertexData3v();
    } else if(vertexType == VERTEX_2) {
        pNewVertexData = new CVertexData2v();
    }
    if(pNewVertexData && this->vertices) {
        delete this->vertices;
        this->vertices = NULL;
    }
    // #TODO - copy data procedures
    if(pNewVertexData) {
        this->vertices = pNewVertexData;
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

gfx::VertexType gfx::SMeshAoS::getVertexType(void) const {
    if(!this->vertices)
        return VertexType::VERTEX_INVALID;
    VertexType result = VertexType::VERTEX_INVALID;
    unsigned int attribMask = this->vertices->attribMask();
    if(attribMask == Vertex5HQv::attribMask()) {
        result = VERTEX_5_HQ; // pos, norm, uv, tangent, bitangent
    } else if(attribMask == Vertex4v::attribMask()) {
        result = VERTEX_4; // pos, norm, uv, color
    } else if(attribMask == Vertex3v::attribMask()) {
        result = VERTEX_3; // pos, norm, uv
    } else if(attribMask == Vertex2v::attribMask()) {
        result = VERTEX_2; // pos, uv
    }
    return result;
}
//------------------------------------------------------------------------------

void gfx::SMeshAoS::fixCenter(fgBool saveDisplacement) {    
    if(!this->vertices || this->vertices->empty())
        return;
    const Vector3f center = this->aabb.getCenter();
    this->vertices->translate(-center);
    if(saveDisplacement) {
        this->displacement += center;
    }
    this->aabb.min -= center;
    this->aabb.max -= center;
}
//------------------------------------------------------------------------------

fgGFXuint gfx::SMeshAoS::getIndicesVBO(void) const {
    if(!hasVBO())
        return 0;
    return getPtrVBO()[INDICES_VBO_ARRAY_IDX].id;
}
//------------------------------------------------------------------------------

fgGFXvoid *gfx::SMeshAoS::getIndicesPointer(void) const {
    if(!hasVBO())
        return (fgGFXvoid *)((unsigned int*)&indices.front());
    return (fgGFXvoid *)0;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SMeshAoS::genBuffers(void) {
    if(!gfx::CPlatform::isInit())
        return FG_GFX_FALSE;
    int &count = getRefVBOCount();
    count = 2;
    if(getNumIndices() < 1)
        count = 1;
    FG_LOG_DEBUG("GFX: MESH AoS: generating %d buffers - static draw", count);
    context::genBuffers(count, getRefPtrVBO(), GL_STATIC_DRAW);
    context::bindBuffer(getRefPtrVBO()[VERTICES_VBO_ARRAY_IDX],
                        GL_ARRAY_BUFFER);

    context::bufferData(getRefPtrVBO()[VERTICES_VBO_ARRAY_IDX],
                        this->stride() * this->size(),
                        SMeshAoS::front());
    if(count == 2) {
        context::bindBuffer(getRefPtrVBO()[INDICES_VBO_ARRAY_IDX],
                            GL_ELEMENT_ARRAY_BUFFER);

        context::bufferData(getRefPtrVBO()[INDICES_VBO_ARRAY_IDX],
                            sizeof (fgGFXushort) * indices.size(),
                            (fgGFXvoid *)(&indices.front()));
    }
    //FG_LOG_DEBUG("GFX: MESH: binding buffer id: %d", (int)getRefPtrVBO()[VERTICES_VBO_ARRAY_IDX].id);
    FG_LOG_DEBUG("GFX: MESH AoS: buffer id[vertices][%d], data[%p], stride[%d], size[%d]",
                 (int)getRefPtrVBO()[VERTICES_VBO_ARRAY_IDX].id, front(), stride(), size());
    //FG_LOG_DEBUG("GFX: MESH: binding buffer id: %d", (int)getRefPtrVBO()[INDICES_VBO_ARRAY_IDX].id);
    if(count == 2) {
        FG_LOG_DEBUG("GFX: MESH AoS: buffer id[indices][%d], data[%p], size(B)[%d], size[%d]",
                     (int)getRefPtrVBO()[INDICES_VBO_ARRAY_IDX].id,
                     (fgGFXvoid *)(&indices.front()),
                     sizeof (fgGFXushort) * indices.size(),
                     indices.size());
    }
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SMeshAoS::deleteBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    FG_LOG_DEBUG("GFX: MESH AoS: removing %d buffers [%p]", getVBOCount(), getPtrVBO());
    context::deleteBuffers(getVBOCount(), getPtrVBO());
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::SMeshAoS::destroyBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    gfx::context::deleteBuffers(getVBOCount(), getPtrVBO());
    SBufferID *& refBuf = getRefPtrVBO();
    fgFree<SBufferID>(refBuf);
    refBuf = NULL;
    int& count = getRefVBOCount();
    count = 0;
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------
