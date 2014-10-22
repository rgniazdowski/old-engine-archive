/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiPopup.h"

/*
 *
 */
fgGuiPopup::fgGuiPopup() {
    fgGuiPopup::setDefaults();
}

/*
 *
 */
fgGuiPopup::~fgGuiPopup() { }

/*
 *
 */
void fgGuiPopup::setDefaults(void) {
    m_type = FG_GUI_POPUP;
    m_typeName = FG_GUI_POPUP_NAME;
    m_typeTraits = FG_GUI_POPUP | FG_GUI_WINDOW | FG_GUI_CONTAINER | FG_GUI_WIDGET;
}

/*
 *
 */
fgBoundingBox3Df fgGuiPopup::updateSize(void) {
    return fgGuiWindow::updateSize();
}

/*
 *
 */
void fgGuiPopup::refresh(void) { }
