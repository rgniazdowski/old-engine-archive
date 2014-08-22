/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_SINGLETON_H_
#define _FG_SINGLETON_H_

#include <cstdio>
#include <typeinfo>

// #FIXME - this is temporary...
#include "fgLog.h"

template<typename Class>
class fgSingleton
{
private:
	static bool instanceFlag;
	static Class *instance;

protected:	
	fgSingleton()
	{
	}

public:
	static Class *getInstance()
	{
		if(!instanceFlag || !instance)
		{
			if(!instance)
				instance = new Class();
			instanceFlag = true;
			FG_WriteLog(">>>>>>>>>> Created instance of type: '%s'\n", typeid(instance).name());
			return instance;
		} else {
			return instance;
		}
	}
	
	static void deleteInstance()
	{
		if(instanceFlag || instance)
		{
			instanceFlag = false;
			FG_WriteLog(">>>>>>>>>> Deleted instance of type: '%s'\n", typeid(instance).name());
			if(instance)
				delete instance;
			instance = NULL;
		}
	}

	~fgSingleton()
	{
		FG_WriteLog(">>>>>>>>>> Deleted instance of Singleton - ~ destructor called.");
		instanceFlag = false;
	}
};

#endif /* _FG_SINGLETON_H_ */
