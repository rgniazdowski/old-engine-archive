/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GFX_STD_INC
    #define FG_INC_GFX_STD_INC
    #define FG_INC_GFX_STD_INC_BLOCK

    #ifdef FG_INC_GFX_TYPES_BLOCK
        #error "FG_GFX_TYPES_BLOCK constant is defined. Do not include GfxStdInc inside of GfxTypes header."
    #endif

    #include "fgGfxGL.h"
    #include "fgGfxContext.h"
    #include "fgTypes.h"
    #include "fgGfxTypes.h"

    #undef FG_INC_GFX_STD_INC_BLOCK
#endif /* FG_INC_GFX_STD_INC */
