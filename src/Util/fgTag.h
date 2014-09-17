/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_TAG_H_
#define _FG_TAG_H_

#define FG_TAG_NAME_LEN_MAX	64

#define FG_TAG_VOID_NAME	"tag{void}"
#define FG_TAG_VOID_ID		-1

#define FG_TAG_FUNCTION_NAME(_name) static const char *name(void) { return _name; }
#define FG_TAG_FUNCTION_ID(_id) static int id(void) { return _id; }

#define FG_TAG_FUNCTION_ID_AUTO() static int id(void) { return __FG_TAG::_fg_tag_s_hashfn(name()); }

namespace __FG_TAG {

	inline int _fg_tag_s_hashfn(const char *_in) {
		int r = 0;
		for(unsigned int i=0;i<strnlen(_in, FG_TAG_NAME_LEN_MAX);i++) {
			r+=(int)_in[i];
		}
		return r;
	}
};

struct fgTagVoid {
};

struct fgTagBase {
};

template<class _type> struct fgTag : fgTagBase { };

#define FG_TAG_TEMPLATE(_tag_type, _tag_name, _tag_id) \
template <> struct fgTag<_tag_type> : fgTagBase { \
	typedef _tag_type _type; \
	FG_TAG_FUNCTION_NAME(_tag_name) \
	FG_TAG_FUNCTION_ID(_tag_id) \
	}

#define FG_TAG_TEMPLATE_ID_AUTO(_tag_type, _tag_name) \
template <> struct fgTag<_tag_type> : fgTagBase { \
	typedef _tag_type _type; \
	FG_TAG_FUNCTION_NAME(_tag_name) \
	FG_TAG_FUNCTION_ID_AUTO() \
	}

FG_TAG_TEMPLATE(fgTagVoid, FG_TAG_VOID_NAME, FG_TAG_VOID_ID);

#define FG_TAG_TYPE_NAME(_tag_type) struct fgTag<_tag_type>
#define FG_TAG_TYPE(_tag_type)		fgTag<_tag_type>

#endif // _FG_TAG_H_
