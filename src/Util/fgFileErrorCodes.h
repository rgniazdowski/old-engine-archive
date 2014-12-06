/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_FILE_ERROR_CODES
    #define FG_INC_FILE_ERROR_CODES
    #define FG_INC_ERRNO_ERROR_CODES_BLOCK_OTHER__

    #ifdef FG_INC_ERRNO_ERROR_CODES_BLOCK__
        #error "FG_ERRNO_ERROR_CODES_BLOCK constant is defined. Do not include error codes definition header inside of fgErrno header."
    #endif

    #include "fgErrno.h"

    #define FG_ERRNO_FILE_BASE_CODE(_code)		(FG_ERRNO_BASE_CODE(800)+_code)

    #define FG_ERRNO_FILE_OK				FG_ERRNO_FILE_BASE_CODE(0)  /* No error */
    #define FG_ERRNO_FILE_ALREADY_OPEN			FG_ERRNO_FILE_BASE_CODE(1)  /* File is already open */
    #define FG_ERRNO_FILE_NO_PATH			FG_ERRNO_FILE_BASE_CODE(2)  /* No file path specified */
    #define FG_ERRNO_FILE_OPEN_FAILED			FG_ERRNO_FILE_BASE_CODE(3)  /* Failed to open file */
    #define FG_ERRNO_FILE_DOESNT_EXIST			FG_ERRNO_FILE_BASE_CODE(4)  /* File doesnt exist */
    #define FG_ERRNO_FILE_WRONG_MODE			FG_ERRNO_FILE_BASE_CODE(5)  /* Wrong file mode specified */
    #define FG_ERRNO_FILE_WRONG_PARAMETERS		FG_ERRNO_FILE_BASE_CODE(6)  /* Wrong parameters to function */
    #define FG_ERRNO_FILE_READ_COUNT			FG_ERRNO_FILE_BASE_CODE(7)  /* Did not read all the elements */
    #define FG_ERRNO_FILE_WRITE_COUNT			FG_ERRNO_FILE_BASE_CODE(8)  /* Did not write all the elements */
    #define FG_ERRNO_FILE_ERROR_STRING			FG_ERRNO_FILE_BASE_CODE(9)  /* Error reading string from file */
    #define FG_ERRNO_FILE_ERROR_FLUSH			FG_ERRNO_FILE_BASE_CODE(10) /* Error while flushing to file */
    #define FG_ERRNO_FILE_ERROR_SIZE			FG_ERRNO_FILE_BASE_CODE(11) /* Error reading file size */
    #define FG_ERRNO_FILE_ERROR_WRITE			FG_ERRNO_FILE_BASE_CODE(12) /* Error while writing to file */
    #define FG_ERRNO_FILE_ERROR_READ			FG_ERRNO_FILE_BASE_CODE(13) /* Error while reading from file */
    #define FG_ERRNO_FILE_NOT_OPENED			FG_ERRNO_FILE_BASE_CODE(14) /* File is not opened */
    #define FG_ERRNO_FILE_EOF				FG_ERRNO_FILE_BASE_CODE(15) /* End of file */
    #define FG_ERRNO_FILE_CLOSING			FG_ERRNO_FILE_BASE_CODE(16) /* Error while closing file */
    #define FG_ERRNO_FILE_ERROR_SEEK			FG_ERRNO_FILE_BASE_CODE(17) /* Error on file seek occured */
    #define FG_ERRNO_FILE_ERROR_TELL			FG_ERRNO_FILE_BASE_CODE(18) /* Error while getting file postion indicator */

    #define FG_ERRNO_FILE_LAST_CODE			FG_ERRNO_FILE_BASE_CODE(18)

    #define FG_ERRNO_FILE_OK_TEXT                       "No error"
    #define FG_ERRNO_FILE_ALREADY_OPEN_TEXT		"File is already open"
    #define FG_ERRNO_FILE_NO_PATH_TEXT			"No file path specified"
    #define FG_ERRNO_FILE_OPEN_FAILED_TEXT		"Failed to open file"
    #define FG_ERRNO_FILE_DOESNT_EXIST_TEXT		"File doesnt exist"
    #define FG_ERRNO_FILE_WRONG_MODE_TEXT		"Wrong file mode specified"
    #define FG_ERRNO_FILE_WRONG_PARAMETERS_TEXT         "Wrong parameters to function"
    #define FG_ERRNO_FILE_READ_COUNT_TEXT		"Did not read all the elements"
    #define FG_ERRNO_FILE_WRITE_COUNT_TEXT		"Did not write all the elements"
    #define FG_ERRNO_FILE_ERROR_STRING_TEXT		"Error reading string from file"
    #define FG_ERRNO_FILE_ERROR_FLUSH_TEXT		"Error while flushing to file"
    #define FG_ERRNO_FILE_ERROR_SIZE_TEXT		"Error reading file size"
    #define FG_ERRNO_FILE_ERROR_WRITE_TEXT		"Error while writing to file"
    #define FG_ERRNO_FILE_ERROR_READ_TEXT		"Error while reading from file"
    #define FG_ERRNO_FILE_NOT_OPENED_TEXT		"File is not opened"
    #define FG_ERRNO_FILE_EOF_TEXT                      "End of file"
    #define FG_ERRNO_FILE_CLOSING_TEXT			"Error while closing file"
    #define FG_ERRNO_FILE_ERROR_SEEK_TEXT		"Error on file seek occured"
    #define FG_ERRNO_FILE_ERROR_TELL_TEXT		"Error while getting file postion indicator"

namespace FG_ERRNO_FILE {
    const char * const __allErrVec[] = {
                                        FG_ERRNO_FILE_OK_TEXT,
                                        FG_ERRNO_FILE_ALREADY_OPEN_TEXT,
                                        FG_ERRNO_FILE_NO_PATH_TEXT,
                                        FG_ERRNO_FILE_OPEN_FAILED_TEXT,
                                        FG_ERRNO_FILE_DOESNT_EXIST_TEXT,
                                        FG_ERRNO_FILE_WRONG_MODE_TEXT,
                                        FG_ERRNO_FILE_WRONG_PARAMETERS_TEXT,
                                        FG_ERRNO_FILE_READ_COUNT_TEXT,
                                        FG_ERRNO_FILE_WRITE_COUNT_TEXT,
                                        FG_ERRNO_FILE_ERROR_STRING_TEXT,
                                        FG_ERRNO_FILE_ERROR_FLUSH_TEXT,
                                        FG_ERRNO_FILE_ERROR_SIZE_TEXT,
                                        FG_ERRNO_FILE_ERROR_WRITE_TEXT,
                                        FG_ERRNO_FILE_ERROR_READ_TEXT,
                                        FG_ERRNO_FILE_NOT_OPENED_TEXT,
                                        FG_ERRNO_FILE_EOF_TEXT,
                                        FG_ERRNO_FILE_CLOSING_TEXT,
                                        FG_ERRNO_FILE_ERROR_SEEK_TEXT,
                                        FG_ERRNO_FILE_ERROR_TELL_TEXT
    };
    inline void __registerAll(void) {
        for(int code = FG_ERRNO_FILE_BASE_CODE(0), i = 0; code <= FG_ERRNO_FILE_LAST_CODE; code++, i++) {
            FG_ERRNO_REGISTER(code, FG_ERRNO_FILE::__allErrVec[i]);
        }
    }
};

    #undef FG_INC_ERRNO_ERROR_CODES_BLOCK_OTHER__
#endif /* FG_INC_FILE_ERROR_CODES */
