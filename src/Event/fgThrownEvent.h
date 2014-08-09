/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_THROWN_EVENT_H_
#define _FG_THROWN_EVENT_H_

#include <iostream>

#include "fgEventDefinitions.h"
#include "fgArgumentList.h"

struct fgThrownEvent
{
	fgEventType eventCode;
	fgArgumentList *argList;

	fgThrownEvent() : eventCode(FG_EVENT_INVALID), argList(NULL) {
	}

	fgThrownEvent(fgEventType _eventCode, fgArgumentList *_argList) {
		eventCode = _eventCode;
		argList = _argList;
	}
};

#endif /* _FG_THROWN_EVENT_H_ */
