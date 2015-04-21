/***************************************************************
 * Name:      FlexiGameEditorApp.h
 * Purpose:   Defines Application Class
 * Author:    Radoslaw Gniazdowski (contact@flexigame.com)
 * Created:   2015-04-21
 * Copyright: Radoslaw Gniazdowski (http://flexigame.com)
 * License:
 **************************************************************/

#ifndef FLEXIGAMEEDITORAPP_H
#define FLEXIGAMEEDITORAPP_H
#include "GFX/fgGfxGL.h"
#include "fgGameMain.h"
#include <wx/app.h>

class BasicGLPane;
class RenderTimer;
class FlexiGameEditorApp : public wxApp
{
public:
    virtual bool OnInit();

private:
    BasicGLPane* glPane;
    RenderTimer* m_renderTimer;
};

#ifndef _glpane_
#define _glpane_

#include "wx/wx.h"
#include "wx/glcanvas.h"

typedef unsigned char fgBool;
#define FG_TRUE 1
#define FG_FALSE 0
#define FG_ZERO 0

class RenderTimer : public wxTimer
{
    BasicGLPane* m_glPane;
public:

    RenderTimer(BasicGLPane* pane);
    void Notify();
    void start();
};



class BasicGLPane : public wxGLCanvas
{
    wxGLContext*	m_context;
    fgBool m_paint;
    fgBool m_appInit;
    fgBool m_isInitializing;
    /// Is exit activated?
    fgBool m_isExit;
    fgBool m_isSuspend;
    /// Game main class - this is for initialization procedures
    /// contains also functions for handling events, drawing, etc #TODO
    /// Needs refactoring, some level of merging within main module or
    /// changing name to fgApplication - or extending fgApplication class
    /// #TODO - support threads
    fg::CGameMain *m_gameMain;
    wxFrame* m_parentFrame;
    int m_argc;
    char *m_argv[2];

public:
    BasicGLPane(wxFrame* parent, int* args);
    virtual ~BasicGLPane();

    void closeProgram(void);
    fgBool mainLoopStep(void);
    fgBool initProgram(void);


    void resized(wxSizeEvent& evt);

    int getWidth();
    int getHeight();

    void idle(wxIdleEvent& evt);
    void render(void);
    void paint(wxPaintEvent& evt);

    // events
    void mouseMoved(wxMouseEvent& event);
    void mouseDown(wxMouseEvent& event);
    void mouseWheelMoved(wxMouseEvent& event);
    void mouseReleased(wxMouseEvent& event);
    void rightClick(wxMouseEvent& event);
    void mouseLeftWindow(wxMouseEvent& event);
    void keyPressed(wxKeyEvent& event);
    void keyReleased(wxKeyEvent& event);
    void closeEvent(wxCloseEvent& event);

    DECLARE_EVENT_TABLE()
};


#endif


#endif // FLEXIGAMEEDITORAPP_H
