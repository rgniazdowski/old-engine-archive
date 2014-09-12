/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_SHADER_PROGRAM_H_
#define _FG_GFX_SHADER_PROGRAM_H_

#include "fgGFXShaderDefs.h"
#include "fgGFXShader.h"
#include "fgGFXShaderBase.h"
#include "fgGFXShaderConfig.h"

#include "fgArrayVector.h"

#include "Util/fgHandle.h"
#include "Util/fgTag.h"
#include "fgStatusReporter.h"

class fgGfxShaderProgram;

#define FG_TAG_GFX_SHADER_PROGRAM_NAME	"tag{fgGfxShaderProgram}"
#define FG_TAG_GFX_SHADER_PROGRAM		FG_TAG_TYPE(fgGfxShaderProgram)

FG_TAG_TEMPLATE_ID_AUTO(fgGfxShaderProgram, FG_TAG_GFX_SHADER_PROGRAM_NAME);
typedef FG_TAG_GFX_SHADER_PROGRAM fgGfxShaderProgramTag;

// Special handle type for shader program
typedef fgHandle<FG_TAG_GFX_SHADER_PROGRAM > fgGfxShaderProgramHandle;

//
enum fgGfxProgramObjParamType {
	// GL_TRUE if program is currently flagged for deletion, and GL_FALSE otherwise.
	FG_GFX_PROGRAM_DELETE_STATUS	= GL_DELETE_STATUS,
	// GL_TRUE if the last link operation on program was successful, and GL_FALSE otherwise.
	FG_GFX_PROGRAM_LINK_STATUS		= GL_LINK_STATUS,
	// GL_TRUE or if the last validation operation on program was successful, and GL_FALSE otherwise.
	FG_GFX_PROGRAM_VALIDATE_STATUS	= GL_VALIDATE_STATUS,
	// the number of characters in the information log for program including the null termination
	// character (i.e., the size of the character buffer required to store the informationlog). 
	// If program has no information log, a value of 0 is returned.
	FG_GFX_PROGRAM_INFO_LOG_LENGTH	= GL_INFO_LOG_LENGTH,
	// the number of shader objects attached to program.
	FG_GFX_PROGRAM_ATTACHED_SHADERS = GL_ATTACHED_SHADERS,
	// number of active attribute variables for program
	FG_GFX_PROGRAM_ACTIVE_ATTRIBUTES = GL_ACTIVE_ATTRIBUTES,
	// the length of the longest active attribute name for program, including the null termination character
	FG_GFX_PROGRAM_ACTIVE_ATTRIBUTE_MAX_LENGTH = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
	// the number of active uniform variables
	FG_GFX_PROGRAM_ACTIVE_UNIFORMS = GL_ACTIVE_UNIFORMS
};

/*
 *
 */
