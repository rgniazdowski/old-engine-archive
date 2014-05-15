/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#ifndef _FG_RESOURCE_MANAGER_H_
#define _FG_RESOURCE_MANAGER_H_

#include "fgSingleton.h"
#include "fgResource.h"

#include <map>

// A resource handle is define as an unsigned integer
#ifndef FG_RHANDLE
#define FG_RHANDLE unsigned int
#endif

// All bits filled defines an invalid resource handle
#define FG_INVALID_RHANDLE			0xFFFFFFFF
#define FG_IS_INVALID_RHANDLE(_rh)	((_rh == FG_INVALID_RHANDLE) ? true : false)
#define FG_IS_VALID_RHANDLE(_rh)	((_rh == FG_INVALID_RHANDLE) ? false : true)

enum fgResourceType {
	FG_RESOURCE_INVALID,
	FG_RESOURCE_SOUND,
	FG_RESOURCE_MUSIC,
	FG_RESOURCE_3D_MODEL,
	FG_RESOURCE_TEXTURE,
	FG_RESOURCE_SAVE_FILE,
	FG_RESOURCE_GUI_STRUCTURE_SHEET,
	FG_RESOURCE_GUI_STYLE_SHEET,
	FG_RESOURCE_SHADER,
	FG_RESOURCE_SCENE,
	FG_RESOURCE_GROUP_CONFIG,
	FG_RESOURCE_CONFIG,
	FG_RESOURCE_SCRIPT,

	FG_RESOURCE_VARIA,
	FG_RESOURCE_BINARY,

	FG_NUM_RESOURCE_TYPES
};

// This class allows an STL object to compare the objects instead of
// comparing the value of the objects' pointers.
template <class T>
class ptr_less
{
public:
	inline bool operator ()(T left, T right)
	{  return ((*left) < (*right));  }
};

// This class allows an STL object to compare the objects instead of
// comparing the value of the objects' pointers.
template <class T>
class ptr_greater
{
public:
	inline bool operator ()(T left, T right)
	{  return !((*left) < (*right));  }
};

typedef std::map<FG_RHANDLE, fgResource*>	fgResourceMap;
typedef fgResourceMap::iterator				fgResourceMapItor;
typedef fgResourceMap::value_type			fgResourceMapPair;

class fgResourceManager : public fgSingleton<fgResourceManager>
{
	friend class fgSingleton<fgResourceManager>;
public:
	
	fgResourceManager()				{  clear();  }
	virtual ~fgResourceManager()	{  destroy();  }

	void clear();
	
	bool create(unsigned int nMaxSize);
	void destroy();

	// --------------------------------------------------------------------------
	// Memory management routines

	bool setMaximumMemory(size_t nMem);
	size_t getMaximumMemory()		{  return m_nMaximumMemory;  }
	
	// --------------------------------------------------------------------------
	// Resource map iteration

	// Access functions for cycling through each item.  Giving direct
	// access to the map or iterator causes a stack pointer fault if you access
	// the map across a dll boundary, but it's safe through the wrappers.  
	inline void goToBegin()
	{  m_currentResource = m_resourceMap.begin(); }
	
	inline fgResource* getCurrentResource()
	{  return (*m_currentResource).second;  }
	
	inline bool isValid()
	{  return (m_currentResource != m_resourceMap.end()) ? true : false;  }

	inline bool goToNext()
	{  m_currentResource++;  return isValid();  }
	
	// -----------------------------------------------------------------------
	// General resource access

	// Allows the resource manager to pre-reserve an amount of memory so
	// an inserted resource does not exceed the maximum allowed memory
	bool reserveMemory(size_t nMem);

	// If you pass in the address of a resource handle, the Resource Manager
	// will provide a unique handle for you.  
	bool insertResource(FG_RHANDLE* rhUniqueID, fgResource* pResource);
	bool insertResource(FG_RHANDLE rhUniqueID, fgResource* pResource);

	// Removes an object completely from the manager. 
	bool removeResource(fgResource* pResource);
	bool removeResource(FG_RHANDLE rhUniqueID);

	// Destroys an object and deallocates it's memory
	bool destroyResource(fgResource* pResource);
	bool destroyResource(FG_RHANDLE rhUniqueID);

	// Using GetResource tells the manager that you are about to access the
	// object.  If the resource has been disposed, it will be recreated 
	// before it has been returned. 
	fgResource* getResource(FG_RHANDLE rhUniqueID);

	// Locking the resource ensures that the resource does not get managed by
	// the Resource Manager.  You can use this to ensure that a surface does not
	// get swapped out, for instance.  The resource contains a reference count
	// to ensure that numerous locks can be safely made.
	fgResource* lockResource(FG_RHANDLE rhUniqueID);

	// Unlocking the object let's the resource manager know that you no longer
	// need exclusive access.  When all locks have been released (the reference
	// count is 0), the object is considered safe for management again and can
	// be swapped out at the manager's discretion.  The object can be referenced
	// either by handle or by the object's pointer. 
	int unlockResource(FG_RHANDLE rhUniqueID);
	int unlockResource(fgResource* pResource);

	// Retrieve the stored handle based on a pointer to the resource.  Note that 
	// it's assumed that there are no duplicate pointers, as it will return the
	// first match found.
	FG_RHANDLE findResourceHandle(fgResource* pResource);

	// This must be called when you wish the manager to check for discardable
	// resources.  Resources will only be swapped out if the maximum allowable
	// limit has been reached, and it will discard them from lowest to highest
	// priority, determined by the resource class's < operator.  Function will
	// fail if requested memory cannot be freed.
	bool checkForOverallocation();

protected:

	// Internal functions
	inline void addMemory(size_t nMem)		{  m_nCurrentUsedMemory += nMem;  }
	inline void removeMemory(size_t nMem)	{  m_nCurrentUsedMemory -= nMem;  }
	FG_RHANDLE getNextResHandle()			{  return --m_rhNextResHandle;  }

protected:
	FG_RHANDLE				m_rhNextResHandle;
	size_t					m_nCurrentUsedMemory;
	size_t					m_nMaximumMemory;
	bool					m_bResourceReserved;
	fgResourceMapItor		m_currentResource;
	fgResourceMap			m_resourceMap;
};

// #FIXME - again, with the singletons...
#define FG_ResourceManager fgResourceManager::getInstance()

#endif