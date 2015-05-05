/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_EXCEPTION
    #define FG_INC_EXCEPTION
    #define FG_INC_EXCEPTION_BLOCK

    #include "fgBool.h"
    #include "fgErrno.h"
    #include "fgMessageCommon.h"
    #include <string>

namespace fg {
    namespace msg {

        /**
         *
         */
        struct SException : SError {
            ///
            std::string data;
            /**
             * 
             */
            SException() {
                type = MSG_ERROR;
                critical = FG_TRUE;
            }
            /**
             * 
             * @param _data
             */
            SException(const char *_data) {
                type = MSG_ERROR;
                critical = FG_TRUE;
                data = _data;
                code = FG_ERRNO_OK;
            }
            /**
             * 
             * @param _data
             * @param _code
             */
            SException(const char *_data, int _code) {
                type = MSG_ERROR;
                critical = FG_TRUE;
                data = _data;
                code = _code;
            }
            /**
             * 
             * @param _code
             */
            SException(int _code) {
                type = MSG_ERROR;
                critical = FG_TRUE;
                code = _code;
                data = FG_ERRNO_STR(_code); // #FIXME
            }
            /**
             * 
             */
            virtual ~SException() {
                data.clear();
            }
        };
    };
};

    #undef FG_INC_EXCEPTION_BLOCK
#endif /* FG_INC_EXCEPTION */
