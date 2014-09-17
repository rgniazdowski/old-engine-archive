/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXShader.h"
#include "GFX/fgGFXErrorCodes.h"
#include "Util/fgMemory.h"
#include "fgLog.h"

/*
 *
 */
fgGfxShader::fgGfxShader(fgGfxShaderType type) :
	m_type(type),
	m_version(FG_GFX_SHADING_LANGUAGE_INVALID),
	m_numSources(0),
	m_sources(NULL),
	m_fileSource(NULL),
	m_precision(FG_GFX_SHADER_PRECISION_DEFAULT),
	m_isSourceLoaded(FG_FALSE)
{
	if(m_type == FG_GFX_SHADER_INVALID)
		reportError(FG_ERRNO_GFX_SHADER_WRONG_TYPE);
	m_params[(fgGFXuint)FG_GFX_SHADER_TYPE] = m_type;
	m_params[(fgGFXuint)FG_GFX_SHADER_DELETE_STATUS] = 0;
	m_params[(fgGFXuint)FG_GFX_SHADER_COMPILE_STATUS] = 0;
	m_params[(fgGFXuint)FG_GFX_SHADER_INFO_LOG_LENGTH] = 0;
	m_params[(fgGFXuint)FG_GFX_SHADER_SOURCE_LENGTH] = 0;
	m_baseType = FG_GFX_BASE_TYPE_SHADER;
}

/*
 *
 */
fgGfxShader::~fgGfxShader()
{
	freeSource();
	m_defineStrVec.clear_optimised();
	m_includeStrVec.clear_optimised();
	m_params.clear();
	deleteShader();
}

/*
 *
 */
fgBool fgGfxShader::setVersion(fgGfxShadingLanguageVersion slVer)
{
	if(slVer != FG_GFX_SHADING_LANGUAGE_INVALID)
		m_version = slVer;
	else
		return FG_FALSE;
	return FG_TRUE;
}

/*
 *
 */
void fgGfxShader::appendDefine(fgGfxShaderConstantDef constantDef)
{
	std::string defStr;
	constantDef.toString(defStr);
	defStr.append("\n");
	m_defineStrVec.push_back(defStr);
}

/*
 *
 */
void fgGfxShader::appendInclude(std::string & includeName)
{
	if(!includeName.empty())
		m_includeStrVec.push_back(includeName);
}

/*
 *
 */
fgBool fgGfxShader::loadSource(void)
{
	fgFile::clearStatus();
	if(getFilePath().empty()) {
		reportWarning(FG_ERRNO_WRONG_PATH);
		return FG_FALSE;
	}
	if(m_version == FG_GFX_SHADING_LANGUAGE_INVALID) {
		reportError(FG_ERRNO_GFX_SHADER_INVALID_SLVER);
		return FG_FALSE;
	}
	// do not reload the source (will need to attach again the rest of the defines / sources)
	if(m_isSourceLoaded || m_sources) {
		return FG_TRUE;
	}

	m_fileSource = fgFile::load(getFilePath().c_str());
	if(!m_fileSource) {
		return FG_FALSE; // PROPER ERROR CODE
	}

	m_numSources = (int)m_includeStrVec.size()+m_defineStrVec.size()+2;
	m_sources = (char const **)fgMalloc(sizeof(char *) * (m_numSources));
	if(!m_sources) {
		//reportError(
		return FG_FALSE;
	}
	std::string _version;
	_version.append("#version ");
	if(m_version == FG_GFX_ESSL_100)
		_version.append("100 es\n");
	m_sources[0] = _version.c_str();
	int n = 1;
	// include constant definitions (#define) into the shader source
	for(int i=0;i<(int)m_defineStrVec.size();i++,n++) {
		m_sources[n] = m_defineStrVec[i].c_str();
	}
	// append additional includes (these are structure definitions)
	for(int i=0;i<(int)m_includeStrVec.size();i++,n++) {
		m_sources[n] = "\n"; // #FIXME
	}
	m_sources[n] = m_fileSource;
	n++;
	m_isSourceLoaded = FG_TRUE;
	return FG_TRUE;
}

/*
 *
 */

fgBool fgGfxShader::loadSource(const char *path)
{
	setFilePath(path);
	fgFile::setPath(path);
	return loadSource();
}

/*
 *
 */
fgBool fgGfxShader::loadSource(std::string & path)
{
	setFilePath(path);
	fgFile::setPath(path);
	return loadSource();
}

/*
 *
 */
void fgGfxShader::freeSource(void)
{
	
	if(m_fileSource)
		fgFree(m_fileSource);
	m_fileSource = NULL;
	if(m_sources)
		fgFree(m_sources);
	m_sources = NULL;
	m_isSourceLoaded = FG_FALSE;
	m_numSources = 0;
}

/*
 *
 */
fgGFXuint fgGfxShader::create(void)
{
	if(m_type == FG_GFX_SHADER_INVALID)
		return 0;
	if(!m_gfxID || !glIsShader(m_gfxID)) {
		m_gfxID = glCreateShader((fgGFXenum)m_type);
	}
	return m_gfxID;
}

/*
 *
 */
fgBool fgGfxShader::compile(void)
{
	fgFile::clearStatus();
	if(!m_isSourceLoaded) {
		if(!loadSource()) {
			reportError(FG_ERRNO_EIO, "Failed to load shader source file.");
			// Failed to load shader source
			return FG_FALSE;
		}
	}
	if(!create()) {
		// Failed to create shader
		FG_LOG::PrintError("Failed to create shader");
		return FG_FALSE;
	}
	glShaderSource(m_gfxID, m_numSources, m_sources, NULL);
	glCompileShader(m_gfxID);
	s3eDeviceYield(0);
	updateLog();
	updateParams();
	if(!m_params[FG_GFX_SHADER_COMPILE_STATUS]) {
		FG_LOG::PrintError("GfxShader::compile()  failed -  %s", getFilePath().c_str());
	}
	return (fgBool)m_params[FG_GFX_SHADER_COMPILE_STATUS];
}

/*
 *
 */
fgBool fgGfxShader::compile(const char *path)
{
	if(m_isSourceLoaded || m_fileSource) {
		return FG_FALSE;
	}
	setFilePath(path);
	fgFile::setPath(path);
	return compile();
}

/*
 *
 */
fgBool fgGfxShader::compile(std::string & path)
{
	if(m_isSourceLoaded || m_fileSource) {
		return FG_FALSE;
	}
	setFilePath(path);
	fgFile::setPath(path);
	return compile();
}

/*
 *
 */
fgBool fgGfxShader::deleteShader(void)
{
	if(glIsShader(m_gfxID)) {
		glDeleteShader(m_gfxID);
		updateParams();
		//m_shaderGfxID = 0;
		return FG_TRUE;
	}
	return FG_FALSE;
}

/*
 *
 */
fgBool fgGfxShader::attach(fgGFXuint program)
{
	if(glIsProgram(program) && glIsShader(m_gfxID)) {
		glAttachShader(program, m_gfxID);
		return FG_TRUE;
	}
	return FG_FALSE;
}

/*
 *
 */
fgBool fgGfxShader::detach(fgGFXuint program)
{
	if(glIsProgram(program) && glIsShader(m_gfxID)) {
		glDetachShader(program, m_gfxID);
		return FG_TRUE;
	}
	return FG_FALSE;
}
