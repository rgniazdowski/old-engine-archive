/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiProgressBar.h"

/*
 *
 */
fgGuiProgressBar::fgGuiProgressBar() {
    fgGuiProgressBar::setDefaults();
}

/*
 *
 */
fgGuiProgressBar::~fgGuiProgressBar() { }

/*
 *
 */
void fgGuiProgressBar::setDefaults(void) {
    m_type = FG_GUI_PROGRESS_BAR;
    m_typeName = FG_GUI_PROGRESS_BAR_NAME;
    m_typeTraits = FG_GUI_PROGRESS_BAR | FG_GUI_WIDGET;
}

/*
 *
 */
fgBoundingBox3Df fgGuiProgressBar::updateBounds(void) {
    return fgGuiWidget::updateBounds();
}

/*
 *
 */
void fgGuiProgressBar::refresh(void) { }
