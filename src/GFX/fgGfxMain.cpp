/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgBuildConfig.h"
#include "fgDebugConfig.h"
#include "fgCommon.h"

#include "fgGfxMain.h"
#include "fgGfxMVPMatrix.h"
#include "fgGfxModelResource.h"
#include "fgGfxErrorCodes.h"
#include "fgGfxPrimitives.h"
#include "fgGfxDrawingBatch.h"
#include "Scene/fgGfxSceneEvent.h"

#include "Textures/fgTextureResource.h"
#include "Resource/fgResourceManager.h"
#include "Event/fgEventManager.h"
#include "Util/fgProfiling.h"
#include "Physics/fgCycloneCoreMath.h"

#include "fgLog.h"

#if defined(FG_USING_MARMALADE)
#include "s3e.h"
#include "s3eTypes.h"
#endif

using namespace fg;
//------------------------------------------------------------------------------

gfx::CGfxMain::CGfxMain() :
m_textureMgr(NULL),
m_pResourceMgr(NULL),
m_pEventMgr(NULL),
m_shaderMgr(NULL),
m_mainWindow(NULL),
m_3DScene(NULL),
m_2DScene(NULL),
m_particleSystem(NULL),
m_resourceCreatedCallback(NULL),
m_sceneNodeInsertedCallback(NULL),
m_programEventCallback(NULL),
m_init(FG_FALSE) {
    m_3DScene = new gfx::CScene3D();
    m_2DScene = new gfx::CScene2D();
    m_particleSystem = new gfx::CParticleSystem();
    m_particleSystem->setSceneManager(m_3DScene);

    m_shaderMgr = new gfx::CShaderManager();
    m_3DScene->setShaderManager(m_shaderMgr);
    m_2DScene->setShaderManager(m_shaderMgr);
}
//------------------------------------------------------------------------------

gfx::CGfxMain::~CGfxMain() {
    unregisterResourceCallbacks();
    unregisterProgramCallbacks();
    unregisterSceneCallbacks();

    if(m_particleSystem) {
        FG_LOG_DEBUG("GFX: Destroying the Particle Subsystem...");
        delete m_particleSystem;
        m_particleSystem = NULL;
    }
    if(m_3DScene) {
        FG_LOG_DEBUG("GFX: Destroying the 3D Scene...");
        delete m_3DScene;
        m_3DScene = NULL;
    }
    if(m_2DScene) {
        FG_LOG_DEBUG("GFX: Destroying the 2D Scene...");
        delete m_2DScene;
        m_2DScene = NULL;
    }
    if(context::isInit()) {
        context::deleteAllBuffers();
    }

    if(m_textureMgr) {
        FG_LOG_DEBUG("GFX: Destroying the Texture Manager...");
        delete m_textureMgr;
        m_textureMgr = NULL;

    }
    if(m_shaderMgr) {
        FG_LOG_DEBUG("GFX: Destroying the Shader Manager...");
        delete m_shaderMgr;
        m_shaderMgr = NULL;

    }
    if(m_mainWindow) {
        delete m_mainWindow;
        m_mainWindow = NULL;

    }
    if(m_resourceCreatedCallback) {
        delete m_resourceCreatedCallback;
        m_resourceCreatedCallback = NULL;
    }
    if(m_sceneNodeInsertedCallback) {
        delete m_sceneNodeInsertedCallback;
        m_sceneNodeInsertedCallback = NULL;
    }
    if(m_programEventCallback) {
        delete m_programEventCallback;
        m_programEventCallback = NULL;
    }

    if(m_loader) {
        delete m_loader;
        m_loader = NULL;
    }

    if(m_init) {
        closeGFX();
    }
    // External pointers
    m_pResourceMgr = NULL;
    m_pEventMgr = NULL;
}
//------------------------------------------------------------------------------

fgBool gfx::CGfxMain::handleMainWindowBufferSwap(void *pSystemData, void *pUserData) {
    if(!pSystemData || !pUserData)
        return FG_FALSE;

    // pSystemData will be the pointer to the main window (or any window to which
    // this callback is assigned)
    // pUserData will be the pointer to the CGfxMain object

    gfx::CGfxMain* pGfxMain = static_cast<gfx::CGfxMain*>(pUserData);
    // SWAP_BUFFER event is not thrown and executed in the main EventMgr function
    // it's always called in place by executeEvent(event) function
    static_cast<event::CEventManager*>(pGfxMain->getEventManager())->executeEvent(event::SWAP_BUFFERS, pSystemData);

    return FG_TRUE;
}

//------------------------------------------------------------------------------

void gfx::CGfxMain::registerResourceCallbacks(void) {
    if(!m_pEventMgr)
        return;

    if(!m_resourceCreatedCallback)
        m_resourceCreatedCallback = new fg::event::CMethodCallback<CGfxMain>(this, &gfx::CGfxMain::resourceCreatedHandler);

    static_cast<fg::event::CEventManager *>(m_pEventMgr)->addCallback(event::RESOURCE_CREATED, m_resourceCreatedCallback);
}
//------------------------------------------------------------------------------

void gfx::CGfxMain::unregisterResourceCallbacks(void) {
    if(!m_pEventMgr)
        return;

    static_cast<fg::event::CEventManager *>(m_pEventMgr)->removeCallback(event::RESOURCE_CREATED, m_resourceCreatedCallback);
}
//------------------------------------------------------------------------------

