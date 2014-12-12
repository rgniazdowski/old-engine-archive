/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_POPUP
    #define FG_INC_GUI_POPUP

    #include "fgGuiWindow.h"
    #include "fgGuiWidgetFactoryTypes.h"

/*
 *
 */
class fgGuiPopup : public fgGuiWindow {
public:
    typedef fgGuiWindow base_type;
protected:

protected:
    // 
    virtual void setDefaults(void);

public:
    // 
    fgGuiPopup();
    // 
    virtual ~fgGuiPopup();

    FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiPopup);

    // 
    virtual fgBoundingBox3Df updateBounds(void);
    // 
    virtual void refresh(void);

};

#endif /* FG_INC_GUI_POPUP */
