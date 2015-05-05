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
 * Name:      FlexiGameEditorMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Radoslaw Gniazdowski (contact@flexigame.com)
 * Created:   2015-04-21
 * Copyright: Radoslaw Gniazdowski (http://flexigame.com)
 * License:
 **************************************************************/

#include "FlexiGameEditorMain.h"
#include "CEditorResMgrPanel.h"

#include <wx/msgdlg.h>

//(*InternalHeaders(FlexiGameEditorFrame)
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)

//-----------------------------------------------------------------------------

//helper functions

enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format) {
    wxString wxbuild(wxVERSION_STRING);

    if(format == long_f) {
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
//-----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
//(*IdInit(FlexiGameEditorFrame)
const long FlexiGameEditorFrame::idLeftNotebook = wxNewId();
const long FlexiGameEditorFrame::idMainNotebook = wxNewId();
const long FlexiGameEditorFrame::idBottomNotebook = wxNewId();
const long FlexiGameEditorFrame::idMenuQuit = wxNewId();
const long FlexiGameEditorFrame::idMenuEngineInitialize = wxNewId();
const long FlexiGameEditorFrame::idMenuEngineQuit = wxNewId();
const long FlexiGameEditorFrame::idMenuEngineFreezeFrame = wxNewId();
const long FlexiGameEditorFrame::idMenuToolsResourceManager = wxNewId();
const long FlexiGameEditorFrame::idMenuToolsScriptManager = wxNewId();
const long FlexiGameEditorFrame::idMenuToolsEventManager = wxNewId();
const long FlexiGameEditorFrame::idMenuToolsFlexiGUIEditor = wxNewId();
const long FlexiGameEditorFrame::idMenuToolsSceneManager = wxNewId();
const long FlexiGameEditorFrame::idMenuToolsShaderManager = wxNewId();
const long FlexiGameEditorFrame::idMenuToolsBSPBuilder = wxNewId();
const long FlexiGameEditorFrame::idMenuToolsParticleEditor = wxNewId();
const long FlexiGameEditorFrame::idMenuToolsModelViewer = wxNewId();
const long FlexiGameEditorFrame::idMenuToolsOptions = wxNewId();
const long FlexiGameEditorFrame::idMenuGitRunGitGUI = wxNewId();
const long FlexiGameEditorFrame::idMenuGitRunGitk = wxNewId();
const long FlexiGameEditorFrame::idMenuGitShowLog = wxNewId();
const long FlexiGameEditorFrame::idMenuGitOpenGitconfig = wxNewId();
const long FlexiGameEditorFrame::idMenuHelpLocalDocs = wxNewId();
const long FlexiGameEditorFrame::idMenuHelpAbout = wxNewId();
const long FlexiGameEditorFrame::idMainStatusBar = wxNewId();
const long FlexiGameEditorFrame::idGfxContextMenuCloseView = wxNewId();
//*)
////////////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE(FlexiGameEditorFrame, wxFrame)
//(*EventTable(FlexiGameEditorFrame)
//*)
EVT_IDLE(FlexiGameEditorFrame::OnIdle)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------
CEditorResMgrPanel *g_resMgrPanel = NULL;

FlexiGameEditorFrame::FlexiGameEditorFrame(wxWindow* parent, wxWindowID id) : wxFrame(),
m_previewMode(FG_PREVIEW_HIDDEN),
m_gfxMainCanvas(NULL),
m_renderTimer(NULL),
m_gfxHolderPanel(NULL),
m_previewTabNames(),
m_engineMain(NULL) {
    ////////////////////////////////////////////////////////////////////////////
    //(*Initialize(FlexiGameEditorFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu5;
    wxMenu* Menu1;
    wxMenuItem* GfxContextItemCloseView;
    wxMenuItem* MenuItem16;
    wxMenuItem* MenuItem12;
    wxMenuItem* MenuItem19;
    wxMenu* Menu3;
    wxMenuItem* MenuItem20;
    wxMenuItem* MenuItem15;
    wxMenuItem* MenuItem17;
    wxMenuItem* MenuItem3;
    wxMenuItem* MenuItem9;
    wxMenu* Menu4;
    wxMenuItem* MenuItem11;
    wxMenuItem* MenuItem5;
    wxMenuItem* MenuItem10;
    wxMenuItem* MenuItem18;
    wxMenuItem* MenuItem7;
    wxMenuItem* MenuItem6;
    wxMenuItem* MenuItem4;
    wxMenuItem* MenuItem13;
    wxMenu* Menu2;
    wxMenuItem* MenuItem8;
    wxMenuItem* MenuItem14;

    Create(parent, wxID_ANY, _("FlexiGame::Editor 1.0"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(800,550));
    SetMinSize(wxSize(600,480));
    wxFont thisFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !thisFont.Ok() ) thisFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    thisFont.SetPointSize((int)(thisFont.GetPointSize() * 0.950000));
    thisFont.SetStyle(wxFONTSTYLE_NORMAL);
    thisFont.SetWeight(wxLIGHT);
    thisFont.SetUnderlined(false);
    thisFont.SetFaceName(_T("Arial"));
    SetFont(thisFont);
    MainBoxSizerH = new wxBoxSizer(wxHORIZONTAL);
    LeftNotebook = new wxNotebook(this, idLeftNotebook, wxDefaultPosition, wxDefaultSize, 0, _T("idLeftNotebook"));
    LeftNotebook->SetMinSize(wxSize(256,384));
    LeftNotebook->SetMaxSize(wxSize(384,0));
    MainBoxSizerH->Add(LeftNotebook, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    MainBoxSizerV = new wxBoxSizer(wxVERTICAL);
    MainNotebook = new wxNotebook(this, idMainNotebook, wxDefaultPosition, wxDefaultSize, 0, _T("idMainNotebook"));
    MainBoxSizerV->Add(MainNotebook, 3, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    BottomNotebook = new wxNotebook(this, idBottomNotebook, wxDefaultPosition, wxSize(-1,64), wxNB_LEFT, _T("idBottomNotebook"));
    BottomNotebook->SetMinSize(wxSize(128,196));
    MainBoxSizerV->Add(BottomNotebook, -1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    MainBoxSizerH->Add(MainBoxSizerV, 3, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    SetSizer(MainBoxSizerH);
    MenuBarTop = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBarTop->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu3, idMenuEngineInitialize, _("Initialize\tAlt-R"), _("Initialize the internal FlexiGame::Engine"), wxITEM_NORMAL);
    Menu3->Append(MenuItem3);
    MenuItem11 = new wxMenuItem(Menu3, idMenuEngineQuit, _("Quit\tAlt+Q"), _("Close the game engine - exit the game"), wxITEM_NORMAL);
    Menu3->Append(MenuItem11);
    Menu3->AppendSeparator();
    MenuItem10 = new wxMenuItem(Menu3, idMenuEngineFreezeFrame, _("Freeze frame\tAlt-P"), _("Pause/freeze current frame"), wxITEM_NORMAL);
    Menu3->Append(MenuItem10);
    MenuBarTop->Append(Menu3, _("En&gine"));
    Menu4 = new wxMenu();
    MenuItem12 = new wxMenuItem(Menu4, idMenuToolsResourceManager, _("Resource Manager"), _("Open window with Resource Manager"), wxITEM_NORMAL);
    Menu4->Append(MenuItem12);
    MenuItem13 = new wxMenuItem(Menu4, idMenuToolsScriptManager, _("Script Manager"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem13);
    MenuItem14 = new wxMenuItem(Menu4, idMenuToolsEventManager, _("Event Manager"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem14);
    MenuItem15 = new wxMenuItem(Menu4, idMenuToolsFlexiGUIEditor, _("Flexi GUI Editor"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem15);
    Menu4->AppendSeparator();
    MenuItem16 = new wxMenuItem(Menu4, idMenuToolsSceneManager, _("Scene Manager"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem16);
    MenuItem17 = new wxMenuItem(Menu4, idMenuToolsShaderManager, _("Shader Manager"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem17);
    MenuItem18 = new wxMenuItem(Menu4, idMenuToolsBSPBuilder, _("BSP Builder"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem18);
    MenuItem19 = new wxMenuItem(Menu4, idMenuToolsParticleEditor, _("Particle Editor"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem19);
    MenuItem20 = new wxMenuItem(Menu4, idMenuToolsModelViewer, _("Model Viewer"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem20);
    Menu4->AppendSeparator();
    MenuItem4 = new wxMenuItem(Menu4, idMenuToolsOptions, _("Options"), _("Edit options for FlexiGame::Editor"), wxITEM_NORMAL);
    Menu4->Append(MenuItem4);
    MenuBarTop->Append(Menu4, _("&Tools"));
    Menu5 = new wxMenu();
    MenuItem5 = new wxMenuItem(Menu5, idMenuGitRunGitGUI, _("Run Git GUI"), _("Execute the git gui application in project root folder"), wxITEM_NORMAL);
    Menu5->Append(MenuItem5);
    MenuItem6 = new wxMenuItem(Menu5, idMenuGitRunGitk, _("Run Gitk"), _("Run the gitk tool for visualing branches and commits"), wxITEM_NORMAL);
    Menu5->Append(MenuItem6);
    MenuItem7 = new wxMenuItem(Menu5, idMenuGitShowLog, _("Show log"), _("Show the git commits log"), wxITEM_NORMAL);
    Menu5->Append(MenuItem7);
    MenuItem8 = new wxMenuItem(Menu5, idMenuGitOpenGitconfig, _("Open .gitconfig"), _("Open for editing the main git configuration file for this project"), wxITEM_NORMAL);
    Menu5->Append(MenuItem8);
    MenuBarTop->Append(Menu5, _("G&it"));
    Menu2 = new wxMenu();
    MenuItem9 = new wxMenuItem(Menu2, idMenuHelpLocalDocs, _("Local docs"), _("Open HTML viewer with documentation (local)"), wxITEM_NORMAL);
    Menu2->Append(MenuItem9);
    MenuItem2 = new wxMenuItem(Menu2, idMenuHelpAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBarTop->Append(Menu2, _("Help"));
    SetMenuBar(MenuBarTop);
    MainStatusBar = new wxStatusBar(this, idMainStatusBar, wxST_SIZEGRIP, _T("idMainStatusBar"));
    int __wxStatusBarWidths_1[2] = { -10, -10 };
    int __wxStatusBarStyles_1[2] = { wxSB_NORMAL, wxSB_NORMAL };
    MainStatusBar->SetFieldsCount(2,__wxStatusBarWidths_1);
    MainStatusBar->SetStatusStyles(2,__wxStatusBarStyles_1);
    SetStatusBar(MainStatusBar);
    GfxContextItemCloseView = new wxMenuItem((&GfxCanvasContextMenu), idGfxContextMenuCloseView, _("Close view"), wxEmptyString, wxITEM_NORMAL);
    GfxCanvasContextMenu.Append(GfxContextItemCloseView);
    SetSizer(MainBoxSizerH);
    Layout();

    Connect(idLeftNotebook,wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnLeftNotebookPageChanged);
    Connect(idMainNotebook,wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnMainNotebookPageChanged);
    Connect(idBottomNotebook,wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnBottomNotebookPageChanged);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnQuit);
    Connect(idMenuEngineInitialize,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnMenuEngineInitialize);
    Connect(idMenuEngineQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnMenuEngineQuit);
    Connect(idMenuEngineFreezeFrame,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnMenuEngineFreezeFrame);
    Connect(idMenuToolsResourceManager,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnMenuToolsResourceManager);
    Connect(idMenuToolsScriptManager,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnMenuToolsScriptManager);
    Connect(idMenuToolsEventManager,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnMenuToolsEventManager);
    Connect(idMenuToolsFlexiGUIEditor,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnMenuToolsFlexiGUIEditor);
    Connect(idMenuToolsSceneManager,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnMenuToolsSceneManager);
    Connect(idMenuToolsShaderManager,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnMenuToolsShaderManager);
    Connect(idMenuToolsBSPBuilder,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnMenuToolsBSPBuilder);
    Connect(idMenuToolsParticleEditor,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnMenuToolsParticleEditor);
    Connect(idMenuToolsModelViewer,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnMenuToolsModelViewer);
    Connect(idMenuToolsOptions,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnMenuToolsOptions);
    Connect(idMenuHelpAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnAbout);
    Connect(idGfxContextMenuCloseView,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&FlexiGameEditorFrame::OnGfxContextItemCloseViewSelected);
    //*)
    ////////////////////////////////////////////////////////////////////////////

    __wxStatusBarStyles_1[0] = wxSB_SUNKEN;
    __wxStatusBarStyles_1[1] = wxSB_SUNKEN;
    MainStatusBar->SetStatusStyles(2, __wxStatusBarStyles_1);

    Connect(idMainNotebook, wxEVT_CONTEXT_MENU, (wxObjectEventFunction)&FlexiGameEditorFrame::onContextMenu);

    m_previewTabNames[FG_PREVIEW_HIDDEN] = wxT("Hidden");
    m_previewTabNames[FG_PREVIEW_GAME] = wxT("Game view");
    m_previewTabNames[FG_PREVIEW_SCENE_MANAGER] = wxT("Scene Manager");
    m_previewTabNames[FG_PREVIEW_SHADER_MANAGER] = wxT("Shader Manager");
    m_previewTabNames[FG_PREVIEW_BSP_BUILDER] = wxT("BSP Builder");
    m_previewTabNames[FG_PREVIEW_PARTICLE_EDITOR] = wxT("Particle Editor");
    m_previewTabNames[FG_PREVIEW_GUI_EDITOR] = wxT("GUI Editor");
    m_previewTabNames[FG_PREVIEW_MODEL_VIEWER] = wxT("Model Viewer");
    //FG_PREVIEW_NUM_MODES

    int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};

    m_gfxHolderPanel = new CGfxHolderPanel(MainNotebook);
    m_gfxMainCanvas = new CEngineGfxCanvas(m_gfxHolderPanel, args, &m_engineMain);
    m_gfxHolderPanel->setGfxCanvas(m_gfxMainCanvas);
    m_gfxHolderPanel->setContextMenu(&GfxCanvasContextMenu);
    
    MainNotebook->InsertPage(0, m_gfxHolderPanel, m_previewTabNames[FG_PREVIEW_GAME], true);
    
    m_renderTimer = new CRenderTimer(m_gfxMainCanvas);
    m_renderTimer->start();

    g_resMgrPanel = new CEditorResMgrPanel(MainNotebook);
    MainNotebook->AddPage(g_resMgrPanel, "Resource manager 1");

    Layout();

    fg::timesys::init();
    m_previewMode = FG_PREVIEW_GAME;
}
//-----------------------------------------------------------------------------


FlexiGameEditorFrame::~FlexiGameEditorFrame() {
    //(*Destroy(FlexiGameEditorFrame)
    //*)
    m_renderTimer->Stop();
    delete m_renderTimer;
    m_renderTimer = NULL;
}
//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnIdle(wxIdleEvent& event) {
    if(m_gfxMainCanvas) {
        g_resMgrPanel->setEngineMain(m_engineMain);
    }
    usleep(1000 * 1); // 100 fps ?
    //usleep(1000 * 20); // 50 fps ?
}
//-----------------------------------------------------------------------------

fgBool FlexiGameEditorFrame::activatePreviewPanel(EnginePreviewMode previewMode, fgBool toggle) {
    if(previewMode == FG_PREVIEW_HIDDEN) {
        return FG_FALSE; // ?
    }
    int nPages = (int)MainNotebook->GetPageCount();
    int selection = MainNotebook->GetSelection();
    fgBool activated = FG_FALSE;
    int existIdx = -1;
    for(int i = 0; i < nPages; i++) {
        wxString pageName = MainNotebook->GetPageText(i);
        EnginePreviewMode tabPreviewMode = getPreviewMode(pageName);
        if(tabPreviewMode == FG_PREVIEW_HIDDEN) {
            continue;
        }
        wxWindow *page = MainNotebook->GetPage(i);
        if(tabPreviewMode == previewMode) {
            // There already is such panel active
            // Need to reinitialize it's preview panel
            //return FG_TRUE;
            existIdx = i;
            if(page == (wxWindow *)m_gfxHolderPanel) {
                // The page already exists and has proper GfxHolder inside
                MainNotebook->ChangeSelection(i);
                m_previewMode = previewMode;
                return FG_TRUE;
            } else {
                // well this means that the page contains a dummy
                // need to erase it and fix it - later
            }
        } else if(page == (wxWindow *)m_gfxHolderPanel) {
            // this page is in different mode but contains the gfxHolderPanel
            // need to remove it and replace with dummy
            m_gfxHolderPanel->getGfxCanvas()->setSuspend(FG_TRUE);
            m_gfxHolderPanel->getGfxCanvas()->Show(false);
            m_gfxHolderPanel->Layout();
            MainNotebook->RemovePage(i);
            wxPanel* dummy = new wxPanel(MainNotebook);
            MainNotebook->InsertPage(i, dummy, pageName, false);
        }
    }
    if(existIdx != -1) {
        wxString pageName = MainNotebook->GetPageText(existIdx);
        wxWindow *page = MainNotebook->GetPage(existIdx);
        MainNotebook->RemovePage(existIdx);
        delete page;
        MainNotebook->InsertPage(existIdx, m_gfxHolderPanel, pageName, false);
        MainNotebook->ChangeSelection(existIdx);
        m_gfxHolderPanel->getGfxCanvas()->setSuspend(FG_FALSE);
        m_gfxHolderPanel->getGfxCanvas()->Show(true);
        m_gfxHolderPanel->Layout();
        MainNotebook->Layout();
        activated = FG_TRUE;
    } else {
        // this will be a new insertion
        MainNotebook->AddPage(m_gfxHolderPanel, m_previewTabNames[previewMode], false);
        MainNotebook->ChangeSelection(MainNotebook->GetPageCount() - 1);
        m_gfxHolderPanel->getGfxCanvas()->setSuspend(FG_FALSE);
        m_gfxHolderPanel->getGfxCanvas()->Show(true);
        m_gfxHolderPanel->Layout();
        MainNotebook->Layout();
        activated = FG_TRUE;
    }
    if(activated) {
        m_previewMode = previewMode;
    }
    return activated;
}
//-----------------------------------------------------------------------------

fgBool FlexiGameEditorFrame::closePreviewPanel(EnginePreviewMode previewMode) {
    if(previewMode == FG_PREVIEW_HIDDEN) {
        return FG_FALSE; // ?
    }
    int nPages = (int)MainNotebook->GetPageCount();
    for(int i = 0; i < nPages; i++) {
        wxString pageName = MainNotebook->GetPageText(i);
        EnginePreviewMode tabPreviewMode = getPreviewMode(pageName);
        if(tabPreviewMode == FG_PREVIEW_HIDDEN) {
            continue;
        }
        wxWindow *page = MainNotebook->GetPage(i);
        if(!page)
            continue;
        if(tabPreviewMode == previewMode) {
            // There is such panel inside
            // need to remove it

            if(page == (wxWindow *)m_gfxHolderPanel) {
                // The page already exists and has proper GfxHolder inside
                // remove the page
                m_gfxHolderPanel->getGfxCanvas()->setSuspend(FG_TRUE);
                m_gfxHolderPanel->getGfxCanvas()->Show(false);
                MainNotebook->SetSelection(i > 0 ? i - 1 : i + 1);
                MainNotebook->RemovePage(i);
                printf("Removed page: %d -> new selection %d | NUM %d\n", i, i > 0 ? i - 1 : i + 1, nPages);
                return FG_TRUE;
            } else {
                // well this means that the page contains a dummy
                // need to erase it and fix it
                MainNotebook->SetSelection(i > 0 ? i - 1 : i + 1);
                MainNotebook->RemovePage(i);
                delete page;
                printf("Removed page: %d -> new selection %d | NUM %d\n", i, i > 0 ? i - 1 : i + 1, nPages);
                return FG_TRUE;
            }
        }
    }
    return FG_FALSE;
}
//-----------------------------------------------------------------------------

EnginePreviewMode FlexiGameEditorFrame::getPreviewMode(const wxString& name) {
    unsigned int n = (unsigned int)FG_PREVIEW_NUM_MODES;
    for(unsigned int i = 0; i < n; i++) {
        if(m_previewTabNames[i].compare(name) == 0) {
            return (EnginePreviewMode)i;
        }
    }
    return FG_PREVIEW_HIDDEN;
}
//-----------------------------------------------------------------------------

EnginePreviewMode FlexiGameEditorFrame::getPreviewMode(const std::string& name) {
    unsigned int n = (unsigned int)FG_PREVIEW_NUM_MODES;
    for(unsigned int i = 0; i < n; i++) {
        if(m_previewTabNames[i].compare(name.c_str()) == 0) {
            return (EnginePreviewMode)i;
        }
    }

    return FG_PREVIEW_HIDDEN;
}
//-----------------------------------------------------------------------------

EnginePreviewMode FlexiGameEditorFrame::getPreviewMode(const char* name) {
    unsigned int n = (unsigned int)FG_PREVIEW_NUM_MODES;
    for(unsigned int i = 0; i < n; i++) {
        if(m_previewTabNames[i].compare(name) == 0) {
            return (EnginePreviewMode)i;
        }
    }
    return FG_PREVIEW_HIDDEN;
}
//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnQuit(wxCommandEvent& event) {
    if(m_gfxMainCanvas) {
        if(m_gfxMainCanvas->isInitialized()) {
            m_gfxMainCanvas->setExit(FG_TRUE);
            m_gfxMainCanvas->update();
            m_gfxMainCanvas->closeProgram();
        }
    }
    Close();
}
//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnAbout(wxCommandEvent& event) {
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
    /*
        MainBoxSizerV->Detach(MainNotebook);
        //MainBoxSizerV->Remove(0);
        wxFrame *frame = new wxFrame(this, wxID_ANY, wxT("FlexiGame::Editor - Main view"));
        frame->SetMinSize(wxSize(700, 500));
        wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
        frame->SetSizer(boxSizer);
        MainNotebook->Reparent(frame);
        boxSizer->Add(MainNotebook, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL);
        m_gfxHolderPanel->Show(true);
        m_gfxMainCanvas->Show(true);
        frame->Layout();
        frame->Show(true);
        Layout();
        activatePreviewPanel(FG_PREVIEW_GAME);
     */
}
//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnMenuEngineInitialize(wxCommandEvent& event) {
    if(m_gfxMainCanvas) {
        if(m_gfxMainCanvas->isPaintReady()) {
            m_gfxMainCanvas->setInitializeFlag(FG_TRUE);
        }
    }
}
//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnMenuEngineFreezeFrame(wxCommandEvent& event) {
    if(m_gfxMainCanvas) {
        static bool toggle = true;
        toggle = !toggle;
        m_gfxMainCanvas->Show(toggle);
        this->Layout();
        //m_gfxPanel->setSuspend(FG_TRUE);
        //MainNotebook->RemovePage(0);
        //MainNotebook->InsertPage(0, m_gfxPanel, wxT("Scene Manager"));
        //m_gfxPanel->setSuspend(FG_FALSE);
        if(m_gfxMainCanvas->isInitialized()) {
            // toggle frame freeze
            //m_gfxPanel->setFrameFreeze(!m_gfxPanel->isFrameFreeze());
        }
    }
}
//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnMenuEngineQuit(wxCommandEvent& event) {
    if(m_gfxMainCanvas) {
        if(m_gfxMainCanvas->isInitialized()) {
            m_gfxMainCanvas->setExit(FG_TRUE);
        }
    }
}
//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnLeftNotebookPageChanged(wxNotebookEvent& event) { }
//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnBottomNotebookPageChanged(wxNotebookEvent& event) { }
//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnMainNotebookPageChanged(wxNotebookEvent& event) {
    if(!MainNotebook) {
        return;
    }
    wxBookCtrlEvent &ctrlEvent = event;
    int oldSelection = ctrlEvent.GetOldSelection();
    int newSelection = ctrlEvent.GetSelection();
    if(oldSelection == wxNOT_FOUND || newSelection == wxNOT_FOUND) {
        // No need to process this event changer
        return;
    }
    if(oldSelection > -1) {
        wxString oldName = MainNotebook->GetPageText(oldSelection);
        FG_LOG_DEBUG("WX: Old preview: '%s'", oldName.c_str().AsChar());
    }

    wxString newName = MainNotebook->GetPageText(newSelection);
    // New selection exists, now can activate a proper tab
    EnginePreviewMode newPreviewMode = getPreviewMode(newName);
    if(newPreviewMode == FG_PREVIEW_HIDDEN) {
        return;
    }
    FG_LOG_DEBUG("WX: Activating new preview: '%s'", newName.c_str().AsChar());
    activatePreviewPanel(newPreviewMode);
    //ctrlEvent.Veto(); // changing?
}

//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnMenuToolsResourceManager(wxCommandEvent& event) { }
//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnMenuToolsScriptManager(wxCommandEvent& event) { }
//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnMenuToolsEventManager(wxCommandEvent& event) { }
//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnMenuToolsFlexiGUIEditor(wxCommandEvent& event) {
    activatePreviewPanel(FG_PREVIEW_GUI_EDITOR);
}
//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnMenuToolsSceneManager(wxCommandEvent& event) {
    activatePreviewPanel(FG_PREVIEW_SCENE_MANAGER);
}
//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnMenuToolsShaderManager(wxCommandEvent& event) {
    activatePreviewPanel(FG_PREVIEW_SHADER_MANAGER);
}
//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnMenuToolsBSPBuilder(wxCommandEvent& event) {
    activatePreviewPanel(FG_PREVIEW_BSP_BUILDER);
}
//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnMenuToolsParticleEditor(wxCommandEvent& event) {
    activatePreviewPanel(FG_PREVIEW_PARTICLE_EDITOR);
}
//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnMenuToolsModelViewer(wxCommandEvent& event) {
    activatePreviewPanel(FG_PREVIEW_MODEL_VIEWER);
}
//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnMenuToolsOptions(wxCommandEvent& event) {
    //if(event.GetId() == idMenuToolsOptions) {
    //    printf("OnMenuToolsOptions -- ID MATCH: %l\n", idMenuToolsOptions);
    //}
}
//-----------------------------------------------------------------------------

void FlexiGameEditorFrame::OnGfxContextItemCloseViewSelected(wxCommandEvent& event) {
    if(MainNotebook) {
        int selection = MainNotebook->GetSelection();
        wxString pageName = MainNotebook->GetPageText(selection);
        EnginePreviewMode previewMode = getPreviewMode(pageName);
        if(previewMode != FG_PREVIEW_HIDDEN && MainNotebook->GetPageCount() > 1) {
            // need to close specified preview
            closePreviewPanel(previewMode);
        }
    }
}
//-----------------------------------------------------------------------------
