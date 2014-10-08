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
#include "fgGFXMVPMatrix.h"
#include "fgGFXModelResource.h"
#include "Textures/fgTextureResource.h"
#include "Hardware/fgHardwareState.h"

#include "fgGFXErrorCodes.h"

#if defined FG_USING_MARMALADE
#include "s3e.h"
#include "s3eTypes.h"
#endif

#include "fgLog.h"
fgGfxMVPMatrix *MVP = NULL;
fgGfxCameraAnimation *cameraAnim = NULL;
fgGFXuint vboIds[4] = {0,0,0,0};

/*
 *
 */
fgGfxMain::fgGfxMain() :
	m_textureMgr(NULL),
	m_resourceMgr(NULL),
	m_shaderMgr(NULL),
	m_mainWindow(NULL),
	m_gfxContext(NULL),
	m_init(FG_FALSE)
{
	cameraAnim = new fgGfxCameraAnimation(); // #FIXME
	MVP = new fgGfxMVPMatrix(); // #FIXME !
}

/*
 *
 */
fgGfxMain::~fgGfxMain()
{
	if(glIsBuffer(vboIds[0]))
		glDeleteBuffers(1, &vboIds[0]);
	if(glIsBuffer(vboIds[1]))
		glDeleteBuffers(1, &vboIds[1]);
	if(MVP)
		delete MVP;
	MVP = NULL;
	if(cameraAnim)
		delete cameraAnim;
	cameraAnim = NULL; // #FIXME
	if(m_init)
		closeGFX();
	if(m_textureMgr)
		delete m_textureMgr;
	if(m_shaderMgr)
		delete m_shaderMgr;
	if(m_mainWindow)
		delete m_mainWindow;

	m_textureMgr = NULL;
	m_resourceMgr = NULL;
	m_shaderMgr = NULL;
	m_mainWindow = NULL;
}

/*
 *
 */
fgBool fgGfxMain::initGFX(void)
{
	fgStatusReporter::clearStatus();
	fgBool status = FG_TRUE;

	if(!fgGfxPlatform::initialize()) {
		// ERROR
		status = FG_FALSE;
	}
	if(status) {
		m_gfxContext = fgGfxPlatform::context();
	}
	if(!m_mainWindow && status) {
		m_mainWindow = new fgGfxWindow();
	}
	if(m_mainWindow && status) {
		// #FIXME - resolution FIXME!
		if(!m_mainWindow->setup(FG_PACKAGE_FULL_TEXT, 1024, 768)) {
			delete m_mainWindow;
			m_mainWindow = NULL;
			status = FG_FALSE;
		}
	}
	//FG_LOG::PrintInfo("S3E Screen BPP: %d", s3eSurfaceGetInt(S3E_SURFACE_PIXEL_TYPE) & S3E_SURFACE_PIXEL_SIZE_MASK);
	if(status) {
		if(!m_shaderMgr)
			m_shaderMgr = new fgGfxShaderManager();

		FG_LOG::PrintDebug("GFX: Setting viewport (0, 0, %d, %d)", m_mainWindow->getWidth(), m_mainWindow->getHeight());
		m_gfxContext->viewport(0, 0, m_mainWindow->getWidth(), m_mainWindow->getHeight());
		m_gfxContext->clearDepth(1.0f);
		m_gfxContext->setDepthTest(FG_TRUE);
		m_gfxContext->depthFunc(GL_LEQUAL);
		m_gfxContext->setCullFace(FG_TRUE);
		m_gfxContext->frontFace(GL_CCW);
		m_gfxContext->cullFace(GL_BACK);
		m_gfxContext->setScissorTest(FG_TRUE);
		m_gfxContext->scissor(0, 0, m_mainWindow->getWidth(), m_mainWindow->getHeight());
		MVP->setPerspective(45.0f, m_mainWindow->getAspect());
		m_init = FG_TRUE;
	}
	if(status) {
		reportSuccess(FG_ERRNO_GFX_OK, "GFX subsystem initialized successfully");
	}
	return status;
}

/*
 *
 */
void fgGfxMain::closeGFX(void)
{
	if(m_init) 
	{
		if(m_mainWindow)
			m_mainWindow->close();
		fgGfxPlatform::quit();
		m_gfxContext = NULL;
	}
	m_init = FG_FALSE;
}

/*
 *
 */
