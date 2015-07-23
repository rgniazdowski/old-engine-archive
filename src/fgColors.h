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
 * File:   fgColors.h
 * Author: vigilant
 *
 * Created on October 20, 2014, 4:25 PM
 */

#ifndef FG_INC_COLORS
    #define FG_INC_COLORS
    #define FG_INC_COLORS_BLOCK

    #ifndef FG_INC_GFX_COLOR
        #include "GFX/fgGfxColor.h"
    #endif

    #include "fgBool.h"
    #include <string>

namespace fg {

    namespace colors {

        /**
         * 
         */
        void initialize(void);

        /**
         * 
         */
        void freeColors(void);

        /**
         * 
         * @return 
         */
        fgBool isInit(void);
        
        /**
         * 
         * @param name
         * @return 
         */
        Color4f getColor(const char *name);
        /**
         * 
         * @param name
         * @return 
         */
        Color4f getColor(const std::string& name);
        /**
         * 
         * @param value
         * @return 
         */
        Color4f parseHEX(const char *value);
        /**
         * 
         * @param value
         * @return 
         */
        Color4f parseHEX(const std::string& value);
        /**
         * 
         * @param value
         * @param comp
         * @return 
         */
        Color4f parseHEX(unsigned long int value, const unsigned char comp = 4);

    } // namespace colors
} // namespace fg

    #undef FG_INC_COLORS_BLOCK
#endif	/* FG_INC_COLORS */

