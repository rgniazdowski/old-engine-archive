/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
#include "CEditorEventMgrPanel.h"

//(*InternalHeaders(CEditorEventMgrPanel)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(CEditorEventMgrPanel)
//*)

BEGIN_EVENT_TABLE(CEditorEventMgrPanel, wxPanel)
//(*EventTable(CEditorEventMgrPanel)
//*)
END_EVENT_TABLE()
//------------------------------------------------------------------------------

CEditorEventMgrPanel::CEditorEventMgrPanel(wxWindow* parent,
                                           wxWindowID id,
                                           const wxPoint& pos,
                                           const wxSize& size) {
    ////////////////////////////////////////////////////////////////////////////
    //(*Initialize(CEditorEventMgrPanel)
    Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
    //*)
    ////////////////////////////////////////////////////////////////////////////
}
//------------------------------------------------------------------------------

CEditorEventMgrPanel::~CEditorEventMgrPanel() {
    //(*Destroy(CEditorEventMgrPanel)
    //*)
}
//------------------------------------------------------------------------------
