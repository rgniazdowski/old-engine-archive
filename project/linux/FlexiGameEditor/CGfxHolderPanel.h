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

class CEngineGfxCanvas;

/**
 *
 */
class CGfxHolderPanel : public wxPanel {
public:
    typedef CGfxHolderPanel type;
    typedef CGfxHolderPanel self_type;
    typedef wxPanel base_type;

public:
    /**
     *
     * @param parent
     * @param gfxPanel
     */
    CGfxHolderPanel(wxWindow* parent, CEngineGfxCanvas* gfxPanel = NULL);
    /**
     *
     */
    virtual ~CGfxHolderPanel();

    /**
     *
     */
    void removeGfxCanvas(void);
    /**
     *
     */
    void activateGfxCanvas(void);

    void OnKeyPressed(wxKeyEvent& event);
    void OnKeyReleased(wxKeyEvent& event);

    /**
     *
     * @param
     */
    void setGfxCanvas(CEngineGfxCanvas* gfxCanvas);
    /**
     *
     * @param toggle
     */
    void showGfxCanvas(fgBool toggle = FG_TRUE);
    /**
     *
     * @param toggle
     */
    void suspendGfxCanvas(fgBool toggle = FG_TRUE);

    /**
     *
     * @param event
     */
    void onContextMenu(wxContextMenuEvent& event);

    /**
     *
     * @param position
     */
    void popupGfxContextMenu(const wxPoint& position);
    /**
     *
     * @return
     */
    CEngineGfxCanvas* getGfxCanvas(void) const {
        return m_gfxCanvas;
    }
    /**
     *
     * @return
     */
    wxBoxSizer* getBoxSizer(void) const {
        return m_boxSizer;
    }
    /**
     *
     * @param contextMenu
     */
    void setContextMenu(wxMenu* contextMenu) {
        m_contextMenu = contextMenu;
    }
    /**
     *
     * @return
     */
    wxMenu* getContextMenu(void) const {
        return m_contextMenu;
    }

    DECLARE_EVENT_TABLE()

private:
    ///
    CEngineGfxCanvas* m_gfxCanvas;
    ///
    wxBoxSizer* m_boxSizer;
    ///
    wxMenu* m_contextMenu;
};

    #undef FG_INC_GFX_HOLDER_PANEL_BLOCK
#endif /* FG_INC_GFX_HOLDER_PANEL */
