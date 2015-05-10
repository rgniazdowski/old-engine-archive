/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGuiWindow.h"

using namespace fg;

//------------------------------------------------------------------------------

gui::CWindow::CWindow() :
base_type() {
    self_type::setDefaults();
}
//------------------------------------------------------------------------------

gui::CWindow::~CWindow() { }
//------------------------------------------------------------------------------

void gui::CWindow::setDefaults(void) {
    m_type = WINDOW;
    m_typeName = FG_GUI_WINDOW_NAME;
    m_typeTraits = WINDOW | CONTAINER | WIDGET;
}
//------------------------------------------------------------------------------

gfx::BoundingBox3Df gui::CWindow::updateBounds(void) {
    return base_type::updateBounds();
}
//------------------------------------------------------------------------------

void gui::CWindow::refresh(void) {
    base_type::refresh();
}
//------------------------------------------------------------------------------
