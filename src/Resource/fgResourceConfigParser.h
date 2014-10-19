/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_RESOURCE_CONFIG_H_
    #define _FG_RESOURCE_CONFIG_H_

    #ifndef _FG_CONFIG_H_
        #include "Util/fgConfig.h"
    #endif

    #ifndef _FG_RESOURCE_H_
        #include "fgResource.h"
    #endif

typedef unsigned int fgResourceConfigType;

    #define FG_RES_CFG_INVALID			0
    #define FG_RES_CFG_RESOURCE			FG_RESOURCE
    #define FG_RES_CFG_RESOURCE_GROUP	FG_RESOURCE_GROUP

/*
 * Resource header is used only for config files
 * This will provide fast and handy data
 */
struct fgResourceHeader {
    ///
    fgVector<fgQuality> qualities;
    ///
    fgStringVector paths;
    ///
    std::string name;
    ///
    std::string configPath;
    /// Priority of this resource
    fgResPriorityType priority;
    /// Quality of the resource
    fgQuality quality;
    /// Resource type
    fgResourceType resType;
    ///
    fgBool isConfig;
    fgResourceHeader() :
    qualities(),
    paths(),
    name(),
    configPath(),
    priority(FG_RES_PRIORITY_LOW),
    quality(FG_QUALITY_UNIVERSAL),
    resType(FG_RESOURCE_INVALID),
    isConfig(FG_FALSE) { }
    ~fgResourceHeader() {
        paths.clear_optimised();
        qualities.clear_optimised();
        name.clear();
        configPath.clear();
    }
};

/*
 *
 */
class fgResourceConfig : public fgConfig {
public:
    typedef std::map<std::string, fgResourceHeader> resourceHeaderMap;
    typedef resourceHeaderMap::iterator resourceHeaderMapItor;
public:
    //
    fgResourceConfig();
    //
    fgResourceConfig(const char *filePath);
    //
    virtual ~fgResourceConfig();

    //
    virtual fgBool load(const char *filePath = NULL);

    //
    fgResourceType getResourceType(void) const {
        return m_header.resType;
    }

    //
    fgResourceConfigType getConfigType(void) const {
        return m_cfgType;
    }

    //
    fgCfgSection *getConfigSection(void);

    //
    fgResourceHeader &getResourceHeader(const char *resName);

    //
    fgResourceHeader &getResourceHeader(const std::string & resName);

    //
    fgStringVector &getRefResourceNames(void) {
        return m_resNames;
    }

    //
    resourceHeaderMap &getRefResourceHeaders(void) {
        return m_resources;
    }

    //
    fgVector<fgQuality> &getRefQualities(void) {
        return m_header.qualities;
    }

    //
    fgStringVector &getRefPaths(void) {
        return m_header.paths;
    }

    //
    fgResPriorityType getPriority(void) const {
        return m_header.priority;
    }

    //
    std::string &getName(void) {
        return m_header.name;
    }

    //
    fgResourceHeader &getRefHeader(void) {
        return m_header;
    }
protected:
    //
    fgBool parseData(void);

private:
    ///
    fgResourceHeader m_header;
    ///
    fgStringVector m_resNames;
    ///
    fgResourceConfigType m_cfgType;
    ///
    resourceHeaderMap m_resources;

};

#endif /* _FG_RESOURCE_CONFIG_H_ */

#undef	_FG_RESOURCE_CONFIG_H_SAFE_
#define _FG_RESOURCE_CONFIG_H_SAFE_
