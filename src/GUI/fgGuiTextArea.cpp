/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiTextArea.h"

/*
 *
 */
fgGuiTextArea::fgGuiTextArea() :
fgGuiScrollArea() {
    fgGuiTextArea::setDefaults();
}

/*
 *
 */
fgGuiTextArea::~fgGuiTextArea() { }

/*
 *
 */
void fgGuiTextArea::setDefaults(void) {
    m_type = FG_GUI_TEXT_AREA;
    m_typeName = FG_GUI_TEXT_AREA_NAME;
    m_typeTraits = FG_GUI_TEXT_AREA | FG_GUI_SCROLL_AREA | FG_GUI_CONTAINER | FG_GUI_WIDGET;
}

/*
 *
 */
fgBoundingBox3Df fgGuiTextArea::updateBounds(void) {
    return fgGuiScrollArea::updateBounds();
}

/*
 *
 */
void fgGuiTextArea::refresh(void) { }
