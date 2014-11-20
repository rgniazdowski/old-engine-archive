/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_FRAME
    #define FG_INC_GUI_FRAME

    #include "fgGuiContainer.h"
    #include "fgGuiWidgetFactoryTypes.h"

/*
 *
 */
class fgGuiFrame : public fgGuiContainer {
public:
    typedef fgGuiContainer base_type;
protected:

protected:
    // 
    virtual void setDefaults(void);

public:
    // 
    fgGuiFrame();
    // 
    virtual ~fgGuiFrame();

    FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiFrame);

    // 
    virtual fgBoundingBox3Df updateBounds(void);
    // 
    virtual void refresh(void);

};

#endif /* FG_INC_GUI_FRAME */
