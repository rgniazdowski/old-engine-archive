/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of #FLEXIGAME_PROJECT
 * 
 * #FLEXIGAME_PROJECT source code and any related files can not be copied, modified 
 * and/or distributed without the express or written permission from the author.
 *******************************************************/
/**
 * Portions Copyright (C) James Boer, 2000
 */

#include "fgResourceManager.h"
#include "fgResourceFactory.h"
#include "fgDirent.h"

#include <queue>

template <>
bool fgSingleton<fgResourceManager>::instanceFlag = false;

template <>
fgResourceManager *fgSingleton<fgResourceManager>::instance = NULL;

//#FIXME #BIGFIXME! ! ! ! #BUG #TODO
#include "GUI/fgFontResource.h"
#include "Graphics/Textures/fgTextureResource.h"
#include "fgResourceGroup.h"

/*
 *
 */
fgResourceManager::fgResourceManager() : 
	m_nCurrentUsedMemory(0),
	m_nMaximumMemory(0),
	m_bResourceReserved(FG_FALSE)
{
	m_resourceHandlesMgr.releaseAllHandles();
	m_currentResource = getRefResourceVector().end();
	m_resourceGroupHandles.clear_optimised();

	// #FIXME #BUG
	FG_ResourceFactory->registerResource(FG_RESOURCE_TEXTURE, &fgTextureResource::createResource);
	FG_ResourceFactory->registerResource(FG_RESOURCE_FONT, &fgFontResource::createResource);
	FG_ResourceFactory->registerResource(FG_RESOURCE_GROUP, &fgResourceGroup::createResource);
}

/*
 *
 */
fgResourceManager::~fgResourceManager()
{
	FG_ResourceFactory->clear(); // #BUG
	destroy();
}

/*
 * Reset local parameters
 */
void fgResourceManager::clear(void)
{
	FG_WriteLog(">>>>> fgResourceManager::clear(void); ALL"); // #TODELETE
	m_resourceHandlesMgr.releaseAllHandles();
	m_nCurrentUsedMemory = 0;
	m_nMaximumMemory = 0;
	m_bResourceReserved = FG_FALSE;
	m_currentResource = getRefResourceVector().end();
	m_resourceGroupHandles.clear_optimised();
}

/*
 * This function will release all data and memory held by resource
 * manager itself (including resources)
 */
void fgResourceManager::destroy(void)
{
	FG_WriteLog(">>>>> fgResourceManager::destroy(void); GROUPS"); // #TODELETE
	{
		rmHandleVecItor begin = m_resourceGroupHandles.begin();
		rmHandleVecItor	end = m_resourceGroupHandles.end(); 
		for(rmHandleVecItor itor = begin; itor != end; ++itor)
		{
			if((*itor).isNull())
				continue;
			fgResource *pResource = m_resourceHandlesMgr.dereference(*itor);
			fgResourceGroup *pResourceGroup = (fgResourceGroup *)pResource;
			if(!pResourceGroup || !pResource) {
				continue;
			}
			pResource->ZeroLock();
			pResourceGroup->dispose();
			fgResourceGroup::rgResVec& resInGrp = pResourceGroup->getRefResourceFiles();
			while(!resInGrp.empty()) {
				fgResource *resPtr = resInGrp.back();
				resInGrp.pop_back();
				destroyResource(resPtr);
			}
			pResourceGroup->clear();
			destroyResource(pResource);
		}
		m_resourceGroupHandles.clear_optimised();
	}

	FG_WriteLog(">>>>> fgResourceManager::destroy(void); RESOURCES");
	{
		rmResVecItor begin = getRefResourceVector().begin();
		rmResVecItor end = getRefResourceVector().end();
		for(rmResVecItor itor = begin; itor != end ; ++itor) {
			if((*itor) == NULL)
				continue;
			destroyResource((*itor));
			if(!m_resourceHandlesMgr.getUsedHandleCount())
				break;
		}
		m_resourceHandlesMgr.releaseAllHandles();
		clear();
	}
}

/*
 * Function pre loads any required data (configs, metadata, etc)
 */
