/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_CYCLIC_CALLBACK
    #define FG_INC_CYCLIC_CALLBACK
    #define FG_INC_CYCLIC_CALLBACK_BLOCK


    #include "fgCallback.h"
    #include "fgArgumentList.h"

    #define FG_CYCLIC_CALLBACK_DEFAULT_REPEAT   10
    #define FG_CYCLIC_CALLBACK_INFINITE_REPEAT  -1
    #define FG_CYCLIC_CALLBACK_DEFAULT_INTERVAL 2500

namespace fg {
    namespace event {

        /**
         * 
         */
        struct SCyclicCallback {
            ///
            CFunctionCallback *callback;
            /// -1 means infinite 
            int repeats;
            /// Interval in milliseconds
            int interval;
            ///
            unsigned long int timeStamp;
            ///
            CArgumentList *argList;
            /**
             * 
             */
            SCyclicCallback() :
            callback(NULL),
            repeats(-1),
            interval(0),
            timeStamp(0),
            argList(NULL) { }
            /**
             * 
             * @param _callback
             * @param _repeats
             * @param _interval
             * @param _argList
             */
            SCyclicCallback(CFunctionCallback *_callback,
                            int _repeats = FG_CYCLIC_CALLBACK_DEFAULT_REPEAT,
                            int _interval = FG_CYCLIC_CALLBACK_DEFAULT_INTERVAL,
                            CArgumentList *_argList = NULL) {
                if(!_callback) {
                    callback = NULL;
                    repeats = 0;
                    argList = 0;
                    return;
                }
                callback = _callback;
                repeats = _repeats;
                interval = _interval;
                timeStamp = 0;
                argList = _argList;
            }
        };
    };
};

    #undef FG_INC_CYCLIC_CALLBACK_BLOCK
#endif /* FG_INC_CYCLIC_CALLBACK */
