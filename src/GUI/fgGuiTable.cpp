/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiTable.h"

using namespace fg;

/*
 *
 */
gui::CTable::CTable() {
    fg::gui::CTable::setDefaults();
}

/*
 *
 */
gui::CTable::~CTable() { }

/**
 *
 */
void gui::CTable::setDefaults(void) {
    m_type = TABLE;
    m_typeName = FG_GUI_TABLE_NAME;
    m_typeTraits = TABLE | CONTAINER | WIDGET;
}

/**
 * 
 * @return 
 */
gfx::BoundingBox3Df gui::CTable::updateBounds(void) {
    return base_type::updateBounds();
}

/**
 *
 */
void gui::CTable::refresh(void) {
    base_type::refresh();
}
