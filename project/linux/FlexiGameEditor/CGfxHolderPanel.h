/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#ifndef FG_INC_GFX_HOLDER_PANEL
#define FG_INC_GFX_HOLDER_PANEL
#define FG_INC_GFX_HOLDER_PANEL_BLOCK

#include "fgBool.h"
#include "wx/panel.h"
#include "wx/sizer.h"
#include "wx/menu.h"

class CEngineGfxPanel;

/**
 *
 */
class CGfxHolderPanel : public wxPanel {
public:
    typedef CGfxHolderPanel type;
    typedef CGfxHolderPanel self_type;
    typedef wxPanel base_type;

public:
    CGfxHolderPanel(wxWindow* parent, CEngineGfxPanel* gfxPanel = NULL);
    virtual ~CGfxHolderPanel();

    void removeGfxPanel(void);
    void activateGfxPanel(void);
    void setGfxPanel(CEngineGfxPanel* gfxPanel);
    void showGfxPanel(fgBool toggle = FG_TRUE);
    void suspendGfxPanel(fgBool toggle = FG_TRUE);

    void onContextMenu(wxContextMenuEvent& event);

    void popupGfxContextMenu(const wxPoint& position);

    CEngineGfxPanel* getGfxPanel(void) const {
        return m_gfxPanel;
    }

    wxBoxSizer* getBoxSizer(void) const {
        return m_boxSizer;
    }

    void setContextMenu(wxMenu* contextMenu) {
        m_contextMenu = contextMenu;
    }

    wxMenu* getContextMenu(void) const {
        return m_contextMenu;
    }

    DECLARE_EVENT_TABLE()

private:
    CEngineGfxPanel* m_gfxPanel;
    wxBoxSizer* m_boxSizer;
    wxMenu* m_contextMenu;
};

#undef FG_INC_GFX_HOLDER_PANEL_BLOCK
#endif // FG_INC_GFX_HOLDER_PANEL
