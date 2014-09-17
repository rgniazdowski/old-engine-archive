/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_MANAGER_BASE_H_
#define _FG_MANAGER_BASE_H_

#include "fgBool.h"

/*
 *
 */
class fgManagerBase
{
public:
	// 
	fgManagerBase() : m_init(FG_FALSE) {}
	// 
	virtual ~fgManagerBase() {}

protected:
	//
	virtual void clear(void) = 0;

public:
	//
	virtual fgBool destroy(void) = 0;
	//
	virtual fgBool initialize(void) = 0;
protected:
	fgBool m_init;
};

#endif /* _FG_MANAGER_BASE_H_ */