class fgGfxShaderProgram : protected fgGfxShaderBase, public fgStatusReporter<fgGfxShaderProgramTag> 
{
protected:
	enum 
	{
		SP_FRAGMENT_SHADER_ID			= 0,
		SP_VERTEX_SHADER_ID				= 1,
#if defined FG_USING_OPENGL
		SP_TESS_CONTROL_SHADER_ID		= 2,
		SP_TESS_EVALUATION_SHADER_ID	= 3,
		SP_GEOMETRY_SHADER_ID			= 4,
		// GL_COMPUTE_SHADER is available only if the GL version is 4.3 or higher.
		SP_COMPUTE_SHADER_ID			= 5
#endif
	};

protected:
	static fgGFXint _shaderTypeToSpID(fgGfxShaderType _type) {
		fgGFXint spID = 0;
		switch(_type) {
		case FG_GFX_SHADER_FRAGMENT:
			spID = SP_FRAGMENT_SHADER_ID;
			break;
		case FG_GFX_SHADER_VERTEX:
			spID = SP_VERTEX_SHADER_ID;
			break;
#if defined FG_USING_OPENGL
		case FG_GFX_SHADER_TESS_CONTROL:
			spID = SP_TESS_CONTROL_SHADER_ID;
			break;
		case FG_GFX_SHADER_TESS_EVALUATION:
			spID = SP_TESS_EVALUATION_SHADER_ID;
			break;
		case FG_GFX_SHADER_GEOMETRY:
			spID = SP_GEOMETRY_SHADER_ID;
			break;
		case FG_GFX_SHADER_COMPUTE:
			spID = SP_COMPUTE_SHADER_ID;
			break;
#endif
		default:
			spID = -1;
			break;
		};
		return spID;
	}

public:
	typedef fgArrayVector<fgGfxShader *>	shaderVec;
	typedef shaderVec::iterator				shaderVecItor;
	typedef fgGfxShaderConfig::shaderUniformBindVec		uniformBindVec;
	typedef uniformBindVec::iterator					uniformBindVecItor;
	typedef fgGfxShaderConfig::shaderAttributeBindVec	attributeBindVec;
	typedef attributeBindVec::iterator					attributeBindVecItor;
protected:
	///
	shaderVec					m_shaders;
	///
	uniformBindVec				m_uniformBinds;
	///
	attributeBindVec			m_attrBinds;
	///
	std::string					m_programName;
	///
	fgGfxShaderConfig*			m_config;
	///
	fgGfxShaderProgramHandle	m_handle;
	///
	fgBool						m_isPreLoaded;
	///
	fgBool						m_isCompiled;
	///
	fgBool						m_isLinked;
public:
	//
	fgGfxShaderProgram();
	//
	virtual ~fgGfxShaderProgram();

	//
	fgBool preLoadConfig(const char *path);

protected:
	//
	fgBool _appendUniformBinds(uniformBindVec & binds);
	//
	fgBool _appendAttributeBinds(attributeBindVec & binds);

	//
	fgBool _attachShader(fgGfxShader *shader);
	//
	fgBool _attachShaders(void);

	//
	fgBool _detachShader(fgGfxShader *shader);
	//
	fgBool _detachShaders(void);
	
	//
	fgGFXint _updateLinkStatus(void);
	//
	fgGFXint _updateValidateStatus(void);

public:
	//
	fgGFXuint create(void);
	//
	fgBool compile(void);
	//
	fgBool link(void);
	//
	fgBool use(void);
	//
	fgBool bindAttributes(void);
	//
	fgBool bindUniforms(void);
	//
	fgBool deleteProgram(void);

public:
	//
	std::string & getName(void) {
		return m_programName;
	}

	//
	const char *getNameStr(void) const {
		return m_programName.c_str();
	}

	//
	fgGfxShaderProgramHandle & getRefHandle(void) {
		return m_handle;
	}

	//
	shaderVec & getRefShaderVec(void) {
		return m_shaders;
	}

	//
	attributeBindVec & getRefAttrBinds(void) {
		return m_attrBinds;
	}

	//
	uniformBindVec & getRefUniformBinds(void) {
		return m_uniformBinds;
	}

	//
	fgGFXuint & getRefGfxID(void) {
		return m_gfxID;
	}

	fgGfxShader *getShader(fgGfxShaderType type) const {
		fgGFXint id = _shaderTypeToSpID(type);
		if(id != -1)
			return m_shaders[id];
		else
			return NULL;
	}

	//
	fgGfxShader *getFragmentShader(void) const {
		return m_shaders[SP_FRAGMENT_SHADER_ID];
	}

	//
	fgGfxShader *getVertexShader(void) const {
		return m_shaders[SP_VERTEX_SHADER_ID];
	}
#if defined FG_USING_OPENGL
	//
	fgGfxShader *getTessControlShader(void) const {
		return m_shaders[SP_TESS_CONTROL_SHADER_ID];
	}

	//
	fgGfxShader *getTessEvaluationShader(void) const {
		return m_shaders[SP_TESS_EVALUATION_SHADER_ID];
	}

	//
	fgGfxShader *getGeometryShader(void) const {
		return m_shaders[SP_GEOMETRY_SHADER_ID];
	}

	//
	fgGfxShader *getComputeShader(void) const {
		return m_shaders[SP_COMPUTE_SHADER_ID];
	}
#endif
};

#endif /* _FG_GFX_SHADER_PROGRAM_H_ */
