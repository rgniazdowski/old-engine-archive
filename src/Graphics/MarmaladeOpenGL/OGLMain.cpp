/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
 *******************************************************/

#include "OGLMain.h"
#include "../../fgCommon.h"

#if defined FG_USING_MARMALADE
#include "s3e.h"
#include "s3eTypes.h"
//#include "IwUtil.h"
//#include "s3eDevice.h"
#endif

// #FIXME
#if defined FG_USING_MARMALADE_EGL
static EGLSurface g_EGLSurface = NULL;
static EGLDisplay g_EGLDisplay = NULL;
static EGLContext g_EGLContext = NULL;
#endif

namespace OGL {
	
	bool initGL(void)
	{		
#if defined FG_USING_MARMALADE_EGL
		EGLint major;
		EGLint minor;
		EGLint numFound = 0;
		EGLConfig configList[FG_EGL_MAX_CONFIG];
		g_EGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
		if (!g_EGLDisplay)
		{
			s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "eglGetDisplay failed");
			return 1;
		}
		EGLBoolean res = eglInitialize(g_EGLDisplay, &major, &minor);
		if (!res)
		{
			s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "eglInitialize failed");
			return 1;
		}
		eglGetConfigs(g_EGLDisplay, configList, FG_EGL_MAX_CONFIG, &numFound);
		if (!numFound)
		{
			s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "eglGetConfigs failed to find any configs");
			return 1;
		}
		int config = -1;
		FG_InfoLog("found %d configs\n", numFound);
		for (int i = 0; i < numFound; i++)
		{
			EGLint renderable = 0;
			eglGetConfigAttrib(g_EGLDisplay, configList[i], EGL_RENDERABLE_TYPE, &renderable);
			if (renderable & EGL_OPENGL_ES2_BIT)
			{
				config = i;
				break;
			}
		}
		if (config == -1)
		{
			s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "No GLES2 configs reported.  Trying random config");
			config = 0;
		}
		int version = s3eGLGetInt(S3E_GL_VERSION)>>8;
		FG_InfoLog("requesting GL version: %d\n", version);
		FG_InfoLog("choosing config: %d\n", config);
		EGLint attribs[] = { EGL_CONTEXT_CLIENT_VERSION, version, EGL_NONE, };
		g_EGLContext = eglCreateContext(g_EGLDisplay, configList[config], NULL, attribs);
		if (!g_EGLContext)
		{
			s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "eglCreateContext failed");
			return 1;
		}
		version = s3eGLGetInt(S3E_GL_VERSION)>>8;
		if (version != 2)
		{
			FG_InfoLog("reported GL version: %d", version);
			s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "This example requires GLES v2.x");
			return 1;
		}
		void* nativeWindow = s3eGLGetNativeWindow();
		g_EGLSurface = eglCreateWindowSurface(g_EGLDisplay, configList[config], nativeWindow, NULL);
		eglMakeCurrent(g_EGLDisplay, g_EGLSurface, g_EGLSurface, g_EGLContext);
		return true;
#elif defined FG_USING_MARMALADE_IWGL
		return IwGLInit();
#endif
	}

	void closeGL(void)
	{
#if defined FG_USING_MARMALADE_EGL
		eglTerminate(g_EGLDisplay);
#elif defined FG_USING_MARMALADE_IWGL
		IwGLTerminate();
#endif
	}

	void swapBuffers(void)
	{
#if defined FG_USING_MARMALADE_EGL
		eglSwapBuffers(g_EGLDisplay, g_EGLSurface);
#elif defined FG_USING_MARMALADE_IWGL
		IwGLSwapBuffers();
#endif		
	}

	int getScreenHeight(void)
	{
		EGLint h = -1;
#if defined FG_USING_MARMALADE_EGL
		eglQuerySurface(g_EGLDisplay,g_EGLSurface,EGL_HEIGHT,&h);
#elif defined FG_USING_MARMALADE_IWGL
		h = IwGLGetInt(IW_GL_HEIGHT);
#endif	
		return (int)h;
	}

	int getScreenWidth(void)
	{
		EGLint w = -1;
#if defined FG_USING_MARMALADE_EGL
		eglQuerySurface(g_EGLDisplay,g_EGLSurface,EGL_WIDTH,&w);
#elif defined FG_USING_MARMALADE_IWGL
		w = IwGLGetInt(IW_GL_WIDTH);
#endif
		return w;
	}

	void clearScreen(void)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
};