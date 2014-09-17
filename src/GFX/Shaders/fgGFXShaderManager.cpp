/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXShaderManager.h"
#include "Util/fgFile.h"
#include "Util/fgDirent.h"

/*
 *
 */
fgGfxShaderManager::fgGfxShaderManager()
{
	setReportToMsgSystem(FG_TRUE);
}

/*
 *
 */
fgGfxShaderManager::~fgGfxShaderManager()
{
	destroy();
}

/*
 *
 */
void fgGfxShaderManager::clear(void)
{
	FG_LOG::PrintDebug("fgGfxShaderManager::clear() - call to: fgGfxShaderManager::clearStatus();");
	fgGfxShaderManager::clearStatus();
	FG_LOG::PrintDebug("fgGfxShaderManager::clear() - call to: m_shadersPath.clear();");
	m_shadersPath.clear();
	FG_LOG::PrintDebug("fgGfxShaderManager::clear() - Going to call releaseAllHandles();");
	releaseAllHandles();
	FG_LOG::PrintDebug("END fgGfxShaderManager::clear() - finito ");
}

/*
 *
 */
fgBool fgGfxShaderManager::destroy(void)
{
	FG_LOG::PrintDebug("BEG: fgGfxShaderManager::destroy();");
	smProgramVec & data = getRefDataVector();
	hmDataVecItor begin = data.begin();
	hmDataVecItor end = data.end();
	std::stack<fgGfxShaderProgram *> stak;
	for(hmDataVecItor itor = begin; itor != end ; ++itor) {
		if((*itor) == NULL)
			continue;
		fgGfxShaderProgram *program = (*itor);
		stak.push(program);
		FG_LOG::PrintDebug("Pushing to del stak prox: %s", program->getNameStr());
	}
	int staksize = stak.size();
	FG_LOG::PrintDebug("Shader proxes on stak: %d", staksize);
	int i = 0;
	while(!stak.empty()) {
		i++;
		fgGfxShaderProgram *program = stak.top();
		FG_LOG::PrintDebug("[%d] Deleting shader prox '%s'", i, program->getNameStr());
		stak.pop();
		delete program;
		program = NULL;
	};
	FG_LOG::PrintDebug("fgGfxShaderManager::destroy() - Going to call clear()");
	fgGfxShaderManager::clear();
	FG_LOG::PrintDebug("END: fgGfxShaderManager::destroy();");
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderManager::initialize(void)
{
	return preLoadShaders();
}

/*
 *
 */
fgBool fgGfxShaderManager::preLoadShaders(void)
{
	fgGfxShaderManager::clearStatus();
	if(m_shadersPath.empty()) {
		return FG_FALSE;
	}
	if(!fgFile::exists(m_shadersPath)) {
		return FG_FALSE;
	}

	m_init = FG_FALSE;
	fgDirent *shadersDir = new fgDirent();
	shadersDir->readDirectory(m_shadersPath);
	const char *filename = NULL;
	fgStringVector shProgramCfgs;
	while((filename = shadersDir->getNextFile()) != NULL) {
		const char *ext = fgPath::fileExt(filename, FG_TRUE);
		if(!ext)
			continue;
		if(strcasecmp(ext, FG_GFX_SHADER_CONFIG_PROGRAM_STD_SUFFIX) == 0) {
			shProgramCfgs.push_back(fgPath::join(m_shadersPath, std::string(filename)));
		}
	}
	delete shadersDir; shadersDir = NULL;

	fgStringVector::iterator begin, end, itor;
	begin = shProgramCfgs.begin(); end = shProgramCfgs.end();
	itor = begin;
	for(;itor!=end;itor++) {
		fgGfxShaderProgram *pProgram = new fgGfxShaderProgram();
		if(!pProgram->preLoadConfig(*itor)) {
			delete pProgram; pProgram = NULL;
			continue;
		}
		if(!insertProgram(pProgram->getRefHandle(), pProgram)) {
			releaseHandle(pProgram->getHandle());
			delete pProgram; pProgram = NULL;
			continue;
		}
	}
	shProgramCfgs.clear_optimised();
	m_init = FG_TRUE;
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderManager::insertProgram(fgGfxShaderHandle& phUniqueID, fgGfxShaderProgram *pProgram)
{
	if(!pProgram) {
		return FG_FALSE;
	}

	if(!insert(phUniqueID, pProgram, pProgram->getName())) {
		return FG_FALSE;
	}

	return FG_TRUE;
}

/*
 *
 */
void fgGfxShaderManager::setShadersPath(std::string &path)
{
	m_shadersPath = path;
}

/*
 *
 */
void fgGfxShaderManager::setShadersPath(const char *path)
{
	m_shadersPath = path;
}

/*
 *
 */
fgBool fgGfxShaderManager::compileShaders(void)
{
	fgGfxShaderManager::clearStatus();
	if(!m_init) {
		return FG_FALSE;
	}
	fgBool status = FG_TRUE;
	smProgramVecItor begin, end, itor;
	begin = getRefDataVector().begin();
	end = getRefDataVector().end();
	itor = begin;
	for(;itor!=end;itor++) {
		fgGfxShaderProgram *pProgram = *itor;
		if(!pProgram)
			continue;
		if(!pProgram->compile()) {
			status = FG_FALSE;
		}
	}
	return status;
}

/*
 *
 */
fgBool fgGfxShaderManager::useProgram(fgGfxShaderHandle spUniqueID)
{
	fgGfxShaderProgram *pProgram = dereference(spUniqueID);
	if(!pProgram) {
		return FG_FALSE;
	}
	return pProgram->use();
}

/*
 *
 */
fgBool fgGfxShaderManager::useProgram(std::string &nameTag)
{
	fgGfxShaderProgram *pProgram = dereference(nameTag);
	if(!pProgram) {
		return FG_FALSE;
	}
	return pProgram->use();
}
