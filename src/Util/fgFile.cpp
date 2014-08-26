/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of #FLEXIGAME_PROJECT
 *
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified
 * and/or distributed without the express or written permission from the author.
 *******************************************************/


#include "fgFile.h"

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
	if(m_file != NULL) {
		int result = fclose(m_file);
		// FIXME
	}
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
	if(m_file != NULL || filePath == NULL)
		return FG_FALSE;
	if(strlen(filePath) <= 1) {
		return FG_FALSE;
	}
	if(mode == FG_FILE_MODE_READ || 
		mode == (FG_FILE_MODE_READ | FG_FILE_MODE_BINARY) ||
		mode & FG_FILE_MODE_READ_UPDATE) {
		if(!exists(filePath))
			return FG_FALSE;
	}
	printf("FILE MODE: %d | str: '%s'\n", (int)mode, modeStr(mode));
	m_file = fopen(filePath, modeStr(mode));

	if(m_file == NULL) {
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
	if(mode == FG_FILE_MODE_NONE)
		return FG_FALSE;
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
	// FIXME
	if(m_file != NULL) {
		fclose(m_file);
		m_file = NULL;
		m_modeFlags = FG_FILE_MODE_NONE;
		return FG_TRUE;
	}
	return FG_FALSE;
}

/*
 *
 */
int fgFile::read(void *buffer, unsigned int elemsize, unsigned int elemcount)
{
	if(buffer == NULL || elemsize == 0 || elemcount == 0 || m_file == NULL) {
		// FIXME
		return 0;
	}

	unsigned int elemRead = (unsigned int)fread(buffer, elemsize, elemcount, m_file);

	if(elemRead != elemcount)
	{
		// FIXME
	}
	return elemRead;
}

/*
 *
 */
char *fgFile::readString(char *buffer, unsigned int maxlen)
{
	if(buffer == NULL || maxlen == 0 || m_file == NULL)
		return NULL;

	char *retString = fgets(buffer, maxlen, m_file);
	if(retString == NULL)
	{
		// FIXME
	}
	return retString;
}

/*
 *
 */
int fgFile::print(const char *fmt, ...)
{
	if(fmt == NULL || m_file == NULL)
		return -1;

	char buf[FG_MAX_BUFFER];
	va_list args;

	va_start(args,fmt);
	vsnprintf(buf, FG_MAX_BUFFER, fmt, args);
	va_end(args);

	int charsCount = fprintf(m_file, buf);
	return charsCount;
}

/*
 *
 */
int fgFile::write(void *buffer, unsigned int elemsize, unsigned int elemcount)
{
	if(m_file == NULL || buffer == NULL || elemsize == 0 || elemcount == 0)
		return -1;

	unsigned int elemWritten = (unsigned int) fwrite(buffer, elemsize, elemcount, m_file);
	if(elemWritten != elemcount)
	{
		// #FIXME
	}

	return elemWritten;
}

/*
 *
 */
int fgFile::puts(const char *str)
{
	if(m_file == NULL || str == NULL)
		return -1;

	int status = fputs(str, m_file);
	// FIXME
	return status;
}