/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgEngineMain.h"
#include "CEngineGfxCanvas.h"

#include "Event/fgEventManager.h"
#include "Event/fgInputHandler.h"
#include "Hardware/fgHardwareState.h"
#include "Util/fgProfiling.h"
#include "Util/fgStrings.h"
#include "fgDebugConfig.h"
#include "fgLog.h"

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <map>
//-----------------------------------------------------------------------------

CRenderTimer::CRenderTimer(CEngineGfxCanvas* gfxCanvas, float fps) :
base_type(),
m_fps(60.0f) {
    m_gfxCanvas = gfxCanvas;
    setFps(fps);
}
//-----------------------------------------------------------------------------

void CRenderTimer::Notify(void) {
    m_gfxCanvas->Refresh();
    //printf("RenderTime::Notify(): THREAD ID: %lu\n", pthread_self());
}
//-----------------------------------------------------------------------------

void CRenderTimer::start(void) {
    //printf("RenderTime::start(): THREAD ID: %lu\n", pthread_self());
    base_type::Start((int)(1000 / m_fps)); // #FIXME / this should be exactly 120 ?
}
//-----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(CEngineGfxCanvas, wxGLCanvas)
EVT_MOTION(CEngineGfxCanvas::OnMouseMoved)
EVT_LEFT_DOWN(CEngineGfxCanvas::OnMouseDown)
EVT_LEFT_UP(CEngineGfxCanvas::OnMouseReleased)
EVT_LEAVE_WINDOW(CEngineGfxCanvas::OnMouseLeftWindow)
EVT_SIZE(CEngineGfxCanvas::OnResized)
EVT_KEY_DOWN(CEngineGfxCanvas::OnKeyPressed)
EVT_KEY_UP(CEngineGfxCanvas::OnKeyReleased)
EVT_MOUSEWHEEL(CEngineGfxCanvas::OnMouseWheelMoved)
EVT_PAINT(CEngineGfxCanvas::OnPaint)
EVT_IDLE(CEngineGfxCanvas::OnIdle)
EVT_CLOSE(CEngineGfxCanvas::OnCloseEvent)
END_EVENT_TABLE()

#include "GFX/Scene/fgGfxBspCompiler.h"
fg::gfx::CBspCompiler *bspCompiler = NULL;

//-----------------------------------------------------------------------------

CEngineGfxCanvas::CEngineGfxCanvas(wxWindow* parent, int* args, fg::CEngineMain **engineMainOrig) :
wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE) {
    m_context = new wxGLContext(this);

    // To avoid flashing on MSW
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    m_argc = 0;
    m_argv[0] = NULL;
    m_argv[1] = NULL;

    m_isFrameFreeze = FG_FALSE;
    m_canInitialize = FG_FALSE;
    m_paint = FG_FALSE;
    m_isExit = FG_FALSE;
    m_appInit = FG_FALSE;
    m_isSuspend = FG_FALSE;
    m_isInitializing = FG_FALSE;

    m_onSwapCallback = new fg::event::CPlainFunctionCallback(&OnGfxWindowSwapBuffer, (void*)this);

    m_parentFrame = parent;
    m_engineMain = NULL;
    m_engineMainOrig = engineMainOrig;
    if(engineMainOrig) {
        m_engineMain = *engineMainOrig;
    }
}
//------------------------------------------------------------------------------

CEngineGfxCanvas::~CEngineGfxCanvas() {
    FG_LOG_DEBUG("WX: Main destructor called");
    //if(m_context && IsShown())
    //    wxGLCanvas::SetCurrent(*m_context);
    closeProgram();
    delete m_context;
    m_context = NULL;
    if(m_onSwapCallback) {
        delete m_onSwapCallback;
    }
    m_onSwapCallback = NULL;
}
//------------------------------------------------------------------------------

