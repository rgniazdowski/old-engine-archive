/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_SHADER_CONFIG_H_
#define _FG_GFX_SHADER_CONFIG_H_

#ifdef _FG_GFX_STD_INC_BLOCK__
#error "FG_GFX_STD_INC_BLOCK constant is defined. Do not include GfxShaderConfig inside of Gfx Standard Include header."
#endif

#include "Util/fgConfig.h"
#include "fgGFXShaderDefs.h"
#include "Hardware/fgQualityTypes.h"

enum fgGfxShaderConfigType
{
	FG_GFX_SHADER_CONFIG_INVALID	= 0,
	FG_GFX_SHADER_CONFIG_PROGRAM	= 1,
	FG_GFX_SHADER_CONFIG_FRAGMENT	= 2,
	FG_GFX_SHADER_CONFIG_VERTEX		= 3
#if defined FG_USING_OPENGL
	,
	FG_GFX_SHADER_CONFIG_TESSELLATION_CONTROL		=	4,
	FG_GFX_SHADER_CONFIG_TESSELLATION_EVALUATION	=	5,
	FG_GFX_SHADER_CONFIG_GEOMETRY	=	6,
	FG_GFX_SHADER_CONFIG_COMPUTE	=	7
#endif
};

#define FG_GFX_SHADER_CONFIG_PROGRAM_SECTION_NAME	"ShaderProgramConfig"
#define FG_GFX_SHADER_CONFIG_BASIC_SECTION_NAME		"ShaderConfig"

/*
 * Shader config mission is to read special configs (INI) holding information
 * about shader program and respective shaders. It's universal for different kinds
 * of shaders. ShaderConfig will be used from ShaderProgram only. 
 * For shader objects information contained in config consists of:
 * - list of uniform variables and corresponding types in the engine,
 * - list of attribute variables,
 * - list of defined constants,
 * - list of configuration modes depending on supported api,
 * - names of the shader source files,
 * - supported versions of shading language,
 * and others. The goal is to make possible loading many different types of shaders
 * and different configurations (also depending on the build target) without the 
 * need to change or rebuild the executable (engine).
 *
 * This class can load and parse only one config at one time, and
 * will provide that data for only one config type.
 */
class fgGfxShaderConfig : protected fgConfig 
{
public:
	typedef fgArrayVector<fgGfxShaderType>		shaderTypeVec;
	typedef fgArrayVector<fgGfxUniformBind>		shaderUniformBindVec;
	typedef fgArrayVector<fgGfxAttributeBind>	shaderAttributeBindVec;
	typedef fgArrayVector<std::string>			shaderIncludeNameVec;
	typedef fgArrayVector<std::string>			shaderFileVec;
	typedef fgArrayVector<fgQuality>			shaderQualityVec;
	typedef fgArrayVector<fgGfxShaderConstantDef>	shaderConstantVec;

protected:
	///
	fgGfxShaderConfigType	m_configType;
	///
	shaderTypeVec			m_shaderTypes;

	/// 
	shaderUniformBindVec	m_uniformBinds;
	///
	shaderAttributeBindVec	m_attributeBinds;
	///
	shaderIncludeNameVec	m_includes;
	///
	shaderFileVec			m_files;
	///
	shaderQualityVec		m_qualities;
	///
	shaderConstantVec		m_constants;
	
	///
	std::string				m_selectedConfigName;
	///
	std::string				m_programName;

	fgGfxShadingLanguageVersion	m_preferredSLVersion; // FIXME - this sould be probably somewhere else

	///
	fgGfxShaderPrecision	m_defaultPrecision;
public:
	//
	fgGfxShaderConfig();
	// 
	fgGfxShaderConfig(const char *filePath);
	// 
	virtual ~fgGfxShaderConfig();

	//
	virtual void clearAll(void);

	// 
	fgBool load(const char *filePath = NULL);

	//
	fgGfxShaderConfigType getType(void) const {
		return m_configType;
	}

	//
	shaderTypeVec & getRefShaderTypes(void) {
		return m_shaderTypes;
	}

	//
	shaderUniformBindVec & getRefUniformBinds(void) {
		return m_uniformBinds;
	}

	//
	shaderAttributeBindVec & getRefAttributeBinds(void) {
		return m_attributeBinds;
	}

	//
	shaderIncludeNameVec & getRefIncludes(void) {
		return m_includes;
	}

	//
	shaderFileVec & getRefFiles(void) {
		return m_files;
	}

	//
	shaderQualityVec & getRefQualities(void) {
		return m_qualities;
	}

	//
	shaderConstantVec & getRefConstants(void) {
		return m_constants;
	}

	//
	std::string & getProgramName(void) {
		return m_programName;
	}

	//
	std::string & getSelectedConfigName(void) {
		return m_selectedConfigName;
	}

private:
	// 
	fgBool _parseData(void);
	//
	fgBool _parseDefines(fgCfgSection *_definesSection);
	//
	fgBool _parseInclude(fgCfgSection *_includeSection);

};

#endif /* _FG_GFX_SHADER_CONFIG_H_ */
