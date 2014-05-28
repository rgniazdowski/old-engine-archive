/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _CYCLIC_CALLBACK_H
#define _CYCLIC_CALLBACK_H

#include <iostream>

#include "fgCallback.h"
#include "fgArgumentList.h"

struct fgCyclicCallback
{
	fgCallbackFunction *callback;
	int repeats; // -1 means infinite 
	int interval; // interval in miliseconds
	unsigned long int timestamp;
	fgArgumentList *argList;

	fgCyclicCallback() : callback(NULL), repeats(-1), interval(0), timestamp(0), argList(NULL)
	{
	}

	fgCyclicCallback(fgCallbackFunction *_callback, int _repeats, int _interval, fgArgumentList *_argList)
	{
		callback = _callback;
		repeats = _repeats;
		interval = _interval;
		timestamp = 0;
		argList = _argList;
	}

};

#endif
