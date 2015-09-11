/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "GFX/fgGfxDrawCall.h"
#include "GFX/Shaders/fgGfxShaderProgram.h"
#include "GFX/Textures/fgTextureResource.h"
#include "GFX/fgGfxMaterial.h"

using namespace fg;

//------------------------------------------------------------------------------

gfx::CDrawCall::CDrawCall(const DrawCallType type, const AttributeMask attribMask) :
base_type(traits::DRAWABLE_DRAWCALL),
m_vecDataBase(NULL),
m_vecData2v(NULL),
m_vecData3v(NULL),
m_vecData4v(NULL),
m_pProgram(NULL),
m_textureIDs(),
m_textureSlots(),
m_pMVP(NULL),
m_pMaterial(NULL),
m_attribMask(attribMask),
m_drawCallType(type),
m_drawAppendMode(DRAW_APPEND_ABSOLUTE),
m_primMode(PrimitiveMode::TRIANGLES),
m_color(1.0f, 1.0f, 1.0f, 1.0f),
m_relMove(0.0f, 0.0f, 0.0f),
m_scissorBox(0, 0, 0, 0),
m_fastCmp(4, fg::util::CFastCmp::CMP_DATA_32),
m_zIndex(Z_INDEX_DEFAULT),
m_isManaged(0) {
    resetAttributeData();

    if(m_drawCallType == DRAW_CALL_INTERNAL_ARRAY) {
        m_vecData2v = new CVertexData2v();
        m_vecData3v = new CVertexData3v();
        m_vecData4v = new CVertexData4v();

        m_vecData2v->reserve(4);
        m_vecData3v->reserve(4);
        m_vecData4v->reserve(4);
    }

    setZIndex(m_zIndex);
    setupVertexData(m_attribMask);
    m_textureIDs.reserve(6);
    m_textureSlots.reserve(6);
}
//------------------------------------------------------------------------------

gfx::CDrawCall::~CDrawCall() {
    m_pProgram = NULL;
    m_pMVP = NULL;
    if(m_vecData2v) {
        m_vecData2v->clear();
        delete m_vecData2v;
        m_vecData2v = NULL;
    }
    if(m_vecData3v) {
        m_vecData3v->clear();
        delete m_vecData3v;
        m_vecData3v = NULL;
    }
    if(m_vecData4v) {
        m_vecData4v->clear();
        delete m_vecData4v;
        m_vecData4v = NULL;
    }
    m_vecDataBase = NULL;
    m_pMaterial = NULL;
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::resetAttributeData(void) {

    memset(m_attrData, 0, sizeof (m_attrData));

    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].index = ATTRIBUTE_POSITION_LOCATION;
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].size = 3;
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].type = ATTRIBUTE_POSITION;
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].dataType = FG_GFX_FLOAT;
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].stride = sizeof (Vertex3v);
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].isEnabled = FG_GFX_FALSE;

    m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].index = ATTRIBUTE_NORMAL_LOCATION;
    m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].size = 3;
    m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].type = ATTRIBUTE_NORMAL;
    m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].dataType = FG_GFX_FLOAT;
    m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].stride = sizeof (Vertex3v);
    m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].isEnabled = FG_GFX_FALSE;

    m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].index = ATTRIBUTE_TEXTURE_COORD_LOCATION;
    m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].size = 2;
    m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].type = ATTRIBUTE_TEXTURE_COORD;
    m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].dataType = FG_GFX_FLOAT;
    m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].stride = sizeof (Vertex3v);
    m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].isEnabled = FG_GFX_FALSE;

    m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].index = ATTRIBUTE_COLOR_LOCATION;
    m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].size = 4;
    m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].type = ATTRIBUTE_COLOR;
    m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].dataType = FG_GFX_FLOAT;
    m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].stride = sizeof (Vertex4v);
    m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].isEnabled = FG_GFX_FALSE;

    m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].index = ATTRIBUTE_TANGENT_LOCATION;
    m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].size = 3;
    m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].type = ATTRIBUTE_TANGENT;
    m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].dataType = FG_GFX_FLOAT;
    m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].stride = 0; // Stride when using tangent?
    m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].isEnabled = FG_GFX_FALSE;

    m_attrData[FG_GFX_ATTRIB_BITANGENT_LOCATION].index = ATTRIBUTE_BITANGENT_LOCATION;
    m_attrData[FG_GFX_ATTRIB_BITANGENT_LOCATION].size = 3;
    m_attrData[FG_GFX_ATTRIB_BITANGENT_LOCATION].type = ATTRIBUTE_BITANGENT;
    m_attrData[FG_GFX_ATTRIB_BITANGENT_LOCATION].dataType = FG_GFX_FLOAT;
    m_attrData[FG_GFX_ATTRIB_BITANGENT_LOCATION].stride = 0; // Stride when using tangent?
    m_attrData[FG_GFX_ATTRIB_BITANGENT_LOCATION].isEnabled = FG_GFX_FALSE;

    m_attrData[FG_GFX_ATTRIB_BLEND_WEIGHTS_LOCATION].index = ATTRIBUTE_BLEND_WEIGHTS_LOCATION;
    m_attrData[FG_GFX_ATTRIB_BLEND_WEIGHTS_LOCATION].size = 4;
    m_attrData[FG_GFX_ATTRIB_BLEND_WEIGHTS_LOCATION].type = ATTRIBUTE_BLEND_WEIGHTS;
    m_attrData[FG_GFX_ATTRIB_BLEND_WEIGHTS_LOCATION].dataType = FG_GFX_FLOAT;
    m_attrData[FG_GFX_ATTRIB_BLEND_WEIGHTS_LOCATION].stride = 0;
    m_attrData[FG_GFX_ATTRIB_BLEND_WEIGHTS_LOCATION].isEnabled = FG_GFX_FALSE;

    m_attrData[FG_GFX_ATTRIB_BLEND_INDICES_LOCATION].index = ATTRIBUTE_BLEND_INDICES_LOCATION;
    m_attrData[FG_GFX_ATTRIB_BLEND_INDICES_LOCATION].size = 4;
    m_attrData[FG_GFX_ATTRIB_BLEND_INDICES_LOCATION].type = ATTRIBUTE_BLEND_INDICES;
    m_attrData[FG_GFX_ATTRIB_BLEND_INDICES_LOCATION].dataType = FG_GFX_FLOAT;
    m_attrData[FG_GFX_ATTRIB_BLEND_INDICES_LOCATION].stride = 0;
    m_attrData[FG_GFX_ATTRIB_BLEND_INDICES_LOCATION].isEnabled = FG_GFX_FALSE;
    
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setManaged(const fgBool toggle) {
    m_isManaged = toggle;
}
//------------------------------------------------------------------------------

