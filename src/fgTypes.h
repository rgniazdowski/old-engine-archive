/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_TYPES_H_
#define _FG_TYPES_H_

#include "fgBuildConfig.h"
#include "fgBool.h"

#include <cstring>

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
#define FG_TEXT(ENUM) ENUM ## _TEXT

// This enum is used to return (exit function) specific value if variable 'text' is equal to 'checkStr'
#define FG_RETURN_VAL_IF_TEXT_EQ(checkStr, returnVal) \
	do { if(strncasecmp(text, checkStr, strlen(checkStr)) == 0) return returnVal; } while(0)

// This is similar to the macro above, but is more automatic.
// As a parameter it needs to get some enum value (not by variable however)
// Macro uses concatenation (token pasting) to get to strings (literals)
// stored in (enum name)_TEXT global constants - this how comparison is made
#define FG_RETURN_ENUM_IF_TEXT_EQ(returnVal) \
	do { if(strncasecmp(text, returnVal ## _TEXT, strlen(returnVal ## _TEXT)) == 0) return returnVal; } while(0)

// Simple if for checking string against enum equivalent
#define FG_ENUM_IF_TEXT_EQ(ENUM) \
	if(strncasecmp(text, ENUM ## _TEXT, strlen(ENUM ## _TEXT)) == 0)

#define FG_RETURN_VAL_IF_EQUAL(varToCheck, valueToCheck, returnVal) \
	do { if(varToCheck == valueToCheck ) return returnVal; } while(0)

// Convert text (literal) to corresponding enum value
inline fgBool _FG_BOOL_FROM_TEXT(const char* text) {
	if(!text)
		return FG_BOOL_INVALID;
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_TRUE);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_FALSE);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_SUCCESS);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_WARNING);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_ERROR);
	return FG_BOOL_INVALID;
}

inline const char * _FG_BOOL_TO_TEXT(fgBool value) {
	FG_RETURN_VAL_IF_EQUAL(value, FG_TRUE, FG_TEXT(FG_TRUE));
	FG_RETURN_VAL_IF_EQUAL(value, FG_FALSE, FG_TEXT(FG_FALSE));
	FG_RETURN_VAL_IF_EQUAL(value, FG_WARNING, FG_TEXT(FG_WARNING));
	return NULL;
}

#define FG_BOOL_FROM_TEXT(text) _FG_BOOL_FROM_TEXT(text)
#define FG_BOOL_TO_TEXT(value) _FG_BOOL_TO_TEXT(value)

#define FG_ENUM_FLAGS(Type) \
inline Type	operator	& (Type x, Type y)		{	return static_cast<Type>	(static_cast<int>(x) & static_cast<int>(y));	} \
inline Type	operator	| (Type x, Type y)		{	return static_cast<Type>	(static_cast<int>(x) | static_cast<int>(y));	} \
inline Type	operator	^ (Type x, Type y)		{	return static_cast<Type>	(static_cast<int>(x) ^ static_cast<int>(y));	} \
inline Type	operator	~ (Type x)			{	return static_cast<Type>	(~static_cast<int>(x));	} \
inline Type& operator	&= (Type& x, Type y)		{	x = x & y;	return x;	} \
inline Type& operator	|= (Type& x, Type y)		{	x = x | y;	return x;	} \
inline Type& operator	^= (Type& x, Type y)		{	x = x ^ y;	return x;	}

#include "fgArrayVector.h"

#endif /* _FG_TYPES_H_ */
