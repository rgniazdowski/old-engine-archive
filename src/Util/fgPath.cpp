/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgPath.h"
#include "fgCommon.h"

/*
 *
 */
const char *FG_FileExt(const char *path, fgBool fullExt) {
	if(!path) return NULL;
	path = FG_Filename(path);
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
const char* FG_Filename (const char* path)
{
	if(!path)
		return NULL;
	return (strrchr(path, '/') ? strrchr(path, '/') + 1 : strrchr(path, '\\') ? strrchr(path, '\\') + 1 : path);
}
