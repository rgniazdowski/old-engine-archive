/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_STATUS_REPORTER_H_
#define _FG_STATUS_REPORTER_H_

#include "fgBool.h"
#include "fgErrno.h"
#include "fgStatus.h"

#include <stack>

/*
 *
 */
template<typename TagType>
class fgStatusReporter {
public:
	fgStatusReporter() : m_errCode(FG_ERRNO_OK),
		m_reportToMsgSystem(FG_TRUE)
	{
	}

	virtual ~fgStatusReporter() {
		clearStatus();
	}
public:
	fgBool isError(void) const {
		return (fgBool)(m_errCode != FG_ERRNO_OK);
	}

	int getErrorCode(void) const {
		return m_errCode;
	}

	int getLastErrorCode(void) const {
		if(!m_statusStack.empty())
			return m_statusStack.top()->code();
		return m_errCode;
	}

	void setReportToMsgSystem(fgBool _set) {
		m_reportToMsgSystem = _set;
	}

	fgStatus *getLastStatus(void) const {
		if(!m_statusStack.empty())
			return m_statusStack.top();
		return NULL;
	}
protected:
	void setErrorCode(int _code) {
		m_errCode = _code;
	}

	void reportStatus(fgStatus *_status) {
		if(!_status)
			return;
		if(_status->hasMessage())
			m_errCode = _status->message->code();
		if(m_reportToMsgSystem) {
			_status->setManaged();
		} else {
			_status->isManaged = FG_FALSE;
		}

		if(_status->hasMessage()) {
			char tmp[64];
			// #FIXME ?
			snprintf(tmp, 63, "%s: ", typeid(TagType::_type).name());
			_status->message->data.insert(0, tmp);
		}

		// Remember that this takes over the ownership of fgStatus object
		m_statusStack.push(_status);

		// Report further to message subsystem:
		// Based on the status code and message, subsystem will print
		// it in proper place, save to corresponding file and take ownership
		if(_status->isManaged) {
			// #TODO #P1

		}
	}

	void reportStatus(fgStatus& _status) { // #FIXME
		fgStatus* newStatus(&_status);
		_status.clearMessage();
		reportStatus(newStatus);
	}

	void reportSuccess(const char *msgData = NULL, int _code = FG_ERRNO_OK) {
		fgStatus *newStatus = new fgStatus();
		reportStatus(newStatus->success(msgData, _code));
	}

	void reportWarning(const char *msgData = NULL, int _code = FG_ERRNO_OK) {
		fgStatus *newStatus = new fgStatus();
		reportStatus(newStatus->warning(msgData, _code));
	}

	void reportError(const char *msgData = NULL, int _code = FG_ERRNO_OK) {
		fgStatus *newStatus = new fgStatus();
		reportStatus(newStatus->error(msgData, _code));
	}

	void reportDebug(const char *msgData = NULL, int _code = FG_ERRNO_OK) {
		fgStatus *newStatus = new fgStatus();
		reportStatus(newStatus->debug(msgData, _code));
	}

	void clearStatus(void) {
		while(!m_statusStack.empty()) {
			fgStatus *top = m_statusStack.top();
			// Remove the message only if it's not managed
			if(!top->message->isManaged)
				top->clearMessage();
			// Delete the status (when not managed)
			if(!top->isManaged)
				delete top;
			m_statusStack.pop();
		}
		m_errCode = FG_ERRNO_OK;
	}
protected:
	int		m_errCode;
	fgBool	m_reportToMsgSystem;
	std::stack<fgStatus *> m_statusStack;
};

#endif /* _FG_STATUS_REPORTER_H_ */
