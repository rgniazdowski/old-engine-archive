/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
 *******************************************************/

#include "fgFileStream.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>

/*
 * #TODO - Need to add error handling and proper calls for non-marmalade version of the code
 */

/*
 *
 */
bool fgFileStream::openFile(const char *filePath, const char *mode)
{
	if(m_file != NULL || mode == NULL || filePath == NULL)
		return false;

	if(strlen(filePath) <= 1)
		return false;

	if(!fileExists(filePath)) {
		return false;
	}

	strncpy(m_filePath, filePath, FG_FILE_PATH_MAX-1);

	// FIXME need to manage the errors and messages
#ifdef FG_USING_MARMALADE
	m_file = s3eFileOpen(filePath, mode);
#else
	m_file = fopen(filePath, mode);
#endif

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
#ifdef FG_USING_MARMALADE
		s3eFileClose(m_file);
#else
		fclose(m_file);
#endif
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

	/*
	 *	Returns:
	 *	The full number of items actually read (same caveats as fread). The total number of bytes read is (elemSize * noElems).
	 *	If the number of items read is less than noElems, an error code is set. Call s3eFileGetError() to retrieve the error code. This will return one of:
	 *		S3E_FILE_ERR_PARAM buffer is NULL or file is invalid.
	 *		S3E_FILE_ERR_DATA if the underlying file device failed to read in data.
	 *		S3E_FILE_ERR_EOF if the end of the file was reached before all the data could be read in.
	 */
#ifdef FG_USING_MARMALADE
	unsigned int elemRead = s3eFileRead(buffer, elemsize, elemcount, m_file);
#else
	unsigned int elemRead = (unsigned int)fread(buffer, elemsize, elemcount, m_file);
#endif

	if(elemRead != elemcount)
	{
#ifdef FG_USING_MARMALADE
		s3eFileError fileError = s3eFileGetError();
#else
		// Non marmalade code here
#endif
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

	/*
	 *	string if the function read any data, NULL if a read error or end-of-file occurred before data could be read. 
	 *	If the result is NULL, call s3eFileGetError() to retrieve the error code. This will return one of:
	 *		S3E_FILE_ERR_PARAM if string is NULL or file is invalid.
	 *		S3E_FILE_ERR_DATA if the underlying file device failed to read in data.
	 *		S3E_FILE_ERR_EOF if the end of the file was reached before all the data could be read in.
	 */
#ifdef FG_USING_MARMALADE
	char *retString = s3eFileReadString(buffer, maxlen, m_file);
#else
	char *retString = fgets(buffer, maxlen, m_file);
#endif
	if(retString == NULL)
	{
#ifdef FG_USING_MARMALADE
		s3eFileError fileError = s3eFileGetError();
#else
		// Non marmalade code here
#endif
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

#ifdef FG_USING_MARMALADE
	int charsCount = s3eFilePrintf(m_file, buf);
#else
	int charsCount = fprintf(m_file, buf);
#endif

	return charsCount;
}

/*
 *
 */
int fgFileStream::writeFile(void *buffer, unsigned int elemsize, unsigned int elemcount)
{
	if(m_file == NULL || buffer == NULL || elemsize == 0 || elemcount == 0)
		return -1;

	/*
	 *	Returns:
	 *	The full number of items actually written (same caveats as fwrite). The total number of bytes written is (elemSize * noElems). If the number of items written is less than noElems, an error code is set. Call s3eFileGetError() to retrieve the error code. This will return one of:
	 *		S3E_FILE_ERR_PARAM buffer is NULL or file is invalid.
	 *		S3E_FILE_ERR_DATA if the underlying file device failed to write the data or an attempt was made to write beyond the end of a memory file's buffer.
	 *		S3E_FILE_ERR_UNSUPPORTED if file is a file opened from a user filesystem and the user filesystem's m_Write function is NULL.
	 */
#ifdef FG_USING_MARMALADE
	unsigned int elemWritten = s3eFileWrite(buffer, elemsize, elemcount, m_file);
#else
	unsigned int elemWritten = (unsigned int) fwrite(buffer, elemsize, elemcount, m_file);
#endif

	if(elemWritten != elemcount)
	{
#ifdef FG_USING_MARMALADE
		s3eFileError fileError = s3eFileGetError();
#else
#endif
		//FIXME
	}

	return elemWritten;
}

