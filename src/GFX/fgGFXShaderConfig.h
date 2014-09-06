/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_SHADER_CONFIG_H_
#define _FG_GFX_SHADER_CONFIG_H_

#include "Util/fgConfig.h"

/*
 *
 */
class fgGfxShaderConfig : protected fgConfig {
protected:
public:
	//
	fgGfxShaderConfig();
	// 
	fgGfxShaderConfig(const char *filePath);
	// 
	virtual ~fgGfxShaderConfig();

	// 
	fgBool load(const char *filePath = NULL);

private:
};

#endif /* _FG_GFX_SHADER_CONFIG_H_ */
