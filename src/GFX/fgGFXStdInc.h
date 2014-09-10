/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_STD_INC_H_
#define _FG_GFX_STD_INC_H_
#define _FG_GFX_STD_INC_BLOCK__

#ifdef _FG_GFX_TYPES_BLOCK__
#error "FG_GFX_TYPES_BLOCK constant is defined. Do not include GfxStdInc inside of Gfx Types header."
#endif

#include "fgBuildConfig.h"

#ifndef FG_GFX_GL_INCLUDES_FINISHED
#define FG_GFX_GL_INCLUDES_FINISHED

#if defined FG_USING_MARMALADE

#if !defined FG_USING_MARMALADE_OPENGL_ES && defined FG_USING_MARMALADE_IWGL
#include <IwGL.h>
#endif // FG_USING_MARMALADE_OPENGL_ES

#elif defined FG_USING_PLATFORM_LINUX

#ifdef FG_USING_OPENGL
#include <GL/gl.h>
#endif // FG_USING_OPENGL

#endif // FG_USING_MARMALADE

#if defined FG_USING_OPENGL_ES
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>

#if defined FG_USING_EGL
#include <EGL/egl.h>
#define FG_EGL_MAX_CONFIG 32
#endif // FG_USING_EGL
#endif // FG_USING_OPENGL_ES

#endif // FG_GFX_GL_INCLUDES_FINISHED
#include "fgTypes.h"
#include "fgGFXTypes.h"

#undef _FG_GFX_STD_INC_BLOCK__
#endif /* _FG_GFX_STD_INC_H_ */
