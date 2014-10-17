/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgGFXAttribBits.h
 * Author: vigilant
 *
 * Created on October 17, 2014, 12:32 PM
 */

#ifndef _FG_GFX_ATTRIB_BITS_H_
    #define	_FG_GFX_ATTRIB_BITS_H_

    #ifndef FG_GFX_ATTRIB_POS_LOCATION
        #define FG_GFX_ATTRIB_POS_LOCATION          0
    #endif

    #ifndef FG_GFX_ATTRIB_NORM_LOCATION
        #define FG_GFX_ATTRIB_NORM_LOCATION         1
    #endif

    #ifndef FG_GFX_ATTRIB_UVS_LOCATION
        #define FG_GFX_ATTRIB_UVS_LOCATION          2
    #endif

    #ifndef FG_GFX_ATTRIB_COLOR_LOCATION
        #define FG_GFX_ATTRIB_COLOR_LOCATION        3
    #endif

    #ifndef FG_GFX_ATTRIB_TANGENT_LOCATION
        #define FG_GFX_ATTRIB_TANGENT_LOCATION      4
    #endif

    #ifndef FG_GFX_POSITION_BIT
        #define FG_GFX_POSITION_BIT		0x0001
    #endif

    #ifndef FG_GFX_NORMAL_BIT
        #define FG_GFX_NORMAL_BIT		0x0002
    #endif 

    #ifndef FG_GFX_UVS_BIT
        #define FG_GFX_UVS_BIT                 0x0004
    #endif 

    #ifndef FG_GFX_COLOR_BIT
        #define FG_GFX_COLOR_BIT               0x0008
    #endif 

    #ifndef FG_GFX_TANGENT_BIT
        #define FG_GFX_TANGENT_BIT             0x0020
    #endif 

#endif	/* _FG_GFX_ATTRIB_BITS_H_ */

