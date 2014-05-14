/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
 *******************************************************/

#include "fgResource.h"

/*
 *
 */
void fgResource::clear()
{
	m_priority = FG_RES_MED_PRIORITY;
	m_nRefCount = 0;
	m_lastAccess = 0;
}

/*
 *
 */
bool fgResource::operator < (fgResource& container)
{
	if(getPriority() < container.getPriority())
		return true;
	else if(getPriority() > container.getPriority())
		return false;
	else
	{
		if(m_lastAccess < container.getLastAccess())
			return true;
		else if(m_lastAccess > container.getLastAccess())
			return false;
		else
		{
			if(getSize() < container.getSize())
				return true;
			else
				return false;
		}
	}
	return false;
}