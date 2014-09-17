/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_EVENT_HELPER_H_
#define _FG_EVENT_HELPER_H_

#include "fgVector.h"
#include "fgCallback.h"

#include "fgThrownEvent.h"
#include "fgTimeoutCallback.h"
#include "fgCyclicCallback.h"

#include <map>
#include <queue>

// #FIXME #TODO #P2 check if it is not deprecated (in Marmalade) to use the standard data types
//		 it can be necessary to use Marmalade specific wrappers
typedef std::map<int, fgVector<fgCallbackFunction *> > fgCallbackBinding;
typedef fgVector<fgCallbackFunction *> fgCallbacksPool;

typedef fgVector<fgCallbackFunction *>::iterator fgCallbacksPoolIt;
typedef fgVector<fgCallbackFunction *>::const_iterator fgCallbacksPoolConstIt;

typedef std::queue<fgThrownEvent> fgEventsQueue;
typedef fgVector<fgTimeoutCallback> fgTimeoutCallbacksPool;
typedef fgVector<fgCyclicCallback> fgCyclicCallbacksPool;

#endif
