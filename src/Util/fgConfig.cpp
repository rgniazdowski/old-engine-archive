/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgConfig.h"
#include "fgMemory.h"
#include "fgException.h"
#include "fgLog.h"

using namespace fg;

//------------------------------------------------------------------------------

util::CConfig::CConfig() : m_parser(NULL), m_writer(NULL) { }
//------------------------------------------------------------------------------

util::CConfig::CConfig(const char *configPath) : m_parser(NULL), m_writer(NULL) {
    if(configPath)
        util::CConfig::load(configPath); // #FIXME
}
//------------------------------------------------------------------------------

util::CConfig::~CConfig() {
    if(m_parser)
        delete m_parser;
    m_parser = NULL;
    if(m_writer)
        delete m_writer;
    m_writer = NULL;
    clearAll();
}
//------------------------------------------------------------------------------

void util::CConfig::refreshParameterVec(void) {
    m_parameterVec.clear_optimised();
    config::SectionMapItor it = m_sectionMap.begin(),
            end = m_sectionMap.end();
    for(; it != end; it++) {
        SCfgSection *section = it->second;
        if(!section) continue;
        for(unsigned int i = 0; i < section->parameters.size(); i++) {
            m_parameterVec.push_back(section->parameters[i]);
        }
    }
}
//------------------------------------------------------------------------------

