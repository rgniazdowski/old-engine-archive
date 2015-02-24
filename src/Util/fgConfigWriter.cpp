/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgConfigWriter.h"

using namespace fg;

/**
 *
 */
util::CConfigWriter::CConfigWriter() { }

/**
 *
 */
util::CConfigWriter::~CConfigWriter() { }

/**
 * 
 * @param filePath
 * @param sectionMap
 * @return 
 */
fgBool util::CConfigWriter::save(const char *filePath, config::SectionMap &sectionMap) {
    if(filePath == NULL) {
        if(m_filePath.empty())
            return FG_FALSE;
        filePath = m_filePath.c_str();
    }
    if(sectionMap.empty())
        return FG_FALSE;

    if(DataFile::isOpen())
        close();

    if(!DataFile::open(filePath, DataFile::Mode::WRITE)) {
        return FG_FALSE;
    }

    config::SectionMapItor it = sectionMap.begin(),
            end = sectionMap.end();
    char linebuf[CONFIG_LINE_MAX];
    for(; it != end; it++) {
        SCfgSection *section = it->second;
        if(!section) continue;
        fg::util::DataFile::print("%s\n", section->toString(linebuf));
        for(unsigned int i = 0; i < section->parameters.size(); i++) {
            fg::util::DataFile::print("%s\n", section->parameters[i]->toString(linebuf));
        }
    }

    // Close the file
    close();
    return FG_TRUE;
}
