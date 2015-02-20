/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXDrawCall.h"

using namespace fg;

/**
 * 
 * @param type
 * @param attribMask
 */
gfx::CDrawCall::CDrawCall(const fgGfxDrawCallType type, const fgGFXuint attribMask) :
CDrawable(DRAWABLE_DRAWCALL),
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
m_fastCmp(4, fg::util::FastCmp::CMP_DATA_32),
m_zIndex(Z_INDEX_DEFAULT),
m_isManaged(0) {
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].index = FG_GFX_ATTRIB_POS_LOCATION;
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].size = 3;
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].type = FG_GFX_POSITION;
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].dataType = FG_GFX_FLOAT;
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].stride = sizeof (Vertex3v);
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].isEnabled = FG_GFX_TRUE;

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
    m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].isEnabled = FG_GFX_TRUE;

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

    // #FIXME #LOL
    m_vecData2v = new CVertexData2v();
    m_vecData3v = new CVertexData3v();
    m_vecData4v = new CVertexData4v();

    m_vecData2v->reserve(2);
    m_vecData3v->reserve(2);
    m_vecData4v->reserve(2);

    setZIndex(m_zIndex);
    setupVertexData(m_attribMask);
}

/*
 *
 */
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

/**
 * 
 * @param toggle
 */
void gfx::CDrawCall::setManaged(const fgBool toggle) {
    m_isManaged = toggle;
}

/**
 * 
 * @return 
 */
fgBool gfx::CDrawCall::isManaged(void) const {
    return m_isManaged;
}

/**
 * 
 * @param attribMask
 */
