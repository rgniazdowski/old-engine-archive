/*******************************************************
 * Copyright (C) 2014 Radoslaw Gniazdowski <r.gniazdowski@gmail.com>. All rights reserved.
 * 
 * This file is part of FlexiGame: Flexible Game Engine
 * 
 * FlexiGame source code and any related files can not be copied, modified 
 * and/or distributed without the express or written consent from the author.
 *******************************************************/

#ifndef FG_INC_DATA_MANAGER_BASE
    #define FG_INC_DATA_MANAGER_BASE

    #include "fgManagerBase.h"
    #include "Util/fgHandleManager.h"
    #include "fgResourceErrorCodes.h"
    
    #include "fgMessageSubsystem.h"

    #define FG_MANAGER_DATA_BASE    0x00000080

/**
 *
 */
template <typename DataType, typename HandleType, typename TagType>
class fgDataManagerBase : public fgManagerBase, protected fgHandleManager<DataType, HandleType> {
public:
    typedef TagType tag_type;
    typedef HandleType handle_type;
    typedef fgHandleManager<DataType, HandleType> handle_mgr_type;
        
public:
    /**
     * 
     */
    fgDataManagerBase() {
        m_managerType = FG_MANAGER_DATA_BASE;
    }
    /**
     * 
     */
    virtual ~fgDataManagerBase() {
        clear();
    }

protected:
    /**
     * 
     */
    virtual void clear(void);

public:
    /**
     * 
     * @return 
     */
    virtual fgBool destroy(void) = 0;
    /**
     * 
     * @return 
     */
    virtual fgBool initialize(void) = 0;

    /**
     * 
     * @param dhUniqueID
     * @param pData
     * @param nameTag
     * @return 
     */
    virtual fgBool insert(DataType pData, const std::string& nameTag);

    /**
     * 
     * @param pData
     * @return 
     */
    virtual fgBool remove(DataType pData);
    /**
     * 
     * @param dhUniqueID
     * @return 
     */
    virtual fgBool remove(const HandleType& dhUniqueID);
    /**
     * 
     * @param nameTag
     * @return 
     */
    virtual fgBool remove(const std::string& nameTag);
    /**
     * 
     * @param nameTag
     * @return 
     */
    virtual fgBool remove(const char *nameTag);

    /**
     * 
     * @param pData
     * @return 
     */
    virtual fgBool destroyData(DataType& pData);
    /**
     * 
     * @param dhUniqueID
     * @return 
     */
    virtual fgBool destroyData(const HandleType& dhUniqueID);
    /**
     * 
     * @param nameTag
     * @return 
     */
    virtual fgBool destroyData(const std::string& nameTag);
    /**
     * 
     * @param nameTag
     * @return 
     */
    virtual fgBool destroyData(const char *nameTag);

    /**
     * 
     * @param dhUniqueID
     * @return 
     */
    virtual DataType get(const HandleType& dhUniqueID);
    /**
     * 
     * @param nameTag
     * @return 
     */
    virtual DataType get(const std::string& nameTag);
    /**
     * 
     * @param nameTag
     * @return 
     */
    virtual DataType get(const char *nameTag);

    /**
     * 
     * @param info
     * @return 
     */
    virtual DataType request(const std::string& info) = 0;
    /**
     * 
     * @param info
     * @return 
     */
    virtual DataType request(const char *info) = 0;

    /**
     * 
     * @param pData
     * @return 
     */
    virtual fgBool isManaged(DataType pData);
    /**
     * 
     * @param dhUniqueID
     * @return 
     */
    virtual fgBool isManaged(const HandleType& dhUniqueID);
    /**
     * 
     * @param nameTag
     * @return 
     */
    virtual fgBool isManaged(const std::string& nameTag);
    /**
     * 
     * @param nameTag
     * @return 
     */
    virtual fgBool isManaged(const char *nameTag);
};
/**
 * 
 */
