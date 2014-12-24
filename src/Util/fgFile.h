/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_FILE
    #define FG_INC_FILE
    #define FG_INC_FILE_BLOCK

    #include "fgBuildConfig.h"
    #include "fgCommon.h"

    #include "fgTag.h"
    #include "fgFileBase.h"

namespace fg {
    namespace util {
        class File;
    };
};
//class fg::util::File;

    #define FG_TAG_FILE_NAME	"File"
    #define FG_TAG_FILE		FG_TAG_TYPE(fg::util::File)

FG_TAG_TEMPLATE_ID_AUTO(fg::util::File, FG_TAG_FILE_NAME);

namespace fg {
    namespace util {
        typedef FG_TAG_FILE FileTag;
    };
};
//typedef FG_TAG_FILE typename fg::util::FileTag;

    #include <cstdio>
    #include <string>

    #define FG_FILE_PATH_MAX	FG_PATH_MAX

/* Seek from beginning of file. */
    #define FG_FILE_SEEK_SET    SEEK_SET   
/* Seek from current position. */
    #define FG_FILE_SEEK_CUR    SEEK_CUR   
/* Seek from end of file. */
    #define FG_FILE_SEEK_END    SEEK_END   
/* End of file */
    #define FG_EOF				EOF
/* Max buffer for format string */
    #define FG_MAX_BUFFER		8192

// Standard input
    #define FG_IN				stdin
// Standard output
    #define FG_OUT				stdout
// Standard error output
    #define FG_ERR				stderr

namespace fg {
    namespace util {

        /*
         * Platform independent wrapper for basic file operations
         */
        class File : public fg::base::File {
        public:
            typedef FileTag tag_type;
            typedef typename fg::base::File::Mode Mode;

        protected:
            /// C standard file handle
            FILE *m_file;

        public:
            // Default constructor for File object
            File();

            // Constructor for File object with parameter (file path)
            File(const char *filePath);

            // Destructor, closes the file, frees up all buffers
            virtual ~File();

            // Get the C standard mode for fopen
            static const char *modeStr(Mode mode);

            using fg::base::File::open;
            
            // Open the file with already set options
            virtual fgBool open(void);
            // Open the file with specified mode
            virtual fgBool open(Mode mode);
            // Open the file (pointed to by path) with specified mode
            virtual fgBool open(const char *filePath, Mode mode);
            // Close the file
            virtual fgBool close(void);

            // Check if file is currently opened
            virtual fgBool isOpen(void) const;

            // Check if file exists
            static fgBool exists(const char *filePath);

            // Check if file exists
            static fgBool exists(const std::string &filePath);

            // Check if file exists
            virtual fgBool exists(void) {
                return File::exists(m_filePath.c_str());
            }

            using fg::base::File::load;
            
            // This will load the whole file into char *buffer
            virtual char *load(void);

            // This will load the whole file into char *buffer
            virtual char *load(const char *filePath);

            // Read from file
            virtual int read(void *buffer, unsigned int elemsize, unsigned int elemcount);
            // Read string from file
            virtual char *readString(char *buffer, unsigned int maxlen);
            // Write to file
            virtual int write(void *buffer, unsigned int elemsize, unsigned int elemcount);
            // Print to file
            virtual int print(const char *fmt, ...);
            // Put string to file :)
            virtual int puts(const char *str);

            // Check is it end of file
            virtual fgBool isEOF(void);
            // Flush file buffers
            virtual fgBool flushFile(void);

            // Get (read) single character from file
            virtual int getChar(void);
            // Put (write) single character to file
            virtual int putChar(char c);
            // Get the file size #FIXME (need to reopen in binary mode)
            virtual int getSize(void);
            // Get current position in file
            virtual long getPosition(void);
            // Set position in file
            virtual int setPosition(long offset, int whence);

            // Return the stdio FILE standard pointer
            FILE *getFilePtr(void) const {
                return m_file;
            }
        };
    };
};
    #undef FG_INC_FILE_BLOCK
#endif /* FG_INC_FILE */