void gfx::CDrawCall::setupVertexData(fgGFXuint attribMask) {
    if(!attribMask)
        return;
    if(m_vecDataBase) {
        if(attribMask != m_vecDataBase->attribMask()) {
            m_vecDataBase->clear();
            //delete m_vecDataBase;
            //printf("delete m_vecDataBase;\n");
            //m_vecDataBase = NULL;
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
    if(m_drawCallType == FG_GFX_DRAW_CALL_CUSTOM_ARRAY) {
        //if(m_vecDataBase->reserve(1))
        //m_vecDataBase->
        //m_vecDataBase->reserve(2);
        m_vecDataBase->setupAttributes(m_attrData);
        memset(&m_drawingInfo, 0, sizeof (m_drawingInfo));
    }
    m_attribMask = attribMask;
    m_fastCmp.setPart(0, (fg::util::FastCmp::data_type_32)m_attribMask);
}

/**
 * 
 * @param pMesh
 */
void gfx::CDrawCall::setupFromMesh(const SMeshBase* pMesh) {
    if(!pMesh)
        return;
    pMesh->setupAttributes(m_attrData);
    m_drawCallType = FG_GFX_DRAW_CALL_MESH;
    m_primMode = pMesh->primMode;
    m_attribMask = pMesh->attribMask();
    m_fastCmp.setPart(0, (util::FastCmp::data_type_32)m_attribMask);
    if(pMesh->hasIndices()) {
        m_drawingInfo.buffer = pMesh->getIndicesVBO();
        m_drawingInfo.indices.pointer = pMesh->getIndicesPointer();
        if(!m_drawingInfo.buffer && !m_drawingInfo.indices.pointer)
            m_drawingInfo.count = pMesh->getNumVertices();
        else
            m_drawingInfo.count = pMesh->getNumIndices();
        // If both pointer/offset and buffer are zero
        // then it means that there is no indices array
    }
}

/**
 * 
 * @param pShape
 */
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

/**
 * 
 * @param pMaterial
 */
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
    if(pMaterial->ambientTex) {
        setTexture(pMaterial->ambientTex->getRefGfxID());
    } else if(pMaterial->diffuseTex) {
        setTexture(pMaterial->diffuseTex->getRefGfxID());
    } else if(pMaterial->specularTex) {
        
    } else if(pMaterial->normalTex) {
        
    }
    // textures?
    // #FIXME
    //m_fastCmp.setPart(1, (fg::util::FastCmp::data_type_32)m_textureID.id);
    // This replaces value in sorting slot
    m_fastCmp.setPart(1, (fg::util::FastCmp::data_type_32)sortingValue);
}

/**
 * 
 * @return 
 */
gfx::SMaterial* gfx::CDrawCall::getMaterial(void) const {
    return m_material;
}

/**
 * 
 * @return 
 */
Vector4i const & gfx::CDrawCall::getScissorBox(void) const {
    return m_scissorBox;
}

/**
 * 
 * @return 
 */
Vector3f const & gfx::CDrawCall::getRelMove(void) const {
    return m_relMove;
}

/**
 * 
 * @return 
 */
int gfx::CDrawCall::getZIndex(void) const {
    return m_zIndex;
}

/**
 * 
 * @return 
 */
gfx::SAttributeData* gfx::CDrawCall::getAttributeData(void) {
    return m_attrData;
}

/**
 * 
 * @return 
 */
fgGFXuint gfx::CDrawCall::getAttribMask(void) const {
    return m_attribMask;
}

/**
 * 
 * @return 
 */
fgGfxDrawCallType gfx::CDrawCall::getDrawCallType(void) const {
    return m_drawCallType;
}

/**
 * 
 * @return 
 */
gfx::DrawAppendMode gfx::CDrawCall::getDrawAppendMode(void) const {
    return m_drawAppendMode;
}

/**
 * 
 * @return 
 */
gfx::PrimitiveMode gfx::CDrawCall::getPrimitiveMode(void) const {
    return m_primMode;
}

/**
 * 
 * @return 
 */
gfx::CVertexData *gfx::CDrawCall::getVertexData(void) const {
    return m_vecDataBase;
}

/**
 * 
 * @param x
 * @param y
 * @param width
 * @param height
 */
void gfx::CDrawCall::setScissorBox(const fgGFXint x, const fgGFXint y, const fgGFXint width, const fgGFXint height) {
    m_scissorBox.x = x;
    m_scissorBox.y = y;
    m_scissorBox.z = width;
    m_scissorBox.w = height;
}

/**
 * 
 * @param pos
 * @param size
 */
void gfx::CDrawCall::setScissorBox(const Vector2i& pos, const Vector2i & size) {
    m_scissorBox.x = pos.x;
    m_scissorBox.y = pos.y;
    m_scissorBox.z = size.x;
    m_scissorBox.w = size.y;
}

/**
 * 
 * @param dimensions
 */
void gfx::CDrawCall::setScissorBox(const Vector4i & dimensions) {
    m_scissorBox = dimensions;
}

/**
 * 
 * @param relMove
 */
void gfx::CDrawCall::setRelMove(const Vector3f& relMove) {
    m_relMove = relMove;
}

/**
 * 
 * @param relMove
 */
void gfx::CDrawCall::setRelMove(const Vector2f& relMove) {
    m_relMove.x = relMove.x;
    m_relMove.y = relMove.y;
    m_relMove.z = 0.0f;
}

/**
 * 
 * @param zIndex
 */
void gfx::CDrawCall::setZIndex(const int zIndex) {
    if(zIndex < 0) {
        m_zIndex = Z_INDEX_DEFAULT + zIndex;
    } else {
        m_zIndex = zIndex;
    }
    m_fastCmp.setPart(3, (fg::util::FastCmp::data_type_32)m_zIndex);
}

/*
 *
 */
void gfx::CDrawCall::upZIndex(void) {
    m_zIndex++;
    m_fastCmp.setPart(3, (fg::util::FastCmp::data_type_32)m_zIndex);
}

/*
 *
 */
void gfx::CDrawCall::downZIndex(void) {
    m_zIndex--;
    m_fastCmp.setPart(3, (fg::util::FastCmp::data_type_32)m_zIndex);
}

/*
 *
 */
void gfx::CDrawCall::setDrawCallType(const fgGfxDrawCallType type) {
    m_drawCallType = type;
}

/*
 *
 */
void gfx::CDrawCall::setDrawAppendMode(const DrawAppendMode mode) {
    m_drawAppendMode = mode;
}

/*
 *
 */
void gfx::CDrawCall::setPrimitiveMode(const PrimitiveMode mode) {
    m_primMode = mode;
}

/*
 * Whether to set UVs, normals or colors active
 */
void gfx::CDrawCall::setComponentActive(unsigned int component, const fgBool reset) {
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

/*
 *
 */
void gfx::CDrawCall::setColor(const fgColor3f& color) {
    m_color = fgColor4f(color.r, color.g, color.b, 1.0f);
}

/*
 *
 */
void gfx::CDrawCall::setColor(const fgColor4f& color) {
    m_color = color;
}

/*
 *
 */
void gfx::CDrawCall::resetColor(void) {
    m_color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

/*
 *
 */
void gfx::CDrawCall::setMVP(CMVPMatrix *MVP) {
    m_MVP = MVP;
}

/*
 *
 */
gfx::CMVPMatrix *gfx::CDrawCall::getMVP(void) const {
    return m_MVP;
}

/*
 * Can be null, which would mean that this draw call does not care about such thing
 * However it should be avoided. Shader program knows if it's being currently used.
 * Also only through shader manager given shader program can be set as active.
 */
void gfx::CDrawCall::setShaderProgram(gfx::CShaderProgram *pProgram) {
    m_program = pProgram;
    if(m_program)
        m_fastCmp.setPart(2, (fg::util::FastCmp::data_type_32)m_program->getHandle().getIndex());
    else
        m_fastCmp.setPart(2, (fg::util::FastCmp::data_type_32)0);

}

/*
 *
 */
gfx::CShaderProgram* gfx::CDrawCall::getShaderProgram(void) const {
    return m_program;
}

/**
 * 
 * @param textureID
 */
void gfx::CDrawCall::setTexture(const STextureID& textureID) {
    m_textureID = textureID;
    m_fastCmp.setPart(1, (fg::util::FastCmp::data_type_32)m_textureID.id);
}

/**
 * 
 * @return 
 */
gfx::STextureID const& gfx::CDrawCall::getTexture(void) const {
    return m_textureID;
}

/*
 *
 */
gfx::STextureID& gfx::CDrawCall::getTexture(void) {
    return m_textureID;
}

/*
 * Clear the buffers
 */
void gfx::CDrawCall::flush(void) {
    m_relMove = Vector3f(0.0f, 0.0f, 0.0f);
    if(m_vecDataBase)
        m_vecDataBase->clear();
    m_zIndex = 0;
    m_scissorBox = Vector4i();
}

/*
 * Append simple rectangle next to the last one
 */
void gfx::CDrawCall::appendRect2D(const Vec2f &size,
                                  const Vec2f &uv1, const Vec2f &uv2,
                                  const fgBool rewind) {
    // #FIXME - TOO DEEP CALL 
    CPrimitives::appendRect2D(m_vecDataBase, Vec2f(0.0f, 0.0f), size, uv1, uv2, m_color, m_primMode, rewind);
}

/*
 *
 */
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
    CPrimitives::appendRect2D(m_vecDataBase, pos, size, uv1, uv2, m_color, m_primMode, rewind);
}

/**
 * 
 * @return 
 */
fgBool gfx::CDrawCall::applyAttributeData(void) {
    if(m_drawCallType == FG_GFX_DRAW_CALL_MESH ||
       m_drawCallType == FG_GFX_DRAW_CALL_CUSTOM_ARRAY) {
        CPlatform::context()->diffVertexAttribArrayMask(m_attribMask);
        if(m_attrData[0].isInterleaved == FG_TRUE && m_attrData[0].isBO) {
            CPlatform::context()->bindBuffer(GL_ARRAY_BUFFER, m_attrData[0].buffer);
        } else {
            CPlatform::context()->bindBuffer(GL_ARRAY_BUFFER, 0);
        }
        for(int i = 0; i < FG_GFX_ATTRIBUTE_COUNT; i++) {
            if(m_attrData[i].isEnabled) {
                if(m_attrData[i].isInterleaved == FG_FALSE && m_attrData[i].isBO) {
                    CPlatform::context()->bindBuffer(GL_ARRAY_BUFFER, m_attrData[i].buffer);
                }
                CPlatform::context()->vertexAttribPointer(m_attrData[i].index,
                                                          m_attrData[i].size,
                                                          m_attrData[i].dataType,
                                                          m_attrData[i].isNormalized,
                                                          m_attrData[i].stride,
                                                          m_attrData[i].offset);
            }
        }
        if(m_drawingInfo.buffer) {
            CPlatform::context()->bindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_drawingInfo.buffer);
        } else {
            CPlatform::context()->bindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    } else {
        return FG_FALSE;
    }
    return FG_TRUE;
}

/*
 *
 */
void gfx::CDrawCall::draw(void) {
    if(!m_vecDataBase && m_drawCallType == FG_GFX_DRAW_CALL_CUSTOM_ARRAY) // ? ?
        return;
    fgBool scissorSet = FG_FALSE;
    if(m_scissorBox.z != 0 && m_scissorBox.w != 0) {
        // If scissor box has some kind of size then...
        CPlatform::context()->scissor(m_scissorBox);
        scissorSet = FG_TRUE;
    }
    if(m_MVP && m_program) {
        // force use program?
        m_program->use();
        //m_MVP->calculate(m_modelMat);
        m_program->setUniform(m_MVP);
    }
    if(m_program) {
        if(CPlatform::context()->isTexture(m_textureID.id)) {
            CPlatform::context()->bindTexture(m_textureID);
            m_program->setUniform(FG_GFX_USE_TEXTURE, 1.0f);
        } else {
            m_program->setUniform(FG_GFX_USE_TEXTURE, 0.0f);
        }
    }
    // #FIXME - need to use attribute data array
    //fgGfxPrimitives::drawArray2D(m_vecDataBase, m_attribMask, m_primMode);
    if(m_drawCallType == FG_GFX_DRAW_CALL_CUSTOM_ARRAY) {
        m_vecDataBase->refreshAttributes(m_attrData);
        m_drawingInfo.count = m_vecDataBase->size();
    }
    // Will now draw data from Other types ...
    if(applyAttributeData()) {
        if(m_material) {
            CPlatform::context()->setCullFace(m_material->isCullFace());
            CPlatform::context()->setDepthTest(m_material->isDepthTest());
            CPlatform::context()->setBlend(m_material->isBlend());
            CPlatform::context()->frontFace((fgGFXenum)m_material->getGfxFrontFace());
            CPlatform::context()->setCapability(gfx::DEPTH_WRITEMASK, m_material->isDepthWriteMask());
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
        CPlatform::context()->bindBuffer(GL_ARRAY_BUFFER, 0);
        CPlatform::context()->bindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    if(scissorSet) //FIXME
    {
        // Reset the scissor box
        CPlatform::context()->scissor();
    }
}
