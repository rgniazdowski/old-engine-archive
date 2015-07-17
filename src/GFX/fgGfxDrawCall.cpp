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

gfx::CDrawCall::CDrawCall(const fgGfxDrawCallType type, const fgGFXuint attribMask) :
base_type(DRAWABLE_DRAWCALL),
m_vecDataBase(NULL),
m_vecData2v(NULL),
m_vecData3v(NULL),
m_vecData4v(NULL),
m_program(NULL),
m_textureID(),
m_MVP(NULL),
m_material(NULL),
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

    if(m_drawCallType == FG_GFX_DRAW_CALL_INTERNAL_ARRAY) {
        m_vecData2v = new CVertexData2v();
        m_vecData3v = new CVertexData3v();
        m_vecData4v = new CVertexData4v();

        m_vecData2v->reserve(4);
        m_vecData3v->reserve(4);
        m_vecData4v->reserve(4);
    }

    setZIndex(m_zIndex);
    setupVertexData(m_attribMask);
}
//------------------------------------------------------------------------------

gfx::CDrawCall::~CDrawCall() {
    m_program = NULL;
    m_MVP = NULL;
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
    m_material = NULL;
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::resetAttributeData(void) {

    memset(m_attrData, 0, sizeof (m_attrData));

    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].index = FG_GFX_ATTRIB_POS_LOCATION;
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].size = 3;
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].type = FG_GFX_POSITION;
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].dataType = FG_GFX_FLOAT;
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].stride = sizeof (Vertex3v);
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].isEnabled = FG_GFX_FALSE;

    m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].index = FG_GFX_ATTRIB_NORM_LOCATION;
    m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].size = 3;
    m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].type = FG_GFX_NORMAL;
    m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].dataType = FG_GFX_FLOAT;
    m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].stride = sizeof (Vertex3v);
    m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].isEnabled = FG_GFX_FALSE;

    m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].index = FG_GFX_ATTRIB_UVS_LOCATION;
    m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].size = 2;
    m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].type = FG_GFX_TEXTURE_COORD;
    m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].dataType = FG_GFX_FLOAT;
    m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].stride = sizeof (Vertex3v);
    m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].isEnabled = FG_GFX_FALSE;

    m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].index = FG_GFX_ATTRIB_COLOR_LOCATION;
    m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].size = 4;
    m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].type = FG_GFX_COLOR;
    m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].dataType = FG_GFX_FLOAT;
    m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].stride = sizeof (Vertex4v);
    m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].isEnabled = FG_GFX_FALSE;

    m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].index = FG_GFX_ATTRIB_TANGENT_LOCATION;
    m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].size = 3;
    m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].type = FG_GFX_TANGENT;
    m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].dataType = FG_GFX_FLOAT;
    m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].stride = 0; // Stride when using tangent?
    m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].isEnabled = FG_GFX_FALSE;
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

