/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_CONFIG_PARSER_H_
#define _FG_CONFIG_PARSER_H_

#include "fgTypes.h"

#include <string>
#include <map>

#include "fgStatus.h"
#include "fgFile.h"

#define FG_CFG_PARAMATER_STRING_MAX 512

/*
 *
 */
enum fgCfgParameterType {
	FG_CFG_PARAMETER_INT,
	FG_CFG_PARAMETER_LONG,
	FG_CFG_PARAMETER_FLOAT,
	FG_CFG_PARAMETER_BOOL,
	FG_CFG_PARAMETER_STRING,
	FG_CFG_PARAMETER_NONE
};

/*
 *
 */
struct fgCfgParameter
{
	std::string name;
	std::string sectionName;
	std::string subSectionName;
	fgCfgParameterType type;

	union {
		int int_val;
		long int long_val;
		float float_val;
		fgBool bool_val;
		char string[FG_CFG_PARAMATER_STRING_MAX];
	};

	fgCfgParameter() : int_val(0) {
		memset(string, 0, FG_CFG_PARAMATER_STRING_MAX);
	}

	void reset() {
		type = FG_CFG_PARAMETER_NONE;
		int_val = 0;
		name.clear();
		sectionName.clear();
		subSectionName.clear();
		memset(string, 0, FG_CFG_PARAMATER_STRING_MAX);
	}

	void set(int _int_val) {
		type = FG_CFG_PARAMETER_INT;
		int_val = _int_val;
	}

	void set(long int _long_val) {
		type = FG_CFG_PARAMETER_LONG;
		long_val = _long_val;
	}

	void set(float _float_val) {
		type = FG_CFG_PARAMETER_FLOAT;
		float_val = _float_val;
	}

	void set(fgBool _bool_val) {
		type = FG_CFG_PARAMETER_BOOL;
		bool_val = _bool_val;
	}

	void set(const char *_string) {
		type = FG_CFG_PARAMETER_STRING;
		strncpy(string, _string, FG_CFG_PARAMATER_STRING_MAX-1);
	}

	void *get(void) {
		switch(type) {
		case FG_CFG_PARAMETER_INT:
			return (void *)&int_val;
			break;
		case FG_CFG_PARAMETER_LONG:
			return (void *)&long_val;
			break;
		case FG_CFG_PARAMETER_FLOAT:
			return (void *)&float_val;
			break;
		case FG_CFG_PARAMETER_BOOL:
			return (void *)&bool_val;
			break;
		case FG_CFG_PARAMETER_STRING:
			return (void *)string;
			break;
		case FG_CFG_PARAMETER_NONE:
			break;
		default:
			break;
		};
		return NULL;
	}
};

/*
 *
 */
class fgConfigParser : protected fgFile
{
public:
	typedef std::pair<std::string, std::string> parameterMapKey;
	typedef std::map<parameterMapKey, fgCfgParameter> parameterMap;
	typedef std::pair<parameterMapKey, fgCfgParameter> parameterMapPair;
	typedef parameterMap::iterator parameterMapItor;

protected:
	// Loaded file size
	unsigned int m_fileSize;
	// Data buffer
	char *m_fileBuffer;
	// Mapped values: Key is a pair of <section name, parameter name>
	// Remember that in this implementation of INI configs, section name can
	// be split into parts: section and sub section. Delimeter is a '.' (point); Example:
	// 'Settings' -> section: 'Settings', subsection: empty
	// 'Settings.debug' -> section: 'Settings', subsection: 'debug'
	// 'Settings.GFX.Textures' -> section: 'Settings.GFX', subsection: 'Textures'
	// Section used in map key is always the last part (subsection or section name if one part exists)
	parameterMap m_parameterMap;

public:
	// Default constructor for config parser object
	fgConfigParser();
	// Constructor with file path parameter - this will load config
	fgConfigParser(const char *filePath);

	// Default destructor for config parser object
	~fgConfigParser() {
		freeConfig();
	}

	// Load config and store all parameters in special parameter map
	fgBool loadConfig(const char *filePath);

	// Parse data
	fgBool parseData(const char *data);

	// Free all data assiocated with the config parameters
	void freeConfig(void);

	// Is config loaded? Is there any element in the map?
	fgBool isConfigLoaded(void) {
		return (fgBool)(!m_parameterMap.empty());
	}

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

	// Return the reference to internal parameter map
	parameterMap & getRefParameterMap(void) {
		return m_parameterMap;
	}

	/*******************************************************
	 * These function are here because ConfigParser extends
	 * fgFile with access level protected. Need to make
	 * public methods of status reporter available. #FIXME
	 */

	fgBool isError(void) const {
		return fgStatusReporter::isError();
	}

	int getErrorCode(void) const {
		return fgStatusReporter::getErrorCode();
	}

	int getLastErrorCode(void) const {
		return fgStatusReporter::getLastErrorCode();
	}

	void setReportToMsgSystem(fgBool _set) {
		fgStatusReporter::setReportToMsgSystem(_set);
	}

	fgStatus *getLastStatus(void) const {
		return fgStatusReporter::getLastStatus();
	}
};

#endif /* _FG_CONFIG_PARSER_H_ */
