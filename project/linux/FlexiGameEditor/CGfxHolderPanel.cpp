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
#include "CEngineGfxPanel.h"

BEGIN_EVENT_TABLE(CGfxHolderPanel, wxPanel)
    EVT_CONTEXT_MENU(CGfxHolderPanel::onContextMenu)
END_EVENT_TABLE()

//-----------------------------------------------------------------------------

CGfxHolderPanel::CGfxHolderPanel(wxWindow* parent, CEngineGfxPanel* gfxPanel) :
    wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxNO_BORDER | wxSIZE_AUTO) {
    m_boxSizer = new wxBoxSizer(wxHORIZONTAL);
    m_gfxPanel = gfxPanel;
    m_contextMenu = NULL;
    this->SetSizer(m_boxSizer);
    activateGfxPanel();
}
//-----------------------------------------------------------------------------

CGfxHolderPanel::~CGfxHolderPanel() {
    removeGfxPanel();
    m_gfxPanel = NULL;
    m_contextMenu = NULL;
}
//-----------------------------------------------------------------------------

void CGfxHolderPanel::removeGfxPanel(void) {
    if(m_boxSizer->GetItemCount() > 0 && m_gfxPanel) {
        m_boxSizer->Detach(m_gfxPanel);
        suspendGfxPanel(FG_TRUE);
    } else if(!m_gfxPanel) {
        if(m_boxSizer->GetItemCount())
            m_boxSizer->Clear(false);
    }
}
//-----------------------------------------------------------------------------

void CGfxHolderPanel::activateGfxPanel(void) {
    removeGfxPanel();
    if(m_gfxPanel) {
        m_boxSizer->Add(m_gfxPanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
        showGfxPanel(FG_TRUE);
        suspendGfxPanel(FG_FALSE);
    }
}
//-----------------------------------------------------------------------------

void CGfxHolderPanel::setGfxPanel(CEngineGfxPanel* gfxPanel) {
    removeGfxPanel();
    if(gfxPanel) {
        m_gfxPanel = gfxPanel;
        activateGfxPanel();
    }
}
//-----------------------------------------------------------------------------

void CGfxHolderPanel::showGfxPanel(fgBool toggle) {
    if(m_gfxPanel) {
        m_gfxPanel->Show((bool)toggle);
    }
}
//-----------------------------------------------------------------------------

void CGfxHolderPanel::suspendGfxPanel(fgBool toggle) {
    if(m_gfxPanel) {
        m_gfxPanel->setSuspend(toggle);
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
