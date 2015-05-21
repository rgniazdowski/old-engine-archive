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

namespace fg {
    namespace event {
        static KeyVirtualCode
        KeyTranslate[] = {
                          FG_KEY_NULL, // WXK_START = 300, // -300 -> 0
                          FG_KEY_NULL, // WXK_LBUTTON, // 1
                          FG_KEY_NULL, // WXK_RBUTTON, // 2
                          FG_KEY_CANCEL, // WXK_CANCEL, // 3
                          FG_KEY_NULL, // WXK_MBUTTON, // 4
                          FG_KEY_CLEAR, // WXK_CLEAR, // 5
                          FG_KEY_LSHIFT, // WXK_SHIFT, // 6
                          FG_KEY_LALT, // WXK_ALT, // 7
                          FG_KEY_LCTRL, // WXK_CONTROL, // 8
                          FG_KEY_MENU, // WXK_MENU, // 9
                          FG_KEY_PAUSE, // WXK_PAUSE, // 10
                          FG_KEY_CAPSLOCK, // WXK_CAPITAL, // 11
                          FG_KEY_END, // WXK_END, // 12
                          FG_KEY_HOME, // WXK_HOME, // 13
                          FG_KEY_LEFT, // WXK_LEFT, // 14
                          FG_KEY_UP, // WXK_UP, // 15
                          FG_KEY_RIGHT, // WXK_RIGHT, // 16
                          FG_KEY_DOWN, // WXK_DOWN, // 17
                          FG_KEY_SELECT, // WXK_SELECT, // 18
                          FG_KEY_PRINTSCREEN, // WXK_PRINT, // 19
                          FG_KEY_EXECUTE, // WXK_EXECUTE, // 20
                          FG_KEY_PRINTSCREEN, // WXK_SNAPSHOT, // 21
                          FG_KEY_INSERT, // WXK_INSERT, // 22
                          FG_KEY_HELP, // WXK_HELP, // 23
                          FG_KEY_NUM_0, // WXK_NUMPAD0, // 24
                          FG_KEY_NUM_1, // WXK_NUMPAD1, // 25
                          FG_KEY_NUM_2, // WXK_NUMPAD2, // 26
                          FG_KEY_NUM_3, // WXK_NUMPAD3, // 27
                          FG_KEY_NUM_4, // WXK_NUMPAD4, // 28
                          FG_KEY_NUM_5, // WXK_NUMPAD5, // 29
                          FG_KEY_NUM_6, // WXK_NUMPAD6, // 30
                          FG_KEY_NUM_7, // WXK_NUMPAD7, // 31
                          FG_KEY_NUM_8, // WXK_NUMPAD8, // 32
                          FG_KEY_NUM_9, // WXK_NUMPAD9, // 33
                          FG_KEY_NULL, // WXK_MULTIPLY, // 34
                          FG_KEY_NULL, // WXK_ADD, // 35
                          FG_KEY_NULL, // WXK_SEPARATOR, // 36
                          FG_KEY_NULL, // WXK_SUBTRACT, // 37
                          FG_KEY_NULL, // WXK_DECIMAL, // 38
                          FG_KEY_NULL, // WXK_DIVIDE, // 39
                          FG_KEY_F1, // WXK_F1, // 40
                          FG_KEY_F2, // WXK_F2, // 41
                          FG_KEY_F3, // WXK_F3, // 42
                          FG_KEY_F4, // WXK_F4, // 43
                          FG_KEY_F5, // WXK_F5, // 44
                          FG_KEY_F6, // WXK_F6, // 45
                          FG_KEY_F7, // WXK_F7, // 46
                          FG_KEY_F8, // WXK_F8, // 47
                          FG_KEY_F9, // WXK_F9, // 48
                          FG_KEY_F10, // WXK_F10, // 49
                          FG_KEY_F11, // WXK_F11, // 50
                          FG_KEY_F12, // WXK_F12, // 51
                          FG_KEY_F13, // WXK_F13, // 52
                          FG_KEY_F14, // WXK_F14, // 53
                          FG_KEY_F15, // WXK_F15, // 54
                          FG_KEY_F16, // WXK_F16, // 55
                          FG_KEY_F17, // WXK_F17, // 56
                          FG_KEY_F18, // WXK_F18, // 57
                          FG_KEY_F19, // WXK_F19, // 58
                          FG_KEY_F20, // WXK_F20, // 59
                          FG_KEY_F21, // WXK_F21, // 60
                          FG_KEY_F22, // WXK_F22, // 61
                          FG_KEY_F23, // WXK_F23, // 62
                          FG_KEY_F24, // WXK_F24, // 63
                          FG_KEY_NULL, // WXK_NUMLOCK, // 64
                          FG_KEY_SCROLL_LOCK, // WXK_SCROLL, // 65
                          FG_KEY_PAGEUP, // WXK_PAGEUP, // 66
                          FG_KEY_PAGEDOWN, // WXK_PAGEDOWN, // 67
                          FG_KEY_NULL, // WXK_NUMPAD_SPACE, // 68
                          FG_KEY_NULL, // WXK_NUMPAD_TAB, // 69
                          FG_KEY_NUM_ENTER, // WXK_NUMPAD_ENTER, // 70
                          FG_KEY_NULL, // WXK_NUMPAD_F1, // 71
                          FG_KEY_NULL, // WXK_NUMPAD_F2, // 72
                          FG_KEY_NULL, // WXK_NUMPAD_F3, // 73
                          FG_KEY_NULL, // WXK_NUMPAD_F4, // 74
                          FG_KEY_NULL, // WXK_NUMPAD_HOME, // 75
                          FG_KEY_NULL, // WXK_NUMPAD_LEFT, // 76
                          FG_KEY_NULL, // WXK_NUMPAD_UP, // 77
                          FG_KEY_NULL, // WXK_NUMPAD_RIGHT, // 78
                          FG_KEY_NULL, // WXK_NUMPAD_DOWN, // 79
                          FG_KEY_NULL, // WXK_NUMPAD_PAGEUP, // 80
                          FG_KEY_NULL, // WXK_NUMPAD_PAGEDOWN, // 81
                          FG_KEY_NULL, // WXK_NUMPAD_END, // 82
                          FG_KEY_NULL, // WXK_NUMPAD_BEGIN, // 83
                          FG_KEY_INSERT, // WXK_NUMPAD_INSERT, // 84
                          FG_KEY_NULL, // WXK_NUMPAD_DELETE, // 85
                          FG_KEY_EQUALS, // WXK_NUMPAD_EQUAL, // 86
                          FG_KEY_NULL, // WXK_NUMPAD_MULTIPLY, // 87
                          FG_KEY_NULL, // WXK_NUMPAD_ADD, // 88
                          FG_KEY_NULL, // WXK_NUMPAD_SEPARATOR, // 89
                          FG_KEY_NULL, // WXK_NUMPAD_SUBTRACT, // 90
                          FG_KEY_NULL, // WXK_NUMPAD_DECIMAL, // 91
                          FG_KEY_NULL, // WXK_NUMPAD_DIVIDE, // 92

                          FG_KEY_LGUI, // WXK_WINDOWS_LEFT, // 93
                          FG_KEY_RGUI, // WXK_WINDOWS_RIGHT, // 94
                          FG_KEY_CONTEXT, // WXK_WINDOWS_MENU // 95
                          FG_KEY_NULL, // 96
                          FG_KEY_NULL, // 97
                          FG_KEY_NULL, // 98
                          FG_KEY_NULL, // 99
                          FG_KEY_NULL, // 100
        };
    } // namespace event
} // namespace fg

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

    //this->Bind(wxEVT_KEY_DOWN, &CGfxHolderPanel::OnKeyPressed, this);
    //this->Bind(wxEVT_KEY_UP, &CGfxHolderPanel::OnKeyReleased, this);
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

