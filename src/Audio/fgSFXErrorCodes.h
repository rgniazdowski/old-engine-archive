/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_SFX_ERROR_CODES
    #define FG_INC_SFX_ERROR_CODES
    #define FG_INC_ERRNO_ERROR_CODES_BLOCK_OTHER__

    #ifdef FG_INC_ERRNO_ERROR_CODES_BLOCK__
        #error "FG_ERRNO_ERROR_CODES_BLOCK constant is defined. Do not include error codes definition header inside of fgErrno header."
    #endif

    #include "fgErrno.h"

    #define FG_ERRNO_SFX_BASE_CODE(_code)		(FG_ERRNO_BASE_CODE(100)+_code)

    #define FG_ERRNO_SFX_OK						FG_ERRNO_SFX_BASE_CODE(0)  /* No error */

    #define FG_ERRNO_SFX_NOT_SUPPORTED_CODEC	FG_ERRNO_SFX_BASE_CODE(1) /* Codec is not supported */

    #define FG_ERRNO_SFX_LAST_CODE				FG_ERRNO_SFX_BASE_CODE(1)


    #define FG_ERRNO_SFX_OK_TEXT					"No error"

    #define FG_ERRNO_SFX_NOT_SUPPORTED_CODEC_TEXT	"Codec is not supported"

namespace FG_ERRNO_SFX {
    const char * const __allErrVec[] = {
                                        FG_ERRNO_SFX_OK_TEXT,
                                        FG_ERRNO_SFX_NOT_SUPPORTED_CODEC_TEXT
    };
    inline void __registerAll(void) {
        for(int code = FG_ERRNO_SFX_BASE_CODE(0), i = 0; code <= FG_ERRNO_SFX_LAST_CODE; code++, i++) {
            FG_ERRNO_REGISTER(code, FG_ERRNO_SFX::__allErrVec[i]);
        }
    }
};

    #undef FG_INC_ERRNO_ERROR_CODES_BLOCK_OTHER__
#endif /* FG_INC_SFX_ERROR_CODES */
