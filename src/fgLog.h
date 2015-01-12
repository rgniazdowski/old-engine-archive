/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
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

// #FIXME #TODO things like that should be in xml config file, settings or whatever
    #define FG_LOG_DEFAULT_FOLDER	"log"

    #define FG_LOG_DEFAULT_PREFIX	

    #define FG_LOG_BUF_MAX			4096

namespace FG_LOG {

    // 
    void PrintInfo(const char *fmt, ...);
    // 
    void PrintError(const char *fmt, ...);
    // 
    void PrintDebug(const char *fmt, ...);
    // 
    void PrintWarning(const char *fmt, ...);

    // 
    void WriteToLog(fg::util::base::CFile *file, const char *fmt, ...);

    // 
    void PrintMessage(fgMessage *message, long timestamp = -1);
    // 
    void PrintMessageToLog(fg::util::base::CFile *file, fgMessage *message, long timestamp = -1);

    // 
    void PrintStatus(fgStatus *status);
    //
    void PrintStatusToLog(fg::util::base::CFile *file, fgStatus *status);

};

    #if defined(FG_DEBUG)
        #define FG_LOG_INFO(...) FG_LOG::PrintInfo(__VA_ARGS__)
        #define FG_LOG_DEBUG(...) FG_LOG::PrintDebug(__VA_ARGS__)
        #define FG_LOG_ERROR(...) FG_LOG::PrintError(__VA_ARGS__)
        #define FG_LOG_WARNING(...) FG_LOG::PrintWarning(__VA_ARGS__)
    #else
        #define FG_LOG_INFO(...) FG_LOG::PrintInfo(__VA_ARGS__)
        #define FG_LOG_DEBUG(...) ((void)0)
        #define FG_LOG_ERROR(...) FG_LOG::PrintError(__VA_ARGS__)
        #define FG_LOG_WARNING(...) FG_LOG::PrintWarning(__VA_ARGS__)
    #endif

#endif /* _FG_LOG_H_ */
