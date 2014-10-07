/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiEditableText.h"

/*
 *
 */
fgGuiEditableText::fgGuiEditableText()
{
	fgGuiEditableText::setDefaults();
}

/*
 *
 */
fgGuiEditableText::~fgGuiEditableText()
{
}

/*
 *
 */
void fgGuiEditableText::setDefaults(void)
{
	m_type = FG_GUI_EDITABLE_TEXT;
	m_typeName = FG_GUI_EDITABLE_TEXT_NAME;
	m_typeTraits = FG_GUI_EDITABLE_TEXT | FG_GUI_TEXT_AREA | FG_GUI_SCROLL_AREA | FG_GUI_CONTAINER | FG_GUI_WIDGET;
}

/*
 *
 */
fgBoundingBox3Df& fgGuiEditableText::updateSize(void)
{
	return fgGuiTextArea::updateSize();
}

/*
 *
 */
void fgGuiEditableText::refresh(void)
{
}
