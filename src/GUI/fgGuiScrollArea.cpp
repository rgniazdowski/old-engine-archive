/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiScrollArea.h"

/*
 *
 */
fgGuiScrollArea::fgGuiScrollArea() :
fgGuiContainer() {
    fgGuiScrollArea::setDefaults();
}

/*
 *
 */
fgGuiScrollArea::~fgGuiScrollArea() { }

/*
 *
 */
void fgGuiScrollArea::setDefaults(void) {
    m_type = FG_GUI_SCROLL_AREA;
    m_typeName = FG_GUI_SCROLL_AREA_NAME;
    m_typeTraits = FG_GUI_SCROLL_AREA | FG_GUI_CONTAINER | FG_GUI_WIDGET;
}

/*
 *
 */
fgBoundingBox3Df fgGuiScrollArea::updateSize(void) {
    return fgGuiContainer::updateSize();
}

/*
 *
 */
void fgGuiScrollArea::refresh(void) { }
