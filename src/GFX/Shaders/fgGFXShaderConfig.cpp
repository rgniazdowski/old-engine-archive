/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXShaderConfig.h"
#include "Util/fgPath.h"
#include "Util/fgStrings.h"

/*
 *
 */
fgGfxShaderConfig::fgGfxShaderConfig() :
	m_configType(FG_GFX_SHADER_CONFIG_INVALID),
	m_preferredSLVersion(FG_GFX_SHADING_LANGUAGE_INVALID),
	m_defaultPrecision(FG_GFX_SHADER_PRECISION_DEFAULT)
{
}

/*
 *
 */
fgGfxShaderConfig::fgGfxShaderConfig(const char *filePath)
{
	fgGfxShaderConfig::load(filePath);
}

/*
 *
 */
fgGfxShaderConfig::~fgGfxShaderConfig()
{
	if(m_parser)
		delete m_parser;
	if(m_writer)
		delete m_writer;
	clearAll();
}

/*
 *
 */
void fgGfxShaderConfig::clearAll(void)
{
	fgConfig::clearAll();
	m_selectedConfigName.clear();
	m_programName.clear();
	m_preferredSLVersion = FG_GFX_SHADING_LANGUAGE_INVALID;
	m_configType = FG_GFX_SHADER_CONFIG_INVALID;
	m_defaultPrecision = FG_GFX_SHADER_PRECISION_DEFAULT;
	m_shaderTypes.clear_optimised();
	m_uniformBinds.clear_optimised();
	m_attributeBinds.clear_optimised();
	m_includes.clear_optimised();
	m_files.clear_optimised();
	m_qualities.clear_optimised();
	m_constants.clear_optimised();
}

/*
 *
 */
fgBool fgGfxShaderConfig::load(const char *filePath)
{
	//fgGfxShaderConfig::clearAll();
	if(!fgConfig::load(filePath))
		return FG_FALSE;
	return _parseData();
}

/*
 *
 */
