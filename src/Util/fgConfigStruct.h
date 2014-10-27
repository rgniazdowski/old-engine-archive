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

    #define FG_CFG_PARAMATER_STRING_MAX		512
    #define FG_CFG_LINE_MAX				1024
    #define FG_CFG_DEFAULT_VALUE			"_default_"

struct fgCfgParameter;
struct fgCfgSection;

namespace fgCfgTypes {
    typedef std::string sectionMapKey;
    typedef std::map<sectionMapKey, fgCfgSection*> sectionMap;
    typedef std::pair<sectionMapKey, fgCfgSection*> sectionMapPair;
    typedef sectionMap::iterator sectionMapItor;

    typedef fgVector<fgCfgParameter*> parameterVec;
    typedef parameterVec::iterator parameterVecItor;

    typedef fgVector<fgCfgSection*> sectionVec;
    typedef sectionVec::iterator sectionVecItor;

    typedef std::string parameterMapKey;
    typedef std::map<parameterMapKey, fgCfgParameter*> parameterMap;
    typedef std::pair<parameterMapKey, fgCfgParameter*> parameterMapPair;
    typedef parameterMap::iterator parameterMapItor;
};

/*
 *
 */
enum fgCfgParameterType {
    FG_CFG_PARAMETER_INT, // Integer value - int
    FG_CFG_PARAMETER_LONG, // Long integer value - long int
    FG_CFG_PARAMETER_FLOAT, // Float value
    FG_CFG_PARAMETER_BOOL, // Boolean value - fgBool
    FG_CFG_PARAMETER_STRING, // String value - char array
    FG_CFG_PARAMETER_NONE // No value specified - unknow
};

/**
 *
 */
struct fgCfgParameter {
    /// Name of the parameter
    std::string name;
    /// Name of the section
    std::string sectionName;
    /// Name of the subsection in which the parameter resides
    std::string subSectionName;
    /// Parameter type (type of the value stored)
    fgCfgParameterType type;

    // Union for storing different values
    union {
        char string[FG_CFG_PARAMATER_STRING_MAX];
        long int long_val;
        float float_val;
        int int_val;
        fgBool bool_val;
    };
    fgCfgParameter() : type(FG_CFG_PARAMETER_NONE) {
        memset(string, 0, FG_CFG_PARAMATER_STRING_MAX);
    }

    // Default destructor for the configs' parameter
    ~fgCfgParameter() {
        name.clear();
        sectionName.clear();
        subSectionName.clear();
    }

    // Reset parameters' values
    void reset() {
        type = FG_CFG_PARAMETER_NONE;
        int_val = 0;
        name.clear();
        sectionName.clear();
        subSectionName.clear();
        memset(string, 0, FG_CFG_PARAMATER_STRING_MAX);
    }

    // Set the integer value for the parameter
    void set(int _int_val) {
        type = FG_CFG_PARAMETER_INT;
        int_val = _int_val;
    }

    // Set the 'long int' value for the parameter
    void set(long int _long_val) {
        type = FG_CFG_PARAMETER_LONG;
        long_val = _long_val;
    }

    // Set the float value of the parameter
    void set(float _float_val) {
        type = FG_CFG_PARAMETER_FLOAT;
        float_val = _float_val;
    }

    // Set the bool value of the parameter
    void set(fgBool _bool_val) {
        type = FG_CFG_PARAMETER_BOOL;
        bool_val = _bool_val;
    }

    // Set the string value of the parameter
    void set(const char *_string) {
        type = FG_CFG_PARAMETER_STRING;
        strncpy(string, _string, FG_CFG_PARAMATER_STRING_MAX - 1);
    }

