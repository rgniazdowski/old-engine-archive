/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgSettings.h"

/*
 *
 */
fgSettings::fgSettings() : m_parser(NULL) {

}

/*
 *
 */
fgSettings::fgSettings(const char *filePath) : m_parser(NULL)
{
	load(filePath);
}

/*
 *
 */
fgSettings::~fgSettings()
{
}

fgBool fgSettings::load(const char *filePath)
{
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

		printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
		printf(">>>>>>> defaultDataPath: '%s'\n", data.defaultDataPath);
		printf(">>>>>>> defaultLogPath:  '%s'\n", data.defaultLogPath);
		printf(">>>>>>> programTitle:    '%s'\n", data.programTitle);
		printf(">>>>>>> useConsole:      '%d'\n", data.useConsole);
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n");
	}
	delete m_parser;
	m_parser = NULL;
	return status;
}
