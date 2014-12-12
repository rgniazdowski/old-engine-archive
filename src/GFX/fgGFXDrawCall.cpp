/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXDrawCall.h"

/*
 *
 */
fgGfxDrawCall::fgGfxDrawCall(const fgGfxDrawCallType type, const fgGFXuint attribMask) :
fgGfxDrawable(FG_GFX_DRAWABLE_DRAWCALL),
m_vecDataBase(NULL),
m_vecData2v(NULL),
m_vecData3v(NULL),
m_vecData4v(NULL),
m_program(NULL),
m_textureID(),
m_MVP(NULL),
m_attribMask(attribMask),
m_drawCallType(type),
m_drawAppendMode(FG_GFX_DRAW_APPEND_ABSOLUTE),
m_primMode(fgGfxPrimitiveMode::FG_GFX_TRIANGLES),
m_color(1.0f, 1.0f, 1.0f, 1.0f),
m_relMove(0.0f, 0.0f, 0.0f),
m_fastCmp(4, fg::util::FastCmp::CMP_DATA_32),
m_zIndex(0),
m_isManaged(0) {
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].index = FG_GFX_ATTRIB_POS_LOCATION;
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].size = 3;
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].type = FG_GFX_POSITION;
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].dataType = FG_GFX_FLOAT;
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].stride = sizeof (fgVertex3v);
    m_attrData[FG_GFX_ATTRIB_POS_LOCATION].isEnabled = FG_GFX_TRUE;

    m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].index = FG_GFX_ATTRIB_NORM_LOCATION;
    m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].size = 3;
    m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].type = FG_GFX_NORMAL;
    m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].dataType = FG_GFX_FLOAT;
    m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].stride = sizeof (fgVertex3v);
    m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].isEnabled = FG_GFX_FALSE;

    m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].index = FG_GFX_ATTRIB_UVS_LOCATION;
    m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].size = 2;
    m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].type = FG_GFX_TEXTURE_COORD;
    m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].dataType = FG_GFX_FLOAT;
    m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].stride = sizeof (fgVertex3v);
    m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].isEnabled = FG_GFX_TRUE;

    m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].index = FG_GFX_ATTRIB_COLOR_LOCATION;
    m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].size = 4;
    m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].type = FG_GFX_COLOR;
    m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].dataType = FG_GFX_FLOAT;
    m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].stride = sizeof (fgVertex4v);
    m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].isEnabled = FG_GFX_FALSE;

    m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].index = FG_GFX_ATTRIB_TANGENT_LOCATION;
    m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].size = 3;
    m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].type = FG_GFX_TANGENT;
    m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].dataType = FG_GFX_FLOAT;
    m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].stride = 0; // Stride when using tangent?
    m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].isEnabled = FG_GFX_FALSE;

    // #FIXME #LOL
    m_vecData2v = new fgVertexData2v();
    m_vecData3v = new fgVertexData3v();
    m_vecData4v = new fgVertexData4v();

    m_vecData2v->reserve(2);
    m_vecData3v->reserve(2);
    m_vecData4v->reserve(2);

    setupVertexData(m_attribMask);
}

/*
 *
 */
fgGfxDrawCall::~fgGfxDrawCall() {
    m_program = NULL;
    m_MVP = NULL;
    if(m_vecData2v) {
        m_vecData2v->clear();
        delete m_vecData2v;
    }
    if(m_vecData3v) {
        m_vecData3v->clear();
        delete m_vecData3v;
    }
    if(m_vecData4v) {
        m_vecData4v->clear();
        delete m_vecData4v;
    }
    m_vecDataBase = NULL;
}

/**
 * 
 * @param toggle
 */
void fgGfxDrawCall::setManaged(const fgBool toggle) {
    m_isManaged = toggle;
}

/**
 * 
 * @return 
 */
fgBool fgGfxDrawCall::isManaged() const {
    return m_isManaged;
}

/*
 *
 */
