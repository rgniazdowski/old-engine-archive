/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgConfigWriter.h"

/*
 *
 */
fgConfigWriter::fgConfigWriter() { }

/*
 *
 */
fgConfigWriter::~fgConfigWriter() { }

fgBool fgConfigWriter::save(const char *filePath, fgCfgTypes::sectionMap &sectionMap) {
    if(filePath == NULL) {
        if(m_filePath.empty())
            return FG_FALSE;
        filePath = m_filePath.c_str();
    }
    if(sectionMap.empty())
        return FG_FALSE;

    if(fgFile::isOpen())
        close();

    if(!fgFile::open(filePath, FG_FILE_MODE_WRITE)) {
        return FG_FALSE;
    }

    fgCfgTypes::sectionMapItor it = sectionMap.begin(),
            end = sectionMap.end();
    char linebuf[FG_CFG_LINE_MAX];
    for(; it != end; it++) {
        fgCfgSection *section = it->second;
        if(!section) continue;
        fgFile::print("%s\n", section->toString(linebuf));
        for(unsigned int i = 0; i < section->parameters.size(); i++) {
            fgFile::print("%s\n", section->parameters[i]->toString(linebuf));
        }
    }

    // Close the file
    close();
    return FG_TRUE;
}