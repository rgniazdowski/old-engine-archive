/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_MESSAGE_BOX
    #define FG_INC_GUI_MESSAGE_BOX

    #include "fgGuiWindow.h"
    #include "fgGuiWidgetFactoryTypes.h"

/*
 *
 */
class fgGuiMessageBox : public fgGuiWindow {
public:
    typedef fgGuiWindow base_type;
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

#endif /* FG_INC_GUI_MESSAGE_BOX */ 
