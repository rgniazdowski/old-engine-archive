/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_EVENT_HELPER_H_
#define _FG_EVENT_HELPER_H_

#include "../fgCommon.h"
#include "fgCallback.h"

#include "fgThrownEvent.h"
#include "fgTimeoutCallback.h"
#include "fgCyclicCallback.h"

#include <map>
#include <queue>

// #FIXME #TODO #P2 check if it is not deprecated (in Marmalade) to use the standard data types
//		 it can be necessary to use Marmalade specific wrappers
typedef std::map<int, fgArrayVector<fgCallbackFunction *> > fgCallbackBinding;
typedef fgArrayVector<fgCallbackFunction *> fgCallbacksPool;

typedef fgArrayVector<fgCallbackFunction *>::iterator fgCallbacksPoolIt;
typedef fgArrayVector<fgCallbackFunction *>::const_iterator fgCallbacksPoolConstIt;

typedef std::queue<fgThrownEvent> fgEventsQueue;
typedef fgArrayVector<fgTimeoutCallback> fgTimeoutCallbacksPool;
typedef fgArrayVector<fgCyclicCallback> fgCyclicCallbacksPool;

#endif
