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

#include "Util/fgTime.h"

/*
 * Methods here need fixing and other. #FIXME #TODO #P2
 */

/**
 * Log info message
 */
void FG_LOG::PrintInfo(const char *fmt, ...)
{
	char buf[FG_LOG_BUF_MAX];
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
void FG_LOG::PrintDebug(const char *fmt, ...)
{
	char buf[FG_LOG_BUF_MAX];
	va_list args;

	sprintf(buf, "DEBUG: ");
	va_start(args,fmt);
	vsprintf(buf+strlen(buf), fmt, args);
	va_end(args);

    // s3eDebugTracePrintf(buf);
    puts(buf);
}

/**
 * Log error message
 */
void FG_LOG::PrintError(const char *fmt, ...)
{
	char buf[FG_LOG_BUF_MAX];
	va_list args;

	sprintf(buf, "ERROR: ");
	va_start(args,fmt);
	vsprintf(buf+strlen(buf), fmt, args);
	va_end(args);

    //s3eDebugErrorPrintf(buf);
    puts(buf);
}

void FG_LOG::WriteToLog(fgFile *file, const char *fmt, ...)
{
	if(!file)
		return;
	if(!strlen(file->getPath()))
		return;
	if(!file->isOpen()) {
		if(!file->open(FG_FILE_MODE_APPEND))
			return;
	}

	char buf[FG_LOG_BUF_MAX];
	va_list args;

	va_start(args,fmt);
	vsprintf(buf, fmt, args);
	va_end(args);

	file->puts(buf);
}

void FG_LOG::PrintMessage(fgMessage *message)
{
	if(!message)
		return;

	long timestamp = fgTime::seconds();
	struct tm *ti;
	ti = localtime(&timestamp);

	char buf[FG_LOG_BUF_MAX];
	snprintf(buf, FG_LOG_BUF_MAX-1, "%2d/%2d/%2d %2d:%2d:%2d - %s\n", 
		ti->tm_mday,
		ti->tm_mon+1,
		ti->tm_year-100,
		ti->tm_hour,
		ti->tm_min,
		ti->tm_sec,
		message->data.c_str());

	puts(buf);
}

void FG_LOG::PrintMessageToLog(fgFile *file, fgMessage *message)
{
	if(!message || !file)
		return;
	if(!strlen(file->getPath()))
		return;
	if(!file->isOpen()) {
		if(!file->open(FG_FILE_MODE_APPEND))
			return;
	}
	long timestamp = fgTime::seconds();
	struct tm *ti;
	ti = localtime(&timestamp);

	char buf[FG_LOG_BUF_MAX];
	snprintf(buf, FG_LOG_BUF_MAX-1, "%2d/%2d/%2d %2d:%2d:%2d - %s\n", 
		ti->tm_mday,
		ti->tm_mon+1,
		ti->tm_year-100,
		ti->tm_hour,
		ti->tm_min,
		ti->tm_sec,
		message->data.c_str());

	file->puts(buf);
}
