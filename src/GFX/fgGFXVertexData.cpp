/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXVertexData.h"
#include "fgGFXPlatform.h"
#include "Util/fgMemory.h"

/**
 * 
 * @param pDataArray
 * @return 
 */
fgGFXboolean fgVertexData2v::refreshAttributes(fgGfxAttributeData *pDataArray) const {
    if(!pDataArray)
        return FG_GFX_FALSE;
    // 2V - pos + uv
    fgGFXint index = 0;
    // If VBOs are not set this will act as data address
    uintptr_t pointer = (uintptr_t)((unsigned int*)fgVertexData2v::front());
    uintptr_t offset = 0;
    // Position coordinates
    index = FG_GFX_ATTRIB_POS_LOCATION;
    pDataArray[index].index = index;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Normals - there are no normals, this attribute will be disabled
    pDataArray[FG_GFX_ATTRIB_NORM_LOCATION] = fgGfxAttributeData(FG_GFX_NORMAL);

    // Move offset to UVs (first is position of type fgVector3f)
    offset += sizeof (fgVector3f);
    pointer += sizeof (fgVector3f);
    // Texture coordinates
    index = FG_GFX_ATTRIB_UVS_LOCATION;
    pDataArray[index].index = index;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
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
 * @param pDataArray
 * @return 
 */
fgGFXboolean fgVertexData2v::setupAttributes(fgGfxAttributeData *pDataArray) const {
    if(!pDataArray)
        return FG_GFX_FALSE;
    // 2V - pos + uv
    fgGFXint index = 0;
    // If VBOs are not set this will act as data address
    uintptr_t pointer = (uintptr_t)((unsigned int*)fgVertexData2v::front());
    uintptr_t offset = 0;
    // Position coordinates
    index = FG_GFX_ATTRIB_POS_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 3;
    pDataArray[index].type = FG_GFX_POSITION;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Normals - there are no normals, this attribute will be disabled
    pDataArray[FG_GFX_ATTRIB_NORM_LOCATION] = fgGfxAttributeData(FG_GFX_NORMAL);

    // Move offset to UVs (first is position of type fgVector3f)
    offset += sizeof (fgVector3f);
    pointer += sizeof (fgVector3f);
    // Texture coordinates
    index = FG_GFX_ATTRIB_UVS_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 2;
    pDataArray[index].type = FG_GFX_TEXTURE_COORD;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
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
fgGFXboolean fgVertexData2v::genBuffers(void) {
    if(!fgGfxPlatform::isInit())
        return FG_GFX_FALSE;
    int &count = getRefVBOCount();
    count = 1;
    fgGfxPlatform::context()->genBuffers(count, getRefPtrVBO(), GL_STATIC_DRAW);
    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[0], GL_ARRAY_BUFFER);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[0], this->stride() * this->size(), fgVertexData2v::front());
    return FG_GFX_TRUE;
}

/**
 * 
 * @return 
 */
fgGFXboolean fgVertexData2v::deleteBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    fgGfxPlatform::context()->deleteBuffers(getVBOCount(), getPtrVBO());
    return FG_GFX_TRUE;

}

/**
 * 
 * @return 
 */
fgGFXboolean fgVertexData2v::destroyBuffers(void) {
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
 * @param pDataArray
 * @return 
 */
fgGFXboolean fgVertexData3v::refreshAttributes(fgGfxAttributeData *pDataArray) const {
    if(!pDataArray)
        return FG_GFX_FALSE;
    // 3V - pos + norm + uv
    fgGFXint index = 0;
    // If VBOs are not set this will act as data address
    uintptr_t pointer = (uintptr_t)((unsigned int*)fgVertexData3v::front());
    uintptr_t offset = 0;
    // Position coordinates
    index = FG_GFX_ATTRIB_POS_LOCATION;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to normals (first is position of type fgVector3f)
    offset += sizeof (fgVector3f);
    pointer += sizeof (fgVector3f);
    // Normals coords - activated
    index = FG_GFX_ATTRIB_NORM_LOCATION;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to UVs (second is normal of type fgVector3f)
    offset += sizeof (fgVector3f);
    pointer += sizeof (fgVector3f);
    // Texture coordinates
    index = FG_GFX_ATTRIB_UVS_LOCATION;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
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
 * @param pDataArray
 * @return 
 */
fgGFXboolean fgVertexData3v::setupAttributes(fgGfxAttributeData *pDataArray) const {
    if(!pDataArray)
        return FG_GFX_FALSE;
    // 3V - pos + norm + uv
    fgGFXint index = 0;
    // If VBOs are not set this will act as data address
    uintptr_t pointer = (uintptr_t)((unsigned int*)fgVertexData3v::front());
    uintptr_t offset = 0;
    // Position coordinates
    index = FG_GFX_ATTRIB_POS_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 3;
    pDataArray[index].type = FG_GFX_POSITION;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to normals (first is position of type fgVector3f)
    offset += sizeof (fgVector3f);
    pointer += sizeof (fgVector3f);
    // Normals coords - activated
    index = FG_GFX_ATTRIB_NORM_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 3;
    pDataArray[index].type = FG_GFX_NORMAL;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to UVs (second is normal of type fgVector3f)
    offset += sizeof (fgVector3f);
    pointer += sizeof (fgVector3f);
    // Texture coordinates
    index = FG_GFX_ATTRIB_UVS_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 2;
    pDataArray[index].type = FG_GFX_TEXTURE_COORD;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
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
fgGFXboolean fgVertexData3v::genBuffers(void) {
    if(!fgGfxPlatform::isInit())
        return FG_GFX_FALSE;
    int &count = getRefVBOCount();
    count = 1;
    fgGfxPlatform::context()->genBuffers(count, getRefPtrVBO(), GL_STATIC_DRAW);
    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[0], GL_ARRAY_BUFFER);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[0], this->stride() * this->size(), fgVertexData3v::front());
    return FG_GFX_TRUE;
}

/**
 * 
 * @return 
 */
fgGFXboolean fgVertexData3v::deleteBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    fgGfxPlatform::context()->deleteBuffers(getVBOCount(), getPtrVBO());
    return FG_GFX_TRUE;
}

