/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 *******************************************************/
/**
 * Portions Copyright (C) James Boer, 2000
 */

#ifndef _FG_RESOURCE_MANAGER_H_
#define _FG_RESOURCE_MANAGER_H_

#include "fgSingleton.h"
#include "fgManagerBase.h"
#include "fgResource.h"
#include "fgResourceGroup.h"
#include "Util/fgHandleManager.h"

#include <iostream>

#ifndef FG_RHANDLE
#define FG_RHANDLE fgResourceHandle
#endif

class fgTextureManager;

//
// The resource manager handles all the external resources. It takes care of the memory
// usage and destroys all unused data. Its very convinient as after pushing resource into
// the manager there's no additional
//
class fgResourceManager : public fgManagerBase, public fgSingleton<fgResourceManager>
{
	friend class fgSingleton<fgResourceManager>;
	friend class fgTextureManager;
protected:
	typedef fgHandleManager<fgResource*, FG_RHANDLE>	rmHandleManager;
	typedef rmHandleManager::hmDataVec					rmResVec;
	typedef rmHandleManager::hmDataVec::iterator		rmResVecItor;
	typedef fgArrayVector<FG_RHANDLE>					rmHandleVec;
	typedef rmHandleVec::iterator						rmHandleVecItor;
private:
	// Default constructor for resource manager
	fgResourceManager();
	// Default destructor for resource manager
	virtual ~fgResourceManager();
public:
	// This function will release all data and memory held by resource
	// manager itself (including resources)
	void destroy(void);
	// Reset local parameters
	void clear(void);
public:
	// This will pre-load any required data
	fgBool initialize(void);

	// --------------------------------------------------------------------------
	// Memory management routines

	// Set maximum memory value for the used memory counter
	fgBool setMaximumMemory(size_t nMaxSize);
	// Return the maximum memory value
	size_t getMaximumMemory(void) const		{  return m_nMaximumMemory;  }

	// --------------------------------------------------------------------------
	// Resource map iteration

	// Access functions for cycling through each item.  Giving direct
	// access to the map or iterator causes a stack pointer fault if you access
	// the map across a dll boundary, but it's safe through the wrappers.

	// Go to the begin of resource map iteration
	void goToBegin(void) {
		m_currentResource = getRefResourceVector().begin();
	}
	// Get pointer to the current resource (based on iterator)
	fgResource* getCurrentResource(void)	{
		if(!isValid())
			return NULL;
		else
			return (*m_currentResource);
	}
	// Is current pointer to resource valid?
	fgBool isValid(void)	{
		return ((m_currentResource != getRefResourceVector().end()) ? FG_TRUE : FG_FALSE);
	}
	// Go to the next resource (iterate to next)
	fgBool goToNext() {
		while((*m_currentResource) != NULL) {
			m_currentResource++;
			if(!isValid())
				break;
		}
		return isValid();
	}
	// Find next resource with given criteria (currently resource type)
	fgBool goToNext(fgResourceType resType);
	// Find next resource with given criteria (currently resource type)
	fgBool goToNext(const fgResourceType* resType, int n);
	// Find next resource with given criteria (currently resource type and quality)
	fgBool goToNext(fgResourceType resType, fgQuality quality);

	// -----------------------------------------------------------------------
	// General resource access

	// Allows the resource manager to pre-reserve an amount of memory so
	// an inserted resource does not exceed the maximum allowed memory
	fgBool reserveMemory(size_t nMem);

	// Insert resource group into manager
	// If you pass in the pointer to resource handle, the Resource Manager
	// will provide a unique handle for you.
	fgBool insertResource(FG_RHANDLE& rhUniqueID, fgResource* pResource);

protected:
	// Insert resource group into manager
	fgBool insertResourceGroup(FG_RHANDLE rhUniqueID, fgResource* pResource);
	// Get the reference to the resource map (protected)
	rmResVec& getRefResourceVector(void) {
		return m_resourceHandlesMgr.getRefDataVector();
	}
public:

	// ! Important !
	// removeResource(...) functions are for internal use only
	// meaning that anywhere else in the code it is not allowed to remove
	// resource from the manager without handling the memory release properly

