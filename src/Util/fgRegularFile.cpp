/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgRegularFile.h"
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

#if defined(FG_USING_SDL2)
#include <SDL2/SDL.h>

/**
 * The fgets function returns s if successful. If end-of-file is 
 * encountered and no characters have been read into the array, 
 * the contents of the array remain unchanged and a null pointer 
 * is returned. If a read error occurs during the operation, the 
 * array contents are indeterminate and a null pointer is returned. 
 * 
 * @param s
 * @param n
 * @param file
 * @return 
 */
char *rw_fgets(char *s, int n, SDL_RWops *file) {
    if(!s || !file || !n) {
        return NULL;
    }
    register char *cs = s;
    char c = 0;
    *cs = 0;
    while(file->read(file, &c, 1, 1)) {
        if(!c) {
            return NULL;
        }
        *(cs) = c;
        cs++;

        if(c == '\n') {
            break;
        }
        c = 0;
        if(!--n)
            break;
    }
    if(!c && n)
        return NULL;
    *cs = 0;
    return s;
}
#endif /* FG_USING_SDL2 */

using namespace fg;

//------------------------------------------------------------------------------

fgBool util::CRegularFile::exists(const char *filePath) {
#if 1
    std::ifstream fileCheck(filePath);
    return (fgBool)fileCheck.good();
#endif
}
//------------------------------------------------------------------------------

fgBool util::CRegularFile::exists(const std::string &filePath) {
    return util::CRegularFile::exists(filePath.c_str());
}
//------------------------------------------------------------------------------

util::CRegularFile::CRegularFile() :
m_file(NULL) {
    m_modeFlags = Mode::READ | Mode::BINARY;
}
//------------------------------------------------------------------------------

util::CRegularFile::CRegularFile(const char *filePath) :
m_file(NULL) {
    m_modeFlags = Mode::READ | Mode::BINARY;
    m_filePath = filePath;
}
//------------------------------------------------------------------------------

util::CRegularFile::~CRegularFile() {
    close();
    m_filePath.clear();
}
//------------------------------------------------------------------------------

const char *util::CRegularFile::modeStr(Mode mode) {
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
//------------------------------------------------------------------------------

fgBool util::CRegularFile::open(const char *filePath, Mode mode) {
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
#if !defined(FG_USING_PLATFORM_ANDROID)
        if(!exists(filePath)) {
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_DOESNT_EXIST, "%s", filePath);
            return FG_FALSE;
        }
#endif
    }
    
    FG_ERRNO_CLEAR();
#if defined(FG_USING_SDL2)
    //FG_LOG_DEBUG("SDL_RWFromFile: opening file '%s'", filePath);
    m_file = SDL_RWFromFile(filePath, modeStr(mode));
    if(!m_file) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_OPEN_FAILED, "%s", SDL_GetError());
    } else {
    }
#else
    m_file = fopen(filePath, modeStr(mode));
#endif

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
//------------------------------------------------------------------------------

fgBool util::CRegularFile::open(Mode mode) {
    if(mode == Mode::NONE) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_WRONG_MODE, "%s", m_filePath.c_str());
        return FG_FALSE;
    }
    return open(m_filePath.c_str(), mode);
}
//------------------------------------------------------------------------------

fgBool util::CRegularFile::open(void) {
    if(m_modeFlags == Mode::NONE)
        m_modeFlags = Mode::READ;
    return open(m_filePath.c_str(), m_modeFlags);
}
//------------------------------------------------------------------------------

