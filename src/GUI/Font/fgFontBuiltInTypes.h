/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_FONT_BUILT_IN_TYPES
    #define FG_INC_FONT_BUILT_IN_TYPES
    #define FG_INC_FONT_BUILT_IN_TYPES_BLOCK

    #ifndef NULL
        #ifndef __cplusplus
            #define NULL ((void *)0)
        #else
            #define NULL 0
        #endif
    #endif

    #include "Util/fgMemory.h"
    #include "Math/fgMathLib.h"
    #include <string>

namespace fg {
    namespace gui {

        /**
         *
         */
        struct SFontBuiltInRawData {
            /// Name of the font - used in resource
            std::string name;
            /// X position data
            signed short *xPtr;
            /// X position data
            signed short *yPtr;
            /// X size data
            unsigned short *wPtr;
            /// Y size data
            unsigned short *hPtr;
            /// Texture coord data
            unsigned short *sPtr;
            /// Texture coord data
            unsigned short *tPtr;
            /// Advance/step data
            unsigned short *aPtr;
            /// Pixel raw data
            unsigned int *bitsPtr;
            /// Data width
            unsigned int width;
            /// Data height
            unsigned int height;
            /// Height POW2
            unsigned int heightPOW2;
            /// Offset of the first character in data
            unsigned int firstChar;
            /// Number of characters in data
            unsigned int numChars;
            /**
             * 
             */
            SFontBuiltInRawData() :
            name(),
            xPtr(NULL),
            yPtr(NULL),
            wPtr(NULL),
            hPtr(NULL),
            sPtr(NULL),
            tPtr(NULL),
            aPtr(NULL),
            bitsPtr(NULL),
            width(0),
            height(0),
            heightPOW2(0),
            firstChar(0),
            numChars(0) { }
        };

        /*
         *
         */
        struct SFontCharInfo {
            // coordinates if using floating positioning
            Vec2f uv1f;
            Vec2f uv2f;
            Vec2f p0f;
            Vec2f p1f;
            float stepf;

            // coordinates if using integer positioning
            Vec2f uv1i;
            Vec2f uv2i;
            Vec2i p0i;
            Vec2i p1i;
            int stepi;
        };

        /*
         *
         */
        struct SFontDataInfo {
            ///
            SFontCharInfo *charInfo;
            ///
            unsigned int firstChar;
            ///
            unsigned int numChars;
            /**
             * 
             */
            SFontDataInfo() :
            charInfo(NULL),
            firstChar(0),
            numChars(0) { }
            /**
             * 
             */
            void destroy(void) {
                if(charInfo) {
                    fgFree(charInfo);
                }
                charInfo = NULL;
                numChars = 0;
                firstChar = 0;
            }
        };
    };
};

    #undef FG_INC_FONT_BUILT_IN_TYPES_BLOCK
#endif /* FG_INC_FONT_BUILT_IN_TYPES */
