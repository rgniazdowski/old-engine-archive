/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_QUALITY_TYPES_H_
#define _FG_QUALITY_TYPES_H_

#include "../fgCommon.h"

// Enums for specifing quality
enum fgQuality {
	FG_QUALITY_UNIVERSAL=-1,
	FG_QUALITY_LOW		= 0,
	FG_QUALITY_MEDIUM	= 1,
	FG_QUALITY_HIGH		= 2,
	FG_QUALITY_EXTRA	= 3
};

// Text (string version) for the universal quality enum
#define FG_QUALITY_UNIVERSAL_TEXT	"universal"
// Text (string version) for the universal quality enum
#define FG_QUALITY_LOW_TEXT			"low"
// Text (string version) for the medium quality enum
#define FG_QUALITY_MEDIUM_TEXT		"medium"
// Text (string version) for the high quality enum
#define FG_QUALITY_HIGH_TEXT		"high"
// Text (string version) for the universal quality enum
#define FG_QUALITY_EXTRA_TEXT		"extra"

// Convert text (literal) to corresponding enum value
inline fgQuality _FG_QUALITY_FROM_TEXT(const char* text) {
	if(!text)
		return FG_QUALITY_UNIVERSAL;
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_QUALITY_UNIVERSAL);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_QUALITY_LOW);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_QUALITY_MEDIUM);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_QUALITY_HIGH);
	FG_RETURN_ENUM_IF_TEXT_EQ(FG_QUALITY_EXTRA);
	return FG_QUALITY_UNIVERSAL;
}

#define FG_QUALITY_FROM_TEXT(text) _FG_QUALITY_FROM_TEXT(text)

#endif /* _FG_QUALITY_TYPES_H_ */
