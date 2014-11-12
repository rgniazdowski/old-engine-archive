/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/* 
 * File:   fgDebugConfig.cpp
 * Author: vigilant
 * 
 * Created on November 11, 2014, 11:06 AM
 */

#include "fgDebugConfig.h"

struct fgDebugConfig g_fgDebugConfig = {
#ifndef FG_DEBUG
    false
#else
    true,
#ifdef FG_VERBOSE
    true,
#else
    false,
#endif
#ifdef FG_VERBOSE_LEVEL
    FG_VERBOSE_LEVEL,
#else
    0,
#endif
    false, //guiBBoxShow;       // Whether to show bounding boxes debug info (GUI)
    false, //gfxBBoxShow;       // Whether to show bounding boxes in GFX?
    false, //gfxFrustumShow;    // Whether to show frustum boxes?
    false, //gfxLightShow;      // Whether to show light sources?
    false, //gfxDumpConfig;     // If true, this will dump available configs in EGL
    false, //gfxDumpDisplay;    // If true, this will dump available display resolutions
    false, //labelsShow;        // Whether to show labels (any kind)
    false, //dumpConfig;        // Dump configs on load?
    false, //forceFullscreen;   // Is fullscreen forced?
    0 //empty;
#endif /* FG_DEBUG */
};