fgBool fgResourceManager::initialize(void)
{
	FG_WriteLog(">>>>>> fgResourceManager::initialize(void); -> Initializing resource manager\nCurrent maximum memory: %.2f", (float)m_nMaximumMemory/1024.0/1024.0);
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
		return FG_FALSE; // #TODO proper error handling
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
		insertResource(grpUniqueID, resGroup);
		// There is a separate holder for resource group
		insertResourceGroup(grpUniqueID, resGroup);
		fgResourceGroup::rgResVec& resInGrp = resGroup->getRefResourceFiles();
		for(fgResourceGroup::rgResVecItor it = resInGrp.begin(); it != resInGrp.end(); it++) {
			FG_RHANDLE resUniqueID;
			insertResource(resUniqueID, (*it));
		}
		resGroup->refreshArrays();
		FG_WriteLog("LOG INSERTED RESOURCE GROUP"); // #FIXME #TODELETE
	}
	resGroupFiles.clear();
	goToBegin();

	return FG_TRUE;
}

/*
 * Set maximum memory value for the used memory counter
 */
fgBool fgResourceManager::setMaximumMemory(size_t nMaxSize)
{
	m_nMaximumMemory = nMaxSize;
	return checkForOverallocation();
}

/*
 * Allows the resource manager to pre-reserve an amount of memory so
 * an inserted resource does not exceed the maximum allowed memory
 */
fgBool fgResourceManager::reserveMemory(size_t nMem)
{
	addMemory(nMem);
	if(!checkForOverallocation())
		return FG_FALSE;
	m_bResourceReserved = FG_TRUE;
	return FG_TRUE;
}

/*
 * Find next resource with given criteria (currently resource type)
 */
fgBool fgResourceManager::goToNext(fgResourceType resType)
{
	while(FG_TRUE) {
		m_currentResource++;
		if(!isValid()) {
			return FG_FALSE;
		}
		if((*m_currentResource)->getResourceType() == resType) {
			return FG_TRUE;
		}
	}

	return isValid();
}

/*
 * Find next resource with given criteria (currently resource type)
 */
fgBool fgResourceManager::goToNext(const fgResourceType* resTypes, int n)
{
	if(!resTypes)
		return FG_FALSE;

	while(FG_TRUE) {
		goToNext();
		if(!isValid()) {
			break;
		}
		fgBool status = FG_FALSE;
		int i = 0;
		while(!status) {
			if(i == n || resTypes[i] == FG_RESOURCE_INVALID)
				break;
			if((*m_currentResource)->getResourceType() == resTypes[i]) {
				status = FG_TRUE;
			}
			i++;
		}
		if(status == FG_TRUE)
			break;
	}

	return isValid();
}

/*
 * Find next resource with given criteria (currently resource type and quality)
 */
fgBool fgResourceManager::goToNext(fgResourceType resType, fgQuality quality)
{
	while(FG_TRUE) {
		goToNext();
		if(!isValid()) {
			return FG_FALSE;
		}
		if((*m_currentResource)->getResourceType() == resType) {
			if((*m_currentResource)->getQuality() == quality) {
				return FG_TRUE;
			}
		}
	}

	return isValid();
}

/*
 * Insert resource group into manager, if you pass in the pointer to
 * resource handle, the Resource Manager will provide a unique handle for you.  
 */
