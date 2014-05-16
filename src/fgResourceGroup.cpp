/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgResourceGroup.h"

/*
 *
 */
void fgResourceGroup::clear(void)
{
	fgResource::clear();
	m_rHandles.clear_optimised();
	m_resourceFiles.clear_optimised();
}

/*
 *
 */
bool fgResourceGroup::create()
{
	return true;
}

/*
 *
 */
void fgResourceGroup::destroy()
{
	
}

/*
 *
 */
bool fgResourceGroup::recreate()
{
	return true;
}

/*
 *
 */
void fgResourceGroup::dispose()
{

}

/*
 *
 */
bool fgResourceGroup::isDisposed(void) const
{
	return false;
}
