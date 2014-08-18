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

/*
 *
 */
struct fgStatus
{
	fgBool isError;
	fgBool isSuccess;
	fgBool isFailure;
	fgMessage *message; // #FIXME

	fgStatus() : isError(FG_FALSE), isSuccess(FG_TRUE), isFailure(FG_FALSE)
	{
		message = NULL;
	}
};

#endif /* _FG_STATUS_H_ */
