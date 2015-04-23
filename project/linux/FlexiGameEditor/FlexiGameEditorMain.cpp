/***************************************************************
 * Name:      FlexiGameEditorMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Radoslaw Gniazdowski (contact@flexigame.com)
 * Created:   2015-04-21
 * Copyright: Radoslaw Gniazdowski (http://flexigame.com)
 * License:
 **************************************************************/

#include "FlexiGameEditorMain.h"
#include <wx/msgdlg.h>
#include <wx/textctrl.h>
#include <wx/richtext/richtextctrl.h>

//(*InternalHeaders(FlexiGameEditorFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(FlexiGameEditorFrame)
const long FlexiGameEditorFrame::idMenuQuit = wxNewId();
const long FlexiGameEditorFrame::idMenuEngineInitialize = wxNewId();
const long FlexiGameEditorFrame::idMenuEngineQuit = wxNewId();
const long FlexiGameEditorFrame::idMenuEngineFreezeFrame = wxNewId();
const long FlexiGameEditorFrame::idMenuToolsOptions = wxNewId();
const long FlexiGameEditorFrame::idMenuGitRunGitGUI = wxNewId();
const long FlexiGameEditorFrame::idMenuGitRunGitk = wxNewId();
const long FlexiGameEditorFrame::idMenuGitShowLog = wxNewId();
const long FlexiGameEditorFrame::idMenuGitOpenGitconfig = wxNewId();
const long FlexiGameEditorFrame::idMenuHelpLocalDocs = wxNewId();
const long FlexiGameEditorFrame::idMenuHelpAbout = wxNewId();
const long FlexiGameEditorFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(FlexiGameEditorFrame,wxFrame)
    //(*EventTable(FlexiGameEditorFrame)
    //*)
END_EVENT_TABLE()

FlexiGameEditorFrame::FlexiGameEditorFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(FlexiGameEditorFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("FlexiGame::Editor 1.0"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(640,480));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    BoxSizer1->Add(BoxSizer2, 5, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu3, idMenuEngineInitialize, _("Initialize\tAlt-R"), _("Initialize the internal FlexiGame::Engine"), wxITEM_NORMAL);
    Menu3->Append(MenuItem3);
    MenuItem11 = new wxMenuItem(Menu3, idMenuEngineQuit, _("Quit\tAlt+Q"), _("Close the game engine - exit the game"), wxITEM_NORMAL);
    Menu3->Append(MenuItem11);
    Menu3->AppendSeparator();
    MenuItem10 = new wxMenuItem(Menu3, idMenuEngineFreezeFrame, _("Freeze frame\tAlt-P"), _("Pause/freeze current frame"), wxITEM_NORMAL);
    Menu3->Append(MenuItem10);
    MenuBar1->Append(Menu3, _("En&gine"));
    Menu4 = new wxMenu();
    MenuItem4 = new wxMenuItem(Menu4, idMenuToolsOptions, _("Options"), _("Edit options for FlexiGame::Editor"), wxITEM_NORMAL);
    Menu4->Append(MenuItem4);
    MenuBar1->Append(Menu4, _("&Tools"));
    Menu5 = new wxMenu();
    MenuItem5 = new wxMenuItem(Menu5, idMenuGitRunGitGUI, _("Run Git GUI"), _("Execute the git gui application in project root folder"), wxITEM_NORMAL);
    Menu5->Append(MenuItem5);
    MenuItem6 = new wxMenuItem(Menu5, idMenuGitRunGitk, _("Run Gitk"), _("Run the gitk tool for visualing branches and commits"), wxITEM_NORMAL);
    Menu5->Append(MenuItem6);
    MenuItem7 = new wxMenuItem(Menu5, idMenuGitShowLog, _("Show log"), _("Show the git commits log"), wxITEM_NORMAL);
    Menu5->Append(MenuItem7);
    MenuItem8 = new wxMenuItem(Menu5, idMenuGitOpenGitconfig, _("Open .gitconfig"), _("Open for editing the main git configuration file for this project"), wxITEM_NORMAL);
    Menu5->Append(MenuItem8);
    MenuBar1->Append(Menu5, _("G&it"));
    Menu2 = new wxMenu();
    MenuItem9 = new wxMenuItem(Menu2, idMenuHelpLocalDocs, _("Local docs"), _("Open HTML viewer with documentation (local)"), wxITEM_NORMAL);
    Menu2->Append(MenuItem9);
    MenuItem2 = new wxMenuItem(Menu2, idMenuHelpAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    SetSizer(BoxSizer1);
    Layout();

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnQuit);
    Connect(idMenuEngineInitialize,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnMenuEngineInitialize);
    Connect(idMenuEngineQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnMenuEngineQuit);
    Connect(idMenuEngineFreezeFrame,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnMenuEngineFreezeFrame);
    Connect(idMenuHelpAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnAbout);
    //*)

    int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
    m_gfxPanel = new CEngineGFXPanel( (wxFrame*) this, args);

    BoxSizer2->Insert(0, m_gfxPanel, 3, wxEXPAND);

    this->m_renderTimer = new CRenderTimer(m_gfxPanel);
    this->m_renderTimer->start();

    //Layout();
}

FlexiGameEditorFrame::~FlexiGameEditorFrame()
{
    //(*Destroy(FlexiGameEditorFrame)
    //*)
}

void FlexiGameEditorFrame::OnQuit(wxCommandEvent& event)
{
    if(m_gfxPanel) {
        if(m_gfxPanel->isInitialized()) {
            m_gfxPanel->setExit(FG_TRUE);
            m_gfxPanel->update();
            m_gfxPanel->closeProgram();
        }
    }
    Close();
}

void FlexiGameEditorFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void FlexiGameEditorFrame::OnMenuEngineInitialize(wxCommandEvent& event)
{
    if(m_gfxPanel) {
        if(m_gfxPanel->isPaintReady()) {
                m_gfxPanel->setInitializeFlag(FG_TRUE);
        }
    }
}

void FlexiGameEditorFrame::OnMenuEngineFreezeFrame(wxCommandEvent& event)
{
    if(m_gfxPanel) {
        if(m_gfxPanel->isInitialized()) {
            // toggle frame freeze
            m_gfxPanel->setFrameFreeze(!m_gfxPanel->isFrameFreeze());
        }
    }
}

void FlexiGameEditorFrame::OnMenuEngineQuit(wxCommandEvent& event)
{
    if(m_gfxPanel) {
        if(m_gfxPanel->isInitialized()) {
            m_gfxPanel->setExit(FG_TRUE);
        }
    }
}
