/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgFile.h"
#include "fgFileErrorCodes.h"

#include "fgMemory.h"
#include "fgLog.h"
#include "fgMessageSubsystem.h"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cerrno>

/**
 * Check if file exists
 * @param filePath
 * @return 
 */
fgBool fg::util::File::exists(const char *filePath) {
#if defined FG_USING_MARMALADE
    return (fgBool)s3eFileCheckExists(filePath);
#else
    std::ifstream fileCheck(filePath);
    return (fgBool)fileCheck.good();
#endif
}

/**
 * Check if file exists
 * @param filePath
 * @return 
 */
fgBool fg::util::File::exists(const std::string &filePath) {
    return fg::util::File::exists(filePath.c_str());
}

/**
 * Default constructor for File object
 */
fg::util::File::File() :
m_file(NULL) {
    m_modeFlags = Mode::READ | Mode::BINARY;
}

/**
 * Constructor for File object with parameter (file path)
 * @param filePath
 */
fg::util::File::File(const char *filePath) :
m_file(NULL) {
    m_modeFlags = Mode::READ | Mode::BINARY;
    m_filePath = filePath;
}

/**
 * Destructor, closes the file, frees up all buffers
 */
fg::util::File::~File() {
    close();
    m_filePath.clear();
}

/**
 * Get the C standard mode for fopen
 * @param mode
 * @return 
 */
const char *fg::util::File::modeStr(Mode mode) {
    if(mode == Mode::NONE)
        return "";
    if(!!(mode & Mode::READ)) {
        if((mode & Mode::UPDATE) && (mode & Mode::BINARY))
            return "r+b";
        if(!!(mode & Mode::UPDATE))
            return "r+";
        if(!!(mode & Mode::BINARY))
            return "rb";
        return "r";
    }
    if(!!(mode & Mode::WRITE)) {
        if(mode & Mode::UPDATE && mode & Mode::BINARY)
            return "w+b";
        if(!!(mode & Mode::UPDATE))
            return "w+";
        if(!!(mode & Mode::BINARY))
            return "wb";
        return "w";
    }
    if(!!(mode & Mode::APPEND)) {
        if(mode & Mode::UPDATE && mode & Mode::BINARY)
            return "a+b";
        if(!!(mode & Mode::UPDATE))
            return "a+";
        if(!!(mode & Mode::BINARY))
            return "ab";
        return "a";
    }
    return "";
}

/**
 * Open the file (pointed to by path) with specified mode
 * @param filePath
 * @param mode
 * @return 
 */
fgBool fg::util::File::open(const char *filePath, Mode mode) {
    if(filePath == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NO_PATH);
        //FG_LOG_WARNING("%s: No file path specified", tag_type::name())
        return FG_FALSE;
    }
    if(m_file != NULL) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ALREADY_OPEN, "%s", filePath);
        //FG_LOG_ERROR("%s: File is already open: '%s'");
        return FG_FALSE;
    }
    if(strlen(filePath) <= 1) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NO_PATH, "%s", filePath);
        return FG_FALSE;
    }
    if(mode == Mode::READ ||
       mode == (Mode::READ | Mode::BINARY) ||
       mode & Mode::UPDATE) {
        if(!exists(filePath)) {
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_DOESNT_EXIST, "%s", filePath);
            return FG_FALSE;
        }
    }

    FG_ERRNO_CLEAR();
    m_file = fopen(filePath, modeStr(mode));

    if(m_file == NULL) {
        if(FG_ERRNO)
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO, "%s", filePath);
        else
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_OPEN_FAILED, "%s", filePath);
        return FG_FALSE;
    }
    setPath(filePath);
    m_modeFlags = mode;
    return FG_TRUE;
}

/**
 * Open the file with specified mode
 * @param mode
 * @return 
 */
fgBool fg::util::File::open(Mode mode) {
    if(mode == Mode::NONE) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_WRONG_MODE, "%s", m_filePath.c_str());
        return FG_FALSE;
    }
    return open(m_filePath.c_str(), mode);
}

/**
 * Open the file with already set options
 * @return 
 */
fgBool fg::util::File::open(void) {
    if(m_modeFlags == Mode::NONE)
        m_modeFlags = Mode::READ;
    return open(m_filePath.c_str(), m_modeFlags);
}

/**
 * Close the file
 * @return 
 */
