/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_QUALITY_TYPES
    #define FG_INC_QUALITY_TYPES

    #include "fgCommon.h"

// Enums for specifing quality

enum fgQuality {
    FG_QUALITY_UNIVERSAL = -1,
    FG_QUALITY_LOW = 0,
    FG_QUALITY_MEDIUM = 1,
    FG_QUALITY_HIGH = 2,
    FG_QUALITY_EXTRA = 3
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
inline fgQuality FG_INC_QUALITY_FROM_TEXT(const char* text) {
    if(!text)
        return FG_QUALITY_UNIVERSAL;
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_QUALITY_UNIVERSAL);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_QUALITY_LOW);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_QUALITY_MEDIUM);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_QUALITY_HIGH);
    FG_RETURN_ENUM_IF_TEXT_EQ(FG_QUALITY_EXTRA);
    return FG_QUALITY_UNIVERSAL;
}
// #FIXME - #P3 - string obfuscation (also for error code -> text msg translations)
    #define FG_QUALITY_FROM_TEXT(text) FG_INC_QUALITY_FROM_TEXT(text)

#endif /* FG_INC_QUALITY_TYPES */
