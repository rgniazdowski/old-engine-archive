/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgLog.h"

#include <cstdio>
#include <cstring>
#include <cstdarg>

/*
 * Methods here need fixing and other. #FIXME #TODO #P2
 */

/**
 * Log info message
 */
void FG_InfoLog(const char *fmt, ...)
{
	char buf[256];
	va_list args;

	sprintf(buf, "INFO: ");
	va_start(args,fmt);
	vsprintf(buf+strlen(buf), fmt, args);
	va_end(args);

    // s3eDebugTracePrintf(buf);
    puts(buf);
}

/**
 * Write log message
 */
void FG_WriteLog(const char *fmt, ...)
{
	char buf[256];
	va_list args;

	sprintf(buf, "LOG: ");
	va_start(args,fmt);
	vsprintf(buf+strlen(buf), fmt, args);
	va_end(args);

    // s3eDebugTracePrintf(buf);
    puts(buf);
}

/**
 * Log error message
 */
void FG_ErrorLog(const char *fmt, ...)
{
	char buf[256];
	va_list args;

	sprintf(buf, "ERROR: ");
	va_start(args,fmt);
	vsprintf(buf+strlen(buf), fmt, args);
	va_end(args);

    //s3eDebugErrorPrintf(buf);
    puts(buf);
}
