/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_WINDOW_H_
    #define _FG_GUI_WINDOW_H_

    #include "fgGuiContainer.h"
    #include "fgGuiWidgetFactoryTypes.h"

    #define FG_GUI_WINDOW		0x00004000
    #define FG_GUI_WINDOW_NAME	"Window"

/*
 *
 */
class fgGuiWindow : public fgGuiContainer {
private:
protected:

protected:
    // 
    virtual void setDefaults(void);

public:
    // 
    fgGuiWindow();
    // 
    virtual ~fgGuiWindow();

    FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiWindow);

    // 
    virtual fgBoundingBox3Df& updateSize(void);
    // 
    virtual void refresh(void);

};

#endif /* _FG_GUI_WINDOW_H_ */
