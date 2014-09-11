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
#include "Util/fgFile.h"

/*
 *
 */
class fgGfxShader : protected fgFile
{
public:
	typedef fgArrayVector<std::string>	defineStrVec;
	typedef defineStrVec::iterator		defineStrVecItor;
	typedef fgArrayVector<std::string>	includeStrVec;
	typedef includeStrVec::iterator		includeStrVecItor;
protected:
	///
	fgGFXuint m_shaderGfxID;
	///
	fgGfxShaderType m_type;
	///
	defineStrVec m_defineStrVec;
	///
	includeStrVec m_includeStrVec;
	///
	fgGfxShadingLanguageVersion m_version;
	///
	std::string m_log;
	///
	int m_numSources;
	///
	char const ** m_sources;
	///
	char * m_fileSource;
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
	//
	fgBool attach(fgGFXuint program);
	//
	fgBool detach(fgGFXuint program);

	//
	fgBool setFilePath(std::string & path);
	//
	fgBool setFilePath(const char *path);

	//
	fgGFXuint getGfxID(void) const {
		return m_shaderGfxID;
	}
	//
	const char *getLog(void) const {
		return m_log.c_str();
	}

	const char *getSource(void) const {
		return (const char *)m_fileSource;
	}
protected:
	void _updateShaderLog(void);
};

#endif /* _FG_GFX_SHADER_H_ */
