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

// Return the file extension
const char *FG_FileExt(const char *path, fgBool fullExt = FG_FALSE);

// Return the file name in path
const char* FG_Filename(const char* path);

#endif /* _FG_PATH_H_ */
