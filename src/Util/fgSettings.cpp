/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgSettings.h"

/*
 *
 */
fgSettings::fgSettings() : m_parser(NULL) { }

/*
 *
 */
fgSettings::fgSettings(const char *filePath) : m_parser(NULL) {
    load(filePath);
}

/*
 *
 */
fgSettings::~fgSettings() { }

/*
 *
 */
fgBool fgSettings::load(const char *filePath) {
    if(!filePath)
        return FG_FALSE;
    if(!m_parser) {
        m_parser = new fgXMLParser();
        m_parser->setReportToMsgSystem(FG_FALSE);
    }
    fgBool status = FG_TRUE;
    fgXMLAutoHandler<fgSettings::settingsData> *content = NULL;
    content = new fgXMLAutoHandler<fgSettings::settingsData>();
    settingsData data;
    content->setTarget(&data);
    m_parser->setContentHandler(content);
    if(!m_parser->loadXML(filePath)) {
        status = FG_FALSE;
    } else {
        if(!m_parser->parseWithHandler()) {
            status = FG_FALSE;
        }
    }
    delete content;
    content = NULL;
    m_parser->freeXML();

    if(status) {
        m_settings = data;
    }
    delete m_parser;
    m_parser = NULL;
    return status;
}
