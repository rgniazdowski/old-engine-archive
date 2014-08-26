/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_LOG_H_
#define _FG_LOG_H_

#include "fgBuildConfig.h"
#include "fgMessageCommon.h"
#include "fgStatus.h"
#include "Util/fgFile.h"

// #FIXME #TODO things like that should be in xml config file, settings or whatever
#define FG_LOG_DEFAULT_FOLDER	"log"

#define FG_LOG_DEFAULT_PREFIX	

#define FG_LOG_BUF_MAX			1024

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
void WriteToLog(fgFile *file, const char *fmt, ...);

// 
void PrintMessage(fgMessage *message, long timestamp = -1);
// 
void PrintMessageToLog(fgFile *file, fgMessage *message, long timestamp = -1);

// 
void PrintStatus(fgStatus *status);
//
void PrintStatusToLog(fgFile *file, fgStatus *status);
};

#endif /* _FG_LOG_H_ */
