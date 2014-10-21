/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiLoader.h"

/*
 *
 */
fgGuiLoader::fgGuiLoader() :
fgGuiWidget() {
    fgGuiLoader::setDefaults();
}

/*
 *
 */
fgGuiLoader::~fgGuiLoader() { }

/*
 *
 */
void fgGuiLoader::setDefaults(void) {
    m_type = FG_GUI_LOADER;
    m_typeName = FG_GUI_LOADER_NAME;
    m_typeTraits = FG_GUI_LOADER | FG_GUI_WIDGET;
}

/*
 *
 */
fgBoundingBox3Df& fgGuiLoader::updateSize(void) {
    return fgGuiWidget::updateSize();
}

/*
 *
 */
void fgGuiLoader::refresh(void) {
    fgGuiWidget::refresh();
}
