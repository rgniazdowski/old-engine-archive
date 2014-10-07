/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_TIMEOUT_CALLBACK_H_
#define _FG_TIMEOUT_CALLBACK_H_

#include "fgCallback.h"
#include "fgArgumentList.h"

/*
 *
 */
struct fgTimeoutCallback
{
	fgFunctionCallback	*callback;
	fgArgumentList		*argList;
	int					timeout;
	unsigned long int	timestamp;

	fgTimeoutCallback() : callback(NULL), argList(NULL), timeout(0), timestamp(0)
	{
	}

	fgTimeoutCallback(fgFunctionCallback *_callback, int _timeout, fgArgumentList *_argList)
	{
		callback = _callback;
		timeout = _timeout;
		timestamp = 0;
		argList = _argList;
	}
};

#endif /* _FG_TIMEOUT_CALLBACK_H_ */
