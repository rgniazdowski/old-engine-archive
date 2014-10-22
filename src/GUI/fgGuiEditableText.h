/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_EDITABLE_TEXT_H_
    #define _FG_GUI_EDITABLE_TEXT_H_

    #include "fgGuiTextArea.h"
    #include "fgGuiWidgetFactoryTypes.h"

    #define FG_GUI_EDITABLE_TEXT		0x00000800
    #define FG_GUI_EDITABLE_TEXT_NAME	"EditableText"

/*
 *
 */
class fgGuiEditableText : public fgGuiTextArea {
private:
protected:

protected:
    // 
    virtual void setDefaults(void);

public:
    // 
    fgGuiEditableText();
    // 
    virtual ~fgGuiEditableText();

    FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiEditableText);

    // 
    virtual fgBoundingBox3Df updateSize(void);
    // 
    virtual void refresh(void);

};

#endif /* _FG_GUI_EDITABLE_TEXT_H_ */
