/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgErrorCodes.h"

/*
 *
 */
void fgErrorCodes::registerAll(void)
{
	FG_ERRNO_MAIN::__registerAll();

	FG_ERRNO_SFX::__registerAll();
	FG_ERRNO_EVENT::__registerAll();
	FG_ERRNO_GFX::__registerAll();
	FG_ERRNO_TEXTURE::__registerAll();
	FG_ERRNO_GUI::__registerAll();
	FG_ERRNO_RESOURCE::__registerAll();
	FG_ERRNO_SCRIPT::__registerAll();
	FG_ERRNO_FILE::__registerAll();
	FG_ERRNO_MEMORY::__registerAll();
	FG_ERRNO_XML::__registerAll();

	FG_ERRNO_GAME::__registerAll();
}

/*
 *
 */
void fgErrorCodes::unregisterAll(void)
{
	fgErrno::reset();
}
