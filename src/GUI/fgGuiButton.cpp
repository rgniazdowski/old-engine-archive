/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiButton.h"

/*
 *
 */
fgGuiButton::fgGuiButton() :
fgGuiWidget(),
m_label(NULL) {
    fgGuiButton::setDefaults();
}

/*
 *
 */
fgGuiButton::~fgGuiButton() { }

/*
 *
 */
void fgGuiButton::setDefaults(void) {
    m_type = FG_GUI_BUTTON;
    m_typeName = FG_GUI_BUTTON_NAME;
    m_typeTraits = FG_GUI_BUTTON | FG_GUI_WIDGET;
}

/*
 *
 */
fgBoundingBox3Df fgGuiButton::updateSize(void) {
    return fgGuiWidget::updateSize();
}

/*
 *
 */
void fgGuiButton::refresh(void) { 
    fgGuiWidget::refresh();
}