    // Set the parameter value based on the type enum and void pointer
    fgBool set(fgCfgParameterType _type, void *_value) {
        if(!_value)
            return FG_FALSE;

        switch(_type) {
            case FG_CFG_PARAMETER_INT:
                int_val = *((int *)_value);
                break;
            case FG_CFG_PARAMETER_LONG:
                long_val = *((long int *)_value);
                break;
            case FG_CFG_PARAMETER_FLOAT:
                float_val = *((float *)_value);
                break;
            case FG_CFG_PARAMETER_BOOL:
                bool_val = *((fgBool *)_value);
                break;
            case FG_CFG_PARAMETER_STRING:
                strncpy(string, (const char *)_value, FG_CFG_PARAMATER_STRING_MAX - 1);
                break;
            case FG_CFG_PARAMETER_NONE:
                return FG_FALSE;
                break;
            default:
                return FG_FALSE;
                break;
        };
        type = _type;
        return FG_TRUE;
    }

    // Get the void* pointer to the value stored in the parameter struct - NULL if invalid
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

    // Convert value of the parameter to string. Will be stored in specified buffer. NULL on failure.
    char *valueToString(char *buf, unsigned int nmax = FG_CFG_PARAMATER_STRING_MAX) {
        if(nmax < FG_CFG_PARAMATER_STRING_MAX || !buf)
            return NULL;

        switch(type) {
            case FG_CFG_PARAMETER_INT:
                snprintf(buf, nmax, "%d", int_val);
                break;
            case FG_CFG_PARAMETER_LONG:
                snprintf(buf, nmax, "%ldL", long_val);
                break;
            case FG_CFG_PARAMETER_FLOAT:
                snprintf(buf, nmax, "%f", float_val);
                break;
            case FG_CFG_PARAMETER_BOOL:
                snprintf(buf, nmax, "%s", FG_BOOL_TO_TEXT(bool_val));
                break;
            case FG_CFG_PARAMETER_STRING:
                snprintf(buf, nmax, "\"%s\"", string);
                break;
            case FG_CFG_PARAMETER_NONE:
                return NULL;
                break;
            default:
                return NULL;
                break;
        };
        return buf;
    }

    // Convert the parameter to string. The string will be in format: name = value
    char *toString(char *buf, unsigned int nmax = FG_CFG_LINE_MAX) {
        if(!buf)
            return NULL;
        char tmp_val[FG_CFG_PARAMATER_STRING_MAX];
        if(!valueToString(tmp_val))
            return NULL;
        snprintf(buf, nmax, "%s = %s", name.c_str(), tmp_val);
        return buf;
    }
};

/*
 *
 */
struct fgCfgSection {
    // Full section name
    std::string name;
    // Name of the subsection
    std::string subName;
    // parameters vector - all parameters one after another
    fgCfgTypes::parameterVec parameters;
    // parameters map - key is the parameter name
    fgCfgTypes::parameterMap parametersMap;

    // Default empty constructor
    fgCfgSection() { }

    // Default destructor for config section
    ~fgCfgSection() {
        name.clear();
        subName.clear();
        parameters.clear_optimised();
        parametersMap.clear();
    }

    // Return the parameter with given name
    fgCfgParameter *getParameter(const char *parameterName) {
        fgCfgTypes::parameterMapKey pmkey = parameterName;
        fgCfgTypes::parameterMapItor pmit = parametersMap.find(pmkey);
        if(pmit == parametersMap.end())
            return NULL;
        return pmit->second;
    }

    //
    fgCfgParameter *getParameter(const char *parameterName, fgCfgParameterType _type) {
        fgCfgParameter *param = getParameter(parameterName);
        if(!param)
            return NULL;
        if(param->type != _type)
            return NULL;
        return param;
    }

    // Return the parameter with given name
    fgCfgParameter *getParameter(std::string & parameterName) {
        return getParameter(parameterName.c_str());
    }

    //
    fgCfgParameter *getParameter(std::string & parameterName, fgCfgParameterType _type) {
        return getParameter(parameterName.c_str(), _type);
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

    // 
    char *toString(char *buf, unsigned int nmax = FG_CFG_PARAMATER_STRING_MAX) {
        if(!buf)
            return NULL;
        snprintf(buf, nmax, "[%s]", name.c_str());
        return buf;
    }
};

#endif /* _FG_CONFIG_STRUCT_H_ */
