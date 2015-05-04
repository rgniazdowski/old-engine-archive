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
 * File:   fgWindowsStd.h
 * Author: vigilant
 *
 * Created on May 4, 2015, 2:25 PM
 */

#ifndef FG_INC_WINDOWS_STD
    #define FG_INC_WINDOWS_STD
    #define FG_INC_WINDOWS_STD_BLOCK

    #if (defined __WINDOWS__ || defined __WIN32__ || defined _WIN32 || defined _WIN64 || defined __TOS_WIN__ || defined WIN32 || defined win32)
        #define WIN32_LEAN_AND_MEAN
        #define STRICT
        #ifndef UNICODE
            #define UNICODE 1
        #endif
        #undef _WIN32_WINNT
        #define _WIN32_WINNT  0x501   /* Need 0x410 for AlphaBlend() and 0x500 for EnumDisplayDevices(), 0x501 for raw input */


        #include <windows.h>

    #endif

    #undef FG_INC_WINDOWS_STD_BLOCK
#endif	/* FG_INC_WINDOWS_STD */
