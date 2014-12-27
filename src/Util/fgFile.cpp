/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgFile.cpp
 * Author: vigilant
 * 
 * Created on December 27, 2014, 12:51 PM
 */

#include "fgFile.h"
#include "fgFileErrorCodes.h"
#include "fgMessageSubsystem.h"

/**
 * 
 */
fg::util::File::File() :
m_zip(),
m_regular(),
m_file(NULL),
m_mode(REGULAR) {
    m_file = &m_regular;
    m_modeFlags = Mode::READ;
}

/**
 * 
 * @param filePath
 */
fg::util::File::File(const char *filePath) :
m_zip(),
m_regular(),
m_file(NULL),
m_mode(REGULAR) {
    m_file = &m_regular;
    m_modeFlags = Mode::READ;
    this->setPath(filePath);
}

/**
 * 
 * @param orig
 */
fg::util::File::File(const File& orig) {
    if(&orig != this) {
        this->m_mode = orig.m_mode;
        this->m_modeFlags = orig.m_modeFlags;
        this->m_zip = orig.m_zip;
        this->m_regular = orig.m_regular;
        if(this->m_mode == ZIP)
            this->m_file = &m_zip;
        else
            this->m_file = &m_regular;
        // #FIXME
    }
}

/**
 * 
 */
fg::util::File::~File() {
    m_zip.close();
    m_regular.close();
    m_file = NULL;
}

/**
 * 
 * @param filePath
 */
void fg::util::File::setPath(const char *filePath) {
    if(!filePath)
        return;
    // Use the m_zip setPath to determine if this points to a ZipFile
    m_zip.setPath(filePath);
    const char *path = m_zip.getPath();
    if(!path || strlen(path) < 1) {
        // This means that path points to a regular file
        // Close the zip file just in case
        if(m_zip.isOpen())
            m_zip.close();
        m_mode = REGULAR;
        m_file = &m_regular;
        m_file->setPath(filePath);
    } else {
        // This means that path points to a valid ZipFile or a file inside a Zip
        if(m_regular.isOpen())
            m_regular.close();
        m_mode = ZIP;
        m_file = &m_zip;
    }
}

/**
 * 
 * @param filePath
 */
void fg::util::File::setPath(const std::string & filePath) {
    if(filePath.size())
        setPath(filePath.c_str());
}

/**
 * 
 * @param fmt
 * @return 
 */
int fg::util::File::print(const char *fmt, ...) {
    if(fmt == NULL || m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_WRONG_PARAMETERS);
        return -1;
    }

    char buf[FG_MAX_BUFFER];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, FG_MAX_BUFFER, fmt, args);
    va_end(args);

    return m_file->puts(buf);
}
