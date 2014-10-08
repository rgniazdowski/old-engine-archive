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
fgGfxDrawCall::fgGfxDrawCall() : 
	m_vecDataBase(NULL),
	m_program(NULL),
	m_texture(NULL),
	m_MVP(NULL),
	m_attribMask(FG_GFX_POSITION_BIT | FG_GFX_UVS_BIT),
	m_drawCallType(FG_GFX_DRAW_CALL_CUSTOM_ARRAY),
	m_drawAppendMode(FG_GFX_DRAW_APPEND_ABSOLUTE),
	m_primMode(FG_GFX_TRIANGLES),
	m_zIndex(0)
{
	m_attrData[FG_GFX_ATTRIB_POS_LOCATION].index = FG_GFX_ATTRIB_POS_LOCATION;
	m_attrData[FG_GFX_ATTRIB_POS_LOCATION].size = 3;
	m_attrData[FG_GFX_ATTRIB_POS_LOCATION].type = FG_GFX_POSITION;
	m_attrData[FG_GFX_ATTRIB_POS_LOCATION].dataType = FG_GFX_FLOAT;
	m_attrData[FG_GFX_ATTRIB_POS_LOCATION].stride = sizeof(fgVertex3);
	m_attrData[FG_GFX_ATTRIB_POS_LOCATION].isEnabled = FG_TRUE;

	m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].index = FG_GFX_ATTRIB_NORM_LOCATION;
	m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].size = 3;
	m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].type = FG_GFX_NORMAL;
	m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].dataType = FG_GFX_FLOAT;
	m_attrData[FG_GFX_ATTRIB_NORM_LOCATION].stride = sizeof(fgVertex3);
	m_attrData[FG_GFX_ATTRIB_POS_LOCATION].isEnabled = FG_FALSE;

	m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].index = FG_GFX_ATTRIB_UVS_LOCATION;
	m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].size = 2;
	m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].type = FG_GFX_TEXTURE_COORD;
	m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].dataType = FG_GFX_FLOAT;
	m_attrData[FG_GFX_ATTRIB_UVS_LOCATION].stride = sizeof(fgVertex3);
	m_attrData[FG_GFX_ATTRIB_POS_LOCATION].isEnabled = FG_TRUE;

	m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].index = FG_GFX_ATTRIB_COLOR_LOCATION;
	m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].size = 4;
	m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].type = FG_GFX_COLOR;
	m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].dataType = FG_GFX_FLOAT;
	m_attrData[FG_GFX_ATTRIB_COLOR_LOCATION].stride = sizeof(fgVertex4);
	m_attrData[FG_GFX_ATTRIB_POS_LOCATION].isEnabled = FG_FALSE;

	m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].index = FG_GFX_ATTRIB_TANGENT_LOCATION;
	m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].size = 3;
	m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].type = FG_GFX_TANGENT;
	m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].dataType = FG_GFX_FLOAT;
	m_attrData[FG_GFX_ATTRIB_TANGENT_LOCATION].stride = 0; // Stride when using tangent?
	m_attrData[FG_GFX_ATTRIB_POS_LOCATION].isEnabled = FG_FALSE;

	setupVertexData(m_attribMask);
	m_color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

/*
 *
 */
fgGfxDrawCall::~fgGfxDrawCall()
{
	m_program = NULL;
	m_texture = NULL;
	m_MVP = NULL;
	if(m_vecDataBase) {
		m_vecDataBase->clear();
		delete m_vecDataBase;
	}
	m_vecDataBase = NULL;
}

/*
 *
 */
void fgGfxDrawCall::setupVertexData(fgGFXuint attribMask)
{
	if(!attribMask)
		return;
	if(m_vecDataBase) {
		if(attribMask != m_vecDataBase->attribMask()) {
			m_vecDataBase->clear();
			delete m_vecDataBase;
			m_vecDataBase = NULL;
		} else {
			return;
		}
	}

	if(attribMask & FG_GFX_COLOR_BIT) {
		m_vecDataBase = new fgVertexData4();
	} else if(attribMask & FG_GFX_NORMAL_BIT) {
		m_vecDataBase = new fgVertexData3();
	} else {
		m_vecDataBase = new fgVertexData2();
	}
}

/*
 *
 */
int fgGfxDrawCall::getZIndex(void) const
{
	return m_zIndex;
}

/*
 *
 */
fgGfxAttributeData* fgGfxDrawCall::getAttributeData(void)
{
	return m_attrData;
}

/*
 *
 */
fgGFXuint fgGfxDrawCall::getAttribMask(void) const
{
	return m_attribMask;
}

/*
 *
 */
fgGfxDrawCallType fgGfxDrawCall::getDrawCallType(void) const
{
	return m_drawCallType;
}

/*
 *
 */
fgGfxDrawAppendMode fgGfxDrawCall::getDrawAppendMode(void) const
{
	return m_drawAppendMode;
}

/*
 *
 */
fgGfxPrimitiveMode fgGfxDrawCall::getPrimitiveMode(void) const
{
	return m_primMode;
}

/*
 *
 */
void fgGfxDrawCall::setZIndex(const int zIndex)
{
	m_zIndex = zIndex;
}

/*
 *
 */
void fgGfxDrawCall::upZIndex(void)
{
	m_zIndex++;
}

/*
 *
 */
void fgGfxDrawCall::downZIndex(void)
{
	m_zIndex--;
}

/*
 *
 */
void fgGfxDrawCall::setDrawCallType(const fgGfxDrawCallType type)
{
	m_drawCallType = type;
}

/*
 *
 */
