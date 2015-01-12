/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_FONT_STB_TIMES
    #define FG_INC_FONT_STB_TIMES
    #define FG_INC_FONT_STB_TIMES_BLOCK

    #ifndef FG_INC_FONT_BUILT_IN_TYPES
        #include "fgFontBuiltInTypes.h"
    #endif

    #ifndef FG_STB_FONT_PTR
        #define FG_STB_FONT_PTR(_font_name, _param) stb__ ## _font_name ## _usascii_ ## _param
    #endif

    #ifndef FG_STB_FONT_CONST
        #define FG_STB_FONT_CONST(_font_name, _const_name) STB_FONT_ ## _font_name ## _usascii_ ## _const_name
    #endif

namespace fg {
    namespace gui {
        namespace font {

            class StbTimes {
            public:
                /**
                 * 
                 * @param size
                 * @return 
                 */
                static SFontBuiltInRawData* getRawData(const int size = 50);

            private:
                ///
                static SFontBuiltInRawData m_stbFontRawData;
                ///
                StbTimes() { }
                ///
                ~StbTimes() { }
            };
        };
    };
};

    #undef FG_INC_FONT_STB_TIMES_BLOCK
#endif /* FG_INC_FONT_STB_TIMES */
