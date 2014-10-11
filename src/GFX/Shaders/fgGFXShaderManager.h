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
#include "Resource/fgDataManagerBase.h"

#include "Util/fgHandleManager.h"
#include "Util/fgTag.h"
#include "fgGFXShaderProgram.h"

class fgGfxShaderManager;

#define FG_TAG_SHADER_MANAGER_NAME		"GfxShaderManager"
//#define FG_TAG_MANAGER_BASE_ID		20 //#FIXME - something automatic maybe?
#define FG_TAG_SHADER_MANAGER			FG_TAG_TYPE(fgGfxShaderManager)

//FG_TAG_TEMPLATE(fgResourceManager, FG_TAG_MANAGER_BASE_NAME, FG_TAG_MANAGER_BASE_ID);
FG_TAG_TEMPLATE_ID_AUTO(fgGfxShaderManager, FG_TAG_SHADER_MANAGER_NAME);

// Special handle type for manager base
typedef FG_TAG_SHADER_MANAGER fgGfxShaderManagerTag;

#define FG_MANAGER_GFX_SHADER	0x00000002

/*
 *
 */
class fgGfxShaderManager : public fgDataManagerBase<fgGfxShaderProgram*, fgGfxShaderHandle, fgGfxShaderManagerTag>
{
protected:
	typedef hmDataVec					smProgramVec;
	typedef hmDataVec::iterator		smProgramVecItor;
public:
	// Default constructor for the shader manager object
	fgGfxShaderManager();
	// Default destructor for the shader manager object
	virtual ~fgGfxShaderManager();

protected:
	//	
	void clear(void);

public:
	// Destroy the shader manager and all managed data (destructors called - every handle becomes invalid)
	fgBool destroy(void);

	// Initialize the shader manager
	fgBool initialize(void);
	
	// Pre load / pre cache the required shaders
	fgBool preLoadShaders(void);

	// This will compile all shader programs (no linking will occur)
	fgBool compileShaders(void);

	// This will link all shader programs (compile will occur if needed)
	fgBool linkShaders(void);

	// This will make all gfx IDs invalid (free gfx side data)
	fgBool allReleaseGFX(void);

	//
	fgBool isProgramUsed(fgGfxShaderProgram *pProgram);
	//
	fgBool isProgramUsed(fgGfxShaderHandle spUniqueID);
	//
	fgBool isProgramUsed(const std::string &nameTag);
	//
	fgBool isProgramUsed(const char *nameTag);

	//
	fgBool useProgram(fgGfxShaderProgram *pProgram);
	//
	fgBool useProgram(fgGfxShaderHandle spUniqueID);
	//
	fgBool useProgram(const std::string &nameTag);
	//
	fgBool useProgram(const char *nameTag);

	//
	virtual fgBool insert(fgGfxShaderHandle& phUniqueID, fgGfxShaderProgram *pProgram, const std::string& nameTag);

	// Insert the specified shader program into the manager
	virtual fgBool insertProgram(fgGfxShaderHandle& phUniqueID, fgGfxShaderProgram *pProgram);

	//
	void setShadersPath(const std::string &path);
	//
	void setShadersPath(const char *path);

	// 
	virtual fgGfxShaderProgram *request(const std::string& info);
	// 
	virtual fgGfxShaderProgram *request(const char *info);

	fgGfxShaderProgram *getCurrentProgram(void) const;
private:
	//
	std::string		m_shadersPath;
	/// Pointer to shader program object which is being currently used
	/// For double checking - after GFX suspend/resume program ID
	/// will become invalid, need to set this pointer to NULL on suspend
	fgGfxShaderProgram *m_currentProgram;
	
};

#endif /* _FG_GFX_SHADER_MANAGER_H_ */
