/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_EDITOR_RES_MGR_PANEL
    #define FG_INC_EDITOR_RES_MGR_PANEL
    #define FG_INC_EDITOR_RES_MGR_PANEL_BLOCK

    #include "fgBool.h"

//(*Headers(CEditorResMgrPanel)
    #include <wx/sizer.h>
    #include <wx/listctrl.h>
    #include <wx/notebook.h>
    #include <wx/button.h>
    #include <wx/panel.h>
    #include <wx/gbsizer.h>
//*)

namespace fg {
    class CGameMain;
}

/**
 *
 */
class CEditorResMgrPanel : public wxPanel {
public:
    typedef CEditorResMgrPanel self_type;
    typedef CEditorResMgrPanel type;
    typedef wxPanel base_type;

public:
    /**
     *
     * @param parent
     * @param id
     * @param pos
     * @param size
     */
    CEditorResMgrPanel(wxWindow* parent,
                       wxWindowID id = wxID_ANY,
                       const wxPoint& pos = wxDefaultPosition,
                       const wxSize& size = wxDefaultSize);
    /**
     *
     */
    virtual ~CEditorResMgrPanel();

    /**
     *
     * @return
     */
    fgBool refreshResourceList(void);

public:
    /**
     *
     * @return
     */
    fg::CGameMain* getGameMain(void) const {
        return m_gameMain;
    }
    /**
     * 
     * @param gameMain
     */
    void setGameMain(fg::CGameMain* gameMain) {
        m_gameMain = gameMain;
    }

private:
    //(*Declarations(CEditorResMgrPanel)
    wxPanel* Page1;
    wxPanel* Page2;
    wxButton* RefreshButton;
    wxListView* ResourceListView;
    wxNotebook* Notebook1;
    //*)

protected:

    //(*Identifiers(CEditorResMgrPanel)
    static const long ID_RESOURCELISTVIEW;
    static const long ID_REFRESHLIST_BUTTON;
    static const long ID_PAGE1;
    static const long ID_PAGE2;
    static const long ID_NOTEBOOK1;
    //*)

private:
    ///
    fg::CGameMain* m_gameMain;

    //(*Handlers(CEditorResMgrPanel)
    void OnResListRefreshButtonClick(wxCommandEvent& event);
    //*)

    DECLARE_EVENT_TABLE()
};

    #undef FG_INC_EDITOR_RES_MGR_PANEL_BLOCK
#endif /* FG_INC_EDITOR_RES_MGR_PANEL */
