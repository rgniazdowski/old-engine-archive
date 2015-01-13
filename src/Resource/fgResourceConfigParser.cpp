/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgResourceConfigParser.h"
#include "Util/fgStrings.h"
#include "Util/fgPath.h"
#include "fgLog.h"

using namespace fg;

/**
 *
 */
resource::CResourceConfig::CResourceConfig() :
m_header(),
m_resNames(),
m_cfgType(FG_RES_CFG_INVALID),
m_resources() { }

/**
 * 
 * @param filePath
 */
resource::CResourceConfig::CResourceConfig(const char *filePath) :
m_header(),
m_resNames(),
m_cfgType(FG_RES_CFG_INVALID),
m_resources() {
    if(filePath)
        resource::CResourceConfig::load(filePath);
}

/**
 * 
 */
resource::CResourceConfig::~CResourceConfig() {
    m_resNames.clear_optimised();
    m_resources.clear();
}

/**
 * 
 * @param filePath
 * @return 
 */
fgBool resource::CResourceConfig::load(const char *filePath) {
    if(!filePath)
        return FG_FALSE;
    if(!CConfig::load(filePath)) {
        return FG_FALSE;
    }

    return resource::CResourceConfig::parseData();
}

/**
 * 
 * @return 
 */
util::SCfgSection *resource::CResourceConfig::getConfigSection(void) {
    if(m_cfgType == FG_RES_CFG_RESOURCE_GROUP)
        return CConfig::getSection(FG_RESOURCE_GROUP_TEXT);
    else if(m_cfgType == FG_RES_CFG_RESOURCE)
        return CConfig::getSection(FG_RESOURCE_TEXT);
    else
        return NULL;
}

/**
 * 
 * @param resName
 * @return 
 */
resource::SResourceHeader &resource::CResourceConfig::getRefHeader(const char *resName) {
    return resource::CResourceConfig::getRefHeader(std::string(resName));
}

/**
 * 
 * @param resName
 * @return 
 */
resource::SResourceHeader &resource::CResourceConfig::getRefHeader(const std::string & resName) {
    ResourceHeaderMapItor rhmit = m_resources.find(resName);
    if(rhmit == m_resources.end())
        return m_resources["__INVALID__"];
    return rhmit->second;
}

/**
 * 
 * @return 
 */
