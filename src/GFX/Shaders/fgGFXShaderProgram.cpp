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
#include "fgLog.h"

#include <algorithm>

/*
 *
 */
fgGfxShaderProgram::fgGfxShaderProgram() :
	m_config(NULL),
	m_isPreLoaded(FG_FALSE),
	m_isCompiled(FG_FALSE),
	m_isLinked(FG_FALSE)
{
	// this needs to depend on some global array GFX config #FIXME
	m_shaders.reserve(6);
	for(int i=0;i<(int)m_shaders.capacity();i++) {
		m_shaders.push_back(NULL);
	}
	m_params[FG_GFX_PROGRAM_DELETE_STATUS]		= 0;
	m_params[FG_GFX_PROGRAM_LINK_STATUS]		= 0;
	m_params[FG_GFX_PROGRAM_VALIDATE_STATUS]	= 0;
	m_params[FG_GFX_PROGRAM_INFO_LOG_LENGTH]	= 0;
	m_params[FG_GFX_PROGRAM_ATTACHED_SHADERS]	= 0;
	m_params[FG_GFX_PROGRAM_ACTIVE_ATTRIBUTES]	= 0;
	m_params[FG_GFX_PROGRAM_ACTIVE_ATTRIBUTE_MAX_LENGTH] = 0;
	m_params[FG_GFX_PROGRAM_ACTIVE_UNIFORMS]	= 0;
	m_baseType = FG_GFX_BASE_TYPE_PROGRAM;
}

/*
 *
 */
fgGfxShaderProgram::~fgGfxShaderProgram()
{
	fgGfxShaderProgram::clearAll();
}

/*
 *
 */
