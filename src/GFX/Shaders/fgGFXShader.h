/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_SHADER_H_
#define _FG_GFX_SHADER_H_

#include "fgGFXShaderDefs.h"

class fgGfxShader {
protected:
	fgGFXuint m_shaderGfxID;
	fgGfxShaderType m_type;
public:
	fgGfxShader() {}
	~fgGfxShader() {}
};

#endif /* _FG_GFX_SHADER_H_ */
