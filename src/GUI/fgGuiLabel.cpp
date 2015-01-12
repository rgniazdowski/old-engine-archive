/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiLabel.h"

using namespace fg;

/**
 *
 */
gui::CLabel::CLabel() :
CWidget() {
    CLabel::setDefaults();
}

/**
 *
 */
gui::CLabel::~CLabel() { }

/**
 *
 */
void gui::CLabel::setDefaults(void) {
    m_type = LABEL;
    m_typeName = FG_GUI_LABEL_NAME;
    m_typeTraits = LABEL | WIDGET;
}

/**
 * 
 * @return 
 */
fgBoundingBox3Df gui::CLabel::updateBounds(void) {
    return base_type::updateBounds();
}
