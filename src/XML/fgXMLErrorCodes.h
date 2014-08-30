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

#define FG_ERRNO_XML_BASE_CODE(_code)		(FG_ERRNO_BASE_CODE(1000)+_code)

// TINYXML / XML PARSING - universal for any xml reader/parser used
#define FG_ERRNO_XML_OK						FG_ERRNO_XML_BASE_CODE(0)	/* No error */
#define FG_ERRNO_XML_ERROR					FG_ERRNO_XML_BASE_CODE(1) /* Error */
#define FG_ERRNO_XML_IOFILE					FG_ERRNO_XML_BASE_CODE(2) /* Failed to open file */
#define FG_ERRNO_XML_PARSE_ELEMENT			FG_ERRNO_XML_BASE_CODE(3) /* Error parsing element */
#define FG_ERRNO_XML_PARSE_ELEMENT_NAME		FG_ERRNO_XML_BASE_CODE(4) /* Failed to read element name */
#define FG_ERRNO_XML_PARSE_ELEMENT_VALUE	FG_ERRNO_XML_BASE_CODE(5) /* Error reading element value */
#define FG_ERRNO_XML_PARSE_ATTRIBUTES		FG_ERRNO_XML_BASE_CODE(6) /* Error reading attributes  */
#define FG_ERRNO_XML_PARSE_EMPTY			FG_ERRNO_XML_BASE_CODE(7) /* Error: empty tag */
#define FG_ERRNO_XML_PARSE_END_TAG			FG_ERRNO_XML_BASE_CODE(8) /* Error reading end tag */
#define FG_ERRNO_XML_PARSE_UNKNOWN			FG_ERRNO_XML_BASE_CODE(9) /* Error parsing unknown */
#define FG_ERRNO_XML_PARSE_COMMENT			FG_ERRNO_XML_BASE_CODE(10) /* Error parsing comment */
#define FG_ERRNO_XML_PARSE_DECLARATION		FG_ERRNO_XML_BASE_CODE(11) /* Error parsing declaration */
#define FG_ERRNO_XML_PARSE_DOCUMENT_EMPTY	FG_ERRNO_XML_BASE_CODE(12) /* Error document empty */
#define FG_ERRNO_XML_PARSE_NULL_EOF			FG_ERRNO_XML_BASE_CODE(13) /* Error null(0) or unexpected EOF found in input stream. */
#define FG_ERRNO_XML_PARSE_CDATA			FG_ERRNO_XML_BASE_CODE(14) /* Error parsing CDATA */
#define FG_ERRNO_XML_PARSE_ROOT_DOCUMENT	FG_ERRNO_XML_BASE_CODE(15) /* Error when XmlDocument added to document, because it can only be at the root.*/

#define FG_ERRNO_XML_LAST_CODE				FG_ERRNO_XML_BASE_CODE(15)

#define FG_ERRNO_XML_OK_TEXT					"No error"
#define FG_ERRNO_XML_ERROR_TEXT					"Error"
#define FG_ERRNO_XML_IOFILE_TEXT				"Failed to open file"
#define FG_ERRNO_XML_PARSE_ELEMENT_TEXT			"Error parsing element"
#define FG_ERRNO_XML_PARSE_ELEMENT_NAME_TEXT	"Failed to read element name"
#define FG_ERRNO_XML_PARSE_ELEMENT_VALUE_TEXT	"Error reading element value"
#define FG_ERRNO_XML_PARSE_ATTRIBUTES_TEXT		"Error reading attributes "
#define FG_ERRNO_XML_PARSE_EMPTY_TEXT			"Error: empty tag"
#define FG_ERRNO_XML_PARSE_END_TAG_TEXT			"Error reading end tag"
#define FG_ERRNO_XML_PARSE_UNKNOWN_TEXT			"Error parsing unknown"
#define FG_ERRNO_XML_PARSE_COMMENT_TEXT			"Error parsing comment"
#define FG_ERRNO_XML_PARSE_DECLARATION_TEXT		"Error parsing declaration"
#define FG_ERRNO_XML_PARSE_DOCUMENT_EMPTY_TEXT	"Error document empty"
#define FG_ERRNO_XML_PARSE_NULL_EOF_TEXT		"Error null(0) or unexpected EOF found in input stream"
#define FG_ERRNO_XML_PARSE_CDATA_TEXT			"Error parsing CDATA"
#define FG_ERRNO_XML_PARSE_ROOT_DOCUMENT_TEXT	"Error when XmlDocument added to document, because it can only be at the root"

namespace FG_ERRNO_XML 
{
	const char * const __allErrVec[] = {
		FG_ERRNO_XML_OK_TEXT,
		FG_ERRNO_XML_ERROR_TEXT,
		FG_ERRNO_XML_IOFILE_TEXT,
		FG_ERRNO_XML_PARSE_ELEMENT_TEXT,
		FG_ERRNO_XML_PARSE_ELEMENT_NAME_TEXT,
		FG_ERRNO_XML_PARSE_ELEMENT_VALUE_TEXT,
		FG_ERRNO_XML_PARSE_ATTRIBUTES_TEXT,
		FG_ERRNO_XML_PARSE_EMPTY_TEXT,
		FG_ERRNO_XML_PARSE_END_TAG_TEXT,
		FG_ERRNO_XML_PARSE_UNKNOWN_TEXT,
		FG_ERRNO_XML_PARSE_COMMENT_TEXT,
		FG_ERRNO_XML_PARSE_DECLARATION_TEXT,
		FG_ERRNO_XML_PARSE_DOCUMENT_EMPTY_TEXT,
		FG_ERRNO_XML_PARSE_NULL_EOF_TEXT,
		FG_ERRNO_XML_PARSE_CDATA_TEXT,
		FG_ERRNO_XML_PARSE_ROOT_DOCUMENT_TEXT
	};

	static void __registerAll(void) {		
		for(int code=FG_ERRNO_XML_BASE_CODE(0), i=0; code<=FG_ERRNO_XML_LAST_CODE; code++, i++) {
			FG_ERRNO_REGISTER(code, FG_ERRNO_XML::__allErrVec[i]);
		}
	}
};

#undef _FG_ERRNO_ERROR_CODES_BLOCK_OTHER__
#endif /* _FG_XML_ERROR_CODES_H_ */
