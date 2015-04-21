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
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
//*)

class FlexiGameEditorFrame: public wxFrame
{
    public:

        FlexiGameEditorFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~FlexiGameEditorFrame();

    private:

        //(*Handlers(FlexiGameEditorFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(FlexiGameEditorFrame)
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(FlexiGameEditorFrame)
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // FLEXIGAMEEDITORMAIN_H
