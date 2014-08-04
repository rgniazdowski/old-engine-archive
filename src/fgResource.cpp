/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgResource.h"

/*
 *
 */
void fgResource::clear(void)
{
	m_handle = FG_INVALID_RHANDLE;
	m_resType = FG_RESOURCE_INVALID;
	m_priority = FG_RES_PRIORITY_LOW;
	m_nRefCount = 0;
	m_lastAccess = 0;
	m_isReady = false;
	m_size = 0;
	m_filePath.clear();
	FG_WriteLog("fgResource::clear(void);");
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