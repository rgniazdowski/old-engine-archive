/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgMessageSubsystem.h"

template <>
bool CSingleton<fg::msg::CMessageSubsystem>::instanceFlag = false;

template <>
fg::msg::CMessageSubsystem *CSingleton<fg::msg::CMessageSubsystem>::instance = NULL;

using namespace fg;

/**
 * 
 */
msg::CMessageSubsystem::CMessageSubsystem() { }

/**
 * 
 */
msg::CMessageSubsystem::~CMessageSubsystem() {
    destroy();
}

/**
 * 
 */
void msg::CMessageSubsystem::clear(void) {
    flushAll();
}

/** \brief
 */
fgBool msg::CMessageSubsystem::destroy(void) {
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
fgBool msg::CMessageSubsystem::initialize(void) {
    return FG_TRUE;
}

/**
 * 
 * @param pathAll
 * @param pathError
 * @param pathDebug
 */
void msg::CMessageSubsystem::setLogPaths(const char *pathAll, const char *pathError, const char *pathDebug) {
    setLogAllPath(pathAll);
    setLogErrorPath(pathError);
    setLogDebugPath(pathDebug);
}

/**
 * 
 * @param pathAll
 */
void msg::CMessageSubsystem::setLogAllPath(const char *pathAll) {
    if(pathAll)
        m_logAll.setPath(pathAll);
    m_logAll.setMode(util::CRegularFile::Mode::APPEND);
}

/**
 * 
 * @param pathError
 */
void msg::CMessageSubsystem::setLogErrorPath(const char *pathError) {
    if(pathError)
        m_logError.setPath(pathError);
    m_logError.setMode(util::CRegularFile::Mode::APPEND);
}

/**
 * 
 * @param pathDebug
 */
void msg::CMessageSubsystem::setLogDebugPath(const char *pathDebug) {
    if(pathDebug)
        m_logDebug.setPath(pathDebug);
    m_logDebug.setMode(fg::util::CRegularFile::Mode::APPEND);
}

/**
 * 
 */
void msg::CMessageSubsystem::flushAll(void) {
    while(!m_statusVec.empty()) {
        SStatus *back = m_statusVec.back();
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
fgBool msg::CMessageSubsystem::pushMessage(SMessage *msg) {
    if(!msg)
        return FG_FALSE;

    SStatus *newStatus = new SStatus(msg);
    return pushStatus(newStatus);
}

/**
 * 
 * @param status
 * @return 
 */
fgBool msg::CMessageSubsystem::pushStatus(SStatus *status) {
    if(!status)
        return FG_FALSE;
    m_statusVec.push_back(status);
    fg::util::CRegularFile *filePtr = NULL;
    if(status->message) {
        switch(status->message->type) {
            case MSG_DEBUG:
                filePtr = &m_logDebug;
                break;
            case MSG_ERROR:
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
    log::PrintStatus(status);
    // #FIXME #TODO - buffering messages, cyclic writing to log files (but always to console output)
    // Warning, Info, Debug, Error
    log::PrintStatusToLog(&m_logAll, status);
    // Debug or Error
    if(filePtr)
        log::PrintStatusToLog(filePtr, status);
    return FG_TRUE;
}

/**
 * 
 * @param tagName
 * @param code
 * @param fmt
 */
void msg::CMessageSubsystem::reportSuccess(const char *tagName, int code, const char *fmt, ...) {
    const char *msgData = NULL;
    char buf[BUFFER_MAX];
    if(fmt) {
        va_list args;
        va_start(args, fmt);
        int movc = tagName ? snprintf(buf, BUFFER_MAX - 1, "%s: ", tagName) : 0;
        vsprintf(buf + movc, fmt, args);
        va_end(args);
        msgData = buf;
    }
    SStatus *newStatus = new SStatus();
    pushStatus(newStatus->success(code, msgData));
}

/**
 * 
 * @param tagName
 * @param code
 * @param fmt
 */
void msg::CMessageSubsystem::reportWarning(const char *tagName, int code, const char *fmt, ...) {
    const char *msgData = NULL;
    char buf[BUFFER_MAX];
    if(fmt) {
        va_list args;
        va_start(args, fmt);
        int movc = tagName ? snprintf(buf, BUFFER_MAX - 1, "%s: ", tagName) : 0;
        vsprintf(buf + movc, fmt, args);
        va_end(args);
        msgData = buf;
    }
    SStatus *newStatus = new SStatus();
    pushStatus(newStatus->warning(code, msgData));
}

/**
 * 
 * @param tagName
 * @param code
 * @param fmt
 */
void msg::CMessageSubsystem::reportError(const char *tagName, int code, const char *fmt, ...) {
    const char *msgData = NULL;
    char buf[BUFFER_MAX];
    if(fmt) {
        va_list args;
        va_start(args, fmt);
        int movc = tagName ? snprintf(buf, BUFFER_MAX - 1, "%s: ", tagName) : 0;
        vsprintf(buf + movc, fmt, args);
        va_end(args);
        msgData = buf;
    }
    SStatus *newStatus = new SStatus();
    pushStatus(newStatus->error(code, msgData));
}

/**
 * 
 * @param tagName
 * @param code
 * @param fmt
 */
void msg::CMessageSubsystem::reportDebug(const char *tagName, int code, const char *fmt, ...) {
    const char *msgData = NULL;
    char buf[BUFFER_MAX];
    if(fmt) {
        va_list args;
        va_start(args, fmt);
        int movc = tagName ? snprintf(buf, BUFFER_MAX - 1, "%s: ", tagName) : 0;
        vsprintf(buf + movc, fmt, args);
        va_end(args);
        msgData = buf;
    }
    SStatus *newStatus = new SStatus();
    pushStatus(newStatus->debug(code, msgData));
}

/**
 * 
 * @return 
 */
msg::SStatus *msg::CMessageSubsystem::getLastStatus(void) {
    if(!m_statusVec.empty()) {
        return m_statusVec.back();
    }
    return NULL;
}

/**
 * 
 * @return 
 */
msg::SMessage *msg::CMessageSubsystem::getLastMessage(void) {
    if(!m_statusVec.empty()) {
        SStatus *status = m_statusVec.back();
        if(status->message)
            return status->message;
    }
    return NULL;
}
