/***************************************************************
 * Name:      FlexiGameEditorApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Radoslaw Gniazdowski (contact@flexigame.com)
 * Created:   2015-04-21
 * Copyright: Radoslaw Gniazdowski (http://flexigame.com)
 * License:
 **************************************************************/

#include "FlexiGameEditorApp.h"

#include "fgBuildConfig.h"
#include "fgCommon.h"
#include "fgGameMain.h"

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



//(*AppHeaders
#include "FlexiGameEditorMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(FlexiGameEditorApp);

bool FlexiGameEditorApp::OnInit()
{
    bool returnVal = true;
    if(false)
    {
        //(*AppInitialize
        bool wxsOK = true;
        wxInitAllImageHandlers();
        if ( wxsOK )
        {
        	FlexiGameEditorFrame* Frame = new FlexiGameEditorFrame(0);
        	Frame->Show();
        	SetTopWindow(Frame);
        }
        //*)
    }
    else
    {
        bool wxsOK = true;
        wxInitAllImageHandlers();
        if ( wxsOK )
        {
            FlexiGameEditorFrame* Frame = new FlexiGameEditorFrame(0);

            wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
            int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
            glPane = new BasicGLPane( (wxFrame*) Frame, args);
            sizer->Add(glPane, 1, wxEXPAND);
            Frame->SetSizer(sizer);
            Frame->SetAutoLayout(true);

            this->m_renderTimer = new RenderTimer(glPane);
            Frame->Show();
            SetTopWindow(Frame);
            this->m_renderTimer->start();
        }
        returnVal = wxsOK;
    }
    return returnVal;

}

//////////////////////////////////

RenderTimer::RenderTimer(BasicGLPane* pane) : wxTimer()
{
    m_glPane = pane;
}

void RenderTimer::Notify()
{
    m_glPane->render();
}

void RenderTimer::start()
{
    wxTimer::Start(1000/60);
}


BEGIN_EVENT_TABLE(BasicGLPane, wxGLCanvas)
    EVT_MOTION(BasicGLPane::mouseMoved)
    EVT_LEFT_DOWN(BasicGLPane::mouseDown)
    EVT_LEFT_UP(BasicGLPane::mouseReleased)
    EVT_RIGHT_DOWN(BasicGLPane::rightClick)
    EVT_LEAVE_WINDOW(BasicGLPane::mouseLeftWindow)
    EVT_SIZE(BasicGLPane::resized)
    EVT_KEY_DOWN(BasicGLPane::keyPressed)
    EVT_KEY_UP(BasicGLPane::keyReleased)
    EVT_MOUSEWHEEL(BasicGLPane::mouseWheelMoved)
    EVT_PAINT(BasicGLPane::paint)
    EVT_IDLE(BasicGLPane::idle)
    EVT_CLOSE(BasicGLPane::closeEvent)
END_EVENT_TABLE()


void BasicGLPane::closeEvent(wxCloseEvent& event) {
    FG_LOG_DEBUG("WX: Close event callback");
    this->m_isExit = FG_TRUE;
    closeProgram();
}

// some useful events to use
void BasicGLPane::mouseMoved(wxMouseEvent& event) {
    int button = event.GetButton();
    int x = event.GetPosition().x;
    int y = event.GetPosition().y;
    this->m_gameMain->getInputHandler()->handlePointerMoved(fg::Vector2i(x,y), FG_DEFAULT_POINTER_ID, event.Dragging());
}

void BasicGLPane::mouseDown(wxMouseEvent& event) {
    int button = event.GetButton();
    int x = event.GetPosition().x;
    int y = event.GetPosition().y;
    this->m_gameMain->getInputHandler()->handlePointerPressed(fg::Vector2i(x,y), button);
    FG_LOG_DEBUG("WX: Mouse down event: %dx%d id:%d", x, y, button);
}

void BasicGLPane::mouseWheelMoved(wxMouseEvent& event) {
}