fgBool fgGfxMain::suspendGFX(void)
{
	fgBool status = FG_TRUE;
	if(!m_init) {
		status = FG_FALSE;
	}
	if(m_textureMgr && status)
		m_textureMgr->allReleaseGFX();
	if(m_shaderMgr && status) {
		if(!m_shaderMgr->allReleaseGFX())
			status = FG_FALSE;
	}
	{
		// FIXME
		if(glIsBuffer(vboIds[0]) && glIsBuffer(vboIds[1])) {
			glDeleteBuffers(2, vboIds);
			FG_LOG::PrintDebug("GFX: VBOS RELEASE... RESET.");

		}
		memset(vboIds, 0, sizeof(vboIds));
		// FIXME
	}
	if(status)
		closeGFX();
	if(!status)
		reportWarning(FG_ERRNO_GFX_OK, "Suspension of GFX subsystem finished with errors");
	else
		reportWarning(FG_ERRNO_GFX_OK, "Suspension of GFX subsystem finished with no errors");
	return status;
}

/*
 *
 */
fgBool fgGfxMain::resumeGFX(void)
{
	fgBool status = FG_TRUE;
	if(!fgGfxMain::initGFX())
		status = FG_FALSE;
	if(m_textureMgr && status)
		if(!m_textureMgr->allToVRAM(FG_TRUE))
			status = FG_FALSE;
	// This will compile all shaders, not just the used ones
	// #FIXME #P1
	if(m_shaderMgr && m_textureMgr) {
		if(!m_shaderMgr->compileShaders())
			status = FG_FALSE;
		if(!m_shaderMgr->linkShaders())
			status = FG_FALSE;
	}
	// REGENERATE VBOS #TODO

	if(!status)
		reportWarning(FG_ERRNO_GFX_OK, "Resume of GFX subsystem finished with errors");
	else
		reportWarning(FG_ERRNO_GFX_OK, "Resume of GFX subsystem finished with no errors");
	return status;
}

/*
 *
 */
void fgGfxMain::display(void)
{
	if(!m_gfxContext)
		return;
}

