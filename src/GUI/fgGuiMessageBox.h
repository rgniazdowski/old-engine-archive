/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_MESSAGE_BOX_H_
    #define _FG_GUI_MESSAGE_BOX_H_

    #include "fgGuiWindow.h"
    #include "fgGuiWidgetFactoryTypes.h"

    #define FG_GUI_MESSAGE_BOX		0x00008000
    #define FG_GUI_MESSAGE_BOX_NAME	"MessageBox"

/*
 *
 */
class fgGuiMessageBox : public fgGuiWindow {
private:
protected:

protected:
    // 
    virtual void setDefaults(void);

public:
    // 
    fgGuiMessageBox();
    // 
    virtual ~fgGuiMessageBox();

    FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiMessageBox);

    // 
    virtual fgBoundingBox3Df updateBounds(void);
    // 
    virtual void refresh(void);

};

#endif /* _FG_GUI_MESSAGE_BOX_H_ */ 
