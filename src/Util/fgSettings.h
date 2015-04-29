/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_SETTINGS
    #define FG_INC_SETTINGS
    #define FG_INC_SETTINGS_BLOCK

    #include "fgTypes.h"
    #include "XML/fgXMLParser.h"
    #include "XML/fgXMLDefaultHandler.h"
    #include "XML/fgXMLAutoHandler.h"

namespace fg {

    /**
     *
     */
    class CSettings {
    public:

        /**
         *
         */
        struct settingsData {
            /// Installation root dir
            std::string installationPath;
            /// Path to the data folder
            std::string defaultDataPath;
            /// Path to the log folder
            std::string defaultLogPath;
            /// Path to the main configuration file
            std::string mainConfigPath;
            /// Program title
            std::string programTitle;
            /// Default profile name
            std::string defaultProfileName;
            /// Main mod path (main modification folder - defaults to main in most cases)
            std::string mainModPath;
            /// Current mod path (modification folder name)
            std::string currentModPath;
            //std::string lastExecution;		// Last run/execution time in readable format (string/text)
            //int	videoModeID;				// Active video mode ID
            /// Verbose level
            int verboseLevel;
            //long lastTimestamp;				// Last run timestamp
            /// Will sound be used?
            fgBool useSound;
            /// Will console be used (GUI)?
            fgBool useConsole;
            /// Will network be used?
            fgBool useNetwork;
            //fgBool cleanExit;				// Did the application closed normally last time?
            /// Is debug mode on?
            fgBool debugMode;
            /**
             * 
             */
            settingsData() :
            defaultProfileName("default"),
            mainModPath("main"),
            currentModPath("mod"),
            //videoModeID(-1),
            verboseLevel(FG_VERBOSE_LEVEL),
            //lastTimestamp(0L),
            useSound(FG_FALSE),
            useConsole(FG_FALSE),
            useNetwork(FG_FALSE),
            //cleanExit(FG_FALSE),
            debugMode(FG_FALSE) { }
            /**
             * 
             */
            void clear(void) { }
        };

    protected:
        ///
        xml::CParser *m_parser;
        /// 
        settingsData m_settings;

    public:
        /**
         * 
         */
        CSettings();
        /**
         * 
         * @param filePath
         */
        CSettings(const char* filePath);
        /**
         * 
         */
        virtual ~CSettings();

        /**
         * 
         * @param filePath
         * @return 
         */
        fgBool load(const char* filePath);

