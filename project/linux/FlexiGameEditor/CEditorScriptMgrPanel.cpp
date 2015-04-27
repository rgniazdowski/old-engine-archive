/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "CEditorScriptMgrPanel.h"

//(*InternalHeaders(CEditorScriptMgrPanel)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(CEditorScriptMgrPanel)
//*)

BEGIN_EVENT_TABLE(CEditorScriptMgrPanel, wxPanel)
//(*EventTable(CEditorScriptMgrPanel)
//*)
END_EVENT_TABLE()
//------------------------------------------------------------------------------

CEditorScriptMgrPanel::CEditorScriptMgrPanel(wxWindow* parent,
                                             wxWindowID id,
                                             const wxPoint& pos,
                                             const wxSize& size) {
    ////////////////////////////////////////////////////////////////////////////
    //(*Initialize(CEditorScriptMgrPanel)
    Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
    //*)
    ////////////////////////////////////////////////////////////////////////////
}
//------------------------------------------------------------------------------

CEditorScriptMgrPanel::~CEditorScriptMgrPanel() {
    //(*Destroy(CEditorScriptMgrPanel)
    //*)
}
//------------------------------------------------------------------------------
