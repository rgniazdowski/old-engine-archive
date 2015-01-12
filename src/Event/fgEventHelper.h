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
    #define FG_INC_EVENT_HELPER_BLOCK

    #include "fgVector.h"
    #include "fgCallback.h"

    #include "fgThrownEvent.h"
    #include "fgTimeoutCallback.h"
    #include "fgCyclicCallback.h"

    #include <map>
    #include <queue>

namespace fg {
    namespace event {

        ///
        typedef std::map<int, fg::CVector<fg::event::CFunctionCallback *> > CallbackBindingMap;
        ///
        typedef CallbackBindingMap::iterator CallbackBindingMapItor;

        ///
        typedef fg::CVector<fg::event::CFunctionCallback *> CallbacksVec;

        ///
        typedef CallbacksVec::iterator CallbacksVecItor;
        ///
        typedef CallbacksVec::const_iterator CallbacksVecConstItor;

        ///
        typedef std::queue<fg::event::SThrownEvent> EventsQueue;

        ///
        typedef fg::CVector<fg::event::STimeoutCallback> TimeoutCallbacksVec;
        ///
        typedef TimeoutCallbacksVec::iterator TimeoutCallbacksVecItor;

        ///
        typedef fg::CVector<fg::event::SCyclicCallback> CyclicCallbacksVec;
        ///
        typedef CyclicCallbacksVec::iterator CyclicCallbacksVecItor;
    };
};

    #undef FG_INC_EVENT_HELPER_BLOCK
#endif /* FG_INC_EVENT_HELPER */