fgBool fg::util::File::close(void) {
    if(m_file) {
        FG_ERRNO_CLEAR();
        clearerr(m_file);
    }
    if(m_file != NULL) {
        if(fclose(m_file) == FG_EOF) {
            if(FG_ERRNO)
                FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO, "%s", m_filePath.c_str());
            else
                FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_CLOSING, "%s", m_filePath.c_str());
            m_file = NULL;
            return FG_FALSE;
        }
        m_file = NULL;
    }
    return FG_TRUE;
}

/**
 * Check if file is currently opened
 * @return 
 */
fgBool fg::util::File::isOpen(void) const {
    if(m_file)
        return FG_TRUE;
    else
        return FG_FALSE;
}

/**
 * This will load the whole file into char *buffer
 * @return Newly allocated string representing the contents of the file
 *         There is a limit for how big this buffer can be. If it's
 *         exceeded a NULL pointer will be returned. The returned
 *         string buffer will be null-terminated ('\0' will be appended)
 */
char *fg::util::File::load(const char *filePath) {
    if(!isOpen() && !open(filePath, Mode::READ | Mode::BINARY)) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_ALREADY_OPEN, "%s", filePath);
        return NULL;
    }

    int fileSize = getSize();
    if(fileSize < 0) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_ERROR_SIZE, "%s", filePath);
        close();
        return NULL;
    }
    // #FIXME
    char *fileBuffer = fgMalloc<char>(fileSize + 1);
    if(fileBuffer == NULL) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO, "%s", filePath); // #FIXME - memory error codes
        close();
        return NULL;
    }

    int bytesRead = read(fileBuffer, 1, fileSize);
    fileBuffer[fileSize] = '\0';
    if(bytesRead != (int)fileSize) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_READ_COUNT, "%s", filePath);
        fgFree(fileBuffer);
        fileBuffer = NULL;
        fileSize = 0;
        close();
        return NULL;
    }

    return fileBuffer;
}

/**
 * This will load the whole file into char *buffer
 * @param filePath
 * @return Newly allocated string representing the contents of the file
 *         There is a limit for how big this buffer can be. If it's
 *         exceeded a NULL pointer will be returned. The returned
 *         string buffer will be null-terminated ('\0' will be appended)
 */
char *fg::util::File::load(void) {
    if(m_filePath.empty()) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NO_PATH, "%s", m_filePath.c_str());
        return NULL;
    }
    return load(m_filePath.c_str());
}

/**
 * Read from file
 * @param buffer
 * @param elemsize
 * @param elemcount
 * @return 
 */
int fg::util::File::read(void *buffer, unsigned int elemsize, unsigned int elemcount) {
    if(buffer == NULL || elemsize == 0 || elemcount == 0 || m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_WRONG_PARAMETERS, "%s", m_filePath.c_str());
        return 0;
    }
    FG_ERRNO_CLEAR();
    clearerr(m_file);
    unsigned int elemRead = (unsigned int)fread(buffer, elemsize, elemcount, m_file);

    if(elemRead != elemcount) {
        if(ferror(m_file) && FG_ERRNO)
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO, "%s", m_filePath.c_str());
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_READ_COUNT, "%s", m_filePath.c_str());
    }
    return elemRead;
}

/**
 * Read string from the file
 * @param buffer
 * @param maxlen
 * @return 
 */
char *fg::util::File::readString(char *buffer, unsigned int maxlen) {
    if(buffer == NULL || maxlen == 0 || m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_WRONG_PARAMETERS);
        return NULL;
    }
    FG_ERRNO_CLEAR();
    clearerr(m_file);
    char *retString = fgets(buffer, maxlen, m_file);
    if(retString == NULL) {
        if(ferror(m_file) && FG_ERRNO)
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO);
        else
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_READ);
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_ERROR_STRING);
    }
    return retString;
}

/**
 * Print to the file
 * @param fmt
 * @return 
 */
int fg::util::File::print(const char *fmt, ...) {
    if(fmt == NULL || m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_WRONG_PARAMETERS);
        return -1;
    }

    char buf[FG_MAX_BUFFER];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, FG_MAX_BUFFER, fmt, args);
    va_end(args);

    FG_ERRNO_CLEAR();
    clearerr(m_file);
    int charsCount = fprintf(m_file, buf);
    if(ferror(m_file)) {
        if(FG_ERRNO)
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO);
        else
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_WRITE);
    }
    return charsCount;
}

/**
 * Write to the file
 * @param buffer
 * @param elemsize
 * @param elemcount
 * @return 
 */
