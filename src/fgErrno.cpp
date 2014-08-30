/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgErrno.h"

fgErrno::strErrMap fgErrno::s_errorMap;
int fgErrno::s_errno = 0;

/*
 *
 */
const char *fgErrno::strError(int _code)
{
	if(_code < FG_ERRNO_BASE_CODE(0)) {
		return strerror(_code);
	} else {
		return fgErrno::_getStrError(_code);
	}
}

/*
 *
 */
const char *fgErrno::_getStrError(int _fg_code)
{
	strErrMapItor it = s_errorMap.find(_fg_code);
	if(it == s_errorMap.end())
		return FG_ERRNO_INVALID_CODE_TEXT;
	else
		return (*it).second.c_str();
}

/*
 *
 */
void fgErrno::registerStrError(int _code, const char *_str)
{
	if(!_str)
		return;
	strErrMapPair query_pair;
	query_pair.first = _code;
	query_pair.second = _str;
	std::pair<strErrMapItor, bool> result = s_errorMap.insert(query_pair);
}

/*
 *
 */
void fgErrno::registerStrError(int _code, std::string& _str)
{
	registerStrError(_code, _str.c_str());
}

/*
 *
 */
void fgErrno::setErrno(int _code)
{
	if(_code < FG_ERRNO_BASE_CODE(0)) {
		errno = _code;
	} else {
		s_errno = _code; // ?
	}
}

/*
 *
 */
void fgErrno::setLocalErrno(int _code)
{
	s_errno = _code;
}

/*
 *
 */
int fgErrno::code(void)
{
	return errno;
}

/*
 *
 */
int fgErrno::localCode(void)
{
	return s_errno;
}

/*
 *
 */
void fgErrno::clearError(void)
{
	errno = 0;
	s_errno = 0;
}

/*
 *
 */
void fgErrno::reset(void)
{
	s_errorMap.clear();
}