void gfx::CGfxMain::registerSceneCallbacks(void) {
    if(!m_3DScene || !m_2DScene)
        return;

    if(!m_sceneNodeInsertedCallback)
        m_sceneNodeInsertedCallback = new fg::event::CMethodCallback<CGfxMain>(this, &gfx::CGfxMain::sceneNodeInsertedHandler);

    m_3DScene->getInternalEventManager()->addCallback(event::SCENE_NODE_INSERTED, m_sceneNodeInsertedCallback);
    m_2DScene->getInternalEventManager()->addCallback(event::SCENE_NODE_INSERTED, m_sceneNodeInsertedCallback);
}
//------------------------------------------------------------------------------

void gfx::CGfxMain::unregisterSceneCallbacks(void) {
    if(!m_3DScene || !m_2DScene)
        return;

    m_3DScene->getInternalEventManager()->removeCallback(event::SCENE_NODE_INSERTED, m_sceneNodeInsertedCallback);
    m_2DScene->getInternalEventManager()->removeCallback(event::SCENE_NODE_INSERTED, m_sceneNodeInsertedCallback);
}
//------------------------------------------------------------------------------

void gfx::CGfxMain::registerProgramCallbacks(void) {
    if(!m_pEventMgr)
        return;

    if(!m_programEventCallback)
        m_programEventCallback = new fg::event::CMethodCallback<CGfxMain>(this, &gfx::CGfxMain::programEventHandler);

    static_cast<fg::event::CEventManager *>(m_pEventMgr)->addCallback(event::PROGRAM_QUIT, m_programEventCallback);
    static_cast<fg::event::CEventManager *>(m_pEventMgr)->addCallback(event::PROGRAM_SUSPEND, m_programEventCallback);
    static_cast<fg::event::CEventManager *>(m_pEventMgr)->addCallback(event::PROGRAM_RESUME, m_programEventCallback);
}
//------------------------------------------------------------------------------

void gfx::CGfxMain::unregisterProgramCallbacks(void) {
    if(!m_pEventMgr)
        return;

    static_cast<fg::event::CEventManager *>(m_pEventMgr)->removeCallback(event::PROGRAM_QUIT, m_programEventCallback);
    static_cast<fg::event::CEventManager *>(m_pEventMgr)->removeCallback(event::PROGRAM_SUSPEND, m_programEventCallback);
    static_cast<fg::event::CEventManager *>(m_pEventMgr)->removeCallback(event::PROGRAM_RESUME, m_programEventCallback);
}
//------------------------------------------------------------------------------

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
    m_mainWindow->registerOnSwap(&gfx::CGfxMain::handleMainWindowBufferSwap, (void*)this);
    m_loader = new CLoader(this);
    int sw = (int)context::getScreenSize().x;
    int sh = (int)context::getScreenSize().y;
#if defined(FG_USING_SDL2) && defined(FG_USING_PLATFORM_ANDROID)
    // This is needed only on android - there is just one video 
    // mode available - full screen resolution
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    sw = displayMode.w;
    sh = displayMode.h;
#endif
    if(m_mainWindow && status) {
        // #FIXME - resolution FIXME!
        if(!m_mainWindow->setup(FG_PACKAGE_FULL_TEXT, sw, sh)) {
            delete m_mainWindow;
            m_mainWindow = NULL;
            status = FG_FALSE;
        }
#if defined(FG_USING_SDL2)
        gfx::CPlatform::initializeMainContext(m_mainWindow->getSysPtr());
#endif
    }
    if(status) {
        if(!context::isInit()) {
#if !defined(FG_USING_SDL2)
            status = context::initialize();
#endif
        }
        if(!context::isInit()) {
            status = FG_FALSE;
        }
        if(!status) {
            FG_LOG_ERROR("GFX: Unable to initialize any kind of context");
        }
    }
    if(status) {

        FG_LOG_DEBUG("GFX: Setting viewport (0, 0, %d, %d)", m_mainWindow->getWidth(), m_mainWindow->getHeight());
        context::clearDepth(1.0f);
        context::setDepthTest(FG_TRUE);
        context::depthFunc(GL_LEQUAL);
        context::setCullFace(FG_TRUE);
        context::frontFace(GL_CCW);
        context::cullFace(GL_BACK);
        context::setScissorTest(FG_TRUE);
        context::setBlend(FG_FALSE);
        context::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        context::blendEquation(GL_FUNC_ADD);
        context::activeTexture(GL_TEXTURE0);
        context::bindTexture2D(0);
        context::bindTextureCube(0);
        context::viewport(0, 0, m_mainWindow->getWidth(), m_mainWindow->getHeight());
        context::scissor(0, 0, m_mainWindow->getWidth(), m_mainWindow->getHeight());
        context::setScreenSize(m_mainWindow->getWidth(), m_mainWindow->getHeight());
        m_2DScene->getMVP()->setOrtho(0.0f, (float)m_mainWindow->getWidth(), (float)m_mainWindow->getHeight(), 0.0f);
        m_init = FG_TRUE;
    }
    if(status && m_shaderMgr) {
        if(!m_shaderMgr->initialize()) {
            FG_LOG_ERROR("GFX: Unable to initialize Shader Manager");
            //status = FG_FALSE; // ?
        }
    }
    if(status) {
        FG_LOG_DEBUG("GFX: Subsystem initialized successfully");
    }
    if(status) {
        m_3DScene->initialize();
        m_2DScene->initialize();
        registerSceneCallbacks();
    }
    float t2 = timesys::ms();
    FG_LOG_DEBUG("GFX: Initialized in %.2f seconds", (t2 - t1) / 1000.0f);
    return status;
}
//------------------------------------------------------------------------------

