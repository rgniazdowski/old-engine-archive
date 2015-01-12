/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <contact@flexigame.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiLoader.h"

using namespace fg;

/**
 *
 */
gui::CLoaderSub::CLoaderSub() :
CWidget() {
    CLoaderSub::setDefaults();
}

/**
 *
 */
gui::CLoaderSub::~CLoaderSub() { }

/**
 *
 */
void gui::CLoaderSub::setDefaults(void) {
    m_type = LOADER;
    m_typeName = FG_GUI_LOADER_NAME;
    m_typeTraits = LOADER | WIDGET;
}

/**
 * 
 * @return 
 */
fgBoundingBox3Df gui::CLoaderSub::updateBounds(void) {
    return base_type::updateBounds();
}

/**
 *
 */
void gui::CLoaderSub::refresh(void) {
    base_type::refresh();
}
