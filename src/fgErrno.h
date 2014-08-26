/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_ERRNO_H_
#define _FG_ERRNO_H_
#define _FG_ERRNO_ERROR_CODES_BLOCK__


#include <cerrno>
#include <map>
#include <string>

#define FG_ERRNO_CLEAR()				do { errno = 0; } while(0)

#define FG_ERRNO_INVALID_CODE_TEXT		"invalid error code"

#define FG_ERRNO_BASE_CODE_				20000
#define FG_ERRNO_BASE_CODE(code)		(FG_ERRNO_BASE_CODE_+code)

#define FG_ERRNO_WARNING_BASE_CODE_		63600
#define FG_ERRNO_DEBUG_BASE_CODE_		616000
#define FG_ERRNO_INFO_BASE_CODE_		100000

/**********************************************************
 * FlexiGame specific error codes
 */

#define FG_ERRNO_OK			FG_ERRNO_BASE_CODE(0)	/* No error */
#define FG_ERRNO_NOCFG		FG_ERRNO_BASE_CODE(1)	/* No config file found */

/*
 * 
 */
class fgErrno {

public:
	// 
	static const char *strError(int _code);
	// 
	static void registerStrError(int _code, const char *_str);
	// 
	static void registerStrError(int _code, std::string& _str);
	// 
	static void setErrno(int _code);
	// 
	static void reset(void);

protected:
	// 
	static const char *_getStrError(int _fg_code);

private:
	typedef std::map<int, std::string> strErrMap;
	typedef std::pair<int, std::string> strErrMapPair;
	typedef strErrMap::iterator strErrMapItor;

	// 
	static strErrMap s_errorMap;
	// 
	static int s_errno;
};

#define FG_ERRNO_STR(code)	fgErrno::strError(code)
#define FG_ERRNO			fgErrno

#define FG_ERRNO_SET(code)				fgErrno::setErrno(code)
#define FG_ERRNO_REGISTER(code, str)	fgErrno::registerStrError(code, str)

#undef _FG_ERRNO_ERROR_CODES_BLOCK__

#endif /* _FG_ERRNO_H_ */