void gfx::CGfxMain::generateBuiltInData(void) {
    if(!m_pResourceMgr) {
        // ERROR
        return;
    }

    /// Will now create built in model shapes
    SMeshAoS *builtin_cube_mesh = new SMeshAoS();
    SShape *builtin_cube_shape = new SShape();
    primitives::createCubeMesh(builtin_cube_mesh);
    CModel *cubeModel = new CModelResource();
    cubeModel->setModelType(ModelType::MODEL_BUILTIN);
    cubeModel->setName("builtinCube1x1");
    builtin_cube_shape->name = "builtinCube1x1";
    builtin_cube_shape->mesh = builtin_cube_mesh;
    builtin_cube_shape->material = new SMaterial();
    builtin_cube_shape->material->diffuseTexName = "empty.tga";
    builtin_cube_shape->material->shaderName = "sPlainEasy";
    cubeModel->addShape(builtin_cube_shape);
    static_cast<resource::CResourceManager *>(m_pResourceMgr)->request("empty.tga");
    if(!static_cast<resource::CResourceManager *>(m_pResourceMgr)->insert(cubeModel)) {
        static_cast<resource::CResourceManager *>(m_pResourceMgr)->remove(cubeModel);
        delete cubeModel;
    }
    // Should not call create manually on the 3D Model
    // This wont call the function for VBO upload
    static_cast<resource::CResourceManager *>(m_pResourceMgr)->request("builtinCube1x1");
    //---------------------------------------------

    SMeshAoS *builtin_sphere_mesh = new SMeshAoS();
    SShape *builtin_sphere_shape = new SShape();
    primitives::createSphereMesh(builtin_sphere_mesh, 16, 16);
    CModel *sphereModel = new CModelResource();
    sphereModel->setModelType(ModelType::MODEL_BUILTIN);
    sphereModel->setName("builtinSphere");
    builtin_sphere_shape->name = "builtinSphere";
    builtin_sphere_shape->mesh = builtin_sphere_mesh;
    builtin_sphere_shape->material = new SMaterial();
    builtin_sphere_shape->material->diffuseTexName = "empty.tga";
    builtin_sphere_shape->material->shaderName = "sPlainEasy";
    sphereModel->addShape(builtin_sphere_shape);
    //static_cast<resource::CResourceManager *>(m_pResourceMgr)->request("empty.tga");
    if(!static_cast<resource::CResourceManager *>(m_pResourceMgr)->insert(sphereModel)) {
        static_cast<resource::CResourceManager *>(m_pResourceMgr)->remove(sphereModel);
        delete sphereModel;
    }
    static_cast<resource::CResourceManager *>(m_pResourceMgr)->request("builtinSphere");
    //---------------------------------------------

    SMeshAoS *builtin_quad_mesh = new SMeshAoS();
    SShape *builtin_quad_shape = new SShape();
    primitives::createQuadMesh(builtin_quad_mesh);
    CModel *quadModel = new CModelResource();
    quadModel->setModelType(ModelType::MODEL_BUILTIN);
    quadModel->setName("builtinQuad1x1");
    builtin_quad_shape->name = "builtinQuad1x1";
    builtin_quad_shape->mesh = builtin_quad_mesh;
    builtin_quad_shape->material = new SMaterial();
    builtin_quad_shape->material->diffuseTexName = "empty.tga";
    builtin_quad_shape->material->shaderName = "sPlainEasy";
    quadModel->addShape(builtin_quad_shape);
    //static_cast<resource::CResourceManager *>(m_pResourceMgr)->request("empty.tga");
    if(!static_cast<resource::CResourceManager *>(m_pResourceMgr)->insert(quadModel)) {
        static_cast<resource::CResourceManager *>(m_pResourceMgr)->remove(quadModel);
        delete quadModel;
    }
    static_cast<resource::CResourceManager *>(m_pResourceMgr)->request("builtinQuad1x1");
    //---------------------------------------------

    SMeshAoS *builtin_hex_prism_mesh = new SMeshAoS();
    SShape *builtin_hex_prism_shape = new SShape();
    primitives::createHexagonalPrismMesh(builtin_hex_prism_mesh, 1.0f, FG_TRUE,
                                         M_PIF/2.0f, Vec3f(1.0f, 0.0f, 0.0f));
    CModel *hexPrismModel = new CModelResource();
    hexPrismModel->setModelType(ModelType::MODEL_BUILTIN);
    hexPrismModel->setName("builtinHexagonalPrism");
    builtin_hex_prism_shape->name = "builtinHexagonalPrism";
    builtin_hex_prism_shape->mesh = builtin_hex_prism_mesh;
    builtin_hex_prism_shape->material = new SMaterial();
    builtin_hex_prism_shape->material->diffuseTexName = "empty.tga";
    builtin_hex_prism_shape->material->shaderName = "sPlainEasy";
    hexPrismModel->addShape(builtin_hex_prism_shape);
    //static_cast<resource::CResourceManager *>(m_pResourceMgr)->request("empty.tga");
    if(!static_cast<resource::CResourceManager *>(m_pResourceMgr)->insert(hexPrismModel)) {
        static_cast<resource::CResourceManager *>(m_pResourceMgr)->remove(hexPrismModel);
        delete hexPrismModel;
    }
    static_cast<resource::CResourceManager *>(m_pResourceMgr)->request("builtinHexagonalPrism");

    //---------------------------------------------
    SMeshAoS *builtin_oct_prism_mesh = new SMeshAoS();
    SShape *builtin_oct_prism_shape = new SShape();
    primitives::createOctagonalPrismMesh(builtin_oct_prism_mesh, 1.0f, FG_TRUE,
                                         M_PIF/2.0f, Vec3f(1.0f, 0.0f, 0.0f));
    CModel *octPrismModel = new CModelResource();
    octPrismModel->setModelType(ModelType::MODEL_BUILTIN);
    octPrismModel->setName("builtinOctagonalPrism");
    builtin_oct_prism_shape->name = "builtinOctagonalPrism";
    builtin_oct_prism_shape->mesh = builtin_oct_prism_mesh;
    builtin_oct_prism_shape->material = new SMaterial();
    builtin_oct_prism_shape->material->diffuseTexName = "empty.tga";
    builtin_oct_prism_shape->material->shaderName = "sPlainEasy";
    octPrismModel->addShape(builtin_oct_prism_shape);
    //static_cast<resource::CResourceManager *>(m_pResourceMgr)->request("empty.tga");
    if(!static_cast<resource::CResourceManager *>(m_pResourceMgr)->insert(octPrismModel)) {
        static_cast<resource::CResourceManager *>(m_pResourceMgr)->remove(octPrismModel);
        delete octPrismModel;
    }
    static_cast<resource::CResourceManager *>(m_pResourceMgr)->request("builtinOctagonalPrism");

    //---------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////

gfx::CGfxMain::CLoader::CLoader(CGfxMain* pGfxMain) :
m_pSplashTex(NULL),
m_pProgressTex(NULL),
m_pGfxMain(pGfxMain),
m_mvp(),
m_mat(),
m_progress(0.0f) { }
//------------------------------------------------------------------------------

gfx::CGfxMain::CLoader::CLoader(const CLoader& orig) {
    if(this != &orig) {
        this->m_pSplashTex = orig.m_pSplashTex;
        this->m_pProgressTex = orig.m_pProgressTex;
        this->m_pGfxMain = orig.m_pGfxMain;
        this->m_mvp = orig.m_mvp;
        this->m_mat = orig.m_mat;
        this->m_progress = orig.m_progress;
    }
}
//------------------------------------------------------------------------------

gfx::CGfxMain::CLoader::~CLoader() {
    m_pSplashTex = NULL;
    m_pProgressTex = NULL;
    m_pGfxMain = NULL;
    m_progress = 0.0f;
    m_mvp.identity();
}
//------------------------------------------------------------------------------

void gfx::CGfxMain::CLoader::update(const float diff) {
    if(!m_pGfxMain || !m_pSplashTex || !context::isInit())
        return;
    if(!m_pGfxMain->getShaderManager()->getCurrentProgram())
        return;
    setupMVP();
    m_pGfxMain->getMainWindow()->clearColor();
    m_progress += diff;
    if(m_progress > 100.0f)
        m_progress = 100.0f;
    if(m_progress < 0.0f)
        m_progress = 0.0f;
    float ratio = m_progress / 100.0f;
    //float sw = m_pSplashTex->getWidth();
    //float sh = m_pSplashTex->getHeight();
    float ww = m_pGfxMain->getMainWindow()->getWidth();
    float wh = m_pGfxMain->getMainWindow()->getHeight();
    /// The splash screen will be shown centered, with proper proportion
    /// based on the screen dimensions
    /// Get the lower dimensions
    float mextent = (float)glm::min((int)ww, (int)wh)*0.9f;
    /// Bind the splash texture
    context::bindTexture(m_pSplashTex->getRefGfxID());
    // Centered on screen, aspect ratio 1:1 regardless of texture dimensions (for now)
    m_mat = math::translate(Matrix4f(),
                            Vec3f(ww / 2.0f,
                                  wh / 2.0f,
                                  0.0f));
    m_mat = math::rotate(m_mat, (float)ratio * M_PIF * (70.0f / (float)FG_RAND(100, 110)), Vec3f(0.0f, 0.0f, 1.0f));
    m_mat = math::scale(m_mat, Vec3f(mextent, mextent, 0.0f));
    m_mvp.calculate(m_mat);
    m_pGfxMain->getShaderManager()->getCurrentProgram()->setUniform(&m_mvp);
    primitives::drawSquare2D();

    if(!m_pProgressTex || m_progress < FG_EPSILON) {
        m_pGfxMain->getMainWindow()->swapBuffers();
        return;
    }
    float pw = ratio * ww;
    float ph = 0.07f * wh;
    /// Bind the progress texture
    context::bindTexture(m_pProgressTex->getRefGfxID());
    // Bottom-left of the screen
    m_mat = math::translate(Matrix4f(),
                            Vec3f(ww / 2.0f,
                                  wh - ph / 2.0f,
                                  0.0f));
    m_mat = math::scale(m_mat, Vec3f(pw, ph, 0.0f));
    m_mvp.calculate(m_mat);
    m_pGfxMain->getShaderManager()->getCurrentProgram()->setUniform(&m_mvp);
    primitives::drawSquare2D();
    m_pGfxMain->getMainWindow()->swapBuffers();
}

////////////////////////////////////////////////////////////////////////////////

void gfx::CGfxMain::setupLoader(void) {
    if(!m_pResourceMgr)
        return;
    if(!m_textureMgr->isInit())
        return;
    resource::CResourceManager *pResourceMgr = static_cast<resource::CResourceManager *>(m_pResourceMgr);
    /// #FIXME - builtin texture names... unacceptable
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
    // DEVICE YIELD
    m_loader->setSplashTexture(texture);
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
    // DEVICE YIELD
    m_loader->setProgressTexture(texture);

}
//------------------------------------------------------------------------------

void gfx::CGfxMain::closeGFX(fgBool suspend) {
    FG_LOG_DEBUG("Closing GFX subsystem...");
    if(m_init) {
#if defined(FG_USING_SDL2)
        // context::getGLContext()
        SDL_GL_MakeCurrent(m_mainWindow->getSysPtr(), NULL);
#endif
        if(m_mainWindow && !suspend) {
            m_mainWindow->close();
        }
        gfx::CPlatform::quit(suspend);
        unregisterResourceCallbacks();
        unregisterSceneCallbacks();
    }
    m_init = FG_FALSE;
}
//------------------------------------------------------------------------------

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

    if(context::isInit()) {
        context::deleteAllBuffers();
    }

    if(status) {
        // With parameter TRUE the SDL will not be closed
        // Window will not be destroyed
        closeGFX(FG_TRUE);
    }
    if(!status) {
        FG_LOG_WARNING("GFX: Suspension of GFX subsystem finished with errors");
    } else {
        FG_LOG_DEBUG("GFX: Suspension of GFX subsystem finished with no errors");
    }
    event::CEventManager* pEventMgr = static_cast<event::CEventManager*>(m_pEventMgr);
    event::SProgram* programEvent = (event::SProgram*)pEventMgr->requestEventStruct(event::PROGRAM_SUSPEND);
    event::CArgumentList* argList = pEventMgr->requestArgumentList();
    programEvent->isOriginGfx = FG_TRUE;
    programEvent->isSuccess = status;
    argList->push(event::SArgument::Type::ARG_TMP_POINTER, (void*)programEvent);
    pEventMgr->throwEvent(event::PROGRAM_SUSPEND, argList);
    return status;
}
//------------------------------------------------------------------------------

