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
#include "Event/fgEventManager.h"
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
m_pEventMgr(NULL),
m_shaderMgr(NULL),
m_mainWindow(NULL),
m_gfxContext(NULL),
m_3DScene(NULL),
m_2DScene(NULL),
m_particleSystem(NULL),
m_resourceCreatedCallback(NULL),
m_init(FG_FALSE) {
    m_3DScene = new fgGfx3DScene();
    m_2DScene = new fgGfx2DScene();
    m_particleSystem = new fgParticleSystem();
    m_particleSystem->setSceneManager(m_2DScene);

    m_shaderMgr = new fgGfxShaderManager();
    m_3DScene->setShaderManager(m_shaderMgr);
    m_2DScene->setShaderManager(m_shaderMgr);
}

/*
 *
 */
fgGfxMain::~fgGfxMain() {
    unregisterResourceCallbacks();
    if(m_particleSystem)
        delete m_particleSystem;
    if(m_3DScene)
        delete m_3DScene;
    if(m_2DScene)
        delete m_2DScene;
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
    if(m_resourceCreatedCallback)
        delete m_resourceCreatedCallback;
    memset(this, 0, sizeof (fgGfxMain)); // ?
    m_resourceCreatedCallback = NULL;
    m_particleSystem = NULL;
    m_textureMgr = NULL;
    m_pResourceMgr = NULL;
    m_pEventMgr = NULL;
    m_shaderMgr = NULL;
    m_mainWindow = NULL;
    m_gfxContext = NULL;
    m_3DScene = NULL;
    m_2DScene = NULL;
    clearStatus(); // #FIXME
}

/*
 *
 */
void fgGfxMain::registerResourceCallbacks(void) {
    if(!m_pEventMgr)
        return;

    if(!m_resourceCreatedCallback)
        m_resourceCreatedCallback = new fgClassCallback<fgGfxMain>(this, &fgGfxMain::resourceCreatedHandler);

    static_cast<fgEventManager *>(m_pEventMgr)->addEventCallback(FG_EVENT_RESOURCE_CREATED, m_resourceCreatedCallback);
}

/*
 *
 */
void fgGfxMain::unregisterResourceCallbacks(void) {
    if(!m_pEventMgr)
        return;

    static_cast<fgEventManager *>(m_pEventMgr)->removeEventCallback(FG_EVENT_RESOURCE_CREATED, m_resourceCreatedCallback);
}

/*
 *
 */
fgBool fgGfxMain::initGFX(void) {
    float t1 = fgTime::ms();
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
        FG_LOG_DEBUG("GFX: Setting viewport (0, 0, %d, %d)", m_mainWindow->getWidth(), m_mainWindow->getHeight());
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
        m_2DScene->getMVP()->setOrtho(0.0f, (float)m_mainWindow->getWidth(), (float)m_mainWindow->getHeight(), 0.0f);
        m_init = FG_TRUE;
    }
    if(status) {
        reportSuccess(FG_ERRNO_GFX_OK, "GFX subsystem initialized successfully");
    }
    float t2 = fgTime::ms();
    FG_LOG_DEBUG("GFX: Initialized in %.2f seconds", (t2 - t1) / 1000.0f);
    return status;
}

/*
 *
 */
