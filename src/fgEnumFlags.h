/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/* 
 * File:   fgEnumFlags.h
 * Author: vigilant
 *
 * Created on September 18, 2015, 11:10 PM
 */

#ifndef FG_INC_ENUM_FLAGS
    #define FG_INC_ENUM_FLAGS

    #define FG_ENUM_FLAGS(Type) \
inline bool operator !(Type x) { return static_cast<int>(x) == 0; } \
inline bool operator &&(Type x, Type y) { return static_cast<bool>(static_cast<int>(x) && static_cast<int>(y)); } \
inline bool operator ||(Type x, Type y) { return static_cast<bool>(static_cast<int>(x) || static_cast<int>(y)); } \
inline bool operator ||(bool x, Type y) { return static_cast<bool>(static_cast<int>(x) || static_cast<int>(y)); } \
inline bool operator ||(Type x, bool y) { return static_cast<bool>(static_cast<int>(x) || static_cast<int>(y)); } \
inline Type	operator	& (Type x, Type y) { return static_cast<Type>(static_cast<int>(x) & static_cast<int>(y));	} \
inline Type	operator	| (Type x, Type y) { return static_cast<Type>(static_cast<int>(x) | static_cast<int>(y));	} \
inline Type	operator	^ (Type x, Type y) { return static_cast<Type>(static_cast<int>(x) ^ static_cast<int>(y));	} \
inline Type	operator	~ (Type x)	{ return static_cast<Type>(~static_cast<int>(x));	} \
inline Type& operator	&= (Type& x, Type y)	{ x = x & y; return x; } \
inline Type& operator	|= (Type& x, Type y)	{ x = x | y; return x; } \
inline Type& operator	^= (Type& x, Type y)	{ x = x ^ y; return x; }

#endif	/* FG_INC_ENUM_FLAGS */
