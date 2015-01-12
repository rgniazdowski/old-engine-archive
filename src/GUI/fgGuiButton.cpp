/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiButton.h"

using namespace fg;

/**
 *
 */
gui::CButton::CButton() :
CWidget(),
m_label(NULL) {
    CButton::setDefaults();
}

/**
 *
 */
gui::CButton::~CButton() { }

/**
 *
 */
void gui::CButton::setDefaults(void) {
    m_type = BUTTON;
    m_typeName = FG_GUI_BUTTON_NAME;
    m_typeTraits = BUTTON | WIDGET;
}

/**
 * 
 * @return 
 */
gfx::BoundingBox3Df gui::CButton::updateBounds(void) {
    return base_type::updateBounds();
}

/**
 *
 */
void gui::CButton::refresh(void) {
    base_type::refresh();
}
