/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXModelTypes.h"
#include "fgGFXPlatform.h"
#include "Util/fgMemory.h"

const unsigned short fgGfxMeshSoA::POSITIONS_VBO_ARRAY_IDX = 0;
const unsigned short fgGfxMeshSoA::VERTICES_VBO_ARRAY_IDX = 0;
const unsigned short fgGfxMeshSoA::NORMALS_VBO_ARRAY_IDX = 1;
const unsigned short fgGfxMeshSoA::TEX_COORDS_VBO_ARRAY_IDX = 2;
const unsigned short fgGfxMeshSoA::UVS_VBO_ARRAY_IDX = 2;
const unsigned short fgGfxMeshSoA::INDICES_VBO_ARRAY_IDX = 3;

/******************************************************************************
 * MESH SOA FUNCTIONS - STRUCTURE OF ARRAYS
 ******************************************************************************/

/**
 * Get the indices VBO ID
 * @return  GFX id for indices VBO or 0 if not generated or invalid
 */
fgGFXuint fgGfxMeshSoA::getIndicesVBO(void) const {
    if(!hasVBO())
        return 0;
    return getPtrVBO()[INDICES_VBO_ARRAY_IDX].id;
}

/**
 * Get the special GFX pointer to indices array
 * @return  Pointer to indices array. May be 0 (NULL) if VBO is
 *          generated (offset) or there are no indices at all
 */
fgGFXvoid *fgGfxMeshSoA::getIndicesPointer(void) const {
    if(!hasVBO())
        return (fgGFXvoid *)((unsigned int*)&indices.front());
    return (fgGFXvoid *)0;
}

/**
 * 
 * @param pDataArray
 * @return 
 */
fgGFXboolean fgGfxMeshSoA::setupAttributes(fgGfxAttributeData *pDataArray) const {
    if(!pDataArray)
        return FG_GFX_FALSE;
    // 3V - pos + norm + uv
    fgGFXint index = 0;
    // If VBO is used, offset is 0 because it'll be separate VBO
    // Set pointer to front of vertices array (positions)
    uintptr_t offset = 0;
    uintptr_t pointer = (uintptr_t)((unsigned int *)&vertices.front());
    // Position coordinates - activated
    index = FG_GFX_ATTRIB_POS_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 3;
    pDataArray[index].type = FG_GFX_POSITION;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = sizeof (fgVector3f);
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_FALSE; // SoA is not interleaved
    pDataArray[index].isNormalized = FG_FALSE;
    if(getPtrVBO() && getVBOCount()) {
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
    pDataArray[index].type = FG_GFX_NORMAL;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = sizeof (fgVector3f);
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_FALSE; // SoA is not interleaved
    pDataArray[index].isNormalized = FG_FALSE;
    if(getPtrVBO() && getVBOCount()) {
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
    pDataArray[index].type = FG_GFX_TEXTURE_COORD;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = sizeof (fgVector2f);
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_FALSE; // SoA is not interleaved
    pDataArray[index].isNormalized = FG_FALSE;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[TEX_COORDS_VBO_ARRAY_IDX].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Colors = there are no colors, this attribute will be disabled
    pDataArray[FG_GFX_ATTRIB_COLOR_LOCATION] = fgGfxAttributeData(FG_GFX_COLOR);
    pDataArray[FG_GFX_ATTRIB_COLOR_LOCATION].isInterleaved = FG_FALSE;

    // Tangents - this attribute will be disabled
    pDataArray[FG_GFX_ATTRIB_TANGENT_LOCATION] = fgGfxAttributeData(FG_GFX_TANGENT);
    pDataArray[FG_GFX_ATTRIB_TANGENT_LOCATION].isInterleaved = FG_FALSE;

    return FG_GFX_TRUE;
}

/**
 * 
 * @return 
 */
fgGFXboolean fgGfxMeshSoA::genBuffers(void) {
    if(!fgGfxPlatform::isInit())
        return FG_GFX_FALSE;
    int &count = getRefVBOCount();
    count = 4;
    fgGfxPlatform::context()->genBuffers(count, getRefPtrVBO(), GL_STATIC_DRAW);
    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[POSITIONS_VBO_ARRAY_IDX],
                                         GL_ARRAY_BUFFER);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[POSITIONS_VBO_ARRAY_IDX],
                                         sizeof (fgGFXfloat) * vertices.size(),
                                         (fgGFXvoid *)(&vertices.front()));

    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[NORMALS_VBO_ARRAY_IDX],
                                         GL_ARRAY_BUFFER);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[NORMALS_VBO_ARRAY_IDX],
                                         sizeof (fgGFXfloat) * normals.size(),
                                         (fgGFXvoid *)(&normals.front()));

    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[TEX_COORDS_VBO_ARRAY_IDX],
                                         GL_ARRAY_BUFFER);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[TEX_COORDS_VBO_ARRAY_IDX],
                                         sizeof (fgGFXfloat) * uvs.size(),
                                         (fgGFXvoid *)(&uvs.front()));

    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[INDICES_VBO_ARRAY_IDX],
                                         GL_ELEMENT_ARRAY_BUFFER);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[INDICES_VBO_ARRAY_IDX],
                                         sizeof (fgGFXushort) * indices.size(),
                                         (fgGFXvoid *)(&indices.front()));
    return FG_GFX_TRUE;

}

