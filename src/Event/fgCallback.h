/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_CALLBACK_H_
#define _FG_CALLBACK_H_

#include "fgTypes.h"

#include <iostream>

#include "fgArgumentList.h"

/*
 *
 */
class fgCallbackFunction
{
public:
	// This is function pointer (to global or static member function)
	typedef fgBool (*fgFunction)(fgArgumentList *argv);

	//
	fgCallbackFunction() { }
	// 
	virtual ~fgCallbackFunction() {	}

	// 
	fgCallbackFunction(fgFunction function)
	{
		m_function = function;
	}

	// 
	void setFunction(fgFunction function)
	{
		m_function = function;
	}

	// 
	virtual fgBool Call(void)
	{
		if(m_function != NULL)
			return m_function(NULL);
		return FG_FALSE;
	}

	// 
	virtual fgBool Call(fgArgumentList *argv)
	{
		if(m_function != NULL)
			return m_function(argv);
		return FG_FALSE;
	}
	
private:
	fgFunction m_function;
};

/*
 *
 */
template < class Class >
class fgCallback : public fgCallbackFunction
{
public:
	typedef fgBool (Class::*fgMethod)(fgArgumentList *argv);

	// 
	fgCallback(Class* class_instance, fgMethod method)
	{
		m_classInstance = class_instance;
		m_method = method;
	}	
	//
	~fgCallback() {	}

	//
	void setMethod(fgMethod method)
	{
		m_classInstance = NULL;
		m_method = method;
	}

	// 
	virtual fgBool Call(void)
	{
		if(m_method != NULL && m_classInstance != NULL)
			return (m_classInstance->*m_method)(NULL);
		return FG_FALSE;
	}

	// 
	virtual fgBool Call(fgArgumentList *argv)
	{
		if(m_method != NULL && m_classInstance != NULL)
			return (m_classInstance->*m_method)(argv);
		return FG_FALSE;
	}

	// 
	fgBool Call(Class *class_instance)
	{
		if(m_method != NULL && class_instance != NULL)
			return (class_instance->*m_method)(NULL);
		return FG_FALSE;
	}

	// 
	fgBool Call(Class *class_instance, fgArgumentList *argv)
	{
		if(m_method != NULL && class_instance != NULL)
			return (class_instance->*m_method)(argv);
		return FG_FALSE;
	}
	
private:
	// 
	Class*		m_classInstance;
	// 
	fgMethod	m_method;
};

#endif /* _FG_CALLBACK_H_ */