fgBool resource::CResourceConfig::parseData(void) {
    if(m_sectionMap.empty()) {
        FG_LOG_ERROR("Resource config section map is empty");
        return FG_FALSE;
    }
    std::string dirPath;
    path::dirName(m_configPath, dirPath);
    util::config::SectionMapItor smit = m_sectionMap.begin(),
            end = m_sectionMap.end();
    for(; smit != end; smit++) {
        util::SCfgSection *section = smit->second;
        fgBool isResGrpCfgSection = (section->name.compare(FG_RESOURCE_GROUP_TEXT) == 0);
        fgBool isResCfgSection = (section->name.compare(FG_RESOURCE_TEXT) == 0);

        if(isResGrpCfgSection || isResCfgSection) { // res grp || resource
            util::SCfgParameter *param = NULL;
            if((param = section->getParameter("name")) != NULL) {
                if(param->type == util::SCfgParameter::STRING)
                    m_header.name = param->string;
            } else {
            }
            if((param = section->getParameter("priority")) != NULL) {
                if(param->type == util::SCfgParameter::STRING)
                    m_header.priority = getResourcePriorityFromText(param->string);
            } else {
            }
        }
        if(!isResGrpCfgSection) {
            util::SCfgParameter *param = NULL;

            // special section parameter which tells that section
            // points to resource config file (not plain data)
            // further scanning is not needed
            if(!isResCfgSection) {
                if((param = section->getParameter("config", util::SCfgParameter::STRING)) != NULL) {
                    SResourceHeader cfgHeader;
                    cfgHeader.isConfig = FG_TRUE;
                    cfgHeader.name = section->name;
                    path::join(cfgHeader.configPath, dirPath, param->string);
                    //cfgHeader.configPath = param->string;
                    cfgHeader.paths.push_back(param->string);
                    m_resources[cfgHeader.name] = cfgHeader;
                    m_resNames.push_back(cfgHeader.name);
                    continue; // go to the next resource def
                }
            }
            fgBool foundName = FG_TRUE,
                    foundType = FG_TRUE,
                    foundQuality = FG_TRUE,
                    foundPath = FG_TRUE,
                    foundPriority = FG_TRUE;
            fgBool isMapped = FG_FALSE;

            std::string name;
            std::string path;
            std::string flags;
            resource::ResourceType type = resource::INVALID;
            fgQuality quality = FG_QUALITY_UNIVERSAL;
            resource::ResourcePriority priority = ResourcePriority::LOW;
            CVector<fgQuality> qualityVec;
            CVector<std::string> pathVec;
            CVector<std::string> _helperVec;

            /// Get the resource name
            if((param = section->getParameter("name", util::SCfgParameter::STRING)) != NULL) {
                name = param->string;
            } else {
                foundName = FG_FALSE;
            }
            if((param = section->getParameter("flags", util::SCfgParameter::STRING)) != NULL) {
                flags = param->string;
            }
            // Get the resource type
            if((param = section->getParameter("type", util::SCfgParameter::STRING)) != NULL) {
                type = getResourceTypeFromText(param->string);
            } else {
                foundType = FG_FALSE;
            }
            // Get the resource priority
            if((param = section->getParameter("priority", util::SCfgParameter::STRING)) != NULL) {
                priority = getResourcePriorityFromText(param->string);
            } else {
                foundPriority = FG_FALSE;
            }
            // Check if the resource has files mapped to different qualities
            if((param = section->getParameter("isMapped", util::SCfgParameter::BOOL)) != NULL) {
                isMapped = param->bool_val;
            } else {
                isMapped = FG_FALSE;
            }
            // When isMapped is true, then check for different parameters names
            // indicating that the values stored inside are separated by ';' char (array/vector)
            if(isMapped) {
                // Get the parameter: quality vector
                if((param = section->getParameter("qualityVec", util::SCfgParameter::STRING)) != NULL) {
                    _helperVec.clear_optimised();
                    strings::split(param->string, ',', _helperVec);
                    for(int i = 0; i < (int)_helperVec.size(); i++) {
                        qualityVec.push_back(FG_QUALITY_FROM_TEXT(_helperVec[i].c_str()));
                    }
                    if(qualityVec.empty())
                        foundQuality = FG_FALSE;
                } else {
                    foundQuality = FG_FALSE;
                }
                if((param = section->getParameter("pathVec", util::SCfgParameter::STRING)) != NULL) {
                    _helperVec.clear_optimised();
                    strings::split(param->string, ',', _helperVec);
                    for(int i = 0; i < (int)_helperVec.size(); i++) {
                        std::string _pathH;
                        path::join(_pathH, dirPath, _helperVec[i]);
                        pathVec.push_back(_pathH);
                    }
                    if(pathVec.empty())
                        foundPath = FG_FALSE;
                } else {
                    foundPath = FG_FALSE;
                }
                // In other case, the resource has single quality selected and stores single file
            } else {
                if((param = section->getParameter("quality", util::SCfgParameter::STRING)) != NULL) {
                    quality = FG_QUALITY_FROM_TEXT(param->string);
                    qualityVec.push_back(quality);
                } else {
                    quality = FG_QUALITY_UNIVERSAL;
                }
                if((param = section->getParameter("path", util::SCfgParameter::STRING)) != NULL) {
                    path::join(path, dirPath, param->string);
                    pathVec.push_back(path);
                } else {
                    foundPath = FG_FALSE;
                }
            }
            if(!foundPath || !foundType || !foundName || !foundQuality)
                continue;
            if(type == resource::GROUP) {
                qualityVec.clear_optimised();
                pathVec.clear_optimised();
                continue;
            }
            if(isResCfgSection) {
                m_header.quality = qualityVec[0];
                m_header.paths.swap(pathVec);
                m_header.qualities.swap(qualityVec);
                m_header.resType = type;
                m_header.flags = flags;
                m_resources[m_header.name] = m_header;
            } else {
                SResourceHeader resHeader;
                resHeader.name = name;
                if(foundPriority)
                    resHeader.priority = priority;
                resHeader.paths.swap(pathVec);
                resHeader.qualities.swap(qualityVec);
                resHeader.quality = quality;
                resHeader.resType = type;
                resHeader.flags = flags;
                m_resources[resHeader.name] = resHeader;
                m_resNames.push_back(resHeader.name);
            }
            // Finish
        } // if ( not resource group )
    } // iteration through section map

    return FG_TRUE;
}
