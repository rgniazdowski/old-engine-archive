/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_ERRNO_H_
#define _FG_ERRNO_H_

#include <cerrno>
#include <map>
#include <string>

#define FG_ERRNO_CLEAR()	do { errno = 0; } while(0)


#define FG_ERRNO_BASE_CODE_	20000
#define FG_ERRNO_BASE_CODE(code) (FG_ERRNO_BASE_CODE_+code)

#define FG_ERRNO_WARNING_BASE_CODE_		63600

#define FG_ERRNO_DEBUG_BASE_CODE_		616000

#define FG_ERRNO_INFO_BASE_CODE_		100000

/**********************************************************
 * FlexiGame specific error codes
 */

#define FG_ERRNO_OK			FG_ERRNO_BASE_CODE(0)	/* No error */
#define FG_ERRNO_NOCFG		FG_ERRNO_BASE_CODE(1)	/* No config file found */

// TINYXML / XML PARSING - universal for any xml reader/parser used
#define FG_ERRNO_XML_OK						FG_ERRNO_BASE_CODE(100)	/* No error */
#define FG_ERRNO_XML_ERROR					FG_ERRNO_BASE_CODE(101) /* Error */
#define FG_ERRNO_XML_IOFILE					FG_ERRNO_BASE_CODE(102) /* Failed to open file */
#define FG_ERRNO_XML_PARSE_ELEMENT			FG_ERRNO_BASE_CODE(103) /* Error parsing element */
#define FG_ERRNO_XML_PARSE_ELEMENT_NAME		FG_ERRNO_BASE_CODE(104) /* Failed to read element name */
#define FG_ERRNO_XML_PARSE_ELEMENT_VALUE	FG_ERRNO_BASE_CODE(105) /* Error reading element value */
#define FG_ERRNO_XML_PARSE_ATTRIBUTES		FG_ERRNO_BASE_CODE(106) /* Error reading attributes  */
#define FG_ERRNO_XML_PARSE_EMPTY			FG_ERRNO_BASE_CODE(107) /* Error: empty tag */
#define FG_ERRNO_XML_PARSE_END_TAG			FG_ERRNO_BASE_CODE(108) /* Error reading end tag */
#define FG_ERRNO_XML_PARSE_UNKNOWN			FG_ERRNO_BASE_CODE(109) /* Error parsing unknown */
#define FG_ERRNO_XML_PARSE_COMMENT			FG_ERRNO_BASE_CODE(110) /* Error parsing comment */
#define FG_ERRNO_XML_PARSE_DECLARATION		FG_ERRNO_BASE_CODE(111) /* Error parsing declaration */
#define FG_ERRNO_XML_PARSE_DOCUMENT_EMPTY	FG_ERRNO_BASE_CODE(112) /* Error document empty */
#define FG_ERRNO_XML_PARSE_NULL_EOF			FG_ERRNO_BASE_CODE(113) /* Error null(0) or unexpected EOF found in input stream. */
#define FG_ERRNO_XML_PARSE_CDATA			FG_ERRNO_BASE_CODE(114) /* Error parsing CDATA */
#define FG_ERRNO_XML_PARSE_ROOT_DOCUMENT	FG_ERRNO_BASE_CODE(115) /* Error when XmlDocument added to document, because it can only be at the root.*/

/*
 * 
 */
class fgErrno {
public:
	static const char *strError(int _code);
	static void registerStrError(int _code, const char *_str);
	static void registerStrError(int _code, std::string& _str);
	static void setErrno(int _code);
	static void reset(void);
protected:
	static const char *_getStrError(int _fg_code);
private:
	typedef std::map<int, std::string> strErrMap;
	typedef std::pair<int, std::string> strErrMapPair;
	typedef strErrMap::iterator strErrMapItor;

	static strErrMap s_errorMap;
	static int s_errno;
};

#define FG_ERRNO_STR(code)	fgErrno::strError(code)
#define FG_ERRNO			fgErrno

#define FG_ERRNO_SET(code)	fgErrno::setErrno(code)
#define FG_ERRNO_REGISTER(code, str) fgErrno::registerStrError(code, str)

#endif /* _FG_ERRNO_H_ */
