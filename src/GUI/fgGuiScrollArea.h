/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_SCROLL_AREA_H_
    #define _FG_GUI_SCROLL_AREA_H_

    #include "fgGuiContainer.h"
    #include "fgGuiWidgetFactoryTypes.h"

    #define FG_GUI_SCROLL_AREA		0x00000200
    #define FG_GUI_SCROLL_AREA_NAME	"ScrollArea"

class fgGuiScrollArea : public fgGuiContainer {
private:
protected:

protected:
    // 
    virtual void setDefaults(void);

public:
    // 
    fgGuiScrollArea();
    // 
    virtual ~fgGuiScrollArea();

    FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiScrollArea);

    // 
    virtual fgBoundingBox3Df& updateSize(void);
    // 
    virtual void refresh(void);

};

#endif /* _FG_GUI_SCROLL_AREA_H_ */
