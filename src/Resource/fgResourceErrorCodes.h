/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_RESOURCE_ERROR_CODES_H_
#define _FG_RESOURCE_ERROR_CODES_H_
#define _FG_ERRNO_ERROR_CODES_BLOCK_OTHER__

#ifdef _FG_ERRNO_ERROR_CODES_BLOCK__
#error "FG_ERRNO_ERROR_CODES_BLOCK constant is defined. Do not include error codes definition header inside of fgErrno header."
#endif

#include "fgErrno.h"

#define FG_ERRNO_RESOURCE_BASE_CODE(_code)		(FG_ERRNO_BASE_CODE(600)+_code)

#define FG_ERRNO_RESOURCE_OK					FG_ERRNO_RESOURCE_BASE_CODE(0) /* No error */
#define FG_ERRNO_RESOURCE_NO_GROUPS				FG_ERRNO_RESOURCE_BASE_CODE(1) /* No resource groups found */
#define FG_ERRNO_RESOURCE_PARAMETER_NULL		FG_ERRNO_RESOURCE_BASE_CODE(2) /* Resource parameter is NULL */
#define FG_ERRNO_RESOURCE_ALREADY_MANAGED		FG_ERRNO_RESOURCE_BASE_CODE(3) /* Resource is already managed (it exists in handle manager) */
#define FG_ERRNO_RESOURCE_INITIALIZED_HANDLE	FG_ERRNO_RESOURCE_BASE_CODE(4) /* Resource has already initialized handle */
#define FG_ERRNO_RESOURCE_ACQUIRE_HANDLE		FG_ERRNO_RESOURCE_BASE_CODE(5) /* Could not acquire handle for the resource */
#define FG_ERRNO_RESOURCE_SETUP_HANDLE_NAME		FG_ERRNO_RESOURCE_BASE_CODE(6) /* Could not setup handle string tag for the resource */
#define FG_ERRNO_RESOURCE_GROUP_HANDLE_INVALID	FG_ERRNO_RESOURCE_BASE_CODE(7) /* Resource Group handle is invalid */
#define FG_ERRNO_RESOURCE_GROUP_IN_VECTOR		FG_ERRNO_RESOURCE_BASE_CODE(8) /* Resource Group is already in the vector */
#define FG_ERRNO_RESOURCE_NOT_FOUND_INVALID_HANDLE	FG_ERRNO_RESOURCE_BASE_CODE(9) /* Could not find resource, handle is invalid */
#define FG_ERRNO_RESOURCE_HANDLE_INVALID		FG_ERRNO_RESOURCE_BASE_CODE(10) /* Resource handle is invalid */
#define FG_ERRNO_RESOURCE_LOCKED_REMOVAL		FG_ERRNO_RESOURCE_BASE_CODE(11) /* Can't remove a locked resource */
#define FG_ERRNO_RESOURCE_NOT_DISPOSED			FG_ERRNO_RESOURCE_BASE_CODE(12) /* For unknown reason resource is still not disposed */
#define FG_ERRNO_RESOURCE_NAME_TAG_EMPTY		FG_ERRNO_RESOURCE_BASE_CODE(13) /* Resource name tag is empty */
#define FG_ERRNO_RESOURCE_NAME_TAG_INVALID		FG_ERRNO_RESOURCE_BASE_CODE(14) /* Name tag is invalid */
#define FG_ERRNO_RESOURCE_TOO_MANY_UNLOCKS		FG_ERRNO_RESOURCE_BASE_CODE(15) /* Resource reference count is already zero - too many unlocks */
#define FG_ERRNO_RESOURCE_NOT_MANAGED			FG_ERRNO_RESOURCE_BASE_CODE(16) /* Resource is not managed */
#define FG_ERRNO_RESOURCE_REMOVE				FG_ERRNO_RESOURCE_BASE_CODE(17) /* Could not remove resource */
#define FG_ERRNO_RESOURCE_OVERALLOCATION		FG_ERRNO_RESOURCE_BASE_CODE(18) /* Overallocation: too many resources were locked or a resource larger than the requested maximum memory was inserted */

#define FG_ERRNO_RESOURCE_LAST_CODE				FG_ERRNO_RESOURCE_BASE_CODE(18)