fgBool gfx::CGfxMain::resumeGFX(void) {
    fgBool status = FG_TRUE;
    if(!gfx::CGfxMain::initGFX())
        status = FG_FALSE;
    setupResourceManager(m_pResourceMgr);
    if(m_textureMgr && status)
        if(!m_textureMgr->allToVRAM(FG_TRUE))
            status = FG_FALSE;
    if(m_shaderMgr && m_textureMgr) {
        // compile and link only recent shaders
        if(!m_shaderMgr->compileShaders(FG_TRUE))
            status = FG_FALSE;
        if(!m_shaderMgr->linkShaders(FG_TRUE))
            status = FG_FALSE;
    }
    generateBuiltInData();
    registerSceneCallbacks();

    if(!status) {
        FG_LOG_WARNING("GFX: Resume of GFX subsystem finished with errors");
    } else {
        FG_LOG_DEBUG("GFX: Resume of GFX subsystem finished with no errors");
    }
    event::CEventManager* pEventMgr = static_cast<event::CEventManager*>(m_pEventMgr);
    event::SProgram* programEvent = (event::SProgram*)pEventMgr->requestEventStruct(event::PROGRAM_RESUME);
    event::CArgumentList* argList = pEventMgr->requestArgumentList();
    programEvent->isOriginGfx = FG_TRUE;
    programEvent->isSuccess = status;
    argList->push(event::SArgument::Type::ARG_TMP_POINTER, (void*)programEvent);
    pEventMgr->throwEvent(event::PROGRAM_RESUME, argList);
    return status;
}
//------------------------------------------------------------------------------

