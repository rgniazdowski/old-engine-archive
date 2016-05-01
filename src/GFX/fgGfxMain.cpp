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

#include "Math/fgMatrixOperations.h"

#include "fgLog.h"

using namespace fg;
//------------------------------------------------------------------------------

gfx::CGfxMain::CGfxMain() :
m_loader(NULL),
m_textureMgr(NULL),
m_pResourceMgr(NULL),
m_pEventMgr(NULL),
m_shaderMgr(NULL),
m_nodeFactory(NULL),
m_mainWindow(NULL),
m_p3DScene(NULL),
m_p2DScene(NULL),
m_particleSystem(NULL),
m_resourceCreatedCallback(NULL),
m_sceneNodeInsertedCallback(NULL),
m_programEventCallback(NULL),
m_init(FG_FALSE) {
    //m_p3DScene = new gfx::CScene3D();
    //m_p2DScene = new gfx::CScene2D();
    m_particleSystem = new gfx::CParticleSystem();
    //m_particleSystem->setSceneManager(m_p3DScene);

    m_shaderMgr = new gfx::CShaderManager();
    //m_p3DScene->setShaderManager(m_shaderMgr);
    //m_p2DScene->setShaderManager(m_shaderMgr);
    m_nodeFactory = new CNodeFactory();
    //m_p3DScene->setNodeFactory(m_nodeFactory);
    //m_p2DScene->setNodeFactory(m_nodeFactory);

    m_nodeFactory->registerObject(SCENE_NODE_OBJECT, new util::CFactoryObject<CSceneNodeObject>());
    m_nodeFactory->registerObject(SCENE_NODE_MESH, new util::CFactoryObject<CSceneNodeMesh>());
    m_nodeFactory->registerObject(SCENE_NODE_TRIGGER, new util::CFactoryObject<CSceneNodeTrigger>());
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
#if 0
    if(m_p3DScene) {
        FG_LOG_DEBUG("GFX: Destroying the 3D Scene...");
        delete m_p3DScene;
        m_p3DScene = NULL;
    }
    if(m_p2DScene) {
        FG_LOG_DEBUG("GFX: Destroying the 2D Scene...");
        delete m_p2DScene;
        m_p2DScene = NULL;
    }
#endif
    if(m_nodeFactory) {
        delete m_nodeFactory;
        m_nodeFactory = NULL;
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
        m_resourceCreatedCallback = new event::CMethodCallback<CGfxMain>(this, &gfx::CGfxMain::resourceCreatedHandler);

    static_cast<event::CEventManager *>(m_pEventMgr)->addCallback(event::RESOURCE_CREATED, m_resourceCreatedCallback);
}
//------------------------------------------------------------------------------

void gfx::CGfxMain::unregisterResourceCallbacks(void) {
    if(!m_pEventMgr)
        return;

    static_cast<event::CEventManager *>(m_pEventMgr)->removeCallback(event::RESOURCE_CREATED, m_resourceCreatedCallback);
}
//------------------------------------------------------------------------------

void gfx::CGfxMain::registerSceneCallbacks(void) {
    if(!m_sceneNodeInsertedCallback) {
        m_sceneNodeInsertedCallback =
                new event::CMethodCallback<self_type>(this,
                                                      &self_type::sceneNodeInsertedHandler);
    }
    if(m_p3DScene) {
        m_p3DScene->getInternalEventManager()->addCallback(event::SCENE_NODE_INSERTED,
                                                           m_sceneNodeInsertedCallback);
    }
    if(m_p2DScene) {
        m_p2DScene->getInternalEventManager()->addCallback(event::SCENE_NODE_INSERTED,
                                                           m_sceneNodeInsertedCallback);
    }
}
//------------------------------------------------------------------------------

void gfx::CGfxMain::unregisterSceneCallbacks(void) {
    if(m_p3DScene)
        m_p3DScene->getInternalEventManager()->removeCallback(event::SCENE_NODE_INSERTED, m_sceneNodeInsertedCallback);
    if(m_p2DScene)
        m_p2DScene->getInternalEventManager()->removeCallback(event::SCENE_NODE_INSERTED, m_sceneNodeInsertedCallback);
}
//------------------------------------------------------------------------------

void gfx::CGfxMain::registerProgramCallbacks(void) {
    if(!m_pEventMgr)
        return;

    if(!m_programEventCallback)
        m_programEventCallback = new event::CMethodCallback<CGfxMain>(this, &gfx::CGfxMain::programEventHandler);

    static_cast<event::CEventManager *>(m_pEventMgr)->addCallback(event::PROGRAM_QUIT, m_programEventCallback);
    static_cast<event::CEventManager *>(m_pEventMgr)->addCallback(event::PROGRAM_SUSPEND, m_programEventCallback);
    static_cast<event::CEventManager *>(m_pEventMgr)->addCallback(event::PROGRAM_RESUME, m_programEventCallback);
}
//------------------------------------------------------------------------------

void gfx::CGfxMain::unregisterProgramCallbacks(void) {
    if(!m_pEventMgr)
        return;

    static_cast<event::CEventManager *>(m_pEventMgr)->removeCallback(event::PROGRAM_QUIT, m_programEventCallback);
    static_cast<event::CEventManager *>(m_pEventMgr)->removeCallback(event::PROGRAM_SUSPEND, m_programEventCallback);
    static_cast<event::CEventManager *>(m_pEventMgr)->removeCallback(event::PROGRAM_RESUME, m_programEventCallback);
}
//------------------------------------------------------------------------------

fgBool gfx::CGfxMain::initGFX(void) {
    float t1 = timesys::ms();
    fgBool status = FG_TRUE;
    
    if(!m_mainWindow && status) {
        m_mainWindow = new gfx::CWindow();
    }
    m_mainWindow->registerOnSwap(&gfx::CGfxMain::handleMainWindowBufferSwap, (void*)this);
    if(!m_loader)
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
        gfx::context::initialize(m_mainWindow->getSysPtr());
#endif /* FG_USING_SDL2 */
    }
    if(status) {
        if(!context::isInit()) {
#if !defined(FG_USING_SDL2)
            status = context::initialize();
#endif /* FG_USING_SDL2 */
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
        //m_p2DScene->getMVP()->setOrtho(0.0f, (float)m_mainWindow->getWidth(), (float)m_mainWindow->getHeight(), 0.0f);
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
        //m_p3DScene->initialize();
        //m_p2DScene->initialize();
        //registerSceneCallbacks();
        m_shaderMgr->getUniformUpdater()->enable(shaders::UNIFORM_DIRECTIONAL_LIGHT);
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
    resource::CResourceManager* pResourceMgr = static_cast<resource::CResourceManager *>(m_pResourceMgr);
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
    pResourceMgr->request("empty.tga");
    if(!pResourceMgr->insert(cubeModel)) {
        pResourceMgr->remove(cubeModel);
        delete cubeModel;
    }
    // Should not call create manually on the 3D Model
    // This wont call the function for VBO upload
    pResourceMgr->request("builtinCube1x1");
    //--------------------------------------------------------------------------

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
    //pResourceMgr->request("empty.tga");
    if(!pResourceMgr->insert(sphereModel)) {
        pResourceMgr->remove(sphereModel);
        delete sphereModel;
    }
    pResourceMgr->request("builtinSphere");
    //--------------------------------------------------------------------------

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
    //pResourceMgr->request("empty.tga");
    if(!pResourceMgr->insert(quadModel)) {
        pResourceMgr->remove(quadModel);
        delete quadModel;
    }
    pResourceMgr->request("builtinQuad1x1");
    //--------------------------------------------------------------------------

    SMeshAoS *builtin_hex_prism_mesh = new SMeshAoS();
    SShape *builtin_hex_prism_shape = new SShape();
    primitives::createHexagonalPrismMesh(builtin_hex_prism_mesh, 1.0f, FG_TRUE,
                                         M_PIF / 2.0f, Vec3f(1.0f, 0.0f, 0.0f));
    CModel *hexPrismModel = new CModelResource();
    hexPrismModel->setModelType(ModelType::MODEL_BUILTIN);
    hexPrismModel->setName("builtinHexagonalPrism");
    builtin_hex_prism_shape->name = "builtinHexagonalPrism";
    builtin_hex_prism_shape->mesh = builtin_hex_prism_mesh;
    builtin_hex_prism_shape->material = new SMaterial();
    builtin_hex_prism_shape->material->diffuseTexName = "empty.tga";
    builtin_hex_prism_shape->material->shaderName = "sPlainEasy";
    hexPrismModel->addShape(builtin_hex_prism_shape);
    //pResourceMgr->request("empty.tga");
    if(!pResourceMgr->insert(hexPrismModel)) {
        pResourceMgr->remove(hexPrismModel);
        delete hexPrismModel;
    }
    pResourceMgr->request("builtinHexagonalPrism");

    //--------------------------------------------------------------------------
    SMeshAoS *builtin_oct_prism_mesh = new SMeshAoS();
    SShape *builtin_oct_prism_shape = new SShape();
    primitives::createOctagonalPrismMesh(builtin_oct_prism_mesh, 1.0f, FG_TRUE,
                                         M_PIF / 2.0f, Vec3f(1.0f, 0.0f, 0.0f));
    CModel *octPrismModel = new CModelResource();
    octPrismModel->setModelType(ModelType::MODEL_BUILTIN);
    octPrismModel->setName("builtinOctagonalPrism");
    builtin_oct_prism_shape->name = "builtinOctagonalPrism";
    builtin_oct_prism_shape->mesh = builtin_oct_prism_mesh;
    builtin_oct_prism_shape->material = new SMaterial();
    builtin_oct_prism_shape->material->diffuseTexName = "empty.tga";
    builtin_oct_prism_shape->material->shaderName = "sPlainEasy";
    octPrismModel->addShape(builtin_oct_prism_shape);
    //pResourceMgr->request("empty.tga");
    if(!pResourceMgr->insert(octPrismModel)) {
        pResourceMgr->remove(octPrismModel);
        delete octPrismModel;
    }
    pResourceMgr->request("builtinOctagonalPrism");

    //--------------------------------------------------------------------------
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
    m_pGfxMain->getShaderManager()->useProgram("DefaultShader");
    CShaderProgram* pProgram = m_pGfxMain->getShaderManager()->getCurrentProgram();
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
    context::activeTexture(GL_TEXTURE0);
    context::bindTexture(m_pSplashTex->getRefGfxID());
    // Centered on screen, aspect ratio 1:1 regardless of texture dimensions (for now)
    m_mat = math::translate(Matrix4f(),
                            Vec3f(ww / 2.0f,
                                  wh / 2.0f,
                                  0.0f));
    m_mat = math::rotate(m_mat, (float)ratio * M_PIF * (70.0f / (float)FG_RAND(100, 110)), Vec3f(0.0f, 0.0f, 1.0f));
    m_mat = math::scale(m_mat, Vec3f(mextent, mextent, 0.0f));
    m_mvp.calculate(m_mat);

    pProgram->setUniform(shaders::UNIFORM_DIFFUSE_TEXTURE, 0);
    pProgram->setUniform(shaders::UNIFORM_USE_TEXTURE, 1.0f);
    pProgram->setUniform(&m_mvp);
    pProgram->setUniform(shaders::UNIFORM_CUSTOM_COLOR,
                         1.0f,
                         1.0f,
                         1.0f,
                         1.0f);
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
    pProgram->setUniform(&m_mvp);
    primitives::drawSquare2D();
    m_pGfxMain->getMainWindow()->swapBuffers();
}
//------------------------------------------------------------------------------

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
    m_shaderMgr->useProgram("DefaultShader");
}
//------------------------------------------------------------------------------

void gfx::CGfxMain::closeGFX(fgBool suspend) {
    FG_LOG_DEBUG("Closing GFX subsystem...");
    if(m_init) {
#if defined(FG_USING_SDL2)        
        SDL_GL_MakeCurrent(m_mainWindow->getSysPtr(), NULL);
#endif
        if(m_mainWindow && !suspend) {
            m_mainWindow->close();
        }
        //gfx::CPlatform::quit(suspend);
        context::destroy();
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
    //m_p3DScene->update(timesys::elapsed(timesys::TICK_PRERENDER));
    //m_p2DScene->update(timesys::elapsed(timesys::TICK_PRERENDER));
    LayerPriorityQueueItor itor = m_layersQueue.begin(),
            end = m_layersQueue.end();
    for(; itor != end; itor++) {
        CLayer* pLayer = *itor;
#if defined(FG_DEBUG)
        if(g_DebugConfig.isDebugProfiling && !pLayer->getLayerName().empty()) {
            profile::g_debugProfiling->begin(pLayer->getLayerName());
        }
#endif
        pLayer->flush();
        pLayer->sortCalls();
#if defined(FG_DEBUG)
        if(g_DebugConfig.isDebugProfiling && !pLayer->getLayerName().empty()) {
            profile::g_debugProfiling->end(pLayer->getLayerName());
        }
#endif
    }
    m_p3DScene->update(timesys::elapsed(timesys::TICK_PRERENDER));
    m_p2DScene->update(timesys::elapsed(timesys::TICK_PRERENDER));
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
    // #FIXME
    SDirectionalLight mainLight;
    mainLight.direction = Vec3f(1.0f, 1.0, 1.0f);
    mainLight.ambient = Color4f(0.25f, 0.25f, 0.25f, 1.0f);
    mainLight.diffuse = Color4f(1.0f, 1.0f, 0.9f, 1.0f);
    mainLight.specular = Color4f(0.9f, 0.7f, 0.5f, 1.0f);
    Vec4f lightDir = m_p3DScene->getMVP()->getViewMatrix() * Vec4f(mainLight.direction, 0.0f);
    mainLight.direction = Vec3f(lightDir);

    m_shaderMgr->getUniformUpdater()->update(shaders::UNIFORM_DIRECTIONAL_LIGHT, mainLight);

    return FG_TRUE;
}
//------------------------------------------------------------------------------

void gfx::CGfxMain::render(void) {
    //m_p3DScene->getCamera()->setSpeed(350.0f);
    m_p3DScene->getCamera()->update();
    m_p3DScene->getMVP()->setCamera(m_p3DScene->getCamera());
    //m_p3DScene->getMVP()->setPerspective(45.0f, m_mainWindow->getAspect());

    //
    // OH MY GOD HOW THIS SUX #FIXME    
    if(true) {
        // Load proper texture
        static resource::CResource *pResourceX = NULL;
        if(!pResourceX)
            pResourceX = static_cast<resource::CResourceManager *>(m_pResourceMgr)->get("PurpleNebulaCube");
        if(pResourceX->getResourceType() == resource::TEXTURE) {
            gfx::CTexture *pTexture = static_cast<gfx::CTexture *>(pResourceX);
            if(pTexture) {
                STextureID &texID = pTexture->getRefGfxID();
                m_p3DScene->getSkyBox()->setTexture(texID);
            }
        }
    }
    LayerPriorityQueueItor itor = m_layersQueue.begin(),
            end = m_layersQueue.end();
    for(; itor != end; itor++) {
        CLayer* pLayer = *itor;
        pLayer->render();
    }
#if 0

    CShaderProgram *pDefaultProgram = m_shaderMgr->request(shaders::USAGE_DEFAULT_BIT | shaders::USAGE_LOW_QUALITY_BIT);
    if(!pDefaultProgram) {
        pDefaultProgram = m_shaderMgr->request(shaders::USAGE_FALLBACK_BIT);
        if(!pDefaultProgram) {
            FG_LOG_ERROR("Cant access default/fallback shader program.");
            return;
        }
    }
    m_shaderMgr->useProgram(pDefaultProgram);
    pDefaultProgram->setUniform(shaders::UNIFORM_USE_TEXTURE, 1.0f);
    pDefaultProgram->setUniform(shaders::UNIFORM_PLAIN_TEXTURE, (fgGFXint)0);
#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->begin("GFX::3DScene::render");
    }
#endif
    // 
    // RENDER THE 3D SCENE
    //
    m_p3DScene->render();

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
    gfx::CShaderProgram *p2DProgram = m_shaderMgr->request(shaders::USAGE_2D_RENDER_BIT);
    if(!p2DProgram) {
        FG_LOG_ERROR("Cant access shader program for 2D rendering.");
        return;
    }
    m_shaderMgr->useProgram(p2DProgram);
    p2DProgram->setUniform(shaders::UNIFORM_CUSTOM_COLOR, 1.0f, 1.0f, 1.0f, 1.0f);
    //context::setBlend(FG_TRUE);

    m_p2DScene->getMVP()->setOrtho(0.0f,
                                   (float)m_mainWindow->getWidth(),
                                   (float)m_mainWindow->getHeight(),
                                   0.0f);
    m_p2DScene->render();
#endif

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
    if(m_p3DScene)
        m_p3DScene->setResourceManager(m_pResourceMgr);
    if(m_p2DScene)
        m_p2DScene->setResourceManager(m_pResourceMgr);
    if(m_particleSystem) {
        m_particleSystem->setResourceManager(m_pResourceMgr);
        //m_particleSystem->setSceneManager(m_2DScene);
        //m_particleSystem->setSceneManager(m_p3DScene); // Particle system working in 3D space
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
    fgBool status = m_shaderMgr->preLoadShaders();
    return status;
}
//------------------------------------------------------------------------------

int gfx::CGfxMain::addLayer(CLayer* pLayer) {
    if(!pLayer)
        return -1;
    int index = m_layers.find(pLayer);
    if(index < 0) {
        // layer not found
        m_layers.push_back(pLayer);
        index = (int)m_layers.size() - 1;
        refreshLayersQueue();
    }
    return index;
}
//------------------------------------------------------------------------------

fgBool gfx::CGfxMain::removeLayer(CLayer* pLayer) {
    if(!pLayer)
        return FG_FALSE;
    int index = m_layers.find(pLayer);
    if(index >= 0) {
        m_layers.remove(index);
        refreshLayersQueue();
    }
    return (fgBool)(index >= 0);
}
//------------------------------------------------------------------------------

gfx::CLayer* gfx::CGfxMain::getLayer(const std::string& layerName) {
    if(layerName.empty())
        return NULL;
    return getLayer(layerName.c_str());
}
//------------------------------------------------------------------------------

gfx::CLayer const* gfx::CGfxMain::getLayer(const std::string& layerName) const {
    if(layerName.empty())
        return NULL;
    return getLayer(layerName.c_str());
}
//------------------------------------------------------------------------------

gfx::CLayer* gfx::CGfxMain::getLayer(const char* name) {
    if(!name)
        return NULL;
    if(!name[0])
        return NULL;
    const unsigned int n = m_layers.size();
    CLayer* pResult = NULL;
    for(unsigned int i = 0; i < n; i++) {
        CLayer* pLayer = m_layers[i];
        if(pLayer->getLayerName().compare(name) == 0) {
            pResult = pLayer;
            break;
        }
    }
    return pResult;
}
//------------------------------------------------------------------------------

gfx::CLayer const* gfx::CGfxMain::getLayer(const char* name) const {
    if(!name)
        return NULL;
    if(!name[0])
        return NULL;
    const unsigned int n = m_layers.size();
    const CLayer* pResult = NULL;
    for(unsigned int i = 0; i < n; i++) {
        const CLayer* pLayer = m_layers[i];
        if(pLayer->getLayerName().compare(name) == 0) {
            pResult = pLayer;
            break;
        }
    }
    return pResult;
}
//------------------------------------------------------------------------------

fgBool gfx::CGfxMain::setLayerID(CLayer* pLayer, int layerID) {
    int index = m_layers.find(pLayer);
    if(index < 0)
        return FG_FALSE;
    pLayer->setLayerID(layerID);
    refreshLayersQueue();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool gfx::CGfxMain::setLayerID(const std::string& name, int layerID) {
    CLayer* pLayer = getLayer(name);
    if(pLayer) {
        pLayer->setLayerID(layerID);
        refreshLayersQueue();
    }
    return (fgBool)(pLayer != NULL);
}
//------------------------------------------------------------------------------

fgBool gfx::CGfxMain::setLayerID(const char* name, int layerID) {
    CLayer* pLayer = getLayer(name);
    if(pLayer) {
        pLayer->setLayerID(layerID);
        refreshLayersQueue();
    }
    return (fgBool)(pLayer != NULL);
}
//------------------------------------------------------------------------------

void gfx::CGfxMain::refreshLayersQueue(void) {
    m_layersQueue.clear();
    const unsigned int n = m_layers.size();
    for(unsigned int i = 0; i < n; i++) {
        if(m_layers[i])
            m_layersQueue.push(m_layers[i]);
    }
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
        CModelResource::ShapesVec& shapes = pModel->getShapes();
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
    event::SSceneEvent* pEventStruct = (event::SSceneEvent*)argv->getValueByID(0);
    CSceneManager* pSceneManager = (CSceneManager*)argv->getValueByID(1);
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
        // the pointer wont be valid
        return FG_FALSE;
    }

    if(!pEventStruct->node.pNodeA) {
        return FG_FALSE;
    }

    if(!pEventStruct->node.pNodeA->doesExtend(gfx::SCENE_NODE_OBJECT)) {
        pEventStruct->node.pNodeA->refreshGfxInternals();
        return FG_TRUE; // event handled
    }
    // need to externally refresh any used materials
    // #FIXME
    CSceneNodeObject* pNodeObj = (CSceneNodeObject*)pEventStruct->node.pNodeA;
    CSceneNode::ChildrenVec& children = pNodeObj->getChildren();
    unsigned int n = children.size();
    for(unsigned int i = 0; i < n; i++) {
        CSceneNode* pNode = children[i];
        if(!pNode) {
            continue;
        }
        if(!pNode->checkNodeType(gfx::SCENE_NODE_MESH)) {
            continue;
        }
        // #FIXME MESH NODE FUBAR
        // #FIXME MATERIAL
        CSceneNodeMesh* pNodeMesh = (CSceneNodeMesh*)pNode;
        SMaterial* pMaterial = pNodeMesh->getMaterial();
        SMeshBase* pMesh = pNodeMesh->getMesh();
        if(!pMesh)
            continue;
        if(!pMaterial)
            continue; // nothing to do, this node is malformed
        if(pMesh->isSkinnedMesh()) {
            fgBool forceSkinningShader = FG_FALSE;
            // the mesh is skinned, need to request proper shader
            CShaderProgram* pProgram = m_shaderMgr->get(pMaterial->shaderName);
            if(!pProgram) {
                forceSkinningShader = FG_TRUE;
            } else if(pProgram->getUsageMask() & shaders::USAGE_MESH_SKINNING_BIT) {
                pMaterial->shaderProgram = pProgram;
            } else {
                forceSkinningShader = FG_TRUE;
            }
            if(forceSkinningShader) {
                pProgram = m_shaderMgr->request(shaders::USAGE_MESH_SKINNING_BIT);
                if(pProgram) {
                    pMaterial->shaderProgram = pProgram;
                    pMaterial->shaderName = pProgram->getName(); // copy new name
                    FG_LOG_DEBUG("GFX: Forcing shader '%s' on node: '%s'",
                                 pProgram->getNameStr(), pNodeMesh->getNameStr());
                }
            }
        }
        if(!pMaterial->shaderProgram) {
            pMaterial->shaderProgram = m_shaderMgr->get(pMaterial->shaderName);
        }

        resource::CResourceManager* pResourceMgr = static_cast<resource::CResourceManager*>(m_pResourceMgr); //#FIXME
        if(!pResourceMgr) {
            continue;
        }
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
    pEventStruct->node.pNodeA->refreshGfxInternals();

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
