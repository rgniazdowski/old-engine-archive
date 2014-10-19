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

#include "fgCommon.h"
#include "fgResourceManager.h"
#include "fgResourceErrorCodes.h"
#include "fgResourceFactory.h"
#include "fgResourceConfigParser.h"

#include <queue>

#include "Util/fgStrings.h"
#include "Util/fgDirent.h"
#include "Util/fgPath.h"
#include "fgLog.h"

/*
 *
 */
fgResourceManager::fgResourceManager(fgResourceFactory *resourceFactory) :
m_dataDir(NULL),
m_nCurrentUsedMemory(0),
m_nMaximumMemory(0),
m_bResourceReserved(FG_FALSE) {
    m_currentResource = getRefDataVector().end();
    m_resourceGroupHandles.clear_optimised();
    setResourceFactory(resourceFactory);
    m_managerType = FG_MANAGER_RESOURCE;
}

/*
 *
 */
fgResourceManager::~fgResourceManager() {
    fgResourceManager::destroy();
}

/*
 *
 */
void fgResourceManager::setResourceFactory(fgResourceFactory *resourceFactory) {
    if(resourceFactory)
        m_resourceFactory = resourceFactory;
}

/*
 *
 */
fgResourceFactory *fgResourceManager::getResourceFactory(void) const {
    return m_resourceFactory;
}

/*
 * Reset local parameters
 */
void fgResourceManager::clear(void) {
    releaseAllHandles();
    m_nCurrentUsedMemory = 0;
    m_nMaximumMemory = 0;
    m_bResourceReserved = FG_FALSE;
    m_currentResource = getRefDataVector().end();
    m_resourceGroupHandles.clear_optimised();
    m_init = FG_FALSE;
    m_resourceFactory = NULL;
    m_managerType = FG_MANAGER_RESOURCE;
}

/*
 * This function will release all data and memory held by resource
 * manager itself (including resources)
 */
fgBool fgResourceManager::destroy(void) {
    FG_LOG::PrintDebug(">>>>> fgResourceManager::destroy(void); GROUPS"); // #TODELETE
    {
        rmHandleVecItor begin = m_resourceGroupHandles.begin();
        rmHandleVecItor end = m_resourceGroupHandles.end();
        for(rmHandleVecItor itor = begin; itor != end; ++itor) {
            if((*itor).isNull())
                continue;
            fgResource *pResource = dereference(*itor);
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
                destroyData(resPtr);
            }
            pResourceGroup->clear();
            destroyData(pResource);
        }
        m_resourceGroupHandles.clear_optimised();
    }

    FG_LOG::PrintDebug(">>>>> fgResourceManager::destroy(void); RESOURCES"); // #TODELETE
    {
        hmDataVecItor begin = getRefDataVector().begin();
        hmDataVecItor end = getRefDataVector().end();
        for(hmDataVecItor itor = begin; itor != end; ++itor) {
            if((*itor) == NULL)
                continue;
            delete (*itor);
            *itor = NULL;
        }
        fgResourceManager::clear();
    }
    if(m_dataDir)
        delete m_dataDir;
    m_dataDir = NULL;
    return FG_TRUE;
}

/*
 * Function pre loads any required data (configs, metadata, etc)
 */
