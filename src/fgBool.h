/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_BOOL_H_
#define _FG_BOOL_H_


#ifndef FG_BOOL_DEFINED_
#define FG_BOOL_DEFINED_
typedef unsigned char fgBool;
#endif

#ifndef FG_FALSE
#define FG_FALSE 0
#endif

#ifndef FG_TRUE
#define FG_TRUE 1
#endif

#ifndef FG_SUCCESS
#define FG_SUCCESS 1
#endif

#ifndef FG_WARNING
#define FG_WARNING 3
#endif

#ifndef FG_ERROR
#define FG_ERROR 0
#endif

#define FG_SUCCESS_TEXT		"success"
#define FG_TRUE_TEXT		"true"
#define FG_FALSE_TEXT		"false"
#define FG_WARNING_TEXT		"warning"
#define FG_ERROR_TEXT		"error"

#endif /* _FG_BOOL_H_ */