void gfx::CDrawCall::setupVertexData(fgGFXuint attribMask) {
    if(!attribMask)
        return;
    if(m_vecDataBase) {
        if(attribMask != m_vecDataBase->attribMask()) {
            m_vecDataBase->clear();
        } else {
            return;
        }
    }

    if(attribMask & FG_GFX_COLOR_BIT) {
        m_vecDataBase = m_vecData4v; //new fgVertexData4v();
    } else if(attribMask & FG_GFX_NORMAL_BIT) {
        m_vecDataBase = m_vecData3v; //new fgVertexData3v();
    } else {
        m_vecDataBase = m_vecData2v; //new fgVertexData2v();
    }
    if(m_drawCallType == FG_GFX_DRAW_CALL_INTERNAL_ARRAY && m_vecDataBase) {
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
    setDrawCallType(FG_GFX_DRAW_CALL_EXTERNAL_ARRAY);
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
    setDrawCallType(FG_GFX_DRAW_CALL_MESH);
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
    m_material = (SMaterial *)pMaterial;
    if(pMaterial->shaderProgram) {
        //m_program = pMaterial->shaderProgram;
        setShaderProgram(pMaterial->shaderProgram);
    }
    if(pMaterial->diffuseTex) {
        setTexture(pMaterial->diffuseTex->getRefGfxID());
    } else if(pMaterial->ambientTex) {
        //setTexture(pMaterial->ambientTex->getRefGfxID());
    } else if(pMaterial->specularTex) {

    } else if(pMaterial->normalTex) {

    }
    // This replaces value in sorting slot
    m_fastCmp.setPart(CMP_SLOT_TEXTURE, (fg::util::CFastCmp::data_type_32)sortingValue);
}
//------------------------------------------------------------------------------

gfx::SMaterial* gfx::CDrawCall::getMaterial(void) const {
    return m_material;
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

fgGfxDrawCallType gfx::CDrawCall::getDrawCallType(void) const {
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

void gfx::CDrawCall::setDrawCallType(const fgGfxDrawCallType type) {
    if(m_drawCallType != type && type == FG_GFX_DRAW_CALL_INTERNAL_ARRAY) {

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
    } else if(m_drawCallType != type && m_drawCallType == FG_GFX_DRAW_CALL_INTERNAL_ARRAY) {
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

void gfx::CDrawCall::setComponentActive(unsigned int component,
                                        const fgBool reset) {
    if(!component || reset)
        m_attribMask = 0;
    if(component & FG_GFX_POSITION_BIT)
        m_attribMask |= FG_GFX_POSITION_BIT;
    if(component & FG_GFX_NORMAL_BIT)
        m_attribMask |= FG_GFX_NORMAL_BIT;
    if(component & FG_GFX_UVS_BIT)
        m_attribMask |= FG_GFX_UVS_BIT;
    if(component & FG_GFX_COLOR_BIT)
        m_attribMask |= FG_GFX_COLOR_BIT;
    //if(component & FG_GFX_TANGENT_BIT)
    //	m_attribMask |= FG_GFX_TANGENT_BIT;
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
    m_MVP = MVP;
}
//------------------------------------------------------------------------------

gfx::CMVPMatrix *gfx::CDrawCall::getMVP(void) const {
    return m_MVP;
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setShaderProgram(gfx::CShaderProgram *pProgram) {
    m_program = pProgram;
    if(m_program) {
        m_fastCmp.setPart(CMP_SLOT_SHADER_PROGRAM, (fg::util::CFastCmp::data_type_32)m_program->getHandle().getIndex());
    } else {
        m_fastCmp.setPart(CMP_SLOT_SHADER_PROGRAM, (fg::util::CFastCmp::data_type_32)0);
    }
}
//------------------------------------------------------------------------------

gfx::CShaderProgram* gfx::CDrawCall::getShaderProgram(void) const {
    return m_program;
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::setTexture(const STextureID& textureID) {
    m_textureID = textureID;
    m_fastCmp.setPart(CMP_SLOT_TEXTURE, (fg::util::CFastCmp::data_type_32)m_textureID.id);
}
//------------------------------------------------------------------------------

gfx::STextureID const& gfx::CDrawCall::getTexture(void) const {
    return m_textureID;
}
//------------------------------------------------------------------------------

gfx::STextureID& gfx::CDrawCall::getTexture(void) {
    return m_textureID;
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

fgBool gfx::CDrawCall::applyAttributeData(void) {
    if(m_drawCallType == FG_GFX_DRAW_CALL_MESH ||
       m_drawCallType == FG_GFX_DRAW_CALL_INTERNAL_ARRAY ||
       m_drawCallType == FG_GFX_DRAW_CALL_EXTERNAL_ARRAY) {
        context::diffVertexAttribArrayMask(m_attribMask);
        if(m_attrData[0].isInterleaved == FG_TRUE && m_attrData[0].isBO) {
            context::bindBuffer(GL_ARRAY_BUFFER, m_attrData[0].buffer);
        } else {
            context::bindBuffer(GL_ARRAY_BUFFER, 0);
        }
        for(int i = 0; i < FG_GFX_ATTRIBUTE_COUNT; i++) {
            if(m_attrData[i].isEnabled) {
                if(m_attrData[i].isInterleaved == FG_FALSE && m_attrData[i].isBO) {
                    context::bindBuffer(GL_ARRAY_BUFFER, m_attrData[i].buffer);
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
            context::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_drawingInfo.buffer);
        } else {
            context::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    } else {
        return FG_FALSE;
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void gfx::CDrawCall::draw(void) {
    // Internal array uses vertex data objects allocated inside of this draw call
    // If it's not set - nothing to draw
    if(!m_vecDataBase && m_drawCallType == FG_GFX_DRAW_CALL_INTERNAL_ARRAY)
        return;
    fgBool scissorSet = FG_FALSE;
    if(m_scissorBox.z != 0 && m_scissorBox.w != 0) {
        // If scissor box has some kind of size then...
        context::scissor(m_scissorBox);
        scissorSet = FG_TRUE;
    }
    if(m_MVP && m_program) {
        // force use program?
        m_program->use();
        //m_MVP->calculate(m_modelMat);
        m_program->setUniform(m_MVP);
    }
    if(m_program) {
        if(context::isTexture(m_textureID.id)) {
            context::bindTexture(m_textureID);
            m_program->setUniform(FG_GFX_USE_TEXTURE, 1.0f);
        } else {
            m_program->setUniform(FG_GFX_USE_TEXTURE, 0.0f);
        }
        if(m_material) {
            if(m_material->isCustomColor()) {
                m_program->setUniform(FG_GFX_CUSTOM_COLOR,
                                      m_material->customColor.r,
                                      m_material->customColor.g,
                                      m_material->customColor.b,
                                      m_material->customColor.a);
            }
        }
    }
    // #FIXME - need to use attribute data array
    //fgGfxPrimitives::drawArray2D(m_vecDataBase, m_attribMask, m_primMode);
    if(m_drawCallType == FG_GFX_DRAW_CALL_INTERNAL_ARRAY) {
        m_vecDataBase->refreshAttributes(m_attrData);
        m_drawingInfo.count = m_vecDataBase->size();
    }
    // Will now draw data from Other types ...
    if(applyAttributeData()) {
        if(m_material) {
            context::setCullFace(m_material->isCullFace());
            context::setDepthTest(m_material->isDepthTest());
            context::setBlend(m_material->isBlend());
            context::frontFace((fgGFXenum)m_material->getGfxFrontFace());
            context::setCapability(gfx::DEPTH_WRITEMASK, m_material->isDepthWriteMask());
        }
        // attribute data array is set
        // unsigned short is mainly because of ES
        if(m_drawingInfo.buffer || m_drawingInfo.indices.pointer) {
            glDrawElements((fgGFXenum)m_primMode, m_drawingInfo.count, GL_UNSIGNED_SHORT, m_drawingInfo.indices.offset);
        } else {
            // #FIXME
            glDrawArrays((fgGFXenum)m_primMode, 0, m_drawingInfo.count);
        }
        // #FIXME
        context::bindBuffer(GL_ARRAY_BUFFER, 0);
        context::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    if(scissorSet) {
        // Reset the scissor box
        context::scissor();
    }
}
//------------------------------------------------------------------------------
