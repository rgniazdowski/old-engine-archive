/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/

#include "fgResourceManager.h"
#include "fgDirent.h"

#include <queue>

template <>
bool fgSingleton<fgResourceManager>::instanceFlag = false;

template <>
fgResourceManager *fgSingleton<fgResourceManager>::instance = NULL;

/*
 *
 */
void fgResourceManager::clear(void)
{
	m_resourceMap.clear();
	m_resourceGroupMap.clear();
	m_rhNextResHandle = FG_INVALID_RHANDLE;
	m_nCurrentUsedMemory = 0;
	m_nMaximumMemory = 0;
	m_bResourceReserved = false;
	m_currentResource = m_resourceMap.end();
}

/*
 *
 */
bool fgResourceManager::create(unsigned int nMaxSize)
{
	clear();
	setMaximumMemory(nMaxSize);
	return true;
}

/*
 *
 */
void fgResourceManager::destroy(void)
{
	for(fgResourceMapItor itor = m_resourceGroupMap.begin(); itor != m_resourceGroupMap.end(); ++itor)
	{
		itor->second->ZeroLock();
		itor->second->dispose();
		fgArrayVector<fgResource *>& resInGrp = ((fgResourceGroup *)itor->second)->getRefResourceFiles();
		for(fgResourceGroup::ResVecIt it = resInGrp.begin(); it != resInGrp.end(); it++) {
			destroyResource((*it));
		}
		itor->second->clear();
		destroyResource(itor->second);
	}
	//m_resourceGroupMap.clear();

	//FG_WriteLog(">>>>> fgResourceManager::destroy(void);");
	for(fgResourceMapItor itor = m_resourceMap.begin(); itor != m_resourceMap.end(); ++itor)
	{
		//if(!((*itor).second)->isLocked())
		{
			itor->second->dispose();
			//FG_WriteLog(">>>>> fgResourceManager: deleting from resource map value:
			//id=%ud; name='%s';", (*itor).first, typeid((*itor).second).name());
			delete ((*itor).second);
		}
	}
	clear();
}

/*
 * Function pre loads any required data (configs, metadata, etc)
 */
bool fgResourceManager::initialize(void)
{
	// First of all load any resource group configs,
	// file extension is *.rgrp and it's a xml file.
	fgDirent *datadir = new fgDirent();
	datadir->readDirectory(".\\");
	const char *filename = NULL;
	fgArrayVector<std::string> resGroupFiles;
	// #FIXME - well this looks kinda bad, probably loading
	// resource groups files should look different - must be
	// more universal - platform independent, check for 
	// correct paths in the environment, etc.
	while((filename = datadir->getNextFile()) != NULL)
	{
		// #FIXME - this should check for string length errors (?)
		const char *ext = FG_FileExt(filename);
		if(!ext)
			continue;
		if(strlen(ext) == 4)
			if(strcmp(ext, "rgrp") == 0)
				resGroupFiles.push_back(std::string(filename));
	}
	delete datadir;
	filename = NULL;

	if(resGroupFiles.size() == 0) {
		return false; // #TODO proper error handling
	}

	for(unsigned int i=0;i<resGroupFiles.size();i++)
	{
		FG_RHANDLE grpUniqueID; // #FIXME - should resource manager hold separate array for res groups IDS ? oh my ...
		filename = resGroupFiles[i].c_str();
		fgResourceGroup *resGroup = new fgResourceGroup();
		resGroup->setFilePath(filename); // #TODO this will not always look like this - requires full path
		resGroup->preLoadConfig();
		// Resource group is inserted as normal resource 
		// Resources within resource group are treated as one
		// so even if resources in main map are being checked
		// for overallocation, they will not be purged if the
		// resource group is still being used (and locked)
		// Locking resource group - locks all the resources 
		insertResource(&grpUniqueID, resGroup);
		// There is a separate holder for resource group
		insertResourceGroup(&grpUniqueID, resGroup);
		fgArrayVector<fgResource *>& resInGrp = resGroup->getRefResourceFiles();
		for(fgResourceGroup::ResVecIt it = resInGrp.begin(); it != resInGrp.end(); it++) {
			FG_RHANDLE resUniqueID;
			insertResource(&resUniqueID, (*it));
		}
		resGroup->refreshArrays();
		FG_WriteLog("LOG INSERTED RESOURCE GROUP"); // #FIXME
	}
	resGroupFiles.clear();
	return true;
}

/*
 *
 */
bool fgResourceManager::setMaximumMemory(size_t nMem)
{
	m_nMaximumMemory = nMem;
	return checkForOverallocation();
}

/*
 *
 */
bool fgResourceManager::reserveMemory(size_t nMem)
{
	addMemory(nMem);
	if(!checkForOverallocation())
		return false;
	m_bResourceReserved = true;
	return true;
}

/*
 *
 */
bool fgResourceManager::insertResource(FG_RHANDLE* rhUniqueID, fgResource* pResource)
{
	// Get the next unique resource ID for this catalog
	*rhUniqueID = getNextResHandle();
	return insertResource(*rhUniqueID, pResource);
}

