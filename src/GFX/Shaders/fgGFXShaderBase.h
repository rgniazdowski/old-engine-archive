/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_SHADER_BASE_H_
#define _FG_GFX_SHADER_BASE_H_

#include "fgGFXShaderDefs.h"
#include <map>

/*
 *
 */
class fgGfxShaderBase
{
	friend class fgGfxShaderProgram;
protected:
	typedef std::map<fgGFXuint, fgGFXint>	objParamMap;
	typedef objParamMap::iterator			objParamMapItor;

	enum shaderBaseType {
		FG_GFX_BASE_TYPE_INVALID	= 0,
		FG_GFX_BASE_TYPE_SHADER		= 1,
		FG_GFX_BASE_TYPE_PROGRAM	= 2
	};

protected:
	shaderBaseType m_baseType;
	///
	fgGFXuint	m_gfxID;
	///
	objParamMap	m_params;
	///
	std::string m_log;

public:
	//
	fgGfxShaderBase();
	// 
	virtual ~fgGfxShaderBase();

	// 
	fgGFXuint getGfxID(void) const {
		return m_gfxID;
	}

	//
	fgGFXint getParam(fgGFXuint pname) {
		return m_params[pname];
	}

	//
	const char *getLog(void) const {
		return m_log.c_str();
	}

protected:
	//
	void _updateLog(void);
	//
	void _updateParams(void);
	//
	fgGFXint _updateParam(fgGFXuint pname);
};

#endif /*_FG_GFX_SHADER_BASE_H_ */
