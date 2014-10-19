/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiStyle.h"
#include "Util/fgConfig.h"
#include "Util/fgStrings.h"

/*
 *
 */
fgGuiStyle::fgGuiStyle() { }

/*
 *
 */
fgGuiStyle::~fgGuiStyle() {
    m_styleContent.clear();
}

/*
 *
 */
fgBool fgGuiStyle::load(void) {
    if(getFilePath().empty())
        return FG_FALSE;
    fgConfig *config = new fgConfig();
    if(!config->load(getFilePathStr())) {
        // ERROR
        delete config;
        return FG_FALSE;
    }

    const char * const _buildInSubStyles[] = {"activated", "deactivated", "focus", "pressed", "main"};
    m_styleContent.clear();

    for(int i = 0; i < 5; i++) {
        m_styleContent[_buildInSubStyles[i]] = fgGuiStyleContent();
    }

    fgCfgTypes::sectionMap &sections = config->getRefSectionMap();
    fgCfgTypes::sectionMapItor begin, end, itor;
    begin = sections.begin();
    end = sections.end();
    itor = begin;
    fgCfgSection *styleSheetSection = config->getSection(FG_GUI_STYLE_SHEET_NAME);
    fgCfgParameter *param = NULL;
    if(!styleSheetSection) {
        // ERROR
        delete config;
        return FG_FALSE;
    } else {
        if((param = styleSheetSection->getParameter("name", FG_CFG_PARAMETER_STRING)) != NULL) {
            setName(param->string);
        } else {
            // ERROR
            delete config;
            return FG_FALSE;
        }
    }
    fgCfgSection *mainSection = config->getSection("main");
    if(mainSection) {
        m_styleContent["main"].initializeFromConfig(mainSection->parameters);
    }

    for(; itor != end; itor++) {
        fgCfgSection *section = itor->second;
        if(!section)
            continue;
        if(section->name.compare(FG_GUI_STYLE_SHEET_NAME) == 0 ||
           section->name.compare("main") == 0) {
            continue;
        }

        fgCfgTypes::parameterVec &params = section->parameters;

        std::string& fullName = section->name;
        std::string& subName = section->subName;
        std::string firstName;
        fgConfigParser::splitSectionName(fullName, firstName, subName);
        // if the subName (subsection) exists it points to the state
        // if not, then depending on the case of the first character
        // of the section specify style parameters for all widgets of
        // a given type or for all widgets of a given state
        // lowercase: none, hover, focus, activated

        fgBool isInherit = FG_FALSE;
        fgBool autoInherit = FG_TRUE;
        std::string inheritFrom;
        fgCfgParameter *paramInherit = section->getParameter("inherit", FG_CFG_PARAMETER_STRING);
        if(paramInherit) {
            if(strcmp(paramInherit->string, "none") == 0) {
                autoInherit = FG_FALSE;
            } else {
                isInherit = FG_TRUE;
                inheritFrom = paramInherit->string;
            }
        } else {
        }
        fgGuiStyleContent newSubStyleContent;

        if(subName.length()) {
            if(isupper(firstName[0]) && islower(subName[0])) {
                // subName points to the widget state
                // it will autoinherit from global widget state
                fgCfgSection *inheritSection = NULL;
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
                fgCfgSection *inheritSection = NULL;
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

/*
 *
 */
fgBool fgGuiStyle::load(const std::string& path) {
    if(path.empty())
        return FG_FALSE;
    setFilePath(path);
    return fgGuiStyle::load();
}

/*
 *
 */
fgBool fgGuiStyle::load(const char *path) {
    if(!path)
        return FG_FALSE;
    setFilePath(path);
    return fgGuiStyle::load();
}

/*
 *
 */
fgGuiStyleContent &fgGuiStyle::getContent(const std::string& info) {
    if(info.empty())
        return m_styleContent["main"];
    fgStringVector parts;
    fgStrings::split(info, '.', parts);
    styleNameMap::iterator end = m_styleContent.end();
    if(parts.size() == 1) {
        styleNameMap::iterator itor = m_styleContent.find(info);
        if(itor != end)
            return itor->second;
    } else if(parts.size() == 2) {
        styleNameMap::iterator itorAll = m_styleContent.find(info);
        if(itorAll != end) {
            return itorAll->second;
        }
        styleNameMap::iterator itor1 = m_styleContent.find(parts[0]);
        styleNameMap::iterator itor2 = m_styleContent.find(parts[1]);
        if(itor1 == end && itor2 != end) {
            return itor2->second;
        } else if(itor1 != end && itor2 == end) {
            return itor1->second;
        }
    }
    return m_styleContent["main"];
}

/*
 *
 */
fgGuiStyleContent &fgGuiStyle::getContent(const char *info) {
    return getContent(std::string(info));
}

/*
 *
 */
fgBool fgGuiStyle::copyFullContent(fgGuiStyleContent *contents, int num, const std::string& info) {
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
    FG_GUI_WIDGET_STATE_NONE		0	// main
    FG_GUI_WIDGET_STATE_FOCUS		1	// focus
    FG_GUI_WIDGET_STATE_PRESSED		2	// pressed
    FG_GUI_WIDGET_STATE_ACTIVATED	3	// activated
    FG_GUI_WIDGET_STATE_DEACTIVATED	4	// deactivated
     */
    fgStringVector parts;
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

/*
 *
 */
fgBool fgGuiStyle::copyFullContent(fgGuiStyleContent *contents, int num, const char *info) {
    return copyFullContent(contents, num, std::string(info));
}
