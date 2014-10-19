/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgConfig.h"
#include "fgMemory.h"
#include "fgException.h"

/*
 *
 */
fgConfig::fgConfig() : m_parser(NULL), m_writer(NULL) { }

/*
 *
 */
fgConfig::fgConfig(const char *filePath) : m_parser(NULL), m_writer(NULL) {
    if(filePath)
        fgConfig::load(filePath); // #FIXME
}

/*
 *
 */
fgConfig::~fgConfig() {
    if(m_parser)
        delete m_parser;
    m_parser = NULL;
    if(m_writer)
        delete m_writer;
    m_writer = NULL;
    clearAll();
}

/*
 *
 */
void fgConfig::refreshParameterVec(void) {
    m_parameterVec.clear_optimised();
    fgCfgTypes::sectionMapItor it = m_sectionMap.begin(),
            end = m_sectionMap.end();
    for(; it != end; it++) {
        fgCfgSection *section = it->second;
        if(!section) continue;
        for(unsigned int i = 0; i < section->parameters.size(); i++) {
            m_parameterVec.push_back(section->parameters[i]);
        }
    }
}

/*
 *
 */
fgBool fgConfig::load(const char *filePath) {
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
    fgConfig::clearAll();
    if(!m_parser->load(filePath, m_sectionMap)) {
        return FG_FALSE;
    }

    refreshParameterVec();
    return FG_TRUE;
}

/*
 *
 */
fgBool fgConfig::save(const char *filePath) {
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

    if(!m_writer->save(filePath, m_sectionMap)) {
        return FG_FALSE;
    }

    return FG_TRUE;
}

/*
 *
 */
