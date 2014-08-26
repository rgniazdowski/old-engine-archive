/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_SETTINGS_H_
#define _FG_SETTINGS_H_

#include "fgTypes.h"
#include "XML/fgXMLParser.h"
#include "XML/fgXMLDefaultHandler.h"
#include "XML/fgXMLAutoHandler.h"


/*
 *
 */
class fgSettings {
public:
	struct settingsData {
		std::string defaultDataPath;
		std::string defaultLogPath;
		std::string mainConfigPath;
		std::string programTitle;
		std::string defaultProfileName;
		std::string mainProfileName;
		std::string lastExecution;
		int	videoModeID;
		int verboseLevel;
		long lastTimestamp;
		fgBool useSound;
		fgBool useConsole;
		fgBool useNetwork;
		fgBool cleanExit;
		fgBool debugMode;

		settingsData() :
			videoModeID(-1),
			verboseLevel(0),
			lastTimestamp(0L),
			useSound(FG_FALSE),
			useConsole(FG_FALSE),
			useNetwork(FG_FALSE),
			cleanExit(FG_FALSE),
			debugMode(FG_FALSE)
		{
		}

		void clear(void) {

		}
	};
public:
	fgSettings();
	fgSettings(const char *filePath);
	~fgSettings();

	fgBool load(const char *filePath);
protected:
	fgXMLParser *m_parser;
	settingsData m_settings;
};

#define FG_SETTINGS_XML_ROOT_NODE_NAME	"Settings"

FG_XML_AUTO_TEMPLATE_ROOT(fgSettings::settingsData, FG_SETTINGS_XML_ROOT_NODE_NAME);

FG_XML_AUTO_TEMPLATE_ELEMENT_BEGIN(fgSettings::settingsData);
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char *, defaultDataPath,		"defaultDataPath");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char *, defaultLogPath,		"defaultLogPath");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char *, mainConfigPath,		"mainConfigPath");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char *, programTitle,			"programTitle");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char *, defaultProfileName,	"defaultProfileName");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char *, mainProfileName,		"mainProfileName");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char *, lastExecution,		"lastExecution");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(int,		videoModeID,		"videoModeID");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(int,		verboseLevel,		"verboseLevel");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(long,		lastTimestamp,		"lastTimestamp");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(fgBool,		useSound,			"useSound");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(fgBool,		useConsole,			"useConsole");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(fgBool,		useNetwork,			"useNetwork");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(fgBool,		cleanExit,			"cleanExit");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(fgBool,		debugMode,			"debugMode");
FG_XML_AUTO_TEMPLATE_ELEMENT_END();

FG_XML_AUTO_TEMPLATE_CHARACTERS_BEGIN(fgSettings::settingsData);
FG_XML_AUTO_TEMPLATE_CHARACTERS_EMPTY
FG_XML_AUTO_TEMPLATE_CHARACTERS_END();

FG_XML_AUTO_TEMPLATE_ATTRIBUTE_BEGIN(fgSettings::settingsData);
FG_XML_AUTO_TEMPLATE_ATTRIBUTE_EMPTY
FG_XML_AUTO_TEMPLATE_ATTRIBUTE_END();

#endif /* _FG_SETTINGS_H_ */
