/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_CONFIG_STRUCT
    #define FG_INC_CONFIG_STRUCT
    #define FG_INC_CONFIG_STRUCT_BLOCK

    #include "fgTypes.h"
    #include <string>
    #include <map>

    #define FG_CFG_DEFAULT_VALUE        "_default_"

namespace fg {
    namespace util {

        struct SCfgParameter;
        struct SCfgSection;

        namespace config {
            ///
            typedef std::string SectionMapKey;
            ///
            typedef std::map<SectionMapKey, SCfgSection*> SectionMap;
            ///
            typedef std::pair<SectionMapKey, SCfgSection*> SectionMapPair;
            ///
            typedef SectionMap::iterator SectionMapItor;

            ///
            typedef fg::CVector<SCfgParameter*> ParameterVec;
            ///
            typedef ParameterVec::iterator ParameterVecItor;

            ///
            typedef fg::CVector<SCfgSection*> SectionVec;
            ///
            typedef SectionVec::iterator SectionVecItor;

            ///
            typedef std::string ParameterMapKey;
            ///
            typedef std::map<ParameterMapKey, SCfgParameter*> ParameterMap;
            ///
            typedef std::pair<ParameterMapKey, SCfgParameter*> ParameterMapPair;
            ///
            typedef ParameterMap::iterator ParameterMapItor;
        };

        ///
        const unsigned int PARAM_STRING_MAX = 512;
        ///
        const unsigned int CONFIG_LINE_MAX = 1024;

        /**
         *
         */
        struct SCfgParameter {
            /// Name of the parameter
            std::string name;
            /// Name of the section
            std::string sectionName;
            /// Name of the subsection in which the parameter resides
            std::string subSectionName;

            /**
             *
             */
            enum Type {
                /// No value specified - unknown
                NONE,
                /// Integer value - int
                INT,
                /// Long integer value - long int
                LONG,
                /// Float value
                FLOAT,
                /// Boolean value - fgBool
                BOOL,
                /// String value - char array
                STRING
            } type;

            /**
             * Union for storing different values
             */
            union {
                ///
                char string[PARAM_STRING_MAX];
                ///
                long int long_val;
                ///
                float float_val;
                ///
                int int_val;
                ///
                fgBool bool_val;
            };
            /**
             * 
             */
            SCfgParameter() : type(NONE) {
                memset(string, 0, PARAM_STRING_MAX);
            }
            /**
             * Destructor for the configs parameter
             */
            virtual ~SCfgParameter() {
                name.clear();
                sectionName.clear();
                subSectionName.clear();
            }
            /**
             * Reset all values
             */
            inline void reset() {
                type = NONE;
                int_val = 0;
                name.clear();
                sectionName.clear();
                subSectionName.clear();
                memset(string, 0, PARAM_STRING_MAX);
            }
            /**
             * Set the integer value for the parameter
             * @param _int_val
             */
            inline void set(int _int_val) {
                type = INT;
                int_val = _int_val;
            }
            /**
             *  Set the 'long int' value for the parameter
             * @param _long_val
             */
            inline void set(long int _long_val) {
                type = LONG;
                long_val = _long_val;
            }
            /**
             *  Set the float value of the parameter
             * @param _float_val
             */
            inline void set(float _float_val) {
                type = FLOAT;
                float_val = _float_val;
            }
            /**
             * Set the bool value of the parameter
             * @param _bool_val
             */
            inline void set(fgBool _bool_val) {
                type = BOOL;
                bool_val = _bool_val;
            }
            /**
             * Set the string value of the parameter
             * @param _string
             */
            inline void set(const char *_string) {
                type = STRING;
                strncpy(string, _string, PARAM_STRING_MAX - 1);
            }
            /**
             * Set the parameter value based on the type enum and void pointer
             * @param _type
             * @param _value
             * @return 
             */
            fgBool set(Type _type, void *_value) {
                if(!_value)
                    return FG_FALSE;

                switch(_type) {
                    case INT:
                        int_val = *((int *)_value);
                        break;
                    case LONG:
                        long_val = *((long int *)_value);
                        break;
                    case FLOAT:
                        float_val = *((float *)_value);
                        break;
                    case BOOL:
                        bool_val = *((fgBool *)_value);
                        break;
                    case STRING:
                        strncpy(string, (const char *)_value, PARAM_STRING_MAX - 1);
                        break;
                    case NONE:
                        return FG_FALSE;
                        break;
                    default:
                        return FG_FALSE;
                        break;
                };
                type = _type;
                return FG_TRUE;
            }
            /**
             * Get the void* pointer to the value stored in the parameter struct - NULL if invalid
             * @return 
             */
            inline void *get(void) {
                switch(type) {
                    case INT:
                        return (void *)&int_val;
                        break;
                    case LONG:
                        return (void *)&long_val;
                        break;
                    case FLOAT:
                        return (void *)&float_val;
                        break;
                    case BOOL:
                        return (void *)&bool_val;
                        break;
                    case STRING:
                        return (void *)string;
                        break;
                    case NONE:
                        break;
                    default:
                        break;
                };
                return NULL;
            }
            /**
             * Convert value of the parameter to string. Will be stored in specified buffer. NULL on failure.
             * @param buf
             * @param nmax
             * @return 
             */
            char *valueToString(char *buf, unsigned int nmax = PARAM_STRING_MAX) {
                if(nmax < PARAM_STRING_MAX || !buf)
                    return NULL;

                switch(type) {
                    case INT:
                        snprintf(buf, nmax, "%d", int_val);
                        break;
                    case LONG:
                        snprintf(buf, nmax, "%ldL", long_val);
                        break;
                    case FLOAT:
                        snprintf(buf, nmax, "%f", float_val);
                        break;
                    case BOOL:
                        snprintf(buf, nmax, "%s", FG_BOOL_TO_TEXT(bool_val));
                        break;
                    case STRING:
                        snprintf(buf, nmax, "\"%s\"", string);
                        break;
                    case NONE:
                        return NULL;
                        break;
                    default:
                        return NULL;
                        break;
                };
                return buf;
            }
            /**
             * Convert the parameter to string. The string will be in format: name = value
             * @param buf
             * @param nmax
             * @return 
             */
            inline char *toString(char *buf, unsigned int nmax = CONFIG_LINE_MAX) {
                if(!buf)
                    return NULL;
                char tmp_val[PARAM_STRING_MAX];
                if(!valueToString(tmp_val))
                    return NULL;
                snprintf(buf, nmax, "%s = %s", name.c_str(), tmp_val);
                return buf;
            }
        };

