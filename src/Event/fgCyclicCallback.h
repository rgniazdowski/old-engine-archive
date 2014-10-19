/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_CYCLIC_CALLBACK_H_
    #define _FG_CYCLIC_CALLBACK_H_

    #include "fgCallback.h"
    #include "fgArgumentList.h"

struct fgCyclicCallback {
    fgFunctionCallback *callback;
    int repeats; // -1 means infinite 
    int interval; // interval in miliseconds
    unsigned long int timestamp;
    fgArgumentList *argList;
    fgCyclicCallback() : callback(NULL), repeats(-1), interval(0), timestamp(0), argList(NULL) { }
    fgCyclicCallback(fgFunctionCallback *_callback, int _repeats, int _interval, fgArgumentList *_argList) {
        callback = _callback;
        repeats = _repeats;
        interval = _interval;
        timestamp = 0;
        argList = _argList;
    }
};

#endif /* _FG_CYCLIC_CALLBACK_H_ */
