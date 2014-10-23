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
#include "Resource/fgResourceManager.h"
#include "fgGFXErrorCodes.h"

#if defined FG_USING_MARMALADE
#include "s3e.h"
#include "s3eTypes.h"
#endif

#include "fgLog.h"

/*
 *
 */
fgGfxMain::fgGfxMain() :
m_textureMgr(NULL),
m_pResourceMgr(NULL),
m_shaderMgr(NULL),
m_mainWindow(NULL),
m_gfxContext(NULL),
m_3DScene(NULL),
m_init(FG_FALSE) {
    m_3DScene = new fgGfx3DScene();
}

/*
 *
 */
fgGfxMain::~fgGfxMain() {
    if(m_3DScene)
        delete m_3DScene;
    if(m_gfxContext)
        m_gfxContext->deleteAllBuffers();
    if(m_init)
        closeGFX();
    if(m_textureMgr)
        delete m_textureMgr;
    if(m_shaderMgr)
        delete m_shaderMgr;
    if(m_mainWindow)
        delete m_mainWindow;

    m_textureMgr = NULL;
    m_pResourceMgr = NULL;
    m_shaderMgr = NULL;
    m_mainWindow = NULL;
    m_gfxContext = NULL;
    m_3DScene = NULL;
}

/*
 *
 */
