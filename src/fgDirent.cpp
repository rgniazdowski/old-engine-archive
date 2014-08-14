/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgDirent.h"

/*
 * Default constructor with the specified directory path
 * Please note that this constructor will also call the
 * read directory function.
 */
fgDirent::fgDirent(const char *dirPath)
{
	m_dirPath.clear();
	m_dirPath.assign(dirPath);
	readDirectory();
}

/*
 * Reads the directory content creating a list
 * with file names in it
 */
fgBool fgDirent::readDirectory(void)
{
#ifdef FG_USING_MARMALADE
	m_fileList = NULL;
#else
	m_curDir = NULL;
	m_curEntry = NULL;
#endif
	m_fileNames.clear_optimised();

#ifdef FG_USING_MARMALADE
	char fileName[FG_FILE_NAME_MAX];
	// #FIXME there are known some issues with this function
	// there are differences between simulator behavior and on device behavior
	m_fileList = s3eFileListDirectory(m_dirPath.c_str());
	if (m_fileList)
	{
		while (S3E_RESULT_SUCCESS == s3eFileListNext(m_fileList, fileName, FG_FILE_NAME_MAX-1))
			m_fileNames.push_back(std::string(fileName));
		s3eFileListClose(m_fileList);
		rewind();
		return FG_TRUE;
	}
	//return s3eFileGetError();
#else
	if ((m_curDir = opendir (m_dirPath.c_str())) != NULL) {
		// put in the list every file in the specified directory
		while ((m_curEntry = readdir (m_curDir)) != NULL) {
			printf ("%s\n", m_curEntry->d_name);
			m_fileNames.push_back(std::string(m_curEntry->d_name));
		}
		closedir (m_curDir);
		rewind();
		return FG_TRUE;
	} else {
		// could not open directory
		//perror ("");
		//return EXIT_FAILURE;
		// #TODO proper error handling
		return FG_FALSE;
	}
#endif
	return FG_FALSE;
}

/*
 * Reads the specified directory content creating
 * a list of file names
 */
fgBool fgDirent::readDirectory(const char *dirPath)
{
	m_dirPath.clear();
	m_dirPath.assign(dirPath);
	return readDirectory();
}

/*
 * Return the next file name
 */
const char *fgDirent::getNextFile(void)
{
	if(m_fileIt == m_fileNames.end())
	{
		m_fileIt = m_fileNames.begin();
		if(m_fileIt != m_fileNames.end())
			return (*m_fileIt).c_str();
		return NULL;
	}
	m_fileIt++;
	if(m_fileIt == m_fileNames.end())
		return NULL;

	return (*m_fileIt).c_str();
}

/*
 * This function rewinds to the beginning the file pointer (in the list)
 */
fgBool fgDirent::rewind(void)
{
	m_fileIt = m_fileNames.end();
	if(!m_fileNames.size())
		return FG_FALSE;
	return FG_TRUE;
}
