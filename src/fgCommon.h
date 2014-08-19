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

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifdef _MSC_VER
#pragma warning(disable : 4244)
#endif

#ifndef fgBool
typedef unsigned char fgBool;
#endif

#ifndef FG_FALSE
#define FG_FALSE 0
#endif

#ifndef FG_TRUE
#define FG_TRUE 1
#endif

#ifndef FG_SUCCESS
#define FG_SUCCESS 1
#endif

#define FG_SUCCESS_TEXT		"success"
#define FG_TRUE_TEXT		"true"
#define FG_FALSE_TEXT		"false"

#ifndef NULL
    #ifndef __cplusplus
        #define NULL ((void *)0)
    #else
        #define NULL 0
    #endif
#endif

#ifndef FG_NULL
    #ifndef __cplusplus
        #define FG_NULL ((void *)0)
    #else
        #define FG_NULL 0
    #endif
#endif /* FG_NULL */

// Special macros for checking text/string value, in context of converting to enums/ints etc.

// Convert enum to text (can be useful)
#define FG_TEXT_FROM_ENUM(ENUM) ENUM ## _TEXT
// Convert enum to text (can be useful)
#define FG_TEXT FG_TEXT_FROM_ENUM

// This enum is used to return (exit function) specific value if variable 'text' is equal to 'checkStr'
#define FG_RETURN_VAL_IF_TEXT_EQ(checkStr, returnVal) \
	do { if(strnicmp(text, checkStr, strlen(checkStr)) == 0) return returnVal; } while(0)

// This is similar to the macro above, but is more automatic.
// As a parameter it needs to get some enum value (not by variable however)
// Macro uses concatenation (token pasting) to get to strings (literals)
// stored in (enum name)_TEXT global constants - this how comparison is made
#define FG_RETURN_ENUM_IF_TEXT_EQ(returnVal) \
	do { if(strnicmp(text, returnVal ## _TEXT, strlen(returnVal ## _TEXT)) == 0) return returnVal; } while(0)

// Simple if for checking string against enum equivalent
#define FG_ENUM_IF_TEXT_EQ(ENUM) \
	if(strnicmp(text, ENUM ## _TEXT, strlen(ENUM ## _TEXT)) == 0)

// Convert text (literal) to corresponding enum value
inline fgBool _FG_BOOL_FROM_TEXT(const char* text) {
	if(!text)
		return FG_FALSE;
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_TRUE);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_FALSE);
	FG_RETURN_VAL_IF_TEXT_EQ(FG_SUCCESS_TEXT, FG_TRUE);
	return FG_FALSE;
}
#define FG_BOOL_FROM_TEXT(text) _FG_BOOL_FROM_TEXT(text)
#define FG_BOOL FG_BOOL_FROM_TEXT

#define FG_ENUM_FLAGS(Type) \
inline Type	operator	& (Type x, Type y)		{	return static_cast<Type>	(static_cast<int>(x) & static_cast<int>(y));	} \
inline Type	operator	| (Type x, Type y)		{	return static_cast<Type>	(static_cast<int>(x) | static_cast<int>(y));	} \
inline Type	operator	^ (Type x, Type y)		{	return static_cast<Type>	(static_cast<int>(x) ^ static_cast<int>(y));	} \
inline Type	operator	~ (Type x)			{	return static_cast<Type>	(~static_cast<int>(x));	} \
inline Type& operator	&= (Type& x, Type y)		{	x = x & y;	return x;	} \
inline Type& operator	|= (Type& x, Type y)		{	x = x | y;	return x;	} \
inline Type& operator	^= (Type& x, Type y)		{	x = x ^ y;	return x;	}

#if defined FG_USING_MARMALADE
#include "IwUtil.h"
template <class X, class A=CIwAllocator<X>, class REALLOCATE = ReallocateDefault<X, A > >
class fgArrayVector : public CIwArray<X, A, REALLOCATE> {
public:
	X & at(int const i) const {
		uint32 index = (uint32)i;
        if(index >= this->num_p) {
			return this->p[0];
		}
        return this->p[index];
	}
};
#else 
#include <vector>
template <class T, class Alloc = allocator<T> >
class fgArrayVector : public std::vector<T, Alloc> {
public:
	void clear_optimised()
	{
		clear();		
	}
		
	int find(T const & value) const
    {
        for (int i = 0, iterator it = begin(); it != end(); it++, i++) {
			if((*it) == value) {
				return i;
			}
		}
        return -1;
    }

    bool contains(T const & value) const
    {
		for (iterator it = begin(); it != end(); it++) {
			if((*it) == value) {
				return true;
			}
		}
        return false;
    }

};
#endif /* FG_USING_MARMALADE */

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


// #FIXME this should not be in this file, but for now (just to compile the damn code) it'll be here
// #TODO #P2 this class needs modification so it will have the standard of all the fgVector*/fgColor* classes
struct Area
{
		int x;
		int y;
		int w;
		int h;
		Area(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {}
		Area() : x(0), y(0), w(0), h(0) {}

// MARK: Getters

        int left() const {
            return x;
        }

        int right() const {
            return x + w;
        }

        int top() const {
            return y;
        }

        int bottom() const {
            return y + h;
        }

        int width() const {
            return w;
        }

        int height() const {
            return h;
        }

// MARK: Setters

        void set_left(int l) {
            x = l;
        }

        void set_right(int r) {
            w = r - x;
        }

        void set_top(int t) {
            y = t;
        }

        void set_bottom(int b) {
            h = b - y;
        }

        void set_width(int _w) {
            w = _w;
        }

        void set_height(int _h) {
            h = _h;
        }
};


//FIXME
void FG_InfoLog(const char *fmt, ...);
void FG_ErrorLog(const char *fmt, ...);
void FG_WriteLog(const char *fmt, ...);

// Platform independent function for getting time in miliseconds
unsigned long int FG_GetTicks(void);

/**
 * Random int from [a,b]
 */
inline int FG_Rand(int a, int b) {
	return a +(int)(((float)(b-a+1))*rand()/(float(RAND_MAX)+1.0f));
}

inline const char *FG_FileExt(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return NULL;
    return dot + 1;
}

const char* FG_Filename (const char* str);



#endif /* _FG_COMMON_H_ */
