/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_GUI_EDITABLE_TEXT
    #define FG_INC_GUI_EDITABLE_TEXT

    #include "fgGuiTextArea.h"
    #include "fgGuiWidgetFactoryTypes.h"

/*
 *
 */
class fgGuiEditableText : public fgGuiTextArea {
public:
    typedef fgGuiTextArea base_type;
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
    virtual fgBoundingBox3Df updateBounds(void);
    // 
    virtual void refresh(void);

};

#endif /* FG_INC_GUI_EDITABLE_TEXT */
