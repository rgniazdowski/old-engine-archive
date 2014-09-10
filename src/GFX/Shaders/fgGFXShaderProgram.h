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

/*
 *
 */
class fgGfxShaderProgram : public fgStatusReporter<fgGfxShaderProgramTag> {
public:
	typedef fgArrayVector<fgGfxShader *>	shaderVec;
	typedef shaderVec::iterator				shaderVecItor;
protected:
	///
	fgGFXuint					m_programGfxID;
	///
	shaderVec					m_shaders;
	///
	fgGfxShaderConfig*			m_config;
	///
	std::string					m_programName;
	///
	fgGfxShaderProgramHandle	m_handle;
public:
	//
	fgGfxShaderProgram();
	//
	virtual ~fgGfxShaderProgram();

	//
	fgBool preLoadConfig(const char *path);

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
	fgGFXuint & getRefProgramGfxID(void) {
		return m_programGfxID;
	}
};

#endif /* _FG_GFX_SHADER_PROGRAM_H_ */