unsigned int CEngineGfxCanvas::executeCallbacks(InternalCallbackType cbType) {
    if((int)cbType >= NUM_ENGINE_CB_TYPES)
        return 0;
    unsigned int nCalls = 0;
    const unsigned int n = m_onEngineCallbacks[(int)cbType].size();
    for(unsigned int i = 0; i < n; i++) {
        CallbackData &info = m_onEngineCallbacks[(int)cbType][i];
        if(info.callback) {
            info.callback((void *)this, (void *)info.userData);
            nCalls++;
        }
    }
    return nCalls;
}
//------------------------------------------------------------------------------

fgBool CEngineGfxCanvas::registerCallback(InternalCallbackType cbType,
                                          CallbackFuncPtr pCallback,
                                          void* pUserData) {
    if(!pCallback || isRegistered(pCallback))
        return FG_FALSE;
    CallbackData callbackInfo(pCallback, pUserData);
    m_onEngineCallbacks[(int)cbType].push_back(callbackInfo);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CEngineGfxCanvas::isRegistered(CallbackFuncPtr pCallback,
                                      InternalCallbackType cbType) {
    if(!pCallback)
        return FG_FALSE;
    const unsigned int nTypes = NUM_ENGINE_CB_TYPES;
    int cbTypeMax = 0;
    int cbTypeIdx = 0;
    if(cbType == INVALID_CALLBACK) {
        cbTypeMax = nTypes - 1;
    } else {
        cbTypeMax = (int)cbType;
        cbTypeIdx = (int)cbType;
    }
    for(; cbTypeIdx <= cbTypeMax; cbTypeIdx++) {
        unsigned int n = m_onEngineCallbacks[cbTypeIdx].size();

        // Check for duplicates
        for(unsigned int i = 0; i < n; i++) {
            CallbackData &info = m_onEngineCallbacks[cbTypeIdx][i];
            if(info.callback == pCallback)
                return FG_TRUE;
        }
    }
    return FG_FALSE;
}
//------------------------------------------------------------------------------

void CEngineGfxCanvas::OnCloseEvent(wxCloseEvent& event) {
    //printf("CLOSE EVENT: THREAD ID: %lu\n", pthread_self());
    FG_LOG_DEBUG("WX: Close event callback");
    this->m_isExit = FG_TRUE;
    this->m_appInit = FG_FALSE;
    closeProgram();
}
//------------------------------------------------------------------------------

void CEngineGfxCanvas::OnMouseMoved(wxMouseEvent& event) {
    if(this->m_appInit && this->m_engineMain) {
        int button = event.GetButton();
        int x = event.GetPosition().x;
        int y = event.GetPosition().y;
        this->m_engineMain->getInputHandler()->handlePointerMoved(fg::Vector2i(x, y), FG_DEFAULT_POINTER_ID, event.Dragging());
        //printf("MOUSE MOVED: THREAD ID: %lu\n", pthread_self());
    }
}
//-----------------------------------------------------------------------------

void CEngineGfxCanvas::OnMouseDown(wxMouseEvent& event) {
    if(this->m_appInit && this->m_engineMain) {
        int button = event.GetButton();
        int x = event.GetPosition().x;
        int y = event.GetPosition().y;
        this->m_engineMain->getInputHandler()->handlePointerPressed(fg::Vector2i(x, y), button);
        FG_LOG_DEBUG("WX: Mouse down event: %dx%d id:%d", x, y, button);
    }
}
//-----------------------------------------------------------------------------

void CEngineGfxCanvas::OnMouseWheelMoved(wxMouseEvent& event) {
    if(this->m_appInit && this->m_engineMain) {
    }
}
//-----------------------------------------------------------------------------

void CEngineGfxCanvas::OnMouseReleased(wxMouseEvent& event) {
    if(this->m_appInit && this->m_engineMain) {
        int button = event.GetButton();
        int x = event.GetPosition().x;
        int y = event.GetPosition().y;
        this->m_engineMain->getInputHandler()->handlePointerReleased(fg::Vector2i(x, y), button);
        FG_LOG_DEBUG("WX: Mouse released event: %dx%d id:%d", x, y, button);
    }
}
//-----------------------------------------------------------------------------

void CEngineGfxCanvas::OnMouseLeftWindow(wxMouseEvent& event) {
    if(this->m_appInit && this->m_engineMain) {
        int button = event.GetButton();
        int x = event.GetPosition().x;
        int y = event.GetPosition().y;
        FG_LOG_DEBUG("WX: Mouse left window event: %dx%d id:%d", x, y, button);
    }
}
//-----------------------------------------------------------------------------

void CEngineGfxCanvas::OnKeyPressed(wxKeyEvent& event) {
    if(this->m_appInit && this->m_engineMain) {
        int keyCode = event.GetKeyCode();
        this->m_engineMain->getInputHandler()->addKeyDown(keyCode);
        FG_LOG_DEBUG("WX: Key pressed event: id:%d, char[%c]", keyCode, (char)keyCode);
    }
}
//-----------------------------------------------------------------------------

void CEngineGfxCanvas::OnKeyReleased(wxKeyEvent& event) {
    if(this->m_appInit && this->m_engineMain) {
        int keyCode = event.GetKeyCode();
        this->m_engineMain->getInputHandler()->addKeyUp(keyCode);
    }
}
//-----------------------------------------------------------------------------

void CEngineGfxCanvas::OnResized(wxSizeEvent& event) {
    int x = event.GetSize().x;
    int y = event.GetSize().y;
    FG_LOG_DEBUG("WX: Resize event %dx%d", x, y);
    m_screenSize.x = x;
    m_screenSize.y = y;
    if(m_appInit && m_engineMain) {
        m_engineMain->getGfxMain()->getMainWindow()->setup("FlexiGame::Editor", x, y);
        m_engineMain->getGuiMain()->setScreenSize(x, y);
        fg::gfx::context::setScreenSize(x, y);
    }
    Refresh();
}
//------------------------------------------------------------------------------

void CEngineGfxCanvas::OnIdle(wxIdleEvent& event) {
    static long int t1 = 0;
    static int f = 0;
    if(t1 == 0) {
        t1 = time(NULL);
    }
    if(m_isSuspend) return;
    if(!IsShown()) return;

    f++;
    if(time(NULL) != t1) {
        t1 = time(NULL);
        FG_LOG_DEBUG("WX: IDLE FPS: %d", f);
        //printf("IDLE: THREAD ID: %lu\n", pthread_self());
        f = 0;
    }
    if(m_paint && !m_appInit && !m_isInitializing && m_canInitialize) {
        m_isInitializing = FG_TRUE;
        fgBool status = this->initProgram();
        if(!status) {
            FG_LOG_ERROR("WX: Failed to initialize the program...");
            m_isExit = FG_TRUE;
            m_appInit = FG_FALSE;
            m_isInitializing = FG_FALSE;
            m_canInitialize = FG_FALSE;
            //m_parentFrame->Close();
        } else {
            m_isInitializing = FG_FALSE;
            m_canInitialize = FG_FALSE;
            m_appInit = FG_TRUE;
            // Unlock display/render FPS
            // Proper FPS still will be maintained thanks to
            // paint/refresh timer which is locked at 60FPS
            m_engineMain->lockFps(FG_FALSE);
            int x = this->getWidth();
            int y = this->getHeight();
            m_engineMain->getGfxMain()->getMainWindow()->setup("FlexiGame::Editor", x, y);
            m_engineMain->getGuiMain()->setScreenSize(x, y);
            fg::gfx::context::setScreenSize(x, y);
            FG_LOG_DEBUG("WX: Successfully initialized program...");
            this->Refresh(); // This will send the repaint signal
        }
    }

    if(m_appInit) {
        wxGLCanvas::SetCurrent(*m_context);
        if(!this->update()) {
            // loop break
            m_isExit = FG_TRUE; // ?
        }
    }
    if(m_isExit) {
        m_appInit = FG_FALSE;
        closeProgram();
    }
    usleep(1000 * 5);
    event.RequestMore();
}
//------------------------------------------------------------------------------

fgBool CEngineGfxCanvas::OnGfxWindowSwapBuffer(void* pSystemData, void *pUserData) {
    if(!pSystemData || !pUserData) {
        return FG_FALSE;
    }
    // this function is static
    // pSystemData will be the pointer to the Window object
    // pUserData will be the pointer to the CEngineGfxCanvas object
    CEngineGfxCanvas *gfxCanvas = static_cast<CEngineGfxCanvas*>(pUserData);

    if(!gfxCanvas->isInitialized()) {
        //wxClientDC(gfxCanvas);
        gfxCanvas->SetCurrent(*(gfxCanvas->m_context));
        wxClientDC dc(gfxCanvas);
        glFlush();
        gfxCanvas->SwapBuffers();
    } else {
        //gfxCanvas->getGameMain()->removeCallbacks(fg::event::SWAP_BUFFERS);
        gfxCanvas->getEngineMain()->deleteCallback(fg::event::SWAP_BUFFERS, gfxCanvas->getRefOnSwapCallback());
    }
    return FG_TRUE;
}

//------------------------------------------------------------------------------

void CEngineGfxCanvas::OnPaint(wxPaintEvent& event) {
    fgBool isSwapBuffers = FG_TRUE;
    static unsigned long int t1 = 0;
    unsigned long int t2 = 0;
    static int f = 0;
    if(t1 == 0) {
        t1 = (unsigned long int)fg::timesys::ms();
    }
    t2 = (unsigned long int)fg::timesys::ms();
    //printf("T2: %lu | clockTicks=%.2f | ms=%.2f | exact=%.2f | elapsed=%.2f\n", t2, fg::timesys::clockTicks(), fg::timesys::ms(), fg::timesys::exact(), fg::timesys::elapsed());
    f++;
    if(t2 - t1 > 1000) {
        float fps = ((float)f) / (1000.0f / (float)(t2 - t1));
        t1 = t2;
        FG_LOG_DEBUG("WX: Paint Event: FPS: %.1f", fps);
        f = 0;
    }

    if(m_isSuspend) return;
    if(!IsShown()) return;
    if(!IsShownOnScreen()) return;
    if(m_isExit) return;
    if(m_isInitializing) return;

    wxGLCanvas::SetCurrent(*m_context);

    // only to be used in paint events. use wxClientDC to paint outside the paint event
    wxPaintDC(this);
    m_paint = FG_TRUE;

    if(m_appInit) {
        // displayAndRender returns FG_FALSE if render func was not called (meaning no swap is required)
        if(!this->displayAndRender()) {
            // loop break
            isSwapBuffers = FG_FALSE;
        }
    } else {
        //FG_LOG_DEBUG("WX: Render func: app is not yet initialized");
    }
    if(isSwapBuffers) {
        glFlush();
        SwapBuffers();
    }
}
//------------------------------------------------------------------------------

void CEngineGfxCanvas::closeProgram(void) {
    // if(m_paint && m_context && IsShown()) {
    //    wxGLCanvas::SetCurrent(*m_context);
    //}
    executeCallbacks(ENGINE_DESTROYED);
    FG_LOG_DEBUG("Closing program...");
    if(m_engineMain) {
        m_engineMain->destroy();
        delete m_engineMain;
    }
    m_engineMain = NULL;
    *m_engineMainOrig = m_engineMain;
    m_appInit = FG_FALSE;
    m_isInitializing = FG_FALSE;
    m_canInitialize = FG_FALSE;
    m_isFrameFreeze = FG_FALSE;
    m_isExit = FG_FALSE;
#if defined(FG_DEBUG)
    if(fg::profile::g_debugProfiling)
        delete fg::profile::g_debugProfiling;
    fg::profile::g_debugProfiling = NULL;
#endif
}
//------------------------------------------------------------------------------

fgBool CEngineGfxCanvas::initProgram(void) {
    using namespace fg;
    if(m_paint && m_context) {
        wxGLCanvas::SetCurrent(*m_context);
    }
    timesys::init(); // #FIXME global time init?
#if defined(FG_DEBUG)
    profile::g_debugProfiling = new profile::CProfiling();
    profile::g_debugProfiling->initialize();
#endif
    float t1 = timesys::ms();
    FG_LOG_DEBUG("Init program main...");
    if(this->m_appInit) {
        // already initialized
        return FG_TRUE;
    }

    if(!this->m_engineMain) {
        FG_LOG_DEBUG("Creating game main object...");
        m_engineMain = new fg::CEngineMain(this->m_argc, this->m_argv);
        *m_engineMainOrig = m_engineMain;
    }
    this->m_engineMain->addCallback(fg::event::SWAP_BUFFERS, m_onSwapCallback);
    // Well the whole configuration process should update the screen (swap buffers)
    // this is needed to display splash screen (after marmalade splash screen) and
    // show the game initialization process by displaying the progress bar
    if(!this->m_engineMain->loadConfiguration()) {
        return FG_FALSE;
    }
    m_engineMain->getMainConfig()->setParameterInt("MainConfig.hardware", "screenWidth", m_screenSize.x);
    m_engineMain->getMainConfig()->setParameterInt("MainConfig.hardware", "screenHeight", m_screenSize.y);

    // Initialize the main subsystems (gui, gfx and others)
    if(!this->m_engineMain->initialize()) {
        return FG_FALSE;
    }
    // Preload any required resources
    if(!this->m_engineMain->loadResources()) {
        return FG_FALSE;
    }
    this->m_engineMain->update(FG_TRUE);
    this->m_engineMain->update(FG_TRUE);
    m_appInit = FG_TRUE;
    float t2 = timesys::ms();
    FG_LOG_DEBUG("Main: Program initialized in %.2f seconds", (t2 - t1) / 1000.0f);

    executeCallbacks(ENGINE_INITIALIZED);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool CEngineGfxCanvas::displayAndRender(void) {
    fgBool status = FG_TRUE;
    if(m_isSuspend) return FG_FALSE;
    using namespace fg;
#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->begin("Game::display");
    }
#endif
    if(!m_isFrameFreeze) {
        // well for now drawing and all update functions will be called in one place (one thread)
        // however it needs changing
        this->m_engineMain->display();
    }
#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("Game::display");
        profile::g_debugProfiling->begin("Game::render");
    }
#endif
    status = this->m_engineMain->render();
#if defined(FG_DEBUG)
    static int loopCount = 0;
    g_DebugConfig.isDebugProfiling = true;
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("Game::render");
        profile::g_debugProfiling->updateHistory();

        loopCount++;
        if(loopCount > 20) {
            loopCount = 0;
            profile::g_debugProfiling->dumpToDefaultFile();
        }
    }
#endif
    return status;
}
//------------------------------------------------------------------------------

fgBool CEngineGfxCanvas::update(void) {
    if(!m_appInit) {
        FG_LOG_DEBUG("MainModule: Loop step - application not initialized...");
        return FG_FALSE;
    }
    if(m_isSuspend) {
        //FG_LOG_DEBUG("MainModule: Loop step - suspend...");
        return FG_TRUE;
    }
    if(m_isExit) {
        m_appInit = FG_FALSE;
        FG_LOG_DEBUG("EXIT IS ACTIVATED - break loop main ! bye!");
        return FG_FALSE;
    }
    using namespace fg;
#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->begin("Game::update");
    }
#endif
    m_engineMain->update();
#if defined(FG_DEBUG)
    if(g_DebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("Game::update");
    }
#endif
    return FG_TRUE;
}
//------------------------------------------------------------------------------
