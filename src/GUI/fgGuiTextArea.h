/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_TEXT_AREA_H_
    #define _FG_GUI_TEXT_AREA_H_

    #include "fgGuiScrollArea.h"
    #include "fgGuiWidgetFactoryTypes.h"

/**
 * 
 */
class fgGuiTextArea : public fgGuiScrollArea {
public:
    typedef fgGuiScrollArea base_type;
protected:

protected:
    // 
    virtual void setDefaults(void);

public:
    // 
    fgGuiTextArea();
    // 
    virtual ~fgGuiTextArea();

    FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiTextArea);

    // 
    virtual fgBoundingBox3Df updateBounds(void);
    // 
    virtual void refresh(void);

};

#endif /* _FG_GUI_TEXT_AREA_H_ */
