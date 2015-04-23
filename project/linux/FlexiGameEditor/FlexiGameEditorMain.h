/***************************************************************
 * Name:      FlexiGameEditorMain.h
 * Purpose:   Defines Application Frame
 * Author:    Radoslaw Gniazdowski (contact@flexigame.com)
 * Created:   2015-04-21
 * Copyright: Radoslaw Gniazdowski (http://flexigame.com)
 * License:
 **************************************************************/

#ifndef FLEXIGAMEEDITORMAIN_H
#define FLEXIGAMEEDITORMAIN_H

//(*Headers(FlexiGameEditorFrame)
#include <wx/sizer.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
//*)

#include "CEngineGFXPanel.h"

class FlexiGameEditorFrame: public wxFrame
{
    public:

        FlexiGameEditorFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~FlexiGameEditorFrame();

    private:
        CEngineGFXPanel* m_gfxPanel;
        CRenderTimer* m_renderTimer;

    private:

        //(*Handlers(FlexiGameEditorFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnMenuEngineInitialize(wxCommandEvent& event);
        void OnMenuEngineFreezeFrame(wxCommandEvent& event);
        void OnMenuEngineQuit(wxCommandEvent& event);
        //*)

        //(*Identifiers(FlexiGameEditorFrame)
        static const long idMenuQuit;
        static const long idMenuEngineInitialize;
        static const long idMenuEngineQuit;
        static const long idMenuEngineFreezeFrame;
        static const long idMenuToolsOptions;
        static const long idMenuGitRunGitGUI;
        static const long idMenuGitRunGitk;
        static const long idMenuGitShowLog;
        static const long idMenuGitOpenGitconfig;
        static const long idMenuHelpLocalDocs;
        static const long idMenuHelpAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(FlexiGameEditorFrame)
        wxMenu* Menu5;
        wxStatusBar* StatusBar1;
        wxMenu* Menu3;
        wxMenuItem* MenuItem3;
        wxMenuItem* MenuItem9;
        wxMenu* Menu4;
        wxMenuItem* MenuItem11;
        wxMenuItem* MenuItem5;
        wxMenuItem* MenuItem10;
        wxMenuItem* MenuItem7;
        wxMenuItem* MenuItem6;
        wxMenuItem* MenuItem4;
        wxMenuItem* MenuItem8;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // FLEXIGAMEEDITORMAIN_H
