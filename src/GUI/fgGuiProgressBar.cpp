/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiProgressBar.h"

using namespace fg;

/*
 *
 */
gui::CProgressBar::CProgressBar() {
    CProgressBar::setDefaults();
}

/*
 *
 */
gui::CProgressBar::~CProgressBar() { }

/*
 *
 */
void gui::CProgressBar::setDefaults(void) {
    m_type = PROGRESS_BAR;
    m_typeName = FG_GUI_PROGRESS_BAR_NAME;
    m_typeTraits = PROGRESS_BAR | WIDGET;
}

/**
 * 
 * @return 
 */
gfx::BoundingBox3Df gui::CProgressBar::updateBounds(void) {
    return base_type::updateBounds();
}

/**
 *
 */
void gui::CProgressBar::refresh(void) { 
    base_type::refresh();
}
