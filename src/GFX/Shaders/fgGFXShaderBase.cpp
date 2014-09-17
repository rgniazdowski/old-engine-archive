/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXShaderBase.h"
#include "Util/fgMemory.h"
#include "fgLog.h"

/*
 *
 */
fgGfxShaderBase::fgGfxShaderBase() :
	m_log(NULL),
	m_gfxID(0),
	m_baseType(FG_GFX_BASE_TYPE_INVALID)
{
}

/*
 *
 */
fgGfxShaderBase::~fgGfxShaderBase()
{
	m_params.clear();
	if(m_log)
		fgFree(m_log);
	m_log = NULL;
}

/*
 *
 */
void fgGfxShaderBase::updateLog(void)
{
	if(m_baseType == FG_GFX_BASE_TYPE_INVALID)
		return;
	fgGFXint length;
	if(m_baseType == FG_GFX_BASE_TYPE_SHADER) {
		if(!glIsShader(m_gfxID))
			return;
		glGetShaderiv(m_gfxID, GL_INFO_LOG_LENGTH, &length);
	} else if(m_baseType == FG_GFX_BASE_TYPE_PROGRAM) {
		if(!glIsProgram(m_gfxID))
			return;
		glGetProgramiv(m_gfxID, GL_INFO_LOG_LENGTH, &length);
	}
	if(length)
	{
		if(m_log)
			fgFree(m_log);
		char *buffer = (char*)fgMalloc(sizeof(char)*length);
		if(m_baseType == FG_GFX_BASE_TYPE_SHADER) {
			glGetShaderInfoLog(m_gfxID, length, NULL, buffer);
		} else if(m_baseType == FG_GFX_BASE_TYPE_PROGRAM) {
			glGetProgramInfoLog(m_gfxID, length, NULL, buffer);
		}
		m_log = buffer;
	}
}

/*
 *
 */
void fgGfxShaderBase::updateParams(void)
{
	if(m_baseType == FG_GFX_BASE_TYPE_INVALID) {
		return;
	}
	GLint value;
	objParamMapItor begin, end, itor;
	begin = m_params.begin(); end = m_params.end();	itor = begin;
	for(;itor!=end;itor++) {
		if(m_baseType == FG_GFX_BASE_TYPE_SHADER) {
			glGetShaderiv(m_gfxID, (fgGFXenum)itor->first, &value);
		} else if(m_baseType == FG_GFX_BASE_TYPE_PROGRAM) {
			glGetProgramiv(m_gfxID, (fgGFXenum)itor->first, &value);
		} else {
			continue;
		}
		itor->second = value;
	}
}

/*
 *
 */
fgGFXint fgGfxShaderBase::updateParam(fgGFXuint pname)
{
	if(m_baseType == FG_GFX_BASE_TYPE_INVALID)
		return 0;
	fgGFXint value = 0;
	if(m_baseType == FG_GFX_BASE_TYPE_SHADER && glIsShader(m_gfxID)) {
		glGetShaderiv(m_gfxID, (fgGFXenum)pname, &value);
	} else if(m_baseType == FG_GFX_BASE_TYPE_PROGRAM && glIsProgram(m_gfxID)) {
		glGetProgramiv(m_gfxID, (fgGFXenum)pname, &value);
	} 
	m_params[pname] = value;
	return value;
}
