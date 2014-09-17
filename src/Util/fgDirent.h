/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_DIRENT_H_
#define _FG_DIRENT_H_

#include "fgCommon.h"

#ifdef FG_USING_MARMALADE
#include "s3eFile.h"
#else
#include <cstdio>
#include <dirent.h>
#endif

// #TODO - need to decide should I use everywhere stl string,
// standard char array or my own wrapper - time will show 
// which will be more crossplatform friendly
#include <string>

/* WINDOWS/LINUX solution using dirent.h 
DIR *dir;
struct dirent *ent;
if ((dir = opendir ("c:\\src\\")) != NULL) {
  // print all the files and directories within directory
  while ((ent = readdir (dir)) != NULL) {
    printf ("%s\n", ent->d_name);
  }
  closedir (dir);
} else {
  // could not open directory
  perror ("");
  return EXIT_FAILURE;
}
*/

/*
 * Simple class for reading directory contents
 * uses dirent.h which is available for linux and windows
 * Initial version just outputs file names - in the future
 * there will be a specialized structure with all the possible
 * info (like from stat for example)...
 */
class fgDirent
{
public:
	// Default empty constructor
	fgDirent()
	{
#ifdef FG_USING_MARMALADE
		m_fileList = NULL;
#else
		m_curDir = NULL;
		m_curEntry = NULL;
#endif
		m_dirPath.clear();
		m_fileNames.clear_optimised();
		m_fileIt = m_fileNames.end();
	}
	// Default constructor with the specified directory path
	// Please note that this constructor will also call the
	// read directory function.
	fgDirent(const char *dirPath);
	fgDirent(std::string &dirPath);

	// The default deconstructor
	~fgDirent()
	{
#ifdef FG_USING_MARMALADE
	// ?
#else
	// ?
#endif
		m_dirPath.clear();
		m_fileNames.clear_optimised();
	}

	// Reads the directory that was specified earlier
	fgBool readDirectory(void);
	// Reads the specified directory creating the list of files
	// to be processed later
	fgBool readDirectory(const char *dirPath);
	// Reads the specified directory creating the list of files
	// to be processed later
	fgBool readDirectory(std::string &dirPath);

	// Returns the next file name
	const char *getNextFile(void);
	// This function rewinds to the beginning the file pointer (in the list)
	fgBool rewind(void);
protected:
	// The whole path to the directory
	std::string m_dirPath;
	// List/vector with the file names in the specified directory #FIXME
	fgVector<std::string> m_fileNames;
	fgVector<std::string>::iterator m_fileIt;
#ifdef FG_USING_MARMALADE
	// Marmalade specific structure for reading directory contents
	s3eFileList *m_fileList;
#else
	DIR *m_curDir;
	struct dirent *m_curEntry;
#endif
};

#endif