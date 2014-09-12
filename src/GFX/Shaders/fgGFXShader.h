/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_SHADER_H_
#define _FG_GFX_SHADER_H_

#include "fgGFXShaderDefs.h"
#include "fgGFXShaderBase.h"
#include "Util/fgFile.h"
#include <map>

enum fgGfxShaderObjParamType {
	FG_GFX_SHADER_TYPE				= GL_SHADER_TYPE,
	FG_GFX_SHADER_DELETE_STATUS		= GL_DELETE_STATUS,
	FG_GFX_SHADER_COMPILE_STATUS	= GL_COMPILE_STATUS,
	FG_GFX_SHADER_INFO_LOG_LENGTH	= GL_INFO_LOG_LENGTH,
	FG_GFX_SHADER_SOURCE_LENGTH		= GL_SHADER_SOURCE_LENGTH
};

/*
 *
 */
class fgGfxShader : protected fgGfxShaderBase, protected fgFile
{
	friend class fgGfxShaderProgram;
public:
	typedef fgArrayVector<std::string>	defineStrVec;
	typedef defineStrVec::iterator		defineStrVecItor;
	typedef fgArrayVector<std::string>	includeStrVec;
	typedef includeStrVec::iterator		includeStrVecItor;

protected:
	///
	fgGfxShaderType m_type;
	///
	defineStrVec m_defineStrVec;
	///
	includeStrVec m_includeStrVec;
	///
	fgGfxShadingLanguageVersion m_version;
	///
	int m_numSources;
	///
	char const ** m_sources;
	///
	char * m_fileSource;
	///
	fgGfxShaderPrecision m_precision;
	///
	fgBool m_isSourceLoaded;
public:
	// 
	fgGfxShader(fgGfxShaderType type);
	//
	virtual ~fgGfxShader();

	//
	fgBool setVersion(fgGfxShadingLanguageVersion slVer);
	//
	void appendDefine(fgGfxShaderConstantDef constantDef);
	//
	void appendInclude(std::string & includeName);

	//
	fgBool loadSource(void);
	//
	fgBool loadSource(const char *path);
	//
	fgBool loadSource(std::string & path);
	//
	void freeSource(void);

	//
	fgGFXuint create(void);
	//
	fgBool compile(void);
	//
	fgBool compile(const char *path);
	//
	fgBool compile(std::string & path);
	//
	fgBool deleteShader(void);

protected:
	//
	fgBool attach(fgGFXuint program);
	//
	fgBool detach(fgGFXuint program);

public:
	//
	fgBool setFilePath(std::string & path);
	//
	fgBool setFilePath(const char *path);

	//
	void setPrecision(fgGfxShaderPrecision precision) {
		m_precision = precision;
	}
	//
	fgGfxShaderPrecision getPrecision(void) const {
		return m_precision;
	}

	//
	const char *getSource(void) const {
		return (const char *)m_fileSource;
	}
};

#endif /* _FG_GFX_SHADER_H_ */
