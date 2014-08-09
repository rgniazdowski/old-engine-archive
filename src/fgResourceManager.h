/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
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
#include "fgResourceGroup.h"

#include <iostream>
#include <hash_map>
//#include <limits>

// A resource handle is define as an unsigned integer
#ifndef FG_RHANDLE
#define FG_RHANDLE unsigned int
#endif

#ifndef FG_INVALID_RHANDLE
// All bits filled defines an invalid resource handle
#define FG_INVALID_RHANDLE			0xFFFFFFFFUL
#define FG_IS_INVALID_RHANDLE(_rh)	((_rh == FG_INVALID_RHANDLE) ? true : false)
#define FG_IS_VALID_RHANDLE(_rh)	((_rh == FG_INVALID_RHANDLE) ? false : true)
#endif

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

typedef std::hash_map<FG_RHANDLE, fgResource*>	fgResourceMap;
typedef fgResourceMap::iterator				fgResourceMapItor;
typedef fgResourceMap::value_type			fgResourceMapPair;

// The resource manager handles all the external resources. It takes care of the memory
// usage and destroys all unused data. Its very convinient as after pushing resource into
// the manager there's no additional
class fgResourceManager : public fgSingleton<fgResourceManager>
{
	friend class fgSingleton<fgResourceManager>;
private:
	// Default constructor for resource manager
	fgResourceManager()				{  clear();  }
	// Default destructor for resource manager
	virtual ~fgResourceManager()	{  destroy();  }
public:
	// This function will release all data and memory held by resource
	// manager itself (including resources)
	void destroy(void);
	// Reset local parameters
	void clear(void);
public:
	// This will pre-load any required data
	bool initialize(void);
	// Creates the resource manager
	bool create(unsigned int nMaxSize);

	// --------------------------------------------------------------------------
	// Memory management routines

	// Set maximum memory value for the used memory counter
	bool setMaximumMemory(size_t nMem);
	// Return the maximum memory value
	size_t getMaximumMemory(void) const		{  return m_nMaximumMemory;  }
	
	// --------------------------------------------------------------------------
	// Resource map iteration

	// Access functions for cycling through each item.  Giving direct
	// access to the map or iterator causes a stack pointer fault if you access
	// the map across a dll boundary, but it's safe through the wrappers. 

	// Go to the begin of resource map iteration
	inline void goToBegin(void)
	{  m_currentResource = m_resourceMap.begin(); }
	// Get pointer to the current resource (based on iterator)
	inline fgResource* getCurrentResource(void) const
	{  return (*m_currentResource).second;  }
	// Is current pointer to resource valid?
	inline bool isValid(void) const
	{  return (m_currentResource != m_resourceMap.end()) ? true : false;  }
	// Go to the next resource (iterate to next)
	inline bool goToNext()
	{  m_currentResource++;  return isValid();  }
	
	// -----------------------------------------------------------------------
	// General resource access

	// Allows the resource manager to pre-reserve an amount of memory so
	// an inserted resource does not exceed the maximum allowed memory
	bool reserveMemory(size_t nMem);

	// Insert resource group into manager
	// If you pass in the pointer to resource handle, the Resource Manager 
	// will provide a unique handle for you.  
	bool insertResource(FG_RHANDLE* rhUniqueID, fgResource* pResource);
	// Insert resource into manager with predefined resource handle ID
	bool insertResource(FG_RHANDLE rhUniqueID, fgResource* pResource);

protected:
	// Insert resource group into manager
	bool insertResourceGroup(FG_RHANDLE* rhUniqueID, fgResource* pResource);
	// Insert resource group into manager with predefined resource handle ID
	bool insertResourceGroup(FG_RHANDLE rhUniqueID, fgResource* pResource);
public:

	// ! Important !
	// removeResource(...) functions are for internal use only
	// meaning that anywhere else in the code it is not allowed to remove
	// resource from the manager without handling the memory release properly

	// Removes an object completely from the manager (does not free memory)
	bool removeResource(fgResource* pResource);
	// Removes an object completely from the manager (does not free memory)
	bool removeResource(FG_RHANDLE rhUniqueID);

