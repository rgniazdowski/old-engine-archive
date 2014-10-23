/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiFrame.h"

/*
 *
 */
fgGuiFrame::fgGuiFrame() :
fgGuiContainer() {
    fgGuiFrame::setDefaults();
}

/*
 *
 */
fgGuiFrame::~fgGuiFrame() { }

/*
 *
 */
void fgGuiFrame::setDefaults(void) {
    m_type = FG_GUI_FRAME;
    m_typeName = FG_GUI_FRAME_NAME;
    m_typeTraits = FG_GUI_FRAME | FG_GUI_CONTAINER | FG_GUI_WIDGET;
}

/*
 *
 */
fgBoundingBox3Df fgGuiFrame::updateBounds(void) {
    return fgGuiContainer::updateBounds();
}

/*
 *
 */
void fgGuiFrame::refresh(void) { 
    fgGuiContainer::refresh();
}
