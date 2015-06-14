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
    #define FG_INC_QUALITY_TYPES_BLOCK

    #include <cstring>

namespace fg {

    /**
     *
     */
    enum class Quality : char {
        ///
        UNIVERSAL = (char)-1,
        ///
        LOW = 0,
        ///
        MEDIUM = 1,
        ///
        HIGH = 2,
        ///
        EXTRA = 3,
        ///
        ULTRA = 4,
        ///
        REALITY = 5
    };
    /**
     * Convert text (literal) to corresponding enum value
     * @param text
     * @return
     */
    inline Quality getQualityFromText(const char* text) {
        Quality quality = Quality::UNIVERSAL;
        if(!text) {
            return quality;
        }
        const unsigned int n = strlen(text);

        if(n == 9 && strncasecmp(text, "universal", 9) == 0) {
            quality = Quality::UNIVERSAL;
        } else if(n == 3 && strncasecmp(text, "low", 3) == 0) {
            quality = Quality::LOW;
        } else if(n == 6 && strncasecmp(text, "medium", 6) == 0) {
            quality = Quality::MEDIUM;
        } else if(n == 4 && strncasecmp(text, "high", 4) == 0) {
            quality = Quality::HIGH;
        } else if(n == 5 && strncasecmp(text, "extra", 5) == 0) {
            quality = Quality::EXTRA;
        } else if(n == 5 && strncasecmp(text, "ultra", 5) == 0) {
            quality = Quality::ULTRA;
        } else if(n == 7 && strncasecmp(text, "reality", 7) == 0) {
            quality = Quality::REALITY;
        }
        return quality;
    }
    /**
     * 
     * @param quality
     * @return
     */
    inline const char* getQualityName(Quality quality) {
        const char* returnText = "universal";
        switch(quality) {
            case Quality::LOW:
                returnText = "low";
                break;
            case Quality::MEDIUM:
                returnText = "medium";
                break;
            case Quality::HIGH:
                returnText = "high";
                break;
            case Quality::EXTRA:
                returnText = "extra";
                break;
            case Quality::ULTRA:
                returnText = "ultra";
                break;
            case Quality::REALITY:
                returnText = "reality";
                break;
            default:
                break;
        }
        return returnText;
    }
}

    #undef FG_INC_QUALITY_TYPES_BLOCK
#endif /* FG_INC_QUALITY_TYPES */
