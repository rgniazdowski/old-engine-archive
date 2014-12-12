/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_EXCEPTION
    #define FG_INC_EXCEPTION

    #include "fgBool.h"
    #include "fgErrno.h"
    #include "fgMessageCommon.h"
    #include <string>

/*
 *
 */
struct fgException : fgError {
    std::string data;
    fgException() {
        type = FG_MESSAGE_ERROR;
        critical = FG_TRUE;
    }
    fgException(const char *_data) {
        type = FG_MESSAGE_ERROR;
        critical = FG_TRUE;
        data = _data;
        code = FG_ERRNO_OK;
    }
    fgException(const char *_data, int _code) {
        type = FG_MESSAGE_ERROR;
        critical = FG_TRUE;
        data = _data;
        code = _code;
    }
    fgException(int _code) {
        type = FG_MESSAGE_ERROR;
        critical = FG_TRUE;
        code = _code;
        data = FG_ERRNO_STR(_code); // #FIXME
    }
    ~fgException() {
        data.clear();
    }
};

#endif /* FG_INC_EXCEPTION */
