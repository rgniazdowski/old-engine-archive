/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/

#include "fgGuiEditableText.h"

using namespace fg;

//------------------------------------------------------------------------------

gui::CEditableText::CEditableText() :
base_type() {
    self_type::setDefaults();
}
//------------------------------------------------------------------------------

gui::CEditableText::~CEditableText() { }
//------------------------------------------------------------------------------

void gui::CEditableText::setDefaults(void) {
    m_type = EDITABLE_TEXT;
    m_typeName = FG_GUI_EDITABLE_TEXT_NAME;
    m_typeTraits = EDITABLE_TEXT | TEXT_AREA | SCROLL_AREA | CONTAINER | WIDGET;
}
//------------------------------------------------------------------------------

gfx::BoundingBox3Df gui::CEditableText::updateBounds(void) {
    return base_type::updateBounds();
}
//------------------------------------------------------------------------------

void gui::CEditableText::refresh(void) {
    base_type::refresh();
}
//------------------------------------------------------------------------------