fgBool fgGfxShaderConfig::_parseDefines(fgCfgSection *_definesSection)
{
	if(!_definesSection)
		return FG_FALSE;
	unsigned short _n = 0;
	fgCfgTypes::parameterVecItor paramsBegin, paramsEnd, paramsItor;
	// This section is optional
	paramsBegin = _definesSection->parameters.begin();
	paramsEnd = _definesSection->parameters.end();
	paramsItor = paramsBegin;
	for(;paramsItor!=paramsEnd;paramsItor++) {
		fgCfgParameter *param = *paramsItor;
		if(!param) continue;
		// for now only BOOL is supported
		if(param->type == FG_CFG_PARAMETER_BOOL && !param->name.empty()) {
			fgGfxShaderConstantDef _constant;
			_constant.name = param->name;
			_constant.value = param->bool_val;
			m_constants.push_back(_constant);
			_n++;
		}
	}
	if(!_n)
		return FG_FALSE;
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderConfig::_parseInclude(fgCfgSection *_includeSection)
{
	if(!_includeSection)
		return FG_FALSE;
	unsigned short _n = 0;
	fgCfgParameter *param = _includeSection->getParameter("list", FG_CFG_PARAMETER_STRING);
	if(!param) return FG_FALSE;
	fgArrayVector<std::string> _incVec;
	std::string _tmp = param->string;
	fgStrings::split(_tmp, ',', _incVec);
	for(int i=0;i<(int)_incVec.size();i++) {
		m_includes.push_back(_incVec[i]);
		_n++;
	}
	if(!_n)
		return FG_FALSE;
	return FG_TRUE;
}

/*
 * #OPTIMISE #DIVIDE #FIXME shader config parse data, move some operations to other function for clarity
 */
fgBool fgGfxShaderConfig::_parseData(void)
{
	if(m_preferredSLVersion == FG_GFX_SHADING_LANGUAGE_INVALID) {
		return FG_FALSE;
	}
	if(m_filePath.empty()) {
		return FG_FALSE;
	}

	if(m_sectionMap.empty()) {
		return FG_FALSE;
	}

	const char *ext = fgPath::fileExt(m_filePath.c_str(), FG_TRUE);
	if(!ext) {
		return FG_FALSE;
	}

	m_configType = FG_GFX_SHADER_CONFIG_INVALID;
	if(strcasecmp(ext, FG_GFX_SHADER_CONFIG_PROGRAM_STD_SUFFIX) == 0) {
		m_configType = FG_GFX_SHADER_CONFIG_PROGRAM;
	} else if(strcasecmp(ext, FG_GFX_SHADER_CONFIG_FRAGMENT_STD_SUFFIX) == 0) {
		m_configType = FG_GFX_SHADER_CONFIG_FRAGMENT;
	} else if(strcasecmp(ext, FG_GFX_SHADER_CONFIG_VERTEX_STD_SUFFIX) == 0) {
		m_configType = FG_GFX_SHADER_CONFIG_VERTEX;
#if defined FG_USING_OPENGL
	} else if(strcasecmp(ext, FG_GFX_SHADER_CONFIG_TESS_CONTROL_STD_SUFFIX) == 0) {
		m_configType = FG_GFX_SHADER_CONFIG_TESS_CONTROL;
	} else if(strcasecmp(ext, FG_GFX_SHADER_CONFIG_TESS_EVALUATION_STD_SUFFIX) == 0) {
		m_configType = FG_GFX_SHADER_CONFIG_TESS_EVALUATION;
	} else if(strcasecmp(ext, FG_GFX_SHADER_CONFIG_GEOMETRY_STD_SUFFIX) == 0) {
		m_configType = FG_GFX_SHADER_CONFIG_VERTEX;
	} else if(strcasecmp(ext, FG_GFX_SHADER_CONFIG_COMPUTE_STD_SUFFIX) == 0) {
		m_configType = FG_GFX_SHADER_CONFIG_VERTEX;
#endif
	}

	if(m_configType == FG_GFX_SHADER_CONFIG_INVALID) {
		return FG_FALSE;
	}
	
	fgCfgSection *mainSection = NULL;
	
	if(m_configType == FG_GFX_SHADER_CONFIG_PROGRAM) {
		mainSection = getSection(FG_GFX_SHADER_CONFIG_PROGRAM_SECTION_NAME);
	} else {
		mainSection = getSection(FG_GFX_SHADER_CONFIG_BASIC_SECTION_NAME);
	}

	if(!mainSection) {
		// No new section found, the ini config is malformed
		return FG_FALSE;
	}

	{
		fgCfgParameter *param = mainSection->getParameter("precision", FG_CFG_PARAMETER_STRING);
		if(param) {
			m_defaultPrecision = (fgGfxShaderPrecision) FG_GFX_PRECISION_FROM_TEXT(param->string);
		}
	}

	char slVerSubSectionName[64];
	char _tmpStr[24];
	if(m_preferredSLVersion == FG_GFX_ESSL_100 || m_preferredSLVersion == FG_GFX_ESSL_300)
		strcpy(_tmpStr, "ESSL");
	else
		strcpy(_tmpStr, "GLSL");
	snprintf(slVerSubSectionName, 64, "Shader.Version.%s.%d", _tmpStr, (int)m_preferredSLVersion);
	// Check if the shader supports that shading language
	fgCfgSection *slVersionSection = getSection(slVerSubSectionName);
	if(!slVersionSection) {
		// Current shading language version is not supported by this shader / program
		return FG_FALSE;
	} else if(!slVersionSection->parametersMap.size()) {
		// there is such section but it does not provide the name of the valid configuration
		return FG_FALSE;
	}
	// Get the name of the configuration based on shading language version
	{
		fgCfgParameter *param = slVersionSection->getParameter("configuration", FG_CFG_PARAMETER_STRING);
		if(!param) {
			return FG_FALSE;
		}
		m_selectedConfigName = param->string;
	}
	// Now populate list of defines (constant values / bool only)
	// Shader.Defines holds list of constants for all configurations (shading language version)
	// and all shader types (shader objects to link with shader program)
	fgCfgSection *definesSection = getSection("Shader.Defines");
	_parseDefines(definesSection);
	// Populate list of constants for selected configuration,
	// like before this section is optional
	{
		std::string _tmp = "Shader.Defines.";
		_tmp.append(m_selectedConfigName);
		definesSection = getSection(_tmp);
		_parseDefines(definesSection);
	}
	//
	// Parse more wide parameters from specific shader configuration (not program config)
	//
	if(m_configType != FG_GFX_SHADER_CONFIG_PROGRAM) {
		fgCfgParameter *param = mainSection->getParameter("shaderType", FG_CFG_PARAMETER_STRING);
		if(!param) {
			// no shader type specified - it has to be explicitly stated in config
			// even if the file extension points to shader type
			return FG_FALSE;
		}
		fgGfxShaderType _shadertype = FG_GFX_SHADER_TYPE_FROM_TEXT(param->string);
		if(_shadertype == FG_GFX_SHADER_INVALID) {
			// Unsupported shader type ...
			return FG_FALSE;
		}
		m_shaderTypes.push_back(_shadertype);
		const char *shortPrefix = FG_GFX_SHADER_SHORT_PREFIX(_shadertype);

		// Parse defines
		//
		std::string _tmp;
		_tmp.append(shortPrefix).append(".Defines");
		std::string _tmp2 = _tmp;
		_parseDefines(getSection(_tmp));
		_tmp2.append(".").append(m_selectedConfigName);
		_parseDefines(getSection(_tmp2));
		_tmp.clear(); _tmp2.clear();

		// parse includes
		//
		_tmp.append(shortPrefix).append(".Include");
		_parseInclude(getSection(_tmp));
		_tmp.clear();

		// Parse file / quality configuration specific for this shader
		// This depends on the selected configuration (sub config) based on
		// shading language version
		_tmp.append(shortPrefix).append(".Config.").append(m_selectedConfigName);
		fgCfgSection *cfgSpecSection = getSection(_tmp);
		_tmp.clear();
		if(!cfgSpecSection) {
			// This is bad - specific config with file/quality list was not found
			return FG_FALSE;
		}
		fgArrayVector<std::string> _helperVec;
		fgBool foundQuality = FG_FALSE, foundFile = FG_FALSE;
		if((param = cfgSpecSection->getParameter("quality", FG_CFG_PARAMETER_STRING)) != NULL) {
			printf("GFX QUALITY  VEC : %s\n", param->string);
			std::string _q_vec = param->string;
			fgStrings::split(_q_vec, ';', _helperVec);
			m_qualities.clear_optimised();
			for(int i=0;i<(int)_helperVec.size();i++) {
				m_qualities.push_back(FG_QUALITY_FROM_TEXT(_helperVec[i].c_str()));
			}
			if(!m_qualities.empty()) {
				foundQuality = FG_TRUE;
			}
			_q_vec.clear();
			_helperVec.clear_optimised();
		} 
		if((param = cfgSpecSection->getParameter("file", FG_CFG_PARAMETER_STRING)) != NULL) {
			printf("GFX FILE VEC : %s\n", param->string);

			std::string _f_vec = param->string;
			fgStrings::split(_f_vec, ';', _helperVec);
			m_files.clear_optimised();
			for(int i=0;i<(int)_helperVec.size();i++) {
				m_files.push_back(_helperVec[i]);
			}
			if(!m_files.empty()) {
				foundFile = FG_TRUE;
			}
			_f_vec.clear();
			_helperVec.clear_optimised();
		}
		if(!foundFile || !foundQuality) {
			// Did not find parameters for quality or file
			return FG_FALSE;
		}
		//
		// Loading attributes
		//
		if(_shadertype == FG_GFX_SHADER_VERTEX) {
			// checking for attributes only for vertex shader 
			// (attributes in fragment shader are not allowed / needed)
			fgCfgTypes::sectionVec _attributes;
			_tmp.append(shortPrefix).append(".").append("Attribute.");
			getSectionsWith(_attributes, _tmp.c_str());
			if(_attributes.empty()) {
				// error - attributes are required - minimum one
				return FG_FALSE;
			}
			// !! data type for attribute (GL) possible values:
			// float, vec2, vec3, vec4, mat2, mat3, and mat4.
			unsigned short _nmax=(unsigned short)_attributes.size(),i;
			for(i=0;i<_nmax;i++) {
				fgGfxAttributeBind _bind;
				_bind.type = FG_GFX_ATTRIBUTE_TYPE_FROM_TEXT(_attributes[i]->subName.c_str());
				if(_bind.type == FG_GFX_ATTRIBUTE_INVALID) {
					// #FIXME
					continue;
				}
				fgCfgParameter *_aname=NULL, *_aDataType=NULL, *_aprecision=NULL;
				_aname = _attributes[i]->getParameter("attributeName", FG_CFG_PARAMETER_STRING);
				_aDataType = _attributes[i]->getParameter("type", FG_CFG_PARAMETER_STRING);
				_aprecision = _attributes[i]->getParameter("precision", FG_CFG_PARAMETER_STRING);
				if(!_aname || !_aDataType) {
					// This attribute definition section is malformed
					continue;
				}
				_bind.precision = FG_GFX_PRECISION_DEFAULT;
				if(_aprecision) {
					_bind.precision = FG_GFX_PRECISION_FROM_TEXT(_aprecision->string);
				}
				_bind.variableName = _aname->string;
				_bind.dataType = FG_GFX_DATA_TYPE_FROM_TEXT(_aDataType->string);
				m_attributeBinds.push_back(_bind);
			}
		}

		//
		// Loading uniforms
		//
		// checking for attributes only for vertex shader 
		// (attributes in fragment shader are not allowed / needed)
		fgCfgTypes::sectionVec _uniforms;
		_tmp.clear();
		_tmp.append(shortPrefix).append(".").append("Uniform.");
		getSectionsWith(_uniforms, _tmp.c_str());
		if(_uniforms.empty()) {
			// error - attributes are required - minimum one
			return FG_FALSE;
		}
		unsigned short _nmax=(unsigned short)_uniforms.size(),i;
		for(i=0;i<_nmax;i++) {
			fgGfxUniformBind _bind;
			_bind.type = FG_GFX_UNIFORM_TYPE_FROM_TEXT(_uniforms[i]->subName.c_str());
			if(_bind.type == FG_GFX_UNIFORM_INVALID) {
				// Not a valid / supported uniform type - can ignore it ? Pass empty data to it?
				// #FIXME
				continue;
			}
			fgCfgParameter *_uname=NULL, *_uDataType=NULL, *_uprecision=NULL;
			_uname = _uniforms[i]->getParameter("uniformName", FG_CFG_PARAMETER_STRING);
			_uDataType = _uniforms[i]->getParameter("type", FG_CFG_PARAMETER_STRING);
			_uprecision = _uniforms[i]->getParameter("precision", FG_CFG_PARAMETER_STRING);
			if(!_uname || !_uDataType) {
				// This attribute definition section is malformed
				continue;
			}
			_bind.precision = FG_GFX_PRECISION_DEFAULT;
			if(_uprecision) {
				_bind.precision = FG_GFX_PRECISION_FROM_TEXT(_uprecision->string);
			}
			_bind.variableName = _uname->string;
			_bind.dataType = FG_GFX_DATA_TYPE_FROM_TEXT(_uDataType->string);
			m_uniformBinds.push_back(_bind);
		}
	}
	if(m_configType == FG_GFX_SHADER_CONFIG_PROGRAM) {
		// specific configuration procedures for main shader config (shader program)
		fgCfgParameter *param = NULL;
		param = mainSection->getParameter("programName", FG_CFG_PARAMETER_STRING);
		if(!param) {
			// this is kinda big error, the program name (string handle ID) is not specified
			return FG_FALSE;
		}
		m_programName = param->string;
		int nmax = 0;
		if(FG_BUILD_CONFIG.usingOpenGLES)
			nmax = 2;
		else if(FG_BUILD_CONFIG.usingOpenGL)
			nmax = 6;	// #FIXME - need global GFX config array (like with build config)
						// for various runtime / etc info on GFX subsystem (no of shader types supported ?)
		if(nmax > sizeof(g_fgGfxSupportedShaderTypes)/sizeof(g_fgGfxSupportedShaderTypes[0]))
			nmax = sizeof(g_fgGfxSupportedShaderTypes)/sizeof(g_fgGfxSupportedShaderTypes[0]); // #FIXME - ugly...
		for(int i=0;i<nmax;i++) {
			std::string qstr = "has";
			qstr.append(g_fgGfxSupportedShaderTypesText[i]);
			param = mainSection->getParameter(qstr, FG_CFG_PARAMETER_BOOL);
			if(param) {
				if(param->bool_val == FG_TRUE) {
					m_shaderTypes.push_back(g_fgGfxSupportedShaderTypes[i]);
				}
			}
		}
		// Check for valid number of shaders to bind into one shader program #FIXME
		if(m_shaderTypes.size() == 2 && 0) {
			// #TODO
		}
	} else if(m_configType == FG_GFX_SHADER_CONFIG_FRAGMENT) {
		// specific configuration for fragment shader (pixel shader)
	} else if(m_configType == FG_GFX_SHADER_CONFIG_VERTEX) {
		// configuration for vertex shader
#if defined FG_USING_OPENGL
	} else if(m_configType == FG_GFX_SHADER_CONFIG_TESS_CONTROL) {
		// configuration for tessellation control shader
	} else if(m_configType == FG_GFX_SHADER_CONFIG_TESS_EVALUATION) {
		// configuration for tessellation evaluation shader
	} else if(m_configType == FG_GFX_SHADER_CONFIG_GEOMETRY) {
		// configuration for geometry shader
	} else if(m_configType == FG_GFX_SHADER_CONFIG_COMPUTE) {
		// specific configuration procedures for compute shader
#endif
	}

	return FG_TRUE;
}
