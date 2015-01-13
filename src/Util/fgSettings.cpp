/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgSettings.h"

using namespace fg;

/*
 *
 */
CSettings::CSettings() : m_parser(NULL) { }

/*
 *
 */
CSettings::CSettings(const char *filePath) : m_parser(NULL) {
    load(filePath);
}

/*
 *
 */
CSettings::~CSettings() { }

/*
 *
 */
fgBool CSettings::load(const char *filePath) {
    if(!filePath)
        return FG_FALSE;
    if(!m_parser) {
        m_parser = new xml::CParser();
        //m_parser->setReportToMsgSystem(FG_FALSE); !?!
    }
    fgBool status = FG_TRUE;
    fgXMLAutoHandler<CSettings::settingsData> *content = NULL;
    content = new fgXMLAutoHandler<CSettings::settingsData>();
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
