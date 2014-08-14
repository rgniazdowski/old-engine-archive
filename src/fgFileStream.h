/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_FILE_STREAM_H_
#define _FG_FILE_STREAM_H_

#include "fgBuildConfig.h"
#include "fgCommon.h"

#include <cstdio>
#include <cstring>

#define FG_FILE_PATH_MAX	FG_PATH_MAX

#define FG_FILE_STREAM_SEEK_SET    SEEK_SET   /* Seek from beginning of file.  */
#define FG_FILE_STREAM_SEEK_CUR    SEEK_CUR   /* Seek from current position.  */
#define FG_FILE_STREAM_SEEK_END    SEEK_END   /* Seek from end of file.  */

/*
 * Platform independent wrapper for basic file operations
 */
class fgFileStream
{
protected:
	FILE *m_file;
	char m_filePath[FG_FILE_PATH_MAX];
public:
	/*
	 *
	 */
	fgFileStream() : m_file(NULL)
	{
		memset(m_filePath, 0, FG_FILE_PATH_MAX);
	}

	/*
	 *
	 */
	fgFileStream(const char *filePath) : m_file(NULL)
	{
		memset(m_filePath, 0, FG_FILE_PATH_MAX);
		strncpy(m_filePath, filePath, strnlen(filePath, FG_FILE_PATH_MAX));
	}

	/*
	 *
	 */
	~fgFileStream()
	{
		if(m_file != NULL) {
			int result = fclose(m_file);
			// FIXME
		}
	}

	// 
	void setFilePath(const char *filePath);
	// 
	fgBool openFile(const char *mode);
	// 
	fgBool openFile(const char *filePath, const char *mode);
	// 
	fgBool closeFile(void);

	// 
	fgBool isFileLoaded(void) const {
		if(m_file)
			return FG_TRUE;
		else
			return FG_FALSE;
	}

	//
	inline static fgBool fileExists(const char *filePath)
	{
		if(0)		// #FIXME
			return FG_FALSE;
		else 
			return FG_TRUE;
	}

	// 
	inline fgBool fileExists(void)
	{
		// #FIXME
		return fgFileStream::fileExists(m_filePath);
	}

	// 
	int readFile(void *buffer, unsigned int elemsize, unsigned int elemcount);
	// 
	char *readString(char *buffer, unsigned int maxlen);
	// 
	int writeFile(void *buffer, unsigned int elemsize, unsigned int elemcount);
	// 
	int print(const char *fmt, ...);

	// 
	fgBool isEOF(void)
	{
		if(m_file == NULL)
			return FG_FALSE;
		return FG_FALSE; // FIXME
	}
	// 
	void flushFile(void)
	{
		if(m_file == NULL)
			return;
		fflush(m_file);
	}
	// 
	int getChar(void)
	{
		if(m_file == NULL)
			return -1;

		int charRead = fgetc(m_file);
		return charRead;
	}
	// 
	void putChar(char c)
	{
		if(m_file == NULL)
			return;
		fputc(c, m_file);
	}
	// 
	int getSize(void)
	{
		if(m_file == NULL)
			return -1;
		long prev = ftell(m_file);
		fseek(m_file, 0L, SEEK_END);
		long size = ftell(m_file);
		fseek(m_file, prev, SEEK_SET); //go back to where we were
		return (int)size; // FIXME
	}
	// 
	long getPosition(void)
	{
		if(m_file == NULL)
			return -1;

		return ftell(m_file);
	}
	//
	int setPosition(long offset, int whence)
	{
		return fseek(m_file, offset, whence);
	}
	// Return the stdio FILE standard pointer
	FILE *getFilePtr(void) const {
		return m_file;
	}

};

#endif
