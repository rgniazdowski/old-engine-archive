/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXShaderConfig.h"

/*
 *
 */
fgGfxShaderConfig::fgGfxShaderConfig()
{
}

/*
 *
 */
fgGfxShaderConfig::fgGfxShaderConfig(const char *filePath)
{
	fgGfxShaderConfig::load(filePath);
}

/*
 *
 */
fgGfxShaderConfig::~fgGfxShaderConfig()
{
	if(m_parser)
		delete m_parser;
	if(m_writer)
		delete m_writer;
	clearAll();
}

/*
 *
 */
fgBool fgGfxShaderConfig::load(const char *filePath)
{
	if(!fgConfig::load(filePath))
		return FG_FALSE;
	return FG_TRUE;
}
