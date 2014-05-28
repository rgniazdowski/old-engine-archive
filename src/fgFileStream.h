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

#include "fgCommon.h"

#ifdef FG_USING_MARMALADE
#include "s3eFile.h"
#else
#include <cstdio>
#endif

#include <cstring>

#define FG_FILE_PATH_MAX	FG_PATH_MAX

/*
 * Platform independent wrapper for basic file operations
 */
class fgFileStream
{
protected:
#ifdef FG_USING_MARMALADE
	s3eFile *m_file;
#else
	FILE *m_file;
#endif
	char m_filePath[FG_FILE_PATH_MAX];
public:
	fgFileStream() : m_file(NULL)
	{
		memset(m_filePath, 0, FG_FILE_PATH_MAX);
	}

	~fgFileStream()
	{
		if(m_file != NULL) {
#ifdef FG_USING_MARMALADE
			s3eResult result = s3eFileClose(m_file);
#else
			int result = fclose(m_file);
#endif
			// FIXME
		}
	}

	void setFilePath(const char *filePath);
	
	bool openFile(const char *mode);
	bool openFile(const char *filePath, const char *mode);
	bool closeFile(void);

	bool isFileLoaded(void) const {
		if(m_file)
			return true;
		else
			return false;
	}

	inline static bool fileExists(const char *filePath)
	{
#ifdef FG_USING_MARMALADE
		if(S3E_FALSE == s3eFileCheckExists(filePath))
#else
		if(0)		// #FIXME
#endif
			return false;
		else 
			return true;
	}

	inline bool fileExists(void)
	{
		// #FIXME
		return fgFileStream::fileExists(m_filePath);
	}

	int readFile(void *buffer, unsigned int elemsize, unsigned int elemcount);
	char *readString(char *buffer, unsigned int maxlen);
	int writeFile(void *buffer, unsigned int elemsize, unsigned int elemcount);
	int print(const char *fmt, ...);

	bool isEOF(void)
	{
		if(m_file == NULL)
			return false;
#ifdef FG_USING_MARMALADE
		if (S3E_FALSE == s3eFileEOF(m_file))
			return false;
		else
			return true;
#else
		return false; // FIXME
#endif
	}

	void flushFile(void)
	{
		if(m_file == NULL)
			return;
#ifdef FG_USING_MARMALADE
		s3eFileFlush(m_file);
#else
		fflush(m_file);
#endif
	}

	int getChar(void)
	{
		if(m_file == NULL)
			return -1;

#ifdef FG_USING_MARMALADE
		/*
		 *	Returns:
		 *	The value of the read byte, or S3E_FILE_EOF if at the end of the file. If S3E_FILE_EOF is returned, call s3eFileGetError() to retrieve the error code. This will return one of:
		 *		S3E_FILE_ERR_PARAM if file is an invalid handle.
		 *		S3E_FILE_ERR_EOF if the end of the file was reached.
		 *		S3E_FILE_ERR_DATA if the underlying file device failed to read data.
		 */

		int charRead = s3eFileGetChar(m_file);

		if(charRead == S3E_FILE_EOF)
		{
			s3eFileError fileError = s3eFileGetError();
			// #FIXME
		}
#else
		int charRead = fgetc(m_file);
#endif
		return charRead;
	}

	void putChar(char c)
	{
		if(m_file == NULL)
			return;
#ifdef FG_USING_MARMALADE
		s3eFilePutChar(c, m_file);
#else
		fputc(c, m_file);
#endif
	}

	int getSize(void)
	{
		if(m_file == NULL)
			return -1;
#ifdef FG_USING_MARMALADE
		return s3eFileGetSize(m_file);
#else
		return -1; // FIXME
#endif
	}

	int getPosition(void)
	{
		if(m_file == NULL)
			return -1;

#ifdef FG_USING_MARMALADE
		return s3eFileTell(m_file);
#else
		return ftell(m_file);
#endif
	}

};

#endif