/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXShaderProgram.h"
#include "GFX/fgGFXErrorCodes.h"
#include "Util/fgPath.h"
#include "Util/fgStrings.h"

/*
 *
 */
fgGfxShaderProgram::fgGfxShaderProgram() :
	m_config(NULL),
	m_isPreLoaded(FG_FALSE),
	m_isCompiled(FG_FALSE),
	m_isLinked(FG_FALSE)
{
	// this needs to depend on some global array GFX config
	m_shaders.reserve(6);
	for(int i=0;i<(int)m_shaders.capacity();i++) {
		m_shaders.push_back(NULL);
	}
	m_params[(fgGFXuint)FG_GFX_PROGRAM_DELETE_STATUS]		= 0;
	m_params[(fgGFXuint)FG_GFX_PROGRAM_LINK_STATUS]			= 0;
	m_params[(fgGFXuint)FG_GFX_PROGRAM_VALIDATE_STATUS]		= 0;
	m_params[(fgGFXuint)FG_GFX_PROGRAM_INFO_LOG_LENGTH]		= 0;
	m_params[(fgGFXuint)FG_GFX_PROGRAM_ATTACHED_SHADERS]	= 0;
	m_params[(fgGFXuint)FG_GFX_PROGRAM_ACTIVE_ATTRIBUTES]	= 0;
	m_params[(fgGFXuint)FG_GFX_PROGRAM_ACTIVE_ATTRIBUTE_MAX_LENGTH] = 0;
	m_params[(fgGFXuint)FG_GFX_PROGRAM_ACTIVE_UNIFORMS]		= 0;
	m_baseType = FG_GFX_BASE_TYPE_PROGRAM;
}

/*
 *
 */
fgGfxShaderProgram::~fgGfxShaderProgram()
{
	if(m_config)
		delete m_config;
	m_config = NULL;

	for(int i=0;i<(int)m_shaders.size();i++) {
		m_shaders[i]->detach(m_gfxID);
		delete m_shaders[i];
		m_shaders[i] = NULL;
	}
	m_uniformBinds.clear_optimised();
	m_attrBinds.clear_optimised();
	m_shaders.clear_optimised();
	deleteProgram();
	m_isLinked = FG_FALSE;
	m_isCompiled = FG_FALSE;
}

/*
 *
 */
fgBool fgGfxShaderProgram::preLoadConfig(const char *path)
{
	clearStatus();
	if(m_isPreLoaded) {
		return FG_FALSE;
	}
	const char *ext = fgPath::fileExt(path, FG_TRUE);
	if(!ext) {
		reportError(FG_ERRNO_WRONG_PATH);
		return FG_FALSE;
	}

	if(strcasecmp(ext, FG_GFX_SHADER_CONFIG_PROGRAM_STD_SUFFIX) != 0) {
		reportError(FG_ERRNO_WRONG_PATH);
		return FG_FALSE;
	}

	if(!m_config) {
		m_config = new fgGfxShaderConfig();
	}

	const char *fileName = fgPath::fileName(path);
	std::string fullPath = path;
	std::string filePathNoExt = fullPath.substr(0, fullPath.length()-1-strlen(ext));
	
	// First load the main shader program config
	if(!m_config->load(path, FG_GFX_ESSL_100)) {
		return FG_FALSE;
	}
	fgGfxShaderConfig::shaderTypeVec shaderTypes = m_config->getRefShaderTypes();
	m_programName = m_config->getProgramName();

	for(int i=0;i<(int)shaderTypes.size();i++) {
		std::string newPath;
		newPath.append(filePathNoExt).append(".").append(FG_GFX_SHADER_STD_SUFFIX(shaderTypes[i]));
		m_config->clearAll();
		if(!m_config->load(newPath.c_str(), FG_GFX_ESSL_100)) {
			return FG_FALSE;
		}
		fgGfxShaderType shaderType = shaderTypes[i];
		int spID = _shaderTypeToSpID(shaderType);
		if(m_shaders[spID]) {
			// ?? shader already initialized lol
		}
		m_shaders[spID] = new fgGfxShader(shaderType);
		fgGfxShader *shader = m_shaders[spID];
		// File quality mapping omg
		// Need to find a way :D for now supporting only one file / quality universal
		// #TODO #FILEMAPPING
		newPath = fgPath::dirName(fullPath);
		newPath.append(m_config->getRefFiles()[0]);
		shader->setFilePath(newPath);
		newPath.clear();
		shader->setVersion(FG_GFX_ESSL_100);
		{
			fgGfxShaderConfig::shaderConstantVec & _vec = m_config->getRefConstants();
			for(int i=0;i<(int)_vec.size();i++)
				shader->appendDefine(_vec[i]);
		}
		{
			fgGfxShaderConfig::shaderIncludeNameVec & _vec = m_config->getRefIncludes();
			for(int i=0;i<(int)_vec.size();i++) {
				shader->appendInclude(_vec[i]);
			}
		}
		_appendAttributeBinds(m_config->getRefAttributeBinds());
		_appendUniformBinds(m_config->getRefUniformBinds());
	}
	m_config->clearAll();
	delete m_config;
	m_config = NULL;
	m_isPreLoaded = FG_TRUE;
	///////////////////////////////////////////////////////
	return FG_TRUE;
}

/*
 *
 */
fgGFXuint fgGfxShaderProgram::create(void)
{
	if(!m_isPreLoaded)
		return 0;
	if(!m_gfxID || !glIsProgram(m_gfxID)) {
		m_gfxID = glCreateProgram();
	}
	return m_gfxID;
}

/*
 *
 */
