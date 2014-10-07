/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GFX_GL_H_
#define _FG_GFX_GL_H_

#include "fgBuildConfig.h"
#include "fgBool.h"
#include "fgLog.h"

#ifndef FG_GFX_GL_INCLUDES_FINISHED
#define FG_GFX_GL_INCLUDES_FINISHED

#if defined FG_USING_MARMALADE
//	MARMALADE SPECIFIC CODE

#	if !defined FG_USING_MARMALADE_OPENGL_ES && defined FG_USING_MARMALADE_IWGL
#		include <IwGL.h>
#		define _FG_INCLUDED_GL_ // #FIXME
#	endif /* FG_USING_MARMALADE_OPENGL_ES */

#elif defined FG_USING_PLATFORM_LINUX /* && !defined FG_USING_MARMALADE */
//	GFX includes for OpenGL/SDL - platform LINUX

#	if defined FG_USING_OPENGL

#		ifndef FG_USING_SDL2
#                       define GL_GLEXT_PROTOTYPES
#			include <GL/gl.h>
#			include <GL/glext.h>
#			define _FG_INCLUDED_GL_
#		else /* FG_USING_SDL2 */
// if defined SDL2 - then use specific GL code for SDL2
#			include <SDL2/SDL.h>
#			include <SDL2/SDL_opengl.h>
#		endif

#	else /* FG_USING_OPENGL */

#		if defined FG_USING_SDL2
#			include <SDL2/SDL.h>
#		endif

#	endif /* FG_USING_OPENGL */

#endif /* FG_USING_MARMALADE */

#	if defined FG_USING_OPENGL_ES

#		if defined FG_USINGL_SDL2
#			include <SDL2/SDL.h>
#			include <SDL2/SDL_opengles2.h>
#		else /* if SDL2 is not defined - native GLES2 support ? */
#			include <GLES2/gl2.h>
#			include <GLES2/gl2ext.h>
#			include <GLES2/gl2platform.h>
#			define _FG_INCLUDED_GL_
#		endif /* defined FG_USINGL_SDL2 */

#		if defined FG_USING_EGL
#			include <EGL/egl.h>
#			define FG_EGL_MAX_CONFIG 32
#		endif /* FG_USING_EGL */

#	endif /* FG_USING_OPENGL_ES */

#endif /* FG_GFX_GL_INCLUDES_FINISHED */

// #FIXME | this can be also used for EGL / SDL ? make it universal?
inline unsigned int fgGLError(const char *afterFunc = NULL) 
{
	static unsigned int repeatCnt = 0;
	static const char *lastError = NULL;
	static unsigned int lastCode = 0;

	const char * invalidEnum = "An unacceptable value is specified for an enumerated argument.";
	const char * invalidValue = "A numeric argument is out of range.";
	const char * invalidOperation = "The specified operation is not allowed in the current state.";
	const char * outOfMemory = "There is not enough memory left to execute the command. The state of the GL is undefined";
	const char * invalidFBOp = "The command is trying to render to or read from the framebuffer while the currently bound framebuffer is not framebuffer complete (i.e. the return value from glCheckFramebufferStatus is not GL_FRAMEBUFFER_COMPLETE).";
	unsigned int retCode = 0;
	if(afterFunc == NULL)
		afterFunc = "gl*";
	unsigned int code = 0;

	while(FG_TRUE) {
		code = glGetError();

		if(code == GL_NO_ERROR)
			break;
		if(repeatCnt >= 2 && lastCode == code) {
			break;
		} else if(lastCode != code) {
			repeatCnt = 0;
		}
		switch (code)
		{
		case GL_INVALID_ENUM:
			FG_LOG::PrintError("GL error GL_INVALID_ENUM after %s(): %s", afterFunc, invalidEnum);
			retCode = code;
			break;
		case GL_INVALID_VALUE:
			FG_LOG::PrintError("GL error GL_INVALID_VALUE after %s(): %s", afterFunc, invalidValue);
			retCode = code;
			break;
		case GL_INVALID_OPERATION:
			FG_LOG::PrintError("GL error GL_INVALID_OPERATION after %s(): %s", afterFunc, invalidOperation);
			retCode = code;
			break;
		case GL_OUT_OF_MEMORY:
			FG_LOG::PrintError("GL error GL_OUT_OF_MEMORY after %s(): %s", afterFunc, outOfMemory);
			retCode = code;
			break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			FG_LOG::PrintError("GL error GL_INVALID_FRAMEBUFFER_OPERATION after %s(): %s", afterFunc, invalidFBOp);
			retCode = code;
			break;
		default:
			break;
		}
		if(lastCode == code)
			repeatCnt++;
		
		lastCode = code;
		// ?
		if(afterFunc) {
			lastError = afterFunc;
		} else {
			lastError = NULL;
		}
	}
	return retCode;
}