void gfx::CGfxMain::preRender(void) {
    if(!context::isInit())
        return;
    if(m_particleSystem) {
        m_particleSystem->calculate();
    }
#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->begin("GFX::3DScene::sortCalls");
    }
#endif
    m_3DScene->sortCalls();
#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("GFX::3DScene::sortCalls");
        profile::g_debugProfiling->begin("GFX::2DScene::sortCalls");
    }
#endif
    m_2DScene->sortCalls();
#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("GFX::2DScene::sortCalls");
    }
#endif

    m_3DScene->update();
    m_2DScene->update();
}
//------------------------------------------------------------------------------

fgBool gfx::CGfxMain::prepareFrame(void) {
    if(!m_mainWindow || !context::isInit()) {
        FG_LOG_ERROR("Main window / context is NULL");
        return FG_FALSE;
    }
    if(!m_textureMgr || !m_shaderMgr) {
        FG_LOG_ERROR("No texture / shader manager");
        return FG_FALSE;

    }
    GLCheckError();
    m_mainWindow->clearColor();

    context::viewport();
    context::scissor();
    context::setCullFace(FG_TRUE);
    context::setDepthTest(FG_TRUE);
    context::setBlend(FG_FALSE);
    context::frontFace(FrontFace::FACE_CCW);
    context::setCapability(gfx::DEPTH_WRITEMASK, FG_TRUE);

    return FG_TRUE;
}
//------------------------------------------------------------------------------