fgBool fgResourceManager::initialize(void) {
    if(m_init) {
        // double initialization ?
        return FG_FALSE;
    }
    if(!m_resourceFactory) {
        // the resource factory is not set
        return FG_FALSE;
    }
    if(!m_dataDir)
        m_dataDir = new fgDirent();
    // Fix me - universal paths - use pwd or something
    // #FIXME - compatibility for different platforms
    m_dataDir->readDirectory("./", FG_TRUE);
    m_dataDir->rewind();
    FG_LOG::PrintDebug("Initializing resource manager\nCurrent maximum memory: %.2f", (float)m_nMaximumMemory / 1024.0 / 1024.0); // #TODELETE
    // First of all load any resource group configs,
    // file extension is *.rgrp and it's a xml file.
    std::string filepath;
    fgStringVector resGroupFiles;
    // #FIXME - well this looks kinda bad, probably loading
    // resource groups files should look different - must be
    // more universal - platform independent, check for
    // correct paths in the environment, etc.
    while(m_dataDir->searchForFile(filepath, std::string("./"), std::string("*group.xml;*group.ini"), FG_FALSE).length()) {
        resGroupFiles.push_back(filepath);
    }

    if(resGroupFiles.size() == 0) {
        reportWarning(FG_ERRNO_RESOURCE_NO_GROUPS, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    const char *filename;
    for(unsigned int i = 0; i < resGroupFiles.size(); i++) {
        // #FIXME - should resource manager hold separate array for res groups IDS ? oh my ...
        FG_RHANDLE grpUniqueID;
        filename = fgPath::fileName(resGroupFiles[i].c_str());
        fgResourceGroup *resGroup = new fgResourceGroup(m_resourceFactory);
        // #TODO this will not always look like this - requires full path (cross platform)
        resGroup->setFilePath(filename);
        if(!resGroup->preLoadConfig()) {
            delete resGroup;
            resGroup = NULL;
            continue;
        }
        // Resource group is inserted as normal resource
        // Resources within resource group are treated as one
        // so even if resources in main map are being checked
        // for overallocation, they will not be purged if the
        // resource group is still being used (and locked)
        // Locking resource group - locks all the resources
        insertResource(resGroup->getRefHandle(), resGroup);
        grpUniqueID = resGroup->getHandle();
        // There is a separate holder for resource group
        insertResourceGroup(grpUniqueID, resGroup);
        fgResourceGroup::rgResVec& resInGrp = resGroup->getRefResourceFiles();
        for(fgResourceGroup::rgResVecItor it = resInGrp.begin(); it != resInGrp.end(); it++) {
            insertResource((*it)->getRefHandle(), (*it));
        }
        // This is really important - refresh array with resource handles
        resGroup->refreshArrays();
    }
    resGroupFiles.clear();
    goToBegin();
    m_init = FG_TRUE;
    return FG_TRUE;
}

/*
 * Set maximum memory value for the used memory counter
 */
fgBool fgResourceManager::setMaximumMemory(size_t nMaxSize) {
    m_nMaximumMemory = nMaxSize;
    return checkForOverallocation();
}

/*
 * Allows the resource manager to pre-reserve an amount of memory so
 * an inserted resource does not exceed the maximum allowed memory
 */
fgBool fgResourceManager::reserveMemory(size_t nMem) {
    addMemory(nMem);
    if(!checkForOverallocation())
        return FG_FALSE;
    m_bResourceReserved = FG_TRUE;
    return FG_TRUE;
}

/*
 * Find next resource with given criteria (currently resource type)
 */
fgBool fgResourceManager::goToNext(fgResourceType resType) {
    while(FG_TRUE) {
        m_currentResource++;
        if(!isValid()) {
            break;
        }
        if((*m_currentResource)->getResourceType() == resType) {
            break;
        }
    }

    return isValid();
}

/*
 * Find next resource with given criteria (currently resource type)
 */
fgBool fgResourceManager::goToNext(const fgResourceType* resTypes, int n) {
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
fgBool fgResourceManager::goToNext(fgResourceType resType, fgQuality quality) {
    while(FG_TRUE) {
        goToNext();
        if(!isValid()) {
            break;
        }
        if((*m_currentResource)->getResourceType() == resType) {
            if((*m_currentResource)->getQuality() == quality) {
                break;
            }
        }
    }

    return isValid();
}

/*
 * Insert resource group into manager, if you pass in the pointer to
 * resource handle, the Resource Manager will provide a unique handle for you.
 */
fgBool fgResourceManager::insertResource(FG_RHANDLE& rhUniqueID, fgResource* pResource) {
    if(!pResource) {
        return FG_FALSE;
    }
    if(!insert(rhUniqueID, pResource, pResource->getName())) {
        return FG_FALSE;
    }
    // Get the memory and add it to the catalog total.  Note that we only have
    // to check for memory overallocation if we haven't preallocated memory
    if(!m_bResourceReserved) {
        addMemory(pResource->getSize());
        // check to see if any overallocation has taken place
        if(!checkForOverallocation())
            return FG_FALSE;
    } else
        m_bResourceReserved = FG_FALSE;
    pResource->setManager(this);
    return FG_TRUE;
}

/*
 * Insert resource group into manager
 */
fgBool fgResourceManager::insertResourceGroup(const FG_RHANDLE& rhUniqueID, fgResource* pResource) {
    if(!fgDataManagerBase::isManaged(pResource)) {
        return FG_FALSE;
    }

    if(m_resourceGroupHandles.find(rhUniqueID) != -1) {
        reportError(FG_ERRNO_RESOURCE_GROUP_IN_VECTOR, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    m_resourceGroupHandles.push_back(rhUniqueID);
    return FG_TRUE;
}

/*
 * Removes an object completely from the manager.
 */
fgBool fgResourceManager::remove(const FG_RHANDLE& rhUniqueID) {
    return fgResourceManager::remove(fgDataManagerBase::get(rhUniqueID));
}

/*
 * Removes an object completely from the manager.
 */
fgBool fgResourceManager::remove(const std::string& nameTag) {
    return fgResourceManager::remove(fgDataManagerBase::get(nameTag));
}

/*
 * Removes an object completely from the manager.
 */
fgBool fgResourceManager::remove(const char *nameTag) {
    return fgResourceManager::remove(fgDataManagerBase::get(nameTag));
}

/*
 * Removes an object completely from the manager.
 * Does not free memory (held by the allocated object).
 */
fgBool fgResourceManager::remove(fgResource* pResource) {
    if(!fgDataManagerBase::isManaged(pResource))
        return FG_FALSE;
    // if the resource was found, check to see that it's not locked
    if(pResource->isLocked()) {
        // Can't remove a locked resource
        reportError(FG_ERRNO_RESOURCE_LOCKED_REMOVAL, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    // Get the memory and subtract it from the manager total
    removeMemory(pResource->getSize());
    releaseHandle(pResource->getHandle());
    return FG_TRUE;
}

/*
 * Disposes of the resource (frees memory) - does not remove resource from the manager
 */
fgBool fgResourceManager::dispose(const FG_RHANDLE& rhUniqueID) {
    return dispose(fgDataManagerBase::get(rhUniqueID));
}

/*
 * Disposes of the resource (frees memory) - does not remove resource from the manager
 */
fgBool fgResourceManager::dispose(const std::string& nameTag) {
    return dispose(fgDataManagerBase::get(nameTag));
}

/*
 * Disposes of the resource (frees memory) - does not remove resource from the manager
 */
fgBool fgResourceManager::dispose(const char *nameTag) {
    return dispose(fgDataManagerBase::get(nameTag));
}

/*
 * Disposes of the resource (frees memory) - does not remove resource from the manager
 */
fgBool fgResourceManager::dispose(fgResource* pResource) {
    if(!fgDataManagerBase::isManaged(pResource))
        return FG_FALSE;
    // if the resource was found, check to see that it's not locked
    if(pResource->isLocked()) {
        // Can't remove a locked resource
        reportError(FG_ERRNO_RESOURCE_LOCKED_REMOVAL, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    unsigned int nDisposalSize = pResource->getSize();
    pResource->dispose();
    if(pResource->isDisposed()) {
        // Get the memory and subtract it from the manager total
        removeMemory(nDisposalSize);
    } else {
        // For some reason the resource is not disposed
        reportWarning(FG_ERRNO_RESOURCE_NOT_DISPOSED, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    return FG_TRUE;
}

/*
 * Get the resource pointer (object) via resource handle ID
 * Using GetResource tells the manager that you are about to access the
 * object.  If the resource has been disposed, it will be recreated
 * before it has been returned.
 */
fgResource* fgResourceManager::get(const FG_RHANDLE& rhUniqueID, const fgQuality quality) {
    fgResource *pResource = fgDataManagerBase::get(rhUniqueID);
    if(!pResource) {
        return NULL;
    }
    // You may need to add your own OS dependent method of getting
    // the current time to set your resource access time

    // Set the current time as the last time the object was accessed
    pResource->setLastAccess(time(0));

    // Recreate the object before giving it to the application
    if(pResource->isDisposed()) {
        pResource->setQuality(quality);
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
fgResource* fgResourceManager::get(const std::string& nameTag, const fgQuality quality) {
    fgResource *pResource = fgDataManagerBase::get(nameTag);
    if(!pResource) {
        return NULL;
    }
    // You may need to add your own OS dependent method of getting
    // the current time to set your resource access time

    // Set the current time as the last time the object was accessed
    pResource->setLastAccess(time(0));

    // Recreate the object before giving it to the application
    if(pResource->isDisposed()) {
        pResource->setQuality(quality); // FIXME
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
fgResource* fgResourceManager::get(const char *nameTag, const fgQuality quality) {
    return fgResourceManager::get(std::string(nameTag), quality);
}

/*
 *
 */
fgResource* fgResourceManager::request(const std::string& info) {
    return request(info, FG_RESOURCE_AUTO);
}

/*
 *
 */
fgResource* fgResourceManager::request(const char *info) {
    return request(std::string(info), FG_RESOURCE_AUTO);
}

/*
 *
 */
fgResource* fgResourceManager::request(const std::string& info, const fgResourceType forcedType) {
    if(!m_dataDir || !m_init || !m_resourceFactory || info.empty())
        return NULL;
    fgResource *resourcePtr = NULL;
    // This is a fallback, if such resource already exists in the resource manager
    // it should not be searched and reloaded - however do not use request() in a main
    // loop as it may be slower
    resourcePtr = fgResourceManager::get(info);
    if(resourcePtr)
        return resourcePtr;
    // info cannot be a path, it has to be resource name or config name
    // required file will be found
    if(fgStrings::contains(info, std::string("/\\")))
        return NULL;

    std::string pattern;
    std::string filePath;
    fgResourceType resExtType = FG_RESOURCE_INVALID;
    fgBool infoAsName = FG_FALSE;
    fgBool isFound = FG_FALSE;
    fgBool isConfig = FG_FALSE;

    const char *iext = fgPath::fileExt(info.c_str(), FG_TRUE);
    if(!iext) { // no extension given so... search all
        infoAsName = FG_TRUE;
        pattern.append(info).append("*;");
    } else { // extension is given, search for exact file
        pattern.append(info);
    }

    if(!infoAsName && iext) {
        // This is special search for filename within already loaded resources
        goToBegin();
        while(isValid()) {
            fgResource *res = getCurrentResource();
            if(!res)
                break;
            fgResource::fileMapping &files = res->getFileMapping();
            fgResource::fileMappingItor fit = files.begin(), fend = files.end();
            for(; fit != fend; fit++) {
                // Comparing using endsWith - resource contains relative file paths
                // not just file name - this request function takes in just file names
                // resource names or patterns (wildcards for extensions)
                if(fgStrings::endsWith(fit->second, pattern, FG_TRUE)) {
                    //if(fit->second.compare(pattern) == 0) {
                    // Found resource containing specified file

                    return res;
                }
            }
            goToNext();
        }
    }

    m_dataDir->rewind();
    while(m_dataDir->searchForFile(filePath, "./", pattern, FG_TRUE).length()) {
        const char *fext = NULL;
        if(iext) {
            fext = iext;
        } else {
            fext = fgPath::fileExt(filePath.c_str(), FG_TRUE);
        }
        if(strcasecmp(fext, "res.ini") == 0) {
            isConfig = FG_TRUE;
        } else if(strcasecmp(fext, "tga") == 0) {
            resExtType = FG_RESOURCE_TEXTURE;
        } else if(strcasecmp(fext, "jpg") == 0) {
            resExtType = FG_RESOURCE_TEXTURE;
        } else if(strcasecmp(fext, "png") == 0) {
            resExtType = FG_RESOURCE_TEXTURE;
        } else if(strcasecmp(fext, "obj") == 0) {
            resExtType = FG_RESOURCE_3D_MODEL;
        } else if(strcasecmp(fext, "wav") == 0) {
            resExtType = FG_RESOURCE_SOUND;
        } else if(strcasecmp(fext, "mp3") == 0) {
            resExtType = FG_RESOURCE_MUSIC;
        } else if(strcasecmp(fext, "mod") == 0) {
            resExtType = FG_RESOURCE_MUSIC;
        } else if(strcasecmp(fext, "raw") == 0) {
            //resExtType = FG_RESOURCE_SOUND;
        } else {
        }

        if(resExtType != FG_RESOURCE_INVALID || isConfig) {
            isFound = FG_TRUE;
            break;
        }
    };

    if(!isFound)
        return NULL;
    if(isConfig) {
        fgResourceConfig *resCfg = new fgResourceConfig();
        // This references to external config file, config should be loaded and proper resource created
        if(!resCfg->load(filePath.c_str())) {
            delete resCfg;
            // MESSAGE?
            return NULL;
        }
        // THIS CODE IS REALLY SIMILAR TO THE ONE IN RESOURCE GROUP
        // NEED TO THINK OF A WAY TO NOT REPEAT THIS CHUNK OF CODE
        // SHOULD RESOURCE GROUP HAVE SOME ACCESS TO THIS RES MGR?
        fgResourceHeader *header = &resCfg->getRefHeader();
        if(m_resourceFactory->isRegistered(header->resType)) {
            resourcePtr = m_resourceFactory->createResource(header->resType);
            resourcePtr->setName(header->name);
            resourcePtr->setPriority(header->priority);
            resourcePtr->setQuality(header->quality);

            if(header->paths.size() != header->qualities.size()) {
                FG_LOG::PrintError("Group config: number of qualities doesn't match number of files for: '%s'", header->name.c_str());
                delete resourcePtr;
                if(resCfg)
                    delete resCfg;
                return NULL;
            }
            for(int i = 0; i < (int)header->paths.size(); i++) {
                resourcePtr->setFilePath(header->paths[i], header->qualities[i]);
            }
            resourcePtr->setDefaultID(header->quality);
        }
        delete resCfg;
    } else if(resExtType != FG_RESOURCE_INVALID) {
        if(forcedType != FG_RESOURCE_AUTO)
            resExtType = forcedType;
        if(m_resourceFactory->isRegistered(resExtType)) {
            resourcePtr = m_resourceFactory->createResource(resExtType);
            resourcePtr->setName(info);
            resourcePtr->setPriority(FG_RES_PRIORITY_LOW);
            resourcePtr->setQuality(FG_QUALITY_UNIVERSAL);
            resourcePtr->setDefaultID(FG_QUALITY_UNIVERSAL);
            resourcePtr->setFilePath(filePath);
        }
    }

    if(resourcePtr) {
        fgResourceManager::insertResource(resourcePtr->getRefHandle(), resourcePtr);
    }

    return resourcePtr;
}

/*
 *
 */
fgResource* fgResourceManager::request(const char *info, const fgResourceType forcedType) {
    return request(std::string(info), forcedType);
}

/*
 * Locking the resource ensures that the resource does not get managed by
 * the Resource Manager.  You can use this to ensure that a surface does not
 * get swapped out, for instance.  The resource contains a reference count
 * to ensure that numerous locks can be safely made.
 * #FIXME #TODO #P3 - locking/unlocking is based on counter - DEPRECATED.
 */
fgResource* fgResourceManager::lockResource(const FG_RHANDLE& rhUniqueID) {
    fgResource *pResource = fgDataManagerBase::get(rhUniqueID);
    lockResource(pResource);
    // return the object pointer
    return pResource;
}

/*
 * Lock the resource
 */
fgBool fgResourceManager::lockResource(fgResource *pResource) {
    if(!fgDataManagerBase::isManaged(pResource)) {
        return FG_FALSE;
    }
    // increment the object's count
    pResource->Lock();
    // recreate the object before giving it to the application
    if(pResource->isDisposed()) {
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
fgResource* fgResourceManager::unlockResource(const FG_RHANDLE& rhUniqueID) {
    fgResource *pResource = fgDataManagerBase::get(rhUniqueID);
    pResource->Unlock();
    return pResource;
}

/*
 * Unlock the resource
 */
fgBool fgResourceManager::unlockResource(fgResource *pResource) {
    if(!fgDataManagerBase::isManaged(pResource)) {
        return FG_FALSE;
    }
    if(pResource->getReferenceCount() == 0) {
        reportError(FG_ERRNO_RESOURCE_TOO_MANY_UNLOCKS, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    pResource->Unlock();
    return FG_TRUE;
}

/*
 * Refresh allocated memory based on managed resources
 */
void fgResourceManager::refreshMemory(void) {
    resetMemory();
    hmDataVecItor begin = getRefDataVector().begin(), end = getRefDataVector().end();
    for(hmDataVecItor itor = begin; itor != end; ++itor) {
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
fgBool fgResourceManager::checkForOverallocation(void) {
    if(m_nCurrentUsedMemory > m_nMaximumMemory) {
        resetMemory();
        // create a temporary priority queue to store the managed items
        std::priority_queue<fgResource*, std::vector<fgResource*>, fgPtrGreater<fgResource*> > PriQueue;
        hmDataVecItor begin = getRefDataVector().begin(), end = getRefDataVector().end();

        // insert copies of all the resource pointers into the priority queue, but
        // exclude those that are current disposed or are locked
        for(hmDataVecItor itor = begin; itor != end; ++itor) {
            if(!(*itor))
                continue;
            addMemory((*itor)->getSize());
            if(!(*itor)->isDisposed() && !(*itor)->isLocked())
                PriQueue.push(*itor);
        }
        // Attempt to remove iMemToPurge bytes from the managed resource
        int iMemToPurge = m_nCurrentUsedMemory - m_nMaximumMemory;
        while((!PriQueue.empty()) && (m_nCurrentUsedMemory > m_nMaximumMemory)) {
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
        if(PriQueue.empty() && (m_nCurrentUsedMemory > m_nMaximumMemory)) {
            reportWarning(FG_ERRNO_RESOURCE_OVERALLOCATION);
            return FG_FALSE;
        }
    }
    return FG_TRUE;
}
