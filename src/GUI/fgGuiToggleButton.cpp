/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiToggleButton.h"

using namespace fg;

gui::CToggleButton::CToggleButton() {
    CToggleButton::setDefaults();
}

gui::CToggleButton::~CToggleButton() { }

void gui::CToggleButton::setDefaults(void) {
    m_type = TOGGLE_BUTTON;
    m_typeName = FG_GUI_TOGGLE_BUTTON_NAME;
    m_typeTraits = TOGGLE_BUTTON | BUTTON | WIDGET;
}
