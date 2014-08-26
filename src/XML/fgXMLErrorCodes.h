/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_XML_ERROR_CODES_H_
#define _FG_XML_ERROR_CODES_H_
#define _FG_ERRNO_ERROR_CODES_BLOCK_OTHER__

#ifdef _FG_ERRNO_ERROR_CODES_BLOCK__
#error "FG_ERRNO_ERROR_CODES_BLOCK constant is defined. Do not include error codes definition header inside of fgErrno header."
#endif

#include "fgErrno.h"

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

#undef _FG_ERRNO_ERROR_CODES_BLOCK_OTHER__
#endif /* _FG_XML_ERROR_CODES_H_ */
