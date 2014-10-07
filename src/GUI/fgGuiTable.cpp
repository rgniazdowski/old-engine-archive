/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiTable.h"

/*
 *
 */
fgGuiTable::fgGuiTable()
{
	fgGuiTable::setDefaults();
}

/*
 *
 */
fgGuiTable::~fgGuiTable()
{
}

/*
 *
 */
void fgGuiTable::setDefaults(void)
{
	m_type = FG_GUI_TABLE;
	m_typeName = FG_GUI_TABLE_NAME;
	m_typeTraits = FG_GUI_TABLE | FG_GUI_CONTAINER | FG_GUI_WIDGET;
}

/*
 *
 */
fgBoundingBox3Df& fgGuiTable::updateSize(void)
{
	return fgGuiContainer::updateSize();
}

/*
 *
 */
void fgGuiTable::refresh(void)
{
}
