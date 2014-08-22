/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_MANAGER_BASE_H_
#define _FG_MANAGER_BASE_H_

#include "fgCommon.h"
#include "fgStatusReporter.h"

class fgManagerBase : public fgStatusReporter {
public:
	fgManagerBase() {}
	virtual ~fgManagerBase() {}
		
	virtual void clear(void) = 0;
	virtual void destroy(void) = 0;

	virtual fgBool initialize(void) = 0;

};

#endif /* _FG_MANAGER_BASE_H_ */

