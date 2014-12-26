/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgBuildConfig.h"
#include "fgLog.h"
#include "fgErrno.h"

#include <cstdio>
#include <cstring>
#include <cstdarg>

#include "Util/fgTime.h"

namespace FG_LOG {

    void _preparePrintBuf(char *buf, const char *type) {
        long timestamp = fgTime::seconds();
        int mstru = (int)fgTime::ms() % 1000;
        struct tm *ti;
        ti = localtime(&timestamp);

        snprintf(buf, FG_LOG_BUF_MAX - 1, "%02d/%02d/%02d %02d:%02d:%02d.%03d: %s",
                 ti->tm_mday,
                 ti->tm_mon + 1,
                 ti->tm_year - 100,
                 ti->tm_hour,
                 ti->tm_min,
                 ti->tm_sec,
                 mstru,
                 type);
    }
};

/*
 * Log info message
 */
void FG_LOG::PrintInfo(const char *fmt, ...) {
    char buf[FG_LOG_BUF_MAX];
    va_list args;

    //memset(buf, 0, FG_LOG_BUF_MAX);
    FG_LOG::_preparePrintBuf(buf, "INFO: ");
    va_start(args, fmt);
    vsprintf(buf + strlen(buf), fmt, args);
    va_end(args);

    // s3eDebugTracePrintf(buf);
    puts(buf);
}

/*
 * Write log message
 */
void FG_LOG::PrintDebug(const char *fmt, ...) {
#ifdef FG_DEBUG
#if FG_DEBUG
    char buf[FG_LOG_BUF_MAX];
    va_list args;

    //memset(buf, 0, FG_LOG_BUF_MAX);
    FG_LOG::_preparePrintBuf(buf, "DEBUG: ");
    int n = strlen(buf);
    va_start(args, fmt);
    //vsprintf(buf + n, fmt, args);
    vsnprintf(buf + n, FG_LOG_BUF_MAX - n - 1, fmt, args);
    n = strlen(buf);
    va_end(args);

    // s3eDebugTracePrintf(buf);
    puts(buf);
#endif
#endif
}

/*
 * Log error message
 */
void FG_LOG::PrintError(const char *fmt, ...) {
    char buf[FG_LOG_BUF_MAX];
    va_list args;

    //memset(buf, 0, FG_LOG_BUF_MAX);
    FG_LOG::_preparePrintBuf(buf, "ERROR: ");
    va_start(args, fmt);
    vsprintf(buf + strlen(buf), fmt, args);
    va_end(args);

    //s3eDebugErrorPrintf(buf);
    puts(buf);
}

/*
 * Log warning message
 */
void FG_LOG::PrintWarning(const char *fmt, ...) {
    char buf[FG_LOG_BUF_MAX];
    va_list args;

    //memset(buf, 0, FG_LOG_BUF_MAX);
    FG_LOG::_preparePrintBuf(buf, "WARNING: ");
    va_start(args, fmt);
    vsprintf(buf + strlen(buf), fmt, args);
    va_end(args);

    //s3eDebugErrorPrintf(buf);
    puts(buf);
}

/*
 *
 */
void FG_LOG::WriteToLog(fg::util::base::File *file, const char *fmt, ...) {
    if(!file)
        return;
    if(!strlen(file->getPath()))
        return;
    if(!file->isOpen()) {
        if(!file->open(fg::util::base::File::Mode::APPEND))
            return;
    }

    char buf[FG_LOG_BUF_MAX];
    va_list args;

    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);

    file->puts(buf);
}

namespace FG_LOG {

    fgBool _prepareMsgBuf(fgMessage *message, char *buf, long timestamp = -1) {
        if(!message || !buf)
            return FG_FALSE;
        if(timestamp == -1)
            timestamp = fgTime::seconds();
        struct tm *ti;
        ti = localtime(&timestamp);
        const char *msg_type;
        switch(message->type) {
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
        int mstru = (int)fgTime::ms() % 1000;

        snprintf(buf, FG_LOG_BUF_MAX - 1, "%02d/%02d/%02d %02d:%02d:%02d.%03d: %s(%d): %s: %s",
                 ti->tm_mday,
                 ti->tm_mon + 1,
                 ti->tm_year - 100,
                 ti->tm_hour,
                 ti->tm_min,
                 ti->tm_sec,
                 mstru,
                 msg_type,
                 message->code(),
                 fgErrno::strError(message->code()),
                 message->data.c_str());

        return FG_TRUE;
    }

    fgBool _prepareStatusBuf(fgStatus *status, char *buf) {
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
            int mstru = (int)fgTime::ms() % 1000;
            snprintf(buf, FG_LOG_BUF_MAX - 1, "%02d/%02d/%02d %02d:%02d:%02d.%03d: %s(%d): %s",
                     ti->tm_mday,
                     ti->tm_mon + 1,
                     ti->tm_year - 100,
                     ti->tm_hour,
                     ti->tm_min,
                     ti->tm_sec,
                     mstru,
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
void FG_LOG::PrintMessage(fgMessage *message, long timestamp) {
    char buf[FG_LOG_BUF_MAX];
    if(!FG_LOG::_prepareMsgBuf(message, buf, timestamp))
        return;
    puts(buf);
}

/*
 *
 */
void FG_LOG::PrintMessageToLog(fg::util::base::File *file, fgMessage *message, long timestamp) {
    if(!message || !file)
        return;
    if(!strlen(file->getPath()))
        return;
    if(!file->isOpen()) {
        if(!file->open(fg::util::base::File::Mode::APPEND))
            return;
    }
    char buf[FG_LOG_BUF_MAX];
    if(!FG_LOG::_prepareMsgBuf(message, buf, timestamp))
        return;
    int n = (int)strlen(buf);
    buf[n] = '\r';
    buf[n + 1] = '\n';
    buf[n + 2] = '\0';
    file->puts(buf);
}

/*
 *
 */
void FG_LOG::PrintStatus(fgStatus *status) {
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
void FG_LOG::PrintStatusToLog(fg::util::base::File *file, fgStatus *status) {
    if(!status || !file)
        return;
    if(!strlen(file->getPath()))
        return;
    if(status->message) {
        FG_LOG::PrintMessageToLog(file, status->message, status->timestamp);
    } else {
        if(!file->isOpen()) {
            if(!file->open(fg::util::base::File::Mode::APPEND))
                return;
        }
        char buf[FG_LOG_BUF_MAX];
        if(!FG_LOG::_prepareStatusBuf(status, buf))
            return;
        int n = (int)strlen(buf);
        buf[n] = '\r';
        buf[n + 1] = '\n';
        buf[n + 2] = '\0';
        file->puts(buf);
    }
}