fgBool util::CRegularFile::close(void) {
    if(m_file) {
        FG_ERRNO_CLEAR();
        //m_file->hidden.stdio.fp
#if !defined(FG_USING_SDL2)
        clearerr(m_file);
#else
        if(m_file->type == SDL_RWOPS_STDFILE)
            clearerr(m_file->hidden.stdio.fp);
#endif
    }
    if(m_file != NULL) {
#if defined(FG_USING_SDL2)
        if(m_file->close(m_file) == -1) {
#else
        if(fclose(m_file) == FG_EOF) {
#endif
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
//------------------------------------------------------------------------------

fgBool util::CRegularFile::isOpen(void) const {
    if(m_file)
        return FG_TRUE;
    else
        return FG_FALSE;
}
//------------------------------------------------------------------------------

char *util::CRegularFile::load(const char *filePath) {
    if(!isOpen() && !open(filePath, Mode::READ | Mode::BINARY)) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_ALREADY_OPEN, "%s", filePath);
        return NULL;
    }
    int fileSize = getSize();
    if(fileSize <= 0) {
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
#if defined(FG_USING_SDL2)
    int bytesRead = m_file->read(m_file, fileBuffer, 1, fileSize);
#if defined(FG_USING_PLATFORM_ANDROID)
    FG_LOG_DEBUG("Loading file '%s' into buffer[%d], contents: '%s'", filePath, bytesRead, fileBuffer);
#endif
#else
    int bytesRead = read(fileBuffer, 1, fileSize);
#endif
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
//------------------------------------------------------------------------------

char *util::CRegularFile::load(void) {
    if(m_filePath.empty()) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NO_PATH, "%s", m_filePath.c_str());
        return NULL;
    }
    return load(m_filePath.c_str());
}
//------------------------------------------------------------------------------

int util::CRegularFile::read(void *buffer, unsigned int elemsize, unsigned int elemcount) {
    if(buffer == NULL || elemsize == 0 || elemcount == 0 || m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_WRONG_PARAMETERS, "%s", m_filePath.c_str());
        return 0;
    }
#if !defined(FG_USING_SDL2)
    FG_ERRNO_CLEAR();
    clearerr(m_file);
#endif
#if defined(FG_USING_SDL2)
    unsigned int elemRead = (unsigned int)m_file->read(m_file, buffer, elemsize, elemcount);
#else
    unsigned int elemRead = (unsigned int)fread(buffer, elemsize, elemcount, m_file);
#endif
    if(elemRead != elemcount) {
#if !defined(FG_USING_SDL2)
        if(ferror(m_file) && FG_ERRNO)
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO, "%s", m_filePath.c_str());
#endif
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_READ_COUNT, "%s", m_filePath.c_str());
    }
    return elemRead;
}
//------------------------------------------------------------------------------

char *util::CRegularFile::readString(char *buffer, unsigned int maxlen) {
    if(buffer == NULL || maxlen == 0 || m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_WRONG_PARAMETERS);
        return NULL;
    }
#if !defined(FG_USING_SDL2)
    FG_ERRNO_CLEAR();
    clearerr(m_file);
#endif
#if defined(FG_USING_SDL2)
    char *retString = rw_fgets(buffer, maxlen, m_file);
#else
    char *retString = fgets(buffer, maxlen, m_file);
#endif
    if(retString == NULL) {
#if !defined(FG_USING_SDL2)
        if(ferror(m_file) && FG_ERRNO)
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO);
        else
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_READ);
#endif
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_ERROR_STRING);
    }
    return retString;
}
//------------------------------------------------------------------------------

int util::CRegularFile::print(const char *fmt, ...) {
    if(fmt == NULL || m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_WRONG_PARAMETERS);
        return -1;
    }

    char buf[FG_MAX_BUFFER];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, FG_MAX_BUFFER, fmt, args);
    va_end(args);

#if !defined(FG_USING_SDL2)
    FG_ERRNO_CLEAR();
    clearerr(m_file);
#endif

#if defined(FG_USING_SDL2)
    int charsCount = m_file->write(m_file, buf, 1, strlen(buf));
#else
    int charsCount = fprintf(m_file, "%s", buf);
    if(ferror(m_file)) {
        if(FG_ERRNO)
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO);
        else
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_WRITE);
    }

#endif
    return charsCount;
}
//------------------------------------------------------------------------------

int util::CRegularFile::write(const void *buffer, unsigned int elemsize, unsigned int elemcount) {
    if(m_file == NULL || buffer == NULL || elemsize == 0 || elemcount == 0) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_WRONG_PARAMETERS);
        return -1;
    }
#if !defined(FG_USING_SDL2)
    FG_ERRNO_CLEAR();
    clearerr(m_file);
#endif
#if defined(FG_USING_SDL2)
    unsigned int elemWritten = (unsigned int)m_file->write(m_file, buffer, elemsize, elemcount);
#else
    unsigned int elemWritten = (unsigned int)fwrite(buffer, elemsize, elemcount, m_file);