void fgConfig::clearAll(void) {
    if(!m_sectionMap.empty()) {
        m_filePath.clear();
        fgCfgTypes::sectionMapItor it = m_sectionMap.begin(),
                end = m_sectionMap.end();
        for(; it != end; it++) {
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
fgCfgSection *fgConfig::getSection(const char *sectionName) {
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
fgCfgSection *fgConfig::getSection(const std::string & sectionName) {
    return getSection(sectionName.c_str());
}

/*
 *
 */
int fgConfig::getSectionsWith(fgCfgTypes::sectionVec & sectionsVec, const char *sectionNameBegin) {
    if(!sectionNameBegin || m_sectionMap.empty()) {
        return 0;
    }

    fgCfgTypes::sectionMapItor begin = m_sectionMap.begin(), end = m_sectionMap.end();
    fgCfgTypes::sectionMapItor smit = begin;
    std::string prefix = sectionNameBegin;
    int prefixLen = (int)prefix.length();
    for(; smit != end; smit++) {
        if(smit->second->name.substr(0, prefixLen).compare(prefix) == 0)
            sectionsVec.push_back(smit->second);
    }
    return sectionsVec.size();
}

/*
 *
 */
fgCfgTypes::parameterMap & fgConfig::getRefSectionsParameterMap(const char *sectionName) {
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
fgCfgTypes::parameterVec & fgConfig::getRefSectionsParameterVec(const char *sectionName) {
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
void *fgConfig::getParameterValue(const char *sectionName, const char *parameterName) {
    if(!sectionName || !parameterName)
        return NULL;
    fgCfgSection *section = getSection(sectionName);
    if(!section)
        return NULL;
    fgCfgParameter *parameter = section->getParameter(parameterName);
    if(!parameter)
        return NULL;
    return parameter->get();
}

/*
 *
 */
int fgConfig::getParameterInt(const char *sectionName, const char *parameterName, fgBool *status) {
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
long int fgConfig::getParameterLong(const char *sectionName, const char *parameterName, fgBool *status) {
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
float fgConfig::getParameterFloat(const char *sectionName, const char *parameterName, fgBool *status) {
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
fgBool fgConfig::getParameterBool(const char *sectionName, const char *parameterName, fgBool *status) {
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
char *fgConfig::getParameterString(const char *sectionName, const char *parameterName) {
    void *ptr = getParameterValue(sectionName, parameterName);
    if(!ptr)
        return NULL;
    return (char *)ptr;
}

/*
 *
 */
fgBool fgConfig::setParameterValue(const char *sectionName, const char *parameterName, fgCfgParameterType type, void *value, fgBool freeInValue) {
    if(!sectionName || !parameterName || !value)
        return FG_FALSE;

    fgCfgSection *section = NULL;
    fgCfgParameter *parameter = NULL;
    fgCfgTypes::sectionMapPair sm_query_pair;
    fgCfgTypes::sectionMapKey sm_key = sectionName;
    sm_query_pair.first = sm_key;
    sm_query_pair.second = NULL;
    std::pair < fgCfgTypes::sectionMapItor, bool> sm_result = m_sectionMap.insert(sm_query_pair);
    if(sm_result.second == false) {
        // already existed
        section = sm_result.first->second;
    } else {
        // inserted new
        section = new fgCfgSection();
        section->name = sectionName;
        m_sectionMap[sm_key] = section;
    }

    fgCfgTypes::parameterMapPair pm_query_pair;
    fgCfgTypes::parameterMapKey pm_key = parameterName;
    pm_query_pair.first = pm_key;
    pm_query_pair.second = NULL;
    std::pair < fgCfgTypes::parameterMapItor, bool> pm_result = section->parametersMap.insert(pm_query_pair);
    if(pm_result.second == false) {
        // already existed
        parameter = pm_result.first->second;
    } else {
        // new insertion
        parameter = new fgCfgParameter();
        parameter->name = parameterName;
        fgConfigParser::splitSectionName(sm_key, parameter->sectionName, parameter->subSectionName);
        section->parametersMap[pm_key] = parameter;
        section->parameters.push_back(parameter);
    }

    fgBool status = parameter->set(type, value);
    if(status)
        refreshParameterVec();
    if(freeInValue) {
        fgFree(value);
        value = NULL;
    }
    return status;
}

/*
 *
 */
fgBool fgConfig::setParameterInt(const char *sectionName, const char *parameterName, int value) {
    int newValue = value;
    void *void_ptr = (void *)(&newValue);
    return setParameterValue(sectionName, parameterName, FG_CFG_PARAMETER_INT, void_ptr);
}

/*
 *
 */
fgBool fgConfig::setParameterLong(const char *sectionName, const char *parameterName, long int value) {
    long int newValue = value;
    void *void_ptr = (void *)(&newValue);
    return setParameterValue(sectionName, parameterName, FG_CFG_PARAMETER_LONG, void_ptr);
}

/*
 *
 */
fgBool fgConfig::setParameterFloat(const char *sectionName, const char *parameterName, float value) {
    float newValue = value;
    void *void_ptr = (void *)(&newValue);
    return setParameterValue(sectionName, parameterName, FG_CFG_PARAMETER_FLOAT, void_ptr);
}

/*
 *
 */
fgBool fgConfig::setParameterBool(const char *sectionName, const char *parameterName, fgBool value) {
    fgBool newValue = value;
    void *void_ptr = (void *)(&newValue);
    return setParameterValue(sectionName, parameterName, FG_CFG_PARAMETER_BOOL, void_ptr);
}

/*
 *
 */
fgBool fgConfig::setParameterString(const char *sectionName, const char *parameterName, const char *value) {
    char *newValue = strdup(value);
    void *void_ptr = (void *)(newValue);
    return setParameterValue(sectionName, parameterName, FG_CFG_PARAMETER_STRING, void_ptr, FG_TRUE);
}

/*
 *
 */
void fgConfig::_dumpAllParameters(void) {
    fgCfgTypes::parameterVecItor begin, end, itor;
    begin = m_parameterVec.begin();
    end = m_parameterVec.end();
    itor = begin;
    char _buf[1024];
    for(; itor != end; itor++) {
        fgCfgParameter *param = *itor;
        param->toString(_buf);
        printf("PARAM: '%s' type: '%d', section: '%s', sub: '%s', dump: '%s'\n",
               param->name.c_str(),
               (int)param->type,
               param->sectionName.c_str(),
               param->subSectionName.c_str(),
               _buf
               );
        memset(_buf, 0, 1024);
    }
}