void gfx::CGfxMain::render(void) {
    glm::mat4 Model;
    resource::CResourceManager *rm = NULL;
    ::std::string sPlainEasyShaderName("sPlainEasy");
    ::std::string sOrthoEasyShaderName("sOrthoEasy");
    ::std::string sSkyBoxEasyShaderName("sSkyBoxEasy");

    rm = (resource::CResourceManager *)m_textureMgr->getResourceManager();
    if(!rm) {
        FG_LOG_ERROR("Cant access resource manager.");
        return;
    }

    m_3DScene->getCamera()->update();
    m_3DScene->getMVP()->setCamera(m_3DScene->getCamera());
    m_3DScene->getMVP()->setPerspective(45.0f, m_mainWindow->getAspect());
    m_3DScene->setSkyBoxShader(sSkyBoxEasyShaderName); // #FIXME #FUBAR

    //
    // OH MY GOD HOW THIS SUX #FIXME
    //
    if(true) {
        // Load proper texture
        static resource::CResource *pResourceX = NULL;
        if(!pResourceX)
            pResourceX = static_cast<resource::CResourceManager *>(m_pResourceMgr)->get("PurpleNebulaCube");
        if(pResourceX->getResourceType() == resource::TEXTURE) {
            gfx::CTexture *pTexture = static_cast<gfx::CTexture *>(pResourceX);
            if(pTexture) {
                STextureID &texID = pTexture->getRefGfxID();
                m_3DScene->getSkyBox()->setTexture(texID);
            }
        }
    }

    CShaderProgram *sPlainEasyProgram = m_shaderMgr->get(sPlainEasyShaderName);
    if(!sPlainEasyProgram) {
        FG_LOG_ERROR("Cant access sPlainEasy shader program.");
        return;
    }
    m_shaderMgr->useProgram(sPlainEasyProgram);
    sPlainEasyProgram->setUniform(FG_GFX_USE_TEXTURE, 1.0f);
    sPlainEasyProgram->setUniform(FG_GFX_PLAIN_TEXTURE, (fgGFXint)0);

#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->begin("GFX::3DScene::render");
    }
#endif
    // 
    // RENDER THE 3D SCENE
    //
    m_3DScene->render();

#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("GFX::3DScene::render");
    }
#endif
    ////////////////////////////////////////////////////////////////////////////
    // 2D LAYER DRAWING TEST - NEEDS TO WORK DIFFERENTLY
    // THIS IS FOR GUI DRAWING - SPECIAL ORTHO SHADER
    ////////////////////////////////////////////////////////////////////////////
    context::frontFace(FrontFace::FACE_CCW);
    gfx::CShaderProgram *sOrthoEasyProgram = m_shaderMgr->get(sOrthoEasyShaderName);
    if(!sOrthoEasyProgram) {
        FG_LOG_ERROR("Cant access sOrthoEasy shader program.");
        return;
    }
    m_shaderMgr->useProgram(sOrthoEasyProgram);
    sOrthoEasyProgram->setUniform(FG_GFX_CUSTOM_COLOR, 1.0f, 1.0f, 1.0f, 1.0f);
    context::setBlend(FG_TRUE);
    m_2DScene->getMVP()->setOrtho(0.0f,
                                  (float)m_mainWindow->getWidth(),
                                  (float)m_mainWindow->getHeight(),
                                  0.0f);
    m_2DScene->render();
    context::blendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    context::setBlend(FG_FALSE);

    // #FIXME ! TOTAL FUBAR SITUATION ! OMG ! OH MY !
    m_shaderMgr->useProgram(sOrthoEasyProgram);
    Model = math::translate(Model, Vec3f(0.0f, 0.0f, 0.0f));
    CMVPMatrix mvp_lol;
    CMVPMatrix *MVP = &mvp_lol;
    MVP->identity();
    MVP->setOrtho(0.0f,
                  (float)m_mainWindow->getWidth(),
                  (float)m_mainWindow->getHeight(),
                  0.0f);
    MVP->calculate(Model);
    sOrthoEasyProgram->setUniform(MVP);
    context::setBlend(FG_TRUE);
    context::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    context::scissor(0, 0, m_mainWindow->getWidth(), m_mainWindow->getHeight()); // #THA FUCK?
    context::frontFace(FrontFace::FACE_CCW);
}
//------------------------------------------------------------------------------

fgBool gfx::CGfxMain::setupResourceManager(fg::base::CManager *pResourceManager) {
    if(!pResourceManager)
        return FG_FALSE;
    if(pResourceManager->getManagerType() != FG_MANAGER_RESOURCE) {
        return FG_FALSE;
    }
    if(!m_textureMgr)
        m_textureMgr = new CTextureManager(pResourceManager);
    else
        m_textureMgr->setResourceManager(pResourceManager);
    m_pResourceMgr = pResourceManager;
    if(m_3DScene)
        m_3DScene->setResourceManager(m_pResourceMgr);
    if(m_2DScene)
        m_2DScene->setResourceManager(m_pResourceMgr);
    if(m_particleSystem) {
        m_particleSystem->setResourceManager(m_pResourceMgr);
        //m_particleSystem->setSceneManager(m_2DScene);
        m_particleSystem->setSceneManager(m_3DScene); // Particle system working in 3D space
        m_particleSystem->initialize();
    }
    fg::base::CManager *pEventMgr = static_cast<resource::CResourceManager *>(m_pResourceMgr)->getEventManager();
    if(!pEventMgr) {
        unregisterResourceCallbacks();
        unregisterProgramCallbacks();
        m_pEventMgr = NULL;
    } else if(m_pEventMgr && m_pEventMgr != pEventMgr) {
        unregisterResourceCallbacks();
        unregisterProgramCallbacks();
    }
    m_pEventMgr = pEventMgr;
    if(m_pEventMgr) {
        registerResourceCallbacks();
        registerProgramCallbacks();
    }
    return m_textureMgr->initialize(); // #FIXME - texture mgr init ?
}
//------------------------------------------------------------------------------

