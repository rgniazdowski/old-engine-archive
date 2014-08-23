/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_EXCEPTION_H_
#define _FG_EXCEPTION_H_

#include "fgBool.h"
#include "fgErrno.h"
#include "fgMessageCommon.h"
#include <string>

/*
 *
 */
struct fgException : fgError
{
	std::string data;

	fgException() {
		critical = FG_TRUE;
	}

	fgException(const char *_data) {
		critical = FG_TRUE;
		data = _data;
		code = FG_ERRNO_OK;
	}

	fgException(const char *_data, int _code) {
		critical = FG_TRUE;
		data = _data;
		code = _code;
	}

	fgException(int _code) {
		critical = FG_TRUE;
		code = _code;
		data = FG_ERRNO_STR(_code); // #FIXME
	}
};

#endif /* _FG_EXCEPTION_H_ */
