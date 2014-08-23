/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_STATUS_H_
#define _FG_STATUS_H_

#include "fgTypes.h"
#include "fgErrno.h"
#include "fgMessageCommon.h"

// ? the hell?
typedef unsigned char fgMask8;

/*
 * Simple structure for returning more complex info.
 * It will store value similar to bool (to indicate error/succes,
 * false/true status). Additionally there is a pointer to message 
 * structure holding error/message code and text.
 * Without code or text message the message structure will not be allocated.
 *
 * If status is managed it means that the pointer is held also in message subsystem,
 * so in status reporter the object should not be deleted (when clearing stack).
 */
struct fgStatus
{
	// Bit mask for holding status (success, error, warning)
	fgMask8 mask;
	// Message - contains indicator code (error code, etc.) and message text.
	fgMessage *message;
	// Is this status managed in the message subsystem?
	fgBool isManaged;
	// 
	int errCode;

	// Default constructor
	fgStatus() : mask(0), isManaged(FG_FALSE), errCode(FG_ERRNO_OK)
	{
		message = NULL;
	}

	// Default destructor
	~fgStatus()
	{
		// Do not free *message
		// overloaded assignment operators in fgStatus and fgMessage
		// take care of it (it's taking over the ownership)
		// Message from source will be cleared
	}

	fgStatus *setManaged(void) {
		isManaged = FG_TRUE;
		// If status is managed, then message needs to be also
		if(message)
			message->setManaged();
		return this;
	}

	// Assignment operator. If source has message allocated it will be
	// taken over by this fgStatus structure. Pointer in source will be deleted.
	// FIXME - this wont be needed (I think) - need further testing
	fgStatus& operator= (fgStatus source)
	{
		if(this == &source)
			return *this;

		errCode = source.errCode;
		mask = source.mask;
		isManaged = source.isManaged;
		if(source.message && !message) {
			message = source.message;
		} else if(source.message) {
			*message = *source.message;
			if(!source.isManaged) // #FIXME #ERROR possible
				source.clearMessage();
		}
		else {
			message = NULL;
		}

		return *this;
	}

	// Clear message contents (delete)
	void clearMessage(void) {
		if(message) {
			delete message;
			message = NULL;
		}
	}

	int code(void) const {
		if(message) {
			return message->code();
		}
		return errCode;
	}

	fgBool hasMessage(void) const {
		if(message)
			return FG_TRUE;
		return FG_FALSE;
	}

	// True if current status is success
	fgBool isSuccess(void)
	{
		return (fgBool)(mask & FG_SUCCESS);
	}

	// Check whether current status is warning (message)
	fgBool isWarning(void)
	{
		return (fgBool)(mask == FG_WARNING);
	}

	// Check whether current status is error
	fgBool isError(void)
	{
		return (fgBool)(mask == FG_ERROR);
	}

	// Set code for the current status (in message).
	// If message is NULL, it'll be allocated with new.
	fgStatus *setCode(int _code)
	{
		if(!message) {
			message = new fgMessage(FG_MESSAGE_INFO, _code);
		}
		message->setCode(_code);
		errCode = _code;
		return this;
	}

	// Create (initialize) and return status with success.
	// If message (text) is passed  (not NULL) the message
	// struct will be initialized.
	fgStatus *success(const char *msgData = NULL, int _code = FG_ERRNO_OK)
	{
		mask = FG_SUCCESS;
		if(msgData) {
			if(!message) {
				message = new fgMessage(FG_MESSAGE_INFO, msgData);
			} else {
				message->data = msgData;
				message->type = FG_MESSAGE_INFO;
				setCode(_code);
			}
		}
		if(isManaged && message)
			message->setManaged();
		return this;
	}

	// Create (initialize) and return status with warning.
	// If message (text) is passed  (not NULL) the message
	// struct will be initialized.
	fgStatus *warning(const char *msgData = NULL, int _code = FG_ERRNO_OK)
	{
		mask = FG_WARNING;
		if(msgData) {
			if(!message) {
				message = new fgMessage(FG_MESSAGE_WARNING, msgData);
			} else {
				message->data = msgData;
				message->type = FG_MESSAGE_WARNING;
				setCode(_code);
			}
		}
		if(isManaged && message)
			message->setManaged();
		return this;
	}

	// Create (initialize)  and return status with error.
	// If message (text) is passed (not NULL) the message
	// struct will be initialized.
	fgStatus *error(const char *msgData = NULL, int _code = FG_ERRNO_OK)
	{
		mask = FG_ERROR;
		if(msgData) {
			if(!message) {
				message = new fgMessage(FG_MESSAGE_ERROR, msgData);
			} else {
				message->data = msgData;
				message->type = FG_MESSAGE_ERROR;
				setCode(_code);
			}
		}
		if(isManaged && message)
			message->setManaged();
		return this;
	}

	// Create (initialize) and return debug status - this not an error in most cases.
	// If message (text) is passed (not NULL) the message struct will be initialized.
	fgStatus *debug(const char *msgData = NULL, int _code = FG_ERRNO_OK)
	{
		mask = FG_WARNING;
		if(msgData) {
			if(!message) {
				message = new fgMessage(FG_MESSAGE_DEBUG, msgData);
			} else {
				message->data = msgData;
				message->type = FG_MESSAGE_DEBUG;
				setCode(_code);
			}
		}
		if(isManaged && message)
			message->setManaged();
		return this;
	}
};

#endif /* _FG_STATUS_H_ */
