/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "CGfxHolderPanel.h"
#include "CEngineGfxCanvas.h"

BEGIN_EVENT_TABLE(CGfxHolderPanel, wxPanel)
EVT_CONTEXT_MENU(CGfxHolderPanel::onContextMenu)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------

CGfxHolderPanel::CGfxHolderPanel(wxWindow* parent, CEngineGfxCanvas* gfxCanvas) :
wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxNO_BORDER | wxSIZE_AUTO) {
    m_boxSizer = new wxBoxSizer(wxHORIZONTAL);
    m_gfxCanvas = gfxCanvas;
    m_contextMenu = NULL;
    this->SetSizer(m_boxSizer);
    activateGfxCanvas();
}
//-----------------------------------------------------------------------------

CGfxHolderPanel::~CGfxHolderPanel() {
    removeGfxCanvas();
    m_gfxCanvas = NULL;
    m_contextMenu = NULL;
}
//-----------------------------------------------------------------------------

void CGfxHolderPanel::removeGfxCanvas(void) {
    if(m_boxSizer->GetItemCount() > 0 && m_gfxCanvas) {
        m_boxSizer->Detach(m_gfxCanvas);
        suspendGfxCanvas(FG_TRUE);
    } else if(!m_gfxCanvas) {
        if(m_boxSizer->GetItemCount())
            m_boxSizer->Clear(false);
    }
}
//-----------------------------------------------------------------------------

void CGfxHolderPanel::activateGfxCanvas(void) {
    removeGfxCanvas();
    if(m_gfxCanvas) {
        m_boxSizer->Add(m_gfxCanvas, 1, wxALL | wxEXPAND | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 2);
        showGfxCanvas(FG_TRUE);
        suspendGfxCanvas(FG_FALSE);
    }
}
//-----------------------------------------------------------------------------

void CGfxHolderPanel::setGfxCanvas(CEngineGfxCanvas* gfxCanvas) {
    removeGfxCanvas();
    if(gfxCanvas) {
        m_gfxCanvas = gfxCanvas;
        activateGfxCanvas();
    }
}
//-----------------------------------------------------------------------------

void CGfxHolderPanel::showGfxCanvas(fgBool toggle) {
    if(m_gfxCanvas) {
        m_gfxCanvas->Show((bool)toggle);
    }
}
//-----------------------------------------------------------------------------

void CGfxHolderPanel::suspendGfxCanvas(fgBool toggle) {
    if(m_gfxCanvas) {
        m_gfxCanvas->setSuspend(toggle);
    }
}
//-----------------------------------------------------------------------------

void CGfxHolderPanel::onContextMenu(wxContextMenuEvent& event) {
    //printf("Position context: %d x %d\n", event.GetPosition().x, event.GetPosition().y);
    popupGfxContextMenu(event.GetPosition());
}
//-----------------------------------------------------------------------------

void CGfxHolderPanel::popupGfxContextMenu(const wxPoint& position) {
    if(m_contextMenu) {
        PopupMenu(m_contextMenu);
    }
}
//-----------------------------------------------------------------------------
