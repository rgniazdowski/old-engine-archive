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
#include "fgLog.h"

inline unsigned int fgGLError(const char *afterFunc = NULL) {
	const char * invalidEnum = "An unacceptable value is specified for an enumerated argument.";
	const char * invalidValue = "A numeric argument is out of range.";
	const char * invalidOperation = "The specified operation is not allowed in the current state.";
	const char * outOfMemory = "There is not enough memory left to execute the command. The state of the GL is undefined";
	const char * invalidFBOp = "The command is trying to render to or read from the framebuffer while the currently bound framebuffer is not framebuffer complete (i.e. the return value from glCheckFramebufferStatus is not GL_FRAMEBUFFER_COMPLETE).";
	unsigned int retCode = 0;
	if(afterFunc == NULL)
		afterFunc = "gl*";
	fgGFXenum code = 0;
	while(FG_TRUE) {
		code = glGetError();
		if(code == GL_NO_ERROR)
			break;
		switch (code)
		{
		case GL_INVALID_ENUM:
			FG_LOG::PrintError("GL error GL_INVALID_ENUM (%d) after %s(): %s", code, afterFunc, invalidEnum);
			retCode = code;
			break;
		case GL_INVALID_VALUE:
			FG_LOG::PrintError("GL error GL_INVALID_VALUE (%d) after %s(): %s", code, afterFunc, invalidValue);
			retCode = code;
			break;
		case GL_INVALID_OPERATION:
			FG_LOG::PrintError("GL error GL_INVALID_OPERATION (%d) after %s(): %s", code, afterFunc, invalidOperation);
			retCode = code;
			break;
		case GL_OUT_OF_MEMORY:
			FG_LOG::PrintError("GL error GL_OUT_OF_MEMORY (%d) after %s(): %s", code, afterFunc, outOfMemory);
			retCode = code;
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			FG_LOG::PrintError("GL error GL_INVALID_FRAMEBUFFER_OPERATION (%d) after %s(): %s", code, afterFunc, invalidFBOp);
			retCode = code;
			break;
		default:
			break;
		}
	}
	return retCode;
}

#undef _FG_GFX_STD_INC_BLOCK__
#endif /* _FG_GFX_STD_INC_H_ */
