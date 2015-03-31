/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgBuildConfig.h"
#include "fgLog.h"
#include "fgErrno.h"
#include "Util/fgTime.h"

#include <cstdio>
#include <cstring>
#include <cstdarg>



#if defined(FG_USING_PLATFORM_ANDROID)
    #include <android/log.h>
#endif

namespace fg {
    namespace log {

        const char *DEFAULT_FOLDER = "log\0";

        /**
         * 
         * @param buf
         * @param type
         */
        void preparePrintBuffer(char *buf, const char *type) {
            long timestamp = timesys::seconds();
            int mstru = (int)timesys::ms() % 1000;
            struct tm *ti;
            ti = localtime(&timestamp);

            snprintf(buf, BUFFER_MAX - 1, "%02d/%02d/%02d %02d:%02d:%02d.%03d: %s",
                     ti->tm_mday,
                     ti->tm_mon + 1,
                     ti->tm_year - 100,
                     ti->tm_hour,
                     ti->tm_min,
                     ti->tm_sec,
                     mstru,
                     type);
        }

        /**
         * 
         * @param message
         * @param buf
         * @param timestamp
         * @return 
         */
        fgBool prepareMsgBuffer(msg::SMessage *message, char *buf, long timestamp = -1) {
            if(!message || !buf)
                return FG_FALSE;
            if(timestamp == -1)
                timestamp = timesys::seconds();
            struct tm *ti;
            ti = localtime(&timestamp);
            const char *msg_type;
            switch(message->type) {
                case msg::MSG_DEBUG:
                    msg_type = "DEBUG";
                    if(message->debug.critical)
                        msg_type = "CRITICAL DEBUG";
                    break;
                case msg::MSG_ERROR:
                    msg_type = "ERROR";
                    if(message->error.critical)
                        msg_type = "CRITICAL ERROR";
                    break;
                case msg::MSG_WARNING:
                    msg_type = "WARNING";
                    if(message->warning.serious)
                        msg_type = "SERIOUS WARNING";
                    break;
                default:
                    msg_type = "INFO";
                    break;
            };
            int mstru = (int)timesys::ms() % 1000;

            snprintf(buf, log::BUFFER_MAX - 1, "%02d/%02d/%02d %02d:%02d:%02d.%03d: %s(%d): %s: %s",
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

        /**
         * 
         * @param status
         * @param buf
         * @return 
         */
        fgBool prepareStatusBuffer(msg::SStatus *status, char *buf) {
            if(!status || !buf)
                return FG_FALSE;
            if(status->message) {
                prepareMsgBuffer(status->message, buf, status->timestamp);
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
                int mstru = (int)timesys::ms() % 1000;
                snprintf(buf, log::BUFFER_MAX - 1, "%02d/%02d/%02d %02d:%02d:%02d.%03d: %s(%d): %s",
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
};

using namespace fg;

/**
 * Log info message
 * @param fmt
 */
void log::PrintInfo(const char *fmt, ...) {
    char buf[BUFFER_MAX];
    va_list args;

    log::preparePrintBuffer(buf, "INFO: ");
    va_start(args, fmt);
    vsprintf(buf + strlen(buf), fmt, args);
    va_end(args);

    // s3eDebugTracePrintf(buf);
#if defined(FG_USING_PLATFORM_ANDROID)
    __android_log_print(ANDROID_LOG_VERBOSE, FG_PACKAGE_NAME, "%s", buf);
#else
    puts(buf);
#endif
}

/**
 * Write log message
 * @param fmt
 */
void log::PrintDebug(const char *fmt, ...) {
#ifdef FG_DEBUG
#if FG_DEBUG
    char buf[BUFFER_MAX];
    va_list args;

    //memset(buf, 0, FG_LOG_BUF_MAX);
    log::preparePrintBuffer(buf, "DEBUG: ");
    int n = strlen(buf);
    va_start(args, fmt);
    //vsprintf(buf + n, fmt, args);
    vsnprintf(buf + n, BUFFER_MAX - n - 1, fmt, args);
    n = strlen(buf);
    va_end(args);

    // s3eDebugTracePrintf(buf);
    #if defined(FG_USING_PLATFORM_ANDROID)
        __android_log_print(ANDROID_LOG_DEBUG, FG_PACKAGE_NAME, "%s", buf);
    #else
        puts(buf);
    #endif
#endif
#endif
}

/**
 * Log error message
 * @param fmt
 */
void log::PrintError(const char *fmt, ...) {
    char buf[BUFFER_MAX];
    va_list args;

    log::preparePrintBuffer(buf, "ERROR: ");
    va_start(args, fmt);
    vsprintf(buf + strlen(buf), fmt, args);
    va_end(args);

    //s3eDebugErrorPrintf(buf);
#if defined(FG_USING_PLATFORM_ANDROID)
    __android_log_print(ANDROID_LOG_ERROR, FG_PACKAGE_NAME, "%s", buf);
#else
    puts(buf);
#endif
}

/**
 * Log warning message
 * @param fmt
 */
void log::PrintWarning(const char *fmt, ...) {
    char buf[BUFFER_MAX];
    va_list args;

    log::preparePrintBuffer(buf, "WARNING: ");
    va_start(args, fmt);
    vsprintf(buf + strlen(buf), fmt, args);
    va_end(args);

    //s3eDebugErrorPrintf(buf);
#if defined(FG_USING_PLATFORM_ANDROID)
    __android_log_print(ANDROID_LOG_WARN, FG_PACKAGE_NAME, "%s", buf);
#else
    puts(buf);
#endif
}

/**
 * 
 * @param file
 * @param fmt
 * @param ...
 */
void log::WriteToLog(util::base::CFile *file, const char *fmt, ...) {
    if(!file)
        return;
    if(!strlen(file->getPath()))
        return;
    if(!file->isOpen()) {
        if(!file->open(fg::util::base::CFile::Mode::APPEND))
            return;
    }

    char buf[BUFFER_MAX];
    va_list args;

    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);

    file->puts(buf);
}

/**
 * 
 * @param message
 * @param timestamp
 */
void log::PrintMessage(msg::SMessage *message, long timestamp) {
    char buf[log::BUFFER_MAX];
    if(!log::prepareMsgBuffer(message, buf, timestamp))
        return;
#if defined(FG_USING_PLATFORM_ANDROID)
    int priority = 0;
    switch(message->type) {
        case msg::MSG_DEBUG:            
            priority = (int)ANDROID_LOG_DEBUG;
            break;
        case msg::MSG_ERROR:
            priority = (int)ANDROID_LOG_ERROR;
            if(message->error.critical)
                priority = (int)ANDROID_LOG_FATAL;
            break;
        case msg::MSG_WARNING:
            priority = (int)ANDROID_LOG_WARN;
            break;
        default:
            priority = (int)ANDROID_LOG_INFO;
        break;
    };
    __android_log_print(priority, FG_PACKAGE_NAME, "%s", buf);
#else
    puts(buf);
#endif    
}

/**
 * 
 * @param file
 * @param message
 * @param timestamp
 */
void log::PrintMessageToLog(util::base::CFile *file, 
                            msg::SMessage *message, 
                            long timestamp) {
    if(!message || !file)
        return;
    if(!strlen(file->getPath()))
        return;
    if(!file->isOpen()) {
        if(!file->open(util::base::CFile::Mode::APPEND))
            return;
    }
    char buf[BUFFER_MAX];
    if(!prepareMsgBuffer(message, buf, timestamp))
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
void log::PrintStatus(msg::SStatus *status) {
    if(!status)
        return;
    if(status->message) {
        PrintMessage(status->message, status->timestamp);
    } else {
        char buf[log::BUFFER_MAX];
        if(!prepareStatusBuffer(status, buf))
            return;
        puts(buf); // #FIXME
    }
}

/*
 *
 */
void log::PrintStatusToLog(util::base::CFile *file, msg::SStatus *status) {
    if(!status || !file)
        return;
    if(!strlen(file->getPath()))
        return;
    if(status->message) {
        PrintMessageToLog(file, status->message, status->timestamp);
    } else {
        if(!file->isOpen()) {
            if(!file->open(util::base::CFile::Mode::APPEND))
                return;
        }
        char buf[BUFFER_MAX];
        if(!prepareStatusBuffer(status, buf))
            return;
        int n = (int)strlen(buf);
        buf[n] = '\r';
        buf[n + 1] = '\n';
        buf[n + 2] = '\0';
        file->puts(buf);
    }
}
