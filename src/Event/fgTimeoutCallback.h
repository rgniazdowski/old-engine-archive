/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_TIMEOUT_CALLBACK_H
#define _FG_TIMEOUT_CALLBACK_H

#include <iostream>

#include "fgCallback.h"
#include "fgArgumentList.h"

struct fgTimeoutCallback
{
	fgCallbackFunction *callback;
	fgArgumentList *argList;
	int timeout;
	unsigned long int timestamp;

	fgTimeoutCallback() : callback(NULL), timeout(0), timestamp(0), argList(NULL) 
	{
	}

	fgTimeoutCallback(fgCallbackFunction *_callback, int _timeout, fgArgumentList *_argList)
	{
		callback = _callback;
		timeout = _timeout;
		timestamp = 0;
		argList = _argList;
	}

};

#endif
