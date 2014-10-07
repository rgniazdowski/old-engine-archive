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
#include "fgArgumentList.h"

/*
 *
 */
class fgFunctionCallback
{
public:
	// This is function pointer (to global or static member function)
	typedef fgBool (*fgFunction)(fgArgumentList *argv);

	//
	fgFunctionCallback() { }
	// 
	virtual ~fgFunctionCallback() {	
		m_function = NULL;
	}

	// 
	fgFunctionCallback(fgFunction function)
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
	
protected:
	fgFunction m_function;
};

/*
 *
 */
class fgPlainFunctionCallback : public fgFunctionCallback
{
public:
	// This is function pointer (to global or static member function)
	typedef fgBool (*fgPlainFunction)(void *userData);

	//
	fgPlainFunctionCallback() { }

	// 
	virtual ~fgPlainFunctionCallback() {	
		m_function = NULL;
	}

	// 
	fgPlainFunctionCallback(fgPlainFunction function)
	{
		m_function = function;
	}

	// 
	void setFunction(fgPlainFunction function)
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
			return m_function((void *)argv);
		return FG_FALSE;
	}

	// 
	virtual fgBool Call(void *argv)
	{
		if(m_function != NULL)
			return m_function(argv);
		return FG_FALSE;
	}
	
protected:
	fgPlainFunction m_function;
};

/*
 *
 */
template < class Class >
class fgClassCallback : public fgFunctionCallback
{
public:
	typedef fgBool (Class::*fgClassMethod)(fgArgumentList *argv);

	// 
	fgClassCallback(Class* class_instance, fgClassMethod method)
	{
		m_classInstance = class_instance;
		m_method = method;
	}	
	//
	virtual ~fgClassCallback() {	
		m_classInstance = NULL;
		m_method = NULL;
	}

	//
	void setMethod(fgClassMethod method)
	{
		m_classInstance = NULL;
		m_method = method;
	}

	//
	void setClass(Class* class_instance)
	{
		m_classInstance = class_instance;
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
	
protected:
	// 
	Class*		m_classInstance;
	// 
	fgClassMethod	m_method;
};

#endif /* _FG_CALLBACK_H_ */
