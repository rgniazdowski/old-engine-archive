/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_MEMORY_ERROR_CODES_H_
#define _FG_MEMORY_ERROR_CODES_H_
#define _FG_ERRNO_ERROR_CODES_BLOCK_OTHER__

#ifdef _FG_ERRNO_ERROR_CODES_BLOCK__
#error "FG_ERRNO_ERROR_CODES_BLOCK constant is defined. Do not include error codes definition header inside of fgErrno header."
#endif

#include "fgErrno.h"

#define FG_ERRNO_MEMORY_BASE_CODE(_code)		(FG_ERRNO_BASE_CODE(900)+_code)

#define FG_ERRNO_MEMORY_OK						FG_ERRNO_MEMORY_BASE_CODE(0)
#define FG_ERRNO_MEMORY_LAST_CODE				FG_ERRNO_MEMORY_BASE_CODE(0)

#define FG_ERRNO_MEMORY_OK_TEXT "No error"

namespace FG_ERRNO_MEMORY {
	const char * const __allErrVec[] = {
		FG_ERRNO_MEMORY_OK_TEXT
	};

	static void __registerAll(void) {		
		for(int code=FG_ERRNO_MEMORY_BASE_CODE(0), i=0; code<=FG_ERRNO_MEMORY_LAST_CODE; code++, i++) {
			FG_ERRNO_REGISTER(code, FG_ERRNO_MEMORY::__allErrVec[i]);
		}
	}
};


#undef _FG_ERRNO_ERROR_CODES_BLOCK_OTHER__
#endif /* _FG_MEMORY_ERROR_CODES_H_ */
