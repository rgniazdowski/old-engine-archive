/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_STATUS_REPORTER_H_
    #define _FG_STATUS_REPORTER_H_

    #include "fgBool.h"
    #include "fgErrno.h"
    #include "fgStatus.h"

    #include <stack>
    #include <typeinfo>
    #include <cstdarg>

namespace FG_STATUS {
    void reportToMessageSubsystem(fgStatus *_status);
    void printStatus(fgStatus *_status);
};

/*
 *
 */
template<typename TagType>
class fgStatusReporter {
public:
    //
    fgStatusReporter() : m_errCode(FG_ERRNO_OK),
    m_reportToMsgSystem(FG_TRUE) { }
    virtual ~fgStatusReporter() {
        clearStatus();
    }
public:
    //
    fgBool isError(void) const {
        return (fgBool)(m_errCode != FG_ERRNO_OK);
    }
    //
    int getErrorCode(void) const {
        return m_errCode;
    }
    //
    int getLastErrorCode(void) const {
        if(!m_statusVec.empty())
            return m_statusVec.back()->code();
        return m_errCode;
    }

    //
    void setReportToMsgSystem(fgBool _set) {
        m_reportToMsgSystem = _set;
    }

    //
    fgStatus *getLastStatus(void) const {
        if(!m_statusVec.empty())
            return m_statusVec.back();
        return NULL;
    }

    //
    void clearStatus(void) {
        while(!m_statusVec.empty()) {
            fgStatus *back = m_statusVec.back();
            // Remove the message only if it's not managed
            if(back->message) {
                if(!back->message->isManaged)
                    back->clearMessage();
            }
            // Delete the status (when not managed)
            if(!back->isManaged)
                delete back;
            m_statusVec.pop_back();
        }
        m_errCode = FG_ERRNO_OK;
    }

protected:
    //
    void setErrorCode(int _code) {
        m_errCode = _code;
    }
    //
    void reportStatus(fgStatus *_status) {
        if(!_status)
            return;
        if(_status->hasMessage())
            m_errCode = _status->message->code();
        else
            m_errCode = _status->code();
        if(m_reportToMsgSystem) {
            _status->setManaged();
        } else {
            _status->isManaged = FG_FALSE;
        }

        if(_status->hasMessage()) {
            char tmp[64];
            // #FIXME ?
            //snprintf(tmp, 63, "%s: ", typeid(typename TagType::_type).name());
            snprintf(tmp, 63, "%s: ", TagType::name());
            _status->message->data.insert(0, tmp);
        }

        // Remember that this takes over the ownership of fgStatus object
        m_statusVec.push_back(_status);

        // Report further to message subsystem:
        // Based on the status code and message, subsystem will print
        // it in proper place, save to corresponding file and take ownership
        if(_status->isManaged) {
            FG_STATUS::reportToMessageSubsystem(_status);
        } else {
            FG_STATUS::printStatus(_status);
        }
    }

    //
    void reportSuccess(int _code = FG_ERRNO_OK, const char *fmt = NULL, ...) {
        const char *msgData = NULL;
        char buf[FG_MESSAGE_BUFFER_MAX];
        if(fmt) {
            va_list args;
            va_start(args, fmt);
            vsprintf(buf, fmt, args);
            va_end(args);
            msgData = buf;
        }
        fgStatus *newStatus = new fgStatus();
        reportStatus(newStatus->success(_code, msgData));
    }

    //
    void reportWarning(int _code = FG_ERRNO_OK, const char *fmt = NULL, ...) {
        const char *msgData = NULL;
        char buf[FG_MESSAGE_BUFFER_MAX];
        if(fmt) {
            va_list args;
            va_start(args, fmt);
            vsprintf(buf, fmt, args);
            va_end(args);
            msgData = buf;
        }
        fgStatus *newStatus = new fgStatus();
        reportStatus(newStatus->warning(_code, msgData));
    }

    //
    void reportError(int _code = FG_ERRNO_OK, const char *fmt = NULL, ...) {
        const char *msgData = NULL;
        char buf[FG_MESSAGE_BUFFER_MAX];
        if(fmt) {
            va_list args;
            va_start(args, fmt);
            vsprintf(buf, fmt, args);
            va_end(args);
            msgData = buf;
        }
        fgStatus *newStatus = new fgStatus();
        reportStatus(newStatus->error(_code, msgData));
    }

    //
    void reportDebug(int _code = FG_ERRNO_OK, const char *fmt = NULL, ...) {
        const char *msgData = NULL;
        char buf[FG_MESSAGE_BUFFER_MAX];
        if(fmt) {
            va_list args;
            va_start(args, fmt);
            vsprintf(buf, fmt, args);
            va_end(args);
            msgData = buf;
        }
        fgStatus *newStatus = new fgStatus();
        reportStatus(newStatus->debug(_code, msgData));
    }

protected:
    ///
    int m_errCode;
    ///
    fgBool m_reportToMsgSystem;
    ///
    fgVector<fgStatus *> m_statusVec;
};

#endif /* _FG_STATUS_REPORTER_H_ */
