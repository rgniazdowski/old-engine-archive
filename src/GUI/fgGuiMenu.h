/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_MENU
    #define FG_INC_GUI_MENU

    #include <map>

    #include "fgCommon.h"
    #include "fgGuiContainer.h"
    #include "fgGuiWidgetFactoryTypes.h"

/**
 * 
 */
class fgGuiMenu : public fgGuiContainer {
public:
    typedef fgGuiContainer base_type;
private:
    ///
    fgBool m_isMainMenu;

protected:
    // 
    virtual void setDefaults(void);

public:
    
    using fgGuiWidget::updateBounds;
    
    // 
    fgGuiMenu();
    // 
    virtual ~fgGuiMenu();

    FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiMenu);

    //
    virtual void setFlags(const std::string& flags);

    // 
    virtual fgBoundingBox3Df updateBounds(void);
    // 
    virtual void refresh(void);

    //
    fgBool isMainMenu(void) const {
        return m_isMainMenu;
    }
};

#endif /* FG_INC_GUI_MENU */
