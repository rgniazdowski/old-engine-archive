/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_STD_INC_H_
#define _FG_GFX_STD_INC_H_
#define _FG_GFX_STD_INC_BLOCK__

#ifdef _FG_GFX_TYPES_BLOCK__
#	error "FG_GFX_TYPES_BLOCK constant is defined. Do not include GfxStdInc inside of Gfx Types header."
#endif

#ifndef _FG_GFX_PLATFORM_H_
#include "fgGFXPlatform.h"
#endif

#ifndef _FG_TYPES_H_
#include "fgTypes.h"
#endif

#ifndef _FG_GFX_TYPES_H_
#include "fgGFXTypes.h"
#endif

#undef _FG_GFX_STD_INC_BLOCK__
#endif /* _FG_GFX_STD_INC_H_ */
