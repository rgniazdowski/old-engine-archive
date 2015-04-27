/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_EDITOR_EVENT_MGR_PANEL
    #define FG_INC_EDITOR_EVENT_MGR_PANEL
    #define FG_INC_EDITOR_EVENT_MGR_PANEL_BLOCK

//(*Headers(CEditorEventMgrPanel)
    #include <wx/panel.h>
//*)

/**
 *
 */
class CEditorEventMgrPanel : public wxPanel {
public:
    typedef CEditorEventMgrPanel self_type;
    typedef CEditorEventMgrPanel type;
    typedef wxPanel base_type;

public:
    /**
     *
     * @param parent
     * @param id
     * @param pos
     * @param size
     */
    CEditorEventMgrPanel(wxWindow* parent,
                         wxWindowID id = wxID_ANY,
                         const wxPoint& pos = wxDefaultPosition,
                         const wxSize& size = wxDefaultSize);
    /**
     * 
     */
    virtual ~CEditorEventMgrPanel();

    //(*Declarations(CEditorEventMgrPanel)
    //*)

protected:

    //(*Identifiers(CEditorEventMgrPanel)
    //*)

private:

    //(*Handlers(CEditorEventMgrPanel)
    //*)

    DECLARE_EVENT_TABLE()
};

    #undef FG_INC_EDITOR_EVENT_MGR_PANEL_BLOCK
#endif /* FG_INC_EDITOR_EVENT_MGR_PANEL */
