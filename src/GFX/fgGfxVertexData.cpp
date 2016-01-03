/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGfxVertexData.h"
#include "fgGfxContext.h"
#include "Util/fgMemory.h"

using namespace fg;

//------------------------------------------------------------------------------
// CVERTEXDATA2V - VERTEX2V
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData2v::refreshAttributes(SAttributeData *pDataArray) const {
    if(!pDataArray)
        return FG_GFX_FALSE;
    // 2V - pos + uv
    fgGFXint index = 0;
    // If VBOs are not set this will act as data address
    uintptr_t pointer = (uintptr_t)((unsigned int*)self_type::front());
    uintptr_t offset = 0;
    const fgBool b_hasVBO = hasVBO();
    // Position coordinates
    index = ATTRIBUTE_POSITION_LOCATION;
    pDataArray[index].index = index;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Normals - there are no normals, this attribute will be disabled
    pDataArray[ATTRIBUTE_NORMAL_LOCATION] = SAttributeData(ATTRIBUTE_NORMAL);

    // Move offset to UVs (first is position of type fgVector3f)
    offset += sizeof (Vector3f);
    pointer += sizeof (Vector3f);
    // Texture coordinates
    index = ATTRIBUTE_TEXTURE_COORD_LOCATION;
    pDataArray[index].index = index;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Colors = there are no colors, this attribute will be disabled
    pDataArray[ATTRIBUTE_COLOR_LOCATION] = SAttributeData(ATTRIBUTE_COLOR);

    // Tangents - this attribute will be disabled
    pDataArray[ATTRIBUTE_TANGENT_LOCATION] = SAttributeData(ATTRIBUTE_TANGENT);

    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData2v::setupAttributes(SAttributeData *pDataArray) const {
    if(!pDataArray)
        return FG_GFX_FALSE;
    // 2V - pos + uv
    fgGFXint index = 0;
    // If VBOs are not set this will act as data address
    uintptr_t pointer = (uintptr_t)((unsigned int*)self_type::front());
    uintptr_t offset = 0;
    const fgBool b_hasVBO = hasVBO();
    // Position coordinates
    index = ATTRIBUTE_POSITION_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 3;
    pDataArray[index].type = ATTRIBUTE_POSITION;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Normals - there are no normals, this attribute will be disabled
    pDataArray[ATTRIBUTE_NORMAL_LOCATION] = SAttributeData(ATTRIBUTE_NORMAL);

    // Move offset to UVs (first is position of type fgVector3f)
    offset += sizeof (Vector3f);
    pointer += sizeof (Vector3f);
    // Texture coordinates
    index = ATTRIBUTE_TEXTURE_COORD_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 2;
    pDataArray[index].type = ATTRIBUTE_TEXTURE_COORD;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Colors = there are no colors, this attribute will be disabled
    pDataArray[ATTRIBUTE_COLOR_LOCATION] = SAttributeData(ATTRIBUTE_COLOR);

    // Tangents - this attribute will be disabled
    pDataArray[ATTRIBUTE_TANGENT_LOCATION] = SAttributeData(ATTRIBUTE_TANGENT);

    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData2v::genBuffers(void) {
    if(!gfx::context::isInit())
        return FG_GFX_FALSE;
    int &count = getRefVBOCount();
    count = 1;
    context::genBuffers(count, getRefPtrVBO(), GL_STATIC_DRAW);
    context::bindBuffer(getRefPtrVBO()[0], GL_ARRAY_BUFFER);
    context::bufferData(getRefPtrVBO()[0],
            this->stride() * this->size(),
            self_type::front());
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData2v::deleteBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    context::deleteBuffers(getVBOCount(), getPtrVBO());
    return FG_GFX_TRUE;

}
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData2v::destroyBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    context::deleteBuffers(getVBOCount(), getPtrVBO());
    SBufferID *& refBuf = getRefPtrVBO();
    fgFree<SBufferID>(refBuf);
    refBuf = NULL;
    int& count = getRefVBOCount();
    count = 0;
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------
// CVERTEXDATA3V - VERTEX3V
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData3v::refreshAttributes(SAttributeData *pDataArray) const {
    if(!pDataArray)
        return FG_GFX_FALSE;
    // 3V - pos + norm + uv
    fgGFXint index = 0;
    // If VBOs are not set this will act as data address
    uintptr_t pointer = (uintptr_t)((unsigned int*)self_type::front());
    uintptr_t offset = 0;
    const fgBool b_hasVBO = hasVBO();
    // Position coordinates
    index = ATTRIBUTE_POSITION_LOCATION;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to normals (first is position of type fgVector3f)
    offset += sizeof (Vector3f);
    pointer += sizeof (Vector3f);
    // Normals coords - activated
    index = ATTRIBUTE_NORMAL_LOCATION;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to UVs (second is normal of type fgVector3f)
    offset += sizeof (Vector3f);
    pointer += sizeof (Vector3f);
    // Texture coordinates
    index = ATTRIBUTE_TEXTURE_COORD_LOCATION;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;

    }

    // Colors = there are no colors, this attribute will be disabled
    pDataArray[ATTRIBUTE_COLOR_LOCATION] = SAttributeData(ATTRIBUTE_COLOR);

    // Tangents - this attribute will be disabled
    pDataArray[ATTRIBUTE_TANGENT_LOCATION] = SAttributeData(ATTRIBUTE_TANGENT);

    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData3v::setupAttributes(SAttributeData *pDataArray) const {
    if(!pDataArray)
        return FG_GFX_FALSE;
    // 3V - pos + norm + uv
    fgGFXint index = 0;
    // If VBOs are not set this will act as data address
    uintptr_t pointer = (uintptr_t)((unsigned int*)self_type::front());
    uintptr_t offset = 0;
    const fgBool b_hasVBO = hasVBO();
    // Position coordinates
    index = ATTRIBUTE_POSITION_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 3;
    pDataArray[index].type = ATTRIBUTE_POSITION;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to normals (first is position of type fgVector3f)
    offset += sizeof (Vector3f);
    pointer += sizeof (Vector3f);
    // Normals coords - activated
    index = ATTRIBUTE_NORMAL_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 3;
    pDataArray[index].type = ATTRIBUTE_NORMAL;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to UVs (second is normal of type fgVector3f)
    offset += sizeof (Vector3f);
    pointer += sizeof (Vector3f);
    // Texture coordinates
    index = ATTRIBUTE_TEXTURE_COORD;
    pDataArray[index].index = index;
    pDataArray[index].size = 2;
    pDataArray[index].type = ATTRIBUTE_TEXTURE_COORD;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Colors = there are no colors, this attribute will be disabled
    pDataArray[ATTRIBUTE_COLOR_LOCATION] = SAttributeData(ATTRIBUTE_COLOR);

    // Tangents - this attribute will be disabled
    pDataArray[ATTRIBUTE_TANGENT_LOCATION] = SAttributeData(ATTRIBUTE_TANGENT);

    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData3v::genBuffers(void) {
    if(!gfx::context::isInit())
        return FG_GFX_FALSE;
    int& count = getRefVBOCount();
    count = 1;
    context::genBuffers(count, getRefPtrVBO(), GL_STATIC_DRAW);
    context::bindBuffer(getRefPtrVBO()[0], GL_ARRAY_BUFFER);
    context::bufferData(getRefPtrVBO()[0],
                        this->stride() * this->size(),
                        self_type::front());
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData3v::deleteBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    context::deleteBuffers(getVBOCount(), getPtrVBO());
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData3v::destroyBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    context::deleteBuffers(getVBOCount(), getPtrVBO());
    SBufferID *& refBuf = getRefPtrVBO();
    fgFree<SBufferID>(refBuf);
    refBuf = NULL;
    int& count = getRefVBOCount();
    count = 0;
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------
// CVERTEXDATA4V - VERTEX4V
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData4v::refreshAttributes(SAttributeData *pDataArray) const {
    if(!pDataArray)
        return FG_GFX_FALSE;

    // 3V - pos + norm + uv + color
    fgGFXint index = 0;
    // If VBOs are not set this will act as data address
    uintptr_t pointer = (uintptr_t)((unsigned int*)self_type::front());
    uintptr_t offset = 0;
    const fgBool b_hasVBO = hasVBO();
    // Position coordinates - always present (at least at the moment)
    index = ATTRIBUTE_POSITION_LOCATION;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to normals (first is position of type fgVector3f)
    offset += sizeof (Vector3f);
    pointer += sizeof (Vector3f);
    // Normals coords - activated
    index = ATTRIBUTE_NORMAL_LOCATION;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to UVs (second is normal of type fgVector3f)
    offset += sizeof (Vector3f);
    pointer += sizeof (Vector3f);
    // Texture coordinates
    index = ATTRIBUTE_TEXTURE_COORD_LOCATION;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to Colors (last one was uv of type fgVector2f)
    offset += sizeof (Vector2f); // 2UVs
    pointer += sizeof (Vector2f);

    // Colors = there are no colors, this attribute will be disabled
    index = ATTRIBUTE_COLOR_LOCATION;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Tangents - this attribute will be disabled - not yet supported
    pDataArray[ATTRIBUTE_TANGENT_LOCATION] = SAttributeData(ATTRIBUTE_TANGENT);

    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData4v::setupAttributes(SAttributeData *pDataArray) const {
    if(!pDataArray)
        return FG_GFX_FALSE;
    // 3V - pos + norm + uv + color
    fgGFXint index = 0;
    // If VBOs are not set this will act as data address
    uintptr_t pointer = (uintptr_t)((unsigned int*)self_type::front());
    uintptr_t offset = 0;
    const fgBool b_hasVBO = hasVBO();
    // Position coordinates - always present (at least at the moment)
    index = ATTRIBUTE_POSITION_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 3;
    pDataArray[index].type = ATTRIBUTE_POSITION;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to normals (first is position of type fgVector3f)
    offset += sizeof (Vector3f);
    pointer += sizeof (Vector3f);
    // Normals coords - activated
    index = ATTRIBUTE_NORMAL_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 3;
    pDataArray[index].type = ATTRIBUTE_NORMAL;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to UVs (second is normal of type fgVector3f)
    offset += sizeof (Vector3f);
    pointer += sizeof (Vector3f);
    // Texture coordinates
    index = ATTRIBUTE_TEXTURE_COORD_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 2;
    pDataArray[index].type = ATTRIBUTE_TEXTURE_COORD;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to Colors (last one was uv of type fgVector2f)
    offset += sizeof (Vector2f); // 2UVs
    pointer += sizeof (Vector2f);

    // Colors = there are no colors, this attribute will be disabled
    index = ATTRIBUTE_COLOR_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 4;
    pDataArray[index].type = ATTRIBUTE_COLOR;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Tangents - this attribute will be disabled - not yet supported
    pDataArray[ATTRIBUTE_TANGENT_LOCATION] = SAttributeData(ATTRIBUTE_TANGENT);

    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData4v::genBuffers(void) {
    if(!gfx::context::isInit())
        return FG_GFX_FALSE;
    int& count = getRefVBOCount();
    count = 1;
    context::genBuffers(count, getRefPtrVBO(), GL_STATIC_DRAW);
    context::bindBuffer(getRefPtrVBO()[0], GL_ARRAY_BUFFER);
    context::bufferData(getRefPtrVBO()[0],
            this->stride() * this->size(),
            self_type::front());
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData4v::deleteBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    context::deleteBuffers(getVBOCount(), getPtrVBO());
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData4v::destroyBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    context::deleteBuffers(getVBOCount(), getPtrVBO());
    SBufferID *& refBuf = getRefPtrVBO();
    fgFree<SBufferID>(refBuf);
    refBuf = NULL;
    int& count = getRefVBOCount();
    count = 0;
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------
// CVERTEXDATA5HQV - VERTEX5HQV
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData5HQv::refreshAttributes(SAttributeData *pDataArray) const {
    if(!pDataArray)
        return FG_GFX_FALSE;

    // 3V - pos + norm + uv + color
    fgGFXint index = 0;
    // If VBOs are not set this will act as data address
    uintptr_t pointer = (uintptr_t)((unsigned int*)self_type::front());
    uintptr_t offset = 0;
    const fgBool b_hasVBO = hasVBO();
    // Position coordinates - always present (at least at the moment)
    index = ATTRIBUTE_POSITION_LOCATION;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to normals (first is position of type fgVector3f)
    offset += sizeof (Vector3f);
    pointer += sizeof (Vector3f);
    // Normals coords - activated
    index = ATTRIBUTE_NORMAL_LOCATION;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to UVs (second is normal of type fgVector3f)
    offset += sizeof (Vector3f);
    pointer += sizeof (Vector3f);
    // Texture coordinates
    index = ATTRIBUTE_TEXTURE_COORD_LOCATION;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to Tangents (last one was uv of type fgVector2f)
    offset += sizeof (Vector2f); // 2UVs
    pointer += sizeof (Vector2f);
   
    index = ATTRIBUTE_TANGENT_LOCATION;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to Bitangents (last one was tangent of type fgVector3f)
    offset += sizeof (Vector3f); // 3 floats
    pointer += sizeof (Vector3f);

    index = ATTRIBUTE_BITANGENT_LOCATION;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData5HQv::setupAttributes(SAttributeData *pDataArray) const {
    if(!pDataArray)
        return FG_GFX_FALSE;
    // 3V - pos + norm + uv + color
    fgGFXint index = 0;
    // If VBOs are not set this will act as data address
    uintptr_t pointer = (uintptr_t)((unsigned int*)self_type::front());
    uintptr_t offset = 0;
    const fgBool b_hasVBO = hasVBO();
    // Position coordinates - always present (at least at the moment)
    index = ATTRIBUTE_POSITION_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 3;
    pDataArray[index].type = ATTRIBUTE_POSITION;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to normals (first is position of type fgVector3f)
    offset += sizeof (Vector3f);
    pointer += sizeof (Vector3f);
    // Normals coords - activated
    index = ATTRIBUTE_NORMAL_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 3;
    pDataArray[index].type = ATTRIBUTE_NORMAL;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to UVs (second is normal of type fgVector3f)
    offset += sizeof (Vector3f);
    pointer += sizeof (Vector3f);
    // Texture coordinates
    index = ATTRIBUTE_TEXTURE_COORD_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 2;
    pDataArray[index].type = ATTRIBUTE_TEXTURE_COORD;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Colors = there are no colors, this attribute will be disabled
    pDataArray[ATTRIBUTE_COLOR_LOCATION] = SAttributeData(ATTRIBUTE_COLOR);

    // Move offset to Tangents (last one was uv of type fgVector2f)
    offset += sizeof (Vector2f); // 2UVs
    pointer += sizeof (Vector2f);
    
    // Tangents - this attribute will be disabled - not yet supported
    index = ATTRIBUTE_TANGENT_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 3;
    pDataArray[index].type = ATTRIBUTE_TANGENT;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }

    // Move offset to Bitangents (last one was tangent of type fgVector3f)
    offset += sizeof (Vector3f); // 3 floats
    pointer += sizeof (Vector3f);
    
    index = ATTRIBUTE_BITANGENT_LOCATION;
    pDataArray[index].index = index;
    pDataArray[index].size = 3;
    pDataArray[index].type = ATTRIBUTE_BITANGENT;
    pDataArray[index].dataType = FG_GFX_FLOAT;
    pDataArray[index].stride = this->stride();
    pDataArray[index].isEnabled = FG_TRUE;
    pDataArray[index].isInterleaved = FG_TRUE;
    pDataArray[index].isNormalized = FG_FALSE;
    if(b_hasVBO) {
        pDataArray[index].isBO = FG_TRUE;
        pDataArray[index].buffer = getPtrVBO()[0].id;
        pDataArray[index].offset = (fgGFXvoid *)offset;
    } else {
        pDataArray[index].isBO = FG_FALSE;
        pDataArray[index].buffer = 0;
        pDataArray[index].pointer = (fgGFXvoid *)pointer;
    }
    
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData5HQv::genBuffers(void) {
    if(!gfx::context::isInit())
        return FG_GFX_FALSE;
    int& count = getRefVBOCount();
    count = 1;
    context::genBuffers(count, getRefPtrVBO(), GL_STATIC_DRAW);
    context::bindBuffer(getRefPtrVBO()[0], GL_ARRAY_BUFFER);
    context::bufferData(getRefPtrVBO()[0],
                        this->stride() * this->size(),
                        gfx::CVertexData5HQv::front());
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData5HQv::deleteBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    context::deleteBuffers(getVBOCount(), getPtrVBO());
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------

fgGFXboolean gfx::CVertexData5HQv::destroyBuffers(void) {
    if(!getPtrVBO())
        return FG_GFX_FALSE;
    context::deleteBuffers(getVBOCount(), getPtrVBO());
    SBufferID *& refBuf = getRefPtrVBO();
    fgFree<SBufferID>(refBuf);
    refBuf = NULL;
    int& count = getRefVBOCount();
    count = 0;
    return FG_GFX_TRUE;
}
//------------------------------------------------------------------------------