fgBool gfx::CGfxMain::preLoadShaders(void) {
    if(!m_shaderMgr) {
        return FG_FALSE;
    }
    if(!m_shaderMgr->isInit())
        m_shaderMgr->initialize();
    return m_shaderMgr->preLoadShaders();
}
//------------------------------------------------------------------------------

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
//------------------------------------------------------------------------------

fgBool gfx::CGfxMain::resourceCreatedHandler(event::CArgumentList* argv) {
    if(!argv)
        return FG_FALSE;
    event::SEvent* event_struct = (event::SEvent*)argv->getValueByID(0);
    if(!event_struct)
        return FG_FALSE;
    event::EventType type = event_struct->code;
    if(type != event::RESOURCE_CREATED)
        return FG_FALSE;
    event::SResource* resourceEvent = (event::SResource*)event_struct;
    resource::CResource *pResource = resourceEvent->resource;
    if(!pResource)
        return FG_FALSE;

    if(pResource->getResourceType() != resource::MODEL3D && pResource->getResourceType() != resource::PARTICLE_EFFECT)
        return FG_FALSE;

    if(pResource->getResourceType() == resource::MODEL3D) {

        CModelResource* pModel = static_cast<CModelResource*>(pResource);
        CModelResource::ShapesVec& shapes = pModel->getRefShapes();
        resource::CResourceManager* pResourceMgr = static_cast<resource::CResourceManager*>(m_pResourceMgr);

        if(pModel) {
            SMaterial* pMainMaterial = pModel->getMainMaterial();
            if(!pModel->getMainMaterial()->shaderProgram) {
                pModel->getMainMaterial()->shaderProgram =
                        m_shaderMgr->get(pModel->getMainMaterial()->shaderName);
            }
            //#FIXME
            if(pResourceMgr) {
                resource::CResource* tex = NULL;
                // Ambient texture handle lookup
                tex = pResourceMgr->request(pMainMaterial->ambientTexName);
                if(tex) {
                    if(tex->getResourceType() == resource::TEXTURE) {
                        pMainMaterial->ambientTex = static_cast<CTextureResource *>(tex);
                    }
                }
                // Diffuse texture handle lookup
                tex = pResourceMgr->request(pMainMaterial->diffuseTexName);
                if(tex) {
                    if(tex->getResourceType() == resource::TEXTURE) {
                        pMainMaterial->diffuseTex = static_cast<CTextureResource *>(tex);
                    }
                }
                // Specular texture handle lookup
                tex = pResourceMgr->request(pMainMaterial->specularTexName);
                if(tex) {
                    if(tex->getResourceType() == resource::TEXTURE) {
                        pMainMaterial->specularTex = static_cast<CTextureResource *>(tex);
                    }
                }
                // Normal texture handle lookup
                tex = pResourceMgr->request(pMainMaterial->normalTexName);
                if(tex) {
                    if(tex->getResourceType() == resource::TEXTURE) {
                        pMainMaterial->normalTex = static_cast<CTextureResource *>(tex);
                    }
                }
            }
        }

        int n = shapes.size();
        if(n) {
            FG_LOG_DEBUG("GFX: Uploading static vertex data to VBO for model: '%s'", pModel->getNameStr());
        }
        for(int i = 0; i < n; i++) {
            SShape *pShape = shapes[i];
            if(!pShape)
                continue;
            if(pShape->material) {
                if(!pShape->material->shaderProgram && pShape->material->shaderName.length()) {
                    pShape->material->shaderProgram =
                            m_shaderMgr->get(pShape->material->shaderName);
                }
            }
            if(pResourceMgr) {
                resource::CResource* tex = NULL;
                // Ambient texture handle lookup
                tex = pResourceMgr->request(pShape->material->ambientTexName);
                if(tex) {
                    if(tex->getResourceType() == resource::TEXTURE) {
                        pShape->material->ambientTex = static_cast<CTextureResource *>(tex);
                    }
                }
                // Diffuse texture handle lookup
                tex = pResourceMgr->request(pShape->material->diffuseTexName);
                if(tex) {
                    if(tex->getResourceType() == resource::TEXTURE) {
                        pShape->material->diffuseTex = static_cast<CTextureResource *>(tex);
                    }
                }
                // Specular texture handle lookup
                tex = pResourceMgr->request(pShape->material->specularTexName);
                if(tex) {
                    if(tex->getResourceType() == resource::TEXTURE) {
                        pShape->material->specularTex = static_cast<CTextureResource *>(tex);
                    }
                }
                // Normal texture handle lookup
                tex = pResourceMgr->request(pShape->material->normalTexName);
                if(tex) {
                    if(tex->getResourceType() == resource::TEXTURE) {
                        pShape->material->normalTex = static_cast<CTextureResource *>(tex);
                    }
                }
            }
            if(!pShape->mesh)
                continue;
            if(!context::isBuffer(pShape->mesh->getPtrVBO())) {
                FG_LOG_DEBUG("GFX: Uploading static vertex data to VBO for shape: '%s'", pShape->name.c_str());
                pShape->mesh->genBuffers();
            }
        }
    } else if(pResource->getResourceType() == resource::PARTICLE_EFFECT) {
        CParticleEffect *pEffect = static_cast<CParticleEffect *>(pResource);
        if(!pEffect->getShaderProgram() && pEffect->getShaderName().length()) {
            pEffect->setShaderProgram(m_shaderMgr->get(pEffect->getShaderName()));
        }
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CGfxMain::sceneNodeInsertedHandler(event::CArgumentList* argv) {
    if(!argv)
        return FG_FALSE;
    event::SSceneEvent *pEventStruct = (event::SSceneEvent *)argv->getValueByID(0);
    CSceneManager* pSceneManager = (CSceneManager *)argv->getValueByID(1);
    if(!pEventStruct)
        return FG_FALSE;
    event::EventType type = pEventStruct->code;
    if(type != event::SCENE_NODE_INSERTED)
        return FG_FALSE;
    if(!pSceneManager) {
        // fail
        FG_LOG_DEBUG("GFX: Scene handler: argument list did not contain valid pointer to SceneManager");
        return FG_FALSE;
    }
    if(!pSceneManager->isManaged(pEventStruct->node.handleNodeA)) {
        // the handle is no longer valid
        // probably before this event was handled the node was removed/deleted
        // the pointer wont be valid (50% chance)
        return FG_FALSE;
    }

    if(pEventStruct->node.pNodeA) {
        pEventStruct->node.pNodeA->refreshGfxInternals();

        if(pEventStruct->node.pNodeA->getNodeType() == gfx::SCENE_NODE_OBJECT) {
            // need to externally refresh any used materials
            // #FIXME
            CSceneNodeObject* pNodeObj = (CSceneNodeObject*)pEventStruct->node.pNodeA;
            CSceneNode::ChildrenVec& children = pNodeObj->getChildren();
            unsigned int n = children.size();
            for(unsigned int i = 0; i < n; i++) {
                CSceneNode* pNode = children[i];
                if(!pNode)
                    continue;
                if(pNode->getNodeType() == gfx::SCENE_NODE_MESH) {
                    // #FIXME MESH NODE FUBAR
                    // #FIXME MATERIAL
                    CSceneNodeMesh* pNodeMesh = (CSceneNodeMesh*)pNode;
                    SMaterial* pMaterial = pNodeMesh->getMaterial();
                    SMeshBase* pMesh = pNodeMesh->getMesh();
                    resource::CResourceManager* pResourceMgr = static_cast<resource::CResourceManager*>(m_pResourceMgr);
                    if(pMaterial) {
                        // #FIXME - TOTAL FUBAR
                        if(!pMaterial->shaderProgram) {
                            pMaterial->shaderProgram = m_shaderMgr->get(pMaterial->shaderName);
                        }
                        //#FIXME
                        if(pResourceMgr) {
                            resource::CResource* tex = NULL;
                            // Ambient texture handle lookup
                            tex = pResourceMgr->request(pMaterial->ambientTexName);
                            if(tex) {
                                if(tex->getResourceType() == resource::TEXTURE) {
                                    pMaterial->ambientTex = static_cast<CTextureResource *>(tex);
                                }
                            }
                            // Diffuse texture handle lookup
                            tex = pResourceMgr->request(pMaterial->diffuseTexName);
                            if(tex) {
                                if(tex->getResourceType() == resource::TEXTURE) {
                                    pMaterial->diffuseTex = static_cast<CTextureResource *>(tex);
                                }
                            }
                            // Specular texture handle lookup
                            tex = pResourceMgr->request(pMaterial->specularTexName);
                            if(tex) {
                                if(tex->getResourceType() == resource::TEXTURE) {
                                    pMaterial->specularTex = static_cast<CTextureResource *>(tex);
                                }
                            }
                            // Normal texture handle lookup
                            tex = pResourceMgr->request(pMaterial->normalTexName);
                            if(tex) {
                                if(tex->getResourceType() == resource::TEXTURE) {
                                    pMaterial->normalTex = static_cast<CTextureResource *>(tex);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CGfxMain::programEventHandler(event::CArgumentList* argv) {
    if(!argv)
        return FG_FALSE;
    event::SProgram* pProgram = (event::SProgram*)argv->getValueByID(0);
    if(!pProgram)
        return FG_FALSE;
    event::EventType type = pProgram->eventType;
    if(type != event::PROGRAM_RESUME && type != event::PROGRAM_SUSPEND) {
        return FG_FALSE;
    }
    if(!pProgram->isOriginGfx) {
        return FG_FALSE;
    }
    if(type == event::PROGRAM_SUSPEND) {

    } else {
        // GFX RESUME
        // need to refresh gfx internals of all SCENE NODES
        this->get3DScene()->refreshGfxInternals();
        this->get2DScene()->refreshGfxInternals();
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------
