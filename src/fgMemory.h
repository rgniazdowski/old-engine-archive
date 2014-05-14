/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
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

#endif


#endif