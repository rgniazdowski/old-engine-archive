/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgFileBase.h
 * Author: vigilant
 *
 * Created on December 24, 2014, 1:31 AM
 */

#ifndef FG_INC_FILE_BASE
    #define FG_INC_FILE_BASE
    #define FG_INC_FILE_BASE_BLOCK

    #ifdef	__cplusplus
extern "C" {
    #endif
    #ifdef	__cplusplus
}
    #endif

    #include "fgTypes.h"

namespace fg {
    namespace util {
        namespace base {

            /**
             *
             */
            class CFile {
            public:

                /**
                 * Enumeration for standard file manipulation modes
                 */
                enum class Mode : unsigned int {
                    /// No mode specified (invalid).
                    NONE = 0,
                    // Open file for input operations. The file must exist.
                    READ = 1 << 0,
                    // Create an empty file for output operations.
                    WRITE = 1 << 1,
                    // Open file for output at the end of a file. The file is created if it does not exist.
                    APPEND = 1 << 2,
                    // Additional update mode (both input/output).
                    UPDATE = 1 << 3,
                    // Open file as a binary file.
                    BINARY = 1 << 4,
                    // Open a file for update (both for input and output). The file must exist.
                    READ_UPDATE = Mode::READ + Mode::UPDATE,
                    // Create an empty file and open it for update (both for input and output). 
                    // If a file with the  same name already exists its  contents are discarded 
                    // and the file is treated as a new empty file.
                    WRITE_UPDATE = Mode::WRITE + Mode::UPDATE,
                    // Open a file for update (both for input and  output) with all output operations
                    // writing data at the end of the file. Repositioning operations (fseek, fsetpos,
                    // rewind)  affects the  next input  operations,  but  output operations move the
                    // position back to the end of file.  The file is  created if  it does not exist.
                    APPEND_UPDATE = Mode::APPEND + Mode::UPDATE

                };

            protected:
                ///
                std::string m_filePath;
                ///
                Mode m_modeFlags;

            public:
                /**
                 * 
                 */
                CFile() : m_filePath(), m_modeFlags(Mode::READ) { }
                /**
                 * 
                 */
                virtual ~CFile() { }

            public:
                /**
                 * Set the file path
                 * @param filePath
                 */
                virtual void setPath(const char *filePath) {
                    if(filePath)
                        m_filePath = filePath;
                }
                /**
                 * Set the file path
                 * @param filePath
                 */
                virtual void setPath(const std::string & filePath) {
                    m_filePath = filePath;
                }
                /**
                 * Return the file path (C string)
                 * @return 
                 */
                virtual const char *getPath(void) const {
                    return m_filePath.c_str();
                }
                /**
                 * Set file open mode
                 * @param mode
                 */
                virtual void setMode(Mode mode) {
                    m_modeFlags = mode;
                }

                /**
                 * Open the file with already set options
                 * @return 
                 */
                virtual fgBool open(void) = 0;
                /**
                 * Open the file with specified mode
                 * @param mode
                 * @return 
                 */
                virtual fgBool open(Mode mode) = 0;
                /**
                 * Open the file (pointed to by path) with specified mode
                 * @param filePath
                 * @param mode
                 * @return 
                 */
                virtual fgBool open(const char *filePath, Mode mode) = 0;

                /**
                 * Close the file
                 * @return 
                 */
                virtual fgBool close(void) = 0;

                /**
                 * Check if file is currently opened
                 * @return 
                 */
                virtual fgBool isOpen(void) const = 0;

                /**
                 * Check if file exists
                 * @return 
                 */
                virtual fgBool exists(void) = 0;

                /**
                 * This will load the whole file into char *buffer
                 * @return Newly allocated string representing the contents of the file
                 *         There is a limit for how big this buffer can be. If it's
                 *         exceeded a NULL pointer will be returned. The returned
                 *         string buffer will be null-terminated ('\0' will be appended)
                 */
                virtual char *load(void) = 0;
                /**
                 * This will load the whole file into char *buffer
                 * @param filePath
                 * @return Newly allocated string representing the contents of the file
                 *         There is a limit for how big this buffer can be. If it's
                 *         exceeded a NULL pointer will be returned. The returned
                 *         string buffer will be null-terminated ('\0' will be appended)
                 */
                virtual char *load(const char *filePath) = 0;

                /**
                 * Read from file
                 * @param buffer
                 * @param elemsize
                 * @param elemcount
                 * @return 
                 */
                virtual int read(void *buffer, unsigned int elemsize, unsigned int elemcount) = 0;
                /**
                 * Read string from the file
                 * @param buffer
                 * @param maxlen
                 * @return 
                 */
                virtual char *readString(char *buffer, unsigned int maxlen) = 0;
                /**
                 * Write to the file
                 * @param buffer
                 * @param elemsize
                 * @param elemcount
                 * @return 
                 */
                virtual int write(void *buffer, unsigned int elemsize, unsigned int elemcount) = 0;
                /**
                 * Print to the file
                 * @param fmt
                 * @return 
                 */
                virtual int print(const char *fmt, ...) = 0;
                /**
                 * Put given string into the file
                 * @param str
                 * @return 
                 */
                virtual int puts(const char *str) = 0;

                /**
                 * Check is it end of file
                 * @return 
                 */
                virtual fgBool isEOF(void) = 0;
                /**
                 * Flush file buffers
                 * @return 
                 */
                virtual fgBool flush(void) = 0;

                /**
                 *  Get (read) single character from file
                 * @return 
                 */
                virtual int getChar(void) = 0;
                /**
                 * Put (write) single character to file
                 * @param c
                 * @return 
                 */
                virtual int putChar(char c) = 0;
                /**
                 * Get the file size (in bytes)
                 * @return 
                 */
                virtual int getSize(void) = 0;
                /**
                 * Get the current position in the file
                 * @return 
                 */
                virtual long getPosition(void) = 0;

                /**
                 * Sets the position in the currently open/selected file
                 * @param offset
                 * @param whence
                 * @return 
                 */
                virtual int setPosition(long offset, int whence) = 0;

            };

            // Overload standard bitwise operator for enum type
            FG_ENUM_FLAGS(CFile::Mode);
        };
    };
};

    #undef FG_INC_FILE_BASE_BLOCK
#endif	/* FG_INC_FILE_BASE */

