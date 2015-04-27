/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
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

//-----------------------------------------------------------------------------

//(*AppHeaders
#include "FlexiGameEditorMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(FlexiGameEditorApp);
//-----------------------------------------------------------------------------

bool FlexiGameEditorApp::OnInit() {
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
        }
        returnVal = wxsOK;
    }
    //printf("FlexiGameEditorApp::OnInit(): THREAD ID: %lu\n", pthread_self());
    return returnVal;

}
//-----------------------------------------------------------------------------
