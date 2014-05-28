/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgArgumentList.h"

#include <iostream>

#include "s3eMemory.h"

/*
 *
 */
fgArgumentList::fgArgumentList()
{
	reset();
	m_maxArgs = FG_ARGUMENT_DEFAULT_COUNT;
}

/*
 *
 */
fgArgumentList::fgArgumentList(int _max)
{
	reset();
	m_maxArgs = _max;
}

/*
 *
 */
fgArgumentList::~fgArgumentList()
{
	clearArguments();
}

/*
 *
 */
inline void fgArgumentList::setMaxArgumentCount(int _max)
{
	m_maxArgs = _max;
}

/*
 *
 */
inline int fgArgumentList::getMaxArgumentCount()
{
	return m_maxArgs;
}

/*
 *
 */
void fgArgumentList::pushArgument(fgArgumentType _type, void *_value)
{
	fgArgument new_argument;
	new_argument.reset();
	new_argument.type = _type;
	switch(_type)
	{
		case FG_ARGUMENT_INTEGER:
			new_argument.int_val = *((int*)_value);
			break;
		case FG_ARGUMENT_DOUBLE:
			new_argument.double_val = *((double*)_value);
			break;
		case FG_ARGUMENT_FLOAT:
			new_argument.float_val = *((float*)_value);
			break;
		case FG_ARGUMENT_STRING:
			snprintf(new_argument.string, FG_ARGUMENT_MAX_STRING, (char *)_value);
			break;
		case FG_ARGUMENT_POINTER:
		case FG_ARGUMENT_STRUCT:
			new_argument.custom_pointer = _value;
			break;
		default:
			new_argument.type = FG_ARGUMENT_NONE;
			break;
	}

	if(new_argument.type == FG_ARGUMENT_NONE)
		return;

	m_argv.push_back(new_argument);
}

/*
 *
 */
void fgArgumentList::pushArgument(int int_val)
{
	fgArgument new_argument;
	if((m_argc+1) > m_maxArgs)
		return;
	m_argc=m_argc+1;
	new_argument.type = FG_ARGUMENT_INTEGER;
	new_argument.int_val = int_val;
	m_argv.push_back(new_argument); 
}

/*
 *
 */
void fgArgumentList::pushArgument(double double_val)
{
	fgArgument new_argument;
	if((m_argc+1) > m_maxArgs)
		return;
	m_argc=m_argc+1;
	new_argument.type = FG_ARGUMENT_DOUBLE;
	new_argument.double_val = double_val;
	m_argv.push_back(new_argument); 
}

/*
 *
 */
void fgArgumentList::pushArgument(float float_val)
{
	fgArgument new_argument;
	if((m_argc+1) > m_maxArgs)
		return;
	m_argc=m_argc+1;

	new_argument.type = FG_ARGUMENT_FLOAT;
	new_argument.float_val = float_val;
	m_argv.push_back(new_argument); 
}

/*
 *
 */
void fgArgumentList::pushArgument(const char *string)
{
	fgArgument new_argument;
	if((m_argc+1) > m_maxArgs)
		return;
	m_argc=m_argc+1;

	new_argument.type = FG_ARGUMENT_STRING;
	snprintf(new_argument.string, FG_ARGUMENT_MAX_STRING, (char *)string);
	m_argv.push_back(new_argument); 
}

/*
 *
 */
void fgArgumentList::pushArgument(void *custom_pointer)
{
	fgArgument new_argument;
	
	if((m_argc+1) > m_maxArgs)
		return;
	m_argc=m_argc+1;

	new_argument.type = FG_ARGUMENT_POINTER;
	new_argument.custom_pointer = custom_pointer;
	m_argv.push_back(new_argument); 
}

/*
 *
 */
inline int fgArgumentList::getArgumentCount()
{
	m_argc = m_argv.size();
	return m_argc;
}

/*
 *
 */
inline void fgArgumentList::reset()
{
	m_currentArg = -1; // FIXME
}

/*
 *
 */
void* fgArgumentList::getNextArgumentValue(fgArgumentType *_type)
{
	m_currentArg=m_currentArg+1;
	if(m_currentArg >= getArgumentCount())
	{
	//	ArgumentList::Reset();
		m_currentArg = getArgumentCount();
		*_type = FG_ARGUMENT_NONE;
		return NULL;
	}

	return fgArgumentList::getArgumentValueByID(m_currentArg, _type);
}

/*
 *
 */
void* fgArgumentList::getArgumentValueByID(int ID, fgArgumentType *_type)
{
	if(ID >=0 && ID < getArgumentCount())
	{
		if(_type != NULL)
			*_type = m_argv[ID].type;
		switch(m_argv[ID].type)
		{
			case FG_ARGUMENT_INTEGER:
				return (void *)(&m_argv[ID].int_val);
				break;
			case FG_ARGUMENT_DOUBLE:
				return (void *)(&m_argv[ID].double_val);
				break;
			case FG_ARGUMENT_FLOAT:
				return (void *)(&m_argv[ID].float_val);
				break;
			case FG_ARGUMENT_STRING:
				return (void *)m_argv[ID].string;
				break;
			case FG_ARGUMENT_POINTER:
			case FG_ARGUMENT_STRUCT:
				return m_argv[ID].custom_pointer;
				break;
			default:
				if(_type != NULL)
					*_type = FG_ARGUMENT_NONE;
				return NULL;
				break;
		}
	}
	if(_type != NULL)
		*_type = FG_ARGUMENT_NONE;
	return NULL;
}

/*
 *
 */
fgArgument fgArgumentList::getNextArgumentStruct()
{
	m_currentArg=m_currentArg+1;
	if(m_currentArg >= getArgumentCount())
	{
		//ArgumentList::Reset();
		m_currentArg = getArgumentCount();
		fgArgument new_argument;
		new_argument.type = FG_ARGUMENT_NONE;
		return new_argument;
	}
	return m_argv[m_currentArg];
}

/*
 *
 */
fgArgument fgArgumentList::getArgumentStructByID(int ID)
{
	if(ID >=0 && ID < getArgumentCount())
	{
		return m_argv[ID];
	}
	else
	{
		fgArgument new_argument;
		new_argument.type = FG_ARGUMENT_NONE;
		return new_argument;
	}
}

/*
 *
 */
inline bool fgArgumentList::isThereNextArgument()
{
	if((m_currentArg+1) >= getArgumentCount())
		return false;
	else
		return true;
}

/*
 *
 */
inline int fgArgumentList::getCurrentID()
{
	return m_currentArg;
}

/*
 * This function  frees the memory  held by the  arguments (argv)
 * The rule is that when some value/structure/pointer is put into
 * the argument list it is being managed by the class, so it also
 * needs to be freed in this function.
 */
void fgArgumentList::clearArguments()
{
	reset();
	while(isThereNextArgument()) {
		fgArgument arg = getNextArgumentStruct();
		if(arg.type == FG_ARGUMENT_STRUCT) {
			if(arg.custom_pointer != NULL) {
				s3eFree(arg.custom_pointer);
			}
		}
	}
	m_argv.clear();
	m_argc = 0;
	reset();
}
