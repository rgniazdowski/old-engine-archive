/***************************************************************
 * Name:      FlexiGameEditorApp.h
 * Purpose:   Defines Application Class
 * Author:    Radoslaw Gniazdowski (contact@flexigame.com)
 * Created:   2015-04-21
 * Copyright: Radoslaw Gniazdowski (http://flexigame.com)
 * License:
 **************************************************************/

#ifndef FG_INC_FLEXI_GAME_EDITOR_APP
    #define FG_INC_FLEXI_GAME_EDITOR_APP
    #define FG_INC_FLEXI_GAME_EDITOR_APP_BLOCK

    #include "fgBool.h"

    #include <wx/app.h>

/**
 *
 */
class FlexiGameEditorApp : public wxApp {
public:
    virtual bool OnInit();

private:
    fgBool m_isInit;
};



    #undef FG_INC_FLEXI_GAME_EDITOR_APP_BLOCK
#endif /* FG_INC_FLEXI_GAME_EDITOR_APP */
