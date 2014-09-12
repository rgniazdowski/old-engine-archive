/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_PATH_H_
#define _FG_PATH_H_

#include "fgBool.h"
#include <string>

class fgPath
{
protected:
	fgPath() {}
	~fgPath() {}
public:
	// Return the file extension //fgPath::fileExt
	static const char* fileExt(const char *path, fgBool fullExt = FG_FALSE);

	// Return the file name in path //fgPath::fileName
	static const char* fileName(const char* path);

	// Retrieve the dirname in path - this will change the input string
	static void dirName(char* path);

	// Remember that this function allocates a new string
	static char *dirName(const char* path);

	static std::string dirName(std::string & path);

};

#endif /* _FG_PATH_H_ */