int fg::util::File::write(void *buffer, unsigned int elemsize, unsigned int elemcount) {
    if(m_file == NULL || buffer == NULL || elemsize == 0 || elemcount == 0) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_WRONG_PARAMETERS);
        return -1;
    }
    FG_ERRNO_CLEAR();
    clearerr(m_file);
    unsigned int elemWritten = (unsigned int)fwrite(buffer, elemsize, elemcount, m_file);
    if(elemWritten != elemcount) {
        if(ferror(m_file) && FG_ERRNO)
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO);
        else
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_WRITE);
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_WRITE_COUNT);
    }

    return elemWritten;
}

/**
 * Put given string into the file
 * @param str
 * @return 
 */
int fg::util::File::puts(const char *str) {
    if(str == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_WRONG_PARAMETERS);
        return -1;
    }
    if(m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NOT_OPENED);
        return -1;
    }

    FG_ERRNO_CLEAR();
    clearerr(m_file);
    int status = fputs(str, m_file);
    if(status == FG_EOF) {
        if(ferror(m_file) && FG_ERRNO)
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO);
        else
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_WRITE);
    }
    return status;
}

/**
 * Check is it end of file
 * @return 
 */
fgBool fg::util::File::isEOF(void) {
    if(m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NOT_OPENED);
        return FG_FALSE;
    }
    if(feof(m_file))
        return FG_TRUE;
    return FG_FALSE;
}

/**
 * Flush file buffers
 * @return 
 */
fgBool fg::util::File::flush(void) {
    if(m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NOT_OPENED);
        return FG_FALSE;
    }
    FG_ERRNO_CLEAR();
    clearerr(m_file);
    if(fflush(m_file) == 0) {
        if(ferror(m_file) && FG_ERRNO)
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO);
        else
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_FLUSH);
        return FG_FALSE;
    }
    return FG_TRUE;
}

/**
 *  Get (read) single character from file
 * @return 
 */
int fg::util::File::getChar(void) {
    if(m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NOT_OPENED);
        return -1;
    }
    FG_ERRNO_CLEAR();
    clearerr(m_file);
    int charRead = fgetc(m_file);
    if(charRead == FG_EOF) {
        if(ferror(m_file) && FG_ERRNO) {
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO);
        } else {
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_READ);
        }
        if(feof(m_file))
            FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_EOF);
    }
    return charRead;
}

/**
 * Put (write) single character to file
 * @param c
 * @return 
 */
int fg::util::File::putChar(char c) {
    if(m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NOT_OPENED);
        return FG_EOF;
    }
    FG_ERRNO_CLEAR();
    clearerr(m_file);
    int charWrite = fputc(c, m_file);
    if(charWrite == FG_EOF) {
        if(ferror(m_file) && FG_ERRNO)
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO);
        else
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_WRITE);
    }
    return charWrite;
}

/**
 * Get the file size (in bytes)
 * @return 
 */
int fg::util::File::getSize(void) {
    if(m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NOT_OPENED);
        return -1;
    }
    long size = 0;
    long prev = 0;
    fgBool _err = FG_FALSE;
    // #FIXME
    // #TODO - there needs to be some consistency with
    // holding local errno codes and setting error indicator
    // in status reporter - need additional functions
    prev = getPosition();
    if(prev == -1L)
        _err = FG_TRUE;
    if(!_err) {
        if(setPosition(0L, SEEK_END))
            _err = FG_TRUE;
    }
    if(!_err) {
        size = getPosition();
        if(size == -1L)
            _err = FG_TRUE;
    }
    if(!_err) {
        if(setPosition(prev, SEEK_SET))
            _err = FG_TRUE;
    }
    if(_err)
        size = -1L;
    return (int)size;
}

/**
 * Get the current position in the file
 * @return 
 */
long fg::util::File::getPosition(void) {
    if(m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NOT_OPENED);
        return -1;
    }
    FG_ERRNO_CLEAR();
    clearerr(m_file);
    long position = ftell(m_file);
    if(position == -1L) {
        if(FG_ERRNO)
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO);
        else
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_TELL);
        return -1L;
    }
    return position;
}

/**
 * Sets the position in the currently open/selected file
 * @param offset
 * @param whence
 * @return 
 */
int fg::util::File::setPosition(long offset, int whence) {
    if(m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NOT_OPENED);
        return -1;
    }
    FG_ERRNO_CLEAR();
    clearerr(m_file);
    if(fseek(m_file, offset, whence)) {
        if(ferror(m_file) && FG_ERRNO)
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO);
        else
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_SEEK);
        return -1;
    }
    return 0;
}
