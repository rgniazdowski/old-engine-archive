/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
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
#include "Util/fgProfiling.h"
#include "fgDebugConfig.h"

#if defined(FG_USING_MARMALADE)
#include "s3e.h"
#include "s3eTypes.h"
#endif

#include "fgLog.h"
#include "fgGFXPrimitives.h"
#include "fgGFXDrawingBatch.h"
float guiScale = 1.0f;
float yolo_posx = 0;
float yolo_posy = 0;

using namespace fg;
 
/*
 *
 */
gfx::CGfxMain::CGfxMain() :
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
    m_3DScene = new gfx::CScene3D();
    m_2DScene = new gfx::CScene2D();
    m_particleSystem = new gfx::CParticleSystem();
    m_particleSystem->setSceneManager(m_2DScene);

    m_shaderMgr = new gfx::CShaderManager();
    m_3DScene->setShaderManager(m_shaderMgr);
    m_2DScene->setShaderManager(m_shaderMgr);
}

/**
 *
 */
gfx::CGfxMain::~CGfxMain() {
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
    memset(this, 0, sizeof (CGfxMain)); // ?
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
}

/**
 *
 */
void gfx::CGfxMain::registerResourceCallbacks(void) {
    if(!m_pEventMgr)
        return;

    if(!m_resourceCreatedCallback)
        m_resourceCreatedCallback = new fg::event::CMethodCallback<CGfxMain>(this, &gfx::CGfxMain::resourceCreatedHandler);

    static_cast<fg::event::CEventManager *>(m_pEventMgr)->addCallback(event::RESOURCE_CREATED, m_resourceCreatedCallback);
}

/**
 *
 */
void gfx::CGfxMain::unregisterResourceCallbacks(void) {
    if(!m_pEventMgr)
        return;

    static_cast<fg::event::CEventManager *>(m_pEventMgr)->removeCallback(event::RESOURCE_CREATED, m_resourceCreatedCallback);
}

/**
 * 
 * @return 
 */