void drawModel(fgGfxModelResource *model, fgGfxShaderProgram *program, fgTextureResource *texture = NULL)
{
	static fgBool buffInit = FG_FALSE;
	if(!model)
		return;

	GLuint offset = 0;
	fgGFXint vtxStride = sizeof(fgVertex3);
	if(model->getRefShapes().empty()) {
		return;
	}
	fgGfxMeshBase *mesh = model->getRefShapes()[0]->mesh;
	if(mesh->isSoA() == FG_TRUE) {
		fgGfxMeshSoA *soa = (fgGfxMeshSoA *)mesh;
		fgGFXint numVertices = soa->getNumVertices();
		fgGFXint numNormals = soa->getNumNormals();
		fgGFXint numUVs = soa->getNumUVs();
		fgGFXint numIndices = soa->getNumIndices();

		fgGfxPlatform::context()->bindBuffer(GL_ARRAY_BUFFER, 0);
		fgGfxPlatform::context()->bindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		//glEnableVertexAttribArray(FG_GFX_ATTRIB_POS_LOCATION);
		//glEnableVertexAttribArray(FG_GFX_ATTRIB_NORM_LOCATION);
		//glEnableVertexAttribArray(FG_GFX_ATTRIB_UVS_LOCATION);
		fgGfxPlatform::context()->diffVertexAttribArrayMask(soa->attribMask());
		fgGfxPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION, 3 /* VEC3 */,
			FG_GFX_FLOAT, GL_FALSE, sizeof(fgVector3f),	(void*)(&soa->vertices.front()));

		offset += 3 /* VEC3 */ * sizeof(fgGFXfloat);
	
		fgGfxPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_NORM_LOCATION,	3 /* VEC3 */,
		FG_GFX_FLOAT, GL_FALSE, sizeof(fgVector3f), (void*)(&soa->normals.front()));

		offset += 3 /* VEC3 */ * sizeof(fgGFXfloat);

		fgGfxPlatform::context()->vertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,	2 /* VEC2 */,
		FG_GFX_FLOAT, GL_FALSE, sizeof(fgVector2f), (void*)(&soa->uvs.front()));

		if(texture && program) {
		// Bind our texture in Texture Unit 0
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture->getTextureGfxID());
			fgGFXint TextureID = glGetUniformLocation(program->getGfxID(), "s_texture");
			// Set our "myTextureSampler" sampler to user Texture Unit 0
			glUniform1i(TextureID, 0);
		}

		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, (const void*)(&soa->indices.front()));
		fgGLError("GL_TRIANGLES glDrawElements");
		glDisableVertexAttribArray(FG_GFX_ATTRIB_POS_LOCATION);
		glDisableVertexAttribArray(FG_GFX_ATTRIB_NORM_LOCATION);
		glDisableVertexAttribArray(FG_GFX_ATTRIB_UVS_LOCATION);

		return;
	}
	fgGfxMeshAoS *aos = (fgGfxMeshAoS *)mesh;
	fgGFXint numVertices = aos->getNumVertices();
	fgGFXint numIndices = aos->getNumIndices();
	// vboIds[0] - used to store vertex attribute data
	// vboIds[l] - used to store element indices
	fgGFXvoid *vtxBuf = aos->vertices.front();
	fgGFXvoid *indices = (fgGFXvoid *)(&aos->indices.front());
	if(!glIsBuffer(vboIds[0]) || !glIsBuffer(vboIds[1])) {
		buffInit = FG_FALSE;
		FG_LOG::PrintDebug("GFX: VBOS NOT PROPER, BUFF INIT FALSE...");
	}
	if ( vboIds[0] == 0 && vboIds[1] == 0  && !buffInit)
	{
		// Only allocate on the first draw
		glGenBuffers(2, vboIds);
		glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
		glBufferData(GL_ARRAY_BUFFER, vtxStride * numVertices, vtxBuf, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,	sizeof(fgGFXushort) * numIndices, indices, GL_STATIC_DRAW);

		buffInit = FG_TRUE;
		FG_LOG::PrintDebug("GFX: GENERATING VBOS...");
		FG_LOG::PrintDebug("GFX: VBO[0] = %d", vboIds[0]);
		FG_LOG::PrintDebug("GFX: VBO[1] = %d", vboIds[1]);
	}
	if(!buffInit) {
		FG_LOG::PrintDebug("GFX: NO BUFFERS. EXIT DRAW...");
		return;
	}
	glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);

	glEnableVertexAttribArray(FG_GFX_ATTRIB_POS_LOCATION);
	glEnableVertexAttribArray(FG_GFX_ATTRIB_NORM_LOCATION);
	glEnableVertexAttribArray(FG_GFX_ATTRIB_UVS_LOCATION);

	glVertexAttribPointer(FG_GFX_ATTRIB_POS_LOCATION, 3 /* VEC3 */,
	FG_GFX_FLOAT, GL_FALSE, vtxStride,	(const void*)offset);
	fgGLError("Position glVertexAttribPointer");

	offset += 3 /* VEC3 */ * sizeof(fgGFXfloat);
	
	glVertexAttribPointer(FG_GFX_ATTRIB_NORM_LOCATION,	3 /* VEC3 */,
	FG_GFX_FLOAT, GL_FALSE, vtxStride, (const void*)offset);
	fgGLError("Normals glVertexAttribPointer");

	offset += 3 /* VEC3 */ * sizeof(fgGFXfloat);

	glVertexAttribPointer(FG_GFX_ATTRIB_UVS_LOCATION,	2 /* VEC2 */,
	FG_GFX_FLOAT, GL_FALSE, vtxStride, (const void*)offset);
	fgGLError("UVs glVertexAttribPointer");

	if(texture && program) {
	// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->getTextureGfxID());
		fgGFXint TextureID = glGetUniformLocation(program->getGfxID(), "s_texture");
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);
	}

	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
	fgGLError("GL_TRIANGLES glDrawElements");
	glDisableVertexAttribArray(FG_GFX_ATTRIB_POS_LOCATION);
	glDisableVertexAttribArray(FG_GFX_ATTRIB_NORM_LOCATION);
	glDisableVertexAttribArray(FG_GFX_ATTRIB_UVS_LOCATION);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	fgGLError("glBindBuffer");
}

void dumpMatrix(const float *mat, const char *title)
{
	if(title)
		printf("%s MATRIX:\n", title);
	printf("{ %.2f %.2f %.2f %.2f }\n", mat[0], mat[1], mat[2], mat[3]);
	printf("{ %.2f %.2f %.2f %.2f }\n", mat[4], mat[5], mat[6], mat[7]);
	printf("{ %.2f %.2f %.2f %.2f }\n", mat[8], mat[9], mat[10], mat[11]);
	printf("{ %.2f %.2f %.2f %.2f }\n\n", mat[12], mat[13], mat[14], mat[15]);
	
}
#include "fgGFXPrimitives.h"
#include "GUI/Font/fgFontDrawer.h"
/*
 *
 */
