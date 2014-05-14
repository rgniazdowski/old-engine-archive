/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied and/or 
 * distributed without the express permission
 *******************************************************/

#ifndef _FG_RESOURCE_H
#define _FG_RESOURCE_H

#include "fgCommon.h"

#include <ctime>

#define FG_RESOURCE_PATH_MAX	FG_PATH_MAX

class fgResource 
{
public:
	enum fgResPriorityType
	{
		FG_RES_LOW_PRIORITY = 0,
		FG_RES_MED_PRIORITY,
		FG_RES_HIGH_PRIORITY
	};

	fgResource()			{  clear();  }
	virtual ~fgResource()	{  destroy();  }

	// Clears the class data
	virtual void clear();

	// Create and destroy functions.  Note that the Create() function of the
	// derived class does not have to exactly match the base class.  No assumptions
	// are made regarding parameters.
	virtual bool create()	{  return false;  }
	virtual void destroy()	{}

	// Dispose and recreate must be able to discard and then completely recreate
	// the data contained in the class with no additional parameters
	virtual bool recreate() = 0;
	virtual void dispose() = 0;

	// GetSize() must return the size of the data inside the class, and IsDisposed()
	// let's the manager know if the data exists.
	virtual size_t getSize() = 0;
	virtual bool isDisposed() = 0;

	// These functions set the parameters by which the sorting operator determines
	// in what order resources are discarded
	inline void setPriority(fgResPriorityType priority)		{  m_priority = priority;  }
	inline fgResPriorityType getPriority()					{  return m_priority;  }

	inline void setReferenceCount(unsigned int nCount)	{  m_nRefCount = nCount;  }
	inline unsigned int getReferenceCount()				{  return m_nRefCount;  }
	inline bool isLocked()								{  return (m_nRefCount > 0) ? true : false;  }

	inline void setLastAccess(time_t lastAccess)		{  m_lastAccess = lastAccess;  }
	inline time_t getLastAccess()						{  return m_lastAccess;  }

	// The less-than operator defines how resources get sorted for discarding.
	virtual bool operator < (fgResource& container);

protected:
	fgResPriorityType	m_priority;
	unsigned int		m_nRefCount;
	time_t				m_lastAccess;
	//union {
	char				m_filePath[FG_RESOURCE_PATH_MAX];
	//	std::string m_filePathString;
	//};
};



#endif