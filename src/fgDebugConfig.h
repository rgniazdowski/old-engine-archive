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
 * File:   fgDebugConfig.h
 * Author: vigilant
 *
 * Created on November 11, 2014, 11:06 AM
 */

#ifndef FG_INC_DEBUG_CONFIG
    #define FG_INC_DEBUG_CONFIG
    #define FG_INC_DEBUG_CONFIG_BLOCK

    #if !defined(FG_INC_BUILD_CONFIG) && !defined(FG_INC_BUILD_CONFIG_BLOCK)
        #include "fgBuildConfig.h"
    #endif

namespace fg {

    struct SDebugConfig {
        const bool isDebug; // Is debug build active?
        const bool isVerbose; // Is there some verbosity active?
        int verboseLevel; // The exact verbosity level
        bool physicsBBoxShow; // Whether to show bounding boxes debug info for physics simulation
        bool guiBBoxShow; // Whether to show bounding boxes debug info (GUI)
        bool gfxBBoxShow; // Whether to show bounding boxes in GFX?
        bool gfxSphereShow; // Whether to show bounding spheres in GFX?
        bool gfxTreeBBoxShow; // Whether to show bounding boxes of spatial trees in GFX?
        bool gfxFrustumShow; // Whether to show frustum boxes?
        bool gfxLightShow; // Whether to show light sources?
        bool gfxDumpConfig; // If true, this will dump available configs in EGL
        bool gfxDumpDisplay; // If true, this will dump available display resolutions
        bool gfxDumpShaders; // If true, this will dump every compiled shader (source)
        bool gameFreeLook; // If true, the free look camera and flying is active (like noclip)
        bool labelsShow; // Whether to show labels (any kind)
        bool dumpConfig; // Dump configs on load?
        bool forceFullscreen; // Is fullscreen forced?
        bool isDebugProfiling; // Is debug profiling enabled?
        bool consoleShow; // Is special console being displayed?
        const int empty;
    };

    extern struct SDebugConfig g_DebugConfig;

}

    #if defined(FG_DEBUG)
        #define FG_DEBUG_CFG_OPTION(_OPTION) ( ::fg::g_DebugConfig._OPTION )
    #else
        #define FG_DEBUG_CFG_OPTION(_OPTION) (false)
    #endif /* FG_DEBUG */

    #undef FG_DEBUG_CONFIG_BLOCK
#endif	/* FG_INC_DEBUG_CONFIG */

