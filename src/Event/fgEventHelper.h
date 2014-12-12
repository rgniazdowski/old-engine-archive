/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_EVENT_HELPER
    #define FG_INC_EVENT_HELPER

    #include "fgVector.h"
    #include "fgCallback.h"

    #include "fgThrownEvent.h"
    #include "fgTimeoutCallback.h"
    #include "fgCyclicCallback.h"

    #include <map>
    #include <queue>

///
typedef std::map<int, fgVector<fgFunctionCallback *> > fgCallbackBindingMap;
///
typedef fgCallbackBindingMap::iterator fgCallbackBindingMapItor;

///
typedef fgVector<fgFunctionCallback *> fgCallbacksVec;

///
typedef fgCallbacksVec::iterator fgCallbacksVecItor;
///
typedef fgCallbacksVec::const_iterator fgCallbacksVecConstItor;

///
typedef std::queue<fgThrownEvent> fgEventsQueue;

///
typedef fgVector<fgTimeoutCallback> fgTimeoutCallbacksVec;
///
typedef fgTimeoutCallbacksVec::iterator fgTimeoutCallbacksVecItor;

///
typedef fgVector<fgCyclicCallback> fgCyclicCallbacksVec;
///
typedef fgCyclicCallbacksVec::iterator fgCyclicCallbacksVecItor;

#endif /* FG_INC_EVENT_HELPER */
