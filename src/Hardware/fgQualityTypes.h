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

enum fgQuality {
	FG_QUALITY_UNIVERSAL=-1,
	FG_QUALITY_LOW		= 0,
	FG_QUALITY_MEDIUM	= 1,
	FG_QUALITY_HIGH		= 2,
	FG_QUALITY_EXTRA	= 3
};

#define FG_QUALITY_UNIVERSAL_NAME	"universal"
#define FG_QUALITY_LOW_NAME			"low"
#define FG_QUALITY_MEDIUM_NAME		"medium"
#define FG_QUALITY_HIGH_NAME		"high"
#define FG_QUALITY_EXTRA_NAME		"extra"

inline fgQuality _FG_QUALITY_FROM_NAME(const char* name) {
	if(!name)
		return FG_QUALITY_UNIVERSAL;
	if(strnicmp(name, FG_QUALITY_UNIVERSAL_NAME, strlen(FG_QUALITY_UNIVERSAL_NAME)) == 0) {
		return FG_QUALITY_UNIVERSAL;
	} else if(strnicmp(name, FG_QUALITY_LOW_NAME, strlen(FG_QUALITY_LOW_NAME)) == 0) {
		return FG_QUALITY_LOW;
	} else if(strnicmp(name, FG_QUALITY_MEDIUM_NAME, strlen(FG_QUALITY_MEDIUM_NAME)) == 0) {
		return FG_QUALITY_MEDIUM;
	} else if(strnicmp(name, FG_QUALITY_HIGH_NAME, strlen(FG_QUALITY_HIGH_NAME)) == 0) {
		return FG_QUALITY_HIGH;
	} else if(strnicmp(name, FG_QUALITY_EXTRA_NAME, strlen(FG_QUALITY_EXTRA_NAME)) == 0) {
		return FG_QUALITY_EXTRA;
	}
	return FG_QUALITY_UNIVERSAL;
}

#define FG_QUALITY_FROM_NAME(name) _FG_QUALITY_FROM_NAME(name)

#endif /* _FG_QUALITY_TYPES_H_ */
