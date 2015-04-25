/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "CEngineGfxPanel.h"

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <map>

#include "Event/fgEventManager.h"
#include "Event/fgInputHandler.h"
#include "Hardware/fgHardwareState.h"
#include "Util/fgProfiling.h"
#include "Util/fgStrings.h"
#include "fgDebugConfig.h"
#include "fgLog.h"

//-----------------------------------------------------------------------------

CRenderTimer::CRenderTimer(CEngineGfxPanel* gfxPanel) : wxTimer() {
    m_gfxPanel = gfxPanel;
}
//-----------------------------------------------------------------------------

void CRenderTimer::Notify(void) {
    m_gfxPanel->Refresh();
    //printf("RenderTime::Notify(): THREAD ID: %lu\n", pthread_self());
}
//-----------------------------------------------------------------------------

void CRenderTimer::Start(void) {
    //printf("RenderTime::start(): THREAD ID: %lu\n", pthread_self());
    wxTimer::Start(1000 / 60); // #FIXME / this should be exactly 120 ?
}
//-----------------------------------------------------------------------------

BEGIN_EVENT_TABLE(CEngineGfxPanel, wxGLCanvas)
EVT_MOTION(CEngineGfxPanel::mouseMoved)
EVT_LEFT_DOWN(CEngineGfxPanel::mouseDown)
EVT_LEFT_UP(CEngineGfxPanel::mouseReleased)
EVT_LEAVE_WINDOW(CEngineGfxPanel::mouseLeftWindow)
EVT_SIZE(CEngineGfxPanel::resized)
EVT_KEY_DOWN(CEngineGfxPanel::keyPressed)
EVT_KEY_UP(CEngineGfxPanel::keyReleased)
EVT_MOUSEWHEEL(CEngineGfxPanel::mouseWheelMoved)
EVT_PAINT(CEngineGfxPanel::paint)
EVT_IDLE(CEngineGfxPanel::idle)
EVT_CLOSE(CEngineGfxPanel::closeEvent)
END_EVENT_TABLE()

#include "GFX/Scene/fgGfxBspCompiler.h"
fg::gfx::CBspCompiler *bspCompiler = NULL;

//-----------------------------------------------------------------------------

CEngineGfxPanel::CEngineGfxPanel(wxWindow* parent, int* args) :
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

    m_parentFrame = parent;
    m_gameMain = NULL;
}
//-----------------------------------------------------------------------------

CEngineGfxPanel::~CEngineGfxPanel() {
    FG_LOG_DEBUG("WX: Main destructor called");
    //if(m_context && IsShown())
    //    wxGLCanvas::SetCurrent(*m_context);
    closeProgram();
    delete m_context;
    m_context = NULL;
}
//-----------------------------------------------------------------------------

void CEngineGfxPanel::closeEvent(wxCloseEvent& event) {
    //printf("CLOSE EVENT: THREAD ID: %lu\n", pthread_self());
    FG_LOG_DEBUG("WX: Close event callback");
    this->m_isExit = FG_TRUE;
    this->m_appInit = FG_FALSE;
    closeProgram();
}
//-----------------------------------------------------------------------------

void CEngineGfxPanel::mouseMoved(wxMouseEvent& event) {
    if(this->m_appInit && this->m_gameMain) {
        int button = event.GetButton();
        int x = event.GetPosition().x;
        int y = event.GetPosition().y;
        this->m_gameMain->getInputHandler()->handlePointerMoved(fg::Vector2i(x, y), FG_DEFAULT_POINTER_ID, event.Dragging());
        //printf("MOUSE MOVED: THREAD ID: %lu\n", pthread_self());
    }
}
//-----------------------------------------------------------------------------

void CEngineGfxPanel::mouseDown(wxMouseEvent& event) {
    if(this->m_appInit && this->m_gameMain) {
        int button = event.GetButton();
        int x = event.GetPosition().x;
        int y = event.GetPosition().y;
        this->m_gameMain->getInputHandler()->handlePointerPressed(fg::Vector2i(x, y), button);
        FG_LOG_DEBUG("WX: Mouse down event: %dx%d id:%d", x, y, button);
    }
}
//-----------------------------------------------------------------------------

void CEngineGfxPanel::mouseWheelMoved(wxMouseEvent& event) {
    if(this->m_appInit && this->m_gameMain) {
    }
}
//-----------------------------------------------------------------------------

void CEngineGfxPanel::mouseReleased(wxMouseEvent& event) {
    if(this->m_appInit && this->m_gameMain) {
        int button = event.GetButton();
        int x = event.GetPosition().x;
        int y = event.GetPosition().y;
        this->m_gameMain->getInputHandler()->handlePointerReleased(fg::Vector2i(x, y), button);
        FG_LOG_DEBUG("WX: Mouse released event: %dx%d id:%d", x, y, button);
    }
}
//-----------------------------------------------------------------------------

void CEngineGfxPanel::mouseLeftWindow(wxMouseEvent& event) {
    if(this->m_appInit && this->m_gameMain) {
        int button = event.GetButton();
        int x = event.GetPosition().x;
        int y = event.GetPosition().y;
        FG_LOG_DEBUG("WX: Mouse left window event: %dx%d id:%d", x, y, button);
    }
}
//-----------------------------------------------------------------------------

