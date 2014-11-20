/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_ERROR_CODES
    #define FG_INC_GFX_ERROR_CODES
    #define FG_INC_ERRNO_ERROR_CODES_BLOCK_OTHER__

    #ifdef FG_INC_ERRNO_ERROR_CODES_BLOCK__
        #error "FG_ERRNO_ERROR_CODES_BLOCK constant is defined. Do not include error codes definition header inside of fgErrno header."
    #endif

    #include "fgErrno.h"

    #define FG_ERRNO_GFX_BASE_CODE(_code)		(FG_ERRNO_BASE_CODE(300)+_code)

    #define FG_ERRNO_GFX_OK						FG_ERRNO_GFX_BASE_CODE(0)

    #define FG_ERRNO_GFX_SHADER_WRONG_PARAM		FG_ERRNO_GFX_BASE_CODE(1)
    #define FG_ERRNO_GFX_SHADER_NO_MAIN_SECTION FG_ERRNO_GFX_BASE_CODE(2)
    #define FG_ERRNO_GFX_SHADER_NO_FILE_SECTION	FG_ERRNO_GFX_BASE_CODE(3)
    #define FG_ERRNO_GFX_SHADER_NO_CONFIG_SECTION	FG_ERRNO_GFX_BASE_CODE(4)
    #define FG_ERRNO_GFX_SHADER_NO_ATTRIBUTES	FG_ERRNO_GFX_BASE_CODE(5)
    #define FG_ERRNO_GFX_SHADER_WRONG_ATTRIBUTE	FG_ERRNO_GFX_BASE_CODE(6)
    #define FG_ERRNO_GFX_SHADER_WRONG_UNIFORM	FG_ERRNO_GFX_BASE_CODE(7)
    #define FG_ERRNO_GFX_SHADER_WRONG_TYPE		FG_ERRNO_GFX_BASE_CODE(8)
    #define FG_ERRNO_GFX_SHADER_INVALID_SLVER			FG_ERRNO_GFX_BASE_CODE(9)
    #define FG_ERRNO_GFX_SHADER_NOT_SUPPORTED_SLVER		FG_ERRNO_GFX_BASE_CODE(10)	/* Current shading language version is not supported by this shader */
    #define FG_ERRNO_GFX_SHADER_FAIL_CFG_LOAD	FG_ERRNO_GFX_BASE_CODE(11)
    #define FG_ERRNO_GFX_SHADER_WRONG_CFG_TYPE	FG_ERRNO_GFX_BASE_CODE(12)
    #define FG_ERRNO_GFX_SHADER_NO_FILEQ_PARAMS	FG_ERRNO_GFX_BASE_CODE(13) /* Did not find paramaters for file/quality binding */
    #define FG_ERRNO_GFX_SHADER_NO_PROG_NAME	FG_ERRNO_GFX_BASE_CODE(14)
    #define FG_ERRNO_GFX_SHADER_NO_TYPE			FG_ERRNO_GFX_BASE_CODE(15) /* No shader type specified */

    #define FG_ERRNO_GFX_LAST_CODE				FG_ERRNO_GFX_BASE_CODE(15)

    #define FG_ERRNO_GFX_OK_TEXT							"Success"
    #define FG_ERRNO_GFX_SHADER_WRONG_PARAM_TEXT			"Wrong config parameter"
    #define FG_ERRNO_GFX_SHADER_NO_MAIN_SECTION_TEXT		"No main shader config section found"
    #define FG_ERRNO_GFX_SHADER_NO_FILE_SECTION_TEXT		"No file section found"
    #define FG_ERRNO_GFX_SHADER_NO_CONFIG_SECTION_TEXT		"No language version config section found"
    #define FG_ERRNO_GFX_SHADER_NO_ATTRIBUTES_TEXT			"No attributes found"
    #define FG_ERRNO_GFX_SHADER_WRONG_ATTRIBUTE_TEXT		"Wrong attribute - this attribute definition section is malformed"
    #define FG_ERRNO_GFX_SHADER_WRONG_UNIFORM_TEXT			"Wrong uniform - this uniform definition section is malformed"
    #define FG_ERRNO_GFX_SHADER_WRONG_TYPE_TEXT				"Wrong shader type"
    #define FG_ERRNO_GFX_SHADER_INVALID_SLVER_TEXT			"Invalid Shading Language version"
    #define FG_ERRNO_GFX_SHADER_NOT_SUPPORTED_SLVER_TEXT	"Not supported Shading Language version"
    #define FG_ERRNO_GFX_SHADER_FAIL_CFG_LOAD_TEXT			"Failed to load shader config"
    #define FG_ERRNO_GFX_SHADER_WRONG_CFG_TYPE_TEXT			"Wrong shader config type"
    #define FG_ERRNO_GFX_SHADER_NO_FILEQ_PARAMS_TEXT		"Did not find parameters for file/quality binding"
    #define FG_ERRNO_GFX_SHADER_NO_PROG_NAME_TEXT			"No shader program name specified"
    #define FG_ERRNO_GFX_SHADER_NO_TYPE_TEXT				"No shader type specified"

namespace FG_ERRNO_GFX {
    const char * const __allErrVec[] = {
                                        FG_ERRNO_GFX_OK_TEXT,
                                        FG_ERRNO_GFX_SHADER_WRONG_PARAM_TEXT,
                                        FG_ERRNO_GFX_SHADER_NO_MAIN_SECTION_TEXT,
                                        FG_ERRNO_GFX_SHADER_NO_FILE_SECTION_TEXT,
                                        FG_ERRNO_GFX_SHADER_NO_CONFIG_SECTION_TEXT,
                                        FG_ERRNO_GFX_SHADER_NO_ATTRIBUTES_TEXT,
                                        FG_ERRNO_GFX_SHADER_WRONG_ATTRIBUTE_TEXT,
                                        FG_ERRNO_GFX_SHADER_WRONG_UNIFORM_TEXT,
                                        FG_ERRNO_GFX_SHADER_WRONG_TYPE_TEXT,
                                        FG_ERRNO_GFX_SHADER_INVALID_SLVER_TEXT,
                                        FG_ERRNO_GFX_SHADER_NOT_SUPPORTED_SLVER_TEXT,
                                        FG_ERRNO_GFX_SHADER_FAIL_CFG_LOAD_TEXT,
                                        FG_ERRNO_GFX_SHADER_WRONG_CFG_TYPE_TEXT,
                                        FG_ERRNO_GFX_SHADER_NO_FILEQ_PARAMS_TEXT,
                                        FG_ERRNO_GFX_SHADER_NO_PROG_NAME_TEXT,
                                        FG_ERRNO_GFX_SHADER_NO_TYPE_TEXT
    };
    inline void __registerAll(void) {
        for(int code = FG_ERRNO_GFX_BASE_CODE(0), i = 0; code <= FG_ERRNO_GFX_LAST_CODE; code++, i++) {
            FG_ERRNO_REGISTER(code, FG_ERRNO_GFX::__allErrVec[i]);
        }
    }
};

    #undef FG_INC_ERRNO_ERROR_CODES_BLOCK_OTHER__
#endif /* FG_INC_GFX_ERROR_CODES */
