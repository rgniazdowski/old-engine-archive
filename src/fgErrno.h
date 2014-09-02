/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_ERRNO_H_
#define _FG_ERRNO_H_
#define _FG_ERRNO_ERROR_CODES_BLOCK__


#include <cerrno>
#include <map>
#include <string>

#define FG_ERRNO_INVALID_CODE_TEXT		"invalid error code"

#define FG_ERRNO	errno

#define FG_ERRNO_BASE_CODE_				20000
#define FG_ERRNO_BASE_CODE(code)		(FG_ERRNO_BASE_CODE_+code)

#define FG_ERRNO_WARNING_BASE_CODE_		63600
#define FG_ERRNO_DEBUG_BASE_CODE_		616000
#define FG_ERRNO_INFO_BASE_CODE_		100000

#define FG_ERRNO_WARNING_BASE_CODE(code)	(FG_ERRNO_WARNING_BASE_CODE_+code)
#define FG_ERRNO_DEBUG_BASE_CODE(code)		(FG_ERRNO_DEBUG_BASE_CODE_+code)
#define FG_ERRNO_INFO_BASE_CODE(code)		(FG_ERRNO_INFO_BASE_CODE_+code)

/**********************************************************
 * FlexiGame specific error codes
 */

#define FG_ERRNO_OK				FG_ERRNO_BASE_CODE(0)	/* No error */
#define FG_ERRNO_NOCFG			FG_ERRNO_BASE_CODE(1)	/* No config file found */
#define FG_ERRNO_EXCEPTION		FG_ERRNO_BASE_CODE(2)   /* Exception */
#define FG_ERRNO_NOT_FOUND		FG_ERRNO_BASE_CODE(3)	/* Element was not found */
#define FG_ERRNO_WRONG_PARAM	FG_ERRNO_BASE_CODE(4)	/* Wrong parameter */

#define FG_ERRNO_LAST_CODE		FG_ERRNO_BASE_CODE(4)	/* Last code */

#define FG_ERRNO_OK_TEXT			"No error"
#define FG_ERRNO_NOCFG_TEXT			"No config file found"
#define FG_ERRNO_EXCEPTION_TEXT		"Exception"
#define FG_ERRNO_NOT_FOUND_TEXT		"Element was not found"
#define FG_ERRNO_WRONG_PARAM_TEXT	"Wrong parameter"

/*
 *
 **********************************************************/

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
	static void setLocalErrno(int _code);
	// 
	static void reset(void);
	//
	static int code(void);
	//
	static int localCode(void);
	//
	static void clearError(void);

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

#define FG_ERRNO_SET(code)				fgErrno::setErrno(code)
#define FG_ERRNO_REGISTER(code, str)	fgErrno::registerStrError(code, str)

#define FG_ERRNO_CLEAR()				do { fgErrno::clearError(); } while(0)

namespace FG_ERRNO_MAIN {
	const char * const __allErrVec[] = {
		FG_ERRNO_OK_TEXT,
		FG_ERRNO_NOCFG_TEXT,
		FG_ERRNO_EXCEPTION_TEXT,
		FG_ERRNO_NOT_FOUND_TEXT,
		FG_ERRNO_WRONG_PARAM_TEXT
	};

	static void __registerAll(void) {		
		for(int code=FG_ERRNO_BASE_CODE(0), i=0; code<=FG_ERRNO_LAST_CODE; code++, i++) {
			FG_ERRNO_REGISTER(code, FG_ERRNO_MAIN::__allErrVec[i]);
		}
	}
};

#undef _FG_ERRNO_ERROR_CODES_BLOCK__
#endif /* _FG_ERRNO_H_ */
