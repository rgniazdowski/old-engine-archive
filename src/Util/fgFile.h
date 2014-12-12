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

    #include "fgBuildConfig.h"
    #include "fgCommon.h"

    #include "fgTag.h"

class fgFile;

    #define FG_TAG_FILE_NAME	"File"
    #define FG_TAG_FILE		FG_TAG_TYPE(fgFile)

FG_TAG_TEMPLATE_ID_AUTO(fgFile, FG_TAG_FILE_NAME);
typedef FG_TAG_FILE fgFileTag;

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

// Enumeration for standard file manipulation modes

enum fgFileMode {
    FG_FILE_MODE_NONE = 0, // No mode specified (invalid).
    FG_FILE_MODE_READ = 1 << 0, // Open file for input operations. The file must exist.
    FG_FILE_MODE_WRITE = 1 << 1, // Create an empty file for output operations.
    FG_FILE_MODE_APPEND = 1 << 2, // Open file for output at the end of a file. The file is created if it does not exist.
    FG_FILE_MODE_UPDATE = 1 << 3, // Additional update mode (both input/output).
    FG_FILE_MODE_BINARY = 1 << 4, // Open file as a binary file.
    // Open a file for update (both for input and output). The file must exist.
    FG_FILE_MODE_READ_UPDATE = FG_FILE_MODE_READ + FG_FILE_MODE_UPDATE,
    // Create an empty file and open it for update (both for input and output). 
    // If a file with the  same name already exists its  contents are discarded 
    // and the file is treated as a new empty file.
    FG_FILE_MODE_WRITE_UPDATE = FG_FILE_MODE_WRITE + FG_FILE_MODE_UPDATE,
    // Open a file for update (both for input and  output) with all output operations
    // writing data at the end of the file. Repositioning operations (fseek, fsetpos,
    // rewind)  affects the  next input  operations,  but  output operations move the
    // position back to the end of file.  The file is  created if  it does not exist.
    FG_FILE_MODE_APPEND_UPDATE = FG_FILE_MODE_APPEND + FG_FILE_MODE_UPDATE
};
// Overload standard bitwise operator for enum type
FG_ENUM_FLAGS(fgFileMode);

/*
 * Platform independent wrapper for basic file operations
 */
class fgFile {
public:
    typedef fgFileTag tag_type;
protected:
    // C standard file handle
    FILE *m_file;
    // File full path
    std::string m_filePath;
    // Current mode in which is open
    fgFileMode m_modeFlags;
public:
    // Default constructor for File object
    fgFile();

    // Constructor for File object with parameter (file path)
    fgFile(const char *filePath);

    // Destructor, closes the file, frees up all buffers
    virtual ~fgFile();

    // Set the file path
    void setPath(const char *filePath) {
        m_filePath = filePath;
    }

    // Set the file path
    void setPath(std::string & filePath) {
        m_filePath = filePath;
    }

    // Return the file path (C string)
    const char *getPath(void) const {
        return m_filePath.c_str();
    }

    // Set file open mode
    void setMode(fgFileMode mode);

    // Get the C standard mode for fopen
    static const char *modeStr(fgFileMode mode);

    // Open the file with already set options
    fgBool open(void);
    // Open the file with specified mode
    fgBool open(fgFileMode mode);
    // Open the file (pointed to by path) with specified mode
    fgBool open(const char *filePath, fgFileMode mode);
    // Close the file
    fgBool close(void);

    // Check if file is currently opened
    fgBool isOpen(void) const;

    // Check if file exists
    static fgBool exists(const char *filePath);

    // Check if file exists
    static fgBool exists(const std::string &filePath);

    // Check if file exists
    fgBool exists(void) {
        return fgFile::exists(m_filePath.c_str());
    }

    // This will load the whole file into char *buffer
    char *load(void);

    // This will load the whole file into char *buffer
    char *load(const char *filePath);

    // Read from file
    int read(void *buffer, unsigned int elemsize, unsigned int elemcount);
    // Read string from file
    char *readString(char *buffer, unsigned int maxlen);
    // Write to file
    int write(void *buffer, unsigned int elemsize, unsigned int elemcount);
    // Print to file
    int print(const char *fmt, ...);
    // Put string to file :)
    int puts(const char *str);

    // Check is it end of file
    fgBool isEOF(void);
    // Flush file buffers
    fgBool flushFile(void);

    // Get (read) single character from file
    int getChar(void);
    // Put (write) single character to file
    int putChar(char c);
    // Get the file size #FIXME (need to reopen in binary mode)
    int getSize(void);
    // Get current position in file
    long getPosition(void);
    // Set position in file
    int setPosition(long offset, int whence);

    // Return the stdio FILE standard pointer
    FILE *getFilePtr(void) const {
        return m_file;
    }
};

#endif /* FG_INC_FILE */
