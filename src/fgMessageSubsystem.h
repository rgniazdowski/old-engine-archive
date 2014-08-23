/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_MESSAGE_SUBSYSTEM_H_
#define _FG_MESSAGE_SUBSYSTEM_H_

#include "fgCommon.h"
#include "fgSingleton.h"
#include "fgManagerBase.h"

#include "fgStatus.h"

/*
 *
 */
class fgMessageSubsystem : public fgManagerBase, public fgSingleton<fgMessageSubsystem>
{
	friend class fgSingleton<fgMessageSubsystem>;
protected:
	fgMessageSubsystem();
	virtual ~fgMessageSubsystem();
public:
	fgBool initialize(void);
	void clear(void);
	void destroy(void);
};

// #FIXME - here we go again with the singletons... :)
#define FG_MessageSubsystem fgMessageSubsystem::getInstance()

#endif /* _FG_MESSAGE_SUBSYSTEM_H_ */
