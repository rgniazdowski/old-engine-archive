/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiMessageBox.h"

using namespace fg;

/**
 *
 */
gui::CMessageBox::CMessageBox() :
base_type() {
    CMessageBox::setDefaults();
}

/**
 *
 */
gui::CMessageBox::~CMessageBox() { }

/**
 *
 */
void gui::CMessageBox::setDefaults(void) {
    m_type = MESSAGE_BOX;
    m_typeName = FG_GUI_MESSAGE_BOX_NAME;
    m_typeTraits = MESSAGE_BOX | WINDOW | CONTAINER | WIDGET;
}

/**
 * 
 * @return 
 */
gfx::BoundingBox3Df gui::CMessageBox::updateBounds(void) {
    return CWindow::updateBounds();
}

/*
 *
 */
void gui::CMessageBox::refresh(void) {
    base_type::refresh();
}
