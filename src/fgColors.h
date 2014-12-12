/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgColors.h
 * Author: vigilant
 *
 * Created on October 20, 2014, 4:25 PM
 */

#ifndef FG_INC_COLORS
    #define	FG_INC_COLORS

    #ifndef FG_INC_GFX_COLOR
        #include "GFX/fgGFXColor.h"
    #endif
    
    #include "fgBool.h"

    #include <string>
/**
 * 
 */
class fgColors {
private:
    /**
     * 
     */
    fgColors();
    /**
     * 
     */
    virtual ~fgColors();
    
public:
    
    /**
     * 
     */
    static void initialize(void);
    
    /**
     * 
     */
    static void freeColors(void);
    
    /**
     * 
     * @param name
     * @return 
     */
    static fgColor4f getColorFromName(const char *name);
    /**
     * 
     * @param name
     * @return 
     */
    static fgColor4f getColorFromName(const std::string& name);
    /**
     * 
     * @param value
     * @return 
     */
    static fgColor4f parseHEX(const char *value);
    /**
     * 
     * @param value
     * @return 
     */
    static fgColor4f parseHEX(const std::string& value);
    /**
     * 
     * @param value
     * @param comp
     * @return 
     */
    static fgColor4f parseHEX(unsigned long int value, const unsigned char comp = 4);
    
private:
    /// Are color tables initialized?
    static fgBool s_isInit;
};

#endif	/* FG_INC_COLORS */

