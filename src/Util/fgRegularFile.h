/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_REGULAR_FILE
    #define FG_INC_REGULAR_FILE
    #define FG_INC_REGULAR_FILE_BLOCK

    #include "fgBuildConfig.h"
    #include "fgCommon.h"

    #include "fgTag.h"
    #include "fgFileBase.h"

namespace fg {
    namespace util {
        class RegularFile;
    };
};
//class fg::util::File;

    #define FG_TAG_FILE_NAME	"RegularFile"
    #define FG_TAG_FILE		FG_TAG_TYPE(fg::util::RegularFile)

FG_TAG_TEMPLATE_ID_AUTO(fg::util::RegularFile, FG_TAG_FILE_NAME);

namespace fg {
    namespace util {
        typedef FG_TAG_FILE RegularFileTag;
    };
};
//typedef FG_TAG_FILE typename fg::util::FileTag;

    #include <cstdio>
    #include <string>

    #define FG_FILE_PATH_MAX    FG_PATH_MAX

/* Seek from beginning of file. */
    #define FG_FILE_SEEK_SET    SEEK_SET   
/* Seek from current position. */
    #define FG_FILE_SEEK_CUR    SEEK_CUR   
/* Seek from end of file. */
    #define FG_FILE_SEEK_END    SEEK_END   
/* End of file */
    #define FG_EOF              EOF
/* Max buffer for format string */
    #define FG_MAX_BUFFER       8192

/* Standard input */
    #define FG_IN               stdin
/* Standard output */
    #define FG_OUT              stdout
/* Standard error output */
    #define FG_ERR              stderr

namespace fg {
    namespace util {

        /*
         * Platform independent wrapper for basic file operations
         */
        class RegularFile : public fg::util::base::File {
        public:
            typedef fg::util::base::File base_type;
            typedef RegularFileTag tag_type;
            typedef typename fg::util::base::File::Mode Mode;

        protected:
            /// C standard file handle
            FILE *m_file;

        public:
            /**
             * Default constructor for File object
             */
            RegularFile();

            /**
             * Constructor for File object with parameter (file path)
             * @param filePath
             */
            RegularFile(const char *filePath);

            /**
             * Destructor, closes the file, frees up all buffers
             */
            virtual ~RegularFile();

            /**
             * Get the C standard mode for fopen
             * @param mode
             * @return 
             */
            static const char *modeStr(Mode mode);

            /******************************************************************/
            
            using fg::util::base::File::open;
            
            /**
             * Open the file with already set options
             * @return 
             */
            virtual fgBool open(void);
            /**
             * Open the file with specified mode
             * @param mode
             * @return 
             */
            virtual fgBool open(Mode mode);
            /**
             * Open the file (pointed to by path) with specified mode
             * @param filePath
             * @param mode
             * @return 
             */
            virtual fgBool open(const char *filePath, Mode mode);
            
            /******************************************************************/
            
            /**
             * Close the file
             * @return 
             */
            virtual fgBool close(void);

            /**
             * Check if file is currently opened
             * @return 
             */
            virtual fgBool isOpen(void) const;

            /**
             * Check if file exists
             * @param filePath
             * @return 
             */
            static fgBool exists(const char *filePath);

            /**
             * Check if file exists
             * @param filePath
             * @return 
             */
            static fgBool exists(const std::string &filePath);

            /**
             * Check if file exists
             * @return 
             */
            virtual fgBool exists(void) {
                return RegularFile::exists(m_filePath.c_str());
            }
            
            /******************************************************************/

            using fg::util::base::File::load;
            
            /**
             * This will load the whole file into char *buffer
             * @return Newly allocated string representing the contents of the file
             *         There is a limit for how big this buffer can be. If it's
             *         exceeded a NULL pointer will be returned. The returned
             *         string buffer will be null-terminated ('\0' will be appended)
             */
            virtual char *load(void);

            /**
             * This will load the whole file into char *buffer
             * @param filePath
             * @return Newly allocated string representing the contents of the file
             *         There is a limit for how big this buffer can be. If it's
             *         exceeded a NULL pointer will be returned. The returned
             *         string buffer will be null-terminated ('\0' will be appended)
             */
            virtual char *load(const char *filePath);

            /**
             * Read from file
             * @param buffer
             * @param elemsize
             * @param elemcount
             * @return 
             */
            virtual int read(void *buffer, unsigned int elemsize, unsigned int elemcount);
            /**
             * Read string from the file
             * @param buffer
             * @param maxlen
             * @return 
             */
            virtual char *readString(char *buffer, unsigned int maxlen);
            /**
             * Write to the file
             * @param buffer
             * @param elemsize
             * @param elemcount
             * @return 
             */
            virtual int write(void *buffer, unsigned int elemsize, unsigned int elemcount);
            /**
             * Print to the file
             * @param fmt
             * @return 
             */
            virtual int print(const char *fmt, ...);
            /**
             * Put given string into the file
             * @param str
             * @return 
             */
            virtual int puts(const char *str);
            
            /******************************************************************/

            /**
             * Check is it end of file
             * @return 
             */
            virtual fgBool isEOF(void);
            /**
             * Flush file buffers
             * @return 
             */
            virtual fgBool flush(void);

            /**
             *  Get (read) single character from file
             * @return 
             */
            virtual int getChar(void);
            /**
             * Put (write) single character to file
             * @param c
             * @return 
             */
            virtual int putChar(char c);
            /**
             * Get the file size (in bytes)
             * @return 
             */
            virtual int getSize(void);
            /**
             * Get the current position in the file
             * @return 
             */
            virtual long getPosition(void);
            /**
             * Sets the position in the currently open/selected file
             * @param offset
             * @param whence
             * @return 
             */
            virtual int setPosition(long offset, int whence);

            /**
             * Return the stdio FILE standard pointer
             * @return 
             */
            FILE *getFilePtr(void) const {
                return m_file;
            }
        };
    };
};
    #undef FG_INC_REGULAR_FILE_BLOCK
#endif /* FG_INC_REGULAR_FILE */
