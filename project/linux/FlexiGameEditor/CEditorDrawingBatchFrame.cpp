/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "CEditorDrawingBatchFrame.h"

//(*InternalHeaders(CEditorDrawingBatchFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(CEditorDrawingBatchFrame)
//*)

BEGIN_EVENT_TABLE(CEditorDrawingBatchFrame, wxFrame)
//(*EventTable(CEditorDrawingBatchFrame)
//*)
END_EVENT_TABLE()
//------------------------------------------------------------------------------

CEditorDrawingBatchFrame::CEditorDrawingBatchFrame(wxWindow* parent,
                                                   wxWindowID id,
                                                   const wxPoint& pos,
                                                   const wxSize& size) {
    ////////////////////////////////////////////////////////////////////////////
    //(*Initialize(CEditorDrawingBatchFrame)
    Create(parent, id, _("FlexiGame::DrawingBatch"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxDefaultSize);
    Move(wxDefaultPosition);
    Center();
    //*)
    ////////////////////////////////////////////////////////////////////////////

}
//------------------------------------------------------------------------------

CEditorDrawingBatchFrame::~CEditorDrawingBatchFrame() {
    //(*Destroy(CEditorDrawingBatchFrame)
    //*)
}
//------------------------------------------------------------------------------