// #FIXME | this can be also used for EGL / SDL ? make it universal?
inline unsigned int fgEGLError(const char *afterFunc = NULL) 
{
	std::map<unsigned int, const char *> errMap;
	// !FIXME
	errMap[EGL_SUCCESS] = "The last function succeeded without error.";
	errMap[EGL_NOT_INITIALIZED] = "EGL is not initialized, or could not be initialized, for the specified EGL display connection.";
	errMap[EGL_BAD_ACCESS] = "EGL cannot access a requested resource (for example a context is bound in another thread).";
	errMap[EGL_BAD_ALLOC] = "EGL failed to allocate resources for the requested operation.";
	errMap[EGL_BAD_ATTRIBUTE] = "An unrecognized attribute or attribute value was passed in the attribute list.";
	errMap[EGL_BAD_CONTEXT] = "An EGLContext argument does not name a valid EGL rendering context.";
	errMap[EGL_BAD_CONFIG] = "An EGLConfig argument does not name a valid EGL frame buffer configuration.";
	errMap[EGL_BAD_CURRENT_SURFACE] = "The current surface of the calling thread is a window, pixel buffer or pixmap that is no longer valid.";
	errMap[EGL_BAD_DISPLAY] = "An EGLDisplay argument does not name a valid EGL display connection.";
	errMap[EGL_BAD_SURFACE] = "An EGLSurface argument does not name a valid surface (window, pixel buffer or pixmap) configured for GL rendering.";
	errMap[EGL_BAD_MATCH] = "Arguments are inconsistent (for example, a valid context requires buffers not supplied by a valid surface).";
	errMap[EGL_BAD_PARAMETER] = "One or more argument values are invalid.";
	errMap[EGL_BAD_NATIVE_PIXMAP] = "A NativePixmapType argument does not refer to a valid native pixmap.";
	errMap[EGL_BAD_NATIVE_WINDOW] = "A NativeWindowType argument does not refer to a valid native window.";
	errMap[EGL_CONTEXT_LOST] = "A power management event has occurred. The application must destroy all contexts and reinitialise OpenGL ES state and objects to continue rendering. ";

	unsigned int retCode = 0;
	if(afterFunc == NULL)
		afterFunc = "gl*";
	unsigned int code = 0;

	while(FG_TRUE) {
		code = eglGetError();
		if(code == EGL_SUCCESS)
			break;
		switch (code)
		{
		case EGL_NOT_INITIALIZED:
			FG_LOG::PrintError("EGL error NOT_INITIALIZED after %s(): %s", afterFunc, errMap[code]);
			retCode = code;
			break;
		case EGL_BAD_ACCESS:
			FG_LOG::PrintError("EGL error BAD_ACCESS after %s(): %s", afterFunc, errMap[code]);
			retCode = code;
			break;
		case EGL_BAD_ALLOC:
			FG_LOG::PrintError("EGL error BAD_ALLOC after %s(): %s", afterFunc, errMap[code]);
			retCode = code;
			break;
		case EGL_BAD_ATTRIBUTE:
			FG_LOG::PrintError("EGL error BAD_ATTRIBUTE after %s(): %s", afterFunc, errMap[code]);
			retCode = code;
			break;
		case EGL_BAD_CONTEXT:
			FG_LOG::PrintError("EGL error BAD_CONTEXT after %s(): %s", afterFunc, errMap[code]);
			retCode = code;
			break;
		case EGL_BAD_CONFIG:
			FG_LOG::PrintError("EGL error BAD_CONFIG after %s(): %s", afterFunc, errMap[code]);
			retCode = code;
			break;
		case EGL_BAD_CURRENT_SURFACE:
			FG_LOG::PrintError("EGL error BAD_CURRENT_SURFACE after %s(): %s", afterFunc, errMap[code]);
			retCode = code;
			break;
		case EGL_BAD_DISPLAY:
			FG_LOG::PrintError("EGL error BAD_DISPLAY after %s(): %s", afterFunc, errMap[code]);
			retCode = code;
			break;
		case EGL_BAD_SURFACE:
			FG_LOG::PrintError("EGL error BAD_SURFACE after %s(): %s", afterFunc, errMap[code]);
			retCode = code;
			break;
		case EGL_BAD_MATCH:
			FG_LOG::PrintError("EGL error BAD_MATCH after %s(): %s", afterFunc, errMap[code]);
			retCode = code;
			break;
		case EGL_BAD_PARAMETER:
			FG_LOG::PrintError("EGL error BAD_PARAMETER after %s(): %s", afterFunc, errMap[code]);
			retCode = code;
			break;
		case EGL_BAD_NATIVE_PIXMAP:
			FG_LOG::PrintError("EGL error BAD_NATIVE_PIXMAP after %s(): %s", afterFunc, errMap[code]);
			retCode = code;
			break;
		case EGL_BAD_NATIVE_WINDOW:
			FG_LOG::PrintError("EGL error BAD_NATIVE_WINDOW after %s(): %s", afterFunc, errMap[code]);
			retCode = code;
			break;
		case EGL_CONTEXT_LOST:
			FG_LOG::PrintError("EGL error CONTEXT_LOST after %s(): %s", afterFunc, errMap[code]);
			retCode = code;
			break;
		default:
			FG_LOG::PrintError("EGL error after %s(): %s", afterFunc, errMap[code]);
			break;
		}
	}
	return retCode;
}

#ifndef FG_GFX_FALSE
#define FG_GFX_FALSE	GL_FALSE
#endif

#ifndef FG_GFX_TRUE
#define FG_GFX_TRUE		GL_TRUE
#endif

#endif /* _FG_GFX_GL_H_ */
