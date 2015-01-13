/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiStyle.h"
#include "Util/fgConfig.h"
#include "Util/fgStrings.h"
#include "fgLog.h"

using namespace fg;

/**
 *
 */
gui::CStyle::CStyle() { }

/**
 *
 */
gui::CStyle::~CStyle() {
    m_styleContent.clear();
}

/**
 * 
 * @return 
 */
fgBool gui::CStyle::load(void) {
    if(getFilePath().empty())
        return FG_FALSE;
    util::CConfig *config = new util::CConfig();
    if(!config->load(getFilePathStr())) {
        FG_LOG_ERROR("GUI: Couldn't load style content file: '%s'", getFilePathStr());
        delete config;
        return FG_FALSE;
    }

    const char * const _buildInSubStyles[] = {"activated", "deactivated", "focus", "pressed", "main"};
    m_styleContent.clear();

    for(int i = 0; i < 5; i++) {
        m_styleContent[_buildInSubStyles[i]] = CStyleContent();
    }

    util::config::SectionMap &sections = config->getRefSectionMap();
    util::config::SectionMapItor begin, end, itor;
    begin = sections.begin();
    end = sections.end();
    itor = begin;
    util::SCfgSection *styleSheetSection = config->getSection(FG_GUI_STYLE_SHEET_NAME);
    util::SCfgParameter *param = NULL;
    if(!styleSheetSection) {
        // ERROR
        delete config;
        return FG_FALSE;
    } else {
        if((param = styleSheetSection->getParameter("name", util::SCfgParameter::STRING)) != NULL) {
            setName(param->string);
        } else {
            // ERROR
            delete config;
            return FG_FALSE;
        }
    }
    util::SCfgSection *mainSection = config->getSection("main");
    if(mainSection) {
        m_styleContent["main"].initializeFromConfig(mainSection->parameters);
    }

    for(; itor != end; itor++) {
        util::SCfgSection *section = itor->second;
        if(!section)
            continue;
        if(section->name.compare(FG_GUI_STYLE_SHEET_NAME) == 0 ||
           section->name.compare("main") == 0) {
            continue;
        }

        util::config::ParameterVec &params = section->parameters;

        std::string& fullName = section->name;
        std::string& subName = section->subName;
        std::string firstName;
        util::CConfigParser::splitSectionName(fullName, firstName, subName);
        // if the subName (subsection) exists it points to the state
        // if not, then depending on the case of the first character
        // of the section specify style parameters for all widgets of
        // a given type or for all widgets of a given state
        // lowercase: none, hover, focus, activated

        fgBool isInherit = FG_FALSE;
        fgBool autoInherit = FG_TRUE;
        std::string inheritFrom;
        util::SCfgParameter *paramInherit = section->getParameter("inherit", util::SCfgParameter::STRING);
        if(paramInherit) {
            if(strcmp(paramInherit->string, "none") == 0) {
                autoInherit = FG_FALSE;
            } else {
                isInherit = FG_TRUE;
                inheritFrom = paramInherit->string;
            }
        } else {
        }
        CStyleContent newSubStyleContent;

        if(subName.length()) {
            if(isupper(firstName[0]) && islower(subName[0])) {
                // subName points to the widget state
                // it will autoinherit from global widget state
                util::SCfgSection *inheritSection = NULL;
                if(autoInherit) {
                    inheritSection = config->getSection(subName);
                    if(!inheritSection)
                        inheritSection = config->getSection(firstName);
                } else if(isInherit && inheritFrom.length()) {
                    inheritSection = config->getSection(inheritFrom);
                }

                //if(!inheritSection)
                newSubStyleContent = m_styleContent["main"];
                if(inheritSection)
                    newSubStyleContent.initializeFromConfig(inheritSection->parameters);
            }
        } else {
            // There is no subsection so, the name refers to widget state or widget type
            if(islower(firstName[0])) {
                // lowercase - widget state
                // Widget state sub style does not inherit / merge any other sub styles
                // It's initialized from 'main' substyle - special substyle for all widgets/states
                // Main substyle is something like 'global default'
                newSubStyleContent = m_styleContent["main"];
            } else {
                // uppercase - widget type
                util::SCfgSection *inheritSection = NULL;
                if(isInherit && inheritFrom.length()) {
                    inheritSection = config->getSection(inheritFrom);
                }
                //if(!inheritSection)
                newSubStyleContent = m_styleContent["main"];
                if(inheritSection)
                    newSubStyleContent.initializeFromConfig(inheritSection->parameters);
            }
        }
        newSubStyleContent.initializeFromConfig(params);
        m_styleContent[fullName] = newSubStyleContent;
    }

    delete config;
    return FG_TRUE;
}

