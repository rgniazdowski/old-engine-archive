/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of #FLEXIGAME_PROJECT
 *
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_COMMON_H_
#define _FG_COMMON_H_

// Global include needed (it defines the parameters of the build)
#include "fgBuildConfig.h"

#include <cstdlib>
#include <cstring>
#include <string>

#define FG_FILE_NAME_MAX	256
#define FG_PATH_MAX			256
#define FG_INVALID			-1

#ifndef MAX
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifdef _MSC_VER
#pragma warning(disable : 4244)
#endif

#include "fgTypes.h"

#ifndef FG_PTR_LESS_DEFINED_
#define FG_PTR_LESS_DEFINED_
// This class allows an STL object to compare the objects instead of
// comparing the value of the objects' pointers.
template <class T>
class fgPtrLess
{
public:
	inline bool operator ()(T left, T right)
	{  return ((*left) < (*right));  }
};
#endif /* FG_PTR_LESS_DEFINED_ */

#ifndef FG_PTR_GREATER_DEFINED_
#define FG_PTR_GREATER_DEFINED_
// This class allows an STL object to compare the objects instead of
// comparing the value of the objects' pointers.
template <class T>
class fgPtrGreater
{
public:
	inline bool operator ()(T left, T right)
	{  return !((*left) < (*right));  }
};
#endif /* FG_PTR_GREATER_DEFINED_ */

/**
 * Random int from [a,b]
 */
inline int FG_Rand(int a, int b) {
	return a +(int)(((float)(b-a+1))*rand()/(float(RAND_MAX)+1.0f));
}

#endif /* _FG_COMMON_H_ */