/**
 * 
 * @return 
 */
fgGFXboolean fgVertexData3v::destroyBuffers(void) {
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
 * @param pDataArray
 * @return 
 */
fgGFXboolean fgVertexData4v::refreshAttributes(fgGfxAttributeData *pDataArray) const {
    if(!pDataArray)
        return FG_GFX_FALSE;
    
    // 3V - pos + norm + uv + color
    fgGFXint index = 0;
    // If VBOs are not set this will act as data address
    uintptr_t pointer = (uintptr_t)((unsigned int*)fgVertexData4v::front());
    uintptr_t offset = 0;
    // Position coordinates - always present (at least at the moment)
    index = FG_GFX_ATTRIB_POS_LOCATION;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to normals (first is position of type fgVector3f)
    offset += sizeof (fgVector3f);
    pointer += sizeof (fgVector3f);
    // Normals coords - activated
    index = FG_GFX_ATTRIB_NORM_LOCATION;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to UVs (second is normal of type fgVector3f)
    offset += sizeof (fgVector3f);
    pointer += sizeof (fgVector3f);
    // Texture coordinates
    index = FG_GFX_ATTRIB_UVS_LOCATION;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to Colors (last one was uv of type fgVector2f)
    offset += sizeof (fgVector2f); // 2UVs
    pointer += sizeof (fgVector2f);

    // Colors = there are no colors, this attribute will be disabled
    index = FG_GFX_ATTRIB_COLOR_LOCATION;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Tangents - this attribute will be disabled - not yet supported
    pDataArray[FG_GFX_ATTRIB_TANGENT_LOCATION] = fgGfxAttributeData(FG_GFX_TANGENT);
    
    return FG_GFX_TRUE;
}

/**
 * 
 * @param pDataArray
 * @return 
 */
fgGFXboolean fgVertexData4v::setupAttributes(fgGfxAttributeData *pDataArray) const {
    if(!pDataArray)
        return FG_GFX_FALSE;
    // 3V - pos + norm + uv + color
    fgGFXint index = 0;
    // If VBOs are not set this will act as data address
    uintptr_t pointer = (uintptr_t)((unsigned int*)fgVertexData4v::front());
    uintptr_t offset = 0;
    // Position coordinates - always present (at least at the moment)
    index = FG_GFX_ATTRIB_POS_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 3;
    pDataArray[index].type = FG_GFX_POSITION;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to normals (first is position of type fgVector3f)
    offset += sizeof (fgVector3f);
    pointer += sizeof (fgVector3f);
    // Normals coords - activated
    index = FG_GFX_ATTRIB_NORM_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 3;
    pDataArray[index].type = FG_GFX_NORMAL;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to UVs (second is normal of type fgVector3f)
    offset += sizeof (fgVector3f);
    pointer += sizeof (fgVector3f);
    // Texture coordinates
    index = FG_GFX_ATTRIB_UVS_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 2;
    pDataArray[index].type = FG_GFX_TEXTURE_COORD;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to Colors (last one was uv of type fgVector2f)
    offset += sizeof (fgVector2f); // 2UVs
    pointer += sizeof (fgVector2f);

    // Colors = there are no colors, this attribute will be disabled
    index = FG_GFX_ATTRIB_COLOR_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 4;
    pDataArray[index].type = FG_GFX_COLOR;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(getPtrVBO() && getVBOCount()) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Tangents - this attribute will be disabled - not yet supported
    pDataArray[FG_GFX_ATTRIB_TANGENT_LOCATION] = fgGfxAttributeData(FG_GFX_TANGENT);

    return FG_GFX_TRUE;
}

/**
 * 
 * @return 
 */
fgGFXboolean fgVertexData4v::genBuffers(void) {
    if(!fgGfxPlatform::isInit())
        return FG_GFX_FALSE;
    int &count = getRefVBOCount();
    count = 1;
    fgGfxPlatform::context()->genBuffers(count, getRefPtrVBO(), GL_STATIC_DRAW);
    fgGfxPlatform::context()->bindBuffer(getRefPtrVBO()[0], GL_ARRAY_BUFFER);
    fgGfxPlatform::context()->bufferData(getRefPtrVBO()[0], this->stride() * this->size(), fgVertexData4v::front());
    return FG_GFX_TRUE;
}

/**
 * 
 * @return 
 */
fgGFXboolean fgVertexData4v::deleteBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    fgGfxPlatform::context()->deleteBuffers(getVBOCount(), getPtrVBO());
    return FG_GFX_TRUE;
}

/**
 * 
 * @return 
 */
fgGFXboolean fgVertexData4v::destroyBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    fgGfxPlatform::context()->deleteBuffers(getVBOCount(), getPtrVBO());
    fgGfxBufferID *& refBuf = getRefPtrVBO();
    fgFree<fgGfxBufferID>(refBuf);
    refBuf = NULL;
    return FG_GFX_TRUE;
}