fgBool gfx::CGfxMain::initGFX(void) {
    float t1 = timesys::ms();
    fgBool status = FG_TRUE;

    if(!gfx::CPlatform::initialize()) {
        // ERROR
        status = FG_FALSE;
    }
    if(!m_mainWindow && status) {
        m_mainWindow = new gfx::CWindow();
    }
    if(m_mainWindow && status) {
        // #FIXME - resolution FIXME!
        if(!m_mainWindow->setup(FG_PACKAGE_FULL_TEXT, 1024, 768)) {
            delete m_mainWindow;
            m_mainWindow = NULL;
            status = FG_FALSE;
        }
#if defined(FG_USING_SDL2)
        gfx::CPlatform::initializeMainContext(m_mainWindow->getSysPtr());
#endif
    }
    if(status) {
        m_gfxContext = gfx::CPlatform::context();
        if(!m_gfxContext) {
            status = FG_FALSE;
        } else if(!m_gfxContext->isInit()) {
            status = FG_FALSE;
        }
        if(!status) {
            FG_LOG_ERROR("GFX: Unable to initialize any kind of context");
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
        m_gfxContext->bindTextureCube(0);
        m_gfxContext->scissor(0, 0, m_mainWindow->getWidth(), m_mainWindow->getHeight());
        m_gfxContext->setScreenSize(m_mainWindow->getWidth(), m_mainWindow->getHeight());
        m_2DScene->getMVP()->setOrtho(0.0f, (float)m_mainWindow->getWidth(), (float)m_mainWindow->getHeight(), 0.0f);
        m_loader.setContext(m_gfxContext);
        m_init = FG_TRUE;
    }
    if(status && m_shaderMgr) {
        if(!m_shaderMgr->initialize()) {
            FG_LOG_ERROR("GFX: Unable to initialize Shader Manager");
            //status = FG_FALSE; // ?
        }
    }
    if(status) {
        m_loader.setProgram(m_shaderMgr->getCurrentProgram());
        m_loader.setMainWindow(m_mainWindow);
        FG_LOG_DEBUG("GFX: Subsystem initialized successfully");
    }
    float t2 = timesys::ms();
    FG_LOG_DEBUG("GFX: Initialized in %.2f seconds", (t2 - t1) / 1000.0f);
    return status;
}

/**
 * 
 */
void gfx::CGfxMain::setupLoader(void) {
    if(!m_pResourceMgr)
        return;
    if(!m_textureMgr->isInit())
        return;
    resource::CResourceManager *pResourceMgr = static_cast<resource::CResourceManager *>(m_pResourceMgr);
    //
    // Splash texture load and upload - #FIXME - splash texture names from config!
    //
    const char *splashes[] = {"developer.jpg", "publisher.jpg", "splash.png"};
    int nsplashes = sizeof (splashes) / sizeof (splashes[0]);
    int x = FG_RAND(0, nsplashes - 1);
    gfx::CTexture *texture = (gfx::CTexture *)(pResourceMgr->request(splashes[x]));
    if(!texture) {
        FG_LOG_ERROR("GFX: Unable to load Splash texture");
        return;
    }
    m_textureMgr->uploadToVRAM(texture, FG_TRUE);
    FG_HardwareState->deviceYield(1);
    m_loader.setSplashTexture(texture);
    //
    // ProgressBar texture load and upload
    //
    const char *loaders[] = {"sun.jpg", "hexangle.jpg"};
    int nloaders = sizeof (loaders) / sizeof (loaders[0]);
    x = FG_RAND(0, nloaders - 1);
    texture = (gfx::CTexture *)(pResourceMgr->request(loaders[x]));
    if(!texture) {
        FG_LOG_ERROR("GFX: Unable to load ProgressBar texture");
        return;
    }
    m_textureMgr->uploadToVRAM(texture, FG_TRUE);
    FG_HardwareState->deviceYield(1);
    m_loader.setProgressTexture(texture);

}

/**
 *
 */
void gfx::CGfxMain::closeGFX(void) {
    FG_LOG_DEBUG("Closing GFX subsystem...");
    if(m_init) {
        if(m_mainWindow)
            m_mainWindow->close();
        gfx::CPlatform::quit();
        unregisterResourceCallbacks();
        m_gfxContext = NULL;
    }
    m_init = FG_FALSE;
}

/**
 * 
 * @return 
 */
fgBool gfx::CGfxMain::suspendGFX(void) {
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
        FG_LOG_WARNING("GFX: Suspension of GFX subsystem finished with errors");
    else
        FG_LOG_WARNING("GFX: Suspension of GFX subsystem finished with no errors");
    return status;
}

/**
 * 
 * @return 
 */
fgBool gfx::CGfxMain::resumeGFX(void) {
    fgBool status = FG_TRUE;
    if(!gfx::CGfxMain::initGFX())
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
        gfx::CModelResource *model = NULL;
        std::string modelname("CobraBomber");
        model = (gfx::CModelResource *)((resource::CResourceManager *)m_textureMgr->getResourceManager())->get(modelname);
        if(model) {
            if(model->getRefShapes().size()) {
                model->getRefShapes()[0]->mesh->genBuffers();
            }
        }
    }

    if(!status)
        FG_LOG_WARNING("GFX: Resume of GFX subsystem finished with errors");
    else
        FG_LOG_WARNING("GFX: Resume of GFX subsystem finished with no errors");
    return status;
}

/**
 *
 */
void gfx::CGfxMain::display(void) {
    if(!m_gfxContext)
        return;
    if(m_particleSystem) {
        m_particleSystem->calculate();
    }
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->begin("GFX::3DScene::sortCalls");
    }
#endif
    m_3DScene->sortCalls();
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("GFX::3DScene::sortCalls");
        profile::g_debugProfiling->begin("GFX::2DScene::sortCalls");
    }
#endif
    //printf("fgGfx2DScene::sortCalls(void)\n");
    m_2DScene->sortCalls();
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("GFX::2DScene::sortCalls");
    }
#endif
}

/**
 *
 */
