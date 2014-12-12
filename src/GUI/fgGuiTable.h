/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_TABLE
    #define FG_INC_GUI_TABLE

    #include "fgGuiContainer.h"
    #include "fgGuiWidgetFactoryTypes.h"

class fgGuiTable : public fgGuiContainer {
public:
    typedef fgGuiContainer base_type;
protected:

protected:
    // 
    virtual void setDefaults(void);

public:
    // 
    fgGuiTable();
    // 
    virtual ~fgGuiTable();

    FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiTable);

    // 
    virtual fgBoundingBox3Df updateBounds(void);
    // 
    virtual void refresh(void);

};

#endif /* FG_INC_GUI_TABLE */
