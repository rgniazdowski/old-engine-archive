/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiMessageBox.h"

/*
 *
 */
fgGuiMessageBox::fgGuiMessageBox() {
    fgGuiMessageBox::setDefaults();
}

/*
 *
 */
fgGuiMessageBox::~fgGuiMessageBox() { }

/*
 *
 */
void fgGuiMessageBox::setDefaults(void) {
    m_type = FG_GUI_MESSAGE_BOX;
    m_typeName = FG_GUI_MESSAGE_BOX_NAME;
    m_typeTraits = FG_GUI_MESSAGE_BOX | FG_GUI_WINDOW | FG_GUI_CONTAINER | FG_GUI_WIDGET;
}

/*
 *
 */
fgBoundingBox3Df fgGuiMessageBox::updateSize(void) {
    return fgGuiWindow::updateSize();
}

/*
 *
 */
void fgGuiMessageBox::refresh(void) { }