void gfx::CGfxMain::render(void) {
    //m_gfxContext->scissor(100,100,200,300);
    static float offset = 0.0f;
    static gfx::CModelResource *cobraBomber = NULL;

    static float rotxyz = 0.0f;
    static bool loadModel = true;
    glm::mat4 Model;

    if(!m_mainWindow || !m_gfxContext) {
        FG_LOG_ERROR("Main window / context is NULL");
        return;
    }
    fgGLError();
    m_mainWindow->clearColor();
    resource::CResourceManager *rm = NULL;
    static int a[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
#if defined(FG_USING_SDL2)
    const Uint8 *state = SDL_GetKeyboardState(NULL);
#endif
    std::string sPlainEasyShaderName("sPlainEasy");
    std::string sOrthoEasyShaderName("sOrthoEasy");
    std::string sSkyBoxEasyShaderName("sSkyBoxEasy");
    std::string modelname("CobraBomber");

    offset = fmodf(offset + 0.2f, 2 * 3.141f);
    if(!m_textureMgr || !m_shaderMgr) {
        FG_LOG_ERROR("No texture / shader manager");
        return;

    }
    rm = (resource::CResourceManager *)m_textureMgr->getResourceManager();
    if(!rm) {
        FG_LOG_ERROR("Cant access resource manager.");
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
        if(!cobraBomber)
            cobraBomber = (gfx::CModelResource *)rm->get(modelname);
        if(!cobraBomber) {
            printf("NO MODEL\n");
            return;
        }
    }

    m_3DScene->getCamera()->setDT((float)FG_HardwareState->getDelta());
#if defined(FG_USING_SDL2)
    if(state[SDL_SCANCODE_W] == SDL_PRESSED)
        m_3DScene->getCamera()->moveForward();

    if(state[SDL_SCANCODE_S] == SDL_PRESSED)
        m_3DScene->getCamera()->moveBackward();

    if(state[SDL_SCANCODE_A] == SDL_PRESSED)
        m_3DScene->getCamera()->moveLeft();

    if(state[SDL_SCANCODE_D] == SDL_PRESSED)
        m_3DScene->getCamera()->moveRight();

    if(state[SDL_SCANCODE_SPACE] == SDL_PRESSED)
        m_3DScene->getCamera()->moveUp();

    if(state[SDL_SCANCODE_LCTRL] == SDL_PRESSED)
        m_3DScene->getCamera()->moveDown();
#else 
    if(s3eKeyboardGetState(s3eKeyW) & S3E_KEY_STATE_DOWN)
        m_3DScene->getCamera()->moveForward();
    if(s3eKeyboardGetState(s3eKeyS) & S3E_KEY_STATE_DOWN)
        m_3DScene->getCamera()->moveBackward();
    if(s3eKeyboardGetState(s3eKeyA) & S3E_KEY_STATE_DOWN)
        m_3DScene->getCamera()->moveLeft();
    if(s3eKeyboardGetState(s3eKeyD) & S3E_KEY_STATE_DOWN)
        m_3DScene->getCamera()->moveRight();

#endif

    m_3DScene->getCamera()->update();
    m_3DScene->getMVP()->setCamera(m_3DScene->getCamera());
    m_3DScene->getMVP()->setPerspective(45.0f, m_mainWindow->getAspect());
    Matrix4f modelMat;
    gfx::CShaderProgram *program = m_shaderMgr->get(sSkyBoxEasyShaderName);
    program->setUniform(FG_GFX_USE_TEXTURE, 1.0f);
    program->setUniform(FG_GFX_CUBE_TEXTURE, (fgGFXint)0);

    if(!program) {
        FG_LOG_ERROR("Cant access sSkyBoxEasy shader program.");
        return;
    }
    m_shaderMgr->useProgram(program);
    if(true) {
#if defined(FG_DEBUG)
        if(g_fgDebugConfig.isDebugProfiling) {
            profile::g_debugProfiling->begin("GFX::drawSkyBox");
        }
#endif
        //
        // #FIXME #TODO - that kind of SkyBox display sucks ass beyond recognition
        //
        // Load proper texture
#if defined(FG_DEBUG)
        if(g_fgDebugConfig.isDebugProfiling) {
            profile::g_debugProfiling->begin("GFX::drawSkyBoxTexResGet");
        }
#endif  
        static resource::CResource *pResourceX = NULL;
        if(!pResourceX)
            pResourceX = static_cast<resource::CResourceManager *>(m_pResourceMgr)->get("PurpleNebulaCube");
#if defined(FG_DEBUG)
        if(g_fgDebugConfig.isDebugProfiling) {
            profile::g_debugProfiling->end("GFX::drawSkyBoxTexResGet");
        }
#endif
        if(pResourceX->getResourceType() == resource::TEXTURE) {
            gfx::CTexture *pTexture = static_cast<gfx::CTexture *>(pResourceX);
            if(pTexture) {
                fgGfxTextureID &texID = pTexture->getRefGfxID();

                //m_gfxContext->activeTexture(GL_TEXTURE1); // ? ? ? 
                m_gfxContext->bindTexture(texID);

                modelMat = math::translate(Matrix4f(), m_3DScene->getCamera()->getRefEye());
                float skyboxScale = FG_GFX_PERSPECTIVE_ZFAR_DEFAULT * 1.1f;
                modelMat = math::scale(modelMat, Vector3f(skyboxScale, skyboxScale, skyboxScale));
                m_3DScene->getMVP()->calculate(modelMat);
                program->setUniform(m_3DScene->getMVP());
                m_gfxContext->frontFace(GL_CW); // #FUBAR
                //m_gfxContext->setCullFace(FG_FALSE);
                CPrimitives::drawSkyBoxOptimized();
                m_gfxContext->frontFace(GL_CCW);
                //m_gfxContext->setCullFace(FG_TRUE);
            }
        }
#if defined(FG_DEBUG)
        if(g_fgDebugConfig.isDebugProfiling) {
            profile::g_debugProfiling->end("GFX::drawSkyBox");
        }
#endif
    }

    rotxyz += 0.0094525f;
    if(rotxyz > M_PI * 2.0f)
        rotxyz = 0.0f;

    modelMat = math::translate(Matrix4f(), Vector3f(yolo_posx, yolo_posy * 0.0f, yolo_posy));
    modelMat = math::rotate(modelMat, rotxyz, Vector3f(1.0f, 1.0f, 1.0f)); //math::translate(fgMatrix4f(1.0f), Vector3f(0.0f, 0.0f, -5.0f));

    program = m_shaderMgr->get(sPlainEasyShaderName);

    if(!program) {
        FG_LOG_ERROR("Cant access sPlainEasy shader program.");
        return;
    }
    m_shaderMgr->useProgram(program);
    program->setUniform(FG_GFX_USE_TEXTURE, 1.0f);
    program->setUniform(FG_GFX_PLAIN_TEXTURE, (fgGFXint)0);

    // #FIXME - this of course needs to be somewhere else 
    if(cobraBomber && m_3DScene && 0) {
        if(!m_3DScene->count()) {
            //m_3DScene->addFromModel(cobraBomber, std::string("PlayerFighter"));
            //m_3DScene->addFromModel(cobraBomber, std::string("PlayerEnemy"));
        }
    }
    static float rot1 = 0.0f;
    static float radius1 = 200.0f;
    // #FIXME
    if(m_3DScene && 0) {
        gfx::CSceneNode *obj1 = m_3DScene->get("PlayerFighter");
        if(obj1) {
            obj1->setModelMatrix(modelMat);
        }
        gfx::CSceneNode *obj2 = m_3DScene->get("PlayerEnemy");
        if(obj2) {
            rot1 += 0.00127f * (float)FG_HardwareState->getDelta();
            if(rot1 > M_PI * 2.0f)
                rot1 = 0.0f;
            float rx = cos(rot1) * radius1;
            float rz = sin(rot1) * radius1;

            modelMat = math::translate(Matrix4f(), Vector3f(rx, 20.0f, rz));
            modelMat = math::rotate(modelMat, (float)M_PI / 2.0f, Vector3f(0.0f, 1.0f, 0.0f));
            obj2->setModelMatrix(modelMat);
        }
    }

#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->begin("GFX::3DScene::render");
    }
#endif
    // RENDER THE 3D SCENE
    m_3DScene->render();
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("GFX::3DScene::render");
    }