void fgGfxMain::render(void)
{
	static float posx = 0;
	static float posy = 0;
	static float offset = 0.0f;
	static fgGfxModelResource *model = NULL;
	static float rotxyz = 0.0f;
	static float scale = 1.0f;
	bool loadModel = true;
	glm::mat4 Model;

	if(!m_mainWindow || !m_gfxContext) {
		FG_LOG::PrintError("Main window / context is NULL");
		return;
	}
	fgGLError();
	m_mainWindow->clearColor();
	fgResourceManager *rm = NULL;
	
	std::string sPlainEasyShaderName("sPlainEasy");
	std::string sOrthoEasyShaderName("sOrthoEasy");
	std::string modelname("CobraBomber");
	std::string texname("CobraBomberTexture");
	std::string texname4("TrueCrimes");

	offset = fmodf(offset + 0.2f, 2*3.141f);
	if(!m_textureMgr || !m_shaderMgr) {
		FG_LOG::PrintError("No texture / shader manager");
		return;

	}
	rm = m_textureMgr->getResourceManager();
	if(!rm) {
		FG_LOG::PrintError("Cant access resource manager.");

		return;
	}
#if 1
	loadModel = false;
	if(loadModel) {
		if(!model)
			model = (fgGfxModelResource *)rm->get(modelname);
		if(!model) {
			printf ("NO MODEL\n");
			return;
		}
	
	}
	cameraAnim->setDT((float)FG_HardwareState->getDelta());
	cameraAnim->update();
	fgMatrix4f modelMat = glm::rotate(glm::mat4(1.0f), rotxyz, glm::vec3(1.0f, 1.0f, 1.0f));//fgMath::translate(fgMatrix4f(1.0f), fgVector3f(0.0f, 0.0f, -5.0f));
	
	MVP->setPerspective(45.0f, m_mainWindow->getAspect());
	MVP->calculate(cameraAnim, modelMat);

	fgGfxShaderProgram *program = m_shaderMgr->get(sPlainEasyShaderName);
	m_shaderMgr->useProgram(program);
	if(!program) {
		FG_LOG::PrintError("Cant access sPlainEasy shader program.");
		return;
	}

	fgTextureResource *texture = (fgTextureResource *) rm->get(texname);
	program->setUniform(FG_GFX_PHASE, offset);
	program->setUniform(MVP);
	program->setUniform(FG_GFX_CUSTOM_COLOR, 1.0f, 0.0f, 0.0f, 1.0f);

	rotxyz += 0.0094525f;
	if(rotxyz > M_PI*2.0f)
		rotxyz = 0.0f;

	if(loadModel)
		drawModel(model, program,  texture);
#endif
	fgGfxShaderProgram *program2 = m_shaderMgr->get(sOrthoEasyShaderName);
	if(!program2) {
		FG_LOG::PrintError("Cant access sOrthoEasy shader program.");
		return;
	}
	m_shaderMgr->useProgram(program2);

	if(s3eKeyboardGetState(s3eKeyLeft) & S3E_KEY_STATE_DOWN) {
		posx-=10.0f;
	}
	if(s3eKeyboardGetState(s3eKeyRight) & S3E_KEY_STATE_DOWN) {
		posx+=10.0f;
	}
	if(s3eKeyboardGetState(s3eKeyUp) & S3E_KEY_STATE_DOWN) {
		posy-=10.0f;
	}
	if(s3eKeyboardGetState(s3eKeyDown) & S3E_KEY_STATE_DOWN) {
		posy+=10.0f;
	}
	if(s3eKeyboardGetState(s3eKeyRightShift) & S3E_KEY_STATE_DOWN) {
		scale += 0.01f;
	}
	fgGfxPlatform::context()->setBlend(FG_TRUE);
	fgGfxPlatform::context()->blendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	Model = glm::translate(Model, glm::vec3(posx, posy, 0.0f));

	MVP->identity();
	MVP->setOrtho(0, (float)m_mainWindow->getWidth(), (float)m_mainWindow->getHeight(), 0.0f);
	MVP->calculate(Model);
	program2->setUniform(MVP);
	
	FG_HardwareState->calculateDT();
	FG_HardwareState->calculateFPS();
	fgGfxPlatform::context()->setBlend(FG_FALSE);
	fgGfxPlatform::context()->scissor(0, 0, m_mainWindow->getWidth(), m_mainWindow->getHeight());
}

/*
 *
 */
fgBool fgGfxMain::setResourceManager(fgManagerBase *resourceManager)
{
	if(!resourceManager)
		return FG_FALSE;
	if(resourceManager->getManagerType() != FG_MANAGER_RESOURCE) {
		return FG_FALSE;
	}
	
	if(!m_textureMgr)
		m_textureMgr = new fgTextureManager(resourceManager);
	else
		m_textureMgr->setResourceManager(resourceManager);
	m_resourceMgr = resourceManager;

	return m_textureMgr->initialize(); // #FIXME - texture mgr init ?
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
fgGfxWindow *fgGfxMain::getMainWindow(void) const
{
	return m_mainWindow;
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
 * #FIXME
 */
fgBool fgGfxMain::releaseTextures(void)
{
	if(m_textureMgr) {
		m_textureMgr->allReleaseGFX();
		m_textureMgr->allReleaseNonGFX();
		delete m_textureMgr;
		m_textureMgr = NULL;
	}
	m_resourceMgr = NULL;
	return FG_TRUE;
}
