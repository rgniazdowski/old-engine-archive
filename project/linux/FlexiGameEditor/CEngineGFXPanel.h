/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_ENGINE_GFX_PANEL
#define FG_INC_ENGINE_GFX_PANEL

#include "fgBuildConfig.h"
#include "fgBool.h"
#include "GFX/fgGfxGL.h"
#include "fgGameMain.h"

#include "wx/wx.h"
#include "wx/glcanvas.h"

class CRenderTimer;
class CEngineGFXPanel;

/**
 *
 */
class CRenderTimer : public wxTimer
{
private:
    ///
    CEngineGFXPanel* m_gfxPanel;

public:
    /**
     *
     */
    CRenderTimer(CEngineGFXPanel* gfxPanel);

    /**
     *
     */
    void Notify(void);
    /**
     *
     */
    void start(void);
};


/**
 *
 */
class CEngineGFXPanel : public wxGLCanvas
{
    ///
    wxGLContext*	m_context;
    ///
    fgBool m_paint;
    ///
    fgBool m_appInit;
    ///
    fgBool m_isInitializing;
    /// Is exit activated?
    fgBool m_isExit;
    ///
    fgBool m_isSuspend;
    ///
    fgBool m_canInitialize;
    ///
    fgBool m_isFrameFreeze;
    /// Game main class - this is for initialization procedures
    /// contains also functions for handling events, drawing, etc #TODO
    /// Needs refactoring, some level of merging within main module or
    /// changing name to fgApplication - or extending fgApplication class
    /// #TODO - support threads
    fg::CGameMain *m_gameMain;
    ///
    wxFrame* m_parentFrame;
    ///
    int m_argc;
    ///
    char *m_argv[2];

public:

    CEngineGFXPanel(wxFrame* parent, int* args);
    virtual ~CEngineGFXPanel();

    fgBool initProgram(void);
    void closeProgram(void);

    fgBool displayAndRender(void);
    fgBool update(void);

    void paint(wxPaintEvent& evt);

    void mouseMoved(wxMouseEvent& event);
    void mouseDown(wxMouseEvent& event);
    void mouseWheelMoved(wxMouseEvent& event);
    void mouseReleased(wxMouseEvent& event);
    void mouseLeftWindow(wxMouseEvent& event);
    void keyPressed(wxKeyEvent& event);
    void keyReleased(wxKeyEvent& event);
    void closeEvent(wxCloseEvent& event);

    void idle(wxIdleEvent& evt);
    void resized(wxSizeEvent& evt);

    inline int getWidth(void) {
        return GetSize().x;
    }

    inline int getHeight(void) {
        return GetSize().y;
    }

    inline fg::CGameMain* getGameMain(void) const {
        return m_gameMain;
    }

    inline fgBool isSuspend(void) const {
        return m_isSuspend;
    }

    inline fgBool isExit(void) const {
        return m_isExit;
    }

    inline fgBool isPaintReady(void) const {
        return m_paint;
    }

    inline fgBool isInitialized(void) const {
        return m_appInit;
    }

    inline fgBool canInitialize(void) const {
        return m_canInitialize;
    }

    inline fgBool isFrameFreeze(void) const {
        return m_isFrameFreeze;
    }

    inline void setExit(fgBool toggle = FG_TRUE) {
        m_isExit = toggle;
    }

    inline void setInitializeFlag(fgBool toggle = FG_TRUE) {
        m_canInitialize = toggle;
    }

    inline void setFrameFreeze(fgBool toggle = FG_TRUE) {
        m_isFrameFreeze = toggle;
    }

    DECLARE_EVENT_TABLE()
};


#endif /* FG_INC_ENGINE_GFX_PANEL */