/**
 * 
 * @param path
 * @return 
 */
fgBool gui::CStyle::load(const std::string& path) {
    if(path.empty())
        return FG_FALSE;
    setFilePath(path);
    return gui::CStyle::load();
}

/**
 * 
 * @param path
 * @return 
 */
fgBool gui::CStyle::load(const char *path) {
    if(!path)
        return FG_FALSE;
    setFilePath(path);
    return gui::CStyle::load();
}

/**
 * 
 * @param info
 * @return 
 */
gui::CStyleContent &gui::CStyle::getContent(const std::string& info) {
    if(info.empty())
        return m_styleContent["main"];
    fg::CStringVector parts;
    fgStrings::split(info, '.', parts);
    StyleNameMap::iterator end = m_styleContent.end();
    if(parts.size() == 1) {
        StyleNameMap::iterator itor = m_styleContent.find(info);
        if(itor != end)
            return itor->second;
    } else if(parts.size() == 2) {
        StyleNameMap::iterator itorAll = m_styleContent.find(info);
        if(itorAll != end) {
            return itorAll->second;
        }
        StyleNameMap::iterator itor1 = m_styleContent.find(parts[0]);
        StyleNameMap::iterator itor2 = m_styleContent.find(parts[1]);
        if(itor1 == end && itor2 != end) {
            return itor2->second;
        } else if(itor1 != end && itor2 == end) {
            return itor1->second;
        } else if(itor1 != end && itor2 != end) {
            return itor1->second;
        }
    }
    return m_styleContent["main"];
}

/**
 * 
 * @param info
 * @return 
 */
gui::CStyleContent &gui::CStyle::getContent(const char *info) {
    return getContent(std::string(info));
}

/**
 * 
 * @param contents
 * @param num
 * @param info
 * @return 
 */
fgBool gui::CStyle::copyFullContent(CStyleContent *contents,
                                    int num,
                                    const std::string& info) {
    if(num < 1 || !contents)
        return FG_FALSE;
    if(num > 5)
        num = 5;
    // #FIXME
    const char * const _buildInSubStyles[] = {
                                              "main", // NONE		0
                                              "focus", // FOCUS	1
                                              "pressed", // PRESSED	2
                                              "activated", // ACTIVATE	3
                                              "deactivated" // DEACTIV	4
    };
    /*
    STATE_NONE		0	// main
    STATE_FOCUS		1	// focus
    STATE_PRESSED		2	// pressed
    STATE_ACTIVATED	3	// activated
    STATE_DEACTIVATED	4	// deactivated
     */
    CStringVector parts;
    fgStrings::split(info, '.', parts);
    std::string search = parts[0];
    parts.clear();
    contents[0] = getContent(search);
    for(int i = 1; i < num; i++) {
        std::string name = search;
        name.append(".");
        name.append(_buildInSubStyles[i]);
        contents[i] = getContent(name);
    }
    return FG_TRUE;
}

/**
 * 
 * @param contents
 * @param num
 * @param info
 * @return 
 */
fgBool gui::CStyle::copyFullContent(CStyleContent *contents,
                                    int num,
                                    const char *info) {
    return copyFullContent(contents, num, std::string(info));
}
