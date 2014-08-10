/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/
/**
 * Portions Copyright (C) Scott Bilas, 2000
 */

#ifndef _FG_HANDLE_H_
#define _FG_HANDLE_H_

#include "fgCommon.h"

#ifndef FG_RAW_HANDLE_TYPE
#define FG_RAW_HANDLE_TYPE unsigned int
#endif

typedef FG_RAW_HANDLE_TYPE fgRawHandle;
typedef FG_RAW_HANDLE_TYPE fgRawIndex;
typedef FG_RAW_HANDLE_TYPE fgRawMagic;

#ifndef FG_INVALID_HANDLE
// All bits filled defines an invalid resource handle
#define FG_INVALID_HANDLE			0xFFFFFFFFUL
//#define FG_IS_INVALID_HANDLE(_rh)	((_rh.getHandle() == FG_INVALID_HANDLE) ? true : false)
#define FG_IS_INVALID_HANDLE(_rh)	( _rh.isNull() )
//#define FG_IS_VALID_HANDLE(_rh)		((_rh.getHandle() == FG_INVALID_HANDLE) ? false : true)
#define FG_IS_VALID_HANDLE(_rh)	( !_rh.isNull() )
#endif

template <typename TagType>
class fgHandle
{
private:
    union
    {
        enum
        {
            // Size to use for index bit field
            FG_HANDLE_MAX_BITS_INDEX = 16,
            // Size to use for magic bit field
            FG_HANDLE_MAX_BITS_MAGIC = 16,

            // Size to compare against for asserting dereferences
            FG_HANDLE_MAX_INDEX = ( 1 << FG_HANDLE_MAX_BITS_INDEX) - 1,
            // Size to compare against for asserting dereferences
            FG_HANDLE_MAX_MAGIC = ( 1 << FG_HANDLE_MAX_BITS_MAGIC) - 1,
        };

        struct
        {
			// index into resource array
			fgRawIndex m_index : FG_HANDLE_MAX_BITS_INDEX;
			// magic number to check
            fgRawMagic m_magic : FG_HANDLE_MAX_BITS_MAGIC;
        };
        fgRawHandle m_handle;
    };

public:
	// Default constructor for Handle object
    fgHandle() : m_handle(FG_INVALID_HANDLE) { }

    fgBool init(fgRawIndex index);

    fgRawIndex getIndex(void) const {
		return m_index;
	}

    fgRawMagic getMagic(void) const {
		return m_magic;
	}

	fgRawHandle getHandle(void) const {
		return m_handle;
	}

    fgBool isNull(void) const {
		return (fgBool)(m_handle == FG_INVALID_HANDLE);
	}

	operator fgRawHandle(void) const {
		return m_handle;
	}
};

template <typename TagType>
fgBool fgHandle<TagType>::init(fgRawIndex index)
{
	if(!isNull()) {
		// Don't allow reassignment
		return FG_FALSE;
	}
	if(index > FG_HANDLE_MAX_INDEX) {
		// Verify range
		return FG_FALSE;
	}

	static fgRawMagic s_autoMagic = 0;
    if(++s_autoMagic >= FG_HANDLE_MAX_MAGIC) {
        s_autoMagic = 1;
    }

    m_index = index;
    m_magic = s_autoMagic;
}

template <typename TagType>
inline bool operator != ( fgHandle <TagType> l, fgHandle <TagType> r )
    {  return ( l.getHandle() != r.getHandle() );  }

template <typename TagType>
inline bool operator == ( fgHandle <TagType> l, fgHandle <TagType> r )
    {  return ( l.getHandle() == r.getHandle() );  }

#endif /* _FG_HANDLE_H_ */
