/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgLog.h"
#include "fgErrno.h"

#include <cstdio>
#include <cstring>
#include <cstdarg>

#include "Util/fgTime.h"

/*
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

/*
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

/*
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

/*
 * Log warning message
 */
void FG_LOG::PrintWarning(const char *fmt, ...)
{
	char buf[FG_LOG_BUF_MAX];
	va_list args;

	sprintf(buf, "WARNING: ");
	va_start(args,fmt);
	vsprintf(buf+strlen(buf), fmt, args);
	va_end(args);

    //s3eDebugErrorPrintf(buf);
    puts(buf);
}

/*
 *
 */
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

namespace FG_LOG {
	fgBool _prepareMsgBuf(fgMessage *message, char *buf, long timestamp = -1)
	{
		if(!message || !buf)
			return FG_FALSE;
		if(timestamp == -1)
			timestamp = fgTime::seconds();
		struct tm *ti;
		ti = localtime(&timestamp);

		const char *msg_type;
		switch(message->type)
		{
		case FG_MESSAGE_DEBUG:
			msg_type = "DEBUG";
			if(message->debug.critical)
				msg_type = "CRITICAL DEBUG";
			break;
		case FG_MESSAGE_ERROR:
			msg_type = "ERROR";
			if(message->error.critical)
				msg_type = "CRITICAL ERROR";
			break;
		case FG_MESSAGE_WARNING:
			msg_type = "WARNING";
			if(message->warning.serious)
				msg_type = "SERIOUS WARNING";
			break;
		default:
			msg_type = "INFO";
			break;
		}; 

		snprintf(buf, FG_LOG_BUF_MAX-1, "%02d/%02d/%02d %02d:%02d:%02d - %s(%d): %s; additional info: %s", 
			ti->tm_mday,
			ti->tm_mon+1,
			ti->tm_year-100,
			ti->tm_hour,
			ti->tm_min,
			ti->tm_sec,
			msg_type,
			message->code(),
			fgErrno::strError(message->code()),
			message->data.c_str());

		return FG_TRUE;
	}

	fgBool _prepareStatusBuf(fgStatus *status, char *buf)
	{
		if(!status || !buf)
			return FG_FALSE;
		if(status->message) {
			FG_LOG::_prepareMsgBuf(status->message, buf, status->timestamp);
		} else {
			const char *msg_type = "INFO";
			if(status->isError()) {
				msg_type = "ERROR";
			} else if(status->isWarning()) {
				msg_type = "WARNING";
			} else if(status->isSuccess()) {
				msg_type = "SUCCESS";
			}
			struct tm *ti;
			ti = localtime(&status->timestamp);
			snprintf(buf, FG_LOG_BUF_MAX-1, "%02d/%02d/%02d %02d:%02d:%02d - %s(%d): %s", 
				ti->tm_mday,
				ti->tm_mon+1,
				ti->tm_year-100,
				ti->tm_hour,
				ti->tm_min,
				ti->tm_sec,
				msg_type,
				status->code(),
				fgErrno::strError(status->code()));
		}
		return FG_TRUE;
	}
};

/*
 *
 */
void FG_LOG::PrintMessage(fgMessage *message, long timestamp)
{
	char buf[FG_LOG_BUF_MAX];
	if(!FG_LOG::_prepareMsgBuf(message, buf, timestamp))
		return;
	puts(buf);
}

/*
 *
 */
void FG_LOG::PrintMessageToLog(fgFile *file, fgMessage *message, long timestamp)
{
	if(!message || !file)
		return;
	if(!strlen(file->getPath()))
		return;
	if(!file->isOpen()) {
		if(!file->open(FG_FILE_MODE_APPEND))
			return;
	}
	char buf[FG_LOG_BUF_MAX];
	if(!FG_LOG::_prepareMsgBuf(message, buf, timestamp))
		return;
	file->puts(buf);
}

/*
 *
 */
void FG_LOG::PrintStatus(fgStatus *status)
{
	if(!status)
		return;
	if(status->message) {
		FG_LOG::PrintMessage(status->message, status->timestamp);
	} else {
		char buf[FG_LOG_BUF_MAX];
		if(!FG_LOG::_prepareStatusBuf(status, buf))
			return;
		puts(buf);
	}
}

/*
 *
 */
void FG_LOG::PrintStatusToLog(fgFile *file, fgStatus *status)
{
	if(!status || !file)
		return;
	if(!strlen(file->getPath()))
		return;
	if(status->message) {
		FG_LOG::PrintMessageToLog(file, status->message, status->timestamp);
	} else {
		if(!file->isOpen()) {
			if(!file->open(FG_FILE_MODE_APPEND))
				return;
		}
		char buf[FG_LOG_BUF_MAX];
		if(!FG_LOG::_prepareStatusBuf(status, buf))
			return;
		file->puts(buf);
	}
}
