/*******************************************************************************
 * Copyright (C) Radoslaw Gniazdowski <contact@flexigame.com>.
 * All rights reserved.
 *
 * This file is part of FlexiGame: Flexible Game Engine
 *
 * FlexiGame source code and any related files can not be copied, modified
 * and/or distributed without the express or written consent from the author.
 ******************************************************************************/
/**
 * Portions Copyright (C) James Boer, 2000
 */

#include "fgCommon.h"
#include "fgResourceManager.h"
#include "fgResourceErrorCodes.h"
#include "fgResourceFactory.h"
#include "fgResourceConfigParser.h"

#include "Hardware/fgQualityManager.h"
#include "Event/fgEventManager.h"
#include "Util/fgStrings.h"
#include "Util/fgDirent.h"
#include "Util/fgMemory.h"
#include "Util/fgPath.h"
#include "fgQueue.h"
#include "fgLog.h"

#if defined(FG_USING_PLATFORM_ANDROID)    
#include "Android/fgAndroid.h"
#endif

using namespace fg;

//------------------------------------------------------------------------------

resource::CResourceManager::CResourceManager(CResourceFactory *pResourceFactory,
                                             fg::base::CManager *pQualityMgr,
                                             fg::base::CManager *pEventMgr) :
m_pResourceFactory(pResourceFactory),
m_pQualityMgr(pQualityMgr),
m_pEventMgr(pEventMgr),
m_dataDir(NULL),
m_nCurrentUsedMemory(0),
m_nMaximumMemory(0),
m_bResourceReserved(FG_FALSE) {
    m_currentResource = getRefDataVector().end();
    m_resourceGroupHandles.clear_optimised();
    m_managerType = FG_MANAGER_RESOURCE;
}
//------------------------------------------------------------------------------

resource::CResourceManager::~CResourceManager() {
    CResourceManager::destroy();
}
//------------------------------------------------------------------------------