/*
 *
 */
bool fgResourceManager::insertResource(FG_RHANDLE rhUniqueID, fgResource* pResource)
{
	fgResourceMapItor itor = m_resourceMap.find(rhUniqueID);
	if(itor != m_resourceMap.end()) {
		// ID has already been allocated as a resource
		return false;
	}
	// Insert the resource into the current catalog's map
	m_resourceMap.insert(fgResourceMapPair(rhUniqueID, pResource));
	// Get the memory and add it to the catalog total.  Note that we only have
	// to check for memory overallocation if we haven't preallocated memory
	if(!m_bResourceReserved)
	{
		addMemory(pResource->getSize());
		// check to see if any overallocation has taken place
		if(!checkForOverallocation())
			return false;
	}
	else
		m_bResourceReserved = false;
	pResource->setResourceHandle(rhUniqueID);
	// return the id to the user for their use and return success
	return true;
}

/*
 *
 */
bool fgResourceManager::insertResourceGroup(FG_RHANDLE* rhUniqueID, fgResource* pResource)
{
	// Get the next unique resource ID for this catalog
	*rhUniqueID = getNextResHandle();
	return insertResourceGroup(*rhUniqueID, pResource);
}

/*
 *
 */
bool fgResourceManager::insertResourceGroup(FG_RHANDLE rhUniqueID, fgResource* pResource)
{
	fgResourceMapItor itor = m_resourceGroupMap.find(rhUniqueID);
	if(itor != m_resourceGroupMap.end()) {
		// ID has already been allocated as a resource
		return false;
	}
	// Insert the resource into the current catalog's map
	m_resourceGroupMap.insert(fgResourceMapPair(rhUniqueID, pResource));
	pResource->setResourceHandle(rhUniqueID);
	// return the id to the user for their use and return success
	return true;
}

/*
 * Removes an object completely from the manager. 
 */
bool fgResourceManager::removeResource(FG_RHANDLE rhUniqueID)
{
	// try to find the resource with the specified id
	fgResourceMapItor itor = m_resourceMap.find(rhUniqueID);
	if(itor == m_resourceMap.end())
		// Could not find resource to remove
		return false;
	// if the resource was found, check to see that it's not locked
	if(itor->second->isLocked())
		// Can't remove a locked resource
		return false;
	// Get the memory and subtract it from the manager total
	removeMemory(itor->second->getSize());
	// remove the requested resource (erase removes the pointers from the container, but does not call delete)
	m_resourceMap.erase(itor);

	return true;
}

/*
 * Removes an object completely from the manager.
 * Does not free memory (held by the allocated object).
 */
bool fgResourceManager::removeResource(fgResource* pResource)
{
	// try to find the resource with the specified resource
	fgResourceMapItor itor;
	for(itor = m_resourceMap.begin(); itor != m_resourceMap.end(); ++itor)
	{
		if(itor->second == pResource)
			break;
	}
	if(itor == m_resourceMap.end())
		// Could not find resource to remove. 
		return false;
	// if the resource was found, check to see that it's not locked
	if(itor->second->isLocked())
		// Can't remove a locked resource
		return false;
	// Get the memory and subtract it from the manager total
	removeMemory(pResource->getSize());
	// remove the requested resource
	m_resourceMap.erase(itor);

	return true;
}

/*
 * Disposes of the resource (frees memory) - does not remove resource from the manager
 */
bool fgResourceManager::disposeResource(FG_RHANDLE rhUniqueID)
{
	// try to find the resource with the specified id
	fgResourceMapItor itor = m_resourceMap.find(rhUniqueID);
	if(itor == m_resourceMap.end()) {
		// Could not find resource to remove
		return false;
	}
	// if the resource was found, check to see that it's not locked
	if(itor->second->isLocked())
		// Can't remove a locked resource
		return false;
	unsigned int nDisposalSize = itor->second->getSize();
	itor->second->dispose();
	if(itor->second->isDisposed()) {
		// Get the memory and subtract it from the manager total
		removeMemory(nDisposalSize);
	} else {
		// For some reason the resource is not disposed
		return false;
	}
	return true;
}

/*
 * Disposes of the resource (frees memory) - does not remove resource from the manager
 */
bool fgResourceManager::disposeResource(fgResource* pResource)
{
	if(!pResource)
		return false;
	// Try to find the resource with the specified id
	fgResourceMapItor itor = m_resourceMap.find(pResource->getHandle());
	if(itor == m_resourceMap.end()) {
		// Could not find resource to remove
		return false;
	}
	// if the resource was found, check to see that it's not locked
	if(pResource->isLocked()) {
		// Can't remove a locked resource
		return false;
	}
	unsigned int nDisposalSize = pResource->getSize();
	pResource->dispose();
	if(pResource->isDisposed()) {
		// Get the memory and subtract it from the manager total
		removeMemory(nDisposalSize);
	} else {
		// For some reason the resource is not disposed
		return false;
	}
	return true;
}