void fgGfxDrawCall::setupVertexData(fgGFXuint attribMask) {
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
void fgGfxDrawCall::setupFromMesh(const fgGfxMeshBase* pMesh) {
    if(!pMesh)
        return;
    pMesh->setupAttributes(m_attrData);
    m_drawCallType = FG_GFX_DRAW_CALL_MESH;
    m_attribMask = pMesh->attribMask();
    m_fastCmp.setPart(0, (fg::util::FastCmp::data_type_32)m_attribMask);
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

/*
 *
 */
int fgGfxDrawCall::getZIndex(void) const {
    return m_zIndex;
}

/*
 *
 */
fgGfxAttributeData* fgGfxDrawCall::getAttributeData(void) {
    return m_attrData;
}

/*
 *
 */
fgGFXuint fgGfxDrawCall::getAttribMask(void) const {
    return m_attribMask;
}

/*
 *
 */
fgGfxDrawCallType fgGfxDrawCall::getDrawCallType(void) const {
    return m_drawCallType;
}

/*
 *
 */
fgGfxDrawAppendMode fgGfxDrawCall::getDrawAppendMode(void) const {
    return m_drawAppendMode;
}

/*
 *
 */
fgGfxPrimitiveMode fgGfxDrawCall::getPrimitiveMode(void) const {
    return m_primMode;
}

/**
 * 
 * @return 
 */
fgVertexData *fgGfxDrawCall::getVertexData(void) const {
    return m_vecDataBase;
}

/*
 *
 */
void fgGfxDrawCall::setZIndex(const int zIndex) {
    m_zIndex = zIndex;
    m_fastCmp.setPart(2, (fg::util::FastCmp::data_type_32)m_zIndex);
}

/*
 *
 */
void fgGfxDrawCall::upZIndex(void) {
    m_zIndex++;
    m_fastCmp.setPart(2, (fg::util::FastCmp::data_type_32)m_zIndex);
}

/*
 *
 */
void fgGfxDrawCall::downZIndex(void) {
    m_zIndex--;
    m_fastCmp.setPart(2, (fg::util::FastCmp::data_type_32)m_zIndex);
}

/*
 *
 */
void fgGfxDrawCall::setDrawCallType(const fgGfxDrawCallType type) {
    m_drawCallType = type;
}

/*
 *
 */
void fgGfxDrawCall::setDrawAppendMode(const fgGfxDrawAppendMode mode) {
    m_drawAppendMode = mode;
}

/*
 *
 */
void fgGfxDrawCall::setPrimitiveMode(const fgGfxPrimitiveMode mode) {
    m_primMode = mode;
}

/*
 * Whether to set UVs, normals or colors active
 */
void fgGfxDrawCall::setComponentActive(unsigned int component, const fgBool reset) {
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
void fgGfxDrawCall::setColor(const fgColor3f& color) {
    m_color = fgColor4f(color.r, color.g, color.b, 1.0f);
}

/*
 *
 */
void fgGfxDrawCall::setColor(const fgColor4f& color) {
    m_color = color;
}

/*
 *
 */
void fgGfxDrawCall::resetColor(void) {
    m_color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

/*
 *
 */
void fgGfxDrawCall::setMVP(fgGfxMVPMatrix *MVP) {
    m_MVP = MVP;
}

/*
 *
 */
fgGfxMVPMatrix *fgGfxDrawCall::getMVP(void) const {
    return m_MVP;
}

/*
 * Can be null, which would mean that this draw call does not care about such thing
 * However it should be avoided. Shader program knows if it's being currently used.
 * Also only through shader manager given shader program can be set as active.
 */
void fgGfxDrawCall::setShaderProgram(fgGfxShaderProgram *pProgram) {
    m_program = pProgram;
    if(m_program)
        m_fastCmp.setPart(3, (fg::util::FastCmp::data_type_32)m_program->getHandle().getIndex());
    else
        m_fastCmp.setPart(3, (fg::util::FastCmp::data_type_32)0);
    
}

/*
 *
 */
fgGfxShaderProgram *fgGfxDrawCall::getShaderProgram(void) const {
    return m_program;
}

/*
 *
 */
void fgGfxDrawCall::setTexture(const fgGfxTextureID& textureID) {
    m_textureID = textureID;
    m_fastCmp.setPart(1, (fg::util::FastCmp::data_type_32)m_textureID.id);
}

/*
 *
 */
fgGfxTextureID const & fgGfxDrawCall::getTexture(void) const {
    return m_textureID;
}

/*
 *
 */
fgGfxTextureID& fgGfxDrawCall::getTexture(void) {
    return m_textureID;
}

/*
 * Clear the buffers
 */
void fgGfxDrawCall::flush(void) {
    m_relMove = fgVector3f(0.0f, 0.0f, 0.0f);
    if(m_vecDataBase)
        m_vecDataBase->clear();
    m_zIndex = 0;
}

/*
 * Append simple rectangle next to the last one
 */
void fgGfxDrawCall::appendRect2D(const fgVec2f &size,
                                 const fgVec2f &uv1, const fgVec2f &uv2,
                                 const fgBool rewind) {
    // #FIXME - TOO DEEP CALL 
    fgGfxPrimitives::appendRect2D(m_vecDataBase, fgVec2f(0.0f, 0.0f), size, uv1, uv2, m_color, m_primMode, rewind);
}

/*
 *
 */
void fgGfxDrawCall::appendRect2D(const fgVec2f &relPos, const fgVec2f &size,
                                 const fgVec2f &uv1, const fgVec2f &uv2,
                                 const fgBool rewind) {
    fgVec2f pos(relPos.x, relPos.y);
    if(m_drawAppendMode == FG_GFX_DRAW_APPEND_RELATIVE) {
        pos.x += m_relMove.x;
        pos.y += m_relMove.y;
        m_relMove.x += size.x;
        m_relMove.y += size.y;
    }
    // #FIXME - TOO DEEP CALL
    fgGfxPrimitives::appendRect2D(m_vecDataBase, pos, size, uv1, uv2, m_color, m_primMode, rewind);
}

/**
 * 
 */
fgBool fgGfxDrawCall::applyAttributeData(void) {
    if(m_drawCallType == FG_GFX_DRAW_CALL_MESH ||
       m_drawCallType == FG_GFX_DRAW_CALL_CUSTOM_ARRAY) {
        fgGfxPlatform::context()->diffVertexAttribArrayMask(m_attribMask);
        if(m_attrData[0].isInterleaved == FG_TRUE && m_attrData[0].isBO) {
            fgGfxPlatform::context()->bindBuffer(GL_ARRAY_BUFFER, m_attrData[0].buffer);
        } else {
            fgGfxPlatform::context()->bindBuffer(GL_ARRAY_BUFFER, 0);
        }
        for(int i = 0; i < FG_GFX_ATTRIBUTE_COUNT; i++) {
            if(m_attrData[i].isEnabled) {
                if(m_attrData[i].isInterleaved == FG_FALSE && m_attrData[i].isBO) {
                    fgGfxPlatform::context()->bindBuffer(GL_ARRAY_BUFFER, m_attrData[i].buffer);
                }
                fgGfxPlatform::context()->vertexAttribPointer(m_attrData[i].index,
                                                              m_attrData[i].size,
                                                              m_attrData[i].dataType,
                                                              m_attrData[i].isNormalized,
                                                              m_attrData[i].stride,
                                                              m_attrData[i].offset);
            }
        }
        if(m_drawingInfo.buffer) {
            fgGfxPlatform::context()->bindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_drawingInfo.buffer);
        } else {
            fgGfxPlatform::context()->bindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    } else {
        return FG_FALSE;
    }
    return FG_TRUE;
}

/*
 *
 */
void fgGfxDrawCall::draw(void) {
    if(!m_vecDataBase && m_drawCallType == FG_GFX_DRAW_CALL_CUSTOM_ARRAY) // ? ?
        return;
    if(m_MVP && m_program) {
        //m_MVP->calculate(m_modelMat);
        m_program->setUniform(m_MVP);
    }
    if(m_program) {
        if(m_textureID.id) {
            fgGfxPlatform::context()->bindTexture(m_textureID);
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
        // attribute data array is set
        // unsigned short is mainly because of ES
        if(m_drawingInfo.buffer) {
            glDrawElements((fgGFXenum)m_primMode, m_drawingInfo.count, GL_UNSIGNED_SHORT, m_drawingInfo.indices.pointer);
        } else {
            // #FIXME
            glDrawArrays((fgGFXenum)m_primMode, 0, m_drawingInfo.count);
        }
        // #FIXME
        fgGfxPlatform::context()->bindBuffer(GL_ARRAY_BUFFER, 0);
        fgGfxPlatform::context()->bindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