fgBool gfx::CDrawCall::isManaged(void) const {
    return m_isManaged;
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setupVertexData(AttributeMask attribMask) {
    if(!attribMask)
        return;
    if(m_vecDataBase) {
        if(attribMask != m_vecDataBase->attribMask()) {
            m_vecDataBase->clear();
        } else {
            return;
        }
    }

    if(attribMask & ATTRIBUTE_COLOR_BIT) {
        m_vecDataBase = m_vecData4v; //new fgVertexData4v();
    } else if(attribMask & ATTRIBUTE_NORMAL_BIT) {
        m_vecDataBase = m_vecData3v; //new fgVertexData3v();
    } else {
        m_vecDataBase = m_vecData2v; //new fgVertexData2v();
    }
    if(m_drawCallType == DRAW_CALL_INTERNAL_ARRAY && m_vecDataBase) {
        m_vecDataBase->setupAttributes(m_attrData);
        memset(&m_drawingInfo, 0, sizeof (m_drawingInfo));
    }
    m_attribMask = attribMask;
    m_fastCmp.setPart(CMP_SLOT_ATTRIB_MASK, (fg::util::CFastCmp::data_type_32)m_attribMask);
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setupFromVertexData(const CVertexData* pVertexData) {
    if(!pVertexData)
        return;
    pVertexData->setupAttributes(m_attrData);
    setDrawCallType(DRAW_CALL_EXTERNAL_ARRAY);
    m_attribMask = pVertexData->attribMask();
    m_fastCmp.setPart(CMP_SLOT_ATTRIB_MASK, (util::CFastCmp::data_type_32)m_attribMask);
    refreshDrawingInfo(pVertexData);
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::refreshDrawingInfo(const CVertexData* pVertexData) {
    if(!pVertexData)
        return;
    m_drawingInfo.buffer = 0;
    m_drawingInfo.indices.pointer = NULL;
    m_drawingInfo.count = pVertexData->getNumVertices();
    if(pVertexData->hasIndices() && pVertexData->getNumIndices()) {
        m_drawingInfo.buffer = pVertexData->getIndicesVBO();
        m_drawingInfo.indices.pointer = pVertexData->getIndicesPointer();
        if(!m_drawingInfo.buffer && !m_drawingInfo.indices.pointer)
            m_drawingInfo.count = pVertexData->getNumVertices();
        else
            m_drawingInfo.count = pVertexData->getNumIndices();
        // If both pointer/offset and buffer are zero
        // then it means that there is no indices array
    }
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setupFromMesh(const SMeshBase* pMesh) {
    if(!pMesh)
        return;
    pMesh->setupAttributes(m_attrData);
    setDrawCallType(DRAW_CALL_MESH);
    m_primMode = pMesh->primMode;
    m_attribMask = pMesh->attribMask();
    m_fastCmp.setPart(CMP_SLOT_ATTRIB_MASK, (util::CFastCmp::data_type_32)m_attribMask);
    refreshDrawingInfo(pMesh);
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setupFromShape(const SShape* pShape) {
    if(!pShape)
        return;
    if(!pShape->mesh)
        return;
    setupFromMesh(pShape->mesh);
    if(pShape->material) {
        setupMaterial(pShape->material);
    }
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setupMaterial(const SMaterial* pMaterial) {
    if(!pMaterial)
        return;

    unsigned int sortingValue = pMaterial->getSortingValue();
    // how to get texture?
    m_pMaterial = (SMaterial *)pMaterial;
    if(pMaterial->shaderProgram) {
        //m_program = pMaterial->shaderProgram;
        setShaderProgram(pMaterial->shaderProgram);
    }
    m_textureIDs.clear();
    m_textureSlots.clear();
    if(pMaterial->diffuseTex) {
        setTexture(pMaterial->diffuseTex->getRefGfxID(), texture::UNIT_DIFFUSE);
    }
    if(pMaterial->ambientTex) {
        setTexture(pMaterial->ambientTex->getRefGfxID(), texture::UNIT_AMBIENT);
    }
    if(pMaterial->specularTex) {
        setTexture(pMaterial->specularTex->getRefGfxID(), texture::UNIT_SPECULAR);
    }
    if(pMaterial->normalTex) {
        setTexture(pMaterial->normalTex->getRefGfxID(), texture::UNIT_NORMAL);
    }
    // This replaces value in sorting slot
    m_fastCmp.setPart(CMP_SLOT_TEXTURE, (fg::util::CFastCmp::data_type_32)sortingValue);
}
//------------------------------------------------------------------------------

gfx::SMaterial* gfx::CDrawCall::getMaterial(void) const {
    return m_pMaterial;
}
//------------------------------------------------------------------------------

Vector4i const& gfx::CDrawCall::getScissorBox(void) const {
    return m_scissorBox;
}
//------------------------------------------------------------------------------

Vector3f const& gfx::CDrawCall::getRelMove(void) const {
    return m_relMove;
}
//------------------------------------------------------------------------------

int gfx::CDrawCall::getZIndex(void) const {
    return m_zIndex;
}
//------------------------------------------------------------------------------

gfx::SAttributeData* gfx::CDrawCall::getAttributeData(void) {
    return m_attrData;
}
//------------------------------------------------------------------------------

fgGFXuint gfx::CDrawCall::getAttribMask(void) const {
    return m_attribMask;
}
//------------------------------------------------------------------------------

gfx::DrawCallType gfx::CDrawCall::getDrawCallType(void) const {
    return m_drawCallType;
}
//------------------------------------------------------------------------------

gfx::DrawAppendMode gfx::CDrawCall::getDrawAppendMode(void) const {
    return m_drawAppendMode;
}
//------------------------------------------------------------------------------

gfx::PrimitiveMode gfx::CDrawCall::getPrimitiveMode(void) const {
    return m_primMode;
}
//------------------------------------------------------------------------------

gfx::CVertexData *gfx::CDrawCall::getVertexData(void) const {
    return m_vecDataBase;
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setScissorBox(const fgGFXint x,
                                   const fgGFXint y,
                                   const fgGFXint width,
                                   const fgGFXint height) {
    m_scissorBox.x = x;
    m_scissorBox.y = y;
    m_scissorBox.z = width;
    m_scissorBox.w = height;
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setScissorBox(const Vector2i& pos, const Vector2i& size) {
    m_scissorBox.x = pos.x;
    m_scissorBox.y = pos.y;
    m_scissorBox.z = size.x;
    m_scissorBox.w = size.y;
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setScissorBox(const Vector4i& dimensions) {
    m_scissorBox = dimensions;
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setRelMove(const Vector3f& relMove) {
    m_relMove = relMove;
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setRelMove(const Vector2f& relMove) {
    m_relMove.x = relMove.x;
    m_relMove.y = relMove.y;
    m_relMove.z = 0.0f;
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setZIndex(const int zIndex) {
    if(zIndex < 0) {
        m_zIndex = Z_INDEX_DEFAULT + zIndex;
    } else {
        m_zIndex = zIndex;
    }
    m_fastCmp.setPart(CMP_SLOT_Z_INDEX, (fg::util::CFastCmp::data_type_32)m_zIndex);
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::upZIndex(void) {
    m_zIndex++;
    m_fastCmp.setPart(CMP_SLOT_Z_INDEX, (fg::util::CFastCmp::data_type_32)m_zIndex);
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::downZIndex(void) {
    m_zIndex--;
    m_fastCmp.setPart(CMP_SLOT_Z_INDEX, (fg::util::CFastCmp::data_type_32)m_zIndex);
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setDrawCallType(const DrawCallType type) {
    if(m_drawCallType != type && type == DRAW_CALL_INTERNAL_ARRAY) {

        if(!m_vecData2v) {
            m_vecData2v = new CVertexData2v();
            m_vecData2v->reserve(4);
        }
        if(!m_vecData3v) {
            m_vecData3v = new CVertexData3v();
            m_vecData3v->reserve(4);
        }
        if(!m_vecData4v) {
            m_vecData4v = new CVertexData4v();
            m_vecData4v->reserve(4);
        }
        m_vecData2v->clear();
        m_vecData3v->clear();
        m_vecData4v->clear();
        setupVertexData(m_attribMask);
    } else if(m_drawCallType != type && m_drawCallType == DRAW_CALL_INTERNAL_ARRAY) {
        if(m_vecData2v) {
            delete m_vecData2v;
            m_vecData2v = NULL;
        }
        if(m_vecData3v) {
            delete m_vecData3v;
            m_vecData3v = NULL;
        }
        if(m_vecData4v) {
            delete m_vecData4v;
            m_vecData4v = NULL;
        }
        m_vecDataBase = NULL;
        resetAttributeData();
        m_fastCmp.setPart(CMP_SLOT_ATTRIB_MASK, (fg::util::CFastCmp::data_type_32)m_attribMask);
    }
    m_drawCallType = type;
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setDrawAppendMode(const DrawAppendMode mode) {
    m_drawAppendMode = mode;
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setPrimitiveMode(const PrimitiveMode mode) {
    m_primMode = mode;
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setComponentActive(AttributeMask component,
                                        const fgBool reset) {
    if(!((int)component) || reset)
        m_attribMask = ATTRIBUTE_ZERO_BIT;
    if(component & ATTRIBUTE_POSITION_BIT)
        m_attribMask |= ATTRIBUTE_POSITION_BIT;
    if(component & ATTRIBUTE_NORMAL_BIT)
        m_attribMask |= ATTRIBUTE_NORMAL_BIT;
    if(component & ATTRIBUTE_UVS_BIT)
        m_attribMask |= ATTRIBUTE_UVS_BIT;
    if(component & ATTRIBUTE_COLOR_BIT)
        m_attribMask |= ATTRIBUTE_COLOR_BIT;
    if(component & ATTRIBUTE_TANGENT_BIT)
        m_attribMask |= ATTRIBUTE_TANGENT_BIT;
    if(component & ATTRIBUTE_BITANGENT_BIT)
        m_attribMask |= ATTRIBUTE_BITANGENT_BIT;
    if(component & ATTRIBUTE_BLEND_WEIGHTS_BIT)
        m_attribMask |= ATTRIBUTE_BLEND_WEIGHTS_BIT;
    if(component & ATTRIBUTE_BLEND_INDICES_BIT)
        m_attribMask |= ATTRIBUTE_BLEND_INDICES_BIT;
    setupVertexData(m_attribMask);
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setColor(const Color3f& color) {
    m_color = Color4f(color.r, color.g, color.b, 1.0f);
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setColor(const Color4f& color) {
    m_color = color;
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::resetColor(void) {
    m_color = Color4f(1.0f, 1.0f, 1.0f, 1.0f);
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setMVP(CMVPMatrix *MVP) {
    m_pMVP = MVP;
}
//------------------------------------------------------------------------------

gfx::CMVPMatrix *gfx::CDrawCall::getMVP(void) const {
    return m_pMVP;
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setShaderProgram(gfx::CShaderProgram *pProgram) {
    m_pProgram = pProgram;
    if(m_pProgram) {
        m_fastCmp.setPart(CMP_SLOT_SHADER_PROGRAM, (fg::util::CFastCmp::data_type_32)m_pProgram->getHandle().getIndex());
    } else {
        m_fastCmp.setPart(CMP_SLOT_SHADER_PROGRAM, (fg::util::CFastCmp::data_type_32)0);
    }
}
//------------------------------------------------------------------------------

gfx::CShaderProgram* gfx::CDrawCall::getShaderProgram(void) const {
    return m_pProgram;
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setTexture(const STextureID& textureID, const unsigned int slot) {
    int sIdx = m_textureSlots.find(slot);
    if(sIdx < 0) {
        m_textureIDs.push_back(textureID);
        m_textureSlots.resize(m_textureIDs.size());
        m_textureSlots[m_textureIDs.size() - 1] = slot;
    } else {
        m_textureIDs[sIdx] = textureID;
        m_textureSlots[sIdx] = slot;
    }
    m_fastCmp.setPart(CMP_SLOT_TEXTURE, (fg::util::CFastCmp::data_type_32)textureID.id);
}
//------------------------------------------------------------------------------

gfx::STextureID const& gfx::CDrawCall::getTexture(const unsigned int slot) const {
    int index = m_textureSlots.find(slot);
    if(index < 0)
        return m_textureIDs[0];
    else
        return m_textureIDs.at(index);
}
//------------------------------------------------------------------------------

gfx::STextureID& gfx::CDrawCall::getTexture(const unsigned int slot) {
    int index = m_textureSlots.find(slot);
    if(index < 0)
        return m_textureIDs[0];
    else
        return m_textureIDs.at(index);
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::flush(void) {
    m_relMove = Vector3f(0.0f, 0.0f, 0.0f);
    if(m_vecDataBase)
        m_vecDataBase->clear();
    m_zIndex = 0;
    m_scissorBox = Vector4i();
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::appendRect2D(const Vec2f &size,
                                  const Vec2f &uv1, const Vec2f &uv2,
                                  const fgBool rewind) {
    // #FIXME - TOO DEEP CALL 
    primitives::appendRect2D(m_vecDataBase, Vec2f(0.0f, 0.0f), size, uv1, uv2, m_color, m_primMode, rewind);
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::appendRect2D(const Vec2f &relPos, const Vec2f &size,
                                  const Vec2f &uv1, const Vec2f &uv2,
                                  const fgBool rewind) {
    Vec2f pos(relPos.x, relPos.y);
    pos.x += m_relMove.x;
    pos.y += m_relMove.y;
    if(m_drawAppendMode == DRAW_APPEND_RELATIVE) {
        m_relMove.x += size.x;
        m_relMove.y += size.y;
    }
    // #FIXME - TOO DEEP CALL
    primitives::appendRect2D(m_vecDataBase, pos, size, uv1, uv2, m_color, m_primMode, rewind);
}
//------------------------------------------------------------------------------
#if 0

fgBool gfx::CDrawCall::applyAttributeData(void) {
    if(m_drawCallType == DRAW_CALL_MESH ||
       m_drawCallType == DRAW_CALL_INTERNAL_ARRAY ||
       m_drawCallType == DRAW_CALL_EXTERNAL_ARRAY) {
        context::diffVertexAttribArrayMask(m_attribMask);
        if(m_attrData[0].isInterleaved == FG_TRUE && m_attrData[0].isBO) {
            context::bindBuffer(gfx::ARRAY_BUFFER, m_attrData[0].buffer);
        } else {
            context::bindBuffer(gfx::ARRAY_BUFFER, 0);
        }
        for(int i = 0; i < NUM_ATTRIBUTE_TYPES; i++) {
            if(m_attrData[i].isEnabled) {
                if(m_attrData[i].isInterleaved == FG_FALSE && m_attrData[i].isBO) {
                    context::bindBuffer(gfx::ARRAY_BUFFER, m_attrData[i].buffer);
                }
                context::vertexAttribPointer(m_attrData[i].index,
                                             m_attrData[i].size,
                                             m_attrData[i].dataType,
                                             m_attrData[i].isNormalized,
                                             m_attrData[i].stride,
                                             m_attrData[i].offset);
            }
        }
        if(m_drawingInfo.buffer) {
            context::bindBuffer(gfx::ELEMENT_ARRAY_BUFFER, m_drawingInfo.buffer);
        } else {
            context::bindBuffer(gfx::ELEMENT_ARRAY_BUFFER, 0);
        }
    } else {
        return FG_FALSE;
    }
    return FG_TRUE;
}
#endif
//------------------------------------------------------------------------------

void gfx::CDrawCall::draw(void) {
    // Internal array uses vertex data objects allocated inside of this draw call
    // If it's not set - nothing to draw
    if(!m_vecDataBase && m_drawCallType == DRAW_CALL_INTERNAL_ARRAY) {
        return;
    }
    if(m_drawCallType == DRAW_CALL_INTERNAL_ARRAY) {
        m_vecDataBase->refreshAttributes(m_attrData);
        m_drawingInfo.count = m_vecDataBase->size();
    }
    if(!m_drawingInfo.count) {
        return;
    }
    fgBool scissorSet = FG_FALSE;
    if(m_scissorBox.z != 0 && m_scissorBox.w != 0) {
        // If scissor box has some kind of size then...
        context::scissor(m_scissorBox);
        scissorSet = FG_TRUE;
    }
    if(m_pMVP && m_pProgram) {
        // force use program?
        m_pProgram->use();
        m_pProgram->setUniform(m_pMVP);
    }
    if(m_pProgram) {
        float useTexture = 0.0f;
        const unsigned int n = m_textureSlots.size();
        for(unsigned int i = 0; i < n; i++) {
            if(context::isTexture(m_textureIDs[i].id)) {
                useTexture = 1.0f;
                context::activeTexture(GL_TEXTURE0 + m_textureSlots[i]);
                context::bindTexture(m_textureIDs[i]);
            }
        }
        if(useTexture < 1.0f)
            context::activeTexture(GL_TEXTURE0);
        //m_pProgram->setUniform(shaders::UNIFORM_NORMAL_MAP)
        m_pProgram->setUniform(shaders::UNIFORM_USE_TEXTURE, useTexture);
        if(m_pMaterial) {
            m_pProgram->setUniform(*m_pMaterial);
            if(m_pMaterial->isCustomColor()) {
                m_pProgram->setUniform(shaders::UNIFORM_CUSTOM_COLOR,
                                       m_pMaterial->customColor.r,
                                       m_pMaterial->customColor.g,
                                       m_pMaterial->customColor.b,
                                       m_pMaterial->customColor.a);
            }
        }
    }
    // Will now draw data    
    if(m_drawCallType == DRAW_CALL_MESH ||
       m_drawCallType == DRAW_CALL_INTERNAL_ARRAY ||
       m_drawCallType == DRAW_CALL_EXTERNAL_ARRAY) {
        primitives::applyAttributeData(m_attrData, m_drawingInfo, m_attribMask);
        if(m_pMaterial) {
            context::setCullFace(m_pMaterial->isCullFace());
            context::setDepthTest(m_pMaterial->isDepthTest());
            context::setBlend(m_pMaterial->isBlend());
            context::frontFace((fgGFXenum)m_pMaterial->getGfxFrontFace());
            context::setCapability(gfx::DEPTH_WRITEMASK, m_pMaterial->isDepthWriteMask());
        }
        // attribute data array is set
        // unsigned short is mainly because of ES
        if(m_drawingInfo.buffer || m_drawingInfo.indices.pointer) {
            context::drawElements(m_primMode, m_drawingInfo.count, m_drawingInfo.indices.offset);
        } else {
            // #FIXME
            context::drawArrays(m_primMode, 0, m_drawingInfo.count);
        }
        // #FIXME
        context::bindBuffer(gfx::ARRAY_BUFFER, 0);
        context::bindBuffer(gfx::ELEMENT_ARRAY_BUFFER, 0);
    }

    if(scissorSet) {
        // Reset the scissor box
        context::scissor();
    }
}
//------------------------------------------------------------------------------
