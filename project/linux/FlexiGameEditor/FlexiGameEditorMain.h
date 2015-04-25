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

//(*Headers(FlexiGameEditorFrame)
#include <wx/sizer.h>
#include <wx/notebook.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
//*)

    #include "CEngineGfxPanel.h"
    #include "CGfxHolderPanel.h"

enum EnginePreviewMode {
    FG_PREVIEW_HIDDEN,
    FG_PREVIEW_GAME,
    FG_PREVIEW_SCENE_MANAGER,
    FG_PREVIEW_SHADER_MANAGER,
    FG_PREVIEW_BSP_BUILDER,
    FG_PREVIEW_PARTICLE_EDITOR,
    FG_PREVIEW_GUI_EDITOR,
    FG_PREVIEW_MODEL_VIEWER,
    FG_PREVIEW_NUM_MODES
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
    CEngineGfxPanel* m_gfxMainCanvas;
    /// Special render timer for calling Refresh() with hard coded fps
    CRenderTimer* m_renderTimer;
    /// Special holding panels for gfx context - it's required because,
    /// there can be only one active gfx context, however the selected
    /// tabs can change along with the preview mode (displayed data)
    CGfxHolderPanel* m_gfxHolderPanels[FG_PREVIEW_NUM_MODES];
    CGfxHolderPanel* m_gfxHolderPanel;
    /// List of proper names for main notebook tabs
    wxString m_previewTabNames[FG_PREVIEW_NUM_MODES];

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


private:

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
    wxMenu GfxCanvasContextMenu;
    wxNotebook* MainNotebook;
    wxNotebook* LeftNotebook;
    wxNotebook* BottomNotebook;
    //*)

    DECLARE_EVENT_TABLE()
};

    #undef FG_INC_FLEXI_GAME_EDITOR_MAIN_BLOCK
#endif // FG_INC_FLEXI_GAME_EDITOR_MAIN
