/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGFXShaderManager.h"

/*
 *
 */
fgGfxShaderManager::fgGfxShaderManager()
{
	setReportToMsgSystem(FG_TRUE);
}

/*
 *
 */
fgGfxShaderManager::~fgGfxShaderManager()
{

}

/*
 *
 */
void fgGfxShaderManager::clear(void)
{
}

/*
 *
 */
void fgGfxShaderManager::destroy(void)
{
}

/*
 *
 */
fgBool fgGfxShaderManager::initialize(void)
{
	return FG_TRUE;
}

/*
 *
 */
fgBool fgGfxShaderManager::preLoadShaders(void)
{
	return FG_TRUE;
}