#endif
    if(elemWritten != elemcount) {
#if !defined(FG_USING_SDL2)
        if(ferror(m_file) && FG_ERRNO)
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO);
        else
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_WRITE);
#endif
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_WRITE_COUNT);
    }

    return elemWritten;
}
//------------------------------------------------------------------------------

int util::CRegularFile::puts(const char *str) {
    if(str == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_WRONG_PARAMETERS);
        return -1;
    }
    if(m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NOT_OPENED);
        return -1;
    }
#if defined(FG_USING_SDL2)
    int status = m_file->write(m_file, str, 1, strlen(str));
    if(!status) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_WRITE);
    }
#else
    FG_ERRNO_CLEAR();
    clearerr(m_file);
    int status = fputs(str, m_file);
    if(status == FG_EOF) {
        if(ferror(m_file) && FG_ERRNO)
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO);
        else
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_WRITE);
    }
#endif
    return status;
}
//------------------------------------------------------------------------------

fgBool util::CRegularFile::isEOF(void) {
    if(m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NOT_OPENED);
        return FG_FALSE;
    }
#if defined(FG_USING_SDL2)
    if(SDL_RWtell(m_file) < 0)
        return FG_TRUE;
#else
    if(feof(m_file))
        return FG_TRUE;
#endif
    return FG_FALSE;
}
//------------------------------------------------------------------------------

fgBool util::CRegularFile::flush(void) {
    if(m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NOT_OPENED);
        return FG_FALSE;
    }
#if !defined(FG_USING_SDL2)
    FG_ERRNO_CLEAR();
    clearerr(m_file);
    if(fflush(m_file) == FG_EOF) {
        if(ferror(m_file) && FG_ERRNO)
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO);
        else
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_FLUSH);
        return FG_FALSE;
    }
#endif
    return FG_TRUE;
}
//------------------------------------------------------------------------------

int util::CRegularFile::getChar(void) {
    if(m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NOT_OPENED);
        return -1;
    }
#if defined(FG_USING_SDL2)
    int charRead = 0;
    int count = m_file->read(m_file, &charRead, 1, 1);
    if(!count) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_EOF);
        return FG_EOF;
    }
#else
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
#endif
    return charRead;
}
//------------------------------------------------------------------------------

int util::CRegularFile::putChar(char c) {
    if(m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NOT_OPENED);
        return FG_EOF;
    }
#if defined(FG_USING_SDL2)
    int charWrite = m_file->write(m_file, &c, 1, 1);
    if(!charWrite) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_WRITE);
    }
#else
    FG_ERRNO_CLEAR();
    clearerr(m_file);
    int charWrite = fputc(c, m_file);
    if(charWrite == FG_EOF) {
        if(ferror(m_file) && FG_ERRNO)
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO);
        else
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_WRITE);
    }
#endif
    return charWrite;
}
//------------------------------------------------------------------------------

int util::CRegularFile::getSize(void) {
    if(m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NOT_OPENED);
        return -1;
    }
    long size = 0;

#if defined(FG_USING_SDL2)
    size = (long)m_file->size(m_file);
#else
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
#endif
    return (int)size;
}
//------------------------------------------------------------------------------

long util::CRegularFile::getPosition(void) {
    if(m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NOT_OPENED);
        return -1;
    }
#if defined(FG_USING_SDL2)
    long position = (long)SDL_RWtell(m_file);
#else
    FG_ERRNO_CLEAR();
    clearerr(m_file);
    long position = ftell(m_file);
#endif
    if(position == -1L) {
        if(FG_ERRNO)
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO);
        else
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_TELL);
        return -1L;
    }
    return position;
}
//------------------------------------------------------------------------------

int util::CRegularFile::setPosition(long offset, int whence) {
    if(m_file == NULL) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_FILE_NOT_OPENED);
        return -1;
    }
#if defined(FG_USING_SDL2)
    if(m_file->seek(m_file, offset, whence) < 0) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_SEEK);
    }
#else
    FG_ERRNO_CLEAR();
    clearerr(m_file);
    if(fseek(m_file, offset, whence)) {
        if(ferror(m_file) && FG_ERRNO)
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO);
        else
            FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_FILE_ERROR_SEEK);
        return -1;
    }
#endif
    return 0;
}
//------------------------------------------------------------------------------
