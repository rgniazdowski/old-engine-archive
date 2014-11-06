/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef _FG_GUI_LABEL_H_
    #define _FG_GUI_LABEL_H_

    #include "fgGuiWidget.h"
    #include "fgGuiWidgetFactoryTypes.h"

/*
 *
 */
class fgGuiLabel : public fgGuiWidget {
public:
    typedef fgGuiWidget base_type;
protected:
    /// 
    std::string m_text;

protected:
    // 
    virtual void setDefaults(void);

public:
    // 
    fgGuiLabel();
    // 
    virtual ~fgGuiLabel();

    FG_GUI_WIDGET_FACTORY_CREATE_FUNCTION(fgGuiLabel);

    // 
    virtual fgBoundingBox3Df updateBounds(void);
};

#endif /* _FG_GUI_LABEL_H_ */
