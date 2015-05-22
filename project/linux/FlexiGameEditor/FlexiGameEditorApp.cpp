/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgLog.h"

#include "FlexiGameEditorApp.h"

//-----------------------------------------------------------------------------

//(*AppHeaders
#include "FlexiGameEditorMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(FlexiGameEditorApp);
//------------------------------------------------------------------------------

bool FlexiGameEditorApp::OnInit() {
    m_mainFrame = NULL;
    bool returnVal = true;
    if(false) {
        //(*AppInitialize
        bool wxsOK = true;
        wxInitAllImageHandlers();
        if(wxsOK) {
            FlexiGameEditorFrame* Frame = new FlexiGameEditorFrame(0);
            Frame->Show();
            SetTopWindow(Frame);
        }
        //*)
    } else {
        bool wxsOK = true;
        wxInitAllImageHandlers();
        if(wxsOK) {
            FlexiGameEditorFrame* Frame = new FlexiGameEditorFrame(0);
            Frame->SetAutoLayout(true);
            Frame->Show();
            SetTopWindow(Frame);
            m_mainFrame = Frame;
        }
        returnVal = wxsOK;
    }
    //printf("FlexiGameEditorApp::OnInit(): THREAD ID: %lu\n", pthread_self());
    return returnVal;

}
//------------------------------------------------------------------------------

int FlexiGameEditorApp::OnExit(void) {
    m_mainFrame = NULL;
    FG_LOG_DEBUG("WX: FlexiGame::Editor closing...");
    return base_type::OnExit();
}
//------------------------------------------------------------------------------

int FlexiGameEditorApp::FilterEvent(wxEvent& event) {
    if(m_mainFrame) {
        return m_mainFrame->FilterEvent(event);
    }
    return wxEventFilter::Event_Skip;
}
//------------------------------------------------------------------------------
