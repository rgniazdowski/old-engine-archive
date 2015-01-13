/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgConfigParser.h"
#include "fgMemory.h"
#include "fgStrings.h"
#include "fgMessageSubsystem.h"

using namespace fg;

/**
 * Default constructor for config parser object
 */
util::CConfigParser::CConfigParser() : m_fileSize(0), m_fileBuffer(NULL) { }

/**
 * Destructor for config parser object
 */
util::CConfigParser::~CConfigParser() {
    freeData();
}

/**
 * Split section name
 * @param fullSectionName
 * @param sectionName
 * @param subSectionName
 * @return 
 */
fgBool util::CConfigParser::splitSectionName(std::string &fullSectionName,
                                             std::string &sectionName,
                                             std::string &subSectionName) {
    fgBool isSection = FG_TRUE;
    fullSectionName = strings::trim(fullSectionName, std::string("[]"));
    fg::CVector<std::string> splitSection;
    splitSection.reserve(4);
    strings::split(fullSectionName, '.', splitSection);
    if(splitSection.size() == 1) {
        sectionName = splitSection[0];
        subSectionName.clear();
    } else if(splitSection.size()) {
        int subid = (int)splitSection.size() - 1;
        int i = 0;
        sectionName.clear();
        for(; i < subid; i++) {
            sectionName += splitSection[i];
            if(i != subid - 1)
                sectionName += ".";
        }
        subSectionName = splitSection[subid];
    } else {
        isSection = FG_FALSE;
        sectionName.clear();
        subSectionName.clear();
    }
    return isSection;
}

/**
 * Load config and store all parameters in given section map
 * @param filePath
 * @param sectionMap
 * @return 
 */
fgBool util::CConfigParser::load(const char *filePath, config::SectionMap &sectionMap) {
    if(m_fileBuffer)
        fgFree(m_fileBuffer);
    if(filePath == NULL) {
        if(m_filePath.empty())
            return FG_FALSE;
        filePath = m_filePath.c_str();
    }
    // DataFile/File is a special class wrapper for RegularFile and ZipFile
    // This allows for transparent manipulation (mostly reading) of files.
    // It doesn't matter whether or not the file being loaded is on disk or
    // inside of a zip archive. #NICE
    m_fileBuffer = fg::util::DataFile::load(filePath);
    // Close the file
    close();
    // parse data and store it in section map
    return parseData(m_fileBuffer, sectionMap);
}

/**
 * Parse data and store parameters in given section map (reference)
 * @param data
 * @param sectionMap
 * @return 
 */
fgBool util::CConfigParser::parseData(const char *data, config::SectionMap &sectionMap) {
    if(!data) {
        if(!m_fileBuffer) {
            FG_MessageSubsystem->reportError(tag_type::name(), FG_WARNING, "Parse data file buffer error - null");
            return FG_FALSE;
        }
        data = m_fileBuffer;
    }
    std::string input = data;
    std::string fullSectionName;
    std::string sectionName;
    std::string subSectionName;
    std::string parameterName;
    fgBool isSection = FG_FALSE;

    size_t cur;
    size_t next = std::string::npos;
    SCfgSection *newSection = NULL;
    do {
        cur = next + 1;
        next = input.find("\n", cur);

        std::string line = input.substr(cur, next - cur);
        if(line.empty())
            continue;
        line = strings::trim(line);
        if(line[0] == ';' ||
           line[0] == '#' ||
           (line[0] == '/' && line[1] == '/')) // Ignore comments
            continue;
        if(line[0] == '[') {
            fullSectionName = strings::trim(line, std::string("[]"));
            isSection = util::CConfigParser::splitSectionName(fullSectionName, sectionName, subSectionName);
            if(newSection) {
                newSection = NULL;
            }
            if(isSection) {
                newSection = new SCfgSection();
                newSection->name = fullSectionName;
                newSection->subName = subSectionName;
                config::SectionMapKey key = fullSectionName;
                sectionMap[key] = newSection;
            }
            //printf(">>> full section '%s', section '%s', subsection '%s'\n", fullSectionName.c_str(),
            //	sectionName.c_str(), subSectionName.c_str());
        } else if(isSection && !sectionName.empty()) {
            // Now checking for parameters and values for given section/subsection
            // parameter = value
            // Also need to ignore comments as some lines can have this format:
            // parameter = value ; comment
            if(line.find_last_of('\"') < line.find_last_of(';'))
                line = line.substr(0, line.find_last_of(';'));
            int eqpos = line.find_first_of('=');
            std::string parameterName = strings::trim(line.substr(0, eqpos));
            std::string parameterValue = strings::trim(line.substr(eqpos + 1));
            //printf("param value: %s = '%s'\n", parameterName.c_str(), parameterValue.c_str());
            if(parameterName.empty())
                continue;
            SCfgParameter *parameter = new SCfgParameter();
            parameter->name = parameterName;
            if(!sectionName.empty())
                parameter->sectionName = sectionName;
            if(!subSectionName.empty())
                parameter->subSectionName = subSectionName;

            int quotepos = parameterValue.find_first_of("'\"");
            fgBool bool_value = FG_BOOL_FROM_TEXT(parameterValue.c_str());

            // Does the string contain quotes?
            if(quotepos != (int)std::string::npos) {
                // it's a string value
                parameterValue = strings::trim(parameterValue, std::string("'\""));
                parameter->set(parameterValue.c_str());
            } else if(bool_value != FG_BOOL_INVALID) {
                // it's a bool value
                parameter->set(bool_value);
            } else if(strings::isFloat(parameterValue)) {
                // it's a float value
                parameter->set((float)atof(parameterValue.c_str()));
            } else if(toupper((int)parameterValue[parameterValue.size() - 1]) == 'L') {
                // it's probably a long int value (last digit L, like in 1230140L)
                parameter->set((long int)atol(parameterValue.c_str()));
            } else if(isdigit((int)parameterValue[0])) {
                // it's probably an int value
                parameter->set(atoi(parameterValue.c_str()));
            } else {
                //parameter->set(FG_CFG_DEFAULT_VALUE); // #FIXME
                parameter->set(parameterValue.c_str());
            }
            config::ParameterMapKey key = parameterName;
            if(newSection) {
                newSection->parametersMap[key] = parameter;
                newSection->parameters.push_back(parameter);
            } else {
                delete parameter;
                parameter = NULL;
            }
        }
    } while(next != std::string::npos);
    if(sectionMap.empty()) {
        return FG_FALSE;
    }
    return FG_TRUE;
}

/**
 * Free all data assiocated with the config parameters
 */
void util::CConfigParser::freeData(void) {
    if(m_fileBuffer)
        fgFree(m_fileBuffer);
    m_fileSize = 0;
    m_fileBuffer = NULL;
}