#define FG_ERRNO_RESOURCE_OK_TEXT					"No error"
#define FG_ERRNO_RESOURCE_NO_GROUPS_TEXT			"No resource groups found"
#define FG_ERRNO_RESOURCE_PARAMETER_NULL_TEXT		"Resource parameter is NULL"
#define FG_ERRNO_RESOURCE_ALREADY_MANAGED_TEXT		"Resource is already managed (it exists in handle manager)"
#define FG_ERRNO_RESOURCE_INITIALIZED_HANDLE_TEXT	"Resource has already initialized handle"
#define FG_ERRNO_RESOURCE_ACQUIRE_HANDLE_TEXT		"Could not acquire handle for the resource"
#define FG_ERRNO_RESOURCE_SETUP_HANDLE_NAME_TEXT	"Could not setup handle string tag for the resource"
#define FG_ERRNO_RESOURCE_GROUP_HANDLE_INVALID_TEXT "Resource Group handle is invalid"
#define FG_ERRNO_RESOURCE_GROUP_IN_VECTOR_TEXT		"Resource Group is already in the vector"
#define FG_ERRNO_RESOURCE_NOT_FOUND_INVALID_HANDLE_TEXT "Could not find resource, handle is invalid"
#define FG_ERRNO_RESOURCE_HANDLE_INVALID_TEXT		"Resource handle is invalid"
#define FG_ERRNO_RESOURCE_LOCKED_REMOVAL_TEXT		"Can't remove a locked resource"
#define FG_ERRNO_RESOURCE_NOT_DISPOSED_TEXT			"For unknown reason resource is still not disposed"
#define FG_ERRNO_RESOURCE_NAME_TAG_EMPTY_TEXT		"Resource name tag is empty"
#define FG_ERRNO_RESOURCE_NAME_TAG_INVALID_TEXT		"Name tag is invalid"
#define FG_ERRNO_RESOURCE_TOO_MANY_UNLOCKS_TEXT		"Resource reference count is already zero - too many unlocks"
#define FG_ERRNO_RESOURCE_NOT_MANAGED_TEXT			"Resource is not managed"
#define FG_ERRNO_RESOURCE_REMOVE_TEXT				"Could not remove resource"
#define FG_ERRNO_RESOURCE_OVERALLOCATION_TEXT		"Overallocation: too many resources were locked or a resource larger than the requested maximum memory was inserted"

// Well this looks like error codes' translations of messages
// could be loaded from external file, the problem would be however 
// with keeping up with error number codes

namespace FG_ERRNO_RESOURCE {
	const char * const __allErrVec[] = {
		FG_ERRNO_RESOURCE_OK_TEXT,
		FG_ERRNO_RESOURCE_NO_GROUPS_TEXT,			
		FG_ERRNO_RESOURCE_PARAMETER_NULL_TEXT,
		FG_ERRNO_RESOURCE_ALREADY_MANAGED_TEXT,
		FG_ERRNO_RESOURCE_INITIALIZED_HANDLE_TEXT,
		FG_ERRNO_RESOURCE_ACQUIRE_HANDLE_TEXT,
		FG_ERRNO_RESOURCE_SETUP_HANDLE_NAME_TEXT,
		FG_ERRNO_RESOURCE_GROUP_HANDLE_INVALID_TEXT,
		FG_ERRNO_RESOURCE_GROUP_IN_VECTOR_TEXT,
		FG_ERRNO_RESOURCE_NOT_FOUND_INVALID_HANDLE_TEXT,
		FG_ERRNO_RESOURCE_HANDLE_INVALID_TEXT,
		FG_ERRNO_RESOURCE_LOCKED_REMOVAL_TEXT,
		FG_ERRNO_RESOURCE_NOT_DISPOSED_TEXT,	
		FG_ERRNO_RESOURCE_NAME_TAG_EMPTY_TEXT,
		FG_ERRNO_RESOURCE_NAME_TAG_INVALID_TEXT,
		FG_ERRNO_RESOURCE_TOO_MANY_UNLOCKS_TEXT,
		FG_ERRNO_RESOURCE_NOT_MANAGED_TEXT,
		FG_ERRNO_RESOURCE_REMOVE_TEXT,
		FG_ERRNO_RESOURCE_OVERALLOCATION_TEXT
	};

	static void __registerAll(void) {		
		for(int code=FG_ERRNO_RESOURCE_BASE_CODE(0), i=0; code<=FG_ERRNO_RESOURCE_LAST_CODE; code++, i++) {
			FG_ERRNO_REGISTER(code, FG_ERRNO_RESOURCE::__allErrVec[i]);
		}
	}
};


#undef _FG_ERRNO_ERROR_CODES_BLOCK_OTHER__
#endif /* _FG_RESOURCE_ERROR_CODES_H_ */
