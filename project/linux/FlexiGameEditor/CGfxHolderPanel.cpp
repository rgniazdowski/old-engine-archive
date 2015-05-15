/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgEngineMain.h"

#include "CGfxHolderPanel.h"
#include "CEngineGfxCanvas.h"

BEGIN_EVENT_TABLE(CGfxHolderPanel, wxPanel)
EVT_CONTEXT_MENU(CGfxHolderPanel::onContextMenu)
END_EVENT_TABLE()
//-----------------------------------------------------------------------------

CGfxHolderPanel::CGfxHolderPanel(wxWindow* parent, CEngineGfxCanvas* gfxCanvas) :
wxPanel(parent, wxID_ANY,
        wxDefaultPosition, wxDefaultSize,
        wxTAB_TRAVERSAL | wxNO_BORDER | wxSIZE_AUTO | wxWANTS_CHARS) {
    m_boxSizer = new wxBoxSizer(wxHORIZONTAL);
    m_gfxCanvas = gfxCanvas;
    m_contextMenu = NULL;
    this->SetSizer(m_boxSizer);
    activateGfxCanvas();

    this->Bind(wxEVT_KEY_DOWN, &CGfxHolderPanel::OnKeyPressed, this);
    this->Bind(wxEVT_KEY_UP, &CGfxHolderPanel::OnKeyReleased, this);
}
//-----------------------------------------------------------------------------

CGfxHolderPanel::~CGfxHolderPanel() {
    removeGfxCanvas();
    m_gfxCanvas = NULL;
    m_contextMenu = NULL;
}
//-----------------------------------------------------------------------------

void CGfxHolderPanel::OnKeyPressed(wxKeyEvent& event) {
#if 0
    wxChar uc = event.GetUnicodeKey();
        if(uc != WXK_NONE) {
            // It's a "normal" character. Notice that this includes
            // control characters in 1..31 range, e.g. WXK_RETURN or
            // WXK_BACK, so check for them explicitly.
            if(uc >= 32) {
               // FG_LOG_DEBUG("You pressed '%c'", uc);
            } else {
                // It's a control character
            }
        } else // No Unicode equivalent.
        {
            // It's a special key, deal with all the known ones:
            switch(event.GetKeyCode()) {
                case WXK_LEFT:
                case WXK_RIGHT:

                    break;
                case WXK_F1:

                    break;
            }
        }
#endif
    if(this->m_gfxCanvas) {
        fg::CEngineMain* pEngineMain = m_gfxCanvas->getEngineMain();
        if(!pEngineMain)
            return;
        int keyCode = event.GetKeyCode();
        pEngineMain->getInputHandler()->addKeyPressed(keyCode);
        FG_LOG_DEBUG("WX: GfxHolderPanel: Key pressed event: id:%d, char[%c]",
                     keyCode, (char)keyCode);
    }
}
//-----------------------------------------------------------------------------

void CGfxHolderPanel::OnKeyReleased(wxKeyEvent& event) {
    if(this->m_gfxCanvas) {
        fg::CEngineMain* pEngineMain = m_gfxCanvas->getEngineMain();
        if(!pEngineMain)
            return;
        int keyCode = event.GetKeyCode();
        pEngineMain->getInputHandler()->addKeyUp(keyCode);
        FG_LOG_DEBUG("WX: GfxHolderPanel: Key released event: id:%d, char[%c]",
                     keyCode, (char)keyCode);
    }
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
