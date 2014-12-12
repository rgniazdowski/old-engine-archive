/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_CONSOLE
    #define FG_INC_GUI_CONSOLE

    #include "fgGuiTextArea.h"
    #include "fgGuiWidgetFactoryTypes.h"

/*
 *
 */
class fgGuiConsole : public fgGuiTextArea {
public:
    typedef fgGuiTextArea base_type;
protected:

protected:
    // 
    virtual void setDefaults(void);

public:
    // 
    fgGuiConsole();
    // 
    virtual ~fgGuiConsole();

    FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiConsole);

    // 
    virtual fgBoundingBox3Df updateBounds(void);
    // 
    virtual void refresh(void);

};

#endif /* FG_INC_GUI_CONSOLE */
