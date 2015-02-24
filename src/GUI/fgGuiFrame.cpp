/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiFrame.h"

using namespace fg;

/*
 *
 */
gui::CFrame::CFrame() :
CContainer() {
    CFrame::setDefaults();
}

/*
 *
 */
gui::CFrame::~CFrame() { }

/*
 *
 */
void gui::CFrame::setDefaults(void) {
    m_type = FRAME;
    m_typeName = FG_GUI_FRAME_NAME;
    m_typeTraits = FRAME | CONTAINER | WIDGET;
}

/**
 * 
 * @return 
 */
gfx::BoundingBox3Df gui::CFrame::updateBounds(void) {
    return CContainer::updateBounds();
}

/**
 * 
 */
void gui::CFrame::refresh(void) {
    CContainer::refresh();
}