fgBool fgResourceManager::insertResource(FG_RHANDLE& rhUniqueID, fgResource* pResource)
{
	if(!pResource) {
		FG_ErrorLog("%s(%d): resource parameter is NULL - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}

	if(m_resourceHandlesMgr.isDataManaged(pResource)) {
		FG_ErrorLog("%s(%d): this resource is already managed (it exists in the handle manager) - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}

	if(!pResource->getHandle().isNull()) {
		FG_ErrorLog("%s(%d): resource has already initialized handle - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	// Acquire next valid resource handle
	// Insert the resource into the current catalog
	if(!m_resourceHandlesMgr.acquireHandle(rhUniqueID, pResource)) {
		FG_ErrorLog("%s(%d): could not acquire handle for the resource - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	pResource->setResourceHandle(rhUniqueID);
	if(!m_resourceHandlesMgr.setupName(pResource->getResourceName(), rhUniqueID)) {
		FG_ErrorLog("%s(%d): could not setup handle string tag for the resource - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	// Get the memory and add it to the catalog total.  Note that we only have
	// to check for memory overallocation if we haven't preallocated memory
	if(!m_bResourceReserved)
	{
		addMemory(pResource->getSize());
		// check to see if any overallocation has taken place
		if(!checkForOverallocation())
			return FG_FALSE;
	}
	else
		m_bResourceReserved = FG_FALSE;
	// return the id to the user for their use and return success
	return FG_TRUE;
}

/*
 * Insert resource group into manager
 */
fgBool fgResourceManager::insertResourceGroup(FG_RHANDLE rhUniqueID, fgResource* pResource)
{
	if(!pResource) {
		FG_ErrorLog("%s(%d): resource parameter is NULL - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	if(!m_resourceHandlesMgr.isHandleValid(rhUniqueID)) {
		FG_ErrorLog("%s(%d): resource group handle is invalid- in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}

	if(m_resourceGroupHandles.find(rhUniqueID) != -1) {
		FG_ErrorLog("%s(%d): this resource group (%s) is already in the vector - in function %s.", FG_Filename(__FILE__), __LINE__-1,pResource->getResourceNameStr(),__FUNCTION__); 
		return FG_FALSE;
	}
	m_resourceGroupHandles.push_back(rhUniqueID);
	return FG_TRUE;
}

/*
 * Removes an object completely from the manager. 
 */
fgBool fgResourceManager::removeResource(FG_RHANDLE rhUniqueID)
{
	FG_WriteLog("fgResourceManager::removeResource(FG_RHANDLE rhUniqueID);"); // #TODELETE
	fgResource *pResource = m_resourceHandlesMgr.dereference(rhUniqueID);
	if(!pResource) {
		// Could not find resource to remove, handle is invalid
		FG_ErrorLog("%s(%d): could not find resource to remove, handle is invalid - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	return removeResource(pResource);
}

/*
 * Removes an object completely from the manager.
 * Does not free memory (held by the allocated object).
 */
fgBool fgResourceManager::removeResource(fgResource* pResource)
{
	FG_WriteLog("fgResourceManager::removeResource(fgResource* pResource);");
	if(!pResource) {
		FG_ErrorLog("%s(%d): resource parameter is NULL - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	if(!m_resourceHandlesMgr.isHandleValid(pResource->getHandle())) {
		// The handle of the resource is invalid, this resource is not managed
		FG_ErrorLog("%s(%d): the handle of the resource is invalid, this resource is not managed- in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	// if the resource was found, check to see that it's not locked
	if(pResource->isLocked()) {
		// Can't remove a locked resource
		FG_ErrorLog("%s(%d): can't remove a locked resource - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	// Get the memory and subtract it from the manager total
	removeMemory(pResource->getSize());
	m_resourceHandlesMgr.releaseHandle(pResource->getHandle());
	return FG_TRUE;
}

/*
 * Disposes of the resource (frees memory) - does not remove resource from the manager
 */
fgBool fgResourceManager::disposeResource(FG_RHANDLE rhUniqueID)
{
	// try to find the resource with the specified id
	fgResource *pResource = m_resourceHandlesMgr.dereference(rhUniqueID);
	if(!pResource) {
		// Could not find resource to remove, handle is invalid
		FG_ErrorLog("%s(%d): could not find resource to remove, handle is invalid - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	return disposeResource(pResource);
}

/*
 * Disposes of the resource (frees memory) - does not remove resource from the manager
 */
fgBool fgResourceManager::disposeResource(fgResource* pResource)
{
	if(!pResource) {
		FG_ErrorLog("%s(%d): resource parameter is NULL - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	if(!m_resourceHandlesMgr.isHandleValid(pResource->getHandle())) {
		// The handle of the resource is invalid, this resource is not managed
		FG_ErrorLog("%s(%d): the handle of the resource is invalid, this resource is not managed- in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	// if the resource was found, check to see that it's not locked
	if(pResource->isLocked()) {
		// Can't remove a locked resource
		FG_ErrorLog("%s(%d): can't remove a locked resource - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	unsigned int nDisposalSize = pResource->getSize();
	pResource->dispose();
	if(pResource->isDisposed()) {
		// Get the memory and subtract it from the manager total
		removeMemory(nDisposalSize);
	} else {
		// For some reason the resource is not disposed
		FG_ErrorLog("%s(%d): for some reason resource is not disposed - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	return FG_TRUE;
}

/*
 * Destroys an object and deallocates it's memory. First resource is removed
 * from the resource managers map, existing rhandles will become invalid
 * regardless of the usage in the program - however if the reference count is
 * not zero the resource wont be removed and destroyed
 */
fgBool fgResourceManager::destroyResource(fgResource* pResource)
{
	if(!removeResource(pResource)) {
		FG_ErrorLog("%s(%d): could not remove resource - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	FG_WriteLog("fgResourceManager::destroyResource(fgResource* pResource) -> delete pResource;");
	delete pResource;
	return FG_TRUE;
}

/*
 * Destroys an object and deallocates it's memory. First resource is removed
 * from the resource managers map, existing rhandles will become invalid
 * regardless of the usage in the program - however if the reference count is
 * not zero the resource wont be removed and destroyed
 */
fgBool fgResourceManager::destroyResource(FG_RHANDLE rhUniqueID)
{
	//fgResource* pResource = getResource(rhUniqueID);
	fgResource *pResource = m_resourceHandlesMgr.dereference(rhUniqueID);
	if(!removeResource(rhUniqueID)) {
		FG_ErrorLog("%s(%d): could not remove resource - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	FG_WriteLog("fgResourceManager::destroyResource(FG_RHANDLE rhUniqueID) -> delete pResource;");
	delete pResource;
	return FG_TRUE;
}

/*
 * Get the resource pointer (object) via resource handle ID
 * Using GetResource tells the manager that you are about to access the
 * object.  If the resource has been disposed, it will be recreated 
 * before it has been returned. 
 */
fgResource* fgResourceManager::getResource(FG_RHANDLE rhUniqueID)
{
	fgResource *pResource = m_resourceHandlesMgr.dereference(rhUniqueID);
	if(!pResource) {
		// Could not find resource to remove, handle is invalid
		FG_ErrorLog("%s(%d): could not find resource, handle is invalid - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return NULL;
	}
	// You may need to add your own OS dependent method of getting
	// the current time to set your resource access time

	// Set the current time as the last time the object was accessed
	pResource->setLastAccess(time(0));

	// Recreate the object before giving it to the application
	if(pResource->isDisposed())
	{
		pResource->recreate();
		addMemory(pResource->getSize());

		// check to see if any overallocation has taken place, but
		// make sure we don't swap out the same resource.
		pResource->Lock();
		checkForOverallocation();
		pResource->Unlock();
	}

	// return the object pointer
	return pResource;
}

/*
 * Get the resource pointer (object) via resource handle ID
 * Using GetResource tells the manager that you are about to access the
 * object.  If the resource has been disposed, it will be recreated 
 * before it has been returned. 
 */
fgResource* fgResourceManager::getResource(std::string& nameTag)
{
	if(nameTag.empty()) {
		FG_ErrorLog("%s(%d): resource name tag is empty - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return NULL;
	}
	fgResource *pResource = m_resourceHandlesMgr.dereference(nameTag);
	if(!pResource) {
		// Could not find resource to remove, handle is invalid
		FG_ErrorLog("%s(%d): could not find resource, tag name is invalid - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return NULL;
	}
	// You may need to add your own OS dependent method of getting
	// the current time to set your resource access time

	// Set the current time as the last time the object was accessed
	pResource->setLastAccess(time(0));

	// Recreate the object before giving it to the application
	if(pResource->isDisposed())
	{
		pResource->recreate();
		addMemory(pResource->getSize());

		// check to see if any overallocation has taken place, but
		// make sure we don't swap out the same resource.
		pResource->Lock();
		checkForOverallocation();
		pResource->Unlock();
	}

	// return the object pointer
	return pResource;
}

/*
 * Locking the resource ensures that the resource does not get managed by
 * the Resource Manager.  You can use this to ensure that a surface does not
 * get swapped out, for instance.  The resource contains a reference count
 * to ensure that numerous locks can be safely made.
 * #FIXME #TODO #P3 - locking/unlocking is based on counter - DEPRECATED.
 */
fgResource* fgResourceManager::lockResource(FG_RHANDLE rhUniqueID)
{
	if(FG_IS_INVALID_HANDLE(rhUniqueID)) {
		FG_ErrorLog("%s(%d): resource handle is invalid - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return NULL;
	}
	fgResource *pResource = m_resourceHandlesMgr.dereference(rhUniqueID);
	if(!pResource) {
		FG_ErrorLog("%s(%d): could not find resource to lock, handle is invalid - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return NULL;
	}
	lockResource(pResource);
	// return the object pointer
	return pResource;
}

/*
 * Lock the resource
 */
fgBool fgResourceManager::lockResource(fgResource *pResource)
{
	if(!pResource) {
		FG_ErrorLog("%s(%d): resource parameter is NULL - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	if(FG_IS_INVALID_HANDLE(pResource->getHandle()) 
		|| !m_resourceHandlesMgr.isHandleValid(pResource->getHandle())) {
		FG_ErrorLog("%s(%d): resource handle is invalid - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	// increment the object's count
	pResource->Lock();
	// recreate the object before giving it to the application
	if(pResource->isDisposed())
	{
		pResource->recreate();
		addMemory(pResource->getSize());
		// check to see if any overallocation has taken place
		checkForOverallocation();
	}
	return FG_TRUE;
}

/*
 * Unlocking the object let's the resource manager know that you no longer
 * need exclusive access.  When all locks have been released (the reference
 * count is 0), the object is considered safe for management again and can
 * be swapped out at the manager's discretion.  The object can be referenced
 * either by handle or by the object's pointer. 
 * #FIXME #TODO #P3 - locking/unlocking is based on counter - DEPRECATED.
 */
fgResource* fgResourceManager::unlockResource(FG_RHANDLE rhUniqueID)
{
	if(FG_IS_INVALID_HANDLE(rhUniqueID)) {
		FG_ErrorLog("%s(%d): resource handle is invalid - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return NULL;
	}
	fgResource *pResource = m_resourceHandlesMgr.dereference(rhUniqueID);
	if(!pResource) {
		FG_ErrorLog("%s(%d): could not find resource to unlock, handle is invalid - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return NULL;
	}
	pResource->Unlock();
	return pResource;
}

/*
 * Unlock the resource
 */
fgBool fgResourceManager::unlockResource(fgResource *pResource)
{
	if(!pResource) {
		FG_ErrorLog("%s(%d): resource parameter is NULL - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	if(FG_IS_INVALID_HANDLE(pResource->getHandle()) 
		|| !m_resourceHandlesMgr.isHandleValid(pResource->getHandle())) {
		FG_ErrorLog("%s(%d): resource handle is invalid - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	if(pResource->getReferenceCount() == 0) {
		FG_ErrorLog("%s(%d): resource reference count is already zero - too many unlocks - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	pResource->Unlock();
	return FG_TRUE;
}

/*
 * This function can be also used to check if given resource is managed
 */
fgBool fgResourceManager::isResourceManaged(fgResource* pResource)
{
	if(!pResource) {
		FG_ErrorLog("%s(%d): resource parameter is NULL - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	if(FG_IS_INVALID_HANDLE(pResource->getHandle()) 
		|| !m_resourceHandlesMgr.isHandleValid(pResource->getHandle())) {
		FG_ErrorLog("%s(%d): resource handle is invalid - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	if(!m_resourceHandlesMgr.isDataManaged(pResource)) {
		FG_ErrorLog("%s(%d): given resource is not managed - in function %s.", FG_Filename(__FILE__), __LINE__-1,__FUNCTION__); 
		return FG_FALSE;
	}
	return pResource->getHandle();
}

/*
 * Refresh allocated memory based on managed resources
 */
void fgResourceManager::refreshMemory(void)
{
	resetMemory();
	rmResVecItor begin = getRefResourceVector().begin(), end = getRefResourceVector().end();
	for(rmResVecItor itor = begin; itor != end; ++itor) {
		addMemory((*itor)->getSize());
	}
}

/*
 * This must be called when you wish the manager to check for discardable
 * resources.  Resources will only be swapped out if the maximum allowable
 * limit has been reached, and it will discard them from lowest to highest
 * priority, determined by the resource class's < operator.  Function will
 * fail if requested memory cannot be freed.
 */
fgBool fgResourceManager::checkForOverallocation(void)
{
	if(m_nCurrentUsedMemory > m_nMaximumMemory)
	{
		resetMemory();
		// create a temporary priority queue to store the managed items
		std::priority_queue<fgResource*, std::vector<fgResource*>, fgPtrGreater<fgResource*> > PriQueue;
		rmResVecItor begin = getRefResourceVector().begin(), end = getRefResourceVector().end();

		// insert copies of all the resource pointers into the priority queue, but
		// exclude those that are current disposed or are locked
		for(rmResVecItor itor = begin; itor != end; ++itor)
		{
			addMemory((*itor)->getSize());
			if(!(*itor)->isDisposed() && !(*itor)->isLocked())
				PriQueue.push(*itor);
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
			return FG_FALSE;
	}
	return FG_TRUE;
}