void CEngineGfxPanel::keyPressed(wxKeyEvent& event) {
    if(this->m_appInit && this->m_gameMain) {
        int keyCode = event.GetKeyCode();
        this->m_gameMain->getInputHandler()->addKeyDown(keyCode);
        FG_LOG_DEBUG("WX: Key pressed event: id:%d, char[%c]", keyCode, (char)keyCode);
    }
}
//-----------------------------------------------------------------------------

void CEngineGfxPanel::keyReleased(wxKeyEvent& event) {
    if(this->m_appInit && this->m_gameMain) {
        int keyCode = event.GetKeyCode();
        this->m_gameMain->getInputHandler()->addKeyUp(keyCode);
    }
}
//-----------------------------------------------------------------------------

void CEngineGfxPanel::resized(wxSizeEvent& event) {
    int x = event.GetSize().x;
    int y = event.GetSize().y;
    FG_LOG_DEBUG("WX: Resize event %dx%d", x, y);
    if(this->m_appInit && this->m_gameMain) {
        this->m_gameMain->getGfxMain()->getMainWindow()->setup("FlexiGame::Editor", x, y);
        this->m_gameMain->getGuiMain()->setScreenSize(x, y);
        fg::gfx::context::setScreenSize(x, y);

    }
    Refresh();
}
//-----------------------------------------------------------------------------

void CEngineGfxPanel::idle(wxIdleEvent& event) {
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
            m_gameMain->lockFps(FG_FALSE);
            int x = this->getWidth();
            int y = this->getHeight();
            m_gameMain->getGfxMain()->getMainWindow()->setup("FlexiGame::Editor", x, y);
            m_gameMain->getGuiMain()->setScreenSize(x, y);
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
    event.RequestMore();
}
//-----------------------------------------------------------------------------

void CEngineGfxPanel::paint(wxPaintEvent& event) {
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
//-----------------------------------------------------------------------------

void CEngineGfxPanel::closeProgram(void) {
    // if(m_paint && m_context && IsShown()) {
    //    wxGLCanvas::SetCurrent(*m_context);
    //}
    FG_LOG_DEBUG("Closing program...");
    if(this->m_gameMain) {
        this->m_gameMain->closeSybsystems();
        delete this->m_gameMain;
    }
    this->m_gameMain = NULL;
    this->m_appInit = FG_FALSE;
    this->m_isInitializing = FG_FALSE;
    this->m_canInitialize = FG_FALSE;
    this->m_isFrameFreeze = FG_FALSE;
    this->m_isExit = FG_FALSE;
#if defined(FG_DEBUG)
    if(fg::profile::g_debugProfiling)
        delete fg::profile::g_debugProfiling;
    fg::profile::g_debugProfiling = NULL;
#endif
}
//-----------------------------------------------------------------------------

fgBool CEngineGfxPanel::initProgram(void) {
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

    if(!this->m_gameMain) {
        FG_LOG_DEBUG("Creating game main object...");
        this->m_gameMain = new fg::CGameMain(this->m_argc, this->m_argv);
    }
    // Well the whole configuration process should update the screen (swap buffers)
    // this is needed to display splash screen (after marmalade splash screen) and
    // show the game initialization process by displaying the progress bar
    if(!this->m_gameMain->loadConfiguration()) {
        return FG_FALSE;
    }
    // Initialize the main subsystems (gui, gfx and others)
    if(!this->m_gameMain->initSubsystems()) {
        return FG_FALSE;
    }
    // Preload any required resources
    if(!this->m_gameMain->loadResources()) {
        return FG_FALSE;
    }
    this->m_gameMain->update(FG_TRUE);
    this->m_gameMain->update(FG_TRUE);
    m_appInit = FG_TRUE;
    float t2 = timesys::ms();
    FG_LOG_DEBUG("Main: Program initialized in %.2f seconds", (t2 - t1) / 1000.0f);
    return FG_TRUE;
}
//-----------------------------------------------------------------------------

fgBool CEngineGfxPanel::displayAndRender(void) {
    fgBool status = FG_TRUE;
    if(m_isSuspend) return FG_FALSE;
    using namespace fg;
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->begin("Game::display");
    }
#endif
    if(!m_isFrameFreeze) {
        // well for now drawing and all update functions will be called in one place (one thread)
        // however it needs changing
        this->m_gameMain->display();
    }
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("Game::display");
        profile::g_debugProfiling->begin("Game::render");
    }
#endif
    status = this->m_gameMain->render();
#if defined(FG_DEBUG)
    static int loopCount = 0;
    g_fgDebugConfig.isDebugProfiling = true;
    if(g_fgDebugConfig.isDebugProfiling) {
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
//-----------------------------------------------------------------------------

fgBool CEngineGfxPanel::update(void) {
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
    if(g_fgDebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->begin("Game::update");
    }
#endif
    m_gameMain->update();
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("Game::update");
    }
#endif
    return FG_TRUE;
}