#endif

    //////////////////////////////////////////////////////////////
    // 2D LAYER DRAWING TEST - NEEDS TO WORK DIFFERENTLY
    // THIS IS FOR GUI DRAWING - SPECIAL ORTHO SHADER
    //////////////////////////////////////////////////////////////
    gfx::CShaderProgram *program2 = m_shaderMgr->get(sOrthoEasyShaderName);
    if(!program2) {
        FG_LOG_ERROR("Cant access sOrthoEasy shader program.");
        return;
    }
    m_shaderMgr->useProgram(program2);

    gfx::CPlatform::context()->setBlend(FG_TRUE);
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
    Model = math::translate(Model, Vec3f(yolo_posx * 0.0f, yolo_posy * 0.0f, 0.0f));
    Model = math::scale(Model, Vec3f(guiScale, guiScale, 0.0f));

    m_2DScene->getMVP()->setOrtho(0, (float)m_mainWindow->getWidth(), (float)m_mainWindow->getHeight(), 0.0f);
    //m_2DScene->getMVP()->calculate(Model);
    //m_2DScene->getMVP()->update();
    //program2->setUniform(MVP);

    gfx::CPlatform::context()->blendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    //printf("fgGfx2DScene::render(void)\n");
    m_2DScene->render();

    // #FIXME ! TOTAL FUBAR SITUATION ! OMG ! OH MY !
    gfx::CMVPMatrix mvp_lol;
    gfx::CMVPMatrix *MVP = &mvp_lol;
    MVP->identity();
    MVP->setOrtho(0, (float)m_mainWindow->getWidth(), (float)m_mainWindow->getHeight(), 0.0f);
    MVP->calculate(Model);
    program2->setUniform(MVP);
    m_gfxContext->blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    m_gfxContext->scissor(0, 0, m_mainWindow->getWidth(), m_mainWindow->getHeight()); // #THA FUCK?
}

