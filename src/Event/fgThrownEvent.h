/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _THROWN_EVENT_H
#define _THROWN_EVENT_H

#include <iostream>

#include "fgEventHelper.h"
#include "fgArgumentList.h"

struct fgThrownEvent
{
	int eventCode;
	fgArgumentList *argList;

	fgThrownEvent() : eventCode(-1), argList(NULL) {
	}

	fgThrownEvent(int _eventCode, fgArgumentList *_argList) {
		eventCode = _eventCode;
		argList = _argList;
	}
};

#endif