#endif
    if(this->m_gfxCanvas) {
        if(this->m_gfxCanvas->isSuspend())
            return;
        fg::CEngineMain* pEngineMain = m_gfxCanvas->getEngineMain();
        if(!pEngineMain)
            return;
        int keyCode = 0;
        wxChar uc = event.GetUnicodeKey();
        if(uc != WXK_NONE) {
            // It's a "normal" character. Notice that this includes
            // control characters in 1..31 range, e.g. WXK_RETURN or
            // WXK_BACK, so check for them explicitly.
            if(uc < 128) {                
                keyCode = std::tolower((int)uc);
            }
        } else {
            // No Unicode equivalent - need to translate.
            keyCode = event.GetKeyCode();
            if(keyCode >= 300 && keyCode < 400) {
                keyCode = (int)fg::event::KeyTranslate[keyCode - 300];
            } else {
                keyCode = 0;
            }
        }
        if(keyCode != 0) {
            pEngineMain->getInputHandler()->addKeyPressed((fg::event::KeyVirtualCode)keyCode);
            if(keyCode == fg::event::FG_KEY_LALT)
                pEngineMain->getInputHandler()->toggleKeyboardMod(fg::event::FG_MOD_RALT, FG_TRUE);
            if(keyCode == fg::event::FG_KEY_LSHIFT)
                pEngineMain->getInputHandler()->toggleKeyboardMod(fg::event::FG_MOD_RSHIFT, FG_TRUE);
            if(keyCode == fg::event::FG_KEY_LCTRL)
                pEngineMain->getInputHandler()->toggleKeyboardMod(fg::event::FG_MOD_RCTRL, FG_TRUE);
            if(keyCode == fg::event::FG_KEY_LGUI)
                pEngineMain->getInputHandler()->toggleKeyboardMod(fg::event::FG_MOD_RGUI, FG_TRUE);
        }
        FG_LOG_DEBUG("WX: GfxHolderPanel: Key pressed event: id:%d, char[%c]",
                     keyCode, (char)keyCode);
    }
}
//-----------------------------------------------------------------------------

