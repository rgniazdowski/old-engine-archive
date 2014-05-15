/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG__EVENT_HELPER_H
#define _FG__EVENT_HELPER_H

#include "fgCallback.h"

#include "fgThrownEvent.h"
#include "fgTimeoutCallback.h"
#include "fgCyclicCallback.h"

#include <map>
#include <queue>
#include <vector>

// #TODO check if it is not deprecated (in Marmalade) to use the standard data types
//		 it can be necessary to use Marmalade specific wrappers

typedef std::map<int, std::vector<fgCallbackFunction *> > fgCallbackBinding;
typedef std::vector<fgCallbackFunction *> fgCallbacksPool;

typedef std::queue<fgThrownEvent> fgEventsQueue;
typedef std::vector<fgTimeoutCallback> fgTimeoutCallbacksPool;
typedef std::vector<fgCyclicCallback> fgCyclicCallbacksPool;

#endif