void BasicGLPane::mouseReleased(wxMouseEvent& event) {
    int button = event.GetButton();
    int x = event.GetPosition().x;
    int y = event.GetPosition().y;
    this->m_gameMain->getInputHandler()->handlePointerReleased(fg::Vector2i(x,y), button);
    FG_LOG_DEBUG("WX: Mouse released event: %dx%d id:%d", x, y, button);
}

void BasicGLPane::rightClick(wxMouseEvent& event) {
}

void BasicGLPane::mouseLeftWindow(wxMouseEvent& event) {
}

void BasicGLPane::keyPressed(wxKeyEvent& event) {
    int keyCode = event.GetKeyCode();
    this->m_gameMain->getInputHandler()->addKeyDown(keyCode);
    FG_LOG_DEBUG("WX: Key pressed event: id:%d, char[%c]", keyCode, (char)keyCode);
}

void BasicGLPane::keyReleased(wxKeyEvent& event) {
    int keyCode = event.GetKeyCode();
    this->m_gameMain->getInputHandler()->addKeyUp(keyCode);

}


void BasicGLPane::idle(wxIdleEvent& event)
{
    static int i = 0;
    static unsigned long t1 = 0;
    static int f = 0;
    if(t1 == 0)
    {
        t1 = time(NULL);
    }
    if(!m_paint)
        printf("idle() shown: %d | i: %d\n", IsShownOnScreen(), i);
    if(!IsShown())
        return;
    event.RequestMore();
    i++;
    f++;
    if(time(NULL) != t1)
    {
        t1 = time(NULL);
        printf("FPS: %d\n", f);
        f = 0;
    }
    if(m_paint && !m_appInit && !m_isInitializing) {
        m_isInitializing = FG_TRUE;
        fgBool status = this->initProgram();
        if(!status) {
            FG_LOG_ERROR("WX: Failed to initialize the program...");
            m_isExit = FG_TRUE;
            m_appInit = FG_FALSE;
            m_parentFrame->Close();
        } else {
            m_isInitializing = FG_FALSE;
            m_appInit = FG_TRUE;
            FG_LOG_DEBUG("WX: Successfully initialized program...");
        }
    }
}
void BasicGLPane::paint( wxPaintEvent& evt )
{
    if(!IsShownOnScreen()) return;
    wxGLCanvas::SetCurrent(*m_context);
    wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event
    m_paint = FG_TRUE;
    render();
    FG_LOG_DEBUG("WX: Paint event...");
}


// Vertices and faces of a simple cube to demonstrate 3D render
// source: http://www.opengl.org/resources/code/samples/glut_examples/examples/cube.c
GLfloat v[8][3];
GLint faces[6][4] =    /* Vertex indices for the 6 faces of a cube. */
{
    {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
    {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3}
};

#include "GFX/Scene/fgGfxBspCompiler.h"
fg::gfx::CBspCompiler *bspCompiler = NULL;

BasicGLPane::BasicGLPane(wxFrame* parent, int* args) :
    wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
    m_context = new wxGLContext(this);
    // prepare a simple cube to demonstrate 3D render
    // source: http://www.opengl.org/resources/code/samples/glut_examples/examples/cube.c
    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;

    // To avoid flashing on MSW
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);

    m_paint = FG_FALSE;
    m_isExit = FG_FALSE;
    m_appInit = FG_FALSE;
    m_isSuspend = FG_FALSE;
    m_gameMain = NULL;
    m_argc = 0;
    m_argv[0] = NULL;
    m_argv[1] = NULL;
    m_parentFrame = parent;
    m_isInitializing = FG_FALSE;
}

BasicGLPane::~BasicGLPane()
{
    FG_LOG_DEBUG("WX: Main destructor called");
    closeProgram();
    delete m_context;
}

