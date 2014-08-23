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

#include "fgCommon.h"
#include "fgMessageCommon.h"

// ? the hell?
typedef unsigned char fgMask8;

/*
 * Simple structure for returning more complex info.
 * It will store value similar to bool (to indicate error/succes,
 * false/true status). Additionally there is a pointer to message 
 * structure holding error/message code and text.
 * Without code or text message the message structure will not be allocated.
 */
struct fgStatus
{
	// Bit mask for holding status (success, error, warning)
	fgMask8 mask;
	// Message - contains indicator code (error code, etc.) and message text.
	fgMessage *message;

	// Default constructor
	fgStatus() : mask(0)
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

	// Assignment operator. If source has message allocated it will be
	// taken over by this fgStatus structure. Pointer in source will be deleted.
	fgStatus& operator= (fgStatus source)
	{
		if(this == &source)
			return *this;

		mask = source.mask;
		if(source.message && !message) {
			message = source.message;
		} else if(source.message) {
			*message = *source.message;
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
		message->info.code = _code;
		return this;
	}

	// Create (initialize) and return status with success.
	// If message (text) is passed  (not NULL) the message
	// struct will be initialized.
	fgStatus *success(const char *msgData = NULL)
	{
		mask = FG_SUCCESS;
		if(msgData) {
			if(!message) {
				message = new fgMessage(FG_MESSAGE_INFO, msgData);
			} else {
				message->data = msgData;
				message->type = FG_MESSAGE_INFO;
				message->info.code = 0;
			}
		}
		return this;
	}

	// Create (initialize) and return status with warning.
	// If message (text) is passed  (not NULL) the message
	// struct will be initialized.
	fgStatus *warning(const char *msgData = NULL)
	{
		mask = FG_WARNING;
		if(msgData) {
			if(!message) {
				message = new fgMessage(FG_MESSAGE_WARNING, msgData);
			} else {
				message->data = msgData;
				message->type = FG_MESSAGE_WARNING;
				message->info.code = 0;
			}
		}
		return this;
	}

	// Create (initialize)  and return status with error.
	// If message (text) is passed (not NULL) the message
	// struct will be initialized.
	fgStatus *error(const char *msgData = NULL)
	{
		mask = FG_ERROR;
		if(msgData) {
			if(!message) {
				message = new fgMessage(FG_MESSAGE_ERROR, msgData);
			} else {
				message->data = msgData;
				message->type = FG_MESSAGE_ERROR;
				message->info.code = 0;
			}
		}
		return this;
	}

	// Create (initialize) and return debug status - this not an error in most cases.
	// If message (text) is passed (not NULL) the message struct will be initialized.
	fgStatus *debug(const char *msgData = NULL)
	{
		mask = FG_WARNING;
		if(msgData) {
			if(!message) {
				message = new fgMessage(FG_MESSAGE_DEBUG, msgData);
			} else {
				message->data = msgData;
				message->type = FG_MESSAGE_DEBUG;
				message->info.code = 0;
			}
		}
		return this;
	}
};

#endif /* _FG_STATUS_H_ */