template <typename DataType, typename HandleType, typename TagType>
void fgDataManagerBase<DataType, HandleType, TagType>::clear(void) {
    fgHandleManager<DataType, HandleType>::releaseAllHandles();
}
/**
 * 
 * @param dhUniqueID
 * @param pData
 * @param nameTag
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::insert(DataType pData, const std::string& nameTag) {
    if(!pData) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_RESOURCE_PARAMETER_NULL, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    HandleType dhUniqueID;
    if(fgHandleManager<DataType, HandleType>::isDataManaged(pData)) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_ALREADY_MANAGED, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }

    if(!pData->getHandle().isNull()) {
        // Resource has already initialized handle
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_INITIALIZED_HANDLE, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    // Acquire next valid resource handle
    // Insert the resource into the current catalog
    if(!fgHandleManager<DataType, HandleType>::acquireHandle(dhUniqueID, pData)) {
        // Could not aquire handle for the resource
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_ACQUIRE_HANDLE, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    // This is important - on addition need to update the handle
    pData->setHandle(dhUniqueID);
    if(!fgHandleManager<DataType, HandleType>::setupName(nameTag, dhUniqueID)) {
        // Could not setup handle string tag/name for the resource
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_SETUP_HANDLE_NAME, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    return FG_TRUE;
}
/**
 * 
 * @param pData
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::remove(DataType pData) {
    if(!fgDataManagerBase<DataType, HandleType, TagType>::isManaged(pData)) {
        return FG_FALSE;
    }
    return fgHandleManager<DataType, HandleType>::releaseHandle(pData->getHandle());
}
/**
 * 
 * @param dhUniqueID
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::remove(const HandleType& dhUniqueID) {
    DataType pData = fgDataManagerBase<DataType, HandleType, TagType>::get(dhUniqueID);
    if(!pData)
        return FG_FALSE;
    return fgHandleManager<DataType, HandleType>::releaseHandle(pData->getHandle());
}
/**
 * 
 * @param nameTag
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::remove(const std::string& nameTag) {
    DataType pData = fgDataManagerBase<DataType, HandleType, TagType>::get(nameTag);
    if(!pData)
        return FG_FALSE;
    return fgHandleManager<DataType, HandleType>::releaseHandle(pData->getHandle());
}
/**
 * 
 * @param nameTag
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::remove(const char *nameTag) {
    DataType pData = fgDataManagerBase<DataType, HandleType, TagType>::get(nameTag);
    if(!pData)
        return FG_FALSE;
    return fgHandleManager<DataType, HandleType>::releaseHandle(pData->getHandle());
}
/**
 * 
 * @param pData
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::destroyData(DataType& pData) {
    if(!remove(pData)) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_REMOVE);
        return FG_FALSE;
    }
    delete pData;
    pData = NULL;
    return FG_TRUE;
}
/**
 * 
 * @param dhUniqueID
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::destroyData(const HandleType& dhUniqueID) {
    DataType pData = fgHandleManager<DataType, HandleType>::dereference(dhUniqueID);
    if(!remove(pData)) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_REMOVE);
        return FG_FALSE;
    }
    delete pData;
    return FG_TRUE;
}
/**
 * 
 * @param nameTag
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::destroyData(const std::string& nameTag) {
    DataType pData = fgHandleManager<DataType, HandleType>::dereference(nameTag);
    if(!remove(pData)) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_REMOVE);
        return FG_FALSE;
    }
    delete pData;
    return FG_TRUE;
}
/**
 * 
 * @param nameTag
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::destroyData(const char *nameTag) {
    DataType pData = fgHandleManager<DataType, HandleType>::dereference(nameTag);
    if(!remove(pData)) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_REMOVE);
        return FG_FALSE;
    }
    delete pData;
    return FG_TRUE;
}
/**
 * 
 * @param dhUniqueID
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
DataType fgDataManagerBase<DataType, HandleType, TagType>::get(const HandleType& dhUniqueID) {
    DataType pData = fgHandleManager<DataType, HandleType>::dereference(dhUniqueID);
    return pData;
}
/**
 * 
 * @param nameTag
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
DataType fgDataManagerBase<DataType, HandleType, TagType>::get(const std::string& nameTag) {
    if(nameTag.empty()) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_RESOURCE_NAME_TAG_EMPTY, FG_MSG_IN_FUNCTION);
        return NULL;
    }
    DataType pData = fgHandleManager<DataType, HandleType>::dereference(nameTag);
    if(!pData) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_NAME_TAG_INVALID, " tag='%s', in function: %s", nameTag.c_str(), __FUNCTION__);
        return NULL;
    }
    return pData;
}
/**
 * 
 * @param nameTag
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
DataType fgDataManagerBase<DataType, HandleType, TagType>::get(const char *nameTag) {
    DataType pData = fgHandleManager<DataType, HandleType>::dereference(nameTag);
    return pData;
}
/**
 * 
 * @param pData
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::isManaged(DataType pData) {
    if(!pData) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_RESOURCE_PARAMETER_NULL, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    if(FG_IS_INVALID_HANDLE(pData->getHandle())
            || !fgHandleManager<DataType, HandleType>::isHandleValid(pData->getHandle())) {
        FG_MessageSubsystem->reportError(tag_type::name(), FG_ERRNO_RESOURCE_HANDLE_INVALID, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    if(!fgHandleManager<DataType, HandleType>::isDataManaged(pData)) {
        FG_MessageSubsystem->reportWarning(tag_type::name(), FG_ERRNO_RESOURCE_NOT_MANAGED, FG_MSG_IN_FUNCTION);
        return FG_FALSE;
    }
    return FG_TRUE;
}
/**
 * 
 * @param dhUniqueID
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::isManaged(const HandleType& dhUniqueID) {
    DataType pData = fgDataManagerBase<DataType, HandleType, TagType>::get(dhUniqueID);
    return (fgBool)(pData != NULL);
}
/**
 * 
 * @param nameTag
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::isManaged(const std::string& nameTag) {
    DataType pData = fgDataManagerBase<DataType, HandleType, TagType>::get(nameTag);
    return (fgBool)(pData != NULL);
}
/**
 * 
 * @param nameTag
 * @return 
 */
template <typename DataType, typename HandleType, typename TagType>
fgBool fgDataManagerBase<DataType, HandleType, TagType>::isManaged(const char *nameTag) {
    DataType pData = fgDataManagerBase<DataType, HandleType, TagType>::get(nameTag);
    return (fgBool)(pData != NULL);
}

#endif /* FG_INC_DATA_MANAGER_BASE */
