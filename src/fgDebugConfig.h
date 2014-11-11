/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgDebugConfig.h
 * Author: vigilant
 *
 * Created on November 11, 2014, 11:06 AM
 */

#ifndef _FG_DEBUG_CONFIG_H_
    #define _FG_DEBUG_CONFIG_H_
    #define _FG_DEBUG_CONFIG_H_BLOCK_

    #if !defined(_FG_BUILD_CONFIG_H_) && !defined(_FG_BUILD_CONFIG_H_BLOCK_)
        #include "fgBuildConfig.h"
    #endif

struct fgDebugConfig {
    #if !defined(FG_DEBUG)
    // When not in Debug mode, this will be a union
    // No data here will be any good on release build
    union {
    #endif
        bool isDebug;           // Is debug build active?
        bool isVerbose;         // Is there some verbosity active?
        int verboseLevel;       // The exact verbosity level
        bool guiBBoxShow;       // Whether to show bounding boxes debug info (GUI)
        bool gfxBBoxShow;       // Whether to show bounding boxes in GFX?
        bool gfxFrustumShow;    // Whether to show frustum boxes?
        bool gfxLightShow;      // Whether to show light sources?
        bool gfxDumpConfig;     // If true, this will dump available configs in EGL
        bool gfxDumpDisplay;    // If true, this will dump available display resolutions
        bool labelsShow;        // Whether to show labels (any kind)
        bool dumpConfig;        // Dump configs on load?
        bool forceFullscreen;   // Is fullscreen forced?
        int empty;
    #if !defined(FG_DEBUG)
    };
    #endif
};

extern struct fgDebugConfig g_fgDebugConfig;

    #undef FG_DEBUG_CONFIG_H_BLOCK_
#endif	/* _FG_DEBUG_CONFIG_H_ */

