/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgBuildConfig.h"
#include "fgCommon.h"
#include "fgGFXMain.h"

#if defined FG_USING_MARMALADE
#include "s3e.h"
#include "s3eTypes.h"
//#include "IwUtil.h" // ?
//#include "s3eDevice.h" // ?
#endif

#include "fgLog.h"

// #FIXME
#if defined FG_USING_EGL
static EGLSurface g_EGLSurface = NULL;
static EGLDisplay g_EGLDisplay = NULL;
static EGLContext g_EGLContext = NULL;
#endif

/*
 *
 */
fgGfxMain::fgGfxMain() :
	m_init(FG_FALSE),
	m_textureManager(NULL),
	m_resourceManager(NULL)
{
}

/*
 *
 */
fgGfxMain::~fgGfxMain()
{
	if(m_init)
		closeGFX();
	if(m_textureManager)
		delete m_textureManager;
	m_textureManager = NULL;
	m_resourceManager = NULL;
}

/*
 *
 */
fgBool fgGfxMain::initGFX(void)
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
		return FG_FALSE;
	}
	EGLBoolean res = eglInitialize(g_EGLDisplay, &major, &minor);
	if (!res)
	{
		s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "eglInitialize failed");
		return FG_FALSE;
	}
	eglGetConfigs(g_EGLDisplay, configList, FG_EGL_MAX_CONFIG, &numFound);
	if (!numFound)
	{
		s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "eglGetConfigs failed to find any configs");
		return FG_FALSE;
	}
	int config = -1;
	FG_LOG::PrintInfo("found %d configs\n", numFound);
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
	FG_LOG::PrintInfo("requesting GL version: %d\n", version);
	FG_LOG::PrintInfo("choosing config: %d\n", config);
	EGLint attribs[] = { EGL_CONTEXT_CLIENT_VERSION, version, EGL_NONE, };
	g_EGLContext = eglCreateContext(g_EGLDisplay, configList[config], NULL, attribs);
	if (!g_EGLContext)
	{
		s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "eglCreateContext failed");
		return FG_FALSE;
	}
	version = s3eGLGetInt(S3E_GL_VERSION)>>8;
	if (version != 2)
	{
		FG_LOG::PrintInfo("reported GL version: %d", version);
		s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "This example requires GLES v2.x");
		return FG_FALSE;
	}
	void* nativeWindow = s3eGLGetNativeWindow();
	g_EGLSurface = eglCreateWindowSurface(g_EGLDisplay, configList[config], nativeWindow, NULL);
	eglMakeCurrent(g_EGLDisplay, g_EGLSurface, g_EGLSurface, g_EGLContext);
	m_init = FG_TRUE;
	return FG_TRUE;
#elif defined FG_USING_MARMALADE_IWGL
	// #FIXME ! m_init = FG_TRUE
	return IwGLInit();
#endif
}

/*
 *
 */
void fgGfxMain::closeGFX(void)
{
	if(m_init) 
	{
		m_resourceManager = NULL;
		
#if defined FG_USING_MARMALADE_EGL
		if (g_EGLDisplay)
		{
			eglMakeCurrent(g_EGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
			eglDestroySurface(g_EGLDisplay, g_EGLSurface);
			eglDestroyContext(g_EGLDisplay, g_EGLContext);
		}
		eglTerminate(g_EGLDisplay);
		g_EGLDisplay = 0;
#elif defined FG_USING_MARMALADE_IWGL
		IwGLTerminate();
#endif
	}
	m_init = FG_FALSE;
}

/*
 *
 */
void fgGfxMain::swapBuffers(void)
{
#if defined FG_USING_MARMALADE_EGL
	eglSwapBuffers(g_EGLDisplay, g_EGLSurface);
#elif defined FG_USING_MARMALADE_IWGL
	IwGLSwapBuffers();
#endif
}

/*
 *
 */
int fgGfxMain::getScreenHeight(void)
{
#if defined FG_USING_MARMALADE_EGL
	EGLint h = -1;
	eglQuerySurface(g_EGLDisplay,g_EGLSurface,EGL_HEIGHT,&h);
#elif defined FG_USING_MARMALADE_IWGL
	int h = IwGLGetInt(IW_GL_HEIGHT);
#else
	int h = 0;
#endif
	return (int)h;
}

/*
 *
 */
int fgGfxMain::getScreenWidth(void)
{
#if defined FG_USING_MARMALADE_EGL
	EGLint w = -1;
	eglQuerySurface(g_EGLDisplay,g_EGLSurface,EGL_WIDTH,&w);
#elif defined FG_USING_MARMALADE_IWGL
	int w = IwGLGetInt(IW_GL_WIDTH);
#else
	int w = 0;
#endif
	return w;
}

/*
 *
 */
void fgGfxMain::clearScreen(void)
{
#if defined FG_USING_OPENGL || defined FG_USING_OPENGL_ES
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif
}


/*
 *
 */
void fgGfxMain::display(void)
{
}

/*
 *
 */
void fgGfxMain::render(void)
{
	// #TODO / #FIXME - all the crap with FG_GFX namespace should be somehow put into classes
	// currently the model for handling different rendering APIs sux so much its too hard
	// to put it in words - however its still not clear whether to stay with the namespace tag name
	clearScreen();

	// #MARKED
	// proper rendering calls go here
	// render something and shit

	// #CRAP
	// the code below should be removed
#if 0
	// V- & T-database INDEXES
	GLushort defaultIndices[] = { 0, 1, 3, 2 };

	float size_x = 100.0f;
	float size_y = 150.0f;

	fgVector2f vertexArray[] = {
		fgVector2f(0.0f, 0.0f),
		fgVector2f(size_x, 0.0f),
		fgVector2f(size_x, size_y),
		fgVector2f(0.0f, size_y)
	};

	glLoadIdentity();
	glTranslatef(FG_GFX::getScreenWidth()/2.0f, FG_GFX::getScreenHeight()/2.0f, 0.0f);
	glRotatef((FG_GetTicks()/4)%360, 0.0f, 0.0f, 1.0f);
	// Activate and specify pointer to vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor4f(1.0f, 0.25f, 0.25f, 1.0f);
	glVertexPointer(2, GL_FLOAT, 0, (GLvoid *)vertexArray);

    // DRAW
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, defaultIndices);

	// glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	// Deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
#endif
	// After rendering swap buffers so the changes are visible on the screen
	swapBuffers();
}

/*
 *
 */
fgBool fgGfxMain::setResourceManager(fgManagerBase *resourceManager)
{
	if(!resourceManager)
		return FG_FALSE;
	if(m_textureManager) {
		// #ERROR - already initialized ?
		return FG_FALSE;
	}
	
	m_textureManager = new fgTextureManager(resourceManager);
	m_resourceManager = resourceManager;

	// should initialize ?

	return m_textureManager->initialize();
}

/*
 *
 */
fgTextureManager *fgGfxMain::getTextureManager(void) const {
	return m_textureManager;
}

/*
 *
 */
fgBool fgGfxMain::releaseTextures(void)
{
	if(m_textureManager) {
		m_textureManager->allReleaseGFX();
		m_textureManager->allReleaseNonGFX();
		delete m_textureManager;
		m_textureManager = NULL;
	}
	m_resourceManager = NULL;
	return FG_TRUE;
}
