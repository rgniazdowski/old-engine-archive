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

#include "fgMessageCommon.h"

#ifndef NULL
    #ifndef __cplusplus
        #define NULL ((void *)0)
    #else
        #define NULL 0
    #endif
#endif

struct fgStatus
{
	bool isError;
	bool isSuccess;
	bool isFailure;
	fgMessage *message;

	fgStatus() : isError(false), isSuccess(true), isFailure(false)
	{
		message = NULL;
	}
};

#endif /* _FG_STATUS_H_ */