fgBool util::CConfig::load(const char *configPath) {
    if(!configPath) {
        if(m_configPath.empty())
            return FG_FALSE;
        configPath = m_configPath.c_str();
    } else {
        m_configPath.clear();
        m_configPath = configPath;
    }

    if(!m_parser)
        m_parser = new CConfigParser();
    util::CConfig::clearAll();
    if(!m_parser->load(configPath, m_sectionMap)) {
        return FG_FALSE;
    }
    m_isLoaded = FG_TRUE;
    refreshParameterVec();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool util::CConfig::save(const char *filePath) {
    if(!filePath) {
        if(m_configPath.empty())
            return FG_FALSE;
        filePath = m_configPath.c_str();
    } else {
        m_configPath.clear();
        m_configPath = filePath;
    }

    if(!m_writer)
        m_writer = new CConfigWriter();

    if(!m_writer->save(filePath, m_sectionMap)) {
        return FG_FALSE;
    }

    return FG_TRUE;
}
//------------------------------------------------------------------------------

void util::CConfig::clearAll(void) {
    if(!m_sectionMap.empty()) {
        m_configPath.clear();
        config::SectionMapItor it = m_sectionMap.begin(),
                end = m_sectionMap.end();
        for(; it != end; it++) {
            SCfgSection *section = it->second;
            section->freeAll();
            delete section;
            m_sectionMap[it->first] = NULL;
        }
    }
    m_sectionMap.clear();
    m_parameterVec.clear_optimised();
    m_isLoaded = FG_FALSE;
}
//------------------------------------------------------------------------------

util::SCfgSection *util::CConfig::getSection(const char *sectionName) {
    if(!sectionName)
        return NULL;
    if(m_sectionMap.empty())
        return NULL;
    config::SectionMapKey smkey = sectionName;
    config::SectionMapItor smit = m_sectionMap.find(smkey);
    if(smit == m_sectionMap.end())
        return NULL;

    return smit->second;
}
//------------------------------------------------------------------------------

util::SCfgSection *util::CConfig::getSection(const std::string & sectionName) {
    return getSection(sectionName.c_str());
}
//------------------------------------------------------------------------------

int util::CConfig::getSectionsWith(config::SectionVec & sectionsVec,
                                   const char *sectionNameBegin) {
    if(!sectionNameBegin || m_sectionMap.empty()) {
        return 0;
    }

    config::SectionMapItor begin = m_sectionMap.begin(), end = m_sectionMap.end();
    config::SectionMapItor smit = begin;
    std::string prefix = sectionNameBegin;
    int prefixLen = (int)prefix.length();
    for(; smit != end; smit++) {
        if(smit->second->name.substr(0, prefixLen).compare(prefix) == 0)
            sectionsVec.push_back(smit->second);
    }
    return sectionsVec.size();
}
//------------------------------------------------------------------------------

void *util::CConfig::getParameterValue(const char *sectionName,
                                       const char *parameterName) {
    if(!sectionName || !parameterName)
        return NULL;
    SCfgSection *section = getSection(sectionName);
    if(!section)
        return NULL;
    SCfgParameter *parameter = section->getParameter(parameterName);
    if(!parameter)
        return NULL;
    return parameter->get();
}
//------------------------------------------------------------------------------

int util::CConfig::getParameterInt(const char *sectionName,
                                   const char *parameterName,
                                   fgBool *status) {
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
//------------------------------------------------------------------------------

long int util::CConfig::getParameterLong(const char *sectionName,
                                         const char *parameterName,
                                         fgBool *status) {
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
//------------------------------------------------------------------------------

float util::CConfig::getParameterFloat(const char *sectionName,
                                       const char *parameterName,
                                       fgBool *status) {
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
//------------------------------------------------------------------------------

fgBool util::CConfig::getParameterBool(const char *sectionName,
                                       const char *parameterName,
                                       fgBool *status) {
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
//------------------------------------------------------------------------------

char *util::CConfig::getParameterString(const char *sectionName,
                                        const char *parameterName) {
    void *ptr = getParameterValue(sectionName, parameterName);
    if(!ptr)
        return NULL;
    return (char *)ptr;
}
//------------------------------------------------------------------------------

fgBool util::CConfig::setParameterValue(const char *sectionName,
                                        const char *parameterName,
                                        util::SCfgParameter::Type type,
                                        void *value,
                                        fgBool freeInValue) {
    if(!sectionName || !parameterName || !value)
        return FG_FALSE;

    SCfgSection *section = NULL;
    SCfgParameter *parameter = NULL;
    config::SectionMapPair sm_query_pair;
    config::SectionMapKey sm_key = sectionName;
    sm_query_pair.first = sm_key;
    sm_query_pair.second = NULL;
    std::pair < config::SectionMapItor, bool> sm_result;
    sm_result = m_sectionMap.insert(sm_query_pair);
    if(sm_result.second == false) {
        // already existed
        section = sm_result.first->second;
    } else {
        // inserted new
        section = new SCfgSection();
        section->name = sectionName;
        m_sectionMap[sm_key] = section;
    }

    config::ParameterMapPair pm_query_pair;
    config::ParameterMapKey pm_key = parameterName;
    pm_query_pair.first = pm_key;
    pm_query_pair.second = NULL;
    std::pair < config::ParameterMapItor, bool> pm_result;
    pm_result = section->parametersMap.insert(pm_query_pair);
    if(pm_result.second == false) {
        // already existed
        parameter = pm_result.first->second;
    } else {
        // new insertion
        parameter = new SCfgParameter();
        parameter->name = parameterName;
        CConfigParser::splitSectionName(sm_key, parameter->sectionName, parameter->subSectionName);
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
//------------------------------------------------------------------------------

fgBool util::CConfig::setParameterInt(const char *sectionName,
                                      const char *parameterName,
                                      int value) {
    int newValue = value;
    void *void_ptr = (void *)(&newValue);
    return setParameterValue(sectionName, parameterName, SCfgParameter::INT, void_ptr);
}
//------------------------------------------------------------------------------

fgBool util::CConfig::setParameterLong(const char *sectionName,
                                       const char *parameterName,
                                       long int value) {
    long int newValue = value;
    void *void_ptr = (void *)(&newValue);
    return setParameterValue(sectionName, parameterName, SCfgParameter::LONG, void_ptr);
}
//------------------------------------------------------------------------------

fgBool util::CConfig::setParameterFloat(const char *sectionName,
                                        const char *parameterName,
                                        float value) {
    float newValue = value;
    void *void_ptr = (void *)(&newValue);
    return setParameterValue(sectionName, parameterName, SCfgParameter::FLOAT, void_ptr);
}
//------------------------------------------------------------------------------

fgBool util::CConfig::setParameterBool(const char *sectionName,
                                       const char *parameterName,
                                       fgBool value) {
    fgBool newValue = value;
    void *void_ptr = (void *)(&newValue);
    return setParameterValue(sectionName, parameterName, SCfgParameter::BOOL, void_ptr);
}
//------------------------------------------------------------------------------

fgBool util::CConfig::setParameterString(const char *sectionName,
                                         const char *parameterName,
                                         const char *value) {
    char *newValue = strdup(value);
    void *void_ptr = (void *)(newValue);
    return setParameterValue(sectionName, parameterName, SCfgParameter::STRING, void_ptr, FG_TRUE);
}
//------------------------------------------------------------------------------

void util::CConfig::dumpAllParameters(void) {
    config::ParameterVecItor begin, end, itor;
    begin = m_parameterVec.begin();
    end = m_parameterVec.end();
    itor = begin;
    char _buf[1024];
    for(; itor != end; itor++) {
        SCfgParameter *param = *itor;
        param->toString(_buf);
        FG_LOG_DEBUG("PARAM: '%s' type: '%d', section: '%s', sub: '%s', dump: '%s'\n",
               param->name.c_str(),
               (int)param->type,
               param->sectionName.c_str(),
               param->subSectionName.c_str(),
               _buf
               );
        memset(_buf, 0, 1024);
    }
}
//------------------------------------------------------------------------------
