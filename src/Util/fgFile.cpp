/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgFile.h"
#include "fgFileErrorCodes.h"

#include "fgMemory.h"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <cerrno>

/*
 * #TODO - Need to add error handling and proper calls for all version of the code
 */

fgBool fgFile::exists(const char *filePath)
{
	std::ifstream fileCheck(filePath);
	return (fgBool)fileCheck.good();
}

/*
 *
 */
fgFile::fgFile() :
	m_file(NULL), 
	m_modeFlags(FG_FILE_MODE_READ | FG_FILE_MODE_BINARY)
{
}

/*
 *
 */
fgFile::fgFile(const char *filePath) : m_file(NULL),
	m_modeFlags(FG_FILE_MODE_READ | FG_FILE_MODE_BINARY)
{
	m_filePath = filePath;
}

/*
 *
 */
fgFile::~fgFile()
{
	close();
	m_filePath.clear();
	clearStatus();
}

/*
 *
 */
void fgFile::setMode(fgFileMode mode)
{
	m_modeFlags = mode;
}

/*
 *
 */
const char *fgFile::modeStr(fgFileMode mode)
{
	if(mode == FG_FILE_MODE_NONE)
		return "";
	if(mode & FG_FILE_MODE_READ) {
		if(mode & FG_FILE_MODE_UPDATE && mode & FG_FILE_MODE_BINARY)
			return "r+b";
		if(mode & FG_FILE_MODE_UPDATE)
			return "r+";
		if(mode & FG_FILE_MODE_BINARY)
			return "rb";
		return "r";
	}
	if(mode & FG_FILE_MODE_WRITE) {
		if(mode & FG_FILE_MODE_UPDATE && mode & FG_FILE_MODE_BINARY)
			return "w+b";
		if(mode & FG_FILE_MODE_UPDATE)
			return "w+";
		if(mode & FG_FILE_MODE_BINARY)
			return "wb";
		return "w";
	}
	if(mode & FG_FILE_MODE_APPEND) {
		if(mode & FG_FILE_MODE_UPDATE && mode & FG_FILE_MODE_BINARY)
			return "a+b";
		if(mode & FG_FILE_MODE_UPDATE)
			return "a+";
		if(mode & FG_FILE_MODE_BINARY)
			return "ab";
		return "a";
	}
	return "";
}

/*
 * #TODO
 */
fgBool fgFile::open(const char *filePath, fgFileMode mode)
{
	if(filePath == NULL) {
		reportWarning(FG_ERRNO_FILE_NO_PATH);
		return FG_FALSE;
	}
	if(m_file != NULL) {
		reportError(FG_ERRNO_FILE_ALREADY_OPEN);
		return FG_FALSE;
	}
	if(strlen(filePath) <= 1) {
		reportWarning(FG_ERRNO_FILE_NO_PATH);
		return FG_FALSE;
	}
	if(mode == FG_FILE_MODE_READ || 
		mode == (FG_FILE_MODE_READ | FG_FILE_MODE_BINARY) ||
		mode & FG_FILE_MODE_READ_UPDATE) {
		if(!exists(filePath)) {
			reportError(FG_ERRNO_FILE_DOESNT_EXIST);
			return FG_FALSE;
		}
	}
	FG_ERRNO_CLEAR();
	m_file = fopen(filePath, modeStr(mode));

	if(m_file == NULL) {
		if(FG_ERRNO)
			reportError(FG_ERRNO);
		else
			reportError(FG_ERRNO_FILE_OPEN_FAILED);
		return FG_FALSE;
	}
	setPath(filePath);
	m_modeFlags = mode;
	return FG_TRUE;
}

/*
 *
 */
fgBool fgFile::open(fgFileMode mode)
{
	if(mode == FG_FILE_MODE_NONE) {
		reportWarning(FG_ERRNO_FILE_WRONG_MODE);
		return FG_FALSE;
	}
	return open(m_filePath.c_str(), mode);
}

/*
 *
 */
fgBool fgFile::open(void) {
	if(m_modeFlags == FG_FILE_MODE_NONE)
		m_modeFlags = FG_FILE_MODE_READ;
	return open(m_filePath.c_str(), m_modeFlags);
}

/*
 *
 */
