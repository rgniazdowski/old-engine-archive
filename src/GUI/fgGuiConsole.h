/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_CONSOLE_H_
    #define _FG_GUI_CONSOLE_H_

    #include "fgGuiTextArea.h"
    #include "fgGuiWidgetFactoryTypes.h"

    #define FG_GUI_CONSOLE		0x00002000
    #define FG_GUI_CONSOLE_NAME		"Console"

/*
 *
 */
class fgGuiConsole : public fgGuiTextArea {
private:
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
    virtual fgBoundingBox3Df updateSize(void);
    // 
    virtual void refresh(void);

};

#endif /* _FG_GUI_CONSOLE_H_ */
