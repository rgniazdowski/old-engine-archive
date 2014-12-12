/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiWindow.h"

/*
 *
 */
fgGuiWindow::fgGuiWindow() {
    fgGuiWindow::setDefaults();
}

/*
 *
 */
fgGuiWindow::~fgGuiWindow() { }

/*
 *
 */
void fgGuiWindow::setDefaults(void) {
    m_type = FG_GUI_WINDOW;
    m_typeName = FG_GUI_WINDOW_NAME;
    m_typeTraits = FG_GUI_WINDOW | FG_GUI_CONTAINER | FG_GUI_WIDGET;
}

/*
 *
 */
fgBoundingBox3Df fgGuiWindow::updateBounds(void) {
    return fgGuiContainer::updateBounds();
}

/*
 *
 */
void fgGuiWindow::refresh(void) { }