void CGfxHolderPanel::OnKeyReleased(wxKeyEvent& event) {
    if(this->m_gfxCanvas) {
        if(this->m_gfxCanvas->isSuspend())
            return;
        fg::CEngineMain* pEngineMain = m_gfxCanvas->getEngineMain();
        if(!pEngineMain)
            return;
        int keyCode = 0;
        wxChar uc = event.GetUnicodeKey();
        if(uc != WXK_NONE) {
            if(uc < 128) {
                keyCode = std::tolower((int)uc);
            }
        } else {
            // No Unicode equivalent - need to translate.
            keyCode = event.GetKeyCode();
            if(keyCode >= 300 && keyCode < 400) {
                keyCode = (int)fg::event::KeyTranslate[keyCode - 300];
            } else {
                keyCode = 0;
            }
        }
        if(keyCode != 0) {
            pEngineMain->getInputHandler()->addKeyUp((fg::event::KeyVirtualCode)keyCode);
            if(keyCode == fg::event::FG_KEY_LALT)
                pEngineMain->getInputHandler()->toggleKeyboardMod(fg::event::FG_MOD_RALT, FG_FALSE);
            if(keyCode == fg::event::FG_KEY_LSHIFT)
                pEngineMain->getInputHandler()->toggleKeyboardMod(fg::event::FG_MOD_RSHIFT, FG_FALSE);
            if(keyCode == fg::event::FG_KEY_LCTRL)
                pEngineMain->getInputHandler()->toggleKeyboardMod(fg::event::FG_MOD_RCTRL, FG_FALSE);
            if(keyCode == fg::event::FG_KEY_LGUI)
                pEngineMain->getInputHandler()->toggleKeyboardMod(fg::event::FG_MOD_RGUI, FG_FALSE);
        }
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
