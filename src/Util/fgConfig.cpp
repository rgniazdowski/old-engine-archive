/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgConfig.h"
#include "fgException.h"

/*
 *
 */
fgConfig::fgConfig() : m_parser(NULL), m_writer(NULL)
{
}

/*
 *
 */
fgConfig::fgConfig(const char *filePath) : m_parser(NULL), m_writer(NULL)
{
	if(filePath)
		load(filePath);
}

/*
 *
 */
fgConfig::~fgConfig()
{
	if(m_parser)
		delete m_parser;
	if(m_writer)
		delete m_writer;
	clearAll();
}
#include <vector>
/*
 *
 */
fgBool fgConfig::load(const char *filePath)
{
	if(!filePath) {
		if(m_filePath.empty())
			return FG_FALSE;
		filePath = m_filePath.c_str();
	} else {
		m_filePath.clear();
		m_filePath = filePath;
	}

	if(!m_parser)
		m_parser = new fgConfigParser();
	clearAll();
	if(!m_parser->load(filePath, m_sectionMap)) {
		return FG_FALSE;
	}
	
	fgCfgTypes::sectionMapItor it = m_sectionMap.begin(),
		end = m_sectionMap.end();
	for(;it!=end; it++) {
		fgCfgSection *section = it->second;
		if(!section) continue;
		for(unsigned int i=0;i<section->parameters.size();i++)
			m_parameterVec.push_back(section->parameters[i]);
	}
	return FG_TRUE;
}

/*
 *
 */
fgBool fgConfig::save(const char *filePath)
{
	if(!filePath) {
		if(m_filePath.empty())
			return FG_FALSE;
		filePath = m_filePath.c_str();
	} else {
		m_filePath.clear();
		m_filePath = filePath;
	}

	if(!m_writer)
		m_writer = new fgConfigWriter();

	// // // // // 

	return FG_TRUE;
}

/*
 *
 */
void fgConfig::clearAll(void)
{
	m_filePath.clear();
	if(!m_sectionMap.empty()) {
		fgCfgTypes::sectionMapItor it = m_sectionMap.begin(),
			end = m_sectionMap.end();
		for(;it!=end;it++)
		{
			fgCfgSection *section = it->second;
			section->freeAll();
			delete section;
			m_sectionMap[it->first] = NULL;
		}
	}
	m_sectionMap.clear();
	m_parameterVec.clear_optimised();
}

/*
 *
 */
fgCfgSection *fgConfig::getSection(const char *sectionName)
{
	if(!sectionName)
		return NULL;
	if(m_sectionMap.empty())
		return NULL;
	fgCfgTypes::sectionMapKey smkey = sectionName;
	fgCfgTypes::sectionMapItor smit = m_sectionMap.find(smkey);
	if(smit == m_sectionMap.end())
		return NULL;
	
	return smit->second;
}

/*
 *
 */
fgCfgTypes::parameterMap & fgConfig::getRefSectionsParameterMap(const char *sectionName)
{
	if(!sectionName)
		throw fgException(FG_ERRNO_WRONG_PARAM);
	fgCfgSection *section = getSection(sectionName);
	if(!section)
		throw fgException(FG_ERRNO_NOT_FOUND);
	return section->parametersMap;		
}

/*
 *
 */
fgCfgTypes::parameterVec & fgConfig::getRefSectionsParameterVec(const char *sectionName)
{
	if(!sectionName)
		throw fgException(FG_ERRNO_WRONG_PARAM);
	fgCfgSection *section = getSection(sectionName);
	if(!section)
		throw fgException(FG_ERRNO_NOT_FOUND);
	return section->parameters;
}


/*
 *
 */
void *fgConfig::getParameterValue(const char *sectionName, const char *parameterName)
{
	if(!sectionName || !parameterName)
		return NULL;
	fgCfgSection *section = getSection(sectionName);
	if(!section)
		return NULL;
	fgCfgTypes::parameterMapKey pmkey = parameterName;
	fgCfgTypes::parameterMapItor pmit = section->parametersMap.find(pmkey);
	if(pmit == section->parametersMap.end())
		return NULL;
	return pmit->second->get();
}

/*
 *
 */
int fgConfig::getParameterInt(const char *sectionName, const char *parameterName, fgBool *status)
{
	void *ptr = getParameterValue(sectionName, parameterName);
	if(!ptr) {
		if(status)
			*status = FG_FALSE;
		return -1;
	}
	int *int_ptr = (int *)ptr;
	if(status)
		*status = FG_TRUE;
	return *int_ptr;
}

/*
 *
 */
long int fgConfig::getParameterLong(const char *sectionName, const char *parameterName, fgBool *status)
{
	void *ptr = getParameterValue(sectionName, parameterName);
	if(!ptr) {
		if(status)
			*status = FG_FALSE;
		return -1L;
	}
	long int *long_ptr = (long int *)ptr;
	if(status)
		*status = FG_TRUE;
	return *long_ptr;
}

/*
 *
 */
float fgConfig::getParameterFloat(const char *sectionName, const char *parameterName, fgBool *status)
{
	void *ptr = getParameterValue(sectionName, parameterName);
	if(!ptr) {
		if(status)
			*status = FG_FALSE;
		return -1.0f;
	}
	float *float_ptr = (float *)ptr;
	if(status)
		*status = FG_TRUE;
	return *float_ptr;
}

/*
 *
 */
fgBool fgConfig::getParameterBool(const char *sectionName, const char *parameterName, fgBool *status)
{
	void *ptr = getParameterValue(sectionName, parameterName);
	if(!ptr) {
		if(status)
			*status = FG_FALSE;
		return FG_FALSE;
	}
	fgBool *bool_ptr = (fgBool *)ptr;
	if(status)
		*status = FG_TRUE;
	return *bool_ptr;
}

/*
 *
 */
char *fgConfig::getParameterString(const char *sectionName, const char *parameterName)
{
	void *ptr = getParameterValue(sectionName, parameterName);
	if(!ptr)
		return NULL;
	return (char *)ptr;
}