/**
 * 
 * @param pResourceManager
 * @return 
 */
fgBool gfx::CGfxMain::setupResourceManager(fg::base::CManager *pResourceManager) {
    if(!pResourceManager)
        return FG_FALSE;
    if(pResourceManager->getManagerType() != FG_MANAGER_RESOURCE) {
        return FG_FALSE;
    }
    if(!m_textureMgr)
        m_textureMgr = new gfx::CTextureManager(pResourceManager);
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
    fg::base::CManager *pEventMgr = static_cast<resource::CResourceManager *>(m_pResourceMgr)->getEventManager();
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
gfx::CTextureManager *gfx::CGfxMain::getTextureManager(void) const {
    return m_textureMgr;
}

/**
 * 
 * @return 
 */
gfx::CShaderManager *gfx::CGfxMain::getShaderManager(void) const {
    return m_shaderMgr;
}

/**
 * 
 * @return 
 */
gfx::CWindow *gfx::CGfxMain::getMainWindow(void) const {
    return m_mainWindow;
}

/**
 * 
 * @return 
 */
gfx::CScene3D *gfx::CGfxMain::get3DScene(void) const {
    return m_3DScene;
}

/**
 * 
 * @return 
 */
gfx::CScene2D *gfx::CGfxMain::get2DScene(void) const {
    return m_2DScene;
}

/**
 * 
 * @return 
 */
gfx::CCameraAnimation *gfx::CGfxMain::get3DSceneCamera(void) const {
    if(!m_3DScene)
        return NULL;
    return m_3DScene->getCamera();
}

/**
 * 
 * @return 
 */
gfx::CParticleSystem *gfx::CGfxMain::getParticleSystem(void) const {
    return m_particleSystem;
}

/**
 *
 * @return
 */
fgBool gfx::CGfxMain::preLoadShaders(void) const {
    if(!m_shaderMgr) {
        return FG_FALSE;
    }
    if(!m_shaderMgr->isInit())
        m_shaderMgr->initialize();
    return m_shaderMgr->preLoadShaders();
}

/**
 * #FIXME
 * @return
 */
fgBool gfx::CGfxMain::releaseTextures(void) {
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
fgBool gfx::CGfxMain::resourceCreatedHandler(fg::event::CArgumentList * argv) {
    if(!argv)
        return FG_FALSE;
    event::SEvent *event_struct = (event::SEvent *)argv->getValueByID(0);
    if(!event_struct)
        return FG_FALSE;
    event::EventType type = event_struct->code;
    if(type != event::RESOURCE_CREATED)
        return FG_FALSE;
    event::SResource *resourceEvent = (event::SResource *)event_struct;
    resource::CResource *pResource = resourceEvent->resource;
    if(!pResource)
        return FG_FALSE;

    if(pResource->getResourceType() != resource::MODEL3D)
        return FG_FALSE;
    gfx::CModelResource *pModel = (gfx::CModelResource *)pResource;
    gfx::CModelResource::modelShapes &shapes = pModel->getRefShapes();
    int n = shapes.size();
    if(n) {
        FG_LOG_DEBUG("GFX: Uploading static vertex data to VBO for model: '%s'", pModel->getNameStr());
    }
    for(int i = 0; i < n; i++) {
        SShape *shape = shapes[i];
        if(!shape)
            continue;
        if(!shape->mesh)
            continue;
        if(!gfx::CPlatform::context()->isBuffer(shape->mesh->getPtrVBO())) {
            FG_LOG_DEBUG("GFX: Uploading static vertex data to VBO for shape: '%s'", shape->name.c_str());
            shape->mesh->genBuffers();
        }
    }
    return FG_TRUE;
}
