/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiLabel.h"

/*
 *
 */
fgGuiLabel::fgGuiLabel() : 
fgGuiWidget() {
    fgGuiLabel::setDefaults();
}

/*
 *
 */
fgGuiLabel::~fgGuiLabel() { }

/*
 *
 */
void fgGuiLabel::setDefaults(void) {
    m_type = FG_GUI_LABEL;
    m_typeName = FG_GUI_LABEL_NAME;
    m_typeTraits = FG_GUI_LABEL | FG_GUI_WIDGET;
}

/*
 *
 */
fgBoundingBox3Df fgGuiLabel::updateSize(void) {
    return fgGuiWidget::updateSize();
}