	// Removes an object completely from the manager (does not free memory)
	fgBool removeResource(fgResource* pResource);
	// Removes an object completely from the manager (does not free memory)
	fgBool removeResource(FG_RHANDLE rhUniqueID);

	// Disposes of the resource (frees memory) - does not remove resource from the manager
	fgBool disposeResource(fgResource* pResource);
	// Disposes of the resource (frees memory) - does not remove resource from the manager
	fgBool disposeResource(FG_RHANDLE rhUniqueID);

	// Destroy functions will release all the memory for the resource, delete
	// the object, remove the resource from the manager - resource handle will
	// become invalid - the resource manager doesnt have it anymore in its map

	// Destroys an object and deallocates it's memory. First resource is removed
	// from the resource managers map, existing rhandles will become invalid
	// regardless of the usage in the program - however if the reference count is
	// not zero the resource wont be removed and destroyed
	fgBool destroyResource(fgResource* pResource);
	// Destroys an object and deallocates it's memory. First resource is removed
	// from the resource managers map, existing rhandles will become invalid
	// regardless of the usage in the program - however if the reference count is
	// not zero the resource wont be removed and destroyed
	fgBool destroyResource(FG_RHANDLE rhUniqueID);

	// Using GetResource tells the manager that you are about to access the
	// object.  If the resource has been disposed, it will be recreated
	// before it has been returned.
	fgResource* getResource(FG_RHANDLE rhUniqueID);

	// Using GetResource tells the manager that you are about to access the
	// object.  If the resource has been disposed, it will be recreated
	// before it has been returned.
	fgResource* getResource(std::string& nameTag);

	// Locking the resource ensures that the resource does not get managed by
	// the Resource Manager.  You can use this to ensure that a surface does not
	// get swapped out, for instance.  The resource contains a reference count
	// to ensure that numerous locks can be safely made.
	// #FIXME #TODO #P3 - locking/unlocking is based on counter - DEPRECATED.
	fgResource* lockResource(FG_RHANDLE rhUniqueID);
	// Lock the resource
	fgBool lockResource(fgResource *pResource);
	// Unlocking the object let's the resource manager know that you no longer
	// need exclusive access.  When all locks have been released (the reference
	// count is 0), the object is considered safe for management again and can
	// be swapped out at the manager's discretion.  The object can be referenced
	// either by handle or by the object's pointer.
	// #FIXME #TODO #P3 - locking/unlocking is based on counter - DEPRECATED.
	fgResource* unlockResource(FG_RHANDLE rhUniqueID);
	// Unlock the resource
	fgBool unlockResource(fgResource *pResource);

	// This function can be also used to check if given resource is managed
	fgBool isResourceManaged(fgResource* pResource);

	// This must be called when you wish the manager to check for discardable
	// resources.  Resources will only be swapped out if the maximum allowable
	// limit has been reached, and it will discard them from lowest to highest
	// priority, determined by the resource class's < operator.  Function will
	// fail if requested memory cannot be freed.
	fgBool checkForOverallocation(void);

protected:
	// Refresh allocated memory based on managed resources
	void refreshMemory(void);
	// Set used memory to zero
	inline void resetMemory(void)			{  m_nCurrentUsedMemory = 0; }
	// Add given value to used memory counter
	inline void addMemory(size_t nMem)		{  m_nCurrentUsedMemory += nMem;  }
	// Substract given value from used memory counter
	inline void removeMemory(size_t nMem)	{  m_nCurrentUsedMemory -= nMem;  }

protected:
	// Size of the current used memory by the managed resources
	size_t					m_nCurrentUsedMemory;
	// Value of the maximum supported size of all managed resources
	size_t					m_nMaximumMemory;
	// Is resources are reserved? Used for blocking overallocation check
	fgBool					m_bResourceReserved;
	// Iterator to the current resource (used for browsing through the resources' map)
	rmResVecItor	m_currentResource;

	// Main resource handles manager (managed resources)
	rmHandleManager	m_resourceHandlesMgr;
	// Array holding handles to resource groups
	rmHandleVec m_resourceGroupHandles;

};

// #FIXME - here we go again, with the singletons... :)
#define FG_ResourceManager fgResourceManager::getInstance()

#endif /* _FG_RESOURCE_MANAGER_H_ */
