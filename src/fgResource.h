/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_RESOURCE_H_
#define _FG_RESOURCE_H_

// A resource handle is define as an unsigned integer
#ifndef FG_RHANDLE
#define FG_RHANDLE unsigned int
#endif

#ifndef FG_INVALID_RHANDLE
// All bits filled defines an invalid resource handle
#define FG_INVALID_RHANDLE			0xFFFFFFFF
#define FG_IS_INVALID_RHANDLE(_rh)	((_rh == FG_INVALID_RHANDLE) ? true : false)
#define FG_IS_VALID_RHANDLE(_rh)	((_rh == FG_INVALID_RHANDLE) ? false : true)
#endif

#include "fgCommon.h"

#include <ctime>
#include <cstring>

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

	// Clears the class data, this actually does not free allocated memory, just resets base class attributes
	virtual void clear();

	// Create and destroy functions.  Note that the create() function of the
	// derived class does not have to exactly match the base class.  No assumptions
	// are made regarding parameters.
	// create() function should simply be overloaded to call any proper loading function,
	// which will load/interpret data from file in ROM and place it in RAM memory.
	virtual bool create()	{  return false;  }
	virtual void destroy()	{ dispose(); clear(); }

	// Dispose and recreate must be able to discard and then completely recreate
	// the data contained in the class with no additional parameters
	// This functions should NOT be overloaded to have different number of parameters.
	virtual bool recreate() = 0;
	// Dispose completely of the all loaded data, free all memory
	virtual void dispose() = 0;

	// Rturn the size of the data actually loaded inside the class
	virtual size_t getSize() = 0;
	// Return true if the data exists (it's loaded and ready)
	virtual bool isDisposed() = 0;

	// These functions set the parameters by which the sorting operator determines
	// in what order resources are discarded

	// Set the resource priority
	inline void setPriority(fgResPriorityType priority)		{  m_priority = priority;  }
	// Get the resource priority
	inline fgResPriorityType getPriority()					{  return m_priority;  }

	inline void setReferenceCount(unsigned int nCount)	{  m_nRefCount = nCount;  }
	inline unsigned int getReferenceCount()				{  return m_nRefCount;  }
	inline bool isLocked()								{  return (m_nRefCount > 0) ? true : false;  }

	inline void setLastAccess(time_t lastAccess)		{  m_lastAccess = lastAccess;  }
	inline time_t getLastAccess()						{  return m_lastAccess;  }

	// Set file path to this resource
	inline void setFilePath(char *path) {
		strncpy(m_filePath, path, FG_RESOURCE_PATH_MAX-1);
	}

	// The less-than operator defines how resources get sorted for discarding.
	virtual bool operator < (fgResource& container);

protected:
	// Increase the reference count
	inline void upRef(void)		{ m_nRefCount++; }
	// Decrease the reference count
	inline void downRef(void)	{ if(m_nRefCount > 0) m_nRefCount--; }

protected:
	// Unique handle number (Resource Handle)
	FG_RHANDLE			m_handle;
	// Priority of this resource
	fgResPriorityType	m_priority;
	// Number of references to this resource
	unsigned int		m_nRefCount;
	// Time of last access, may become handy
	time_t				m_lastAccess;
	// File path (can be relative) to file holding data
	char				m_filePath[FG_RESOURCE_PATH_MAX];
	// Is the resource loaded and ready to be used in program?
	bool				m_isReady;

};



#endif