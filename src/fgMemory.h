/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_MEMORY_H
#define _FG_MEMORY_H

#include "fgBuildConfig.h"

#ifdef FG_USING_MARMALADE

#include "s3eMemory.h"

#define fgMalloc	s3eMalloc
#define fgFree		s3eFree
#define fgRealloc	s3eRealloc

// FIXME need more wrappers for marmalade's heap memory handling

#else

#include <malloc.h>

#define fgMalloc	malloc
#define fgFree		free
#define fgRealloc	realloc

#endif

#endif