        /*
         *
         */
        struct SCfgSection {
            // Full section name
            std::string name;
            // Name of the subsection
            std::string subName;
            // parameters vector - all parameters one after another
            config::ParameterVec parameters;
            // parameters map - key is the parameter name
            config::ParameterMap parametersMap;
            /**
             * Default empty constructor
             */
            SCfgSection() { }
            /**
             * Default destructor for config section
             */
            virtual ~SCfgSection() {
                name.clear();
                subName.clear();
                parameters.clear_optimised();
                parametersMap.clear();
            }
            /**
             * Return the parameter with given name
             * @param parameterName
             * @return 
             */
            SCfgParameter *getParameter(const char *parameterName) {
                config::ParameterMapKey pmkey = parameterName;
                config::ParameterMapItor pmit = parametersMap.find(pmkey);
                if(pmit == parametersMap.end())
                    return NULL;
                return pmit->second;
            }
            /**
             * 
             * @param parameterName
             * @param _type
             * @return 
             */
            SCfgParameter *getParameter(const char *parameterName, SCfgParameter::Type _type) {
                SCfgParameter *param = getParameter(parameterName);
                if(!param)
                    return NULL;
                if(param->type != _type)
                    return NULL;
                return param;
            }
            /**
             * Return the parameter with given name
             * @param parameterName
             * @return 
             */
            inline SCfgParameter *getParameter(std::string & parameterName) {
                return getParameter(parameterName.c_str());
            }
            /**
             * 
             * @param parameterName
             * @param _type
             * @return 
             */
            inline SCfgParameter *getParameter(std::string & parameterName, SCfgParameter::Type _type) {
                return getParameter(parameterName.c_str(), _type);
            }
            /**
             * This will release all data - calls destructors
             */
            void freeAll(void) {
                parametersMap.clear();
                while(!parameters.empty()) {
                    SCfgParameter *&param = parameters.back();
                    delete param;
                    param = NULL;
                    parameters.pop_back();
                }
            }
            /**
             * 
             * @param buf
             * @param nmax
             * @return 
             */
            inline char *toString(char *buf, unsigned int nmax = PARAM_STRING_MAX) {
                if(!buf)
                    return NULL;
                snprintf(buf, nmax, "[%s]", name.c_str());
                return buf;
            }
        };
    };
};

    #undef FG_INC_CONFIG_STRUCT_BLOCK
#endif /* FG_INC_CONFIG_STRUCT */
