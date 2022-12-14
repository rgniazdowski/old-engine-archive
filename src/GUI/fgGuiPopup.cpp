/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGuiPopup.h"

using namespace fg;

//------------------------------------------------------------------------------

gui::CPopup::CPopup() :
base_type() {
    self_type::setDefaults();
}
//------------------------------------------------------------------------------

gui::CPopup::~CPopup() { }
//------------------------------------------------------------------------------

void gui::CPopup::setDefaults(void) {
    m_type = POPUP;
    m_typeName = FG_GUI_POPUP_NAME;
    m_typeTraits = POPUP | WINDOW | CONTAINER | WIDGET;
}
//------------------------------------------------------------------------------

gfx::BoundingBox3Df gui::CPopup::updateBounds(void) {
    return base_type::updateBounds();
}
//------------------------------------------------------------------------------

void gui::CPopup::refresh(void) {
    base_type::refresh();
}
//------------------------------------------------------------------------------