/*
 * Destroys an object and deallocates it's memory
 */
bool fgResourceManager::destroyResource(fgResource* pResource)
{
	if(!removeResource(pResource))
		return false;
	delete pResource;
	return true;
}

/*
 * Destroys an object and deallocates it's memory. First resource is removed
 * from the resource managers map, existing rhandles will become invalid
 * regardless of the usage in the program - however if the reference count is
 * not zero the resource wont be removed and destroyed
 */
bool fgResourceManager::destroyResource(FG_RHANDLE rhUniqueID)
{
	fgResource* pResource = getResource(rhUniqueID);
	if(!removeResource(rhUniqueID))
		return false;
	delete pResource;
	return true;
}

/*
 * Get the resource pointer (object) via rhandle ID
 */
fgResource* fgResourceManager::getResource(FG_RHANDLE rhUniqueID)
{
	fgResourceMapItor itor = m_resourceMap.find(rhUniqueID);
	if(itor == m_resourceMap.end()) {
		return NULL;
	}
	
	// You may need to add your own OS dependent method of getting
	// the current time to set your resource access time

	// Set the current time as the last time the object was accessed
	itor->second->setLastAccess(time(0));

	// Recreate the object before giving it to the application
	if(itor->second->isDisposed())
	{
		itor->second->recreate();
		addMemory(itor->second->getSize());

		// check to see if any overallocation has taken place, but
		// make sure we don't swap out the same resource.
		lockResource(rhUniqueID);
		checkForOverallocation();
		unlockResource(rhUniqueID);
	}

	// return the object pointer
	return itor->second;
}

/*
 *
 */
fgResource* fgResourceManager::lockResource(FG_RHANDLE rhUniqueID)
{
	if(FG_IS_INVALID_RHANDLE(rhUniqueID)) {
		return NULL;
	}
	fgResourceMapItor itor = m_resourceMap.find(rhUniqueID);
	if(itor == m_resourceMap.end()) {
		return NULL;
	}
	
	// increment the object's count
	itor->second->Lock();

	// recreate the object before giving it to the application
	if(itor->second->isDisposed())
	{
		itor->second->recreate();
		addMemory(itor->second->getSize());
		// check to see if any overallocation has taken place
		checkForOverallocation();
	}
	// return the object pointer
	return itor->second;
}

/*
 *
 */
fgResource* fgResourceManager::unlockResource(FG_RHANDLE rhUniqueID)
{
	if(FG_IS_INVALID_RHANDLE(rhUniqueID)) {
		return NULL;
	}
	fgResourceMapItor itor = m_resourceMap.find(rhUniqueID);
	if(itor == m_resourceMap.end())
		return NULL;
	itor->second->Unlock();
	return itor->second;
}

/*
 *
 */
FG_RHANDLE fgResourceManager::findResourceHandle(fgResource* pResource)
{
	// Try to find the resource in the resource map
	fgResourceMapItor itor;
	for(itor = m_resourceMap.begin(); itor != m_resourceMap.end(); ++itor)
	{
		if(itor->second == pResource)
			break;
	}
	if(itor == m_resourceMap.end())
		return FG_INVALID_RHANDLE;
	return itor->first;
}

/*
 *
 */
void fgResourceManager::refreshMemory(void)
{
	resetMemory();
	for(fgResourceMapItor itor = m_resourceMap.begin(); itor != m_resourceMap.end(); ++itor) {
		addMemory(itor->second->getSize());
	}
}

/*
 *
 */
bool fgResourceManager::checkForOverallocation(void)
{
	if(m_nCurrentUsedMemory > m_nMaximumMemory)
	{
		resetMemory();
		// create a temporary priority queue to store the managed items
		std::priority_queue<fgResource*, std::vector<fgResource*>, ptr_greater<fgResource*> > PriQueue;

		// insert copies of all the resource pointers into the priority queue, but
		// exclude those that are current disposed or are locked
		for(fgResourceMapItor itor = m_resourceMap.begin(); itor != m_resourceMap.end(); ++itor)
		{
			addMemory(itor->second->getSize());
			if(!itor->second->isDisposed() && !itor->second->isLocked())
				PriQueue.push(itor->second);
		}
		// Attempt to remove iMemToPurge bytes from the managed resource
		int iMemToPurge = m_nCurrentUsedMemory - m_nMaximumMemory;
		while((!PriQueue.empty()) && (m_nCurrentUsedMemory > m_nMaximumMemory))
		{
			unsigned int nDisposalSize = PriQueue.top()->getSize();
			// Dispose of the all loaded data, free all memory, but don't destroy the object
			PriQueue.top()->dispose();
			if(PriQueue.top()->isDisposed())
				removeMemory(nDisposalSize);
			PriQueue.pop();
		}

		// If the resource queue is empty and we still have too much memory allocated,
		// then we return failure.  This could happen if too many resources were locked
		// or if a resource larger than the requested maximum memory was inserted.
		if(PriQueue.empty() && (m_nCurrentUsedMemory > m_nMaximumMemory))
			return false;
	}
	return true;
}
