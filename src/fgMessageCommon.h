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

/*
 * Structure for the info message
 */
struct fgInfo
{
	fgMessageType messageType;
	int infoCode;
};

/*
 * Structure for the warning message
 */
struct fgWarning
{
	fgMessageType messageType;
	int warningCode;
	fgBool isSerious;
};

/*
 * Structure for the error message
 */
struct fgError
{
	fgMessageType messageType;
	int errorCode;
	fgBool isCritical;
};

/*
 * Structure for the debug message
 */
struct fgDebug
{
	fgMessageType messageType;
	int debugCode;
	fgBool isCritical;
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
		fgMessageType messageType;
		int messageCode;
		fgInfo info;
		fgWarning warning;
		fgError error;
		fgDebug debug;
	};
	std::string messageData;
};

#endif /* _FG_MESSAGE_COMMON_H_ */
