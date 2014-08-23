/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of #FLEXIGAME_PROJECT
 *
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_RESOURCE_FACTORY_TYPES_H_
#define _FG_RESOURCE_FACTORY_TYPES_H_

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

#endif /* _FG_RESOURCE_FACTORY_TYPES_H_ */