void fgGfxDrawCall::setDrawAppendMode(const fgGfxDrawAppendMode mode)
{
	m_drawAppendMode = mode;
}

/*
 *
 */
void fgGfxDrawCall::setPrimitiveMode(const fgGfxPrimitiveMode mode)
{
	m_primMode = mode;
}


/*
 * Whether to set UVs, normals or colors active
 */
void fgGfxDrawCall::setComponentActive(unsigned int component)
{
	if(!component)
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
void fgGfxDrawCall::setColor(const fgColor3f& color)
{
	m_color = fgColor4f(color.r, color.g, color.b, 1.0f);
}

/*
 *
 */
void fgGfxDrawCall::setColor(const fgColor4f& color)
{
	m_color = color;
}

/*
 *
 */
void fgGfxDrawCall::resetColor(void)
{
	m_color = fgColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

/*
 *
 */
void fgGfxDrawCall::setMVP(fgGfxMVPMatrix *MVP)
{
	m_MVP = MVP;
}

/*
 *
 */
fgGfxMVPMatrix *fgGfxDrawCall::getMVP(void) const
{
	return m_MVP;
}


/*
 * Can be null, which would mean that this draw call does not care about such thing
 * However it should be avoided. Shader program knows if it's being currently used.
 * Also only through shader manager given shader program can be set as active.
 */
void fgGfxDrawCall::setShaderProgram(fgGfxShaderProgram *pProgram)
{
	m_program = pProgram;
}

/*
 *
 */
fgGfxShaderProgram *fgGfxDrawCall::getShaderProgram(void) const
{
	return m_program;
}


/*
 *
 */
void fgGfxDrawCall::setTexture(fgTextureResource *texture)
{
	m_texture = texture;
}

/*
 *
 */
fgTextureResource *fgGfxDrawCall::getTexture(void) const
{
	return m_texture;
}
	

/*
 * Clear the buffers
 */
void fgGfxDrawCall::flush(void)
{
	m_relMove = fgVector3f(0.0f, 0.0f, 0.0f);
	m_modelMat = fgMatrix4f();
	if(m_vecDataBase)
		m_vecDataBase->clear();
	m_zIndex = 0;
}


/*
 * Append simple rectangle next to the last one
 */
void fgGfxDrawCall::appendRect2D(const fgVec2f &size,
	const fgVec2f &uv1, const fgVec2f &uv2, 
	const fgBool rewind)
{
	fgGfxPrimitives::appendRect2D(m_vecDataBase, fgVec2f(0.0f, 0.0f), size, uv1, uv2, m_color, m_primMode, rewind);
}

/*
 *
 */
void fgGfxDrawCall::appendRect2D(const fgVec2f &relPos, const fgVec2f &size,
	const fgVec2f &uv1, const fgVec2f &uv2, 
	const fgBool rewind)
{
	fgVec2f pos(relPos.x, relPos.y);
	if(m_drawAppendMode == FG_GFX_DRAW_APPEND_RELATIVE) {
		pos.x+=m_relMove.x;
		pos.y+=m_relMove.y;
		m_relMove.x+=size.x;
		m_relMove.y+=size.y;
	}
	fgGfxPrimitives::appendRect2D(m_vecDataBase, pos, size, uv1, uv2, m_color, m_primMode, rewind);
}

/*
 *
 */
void fgGfxDrawCall::draw(void)
{
	if(!m_vecDataBase)
		return;
	if(m_MVP && m_program) {
		m_MVP->calculate(m_modelMat);
		m_program->setUniform(m_MVP);
	}
	if(m_vecDataBase->attribMask() & FG_GFX_COLOR_BIT && m_vecDataBase->size())
	{
		fgVertexData4 *vData = (fgVertexData4 *)m_vecDataBase;
		if(vData->begin()->color.a < 1.0f) {
			fgGfxPlatform::context()->blendFunc(GL_SRC_ALPHA, GL_ONE);
		} else {
			fgGfxPlatform::context()->blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
	} else {
		fgGfxPlatform::context()->blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	if(m_texture) {
	//if(m_program && m_texture) {
		// CHECK FOR ACTIVE TEXTURE ID
		// NEED GL STATE GHRHDFHASDH
		fgGfxPlatform::context()->bindTexture2D(m_texture->getTextureGfxID());
		if(m_program)
			m_program->setUniform(FG_GFX_USE_TEXTURE, 1.0f);
		
	} else if(m_program) {
		m_program->setUniform(FG_GFX_USE_TEXTURE, 0.0f);
	}
	//fgGfxPlatform::context()->setBlend(FG_FALSE);
	fgGfxPrimitives::drawArray2D(m_vecDataBase, m_attribMask, m_primMode);
	//fgGfxPlatform::context()->setBlend(FG_TRUE);
}

/*
 *
 */
void fgGfxDrawCall::draw(const fgVec2f& relPos)
{
	if(m_MVP && m_program) {
		m_modelMat = fgMath::translate(fgMatrix4f(), fgVec3f(relPos.x, relPos.y, 0.0f));
	}
	fgGfxDrawCall::draw();
}

/*
 *
 */
void fgGfxDrawCall::draw(const fgVec3f& relPos)
{
	if(m_MVP && m_program) {
		m_modelMat = fgMath::translate(fgMatrix4f(), relPos);
	}
	fgGfxDrawCall::draw();
}

/*
 *
 */
void fgGfxDrawCall::draw(const fgMatrix4f& modelMat)
{
	if(m_MVP) {
		m_modelMat = modelMat;
	}
	fgGfxDrawCall::draw();
}
