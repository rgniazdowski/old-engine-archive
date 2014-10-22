/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiToggleButton.h"

/*
 *
 */
fgGuiToggleButton::fgGuiToggleButton() {
    fgGuiToggleButton::setDefaults();
}

/*
 *
 */
fgGuiToggleButton::~fgGuiToggleButton() { }

/*
 *
 */
void fgGuiToggleButton::setDefaults(void) {
    m_type = FG_GUI_TOGGLE_BUTTON;
    m_typeName = FG_GUI_TOGGLE_BUTTON_NAME;
    m_typeTraits = FG_GUI_TOGGLE_BUTTON | FG_GUI_BUTTON | FG_GUI_WIDGET;
}

/*
 *
 */
fgBoundingBox3Df fgGuiToggleButton::updateSize(void) {
    return fgGuiButton::updateSize();
}

/*
 *
 */
void fgGuiToggleButton::refresh(void) { }
