/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_LOG_H_
    #define _FG_LOG_H_

    #include "fgBuildConfig.h"
    #include "fgMessageCommon.h"
    #include "fgStatus.h"
    #include "Util/fgFileBase.h"

    #define FG_LOG_DEFAULT_PREFIX	

namespace fg {
    namespace log {
        
        ///
        extern const char* DEFAULT_FOLDER;
        ///
        const unsigned int BUFFER_MAX = 4096;

        /**
         * 
         * @param fmt
         */
        void PrintInfo(const char *fmt, ...);
        /**
         * 
         * @param fmt
         */
        void PrintError(const char *fmt, ...);
        /**
         * 
         * @param fmt
         */ 
        void PrintDebug(const char *fmt, ...);
        /**
         * 
         * @param fmt
         */
        void PrintWarning(const char *fmt, ...);

        /**
         * 
         * @param file
         * @param fmt
         */
        void WriteToLog(util::base::CFile *file, const char *fmt, ...);

        /**
         * 
         * @param message
         * @param timestamp
         */
        void PrintMessage(msg::SMessage *message, long timestamp = -1);
        /**
         * 
         * @param file
         * @param message
         * @param timestamp
         */
        void PrintMessageToLog(util::base::CFile *file, msg::SMessage *message, long timestamp = -1);

        /**
         * 
         * @param status
         */
        void PrintStatus(msg::SStatus *status);
        /**
         * 
         * @param file
         * @param status
         */
        void PrintStatusToLog(util::base::CFile *file, msg::SStatus *status);

    };
};

    #if defined(FG_DEBUG) || defined(DEBUG)
        #define FG_LOG_INFO(...) fg::log::PrintInfo(__VA_ARGS__)
        #define FG_LOG_DEBUG(...) fg::log::PrintDebug(__VA_ARGS__)
        #define FG_LOG_ERROR(...) fg::log::PrintError(__VA_ARGS__)
        #define FG_LOG_WARNING(...) fg::log::PrintWarning(__VA_ARGS__)
    #else
        #define FG_LOG_INFO(...) fg::log::PrintInfo(__VA_ARGS__)
        #define FG_LOG_DEBUG(...) ((void)0)
        #define FG_LOG_ERROR(...) fg::log::PrintError(__VA_ARGS__)
        #define FG_LOG_WARNING(...) fg::log::PrintWarning(__VA_ARGS__)
    #endif

#endif /* _FG_LOG_H_ */