/**
 * 
 * @return 
 */
fgGFXboolean fgGfxMeshSoA::deleteBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    fgGfxPlatform::context()->deleteBuffers(getVBOCount(), getPtrVBO());
    return FG_GFX_TRUE;

}

/**
 * 
 * @return 
 */
fgGFXboolean fgGfxMeshSoA::destroyBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    fgGfxPlatform::context()->deleteBuffers(getVBOCount(), getPtrVBO());
    fgGfxBufferID *& refBuf = getRefPtrVBO();
    fgFree<fgGfxBufferID>(refBuf);
    refBuf = NULL;
    return FG_GFX_TRUE;
}

/******************************************************************************
 * MESH AOS FUNCTION - ARRAY OF STRUCTURES
 ******************************************************************************/

const unsigned short fgGfxMeshAoS::POSITIONS_VBO_ARRAY_IDX = 0;
const unsigned short fgGfxMeshAoS::VERTICES_VBO_ARRAY_IDX = 0;
const unsigned short fgGfxMeshAoS::NORMALS_VBO_ARRAY_IDX = 0;
const unsigned short fgGfxMeshAoS::TEX_COORDS_VBO_ARRAY_IDX = 0;
const unsigned short fgGfxMeshAoS::UVS_VBO_ARRAY_IDX = 0;
const unsigned short fgGfxMeshAoS::INDICES_VBO_ARRAY_IDX = 1;

/**
 * Get the indices VBO ID
 * @return  GFX id for indices VBO or 0 if not generated or invalid
 */
fgGFXuint fgGfxMeshAoS::getIndicesVBO(void) const {
    if(!hasVBO())
        return 0;
    return getPtrVBO()[INDICES_VBO_ARRAY_IDX].id;
}

/**
 * Get the special GFX pointer to indices array
 * @return  Pointer to indices array. May be 0 (NULL) if VBO is
 *          generated (offset) or there are no indices at all
 */
fgGFXvoid *fgGfxMeshAoS::getIndicesPointer(void) const {
    if(!hasVBO())
        return (fgGFXvoid *)((unsigned int*)&indices.front());
    return (fgGFXvoid *)0;
}

/**
 * 
 * @return  GFX_TRUE if buffers (VBO) were generated successfully
 */
fgGFXboolean fgGfxMeshAoS::genBuffers(void) {
    if(!fgGfxPlatform::isInit())
        return FG_GFX_FALSE;
    int &count = getRefVBOCount();
    count = 2;
    fgGfxPlatform::context()->genBuffers(count, getRefPtrVBO(), GL_STATIC_DRAW);
    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[VERTICES_VBO_ARRAY_IDX],
                                         GL_ARRAY_BUFFER);

    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[VERTICES_VBO_ARRAY_IDX],
                                         this->stride() * this->size(),
                                         fgGfxMeshAoS::front());

    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[INDICES_VBO_ARRAY_IDX],
                                         GL_ELEMENT_ARRAY_BUFFER);

    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[INDICES_VBO_ARRAY_IDX],
                                         sizeof (fgGFXushort) * indices.size(),
                                         (fgGFXvoid *)(&indices.front()));

    FG_LOG::PrintDebug("GFX: MESH: binding buffer id: %d", (int)getRefPtrVBO()[VERTICES_VBO_ARRAY_IDX].id);
    FG_LOG::PrintDebug("GFX: MESH: buffer id: %d, data: %p, stride: %d, size: %d",
                       (int)getRefPtrVBO()[VERTICES_VBO_ARRAY_IDX].id, front(), stride(), size());
    FG_LOG::PrintDebug("GFX: MESH: binding buffer id: %d", (int)getRefPtrVBO()[INDICES_VBO_ARRAY_IDX].id);
    FG_LOG::PrintDebug("GFX: MESH: buffer id: %d, data: %p, size(B): %d, size: %d",
                       (int)getRefPtrVBO()[INDICES_VBO_ARRAY_IDX].id,
                       (fgGFXvoid *)(&indices.front()),
                       sizeof (fgGFXushort) * indices.size(),
                       indices.size());

    return FG_GFX_TRUE;

}

/**
 * 
 * @return 
 */
fgGFXboolean fgGfxMeshAoS::deleteBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    fgGfxPlatform::context()->deleteBuffers(getVBOCount(), getPtrVBO());
    return FG_GFX_TRUE;

}

/**
 * 
 * @return 
 */
fgGFXboolean fgGfxMeshAoS::destroyBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    fgGfxPlatform::context()->deleteBuffers(getVBOCount(), getPtrVBO());
    fgGfxBufferID *& refBuf = getRefPtrVBO();
    fgFree<fgGfxBufferID>(refBuf);
    refBuf = NULL;
    return FG_GFX_TRUE;
}