void fgGfxMain::closeGFX(void) {
    FG_LOG_DEBUG("Closing GFX subsystem...");
    if(m_init) {
        if(m_mainWindow)
            m_mainWindow->close();
        fgGfxPlatform::quit();
        unregisterResourceCallbacks();
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
    if(m_particleSystem) {
        m_particleSystem->calculate();
    }
    m_3DScene->sortCalls();
    m_2DScene->sortCalls();
}

#include "fgGFXPrimitives.h"
#include "fgGFXDrawingBatch.h"
float guiScale = 1.0f;
float yolo_posx = 0;
float yolo_posy = 0;

/*
 *
 */
void fgGfxMain::render(void) {

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

    if(state[SDL_SCANCODE_W] == SDL_PRESSED)
        m_3DScene->getCamera()->moveForward();

    if(state[SDL_SCANCODE_S] == SDL_PRESSED)
        m_3DScene->getCamera()->moveBackward();

    if(state[SDL_SCANCODE_A] == SDL_PRESSED)
        m_3DScene->getCamera()->moveLeft();

    if(state[SDL_SCANCODE_D] == SDL_PRESSED)
        m_3DScene->getCamera()->moveRight();
    
    m_3DScene->getCamera()->update();
    m_3DScene->getMVP()->setCamera(m_3DScene->getCamera());
    m_3DScene->getMVP()->setPerspective(45.0f, m_mainWindow->getAspect());
    
    rotxyz += 0.0094525f;
    if(rotxyz > M_PI * 2.0f)
        rotxyz = 0.0f;
    fgMatrix4f modelMat;
    modelMat = fgMath::translate(modelMat, fgVector3f(yolo_posx, yolo_posy * 0.0f, yolo_posy));
    modelMat = fgMath::rotate(modelMat, rotxyz, fgVector3f(1.0f, 1.0f, 1.0f)); //fgMath::translate(fgMatrix4f(1.0f), fgVector3f(0.0f, 0.0f, -5.0f));

    fgGfxShaderProgram *program = m_shaderMgr->get(sPlainEasyShaderName);
    m_shaderMgr->useProgram(program);
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
        fgGfxSceneNode *obj1 = m_3DScene->get("PlayerFighter");
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
#if defined(FG_USING_MARMALADE)
    if(s3eKeyboardGetState(s3eKeyLeft) & S3E_KEY_STATE_DOWN) {
        yolo_posx -= 10.0f;
    }
    if(s3eKeyboardGetState(s3eKeyRight) & S3E_KEY_STATE_DOWN) {
        yolo_posx += 10.0f;
    }
    if(s3eKeyboardGetState(s3eKeyUp) & S3E_KEY_STATE_DOWN) {
        yolo_posy -= 10.0f;
    }
    if(s3eKeyboardGetState(s3eKeyDown) & S3E_KEY_STATE_DOWN) {
        yolo_posy += 10.0f;
    }
    if(s3eKeyboardGetState(s3eKeyRightShift) & S3E_KEY_STATE_DOWN) {
        //        scale += 0.01f;
    }
#else
    if(state[SDL_SCANCODE_LEFT] == SDL_PRESSED) {
        yolo_posx -= 10.0f;
    }
    if(state[SDL_SCANCODE_RIGHT] == SDL_PRESSED) {
        yolo_posx += 10.0f;
    }
    if(state[SDL_SCANCODE_UP] == SDL_PRESSED) {
        yolo_posy -= 10.0f;
    }
    if(state[SDL_SCANCODE_DOWN] == SDL_PRESSED) {
        yolo_posy += 10.0f;
    }

#endif
    Model = fgMath::translate(Model, fgVec3f(yolo_posx * 0.0f, yolo_posy * 0.0f, 0.0f));
    Model = fgMath::scale(Model, fgVec3f(guiScale, guiScale, 0.0f));

    m_2DScene->getMVP()->setOrtho(0, (float)m_mainWindow->getWidth(), (float)m_mainWindow->getHeight(), 0.0f);
    //m_2DScene->getMVP()->calculate(Model);
    //m_2DScene->getMVP()->update();
    //program2->setUniform(MVP);

    fgGfxPlatform::context()->blendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    m_2DScene->render();

    // #FIXME ! TOTAL FUBAR SITUATION ! OMG ! OH MY !
    fgGfxMVPMatrix mvp_lol;
    fgGfxMVPMatrix *MVP = &mvp_lol;
    MVP->identity();
    MVP->setOrtho(0, (float)m_mainWindow->getWidth(), (float)m_mainWindow->getHeight(), 0.0f);
    MVP->calculate(Model);
    program2->setUniform(MVP);
    fgGfxPlatform::context()->blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    fgGfxPlatform::context()->scissor(0, 0, m_mainWindow->getWidth(), m_mainWindow->getHeight());
}

/**
 * 
 * @param pResourceManager
 * @return 
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
    if(m_2DScene)
        m_2DScene->setResourceManager(m_pResourceMgr);
    if(m_particleSystem) {
        m_particleSystem->setResourceManager(m_pResourceMgr);
        m_particleSystem->setSceneManager(m_2DScene);
        m_particleSystem->initialize();
    }
    fgManagerBase *pEventMgr = static_cast<fgResourceManager *>(m_pResourceMgr)->getEventManager();
    if(!pEventMgr) {
        unregisterResourceCallbacks();
        m_pEventMgr = NULL;
    } else if(m_pEventMgr && m_pEventMgr != pEventMgr) {
        unregisterResourceCallbacks();
    }
    m_pEventMgr = pEventMgr;
    if(m_pEventMgr)
        registerResourceCallbacks();
    return m_textureMgr->initialize(); // #FIXME - texture mgr init ?
}

/**
 * 
 * @return 
 */
fgTextureManager *fgGfxMain::getTextureManager(void) const {
    return m_textureMgr;
}

/**
 * 
 * @return 
 */
fgGfxShaderManager *fgGfxMain::getShaderManager(void) const {
    return m_shaderMgr;
}

/**
 * 
 * @return 
 */
fgGfxWindow *fgGfxMain::getMainWindow(void) const {
    return m_mainWindow;
}

/**
 * 
 * @return 
 */
fgGfx3DScene *fgGfxMain::get3DScene(void) const {
    return m_3DScene;
}

/**
 * 
 * @return 
 */
fgGfx2DScene *fgGfxMain::get2DScene(void) const {
    return m_2DScene;
}

/**
 * 
 * @return 
 */
fgGfxCameraAnimation *fgGfxMain::get3DSceneCamera(void) const {
    if(!m_3DScene)
        return NULL;
    return m_3DScene->getCamera();
}

/**
 * 
 * @return 
 */
fgParticleSystem *fgGfxMain::getParticleSystem(void) const {
    return m_particleSystem;
}

/*
 *
 */
fgBool fgGfxMain::preLoadShaders(void) const {
    if(!m_shaderMgr) {
        return FG_FALSE;
    }
    if(!m_shaderMgr->isInit())
        m_shaderMgr->initialize();
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

/**
 * 
 * @param argv
 * @return 
 */
fgBool fgGfxMain::resourceCreatedHandler(fgArgumentList * argv) {
    if(!argv)
        return FG_FALSE;
    fgEventBase *event = (fgEventBase *)argv->getArgumentValueByID(0);
    if(!event)
        return FG_FALSE;
    fgEventType type = event->eventType;
    if(type != FG_EVENT_RESOURCE_CREATED)
        return FG_FALSE;
    fgResourceEvent *resourceEvent = (fgResourceEvent *)event;
    fgResource *pResource = resourceEvent->resource;
    if(!pResource)
        return FG_FALSE;

    if(pResource->getResourceType() != FG_RESOURCE_3D_MODEL)
        return FG_FALSE;
    fgGfxModelResource *pModel = (fgGfxModelResource *)pResource;
    fgGfxModelResource::modelShapes &shapes = pModel->getRefShapes();
    int n = shapes.size();
    if(n) {
        FG_LOG_DEBUG("GFX: Uploading static vertex data to VBO for model: '%s'", pModel->getNameStr());
    }
    for(int i = 0; i < n; i++) {
        fgGfxShape *shape = shapes[i];
        if(!shape)
            continue;
        if(!shape->mesh)
            continue;
        if(!fgGfxPlatform::context()->isBuffer(shape->mesh->getPtrVBO())) {
            FG_LOG_DEBUG("GFX: Uploading static vertex data to VBO for shape: '%s'", shape->name.c_str());
            shape->mesh->genBuffers();
        }
    }
    return FG_TRUE;
}