fgBool fgGfxShaderProgram::compile(void)
{
	if(!m_isPreLoaded) {
		return FG_FALSE;
	}
	create();
	shaderVecItor begin,end,itor;
	begin = m_shaders.begin(), end = m_shaders.end(); itor = begin;
	for(;itor!=end;itor++) {
		if(!(*itor))
			continue;
		fgGfxShader *shader = *itor;
		if(!shader->compile()) {
			//reportError();
			printf("%s\n", shader->getLog());
			return FG_FALSE;
		}
	}
	itor = begin;
	for(;itor!=end;itor++) {
		_attachShader(*itor);
	}
	m_isCompiled = FG_TRUE;
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderProgram::link(void)
{
	if(m_isLinked || !m_isPreLoaded) {
		return FG_FALSE;
	}
	if(!m_isCompiled) {
		if(!compile()) {
			return FG_FALSE;
		}
	}

	if(!bindAttributes()) {
		return FG_FALSE;
	}
	fgBool status = FG_TRUE;
	glLinkProgram(m_gfxID);
	_updateLinkStatus();
	if(!m_params[(fgGFXuint)FG_GFX_PROGRAM_LINK_STATUS]) {
		_updateLog();
		printf("%s\n", getLog());
		return FG_FALSE;
	}
	glValidateProgram(m_gfxID);
	_updateValidateStatus();
	if(!m_params[(fgGFXuint)FG_GFX_PROGRAM_VALIDATE_STATUS]) {
		//Warning?
		status = FG_FALSE;
	}
	_updateParams();
	_updateLog();

	return status;
}

/*
 *
 */
fgBool fgGfxShaderProgram::use(void)
{
	if(!glIsProgram(m_gfxID) || !m_isPreLoaded)
		return FG_FALSE;
	glUseProgram(m_gfxID);
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderProgram::deleteProgram(void)
{
	if(glIsProgram(m_gfxID)) {
		glDeleteProgram(m_gfxID);
		_updateParams();
		return FG_TRUE;
	}
	return FG_FALSE;
}

/*
 *
 */
fgBool fgGfxShaderProgram::_appendUniformBinds(uniformBindVec & binds)
{
	if(binds.empty())
		return FG_FALSE;
	const int imax = binds.size();
	for(int i=0;i<imax;i++) {
		if(m_uniformBinds.contains(binds[i]))
			continue;
		m_uniformBinds.push_back(binds[i]);
	}
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderProgram::_appendAttributeBinds(attributeBindVec & binds)
{
	if(binds.empty())
		return FG_FALSE;
	const int imax = binds.size();
	for(int i=0;i<imax;i++) {
		if(m_attrBinds.contains(binds[i]))
			continue;
		m_attrBinds.push_back(binds[i]);
	}
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderProgram::_attachShader(fgGfxShader *shader)
{
	if(!shader) {
		return FG_FALSE;
	}
	fgBool status = shader->attach(m_gfxID);
	_updateParams();
	return status;
}

/*
 *
 */
fgBool fgGfxShaderProgram::_attachShaders(void)
{
	if(!m_isPreLoaded) {
		return FG_FALSE;
	}
	fgBool status = FG_TRUE;
	shaderVecItor begin,end,itor;
	begin = m_shaders.begin(), end = m_shaders.end(); itor = begin;
	for(;itor!=end;itor++) {
		if(!(*itor))
			continue;
		if(!_attachShader(*itor))
			status = FG_FALSE;
	}
	return status;
}

/*
 *
 */
fgBool fgGfxShaderProgram::_detachShader(fgGfxShader *shader)
{
	if(!shader) {
		return FG_FALSE;
	}
	fgBool status = shader->detach(m_gfxID);
	_updateParams();
	return status;
}

/*
 *
 */
fgBool fgGfxShaderProgram::_detachShaders(void)
{
	if(!m_isPreLoaded) {
		return FG_FALSE;
	}
	fgBool status = FG_TRUE;
	shaderVecItor begin,end,itor;
	begin = m_shaders.begin(), end = m_shaders.end(); itor = begin;
	for(;itor!=end;itor++) {
		if(!(*itor))
			continue;
		if(!_detachShader(*itor))
			status = FG_FALSE;
	}
	return status;

}

/*
 *
 */
fgGFXint fgGfxShaderProgram::_updateLinkStatus(void)
{
	return _updateParam((fgGFXuint)FG_GFX_PROGRAM_LINK_STATUS);
}

fgGFXint fgGfxShaderProgram::_updateValidateStatus(void)
{
	return _updateParam((fgGFXuint)FG_GFX_PROGRAM_VALIDATE_STATUS);
}

/*
 *
 */
fgBool fgGfxShaderProgram::bindAttributes(void)
{
	if(!m_isPreLoaded || !m_isCompiled) {
		return FG_FALSE;
	}
	if(!glIsProgram(m_gfxID)) {
		return FG_FALSE;
	}
	attributeBindVecItor begin, end, itor;
	begin = m_attrBinds.begin(); end = m_attrBinds.end(); itor = begin;
	for(;itor!=end;itor++) {
		fgGfxAttributeBind & bind = *itor;
		// ? NEED STANDARD LOCATIONS
	}
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderProgram::bindUniforms(void)
{
	if(!m_isPreLoaded || !m_isCompiled) {
		return FG_FALSE;
	}
	if(!glIsProgram(m_gfxID)) {
		return FG_FALSE;
	}
	uniformBindVecItor begin, end, itor;
	begin = m_uniformBinds.begin(); end = m_uniformBinds.end(); itor = begin;
	for(;itor!=end;itor++) {
		fgGfxUniformBind & bind = *itor;
		bind.location = glGetUniformLocation(m_gfxID, bind.variableName.c_str());
		// glGetError
	}
	return FG_TRUE;
}
