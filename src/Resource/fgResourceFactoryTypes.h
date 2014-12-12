/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_RESOURCE_FACTORY_TYPES
    #define FG_INC_RESOURCE_FACTORY_TYPES

class fgResource;

    #if __cplusplus > 199711L
using fgCreateResourceFn = fgResource* (*)(void);
    #else
typedef fgResource* (*fgCreateResourceFn)(void);
    #endif

    #ifndef FG_FACTORY_CREATE_FUNCTION
        #define FG_FACTORY_CREATE_FUNCTION(RETURNTYPE, CREATETYPE) \
static RETURNTYPE * createResource(void) { return new CREATETYPE(); }
    #endif

    #ifndef FG_RESOURCE_FACTORY_CREATE_FUNCTION
        #define FG_RESOURCE_FACTORY_CREATE_FUNCTION(CREATETYPE) \
static fgResource * createResource(void) { return new CREATETYPE(); }
    #endif

#endif /* FG_INC_RESOURCE_FACTORY_TYPES */