fgBool fgFile::close(void)
{
	if(m_file) {
		FG_ERRNO_CLEAR();
		clearerr(m_file);
	}
	if(m_file != NULL) {
		if(fclose(m_file) == FG_EOF) {
			if(FG_ERRNO)
				reportError(FG_ERRNO);
			else
				reportError(FG_ERRNO_FILE_CLOSING);
			m_file = NULL;
			return FG_FALSE;
		}
		m_file = NULL;
	}
	return FG_TRUE;
}

/*
 *
 */
fgBool fgFile::isOpen(void) const {
	if(m_file)
		return FG_TRUE;
	else
		return FG_FALSE;
}

/*
 *
 */
char *fgFile::load(const char *filePath)
{
	if(!open(filePath, FG_FILE_MODE_READ | FG_FILE_MODE_BINARY)) {
		return NULL;
	}

	int fileSize = getSize();
	if(fileSize < 0) {
		reportWarning(FG_ERRNO_FILE_ERROR_SIZE);
		return NULL;
	}

	char *fileBuffer = (char *) fgMalloc(sizeof(char) * (fileSize+1));
	if(fileBuffer == NULL) {
		reportError(FG_ERRNO); // FIXME - memory error codes
		return NULL;
	}

	int bytesRead = read(fileBuffer, 1, fileSize);
	fileBuffer[fileSize] = '\0';
	if(bytesRead != (int)fileSize) {
		fgFree(fileBuffer);
		fileBuffer = NULL;
		fileSize = 0;
		close();
		return NULL;
	}

	return fileBuffer;
}

/*
 *
 */
char *fgFile::load(void) 
{
	if(m_filePath.empty()) {
		reportWarning(FG_ERRNO_FILE_NO_PATH);
		return NULL;
	}
	return load(m_filePath.c_str());
}

/*
 *
 */
int fgFile::read(void *buffer, unsigned int elemsize, unsigned int elemcount)
{
	if(buffer == NULL || elemsize == 0 || elemcount == 0 || m_file == NULL) {
		reportWarning(FG_ERRNO_FILE_WRONG_PARAMETERS);
		return 0;
	}
	FG_ERRNO_CLEAR();
	clearerr(m_file);
	unsigned int elemRead = (unsigned int)fread(buffer, elemsize, elemcount, m_file);

	if(elemRead != elemcount)
	{
		if(ferror(m_file) && FG_ERRNO)
			reportError(FG_ERRNO);
		reportWarning(FG_ERRNO_FILE_READ_COUNT);
	}
	return elemRead;
}

/*
 *
 */
char *fgFile::readString(char *buffer, unsigned int maxlen)
{
	if(buffer == NULL || maxlen == 0 || m_file == NULL) {
		reportWarning(FG_ERRNO_FILE_WRONG_PARAMETERS);
		return NULL;
	}
	FG_ERRNO_CLEAR();
	clearerr(m_file);
	char *retString = fgets(buffer, maxlen, m_file);
	if(retString == NULL)
	{
		if(ferror(m_file) && FG_ERRNO)
			reportError(FG_ERRNO);
		else
			reportError(FG_ERRNO_FILE_ERROR_READ);
		reportWarning(FG_ERRNO_FILE_ERROR_STRING);
	}
	return retString;
}

/*
 *
 */
int fgFile::print(const char *fmt, ...)
{
	if(fmt == NULL || m_file == NULL) {
		reportWarning(FG_ERRNO_FILE_WRONG_PARAMETERS);
		return -1;
	}

	char buf[FG_MAX_BUFFER];
	va_list args;

	va_start(args,fmt);
	vsnprintf(buf, FG_MAX_BUFFER, fmt, args);
	va_end(args);

	FG_ERRNO_CLEAR();
	clearerr(m_file);
	int charsCount = fprintf(m_file, buf);
	if(ferror(m_file)) {
		if(FG_ERRNO)
			reportError(FG_ERRNO);
		else
			reportError(FG_ERRNO_FILE_ERROR_WRITE);
	}
	return charsCount;
}

/*
 *
 */
int fgFile::write(void *buffer, unsigned int elemsize, unsigned int elemcount)
{
	if(m_file == NULL || buffer == NULL || elemsize == 0 || elemcount == 0) {
		reportWarning(FG_ERRNO_FILE_WRONG_PARAMETERS);
		return -1;
	}
	FG_ERRNO_CLEAR();
	clearerr(m_file);
	unsigned int elemWritten = (unsigned int) fwrite(buffer, elemsize, elemcount, m_file);
	if(elemWritten != elemcount)
	{
		if(ferror(m_file) && FG_ERRNO)
			reportError(FG_ERRNO);
		else
			reportError(FG_ERRNO_FILE_ERROR_WRITE);
		reportWarning(FG_ERRNO_FILE_WRITE_COUNT);
	}

	return elemWritten;
}

