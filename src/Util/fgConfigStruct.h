/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_CONFIG_STRUCT_H_
#define _FG_CONFIG_STRUCT_H_

#include "fgTypes.h"

#include <string>
#include <map>

#define FG_CFG_PARAMATER_STRING_MAX 512
#define FG_CFG_DEFAULT_VALUE "_default_"

struct fgCfgParameter;
struct fgCfgSection;

namespace fgCfgTypes {
	typedef std::string sectionMapKey;
	typedef std::map<sectionMapKey, fgCfgSection*> sectionMap;
	typedef std::pair<sectionMapKey, fgCfgSection*> sectionMapPair;
	typedef sectionMap::iterator sectionMapItor;

	typedef fgArrayVector<fgCfgParameter*> parameterVec;
	typedef parameterVec::iterator parameterVecItor;

	typedef std::string parameterMapKey;
	typedef std::map<parameterMapKey, fgCfgParameter*> parameterMap;
	typedef std::pair<parameterMapKey, fgCfgParameter*> parameterMapPair;
	typedef parameterMap::iterator parameterMapItor;
};

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

	fgCfgParameter() : int_val(0), type(FG_CFG_PARAMETER_NONE) {
		memset(string, 0, FG_CFG_PARAMATER_STRING_MAX);
	}

	~fgCfgParameter() {
		name.clear();
		sectionName.clear();
		subSectionName.clear();
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
struct fgCfgSection {
	std::string name;
	// parameters vector - all parameters one after another
	fgCfgTypes::parameterVec parameters;
	// parameters map - key is the parameter name
	fgCfgTypes::parameterMap parametersMap;	

	// Default empty constructor
	fgCfgSection() { }

	// Default destructor for config section
	~fgCfgSection() {
		parameters.clear_optimised();
		parametersMap.clear();
	}
	
	// This will release all data - calls destructors
	void freeAll(void) {
		parametersMap.clear();
		while(!parameters.empty()) {
			fgCfgParameter *&param = parameters.back();
			delete param;
			param = NULL;
			parameters.pop_back();
		}
	}
};

#endif /* _FG_CONFIG_STRUCT_H_ */