	// Disposes of the resource (frees memory) - does not remove resource from the manager
	bool disposeResource(fgResource* pResource);
	// Disposes of the resource (frees memory) - does not remove resource from the manager
	bool disposeResource(FG_RHANDLE rhUniqueID);

	// Destroy functions will release all the memory for the resource, delete
	// the object, remove the resource from the manager - resource handle will
	// become invalid - the resource manager doesnt have it anymore in its map

	// Destroys an object and deallocates it's memory. First resource is removed
	// from the resource managers map, existing rhandles will become invalid
	// regardless of the usage in the program - however if the reference count is
	// not zero the resource wont be removed and destroyed
	bool destroyResource(fgResource* pResource);
	// Destroys an object and deallocates it's memory. First resource is removed
	// from the resource managers map, existing rhandles will become invalid
	// regardless of the usage in the program - however if the reference count is
	// not zero the resource wont be removed and destroyed
	bool destroyResource(FG_RHANDLE rhUniqueID);

	// Using GetResource tells the manager that you are about to access the
	// object.  If the resource has been disposed, it will be recreated 
	// before it has been returned. 
	fgResource* getResource(FG_RHANDLE rhUniqueID);

	// Locking the resource ensures that the resource does not get managed by
	// the Resource Manager.  You can use this to ensure that a surface does not
	// get swapped out, for instance.  The resource contains a reference count
	// to ensure that numerous locks can be safely made.
	// #FIXME #TODO #P3 - locking/unlocking is based on counter - DEPRECATED.
	fgResource* lockResource(FG_RHANDLE rhUniqueID);
	// Unlocking the object let's the resource manager know that you no longer
	// need exclusive access.  When all locks have been released (the reference
	// count is 0), the object is considered safe for management again and can
	// be swapped out at the manager's discretion.  The object can be referenced
	// either by handle or by the object's pointer. 
	// #FIXME #TODO #P3 - locking/unlocking is based on counter - DEPRECATED.
	fgResource* unlockResource(FG_RHANDLE rhUniqueID);

	// Retrieve the stored handle based on a pointer to the resource.  Note that 
	// it's assumed that there are no duplicate pointers, as it will return the
	// first match found.
	// This function can be also used to check if given resource is managed
	FG_RHANDLE findResourceHandle(fgResource* pResource);

	// This must be called when you wish the manager to check for discardable
	// resources.  Resources will only be swapped out if the maximum allowable
	// limit has been reached, and it will discard them from lowest to highest
	// priority, determined by the resource class's < operator.  Function will
	// fail if requested memory cannot be freed.
	bool checkForOverallocation(void);
	
protected:
	// Refresh allocated memory based on managed resources
	void refreshMemory(void);
	// Set used memory to zero
	inline void resetMemory(void)			{  m_nCurrentUsedMemory = 0; }
	// Add given value to used memory counter
	inline void addMemory(size_t nMem)		{  m_nCurrentUsedMemory += nMem;  }
	// Substract given value from used memory counter
	inline void removeMemory(size_t nMem)	{  m_nCurrentUsedMemory -= nMem;  }
	// Return next valid (not used) resource handle #FIXME
	FG_RHANDLE getNextResHandle(void)			{  return --m_rhNextResHandle;  }

protected:
	// Value of the next valid resource handle (used while adding new resource to manage)
	FG_RHANDLE				m_rhNextResHandle;
	// Size of the current used memory by the managed resources
	size_t					m_nCurrentUsedMemory;
	// Value of the maximum supported size of all managed resources
	size_t					m_nMaximumMemory;
	// Is resources are reserved? Used for blocking overallocation check
	bool					m_bResourceReserved;
	// Iterator to the current resource (used for browsing through the resources' map)
	fgResourceMapItor		m_currentResource;
	// Main resource map (managed resources)
	fgResourceMap			m_resourceMap;
	// Resource group map (managed resource groups)
	fgResourceMap			m_resourceGroupMap;
};

// #FIXME - here we go again, with the singletons... :)
#define FG_ResourceManager fgResourceManager::getInstance()

#endif
