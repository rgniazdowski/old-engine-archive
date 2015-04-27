/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_EDITOR_CONFIG_PANEL
    #define FG_INC_EDITOR_CONFIG_PANEL
    #define FG_INC_EDITOR_CONFIG_PANEL_BLOCK

//(*Headers(CEditorConfigPanel)
    #include <wx/panel.h>
//*)

/**
 *
 */
class CEditorConfigPanel : public wxPanel {
public:
    typedef CEditorConfigPanel self_type;
    typedef CEditorConfigPanel type;
    typedef wxPanel base_type;

public:
    /**
     *
     * @param parent
     * @param id
     */
    CEditorConfigPanel(wxWindow* parent, wxWindowID id = wxID_ANY);
    /**
     *
     */
    virtual ~CEditorConfigPanel();

    //(*Declarations(CEditorConfigPanel)
    //*)

protected:

    //(*Identifiers(CEditorConfigPanel)
    //*)

private:

    //(*Handlers(CEditorConfigPanel)
    //*)

    DECLARE_EVENT_TABLE()
};

    #undef FG_INC_EDITOR_CONFIG_PANEL_BLOCK
#endif /* FG_INC_EDITOR_CONFIG_PANEL */
