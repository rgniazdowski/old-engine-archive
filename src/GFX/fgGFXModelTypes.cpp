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
            sizeof(fgGFXfloat)*vertices.size(), 
            (fgGFXvoid *)(&vertices.front()));
    
    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[1], GL_ARRAY_BUFFER);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[1], 
            sizeof(fgGFXfloat)*normals.size(), 
            (fgGFXvoid *)(&normals.front()));
    
    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[2], GL_ARRAY_BUFFER);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[2], 
            sizeof(fgGFXfloat)*uvs.size(), 
            (fgGFXvoid *)(&uvs.front()));
    
    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[3], GL_ELEMENT_ARRAY_BUFFER);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[3], 
            sizeof(fgGFXushort)*indices.size(), 
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
            this->stride()*this->size(), 
            fgGfxMeshAoS::front());
    FG_LOG::PrintDebug("GFX: MESH: buffer id: %d, data: %p, stride: %d, size: %d", 
                       (int)getRefPtrVBO()[0].id, front(), stride(), size());

    
    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[1], GL_ELEMENT_ARRAY_BUFFER);
    FG_LOG::PrintDebug("GFX: MESH: binding buffer id: %d", (int)getRefPtrVBO()[1].id);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[1], 
            sizeof(fgGFXushort)*indices.size(),
            (fgGFXvoid *)(&indices.front()));
    FG_LOG::PrintDebug("GFX: MESH: buffer id: %d, data: %p, size(B): %d, size: %d", 
                       (int)getRefPtrVBO()[1].id, 
                               (fgGFXvoid *)(&indices.front()), 
                               sizeof(fgGFXushort)*indices.size(),
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