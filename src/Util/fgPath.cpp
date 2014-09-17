/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgPath.h"
#include "fgCommon.h"
#include "fgMemory.h"

/*
 *
 */
const char *fgPath::fileExt(const char *path, fgBool fullExt) 
{
	if(!path) return NULL;
	path = fgPath::fileName(path);
	const char *dot = NULL;
	if(fullExt == FG_TRUE)
		dot = strchr(path, '.');
	else
		dot = strrchr(path, '.');
    if(!dot || dot == path) return NULL;
    return dot + 1;
}

/*
 *
 */
const char* fgPath::fileName (const char* path)
{
	if(!path)
		return NULL;
	return (strrchr(path, '/') ? strrchr(path, '/') + 1 : strrchr(path, '\\') ? strrchr(path, '\\') + 1 : path);
}

/*
 *
 */
void fgPath::dirName(char *path)
{
	const char* filename = fgPath::fileName(path);
	if(!filename)
		return;
	int npath = strlen(path);
	int nfile = strlen(filename);
	int pos = npath-nfile;
	for(int i=pos;i<npath;i++)
		path[i] = 0;
}

/*
 *
 */
char *fgPath::dirName(const char *path)
{
	const char* filename = fgPath::fileName(path);
	if(!filename)
		return NULL;
	int npath = strlen(path);
	int nfile = strlen(filename);
	int newlen = npath-nfile;
	char *buf = (char *)fgMalloc(sizeof(char) * (newlen+1));
	strncpy(buf, path, newlen);
	buf[newlen] = 0;
	return buf;
}

/*
 *
 */
std::string fgPath::dirName(std::string &path)
{
	const char* filename = fgPath::fileName(path.c_str());
	if(!filename)
		return path;
	return path.substr(0, path.length()-strlen(filename));
}

/*
 *
 */
std::string& fgPath::dirName(std::string &path, std::string &dirpath)
{
	dirpath = dirName(path);
	return dirpath;
}

/*
 *
 */
void fgPath::split(std::string &path, std::string &dirpath, std::string &filename)
{
	dirpath = dirName(path);
	const char* filename_c = fgPath::fileName(path.c_str());
	if(!filename_c)
		filename.clear();
	else
		filename = filename_c;
}

/*
 *
 */
std::string& fgPath::join(std::string &path, std::string &dirpath, std::string &filename)
{
	// path - here is the result stored
	
	int dirlen = (int)dirpath.length();
	int filelen = (int)filename.length();
	path = dirpath;
	if(path[dirlen-1] == FG_PATH_DELIMC || path[dirlen-1] == FG_PATH_DELIM2C)
		path[dirlen-1] = FG_PATH_DELIMC;
	else
		path.append(FG_PATH_DELIM);
	path.append(filename);
	return path;
}

/*
 *
 */
std::string fgPath::join(std::string &dirpath, std::string &filename)
{
	std::string path;
	fgPath::join(path, dirpath, filename);
	return path;
}

/*
 *
 */
void fgPath::join(std::string &path, fgStringVector &parts)
{
}
