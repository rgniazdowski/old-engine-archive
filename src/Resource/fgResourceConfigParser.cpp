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

/*
 *
 */
fgResourceConfig::fgResourceConfig() :
m_header(),
m_resNames(),
m_cfgType(FG_RES_CFG_INVALID),
m_resources() { }

/*
 *
 */
fgResourceConfig::fgResourceConfig(const char *filePath) :
m_header(),
m_resNames(),
m_cfgType(FG_RES_CFG_INVALID),
m_resources() {
    if(filePath)
        fgResourceConfig::load(filePath);
}

/*
 *
 */
fgResourceConfig::~fgResourceConfig() {
    m_resNames.clear_optimised();
    m_resources.clear();
}

/*
 *
 */
fgBool fgResourceConfig::load(const char *filePath) {
    if(!filePath)
        return FG_FALSE;
    if(!fgConfig::load(filePath)) {
        return FG_FALSE;
    }

    return fgResourceConfig::parseData();
}

/*
 *
 */
fgCfgSection *fgResourceConfig::getConfigSection(void) {
    if(m_cfgType == FG_RES_CFG_RESOURCE_GROUP)
        return fgConfig::getSection(FG_RESOURCE_GROUP_TEXT);
    else if(m_cfgType == FG_RES_CFG_RESOURCE)
        return fgConfig::getSection(FG_RESOURCE_TEXT);
    else
        return NULL;
}

/*
 *
 */
fgResourceHeader &fgResourceConfig::getResourceHeader(const char *resName) {
    return fgResourceConfig::getResourceHeader(std::string(resName));
}

/*
 *
 */
fgResourceHeader &fgResourceConfig::getResourceHeader(const std::string & resName) {
    resourceHeaderMapItor rhmit = m_resources.find(resName);
    if(rhmit == m_resources.end())
        return m_resources["__INVALID__"];
    return rhmit->second;
}

/*
 *
 */
fgBool fgResourceConfig::parseData(void) {
    if(m_sectionMap.empty()) {
        FG_LOG_ERROR("Resource config section map is empty");
        return FG_FALSE;
    }
    std::string dirPath;
    fg::path::dirName(m_configPath, dirPath);
    fgCfgTypes::sectionMapItor smit = m_sectionMap.begin(),
            end = m_sectionMap.end();
    for(; smit != end; smit++) {
        fgCfgSection *section = smit->second;
        fgBool isResGrpCfgSection = (section->name.compare(FG_RESOURCE_GROUP_TEXT) == 0);
        fgBool isResCfgSection = (section->name.compare(FG_RESOURCE_TEXT) == 0);

        if(isResGrpCfgSection || isResCfgSection) { // res grp || resource
            fgCfgParameter *param = NULL;
            if((param = section->getParameter("name")) != NULL) {
                if(param->type == FG_CFG_PARAMETER_STRING)
                    m_header.name = param->string;
            } else {
            }
            if((param = section->getParameter("priority")) != NULL) {
                if(param->type == FG_CFG_PARAMETER_STRING)
                    m_header.priority = FG_RES_PRIORITY_FROM_TEXT(param->string);
            } else {
            }
        }
        if(!isResGrpCfgSection) {
            fgCfgParameter *param = NULL;

            // special section parameter which tells that section
            // points to resource config file (not plain data)
            // further scanning is not needed
            if(!isResCfgSection) {
                if((param = section->getParameter("config", FG_CFG_PARAMETER_STRING)) != NULL) {
                    fgResourceHeader cfgHeader;
                    cfgHeader.isConfig = FG_TRUE;
                    cfgHeader.name = section->name;
                    fg::path::join(cfgHeader.configPath, dirPath, param->string);
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
            fgResourceType type = FG_RESOURCE_INVALID;
            fgQuality quality = FG_QUALITY_UNIVERSAL;
            fgResPriorityType priority = FG_RES_PRIORITY_LOW;
            fgVector<fgQuality> qualityVec;
            fgVector<std::string> pathVec;
            fgVector<std::string> _helperVec;

            /// Get the resource name
            if((param = section->getParameter("name", FG_CFG_PARAMETER_STRING)) != NULL) {
                name = param->string;
            } else {
                foundName = FG_FALSE;
            }
            if((param = section->getParameter("flags", FG_CFG_PARAMETER_STRING)) != NULL) {
                flags = param->string;
            }
            // Get the resource type
            if((param = section->getParameter("type", FG_CFG_PARAMETER_STRING)) != NULL) {
                type = FG_RESOURCE_TYPE_FROM_TEXT(param->string);
            } else {
                foundType = FG_FALSE;
            }
            // Get the resource priority
            if((param = section->getParameter("priority", FG_CFG_PARAMETER_STRING)) != NULL) {
                priority = FG_RES_PRIORITY_FROM_TEXT(param->string);
            } else {
                foundPriority = FG_FALSE;
            }
            // Check if the resource has files mapped to different qualities
            if((param = section->getParameter("isMapped", FG_CFG_PARAMETER_BOOL)) != NULL) {
                isMapped = param->bool_val;
            } else {
                isMapped = FG_FALSE;
            }
            // When isMapped is true, then check for different parameters names
            // indicating that the values stored inside are separated by ';' char (array/vector)
            if(isMapped) {
                // Get the parameter: quality vector
                if((param = section->getParameter("qualityVec", FG_CFG_PARAMETER_STRING)) != NULL) {
                    _helperVec.clear_optimised();
                    fgStrings::split(param->string, ',', _helperVec);
                    for(int i = 0; i < (int)_helperVec.size(); i++) {
                        qualityVec.push_back(FG_QUALITY_FROM_TEXT(_helperVec[i].c_str()));
                    }
                    if(qualityVec.empty())
                        foundQuality = FG_FALSE;
                } else {
                    foundQuality = FG_FALSE;
                }
                if((param = section->getParameter("pathVec", FG_CFG_PARAMETER_STRING)) != NULL) {
                    _helperVec.clear_optimised();
                    fgStrings::split(param->string, ',', _helperVec);
                    for(int i = 0; i < (int)_helperVec.size(); i++) {
                        std::string _pathH;
                        fg::path::join(_pathH, dirPath, _helperVec[i]);
                        pathVec.push_back(_pathH);
                    }
                    if(pathVec.empty())
                        foundPath = FG_FALSE;
                } else {
                    foundPath = FG_FALSE;
                }
                // In other case, the resource has single quality selected and stores single file
            } else {
                if((param = section->getParameter("quality", FG_CFG_PARAMETER_STRING)) != NULL) {
                    quality = FG_QUALITY_FROM_TEXT(param->string);
                    qualityVec.push_back(quality);
                } else {
                    quality = FG_QUALITY_UNIVERSAL;
                }
                if((param = section->getParameter("path", FG_CFG_PARAMETER_STRING)) != NULL) {
                    fg::path::join(path, dirPath, param->string);
                    pathVec.push_back(path);
                } else {
                    foundPath = FG_FALSE;
                }
            }
            if(!foundPath || !foundType || !foundName || !foundQuality)
                continue;
            if(type == FG_RESOURCE_GROUP) {
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
                fgResourceHeader resHeader;
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
