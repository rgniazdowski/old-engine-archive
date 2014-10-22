/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_MENU_H_
    #define _FG_GUI_MENU_H_

    #include <map>

    #include "fgCommon.h"
    #include "fgGuiContainer.h"
    #include "fgGuiWidgetFactoryTypes.h"

    #define FG_GUI_MENU         0x00000040
    #define FG_GUI_MENU_NAME    "Menu"

/**
 * 
 */
class fgGuiMenu : public fgGuiContainer {
private:
    ///
    fgBool m_isMainMenu;
    
protected:
    // 
    virtual void setDefaults(void);

public:
    // 
    fgGuiMenu();
    // 
    virtual ~fgGuiMenu();

    FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiMenu);

    //
    virtual void setFlags(const std::string& flags);
    
    // 
    virtual fgBoundingBox3Df updateSize(void);
    // 
    virtual void refresh(void);

    //
    fgBool isMainMenu(void) const {
        return m_isMainMenu;
    }
};

#endif /* _FG_GUI_MENU_H_ */
