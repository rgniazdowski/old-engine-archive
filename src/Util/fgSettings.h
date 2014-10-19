/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
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
    // 

    struct settingsData {
        std::string defaultDataPath; // Path to the data folder
        std::string defaultLogPath; // Path to the log folder
        std::string mainConfigPath; // Path to the main configuration file
        std::string programTitle; // Program title
        std::string defaultProfileName; // Default profile name
        std::string mainProfileName; // Main profile name
        //std::string lastExecution;		// Last run/execution time in readable format (string/text)
        //int	videoModeID;				// Active video mode ID
        int verboseLevel; // Verbose level
        //long lastTimestamp;				// Last run timestamp
        fgBool useSound; // Will be sound used?
        fgBool useConsole; // Will be console used (GUI)?
        fgBool useNetwork; // Will be network used?
        //fgBool cleanExit;				// Did the application closed normally last time?
        fgBool debugMode; // Is debug mode on?

        // 
        settingsData() :
        //videoModeID(-1),
        verboseLevel(0),
        //lastTimestamp(0L),
        useSound(FG_FALSE),
        useConsole(FG_FALSE),
        useNetwork(FG_FALSE),
        //cleanExit(FG_FALSE),
        debugMode(FG_FALSE) { }

        // 
        void clear(void) {
 }
    };
public:
    // 
    fgSettings();
    // 
    fgSettings(const char *filePath);
    // 
    ~fgSettings();

    // 
    fgBool load(const char *filePath);
protected:
    // 
    fgXMLParser *m_parser;
    // 
    settingsData m_settings;
public:
    // 
    std::string &getDefaultDataPath(void) {
        return m_settings.defaultDataPath;
    }
    // 
    const char *getDefaultDataPathStr(void) const {
        return m_settings.defaultDataPath.c_str();
    }
    // 
    void setDefaultDataPath(const char *path) {
        if(path)
            m_settings.defaultDataPath = path;
    }

    // 
    std::string &getDefaultLogPath(void) {
        return m_settings.defaultLogPath;
    }
    // 
    const char *getDefaultLogPathStr(void) const {
        return m_settings.defaultLogPath.c_str();
    }
    // 
    void setDefaultLogPath(const char *path) {
        if(path)
            m_settings.defaultLogPath = path;
    }

    // 
    std::string &getMainConfigPath(void) {
        return m_settings.mainConfigPath;
    }
    // 
    const char *getMainConfigPathStr(void) const {
        return m_settings.mainConfigPath.c_str();
    }
    // 
    void setMainConfigPath(const char *path) {
        if(path)
            m_settings.mainConfigPath = path;
    }

    // 
    std::string &getProgramTitle(void) {
        return m_settings.programTitle;
    }
    // 
    const char *getProgramTitleStr(void) const {
        return m_settings.programTitle.c_str();
    }
    // 
    void setProgramTitle(const char *path) {
        if(path)
            m_settings.programTitle = path;
    }

    // 
    std::string &getDefaultProfileName(void) {
        return m_settings.defaultProfileName;
    }
    // 
    const char *getDefaultProfileNameStr(void) const {
        return m_settings.defaultProfileName.c_str();
    }
    // 
    void setDefaultProfileName(const char *path) {
        if(path)
            m_settings.defaultProfileName = path;
    }

    // 
    std::string &getMainProfileName(void) {
        return m_settings.mainProfileName;
    }
    // 
    const char *getMainProfileNameStr(void) const {
        return m_settings.mainProfileName.c_str();
    }
    // 
    void setMainProfileName(const char *path) {
        if(path)
            m_settings.mainProfileName = path;
    }
    #if 0
    // 
    std::string &getLastExecution(void) {
        return m_settings.lastExecution;
    }
    // 
    const char *getLastExecutionStr(void) const {
        return m_settings.lastExecution.c_str();
    }
    // 
    void setLastExecution(const char *path) {
        if(path)
            m_settings.lastExecution = path;
    }

    // 
    int getVideoModeID(void) const {
        return m_settings.videoModeID;
    }
    // 
    void setVideoModeID(int modeID) {
        m_settings.videoModeID = modeID;
    }
    #endif
    // 
    int getVerboseLevel(void) const {
        return m_settings.verboseLevel;
    }
    // 
    void setVerboseLevel(int verboseLevel) {
        m_settings.verboseLevel = verboseLevel;
    }
    #if 0
    // 
    long getLastTimestamp(void) const {
        return m_settings.lastTimestamp;
    }
    // 
    void setLastTimestamp(long timestamp) {
        m_settings.lastTimestamp = timestamp;
    }
    #endif
    // 
    fgBool isUseSound(void) const {
        return m_settings.useSound;
    }
    // 
    void setUseSound(fgBool toggle) {
        m_settings.useSound = toggle;
    }

    // 
    fgBool isUseConsole(void) const {
        return m_settings.useConsole;
    }
    // 
    void setUseConsole(fgBool toggle) {
        m_settings.useConsole = toggle;
    }

    // 
    fgBool isUseNetwork(void) const {
        return m_settings.useNetwork;
    }
    // 
    void setUseNetwork(fgBool toggle) {
        m_settings.useNetwork = toggle;
    }
    #if 0
    // 
    fgBool isCleanExit(void) const {
        return m_settings.cleanExit;
    }
    // 
    void setCleanExit(fgBool toggle) {
        m_settings.cleanExit = toggle;
    }
    #endif
    // 
    fgBool isDebugMode(void) const {
        return m_settings.debugMode;
    }
    // 
    void setDebugMode(fgBool toggle) {
        m_settings.debugMode = toggle;
    }

};

    #define FG_SETTINGS_XML_ROOT_NODE_NAME	"Settings"

FG_XML_AUTO_TEMPLATE_ROOT(fgSettings::settingsData, FG_SETTINGS_XML_ROOT_NODE_NAME);

FG_XML_AUTO_TEMPLATE_ELEMENT_BEGIN(fgSettings::settingsData);
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char *, defaultDataPath, "defaultDataPath");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char *, defaultLogPath, "defaultLogPath");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char *, mainConfigPath, "mainConfigPath");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char *, programTitle, "programTitle");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char *, defaultProfileName, "defaultProfileName");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char *, mainProfileName, "mainProfileName");
//FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char *, lastExecution,		"lastExecution");
//FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(int,		videoModeID,		"videoModeID");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(int, verboseLevel, "verboseLevel");
//FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(long,		lastTimestamp,		"lastTimestamp");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(fgBool, useSound, "useSound");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(fgBool, useConsole, "useConsole");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(fgBool, useNetwork, "useNetwork");
//FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(fgBool,		cleanExit,			"cleanExit");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(fgBool, debugMode, "debugMode");
FG_XML_AUTO_TEMPLATE_ELEMENT_END();

FG_XML_AUTO_TEMPLATE_CHARACTERS_BEGIN(fgSettings::settingsData);
FG_XML_AUTO_TEMPLATE_CHARACTERS_EMPTY
FG_XML_AUTO_TEMPLATE_CHARACTERS_END();

FG_XML_AUTO_TEMPLATE_ATTRIBUTE_BEGIN(fgSettings::settingsData);
FG_XML_AUTO_TEMPLATE_ATTRIBUTE_EMPTY
FG_XML_AUTO_TEMPLATE_ATTRIBUTE_END();

#endif /* _FG_SETTINGS_H_ */
