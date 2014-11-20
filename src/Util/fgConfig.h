/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_CONFIG
    #define FG_INC_CONFIG

    #include "fgConfigStruct.h"
    #include "fgConfigParser.h"
    #include "fgConfigWriter.h"

/**
 *
 */
class fgConfig {
protected:
    /// Internal config parser
    fgConfigParser *m_parser;
    /// Internal config writer
    fgConfigWriter *m_writer;
    /// Map with config file sections
    fgCfgTypes::sectionMap m_sectionMap;
    /// Special vector with parameters
    fgCfgTypes::parameterVec m_parameterVec;
    /// Path to the config file
    std::string m_configPath;
    /// Simple flag to check if the config file loaded successfully
    fgBool m_isLoaded;
public:
    /**
     * 
     */
    fgConfig();
    /**
     * 
     * @param filePath
     */
    fgConfig(const char *configPath);
    /**
     * 
     */
    virtual ~fgConfig();

    inline fgBool isLoaded(void) const {
        return m_isLoaded;
    }
    
    /**
     * 
     */
    void refreshParameterVec(void);
    /**
     * 
     * @param filePath
     * @return 
     */
    virtual fgBool load(const char *configPath = NULL);
    /**
     * 
     * @param filePath
     * @return 
     */
    fgBool save(const char *configPath = NULL);

    /**
     * 
     */
    virtual void clearAll(void);

    /**
     * Return the void* pointer to parameter value. NULL if there is no such parameter.
     * @param sectionName
     * @param parameterName
     * @return 
     */
    void *getParameterValue(const char *sectionName, const char *parameterName);
    /**
     * Return the int value of the parameter. status will be set to NULL if there is no such parameter.
     * @param sectionName
     * @param parameterName
     * @param status
     * @return 
     */
    int getParameterInt(const char *sectionName, const char *parameterName, fgBool *status = NULL);
    /**
     * Return the int value of the parameter. status will be set to NULL if there is no such parameter.
     * @param sectionName
     * @param parameterName
     * @param status
     * @return 
     */
    long int getParameterLong(const char *sectionName, const char *parameterName, fgBool *status = NULL);
    /**
     * Return the float value of the parameter
     * @param sectionName
     * @param parameterName
     * @param status
     * @return 
     */
    float getParameterFloat(const char *sectionName, const char *parameterName, fgBool *status = NULL);
    /**
     * Return the float value of the parameter
     * @param sectionName
     * @param parameterName
     * @param status
     * @return 
     */
    fgBool getParameterBool(const char *sectionName, const char *parameterName, fgBool *status = NULL);
    /**
     * Return the pointer to string value of the parameter. NULL if there is no such parameter.
     * @param sectionName
     * @param parameterName
     * @return 
     */
    char *getParameterString(const char *sectionName, const char *parameterName);

    /**
     * 
     * @param sectionName
     * @param parameterName
     * @param type
     * @param value
     * @param freeInValue
     * @return 
     */
    fgBool setParameterValue(const char *sectionName, const char *parameterName, fgCfgParameterType type, void *value, fgBool freeInValue = FG_FALSE);
    /**
     * 
     * @param sectionName
     * @param parameterName
     * @param value
     * @return 
     */
    fgBool setParameterInt(const char *sectionName, const char *parameterName, int value);
    /**
     * 
     * @param sectionName
     * @param parameterName
     * @param value
     * @return 
     */
    fgBool setParameterLong(const char *sectionName, const char *parameterName, long int value);
    /**
     * 
     * @param sectionName
     * @param parameterName
     * @param value
     * @return 
     */
    fgBool setParameterFloat(const char *sectionName, const char *parameterName, float value);
    /**
     * 
     * @param sectionName
     * @param parameterName
     * @param value
     * @return 
     */
    fgBool setParameterBool(const char *sectionName, const char *parameterName, fgBool value);
    /**
     * 
     * @param sectionName
     * @param parameterName
     * @param value
     * @return 
     */
    fgBool setParameterString(const char *sectionName, const char *parameterName, const char *value);

    /**
     * Return the reference to internal section map
     * @return 
     */
    inline fgCfgTypes::sectionMap & getRefSectionMap(void) {
        return m_sectionMap;
    }
    /**
     * Return the reference to internal parameter vector
     * @return 
     */
    inline fgCfgTypes::parameterVec & getRefParameterVec(void) {
        return m_parameterVec;
    }

    /**
     * 
     * @return 
     */
    inline int getSectionsCount(void) const {
        return m_sectionMap.size();
    }

    /**
     * 
     * @return 
     */
    inline int getParametersCount(void) const {
        return m_parameterVec.size();
    }

    /**
     * 
     * @param sectionsVec
     * @param sectionNameBegin
     * @return 
     */
    int getSectionsWith(fgCfgTypes::sectionVec & sectionsVec, const char *sectionNameBegin);

    /**
     * Return pointer to section structure
     * @param sectionName
     * @return 
     */
    fgCfgSection *getSection(const char *sectionName);

    /**
     * Return pointer to section structure
     * @param sectionName
     * @return 
     */
    fgCfgSection *getSection(const std::string & sectionName);

    /**
     * Return the reference to the given sections parameter map
     * @param sectionName
     * @return 
     */
    fgCfgTypes::parameterMap & getRefSectionsParameterMap(const char *sectionName);

    /**
     * Return the reference to the given sections parameter vector
     * @param sectionName
     * @return 
     */
    fgCfgTypes::parameterVec & getRefSectionsParameterVec(const char *sectionName);

protected:
    /**
     * 
     */
    void _dumpAllParameters(void);
};

#endif /* FG_INC_CONFIG */
