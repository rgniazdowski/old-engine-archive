/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_SHADER_MANAGER_H_
#define _FG_GFX_SHADER_MANAGER_H_

#ifdef _FG_GFX_STD_INC_BLOCK__
#error "FG_GFX_STD_INC_BLOCK constant is defined. Do not include GfxShaderManager inside of Gfx Standard Include header."
#endif

#include "GFX/fgGFXStdInc.h"
#include "fgManagerBase.h"

#include "Util/fgHandleManager.h"
#include "fgGFXShaderProgram.h"

/*
 *
 */
class fgGfxShaderManager : public fgManagerBase
{
protected:
	typedef fgHandleManager<fgGfxShaderProgram*, fgGfxShaderProgramHandle>	smHandleManager;
	typedef smHandleManager::hmDataVec					smProgramVec;
	typedef smHandleManager::hmDataVec::iterator		smProgramVecItor;
protected:
	/// 
	smHandleManager		m_programHandlesMgr;
public:
	// 
	fgGfxShaderManager() {}
	// 
	virtual ~fgGfxShaderManager() {}

	// 
	void clear(void) {}
	//
	void destroy(void) {}

	//
	fgBool initialize(void) { return FG_FALSE; }
	
	//
	fgBool preLoadShaders(void) { return FG_FALSE; }

};

#endif /* _FG_GFX_SHADER_MANAGER_H_ */