void resource::CResourceManager::clear(void) {
    releaseAllHandles();
    m_nCurrentUsedMemory = 0;
    m_nMaximumMemory = 0;
    m_bResourceReserved = FG_FALSE;
    m_currentResource = getRefDataVector().end();
    m_resourceGroupHandles.clear_optimised();
    m_init = FG_FALSE;
    m_pResourceFactory = NULL;
    m_pQualityMgr = NULL;
    m_pEventMgr = NULL;
    m_managerType = FG_MANAGER_RESOURCE;
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::destroy(void) {
    FG_LOG_DEBUG("Destroying groups..."); // #TODELETE
    {
        HandleVecItor begin = m_resourceGroupHandles.begin();
        HandleVecItor end = m_resourceGroupHandles.end();
        for(HandleVecItor itor = begin; itor != end; ++itor) {
            if((*itor).isNull())
                continue;
            CResource *pResource = dereference(*itor);
            CResourceGroup *pResourceGroup = (CResourceGroup *)pResource;
            if(!pResourceGroup || !pResource) {
                continue;
            }
            pResource->ZeroLock();
            pResourceGroup->dispose();
            CResourceGroup::rgResVec& resInGrp = pResourceGroup->getRefResourceFiles();
            while(!resInGrp.empty()) {
                CResource *resPtr = resInGrp.back();
                resInGrp.pop_back();
                destroyData(resPtr);
            }
            pResourceGroup->clear();
            destroyData(pResource);
        }
        m_resourceGroupHandles.clear_optimised();
    }

    FG_LOG_DEBUG("Destroying resources..."); // #TODELETE
    {
        DataVecItor begin = getRefDataVector().begin();
        DataVecItor end = getRefDataVector().end();
        for(DataVecItor itor = begin; itor != end; ++itor) {
            if((*itor).data == NULL)
                continue;
            delete (*itor).data;
            (*itor).clear();
        }
    }
    CResourceManager::clear();
    if(m_dataDir)
        delete m_dataDir;
    m_dataDir = NULL;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::initialize(void) {
    if(m_init) {
        // double initialization ?
        return FG_FALSE;
    }
    if(!m_pResourceFactory || !m_pQualityMgr) {
        // the resource factory is not set
        return FG_FALSE;
    }
    if(!m_dataDir)
        m_dataDir = new util::CDirent();
    // Fix me - universal paths - use pwd or something
    // #FIXME - compatibility for different platforms
    m_dataDir->readDir("./", FG_TRUE, FG_TRUE);
    m_dataDir->rewind();
    FG_LOG_DEBUG("Resource: Initializing resource manager. Current maximum memory: %.2f MiB", (float)m_nMaximumMemory / 1024.0 / 1024.0); // #TODELETE
    // First of all load any resource group configs,
    // file extension is *.rgrp and it's a xml file.
    std::string filepath;
    CStringVector resGroupFiles;
    // #FIXME - well this looks kinda bad, probably loading
    // resource groups files should look different - must be
    // more universal - platform independent, check for
    // correct paths in the environment, etc.
    while(m_dataDir->searchForFile(filepath, std::string("./"), std::string("*group.xml;*group.ini"), FG_TRUE).length()) {
        resGroupFiles.push_back(filepath);
    }

    if(resGroupFiles.size() == 0) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_RESOURCE_NO_GROUPS, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    for(unsigned int i = 0; i < resGroupFiles.size(); i++) {
        // #FIXME - should resource manager hold separate array for res groups IDS ? oh my ...
        ResourceHandle grpUniqueID;
        CResourceGroup *resGroup = new CResourceGroup(m_pResourceFactory);
        // #TODO this will not always look like this - requires full path (cross platform)
        FG_LOG_DEBUG("Resource: Loading resource group file: '%s'", resGroupFiles[i].c_str());
        resGroup->setFilePath(resGroupFiles[i].c_str());
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
        insertResource(resGroup);
        grpUniqueID = resGroup->getHandle();
        // There is a separate holder for resource group
        insertResourceGroup(grpUniqueID, resGroup);
        // Force create - some resource groups have this special flag
        // This means that when resource group is pre-cached the resources
        // in this group will be created - additional memory will be allocated
        const fgBool forceCreate = resGroup->isForceCreate();
        CResourceGroup::rgResVec& resInGrp = resGroup->getRefResourceFiles();
        for(CResourceGroup::rgResVecItor it = resInGrp.begin(); it != resInGrp.end(); it++) {
            (*it)->setQuality(static_cast<CQualityManager *>(m_pQualityMgr)->getQuality());
            insertResource((*it));
            if(forceCreate) {
                refreshResource((*it));
            }
        }
        // This is really important - refresh array with resource handles
        resGroup->refreshArrays();
    }
    FG_LOG_DEBUG("Resource: Pre cached %d resource group files.", resGroupFiles.size());
    FG_LOG_DEBUG("Resource: Current number of cached resources: %d, total: %d bytes [%d KiB]",
                 (int)getUsedHandleCount(),
                 (int)m_nCurrentUsedMemory,
                 (int)m_nCurrentUsedMemory / 1024);
#if defined(FG_DEBUG)
    // With debug mode - printout the names of the resources and their size in bytes/kbytes
    this->goToBegin();
    do {
        CResource *pResource = this->getCurrentResource();
        if(pResource) {
            FG_LOG_DEBUG("Resource[%.3d]: name[%s], size: %d bytes [%d KiB]",
                         pResource->getHandle().getIndex(),
                         pResource->getNameStr(),
                         (int)pResource->getSize(),
                         (int)pResource->getSize() / 1024);
        }
    } while(this->goToNext());
#endif /* FG_DEBUG */
    resGroupFiles.clear();
    goToBegin();
    m_init = FG_TRUE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::setMaximumMemory(size_t nMaxSize) {
    m_nMaximumMemory = nMaxSize;
    return checkForOverallocation();
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::reserveMemory(size_t nMem) {
    addMemory(nMem);
    if(!checkForOverallocation())
        return FG_FALSE;
    m_bResourceReserved = FG_TRUE;
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::goToNext(ResourceType resType) {
    while(FG_TRUE) {
        m_currentResource++;
        if(!isValid()) {
            break;
        }
        if(!(*m_currentResource).data)
            continue;
        if((*m_currentResource).data->getResourceType() == resType) {
            break;
        }
    }

    return isValid();
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::goToNext(const ResourceType* resTypes, int n) {
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
            if(i == n || resTypes[i] == resource::INVALID)
                break;
            if((*m_currentResource).data->getResourceType() == resTypes[i]) {
                status = FG_TRUE;
            }
            i++;
        }
        if(status == FG_TRUE)
            break;
    }

    return isValid();
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::goToNext(ResourceType resType, Quality quality) {
    while(FG_TRUE) {
        goToNext();
        if(!isValid()) {
            break;
        }
        if((*m_currentResource).data->getResourceType() == resType) {
            if((*m_currentResource).data->getQuality() == quality) {
                break;
            }
        }
    }

    return isValid();
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::insertResource(CResource* pResource) {
    if(!pResource) {
        return FG_FALSE;
    }
    if(!base_type::insert(pResource, pResource->getName())) {
        return FG_FALSE;
    }
    pResource->setManaged(FG_TRUE);
    pResource->setManager(this);
    // Get the memory and add it to the catalog total.  Note that we only have
    // to check for memory overallocation if we haven't preallocated memory
    if(!m_bResourceReserved) {
        addMemory(pResource->getSize()); // ? nope
        // check to see if any overallocation has taken place
        if(!checkForOverallocation())
            return FG_FALSE;
    } else
        m_bResourceReserved = FG_FALSE;

    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::insertResourceGroup(const ResourceHandle& rhUniqueID,
                                                       CResource* pResource) {
    if(!CDataManagerBase::isManaged(pResource)) {
        return FG_FALSE;
    }
    if(m_resourceGroupHandles.find(rhUniqueID) != -1) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_GROUP_IN_VECTOR, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    m_resourceGroupHandles.push_back(rhUniqueID);
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::remove(const ResourceHandle& rhUniqueID) {
    return CResourceManager::remove(CDataManagerBase::get(rhUniqueID));
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::remove(const std::string& nameTag) {
    return CResourceManager::remove(CDataManagerBase::get(nameTag));
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::remove(const char *nameTag) {
    return CResourceManager::remove(CDataManagerBase::get(nameTag));
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::remove(CResource* pResource) {
    if(!CDataManagerBase::isManaged(pResource))
        return FG_FALSE;
    // if the resource was found, check to see that it's not locked
    if(pResource->isLocked()) {
        // Can't remove a locked resource
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_LOCKED_REMOVAL, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    // Get the memory and subtract it from the manager total
    removeMemory(pResource->getSize());
    releaseHandle(pResource->getHandle());
    return FG_TRUE;
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::dispose(const ResourceHandle& rhUniqueID) {
    return dispose(CDataManagerBase::get(rhUniqueID));
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::dispose(const std::string& nameTag) {
    return dispose(CDataManagerBase::get(nameTag));
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::dispose(const char *nameTag) {
    return dispose(CDataManagerBase::get(nameTag));
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::dispose(CResource* pResource) {
    if(!CDataManagerBase::isManaged(pResource))
        return FG_FALSE;
    // if the resource was found, check to see that it's not locked
    if(pResource->isLocked()) {
        // Can't remove a locked resource
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_LOCKED_REMOVAL, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    unsigned int nDisposalSize = pResource->getSize();
    pResource->dispose();
    if(pResource->isDisposed()) {
        // Get the memory and subtract it from the manager total
        removeMemory(nDisposalSize);
    } else {
        // For some reason the resource is not disposed
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_RESOURCE_NOT_DISPOSED, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void resource::CResourceManager::refreshResource(CResource* pResource) {
    if(!pResource)
        return;

    // You may need to add your own OS dependent method of getting
    // the current time to set your resource access time

    // Set the current time as the last time the object was accessed
    pResource->setLastAccess(time(0));

    // Recreate the object before giving it to the application
    if(pResource->isDisposed()) {
        if(m_pQualityMgr)
            pResource->setQuality(static_cast<CQualityManager *>(m_pQualityMgr)->getQuality());

        pResource->recreate();
        if(!pResource->isDisposed() && m_pEventMgr) {
            //event::SResource *resEvent = fgMalloc<event::SResource>();
            event::SResource *resEvent = (event::SResource*)static_cast<event::CEventManager *>(m_pEventMgr)->requestEventStruct();
            event::CArgumentList *argList = static_cast<event::CEventManager *>(m_pEventMgr)->requestArgumentList();
            resEvent->eventType = event::RESOURCE_CREATED;
            resEvent->timeStamp = timesys::ticks();
            resEvent->status = event::SResource::CREATED;
            resEvent->resource = pResource;

            //event::CArgumentList *argList = new event::CArgumentList();
            argList->push(event::SArgument::Type::ARG_TMP_POINTER, (void *)resEvent);
            static_cast<event::CEventManager *>(m_pEventMgr)->throwEvent(event::RESOURCE_CREATED, argList);
        }
        addMemory(pResource->getSize());

        // check to see if any overallocation has taken place, but
        // make sure we don't swap out the same resource.
        pResource->Lock();
        checkForOverallocation();
        pResource->Unlock();
    }
}
//------------------------------------------------------------------------------

resource::CResource* resource::CResourceManager::get(const ResourceHandle& rhUniqueID) {
    resource::CResource *pResource = CDataManagerBase::get(rhUniqueID);
    if(!pResource) {
        return NULL;
    }
    resource::CResourceManager::refreshResource(pResource);
    // return the object pointer
    return pResource;
}
//------------------------------------------------------------------------------

resource::CResource* resource::CResourceManager::get(const std::string& nameTag) {
    CResource *pResource = CDataManagerBase::get(nameTag);
    if(!pResource) {
        return NULL;
    }
    CResourceManager::refreshResource(pResource);
    // return the object pointer
    return pResource;
}
//------------------------------------------------------------------------------

resource::CResource* resource::CResourceManager::get(const char *nameTag) {
    return CResourceManager::get(std::string(nameTag));
}
//------------------------------------------------------------------------------

resource::CResource* resource::CResourceManager::request(const std::string& info) {
    return request(info, AUTO);
}
//------------------------------------------------------------------------------

resource::CResource* resource::CResourceManager::request(const char *info) {
    return request(std::string(info), AUTO);
}
//------------------------------------------------------------------------------

resource::CResource* resource::CResourceManager::request(const std::string& info,
                                                         const ResourceType forcedType) {
    if(!m_dataDir || !m_init || !m_pResourceFactory || info.empty())
        return NULL;
    CResource *resourcePtr = NULL;
    // This is a fallback, if such resource already exists in the resource manager
    // it should not be searched and reloaded - however do not use request() in a main
    // loop as it may be slower
    resourcePtr = CResourceManager::get(info);
    if(resourcePtr) {
        // This print will flood output
        //FG_LOG_DEBUG("Resource: Found requested resource: name[%s], request[%s]", resourcePtr->getNameStr(), info.c_str());
        return resourcePtr;
    }
    // info cannot be a path, it has to be resource name or config name
    // required file will be found
    if(strings::containsChars(info, std::string("/\\"))) {
        FG_LOG_ERROR("Resource: Request cannot contain full path: '%s'", info.c_str());
        return NULL;
    }

    std::string pattern;
    std::string filePath;
    ResourceType resExtType = resource::INVALID;
    fgBool infoAsName = FG_FALSE;
    fgBool isFound = FG_FALSE;
    fgBool isConfig = FG_FALSE;

    const char *iext = fg::path::fileExt(info.c_str(), FG_TRUE);
    if(!iext) { // no extension given so... search all
        infoAsName = FG_TRUE;
        pattern.append(info).append(".*;");
    } else { // extension is given, search for exact file
        pattern.append(info);
    }

    // Search file names of resources already in cache
    if(!infoAsName && iext) {
        // This is special search for filename within already loaded resources
        goToBegin();
        while(isValid()) {
            CResource *res = getCurrentResource();
            if(!res) {
                goToNext();
                continue;
            }
            CResource::FileMapping &files = res->getFileMapping();
            CResource::FileMappingItor fit = files.begin(), fend = files.end();
            for(; fit != fend; fit++) {
                // Comparing using endsWith - resource contains relative file paths
                // not just file name - this request function takes in just file names
                // resource names or patterns (wildcards for extensions)
                if(strings::endsWith(fit->second, pattern, FG_TRUE)) {
                    //if(fit->second.compare(pattern) == 0) {
                    // Found resource containing specified file
                    CResourceManager::refreshResource(res);
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
            fext = fg::path::fileExt(filePath.c_str(), FG_TRUE);
        }

        if(strings::endsWith(fext, "res.ini", FG_TRUE)) {
            isConfig = FG_TRUE;
        } else if(strings::endsWith(fext, "tga", FG_TRUE)) {
            resExtType = resource::TEXTURE;
        } else if(strings::endsWith(fext, "jpg", FG_TRUE)) {
            resExtType = resource::TEXTURE;
        } else if(strings::endsWith(fext, "png", FG_TRUE)) {
            resExtType = resource::TEXTURE;
        } else if(strings::endsWith(fext, "obj", FG_TRUE)) {
            resExtType = resource::MODEL3D;
        } else if(strings::endsWith(fext, "wav", FG_TRUE)) {
            resExtType = resource::SOUND;
        } else if(strings::endsWith(fext, "mp3", FG_TRUE)) {
            resExtType = resource::MUSIC;
        } else if(strings::endsWith(fext, "mod", FG_TRUE)) {
            resExtType = resource::MUSIC;
        } else if(strings::endsWith(fext, "raw", FG_TRUE)) {
            // marmalade #FIXME
            resExtType = resource::SOUND;
        } else if(strings::endsWith(fext, "particle.ini", FG_TRUE)) {
            resExtType = resource::PARTICLE_EFFECT;
        } else {
        }

        if(resExtType != resource::INVALID || isConfig) {
            isFound = FG_TRUE;
            break;
        }
    };

    if(!isFound)
        return NULL;
    if(isConfig) {
        CResourceConfig *resCfg = new CResourceConfig();
        // This references to external config file, config should be loaded and proper resource created
        if(!resCfg->load(filePath.c_str())) {
            delete resCfg;
            // MESSAGE?
            return NULL;
        }
        // THIS CODE IS REALLY SIMILAR TO THE ONE IN RESOURCE GROUP
        // NEED TO THINK OF A WAY TO NOT REPEAT THIS CHUNK OF CODE
        // SHOULD RESOURCE GROUP HAVE SOME ACCESS TO THIS RES MGR?
        SResourceHeader *header = &resCfg->getRefHeader();
        if(m_pResourceFactory->isRegistered(header->resType)) {
            resourcePtr = m_pResourceFactory->createResource(header->resType);
            resourcePtr->setName(header->name);
            resourcePtr->setFlags(header->flags);
            resourcePtr->setPriority(header->priority);
            resourcePtr->setQuality(header->quality);

            if(header->paths.size() != header->qualities.size()) {
                FG_LOG_ERROR("Group config: number of qualities doesn't match number of files for: '%s'", header->name.c_str());
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
    } else if(resExtType != resource::INVALID) {
        if(forcedType != AUTO)
            resExtType = forcedType;
        if(m_pResourceFactory->isRegistered(resExtType)) {
            resourcePtr = m_pResourceFactory->createResource(resExtType);
            resourcePtr->setName(info);
            resourcePtr->setPriority(ResourcePriority::LOW);
            resourcePtr->setQuality(Quality::UNIVERSAL);
            resourcePtr->setDefaultID(Quality::UNIVERSAL);
            resourcePtr->setFilePath(filePath);
            FG_LOG_DEBUG("Resource: Requested resource: '%s'", filePath.c_str());
        }
    }

    if(resourcePtr) {
        if(!insertResource(resourcePtr)) {
            releaseHandle(resourcePtr->getHandle());
            delete resourcePtr;
            resourcePtr = NULL;
            return NULL;
        }
        // This will recreate the resource if necessary and throw proper event
        // if the pointer to the external event manager is set.
        CResourceManager::refreshResource(resourcePtr);
        if(m_pEventMgr) {
            // #FIXME ! ! ! !
            //event::SResource *resEvent = fgMalloc<event::SResource>();
            event::SResource *resEvent = (event::SResource*)static_cast<event::CEventManager *>(m_pEventMgr)->requestEventStruct();
            event::CArgumentList *argList = static_cast<event::CEventManager *>(m_pEventMgr)->requestArgumentList();
            resEvent->eventType = event::RESOURCE_REQUESTED;
            resEvent->timeStamp = timesys::ticks();
            resEvent->status = event::SResource::REQUESTED;
            resEvent->resource = resourcePtr;

            //event::CArgumentList *argList = new event::CArgumentList();
            argList->push(event::SArgument::Type::ARG_TMP_POINTER, (void *)resEvent);
            static_cast<event::CEventManager *>(m_pEventMgr)->throwEvent(event::RESOURCE_REQUESTED, argList);
        }
    }
    return resourcePtr;
}
//------------------------------------------------------------------------------

resource::CResource* resource::CResourceManager::request(const char *info, const ResourceType forcedType) {
    return request(std::string(info), forcedType);
}
//------------------------------------------------------------------------------

resource::CResource* resource::CResourceManager::lockResource(const ResourceHandle& rhUniqueID) {
    CResource *pResource = CDataManagerBase::get(rhUniqueID);
    lockResource(pResource);
    // return the object pointer
    return pResource;
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::lockResource(resource::CResource *pResource) {
    if(!CDataManagerBase::isManaged(pResource)) {
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
//------------------------------------------------------------------------------

resource::CResource* resource::CResourceManager::unlockResource(const ResourceHandle& rhUniqueID) {
    CResource *pResource = CDataManagerBase::get(rhUniqueID);
    pResource->Unlock();
    return pResource;
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::unlockResource(resource::CResource *pResource) {
    if(!CDataManagerBase::isManaged(pResource)) {
        return FG_FALSE;
    }
    if(pResource->getReferenceCount() == 0) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_TOO_MANY_UNLOCKS, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    pResource->Unlock();
    return FG_TRUE;
}
//------------------------------------------------------------------------------

void resource::CResourceManager::refreshMemory(void) {
    resetMemory();
    DataVecItor begin = getRefDataVector().begin(), end = getRefDataVector().end();
    for(DataVecItor itor = begin; itor != end; ++itor) {
        if(!(*itor).data)
            continue;
        addMemory((*itor).data->getSize());
    }
}
//------------------------------------------------------------------------------

fgBool resource::CResourceManager::checkForOverallocation(void) {
    if(m_nCurrentUsedMemory > m_nMaximumMemory) {
        resetMemory();
        // create a temporary priority queue to store the managed items
        CPriorityQueue<CResource*, std::vector<CResource*>, fgPtrGreater<CResource*> > priorityResQ;
        DataVecItor begin = getRefDataVector().begin(), end = getRefDataVector().end();

        // insert copies of all the resource pointers into the priority queue, but
        // exclude those that are current disposed or are locked
        for(DataVecItor itor = begin; itor != end; ++itor) {
            if(!(*itor).data)
                continue;
            addMemory((*itor).data->getSize());
            if(!(*itor).data->isDisposed() && !(*itor).data->isLocked())
                priorityResQ.push((*itor).data);
        }
        // Attempt to remove iMemToPurge bytes from the managed resource
        const int iMemToPurge = m_nCurrentUsedMemory - m_nMaximumMemory;
        while((!priorityResQ.empty()) && (m_nCurrentUsedMemory > m_nMaximumMemory)) {
            unsigned int nDisposalSize = priorityResQ.top()->getSize();
            // Dispose of the all loaded data, free all memory, but don't destroy the object
            priorityResQ.top()->dispose();
            if(priorityResQ.top()->isDisposed())
                removeMemory(nDisposalSize);
            priorityResQ.pop();
        }

        // If the resource queue is empty and we still have too much memory allocated,
        // then we return failure.  This could happen if too many resources were locked
        // or if a resource larger than the requested maximum memory was inserted.
        if(priorityResQ.empty() && (m_nCurrentUsedMemory > m_nMaximumMemory)) {
            FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_RESOURCE_OVERALLOCATION);
            return FG_FALSE;
        }
    }
    return FG_TRUE;
}
//------------------------------------------------------------------------------