void BasicGLPane::closeProgram(void)
{
    FG_LOG_DEBUG("Closing program...");
    if(this->m_gameMain) {
        this->m_gameMain->closeSybsystems();
        delete this->m_gameMain;
    }
    this->m_gameMain = NULL;
    this->m_appInit = FG_FALSE;
#if defined(FG_DEBUG)
    if(fg::profile::g_debugProfiling)
        delete fg::profile::g_debugProfiling;
    fg::profile::g_debugProfiling = NULL;
#endif
}

fgBool BasicGLPane::initProgram(void)
{
    using namespace fg;
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
    this->m_gameMain->update();
    m_appInit = FG_TRUE;
    float t2 = timesys::ms();
    FG_LOG_DEBUG("Main: Program initialized in %.2f seconds", (t2 - t1) / 1000.0f);
    return FG_TRUE;
}

fgBool BasicGLPane::mainLoopStep(void)
{
    using namespace fg;
    FG_HardwareState->deviceYield(0);
    if(!this->m_appInit) {
        FG_LOG_DEBUG("MainModule: Loop step - application not initialized...");
        return FG_FALSE;
    }
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->begin("Program::loopStep");
    }
#endif
    // #FIXME - This event checking should not be in here

    if(this->m_isSuspend) {
        //FG_LOG_DEBUG("MainModule: Loop step - suspend...");
        return FG_TRUE;
    }

    if(this->m_isExit) {
        this->m_appInit = FG_FALSE;
        FG_LOG_DEBUG("EXIT IS ACTIVATED - break loop main ! bye!");
        return FG_FALSE;
    }

#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->begin("Game::update");
    }
#endif
    FG_HardwareState->deviceYield(0);
    this->m_gameMain->update();
    FG_HardwareState->deviceYield(0);
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("Game::update");
        profile::g_debugProfiling->begin("Game::display");
    }
#endif
    // well for now drawing and all update functions will be called in one place (one thread)
    // however it needs changing
    this->m_gameMain->display();
    FG_HardwareState->deviceYield(0);
#if defined(FG_DEBUG)
    if(g_fgDebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("Game::display");
        profile::g_debugProfiling->begin("Game::render");
    }
#endif
    FG_HardwareState->deviceYield();
    this->m_gameMain->render();
    FG_HardwareState->deviceYield(0);
#if defined(FG_DEBUG)
    static int loopCount = 0;
    g_fgDebugConfig.isDebugProfiling = true;
    if(g_fgDebugConfig.isDebugProfiling) {
        profile::g_debugProfiling->end("Game::render");
        profile::g_debugProfiling->end("Program::loopStep");
        profile::g_debugProfiling->updateHistory();

        loopCount++;
        if(loopCount > 20) {
            loopCount = 0;
            profile::g_debugProfiling->dumpToDefaultFile();
        }
    }
#endif
    return FG_TRUE;
}

void BasicGLPane::resized(wxSizeEvent& evt)
{
//	wxGLCanvas::OnSize(evt);

    int x = evt.GetSize().x;
    int y = evt.GetSize().y;
    FG_LOG_DEBUG("WX: Resize event %dx%d", x, y);
    if(this->m_appInit)
    {
        this->m_gameMain->getGfxMain()->getMainWindow()->setup("BasicGLPane", x, y);
        this->m_gameMain->getGuiMain()->setScreenSize(x, y);
        fg::gfx::context::setScreenSize(x, y);

    }
    Refresh();
}

int BasicGLPane::getWidth()
{
    return GetSize().x;
}

int BasicGLPane::getHeight()
{
    return GetSize().y;
}


void BasicGLPane::render(void)
{
    if(!IsShown()) return;
    if(!IsShownOnScreen()) return;
    if(!m_paint) return;
    if(m_isExit) return;
    if(m_isInitializing) return;
    wxGLCanvas::SetCurrent(*m_context);
    if(m_appInit) {
        if(!this->mainLoopStep()) {
            // loop break
            m_isExit = FG_TRUE; // ?
        }
    } else {
        FG_LOG_DEBUG("WX: Render func: app is not yet initialized");
    }

    glFlush();
    SwapBuffers();
}
