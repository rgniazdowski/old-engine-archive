/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/


#include "fgFileStream.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

/*
 * #TODO - Need to add error handling and proper calls for all version of the code
 */

/*
 * #TODO
 */
bool fgFileStream::openFile(const char *filePath, const char *mode)
{
	if(m_file != NULL || mode == NULL || filePath == NULL)
		return false;
	if(strlen(filePath) <= 1) {
		return false;
	}
	if(!fileExists(filePath)) {
		return false;
	}

	strncpy(m_filePath, filePath, FG_FILE_PATH_MAX-1);
	m_file = fopen(filePath, mode);

	if(m_file == NULL) {
		return false;
	}
	return true;
}

/*
 *
 */
bool fgFileStream::openFile(const char *mode)
{
	if(mode == NULL)
		return false;
	if(strlen(mode) < 1)
		return false;

	return openFile(m_filePath, mode);
}

/*
 *
 */
bool fgFileStream::closeFile(void)
{
	// FIXME
	if(m_file != NULL) {
		fclose(m_file);
		m_file = NULL;
		return true;
	}
	return false;
}

/*
 *
 */
int fgFileStream::readFile(void *buffer, unsigned int elemsize, unsigned int elemcount)
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
char *fgFileStream::readString(char *buffer, unsigned int maxlen)
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
int fgFileStream::print(const char *fmt, ...)
{
	if(fmt == NULL || m_file == NULL)
		return -1;

	char buf[512];
	va_list args;

	va_start(args,fmt);
	vsnprintf(buf, 512, fmt, args);
	va_end(args);

	int charsCount = fprintf(m_file, buf);
	return charsCount;
}

/*
 *
 */
int fgFileStream::writeFile(void *buffer, unsigned int elemsize, unsigned int elemcount)
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

