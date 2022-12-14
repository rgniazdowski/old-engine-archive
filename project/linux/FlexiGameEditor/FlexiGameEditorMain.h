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
 * Name:      FlexiGameEditorMain.h
 * Purpose:   Defines Application Frame
 * Author:    Radoslaw Gniazdowski (contact@flexigame.com)
 * Created:   2015-04-21
 * Copyright: Radoslaw Gniazdowski (http://flexigame.com)
 * License:
 **************************************************************/

#ifndef FG_INC_FLEXI_GAME_EDITOR_MAIN
    #define FG_INC_FLEXI_GAME_EDITOR_MAIN
    #define FG_INC_FLEXI_GAME_EDITOR_MAIN_BLOCK

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
//(*Headers(FlexiGameEditorFrame)
#include <wx/sizer.h>
#include <wx/notebook.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
//*)
#pragma GCC diagnostic pop

    #include "CEngineGfxCanvas.h"
    #include "CGfxHolderPanel.h"
    #include "CPreviewModeBase.h"
    #include "CPreviewBspBuilder.h"

/**
 *
 */
enum EnginePreviewMode {
    /// Hidden - invalid preview mode
    FG_PREVIEW_HIDDEN = 0,
    /// Gfx preview for Game
    FG_PREVIEW_GAME = 1,
    /// Special gfx preview mode - scene management
    FG_PREVIEW_SCENE_MANAGER = 2,
    /// Shader management - testing, writing shaders
    FG_PREVIEW_SHADER_MANAGER = 3,
    /// BSP Builder preview mode - editing for BSP trees
    FG_PREVIEW_BSP_BUILDER = 4,
    /// Particle editing gfx preview
    FG_PREVIEW_PARTICLE_EDITOR = 5,
    /// Special XML editor for GUI structures
    FG_PREVIEW_GUI_EDITOR = 6,
    /// Model viewer, saver/exporter
    FG_PREVIEW_MODEL_VIEWER = 7,
    /// Total number of 3D preview modes
    FG_PREVIEW_NUM_MODES = 8
};

/**
 *
 */
class FlexiGameEditorFrame : public wxFrame {
public:
    /**
     *
     * @param parent
     * @param id
     */
    FlexiGameEditorFrame(wxWindow* parent, wxWindowID id = -1);
    /**
     *
     */
    virtual ~FlexiGameEditorFrame();

private:
    /// Currently selected/active preview mode
    /// This will also match the currently selected main notebook tab
    EnginePreviewMode m_previewMode;
    /// This is a special gfx context panel - only one can be active
    CEngineGfxCanvas* m_engineGfxCanvas;
    /// Special render timer for calling Refresh() with hard coded fps
    CRenderTimer* m_renderTimer;
    /// Special holding panels for gfx context - it's required because,
    /// there can be only one active gfx context, however the selected
    /// tabs can change along with the preview mode (displayed data)
    //CGfxHolderPanel* m_gfxHolderPanels[FG_PREVIEW_NUM_MODES];
    CGfxHolderPanel* m_gfxHolderPanel;
    /// List of proper names for main notebook tabs
    wxString m_previewTabNames[FG_PREVIEW_NUM_MODES];
    ///
    fg::editor::CPreviewModeBase* m_previews[FG_PREVIEW_NUM_MODES];
    ///
    fg::CEngineMain* m_engineMain;

public:
    /**
     * This function will activate the selected preview panel, meaning:
     * If there are other panels, their EngineGfxPanel will be removed,
     * the suspend will be activated, gfx panel hidden. After that a
     * given notebook tab will be selected/added and gfx context activated
     * on a selected tab
     * @param previewMode
     * @param toggle
     * @return
     */
    fgBool activatePreviewPanel(EnginePreviewMode previewMode = FG_PREVIEW_GAME,
                                fgBool toggle = FG_TRUE);
    /**
     * This function will remove the selected preview panel (not destroy)
     * The engine gfx panel (wxGLCanvas) will be suspended, and hidden
     * Now depending on available (present) preview tabs, the first available
     * will be selected and activated
     * @param previewMode
     * @return
     */
    fgBool closePreviewPanel(EnginePreviewMode previewMode = FG_PREVIEW_GAME);

    /**
     *
     * @param name
     * @return
     */
    EnginePreviewMode getPreviewMode(const wxString& name);
    /**
     *
     * @param name
     * @return
     */
    EnginePreviewMode getPreviewMode(const std::string& name);
    /**
     *
     * @param name
     * @return
     */
    EnginePreviewMode getPreviewMode(const char* name);

    void onContextMenu(wxContextMenuEvent& event);

    int FilterEvent(wxEvent& event);

private:

    void OnIdle(wxIdleEvent& event);

    //(*Handlers(FlexiGameEditorFrame)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnMenuEngineInitialize(wxCommandEvent& event);
    void OnMenuEngineFreezeFrame(wxCommandEvent& event);
    void OnMenuEngineQuit(wxCommandEvent& event);
    void OnLeftNotebookPageChanged(wxNotebookEvent& event);
    void OnBottomNotebookPageChanged(wxNotebookEvent& event);
    void OnMenuToolsResourceManager(wxCommandEvent& event);
    void OnMenuToolsScriptManager(wxCommandEvent& event);
    void OnMenuToolsEventManager(wxCommandEvent& event);
    void OnMenuToolsFlexiGUIEditor(wxCommandEvent& event);
    void OnMenuToolsSceneManager(wxCommandEvent& event);
    void OnMenuToolsShaderManager(wxCommandEvent& event);
    void OnMenuToolsBSPBuilder(wxCommandEvent& event);
    void OnMenuToolsParticleEditor(wxCommandEvent& event);
    void OnMenuToolsModelViewer(wxCommandEvent& event);
    void OnMenuToolsOptions(wxCommandEvent& event);
    void OnMainNotebookPageChanged(wxNotebookEvent& event);
    void OnGfxContextItemCloseViewSelected(wxCommandEvent& event);
    //*)

    //(*Identifiers(FlexiGameEditorFrame)
    static const long idLeftNotebook;
    static const long idMainNotebook;
    static const long idBottomNotebook;
    static const long idMenuQuit;
    static const long idMenuEngineInitialize;
    static const long idMenuEngineQuit;
    static const long idMenuEngineFreezeFrame;
    static const long idMenuToolsResourceManager;
    static const long idMenuToolsScriptManager;
    static const long idMenuToolsEventManager;
    static const long idMenuToolsFlexiGUIEditor;
    static const long idMenuToolsSceneManager;
    static const long idMenuToolsShaderManager;
    static const long idMenuToolsBSPBuilder;
    static const long idMenuToolsParticleEditor;
    static const long idMenuToolsModelViewer;
    static const long idMenuToolsOptions;
    static const long idMenuGitRunGitGUI;
    static const long idMenuGitRunGitk;
    static const long idMenuGitShowLog;
    static const long idMenuGitOpenGitconfig;
    static const long idMenuHelpLocalDocs;
    static const long idMenuHelpAbout;
    static const long idMainStatusBar;
    static const long idGfxContextMenuCloseView;
    //*)

    //(*Declarations(FlexiGameEditorFrame)
    wxStatusBar* MainStatusBar;
    wxMenuBar* MenuBarTop;
    wxBoxSizer* MainBoxSizerV;
    wxMenu GfxCanvasContextMenu;
    wxBoxSizer* MainBoxSizerH;
    wxNotebook* MainNotebook;
    wxNotebook* LeftNotebook;
    wxNotebook* BottomNotebook;
    //*)

    DECLARE_EVENT_TABLE()
};

    #undef FG_INC_FLEXI_GAME_EDITOR_MAIN_BLOCK
#endif // FG_INC_FLEXI_GAME_EDITOR_MAIN
