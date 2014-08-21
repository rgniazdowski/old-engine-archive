/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_MESSAGE_COMMON_H_
#define _FG_MESSAGE_COMMON_H_

// #FIXME
#ifndef FG_BOOL_DEFINED_
#define FG_BOOL_DEFINED_
typedef unsigned char fgBool;
#endif

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
		fgMessageType type;
		fgInfo info;
		fgWarning warning;
		fgError error;
		fgDebug debug;
	};
	std::string data;

	// Default constructor for message object
	fgMessage() : 
		type(FG_MESSAGE_INFO) {
		info.code = 0;
		warning.serious = FG_FALSE;
	}
	
	// Default destructor for message object
	~fgMessage() {
		data.clear();
	}
	
	fgMessage& operator= (const fgMessage &source)
	{
		printf(" --- --- fgMessage assignment called =!, this: %p, source: %p\n", this, &source);

		if(this == &source)
			return *this;

		type = source.type;
		info.code = source.info.code;
		warning.serious = source.warning.serious;
		data = source.data;

		return *this;
	}

	fgMessage(fgMessageType _type, int _code) : 
		type(_type) {
		info.code = 0;
		warning.serious = FG_FALSE;
	}

	fgMessage(fgMessageType _type, int _code, fgBool _critical) : 
		type(_type) {
		info.code = _code;
		warning.serious = _critical; // this will also set similar flag in error/debug - union
	}

	fgMessage(fgMessageType _type, const char *_data) : 
		type(_type) {
		info.code = 0;
		warning.serious = FG_FALSE;
		if(_data)
			data = _data;
	}

	fgMessage(fgMessageType _type, const char *_data, int _code) : 
		type(_type) {
		info.code = _code;
		warning.serious = FG_FALSE;
		if(_data)
			data = _data;
	}

	fgMessage(fgMessageType _type, const char *_data, int _code, fgBool _critical) : 
		type(_type) {
		info.code = _code;
		warning.serious = _critical;
		if(_data)
			data = _data;
	}

	fgMessage(const char *_data) : 
		type(FG_MESSAGE_INFO) {
		info.code = 0;
		warning.serious = FG_FALSE;
		if(_data)
			data = _data;
	}

	fgMessage(const char *_data, int _code) : 
		type(FG_MESSAGE_INFO) {
		info.code = _code;
		warning.serious = FG_FALSE;
		if(_data)
			data = _data;
	}

	fgMessage(const char *_data, int _code, fgBool _critical) : 
		type(FG_MESSAGE_INFO) {
		info.code = _code;
		warning.serious = _critical;
		if(_data)
			data = _data;
	}

	fgMessage *setCode(int _code) {
		info.code = _code;
		return this;
	}
};

#endif /* _FG_MESSAGE_COMMON_H_ */
