/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
 *******************************************************/

#ifndef _FG_SINGLETON_H_
#define _FG_SINGLETON_H_

#include <cstdio>
#include <typeinfo>

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
			printf(">>>>>>>>>> Created instance of type: '%s'\n", typeid(instance).name());
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
			printf(">>>>>>>>>> Deleted instance of type: '%s'\n", typeid(instance).name());
			if(instance)
				delete instance;
			instance = NULL;
		}
	}

	~fgSingleton()
	{
		instanceFlag = false;
	}
};

#endif
