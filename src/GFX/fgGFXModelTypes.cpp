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

/**
 * 
 * @param pDataArray
 * @return 
 */
fgGFXboolean fgGfxMeshSoA::setupAttributes(fgGfxAttributeData *pDataArray)
{
    if(!pDataArray)
        return FG_GFX_FALSE;
    // 3V - pos + norm + uv
    fgGFXint index = 0;
    // If VBOs are not set this will act as data address
    uintptr_t pointer = 0;
    uintptr_t offset = 0;
    // Position coordinates
    index = FG_GFX_ATTRIB_POS_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 3;
    pDataArray[index].type = FG_GFX_POSITION;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = sizeof(fgVector3f);
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getRefPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }
    
    // Move offset to normals (first is position of type fgVector3f)
    offset = 0;
    pointer = (uintptr_t)((unsigned int*)&normals.front());
    // Normals coords - activated
    index = FG_GFX_ATTRIB_NORM_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 3;
    pDataArray[index].type = FG_GFX_NORMAL;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = sizeof(fgVector3f);
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getRefPtrVBO()[1].id;
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
    pDataArray[index].stride = sizeof(fgVector2f);
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;    
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getRefPtrVBO()[2].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }
    
    // Colors = there are no colors, this attribute will be disabled
    pDataArray[FG_GFX_ATTRIB_COLOR_LOCATION] = fgGfxAttributeData(FG_GFX_COLOR);
    
    // Tangents - this attribute will be disabled
    pDataArray[FG_GFX_ATTRIB_TANGENT_LOCATION] = fgGfxAttributeData(FG_GFX_TANGENT);
    
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
    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[0], GL_ARRAY_BUFFER);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[0],
                                         sizeof (fgGFXfloat) * vertices.size(),
                                         (fgGFXvoid *)(&vertices.front()));

    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[1], GL_ARRAY_BUFFER);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[1],
                                         sizeof (fgGFXfloat) * normals.size(),
                                         (fgGFXvoid *)(&normals.front()));

    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[2], GL_ARRAY_BUFFER);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[2],
                                         sizeof (fgGFXfloat) * uvs.size(),
                                         (fgGFXvoid *)(&uvs.front()));

    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[3], GL_ELEMENT_ARRAY_BUFFER);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[3],
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

/**
 * 
 * @return 
 */
fgGFXboolean fgGfxMeshAoS::genBuffers(void) {
    if(!fgGfxPlatform::isInit())
        return FG_GFX_FALSE;
    int &count = getRefVBOCount();
    count = 2;
    fgGfxPlatform::context()->genBuffers(count, getRefPtrVBO(), GL_STATIC_DRAW);
    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[0], GL_ARRAY_BUFFER);
    FG_LOG::PrintDebug("GFX: MESH: binding buffer id: %d", (int)getRefPtrVBO()[0].id);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[0],
                                         this->stride() * this->size(),
                                         fgGfxMeshAoS::front());
    FG_LOG::PrintDebug("GFX: MESH: buffer id: %d, data: %p, stride: %d, size: %d",
                       (int)getRefPtrVBO()[0].id, front(), stride(), size());


    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[1], GL_ELEMENT_ARRAY_BUFFER);
    FG_LOG::PrintDebug("GFX: MESH: binding buffer id: %d", (int)getRefPtrVBO()[1].id);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[1],
                                         sizeof (fgGFXushort) * indices.size(),
                                         (fgGFXvoid *)(&indices.front()));
    FG_LOG::PrintDebug("GFX: MESH: buffer id: %d, data: %p, size(B): %d, size: %d",
                       (int)getRefPtrVBO()[1].id,
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