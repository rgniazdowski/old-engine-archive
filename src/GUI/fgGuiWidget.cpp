/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#include "fgGuiWidget.h"

/*
 *
 */
fgGuiWidget::fgGuiWidget()
{
}

/*
 *
 */
fgGuiWidget::~fgGuiWidget()
{
}

/*
 *
 */
void fgGuiWidget::setDefaults(void)
{
}

/*
 *
 */
fgVector4f fgGuiWidget::updateSize(void)
{
	fgVector4f returnVec;
	return returnVec;
}

/*
 *
 */
fgVector4f fgGuiWidget::updateSize(const fgVector2f & boundPos, const fgVector2f & boundSize)
{
	fgVector4f returnVec;
	return returnVec;
}

/*
 *
 */
void fgGuiWidget::refresh(void)
{
}

/*
 *
 */
int fgGuiWidget::updateState(void)
{
	return 0;
}
