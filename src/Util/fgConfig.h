/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_CONFIG_H_
#define _FG_CONFIG_H_

#include "fgConfigStruct.h"
#include "fgConfigParser.h"
#include "fgConfigWriter.h"

// some kind of status reporter ? ....

/*
 *
 */
class fgConfig
{
protected:
	//
	fgConfigParser *m_parser;
	//
	fgConfigWriter *m_writer;
	//
	fgCfgTypes::sectionMap m_sectionMap;
	//
	fgCfgTypes::parameterVec m_parameterVec;
	//
	std::string m_filePath;
public:
	//
	fgConfig();
	//
	fgConfig(const char *filePath);
	//
	virtual ~fgConfig();

	//
	void refreshParameterVec(void);
	//
	virtual fgBool load(const char *filePath = NULL);
	//
	fgBool save(const char *filePath = NULL);

	//
	void clearAll(void);

	// Return the void* pointer to parameter value. NULL if there is no such parameter.
	void *getParameterValue(const char *sectionName, const char *parameterName);
	// Return the int value of the parameter. status will be set to NULL if there is no such parameter.
	int getParameterInt(const char *sectionName, const char *parameterName, fgBool *status = NULL);
	// Return the int value of the parameter. status will be set to NULL if there is no such parameter.
	long int getParameterLong(const char *sectionName, const char *parameterName, fgBool *status = NULL);
	// Return the float value of the paramater.
	float getParameterFloat(const char *sectionName, const char *parameterName, fgBool *status = NULL);
	// Return the float value of the paramater.
	fgBool getParameterBool(const char *sectionName, const char *parameterName, fgBool *status = NULL);
	// Return the pointer to string value of the paramater. NULL if there is no such parameter.
	char *getParameterString(const char *sectionName, const char *parameterName);

	//
	fgBool setParameterValue(const char *sectionName, const char *parameterName, fgCfgParameterType type, void *value, fgBool freeInValue = FG_FALSE);
	//
	fgBool setParameterInt(const char *sectionName, const char *parameterName, int value);
	//
	fgBool setParameterLong(const char *sectionName, const char *parameterName, long int value);
	//
	fgBool setParameterFloat(const char *sectionName, const char *parameterName, float value);
	//
	fgBool setParameterBool(const char *sectionName, const char *parameterName, fgBool value);
	//
	fgBool setParameterString(const char *sectionName, const char *parameterName, const char *value);

	// Return the reference to internal section map
	fgCfgTypes::sectionMap & getRefSectionMap(void) {
		return m_sectionMap;
	}
	// Return the reference to internal parameter vector
	fgCfgTypes::parameterVec & getRefParameterVec(void) {
		return m_parameterVec;
	}

	// Return pointer to section structure
	fgCfgSection *getSection(const char *sectionName);

	// Return the reference to the given sections parameter map
	fgCfgTypes::parameterMap & getRefSectionsParameterMap(const char *sectionName);

	// Return the reference to the given sections parameter vector
	fgCfgTypes::parameterVec & getRefSectionsParameterVec(const char *sectionName);
};

#endif /* _FG_CONFIG_H_ */
