/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
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

#ifndef _FG_COLORS_H_
    #define	_FG_COLORS_H_

    #ifndef _FG_GFX_COLOR_H_
        #include "GFX/fgGFXColor.h"
    #endif
    
    #include "fgBool.h"

    #include <string>
/**
 * 
 */
class fgColors {
private:
    //
    fgColors();
    //
    virtual ~fgColors();
    
public:
    
    //
    static void initialize(void);
    
    //
    static void freeColors(void);
    
    //
    static fgColor4f getColorFromName(const char *name);
    //
    static fgColor4f getColorFromName(const std::string& name);
    //
    static fgColor4f parseHEX(const char *value);
    //
    static fgColor4f parseHEX(const std::string& value);
    //
    static fgColor4f parseHEX(unsigned long int value, const unsigned char comp = 4);
    
private:
    static fgBool s_isInit;
};

#endif	/* _FG_COLORS_H_ */

