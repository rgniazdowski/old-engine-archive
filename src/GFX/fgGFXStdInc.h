/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_STD_INC
    #define FG_INC_GFX_STD_INC
    #define FG_INC_GFX_STD_INC_BLOCK__

    #ifdef FG_INC_GFX_TYPES_BLOCK__
        #error "FG_GFX_TYPES_BLOCK constant is defined. Do not include GfxStdInc inside of Gfx Types header."
    #endif

    #ifndef FG_INC_GFX_PLATFORM
        #include "fgGFXPlatform.h"
    #endif

    #ifndef FG_INC_TYPES
        #include "fgTypes.h"
    #endif

    #ifndef FG_INC_GFX_TYPES
        #include "fgGFXTypes.h"
    #endif

    #undef FG_INC_GFX_STD_INC_BLOCK__
#endif /* FG_INC_GFX_STD_INC */
