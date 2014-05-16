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
void fgResourceGroup::clear()
{
	fgResource::clear();
	m_rHandles.clear();
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
size_t fgResourceGroup::getSize() 
{
	return 0;
}

/*
 *
 */
bool fgResourceGroup::isDisposed()
{
	return false;
}
