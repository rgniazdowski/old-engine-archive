/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_FONT_STB_TIMES_BOLD_H_
#define _FG_FONT_STB_TIMES_BOLD_H_

#ifndef _FG_FONT_BUILT_IN_TYPES_H_
#include "fgFontBuiltInTypes.h"
#endif

#ifndef FG_STB_FONT_PTR
#define FG_STB_FONT_PTR(_font_name, _param) stb__ ## _font_name ## _usascii_ ## _param
#endif

#ifndef FG_STB_FONT_CONST
#define FG_STB_FONT_CONST(_font_name, _const_name) STB_FONT_ ## _font_name ## _usascii_ ## _const_name
#endif

namespace fgFontBuiltIn 
{
	class StbTimesBold 
	{
	public:
		static fgFontBuiltInRawData* getRawData(const int size = 50);
		
	private:
		static fgFontBuiltInRawData m_stbFontRawData;

		StbTimesBold() {}
		~StbTimesBold() {}
	};
};

#endif /* _FG_FONT_STB_TIMES_BOLD_H_ */
