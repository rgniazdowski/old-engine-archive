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

class fgGuiScrollArea : public fgGuiContainer {
public:
    typedef fgGuiContainer base_type;
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
    virtual fgBoundingBox3Df updateBounds(void);
    // 
    virtual void refresh(void);

};

#endif /* _FG_GUI_SCROLL_AREA_H_ */
