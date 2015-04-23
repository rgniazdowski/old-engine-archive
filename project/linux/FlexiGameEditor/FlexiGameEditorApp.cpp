/***************************************************************
 * Name:      FlexiGameEditorApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Radoslaw Gniazdowski (contact@flexigame.com)
 * Created:   2015-04-21
 * Copyright: Radoslaw Gniazdowski (http://flexigame.com)
 * License:
 **************************************************************/

#include "FlexiGameEditorApp.h"

#include <pthread.h>

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

            //wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
            //int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
            //glPane = new CEngineGFXPanel( (wxFrame*) Frame, args);
            //sizer->Add(glPane, 1, wxEXPAND);
            //Frame->SetSizer(sizer);
            //Frame->GetSizer()->Add(glPane, 1, wxEXPAND);
            Frame->SetAutoLayout(true);

            //this->m_renderTimer = new CRenderTimer(glPane);
            Frame->Show();
            SetTopWindow(Frame);
            //this->m_renderTimer->start();
        }
        returnVal = wxsOK;
    }
    //printf("FlexiGameEditorApp::OnInit(): THREAD ID: %lu\n", pthread_self());
    return returnVal;

}
