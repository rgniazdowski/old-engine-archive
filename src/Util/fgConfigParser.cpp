/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgConfigParser.h"
#include "fgMemory.h"
#include "fgStrings.h"

/*
 *
 */
fgConfigParser::fgConfigParser() : m_fileSize(0), m_fileBuffer(NULL)
{
}

/*
 *
 */
fgConfigParser::fgConfigParser(const char *filePath) : 
	m_fileSize(0),
	m_fileBuffer(NULL), 
	fgFile(filePath)
{
	loadConfig(filePath);
}

/*
 *
 */
fgBool fgConfigParser::loadConfig(const char *filePath)
{
	fgStatusReporter::clearStatus();
	if(filePath == NULL) {
		reportError(FG_WARNING, "error");
		return FG_FALSE;
	}

	if(!open(filePath, FG_FILE_MODE_READ)) {
		reportError(FG_WARNING, "could not open file config ini");
		return FG_FALSE;
	}

	m_fileSize = getSize();

	m_fileBuffer = (char *) fgMalloc(sizeof(char) * (m_fileSize+1));
	if(m_fileBuffer == NULL) {
		reportError(FG_WARNING, "m_fileBuffer is NULL");
		return FG_FALSE;
	}

	int bytesRead = read(m_fileBuffer, 1, m_fileSize);
	m_fileBuffer[m_fileSize] = '\0';
	if(bytesRead != (int)m_fileSize) {
		reportError(FG_WARNING, "if(!bytesRead != (int)m_fileSize)");
		fgFree(m_fileBuffer);
		m_fileBuffer = NULL;
		m_fileSize = 0;
		close();
		return FG_FALSE;
	}

	// Close the file
	close();
	
	// The above code is just the same as in xml parser, 
	// this could be separate function in fgFile, #TODO #FIXME #P2
	//

	// parse
	return parseData(m_fileBuffer);
}

/*
 *
 */
fgBool fgConfigParser::parseData(const char *data)
{
	if(!data) {
		if(!m_fileBuffer) {
			reportError(FG_WARNING, "Parse data file buffer error - null");
			return FG_FALSE;
		}
		data = m_fileBuffer;
	}
	std::string input = data;
	std::string sectionName;
	std::string subSectionName;
	std::string parameterName;
	fgBool isSection = FG_FALSE;

	m_parameterMap.clear();
	size_t cur;
	size_t next = std::string::npos;
	do {
		cur = next + 1;
		next = input.find("\n", cur);

		std::string line = input.substr(cur, next - cur);

		line = fgStrings::trim(line);
		if(line[0] == ';' ||
			line[0] == '#' || 
			(line[0] == '/' && line[1] == '/')) // Ignore comments
			continue;
		if(line[0] == '[') {
			isSection = true;
			sectionName = fgStrings::trim(line, "[]");
			fgArrayVector<std::string> splitSection;
			splitSection.reserve(4);
			fgStrings::split(sectionName, '.', splitSection);
			if(splitSection.size() == 1) {
				sectionName = splitSection[0];
				subSectionName.clear();
			} else if(splitSection.size()) {
				int subid = (int)splitSection.size()-1;
				int i = 0;
				sectionName.clear();
				for(;i<subid;i++) {
					sectionName += splitSection[i];
					if(i != subid-1)
						sectionName += ".";
				}
				subSectionName = splitSection[subid];
			} else {
				isSection = false;
			}
			printf("section name: %s\n", sectionName.c_str());
			if(!subSectionName.empty())
				printf("sub section name: %s\n", subSectionName.c_str());
		} else if(isSection && !sectionName.empty()) {
			// Now checking for parameters and values for given section/subsection
			// parameter = value
			// Also need to ignore comments as some lines can have this format:
			// parameter = value ; comment
			line = line.substr(0, line.find_last_of(';'));
			int eqpos = line.find_first_of('=');
			std::string parameterName = fgStrings::trim(line.substr(0,eqpos));
			std::string parameterValue = fgStrings::trim(line.substr(eqpos+1));
			printf("param value: %s = '%s'\n", parameterName.c_str(), parameterValue.c_str());
			if(parameterName.empty())
				continue;
			fgCfgParameter parameter;
			parameter.name = parameterName;
			if(!sectionName.empty())
				parameter.sectionName = sectionName;
			if(!subSectionName.empty())
				parameter.subSectionName = subSectionName;

			int quotepos = parameterValue.find_first_of("'\"");
			fgBool bool_value = FG_BOOL_FROM_TEXT(parameterValue.c_str());

			// Does the string contain quotes?
			if(quotepos != std::string::npos) {
				// it's a string value
				parameterValue = fgStrings::trim(parameterValue, "'\"");
				parameter.set(parameterValue.c_str());
			} else if(bool_value != FG_BOOL_INVALID) {
				// it's a bool value
				parameter.set(bool_value);
			} else if(fgStrings::isFloat(parameterValue)) {
				// it's a float value
				parameter.set((float)atof(parameterValue.c_str()));
			} else if(toupper((int)parameterValue[parameterValue.size()-1]) == 'L') {
				// it's probably a long int value (last digit L, like in 1230140L)
				parameter.set((long int)atol(parameterValue.c_str()));
			} else if(isdigit((int)parameterValue[0])) {
				// it's probably an int value
				parameter.set(atoi(parameterValue.c_str()));
			} else {
				parameter.set("__INVALID__"); // #FIXME
			}
			parameterMapKey key;
			if(subSectionName.empty())
				key.first = sectionName;
			else
				key.first = subSectionName;
			key.second = parameterName;
			m_parameterMap[key] = parameter;
		}
	} while (next != std::string::npos);
	if(m_parameterMap.empty())
		return FG_FALSE;
	return FG_TRUE;
}

/*
 * Free all data assiocated with the config parameters
 */
void fgConfigParser::freeConfig(void)
{
	if(m_fileBuffer)
		fgFree(m_fileBuffer);
	m_fileSize = 0;
	m_parameterMap.clear();
}

/*
 *
 */
void *fgConfigParser::getParameterValue(const char *sectionName, const char *parameterName)
{
	if(!sectionName || !parameterName)
		return NULL;
	if(m_parameterMap.empty())
		return NULL;
	parameterMapKey key;
	key.first = sectionName;
	key.second = parameterName;
	parameterMapItor it = m_parameterMap.find(key);
	if(it == m_parameterMap.end())
		return NULL;
	if(0 != it->second.name.compare(parameterName))
		return NULL;
	return it->second.get();
}

/*
 *
 */
int fgConfigParser::getParameterInt(const char *sectionName, const char *parameterName, fgBool *status)
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
long int fgConfigParser::getParameterLong(const char *sectionName, const char *parameterName, fgBool *status)
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
float fgConfigParser::getParameterFloat(const char *sectionName, const char *parameterName, fgBool *status)
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
fgBool fgConfigParser::getParameterBool(const char *sectionName, const char *parameterName, fgBool *status)
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
char *fgConfigParser::getParameterString(const char *sectionName, const char *parameterName)
{
	void *ptr = getParameterValue(sectionName, parameterName);
	if(!ptr)
		return NULL;
	return (char *)ptr;
}