fgBool fgGfxMain::initGFX(void) {
    fgStatusReporter::clearStatus();
    fgBool status = FG_TRUE;

    if(!fgGfxPlatform::initialize()) {
        // ERROR
        status = FG_FALSE;
    }
    if(!m_mainWindow && status) {
        m_mainWindow = new fgGfxWindow();

    }
    if(m_mainWindow && status) {
        // #FIXME - resolution FIXME!
        if(!m_mainWindow->setup(FG_PACKAGE_FULL_TEXT, 800, 600)) {
            delete m_mainWindow;
            m_mainWindow = NULL;
            status = FG_FALSE;
        }
#if defined(FG_USING_SDL2)
        fgGfxPlatform::initializeMainContext(m_mainWindow->getSysPtr());
#endif
    }
    if(status) {
        m_gfxContext = fgGfxPlatform::context();
        if(!m_gfxContext) {
            status = FG_FALSE;
        } else if(!m_gfxContext->isInit()) {
            status = FG_FALSE;
        }
        if(!status) {
            FG_LOG::PrintError("GFX: Unable to initialize any kind of context");
        }
    }
    if(status) {
        if(!m_shaderMgr)
            m_shaderMgr = new fgGfxShaderManager();
        m_3DScene->setShaderManager(m_shaderMgr);

        FG_LOG::PrintDebug("GFX: Setting viewport (0, 0, %d, %d)", m_mainWindow->getWidth(), m_mainWindow->getHeight());
        m_gfxContext->viewport(0, 0, m_mainWindow->getWidth(), m_mainWindow->getHeight());
        m_gfxContext->clearDepth(1.0f);
        m_gfxContext->setDepthTest(FG_TRUE);
        m_gfxContext->depthFunc(GL_LEQUAL);
        m_gfxContext->setCullFace(FG_TRUE);
        m_gfxContext->frontFace(GL_CCW);
        m_gfxContext->cullFace(GL_BACK);
        m_gfxContext->setScissorTest(FG_TRUE);
        m_gfxContext->setBlend(FG_FALSE);
        m_gfxContext->blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        m_gfxContext->blendEquation(GL_FUNC_ADD);
        m_gfxContext->activeTexture(GL_TEXTURE0);
        m_gfxContext->bindTexture2D(0);
        m_gfxContext->bindTexture3D(0);
        m_gfxContext->scissor(0, 0, m_mainWindow->getWidth(), m_mainWindow->getHeight());
        //MVP->setPerspective(45.0f, m_mainWindow->getAspect());
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
void fgGfxMain::closeGFX(void) {
    FG_LOG::PrintDebug("Closing GFX subsystem...");
    if(m_init) {
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
fgBool fgGfxMain::suspendGFX(void) {
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
        if(m_gfxContext)
            m_gfxContext->deleteAllBuffers();
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
fgBool fgGfxMain::resumeGFX(void) {
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
    // #FIXME lol
    {
        fgGfxModelResource *model = NULL;
        std::string modelname("CobraBomber");
        model = (fgGfxModelResource *)((fgResourceManager *)m_textureMgr->getResourceManager())->get(modelname);
        if(model) {
            if(model->getRefShapes().size()) {
                model->getRefShapes()[0]->mesh->genBuffers();
            }
        }
    }

    if(!status)
        reportWarning(FG_ERRNO_GFX_OK, "Resume of GFX subsystem finished with errors");
    else
        reportWarning(FG_ERRNO_GFX_OK, "Resume of GFX subsystem finished with no errors");
    return status;
}

/*
 *
 */
void fgGfxMain::display(void) {
    if(!m_gfxContext)
        return;
    m_3DScene->sortCalls();
}

void dumpMatrix(const float *mat, const char *title) {
    if(title)
        printf("%s MATRIX:\n", title);
    printf("{ %.2f %.2f %.2f %.2f }\n", mat[0], mat[1], mat[2], mat[3]);
    printf("{ %.2f %.2f %.2f %.2f }\n", mat[4], mat[5], mat[6], mat[7]);
    printf("{ %.2f %.2f %.2f %.2f }\n", mat[8], mat[9], mat[10], mat[11]);
    printf("{ %.2f %.2f %.2f %.2f }\n\n", mat[12], mat[13], mat[14], mat[15]);
}

#include "fgGFXPrimitives.h"
#include "fgGFXDrawingBatch.h"
float guiScale = 1.0f;

/*
 *
 */
void fgGfxMain::render(void) {
    static float posx = 0;
    static float posy = 0;
    static float offset = 0.0f;
    static fgGfxModelResource *model = NULL;
    static float rotxyz = 0.0f;
    static bool loadModel = true;
    glm::mat4 Model;

    if(!m_mainWindow || !m_gfxContext) {
        FG_LOG::PrintError("Main window / context is NULL");
        return;
    }
    fgGLError();
    m_mainWindow->clearColor();
    fgResourceManager *rm = NULL;
    static int a[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#if defined(FG_USING_SDL2)
    const Uint8 *state = SDL_GetKeyboardState(NULL);
#endif
    std::string sPlainEasyShaderName("sPlainEasy");
    std::string sOrthoEasyShaderName("sOrthoEasy");
    std::string modelname("CobraBomber");
    std::string texname("CobraBomberTexture");

    offset = fmodf(offset + 0.2f, 2 * 3.141f);
    if(!m_textureMgr || !m_shaderMgr) {
        FG_LOG::PrintError("No texture / shader manager");
        return;

    }
    rm = (fgResourceManager *)m_textureMgr->getResourceManager();
    if(!rm) {
        FG_LOG::PrintError("Cant access resource manager.");

        return;
    }

#if defined(FG_USING_SDL2)
    if(state[SDL_SCANCODE_SPACE] == SDL_PRESSED && !a[6]) {
        a[6]++;
        loadModel = !loadModel;
    } else if(state[SDL_SCANCODE_SPACE] == SDL_RELEASED) {
        a[6] = 0;
    }
#endif
#if defined(FG_USING_MARMALADE)
    if(s3eKeyboardGetState(s3eKeySpace) & S3E_KEY_STATE_PRESSED) {
        loadModel = !loadModel;
    }
#endif
    if(loadModel) {
        if(!model)
            model = (fgGfxModelResource *)rm->get(modelname);
        if(!model) {
            printf("NO MODEL\n");
            return;
        }
    }
    m_3DScene->getCamera()->setDT((float)FG_HardwareState->getDelta());
    m_3DScene->getCamera()->update();
    //cameraAnim->setDT((float)FG_HardwareState->getDelta());
    //cameraAnim->update();
    //m_3DScene->applyCamera(cameraAnim);
    rotxyz += 0.0094525f;
    if(rotxyz > M_PI * 2.0f)
        rotxyz = 0.0f;
    fgMatrix4f modelMat = glm::rotate(glm::mat4(1.0f), rotxyz, glm::vec3(1.0f, 1.0f, 1.0f)); //fgMath::translate(fgMatrix4f(1.0f), fgVector3f(0.0f, 0.0f, -5.0f));

    m_3DScene->getMVP()->setPerspective(45.0f, m_mainWindow->getAspect());
    fgGfxShaderProgram *program = m_shaderMgr->get(sPlainEasyShaderName);
    m_shaderMgr->useProgram(program);
    //program->setUniform(FG_GFX_PLAIN_TEXTURE, 0);
    if(!program) {
        FG_LOG::PrintError("Cant access sPlainEasy shader program.");
        return;
    }
    // #FIXME - this of course needs to be somewhere else 
    if(model && m_3DScene) {
        if(!m_3DScene->count()) {
            m_3DScene->addFromModel(model, std::string("PlayerFighter"));
        }
    }
    // #FIXME
    if(m_3DScene) {
        fgGfxObject *obj1 = m_3DScene->get("PlayerFighter");
        if(obj1) {
            obj1->setModelMatrix(modelMat);
        }
    }
    // RENDER THE 3D SCENE
    m_3DScene->render();

    //////////////////////////////////////////////////////////////
    // 2D LAYER DRAWING TEST - NEEDS TO WORK DIFFERENTLY
    // THIS IS FOR GUI DRAWING - SPECIAL ORTHO SHADER
    //////////////////////////////////////////////////////////////
    fgGfxShaderProgram *program2 = m_shaderMgr->get(sOrthoEasyShaderName);
    if(!program2) {
        FG_LOG::PrintError("Cant access sOrthoEasy shader program.");
        return;
    }
    m_shaderMgr->useProgram(program2);

    fgGfxPlatform::context()->setBlend(FG_TRUE);
    fgGfxPlatform::context()->blendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //fgGfxPlatform::context()->blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#if defined(FG_USING_MARMALADE)
    if(s3eKeyboardGetState(s3eKeyLeft) & S3E_KEY_STATE_DOWN) {
        posx -= 10.0f;
    }
    if(s3eKeyboardGetState(s3eKeyRight) & S3E_KEY_STATE_DOWN) {
        posx += 10.0f;
    }
    if(s3eKeyboardGetState(s3eKeyUp) & S3E_KEY_STATE_DOWN) {
        posy -= 10.0f;
    }
    if(s3eKeyboardGetState(s3eKeyDown) & S3E_KEY_STATE_DOWN) {
        posy += 10.0f;
    }
    if(s3eKeyboardGetState(s3eKeyRightShift) & S3E_KEY_STATE_DOWN) {
        //        scale += 0.01f;
    }
#else
    if(state[SDL_SCANCODE_LEFT] == SDL_PRESSED) {
        posx -= 10.0f;
    }
    if(state[SDL_SCANCODE_RIGHT] == SDL_PRESSED) {
        posx += 10.0f;
    }
    if(state[SDL_SCANCODE_UP] == SDL_PRESSED) {
        posy -= 10.0f;
    }
    if(state[SDL_SCANCODE_DOWN] == SDL_PRESSED) {
        posy += 10.0f;
    }
    
#endif
    Model = glm::translate(Model, glm::vec3(posx*0.0f, posy*0.0f, 0.0f));
    Model = glm::scale(Model, glm::vec3(guiScale, guiScale, 0.0f));
    // #FIXME !
    fgGfxMVPMatrix mvp_lol;
    fgGfxMVPMatrix *MVP = &mvp_lol;
    MVP->identity();
    MVP->setOrtho(0, (float)m_mainWindow->getWidth(), (float)m_mainWindow->getHeight(), 0.0f);
    MVP->calculate(Model);
    program2->setUniform(MVP);

    fgGfxPlatform::context()->scissor(0, 0, m_mainWindow->getWidth(), m_mainWindow->getHeight());
}

/*
 *
 */
fgBool fgGfxMain::setResourceManager(fgManagerBase *pResourceManager) {
    if(!pResourceManager)
        return FG_FALSE;
    if(pResourceManager->getManagerType() != FG_MANAGER_RESOURCE) {
        return FG_FALSE;
    }

    if(!m_textureMgr)
        m_textureMgr = new fgTextureManager(pResourceManager);
    else
        m_textureMgr->setResourceManager(pResourceManager);
    m_pResourceMgr = pResourceManager;
    if(m_3DScene)
        m_3DScene->setResourceManager(m_pResourceMgr);
    return m_textureMgr->initialize(); // #FIXME - texture mgr init ?
}

/*
 *
 */
fgTextureManager *fgGfxMain::getTextureManager(void) const {
    return m_textureMgr;
}

/*
 *
 */
fgGfxShaderManager *fgGfxMain::getShaderManager(void) const {
    return m_shaderMgr;
}

/*
 *
 */
fgGfxWindow *fgGfxMain::getMainWindow(void) const {
    return m_mainWindow;
}

/*
 *
 */
fgGfx3DScene *fgGfxMain::get3DScene(void) const {
    return m_3DScene;
}

/*
 *
 */
fgGfxCameraAnimation *fgGfxMain::get3DSceneCamera(void) const {
    if(!m_3DScene)
        return NULL;
    return m_3DScene->getCamera();
}

/*
 *
 */
fgBool fgGfxMain::preLoadShaders(void) const {
    if(!m_shaderMgr) {
        return FG_FALSE;
    }
    return m_shaderMgr->preLoadShaders();
}

/*
 * #FIXME
 */
fgBool fgGfxMain::releaseTextures(void) {
    if(m_textureMgr) {
        m_textureMgr->allReleaseGFX();
        m_textureMgr->allReleaseNonGFX();
        delete m_textureMgr;
        m_textureMgr = NULL;
    }
    m_pResourceMgr = NULL;
    return FG_TRUE;
}
