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
#include "Textures/fgTextureResource.h"
#include "Hardware/fgHardwareState.h"

#if defined FG_USING_MARMALADE
#include "s3e.h"
#include "s3eTypes.h"
//#include "IwUtil.h" // ?
//#include "s3eDevice.h" // ?
#endif

#include "fgLog.h"
/*
 *
 */
fgGfxMain::fgGfxMain() :
	m_textureMgr(NULL),
	m_resourceMgr(NULL),
	m_shaderMgr(NULL),
	m_EGLSurface(NULL),
	m_EGLDisplay(NULL),
	m_EGLContext(NULL),
	m_screenW(-1),
	m_screenH(-1),
	m_init(FG_FALSE)
{
}

/*
 *
 */
fgGfxMain::~fgGfxMain()
{
	FG_LOG::PrintInfo("BEG: >>> fgGfxMain::~fgGfxMain();");
	if(m_init)
		closeGFX();
	if(m_textureMgr)
		delete m_textureMgr;
	if(m_shaderMgr)
		delete m_shaderMgr;

	m_textureMgr = NULL;
	m_resourceMgr = NULL;
	m_shaderMgr = NULL;
	
	FG_LOG::PrintDebug("END: <<< fgGfxMain::~fgGfxMain();");
}



/*
 *
 */
fgBool fgGfxMain::initGFX(void)
{
	FG_LOG::PrintDebug("BEG: >>> fgGfxMain::initGFX();");

#if defined FG_USING_MARMALADE_EGL
	EGLint major;
	EGLint minor;
	EGLint numFound = 0;
	EGLConfig configList[FG_EGL_MAX_CONFIG];

	m_EGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if (!m_EGLDisplay)
	{
		//s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "eglGetDisplay failed");
		FG_LOG::PrintError("eglGetDisplay failed");
		return FG_FALSE;
	}
	EGLBoolean res = eglInitialize(m_EGLDisplay, &major, &minor);
	if (!res)
	{
		//s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "eglInitialize failed");
		FG_LOG::PrintError("eglInitialize failed");
		return FG_FALSE;
	}
	eglGetConfigs(m_EGLDisplay, configList, FG_EGL_MAX_CONFIG, &numFound);
	if (!numFound)
	{
		//s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "eglGetConfigs failed to find any configs");
		FG_LOG::PrintError("eglGetConfigs failed to find any configs");
		return FG_FALSE;
	}
	int config = -1;
	FG_LOG::PrintInfo("found %d configs\n", numFound);
	for (int i = 0; i < numFound; i++)
	{
		EGLint renderable = 0;
		eglGetConfigAttrib(m_EGLDisplay, configList[i], EGL_RENDERABLE_TYPE, &renderable);
		if (renderable & EGL_OPENGL_ES2_BIT)
		{
			config = i;
			break;
		}
	}
	if (config == -1)
	{
		//s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "No GLES2 configs reported.  Trying random config");
		FG_LOG::PrintError("No GLES2 configs reported.  Trying random config");
		config = 0;
	}
	int version = s3eGLGetInt(S3E_GL_VERSION)>>8;
	FG_LOG::PrintInfo("requesting GL version: %d\n", version);
	FG_LOG::PrintInfo("choosing config: %d\n", config);
	EGLint attribs[] = { EGL_CONTEXT_CLIENT_VERSION, version, EGL_NONE, };
	m_EGLContext = eglCreateContext(m_EGLDisplay, configList[config], NULL, attribs);
	if (!m_EGLContext)
	{
		//s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "eglCreateContext failed");
		FG_LOG::PrintError("eglCreateContext failed");
		return FG_FALSE;
	}
	version = s3eGLGetInt(S3E_GL_VERSION)>>8;
	if (version != 2)
	{
		FG_LOG::PrintInfo("reported GL version: %d", version);
		FG_LOG::PrintError("Required GLES v2.x");
		//s3eDebugErrorShow(S3E_MESSAGE_CONTINUE, "Required GLES v2.x");
		return FG_FALSE;
	}
	void* nativeWindow = s3eGLGetNativeWindow();
	m_EGLSurface = eglCreateWindowSurface(m_EGLDisplay, configList[config], nativeWindow, NULL);
	eglMakeCurrent(m_EGLDisplay, m_EGLSurface, m_EGLSurface, m_EGLContext);
	
	glViewport(0,0,getScreenWidth(), getScreenHeight());
	FG_LOG::PrintInfo("Screen BPP: %d", s3eSurfaceGetInt(S3E_SURFACE_PIXEL_TYPE) & S3E_SURFACE_PIXEL_SIZE_MASK);
	FG_LOG::PrintInfo("Vendor : %s", (const char*)glGetString( GL_VENDOR ) );
	FG_LOG::PrintInfo("Renderer : %s", (const char*)glGetString( GL_RENDERER ) );
	FG_LOG::PrintInfo("Version : %s", (const char*)glGetString( GL_VERSION ) );
	FG_LOG::PrintInfo("Shading Lang Version : %s", (const char*)glGetString( GL_SHADING_LANGUAGE_VERSION ) );

	FG_LOG::PrintInfo("Extensions : %s\n", (const char*)glGetString( GL_EXTENSIONS ) );

	if(!m_shaderMgr)
		m_shaderMgr = new fgGfxShaderManager();
	#if defined FG_USING_OPENGL_ES
        glClearDepthf(1.0f);
    #else
        glClearDepth(1.0f);
    #endif
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	m_init = FG_TRUE;
	FG_LOG::PrintDebug("END: <<< fgGfxMain::initGFX();");
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
		m_resourceMgr = NULL;
		
#if defined FG_USING_MARMALADE_EGL
		if (m_EGLDisplay)
		{
			eglMakeCurrent(m_EGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
			eglDestroySurface(m_EGLDisplay, m_EGLSurface);
			eglDestroyContext(m_EGLDisplay, m_EGLContext);
		}
		eglTerminate(m_EGLDisplay);
		m_EGLDisplay = NULL;
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
	if(m_textureMgr) {
		// #ERROR - already initialized ?
		return FG_FALSE;
	}
	m_textureMgr = new fgTextureManager(resourceManager);
	m_resourceMgr = resourceManager;

	// should initialize ?

	return m_textureMgr->initialize();
}

/*
 *
 */
fgTextureManager *fgGfxMain::getTextureManager(void) const 
{
	return m_textureMgr;
}

/*
 *
 */
fgGfxShaderManager *fgGfxMain::getShaderManager(void) const
{
	return m_shaderMgr;
}

/*
 *
 */
fgBool fgGfxMain::preLoadShaders(void) const 
{
	if(!m_shaderMgr) {
		return FG_FALSE;
	}
	return m_shaderMgr->preLoadShaders();
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