/*
 *
 */
int fgFile::puts(const char *str)
{
	if(str == NULL) {
		reportWarning(FG_ERRNO_FILE_WRONG_PARAMETERS);
		return -1;
	}
	if(m_file == NULL) {
		reportWarning(FG_ERRNO_FILE_NOT_OPENED);
		return -1;
	}

	FG_ERRNO_CLEAR();
	clearerr(m_file);
	int status = fputs(str, m_file);
	if(status == FG_EOF) {
		if(ferror(m_file) && FG_ERRNO)
			reportError(FG_ERRNO);
		else
			reportError(FG_ERRNO_FILE_ERROR_WRITE);
	}
	return status;
}

/*
 *
 */
fgBool fgFile::isEOF(void)
{
	if(m_file == NULL)
	{
		reportWarning(FG_ERRNO_FILE_NOT_OPENED);
		return FG_FALSE;
	}
	if(feof(m_file))
		return FG_TRUE;
	return FG_FALSE;
}

/*
 *
 */
fgBool fgFile::flushFile(void)
{
	if(m_file == NULL) {
		reportWarning(FG_ERRNO_FILE_NOT_OPENED);
		return FG_FALSE;
	}
	FG_ERRNO_CLEAR();
	clearerr(m_file);
	if(fflush(m_file) == 0) {
		if(ferror(m_file) && FG_ERRNO)
			reportError(FG_ERRNO);
		else
			reportError(FG_ERRNO_FILE_ERROR_FLUSH);
		return FG_FALSE;
	}
	return FG_TRUE;
}

/*
 *
 */
int fgFile::getChar(void)
{
	if(m_file == NULL) {
		reportWarning(FG_ERRNO_FILE_NOT_OPENED);
		return -1;
	}
	FG_ERRNO_CLEAR();
	clearerr(m_file);
	int charRead = fgetc(m_file);
	if(charRead == FG_EOF) {
		if(ferror(m_file) && FG_ERRNO) {
			reportError(FG_ERRNO);
		} else {
			reportError(FG_ERRNO_FILE_ERROR_READ);
		}
		if(feof(m_file))
			reportWarning(FG_ERRNO_FILE_EOF);
	}
	return charRead;
}

/*
 *
 */
int fgFile::putChar(char c)
{
	if(m_file == NULL) {
		reportWarning(FG_ERRNO_FILE_NOT_OPENED);
		return FG_EOF;
	}
	FG_ERRNO_CLEAR();
	clearerr(m_file);
	int charWrite = fputc(c, m_file);
	if(charWrite == FG_EOF) {
		if(ferror(m_file) && FG_ERRNO)
			reportError(FG_ERRNO);
		else
			reportError(FG_ERRNO_FILE_ERROR_WRITE);
	}
	return charWrite;
}

/*
 * Get the file size #FIXME (need to reopen in binary mode)
 */
int fgFile::getSize(void)
{
	if(m_file == NULL) {
		reportWarning(FG_ERRNO_FILE_NOT_OPENED);
		return -1;
	}
	long size=0;
	long prev=0;
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

/*
 * Get current position in file
 */
long fgFile::getPosition(void) 
{
	if(m_file == NULL) {
		reportWarning(FG_ERRNO_FILE_NOT_OPENED);
		return -1;
	}
	FG_ERRNO_CLEAR();
	clearerr(m_file);
	long position = ftell(m_file);
	if(position == -1L) {
		if(FG_ERRNO)
			reportError(FG_ERRNO);
		else
			reportError(FG_ERRNO_FILE_ERROR_TELL);
		return -1L;
	}
	return position;
}

/*
 *
 */
int fgFile::setPosition(long offset, int whence) 
{
	if(m_file == NULL) {
		reportWarning(FG_ERRNO_FILE_NOT_OPENED);
		return -1;
	}
	FG_ERRNO_CLEAR();
	clearerr(m_file);
	if(fseek(m_file, offset, whence)) {
		if(ferror(m_file) && FG_ERRNO)
			reportError(FG_ERRNO);
		else
			reportError(FG_ERRNO_FILE_ERROR_SEEK);
		return -1;
	}
	return 0;
}
