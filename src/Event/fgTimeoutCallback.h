/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_TIMEOUT_CALLBACK
    #define FG_INC_TIMEOUT_CALLBACK
    #define FG_INC_TIMEOUT_CALLBACK_BLOCK

    #include "fgCallback.h"
    #include "fgArgumentList.h"

    #define FG_TIMEOUT_CALLBACK_DEFAULT_TIMEOUT 2500

namespace fg {
    namespace event {

        /**
         *
         */
        struct STimeoutCallback {
            ///
            CFunctionCallback *callback;
            ///
            CArgumentList *argList;
            ///
            int timeout;
            ///
            unsigned long int timeStamp;
            /**
             * 
             */
            STimeoutCallback() :
            callback(NULL),
            argList(NULL),
            timeout(FG_TIMEOUT_CALLBACK_DEFAULT_TIMEOUT),
            timeStamp(0) { }
            /**
             * 
             * @param _callback
             * @param _timeout
             * @param _argList
             */
            STimeoutCallback(CFunctionCallback *_callback,
                             int _timeout = FG_TIMEOUT_CALLBACK_DEFAULT_TIMEOUT,
                             CArgumentList *_argList = NULL) {
                callback = _callback;
                timeout = _timeout;
                timeStamp = 0;
                argList = _argList;
            }
        };
    };
};

    #undef FG_INC_TIMEOUT_CALLBACK_BLOCK
#endif /* FG_INC_TIMEOUT_CALLBACK */
