/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_CALLBACK_H
#define _FG_CALLBACK_H

#include <iostream>
#include "fgArgumentList.h"

class fgCallbackFunction
{
public:
	// This is function pointer (to global or static member function)
	typedef bool (*fgFunction)(fgArgumentList *argv);

	fgCallbackFunction()
	{
	}

	fgCallbackFunction(fgFunction function)
	{
		m_function = function;
	}

	void setFunction(fgFunction function)
	{
		m_function = function;
	}

	virtual bool Call(void)
	{
		if(m_function != NULL)
			return m_function(NULL);
		return false;
	}

	virtual bool Call(fgArgumentList *argv)
	{
		if(m_function != NULL)
			return m_function(argv);
		return false;
	}

	~fgCallbackFunction()
	{
	}

private:
	fgFunction m_function;
};

template < class Class >
class fgCallback : public fgCallbackFunction
{
public:
	typedef bool (Class::*fgMethod)(fgArgumentList *argv);

	fgCallback(Class* class_instance, fgMethod method)
	{
		m_classInstance = class_instance;
		m_method = method;
	}

	void setMethod(fgMethod method)
	{
		m_classInstance = NULL;
		m_method = method;
	}

	virtual bool Call(void)
	{
		if(m_method != NULL && m_classInstance != NULL)
			return (m_classInstance->*m_method)(NULL);
		return false;
	}

	virtual bool Call(fgArgumentList *argv)
	{
		if(m_method != NULL && m_classInstance != NULL)
			return (m_classInstance->*m_method)(argv);
		return false;
	}

	bool Call(Class *class_instance)
	{
		if(m_method != NULL && class_instance != NULL)
			return (class_instance->*m_method)(NULL);
		return false;
	}

	bool Call(Class *class_instance, fgArgumentList *argv)
	{
		if(m_method != NULL && class_instance != NULL)
			return (class_instance->*m_method)(argv);
		return false;
	}

	~fgCallback()
	{
	}

private:
	Class*  m_classInstance;
	fgMethod  m_method;
};

#endif /* _FG_CALLBACH_H */