void fgGfxShaderProgram::clearAll(void)
{
	FG_LOG::PrintDebug("BEGIN: fgGfxShaderProgram::clearAll(); NAME: %s, P: %p", getNameStr(), this);

	if(m_config)
		delete m_config;
	m_config = NULL;

	for(int i=0;i<(int)m_shaders.size();i++) {
		if(m_shaders[i]) {
			m_shaders[i]->detach(m_gfxID);
			fgGfxShader *shader =  m_shaders[i];
			m_shaders[i] = NULL;
			delete shader;
		}
	}
	m_uniformBinds.clear_optimised();
	m_attrBinds.clear_optimised();
	m_shaders.clear_optimised();
	deleteProgram();
	m_isLinked = FG_FALSE;
	m_isCompiled = FG_FALSE;
	m_isPreLoaded = FG_FALSE;
	FG_LOG::PrintDebug("END: fgGfxShaderProgram::clearAll();");
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
	setFilePath(path);
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
	m_nameTag = m_config->getProgramName();
	
	fgGfxShaderConfig::shaderConstantVec shaderConstants = m_config->getRefConstants();

	for(int i=0;i<(int)shaderTypes.size();i++) {
		std::string newPath;
		newPath.append(filePathNoExt).append(".").append(FG_GFX_SHADER_CFG_STD_SUFFIX(shaderTypes[i]));
		
		if(!m_config->load(newPath.c_str(), FG_GFX_ESSL_100)) {
			FG_LOG::PrintError("loading shader config failed\n");
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
			for(int i=0;i<(int)shaderConstants.size();i++)
				shader->appendDefine(shaderConstants[i]);
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
	delete m_config;
	m_config = NULL;
	m_isPreLoaded = FG_TRUE;
	reportSuccess(FG_ERRNO_GFX_OK, "Shader program loaded successfully");
	///////////////////////////////////////////////////////
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderProgram::preLoadConfig(std::string &path)
{
	return preLoadConfig(path.c_str());
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
		reportError(FG_ERRNO_EPERM, "Compile function called without loaded shader configuration");
		return FG_FALSE;
	}
	if(m_isCompiled) {
		reportError(FG_ERRNO_EPERM, "Shader program is already compiled. Use option for forced recompilation.");
		return FG_FALSE;
	}
	if(!create()) {
		FG_LOG::PrintError("Failed to create shader program");
		return FG_FALSE;
	}
	shaderVecItor begin,end,itor;
	begin = m_shaders.begin(), end = m_shaders.end(); itor = begin;
	for(;itor!=end;itor++) {
		if(!(*itor))
			continue;
		fgGfxShader *shader = *itor;
		FG_LOG::PrintDebug("Attempting to compile shader: %s", shader->getFilePath());
		if(!shader->compile()) {
			updateParams();
			updateLog();
			const char *log = shader->getLog();
			if(!log) log = "No message"; // #FIXME PLOIX
			FG_LOG::PrintError("Failed to compile shader: %s (%s)", shader->getNameStr(), log);
			return FG_FALSE;
		}
	}

	itor = begin;
	for(;itor!=end;itor++) {
		_attachShader(*itor);
	}
	m_isCompiled = FG_TRUE;
	reportSuccess(FG_ERRNO_GFX_OK, "Shaders for '%s' compiled successfully", getNameStr());
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderProgram::link(void)
{
	clearStatus();
	if(m_isLinked || !m_isPreLoaded) {
		FG_LOG::PrintError("Shader is already linked / is not preloaded on link()\n");
		return FG_FALSE;
	}
	if(!m_isCompiled) {
		if(!compile()) {
			FG_LOG::PrintError("Failed to compile shaders for program");
			return FG_FALSE;
		}
	}
	if(!bindAttributes()) {
		FG_LOG::PrintError("Failed to bind attributes for '%s' program", getNameStr());
		return FG_FALSE;
	}
	fgBool status = FG_TRUE;
	glLinkProgram(m_gfxID);
	fgGLError("glLinkProgram");
	s3eDeviceYield(0);
	updateLinkStatus();
	if(!m_params[FG_GFX_PROGRAM_LINK_STATUS]) {
		updateLog();
		FG_LOG::PrintError("Error linking program: %s\n", getLog());
		return FG_FALSE;
	}
	glValidateProgram(m_gfxID);
	fgGLError("glValidateProgram");
	s3eDeviceYield(0);
	updateValidateStatus();
	if(!m_params[FG_GFX_PROGRAM_VALIDATE_STATUS]) {
		//Warning?
		FG_LOG::PrintWarning("The '%s' program did not validate successfully", getNameStr());
		status = FG_FALSE;
	}
	updateParams();
	updateLog();
	if(status) {
		reportSuccess(FG_ERRNO_GFX_OK, "Shader program '%s' linked with no errors", getNameStr());
	}
	m_isLinked = FG_TRUE;
	if(!bindUniforms()) {
		// ERROR CODES ! ! !
		reportWarning(FG_ERRNO_EINVAL, "Failed to bind all uniforms in shader program '%s'", getNameStr());
		status = FG_FALSE;
	}
	{
		FG_LOG::PrintDebug("Validating bound locations of attributes...");
		attributeBindVecItor begin, end, itor;
		begin = m_attrBinds.begin(); end = m_attrBinds.end(); itor = begin;
		for(;itor!=end;itor++) {
			fgGfxAttributeBind & bind = *itor;
			if(bind.location == -1 || bind.type == FG_GFX_ATTRIBUTE_INVALID)
				continue;
			int boundLoc = glGetAttribLocation(m_gfxID, bind.variableName.c_str());
			FG_LOG::PrintDebug("Bound attribute '%s' to location %d (should be %d)",
				bind.variableName.c_str(), boundLoc, (int)bind.type);
			fgGLError("glGetAttribLocation");
		}
	}
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
	fgGLError("glUseProgram");
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderProgram::deleteProgram(void)
{
	if(glIsProgram(m_gfxID)) {
		glDeleteProgram(m_gfxID);
		fgGLError("glDeleteProgram");
		updateParams();
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
	unsigned int pos = 1;
	while (pos < m_attrBinds.size()) {
		if (m_attrBinds[pos] >= m_attrBinds[pos-1]) {
			pos = pos + 1;
		} else {
			std::swap<fgGfxAttributeBind>(m_attrBinds[pos], m_attrBinds[pos-1]);
			if (pos > 1) {
				pos = pos - 1;
			}
		}
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
	updateParams();
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
	updateParams();
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
fgGFXint fgGfxShaderProgram::updateLinkStatus(void)
{
	return updateParam(FG_GFX_PROGRAM_LINK_STATUS);
}

/*
 *
 */
fgGFXint fgGfxShaderProgram::updateValidateStatus(void)
{
	return updateParam(FG_GFX_PROGRAM_VALIDATE_STATUS);
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
		if(bind.location == -1 || bind.type == FG_GFX_ATTRIBUTE_INVALID)
			continue;
		FG_LOG::PrintDebug("Binding attribute '%s' of type: '%s'(%d), in shader program: '%s' to location: %d",
			bind.variableName.c_str(),
			FG_GFX_ATTRIBUTE_TYPE_TO_TEXT(bind.type), 
			(int)bind.type, 
			getNameStr(),
			(int)bind.location);

		glBindAttribLocation(m_gfxID, (fgGFXuint)bind.location, bind.variableName.c_str());
		fgGLError("glBindAttribLocation");
		bind.isBound = FG_TRUE;
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
		if(bind.type == FG_GFX_UNIFORM_INVALID)
			continue;
		FG_LOG::PrintDebug("Preparing for binding uniform '%s' of type: '%s' (%d)", bind.variableName.c_str(), FG_GFX_UNIFORM_TYPE_TO_TEXT(bind.type), (int)bind.type);
		bind.location = glGetUniformLocation(m_gfxID, bind.variableName.c_str());
		FG_LOG::PrintDebug("Bound uniform '%s' to location: %d", bind.variableName, bind.location);
		fgGLError("glGetUniformLocation");
	}
	return FG_TRUE;
}

// #FIXME ! too much code repetition - it can be managed, similar code into one function
// like ... findUniformBind etc. which would return the proper reference
// or pointer (pointer is easier)

//
fgGFXint fgGfxShaderProgram::getUniformBindIndex(fgGfxUniformType type)
{
	if(type == FG_GFX_UNIFORM_INVALID)
		return -1;
	fgGFXint foundIndex = -1;
	int i, n = (int)m_uniformBinds.size();
	for(i=0;i<n;i++) {
		fgGfxUniformBind & bind = m_uniformBinds.at(i);
		if(bind.type == FG_GFX_UNIFORM_INVALID)
			continue;
		if(bind.type == type) {
			foundIndex = i;
			break;
		}
	}
	return foundIndex;
}

fgGfxUniformBind *fgGfxShaderProgram::getUniformBind(fgGfxUniformType type)
{
	int index = getUniformBindIndex(type);
	if(index < 0)
		return NULL;
	return &m_uniformBinds[index];
}

/*
 *
 */
fgGFXint fgGfxShaderProgram::getUniformLocation(fgGfxUniformType type)
{
	fgGfxUniformBind * bind = getUniformBind(type);
	if(!bind)
		return -1;
	return bind->location;
}

/*
 *
 */
fgGFXint fgGfxShaderProgram::getUniformLocation(std::string variableName)
{
	return -1;
}

///////////////////////////////////////////////////////////

fgBool fgGfxShaderProgram::setUniform(fgGfxMVPMatrix *matrix)
{
	if(!matrix)
		return FG_FALSE;
	fgGfxUniformBind * bind = getUniformBind(FG_GFX_MVP_MATRIX);
	if(!bind)
		return FG_FALSE;
	if(bind->location == -1)
		return FG_FALSE;
	glUniformMatrix4fv(bind->location, 1, GL_FALSE, matrix->getModelViewProjMatPtr());
	fgGLError("glUniformMatrix4fv");
	return FG_TRUE;
}

fgBool fgGfxShaderProgram::setUniform(fgGfxMVMatrix *matrix)
{
	fgGfxUniformBind * bind = getUniformBind(FG_GFX_MV_MATRIX);
	if(!bind || !matrix)
		return FG_FALSE;
	if(bind->location == -1)
		return FG_FALSE;
	glUniformMatrix4fv(bind->location, 1, GL_FALSE, matrix->getModelViewMatPtr());
	fgGLError("glUniformMatrix4fv");
	return FG_TRUE;
}

///////////////////////////////////////////////////////////

/*
 *
 */
fgBool fgGfxShaderProgram::setUniform(fgGfxUniformType type, fgGFXfloat v0)
{
	fgGfxUniformBind * bind = getUniformBind(type);
	if(!bind)
		return FG_FALSE;
	if(bind->location == -1)
		return FG_FALSE;
	glUniform1f(bind->location, v0);
	fgGLError("glUniform1f");
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderProgram::setUniform(fgGfxUniformType type, fgGFXfloat v0, fgGFXfloat v1)
{
	fgGfxUniformBind * bind = getUniformBind(type);
	if(!bind)
		return FG_FALSE;
	if(bind->location == -1)
		return FG_FALSE;
	glUniform2f(bind->location, v0, v1);
	fgGLError("glUniform2f");
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderProgram::setUniform(fgGfxUniformType type, fgGFXfloat v0, fgGFXfloat v1, fgGFXfloat v2)
{
	fgGfxUniformBind * bind = getUniformBind(type);
	if(!bind)
		return FG_FALSE;
	if(bind->location == -1)
		return FG_FALSE;
	glUniform3f(bind->location, v0, v1, v2);
	fgGLError("glUniform3f");
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderProgram::setUniform(fgGfxUniformType type, fgGFXfloat v0, fgGFXfloat v1, fgGFXfloat v2, fgGFXfloat v3)
{
	fgGfxUniformBind * bind = getUniformBind(type);
	if(!bind)
		return FG_FALSE;
	if(bind->location == -1)
		return FG_FALSE;
	glUniform4f(bind->location, v0, v1, v2, v3);
	fgGLError("glUniform4f");
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderProgram::setUniform(fgGfxUniformType type, fgGFXint v0)
{
	fgGfxUniformBind * bind = getUniformBind(type);
	if(!bind)
		return FG_FALSE;
	if(bind->location == -1)
		return FG_FALSE;
	glUniform1i(bind->location, v0);
	fgGLError("glUniform1i");
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderProgram::setUniform(fgGfxUniformType type, fgGFXint v0, fgGFXint v1)
{
	fgGfxUniformBind * bind = getUniformBind(type);
	if(!bind)
		return FG_FALSE;
	if(bind->location == -1)
		return FG_FALSE;
	glUniform2i(bind->location, v0, v1);
	fgGLError("glUniform2i");
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderProgram::setUniform(fgGfxUniformType type, fgGFXint v0, fgGFXint v1, fgGFXint v2)
{
	fgGfxUniformBind * bind = getUniformBind(type);
	if(!bind)
		return FG_FALSE;
	if(bind->location == -1)
		return FG_FALSE;
	glUniform3i(bind->location, v0, v1, v2);
	fgGLError("glUniform3i");
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderProgram::setUniform(fgGfxUniformType type, fgGFXint v0, fgGFXint v1, fgGFXint v2, fgGFXint v3)
{
	fgGfxUniformBind * bind = getUniformBind(type);
	if(!bind)
		return FG_FALSE;
	if(bind->location == -1)
		return FG_FALSE;
	glUniform4i(bind->location, v0, v1, v2, v3);
	fgGLError("glUniform4i");
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderProgram::setUniform(fgGfxUniformType type, fgGFXsizei count, const fgGFXfloat *value)
{
	fgGfxUniformBind * bind = getUniformBind(type);
	if(!bind)
		return FG_FALSE;
	if(bind->location == -1)
		return FG_FALSE;
	// NEED MORE IFS :D
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderProgram::setUniform(fgGfxUniformType type, fgGFXsizei count, const fgGFXint *value)
{
	fgGfxUniformBind * bind = getUniformBind(type);
	if(!bind)
		return FG_FALSE;
	if(bind->location == -1)
		return FG_FALSE;
	// NEED MORE IFS :D
	return FG_TRUE;
}
