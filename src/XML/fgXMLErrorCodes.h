/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_XML_ERROR_CODES_H_
    #define _FG_XML_ERROR_CODES_H_
    #define _FG_ERRNO_ERROR_CODES_BLOCK_OTHER__

    #ifdef _FG_ERRNO_ERROR_CODES_BLOCK__
        #error "FG_ERRNO_ERROR_CODES_BLOCK constant is defined. Do not include error codes definition header inside of fgErrno header."
    #endif

    #include "fgErrno.h"

    #define FG_ERRNO_XML_BASE_CODE(_code)		(FG_ERRNO_BASE_CODE(1000)+_code)

// TINYXML / XML PARSING - universal for any xml reader/parser used
    #define FG_ERRNO_XML_OK						FG_ERRNO_XML_BASE_CODE(0) /* No error */
    #define FG_ERRNO_XML_ERROR					FG_ERRNO_XML_BASE_CODE(1) /* Error */
    #define FG_ERRNO_XML_IOFILE					FG_ERRNO_XML_BASE_CODE(2) /* Failed to open file */
    #define FG_ERRNO_XML_PARSE					FG_ERRNO_XML_BASE_CODE(3) /* Error parsing file */
    #define FG_ERRNO_XML_LOAD					FG_ERRNO_XML_BASE_CODE(4) /* Failed to load file data */

    #define FG_ERRNO_XML_NO_CONTENT_HANDLER		FG_ERRNO_XML_BASE_CODE(5) /* No content handler set */
    #define FG_ERRNO_XML_NOT_LOADED				FG_ERRNO_XML_BASE_CODE(6) /* File not loaded */
    #define FG_ERRNO_XML_PARSE_DEEP				FG_ERRNO_XML_BASE_CODE(7) /* Error occured while parsing with content handler */

    #define FG_ERRNO_XML_LAST_CODE				FG_ERRNO_XML_BASE_CODE(7)

    #define FG_ERRNO_XML_OK_TEXT					"No error"
    #define FG_ERRNO_XML_ERROR_TEXT					"Error"
    #define FG_ERRNO_XML_IOFILE_TEXT				"Failed to open file"
    #define FG_ERRNO_XML_PARSE_TEXT					"Error parsing file"
    #define FG_ERRNO_XML_LOAD_TEXT					"Failed to load file data"

    #define FG_ERRNO_XML_NO_CONTENT_HANDLER_TEXT	"No content handler set"
    #define FG_ERRNO_XML_NOT_LOADED_TEXT			"File not loaded"
    #define FG_ERRNO_XML_PARSE_DEEP_TEXT			"Error occured while parsing with content handler"

namespace FG_ERRNO_XML {
    const char * const __allErrVec[] = {
                                        FG_ERRNO_XML_OK_TEXT,
                                        FG_ERRNO_XML_ERROR_TEXT,
                                        FG_ERRNO_XML_IOFILE_TEXT,
                                        FG_ERRNO_XML_PARSE_TEXT,
                                        FG_ERRNO_XML_LOAD_TEXT,
                                        FG_ERRNO_XML_NO_CONTENT_HANDLER_TEXT,
                                        FG_ERRNO_XML_NOT_LOADED_TEXT,
                                        FG_ERRNO_XML_PARSE_DEEP_TEXT
    };
    inline void __registerAll(void) {
        for(int code = FG_ERRNO_XML_BASE_CODE(0), i = 0; code <= FG_ERRNO_XML_LAST_CODE; code++, i++) {
            FG_ERRNO_REGISTER(code, FG_ERRNO_XML::__allErrVec[i]);
        }
    }
};

    #undef _FG_ERRNO_ERROR_CODES_BLOCK_OTHER__
#endif /* _FG_XML_ERROR_CODES_H_ */
