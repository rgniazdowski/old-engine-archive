/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgMessageSubsystem.h"

template <>
bool fgSingleton<fgMessageSubsystem>::instanceFlag = false;

template <>
fgMessageSubsystem *fgSingleton<fgMessageSubsystem>::instance = NULL;

/**
 * 
 */
fgMessageSubsystem::fgMessageSubsystem() { }

/**
 * 
 */
fgMessageSubsystem::~fgMessageSubsystem() {
    destroy();
}

/**
 * 
 */
void fgMessageSubsystem::clear(void) {
    flushAll();
}

/** \brief
 */
fgBool fgMessageSubsystem::destroy(void) {
    flushAll();

    m_logAll.close();
    m_logError.close();
    m_logDebug.close();
    return FG_TRUE;
}

/**
 * 
 * @return 
 */
fgBool fgMessageSubsystem::initialize(void) {
    return FG_TRUE;
}

/**
 * 
 * @param pathAll
 * @param pathError
 * @param pathDebug
 */
void fgMessageSubsystem::setLogPaths(const char *pathAll, const char *pathError, const char *pathDebug) {
    setLogAllPath(pathAll);
    setLogErrorPath(pathError);
    setLogDebugPath(pathDebug);
}

/**
 * 
 * @param pathAll
 */
void fgMessageSubsystem::setLogAllPath(const char *pathAll) {
    if(pathAll)
        m_logAll.setPath(pathAll);
    m_logAll.setMode(FG_FILE_MODE_APPEND);
}

/**
 * 
 * @param pathError
 */
void fgMessageSubsystem::setLogErrorPath(const char *pathError) {
    if(pathError)
        m_logError.setPath(pathError);
    m_logError.setMode(FG_FILE_MODE_APPEND);
}

/**
 * 
 * @param pathDebug
 */
void fgMessageSubsystem::setLogDebugPath(const char *pathDebug) {
    if(pathDebug)
        m_logDebug.setPath(pathDebug);
    m_logDebug.setMode(FG_FILE_MODE_APPEND);
}

/**
 * 
 */
void fgMessageSubsystem::flushAll(void) {
    while(!m_statusVec.empty()) {
        fgStatus *back = m_statusVec.back();
        //FG_LOG_DEBUG("MSG: Delete status: [%p] - msg: [%p] ", back, back->message);
        //if(back->message)
        //FG_LOG_DEBUG("MSG: Delete [%p] - [%s]", back->message, back->message->data.c_str());
        back->clearMessage();
        delete back;
        m_statusVec.pop_back();
    }
    m_statusVec.clear_optimised();
}

/**
 * 
 * @param msg
 * @return 
 */
fgBool fgMessageSubsystem::pushMessage(fgMessage *msg) {
    if(!msg)
        return FG_FALSE;

    fgStatus *newStatus = new fgStatus(msg);
    return pushStatus(newStatus);
}

/**
 * 
 * @param status
 * @return 
 */
fgBool fgMessageSubsystem::pushStatus(fgStatus *status) {
    if(!status)
        return FG_FALSE;
    m_statusVec.push_back(status);
    fgFile *filePtr = NULL;
    if(status->message) {
        switch(status->message->type) {
            case FG_MESSAGE_DEBUG:
                filePtr = &m_logDebug;
                break;
            case FG_MESSAGE_ERROR:
                filePtr = &m_logError;
                break;
            default:
                break;
        }
    } else {
        if(status->isError()) {
            filePtr = &m_logError;
        }
    }
    FG_LOG::PrintStatus(status);
    // #FIXME #TODO - buffering messages, cyclic writing to log files (but always to console output)
    // Warning, Info, Debug, Error
    FG_LOG::PrintStatusToLog(&m_logAll, status);
    // Debug or Error
    if(filePtr)
        FG_LOG::PrintStatusToLog(filePtr, status);
    return FG_TRUE;
}

/**
 * 
 * @param tagName
 * @param code
 * @param fmt
 */
void fgMessageSubsystem::reportSuccess(const char *tagName, int code, const char *fmt, ...) {
    const char *msgData = NULL;
    char buf[FG_MESSAGE_BUFFER_MAX];
    if(fmt) {
        va_list args;
        va_start(args, fmt);
        int movc = tagName ? snprintf(buf, FG_MESSAGE_BUFFER_MAX - 1, "%s: ", tagName) : 0;
        vsprintf(buf + movc, fmt, args);
        va_end(args);
        msgData = buf;
    }
    fgStatus *newStatus = new fgStatus();
    pushStatus(newStatus->success(code, msgData));
}

/**
 * 
 * @param tagName
 * @param code
 * @param fmt
 */
void fgMessageSubsystem::reportWarning(const char *tagName, int code, const char *fmt, ...) {
    const char *msgData = NULL;
    char buf[FG_MESSAGE_BUFFER_MAX];
    if(fmt) {
        va_list args;
        va_start(args, fmt);
        int movc = tagName ? snprintf(buf, FG_MESSAGE_BUFFER_MAX - 1, "%s: ", tagName) : 0;
        vsprintf(buf + movc, fmt, args);
        va_end(args);
        msgData = buf;
    }
    fgStatus *newStatus = new fgStatus();
    pushStatus(newStatus->warning(code, msgData));
}

/**
 * 
 * @param tagName
 * @param code
 * @param fmt
 */
void fgMessageSubsystem::reportError(const char *tagName, int code, const char *fmt, ...) {
    const char *msgData = NULL;
    char buf[FG_MESSAGE_BUFFER_MAX];
    if(fmt) {
        va_list args;
        va_start(args, fmt);
        int movc = tagName ? snprintf(buf, FG_MESSAGE_BUFFER_MAX - 1, "%s: ", tagName) : 0;
        vsprintf(buf + movc, fmt, args);
        va_end(args);
        msgData = buf;
    }
    fgStatus *newStatus = new fgStatus();
    pushStatus(newStatus->error(code, msgData));
}

/**
 * 
 * @param tagName
 * @param code
 * @param fmt
 */
void fgMessageSubsystem::reportDebug(const char *tagName, int code, const char *fmt, ...) {
    const char *msgData = NULL;
    char buf[FG_MESSAGE_BUFFER_MAX];
    if(fmt) {
        va_list args;
        va_start(args, fmt);
        int movc = tagName ? snprintf(buf, FG_MESSAGE_BUFFER_MAX - 1, "%s: ", tagName) : 0;
        vsprintf(buf + movc, fmt, args);
        va_end(args);
        msgData = buf;
    }
    fgStatus *newStatus = new fgStatus();
    pushStatus(newStatus->debug(code, msgData));
}

/**
 * 
 * @return 
 */
fgStatus *fgMessageSubsystem::getLastStatus(void) {
    if(!m_statusVec.empty()) {
        return m_statusVec.back();
    }
    return NULL;
}

/**
 * 
 * @return 
 */
fgMessage *fgMessageSubsystem::getLastMessage(void) {
    if(!m_statusVec.empty()) {
        fgStatus *status = m_statusVec.back();
        if(status->message)
            return status->message;
    }
    return NULL;
}