    public:
        /**
         *
         * @return
         */
        std::string& getInstallationPath(void) {
            return m_settings.installationPath;
        }
        /**
         * 
         * @return 
         */
        std::string const& getInstallationPath(void) const {
            return m_settings.installationPath;
        }
        /**
         *
         * @return
         */
        const char* getInstallationPathStr(void) const {
            return m_settings.installationPath.c_str();
        }
        /**
         * 
         * @param path
         */
        void setInstallationPath(const char* path) {
            if(path)
                m_settings.installationPath = path;
        }
        //----------------------------------------------------------------------
        /**
         * 
         * @return 
         */
        std::string& getDefaultDataPath(void) {
            return m_settings.defaultDataPath;
        }
        /**
         *
         * @return
         */
        std::string const& getDefaultDataPath(void) const {
            return m_settings.defaultDataPath;
        }
        /**
         * 
         * @return 
         */
        const char* getDefaultDataPathStr(void) const {
            return m_settings.defaultDataPath.c_str();
        }
        /**
         * 
         * @param path
         */
        void setDefaultDataPath(const char* path) {
            if(path)
                m_settings.defaultDataPath = path;
        }
        //----------------------------------------------------------------------
        /**
         * 
         * @return 
         */
        std::string& getDefaultLogPath(void) {
            return m_settings.defaultLogPath;
        }
        /**
         *
         * @return
         */
        std::string const& getDefaultLogPath(void) const {
            return m_settings.defaultLogPath;
        }
        /**
         * 
         * @return 
         */
        const char* getDefaultLogPathStr(void) const {
            return m_settings.defaultLogPath.c_str();
        }
        /**
         * 
         * @param path
         */
        void setDefaultLogPath(const char* path) {
            if(path)
                m_settings.defaultLogPath = path;
        }
        //----------------------------------------------------------------------
        /**
         * 
         * @return 
         */
        std::string& getMainConfigPath(void) {
            return m_settings.mainConfigPath;
        }
        /**
         *
         * @return
         */
        std::string const& getMainConfigPath(void) const {
            return m_settings.mainConfigPath;
        }
        /**
         * 
         * @return 
         */
        const char* getMainConfigPathStr(void) const {
            return m_settings.mainConfigPath.c_str();
        }
        /**
         * 
         * @param path
         */
        void setMainConfigPath(const char* path) {
            if(path)
                m_settings.mainConfigPath = path;
        }
        //----------------------------------------------------------------------
        /**
         * 
         * @return 
         */
        std::string& getProgramTitle(void) {
            return m_settings.programTitle;
        }
        /**
         *
         * @return
         */
        std::string const& getProgramTitle(void) const {
            return m_settings.programTitle;
        }
        /**
         * 
         * @return 
         */
        const char* getProgramTitleStr(void) const {
            return m_settings.programTitle.c_str();
        }
        /**
         * 
         * @param path
         */
        void setProgramTitle(const char* path) {
            if(path)
                m_settings.programTitle = path;
        }
        //----------------------------------------------------------------------
        /**
         * 
         * @return 
         */
        std::string& getDefaultProfileName(void) {
            return m_settings.defaultProfileName;
        }
/**
         *
         * @return
         */
        std::string const& getDefaultProfileName(void) const {
            return m_settings.defaultProfileName;
        }
        /**
         * 
         * @return 
         */
        const char* getDefaultProfileNameStr(void) const {
            return m_settings.defaultProfileName.c_str();
        }
        /**
         * 
         * @param path
         */
        void setDefaultProfileName(const char* path) {
            if(path)
                m_settings.defaultProfileName = path;
        }
        //----------------------------------------------------------------------
        /**
         * 
         * @return 
         */
        std::string& getMainModPath(void) {
            return m_settings.mainModPath;
        }
        /**
         *
         * @return
         */
        std::string const& getMainModPath(void) const {
            return m_settings.mainModPath;
        }
        /**
         * 
         * @return 
         */
        const char* getMainModPathStr(void) const {
            return m_settings.mainModPath.c_str();
        }
        /**
         * 
         * @param path
         */
        void setMainModPath(const char* path) {
            if(path)
                m_settings.mainModPath = path;
        }
        //----------------------------------------------------------------------
        /**
         * 
         * @return 
         */
        std::string& getCurrentModPath(void) {
            return m_settings.currentModPath;
        }
        /**
         *
         * @return
         */
        std::string const& getCurrentModPath(void) const {
            return m_settings.currentModPath;
        }
        /**
         * 
         * @return 
         */
        const char* getCurrentModPathStr(void) const {
            return m_settings.currentModPath.c_str();
        }
        /**
         * 
         * @param path
         */
        void setCurrentModPath(const char* path) {
            if(path)
                m_settings.currentModPath = path;
        }
        //----------------------------------------------------------------------
    #if 0
        // 
        std::string& getLastExecution(void) {
            return m_settings.lastExecution;
        }
        // 
        const char* getLastExecutionStr(void) const {
            return m_settings.lastExecution.c_str();
        }
        // 
        void setLastExecution(const char* path) {
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
        /**
         * 
         * @return 
         */
        int getVerboseLevel(void) const {
            return m_settings.verboseLevel;
        }
        /**
         * 
         * @param verboseLevel
         */
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
        /**
         * 
         * @return 
         */
        fgBool isUseSound(void) const {
            return m_settings.useSound;
        }
        /**
         * 
         * @param toggle
         */
        void setUseSound(fgBool toggle) {
            m_settings.useSound = toggle;
        }
        //----------------------------------------------------------------------
        /**
         * 
         * @return 
         */
        fgBool isUseConsole(void) const {
            return m_settings.useConsole;
        }
        /**
         * 
         * @param toggle
         */
        void setUseConsole(fgBool toggle) {
            m_settings.useConsole = toggle;
        }
        //----------------------------------------------------------------------
        /**
         * 
         * @return 
         */
        fgBool isUseNetwork(void) const {
            return m_settings.useNetwork;
        }
        /**
         * 
         * @param toggle
         */
        void setUseNetwork(fgBool toggle) {
            m_settings.useNetwork = toggle;
        }
        //----------------------------------------------------------------------
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
        //----------------------------------------------------------------------
        /**
         * 
         * @return 
         */
        fgBool isDebugMode(void) const {
            return m_settings.debugMode;
        }
        /**
         * 
         * @param toggle
         */
        void setDebugMode(fgBool toggle) {
            m_settings.debugMode = toggle;
        }
    };

};
    #define FG_SETTINGS_XML_ROOT_NODE_NAME	"Settings"

FG_XML_AUTO_TEMPLATE_ROOT(fg::CSettings::settingsData, FG_SETTINGS_XML_ROOT_NODE_NAME);

FG_XML_AUTO_TEMPLATE_ELEMENT_BEGIN(fg::CSettings::settingsData);
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char*, installationPath, "installationPath");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char*, defaultDataPath, "defaultDataPath");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char*, defaultLogPath, "defaultLogPath");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char*, mainConfigPath, "mainConfigPath");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char*, programTitle, "programTitle");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char*, defaultProfileName, "defaultProfileName");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char*, mainModPath, "mainModPath");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char*, currentModPath, "currentModPath");
//FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(const char* , lastExecution,		"lastExecution");
//FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(int,		videoModeID,		"videoModeID");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(int, verboseLevel, "verboseLevel");
//FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(long,		lastTimestamp,		"lastTimestamp");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(fgBool, useSound, "useSound");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(fgBool, useConsole, "useConsole");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(fgBool, useNetwork, "useNetwork");
//FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(fgBool,		cleanExit,			"cleanExit");
FG_XML_AUTO_TEMPLATE_ELEMENT_CHECK_NAME(fgBool, debugMode, "debugMode");
FG_XML_AUTO_TEMPLATE_ELEMENT_END();

FG_XML_AUTO_TEMPLATE_CHARACTERS_BEGIN(fg::CSettings::settingsData);
FG_XML_AUTO_TEMPLATE_CHARACTERS_EMPTY
FG_XML_AUTO_TEMPLATE_CHARACTERS_END();

FG_XML_AUTO_TEMPLATE_ATTRIBUTE_BEGIN(fg::CSettings::settingsData);
FG_XML_AUTO_TEMPLATE_ATTRIBUTE_EMPTY
FG_XML_AUTO_TEMPLATE_ATTRIBUTE_END();

    #undef FG_INC_SETTINGS_BLOCK
#endif /* FG_INC_SETTINGS */
