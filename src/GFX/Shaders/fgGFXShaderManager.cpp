/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXShaderManager.h"
#include "GFX/fgGFXErrorCodes.h"
#include "Util/fgFile.h"
#include "Util/fgDirent.h"

/*
 *
 */
fgGfxShaderManager::fgGfxShaderManager() : 
	m_shadersPath(),
	m_currentProgram(NULL)
{
	m_managerType = FG_MANAGER_GFX_SHADER;
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
	fgGfxShaderManager::clearStatus();
	m_currentProgram = NULL;
	m_shadersPath.clear();
	releaseAllHandles();
	m_managerType = FG_MANAGER_GFX_SHADER;
}

/*
 *
 */
fgBool fgGfxShaderManager::destroy(void)
{
	FG_LOG::PrintDebug("BEG: fgGfxShaderManager::destroy();");
	smProgramVec & data = getRefDataVector();
	hmDataVecItor begin = data.begin(), end = data.end(), itor = begin;
	for(;itor!=end;++itor) {
		if((*itor) == NULL)
			continue;
		delete (*itor);
		*itor = NULL;
	}
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
fgBool fgGfxShaderManager::insert(fgGfxShaderHandle& phUniqueID, fgGfxShaderProgram *pProgram, const std::string& nameTag)
{
	if(!pProgram)
		return FG_FALSE;
	if(fgDataManagerBase::insert(phUniqueID, pProgram, nameTag)) {
		pProgram->setManaged(FG_TRUE);
		pProgram->setManager(this);
		return FG_TRUE;
	}
	return FG_FALSE;
}

/*
 *
 */
fgBool fgGfxShaderManager::insertProgram(fgGfxShaderHandle& phUniqueID, fgGfxShaderProgram *pProgram)
{
	return insert(phUniqueID, pProgram, pProgram->getName());
}

/*
 *
 */
fgGfxShaderProgram *fgGfxShaderManager::request(const std::string& info)
{
	return NULL;
}

/*
 *
 */
fgGfxShaderProgram *fgGfxShaderManager::request(const char *info)
{
	return NULL;
}

/*
 *
 */
fgGfxShaderProgram *fgGfxShaderManager::getCurrentProgram(void) const
{
	return m_currentProgram;
}

/*
 *
 */
void fgGfxShaderManager::setShadersPath(const std::string &path)
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
	begin = getRefDataVector().begin();	end = getRefDataVector().end();	itor = begin;
	for(;itor!=end;itor++) {
		fgGfxShaderProgram *pProgram = *itor;
		if(!pProgram)
			continue;
		if(!pProgram->compile()) {
			status = FG_FALSE;
		}
	}
	if(status)
		reportSuccess(FG_ERRNO_GFX_OK, "All shader programs compiled successfully");
	else
		reportWarning(FG_ERRNO_GFX_OK, "Problem occured when compiling shader programs");
	return status;
}

/*
 *
 */
fgBool fgGfxShaderManager::linkShaders(void)
{
	fgGfxShaderManager::clearStatus();
	if(!m_init) {
		return FG_FALSE;
	}
	fgBool status = FG_TRUE;
	smProgramVecItor begin, end, itor;
	begin = getRefDataVector().begin();	end = getRefDataVector().end();	itor = begin;
	for(;itor!=end;itor++) {
		fgGfxShaderProgram *pProgram = *itor;
		if(!pProgram)
			continue;
		if(!pProgram->link()) {
			status = FG_FALSE;
		}
	}
	if(status)
		reportSuccess(FG_ERRNO_GFX_OK, "All shader programs linked successfully");
	else
		reportWarning(FG_ERRNO_GFX_OK, "Problem occured when linking shader programs");
	return status;
}

/*
 *
 */
fgBool fgGfxShaderManager::allReleaseGFX(void)
{
	fgGfxShaderManager::clearStatus();
	if(!m_init) {
		return FG_FALSE; // ERROR ?
	}
	fgBool status = FG_TRUE;
	smProgramVecItor begin, end, itor;
	begin = getRefDataVector().begin();	end = getRefDataVector().end();	itor = begin;
	for(;itor!=end;itor++) {
		fgGfxShaderProgram *pProgram = *itor;
		if(!pProgram)
			continue;
		if(!pProgram->releaseGFX()) {
			status = FG_FALSE;
		}
	}
	if(status)
		reportSuccess(FG_ERRNO_GFX_OK, "All shader programs released successfully");
	else
		reportWarning(FG_ERRNO_GFX_OK, "Problem occured when releasing shader programs");
	return status;
}

/*
 *
 */
fgBool fgGfxShaderManager::useProgram(fgGfxShaderProgram *pProgram)
{
	if(!pProgram)
		return FG_FALSE;
	if(pProgram->use()) {
		m_currentProgram = pProgram;
	}
	return FG_FALSE;
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
	if(pProgram == m_currentProgram)
		return FG_FALSE;
	m_currentProgram = pProgram;
	return pProgram->use();
}

/*
 *
 */
fgBool fgGfxShaderManager::useProgram(const std::string &nameTag)
{
	fgGfxShaderProgram *pProgram = dereference(nameTag);
	if(!pProgram) {
		return FG_FALSE;
	}
	if(pProgram == m_currentProgram)
		return FG_FALSE;
	m_currentProgram = pProgram;
	return pProgram->use();
}

/*
 *
 */
fgBool fgGfxShaderManager::useProgram(const char *nameTag)
{
	fgGfxShaderProgram *pProgram = dereference(nameTag);
	if(!pProgram) {
		return FG_FALSE;
	}
	if(pProgram == m_currentProgram)
		return FG_FALSE;
	m_currentProgram = pProgram;
	return pProgram->use();
}

/*
 *
 */
fgBool fgGfxShaderManager::isProgramUsed(fgGfxShaderProgram *pProgram)
{
	if(m_currentProgram && m_currentProgram == pProgram) {
		if(m_currentProgram->getGfxID() == pProgram->getGfxID())
			return FG_TRUE;
	}
	return FG_FALSE;
}

/*
 *
 */
fgBool fgGfxShaderManager::isProgramUsed(fgGfxShaderHandle spUniqueID)
{
	fgGfxShaderProgram *pProgram = dereference(spUniqueID);
	return fgGfxShaderManager::isProgramUsed(pProgram);
}

/*
 *
 */
fgBool fgGfxShaderManager::isProgramUsed(const std::string &nameTag)
{
	fgGfxShaderProgram *pProgram = dereference(nameTag);
	return fgGfxShaderManager::isProgramUsed(pProgram);
}

/*
 *
 */
fgBool fgGfxShaderManager::isProgramUsed(const char *nameTag)
{
	fgGfxShaderProgram *pProgram = dereference(nameTag);
	return fgGfxShaderManager::isProgramUsed(pProgram);
}
