/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiConsole.h"

/*
 *
 */
fgGuiConsole::fgGuiConsole() :
fgGuiTextArea() {
    fgGuiConsole::setDefaults();
}

/*
 *
 */
fgGuiConsole::~fgGuiConsole() { }

/*
 *
 */
void fgGuiConsole::setDefaults(void) {
    m_type = FG_GUI_CONSOLE;
    m_typeName = FG_GUI_CONSOLE_NAME;
    m_typeTraits = FG_GUI_CONSOLE | FG_GUI_TEXT_AREA | FG_GUI_SCROLL_AREA | FG_GUI_CONTAINER | FG_GUI_WIDGET;
}

/*
 *
 */
fgBoundingBox3Df fgGuiConsole::updateSize(void) {
    return fgGuiTextArea::updateSize();
}

/*
 *
 */
void fgGuiConsole::refresh(void) { }
