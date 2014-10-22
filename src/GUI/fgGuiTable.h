/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_TABLE_H_
    #define _FG_GUI_TABLE_H_

    #include "fgGuiContainer.h"
    #include "fgGuiWidgetFactoryTypes.h"

    #define FG_GUI_TABLE		0x00080000
    #define FG_GUI_TABLE_NAME	"Table"

class fgGuiTable : public fgGuiContainer {
private:
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
    virtual fgBoundingBox3Df updateSize(void);
    // 
    virtual void refresh(void);

};

#endif /* _FG_GUI_TABLE_H_ */
