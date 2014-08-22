/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_LOG_H_
#define _FG_LOG_H_

void FG_InfoLog(const char *fmt, ...);
void FG_ErrorLog(const char *fmt, ...);
void FG_WriteLog(const char *fmt, ...);

#endif