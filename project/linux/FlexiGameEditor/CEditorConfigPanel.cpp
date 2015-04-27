/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "CEditorConfigPanel.h"

//(*InternalHeaders(CEditorConfigPanel)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(CEditorConfigPanel)
//*)

BEGIN_EVENT_TABLE(CEditorConfigPanel, wxPanel)
//(*EventTable(CEditorConfigPanel)
//*)
END_EVENT_TABLE()
//------------------------------------------------------------------------------

CEditorConfigPanel::CEditorConfigPanel(wxWindow* parent, wxWindowID id) {
    ////////////////////////////////////////////////////////////////////////////
    //(*Initialize(CEditorConfigPanel)
    Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
    //*)
    ////////////////////////////////////////////////////////////////////////////
}
//------------------------------------------------------------------------------

CEditorConfigPanel::~CEditorConfigPanel() {
    //(*Destroy(CEditorConfigPanel)
    //*)
}
//------------------------------------------------------------------------------
