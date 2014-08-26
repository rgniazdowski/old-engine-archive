/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_MESSAGE_COMMON_H_
#define _FG_MESSAGE_COMMON_H_

#include "fgBool.h"
#include "fgErrno.h"

/*
 * Enum for the common message types
 */
enum fgMessageType {
	FG_MESSAGE_INVALID = -1,
	FG_MESSAGE_INFO = 0,
	FG_MESSAGE_WARNING = 1,
	FG_MESSAGE_ERROR = 2,
	FG_MESSAGE_DEBUG = 3,
	FG_NUM_MESSAGE_TYPES = 5
};

struct fgMsgBase {
	fgMessageType type;
	int code;
};

/*
 * Structure for the info message
 */
struct fgInfo : fgMsgBase
{
};

/*
 * Structure for the warning message
 */
struct fgWarning : fgMsgBase
{
	fgBool serious;
};

/*
 * Structure for the error message
 */
struct fgError : fgMsgBase
{
	fgBool critical;
};

/*
 * Structure for the debug message
 */
struct fgDebug : fgMsgBase
{
	fgBool critical;
};

#define FG_MESSAGE_BUFFER_MAX		512

/*
 * Main structure for any type of message (and message code)
 * When returning this kind of object - via fgStatus struct
 * for example - it should be newly allocated and then 
 * disposed by the function retrieving it. Or it can be thrown
 * onto some kind of stack (message log/history/console)
 */
struct fgMessage
{
	union {
		// The type of the message
		fgMessageType type;
		// Info part of the message
		fgInfo info;
		// Warning part of the message
		fgWarning warning;
		// Error part
		fgError error;
		// Debug part (type, code)
		fgDebug debug;
	};
	// Message data (text)
	std::string data;
	// Is this status managed in the message subsystem?
	fgBool isManaged;

	// Default constructor for message object
	fgMessage() : 
		type(FG_MESSAGE_INFO),
		isManaged(FG_FALSE) {
		info.code = FG_ERRNO_OK;
		warning.serious = FG_FALSE;
	}
	
	// Default destructor for message object
	~fgMessage() {
		data.clear();
	}
	
	fgMessage(fgMessageType _type, int _code) : 
		type(_type),
		isManaged(FG_FALSE) {
		info.code = FG_ERRNO_OK;
		warning.serious = FG_FALSE;
	}

	fgMessage(fgMessageType _type, int _code, fgBool _critical) : 
		type(_type),
		isManaged(FG_FALSE) {
		info.code = _code;
		warning.serious = _critical; // this will also set similar flag in error/debug - union
	}

	fgMessage(fgMessageType _type, const char *_data) : 
		type(_type),
		isManaged(FG_FALSE) {
		info.code = FG_ERRNO_OK;
		warning.serious = FG_FALSE;
		if(_data)
			data = _data;
	}

	fgMessage(fgMessageType _type, const char *_data, int _code) : 
		type(_type),
		isManaged(FG_FALSE) {
		info.code = _code;
		warning.serious = FG_FALSE;
		if(_data)
			data = _data;
	}

	fgMessage(fgMessageType _type, const char *_data, int _code, fgBool _critical) : 
		type(_type),
		isManaged(FG_FALSE) {
		info.code = _code;
		warning.serious = _critical;
		if(_data)
			data = _data;
	}

	fgMessage(const char *_data) : 
		type(FG_MESSAGE_INFO),
		isManaged(FG_FALSE) {
		info.code = FG_ERRNO_OK;
		warning.serious = FG_FALSE;
		if(_data)
			data = _data;
	}

	fgMessage(const char *_data, int _code) : 
		type(FG_MESSAGE_INFO),
		isManaged(FG_FALSE) {
		info.code = _code;
		warning.serious = FG_FALSE;
		if(_data)
			data = _data;
	}

	fgMessage(const char *_data, int _code, fgBool _critical) : 
		type(FG_MESSAGE_INFO),
		isManaged(FG_FALSE) {
		info.code = _code;
		warning.serious = _critical;
		if(_data)
			data = _data;
	}

	// Set the code for the message (returns pointer to this)
	fgMessage *setCode(int _code) {
		info.code = _code;
		return this;
	}

	// Get the message code (error code/etc)
	int code(void) const {
		return info.code;
	}

	// Set the message to be managed via message subsystem
	fgMessage *setManaged(void) {
		isManaged = FG_TRUE;
		return this;
	}
};

#endif /* _FG_MESSAGE_COMMON_H_ */
